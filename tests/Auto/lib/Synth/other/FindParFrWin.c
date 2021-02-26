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
static char rcsid[] = "$XConsortium: FindParFrWin.c /main/7 1995/07/14 11:33:37 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FindParFrWin.c	1.2.1.1	Date:1/22/91
  	Author: TAT
	History:
            06/30/90 TAT create
	Calls:

	Summary:
            Looks up the object highest in the hierarchy that has the 
        given window in its children_windows list.

        INPUTS
            window - X window id to match

        OUTPUTS
            none

        RETURNS
            Pointer to object which matches given window id
************************************************************************/
#include "xislib.h"

XisObjectRecord *xisFindParentObjectFromWindow(window)
Window window;
{
    XisObjectRecord *object;
    XisObjectRecord *object_stack[100];
    short stack_top = 0;
    int i;

    object = &xisObjects[0];

    /* Perform Depth-First Search */

    while (1) {

        for (i=0; i < object->id.num_children; i++) {
            if (object->id.children_windows[i] == window)
                break;
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
            while (stack_top > 0 && object == NULL)
                object = object_stack[--stack_top]->next_sibling;

            if (stack_top == 0)
                break;
        }       
    }

    return object;

} /* End xisFindParentFromWindow() */
