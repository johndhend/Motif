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
static char rcsid[] = "$XConsortium: MainWin2.c /main/9 1995/07/13 19:46:45 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 * Create a MainWindow, with a RowColumn button box as the command window
 *
 * Add a message area label widget
 *
 * change the command window location
 *
 ************************************************************************/

#include <signal.h>
#include <testlib.h>

void main (argc, argv)
int argc;
char **argv;
{
   Widget main_id;
   Widget bb_id;
   Widget label_id;
   Widget command_id;
   Widget rc_id;
   Widget pb1_id;
   Widget pb2_id;
   Widget pb3_id;
   Widget pb4_id;

   Arg args[10];
   int n;
   int i;

   CommonTestInit(argc, argv);
    
   n = 0;
   XtSetArg(args[n], XmNwidth, 400); 			n++;
   XtSetArg(args[n], XmNheight, 400);			n++;
   XtSetArg(args[n], XmNshowSeparator, True);		n++;
   XtSetArg(args[n], XmNcommandWindowLocation, XmCOMMAND_ABOVE_WORKSPACE); n++;
   main_id = XmCreateMainWindow(Shell1, "main", args, n);
   XtManageChild(main_id);

   n = 0;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL); 	n++;
   rc_id = XmCreateRowColumn(main_id, "rc", args, n);
   XtManageChild(rc_id);

   n = 0;
   pb1_id = XmCreatePushButton(rc_id, "pb1", args, n);
   XtManageChild(pb1_id);

   pb2_id = XmCreatePushButton(rc_id, "pb2", args, n);
   XtManageChild(pb2_id);

   pb3_id = XmCreatePushButton(rc_id, "pb3", args, n);
   XtManageChild(pb3_id);

   pb4_id = XmCreatePushButton(rc_id, "pb4", args, n);
   XtManageChild(pb4_id);

   n = 0;
   XtSetArg(args[n], XmNwidth, 300); 			n++;
   XtSetArg(args[n], XmNheight, 300); 			n++;
   bb_id = XmCreateBulletinBoard(main_id, "bb", args, n);
   XtManageChild(bb_id);

   /* test case for PIR 4140 */
   XmMainWindowSetAreas (main_id, NULL, rc_id, NULL, NULL, bb_id);

   XtRealizeWidget(Shell1);

   CommonPause();
   /* end of test case for PIR 4140 */

   label_id = XmCreateLabel(main_id, "Message Area", NULL, 0);
   XtManageChild(label_id);

   n = 0;
   XtSetArg(args[n], XmNmessageWindow, label_id); 	n++;
   XtSetValues(main_id, args, n);

   CommonPause();

   XtSetArg(args[n], XmNcommandWindowLocation, XmCOMMAND_BELOW_WORKSPACE); n++;
   XtSetValues(main_id, args, n);

   CommonPause();

   XtAppMainLoop(app_context);
}
