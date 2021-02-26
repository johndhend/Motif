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
static char rcsid[] = "$XConsortium: WarningDia1.c /main/9 1995/07/13 19:03:33 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include <Xm/XmP.h>

Widget  	mbox;

static int destroy = False;
static  XmString str1 = NULL;
static  XmString str2 = NULL;
static  XmString str3 = NULL;
static  XmString str4 = NULL;
static  XmString str5 = NULL;
static  XmString str6 = NULL;


/* callbacks */
static void OkCB();
static XtCallbackRec ok_cb[] = {
    { OkCB, NULL},
    { NULL, NULL}
};
static void CancelCB();
static XtCallbackRec cancel_cb[] = {
    { CancelCB, NULL},
    { NULL, NULL}
};
static void HelpCB();
static XtCallbackRec help_cb[] = {
    { HelpCB, NULL},
    { NULL, NULL}
};


/*#### OkCB ####*/
static void OkCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    if (destroy) {
        n=0;
        XtSetArg (args[n], XmNokLabelString, str1); n++;
        XtSetValues (w, args, n);
        destroy = False;
    }
    else {
        n=0;
    	child = XmMessageBoxGetChild (w, XmDIALOG_CANCEL_BUTTON);
	if (child)
		XtManageChild (child);
    	child = XmMessageBoxGetChild (w, XmDIALOG_HELP_BUTTON);
	if (child)
		XtManageChild (child);
	child = XmMessageBoxGetChild (w, XmDIALOG_SYMBOL_LABEL);
	if (child)
		XtManageChild (child);
	child = XmMessageBoxGetChild (w, XmDIALOG_MESSAGE_LABEL);
	if (child)
		XtManageChild (child);
	XtSetArg (args[n], XmNcancelLabelString, str2);n++;
        XtSetArg (args[n], XmNokLabelString, str5); n++;
        XtSetValues (w, args, n);
        destroy = True;
    }
}


/*#### CancelCB ####*/
static void CancelCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    child = XmMessageBoxGetChild (w, XmDIALOG_HELP_BUTTON);
    if (child && XtIsManaged(child)) {
        if (destroy) XtDestroyWidget (child);
        else XtUnmanageChild (child);
        n=0;
        XtSetArg (args[n], XmNcancelLabelString, str6); n++;
        XtSetValues (w, args, n);
    }
    else {
        child = XmMessageBoxGetChild (w, XmDIALOG_CANCEL_BUTTON);
        if (child) 
            if (destroy) XtDestroyWidget (child);
            else XtUnmanageChild (child);
    }
}


/*#### HelpCB ####*/
static void HelpCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    child = XmMessageBoxGetChild (w, XmDIALOG_SYMBOL_LABEL);
    if (child) 
        if (destroy) XtDestroyWidget (child);
        else XtUnmanageChild (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_MESSAGE_LABEL);
    if (child) 
        if (destroy) XtDestroyWidget (child);
        else XtUnmanageChild (child);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[MAX_ARGS]; 
    register int    n;             
    Widget	    Frame;

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 10);                     n++;
    XtSetArg (args[n], XmNheight, 10);                    n++;
    XtSetValues(Shell1, args, n);

    n = 0;
    Frame = XmCreateFrame(Shell1, "Frame", args, n);
    XtManageChild(Frame);
    
    /* create compound string */
    str1 = XmStringCreate ("Unmanage", XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringCreate ("HelpBtn", XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringCreate ("Symbol&Message", XmSTRING_DEFAULT_CHARSET);
    str4 = XmStringLtoRCreate ("Toggle Unmanage/Destroy and select a button",
                                XmSTRING_DEFAULT_CHARSET);
    str5 = XmStringCreate ("Destroy", XmSTRING_DEFAULT_CHARSET);
    str6 = XmStringCreate ("Me", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                         n++;
    XtSetArg (args[n], XmNcancelCallback, cancel_cb);         n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                     n++;
    XtSetArg (args[n], XmNmessageString, str4);                       n++;
    XtSetArg (args[n], XmNokLabelString, str1);                       n++;
    XtSetArg (args[n], XmNcancelLabelString, str2);           n++;
    XtSetArg (args[n], XmNhelpLabelString, str3);                     n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                       n++;
    XtSetArg (args[n], XmNdialogType, XmDIALOG_INFORMATION);  n++;
    /* dialogType should be ignored... in favor of creation routine type */

    mbox = XmCreateWarningDialog (Frame, "mbox", args, n);

    XtRealizeWidget (Shell1);
    XtManageChild (mbox);

    CommonPause();
    CommonPause();

    /*  process events  */
    XtAppMainLoop(app_context);
}
