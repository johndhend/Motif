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
static char rcsid[] = "$XConsortium: PopupMenu6.c /main/8 1995/07/13 18:53:32 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget popup11, popup12, popup21, popup22, popup31, popup32, popup;
Widget popup1, popup2, popup3;
Widget drawAreaParent, drawAreaChild, pushChild, pushChild2;

sleep_handler(Widget w, int tag, XEvent *event)
{
  if (event->xbutton.button == 3)
    {
      XmMenuPosition(popup11, (XButtonPressedEvent *) event);
      XtManageChild(popup11);
    }
}

sleep_rtn(Widget w, int tag, XEvent *event)
{
  printf("Sleeping...\n");
  sleep(5);
  printf("Brrrrring, Brrrring, Time to get up!\n");
}

static void SayCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  (void)fprintf(stderr, "SayCB: %s\n", (char *)client_data);
}

void PostWhich3(Widget w, XtPointer popup, XEvent *ev,
           Boolean *continue_to_dispatch)
{
  XButtonEvent * event = (XButtonEvent *) ev;
  printf("whichButton = 3,  button %d\n", event->button);

  if (event->button != Button3)
    return;
  XmMenuPosition((Widget) popup, event);
  XtManageChild((Widget) popup);
  *continue_to_dispatch = False;
}

void PostMenu3(Widget w, XtPointer popup, XEvent *ev, Boolean *c)
{
  XButtonEvent * event = (XButtonEvent *) ev;
  printf("menuPost = 3, button %d\n", event->button);

  if (event->button != Button3)
    return;
  XmMenuPosition((Widget)popup, event);
  XtManageChild((Widget)popup);
}

void main(argc, argv)
int argc;
char *argv[];
{
  Widget label, label2, rc, bb,push1;
  Widget pushbutton, m1, m2, m3, text, n1, n2, n3, o1, o2, o3;
  Arg args[10];
  int n;

  /* initialize toolkit; classname is XMcommon; sets global Shell1  */

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);

  /* Pause 1 */

  /* Test: whichButton = 3, RowColumn */

  XtManageChild(rc=XmCreateRowColumn(Shell1, "rc", NULL, 0));
  XtManageChild(label = XmCreateLabel(rc, "label", NULL, 0));
  XtManageChild(text = XmCreateText(rc, "text", NULL, 0));

  n = 0;
  XtSetArg(args[n], XmNwhichButton, 3); n++;
  popup = XmCreatePopupMenu(rc, "popup", args, n);

  XtAddEventHandler(rc, ButtonPressMask, False, PostWhich3, popup);
/*  
  XtAddEventHandler(label, ButtonPressMask, False, PostWhich2, popup);
  XtAddEventHandler(text, ButtonPressMask, False, PostWhich2, popup);
*/

  XtManageChild(m1 = XmCreatePushButton(popup, "m1", NULL, 0));
  XtManageChild(m2 = XmCreatePushButton(popup, "m2", NULL, 0));
  XtManageChild(m3 = XmCreatePushButton(popup, "m3", NULL, 0));

  XtAddCallback(m1, XmNactivateCallback, SayCB, "button M1");
  XtAddCallback(m2, XmNactivateCallback, SayCB, "button M2");
  XtAddCallback(m3, XmNactivateCallback, SayCB, "button M3");

  XtManageChild(pushbutton = XmCreatePushButton(rc, "pushbutton", NULL, 0));
/*  XtAddEventHandler(pushbutton, ButtonPressMask, False, PostWhich2, popup);
*/

  XtRealizeWidget(Shell1);

  CommonPause();  

  /* Pause 2 */

  /* Begin Test for PIR 2967 and PIR 3435 */

  XtDestroyWidget(rc);   /* No warnings should occur! */

  XtManageChild(rc=XmCreateRowColumn(Shell1, "rc", NULL, 0));
  XtManageChild(label = XmCreateLabel(rc, "label", NULL, 0));
  XtManageChild(text = XmCreateText(rc, "text", NULL, 0));

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++;
  popup = XmCreatePopupMenu(rc, "popup", args, n);

  XtAddEventHandler(rc, ButtonPressMask, False, PostMenu3, popup);
