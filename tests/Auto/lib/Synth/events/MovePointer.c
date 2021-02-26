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
static char rcsid[] = "$XConsortium: MovePointer.c /main/7 1995/07/14 11:30:21 drk $"
#endif
#endif
/***********************************************************************
  	@(#)MovePointer.c	1.9.1.2     Date:2/7/91
  	Author: TAT
	History:
            05/29/90 SJS add to sccs
            07/24/90 SJS needs fixing to account for a pointer grab. Also,
	                 seems to really be doing the wrong thing for deciding
	                 where to send motion events on boundary crossings.
	Calls:

	Summary:
        Moves the pointer on the screen to the specified x,y location.
        It does this by moving the pointer many times along a line connecting
        the current location with the destination location (much like a
        workstation user might move the mouse).  Each iteration results in the
        mouse moving PTR_MOVE_INCREMENT pixels towards the destination.

        If the user fiddles with the mouse during this algorithm, it should not
        affect its ability to arrive at the target position since it just reads
        the new current position and calculates the next appropriate position
        PTR_MOVE_INCREMENT pixels closer to the destination.

        INPUTS:
            new_x,new_y       - location to move pointer relative to root
        
        OUTPUTS:
            none

        RETURNS:
            void
************************************************************************/

#include "xislib.h"

#define PTR_MOVE_INCREMENT 10

void xisMovePointer(new_x,new_y)
int new_x,new_y;
{
    register unsigned long relevant_event;
    register XisObjectRecord *object;
    static char routine_name[] = "xisMovePointer";
    int root_x,root_y,x=(-100),y=(-100);
    int a,b;
    double dist,tmp;
    Window subwindow;

    xisUseSessionInfo(routine_name);

    xisUpdateObjectAttributes();

    /* loop until position of mouse hotspot is over the destination */

    while ((x != new_x) || (y != new_y)) {
        xisGetPointerLocation(&root_x,&root_y);

        a = new_y - root_y;              /* Given start and end points,       */
        b = -(new_x - root_x);           /* calculate coefficients of line    */
                                         /* Ax + By + C = 0.                  */

        dist = sqrt((double)(a*a + b*b));/* Calc current distance betw points */

        if (dist < PTR_MOVE_INCREMENT) { /* If within incr range set to end pt*/
            x = new_x;            
            y = new_y;
        }
        else {                           /* Otherwise calc new x,y along line */
            tmp = PTR_MOVE_INCREMENT / dist;
            x = (int)(-b * tmp + root_x + 0.5);
            y = (int)(a * tmp + root_y + 0.5);
        }

        /* Move pointer to next x,y location */

        XWarpPointer(xisDisplay,None,xisRootWindow,0,0,0,0,x,y);

        /* Generate motion notify events if needed */

        xisGetPointerLocation(&root_x,&root_y);

        if (xisPointerGrabbed && xisWindowExists(xisGrabPointerWindow)) {
            object = xisFindObject(xisState.selected_widget,
                                   xisState.selected_object_type,
                                   xisState.selected_instance);
        }
        else {
            object = xisFindObjectAtLocation(root_x,root_y);
        }

        /* Send appropriate motion notify events */

        subwindow = None;

        relevant_event = PointerMotionMask | Button1MotionMask |
                          Button2MotionMask | Button3MotionMask | 
                          Button4MotionMask | Button5MotionMask | 
                          ButtonMotionMask;        

/* 
   Automation Added. If you are off the current hierarchy the object will
   be NULL. So wait until the object becomes valid to send appropriate
   events. 
*/

     	if (object != NULL) {
          while (object != &xisObjects[0]) {

            if (object->id.window) {
                if (relevant_event & PointerMotionMask) { 
                    if ((object->your_event_mask)&PointerMotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~PointerMotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&PointerMotionMask)
                        relevant_event &= ~(PointerMotionMask);
		}
                if ((relevant_event & Button1MotionMask) &&
                    (xisState.mod_button_state & Button1Mask)) { 
                    if ((object->your_event_mask)&Button1MotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~Button1MotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&Button1MotionMask)
                        relevant_event &= ~(Button1MotionMask);
		}
                if ((relevant_event & Button2MotionMask) &&
                    (xisState.mod_button_state & Button2Mask)) { 
                    if ((object->your_event_mask)&Button2MotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~Button2MotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&Button2MotionMask)
                        relevant_event &= ~(Button2MotionMask);
		}
                if ((relevant_event & Button3MotionMask) &&
                    (xisState.mod_button_state & Button3Mask)) { 
                    if ((object->your_event_mask)&Button3MotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~Button3MotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&Button3MotionMask)
                        relevant_event &= ~(Button3MotionMask);
		}
                if ((relevant_event & Button4MotionMask) &&
                    (xisState.mod_button_state & Button4Mask)) { 
                    if ((object->your_event_mask)&Button4MotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~Button4MotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&Button4MotionMask)
                        relevant_event &= ~(Button4MotionMask);
		}
                if ((relevant_event & Button5MotionMask) &&
                    (xisState.mod_button_state & Button5Mask)) { 
                    if ((object->your_event_mask)&Button5MotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~Button5MotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&Button5MotionMask)
                        relevant_event &= ~(Button5MotionMask);
		}
                if ((relevant_event & ButtonMotionMask) &&
                    (xisState.mod_button_state & (Button1Mask|Button2Mask|
                     Button3Mask|Button4Mask|Button5Mask))) { 
                    if ((object->your_event_mask)&ButtonMotionMask) {
                        xisSendEvent(object->id.window,subwindow,
                                     MotionNotify,xisGetServerTime(0),
                                     x - object->x,y - object->y,
                                     x,y,xisState.mod_button_state,False);
                        relevant_event &= (~ButtonMotionMask);
                        
                    }
                    if ((object->do_not_propagate_mask)&ButtonMotionMask)
                        relevant_event &= ~(ButtonMotionMask);
		}

            } /* if object->id.window != NULL */

            subwindow = object->id.window;
            object = object->parent;
        }
      }
    }

} /* End MovePointer() */
