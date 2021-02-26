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
static char rcsid[] = "$XConsortium: PopupMenu3.c /main/9 1995/07/13 18:52:17 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

/*  Global Variables  */
Widget Label, PopupMenu1, PopupMenu2, Label1, Separator1;
Widget PushBtn1, ToggleBtn1, Label2, Separator2, PushBtn2;
Widget ToggleBtn2, popup, MainButton, push, testingArea;

static Widget CreateLabel(char *label, Widget parent)
{
  Widget widget;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  widget = XmCreateLabel(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);
  return(widget);
}

static Widget CreatePushButton(char *label, Widget parent)
{
  Widget widget;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  widget = XmCreatePushButton(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);
  return(widget);
}

static Widget CreateToggle(char *label, Widget parent)
{
  Widget widget;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  widget = XmCreateToggleButton(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);
  return(widget);
}

static Widget CreateSeparator(Widget parent, char *name)
{
  Widget widget;
  widget = XmCreateSeparator(parent, name, NULL, 0);
  XtManageChild(widget);
  return(widget);
}

int main(int argc, char **argv)
{
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs;
    void PostPopup();
    void ButtonCB();

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  200);  n++;
    XtSetArg(args[n], XmNheight, 40);   n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    Label = CreateLabel("Press MB3 to dismiss PopupMenu", Shell1);

    /*
    **  PopupMenu1
    */

    n = 0;
    XtSetArg(args[n], XmNx,  100);  n++;
    XtSetArg(args[n], XmNy, 100);   n++;
    XtSetArg(args[n], XmNmenuAccelerator, NULL); n++;
    PopupMenu1 = XmCreatePopupMenu(Label, "popupMenu", args, n);

    /*
    **  Menu1
    */

    Label1 = CreateLabel("Menu1", PopupMenu1);
    Separator1 = CreateSeparator(PopupMenu1, "Separator1");
    PushBtn1 = CreatePushButton("PushButton1", PopupMenu1);
    ToggleBtn1 = CreateToggle("Toggle1", PopupMenu1);
    XtManageChild(PopupMenu1);

    CommonPause();
    XtDestroyWidget(PopupMenu1);
    
    n =0;
    XtSetArg(args[n], XmNrowColumnType, XmMENU_POPUP); n++;
    PopupMenu2 = XmCreateRowColumn(Shell1, "popupMenu2", args, n);

    /*
    **  Menu2
    */

    Label2 = CreateLabel("Menu2", PopupMenu2);
    Separator2 = CreateSeparator(PopupMenu2, "Separator2");
    PushBtn2 = CreatePushButton("PushButton2", PopupMenu2);
    ToggleBtn2 = CreateToggle("Toggle2", PopupMenu2);
    XtManageChild(PopupMenu2);

    CommonPause();

    XtDestroyWidget(Label);
    XtDestroyWidget(PopupMenu2);

    /*
     *  Test 3 for PIR 2669
     */

    n = 0;
    testingArea = XmCreateBulletinBoard(Shell1, "PushButtonHere", args, n);

    n = 0;
    XtSetArg(args[n], XmNx, 10); n++;
    XtSetArg(args[n], XmNy, 30); n++;
    MainButton = XmCreatePushButton(testingArea, "button0", args, n);
    XtAddCallback(MainButton, XmNactivateCallback, ButtonCB, (XtPointer) 0); 
    XtManageChild(MainButton);

    popup = XmCreatePopupMenu(testingArea, "Popups", NULL, 0);
    XtAddEventHandler(testingArea, ButtonPressMask, FALSE, PostPopup, popup);
    
    XmAddToPostFromList(popup, MainButton);
    
    push = XmCreatePushButton(popup, "button1", NULL, 0);
    XtAddCallback(push, XmNactivateCallback, ButtonCB, (XtPointer) 1);
    XtManageChild(push);

    push = XmCreatePushButton(popup, "button2", NULL, 0);
    XtAddCallback(push, XmNactivateCallback, ButtonCB, (XtPointer) 2);
    XtManageChild(push);

    push = XmCreatePushButton(popup, "button3", NULL, 0);
    XtAddCallback(push, XmNactivateCallback, ButtonCB, (XtPointer) 3);
    XtManageChild(push);
    
    XtManageChild(testingArea);
    
    CommonPause();

    XtDestroyWidget(testingArea);

    CommonPause();

    XtAppMainLoop(app_context);
}

void PostPopup(Widget widget, XmRowColumnWidget popup, XEvent *event)
{
  printf("PostPopup\n");
  XmMenuPosition((Widget) popup, &event->xbutton);
  XtManageChild((Widget) popup);
}

void ButtonCB(Widget widget, XtPointer n, XtPointer call_data)
{
  printf("Callback button %d\n", (int) n);
}
