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
static char rcsid[] = "$XConsortium: Scrollbar5.c /main/6 1995/07/13 19:15:09 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a scrollbar with a full set of callbacks.
 *
 ************************************************************************/

#include <X11/StringDefs.h>
#include <testlib.h>

extern void ScrollCallback();

void main(argc, argv)
int argc;
char **argv;
{
   Widget frame;
   Widget scrollbar;
   Arg args[10];
   int n;

   CommonTestInit(argc, argv);
    
   frame = 
      XmCreateFrame(Shell1, "frame", NULL, 0);
   XtManageChild(frame);
   n = 0;

   XtSetArg(args[n], XmNwidth, 50); n++;
   XtSetArg(args[n], XmNheight, 250); n++;
   scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
   XtManageChild(scrollbar);

   XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNincrementCallback,     ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNdecrementCallback,     ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNpageIncrementCallback, ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNpageDecrementCallback, ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNtoTopCallback,         ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNtoBottomCallback,      ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNdragCallback,          ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);

   XtRealizeWidget(Shell1);

   CommonPause();
   CommonPause();

   /* Change Orientation to Horizontal and resume testing */

   n = 0;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
   XtSetArg(args[n], XmNwidth, 250); n++;
   XtSetArg(args[n], XmNheight, 50); n++;
   XtSetArg(args[n] , XmNvalue, 0); n++;
   XtSetValues(scrollbar, args, n);

   CommonPause();
   CommonPause();

   XtDestroyWidget(scrollbar);
   XtDestroyWidget(frame);
   CommonPause();
   XtAppMainLoop(app_context);
}

void ScrollCallback(sbw, closure, call_data)
XmScrollBarWidget sbw;
caddr_t closure;
caddr_t call_data;
{
  int value;
  int reason;
  int pixel;

  XmScrollBarCallbackStruct * call_value = 
    (XmScrollBarCallbackStruct *) call_data;

  reason = call_value -> reason;
  value = call_value -> value;
  pixel = call_value -> pixel;

  switch(reason)
   {
      case XmCR_VALUE_CHANGED:
         printf("Reason = XmCR_VALUE_CHANGED,	Value = %d\n", value);
      break;

      case XmCR_INCREMENT:
         printf("Reason = XmCR_INCREMENT,	Value = %d\n", value);
      break;

      case XmCR_DECREMENT:
         printf("Reason = XmCR_DECREMENT,	Value = %d\n", value);
      break;

      case XmCR_PAGE_INCREMENT:
         printf("Reason = XmCR_PAGE_INCREMENT,	Value = %d\n", value);
      break;

      case XmCR_PAGE_DECREMENT:
         printf("Reason = XmCR_PAGE_DECREMENT,	Value = %d\n", value);
      break;

      case XmCR_TO_TOP:
         printf("Reason = XmCR_TO_TOP,	Value = %d,	Pixel = %d\n",
                 value, pixel);
      break;

      case XmCR_TO_BOTTOM:
         printf("Reason = XmCR_TO_BOTTOM,	Value = %d,	Pixel = %d\n",
                 value, pixel);
      break;

      case XmCR_DRAG:
            printf("Reason = XmCR_DRAG,	Value = %d\n", value);
      break;

      case XmCR_HELP:
         printf("Reason = XmCR_HELP,	Value = %d\n", value);
      break;

      default:
         printf("Hit the default, incorrect reason sent!!\n");
      break;

   }
}












