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
static char rcsid[] = "$XConsortium: ArrowBGad1.c /main/7 1995/07/13 17:27:08 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include "Xm/XmP.h"

Widget PanedWindow1, ArrowButton1, ArrowButtonGadget1; 
Widget ArrowButtonGadget2, ArrowButtonGadget3, ArrowButtonGadget4;

void main(argc, argv)
int argc;
char **argv;
{
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);

  n = 0;
  PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1", args, n);
  XtManageChild(PanedWindow1);

  n = 0;
  ArrowButton1 = XmCreateArrowButton(PanedWindow1, "ArrowButton1", args, n);
  XtManageChild(ArrowButton1);

  /*
   * We must realize the top level shell here for arrow to size correctly.
   */

  XtRealizeWidget(Shell1);
  CommonPause();

  n = 0;
  ArrowButtonGadget1 = 
    XmCreateArrowButtonGadget(PanedWindow1,
			      "ArrowButtonGadget1", args, n);
  XtManageChild(ArrowButtonGadget1);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);  n++;
  ArrowButtonGadget2 = 
    XmCreateArrowButtonGadget(PanedWindow1,
			      "ArrowButtonGadget2", args, n);
  XtManageChild(ArrowButtonGadget2);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_LEFT);  n++;
  ArrowButtonGadget3 = 
    XmCreateArrowButtonGadget(PanedWindow1,
			      "ArrowButtonGadget3", args, n);
  XtManageChild(ArrowButtonGadget3);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_RIGHT);  n++;
  ArrowButtonGadget4 = 
    XmCreateArrowButtonGadget(PanedWindow1,
			      "ArrowButtonGadget4", args, n);
  XtManageChild(ArrowButtonGadget4);

  CommonPause();
  CommonPause();
  CommonPause();
  XtAppMainLoop(app_context);

  /*
   * Clean up to test more easily for memory leaks
   */

  XtDestroyWidget(ArrowButtonGadget1);
  XtDestroyWidget(ArrowButtonGadget2);
  XtDestroyWidget(ArrowButtonGadget3);
  XtDestroyWidget(ArrowButtonGadget4);
  XtDestroyWidget(ArrowButton1);
  XtDestroyWidget(PanedWindow1);
}
