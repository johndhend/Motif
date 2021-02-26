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
static char rcsid[] = "$XConsortium: Navigation8.c /main/6 1995/07/13 19:45:23 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
	/* test for PIR 1321 */

#include <X11/Xlib.h>

#include <testlib.h>


/*************Some Globals***********************/

Widget bb;
Widget Frame1, Frame2, Frame3, Frame4, Frame5, Frame6;
Widget Draw1, Draw2; 
Widget rc1, rc2, rc3, rc4, rc5, rc6;
Widget btn1, btn2, btn3;
Widget toggle1;
Widget misc1, misc2;
Widget toggle21, toggle22;
Widget btn31, btn32, btn33, btn34, btn35, btn36;
Widget toggle31, toggle32, toggle33;
Widget btn41, btn42;
Widget toggle41, toggle42;
Widget help_button;

/* forward refs */
void MoveFocus ();


void main (argc, argv)
int argc;
char **argv;

{
    Arg args[15];
    int n;
    Widget child[20];
    XmString tcs;


    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
 
    bb = XmCreateBulletinBoard(Shell1, "bb", (ArgList) args, 0);
    XtManageChild(bb);

/* We want to test navigation across different widgets on the Bulletin
	Board as well as Navigation within the Frames within the BB, thus
	we are creating a set of three frames within the Bulleting Board,
	and they will each have a set of buttons within them.  */


	 n = 0;
	 XtSetArg(args[n], XmNx, 10); n++;
	 XtSetArg(args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
	 Frame1 = XmCreateFrame (bb, "Frame1", args, n);
	 XtManageChild (Frame1);

/* Let's make this Frame contain a RowColumn with three buttons.
	All the buttons will be added to the Tab Group. */

	 n = 0;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg(args[n], XmNnumColumns, 1); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc1 = XmCreateRowColumn(Frame1, "rc1", (ArgList) args, n);
    XtManageChild(rc1);

/* Create the children of the row column manager. The children are
	buttons. */

	 n = 0;
   XtSetArg(args[n], XmNtraversalOn, True); n++;
   XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
   XtSetArg(args[n], XmNhighlightThickness, 2); n++;
   XtSetArg(args[n], XmNactivateCallback, (XtArgVal) NULL); n++;
   btn1 = XmCreatePushButton(rc1, "btn1",(ArgList)args, n);
   XtManageChild(btn1);
   n--;
   XtSetArg(args[n],XmNactivateCallback,(XtArgVal) NULL); n++;
   btn2 = XmCreatePushButton(rc1, "btn2", (ArgList) args, n);
   XtManageChild(btn2);
   n--;
   XtSetArg(args[n], XmNactivateCallback, (XtArgVal) NULL); n++;
   btn3 = XmCreatePushButton(rc1, "btn3", (ArgList) args, n);
   XtManageChild(btn3);
/* Lets do a toggle now... */
    n = 0;
    tcs = XmStringLtoRCreate("Toggle1", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle1 = XmCreateToggleButtonGadget(rc1,"toggle1",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle1);

/* Create the other Frame/Children combos. */
/* First the Frame */
	 n = 0;
	 XtSetArg(args[n], XmNx, 100); n++;
	 XtSetArg(args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
	 Frame2 = XmCreateFrame (bb, "Frame2", args, n);
	 XtManageChild (Frame2);
/* Let's make this Frame contain a RowColumn with two buttons.
	All the buttons will be added to the Tab Group. */

	 n = 0;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg(args[n], XmNnumColumns, 1); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc2 = XmCreateRowColumn(Frame2, "rc2", (ArgList) args, n);
    XtManageChild(rc2);


/* create the  children now. */
   n = 0;
   XtSetArg(args[n], XmNtraversalOn, True); n++;
   XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
   XtSetArg(args[n], XmNhighlightThickness, 2); n++;
   misc1 = XmCreatePushButton(rc2, "misc1", (ArgList) args, n);
   XtManageChild(misc1);
   misc2 = XmCreatePushButton(rc2, "misc2", (ArgList) args, n);
   XtManageChild(misc2);
/* Lets do a couple of  toggles now... */
    n = 0;
    tcs = XmStringLtoRCreate("Toggle21", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle21 = XmCreateToggleButtonGadget(rc2,"toggle21",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle21);
/* and another... */
    n = 0;
    tcs = XmStringLtoRCreate("Toggle22", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle22 = XmCreateToggleButtonGadget(rc2,"toggle22",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle22);


/*Two down, many to go... */

	 n = 0;
	 XtSetArg(args[n], XmNx, 200); n++;
	 XtSetArg(args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
	 Frame3 = XmCreateFrame (bb, "Frame3", args, n);
	 XtManageChild (Frame3);
/* Let's make this Frame contain a RowColumn with six buttons.
	All the buttons will be added to the Tab Group. */

	 n = 0;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg(args[n], XmNnumColumns, 2); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc3 = XmCreateRowColumn(Frame3, "rc3", (ArgList) args, n);
    XtManageChild(rc3);


/* create the  children now. */
   n = 0;
   XtSetArg(args[n], XmNtraversalOn, True); n++;
   XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
   XtSetArg(args[n], XmNhighlightThickness, 2); n++;
   btn31 = XmCreatePushButton(rc3, "btn31", (ArgList) args, n);
   XtManageChild(btn31);
   btn32 = XmCreatePushButton(rc3, "btn32", (ArgList) args, n);
   XtManageChild(btn32);
   btn33 = XmCreatePushButton(rc3, "btn33", (ArgList) args, n);
   XtManageChild(btn33);
   btn34 = XmCreatePushButton(rc3, "btn34", (ArgList) args, n);
   XtManageChild(btn34);
   btn35 = XmCreatePushButton(rc3, "btn35", (ArgList) args, n);
   XtManageChild(btn35);
   btn36 = XmCreatePushButton(rc3, "btn36", (ArgList) args, n);
   XtManageChild(btn36);
/* Toggle another... */
    n = 0;
    tcs = XmStringLtoRCreate("btn7", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle31 = XmCreateToggleButtonGadget(rc3,"toggle31",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle31);
    n = 0;
    tcs = XmStringLtoRCreate("btn8", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle32 = XmCreateToggleButtonGadget(rc3,"toggle32",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle32);
    n = 0;
    tcs = XmStringLtoRCreate("btn9", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNindicatorOn, True);  n++;
    toggle33 = XmCreateToggleButtonGadget(rc3,"toggle33",(ArgList) args, n);
    if(tcs) XmStringFree(tcs);
    XtManageChild(toggle33);


	 n = 0;
	 XtSetArg(args[n], XmNx, 375); n++;
	 XtSetArg(args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
	 Frame4 = XmCreateFrame (bb, "Frame4", args, n);
	 XtManageChild (Frame4);
/* Let's make this Frame contain a RowColumn with two buttons and two toggles.
	All the buttons will be added to the Tab Group. */

	 n = 0;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg(args[n], XmNnumColumns, 1); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc4 = XmCreateRowColumn(Frame4, "rc4", (ArgList) args, n);
    XtManageChild(rc4);

/* create the  children now. */
   n = 0;
   XtSetArg(args[n], XmNtraversalOn, True); n++;
   XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
   XtSetArg(args[n], XmNhighlightThickness, 2); n++;
   btn41 = XmCreatePushButton(rc4, "btn41", (ArgList) args, n);
   XtManageChild(btn41);
   btn42 = XmCreatePushButton(rc4, "btn42", (ArgList) args, n);
   XtManageChild(btn42);
   n = 0;
   tcs = XmStringLtoRCreate("Toggle41", XmSTRING_DEFAULT_CHARSET);
   XtSetArg(args[n], XmNlabelString, tcs);  n++;
   XtSetArg(args[n], XmNindicatorOn, True);  n++;
   toggle41 = XmCreateToggleButtonGadget(rc4,"toggle41",(ArgList) args, n);
   if(tcs) XmStringFree(tcs);
   XtManageChild(toggle41);


	n = 0;
	XtSetArg (args[n], XmNx, 485); n++;
	XtSetArg (args[n], XmNy, 10); n++;
	XtSetArg (args[n], XmNnavigationType, XmNONE); n++;
   XtSetArg(args[n], XmNwidth, 135);  n++;
   XtSetArg(args[n], XmNheight, 18);  n++;
	XtSetArg(args[n], XmNarrowDirection, XmARROW_RIGHT);  n++;
	Draw1 = XmCreateArrowButton (bb,"Draw1", args, n);
	XtManageChild (Draw1);
	

/* Now lets make two more RCs with nothing on them! */

	 n = 0;
	 XtSetArg (args[n], XmNx, 485); n++;
	 XtSetArg (args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNborderWidth, 5); n++;
	 XtSetArg(args[n], XmNheight, 5); n++;
	 XtSetArg(args[n], XmNwidth, 5); n++;
	 Frame5 = XmCreateFrame (bb, "Frame5", args, n);
	 XtManageChild (Frame5);

	 n = 0;
	 XtSetArg(args[n], XmNborderWidth, 5); n++;
	 XtSetArg (args[n], XmNx, 485); n++;
	 XtSetArg (args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNwidth, 20); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc5 = XmCreateRowColumn(bb, "rc5", (ArgList) args, n);
    XtManageChild(rc5);

	 n = 0;
	 XtSetArg (args[n], XmNx, 550); n++;
	 XtSetArg (args[n], XmNy, 10); n++;
	 XtSetArg(args[n], XmNborderWidth, 5); n++;
	 XtSetArg(args[n], XmNheight, 5); n++;
	 XtSetArg(args[n], XmNwidth, 5); n++;
	 Frame6 = XmCreateFrame (bb, "Frame6", args, n);
	 XtManageChild (Frame6);
	 n = 0;
	 XtSetArg(args[n], XmNborderWidth, 5); n++;
	 XtSetArg(args[n], XmNwidth, 5); n++;
	 XtSetArg(args[n], XmNnavigationType, XmNONE); n++;
    rc6 = XmCreateRowColumn(Frame6, "rc6", (ArgList) args, n);
    XtManageChild(rc6);


    XtRealizeWidget (Shell1);
    CommonPause ();

    n = 0;
    XtSetArg (args[n], XmNnavigationType, XmTAB_GROUP); n++;
    XtSetValues (rc3, args, n);

/* fire up Help button on Pause dialog to help us test */

    help_button = XmMessageBoxGetChild (InstructionBox, XmDIALOG_HELP_BUTTON);
    XtSetSensitive (help_button, True);
    n = 0;
    XtSetArg (args[n], XmNlabelString,
              XmStringCreateSimple ("Traverse")); n++;
    XtSetValues (help_button, args, n);
    XtAddCallback (help_button, XmNactivateCallback,
                   MoveFocus, (XtPointer) XmTRAVERSE_DOWN);

    CommonPause();


    CommonPause (); /* end */
    XtAppMainLoop(app_context);
}


void MoveFocus (w, client_data, call_data)
Widget w;
XtPointer client_data;
XtPointer call_data;

{
  Widget current_focus;

  current_focus = XmGetFocusWidget (bb);
  XmProcessTraversal (current_focus, (int) (long)client_data);
  fflush (stdout);
}
