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
static char rcsid[] = "$XConsortium: IsPntrOver.c /main/7 1995/07/14 11:39:44 drk $"
#endif
#endif
/***********************************************************************
  	@(#)IsPntrOver.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/30/90 SJS add to sccs
            10/16/90 SJS check for ancestor relationship
	Calls:

	Summary:
            Returns True if pointer_obj matches specified object type.The object
	type passed in is a concatenation of the object types from the parent on
	down to the one we are interested in. Thus, from the keyboard region
	we go upwards from object to object. As we travel up the ancestor
	chain, each object type is compared against the corresponding "piece"
	of the concatenated type.

        INPUTS:
            none
        
        OUTPUTS:
            none

        RETURNS:
            True = pointer_obj is of specified type
            False = otherwise
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

int xisIsPointerOverRegion(object_type_in)
int object_type_in;
{
    XisObjectRecord *object = xisInform.pointer_obj;
    int object_type, cum_object_type = object_type_in;
    int tmp;
    int succeed = 1;

    if (!xisInform.is_valid)
         AutoMessage(_AutoMessages[WARNMSG53]);

    if (object == NULL)
        return(FALSE);

    while (object != NULL && cum_object_type > 0) {

        tmp = cum_object_type / xisNumObjectTypes;
        object_type = cum_object_type - (tmp*xisNumObjectTypes);
     
        if (object->id.object_type != object_type) { /* Does not match */
            succeed = 0;
            break;
	}

        cum_object_type = tmp;
        object = object->parent;
    }

    /* This should be a straight equality */
    return (xisIsAncestorObject(xisInform.current_obj, object) && succeed);

} /* End xisIsPointerOverRegion() */
