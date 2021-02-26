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
static char rcsid[] = "$TOG: Scrollbar8.c /main/7 1999/01/15 12:36:34 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a vertical scrollbar and test out the XmGetScrollBarValues
 *  XmSetScrollBarValues external functions.
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
  int i;
  int value, slider_size, increment, page_increment;
  Boolean notify = False;

  CommonTestInit(argc, argv);
    
  frame = XmCreateFrame(Shell1, "frame", NULL, 0);
  XtManageChild(frame);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);	n++;
  XtSetArg(args[n], XmNheight, 250);				n++;
  XtSetArg(args[n], XmNwidth, 50);				n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtManageChild(scrollbar);

  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);

  XtRealizeWidget(Shell1);

  value = 0;
  slider_size = 10;
  increment = 1;
  page_increment = 10;

  for(i = 0; i < 5; i ++)
    {
      XmScrollBarSetValues(scrollbar, value, slider_size, 
			   increment, page_increment, notify);
      if(notify == False) notify = True;
      else notify = False;
      XmScrollBarGetValues(scrollbar, &value, &slider_size, 
                            &increment, &page_increment);
      printf("value = %d,  slider_size = %d,  incr = %d,  page_incr = %d\n\n",
              value, slider_size, increment, page_increment);
      value += 10;
      slider_size += 10;
      increment += 4;
      page_increment += 5;
      CommonPause();
    }

  XtDestroyWidget(scrollbar);
  XtDestroyWidget(frame);

  CommonPause();

  XtAppMainLoop(app_context);
}

void ScrollCallback(sbw, closure, call_data)
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
   XtGetValues((Widget) sbw, args, n);
   printf(",   GetValues value = %d\n", value);
}
