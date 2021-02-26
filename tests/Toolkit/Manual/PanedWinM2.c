/* $XConsortium: PanedWinM2.c /main/4 1995/07/15 21:06:18 drk $ */
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
#include <signal.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/StringDefs.h>

#include <Xm/XmP.h>
#include <Xm/RowColumnP.h>

#include <testlib.h>

/*************Some Globals***********************/

int     argc_lookalike;
char ** argv_lookalike;

Widget mainWindow;
Widget rc1, rc2;
Widget button1, rc, button2, button3, button4, button5, button6;
Widget pb1, pb2;

Display *secondDisplay = NULL;
static int goAheadFlag = 0;

/* forward refs */
extern CreateOption();
void OpenSecondDisplay();
void OkayToDoTest();
void DontTest();
void SwitchInitialFocus();

void PrintName(w)
Widget w;
{
    fprintf(stdout, "Widget %s was activated\n",
	    XrmQuarkToString(w->core.xrm_name));
}

void PrintName_2(rc, client_data, data)
Widget		rc;
XtPointer			client_data;
XtPointer	data;
{
XmRowColumnCallbackStruct	*rc_data=(XmRowColumnCallbackStruct*) data ;
    fprintf(stdout, "Widget %s was activated\n", 
	    XrmQuarkToString(rc_data->widget->core.xrm_name));
}

static XtCallbackRec PrintName_CB[] =
{
    {PrintName_2, NULL},
    {NULL, NULL}
};

void SetInsensitive(w, cld, cad)
Widget w;
XtPointer cld ; 
XtPointer cad ; 
{
    Arg args[1];
    int	n;

    XtSetSensitive(w, False);
}

void main (argc, argv)
int argc;
char		*argv[];
{
    Widget	child[7];
    XEvent	event;
    Arg		args[15];
    int		n;
    Widget      displayPrompt, okayButton;
    char *      displayString;
    Widget      Shell2, PW1, PW2;
    Widget      tokenChild1, tokenChild2, tokenChild3, tokenChild4;
    Widget	tokenChild5, tokenChild6;
    
    /* 
     * Copy argv for use in opening second display because XtOpenDisplay
     * can destructively modify.
     */
    argc_lookalike = argc;
    argv_lookalike = (char **)XtMalloc(argc * sizeof(char *));
    if (argv_lookalike != NULL)
      {
	for (n = 0; n < argc; n++) argv_lookalike[n] = argv[n];
      }
    else
      {
	printf("Couldn't perform XtMalloc for argv_lookalike!\n");
	exit(1);
      }
    
    CommonTestInit(argc, argv);

    /* to test P2641, we need to open a second display, and to do that */
    /* we need to get the name of a second display from the user.      */

    n = 0;
    XtSetArg (args[n], XmNselectionLabelString, 
	      XmStringCreateLtoR ("If you wish to perform some multi-display tests,\nenter the name of a second display here (ex: workstation:0)", "charset")); n++;
    XtSetArg (args[n], XmNokLabelString, 
	      XmStringCreateLtoR ("Perform test", "charset")); n++;
    XtSetArg (args[n], XmNcancelLabelString,
	      XmStringCreateLtoR ("Don't perform test", "charset")); n++;
    displayPrompt = XmCreatePromptDialog (Shell1, "displayPrompt", args, n);

    XtUnmanageChild (XmSelectionBoxGetChild (displayPrompt, 
					     XmDIALOG_HELP_BUTTON));

    /* we need to set a callback on the okay button so the we only open
       the second display once we've got their info and okay to proceed. */

    XtAddCallback (displayPrompt, XmNokCallback, OkayToDoTest, NULL);
    XtAddCallback (displayPrompt, XmNcancelCallback, DontTest, NULL);
    XtAddCallback (displayPrompt, XmNmapCallback, SwitchInitialFocus, NULL);

    n = 0;
    XtSetArg (args[n], XmNwidth, 300); n++;
    XtSetArg (args[n], XmNheight, 300); n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget (Shell1);

    XtManageChild (displayPrompt);

    while (!goAheadFlag) {
        XtAppProcessEvent(app_context, XtIMAll);
        XSync(display, 0);
    }

    if (secondDisplay != NULL) {        /* perform the experiment for
					   PIR 2641 */

        Shell2 = XtAppCreateShell (argv_lookalike[0], "XMcommon",
				   applicationShellWidgetClass, 
				   secondDisplay, NULL, 0);

	
        PW1 = XmCreatePanedWindow(Shell1, "PW1", NULL, 0);
        PW2 = XmCreatePanedWindow(Shell2, "PW2", NULL, 0);

	n = 0;
	tokenChild1 = XmCreateLabelGadget (PW1, "tokenChild1", args, n);
	tokenChild2 = XmCreateLabelGadget (PW2, "tokenChild1", args, n);
	tokenChild3 = XmCreateLabel (PW1, "tokenChild2", args, n);
	tokenChild4 = XmCreateLabel (PW2, "tokenChild2", args, n);
	tokenChild5 = XmCreatePushButton (PW1, "tokenChild3", args, n);
	tokenChild6 = XmCreatePushButton (PW2, "tokenChild3", args, n);
	
	XtManageChild (tokenChild1);
	XtManageChild (tokenChild2);
	XtManageChild (tokenChild3);
	XtManageChild (tokenChild4);
	XtManageChild (tokenChild5);
	XtManageChild (tokenChild6);
	XtManageChild (PW1);
	XtManageChild (PW2);

	XtRealizeWidget (Shell2);
    }

    CommonPause();

    if (secondDisplay != NULL) XtDestroyWidget (Shell2);

    /*
     * XmRowColumn: rc1
     */

    n = 0;
    rc1 = XmCreatePanedWindow(Shell1, "rc1", (ArgList) args, n);


    /* 
     * Create the children of the first row-column manager
     */

    CreateButtons();
    
    /*
     * Create the children of the second row-column manager
     */

    XtManageChild(rc1); 


    CommonPause();


    XtAppMainLoop(app_context);
}

