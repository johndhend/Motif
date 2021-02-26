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
static char rcsid[] = "$TOG: PanedWin1.c /main/5 1999/08/04 13:17:23 mgreess $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.4              *
*       Fri Jun  2 11:59:53 1989        *
****************************************/

#include <testlib.h>

Widget PB1, PB2, PB3;
Widget PanedWindow1;
Widget rc, textw;
int		counter = 0;

void add_buttons(w, client, call)
Widget w;
XtPointer client, call;
{
  int i;
  char str[10];
  Arg args[2];
  int n;

  n = 0;
  XtSetArg(args[n], XmNheight, 20); n++;
  XtSetArg(args[n], XmNwidth, 40); n++;
  for (i=0; i<8; i++) {
    sprintf(str, "%d-%d", counter, i);
    XtManageChild(XmCreatePushButton(rc, str, args, n));
  }
  counter++;
}	


void  main(argc, argv)
int argc;
char **argv;
{
  register int  n;
  Arg           args[MAX_ARGS];
  XmString      tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetValues(Shell1, args, n);
    
  XtRealizeWidget(Shell1);

  printf("Paned Window created.\n");
  n = 0;
  PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1", args, n);
  XtManageChild(PanedWindow1);

  CommonPause();

  printf("Creating push button PB1 with XmNmappedWhenManaged set to true.\n");
  n = 0;
  PB1 = XmCreatePushButton(PanedWindow1, "PB1", args, n);
  XtManageChild(PB1);

  CommonPause();

  printf("Creating push button PB2 with XmNmappedWhenManaged set to false.\n");
  n = 0;
  XtSetArg(args[n], XmNmappedWhenManaged,  False);  n++;
  PB2 = XmCreatePushButton(PanedWindow1, "PB2", args, n);
  XtManageChild(PB2);

  CommonPause();

  printf("Creating push button PB3 with XmNmappedWhenManaged set to true.\n");
  n = 0;
  PB3 = XmCreatePushButton(PanedWindow1, "PB3", args, n);
  XtManageChild(PB3);

  CommonPause();
  
  printf("Setting PB2's XmNmappedWhenManaged to true via XtSetValues.\n");
  n = 0;
  XtSetArg(args[n], XmNmappedWhenManaged,  True);  n++;
  XtSetValues(PB2, args, n);

  CommonPause();
  
  XtSetMappedWhenManaged(PB1,FALSE);
  printf(
  "Setting PB1's XmNmappedWhenManaged to false via XtSetMappedWhenManaged.\n");

  CommonPause();

  printf("Setting PB1's XmNmappedWhenManaged to true via XtSetValues.\n");
  n = 0;
  XtSetArg(args[n], XmNmappedWhenManaged,  True);  n++;
  XtSetValues(PB1, args, n);

  CommonPause();

  /* two variations on test for PIR 3063. Note there are several resource
     settings that make the problems disappear; see the PIR report for
     details.
     */

  XtDestroyWidget (PB2);

  n=0;
  tcs = XmStringCreateSimple("Push Me");
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNheight, 30); n++;
  XtSetArg(args[n], XmNskipAdjust, True); n++;
  XtSetArg(args[n], XmNallowResize, False); n++;
  XtSetArg(args[n], XmNpaneMinimum, 30); n++;	
  XtSetArg(args[n], XmNpaneMaximum, 30); n++;
  XtSetValues (PB1, args, n);
  XtAddCallback(PB1, XmNactivateCallback, add_buttons, 0);

  n=0;
  XtSetArg(args[n], XmNallowResize, True); n++;
  XtSetArg(args[n], XmNskipAdjust, False); n++;
  XtSetArg(args[n], XmNpaneMinimum, 10); n++;
  XtSetArg(args[n], XmNpaneMaximum, 1000); n++;
  rc = XmCreateRowColumn(PanedWindow1, "rc", args, n);
  XtManageChild(rc);

  CommonPause();
  
  XtDestroyWidget(rc);
  XtDestroyWidget(PB3);

  n=0;
  XtSetArg(args[n], XmNallowResize, True); n++;
  XtSetArg(args[n], XmNskipAdjust, False); n++;
  XtSetArg(args[n], XmNpaneMinimum, 10); n++;
  XtSetArg(args[n], XmNpaneMaximum, 1000); n++;
  rc = XmCreateRowColumn(PanedWindow1, "rc", args, n);
  XtManageChild(rc);

  n = 0;
  PB3 = XmCreatePushButton (PanedWindow1, "PB3", args, n);
  XtManageChild (PB3);
  
  CommonPause();
    
  /* end of test for PIR 3063 */

  XtDestroyWidget(PanedWindow1);

  /* begin test for PIR 2327 */

  PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1", args, n);
  XtManageChild(PanedWindow1);
    
  CommonPause();

  n = 0;
  textw = XmCreateScrolledText(PanedWindow1, "ScrollText", args, n);
  XtManageChild(textw);

  CommonPause();

  XtDestroyWidget(XtParent(textw));
  CommonPause();

  XtAppMainLoop(app_context);

}



