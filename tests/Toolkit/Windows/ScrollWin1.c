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
static char rcsid[] = "$XConsortium: ScrollWin1.c /main/8 1995/07/13 19:47:41 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget	PushButton1, PushButton2, PushButton3, PushButton4, PushButton5,
	PushButton6, PushButton7, PushButton8, PushButton9, PushButton10,
	PushButton11,PushButton12,PushButton13,PushButton14,PushButton15,
	ScrolledWindow1, RowColumn2;


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;


    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetValues(Shell1, args, n);
    
    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);  n++;
    XtSetArg(args[n], XmNshadowThickness, 4);  n++;
    ScrolledWindow1 = XmCreateScrolledWindow(Shell1, "ScrolledWindow1", 
	args, n);

    if (ScrolledWindow1 != NULL) 
	XtManageChild(ScrolledWindow1);
    else
	printf ("ScrolledWindow zero\n");

    XtRealizeWidget(Shell1);

    CommonPause();
 
    n = 0;
    RowColumn2 = XmCreateRowColumn(ScrolledWindow1, "RowColumn2", args, n);
    XtManageChild(RowColumn2);

    n = 0;
    PushButton1 = XmCreatePushButton(RowColumn2, "PushButton1", args, n);
    XtManageChild(PushButton1);

    n = 0;
    PushButton2 = XmCreatePushButton(RowColumn2, "PushButton2", args, n);
    XtManageChild(PushButton2);

    n = 0;
    PushButton3 = XmCreatePushButton(RowColumn2, "PushButton3", args, n);
    XtManageChild(PushButton3);

    n = 0;
    PushButton4 = XmCreatePushButton(RowColumn2, "PushButton4", args, n);
    XtManageChild(PushButton4);

    n = 0;
    PushButton5 = XmCreatePushButton(RowColumn2, "PushButton5", args, n);
    XtManageChild(PushButton5);

    n = 0;
    PushButton6 = XmCreatePushButton(RowColumn2, "PushButton6", args, n);
    XtManageChild(PushButton6);

    n = 0;
    PushButton7 = XmCreatePushButton(RowColumn2, "PushButton7", args, n);
    XtManageChild(PushButton7);

    n = 0;
    PushButton8 = XmCreatePushButton(RowColumn2, "PushButton8", args, n);
    XtManageChild(PushButton8);

    n = 0;
    PushButton9 = XmCreatePushButton(RowColumn2, "PushButton9", args, n);
    XtManageChild(PushButton9);

    n = 0;
    PushButton10 = XmCreatePushButton(RowColumn2, "PushButton10", args, n);
    XtManageChild(PushButton10);

    n = 0;
    PushButton11 = XmCreatePushButton(RowColumn2, "PushButton11", args, n);
    XtManageChild(PushButton11);

    n = 0;
    PushButton12 = XmCreatePushButton(RowColumn2, "PushButton12", args, n);
    XtManageChild(PushButton12);

    n = 0;
    PushButton13 = XmCreatePushButton(RowColumn2, "PushButton13", args, n);
    XtManageChild(PushButton13);

    n = 0;
    PushButton14 = XmCreatePushButton(RowColumn2, "PushButton14", args, n);
    XtManageChild(PushButton14);

    n = 0;
    PushButton15 = XmCreatePushButton(RowColumn2, "PushButton15", args, n);
    XtManageChild(PushButton15);


    CommonPause();
    CommonPause();
    CommonPause();

    XtAppMainLoop(app_context);
}
