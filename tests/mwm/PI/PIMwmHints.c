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
static char rcsid[] = "$XConsortium: PIMwmHints.c /main/7 1995/07/13 20:21:39 drk $"
#endif
#endif

#include	<testlib.h>
#include	<PITests.h>

#include	"PIMwmHints.h" 
#include	"btn1.bmp"
#include	"btn2.bmp"


/*
 * Button callback
 */
static void test1_btn1_proc(w, client_data, call_data)
Widget		w;
XtPointer	client_data, call_data;
{
	PropMwmHints	mwm_set_hints, *mwm_get_hints;
	XWMHints	wm_set_hints;
	static int	done = 0;

	if (!done)
	{
		done = 1;

		/*
		 * Change the decorations again and the functions
		 */
		test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
		mwm_set_hints.flags = ( MWM_HINTS_INPUT_MODE );
		mwm_set_hints.inputMode = MWM_INPUT_APPLICATION_MODAL;
		XChangeProperty(display, test_wdw,
			test_atom, 
			test_atom, 32, PropModeReplace,
			(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));
	
		/*
		 * Unmap and remap the window to change state
		 */
		PIUnmapWindow(test_wdw);
		wm_set_hints.flags = (StateHint);
		wm_set_hints.initial_state = NormalState;
		XSetWMHints(display, test_wdw, &wm_set_hints);
		XMapWindow(display, test_wdw);
		XMoveWindow(display, test_wdw, 100, 100);
	
		printf("Keyboard input focus set back to APPLICATION MODAL\n");
	}
}


main(argc, argv)
int argc;
char	*argv[];
{

	Arg     args[10];
	int     n;
	int		i;

	XmString    message;
	XmString    cancel_label, ok_label, help_label;
	char    message_begin[120];
	XtAppContext   app_context;


	n = 0;

    CommonTestInit(argc, argv);

     n = 0;
     XtSetArg(args[n], XmNwidth, 10); n++;
     XtSetArg(args[n], XmNheight, 10); n++;
     XtSetValues(Shell1, args, n);

     XtRealizeWidget(Shell1);

    CommonPause();
	/*
 	 * Initialize the PIInfo data values
  	 */
	for (i = 0; i < NUM_TESTS; i++)
		PIInfo[i].actual_return = False;

/*
    
/*
 * Create top level shell widget as parent for test_button widgets
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;

	test_top = XtAppCreateShell("test_top",				/* application name */
		 						"Test_top",				/* application class */
		 						topLevelShellWidgetClass,	/* widget class */
		 						display,				/* display */
		 						args, n);				/* arguments */

/*
 * Create button1 widget
 */
	display = XtDisplay(test_top);
	screen = DefaultScreenOfDisplay(display);
	test1_btn1_icon = XCreatePixmapFromBitmapData(display, rootWindow,
								btn1_bits, btn1_width,
								btn1_height,
								CommonGetColor("red"),
								CommonGetColor("yellow"),
								DefaultDepth(display, DefaultScreen(display)));
	test2_btn1_icon = XCreatePixmapFromBitmapData(display, rootWindow,
								btn2_bits, btn2_width,
								btn2_height,
								CommonGetColor("yellow"),
								CommonGetColor("red"),
								DefaultDepth(display, DefaultScreen(display)));
	n = 0;
	XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg(args[n], XmNlabelPixmap, test1_btn1_icon); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	test1_btn1 = XmCreatePushButton(test_top, "test1_btn1", args, n);
	XtManageChild(test1_btn1);
	XtAddCallback(test1_btn1, XmNarmCallback, test1_btn1_proc, NULL);
	XtRealizeWidget(test_top);

	test_wdw = XtWindow(test_top);
	top_wdw = XtWindow(Shell1);

	/*
	 * Move the test_top shell window and the Shell1 window
	 */
	XMoveWindow(display, test_wdw, 100, 100);
	XMoveWindow(display, top_wdw, 300, 100);

	/*
	 * Change the decorations
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);

	mwm_set_hints.flags = (
							MWM_HINTS_DECORATIONS |
							MWM_HINTS_INPUT_MODE
							);
	mwm_set_hints.decorations = MWM_DECOR_TITLE;
	mwm_set_hints.inputMode = MWM_INPUT_SYSTEM_MODAL;
	XChangeProperty(display, test_wdw,
		test_atom, 
		test_atom, 32, PropModeReplace,
		(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));


    /*
     * Unmap and remap the window to change state
     */
	PIUnmapWindow(test_wdw);
    wm_set_hints.flags = (StateHint);
    wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw, &wm_set_hints);
	XMapWindow(display, test_wdw);
    XMoveWindow(display, test_wdw, 100, 100);

	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
	XGetWindowProperty(display, test_wdw, test_atom,
					   0, 100, False, AnyPropertyType,
					   &new_type, &new_format, &new_nitems, &new_bytes_after,
					   (unsigned char **)(&mwm_get_hints));

