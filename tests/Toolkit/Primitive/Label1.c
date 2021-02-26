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
static char rcsid[] = "$XConsortium: Label1.c /main/7 1995/07/13 19:08:18 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/****************************************
*   Automatic test program generation   *
*              Version 1.0              *
*       Fri Mar 31 10:55:08 1989        *
****************************************/

#include <testlib.h>

#include "gnu.bmp"
Pixmap gnumap;

/*  Global Variables  */
Widget    RowColumn1;
Widget    Label1;
Widget    Separator1;
Widget    Label2;

void  main (argc, argv)
int     argc;
char  **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XmString           tcs;
  XEvent             DummyEvent;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetValues(Shell1, args, n);
    
  XtRealizeWidget(Shell1);

  /* create and realize a rowcolumn container widget */
  n = 0;
  XtSetArg(args[n], XmNisAligned, FALSE);  n++;
  RowColumn1 = XmCreateRowColumn(Shell1, "RowColumn1", args, n);
  XtManageChild(RowColumn1);

  /* make a string label widget */
  n = 0;
  tcs = XmStringLtoRCreate("Multi-Line\nLabel String\n\n\n\nwith extra newlines",
			   XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNalignment, XmALIGNMENT_CENTER); n++;
  XtSetArg(args[n], XmNrecomputeSize, TRUE); n++;
  Label1 = XmCreateLabel(RowColumn1, "Label1", args, n);
  XtManageChild(Label1);

  /* add a separator */
  n = 0;
  Separator1 = XmCreateSeparator(RowColumn1, "Separator1", args, n);
  XtManageChild(Separator1);
  
  /* stick in a pixmap label widget. 1st create the pixmap */
  gnumap = 
    XCreatePixmapFromBitmapData(display,
				DefaultRootWindow(display),
				gnu_bits, gnu_width, gnu_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));

  n = 0;
  XtSetArg(args[n], XmNheight, 54);  n++;
  XtSetArg(args[n], XmNlabelType, XmPIXMAP);  n++;
  XtSetArg(args[n], XmNrecomputeSize, TRUE); n++;
  XtSetArg(args[n], XmNlabelPixmap, gnumap);  n++;
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  Label2 = XmCreateLabel(RowColumn1, "Label2", args, n);
  XtManageChild(Label2);
  XmStringFree(tcs);

  /* 
   * try to force contained widget to change size - do a SetValues
   * without changing anything
   */
  
  n = 0;
  XtSetValues(Label2,args,n);

  CommonPause();
  CommonPause(); 
  CommonPause();

  XtDestroyWidget(Label2);
  XtDestroyWidget(Label1);
  XtDestroyWidget(Separator1);
  XtDestroyWidget(RowColumn1);
  CommonPause();

  XtAppMainLoop(app_context);
}

















