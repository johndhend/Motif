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
static char rcsid[] = "$XConsortium: SetFocus.c /main/8 1995/07/14 11:43:06 drk $"
#endif
#endif
/***********************************************************************
  	@(#)SetFocus.c	1.9.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/30/90 SJS add to sccs
            06/21/90 SJS do not set focus to unmapped objects
            07/11/90 SJS test for success of XmProcessTraversal() even though
                         it is somewhat meaningless
            08/23/90 SJS synchronize for events when creating the dummy window
            10/17/90 SJS only worry about FocusIn/FocusOut when focus really
		         changes
	Calls:

	Summary:
            Sets the keyboard focus to the specified widget

        INPUTS:
            widget - the widget to set the keyboard focus to.
        
        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/

#include "xislib.h"
#include <Xm/XmP.h>         /* Warning: Potentially non-portable */

void xisSetKeyboardFocus(widget,object_type,instance)
Widget widget;
int object_type;
int instance;
{
    XisObjectRecord *object = xisFindObjectFromWidget(widget);
    XisObjectRecord *current_object;
    unsigned char   rc_type;
    Arg             args[1];


    if (widget == NULL) 
        (*xisTraceMsg)("Got send_event_request = SetFocus to RootWindow\n");
    else
        (*xisTraceMsg)("Got send_event_request = SetFocus to %s\n",
                  xisGetObjectName(object));

    if (widget != NULL && XmIsRowColumn(widget)) {
        XtSetArg(args[0], XmNrowColumnType, &rc_type);
        XtGetValues(widget, args, 1);
    }
    
    /* Call all relavent InformExpectedActions functions for Focus Out */
  
    current_object = xisGetFocusObject();

    if(object == current_object) {
        return; /* Already here */
    }
    xisInform.is_valid = 1;
    xisInform.action_obj = current_object;
    xisInform.modifier_key_status = 0;
    xisInform.button_num = 0;
    xisInform.key_code = 0;
    xisInform.edge_code = 0;
    xisInform.num_clicks = 0;
    xisInform.event_code = EventFocusOut;

    while (current_object != NULL) {

        if (current_object->proc_InformExpectedActions != NULL) {
            xisInform.current_obj = current_object;
            (*current_object->proc_InformExpectedActions)(EventFocusOut); 
        }
        current_object = current_object->parent;
    }

    if (widget == NULL || object == (&xisObjects[0]) ||
        !xisWindowExists(XtWindowOfObject(widget)) ||
        !xisIsMapped(XtWindowOfObject(widget)))  {

        if (!xisDummyFocusWindow) {
            xisCreateSimple();
            (void)xisSynchronize();
	}
        xisState.focus_widget = NULL;
        xisState.focus_object_type = 0;
        xisState.focus_instance = 0;
        xisState.focus_window = xisDummyFocusWindow;
        XSetInputFocus(xisDisplay,xisState.focus_window,RevertToParent,
                       CurrentTime);
    }
    else {

        xisState.focus_window = object->id.window;
        xisState.focus_widget = widget;
        xisState.focus_object_type = object_type;
        xisState.focus_instance = instance;

        /* Call all relavent InformExpectedActions functions for Focus In */
  
        current_object = object;
        xisInform.action_obj = object;
        xisInform.modifier_key_status = 0;
        xisInform.button_num = 0;
        xisInform.key_code = 0;
        xisInform.edge_code = 0;
        xisInform.num_clicks = 0;
        xisInform.event_code = EventFocusIn;

        while (current_object != NULL) {

            if (current_object->proc_InformExpectedActions != NULL) {
                xisInform.current_obj = current_object;
                (*current_object->proc_InformExpectedActions)(EventFocusIn); 
	    }
            current_object = current_object->parent;
        }

        if(object->visibility_state & IsViewable) {
            XSetInputFocus(xisDisplay,XtWindow(xisGetShellWidget(widget)),
                           RevertToNone,CurrentTime);
        }

        /* XmProcessTraversal() does not do anything useful in the way
           of being a query function. Add Check for RoWColumn Type. This
   	   because in 1.2 XmProcessTraversal() will not return False
	   for the Traversal to a MenuBar, Pulldown, or Popup.   */

        if(!XmProcessTraversal(widget,XmTRAVERSE_CURRENT) &&
           rc_type != XmMENU_BAR &&
           rc_type != XmMENU_POPUP &&
           rc_type != XmMENU_PULLDOWN ) {
            XisObjectRecord *new_focus; /* Lord only knows where it ends up */

            XGetInputFocus(xisDisplay,&xisState.focus_window,
                           &xisState.focus_revert_to);
            new_focus = xisFindObjectFromWindow(xisState.focus_window);
            if(new_focus != NULL) {
                xisState.focus_widget = new_focus->id.widget;
                xisState.focus_object_type = new_focus->id.object_type;
                xisState.focus_instance = new_focus->id.instance;
            }
        }
        else {
            XGetInputFocus(xisDisplay,&xisState.focus_window,
                           &xisState.focus_revert_to);
        }
    } /* End if (widget == NULL || object == (&xisObjects[0]) */

    xisProcessEvents(NULL,0);

} /* End xisSetFocus() */
