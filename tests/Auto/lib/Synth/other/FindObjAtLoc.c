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
static char rcsid[] = "$XConsortium: FindObjAtLoc.c /main/7 1995/07/14 11:33:04 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FindObjAtLoc.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
            07/19/90 SJS correct Null sibling/first_child cases
            07/24/90 SJS use some register variables
            09/12/90 SJS check for the Map state of the objects
	Calls:

	Summary:
            Looks up the object lowest in the hierarchy and highest in
        stacking order that contains the given x,y location. This object
	must also be mapped (possibly should be viewable, but not sure yet)

        INPUTS
            x,y - the location relative to the root window

        OUTPUTS
            none

        RETURNS
            Pointer to object which contains the given x,y location
************************************************************************/
#include <Xm/Xm.h>
#include "xislib.h"
#include <X11/IntrinsicP.h>

XisObjectRecord *xisFindObjectAtLocation(x,y)
int x,y;
{
    register int stack_top = 0;
    register int done = False;
    register XisObjectRecord *object;
    register XisObjectRecord *save_object=NULL_Object;
    XisObjectRecord *object_stack[100];
    int border_width;

    /* Check to see if the current l & y is valid */

    if ( x < 0 || y < 0 || 
         x > DisplayWidth(xisDisplay,xisScreen) || 
         y > DisplayHeight(xisDisplay,xisScreen)   ) {

        return(NULL);
    }

    object = (&xisObjects[0]);  /* Start at the Root object */

    /* Perform Depth-First Search to find inner-most containing object */
    /* As we go along create a stack of the objects we are in   (!?!)  */

    while (!done) {

	border_width = 0;

	if (object->id.widget != NULL) {
		border_width = 
			(int) object->id.widget->core.border_width;
	}

        /* Check to see if the current x & y is within the object */
        if ( ((object->x - border_width) <= x) &&
             ((object->y - border_width) <= y) &&
             ((object->x + object->width + border_width) > x) &&
             ((object->y + object->height + border_width) > y) &&
             (object->visibility_state != IsUnmapped)   ) {
        
            save_object = object;
	}

        if ((save_object == object) && (object->first_child != NULL) ) {
            object_stack[stack_top++] = object;
            object = object->first_child;
        }
        else if (object->next_sibling != NULL) {
            if ((object == save_object)) {
                done = True;
            }
            else
                object = object->next_sibling;
        }
        else {
            if ((object == save_object) ) {
                done = True;
            }
            else {
                object = NULL;
                while (stack_top > 0) {
                    object = object_stack[--stack_top];
                    if (object == save_object)
                        done = True;
                    object = object->next_sibling;
                    if (object != NULL) 
                        break;
	        }
                if (object == NULL)
                    done = True;
            }
        }
    } /* End while(!done) */

    return(save_object);

} /* End xisFindObjectAtLocation() */
