/* $TOG: DNDScroll.c /main/5 1999/11/11 15:42:21 jff $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */
#include <testlib.h>


Widget  ScrolledWin1;
Widget  vertSB, horizSB;
Widget	Clip1;

#define SLIDER_SIZE 10
#define	SCROLL_DELAY 50


void CreateScrollBars(parent)
Widget parent;
{
    Arg args[10];
    int n;

    n = 0;
    XtSetArg (args[n], XmNorientation, XmVERTICAL);  n++;
    XtSetArg (args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg (args[n], XmNmaximum, 60);  n++;
    XtSetArg (args[n], XmNminimum, 0);  n++;
    XtSetArg (args[n], XmNtraversalOn, True);  n++;
    XtSetArg (args[n], XmNhighlightOnEnter, True);  n++;
    XtSetArg (args[n], XmNhighlightThickness, 2);  n++;
    XtSetArg (args[n], XmNsliderSize, SLIDER_SIZE);  n++;
    XtSetArg (args[n], XmNinitialDelay, SCROLL_DELAY);  n++;
    XtSetArg (args[n], XmNrepeatDelay, SCROLL_DELAY);  n++;
    vertSB = XmCreateScrollBar (parent, "vertSB", args, n);
    XtManageChild (vertSB);

    n = 0;
    XtSetArg (args[n], XmNorientation, XmHORIZONTAL);  n++;
    XtSetArg (args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg (args[n], XmNmaximum, 59);  n++;
    XtSetArg (args[n], XmNminimum, 0);  n++;
    XtSetArg (args[n], XmNtraversalOn, True);  n++;
    XtSetArg (args[n], XmNhighlightOnEnter, True);  n++;
    XtSetArg (args[n], XmNhighlightThickness, 2);  n++;
    XtSetArg (args[n], XmNsliderSize, SLIDER_SIZE);  n++;
    XtSetArg (args[n], XmNinitialDelay, SCROLL_DELAY);  n++;
    XtSetArg (args[n], XmNrepeatDelay, SCROLL_DELAY);  n++;
    horizSB = XmCreateScrollBar (parent, "horizSB", args, n);

    XtManageChild (horizSB);
}




void  main(argc, argv)
    int     argc;
    char  **argv;
{
    int  n,i;
    Arg args[MAX_ARGS];
    XmString tcs;
    Pixel colorVal;
    Widget  ScrolledWin1;
    Widget RowCol1;
    Widget PushB[15];
    char name[16];


    CommonTestInit(argc, argv);
    

    XtRealizeWidget(Shell1);



    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);  n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmBOTTOM_RIGHT);  n++;
    XtSetArg(args[n], XmNautoDragModel, XmAUTO_DRAG_ENABLED); n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    ScrolledWin1 = XmCreateScrolledWindow(Shell1, "ScrolledWin1", args, n);
    XtManageChild(ScrolledWin1);



    n=0;
    XtSetArg (args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg (args[n], XmNnumColumns, 2); n++;
    RowCol1 = XmCreateRowColumn (ScrolledWin1, "RowCol1", args, n);
    XtManageChild (RowCol1);

    for (i=0; i < 15; i++)
      {
	n=0;
	sprintf (name, "PushB%d", i);
	PushB[i] = XmCreatePushButton (RowCol1, name, args, n);
      }
    XtManageChildren (PushB, 15);

    CreateScrollBars (ScrolledWin1);
    XmScrolledWindowSetAreas (ScrolledWin1, horizSB, vertSB, RowCol1);



    CommonPause();
    CommonPause();
    CommonPause();

    n=0;
    XtSetArg (args[n], XmNautoDragModel, XmAUTO_DRAG_DISABLED); n++;
    XtSetValues (ScrolledWin1, args, n);

    CommonPause();
    CommonPause();

    XtAppMainLoop(app_context);
}

