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
static char rcsid[] = "$XConsortium: Menu7.c /main/5 1995/07/13 18:46:13 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <X11/StringDefs.h>

Widget mainWindow = NULL, MenuBar, cascade1, cascade2, ob1, ob2, ob3, ob4;
Widget pb1, pb2, pb3, pb4, newkid1, newkid2, newkid3;
Widget submenu4, submenu6, pulldown1, pulldown2, w;

int main(argc, argv)
int argc;
char **argv;
{
  register int  n;
  Arg args[MAX_ARGS];
  Arg nargs[MAX_ARGS];
  int i;
  char buf[32];
  XmString string, tcs;

  CommonTestInit(argc, argv);

  /* 
   * The parent of all this will be a main window
   */
  mainWindow = XmCreateMainWindow(Shell1, "mainWindow", NULL, 0);
  XtManageChild(mainWindow);

  MenuBar = XmCreateMenuBar(mainWindow, "MenuBar", NULL, 0);
  XtManageChild(MenuBar);

  pulldown1 = XmCreatePulldownMenu(MenuBar, "pulldown1", NULL, 0);

  n=0;
  XtSetArg(nargs[n],XmNsubMenuId, pulldown1); n++;
  XtManageChild(XmCreateCascadeButtonGadget(MenuBar, "Menu1", nargs, n));

  pb1 = XmCreatePushButton(pulldown1, "PushButton1", args, 0);
  pb2 = XmCreatePushButton(pulldown1, "PushButton2", args, 0);
  pb3 = XmCreatePushButton(pulldown1, "PushButton3", args, 0);
  
  XtManageChild(pb1);
  XtManageChild(pb2);
  XtManageChild(pb3);

  pulldown2 = XmCreatePulldownMenu(MenuBar, "pulldown2", NULL, 0);
  n=0;
  XtSetArg(nargs[n],XmNsubMenuId, pulldown2); n++;
  XtManageChild(XmCreateCascadeButtonGadget(MenuBar, "Menu2", nargs, n));
  ob1 = XmCreatePushButton(pulldown2, "OtherButton1", args, 0);
  ob2 = XmCreatePushButton(pulldown2, "OtherButton2", args, 0);
  ob3 = XmCreatePushButton(pulldown2, "OtherButton3", args, 0);
  ob4 = XmCreatePushButton(pulldown2, "OtherButton4", args, 0);
  XtManageChild(ob1);
  XtManageChild(ob2);
  XtManageChild(ob3);
  XtManageChild(ob4);
  XtRealizeWidget(Shell1);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, XmLAST_POSITION); n++;
  XtSetValues(pb1, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 0); n++;
  XtSetValues(ob4, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 1); n++;
  XtSetValues(ob3, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 2); n++;
  XtSetValues(ob2, args, n);

  CommonPause();

  /* Try some illegal values */

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, -3); n++;
  XtSetValues(ob2, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 20); n++;
  XtSetValues(pb2, args, n);
  CommonPause();

  /* Add some to the middle */

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 2); n++;
  newkid1 = XmCreatePushButton(pulldown1, "NewKid1", args, n);
  XtManageChild(newkid1);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, XmLAST_POSITION); n++;
  newkid2 = XmCreatePushButton(pulldown2, "NewKid2", args, n);
  XtManageChild(newkid2);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 0); n++;
  newkid3 = XmCreatePushButton(pulldown2, "NewKid3", args, n);
  XtManageChild(newkid3);

  CommonPause();

  CommonPause(); /* Exit */
  XtAppMainLoop(app_context);
  return(1);
}












