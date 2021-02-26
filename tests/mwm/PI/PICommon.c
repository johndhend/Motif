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
static char rcsid[] = "$XConsortium: PICommon.c /main/6 1995/07/13 20:19:08 drk $"
#endif
#endif
#include <testlib.h>
#include <PITests.h>

/*
 * Global declarations 
 */
int	PIInfo_cnt = 0;
Widget	result;
String	summary_msg;


/*
 * Local declarations
 */
#define PASSED		1
#define FAILED		0

String	result_choice[2] =
{
    "FAILED",
	"Passed"
};

/*
 * Return value strings
 */

String	retstr[2] = 
{
    "False        ",
    "True         ",
};

static void	remove_result(w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;
{

	XtUnmapWidget(Shell1);

}


void	display_summary(num_tests, description_length, test_info)
int	num_tests;
int	description_length;
struct TestInfo	*test_info;
{

	Arg	args[4];
	int	n;
	XmString	message;
	Widget	ok_button, cancel_button;

	summary_msg = summary(num_tests, description_length, test_info);
	message = XmStringCreateLtoR(summary_msg, XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNx, 50); n++;
	XtSetArg(args[n], XmNy, 200); n++;
	XtSetValues(Shell1, args, n);
	XtUnmapWidget(Shell1);
	n = 0;
	XtSetArg(args[n], XmNx, 50); n++;
	XtSetArg(args[n], XmNy, 200); n++;
#ifdef MOTIF1_1
	XtSetArg(args[n], XmNmessageString, message); n++;
#endif
	result = XmCreateMessageBox(Shell1, "result", args, n);
	ok_button = XmMessageBoxGetChild (result, XmDIALOG_OK_BUTTON);
	cancel_button = XmMessageBoxGetChild (result, XmDIALOG_CANCEL_BUTTON);
	XtAddCallback (ok_button, XmNactivateCallback, remove_result, NULL);
	XtAddCallback (cancel_button, XmNactivateCallback, remove_result, NULL);

	XtManageChild(result);

#ifndef MOTIF1_1
	n = 0;
	XtSetArg(args[n], XmNmessageString, message); n++;
	XtSetValues(result, args, n);
#endif

	XtMapWidget(Shell1);

}


/*
 * summary():
 * summary() will return a String formed by formatting the test results
 * together with some other verbage to make a nice pretty results display.
 *
 * The String that summary() returns to the calling routine is allocated 
 * within this routine.  It is the calling routine's responsibility to
 * ***FREE THE STRING THAT IS RETURNED***
 * after it is used in the calling routine.
 */

String	summary(num_tests, description_length, test_info)
int		num_tests,
		description_length;
struct TestInfo	*test_info;
{

/*
 * All of the headers except header_top and trailer will be used as
 * strings to satisfy the %s's in testline (below) so that the format
 * of the headers will always match the format of the description lines.
 */
	String	testline			= "%s    %s  %s  %s\n",
			header_top			= "Test completed.\n\nResults:\n\n",
			header_test			= "Test",
			header_exp			= "Expected Rslt",
			header_act			= "Actual Result",
				/* exp and act sizes match the name field of retstr[] above */
    		header_rslt			= "Result",
			header_test_dash	= "----",
			header_exp_act_dash	= "-------------",
    		header_rslt_dash	= "------\n",
    		trailer				= "\n\nPress the exit button to end the test.",
				/* no specific size for padding, just a lot of spaces */
			padding				= "                                                                                                                          ";
	String	retval,
			result_this_test,
			temp_padded_str;

    int		i,
			padding_len,	/* amount of padding to get "Test" out to 
								description_length size */
			testline_len;	/* length of a full test description line */

/*
 * Allocate space for string we're creating
 */
	testline_len = strlen(testline) +
				   description_length +
				   strlen(header_exp) +
				   strlen(header_act) +
				   strlen(header_rslt);
	/* 
	 * Yes, I know I haven't accounted for the extra space occupied by
	 * the %s's and the \ in the \n in testline, but that's okay.  So,
	 * we allocate a few extra bytes - it will allow for things like
	 * NULLs, etc.
	 */
    result_this_test = XtCalloc(testline_len, 1);

	padding_len = description_length - strlen(header_test);
    retval = XtCalloc(((num_tests + 2) * testline_len) +
							strlen(header_top) +
							strlen(trailer),
							1);
	/*
	 * num_tests + 2 because there are two header lines on top of the
	 * description lines
	 */

	temp_padded_str = XtCalloc(description_length + 5, 1);
	/* add 5 more bytes just for good luck */

/*
 * Build and add header lines, use testline as the format to insure uniformity
 */
	strcpy(retval, header_top);
	/* have to pad the test header out to the size of description_length */
	strcpy(temp_padded_str, header_test);
	strncat(temp_padded_str, padding, padding_len);
	sprintf(result_this_test, testline,
			temp_padded_str,
			header_exp,
			header_act,
			header_rslt);
	strcat(retval, result_this_test);

	/* have to pad the test_dash header out to the size of description_length */
	strcpy(temp_padded_str, header_test_dash);
	strncat(temp_padded_str, padding, padding_len);
	sprintf(result_this_test, testline,
			temp_padded_str,
			header_exp_act_dash,
			header_exp_act_dash,
			header_rslt_dash);
	strcat(retval, result_this_test);

/*
 * Add description of, and results from, each individual test
 */
    for(i=0 ; i<num_tests ; i++)
    {
		sprintf(result_this_test, testline,
			(*test_info).description,
			retstr[(*test_info).expected_return],
			retstr[(*test_info).actual_return],
			((*test_info).actual_return == (*test_info).expected_return) ?
			result_choice[PASSED] : result_choice[FAILED]);
	
		strcat(retval, result_this_test);
		*test_info++;
    }

/*
 * Add closing message
 */
    strcat(retval, trailer);
    
    return(retval);
}


void	PIUnmapWindow(window)
Window	window;
{

	XUnmapEvent		Unmap_ev;
  
	XUnmapWindow(display, window);

	Unmap_ev.type = UnmapNotify;
	Unmap_ev.event = rootWindow;
	Unmap_ev.window = window;
	Unmap_ev.from_configure = False;
	XSendEvent(display, rootWindow, False,
			  (SubstructureNotifyMask|SubstructureRedirectMask), 
			  (XEvent *) &Unmap_ev);
	XSync(display, False);

}
