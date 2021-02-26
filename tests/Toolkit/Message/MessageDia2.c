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
static char rcsid[] = "$XConsortium: MessageDia2.c /main/8 1995/07/13 19:02:36 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*  include files  */

#include <signal.h>

#include <X11/IntrinsicP.h>
#include <Xm/XmP.h>
#include <Xm/BulletinBP.h>
#include <Xm/MessageBP.h>

#include <testlib.h>
#include "MessageDia2.h"

XmMessageBoxWidget  mbox;                        /*  MessageBox widget   */
Widget              shell;            		 /*  Dialog Shell        */

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


/*#### OkCB ####*/
static void OkCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Widget   child=NULL;


    /* destroy all children except help */

    child = XmMessageBoxGetChild (w, XmDIALOG_MESSAGE_LABEL);
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_SYMBOL_LABEL);
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_SEPARATOR);
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_APPLY_BUTTON); /* doesn't exist */
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_OK_BUTTON);
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_CANCEL_BUTTON);
    if (child) XtDestroyWidget (child);

    child = XmMessageBoxGetChild (w, XmDIALOG_DEFAULT_BUTTON);
    child = XmMessageBoxGetChild (w, XmDIALOG_HELP_BUTTON);
}


/*#### CancelCB ####*/
static void CancelCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Arg        args[10];
    int        n;
    static int flag = 0;

    if (flag) {
        n=0;
        XtSetArg (args[0], XmNhelpLabelString, str1);                     n++;
        XtSetArg (args[n], XmNdialogType, 88);         /* invalid type */ n++;
        XtSetArg (args[n], XmNmessageAlignment, 88);   /* invalid type */ n++;
        XtSetArg (args[n], XmNdefaultButtonType, 88);  /* invalid type */ n++;
        XtSetValues (w, args, n);
        flag = 0;
    }
    else {
        XtSetArg (args[0], XmNhelpLabelString, str2);
        XtSetValues (w, args, 1);
        flag = 1;
    }
}


/*#### HelpCB ####*/
static void HelpCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer   client_data;                 /*  data from application   */
XtPointer   call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    XmString     data;
    Pixmap       pixData;

    XtSetArg (args[0], XmNmessageString, str3);
    XtSetValues (w, args, 1);

    data = NULL;
    XtSetArg (args[0], XmNmessageString, &data);
    XtGetValues (w, args, 1);
    XmStringFree(data);

    XtSetArg (args[0], XmNsymbolPixmap, &pixData);
    XtGetValues (w, args, 1);

    data = NULL;
    XtSetArg (args[0], XmNokLabelString, &data);
    XtGetValues (w, args, 1);
    XmStringFree(data);

    data = NULL;
    XtSetArg (args[0], XmNcancelLabelString, &data);
    XtGetValues (w, args, 1);
    XmStringFree(data);

    data = NULL;
    XtSetArg (args[0], XmNhelpLabelString, &data);
    XtGetValues (w, args, 1);
    XmStringFree(data);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[20];           /*  arg list            */
    register int    n;                  /*  arg count           */

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 10);                     n++;
    XtSetArg (args[n], XmNheight, 10);                    n++;
    XtSetValues(Shell1, args, n);
    
    /* create compound string */
    str1 = XmStringLtoRCreate ("h", XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringLtoRCreate ("longHelpLabelString", XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringLtoRCreate ("shortMessage", XmSTRING_DEFAULT_CHARSET);
    str4 = XmStringLtoRCreate ("MBox is GrowOnly, Ok=Destroy, Help=GetValues",
                                XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                         n++;
    XtSetArg (args[n], XmNcancelCallback, cancel_cb);                 n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                     n++;
    XtSetArg (args[n], XmNmessageString, str4);                       n++;
    XtSetArg (args[n], XmNmessageAlignment, 88);   /* invalid type */ n++;
    XtSetArg (args[n], XmNdialogType, 88);         /* invalid type */ n++;
    XtSetArg (args[n], XmNdefaultButtonType, XmDIALOG_HELP_BUTTON);   n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);               n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                       n++;

    mbox = (XmMessageBoxWidget) XmCreateMessageDialog (Shell1, "mbox", args, n);

    XtRealizeWidget (Shell1);
    XtManageChild ((Widget) mbox);

    CommonPause();

    /*  process events  */
    XtAppMainLoop(app_context);
}
