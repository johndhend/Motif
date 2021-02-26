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
static char rcsid[] = "$XConsortium: InfoDia1.c /main/9 1995/07/13 18:57:45 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <signal.h>

#include <X11/IntrinsicP.h>

#include <Xm/XmP.h>
#include <Xm/BulletinBP.h>
#include <Xm/MessageBP.h>

#include <testlib.h>

/* global variables */

Widget          shell;              		 /*  Dialog Shell        */
XmMessageBoxWidget  mbox;                        /*  MessageBox widget   */
Widget dialog;

static XmString str1 = NULL;
static XmString str2 = NULL;
static XmString str3 = NULL;
static XmString str4 = NULL;


/* callbacks */

static void FocusCB();

static void OkCB();
static XtCallbackRec ok_cb[] = {
    { OkCB, NULL},
    { NULL,                  NULL}
};

static void CancelCB();
static XtCallbackRec cancel_cb[] = {
    { CancelCB, NULL},
    { NULL,                  NULL}
};

static void HelpCB();
static XtCallbackRec help_cb[] = {
    { HelpCB, NULL},
    { NULL,                NULL}
};


/*-------------------------------------------------------------
**      OkCB        - callback for ok button
*/
static void OkCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    static int minimize = False;

    if (minimize) {
        n=0;
        XtSetArg (args[n], XmNminimizeButtons, False); n++;
        XtSetArg (args[n], XmNokLabelString, str1); n++;
        XtSetValues (w, args, n);
        minimize = False;
    }
    else {
        n=0;
        XtSetArg (args[n], XmNminimizeButtons, True); n++;
        XtSetArg (args[n], XmNokLabelString, str2); n++;
        XtSetValues (w, args, n);
        minimize = True;
    }
}

/*-------------------------------------------------------------
**      CancelCB        - callback for cancel button
*/
static void CancelCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;

    n=0;
    XtSetArg (args[n], XmNwidth, 500); n++;
    XtSetValues (w, args, n);
}

/*-------------------------------------------------------------
**      HelpCB        - callback for help button
*/
static void HelpCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;

    n=0;
    XtSetArg (args[n], XmNheight, 300); n++;
    XtSetValues (w, args, n);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[10];           /*  arg list            */
    register int    n;                  /*  arg count           */

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 10);                            n++;
    XtSetArg (args[n], XmNheight, 10);                           n++;
    XtSetValues(Shell1, args, n);

    /* create a set of compound strings */
    str1 = XmStringCreate ("Minimize",  XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringCreate ("To Default",  XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringCreate ("W=500",  XmSTRING_DEFAULT_CHARSET);
    str4 = XmStringCreate ("H=300",  XmSTRING_DEFAULT_CHARSET);

    /* create message dialog */
    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                     n++;
    XtSetArg (args[n], XmNcancelCallback, cancel_cb);             n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                 n++;
    XtSetArg (args[n], XmNokLabelString, str1);                   n++;
    XtSetArg (args[n], XmNcancelLabelString, str3);               n++;
    XtSetArg (args[n], XmNhelpLabelString, str4);                 n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNminimizeButtons, False);                n++;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_CANCEL_BUTTON); n++;

    mbox = (XmMessageBoxWidget)XmCreateInformationDialog (Shell1, "mbox", 
                                                          args, n);

/* Test for Pir 4109 and 4114 */

    XtAddCallback((Widget) mbox, XmNfocusCallback, FocusCB, NULL);

    XtRealizeWidget ((Widget) Shell1);
    XtManageChild ((Widget) mbox);

    CommonPause();
    CommonPause();

    /* begin PIR 2320 */

    XtDestroyWidget ((Widget) mbox);

    n = 0;
    XtSetArg (args[n], XmNmappedWhenManaged, False);              n++;
    XtSetArg (args[n], XmNtitle, "Shouldn\'t be mapped");         n++;
    XtSetArg (args[n], XmNgeometry, "300x300+0+50");              n++;
    dialog = XmCreateDialogShell (Shell1, "mbox", args, n);

    XtManageChild (dialog);

    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNmappedWhenManaged, True);             n++;
    XtSetArg (args[n], XmNtitle, "Should be mapped");           n++;
    XtSetArg (args[n], XmNwidth, 200);				n++;
    XtSetArg (args[n], XmNheight, 200);				n++;
    XtSetValues (dialog, args, n);
    XtMapWidget (dialog);

    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNwidth, 300);				n++;
    XtSetArg (args[n], XmNheight, 400);				n++;
    XtSetArg (args[n], XmNx, 0);				n++;
    XtSetArg (args[n], XmNy, 200);				n++;
    XtSetValues (dialog, args, n);

    CommonPause();

    XtDestroyWidget (dialog);

    n = 0;
    XtSetArg (args[n], XmNokLabelString, str1);                   n++;
    XtSetArg (args[n], XmNcancelLabelString, str3);               n++;
    XtSetArg (args[n], XmNhelpLabelString, str4);                 n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNminimizeButtons, False);                n++;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_CANCEL_BUTTON); n++;
    XtSetArg (args[n], XmNmappedWhenManaged, False);             n++;

    mbox = (XmMessageBoxWidget)XmCreateInformationDialog (Shell1, "mbox", 
                                                          args, n);

    n = 0;
    XtSetArg (args[n], XmNmappedWhenManaged, False);              n++;
    XtSetValues (XtParent(mbox), args, n);

    XtManageChild ((Widget) mbox);

    CommonPause();

    XtDestroyWidget ((Widget) mbox);

    n = 0;
    XtSetArg (args[n], XmNokLabelString, str1);                   n++;
    XtSetArg (args[n], XmNcancelLabelString, str3);               n++;
    XtSetArg (args[n], XmNhelpLabelString, str4);                 n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNminimizeButtons, False);                n++;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_CANCEL_BUTTON); n++;
    XtSetArg (args[n], XmNmappedWhenManaged, False);             n++;

    mbox = (XmMessageBoxWidget)XmCreateInformationDialog (Shell1, "mbox", 
                                                          args, n);

    XtManageChild ((Widget) mbox);

    CommonPause();

    /* end PIR 2320 */


    /*  process events  */
    XtAppMainLoop(app_context);
}


static void FocusCB(w, client_data, call_data)
    Widget   w;
    XtPointer  client_data;
    XtPointer  call_data;

{
    static int i = 0;

    printf("(%d) FocusCallback called for %s\n", i++, XtName(w));

}