/*
 * Change the decorations to title
 */
	PIInfo[PIInfo_cnt].actual_return =
		(mwm_get_hints->decorations == mwm_set_hints.decorations);
	PIInfo_cnt++;

/*
 * Change the input_mode to system_modal
 */
	PIInfo[PIInfo_cnt].actual_return =
		(mwm_get_hints->inputMode == mwm_set_hints.inputMode);
	PIInfo_cnt++;

    CommonPause();

	/*
	 * Change the decorations again and the functions
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);

	mwm_set_hints.flags = (
							MWM_HINTS_DECORATIONS |
							MWM_HINTS_FUNCTIONS
							);
	mwm_set_hints.decorations = (
								MWM_DECOR_TITLE |
								MWM_DECOR_MENU |
								MWM_DECOR_MINIMIZE |
								MWM_DECOR_MAXIMIZE
								);
	mwm_set_hints.functions = (
								MWM_FUNC_RESIZE |
								MWM_FUNC_MINIMIZE
								);
	XChangeProperty(display, test_wdw,
		test_atom, 
		test_atom, 32, PropModeReplace,
		(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));


	/*
         * Unmap and remap the window to change state
         */
	PIUnmapWindow(test_wdw);
    wm_set_hints.flags = (StateHint);
    wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw, &wm_set_hints);
	XMapWindow(display, test_wdw);
    XMoveWindow(display, test_wdw, 100, 100);

	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
	XGetWindowProperty(display, test_wdw,
		test_atom,
		0, 100, False, AnyPropertyType,
		&new_type, &new_format, &new_nitems, &new_bytes_after,
		(unsigned char **)(&mwm_get_hints));

/*
 * Change decorations to title/resize/menu/min/max
 */
	PIInfo[PIInfo_cnt].actual_return =
		(mwm_get_hints->decorations == mwm_set_hints.decorations);
	PIInfo_cnt++;

/*
 * Change the functions to resize/min
 */
	PIInfo[PIInfo_cnt].actual_return =
		(mwm_get_hints->functions == mwm_set_hints.functions);
	PIInfo_cnt++;

	CommonPause();

	/*
	 * Change the decorations again and the functions
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);

	mwm_set_hints.flags = (
							MWM_HINTS_DECORATIONS |
							MWM_HINTS_FUNCTIONS |
							MWM_HINTS_INPUT_MODE
							);
	mwm_set_hints.decorations = ( MWM_DECOR_ALL );
	mwm_set_hints.functions = ( MWM_FUNC_ALL );
	mwm_set_hints.inputMode = ( MWM_INPUT_MODELESS );
	XChangeProperty(display, test_wdw,
		test_atom, 
		test_atom, 32, PropModeReplace,
		(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));


	/*
         * Unmap and remap the window to change state
         */
	PIUnmapWindow(test_wdw);
    wm_set_hints.flags = (StateHint);
    wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw, &wm_set_hints);
	XMapWindow(display, test_wdw);
    XMoveWindow(display, test_wdw, 100, 100);

	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
	XGetWindowProperty(display, test_wdw,
		test_atom,
		0, 100, False, AnyPropertyType,
		&new_type, &new_format, &new_nitems, &new_bytes_after,
		(unsigned char **)(&mwm_get_hints));