CreateButtons()
{
    button1 = XmCreateArrowButtonGadget(rc1, "button1", NULL, 0);
    XtAddCallback(button1, XmNactivateCallback, SetInsensitive, NULL);

    button5 = XmCreateSeparatorGadget(rc1, "button5", NULL, 0);

    XtManageChild(button1);
    XtManageChild(button5);
}

void DontTest (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{

  /* just return the flag so we get on with life */
  goAheadFlag = 1;

}


void OkayToDoTest (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{
  /* w is displayPrompt */
  /* so call OpenSecondDisplay */
  OpenSecondDisplay (w);

}

void OpenSecondDisplay (displayPrompt)
Widget displayPrompt;
{
char * displayString;

    /* get the string the user typed, and attempt to open that display */

    displayString = XmTextGetString(XmSelectionBoxGetChild(displayPrompt,
							   XmDIALOG_TEXT));
    /* open the display and check the return */

    secondDisplay = XtOpenDisplay (app_context, displayString, 
				   argv_lookalike[0], "XMcommon",
				   (XrmOptionDescRec * )NULL, 0,
				    &argc_lookalike, argv_lookalike);

    if (secondDisplay == NULL) {
      printf ("Couldn't open display %s\n", displayString);
      printf ("Proceeding without this test...\n");
      goAheadFlag = 1;
    }
    else {
      printf ("I have opened display %s\n", displayString);
      goAheadFlag = 1;
    }

    fflush (stdout);
}

void SwitchInitialFocus (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{
  /* on focus, put location cursor on text widget */

  Widget text;
  Boolean made_it;

  text = XmSelectionBoxGetChild (w, XmDIALOG_TEXT);
  made_it = XmProcessTraversal (text, XmTRAVERSE_CURRENT);
  if ( made_it != TRUE) {
    printf ("Call to XmProcessTraversal failed! File a PIR.\n");
/*    if ( (made_it = XmProcessTraversal (w, XmTRAVERSE_PREV)) != TRUE)
      printf ("POO - PREV didn't either.\n");
*/
  }
}
