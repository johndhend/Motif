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
static char rcsid[] = "$XConsortium: PushBGad3.c /main/8 1995/07/13 17:29:42 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <X11/Xlib.h>
#include <testlib.h>

static void  arrow1CB();
static void  arrow2CB();

Widget bb;
Widget rc1, rc2;
Widget arrow1, arrow2, arrow3, arrow4, arrow5, arrow6;

AddAllTabGroups()
{
  /* Add in correct order */
  XmAddTabGroup(rc1);
  XmAddTabGroup(rc2);
}

/*******************************************************/

void main (argc, argv)
int argc;
char **argv;
{
  Arg args[15];
  int n;

  CommonTestInit(argc, argv);
   
  bb = XmCreateBulletinBoard(Shell1, "bb", (ArgList) args, 0);
  XtManageChild(bb);

  XtSetArg(args[0], XmNborderWidth, 4); 
  rc1 = XmCreateRowColumn(bb, "rc1", (ArgList) args, 1);
  XtManageChild(rc1);
  n = 0;
  XtSetArg (args[0], XmNborderWidth, 4); n++;
  XtSetArg (args[n], XmNx, 100); n++;
  XtSetArg (args[n], XmNy, 100); n++;
  rc2 = XmCreateRowColumn(bb, "rc2", (ArgList) args, n);
  XtManageChild(rc2);

  /* resources common to all buttons */
  n = 0;
  XtSetArg(args[n], XmNtraversalOn, True); n++;
  XtSetArg(args[n], XmNhighlightThickness, 2); n++;
  XtSetArg(args[n], XmNhighlightOnEnter, True); n++;

  arrow1 = XmCreatePushButtonGadget(rc1, "arrow1", args, n);
  XtManageChild(arrow1);
  XtAddCallback(arrow1, XmNactivateCallback, arrow1CB, NULL);

  arrow2 = XmCreatePushButtonGadget(rc1, "arrow2", args, n);
  XtManageChild(arrow2);
  XtAddCallback(arrow2, XmNactivateCallback, arrow2CB, NULL);

  arrow3 = XmCreatePushButtonGadget(rc1, "arrow3", args, n);
  XtManageChild(arrow3);

  arrow4 = XmCreatePushButtonGadget(rc2, "arrow4", args, n);
  XtManageChild(arrow4);

  arrow5 = XmCreatePushButtonGadget(rc2, "arrow5", args, n);
  XtManageChild(arrow5);

  arrow6 = XmCreatePushButtonGadget(rc2, "arrow6", args, n);
  XtManageChild(arrow6);

  AddAllTabGroups();
  XtRealizeWidget (Shell1);
  CommonPause ();
  CommonPause ();
  CommonPause (); /* end */
  XtAppMainLoop(app_context);
  XtDestroyWidget(arrow1);
  XtDestroyWidget(arrow2);
  XtDestroyWidget(arrow3);
  XtDestroyWidget(arrow4);
  XtDestroyWidget(arrow5);
  XtDestroyWidget(arrow6);
  XtDestroyWidget(bb);
  XtDestroyWidget(rc1);
  XtDestroyWidget(rc2);
}

static void  arrow1CB(w, client_data, call_data)
Widget   w;
caddr_t  client_data;
caddr_t  call_data;
{
  XtManageChild(arrow2);
}

static void  arrow2CB(w, client_data, call_data)
Widget   w;
caddr_t  client_data;
caddr_t  call_data;
{
  XtUnmanageChild(arrow2);
}