/*
 * Change decorations/functions to ALL, input_mode to MODELESS
 */
	PIInfo[PIInfo_cnt].actual_return =
		(
		mwm_get_hints->decorations == mwm_set_hints.decorations &&
		mwm_get_hints->functions == mwm_set_hints.functions &&
		mwm_get_hints->inputMode == mwm_set_hints.inputMode
		);
	PIInfo_cnt++;

	CommonPause();

	/*
	 * Change the decorations again and the functions for button1
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);

	mwm_set_hints.flags = (
							MWM_HINTS_DECORATIONS |
							MWM_HINTS_FUNCTIONS
							);
	mwm_set_hints.decorations = ( MWM_DECOR_ALL | MWM_DECOR_RESIZEH );
	mwm_set_hints.functions = ( MWM_FUNC_ALL | MWM_FUNC_CLOSE );
	XChangeProperty(display, test_wdw,
		test_atom, 
		test_atom, 32, PropModeReplace,
		(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));


	/*
         * Unmap and remap the window to change state
         */
	PIUnmapWindow(test_wdw);
        wm_set_hints.flags = (StateHint);
        wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw, &wm_set_hints);
	XMapWindow(display, test_wdw);
        XMoveWindow(display, test_wdw, 100, 100);

	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
	XGetWindowProperty(display, test_wdw,
		test_atom,
		0, 100, False, AnyPropertyType,
		&new_type, &new_format, &new_nitems, &new_bytes_after,
		(unsigned char **)(&mwm_get_hints));

/*
 * Change FUNC=~Close, DECOR=~Resize using ALL | CLOSE/RESIZEH
 */
	PIInfo[PIInfo_cnt].actual_return =
		(
		mwm_get_hints->decorations == mwm_set_hints.decorations &&
		mwm_get_hints->functions == mwm_set_hints.functions
		);
	PIInfo_cnt++;

/*
 * Create top level shell widget as parent for test_button2 widget
 */
	n = 0;
	XtSetArg(args[n], XtNallowShellResize, TRUE); n++;

	test_top2 = XtAppCreateShell("test_top2",			/* application name */
		 						"Test_top2",			/* application class */
		 						topLevelShellWidgetClass,	/* widget class */
		 						display,				/* display */
		 						args, n);				/* arguments */

/*
 * Create button2 widget
 */
	n = 0;
	XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg(args[n], XmNlabelPixmap, test2_btn1_icon); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	test2_btn1 = XmCreatePushButton(test_top2, "test2_btn1", args, n);
	XtManageChild(test2_btn1);
	XtRealizeWidget(test_top2);

	test_wdw2 = XtWindow(test_top2);

	/*
	 * Change the decorations again and the functions for button2
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);

	mwm_set_hints.flags = (
							MWM_HINTS_DECORATIONS |
							MWM_HINTS_FUNCTIONS
							);
	mwm_set_hints.decorations = ( MWM_DECOR_BORDER |
								MWM_DECOR_TITLE |
								MWM_DECOR_MENU |
								MWM_DECOR_MINIMIZE |
								MWM_DECOR_MAXIMIZE
								);
	mwm_set_hints.functions = ( MWM_FUNC_RESIZE | 
								MWM_FUNC_MOVE |
								MWM_FUNC_MINIMIZE |
								MWM_FUNC_MAXIMIZE
								);
	XChangeProperty(display, test_wdw2,
		test_atom, 
		test_atom, 32, PropModeReplace,
		(unsigned char *)&mwm_set_hints, sizeof(PropMwmHints)/sizeof(int));

	/*
     * Unmap and remap the window to change state
     */
	PIUnmapWindow(test_wdw2);
    wm_set_hints.flags = (StateHint);
    wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw2, &wm_set_hints);
	XMapWindow(display, test_wdw2);
    XMoveWindow(display, test_wdw2, 150, 150);

	test_atom = XmInternAtom(display, "_MOTIF_WM_HINTS", False);
	XGetWindowProperty(display, test_wdw2,
		test_atom,
		0, 100, False, AnyPropertyType,
		&new_type, &new_format, &new_nitems, &new_bytes_after,
		(unsigned char **)(&mwm_get_hints));

/*
 * Change FUNC=~Close, DECOR=~Resize using |'d list
 */
	PIInfo[PIInfo_cnt].actual_return =
		(
		mwm_get_hints->decorations == mwm_set_hints.decorations &&
		mwm_get_hints->functions == mwm_set_hints.functions
		);
	PIInfo_cnt++;

	CommonPause();

/*
 * Put up a message box with the results of the test.
 */
	display_summary(NUM_TESTS, TEST_DESCRIP_LENGTH, PIInfo);

	CommonPause();

/*
 *  Loop and process events.
 */

	XtAppMainLoop(app_context);

}

