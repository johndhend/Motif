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
static char rcsid[] = "$XConsortium: PIMwmInfo.c /main/8 1995/07/13 20:22:11 drk $"
#endif
#endif

#include	<testlib.h>
#include	<PITests.h>

#include	"PIMwmInfo.h"


int	ErrorHandle(dpy, err_event)
Display	*dpy;
XErrorEvent	*err_event;
{

	char    msg[80];

	XGetErrorText(dpy, err_event->error_code, msg, 80);
	printf("X Error code: %s\n", msg);

	/*
	 * Window was not found, so result is False.
	 */
	PIInfo[PIInfo_cnt].actual_return = False;

}


main(argc, argv)
int argc;
char	*argv[];
{

	Arg     args[10];
	int     n;
	int		i;

	n = 0;

    CommonTestInit(argc, argv);

    n = 0;
	XtSetArg(args[n], XmNwidth, 10); n++;
	XtSetArg(args[n], XmNheight, 10); n++;
	XtSetValues(Shell1, args, n);

	XtRealizeWidget(Shell1);

	XSetErrorHandler(ErrorHandle);

	top_wdw = XtWindow(Shell1);

    CommonPause();
	/*
 	 * Initialize the PIInfo data values
  	 */
	for (i = 0; i < NUM_TESTS; i++)
		PIInfo[i].actual_return = False;

/*
	/*
	 * Get the MwmInfo flags
	 */
	test_atom = XmInternAtom(display, "_MOTIF_WM_INFO", False);

	XGetWindowProperty(display, rootWindow, test_atom, 0, 100, False, 
					   AnyPropertyType, &new_type, &new_format, 
					   &new_nitems, &new_bytes_after,
					   (unsigned char **)(&mwm_get_info));

	/*
 	 * Check validity of info flags
 	 */
	PIInfo[PIInfo_cnt].actual_return =
		(
		( mwm_get_info->flags == MWM_INFO_STARTUP_STANDARD ) ||
		( mwm_get_info->flags == MWM_INFO_STARTUP_CUSTOM ));
	PIInfo_cnt++;

	/*
 	 * Check validity of wm_window while mwm running
 	 */
	/* Proper result here is TRUE */
	if (mwm_get_info->wm_window) {
		/*
		 * If XRaiseWindow() succeeds, then the property's 
		 * function IS working - the window SHOULD be valid
		 * while the window manager is running.
		 *
		 * So, we preload the result to be True, but if the
		 * XRaiseWindow() fails, the error handler will reset
		 * the result to False (an error condition).
		 */
		PIInfo[PIInfo_cnt].actual_return = True;
		XRaiseWindow(display, mwm_get_info->wm_window);
	}
	else {
		/*
		 * The window was NULL, so wm must not be running or
		 * is broken, and the window is not valid.  The result
		 * is False.
		 */
		PIInfo[PIInfo_cnt].actual_return = False;
	}
	XSync(display, False);
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

