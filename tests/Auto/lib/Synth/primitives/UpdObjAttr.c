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
static char rcsid[] = "$XConsortium: UpdObjAttr.c /main/7 1995/07/14 11:43:30 drk $"
#endif
#endif
/***********************************************************************
  	@(#)UpdObjAttr.c	1.9.1.1	Date:1/22/91
  	Author: TAT
	History:
            06/06/90 TAT/SJS add in gadget check for getting window attributes
            08/02/90 SJS clear out propagate & event masks of gadgets/regions
            09/12/90 SJS set the visibility_state of regions to be equal to
	                 their parent's visibility_state
	Calls:

	Summary:
            Updates the object hierarchy with recent object window 
        attributes.

        INPUTS

        OUTPUTS

        RETURNS
            none
************************************************************************/

#include "xislib.h"

void xisUpdateObjectAttributes()
{
    register XisObjectRecord *object;
    XisObjectRecord *object_stack[100];
    short stack_top = 0;
    XWindowAttributes wattr;

    object = &xisObjects[0];

    /* Perform Depth-First Search */

    while (1) {

    /* If the id.window is NULL then this is a Region and does not have
       window attributes. We also check to see if we have a gadget to
       determine the event mask. (NULL parent means it's not a gadget or a
       window different from the parent means it's not a gadget) */

        if (object->id.window) {

            XGetWindowAttributes(xisDisplay,object->id.window,&wattr);

            if ((object->parent == NULL) ||
                (object->parent->id.window != object->id.window)) {

                object->your_event_mask = wattr.your_event_mask;
                object->do_not_propagate_mask = wattr.do_not_propagate_mask;
                object->visibility_state = wattr.map_state;
            }
            else {
                object->your_event_mask = 0;
                object->do_not_propagate_mask = 0;
		if (object->id.widget != NULL &&
		    			!XtIsManaged(object->id.widget))
			object->visibility_state = IsUnmapped;
		else
			object->visibility_state = wattr.map_state;
            }

        } /* End if (object->id.window != NULL) */
        else {
            object->visibility_state = object->parent->visibility_state;
        }
        if (object->first_child != NULL) {
            object_stack[stack_top++] = object;
            object = object->first_child;
        }
        else if (object->next_sibling != NULL) {
            object = object->next_sibling;
	}
        else {
            object = NULL;
            while (stack_top > 0 && object == NULL) {
                object = object_stack[--stack_top]->next_sibling;
            }
            if (stack_top == 0)
                break;
        }       
    } /* End while(1) */

} /* End xisUpdateObjectAttributes() */
