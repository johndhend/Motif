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
static char rcsid[] = "$XConsortium: Scrollbar3.c /main/6 1995/07/13 19:14:33 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.3              *
*       Thu Apr  6 08:30:55 1989        *
****************************************/

#include <testlib.h>

Widget	Form1, ScrollBar1, ScrollBar2, ScrollBar3, ScrollBar4, ScrollBar5;

void  main(argc, argv)
int     argc;
char  **argv;
{
  register int  n;
  Arg args[MAX_ARGS];

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);
  XtRealizeWidget(Shell1);

  n = 0;
  Form1 = XmCreateForm(Shell1, "Form1", args, n);
  XtManageChild(Form1);

  n = 0;
  XtSetArg(args[n], XmNvalue, 100);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar1 = XmCreateScrollBar(Form1, "ScrollBar1", args, n);
  XtManageChild(ScrollBar1);

  n = 0;
  XtSetArg(args[n], XmNx, 50);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar2 = XmCreateScrollBar(Form1, "ScrollBar2", args, n);
  XtManageChild(ScrollBar2);

  n = 0;
  XtSetArg(args[n], XmNx, 50);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar3 = XmCreateScrollBar(Form1, "ScrollBar3", args, n);
  XtManageChild(ScrollBar3);

  XtDestroyWidget(ScrollBar3);

  n = 0;
  XtSetArg(args[n], XmNx, 100);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar3 = XmCreateScrollBar(Form1, "ScrollBar3", args, n);
  XtManageChild(ScrollBar3);

  n = 0;
  XtSetArg(args[n], XmNx, 150);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar4 = XmCreateScrollBar(Form1, "ScrollBar4", args, n);
  XtManageChild(ScrollBar4);

  n = 0;
  XtSetArg(args[n], XmNx, 200);  n++;
  XtSetArg(args[n], XmNsliderSize, 20);  n++;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 25);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 5);  n++;
  ScrollBar5 = XmCreateScrollBar(Form1, "ScrollBar5", args, n);
  XtManageChild(ScrollBar5);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNvalue, 10);  n++;
  XtSetArg(args[n], XmNminimum, 20);  n++;
  XtSetValues(ScrollBar1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNminimum, 0);  n++;
  XtSetValues(ScrollBar1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpageIncrement, 5);  n++;
  XtSetValues(ScrollBar1, args, n);
  CommonPause();
  
  n = 0;
  XtSetArg(args[n], XmNinitialDelay, 5);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 25);  n++;
  XtSetValues(ScrollBar1, args, n);

  n = 0;
  XtSetArg(args[n], XmNminimum, 50);  n++;
  XtSetValues(ScrollBar1, args, n);
  CommonPause();
  
  n = 0;
  XtSetArg(args[n], XmNmaximum, 20);  n++;
  XtSetValues(ScrollBar1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNshowArrows, FALSE);  n++;
  XtSetValues(ScrollBar2, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNvalue, 0);  n++;
  XtSetValues(ScrollBar2, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNincrement, -1);  n++;
  XtSetArg(args[n], XmNpageIncrement, -1);  n++;
  XtSetArg(args[n], XmNinitialDelay, -1);  n++;
  XtSetArg(args[n], XmNrepeatDelay, -1);  n++;
  XtSetValues(ScrollBar3, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNincrement, 10);  n++;
  XtSetArg(args[n], XmNpageIncrement, 20);  n++;
  XtSetArg(args[n], XmNinitialDelay, 0);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 0);  n++;
  XtSetValues(ScrollBar3, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNinitialDelay, 1);  n++;
  XtSetArg(args[n], XmNrepeatDelay, 1);  n++;
  XtSetValues(ScrollBar3, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);  n++;
  XtSetValues(ScrollBar4, args, n);
  CommonPause();
  
  n = 0;
  XtSetArg(args[n], XmNvalue, 10);  n++;
  XtSetValues(ScrollBar4, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNminimum, 20);  n++;
  XtSetValues(ScrollBar4, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNvalue, 30);  n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNvalue, 60);  n++;
  XtSetArg(args[n], XmNsliderSize, 50);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNsliderSize, 100);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNsliderSize, 99);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNsliderSize, 101);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNminimum, 20);  n++;
  XtSetValues(ScrollBar5, args, n);
  CommonPause();

  XtDestroyWidget(ScrollBar5);
  XtDestroyWidget(ScrollBar4);
  XtDestroyWidget(ScrollBar3);
  XtDestroyWidget(ScrollBar2);
  XtDestroyWidget(ScrollBar1);
  XtDestroyWidget(Form1);
  CommonPause();

  XtAppMainLoop(app_context);
}


















