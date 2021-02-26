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
static char rcsid[] = "$XConsortium: ScrollWin5.c /main/8 1995/07/13 19:50:28 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>

static XtCallbackProc  ResizeDrawAreaCB();

Widget  DrawingArea1;
Widget  ScrolledWindow1;
Widget  ArrowB1, ArrowB2, ArrowB3, ArrowB4;
Widget  Form;



void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    CommonTestInit(argc, argv);

#ifdef MOTIF1_1
#ifdef AUTOMATION
    n = 0;
    XtSetArg(args[n], XmNwidth, 200); n++;
    XtSetArg(args[n], XmNheight, 200); n++;
    XtSetValues(Shell1, args, n);
#endif
#endif

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);			n++;
    XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE);			n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmBOTTOM_LEFT); 		n++; 
    XtSetArg(args[n], XmNbackground, CommonGetColor("MediumAquamarine")); n++;
    XtSetArg(args[n], XmNwidth, 200);					n++;
    XtSetArg(args[n], XmNheight, 200);					n++;
    ScrolledWindow1 = XmCreateScrolledWindow
				(Shell1, "ScrolledWindow1", args, n);
    XtManageChild(ScrolledWindow1);

    n = 0;
    Form = XmCreateForm(ScrolledWindow1, "Form", args, n);
    XtManageChild(Form);

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg(args[n], XmNheight, 200);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("coral"));	n++;
    ArrowB1 = XmCreateArrowButton(Form, "ArrowButton1", args, n);
    XtManageChild(ArrowB1);

    n = 0;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
    XtSetArg(args[n], XmNleftWidget, ArrowB1);			n++;
    XtSetArg(args[n], XmNleftOffset, 10);			n++;
    XtSetArg(args[n], XmNwidth, 200);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("violet"));	n++;
    ArrowB2 = XmCreateArrowButton(Form, "ArrowButton2", args, n);
    XtManageChild(ArrowB2);

    n = 0;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++; 
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);      n++;
    XtSetArg(args[n], XmNleftWidget, ArrowB1);      		n++;
    XtSetArg(args[n], XmNleftOffset, 10);	      		n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
    XtSetArg(args[n], XmNtopWidget, ArrowB2);			n++;
    XtSetArg(args[n], XmNtopOffset, 10);			n++;
    XtSetArg(args[n], XmNwidth, 150);				n++;
    XtSetArg(args[n], XmNheight, 150);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("Yellow"));	n++;
    ArrowB3 = XmCreateArrowButton(Form, "ArrowButton3", args, n);
    XtManageChild(ArrowB3);

    XtRealizeWidget(Shell1);
 
    CommonPause();  

    n = 0;
    XtSetArg(args[n], XmNarrowDirection, XmARROW_LEFT);		n++;
    XtSetArg(args[n], XmNbottomOffset, 25);			n++;
    XtSetArg(args[n], XmNtopOffset, 25);			n++;
    XtSetValues(ArrowB3, args, n);

    CommonPause();

    XtUnmanageChild(ArrowB3);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE);	n++;
    XtSetValues(ArrowB3, args, n);

    n = 0;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
    XtSetArg(args[n], XmNtopWidget, ArrowB3);			n++;
    XtSetArg(args[n], XmNtopOffset, 10);			n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("White"));	n++;
    ArrowB4 = XmCreateArrowButton(Form, "ArrowButton4", args, n);
    XtManageChild(ArrowB4);

    CommonPause();

    XtManageChild(ArrowB3);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 300);				n++;
    XtSetArg(args[n], XmNheight, 300);				n++;
    XtSetValues(ScrolledWindow1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 400);				n++;
    XtSetArg(args[n], XmNheight, 400);				n++;
    XtSetValues(Form, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNx, 50);				n++;
    XtSetArg(args[n], XmNy, 50);				n++;
    XtSetValues(Form, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);				n++;
    XtSetArg(args[n], XmNheight, 100);				n++;
    XtSetValues(ScrolledWindow1, args, n);

    CommonPause();

    XtAppMainLoop(app_context);
}
