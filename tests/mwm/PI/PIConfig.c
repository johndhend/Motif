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
static char rcsid[] = "$XConsortium: PIConfig.c /main/6 1995/07/13 20:19:23 drk $"
#endif
#endif

#include	<testlib.h>
#include	<PITests.h>

#include 	<X11/Xlib.h>
#include 	<X11/StringDefs.h>
#include 	<X11/Xatom.h>

#include 	<Xm/MwmUtil.h>

#include	"btn1.bmp"
#include	"btn2.bmp"


Widget	TestTop1, TestTop2, Test1Btn1, Test2Btn1;
Pixmap	Test1Btn1Icon, Test2Btn1Icon;

Widget	NoResizeShell, NoMaximizeShell, NoMinMaxShell, 
		JustBorderShell, NoDecorShell;
Widget	NoResizeBtn, NoMaximizeBtn, NoMinMaxBtn, JustBorderBtn, 
		NoDecorBtn;
Window	TestTop1Wdw, TestTop2Wdw, Shell1Wdw;


main(argc, argv)
int argc;
char	*argv[];
{

	Arg     args[MAX_ARGS];
	int     n;
	int		x, y;

	n = 0;

    CommonTestInit(argc, argv);

    n = 0;
	XtSetArg(args[n], XmNwidth, 10); n++;
	XtSetArg(args[n], XmNheight, 10); n++;
	XtSetValues(Shell1, args, n);

	XtRealizeWidget(Shell1);

    CommonPause();
    
/*
 * Create top level shell widget as parent for test_button widgets
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;

	TestTop1 = XtAppCreateShell("TestTop1",				/* application name */
		 						"TestTop1",				/* application class */
		 						topLevelShellWidgetClass,	/* widget class */
		 						display,				/* display */
		 						args, n);				/* arguments */

/*
 * Create button1 widget
 */
	display = XtDisplay(TestTop1);
	screen = DefaultScreenOfDisplay(display);
	Test1Btn1Icon = XCreatePixmapFromBitmapData(display, rootWindow,
								btn1_bits, btn1_width,
								btn1_height,
								CommonGetColor("red"),
								CommonGetColor("yellow"),
								DefaultDepth(display, DefaultScreen(display)));
	Test2Btn1Icon = XCreatePixmapFromBitmapData(display, rootWindow,
								btn2_bits, btn2_width,
								btn2_height,
								CommonGetColor("yellow"),
								CommonGetColor("red"),
								DefaultDepth(display, DefaultScreen(display)));
	n = 0;
	XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg(args[n], XmNlabelPixmap, Test1Btn1Icon); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	Test1Btn1 = XmCreatePushButton(TestTop1, "Test1Btn1", args, n);
	XtManageChild(Test1Btn1);
	XtRealizeWidget(TestTop1);

/*
 * Create top level shell widget as parent for test_button2 widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;

	TestTop2 = XtAppCreateShell("TestTop2",			/* application name */
		 						"TestTop2",			/* application class */
		 						topLevelShellWidgetClass,	/* widget class */
		 						display,				/* display */
		 						args, n);				/* arguments */

/*
 * Create button2 widget
 */
	n = 0;
	XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg(args[n], XmNlabelPixmap, Test2Btn1Icon); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	Test2Btn1 = XmCreatePushButton(TestTop2, "Test2Btn1", args, n);
	XtManageChild(Test2Btn1);
	XtRealizeWidget(TestTop2);

	TestTop1Wdw = XtWindow(TestTop1);
	Shell1Wdw = XtWindow(Shell1);
	TestTop2Wdw = XtWindow(TestTop2);

	/*
	 * Move the test_top shell window and the Shell1 window
	 */
	XMoveWindow(display, TestTop1Wdw, 100, 100);
	XMoveWindow(display, TestTop2Wdw, 100, 300);

	CommonPause();

	x = 0;
	y = 0;
