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
static char rcsid[] = "$XConsortium: AllocObject.c /main/7 1995/07/14 11:31:17 drk $"
#endif
#endif
/***********************************************************************
  	@(#)AllocObject.c	1.12.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
            06/28/90 TAT add stacking order code
            06/29/90 SJS differentiate between widget/gadget/region
            08/08/90 SJS init proc_Inform field & any others I see
            08/13/90 SJS correct logic for exceeding MAX tests
            08/24/90 SJS correct free of child_windows
	Calls:

	Summary:
            Allocates one object record and returns a pointer to it.
        The object is placed into the object hierarchy and filled in
        according to what is learned about it (geometry, stacking, etc)

        INPUTS
            none

        OUTPUTS
            none

        RETURNS
            Pointer to statically allocated object record.
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

XisObjectRecord *xisAllocObject(parent_obj,widget,object_type,instance)

XisObjectRecord *parent_obj;
Widget widget;
int object_type,instance;
{
    XisObjectRecord *object;
    Window window, parent_window, root_window,*child_windows;
    unsigned int n_children;
    int i,j,k;
    static char routine_name[] = "xisAllocObject():";
    char msg_string[125];

    /* Find first unused object. */   
    /* Note "<=" since we may need 1 beyond end */

    for (i=0; (i <= xisMaxObjectNum && xisObjects[i].in_use); i++) {
        if (i >= MAX_NUM_OBJECTS) {
	    sprintf (msg_string, _AutoMessages[WARNMSG101], routine_name);
            AutoError(msg_string);
                            
            
        }
    } 

    xisObjects[i].in_use = True;

    /* If found one on end of list, bump up xisMaxObjectNum */
    if (i == xisMaxObjectNum)
        xisMaxObjectNum++;

    /* Stuff fields */
    xisObjects[i].id.object_type = object_type;
    xisObjects[i].id.instance = instance;
    xisObjects[i].first_child = NULL_Object;
    xisObjects[i].next_sibling = NULL_Object;

    xisObjects[i].id.widget = widget;
    xisObjects[i].id.window = (widget == NULL ? 0L:XtWindowOfObject(widget));
    xisObjects[i].proc_InformExpectedActions = NULL;

    /* Then stuff root_window, parent_window, children_windows, num_childs */
    /* This is a sort of cache for the ancestor and stacking order info.   */

    if ((xisObjects[i].id.window != 0) &&
        (xisObjects[i].id.window != parent_obj->id.window)){

        /* It is not a region nor a gadget, so query */
        XQueryTree(xisDisplay,xisObjects[i].id.window,
                   &xisObjects[i].id.root_window, /* for multi-screen */
                   &xisObjects[i].id.parent_window,
                   &xisObjects[i].id.children_windows,
                   &xisObjects[i].id.num_children);
    }
    else {
        xisObjects[i].id.root_window = xisRootWindow;
        xisObjects[i].id.children_windows = NULL;
        xisObjects[i].id.num_children = 0;
        xisObjects[i].id.parent_window = 0; /* Not absolutely necessary */
    }

    /* Then stuff parent_obj */
    xisObjects[i].parent = parent_obj;

    /* Then stuff window_under_parent */
    if (XtIsShell(widget)) {
        window = parent_window = XtWindow(widget);
        while (parent_window != xisRootWindow) {
            window = parent_window;
            child_windows = NULL;
            if(!XQueryTree(xisDisplay,window,&root_window,&parent_window,
                           &child_windows,&n_children)) {
	        sprintf(msg_string, _AutoMessages[WARNMSG102], routine_name);
                AutoMessage(msg_string);
            }
            else {
                if (n_children)
                    XFree( (caddr_t)child_windows);
            }
	} /* End while() */
	xisObjects[i].id.window_under_parent = window;
    }
    else 
        xisObjects[i].id.window_under_parent = xisObjects[i].id.window;

    /* Then insert in parent's child list in correct stacking position */
    if (parent_obj != NULL_Object) {
                
        object = xisObjects[i].parent->first_child;

        /* If 1st child for parent... */
        if (object == NULL_Object) /* Then its trivial */
            xisObjects[i].parent->first_child = (&xisObjects[i]);

        /* If the parent object has no descendant info or  */
        /*    this object is a gadget/region.              */

        else if ((parent_obj->id.num_children == 0) ||
                 (xisObjects[i].id.window == 0) ||
                 (xisObjects[i].id.window == parent_obj->id.window)) {

            /* Blow it off and just put in sequential order */

            while (object->next_sibling != NULL_Object) {
                object = object->next_sibling;
	    }
	    object->next_sibling = (&xisObjects[i]);
        }

        /* Otherwise, look at parent's children window list */
        /* and figure out where this new widget fits in (in */
        /* top to bottom stacking order)                    */

        else {
                   
            /* First find this new obj's window in parent list */
            for (j=0; j<parent_obj->id.num_children; j++) {
                if (parent_obj->id.children_windows[j] 
                    == xisObjects[i].id.window_under_parent)

                    break;
            }
            if (j == parent_obj->id.num_children) {
                (*xisTraceMsg)("xisAllocObject(): parent_obj not true window parent of widget\n");
                        
                /* If parent does not know this window then orphan :-)*/
                /* So, blow it off again, and just put on end of list.*/
                /* This occurs with PullDown/Popup children of        */
                /* Pulldown/Popup widgets. Even though the 2nd is the */
                /* child of the first, they both "share" the same     */
                /* Shell parent.                                      */
                      
                while (object->next_sibling != NULL_Object) {
                    object = object->next_sibling;
	        }
                object->next_sibling = (&xisObjects[i]);
            }
            else { /* Found widget's window in parent's list of children */

                /* Now, starting from the child following that child  */
                /* in the parent's list (in bot to top stacking order */
                /* see Xlib's XQueryTree for more on this) look for   */
                /* first window that we find a corresponding object   */ 
                /* for.  This object is above the new object.         */

                for (k=j+1; k<parent_obj->id.num_children; k++) {

                    /* See if we find corresponding child object */
                    for ( object=parent_obj->first_child;
                          (object != NULL_Object) &&
                          (object->id.window_under_parent != 
                              parent_obj->id.children_windows[k]);
                          object=object->next_sibling               );

                    /* If we found it, leave for loop */

                    if (object != NULL_Object)
                        break;
                }

                /* If found a child window on top of our new object...*/
                if (k < parent_obj->id.num_children) {

                    /* Insert the new object after it in list */
                    xisObjects[i].next_sibling = object->next_sibling;
                    object->next_sibling = (&xisObjects[i]);
                }

                /* Otherwise, new object is first child */

                else {
                    xisObjects[i].next_sibling = parent_obj->first_child;
                    parent_obj->first_child = (&xisObjects[i]);
		}
            } /* else found corresponding child */
        } /* else Look in paren't children window list... */
    } /* if (parent_obj != NULL_Object) */

    return (&xisObjects[i]);

} /* End xisAllocObject() */
