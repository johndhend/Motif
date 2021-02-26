/* $TOG: MessageDiaM1.c /main/5 1999/07/01 13:22:03 vipin $ */
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

static 	void  OkCB();
static  void  FocusCB();
static  void  PrintMessage();
Widget  shell;
Widget  mbox; 

void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[10];           /*  arg list            */
    register int    n;                  /*  arg count           */
    XmString	    tcs, tcs2;
    XFontStruct     *newfont;
    XmFontList      newfontlist;
    Widget db, cancelbutton;



    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 400);                     n++;
    XtSetArg (args[n], XmNheight, 400);                    n++;
    XtSetValues(Shell1, args, n);
    

    tcs = XmStringCreateLtoR("DialogStyle Unmanaged Test", 
			     XmSTRING_DEFAULT_CHARSET);
    tcs2 = XmStringCreateLtoR("UnManage", XmSTRING_DEFAULT_CHARSET);

    newfont = XLoadQueryFont(display, "variable");
    newfontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_MODELESS);	  n++; 
    XtSetArg (args[n], XmNmessageString, tcs);			  n++;
    XtSetArg (args[n], XmNokLabelString, tcs2);			  n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNminimizeButtons, False);                n++;
    XtSetArg (args[n], XmNlabelFontList, newfontlist);		  n++;
    XtSetArg (args[n], XmNbuttonFontList, newfontlist);		  n++;
    mbox = XmCreateMessageDialog (Shell1, "mbox", args, n);
    XmStringFree(tcs);

    XtAddCallback(mbox, XmNokCallback, OkCB, NULL);

    XtAddCallback(mbox, XmNfocusCallback, FocusCB, NULL);

    cancelbutton = XmMessageBoxGetChild (mbox, XmDIALOG_CANCEL_BUTTON);
    XtAddCallback (cancelbutton, XmNactivateCallback, PrintMessage, NULL);

    /* begin test for PIR 4147 */
    XtRealizeWidget (Shell1);
    XtManageChild (mbox);
    /* end test for PIR 4147 */

    CommonPause();

    XtRemoveCallback(mbox, XmNfocusCallback, FocusCB, NULL);

    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_SYSTEM_MODAL);	  n++; 
    XtSetValues (mbox, args, n);

    XtManageChild(mbox);

    CommonPause();

    tcs = XmStringCreateLtoR(" DialogType Unmanaged Test ", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);  n++; 
    XtSetArg (args[n], XmNmessageString, tcs);			n++;
    XtSetArg (args[n], XmNdialogType, XmDIALOG_QUESTION);	n++;
    XtSetValues (mbox, args, n);

    XtManageChild(mbox);

    XmStringFree(tcs);

    CommonPause();

    /* begin test for PIR 3306 */
    /* 1) make sure we *have* a default button */

    db = XmMessageBoxGetChild (mbox, XmDIALOG_DEFAULT_BUTTON);

    if (db != NULL) 
      printf ("The default button is %s\n", XtName (db));
    else {
      printf ("There is no default button! I am setting one.\n");
      db = XmMessageBoxGetChild (mbox, XmDIALOG_OK_BUTTON);
      n = 0;
      XtSetArg (args[n], XmNdefaultButton, db);
      n++;
      XtSetValues (mbox, args, n);
      printf ("The default button is %s\n", XtName (db));
    }

    /* 2) set the "unmanage" button to another button and switch callbacks. */

    n = 0;
    XtSetArg (args[n], XmNlabelString, tcs2); n++;
    XtSetValues (XmMessageBoxGetChild (mbox, XmDIALOG_CANCEL_BUTTON), args, n);

    n = 0;
    XtSetArg (args[n], XmNlabelString, 
	      XmStringCreateSimple ("does nothing")); n++;
    XtSetValues (XmMessageBoxGetChild (mbox, XmDIALOG_OK_BUTTON), args, n);

    XtRemoveCallback (mbox, XmNokCallback, OkCB, NULL);
    XtAddCallback (mbox, XmNcancelCallback, OkCB, NULL);

    XmStringFree(tcs2);

    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_MODELESS);	  n++; 
    XtSetValues (mbox, args, n);
    XtManageChild (mbox);

    CommonPause();    /* pop up, user unmanages */

    XtManageChild (mbox);
    /* check the default button again */

    db = XmMessageBoxGetChild (mbox, XmDIALOG_DEFAULT_BUTTON);

    if (db != NULL) 
      printf ("The default button is %s\n", XtName (db));
    else {
      printf ("There is no default button! I am setting one.\n");
      db = XmMessageBoxGetChild (mbox, XmDIALOG_OK_BUTTON);
      n = 0;
      XtSetArg (args[n], XmNdefaultButton, db);
      n++;
      XtSetValues (mbox, args, n);
      printf ("The default button is %s\n", XtName (db));
    }

    CommonPause();    /* where is the focus? */

    /*  process events  */
    CommonPause (); /* exit */
    XtAppMainLoop(app_context);
}

static void  OkCB(w, client_data, call_data)
    Widget   w;
    XtPointer  client_data;
    XtPointer  call_data;
{

    XtUnmanageChild (w);
}


static void FocusCB (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{

	XtCallCallbacks (XmMessageBoxGetChild (w, XmDIALOG_CANCEL_BUTTON),
			 XmNactivateCallback, NULL);

}

static void PrintMessage (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{
	printf ("This message is expected on Cancel or FocusIn\n");
	fflush (stdout);
}
