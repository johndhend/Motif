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
static char rcsid[] = "$XConsortium: DrawnBtn2.c /main/8 1995/07/13 17:29:03 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*       Wed Mar 29 15:48:35 1989        *
****************************************/

#include <testlib.h>
#include <signal.h>
#include "dp.bmp"

Widget  RowColumn1 = NULL;
Widget  DrawnButton1 = NULL;
Widget  Separator1 = NULL;
Widget  DrawnButton2 = NULL;
Widget  Separator2 = NULL;
Widget  DrawnButton3 = NULL;
Widget  Separator3 = NULL;
Widget  DrawnButton4 = NULL;
Widget  Separator4 = NULL;

void ReDrawdb4();

Pixmap    nopanic;
GC    	  dbgc;
XGCValues dbgcv;

/************ Call Back for resize events *************/

void ReSizeCB( w, client_data, call_data)
Widget  w;
XtPointer client_data; 
XtPointer call_data;
{
  Arg    wargs[MAX_ARGS];
  int n;
  Dimension w_width, w_height;

  /* Get new size of widget */
  n=0;
  XtSetArg(wargs[n],XmNwidth,&w_width); n++;
  XtSetArg(wargs[n],XmNheight,&w_height); n++;
  XtGetValues(w,wargs,n);

  printf("Resized width & height is %d, %d\n",w_width, w_height);
}

/*********************** MAIN STARTS HERE **************************/
void  main (argc, argv)
int     argc;
char  **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XmString           tcs;
  XEvent             DummyEvent;

  XtArgVal  getValue();
  void      quit();

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 400);  n++;
  XtSetValues(Shell1, args, n);
  

  XtRealizeWidget(Shell1);


  n = 0;
  XtSetArg(args[n], XmNwidth, 160);  n++;
  XtSetArg(args[n], XmNheight, 400);  n++;
  XtSetArg(args[n], XmNmarginWidth, 5);  n++;
  XtSetArg(args[n], XmNmarginHeight, 5);  n++;
  RowColumn1 = XmCreateRowColumn(Shell1, "RowColumn1", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 150);  n++;
  XtSetArg(args[n], XmNheight, 25);  n++;
  tcs = XmStringLtoRCreate("Drawn_Button", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNpushButtonEnabled, TRUE);  n++;
  DrawnButton1 = XmCreateDrawnButton(RowColumn1, "DrawnButton1", args, n);
  XtManageChild(DrawnButton1);
  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNseparatorType, XmDOUBLE_DASHED_LINE);  n++;
  Separator1 = XmCreateSeparator(RowColumn1, "Separator1", args, n);
  XtManageChild(Separator1);
  
  n = 0;
  XtSetArg(args[n], XmNwidth, 150);  n++;
  XtSetArg(args[n], XmNheight, 25);  n++;
  tcs = XmStringLtoRCreate("Drawn_Button", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNpushButtonEnabled, FALSE);  n++;
  DrawnButton2 = XmCreateDrawnButton(RowColumn1, "DrawnButton2", args, n);
  XtManageChild(DrawnButton2);
  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNseparatorType, XmDOUBLE_DASHED_LINE);  n++;
  Separator2 = XmCreateSeparator(RowColumn1, "Separator2", args, n);
  XtManageChild(Separator2);

  n = 0;
  XtSetArg(args[n], XmNwidth, 150);  n++;
  XtSetArg(args[n], XmNheight, 25);  n++;
  tcs = XmStringLtoRCreate("Drawn_Button", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNpushButtonEnabled, FALSE);  n++;
  XtSetArg(args[n], XmNshadowType, XmSHADOW_ETCHED_OUT);  n++;
  DrawnButton3 = XmCreateDrawnButton(RowColumn1, "DrawnButton3", args, n);
  XtManageChild(DrawnButton3);
  XmStringFree(tcs);

  /* add resize callback */
  XtAddCallback(DrawnButton1,XmNresizeCallback,ReSizeCB,NULL);
  XtManageChild(RowColumn1); 

  CommonPause();
  CommonPause();
  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(DrawnButton1);
  XtDestroyWidget(DrawnButton2);
  XtDestroyWidget(DrawnButton3);
  XtDestroyWidget(Separator1);
  XtDestroyWidget(Separator2);
}

