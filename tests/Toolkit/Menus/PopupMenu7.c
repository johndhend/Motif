/* $XConsortium: PopupMenu7.c /main/5 1995/07/15 21:07:00 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 */
/*
 * HISTORY
 */

#include <testlib.h>


static void PopupCB(Widget w, XtPointer client_data, XtPointer call_data)
{
    if (((XmPopupHandlerCallbackStruct*)call_data)->reason == XmCR_POST)
	printf("%s Posting Popup.\n", (char*)client_data);
    else
	printf("%s Unposting Popup.\n", (char*)client_data);
}

static void PostMenu(Widget w, XtPointer popup, XEvent *event, Boolean *c)
{
    XButtonEvent *ev = (XButtonEvent *)event;
    if (ev->button != Button3)
	return;
    XmMenuPosition((Widget)popup, ev);
    XtManageChild((Widget)popup);
}



int main(int argc, char *argv[])
{
  Arg args[20];
  int n;
  XmString str;
  Widget drawarea;
  Widget popup1;
  Widget title1;
  Widget text1;

Widget popup2;
XmString str2;
Widget title2;
XEvent event;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth, 300); n++;
  XtSetArg(args[n], XmNheight, 200); n++;
  XtSetArg(args[n], XmNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);

  n = 0;
  drawarea = XmCreateDrawingArea(Shell1, "drawarea", args, n);
  XtManageChild(drawarea);

  n = 0; 
  XtSetArg(args[n], XmNx, 175); n++;
  XtSetArg(args[n], XmNy, 100); n++;
  XtSetArg(args[n], XmNwidth, 50); n++;
  text1 = XmCreateTextField(drawarea, "text1", args, n);
  XtManageChild(text1);

  XtRealizeWidget(Shell1);

  n = 0;
  XtSetArg(args[n], XmNmnemonic, "P"); n++;
  popup1 = XmCreatePopupMenu(drawarea, "popup1", args, n);

  n = 0;
  str = XmStringCreateSimple("title1");
  XtSetArg(args[n], XmNlabelString, str); n++;
  title1 = XmCreateLabel(popup1, "title1", args, n);
  XtManageChild(title1);
  XmStringFree(str);

  CommonPause();
 
  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC_RECURSIVE); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_DISABLED); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_KEYBOARD); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  /* Install a PopupHandler on the DrawArea and TextField. */

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC); n++;
  XtSetValues(popup1, args, n);
  XtAddCallback(drawarea, XmNpopupHandlerCallback,
		(XtCallbackProc)PopupCB, "DrawArea");
  XtAddCallback(text1, XmNpopupHandlerCallback,
		(XtCallbackProc)PopupCB, "TextField");
  XtAddCallback(popup1, XmNpopupHandlerCallback,
		(XtCallbackProc)PopupCB, "Popup");


  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC_RECURSIVE); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_DISABLED); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_KEYBOARD); n++;
  XtSetValues(popup1, args, n);

  CommonPause();

XtDestroyWidget(drawarea);

n = 0;
drawarea = XmCreateDrawingArea(Shell1, "drawarea", args, n);
XtManageChild(drawarea);

n = 0; 
XtSetArg(args[n], XmNx, 175); n++;
XtSetArg(args[n], XmNy, 100); n++;
XtSetArg(args[n], XmNwidth, 50); n++;
text1 = XmCreateTextField(drawarea, "text1", args, n);
XtManageChild(text1);

n = 0;
XtSetArg(args[n], XmNmnemonic, "P"); n++;
popup1 = XmCreatePopupMenu(drawarea, "popup1", args, n);
popup2 = XmCreatePopupMenu(text1, "popup2", args, n);

n = 0;
str2 = XmStringCreateSimple("Text Field");
XtSetArg(args[n], XmNlabelString, str2); n++;
title2 = XmCreateLabel(popup2, "title2", args, n);
XtManageChild(title2);
XmStringFree(str2);

n = 0;
str = XmStringCreateSimple("Drawing Area");
XtSetArg(args[n], XmNlabelString, str); n++;
title1 = XmCreateLabel(popup1, "title1", args, n);
XtManageChild(title1);
XmStringFree(str);

n = 0;
XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC); n++;
XtSetValues(popup1, args, n);
XtSetValues(popup2, args, n);
XtAddCallback(drawarea, XmNpopupHandlerCallback,
	      (XtCallbackProc)PopupCB, "DrawArea");
XtAddCallback(text1, XmNpopupHandlerCallback,
	      (XtCallbackProc)PopupCB, "TextField");
XtAddCallback(popup1, XmNpopupHandlerCallback,
	      (XtCallbackProc)PopupCB, "Popup1");
XtAddCallback(popup2, XmNpopupHandlerCallback,
	      (XtCallbackProc)PopupCB, "Popup2");

CommonPause();

n = 0;
XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_AUTOMATIC_RECURSIVE); n++;
XtSetValues(popup1, args, n);
XtSetValues(popup2, args, n);

CommonPause();

n = 0;
XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++;
XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_DISABLED); n++;
XtSetValues(popup1, args, n);
XtSetValues(popup2, args, n);
XtAddEventHandler(drawarea, ButtonPressMask, False, PostMenu, popup1);
XtAddEventHandler(text1, ButtonPressMask, False, PostMenu, popup2);

CommonPause();

n = 0;
XtSetArg(args[n], XmNpopupEnabled, XmPOPUP_KEYBOARD); n++;
XtSetValues(popup1, args, n);
XtSetValues(popup2, args, n);

CommonPause();

  XtAppMainLoop(app_context);
  return(1);
}
