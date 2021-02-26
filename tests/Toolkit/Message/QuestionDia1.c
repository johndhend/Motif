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
static char rcsid[] = "$XConsortium: QuestionDia1.c /main/8 1995/07/13 19:02:55 drk $"
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


XmMessageBoxWidget  mbox;                        /*  MessageBox widget   */
Widget          shell;              		 /*  Dialog Shell        */

static XmString str1 = NULL;
static XmString str2 = NULL;
static XmString str3 = NULL;


/* callbacks */

static void OkCB();
static XtCallbackRec ok_cb[] = {
    {  OkCB, NULL},
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
    Arg      args[10];
    register int n;

    n=0;
    XtSetArg (args[n], XmNdialogType, XmDIALOG_WARNING); 	n++;
    XtSetValues (w, args, n);
}


/*-------------------------------------------------------------
**      CancelCB        - callback for cancel button
*/
static void CancelCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;

    n = 0;
    XtSetArg (args[n], XmNdialogType, XmDIALOG_WORKING); 	n++;
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

    n = 0;
    XtSetArg (args[n], XmNdialogType, XmDIALOG_INFORMATION); 	n++;
    XtSetValues (w, args, n);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[10];           /*  arg list            */
    register int    n;                  /*  arg count           */
    /* for test for PIR 4070 */
    Widget textfield, bb, button[3];
    int i;
    char buf[32];

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 10);                     n++;
    XtSetArg (args[n], XmNheight, 10);                    n++;
    XtSetValues(Shell1, args, n);
    
    /* create message dialog */

    str1 = XmStringCreate ("Warning",  XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringCreate ("Working",  XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringCreate ("Information", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                     n++;
    XtSetArg (args[n], XmNcancelCallback, cancel_cb);             n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                 n++;
    XtSetArg (args[n], XmNokLabelString, str1);                   n++;
    XtSetArg (args[n], XmNcancelLabelString, str2);               n++;
    XtSetArg (args[n], XmNhelpLabelString, str3);                 n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_OK_BUTTON); n++;

    mbox = (XmMessageBoxWidget)
            XmCreateQuestionDialog (Shell1, "mbox", args, n);


    XtManageChild ((Widget) mbox);
    XtRealizeWidget (Shell1);

    CommonPause();

    /* begin test for PIR 4070 */

    n = 0;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_HELP_BUTTON); 	n++;
    XtSetArg (args[n], XmNbackground, CommonGetColor ("thistle")); 	n++;
    XtSetValues ((Widget) mbox, args, n);

    CommonPause();

    /* because the default button always tracks the focus in 1.2,
       the above is not the right test. You need to have another type
       of widget with the focus before the set values. */
    /* Widget textfield, bb, button[3]; */

    XtDestroyWidget ((Widget) mbox);
    n = 0;
    bb = XmCreateBulletinBoardDialog (Shell1, "bb", args, n);
    
    for (i = 0; i <= 2; i++) {
	sprintf (buf, "button%d", i);
	n = 0;
        XtSetArg (args[n], XmNx, 200); n++;
	XtSetArg (args[n], XmNy, i*100); n++;
	XtSetArg (args[n], XmNdefaultButtonShadowThickness, 2); n++;
	button[i] = XmCreatePushButton (bb, buf, args, n);
    }

    n = 0;
    XtSetArg (args[n], XmNdefaultButton, button[1]); n++;
    XtSetValues (bb, args, n);

    n = 0;
    XtSetArg (args[n], XmNx, 0); n++;
    XtSetArg (args[n], XmNy, 0); n++;
    textfield = XmCreateTextField (bb, "textfield", args, n);
    XtManageChild (textfield);

    XtManageChildren (button, 3);
    XtManageChild (bb);

    CommonPause ();

    /*  process events  */
    XtAppMainLoop(app_context);
}
