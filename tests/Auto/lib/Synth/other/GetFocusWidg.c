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
static char rcsid[] = "$XConsortium: GetFocusWidg.c /main/8 1995/07/14 11:34:18 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetFocusWidg.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
            07/31/90 SJS the _XmFocusDataRec is changed (I don't much
                         like this dependence, but I guess we are stuck.
            08/23/90 SJS call to XtWindowToWidget() was incorrect
	Calls:

	Summary:
            Returns the widget that is currently in focus. It does this by first
        identifying which top-most shell widget is in focus (if any are) and
        then determining which item of which tab group under that shell is
        currently in focus.

        INPUTS
            none

        OUTPUTS
            none

        RETURNS
            Widget that is in keyboard focus. If the current window is not a 
            recognizable widget, it then returns NULL.  If the current window
            is the root window, then it return the constant PointerRoot.
************************************************************************/
#include <Xm/Xm.h>
#include "xislib.h"

Widget xisGetFocusWidget()
{
    Window server_focus_window,pointer_window;
    Widget server_focus_widget,tmp_widget;
    int revert;
    int rx,ry,wx,wy;
    unsigned int button_mask;

    XGetInputFocus(xisDisplay, &server_focus_window, &revert);
    xisGetPointerInfo(&pointer_window,&rx,&ry,&wx,&wy,&button_mask);

    if ( (server_focus_window == PointerRoot) || 
         (xisIsAncestorWindow(server_focus_window,pointer_window)) )
        server_focus_window = pointer_window;

    if (server_focus_window == None)
        return (Widget)NULL;

    server_focus_widget = XtWindowToWidget(xisDisplay, server_focus_window);

    if (server_focus_widget == NULL)
        return (Widget)NULL;

    tmp_widget = xisGetShellWidget(server_focus_widget);

    if (tmp_widget == NULL)
        return (Widget)NULL;

    return XmGetFocusWidget(tmp_widget);

} /* End xisGetFocusWidget() */
