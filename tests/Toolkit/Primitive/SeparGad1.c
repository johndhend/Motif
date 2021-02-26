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
static char rcsid[] = "$XConsortium: SeparGad1.c /main/8 1995/07/13 19:09:55 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.4              *
*       Fri Jun 30 13:18:18 1989        *
****************************************/


#include <testlib.h>

void  main(argc, argv)
int argc;
char **argv;
{
  Widget BBoard, Label1, Label2, Separator1, Separator2, Separator3;
  Widget Separator4, Label3, Label4;
  register int n;
  Arg args[MAX_ARGS];
  Dimension separator_margin;
  char trace_string[128];
  XmString tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++; 
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);
  XtRealizeWidget(Shell1);

  n = 0;
  BBoard = XmCreateBulletinBoard(Shell1, "BBoard", args, n);
  XtManageChild(BBoard);

  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 10); n++;
  Label1 = XmCreateLabel(BBoard, "Label1", args, n);
  XtManageChild(Label1);
  
  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 30); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  Separator1 = XmCreateSeparatorGadget(BBoard, "Separator1", args, n);
  XtManageChild(Separator1);
  
  n = 0;
  XtSetArg(args[n], XmNmargin, &separator_margin); n++;
  XtGetValues(Separator1, args, n);
  sprintf(trace_string, "XtGetValues: Separator1 = %d\n\n",
	  separator_margin);

  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 70); n++;
  Label2 = XmCreateLabel(BBoard, "Label2", args, n);
  XtManageChild(Label2);
  
  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 90); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  Separator2 = XmCreateSeparatorGadget(BBoard, "Separator2", args, n);
  XtManageChild(Separator2);
  
  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 130); n++;
  Label3 = XmCreateLabel(BBoard, "Label3", args, n);
  XtManageChild(Label3);

  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 150); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  Separator3 = XmCreateSeparatorGadget(BBoard, "Separator3", args, n);
  XtManageChild(Separator3);
  
  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 190); n++;
  Label4 = XmCreateLabel(BBoard, "Label4", args, n);
  XtManageChild(Label4);

  n = 0;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 210); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  Separator4 = XmCreateSeparatorGadget(BBoard, "Separator4", args, n);
  XtManageChild(Separator4);

  CommonPause();		

  n = 0;
  tcs = XmStringCreateLtoR("Shadow Etched Out", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetValues(Label1, args, n);
  XmStringFree (tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++;
  XtSetArg(args[n], XmNseparatorType, XmSHADOW_ETCHED_OUT);  n++;
  XtSetArg(args[n], XmNmargin, 25);  n++;
  XtSetValues(Separator1, args, n);

  n = 0;
  tcs = XmStringCreateLtoR("Double Line", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetValues(Label2, args, n);
  XmStringFree (tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++;
  XtSetArg(args[n], XmNseparatorType, XmDOUBLE_LINE);  n++;
  XtSetValues(Separator2, args, n);

  n = 0;
  tcs = XmStringCreateLtoR("Double Dashed Line", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetValues(Label3, args, n);
  XmStringFree (tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++;
  XtSetArg(args[n], XmNseparatorType, XmDOUBLE_DASHED_LINE);  n++;
  XtSetValues(Separator3, args, n);

  n = 0;
  tcs = XmStringCreateLtoR("Single Dashed Line", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetValues(Label4, args, n);
  XmStringFree (tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++; 
  XtSetArg(args[n], XmNseparatorType, XmSINGLE_DASHED_LINE);  n++;
  XtSetValues(Separator4, args, n);
  CommonPause();


  n = 0;
  tcs = XmStringCreateLtoR("Shadow Etched In", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetValues(Label1, args, n);
  XmStringFree (tcs);

  n = 0;
  XtSetArg(args[n], XmNwidth, 2); n++;
  XtSetArg(args[n], XmNmargin, 0); n++;
  XtSetArg(args[n], XmNheight, 40); n++;
  XtSetArg(args[n], XmNseparatorType, XmSHADOW_ETCHED_IN);  n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
  XtSetValues(Separator1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNmargin, 15);  n++;
  XtSetArg(args[n], XmNheight, 6); n++;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
  XtSetValues(Separator1, args, n);
  XtSetValues(Separator2, args, n);
  XtSetValues(Separator3, args, n);
  XtSetValues(Separator4, args, n);
  CommonPause();

  XtDestroyWidget(Label1);
  XtDestroyWidget(Label2);
  XtDestroyWidget(Label3);
  XtDestroyWidget(Label4);
  XtDestroyWidget(Separator1);
  XtDestroyWidget(Separator2);
  XtDestroyWidget(Separator3);
  XtDestroyWidget(Separator4);
  XtDestroyWidget(BBoard);
  CommonPause();
  XtAppMainLoop(app_context);
}
