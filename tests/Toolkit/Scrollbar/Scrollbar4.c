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
static char rcsid[] = "$TOG: Scrollbar4.c /main/7 1999/01/15 12:35:11 jff $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a horizontal scrollbar with reverse processing direction
 *  SetValues on the scrollbar value and ensure that the slider is
 *  positioned to the proper location.
 *
 ************************************************************************/

#include <testlib.h>

void DumpData();
static void ScrollCallback();

void main (argc, argv)
int argc;
char **argv;

{
   Widget frame;
   Widget scrollbar;
   Arg args[10];
   int n;
   int i;
   int value, slider_size, increment, page_increment;
   Boolean notify = False;

   CommonTestInit(argc, argv);

   n = 0;
   XtSetArg(args[n], XmNwidth,  400);  n++;
   XtSetArg(args[n], XmNheight, 300);  n++;
   XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
   XtSetValues(Shell1, args, n);
    
   frame = 
     XmCreateFrame(Shell1, "frame", NULL, 0);
   XtManageChild(frame);

   n = 0;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL);		n++;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_LEFT);	n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild(scrollbar);

   XtRealizeWidget(Shell1);

   printf("Setting the value to 20.\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 20); n++;
   XtSetValues(scrollbar, args, n);

   XtAddCallback(scrollbar, XmNvalueChangedCallback, ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNhelpCallback, ScrollCallback, NULL);

   CommonPause();
   XtDestroyWidget(scrollbar);

   /*
    *
    *  Create a horizontal scrollbar with reverse processing direction
    *  SetValues on the scrollbar value and ensure that the slider is
    *  positioned to the proper location.
    *
    */

   n = 0;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL);		n++;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_LEFT);	n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild(scrollbar);

   printf("Setting the value to 20.\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 20); n++;
   XtSetValues(scrollbar, args, n);

   n = 0;
   XtSetArg(args[n], XmNvalue, &value);	n++;
   XtGetValues(scrollbar, args, n);
   printf("GetValues value = %d\n", value);

   printf("Reversing the processing direction to max on right.\n");
   n = 0;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT);	n++;
   XtSetValues(scrollbar, args, n);

   n = 0;
   XtSetArg(args[n], XmNvalue, &value);	n++;
   XtGetValues(scrollbar, args, n);
   printf("GetValues value = %d\n", value);

   XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);

   CommonPause();
   XtDestroyWidget(scrollbar);

   /*
    *
    *  Create a vertical scrollbar with reverse processing direction
    *  SetValues on the scrollbar value and ensure that the slider is
    *  positioned to the proper location.  SetValues to change both
    *  the processing direction and value and ensure that the scrollbar
    *  is displayed correctly.
    *
    */

   n = 0;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);	n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild (scrollbar);

   printf("Setting the value to 20.\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 20); n++;
   XtSetValues(scrollbar, args, n);

   n = 0;
   XtSetArg(args[n], XmNvalue, &value);	n++;
   XtGetValues(scrollbar, args, n);
   printf("GetValues value = %d\n", value);

   printf("Reversing the processing direction to max on bottom.\n");
   printf("Changing the value to 80.\n");
   n = 0;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_BOTTOM);	n++;
   XtSetArg(args[n], XmNvalue, 80);				n++;
   XtSetValues(scrollbar, args, n);

   n = 0;
   XtSetArg(args[n], XmNvalue, &value);	n++;
   XtGetValues(scrollbar, args, n);
   printf("GetValues value = %d\n", value);

   XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);

   CommonPause();
   XtDestroyWidget(scrollbar);

   n = 0;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);	n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild(scrollbar);

   XtAddCallback(scrollbar, XmNvalueChangedCallback, ScrollCallback, NULL);
   XtAddCallback(scrollbar, XmNhelpCallback, ScrollCallback, NULL);

   value = 0;
   slider_size = 10;
   increment = 1;
   page_increment = 10;

   for (i = 0; i < 10; i ++)
   {
      XmScrollBarSetValues(scrollbar, value, slider_size, 
			   increment, page_increment, notify);
      if (notify == False) notify = True;
      else notify = False;
      XmScrollBarGetValues(scrollbar, &value, &slider_size, 
                            &increment, &page_increment);
      printf("value = %d,  slider_size = %d,  incr = %d,  page_incr = %d\n\n",
              value, slider_size, increment, page_increment);
      value += 5;
      slider_size += 5;
      increment += 2;
      page_increment += 5;
   }

   CommonPause();
   XtDestroyWidget(scrollbar);

   /*
    *
    *  Create a vertical scrollbars with various incorrect data.
    *  Ensure that the display and error messages are correct.
    *
    */

   printf ("creating with the slider size to 40 and value to 70\n");
   n = 0;
   XtSetArg(args[n], XmNsliderSize, 40); n++;
   XtSetArg(args[n], XmNvalue, 70); n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
   XtSetArg(args[n], XmNheight, 400); n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild (scrollbar);
   DumpData(scrollbar);

   CommonPause();
   XtDestroyWidget(scrollbar);

   printf("creating with the maximum to 50 and value to 60\n");
   n = 0;
   XtSetArg(args[n], XmNmaximum, 50);	n++;
   XtSetArg(args[n], XmNvalue, 60);	n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNheight, 400);				n++;
   scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
   XtManageChild(scrollbar);
   DumpData(scrollbar);

   CommonPause();
   XtDestroyWidget(scrollbar);

   printf("creating with the value of 110\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 110);	n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNheight, 400);				n++;
   scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
   XtManageChild(scrollbar);
   DumpData(scrollbar);

   CommonPause();
   XtDestroyWidget(scrollbar);

   printf("creating with the maximum of 5\n");
   n = 0;
   XtSetArg(args[n], XmNmaximum, 5);	n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNheight, 400);				n++;
   scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
   XtManageChild(scrollbar);
   DumpData(scrollbar);

   CommonPause();
   XtDestroyWidget(scrollbar);

   printf("creating with the value of 0 and the min of 10\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 0);	n++;
   XtSetArg(args[n], XmNminimum, 10);	n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg(args[n], XmNheight, 400);				n++;
   scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
   XtManageChild(scrollbar);
   DumpData(scrollbar);
   CommonPause();
   XtDestroyWidget(scrollbar);

   printf("creating with the min to 20\n");
   n = 0;
   XtSetArg(args[n], XmNminimum, 20);	n++;
   XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
   XtSetArg(args[n], XmNheight, 400); n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild(scrollbar);
   DumpData(scrollbar);

   CommonPause();
   XtDestroyWidget(scrollbar);

   /*
    *
    *  Create a vertical scrollbar and test SetValue for some invalid
    *  data.  Ensure that the redisplay is correct.
    *
    */

   n = 0;
   XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
   XtSetArg(args[n], XmNheight, 400); n++;
   scrollbar = XmCreateScrollBar (frame, "scrollbar", args, n);
   XtManageChild(scrollbar);

   DumpData(scrollbar);
   CommonPause();

   printf("changing the slider size to 40 and value to 70\n");
   n = 0;
   XtSetArg(args[n], XmNsliderSize, 40); n++;
   XtSetArg(args[n], XmNvalue, 70); n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   CommonPause();

   printf("changing the maximum to 90 and value to 60\n");
   n = 0;
   XtSetArg(args[n], XmNmaximum, 90); n++;
   XtSetArg(args[n], XmNvalue, 60); n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   CommonPause();

   printf("changing the value to 50\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 50); n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   CommonPause();

   printf("changing the maximum to 80\n");
   n = 0;
   XtSetArg(args[n], XmNmaximum, 80);	n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   CommonPause();

   printf ("changing the value to 0 and the min to 10\n");
   n = 0;
   XtSetArg(args[n], XmNvalue, 0);	n++;
   XtSetArg(args[n], XmNminimum, 10);	n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   CommonPause();

   printf("changing the min to 20\n");
   n = 0;
   XtSetArg(args[n], XmNminimum, 20);	n++;
   XtSetValues(scrollbar, args, n);
   DumpData(scrollbar);
   XtAddCallback (scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
   XtAddCallback (scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
   CommonPause();

   XtDestroyWidget(scrollbar);
   XtDestroyWidget(frame);
   CommonPause();
   XtAppMainLoop(app_context);
}

static void ScrollCallback (sbw, closure, call_data)
XmScrollBarWidget sbw;
XtPointer closure;
XtPointer call_data;

{
  int value;
  int reason;
  int pixel;
  Arg args[10];
  int n;

  XmScrollBarCallbackStruct * call_value = 
    (XmScrollBarCallbackStruct *) call_data;

  reason = call_value -> reason;
  value = call_value -> value;
  pixel = call_value -> pixel;

  switch (reason)
   {
      case XmCR_VALUE_CHANGED:
         printf ("Reason = XmCR_VALUE_CHANGED,	Value = %d", value);
      break;

      case XmCR_INCREMENT:
         printf ("Reason = XmCR_INCREMENT,	Value = %d", value);
      break;

      case XmCR_DECREMENT:
         printf ("Reason = XmCR_DECREMENT,	Value = %d", value);
      break;

      case XmCR_PAGE_INCREMENT:
         printf ("Reason = XmCR_PAGE_INCREMENT,	Value = %d", value);
      break;

      case XmCR_PAGE_DECREMENT:
         printf ("Reason = XmCR_PAGE_DECREMENT,	Value = %d", value);
      break;

      case XmCR_TO_TOP:
         printf ("Reason = XmCR_TO_TOP,	Value = %d,	Pixel = %d\n",
                 value, pixel);
      break;

      case XmCR_TO_BOTTOM:
         printf ("Reason = XmCR_TO_BOTTOM,	Value = %d,	Pixel = %d\n",
                 value, pixel);
      break;

      case XmCR_DRAG:
         printf ("Reason = XmCR_DRAG,	Value = %d", value);
      break;

      case XmCR_HELP:
         printf ("Reason = XmCR_HELP,	Value = %d\n", value);
      break;

      default:
         printf ("Hit the default, incorrect reason sent!!\n");
      break;

   }

  n = 0;
  XtSetArg (args[n], XmNvalue, &value);	n++;
  XtGetValues ((Widget) sbw, args, n);
  printf (",   GetValues value = %d\n", value);
}

void DumpData (sbw)
Widget sbw;
{
  Arg args[10];
  int n;
  int minimum;
  int maximum;
  int value;
  int slider_size;
   
  n = 0;
  XtSetArg (args[n], XmNminimum, &minimum);	n++;
  XtSetArg (args[n], XmNmaximum, &maximum);	n++;
  XtSetArg (args[n], XmNvalue, &value);		n++;
  XtSetArg (args[n], XmNsliderSize, &slider_size);	n++;
  XtGetValues (sbw, args, n);
  printf ("min = %d,   max = %d,   value = %d,  slider size = %d\n\n",
	  minimum, maximum, value, slider_size);
}
