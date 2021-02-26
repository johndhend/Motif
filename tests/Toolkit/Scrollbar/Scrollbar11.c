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
static char rcsid[] = "$XConsortium: Scrollbar11.c /main/7 1995/07/13 19:13:56 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 * Create 2 scroll bars. One with MAX_ON_LEFT, the other with MAX_ON_RIGHT
 * Check the keybindings work
 *
 * Repeat for Vertical scrollbar with MAX_ON_TOP, MAX_ON_BOTTOM
 *
 ************************************************************************/

#include <X11/StringDefs.h>
#include <testlib.h>

static void ScrollCallback();

static void ScrollCallback(sbw, closure, call_data)
Widget sbw;
XtPointer closure;
XtPointer call_data;

{
   int value;
   int reason;
   XmScrollBarCallbackStruct 
          *call_value=(XmScrollBarCallbackStruct *) call_data;

   reason = call_value -> reason;
   value = call_value -> value;

   switch(reason)
   {
      case XmCR_VALUE_CHANGED:
         printf("XmScrollbar(XmCR_VALUE_CHANGED,%d)\n", value);
         break;
      case XmCR_INCREMENT:
         printf("XmScrollbar(XmCR_INCREMENT,%d)\n", value);
         break;
      case XmCR_DECREMENT:
         printf("XmScrollbar(XmCR_DECREMENT,%d)\n", value);
         break;
      case XmCR_PAGE_INCREMENT:
         printf("XmScrollbar(XmCR_PAGE_INCREMENT,%d)\n", value);
         break;
      case XmCR_PAGE_DECREMENT:
         printf("XmScrollbar(XmCR_PAGE_DECREMENT,%d)\n", value);
         break;
      case XmCR_TO_TOP:
         printf("XmScrollbar(XmCR_TO_TOP,%d)\n", value);
         break;
      case XmCR_TO_BOTTOM:
         printf("XmScrollbar(XmCR_TO_BOTTOM,%d)\n", value);
         break;
      case XmCR_HELP:
         printf("XmScrollbar(XmCR_HELP,%d)\n", value);
         break;
      default:
         printf("Unexpected Callback reason!\n");
         break;
   }
}

void main(argc, argv)
int argc;
char **argv;
{
  Widget bb, bb2;
  Widget scrollbar1;
  Widget scrollbar2;
  Arg args[10];
  int n, i;

  CommonTestInit(argc, argv);

  bb = XmCreateBulletinBoard(Shell1, "bb", NULL, 0);
  XtManageChild(bb);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  XtSetArg(args[n], XmNprocessingDirection,XmMAX_ON_TOP); n++;
  XtSetArg(args[n], XmNx, 20); n++;
  XtSetArg(args[n], XmNy, 20); n++;
  XtSetArg(args[n], XmNwidth, 30); n++;
  XtSetArg(args[n], XmNheight, 400);		n++;
  XtSetArg(args[n], XmNtraversalOn, True); 	n++;
  XtSetArg(args[n], XmNhighlightThickness, 2);		n++;
  XtSetArg(args[n], XmNhighlightOnEnter, True);		n++;
  scrollbar1 = XmCreateScrollBar(bb, "scrollbar1", args, n);
  XtManageChild(scrollbar1);
  XtAddCallback(scrollbar1, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNincrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNdecrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNpageIncrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNpageDecrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNtoTopCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar1, XmNtoBottomCallback,  ScrollCallback, NULL);
  n = 0;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_BOTTOM); n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNx, 70); n++;
  XtSetArg(args[n], XmNy, 20); n++;
  XtSetArg(args[n], XmNwidth, 30); n++;
  XtSetArg(args[n], XmNheight, 400);		n++;
  XtSetArg(args[n], XmNtraversalOn, True); 	n++;
  XtSetArg(args[n], XmNhighlightThickness, 2);		n++;
  XtSetArg(args[n], XmNhighlightOnEnter, True);		n++;
  scrollbar2 = XmCreateScrollBar(bb, "scrollbar2", args, n);
  XtManageChild(scrollbar2);

  XtAddCallback(scrollbar2, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNincrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNdecrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNpageIncrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNpageDecrementCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNtoTopCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar2, XmNtoBottomCallback,  ScrollCallback, NULL);

  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();
  printf("changing to orientation = HORIZONTAL\n");
  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL);	n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
  XtSetArg(args[n], XmNx, 20); n++;
  XtSetArg(args[n], XmNy, 20); n++;
  XtSetArg(args[n], XmNwidth, 400); n++;
  XtSetArg(args[n], XmNheight, 30);		n++;
  XtSetValues(scrollbar1, args, n);
  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL);	n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_LEFT); n++;
  XtSetArg(args[n], XmNx, 20); n++;
  XtSetArg(args[n], XmNy, 70); n++;
  XtSetArg(args[n], XmNwidth, 400); n++;
  XtSetArg(args[n], XmNheight, 30);		n++;
  XtSetValues(scrollbar2, args, n);

  CommonPause();

  XtDestroyWidget(scrollbar2);

  /*** Test case for CR 6607 ***/

  n = 0;
  XtSetArg(args[n], XmNx, 0); n++;
  XtSetArg(args[n], XmNy, 70); n++;
  bb2 = XmCreateBulletinBoard(bb, "bb2", args, n);
  XtManageChild(bb2);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL);	n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_LEFT); n++;
  XtSetArg(args[n], XmNx, 15); n++;
  XtSetArg(args[n], XmNy, 0); n++;
  XtSetArg(args[n], XmNwidth, 400); n++;
  XtSetArg(args[n], XmNheight, 30);		n++;
  XtSetArg(args[n], XmNtraversalOn, True); 	n++;
  XtSetArg(args[n], XmNhighlightThickness, 2);		n++;
  XtSetArg(args[n], XmNhighlightOnEnter, True);		n++;
  scrollbar2 = XmCreateScrollBar(bb2, "scrollbar2", args, n);
  XtManageChild(scrollbar2);

  XtSetSensitive(scrollbar1, False);
  XtSetSensitive(bb2, False);

  CommonPause();
  CommonPause();

  XtDestroyWidget(scrollbar2);
  XtDestroyWidget(bb2);

  /*** End test case for CR 6607 ***/

  XtDestroyWidget(scrollbar1);
  XtDestroyWidget(bb);

  XtAppMainLoop(app_context);
}
