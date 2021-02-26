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
static char rcsid[] = "$TOG: FileSelect3.c /main/11 1999/05/28 15:46:09 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/* 
 * Create a file selection box with menu bar and button children, as 
 *  detailed in the Motif 1.2 specification
 */

#include <signal.h>
#include <unistd.h>
#include <testlib.h>

#define TARGET_DIR "/tmp/FS/fourteencharac/fourteencharac/fourteencharac/"

Widget fsbox;            /* File Selection Box widget   */
Widget pushButton, toggleButton, arrowButton, drawnButton;
Widget menuBar, cascButton1, cascButton2, pulldown1, pulldown2;
Widget buttonsa[3], buttonsb[3];
Widget drawingArea, scale1;

/* callbacks */

static void OkCB();

static XtCallbackRec ok_cb[] = {
  { OkCB, NULL},
  { NULL, NULL}
};

static void HelpCB();

static XtCallbackRec help_cb[] = {
  { HelpCB, NULL},
  { NULL, NULL}
};


/*-------------------------------------------------------------
**      OkCB        - callback for ok button
*/

/* ARGSUSED */

static void OkCB(Widget w, caddr_t client_data, caddr_t call_data)
{
  printf("OK Callback received\n");
}	

/*-------------------------------------------------------------
**      HelpCB        - callback for help button
*/

/* ARGSUSED */

static void HelpCB(Widget w, caddr_t client_data, caddr_t call_data)
{
  printf("Help Callback received\n");
}


void main (argc,argv)
int argc;
char **argv;
{
  Arg args[10]; 
  register int n;
  XmString tcs;
  Widget  Frame;

#ifndef MOTIF1_1

/* Ensure target directory for FSB is set up properly */

  if ( access(TARGET_DIR,F_OK | R_OK) ) {
	printf("Target directory %s is not set up\n",TARGET_DIR);
	exit(1);
  }

  /*  initialize toolkit */

  CommonTestInit(argc, argv);
  
  n = 0;
  Frame = XmCreateFrame(Shell1, "Frame", args, n);
  XtManageChild(Frame);

  tcs = XmStringCreateSimple(TARGET_DIR);

  n = 0;
  XtSetArg(args[n], XmNdirMask, tcs);                         	n++;
  XtSetArg(args[n], XmNokCallback, ok_cb); 			n++;
  XtSetArg(args[n], XmNhelpCallback, help_cb); 			n++;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_ABOVE_SELECTION); n++;
  XtSetArg(args[n], XmNheight, 410); 				n++;
  XtSetArg(args[n], XmNwidth, 400); 				n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_NONE); 		n++;
  fsbox = XmCreateFileSelectionBox(Frame, "fsbox", args, n);

  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); 				n++;
  XtSetArg(args[n], XmNheight, 75); 				n++;
  drawingArea = XmCreateDrawingArea(fsbox, "Drawarea", args, n);
  XtManageChild(drawingArea);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); 		n++;
  XtSetArg(args[n], XmNscaleWidth, 200); 			n++;
  scale1 = XmCreateScale(drawingArea, "Scale", args, n);
  XtManageChild(scale1);

  n = 0;
  pushButton = XmCreatePushButton(fsbox, "PushMe1", args, n);
  XtManageChild(pushButton);

  tcs = XmStringLtoRCreate("ToggleMe2", XmSTRING_DEFAULT_CHARSET); 

  XtSetArg(args[n], XmNlabelString, tcs); 			n++;
  toggleButton = XmCreateToggleButton(fsbox, "ToggleMe2", args, n);
  XtManageChild(toggleButton);

  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_UP); 		n++;
  arrowButton = XmCreateArrowButton(fsbox, "PointMe3", args, n);
  XtManageChild(arrowButton);

  tcs = XmStringLtoRCreate("DrawnButton", XmSTRING_DEFAULT_CHARSET);

  n = 0;
  XtSetArg(args[n], XmNpushButtonEnabled, True); 		n++;
  XtSetArg(args[n], XmNlabelString, tcs); 			n++;
  drawnButton = XmCreateDrawnButton(fsbox, "drawnbutton", args, n);
  XtManageChild(drawnButton);

  XmStringFree(tcs);

  n = 0;
  menuBar = XmCreateMenuBar(fsbox, "menuBar", args, n);
  XtManageChild(menuBar);

  n = 0;
  pulldown1 = XmCreatePulldownMenu(menuBar, "Pulldown1", args, n);
  pulldown2 = XmCreatePulldownMenu(menuBar, "Pulldown2", args, n);

  n = 0;
  XtSetArg(args[n], XmNsubMenuId, pulldown1); 			n++;
  cascButton1 = XmCreateCascadeButton(menuBar, "Cascade1", args, n);
  XtManageChild(cascButton1);

  n = 0;
  XtSetArg(args[n], XmNsubMenuId, pulldown2); 			n++;
  cascButton2 = XmCreateCascadeButton(menuBar, "Cascade2", args, n);
  XtManageChild(cascButton2);

  buttonsa[0] = XmCreatePushButton(pulldown1, "button11", NULL, 0);
  buttonsa[1] = XmCreatePushButton(pulldown1, "button12", NULL, 0);
  buttonsa[2] = XmCreatePushButton(pulldown1, "button13", NULL, 0);
  buttonsb[0] = XmCreatePushButton(pulldown2, "button21", NULL, 0);
  buttonsb[1] = XmCreateSeparator(pulldown2, "separator22", NULL, 0);
  buttonsb[2] = XmCreatePushButton(pulldown2, "button31", NULL, 0);
  XtManageChildren(buttonsa, 3);
  XtManageChildren(buttonsb, 3);

  XtManageChild(fsbox);
  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_BELOW_SELECTION); 	n++;
  XtSetValues(fsbox, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_TOP); 			n++;
  XtSetValues(fsbox, args, n);

  CommonPause();
  CommonPause();  /* Exit */

  /*  process events  */
  XtAppMainLoop(app_context);

#else

  printf("This test is for 1.2 only\n");

#endif
}
