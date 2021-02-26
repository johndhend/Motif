
#include <localdef.h>

/* 
 *  @OPENGROUP_COPYRIGHT@
 *  COPYRIGHT NOTICE
 *  Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 *  Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 *  ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
 *  the full copyright text.
 *  
 *  This software is subject to an open license. It may only be
 *  used on, with or for operating systems which are themselves open
 *  source systems. You must contact The Open Group for a license
 *  allowing distribution and sublicensing of this software on, with,
 *  or for operating systems which are not Open Source programs.
 *  
 *  See http://www.opengroup.org/openmotif/license for full
 *  details of the license agreement. Any use, reproduction, or
 *  distribution of the program constitutes recipient's acceptance of
 *  this agreement.
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 *  PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 *  WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 *  OR FITNESS FOR A PARTICULAR PURPOSE
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 *  NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 *  EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGES.
 */ 
/* 
 * HISTORY
 */ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: CallbackI.c /main/8 1995/07/14 10:13:10 drk $"
#endif
#endif
/* (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */



#include "CallbackI.h"


/********************************************************************
 * VendorShell and Dialog Shell's extension objects are no longer 
 * full fledged Xt objects and therefore  cannot be passed as an
 * argument  to the Xt calls XtAddCallback(), XtRemoveCallback(),
 * and XtCallCallbackList(). The functions _XmAddCallback()
 * _XmRemoveCallback() and _XmCallCallbackList() replace these 
 * Xt calls for non Xt objects.
 ********************************************************************/


/* However it doesn't contain a final NULL record */
#define ToList(p)	((XtCallbackList) (&(p)->callbacks))

void
_XmAddCallback(InternalCallbackList* callbacks,
	       XtCallbackProc        callback,
	       XtPointer             closure)
{
  register XtCallbackList cl;
  register InternalCallbackList icl = *callbacks;
  register int count = icl ? icl->count : 0;
  
  if (icl && icl->call_state) 
    {
      icl->call_state |= _XtCBFreeAfterCalling;
      icl = (InternalCallbackList)
	XtMalloc(sizeof(InternalCallbackRec) + sizeof(XtCallbackRec) * count);
      
      memcpy((char *)ToList(icl), (char *)ToList(*callbacks),
	     sizeof(XtCallbackRec) * count);
    } 
  else 
    {
      icl = (InternalCallbackList)
	XtRealloc((char *) icl, sizeof(InternalCallbackRec) +
		  sizeof(XtCallbackRec) * count);
    }

  *callbacks = icl;
  icl->count = count + 1;
  icl->is_padded = 0;
  icl->call_state = 0;
  cl = ToList(icl) + count;
  cl->callback = callback;
  cl->closure = closure;
}

void
 _XmRemoveCallback (InternalCallbackList *callbacks,
		    XtCallbackProc        callback,
		    XtPointer             closure)
{
  register int i, j;
  register XtCallbackList cl, ncl, ocl;
  register InternalCallbackList icl = *callbacks;

  if (!icl) 
    return;
  
  cl = ToList(icl);
  for (i = icl->count; --i >= 0; cl++) 
    {
      if (cl->callback == callback && cl->closure == closure) 
	{
	  if (icl->call_state) 
	    {
	      icl->call_state |= _XtCBFreeAfterCalling;
	      if (icl->count == 1) 
		{
		  *callbacks = NULL;
		} 
	      else 
		{
		  j = icl->count - i - 1;
		  ocl = ToList(icl);
		  icl = (InternalCallbackList)
		    XtMalloc(sizeof(InternalCallbackRec) +
			     sizeof(XtCallbackRec) * (i + j - 1));
		  icl->count = i + j;
		  icl->is_padded = 0;
		  icl->call_state = 0;
		  ncl = ToList(icl);
		  while (--j >= 0)
		    *ncl++ = *ocl++;
		  while (--i >= 0)
		    *ncl++ = *++cl;
		  *callbacks = icl;
		}
	    }
	  else 
	    {
	      if (--icl->count) 
		{
		  ncl = cl + 1;
		  while (--i >= 0)
		    *cl++ = *ncl++;
		  icl = (InternalCallbackList)
		    XtRealloc((char *) icl, sizeof(InternalCallbackRec)
			      + sizeof(XtCallbackRec) * (icl->count - 1));
		  icl->is_padded = 0;
		  *callbacks = icl;
		} else {
		  XtFree((char *) icl);
		  *callbacks = NULL;
		}
	    }
	  return;
	}
    }
}

void
_XmRemoveAllCallbacks(InternalCallbackList *callbacks)
{
  register InternalCallbackList icl = *callbacks;
  
  if (icl) 
    {
      if (icl->call_state)
	icl->call_state |= _XtCBFreeAfterCalling;
      else
	XtFree((char *) icl);

      *callbacks = NULL;
    }
}

void 
_XmCallCallbackList(Widget widget,
		    XtCallbackList callbacks,
		    XtPointer call_data)
{
  register InternalCallbackList icl;
  register XtCallbackList cl;
  register int i;
  char ostate;
  
  if (!callbacks) 
    return;

  icl = (InternalCallbackList)callbacks;
  cl = ToList(icl);
  if (icl->count == 1) 
    {
      (*cl->callback) (widget, cl->closure, call_data);
      return;
    }

  ostate = icl->call_state;
  icl->call_state = _XtCBCalling;

  for (i = icl->count; --i >= 0; cl++)
    (*cl->callback) (widget, cl->closure, call_data);

  if (ostate)
    icl->call_state |= ostate;
  else if (icl->call_state & _XtCBFreeAfterCalling)
    XtFree((char *)icl);
  else
    icl->call_state = 0;
}
