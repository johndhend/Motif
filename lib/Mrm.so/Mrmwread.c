
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
static char rcsid[] = "$XConsortium: Mrmwread.c /main/11 1996/11/13 14:07:06 drk $"
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
 *	This module contains the widget read routines. All these routines
 *	read a widget from a hierarchy or IDB file into a resource context.
 *
 *--
 */


/*
 *
 *  INCLUDE FILES
 *
 */


#include <Mrm/MrmAppl.h>
#include <Mrm/Mrm.h>
#include "MrmMsgI.h"


/*
 *
 *  TABLE OF CONTENTS
 *
 *	UrmHGetWidget		Read indexed widget from hierarchy
 *
 *	UrmGetIndexedWidget	Read indexed widget from IDB file
 *
 *	UrmGetRIDWidget		Read RID widget from IDB file
 *
 */


/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	UrmHGetWidget searches the database hierarchy for a public
 *	(EXPORTed) widget given its index. It returns the RGM widget record
 *	in a resource context.
 *
 *  FORMAL PARAMETERS:
 *
 *	hierarchy_id	id of an open URM database hierarchy
 *	index		index of the desired widget
 *	context_id	widget context in which to return record read in
 *	file_id_return	to return IDB file in which widget was found
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmNOT_FOUND	widget not found
 *	MrmBAD_HIERARCHY	invalid URM file hierarchy
 *	MrmBAD_WIDGET_REC	invalid widget record in context
 *	Others		see UrmGetIndexedWidget
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmHGetWidget (MrmHierarchy		hierarchy_id,
	       String			index,
	       URMResourceContextPtr	context_id,
	       IDBFile			*file_id_return)
{
  /*
   *  Local variables
   */
  Cardinal		result ;	/* function results */
  RGMWidgetRecordPtr	widgetrec ;	/* widget record in context */


  /*
   * Get the widget
   */
  result = UrmHGetIndexedResource
    (hierarchy_id, index, URMgWidget, URMtNul, context_id, file_id_return) ;
  if ( result != MrmSUCCESS ) return result ;

  /*
   * Validate the widget record in the context
   */
  widgetrec = (RGMWidgetRecordPtr) UrmRCBuffer (context_id) ;
  if ( UrmWRValid(widgetrec) ) 
    return MrmSUCCESS ;
  else
    {
      if ( (*file_id_return)->byte_swapped ) swapbytes(widgetrec->validation);
      if ( UrmWRValid(widgetrec) )
	{
	  Urm__SwapRGMWidgetRecord(widgetrec);
	  return MrmSUCCESS ;
	}
    }

  return Urm__UT_Error("UrmHGetIndexedWidget", _MrmMMsg_0026,
		       NULL, context_id, MrmBAD_WIDGET_REC) ;
}

/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	UrmGetIndexedWidget searches a single database file for a widget
 *	given its index (i.e. it gets a public widget from a single file).
 *	It returns the RGM widget record.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		id of an open URM database file (IDB file)
 *	index		index of the desired widget
 *	context_id	widget context in which to return record read in
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmBAD_CONTEXT	invalid resource context
 *	Other		See UrmIdbGetIndexedResource
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmGetIndexedWidget (IDBFile			file_id,
		     String			index,
		     URMResourceContextPtr	context_id)
{
  /*
   *  Local variables
   */
  Cardinal		result ;	/* function results */
  RGMWidgetRecordPtr	widgetrec ;	/* widget record in context */


  /*
   * Validate context, then attempt the read.
   */
  if ( ! UrmRCValid(context_id) )
    return Urm__UT_Error ("UrmGetIndexedWidget", _MrmMMsg_0043,
			  file_id, NULL, MrmBAD_CONTEXT) ;

  result =
    UrmIdbGetIndexedResource (file_id, index, URMgWidget, URMtNul, context_id) ;
  if ( result != MrmSUCCESS ) return result ;

  /*
   * Validate the widget record in the context
   */
  widgetrec = (RGMWidgetRecordPtr) UrmRCBuffer (context_id) ;
  if ( UrmWRValid(widgetrec) ) 
    return MrmSUCCESS ;
  else
    {
      if ( file_id->byte_swapped ) swapbytes(widgetrec->validation);
      if ( UrmWRValid(widgetrec) )
	{
	  Urm__SwapRGMWidgetRecord(widgetrec);
	  return MrmSUCCESS ;
	}
    }

  return Urm__UT_Error("UrmGetIndexedWidget", _MrmMMsg_0026,
		       NULL, context_id, MrmBAD_WIDGET_REC) ;
}


/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	UrmGetRIDWidget retrieves a widget from a single database file
 *	given its resource id as an accessor. It returns the widget record.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		id of an open URM database file (IDB file)
 *	resource_id	resource id for widget
 *	context_id	widget context in which to return record read in
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmNOT_FOUND	widget not found
 *	MrmFAILURE	operation failed, further reason not given.
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmGetRIDWidget (IDBFile		file_id,
		 MrmResource_id		resource_id,
		 URMResourceContextPtr	context_id)
{
  /*
   *  Local variables
   */
  Cardinal		result ;	/* function results */
  RGMWidgetRecordPtr	widgetrec ;	/* widget record in context */


  /*
   * Validate context, then attempt the read.
   */
  if ( ! UrmRCValid(context_id) )
    return Urm__UT_Error ("UrmGetRIDWidget", _MrmMMsg_0043,
			  file_id, NULL, MrmBAD_CONTEXT) ;

  result = UrmIdbGetRIDResource (file_id, resource_id,
				 URMgWidget, URMgNul, context_id) ;
  if ( result != MrmSUCCESS ) return result ;

  /*
   * Validate the widget record in the context
   */
  widgetrec = (RGMWidgetRecordPtr) UrmRCBuffer (context_id) ;
  if ( UrmWRValid(widgetrec) ) 
    return MrmSUCCESS ;
  else
    {
      if ( file_id->byte_swapped ) swapbytes(widgetrec->validation);
      if ( UrmWRValid(widgetrec) )
	{
	  Urm__SwapRGMWidgetRecord(widgetrec);
	  return MrmSUCCESS ;
	}
    }
  return Urm__UT_Error("UrmGetRIDWidget", _MrmMMsg_0026,
		       NULL, context_id, MrmBAD_WIDGET_REC) ;

}

