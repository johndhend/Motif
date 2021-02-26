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
static char rcsid[] = "$XConsortium: PrintEvent.c /main/7 1995/07/14 11:30:35 drk $"
#endif
#endif
/***********************************************************************
  	@(#)PrintEvent.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/29/90 SJS add to sccs
	Calls:

	Summary:
            Prints out a brief description of the event (mostly on one line)
           
        INPUTS:
            event         - the event structure to be briefly printed out
        
        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

void xisPrintEvent(event)
XEvent *event;
{
    Window window;
    char msg_string[125];

    static char *event_name[] = { 
        "","","KeyPress","KeyRelease","ButtonPress","ButtonRelease",
        "MotionNotify","EnterNotify","LeaveNotify","FocusIn","FocusOut",
        "KeymapNotify","Expose","GraphicsExpose","NoExpose",
        "VisibilityNotify","CreateNotify","DestroyNotify","UnmapNotify",
        "MapNotify","MapRequest","ReparentNotify","ConfigureNotify",
        "ConfigureRequest","GravityNotify","ResizeRequest","CirculateNotify",
        "CirculateRequest","PropertyNotify","SelectionClear","SelectionRequest",
        "SelectionNotify","ColormapNotify","ClientMessage","MappingNotify" };

    static char *crossing_mode[] = {"NotifyNormal","NotifyGrab","NotifyUngrab",
                                    "NotifyWhileGrabbed"};

    static char *crossing_detail[] = {"NotifyAncestor","NotifyVirtual",
                                      "NotifyInferior","NotifyNonlinear",
                                      "NotifyNonlinearVirtual","NotifyPointer",
                                      "NotifyPointerRoot","NotifyDetailNone" };

    switch (event->type) {
      case MotionNotify:
          window = event->xmotion.window;
          break;
      case ButtonPress:
      case ButtonRelease:
          window = event->xbutton.window;
          break;
      case KeyPress:
      case KeyRelease:
          window = event->xkey.window;
          break;
      case EnterNotify:
      case LeaveNotify:
          window = event->xcrossing.window;
          break;
      case FocusIn:
      case FocusOut:
          window = event->xfocus.window;
          break;
      case Expose:
          window = event->xexpose.window;
          break;
      case GraphicsExpose:
          window = event->xgraphicsexpose.drawable;
          break;
      case NoExpose:
          window = event->xnoexpose.drawable;
          break;
      case VisibilityNotify:
          window = event->xvisibility.window;
          break;
      case CreateNotify:
        window = event->xcreatewindow.window;
        break;
      case DestroyNotify:
        window = event->xdestroywindow.window;
        break;
      case UnmapNotify:
        window = event->xunmap.window;
        break;
      case MapNotify:
        window = event->xmap.window;
        break;
      case MapRequest:
        window = event->xmaprequest.window;
        break;
      case ReparentNotify:
        window = event->xreparent.window;
        break;
      case ConfigureNotify:
        window = event->xconfigure.window;
        break;
      case GravityNotify:
        window = event->xgravity.window;
        break;
      case ResizeRequest:
        window = event->xresizerequest.window;
        break;
      case ConfigureRequest:
        window = event->xconfigurerequest.window;
        break;
      case CirculateNotify:
        window = event->xcirculate.window;
        break;
      case CirculateRequest:
        window = event->xcirculaterequest.window;
        break;
      case PropertyNotify:
        window = event->xproperty.window;
        break;
      case SelectionClear:
        window = event->xselectionclear.window;
        break;
      case SelectionRequest:
        window = event->xselectionrequest.owner;
        break;
      case SelectionNotify:
        window = event->xselection.requestor;
        break;
      case ColormapNotify:
        window = event->xcolormap.window;
        break;
      case ClientMessage:
        window = event->xclient.window;
        break;
      case MappingNotify:
        window = event->xmapping.window;
        break;
      case KeymapNotify:
        window = event->xkeymap.window;
        break;
      default:
        AutoMessage(_AutoMessages[WARNMSG125]);
        window = xisRootWindow;
        break;
    }

    (*xisTraceMsg)("Received %s event\n\t\t\t from %s, send_event=%d\n",
                   event_name[event->type],
                   xisGetObjectName(xisFindObjectFromWindow(window)),
                   event->xany.send_event);

    if (event->type == EnterNotify || event->type == LeaveNotify) {
        (*xisTraceMsg)("with crossing_mode=%s, detail=%s\n",
                       crossing_mode[event->xcrossing.mode],
                       crossing_detail[event->xcrossing.detail] );
    }

    else if (event->type == KeyPress || event->type == KeyRelease) {
        char buf[20];
        char outbuf[80];
        int buf_size;
        KeySym keysym_return;
        buf_size = XLookupString((XKeyEvent *)event,buf,20,&keysym_return,
                                 (XComposeStatus *)NULL);
        buf[buf_size] = '\0';
        if (isprint(buf[0]))
            sprintf(outbuf,"'%s'",buf);
        else if (iscntrl(buf[0]))
            sprintf(outbuf,"'^%c'",buf[0]+'A'-1);
        else 
            sprintf(outbuf,"non-printable");
            
        (*xisTraceMsg)("Keycode = %d (%s)\n",buf[0],outbuf);
    }

} /* End xisPrintEvent() */
