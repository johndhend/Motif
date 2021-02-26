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
static char rcsid[] = "$XConsortium: PopupMenu5.c /main/9 1995/07/13 18:53:02 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget popup11, popup12, popup31, popup32, popup;

void menu_handler(Widget w, XtPointer tag, XEvent *event, Boolean *c)
{
  printf("MenuHandler: button %d\n", event->xbutton.button);
  if ((int)(long)tag == 1) 
    switch (event->xbutton.button) {
    case Button1:
      XmMenuPosition(popup11, (XButtonPressedEvent *)event);
      XtManageChild(popup11);
      break;
    case Button3:
      XmMenuPosition(popup31, (XButtonPressedEvent *)event);
      XtManageChild(popup31);
      break;
    }
  else if ((int)(long)tag == 2)
    switch (event->xbutton.button) {
    case Button1:
      XmMenuPosition(popup12, (XButtonPressedEvent *)event);
      XtManageChild(popup12);
      break;
    case Button3:
      XmMenuPosition(popup32, (XButtonPressedEvent *)event);
      XtManageChild(popup32);
      break;
    }
}

void menu_handler3(Widget w, XtPointer tag, XEvent *event,Boolean *c)
{
  printf("whichButton = 3, handler called for Button %d\n", 
	 event->xbutton.button);

  if (event->xbutton.button == 3)
    {
      XmMenuPosition(popup11, (XButtonPressedEvent *)event);
      XtManageChild(popup11);
    }
}

void menu_post3(Widget w, XtPointer tag, XEvent *event, Boolean *c)
{
  printf("menuPost = 3, handler called for Button %d\n", 
	 event->xbutton.button);

  if (event->xbutton.button == 3)
    {
      XmMenuPosition(popup11, (XButtonPressedEvent *)event);
      XtManageChild(popup11);
    }
}

void menu_post1(Widget w, XtPointer tag, XEvent *event, Boolean *c)
{
  printf("menuPost = 3, handler called for Button %d\n", 
	 event->xbutton.button);

  if (event->xbutton.button == 1)
    {
      printf("Button \n");

    }
}

