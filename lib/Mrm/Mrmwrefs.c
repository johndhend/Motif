
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
static char rcsid[] = "$XConsortium: Mrmwrefs.c /main/14 1996/11/13 14:07:43 drk $"
#endif
#endif

/* (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */


/*
 *++
 *  FACILITY:
 *
 *      UIL Resource Manager (URM):
 *
 *  ABSTRACT:
 *
 *	This module contains all routines which manage references to
 *	widgets which must be handled during or immediately after
 *	widget creation.
 *
 *--
 */


/*
 *
 *  INCLUDE FILES
 *
 */

#include <stdio.h>
#include <Mrm/MrmAppl.h>
#include <Mrm/Mrm.h>
#include "MrmMsgI.h"


/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	routine acquires a resource context, and initializes
 *	it for use a a widget reference structure.
 *
 *  FORMAL PARAMETERS:
 *
 *	wref_id		to return pointer to initialized context
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *      See UrmGetResourceContext
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
Urm__CW_InitWRef (URMResourceContextPtr		*wref_id)
{
  Cardinal		result;		/* function results */
  URMWRefStructPtr	refdsc;		/* buffer as reference structure */


  /*
   * Acquire and initialize resource context
   */
  result = UrmGetResourceContext ((char *(*)())NULL,(void(*)())NULL, 
				  500, wref_id);
  if ( result != MrmSUCCESS ) return result;

  refdsc = (URMWRefStructPtr) UrmRCBuffer (*wref_id);
  refdsc->num_refs = 0;
  refdsc->heap_size = 0;

  return MrmSUCCESS;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine adds a widget definition to the widget reference structure
 *
 *  FORMAL PARAMETERS:
 *
 *	wref_id		widget reference structure
 *	w_name		name of the widget to enter
 *	w_id		widget id
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *      See UrmResizeResourceContext
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
Urm__CW_AddWRef (URMResourceContextPtr	wref_id,
		 String			w_name,
		 Widget			w_id)
{
  /*
   *  Local variables
   */
  Cardinal		result;		/* function results */
  URMWRefStructPtr	refdsc;		/* buffer as reference structure */
  MrmCount		name_bytes;	/* # bytes for name & NULL */
  MrmCount		bytes_needed;	/* # bytes for whole ref */
  Cardinal		ndx;		/* entry index in structure */
  MrmOffset		new_offs;	/* new offset in heap */
  Cardinal		old_size;	/* old buffer size */
  Cardinal		new_size;	/* new buffer size */
  Cardinal		delta;		/* difference in size */
  char			*old_heap;	/* old heap address */
  char			*new_heap;	/* new heap address */


  /*
   * Set up pointers. Compute size needed and available, and resize structure
   * if required. Name need not be entered if it is compiler-generated
   * (contains non-legal character '-')
   */
  refdsc = (URMWRefStructPtr) UrmRCBuffer (wref_id);
  name_bytes = strlen(w_name);
  for ( ndx=0 ; ndx<name_bytes ; ndx++ )
    if ( w_name[ndx] == '-' ) return MrmFAILURE;
  name_bytes += 1;

  bytes_needed = sizeof(URMWRef) + name_bytes;
  bytes_needed = _FULLWORD(bytes_needed);
  if ( bytes_needed > (UrmRCBufSize(wref_id)-UrmWRefBytesUsed(refdsc)) )
    {
      old_size = UrmRCBufSize (wref_id);
      new_size = 2 * old_size;
      delta = new_size - old_size;
      result = UrmResizeResourceContext (wref_id, new_size);
      if ( result != MrmSUCCESS ) return result;
      refdsc = (URMWRefStructPtr) UrmRCBuffer (wref_id);
      old_heap = (char *) refdsc+old_size-refdsc->heap_size;
      new_heap = (char *) (old_heap+delta);
      UrmBCopy (old_heap, new_heap, refdsc->heap_size);
      for ( ndx=0 ; ndx<refdsc->num_refs ; ndx++ )
	refdsc->refs[ndx].w_name_offs += delta;
    }

  /*
   * There is enough space. Copy in the name, and set up the descriptor.
   */
  new_offs = UrmRCBufSize(wref_id) - refdsc->heap_size - name_bytes;
  ndx = refdsc->num_refs;
  refdsc->refs[ndx].w_id = w_id;
  refdsc->refs[ndx].w_name_offs = new_offs;
  refdsc->num_refs += 1;
  refdsc->heap_size += name_bytes;
  strcpy ((String)refdsc+new_offs, w_name);

  return MrmSUCCESS;
}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine searches the widget reference structure for a widget,
 *	and returns its id if found.
 *
 *  FORMAL PARAMETERS:
 *
 *	wref_id		widget reference structure
 *	w_name		name of widget to be found
 *	w_id_return	to return widget id
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *      MrmSUCCESS	- found, id is returned
 *	MrmNOT_FOUND	- not found
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
Urm__CW_FindWRef (URMResourceContextPtr	wref_id,
		  String		w_name,
		  Widget		*w_id_return)
{
  /*
   *  Local variables
   */
  URMWRefStructPtr	refdsc;		/* buffer as reference structure */
  int			ndx;		/* loop index */


  /*
   * Search the vector for the name, returning the id if found. Search
   * backwards, so the most recent definitions are searched first.
   */
  refdsc = (URMWRefStructPtr) UrmRCBuffer (wref_id);
  for ( ndx=refdsc->num_refs-1 ; ndx>=0 ; ndx-- )
    if ( strcmp(w_name,UrmWRefNameN(refdsc,ndx)) == 0 )
      {
	*w_id_return = UrmWRefIdN (refdsc, ndx);
	return MrmSUCCESS;
      }
  return MrmNOT_FOUND;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine creates a SetValues descriptor, initializes it from
 *	the resource descriptor, and appends it to the list. The id of the
 *	widget to be modified is set NULL to identify this descriptor as
 *	one to be set.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		file from which to uncompress argtag
 *	svlist		list of SetValues of descriptor
 *	w_name		widget name
 *	argtag		Argument tag code
 *	argname		Argument tag name if code is URMcUnknown
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void 
Urm__CW_AppendSVWidgetRef (IDBFile		file_id,
			   URMPointerListPtr	*svlist,
			   String		w_name,
			   MrmCode		argtag,
			   String		argname)
{
  /*
   *  Local variables
   */
  URMSetValuesDescPtr	svdesc ;	/* new descriptor */
  Cardinal		uncmp_res;	/* function result */
  char			errmsg[300];


  /*
   * Initialize the pointer list if required
   */
  if ( *svlist == NULL )
    UrmPlistInit (10, svlist) ;

  /*
   * Create and set the new descriptor. The argument tag must be uncompressed
   * into its string now, when the compression code for it is available from the
   * file. If the tag code is unknown, then the string must be copied into
   * allocated memory.
   */
  svdesc = (URMSetValuesDescPtr) XtMalloc (sizeof(URMSetValuesDesc)) ;
  svdesc->setw = NULL ;
  svdesc->type = URMsvWidgetRef ;
  svdesc->tagcode = argtag ;
  if ( argtag == UilMrmUnknownCode )
    {
      svdesc->tagname = (String) XtMalloc (strlen(argname)+1);
      strcpy (svdesc->tagname, argname);
    }
  else
    {
      uncmp_res = Urm__UncompressCode (file_id, argtag, &svdesc->tagname);
      if ( uncmp_res != MrmSUCCESS )
	{
	  sprintf (errmsg, _MrmMMsg_0108, argtag);
	  XtFree ((char *)svdesc);
	  Urm__UT_Error ("Urm__CW_AppendSVWidgetRef", errmsg, 
			 NULL, NULL, MrmNOT_FOUND);
	  return;
	}
    }
  svdesc->done = FALSE ;
  svdesc->sv.wname = Urm__UT_AllocString (w_name) ;
  UrmPlistAppendPointer (( URMPointerListPtr)*svlist, (XtPointer) svdesc) ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine creates a SetValues descriptor, initializes it from
 *	the resource descriptor, adds the callback list and appends it to the
 *	list. The id of the
 *	widget to be modified is set NULL to identify this descriptor as
 *	one to be set.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		file from which to uncompress argtag
 *	svlist		list of SetValues of descriptor
 *	w_name		widget name
 *	argtag		Argument tag code
 *	argname		Argument tag name if code is URMcUnknown
 *	cbptr		Callback description pointer
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void 
Urm__CW_AppendCBSVWidgetRef (IDBFile			file_id,
			     URMPointerListPtr		*svlist,
			     RGMCallbackDescPtr		cbptr,
			     MrmCode			argtag,
			     String			argname)
{
  URMSetValuesDescPtr	svdesc ;	/* new descriptor */
  RGMCallbackDescPtr	cbdesc;		/* Copy of descriptor */
  MrmSize		descsize;	/* Size of descriptor to be copied */
  Cardinal		uncmp_res;	/* function result */
  char			errmsg[300];


  /*
   * Initialize the pointer list if required
   */
  if ( *svlist == NULL )
    UrmPlistInit (10, svlist) ;

  /*
   * Create and set the new descriptor. The argument tag must be uncompressed
   * into its string now, when the compression code for it is available from the
   * file. If the tag code is unknown, then the string must be copied into
   * allocated memory.
   */
  svdesc = (URMSetValuesDescPtr) XtMalloc (sizeof(URMSetValuesDesc)) ;
  svdesc->setw = NULL ;
  svdesc->type = URMsvCallBackList ;
  svdesc->tagcode = argtag ;
  if ( argtag == UilMrmUnknownCode )
    {
      svdesc->tagname = (String) XtMalloc (strlen(argname)+1);
      strcpy (svdesc->tagname, argname);
    }
  else
    {
      uncmp_res = Urm__UncompressCode (file_id, argtag, &svdesc->tagname);
      if ( uncmp_res != MrmSUCCESS )
	{
	  sprintf (errmsg, _MrmMMsg_0108, argtag);
	  XtFree ((char *)svdesc);
	  Urm__UT_Error ("Urm__CW_AppendCBSVWidgetRef", errmsg, 
			 NULL, NULL, MrmNOT_FOUND);
	  return;
	}
    }
  svdesc->done = FALSE ;
  /* Copy callback descriptor */
  descsize = sizeof(RGMCallbackDesc) + (cbptr->count)*sizeof(RGMCallbackItem);
  cbdesc = (RGMCallbackDescPtr)XtMalloc(descsize);
  memcpy(cbdesc, cbptr, descsize);
  svdesc->sv.callbacks = cbdesc ;
  UrmPlistAppendPointer (( URMPointerListPtr)*svlist, (XtPointer) svdesc) ;
}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine updates a SetValues list from a just-created widget.
 *	Any entry whose modified widget field is NULL is has the modified
 *	widget set to the given widget. 
 *
 *  FORMAL PARAMETERS:
 *
 *	svlist		List of SetValues descriptors
 *	cur_id		current widget to be entered in descriptors
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void 
Urm__CW_UpdateSVWidgetRef (URMPointerListPtr		*svlist,
			   Widget			cur_id)
{
  /*
   *  Local variables
   */
  int			ndx ;		/* loop index */
  URMSetValuesDescPtr	svdesc ;	/* current SetValues descriptor */

  /*
   * Loop over all descriptors. Enter the current widget as appropriate.
   * Since each descriptor is used only once, immediately free any
   * allocated tag string.
   */
  for ( ndx=0 ; ndx<UrmPlistNum(*svlist) ; ndx++ )
    {
      svdesc = (URMSetValuesDescPtr) UrmPlistPtrN(*svlist,ndx) ;
      if ( svdesc->done ) continue ;
      if ( svdesc->setw == NULL )
	svdesc->setw = cur_id ;
    }
}

/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine updates a SetValues list from a just-created widget.
 *	Any entry whose modified widget field is NULL is has the modified
 *	widget set to the given widget. It also uses this widget to
 *	immediately update any previously saved widget which can be
 *	resolved with this new widget and to update widget references
 *	in callback items.
 *
 *  FORMAL PARAMETERS:
 *
 *	svlist		List of SetValues descriptors
 *	cur_name	current widget's name
 *	cur_id		current widget to be entered in descriptors
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void 
Urm__CW_ResolveSVWidgetRef (URMPointerListPtr		*svlist,
			    String			cur_name,
			    Widget			cur_id)
{
  /*
   *  Local variables
   */
  int			ndx ;		/* loop index */
  int			cbndx;		/* callback list index */
  URMSetValuesDescPtr	svdesc ;	/* current SetValues descriptor */
  Arg			args[1] ;	/* SetValues argument list */
  RGMCallbackDescPtr	cbdesc;		/* Current callback descriptor */
  RGMCallbackItemPtr	items;		/* Array of callback items */

  /*
   * Loop over all descriptors. Enter the current widget as appropriate.
   * Since each descriptor is used only once, immediately free any
   * allocated tag string.
   */
  for ( ndx=0 ; ndx<UrmPlistNum(*svlist) ; ndx++ )
    {
      svdesc = (URMSetValuesDescPtr) UrmPlistPtrN(*svlist,ndx) ;
      if ( svdesc->done ) continue ;
      if ( svdesc->setw == NULL )
	{
	  svdesc->setw = cur_id ;
	  continue ;
	}
      switch (svdesc->type)
	{
	case URMsvWidgetRef:
	  if ( strcmp(cur_name,svdesc->sv.wname) == 0 )
	    {
	      args[0].name = svdesc->tagname ;
	      args[0].value = (XtArgVal) cur_id ;
	      XtSetValues (svdesc->setw, args, 1) ;
	      svdesc->done = TRUE ;
	      if ( svdesc->tagcode == UilMrmUnknownCode )
		{
		  XtFree ((char *)svdesc->tagname);
		  svdesc->tagname = NULL;
		}
	      /* Does this really need to be freed here? */
	      XtFree(svdesc->sv.wname);
	      svdesc->sv.wname = NULL;
	    }
	  break;
	
	case URMsvCallBackList:
	  cbdesc = (RGMCallbackDescPtr)svdesc->sv.callbacks;
	  items = cbdesc->item;
	
	  /* Loop through callback items, resolving where possible */
	  for (cbndx = 0; cbndx < cbdesc->count; cbndx++)
	    {
	      if (items[cbndx].runtime.resolved) continue; 

	      if (strcmp(cur_name, items[cbndx].runtime.wname) == 0) 
		/* Finish resolving the callback item. */
		{
		  items[cbndx].runtime.callback.closure = (XtPointer)cur_id;
		  items[cbndx].runtime.resolved = TRUE;
		  cbdesc->unres_ref_count--;
		  /* Free the widget name. */
		  XtFree(items[cbndx].runtime.wname);
		  items[cbndx].runtime.wname = NULL;
		}
	    }
	
	  if (cbdesc->unres_ref_count == 0)
	    {
	      /* Move individual items so array functions as callback list */
	      XtCallbackRec *callbacks = (XtCallbackRec *)items;
	    
	      for (cbndx = 0; cbndx <= cbdesc->count; cbndx++)
		/* <= so that null item is copied. */
		{
		  callbacks[cbndx].callback = (XtCallbackProc)
		    items[cbndx].runtime.callback.callback;
		  callbacks[cbndx].closure = (XtPointer)
		    items[cbndx].runtime.callback.closure;
		}
		
		
	      args[0].name = svdesc->tagname;
	      args[0].value = (XtArgVal)items;
	      XtSetValues(svdesc->setw, args, 1);
	      svdesc->done = TRUE;

	      /* Free memory. */
	      if ( svdesc->tagcode == UilMrmUnknownCode )
		{
		  XtFree ((char *)svdesc->tagname);
		  svdesc->tagname = NULL;
		}

	      XtFree((char *)svdesc->sv.callbacks);
	      svdesc->sv.callbacks = NULL;
	    }
	  break;
	    
	default:
	  continue;
	}
    }
}

/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *      This routine frees a SetValues descriptor.
 *
 *  FORMAL PARAMETERS:
 *
 *      svdesc          SetValues descriptor
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void 
Urm__CW_FreeSetValuesDesc (URMSetValuesDescPtr         svdesc)
{
  if ( (svdesc->type == URMsvWidgetRef) && (svdesc->sv.wname != NULL) )
    XtFree ((char *)svdesc->sv.wname);

  XtFree ((char *)svdesc);
}
