
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
static char rcsid[] = "$XConsortium: Mrmptrlist.c /main/12 1996/11/13 14:03:53 drk $"
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
 *	These routines manage a dynamic pointer list
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
 */


/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine acquires and initializes a new pointer list.
 *
 *  FORMAL PARAMETERS:
 *
 *	size		number of pointer slots to allocate in list
 *	list_id_return	to return pointer to new list structure
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmFAILURE	allocation failure
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal
UrmPlistInit (int		size,
	      URMPointerListPtr	*list_id_return)
{

  /*
   * Allocate the list buffer and the slot vector buffer, and initialize
   */
  *list_id_return = (URMPointerListPtr) XtMalloc (sizeof(URMPointerList)) ;
  if ( *list_id_return == NULL )
    return Urm__UT_Error ("UrmPlistInit", _MrmMMsg_0046,
			  NULL, NULL, MrmFAILURE) ;

  (*list_id_return)->ptr_vec = (XtPointer *) XtMalloc (size*sizeof(XtPointer)) ;
  if ( (*list_id_return)->ptr_vec == NULL )
    return Urm__UT_Error ("UrmPlistInit", _MrmMMsg_0047,
			  NULL, NULL, MrmFAILURE) ;

  (*list_id_return)->num_slots = size ;
  (*list_id_return)->num_ptrs = 0 ;
  return MrmSUCCESS ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine reallocates the list vector in a pointer list in order
 *	to increase its size. The contents of the current list are copied
 *	into the new list.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list to be resized
 *	size		The new number of pointer slots
 *
 *  IMPLICIT INPUTS:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmFAILURE	memory allocation failure
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmPlistResize (URMPointerListPtr	list_id,
		int			size)
{

  /*
   * Allocate the new vector, and copy the current vector into it.
   */
  list_id->ptr_vec = (XtPointer *) XtRealloc ((char *)(list_id->ptr_vec),
					      size*sizeof(XtPointer)) ;
  if ( list_id->ptr_vec == NULL )
    return Urm__UT_Error ("UrmPlistResize", _MrmMMsg_0048,
			  NULL, NULL, MrmFAILURE) ;

  list_id->num_slots = size ;
  return MrmSUCCESS ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine frees the pointer vector and list structure.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list to be freed
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal UrmPlistFree (URMPointerListPtr	list_id)
{

  XtFree ((char*)list_id->ptr_vec) ;
  XtFree ((char*)list_id) ;
  return MrmSUCCESS ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine frees each of the items pointed to by the active
 *	pointers in the pointer list. The items must have been allocated
 *	with XtMalloc.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operatoin succeeded
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmPlistFreeContents (URMPointerListPtr	list_id)
{

  /*
   *  Local variables
   */
  int			ndx ;		/* loop index */


  for ( ndx=0 ; ndx<list_id->num_ptrs ; ndx++ )
    XtFree (list_id->ptr_vec[ndx]) ;
  return MrmSUCCESS ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine appends a pointer to the list. If no space remains,
 *	the list is resized to double its current size.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list
 *	ptr		The pointer to append
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmFAILURE	allocation failure
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmPlistAppendPointer (URMPointerListPtr	list_id ,
		       XtPointer		ptr )
{
  /*
   *  Local variables
   */
  Cardinal		result ;	/* function results */


  if ( list_id->num_ptrs == list_id->num_slots )
    {
      result = UrmPlistResize (list_id, 2*list_id->num_slots) ;
      if ( result != MrmSUCCESS ) return result ;
    }

  list_id->ptr_vec[list_id->num_ptrs] = ptr ;
  list_id->num_ptrs++ ;
  return MrmSUCCESS ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine allocates space for a string, copies, and appends the
 *	pointer to the string in the pointer list. All the strings in the
 *	list may be freed with UrmPlistFreeContents.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list
 *	stg		The string to alocate, copy, and append
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmFAILURE	allocation failure
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
UrmPlistAppendString (URMPointerListPtr		list_id ,
		      String			stg )
{
  /*
   *  Local variables
   */
  Cardinal		result ;	/* function results */
  String			newstg ;	/* allocated string */


  newstg = XtMalloc (strlen(stg)+1) ;
  if ( newstg == NULL )
    return Urm__UT_Error ("UrmPlistAppendString", _MrmMMsg_0049,
			  NULL, NULL, MrmFAILURE) ;

  strcpy (newstg, stg) ;
  result = UrmPlistAppendPointer (list_id, newstg) ;
  return result ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine searches a list (assumed to be a list of string
 *	pointers) for a case-sensitive match to a string. If found,
 *	its index in the list is found; else -1 is returned.
 *
 *  FORMAL PARAMETERS:
 *
 *	list_id		The pointer list
 *	stg		the (case-sensitive) string to be found
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *	0-based index in list if found
 *	-1 if not found
 *
 *  SIDE EFFECTS:
 *
 *--
 */

MrmCount 
UrmPlistFindString (URMPointerListPtr		list_id ,
		    String			stg )

{
  /*
   *  Local variables
   */
  MrmCount		ndx ;		/* search index */


  for ( ndx=0 ; ndx<UrmPlistNum(list_id) ; ndx++ )
    if ( strcmp(stg,(String)UrmPlistPtrN(list_id,ndx)) == 0 )
      return ndx ;
  return -1 ;

}

