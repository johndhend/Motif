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
static char rcsid[] = "$XConsortium: MessageBox8.c /main/8 1995/07/13 19:01:56 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <X11/IntrinsicP.h>

#include <Xm/XmP.h>
#include <Xm/BulletinBP.h>
#include <Xm/MessageBP.h>

#include <testlib.h>

XmMessageBoxWidget  mbox;                        /*  MessageBox widget   */

static XmString str1 = NULL;
static XmString str2 = NULL;
static XmString str3 = NULL;

/* callbacks */

static void OkCB();
static XtCallbackRec ok_cb[] = {
    { OkCB, NULL},
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
    static   int minimize = False;

    if (minimize) {
        n=0;
        XtSetArg (args[n], XmNminimizeButtons, False); n++;
        XtSetArg (args[n], XmNokLabelString, str1); n++;
        XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_OK_BUTTON); n++;
        XtSetValues (w, args, n);
        minimize = False;
    }
    else {
        n=0;
        XtSetArg (args[n], XmNminimizeButtons, True); n++;
        XtSetArg (args[n], XmNokLabelString, str2); n++;
        XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_OK_BUTTON); n++;
        XtSetValues (w, args, n);
        minimize = True;
    }
}


/*-------------------------------------------------------------
**      HelpCB        - callback for help button
*/
static void HelpCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    static Boolean flag=False;
    XtGeometryResult geoResult;
    XtWidgetGeometry intended;
    XtWidgetGeometry result;

    if (flag) { 
        XtQueryGeometry (w, NULL, &result);
        printf("query with NULL\n");
        printf("      result is (mode, x, y, w, h) %d %d %d %d %d\n", 
                result.request_mode, result.x, result.y, 
                result.width, result.height);
        printf("      current is %d %d %d %d\n", w->core.x, w->core.y,
                w->core.width, w->core.height);
        flag=False;
    }
    else {
        intended.request_mode = (CWX | CWY | CWWidth | CWHeight);
        intended.x = 50;
        intended.y = 75;
        intended.width = 300;
        intended.height = 500;
        XtQueryGeometry (w, &intended, &result);
        printf("query with 50, 75, 300, 500\n");
        printf("      result is (mode, x, y, w, h) %d %d %d %d %d\n", 
                result.request_mode, result.x, result.y, 
                result.width, result.height);
        printf("               current is  %d %d %d %d\n", w->core.x, w->core.y,
                w->core.width, w->core.height);
        flag=True;
    }
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[10];
    register int    n;      
    Widget 	    Frame;

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);

    n = 0; 
    Frame = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame);

    /* create message dialog */

    str1 = XmStringCreate ("NoMinimize",  XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringCreate ("Minimize",  XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringCreate ("DoQuery",  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                     n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                 n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                   n++;
    XtSetArg (args[n], XmNhelpLabelString, str3);                 n++;
    XtSetArg (args[n], XmNokLabelString, str1);                   n++;
    XtSetArg (args[n], XmNminimizeButtons, False);                n++;

    mbox = (XmMessageBoxWidget) XmCreateMessageBox (Frame, "mbox", args, n);

    XtUnmanageChild(XmMessageBoxGetChild((Widget) mbox, 
		    XmDIALOG_CANCEL_BUTTON));
    XtManageChild ((Widget) mbox);

    XtRealizeWidget (Shell1);

    CommonPause();
    CommonPause();

    /*  process events  */
    XtAppMainLoop(app_context);
}
