/* $XConsortium: VenShellM3.c /main/5 1995/07/15 21:06:51 drk $ */
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


#include <testlib.h>

Widget button0,  shell1, shell2, shell3, button1, button2, button3;

static void 
button_activate(Widget w, XtPointer client, XtPointer data)
{
    int button_num = *((int *)client);

    switch (button_num) {
      case 1 :
	  XtPopup (shell1, XtGrabNone);
	  XtAddGrab (Shell1, TRUE, FALSE);
	  XtPopup (shell2, XtGrabNone);
	  XtRemoveGrab (Shell1);
	  XtPopup (shell3, XtGrabNone);
	  break;
      default :
	  break;
    }
}

void
main(int argc, char *argv[])
{
 Arg args[10];
 int n;
 static int i = 1;

  
 CommonTestInit (argc,argv);

 n=0;
 button0 = (Widget) XmCreatePushButton(Shell1, "Pop 'em up", args,n);
 XtAddCallback(button0, XmNactivateCallback, button_activate, (XtPointer)&i);
 XtManageChild(button0);

 n=0;
 shell1 = XtAppCreateShell("shell1", "Shell1", topLevelShellWidgetClass, 
			   display,args,n);

 n=0;
 button1 = (Widget) XmCreatePushButton(shell1, "Button1", args,n);
 XtManageChild (button1);

 shell2 = XtAppCreateShell("shell2", "Shell2", topLevelShellWidgetClass, 
			   display,args,n);


 n=0;
 button2 = (Widget) XmCreatePushButton(shell2, "Button2", args,n);
 XtManageChild (button2);

 shell3 = XtAppCreateShell("shell3", "Shell3", topLevelShellWidgetClass, 
			   display,args,n);

 
 n=0;
 button3 = (Widget) XmCreatePushButton(shell3, "Button3", args,n);
 XtManageChild (button3);

 XtRealizeWidget(Shell1);

 CommonPause();

 XtAppMainLoop(app_context);
}
