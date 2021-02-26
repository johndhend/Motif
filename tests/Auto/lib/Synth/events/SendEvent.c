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
static char rcsid[] = "$XConsortium: SendEvent.c /main/8 1995/07/14 11:30:58 drk $"
#endif
#endif
/***********************************************************************
  	@(#)SendEvent.c	1.12.1.2	Date:2/8/91
  	Author: TAT
	History:
            05/29/90 SJS add to sccs
            11/27/90 PSN quick fix for time stamp that was failing the
			 List and Text class of widgets. Use CurrentTime
			 instead of time passed in.

	Calls:

	Summary:
            Sets up and sends one event to the specified window on the display
        specified by the global variable display (local to this module only).

        INPUTS:
            window    - window to send the event to
            subwindow - child window in direction of descendent where event
                        happened
            type      - event type (ButtonPress,ButtonRelease,KeyPress,
                        KeyRelease,etc)
            time      - event time in milliseconds (use xisGetServerTime())
            wx,wy     - location of pointer when event occured relative to
                        window
            rx,ry     - location of pointer when event occured relative to root
            state     - key or button mask (Button1Mask, etc)
            detail    - Button that changed state (Button1,etc) 
                        or Key pressed (KeyReturn,KeySpace, etc)
        
        OUTPUTS:
            none

        RETURNS:
            void
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

void xisSendEvent(window,subwindow,type,time,wx,wy,rx,ry,state,detail)
Window window,subwindow;
int type;
Time time;
int wx,wy,rx,ry;
unsigned int state,detail;
{
    char msg_string[125];
    static char routine_name[] = "xisSendEvent";

    static unsigned int event_mask[] = 
       { 0,0,KeyPressMask,KeyPressMask|KeyReleaseMask,
	 ButtonPressMask,
	 ButtonPressMask|ButtonReleaseMask,
         PointerMotionMask|Button1MotionMask|
         Button2MotionMask|Button3MotionMask|Button4MotionMask|
         Button5MotionMask|ButtonMotionMask,EnterWindowMask,LeaveWindowMask };

    XEvent event;

    xisUseSessionInfo(routine_name);

    /* Hack for List and Text tests that does not get correct time from X11r3
     * server and crashes.
     */
    if (xisUseCurrentTime && 
	(xisInform.event_code != EventMouseButtonMultiClick ||
	 xisInform.num_clicks < 2) )
	time = CurrentTime;

    event.type = type;
    event.xany.display = xisDisplay;
    event.xany.window = window;

    switch (type) {
      case KeyPress:
      case KeyRelease:
        event.xkey.root = xisRootWindow;
        event.xkey.subwindow = subwindow;
        event.xkey.x = wx;
        event.xkey.y = wy;
        event.xkey.x_root = rx;
        event.xkey.y_root = ry;
        event.xkey.state = state | xisKeySymName[detail].modifier;
        event.xkey.keycode =  xisKeySymName[detail].code;
        event.xkey.same_screen = True;
        event.xkey.time = time;
  /*
   *     msg_info(" we are sending key code %d:%d that represents ]%s[ \n",
   *          xisKeySymName[detail].code,state,xisKeySymName[detail].key_name);
   */
        break;

    case ButtonPress:
    case ButtonRelease:
        event.xbutton.root = xisRootWindow;
        event.xbutton.subwindow = subwindow;
        event.xbutton.x = wx;
        event.xbutton.y = wy;
        event.xbutton.x_root = rx;
        event.xbutton.y_root = ry;
        event.xbutton.state = state;
        event.xbutton.button = detail;
        event.xbutton.same_screen = True;
        event.xbutton.time = time;
        break;

    case MotionNotify:
        event.xmotion.root = xisRootWindow;
        event.xmotion.subwindow = subwindow;
        event.xmotion.x = wx;
        event.xmotion.y = wy;
        event.xmotion.x_root = rx;
        event.xmotion.y_root = ry;
        event.xmotion.state = state;
        event.xmotion.is_hint = detail;
        event.xmotion.same_screen = True;
        event.xmotion.time = time;
        break;
      
      default:
        sprintf (msg_string, _AutoMessages[WARNMSG47], type);
        AutoMessage(msg_string);
        return;
        break;
    }

    XSendEvent(xisDisplay,window,True,event_mask[type],&event);

} /* End xisSendEvent() */










