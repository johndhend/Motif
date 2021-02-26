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
static char rcsid[] = "$XConsortium: Frame4.c /main/7 1995/07/13 18:32:31 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#define REALIZE_AFTER 1

Widget    RowColumn1;
Widget    Frame1;
Widget    ArrowButton1;
Widget    Frame2;
Widget    Label1;
Widget    Frame3;
Widget    PushButton1;
Widget    Frame4;
Widget    ToggleButton1;
Widget    Frame5;
Widget    LabelGadget1;


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  			n++;
    XtSetArg(args[n], XmNheight, 300);  			n++;
    XtSetValues(Shell1, args, n);
    
#ifndef REALIZE_AFTER
    XtRealizeWidget(Shell1);
#endif 

    n = 0;
    RowColumn1 = XmCreateRowColumn(Shell1, "RowColumn1", args, n);
    XtManageChild(RowColumn1);

    n = 0;
    Frame1 = XmCreateFrame(RowColumn1, "Frame1", args, n);
    XtManageChild(Frame1);

    n = 0;
    ArrowButton1 = XmCreateArrowButton(Frame1, "ArrowButton1", args, n);
    XtManageChild(ArrowButton1);

    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 50);  			n++;
    XtSetArg(args[n], XmNmarginHeight, 50);  			n++;
    Frame2 = XmCreateFrame(RowColumn1, "Frame2", args, n);
    XtManageChild(Frame2);

    tcs = XmStringLtoRCreate("LABEL1", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlabelString, tcs);  			n++;
    Label1 = XmCreateLabel(Frame2, "Label1", args, n);
    XtManageChild(Label1);

    XmStringFree(tcs);

    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 30);  			n++;
    XtSetArg(args[n], XmNmarginHeight, 10);  			n++;
    XtSetArg(args[n], XmNshadowType, XmSHADOW_ETCHED_OUT);  	n++;
    Frame3 = XmCreateFrame(RowColumn1, "Frame3", args, n);
    XtManageChild(Frame3);

    n = 0;
    PushButton1 = XmCreatePushButton(Frame3, "PushButton1", args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 10);  			n++;
    XtSetArg(args[n], XmNmarginHeight, 10);  			n++;
    XtSetArg(args[n], XmNshadowType, XmSHADOW_IN);  		n++;
    Frame4 = XmCreateFrame(RowColumn1, "Frame4", args, n);
    XtManageChild(Frame4);

    n = 0;
    ToggleButton1 = XmCreateToggleButton(Frame4, "ToggleButton1", args, n);
    XtManageChild(ToggleButton1);

    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 10);  			n++;
    XtSetArg(args[n], XmNmarginHeight, 10);  			n++;
    XtSetArg(args[n], XmNshadowType, XmSHADOW_OUT);  		n++;
    Frame5 = XmCreateFrame(RowColumn1, "Frame5", args, n);
    XtManageChild(Frame5);

    tcs = XmStringLtoRCreate("LABELGADGET1", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlabelString, tcs);  			n++;
    LabelGadget1 = XmCreateLabelGadget(Frame5, "LabelGadget1", args, n);
    XtManageChild(LabelGadget1);

    XmStringFree(tcs);

#ifdef REALIZE_AFTER
    XtRealizeWidget(Shell1);
#endif

    CommonPause();
    CommonPause();

    /* begin tests for PIR 2297 */

    n = 0;
    XtSetArg (args[n], XmNmarginHeight, 40); n++;
    XtSetValues (Frame5, args, n);

    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNmarginWidth, 40); n++;
    XtSetValues (Frame5, args, n);

    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNshadowType, XmSHADOW_IN); n++;
    XtSetValues (Frame5, args, n);

    CommonPause();

    /* end tests for PIR 2297 */

    XtAppMainLoop(app_context);
}
