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
static char rcsid[] = "$TOG: Scrollbar9.c /main/8 1999/01/15 12:36:59 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a vertical scrollbars with various incorrect data.
 *  Ensure that the display and error messages are correct.
 *
 ************************************************************************/

#include <X11/StringDefs.h>
#include <testlib.h>

static void ScrollCallback();

void DumpData(sbw)
Widget sbw;
{
   Arg args[10];
   int n;
   int minimum;
   int maximum;
   int value;
   int slider_size;
   
   n = 0;
   XtSetArg(args[n], XmNminimum, &minimum);	n++;
   XtSetArg(args[n], XmNmaximum, &maximum);	n++;
   XtSetArg(args[n], XmNvalue, &value);		n++;
   XtSetArg(args[n], XmNsliderSize, &slider_size);	n++;
   XtGetValues(sbw, args, n);
   printf("min = %d,   max = %d,   value = %d,  slider size = %d\n\n",
            minimum, maximum, value, slider_size);
}

void main(argc, argv)
int argc;
char **argv;
{
  Widget frame;
  Widget scrollbar;
  Arg args[10];
  int n, i;

  CommonTestInit(argc, argv);

  frame = XmCreateFrame(Shell1, "frame", NULL, 0);
  XtManageChild(frame);

  XtRealizeWidget(Shell1);

  printf("creating with the slider size to 40 and value to 70\n");
  n = 0;
  XtSetArg(args[n], XmNsliderSize, 40);	n++;
  XtSetArg(args[n], XmNvalue, 70);		n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNheight, 400);				n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
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
  XtRealizeWidget(scrollbar);	/* to make geo mgmt happy */
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
  DumpData(scrollbar);

  CommonPause();
  XtDestroyWidget(scrollbar); 

  printf("creating with the value of 110\n");
  n = 0;
  XtSetArg(args[n], XmNvalue, 110);	n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNheight, 400);				n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtRealizeWidget(scrollbar);	/* to make geo mgmt happy */
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
  DumpData(scrollbar);

  CommonPause();
  XtDestroyWidget(scrollbar); 

  printf("creating with the maximum of 5\n");
  n = 0;
  XtSetArg(args[n], XmNmaximum, 5);	n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNheight, 400);				n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtRealizeWidget(scrollbar);	/* to make geo mgmt happy */
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
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
  XtRealizeWidget(scrollbar);	/* to make geo mgmt happy */
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
  DumpData(scrollbar);

  CommonPause();
  XtDestroyWidget(scrollbar); 

  printf("creating with the min to 20\n");
  n = 0;
  XtSetArg(args[n], XmNminimum, 20);	n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNheight, 400);				n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtRealizeWidget(scrollbar);	/* to make geo mgmt happy */
  XtManageChild(scrollbar);
  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
  DumpData(scrollbar);

  CommonPause();

  XtDestroyWidget(scrollbar);
  XtDestroyWidget(frame);
  CommonPause();
  XtAppMainLoop(app_context);
}

static void ScrollCallback(sbw, closure, call_data)
XmScrollBarWidget sbw;
caddr_t closure;
caddr_t call_data;
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

  switch(reason)
   {
   case XmCR_VALUE_CHANGED:
     printf("Reason = XmCR_VALUE_CHANGED,	Value = %d", value);
     break;

   case XmCR_HELP:
     printf("Reason = XmCR_HELP,	Value = %d\n", value);
     break;

   default:
     printf("Hit the default, incorrect reason sent!!\n");
     break;

   }

  n = 0;
  XtSetArg(args[n], XmNvalue, &value);	n++;
  XtGetValues((Widget)sbw, args, n);
  printf(",   GetValues value = %d\n", value);
}
