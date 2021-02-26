
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
static char rcsid[] = "$XConsortium: UniqueEvnt.c /main/14 1996/11/25 11:33:58 pascale $"
#endif
#endif
/* (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#include <limits.h>
#include <Xm/XmP.h>
#include <Xm/DisplayP.h>
#include "UniqueEvnI.h"

#define XmCHECK_UNIQUENESS 1
#define XmRECORD_EVENT     2


/* XmUniqueStamp structure is per display */
typedef struct _XmUniqueStampRec
{
  unsigned long serial;
  Time time;
  int type;
} XmUniqueStampRec, *XmUniqueStamp;


/********    Static Function Declarations    ********/

static Time ExtractTime( 
                        XEvent *event) ;
static Boolean ManipulateEvent( 
                        XEvent *event,
                        int action) ;
static XmUniqueStamp GetUniqueStamp(
			XEvent *event ) ;
static void UniqueStampDisplayDestroyCallback(
			Widget w,
			XtPointer client_data,
			XtPointer call_data ) ;

/********    End Static Function Declarations    ********/


/************************************************************************
 *
 *  _XwExtractTime
 *     Extract the time field from the event structure.
 *
 ************************************************************************/
static Time 
ExtractTime(
        XEvent *event )
{
   if ((event->type == ButtonPress) || (event->type == ButtonRelease))
      return (event->xbutton.time);

   if ((event->type == KeyPress) || (event->type == KeyRelease))
      return (event->xkey.time);

   return ((Time) 0);
}

static Boolean
Later(unsigned long recorded,
      unsigned long new_l)
{
  long normalizedNew;

  /* The pathogenic cases for this calculation involve numbers
     very close to 0 or ULONG_MAX.  

     So the way we do it is by normalizing to 0 (signed).  That
     way the differences are +/- in the appropriate way.
     
     These numbers are defined as a unsigned long.  Please 
     remember that when changing this code.
     */

  normalizedNew = new_l - recorded;

  return (normalizedNew > 0);
}

static XmUniqueStamp
GetUniqueStamp(
	XEvent *event )
{
  XmDisplay xmDisplay = (XmDisplay)XmGetXmDisplay(event->xany.display);
  XmUniqueStamp uniqueStamp = (XmUniqueStamp)NULL;

  if ((XmDisplay)NULL != xmDisplay)
  {
    uniqueStamp = (XmUniqueStamp)((XmDisplayInfo *)(xmDisplay->display.
						displayInfo))->UniqueStamp;
    if ((XmUniqueStamp)NULL == uniqueStamp)
    {
      uniqueStamp = (XmUniqueStamp) XtMalloc(sizeof(XmUniqueStampRec));

      ((XmDisplayInfo *)(xmDisplay->display.displayInfo))->UniqueStamp = 
	(XtPointer)uniqueStamp;
      
      XtAddCallback((Widget)xmDisplay, XtNdestroyCallback,
		      UniqueStampDisplayDestroyCallback, (XtPointer) NULL);

      uniqueStamp->serial = 0;
      uniqueStamp->time = 0;
      uniqueStamp->type = 0;
    }
  }
  return uniqueStamp;
}

/*ARGSUSED*/
static void
UniqueStampDisplayDestroyCallback
        ( Widget w,
        XtPointer client_data,	/* unused */
        XtPointer call_data )	/* unused */
{
  XmDisplay xmDisplay = (XmDisplay)XmGetXmDisplay(XtDisplay(w));

  if ((XmDisplay)NULL != xmDisplay)
  {
    XmUniqueStamp uniqueStamp = (XmUniqueStamp)((XmDisplayInfo *)
			     (xmDisplay->display.displayInfo))->UniqueStamp;
    if ((XmUniqueStamp)NULL != uniqueStamp)
    {
      XtFree((char*)uniqueStamp);
      /* no need to set xmDisplay's displayInfo->UniqueStamp to NULL cause
       * it's being destroyed.
       */
    }
  }
}

static Boolean 
ManipulateEvent(
        XEvent *event,
        int action )
{
   XmUniqueStamp uniqueStamp = GetUniqueStamp(event);

   switch (action)
   {
      case XmCHECK_UNIQUENESS:
      {
	/*
	 * Ignore duplicate events, caused by an event being dispatched
	 * to both the focus widget and the spring-loaded widget, where
	 * these map to the same widget (menus).
	 * Also, ignore an event which has already been processed by
	 * another menu component.
	 * 
	 * Changed D.Rand 6/26/92 Discussion:
	 *
	 * This used to be done by making an exact comparison with
	 * a recorded event.  But there are many times when we can
	 * get an event,  but not the original event.  This cuts
	 * down on some distributed processing in the menu
	 * system.  
	 *
	 * So now we compare the serial number of the 
	 * examined event against the recorded event.  This needs
	 * to be done carefully to include the case where the
	 * serial number wraps
	 *
	 * 7/23/92 added discussion:
	 *
	 * The other case we must be careful of is when the serial
	 * number are the same.  This can only realistically occur
	 * if the user is very fast and therefore clicks while no
	 * protocol request occurs.  XSentEvent would cause an
	 * increment,  so we needn't worry over synthetic events
	 * causing problems.  
	 *
	 * So if the serial numbers match,  we use the timestamps.
	 */

	if ( Later(uniqueStamp->serial, event->xany.serial) 
	     ||  ( uniqueStamp->serial == event->xany.serial &&
		   Later(uniqueStamp->time, event->xbutton.time)))
	  return (TRUE);
	else
	  return (FALSE);
      }

      case XmRECORD_EVENT:
      {
         /* Save the fingerprints for the new event */
         uniqueStamp->type = event->type;
         uniqueStamp->serial = event->xany.serial;
         uniqueStamp->time = ExtractTime(event);

         return (TRUE);
      }

      default:
      {
         return (FALSE);
      }
   }
}


/*
 * Check to see if this event has already been processed.
 */
Boolean 
_XmIsEventUnique(
        XEvent *event )
{
   return (ManipulateEvent (event, XmCHECK_UNIQUENESS));
}



/*
 * Record the specified event, so that it will not be reprocessed.
 */
void 
_XmRecordEvent(
        XEvent *event )
{
   ManipulateEvent (event, XmRECORD_EVENT);
}
