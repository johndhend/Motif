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
static char rcsid[] = "$XConsortium: Form6.c /main/4 1995/07/13 18:11:42 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */



/****************************************
*   Automatic test program generation   *
*              Version 1.4              *
*       Mon May  8 15:08:52 1989        *
****************************************/


#include <testlib.h>
#include <Xm/XmP.h>

Widget Form1;

static Pixel  GetPixel();
static char           *GetReasonString();
static void  formCB();

void  main(argc, argv)
int     argc;
char  **argv;
{
    Boolean       trace = False;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    Widget	  pb;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetValues(Shell1, args, n);
    
    n = 0;
    XtSetArg (args[n], XmNbackground, CommonGetColor("magenta"));	n++;
    XtSetValues (Shell1, args, n);

    XtRealizeWidget(Shell1);

    n = 0;
    XtSetArg(args[n], XmNbackground, CommonGetColor("white"));  n++;
    XtSetArg(args[n], XmNmappedWhenManaged,  True);  n++;
    XtSetArg(args[n], XmNwidth,  450);  n++;
    XtSetArg(args[n], XmNheight, 350);  n++;
    Form1 = XmCreateForm(Shell1, "Form1", args, n);
    XtManageChild(Form1);

    XtAddCallback(Form1, XmNhelpCallback, formCB, NULL);

    XtAddCallback(Form1, XmNfocusCallback, formCB, NULL);

    XtAddCallback(Form1, XmNmapCallback, formCB, NULL);

    XtAddCallback(Form1, XmNunmapCallback, formCB, NULL);

#ifdef MOTIF1_1
    /* The destroyCallback is currently handled by Xt so no widget 
       information is placed into the call data.  For this reason, formCB
       may have a NULL pointer reference and cause an unexpected abort.
       This has been logged as an enhancement request for a later release. 
    */
    XtAddCallback(Form1, XmNdestroyCallback, formCB, NULL);
#endif

    CommonPause();

    n = 0;
    pb = XmCreatePushButton (Form1, "pb", args, n);
    XtManageChild (pb);

    CommonPause();

    XtDestroyWidget(Form1);

    CommonPause();

    XtAppMainLoop(app_context);
}

static void  formCB(w, client_data, call_data)
Widget   w;
caddr_t  client_data;
caddr_t  call_data;
{
  printf("formCB callback: %s %s\n", XrmQuarkToString(w->core.xrm_name),
	 GetReasonString(((XmAnyCallbackStruct *)call_data)->reason));
}

static char  *GetReasonString(reason_code)
int  reason_code;
{
    char  *reason;

    switch (reason_code) {
         case XmCR_NONE:                    reason = "none";
                                            break;
         case XmCR_HELP:                    reason = "help";
                                            break;
         case XmCR_VALUE_CHANGED:           reason = "value_changed";
                                            break;
         case XmCR_INCREMENT:               reason = "increment";
                                            break;
         case XmCR_DECREMENT:               reason = "decrement";
                                            break;
         case XmCR_PAGE_INCREMENT:          reason = "page_increment";
                                            break;
         case XmCR_PAGE_DECREMENT:          reason = "page_decrement";
                                            break;
         case XmCR_TO_TOP:                  reason = "to_top";
                                            break;
         case XmCR_TO_BOTTOM:               reason = "to_bottom";
                                            break;
         case XmCR_DRAG:                    reason = "drag";
                                            break;
         case XmCR_ACTIVATE:                reason = "activate";
                                            break;
         case XmCR_ARM:                     reason = "arm";
                                            break;
         case XmCR_DISARM:                  reason = "disarm";
                                            break;
         case XmCR_MAP:                     reason = "map";
                                            break;
         case XmCR_UNMAP:                   reason = "unmap";
                                            break;
         case XmCR_FOCUS:                   reason = "focus";
                                            break;
         case XmCR_LOSING_FOCUS:            reason = "losing_focus";
                                            break;
         case XmCR_MODIFYING_TEXT_VALUE:    reason = "modifying_text_value";
                                            break;
         case XmCR_MOVING_INSERT_CURSOR:    reason = "moving_insert_cursor";
                                            break;
         case XmCR_EXECUTE:                 reason = "execute";
                                            break;
         case XmCR_SINGLE_SELECT:           reason = "single_select";
                                            break;
         case XmCR_MULTIPLE_SELECT:         reason = "multiple_select";
                                            break;
         case XmCR_EXTENDED_SELECT:         reason = "extended_select";
                                            break;
         case XmCR_BROWSE_SELECT:           reason = "browse_select";
                                            break;
         case XmCR_DEFAULT_ACTION:          reason = "default_action";
                                            break;
         case XmCR_CLIPBOARD_DATA_REQUEST:  reason = "clipboard_data_request";
                                            break;
         case XmCR_CLIPBOARD_DATA_DELETE:   reason = "clipboard_data_delete";
                                            break;
         case XmCR_CASCADING:               reason = "cascading";
                                            break;
         case XmCR_OK:                      reason = "ok";
                                            break;
         case XmCR_CANCEL:                  reason = "cancel";
                                            break;
         case XmCR_APPLY:                   reason = "apply";
                                            break;
         case XmCR_NO_MATCH:                reason = "no_match";
                                            break;
         case XmCR_COMMAND_ENTERED:         reason = "command_entered";
                                            break;
         case XmCR_COMMAND_CHANGED:         reason = "command_changed";
                                            break;
         case XmCR_EXPOSE:                  reason = "expose";
                                            break;
         case XmCR_RESIZE:                  reason = "resize";
                                            break;
         case XmCR_INPUT:                   reason = "input";
                                            break;
         default:                           reason = "invalid reason";
                                            break;
    }

    return(reason);
}












