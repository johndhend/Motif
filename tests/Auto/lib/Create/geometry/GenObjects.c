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
static char rcsid[] = "$XConsortium: GenObjects.c /main/7 1995/07/14 10:58:23 drk $"
#endif
#endif
/***********************************************************************
        @(#)GenObjects.c	1.5.1.1     Date:1/22/91
  	Author: TAT
	History:
            05/21/90 SJS Add tp sccs
            06/15/90 SJS fix propagation of events problem (call to 
                         mvsGetSubObjects()
            06/22/90 SJS Really do a depth first search to generate
	Calls:

	Summary:
            Generate the xis object hierarchy.

            INPUTS
                root_obj - Pointer to the root object

            OUTPUTS
                root_obj - Pointer to the root object with new hierarchy 

            RETURNS
                none
************************************************************************/

#include "mvslib.h"

void mvsGenerateObjects(root_obj)
XisObjectRecord *root_obj;
{
    MvsWidgetInfoRecord *winfo = mvsRootWidgetInfo->first_child;
    int stack_top=0;
    MvsWidgetInfoRecord *object_stack[50];

    /* Re-initialize next_avail_id_code to 0 */

    mvsGetSubObjects(NULL,NULL,0,0,False);

    /* Perform Depth-First Search */

    while (winfo != NULL) {

        if(!winfo->being_destroyed)
            mvsGetSubObjects(xisFindObjectFromWidget(winfo->parent->widget),
                                                     winfo->widget,0,0,False);

        if (winfo->first_child != NULL) {
            object_stack[stack_top++] = winfo;
            winfo = winfo->first_child;
        }
        else if (winfo->next_sibling != NULL) {
            winfo = winfo->next_sibling;
	}
        else {

            winfo = NULL;
            while (stack_top > 0 && winfo == NULL) {
                winfo = object_stack[--stack_top]->next_sibling;
            }
        }       
    }
} /* End mvsGenerateObjects() */
