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
static char rcsid[] = "$XConsortium: PopupMenu4.c /main/9 1996/02/28 15:39:27 schuldy $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <Xm/Screen.h>

Widget popup11, popup12, popup21, popup22, popup31, popup32, popup;

static Boolean dyn_flag = False;

void menu_handler(Widget w, XtPointer tag, XEvent *event, Boolean *c)
{
  if (!dyn_flag)
    switch (event->xbutton.button) {
    case Button3:
      printf("MenuHandler: button %d\n", event->xbutton.button);
      XmMenuPosition(popup32, (XButtonPressedEvent *) event);
      XtManageChild(popup32);
      break;
    }
  else
    switch (event->xbutton.button) {
    case Button1:
      printf("MenuHandler: button %d\n", event->xbutton.button);
      XmMenuPosition(popup32, (XButtonPressedEvent *) event);
      XtManageChild(popup32);
      break;
    }    
}

void main(argc, argv)
int argc;
char *argv[];
{
  Widget label, label2, rc, bb,push1, xmscreen;
  Arg args[10];
  int n;

  /* initialize toolkit; classname is XMcommon; sets global Shell1  */

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);

  /* Pause 1 */


  n = 0;
  rc = XmCreateRowColumn(Shell1, "rc", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNborderWidth, 3); n++;
  label2 = XmCreateLabel(rc, "Test for XmNunpostBehavior", args, n);

  XtManageChild(label2);
  XtManageChild(rc);

  XtAddEventHandler(label2, ButtonPressMask, FALSE, menu_handler, 0);

  XtSetArg(args[0], XmNmenuPost, "<Btn3>");
  popup22 = XmCreatePopupMenu(label2, "popup22", args, 1);

  XtSetArg(args[0], XmNmenuPost, "<Btn3>");
  popup32 = XmCreatePopupMenu(label2, "popup32", args, 1);

  XtManageChild(XmCreatePushButton(popup22, "Dog", NULL, 0));
  XtManageChild(XmCreatePushButton(popup22, "Cat", NULL, 0));
  XtManageChild(XmCreatePushButton(popup22, "Bird", NULL, 0));

  XtManageChild(XmCreatePushButton(popup32, "Pink", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "Black", NULL, 0));
  XtManageChild(XmCreatePushButton(popup32, "Red", NULL, 0));

  XtRealizeWidget(Shell1);

  CommonPause();

  CommonPause();

  /* Get the XmScreen to set XmNunpostBehavior */

  xmscreen = XmGetXmScreen(screen);

  n = 0;
  XtSetArg(args[n], XmNunpostBehavior, XmUNPOST); n++;
  XtSetValues(xmscreen, args, n);

  CommonPause();

  dyn_flag = True;
  n = 0;
  XtSetArg(args[n], XmNmenuPost, "<Btn1>"); n++;
  XtSetValues(popup32, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNunpostBehavior, XmUNPOST_AND_REPLAY); n++;
  XtSetValues(xmscreen, args, n);

  CommonPause();

  CommonPause();   /* Exit */

  XtAppMainLoop(app_context); 
}