void main(argc, argv)
int argc;
char *argv[];
{
  Widget label, label2, rc, bb,push1;
  Arg args[10];
  int n;

  /* initialize toolkit; classname is XMcommon; sets global Shell1  */

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);

  /* Pause 1 */

  /* Begin test case for PIR 2968 */

  n = 0;
  rc = XmCreateRowColumn(Shell1, "rc", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNborderWidth, 3); n++;
  label = XmCreateLabel(rc, "Popup_with_whichButton", args, n);
  label2 = XmCreateLabel(rc, "Popup_with_menuPost", args, n);

  XtManageChild(label);
  XtManageChild(label2);
  XtManageChild(rc);

  XtAddEventHandler(label, ButtonPressMask, FALSE, menu_handler, (XtPointer) 1);
  XtAddEventHandler(label2, ButtonPressMask, FALSE, menu_handler, (XtPointer) 2);

  XtSetArg(args[0], XmNwhichButton, Button1);
  popup11 = XmCreatePopupMenu(label, "popup11", args, 1);

  XtSetArg(args[0], XmNmenuPost, "<Btn1>");
  popup12 = XmCreatePopupMenu(label2, "popup12", args, 1);

  XtSetArg(args[0], XmNwhichButton, Button3);
  popup31 = XmCreatePopupMenu(label, "popup31", args, 1);

  XtSetArg(args[0], XmNmenuPost, "<Btn3>");
  popup32 = XmCreatePopupMenu(label2, "popup32", args, 1);


  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  XtManageChild(XmCreatePushButton(popup12, "12entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup12, "12entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup12, "12entry3", NULL, 0));


  XtManageChild(XmCreatePushButton(popup31, "31entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup31, "31entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup31, "31entry3", NULL, 0));

  XtManageChild(XmCreatePushButton(popup32, "32entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "32entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "32entry3", NULL, 0));

  XtRealizeWidget(Shell1);

  CommonPause();

  /* Pause 2 */

  /*  Now try it at SetValues time */

  XtDestroyWidget(rc);  /* Test for PIR 2972; no warnings should occur */

  n = 0;
  rc = XmCreateRowColumn(Shell1, "rc", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNborderWidth, 3); n++;
  label = XmCreateLabel(rc, "Popup_with_whichButton", args, n);
  label2 = XmCreateLabel(rc, "Popup_with_menuPost", args, n);

  XtManageChild(label);
  XtManageChild(label2);
  XtManageChild(rc);

  XtAddEventHandler(label, ButtonPressMask, FALSE, menu_handler, (XtPointer) 1);
  XtAddEventHandler(label2, ButtonPressMask, FALSE, menu_handler, (XtPointer) 2);

  popup11 = XmCreatePopupMenu(label, "popup11", NULL, 0);

  XtSetArg(args[0], XmNwhichButton, Button1);
  XtSetValues(popup11, args, 1);

  popup12 = XmCreatePopupMenu(label2, "popup12", NULL, 0);

  XtSetArg(args[0], XmNmenuPost, "<Btn1>");
  XtSetValues(popup12, args, 1);

  popup31 = XmCreatePopupMenu(label, "popup31", NULL, 0);

  XtSetArg(args[0], XmNwhichButton, Button3);
  XtSetValues(popup31, args, 1);

  popup32 = XmCreatePopupMenu(label2, "popup32", NULL, 0);

  XtSetArg(args[0], XmNmenuPost, "<Btn3Down>");
  XtSetValues(popup32, args, 1);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  XtManageChild(XmCreatePushButton(popup12, "12entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup12, "12entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup12, "12entry3", NULL, 0));

  XtManageChild(XmCreatePushButton(popup31, "31entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup31, "31entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup31, "31entry3", NULL, 0));

  XtManageChild(XmCreatePushButton(popup32, "32entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "32entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "32entry3", NULL, 0));

  /* End test case for PIR 2968 */

  CommonPause();
  
  /* Pause 3 */

  /* 
   *  Test: whichButton = Btn3, event handler set for bulletinBoard
   *   and pushButton
   */

  XtDestroyWidget(rc);   /* Test for PIR 2972; no warnings should occur */

  bb = XmCreateBulletinBoard(Shell1, "bb", args, 0);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  push1 = XmCreatePushButton(bb, "push1", args, n);

  XtAddEventHandler(push1, ButtonPressMask, FALSE, menu_handler3, NULL);
  XtAddEventHandler(bb, ButtonPressMask, FALSE, menu_handler3, NULL);

  XtSetArg(args[0], XmNwhichButton, Button3);
  popup11 = XmCreatePopupMenu(bb, "popup11", args, 1);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  XtManageChild(push1);
  XtManageChild(bb);

  CommonPause();

  /* Pause 4 */

  /* Test: whichButton = Btn3, event handler set for push button */
  
  XtDestroyWidget(popup11);
  XtDestroyWidget(push1);
  XtDestroyWidget(bb);

  bb = XmCreateBulletinBoard(Shell1, "bb", args, 0);

  n = 0;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  push1 = XmCreatePushButton(bb, "push1", args, n);
  XtManageChild(push1);
  XtManageChild(bb);

  XtAddEventHandler(push1, ButtonPressMask, FALSE, menu_handler3, NULL);

  n = 0;
  XtSetArg(args[n], XmNwhichButton, Button3); n++;
  popup11 = XmCreatePopupMenu(push1, "popup11", args, n);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  CommonPause();

  /* Pause 5 */
  
  /* 
   * Test: menuPost = Btn3, Set event handler on BulletinBoard
   *  and pushbutton 
   */

  XtDestroyWidget(bb);   /* Test for PIR 2972; no warnings should occur */

  bb = XmCreateBulletinBoard(Shell1, "bb", args, 0);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  push1 = XmCreatePushButton(bb, "push1", args, n);

  XtAddEventHandler(push1, ButtonPressMask, FALSE, menu_post3, NULL); 
  XtAddEventHandler(bb, ButtonPressMask, FALSE, menu_post3, NULL);

  XtSetArg(args[0], XmNmenuPost, "<Btn3>");
  popup11 = XmCreatePopupMenu(bb, "popup11", args, 1);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  XtManageChild(push1);
  XtManageChild(bb);

  CommonPause();

  /* Pause 6 */

  /* Test: menuPost = Btn3, event handler set on push button */
  
  XtDestroyWidget(popup11);
  XtDestroyWidget(push1);
  XtDestroyWidget(bb);

  bb = XmCreateBulletinBoard(Shell1, "bb", args, 0);

  n = 0;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  push1 = XmCreatePushButton(bb, "push1", args, n);
  XtManageChild(push1);
  XtManageChild(bb);

  XtAddEventHandler(push1, ButtonPressMask, FALSE, menu_post3, NULL);

  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn3>"); n++;
  popup11 = XmCreatePopupMenu(push1, "popup11", args, n);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));
  
  CommonPause();

  /* Pause 7 */

  /* 
   * Test: menuPost = Btn3, Set event handler on BulletinBoard
   */

  /*
   *  Begin test for PIR 3432
   */

  XtDestroyWidget(bb);

  bb = XmCreateBulletinBoard(Shell1, "bb", args, 0);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNx, 25); n++;
  XtSetArg(args[n], XmNy, 25); n++;
  push1 = XmCreatePushButton(bb, "push1", args, n);

  XtAddEventHandler(bb, ButtonPressMask, FALSE, menu_post3, NULL);

  XtSetArg(args[0], XmNmenuPost, "<Btn3>");
  popup11 = XmCreatePopupMenu(bb, "popup11", args, 1);

  XtManageChild(XmCreatePushButton(popup11, "11entry1", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry2", NULL, 0));
  XtManageChild(XmCreatePushButton(popup11, "11entry3", NULL, 0));

  XtManageChild(push1);
  XtManageChild(bb);

  /*
   *  End test for PIR 3432
   */
  CommonPause();

  XtDestroyWidget(bb);   /* Test for PIR 2972; no warnings should occur */

  /* Pause 8 */

  CommonPause();   /* Exit */

  XtAppMainLoop(app_context); 
}