/*
 * Create top level shell widget as parent for NoResize widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;
	XtSetArg(args[n], XmNmwmDecorations, 
			 MWM_DECOR_BORDER | MWM_DECOR_TITLE |
			 MWM_DECOR_MENU | MWM_DECOR_MINIMIZE |
			 MWM_DECOR_MAXIMIZE); n++;
	NoResizeShell = XtAppCreateShell("NoResizeShell", /* application name */
		 						"NoResizeShell",      /* application class */
		 						topLevelShellWidgetClass,	/* widget class */
		 						display,				/* display */
		 						args, n);				/* arguments */

	n = 0;
    XtSetArg (args[n], XmNlabelString, 
			  XmStringCreateSimple ("No_ResizeH")); n++;
	NoResizeBtn = XmCreatePushButton(NoResizeShell, "NoResizeBtn", args, n);
	XtManageChild(NoResizeBtn);
	XtRealizeWidget(NoResizeShell);

	x += 50;
	y += 50;
/*
 * Create top level shell widget as parent for NoMaximizeShell widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;
	XtSetArg(args[n], XmNmwmDecorations, 
			 MWM_DECOR_BORDER | MWM_DECOR_TITLE |
			 MWM_DECOR_MENU | MWM_DECOR_MINIMIZE |
			 MWM_DECOR_RESIZEH); n++;
	NoMaximizeShell = XtAppCreateShell("NoMaximizeShell",
		 						"NoMaximizeShell",
		 						topLevelShellWidgetClass,
		 						display,
		 						args, n);

	n = 0;
    XtSetArg (args[n], XmNlabelString, 
			  XmStringCreateSimple ("No_Maximize")); n++;
	NoMaximizeBtn = XmCreatePushButton(NoMaximizeShell, "NoMaximizeBtn", 
										 args, n);
	XtManageChild(NoMaximizeBtn);
	XtRealizeWidget(NoMaximizeShell);

	x += 50;
	y += 50;
/*
 * Create top level shell widget as parent for NoMinMaxShell widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;
	XtSetArg(args[n], XmNmwmDecorations, 
			 MWM_DECOR_BORDER | MWM_DECOR_TITLE |
			 MWM_DECOR_MENU | MWM_DECOR_RESIZEH); n++;
	NoMinMaxShell = XtAppCreateShell("NoMinMaxShell",
		 						"NoMinMaxShell",
		 						topLevelShellWidgetClass,
		 						display,
		 						args, n);

	n = 0;
    XtSetArg (args[n], XmNlabelString, 
			  XmStringCreateSimple ("No_Minmax")); n++;
	NoMinMaxBtn = XmCreatePushButton(NoMinMaxShell, "NoMinMaxBtn", args, n);
	XtManageChild(NoMinMaxBtn);
	XtRealizeWidget(NoMinMaxShell);

	x += 50;
	y += 50;
/*
 * Create top level shell widget as parent for JustBorderShell widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;
	XtSetArg(args[n], XmNmwmDecorations, MWM_DECOR_BORDER); n++;
	JustBorderShell = XtAppCreateShell("JustBorderShell",
		 						"JustBorderShell",
		 						topLevelShellWidgetClass,
		 						display,
		 						args, n);

	n = 0;
    XtSetArg (args[n], XmNlabelString, 
			  XmStringCreateSimple ("Just_border")); n++;
	JustBorderBtn = XmCreatePushButton(JustBorderShell, "JustBorderBtn", 
										 args, n);
	XtManageChild(JustBorderBtn);
	XtRealizeWidget(JustBorderShell);

/*
 * Create top level shell widget as parent for NoDecorShell widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;
	XtSetArg(args[n], XmNmwmDecorations, 0); n++;
	XtSetArg(args[n], XmNx, 200); n++;
	XtSetArg(args[n], XmNy, 100); n++;
	NoDecorShell = XtAppCreateShell("NoDecorShell",
		 						"NoDecorShell",
		 						topLevelShellWidgetClass,
		 						display,
		 						args, n);

	n = 0;
    XtSetArg (args[n], XmNlabelString, 
			  XmStringCreateSimple ("No_decor")); n++;
	NoDecorBtn = XmCreatePushButton(NoDecorShell, "NoDecorBtn", 
										 args, n);
	XtManageChild(NoDecorBtn);
	XtRealizeWidget(NoDecorShell);

	CommonPause();

	XtMoveWidget(JustBorderShell, 250, 250);
	XtMoveWidget(NoMinMaxShell, 400, 400);
	XtMoveWidget(NoDecorShell, 100, 400);

	CommonPause();

/*
 *  Loop and process events.
 */

	XtAppMainLoop(app_context);

}