/*  XtAddEventHandler(label, ButtonPressMask, False, PostMenu2, popup);
  XtAddEventHandler(text, ButtonPressMask, False, PostMenu2, popup);
*/

  XtManageChild(m1 = XmCreatePushButton(popup, "m1", NULL, 0));
  XtManageChild(m2 = XmCreatePushButton(popup, "m2", NULL, 0));
  XtManageChild(m3 = XmCreatePushButton(popup, "m3", NULL, 0));
  XtAddCallback(m1, XmNactivateCallback, SayCB, "button M1");
  XtAddCallback(m2, XmNactivateCallback, SayCB, "button M2");
  XtAddCallback(m3, XmNactivateCallback, SayCB, "button M3");

  XtManageChild(pushbutton = XmCreatePushButton(rc, "pushbutton", NULL, 0));
 /* XtAddEventHandler(pushbutton, ButtonPressMask, False, PostMenu2, popup);
	*/

  /* End test for PIR 2967 */

  CommonPause();

  /* Pause 3 */

  XtDestroyWidget(rc);

  XtManageChild(rc=XmCreateRowColumn(Shell1, "rc", NULL, 0));
  XtManageChild(label = XmCreateLabel(rc, "label", NULL, 0));
  XtManageChild(text = XmCreateText(rc, "text", NULL, 0));

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++;
  popup = XmCreatePopupMenu(rc, "popup", args, n);

  XtAddEventHandler(rc, ButtonPressMask, False, PostMenu3, popup);
 /* XtAddEventHandler(text, ButtonPressMask, False, PostMenu3, popup);
  XtAddEventHandler(label, ButtonPressMask, False, PostMenu3, popup);
*/

  XtManageChild(m1 = XmCreatePushButton(popup, "m1", NULL, 0));
  XtManageChild(m2 = XmCreatePushButton(popup, "m2", NULL, 0));
  XtManageChild(m3 = XmCreatePushButton(popup, "m3", NULL, 0));
  XtAddCallback(m1, XmNactivateCallback, SayCB, "button M1");
  XtAddCallback(m2, XmNactivateCallback, SayCB, "button M2");
  XtAddCallback(m3, XmNactivateCallback, SayCB, "button M3");

  XtManageChild(pushbutton = XmCreatePushButton(rc, "pushbutton", NULL, 0));
  /* XtAddEventHandler(pushbutton, ButtonPressMask, False, PostMenu3, popup);
*/

  CommonPause();

  /* Pause 4 */

  /*  
   *  Create a drawing area with a drawing area child, and a push 
   *   button child.  Associate a popupmenu with the parent drawing
   *   area and the child drawing area, and a different one with the 
   *   push button drawing area.
   */

  XtDestroyWidget(rc);

  n = 0;
  XtSetArg(args[n], XmNwidth, 500); n++;
  XtSetArg(args[n], XmNheight, 500); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_ANY); n++;
  drawAreaParent = XmCreateDrawingArea(Shell1, "DrawAreaParent", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 50); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  pushChild = XmCreatePushButton(drawAreaParent, "MB3 to popup", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNmarginWidth, 50); n++;
  XtSetArg(args[n], XmNmarginHeight, 50); n++;
  XtSetArg(args[n], XmNborderWidth, 5); n++;
  XtSetArg(args[n], XmNx, 300); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW); n++;
  drawAreaChild = XmCreateDrawingArea(drawAreaParent, 
				      "DrawAreaParent", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  pushChild2 = XmCreatePushButton(drawAreaChild, "Push Me", args, n);

  XtManageChild(drawAreaParent);
  XtManageChild(pushChild2);
  XtManageChild(drawAreaChild);
  XtManageChild(pushChild);

  /* Create 2 different popups */

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup2 = XmCreatePopupMenu(drawAreaParent, "popup2", args, n);

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup3 = XmCreatePopupMenu(pushChild, "popup3", args, n);

  XtManageChild(n1 = XmCreatePushButton(popup2, "DrawChild1", NULL, 0));
  XtManageChild(n2 = XmCreatePushButton(popup2, "DrawChild2", NULL, 0));
  XtManageChild(n3 = XmCreatePushButton(popup2, "DrawChild3", NULL, 0));

  XtManageChild(o1 = XmCreatePushButton(popup3, "PushChild1", NULL, 0));
  XtManageChild(o2 = XmCreatePushButton(popup3, "PushChild2", NULL, 0));
  XtManageChild(o3 = XmCreatePushButton(popup3, "PushChild3", NULL, 0));

  XtAddEventHandler(drawAreaParent, ButtonPressMask, False, PostMenu3, popup2);
/*
  XtAddEventHandler(drawAreaChild, ButtonPressMask, False, PostMenu3, popup2);
  XtAddEventHandler(pushChild, ButtonPressMask, False, PostMenu3, popup3);
*/

  CommonPause();

  /* Pause 5 */

  /*  
   *  Create a drawing area with a drawing area child, and a push 
   *   button child.  Associate a popupmenu with the parent drawing
   *   area and the child drawing area, and a different one with the 
   *   push button drawing area.
   */

  XtDestroyWidget(drawAreaParent);

  n = 0;
  XtSetArg(args[n], XmNwidth, 500); n++;
  XtSetArg(args[n], XmNheight, 500); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_ANY); n++;
  drawAreaParent = XmCreateDrawingArea(Shell1, "DrawAreaParent", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 50); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  pushChild = XmCreatePushButton(drawAreaParent, "MB2 to popup", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNmarginWidth, 50); n++;
  XtSetArg(args[n], XmNmarginHeight, 50); n++;
  XtSetArg(args[n], XmNborderWidth, 5); n++;
  XtSetArg(args[n], XmNx, 300); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW); n++;
  drawAreaChild = XmCreateDrawingArea(drawAreaParent, 
				      "DrawAreaParent", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  pushChild2 = XmCreatePushButton(drawAreaChild, "Push Me", args, n);

  XtManageChild(drawAreaParent);
  XtManageChild(pushChild2);
  XtManageChild(drawAreaChild);
  XtManageChild(pushChild);

  /* Create 2 different popups */

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup2 = XmCreatePopupMenu(drawAreaParent, "popup2", args, n);

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup3 = XmCreatePopupMenu(pushChild, "popup3", args, n);

  XtManageChild(n1 = XmCreatePushButton(popup2, "DrawChild1", NULL, 0));
  XtManageChild(n2 = XmCreatePushButton(popup2, "DrawChild2", NULL, 0));
  XtManageChild(n3 = XmCreatePushButton(popup2, "DrawChild3", NULL, 0));

  XtManageChild(o1 = XmCreatePushButton(popup3, "PushChild1", NULL, 0));
  XtManageChild(o2 = XmCreatePushButton(popup3, "PushChild2", NULL, 0));
  XtManageChild(o3 = XmCreatePushButton(popup3, "PushChild3", NULL, 0));

  XtAddEventHandler(drawAreaParent, ButtonPressMask, False, PostMenu3, popup2);
  XtAddEventHandler(drawAreaChild, ButtonPressMask, False, PostMenu3, popup2);
  XtAddEventHandler(pushChild, ButtonPressMask, False, PostMenu3, popup3);

  CommonPause();

  XtDestroyWidget(drawAreaParent);

  /* Pause 6 */

  /* Begin Test case for PIR 3436 */

  /*  
   *  Create a drawing area with a drawing area child, and a push 
   *   button child.  Three different popup menus get created as children
   *   of the three widgets.
   */

  n = 0;
  XtSetArg(args[n], XmNwidth, 500); n++;
  XtSetArg(args[n], XmNheight, 500); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_ANY); n++;
  drawAreaParent = XmCreateDrawingArea(Shell1, "DrawAreaParent", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 50); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  pushChild = XmCreatePushButton(drawAreaParent, "MB3 to popup", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNmarginWidth, 50); n++;
  XtSetArg(args[n], XmNmarginHeight, 50); n++;
  XtSetArg(args[n], XmNborderWidth, 5); n++;
  XtSetArg(args[n], XmNx, 300); n++;
  XtSetArg(args[n], XmNy, 50); n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW); n++;
  drawAreaChild = XmCreateDrawingArea(drawAreaParent, 
				      "DrawAreaParent", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  pushChild2 = XmCreatePushButton(drawAreaChild, "Push Me", args, n);

  XtManageChild(drawAreaParent);
  XtManageChild(pushChild2);
  XtManageChild(drawAreaChild);
  XtManageChild(pushChild);

  /* Create 3 different popups */

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup1 = XmCreatePopupMenu(drawAreaParent, "popup1", args, n);

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup2 = XmCreatePopupMenu(drawAreaChild, "popup2", args, n);

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3Down>"); n++; 
  popup3 = XmCreatePopupMenu(pushChild, "popup3", args, n);

  XtManageChild(m1 = XmCreatePushButton(popup1, "Parent1", NULL, 0));
  XtManageChild(m2 = XmCreatePushButton(popup1, "Parent2", NULL, 0));
  XtManageChild(m3 = XmCreatePushButton(popup1, "Parent3", NULL, 0));

  XtManageChild(n1 = XmCreatePushButton(popup2, "DrawChild1", NULL, 0));
  XtManageChild(n2 = XmCreatePushButton(popup2, "DrawChild2", NULL, 0));
  XtManageChild(n3 = XmCreatePushButton(popup2, "DrawChild3", NULL, 0));

  XtManageChild(o1 = XmCreatePushButton(popup3, "PushChild1", NULL, 0));
  XtManageChild(o2 = XmCreatePushButton(popup3, "PushChild2", NULL, 0));
  XtManageChild(o3 = XmCreatePushButton(popup3, "PushChild3", NULL, 0));

  XtAddEventHandler(drawAreaParent, ButtonPressMask, False, PostMenu3, popup1);
  XtAddEventHandler(drawAreaChild, ButtonPressMask, False, PostMenu3, popup2);
  XtAddEventHandler(pushChild, ButtonPressMask, False, PostMenu3, popup3);

  CommonPause();

  /* End test case for PIR 3436 */

  /* Pause 7 */

  XtDestroyWidget(drawAreaParent);

  CommonPause(); /* exit */

  XtAppMainLoop(app_context); 
}
