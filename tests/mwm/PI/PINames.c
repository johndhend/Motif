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
static char rcsid[] = "$XConsortium: PINames.c /main/8 1995/07/13 20:22:48 drk $"
#endif
#endif
#include	<X11/Xatom.h>

#include	<testlib.h>
#include	<PITests.h>
#include	"PINames.h"


main(argc, argv)
int argc;
char	*argv[];
{

	Arg     args[10];
	int     n;
	int		i;

	XmString    message;


    CommonTestInit(argc, argv);
    
    n = 0;
	XtSetArg(args[n], XmNwidth, 200); n++;
	XtSetArg(args[n], XmNheight, 50); n++;
	XtSetValues(Shell1, args, n);

/*
 *  Realize the Shell1 widget.
 */

	XtRealizeWidget(Shell1);

    CommonPause();
	/*
	 * Initialize the callbacks actual returns
	 */
	for (i = 0; i < NUM_TESTS; i++)
		PIInfo[i].actual_return = False;
    
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
 * Create a Label box
 */
	message = XmStringCreateLtoR(look_at_name, XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNlabelType, XmSTRING); n++;
	XtSetArg(args[n], XmNlabelString, message); n++;
	label_box = XmCreateLabel(test_top, "label_box", args, n);
	XtManageChild(label_box);
	XtRealizeWidget(test_top);

	test_wdw = XtWindow(test_top);
	top_wdw = XtWindow(Shell1);

	/*
	 * Move the test_top shell window and the Shell1 window
	 */
	XMoveWindow(display, test_wdw, 100, 100);

	/*
 	 * Change the window name of a window (WM_NAME)
  	 */
	test_atom = XmInternAtom(display, "WM_NAME", False);
	XChangeProperty(display, test_wdw, test_atom, XA_STRING, 8, 
					PropModeReplace, (unsigned char *)new_winname, 
					strlen(new_winname));
	XGetWindowProperty(display, test_wdw, test_atom, 0, 20, False, 
					   AnyPropertyType, &new_type, &new_format, 
					   &new_nitems, &new_bytes_after, &new_data);
	PIInfo[PIInfo_cnt].actual_return = 
					!strcmp(new_winname, (char *) new_data);
	PIInfo_cnt++;

	/*
 	 * Check for a ***** default name
  	 */
	normal_wdw = XCreateSimpleWindow(display, rootWindow, 100, 300,
								   	 200, 50, 10, 1, 
									 CommonGetColor("black"));
    XMapWindow(display, normal_wdw);
	XSync(display, False);
	if (!XFetchName(display, normal_wdw, &new_name)) {
		if (!XGetClassHint(display, normal_wdw, &class_hints)) {

			/*
			 * If the name couldn't be fetched, and res_name
			 * had no value, it means that
			 * there was no name, so it's supposed to use '*****'
			 */
			PIInfo[PIInfo_cnt].actual_return = True;
			PIInfo_cnt++;

		}
		else {

			/*
			 * It must have found a class hint, using res_name
			 */
			printf("normal_wdw classhints, res_name=%s=\n", 
				   class_hints.res_name);
			PIInfo[PIInfo_cnt].actual_return = !strcmp(old_winname2, 
													   class_hints.res_name);	
			PIInfo_cnt++;
			XFree(class_hints.res_name);
			XFree(class_hints.res_class);

		}
	}
	else {
		/*
		 * It must have found a fetched name, using name returned
		 */
		printf("new_name=%s=\n", new_name);
		PIInfo[PIInfo_cnt].actual_return = !strcmp(old_winname2, new_name);	
		PIInfo_cnt++;
		XFree(new_name);
	}

    CommonPause();

	/*
 	* Change the icon name of a window (WM_ICON_NAME)
 	*/
	test_atom = XmInternAtom(display, "WM_ICON_NAME", False);
	XChangeProperty(display, test_wdw, test_atom, XA_STRING, 8, 
					PropModeReplace, (unsigned char *)new_iconname, 
					strlen(new_iconname));

	XGetWindowProperty(display, test_wdw, test_atom, 0, 20, False, 
					   AnyPropertyType, &new_type, &new_format, 
					   &new_nitems, &new_bytes_after, &new_data);
	PIInfo[PIInfo_cnt].actual_return = 
						!strcmp(new_iconname, (char *) new_data);	
	PIInfo_cnt++;

	ClientMsg_ev.type = ClientMessage;
	ClientMsg_ev.window = test_wdw;
	ClientMsg_ev.message_type = XmInternAtom(display, "WM_CHANGE_STATE", 
											 False);
	ClientMsg_ev.format = 32;
	ClientMsg_ev.data.l[0] = IconicState;

	XSendEvent(display, rootWindow, False,
			  (SubstructureNotifyMask|SubstructureRedirectMask), 
			  (XEvent *) &ClientMsg_ev);

	/*
 	 * Change the label_box label
 	 */
	message = XmStringCreateLtoR(look_at_icon, XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNlabelString, message); n++;
	XtSetValues(label_box, args, n);
	XmStringFree(message);
				       
	/*
 	 * Change the window name of ***** (WM_NAME)
 	 */
	test_atom = XmInternAtom(display, "WM_NAME", False);
	XChangeProperty(display, normal_wdw, test_atom, XA_STRING, 8, 
					PropModeReplace, (unsigned char *)new_winname2, 
					strlen(new_winname2));

	XGetWindowProperty(display, normal_wdw, test_atom, 0, 20, False, 
					   AnyPropertyType, &new_type, &new_format, 
					   &new_nitems, &new_bytes_after, &new_data);
	PIInfo[PIInfo_cnt].actual_return = 
						!strcmp(new_winname2, (char *) new_data);	
	PIInfo_cnt++;
	XSync(display, False);

	CommonPause();

	/*
 	 * Change the class name structure of a window (WM_CLASS)
 	 */
	/* 
	 * put window from IconicState to WithdrawnState
	 */
	PIUnmapWindow(test_wdw);

	/*
	 * delete the WM_NAME first so the class name kicks in
	 */
	test_atom = XmInternAtom(display, "WM_NAME", False);
	XDeleteProperty(display, test_wdw, test_atom);

	/*
	 * change class info
	 */
	l_name = strlen(new_class_name);
	l_class = strlen(new_class_class);
	strcpy(class_buf, new_class_name);
	strcpy(&class_buf[l_name+1], new_class_class);
	test_atom = XmInternAtom(display, "WM_CLASS", False);
	XChangeProperty(display, test_wdw, test_atom, XA_STRING, 8, 
					PropModeReplace, (unsigned char *)class_buf,
					l_name+l_class+2);
		
	/*
	 * revive from the WithdrawnState to NormalState
	 */
	wm_set_hints.flags = StateHint;
	wm_set_hints.initial_state = NormalState;
	XSetWMHints(display, test_wdw, &wm_set_hints);
	XMapWindow(display, test_wdw);
	XMoveWindow(display, test_wdw, 100, 100);

	XGetClassHint(display, test_wdw, &class_hints);
	PIInfo[PIInfo_cnt].actual_return = 
		(!strcmp(new_class_name, class_hints.res_name) &&
		!strcmp(new_class_class, class_hints.res_class));	
	PIInfo_cnt++;

/*************???????????????????????????*****************/
	/*
 	 * Change the label_box label
 	 */
	message = XmStringCreateLtoR(look_at_classname, XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNlabelString, message); n++;
	XtSetValues(label_box, args, n);
	XmStringFree(message);

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

