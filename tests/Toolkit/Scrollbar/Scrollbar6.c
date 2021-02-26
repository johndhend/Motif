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
static char rcsid[] = "$TOG: Scrollbar6.c /main/8 1999/01/15 12:35:43 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a horizontal scrollbar with reverse processing direction
 *
 ************************************************************************/

#include <X11/StringDefs.h>
#include <testlib.h>

static void ScrollCallback(Widget,XtPointer,XtPointer);
static void CreateControlPanel();
static void SliderMarkCB(Widget,XtPointer,XtPointer);
static void SliderVisualCB(Widget,XtPointer,XtPointer);

Widget scrollbar;

void main(argc, argv)
int argc;
char **argv;
{
  Widget frame;
  Arg args[10];
  int n;

  CommonTestInit(argc, argv);
    
  frame = XmCreateFrame(Shell1, "frame", NULL, 0);
  XtManageChild(frame);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_LEFT); n++;
  XtSetArg(args[n], XmNheight, 50); n++;
  XtSetArg(args[n], XmNwidth, 250); n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtManageChild(scrollbar);

  n = 0;
  XtSetArg(args[n], XmNvalue, 20);          n++;
  XtSetValues(scrollbar, args, n);

  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNpageIncrementCallback, ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNpageDecrementCallback, ScrollCallback, NULL); 
  
  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();

  /* Change orientation to Vertical and re-do testing */

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);	n++;
  XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);	n++;
  XtSetArg(args[n], XmNheight, 250);			n++;
  XtSetArg(args[n], XmNwidth, 50);			n++;
  XtSetValues(scrollbar, args, n);

  CommonPause();
  CommonPause();	

  /* Test slider visuals */
  CreateControlPanel();
  
  n = 0;
  XtSetArg(args[n], XmNslidingMode, XmSLIDER);	n++;
  XtSetValues(scrollbar, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNslidingMode, XmTHERMOMETER);	n++;
  XtSetValues(scrollbar, args, n);
  CommonPause();

  XtDestroyWidget(scrollbar);
  XtDestroyWidget(frame);
  CommonPause();
  XtAppMainLoop(app_context);
}


static void 
ScrollCallback(Widget w, XtPointer closure, XtPointer call_data)
{
   XmScrollBarWidget sbw = (XmScrollBarWidget)w;
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

      case XmCR_PAGE_INCREMENT:
         printf("Reason = XmCR_PAGE_INCREMENT,	Value = %d", value);
      break;

      case XmCR_PAGE_DECREMENT:
         printf("Reason = XmCR_PAGE_DECREMENT,	Value = %d", value);
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

static void
CreateControlPanel()
{
   Widget FormD1;
   Widget RowC1, RowC2, header;
   Widget RCToggle[4];
   Arg    args[20];
   int    n, i;

   static char          *mark_labels[] = 
                         { "XmNONE",
			   "XmETCHED_LINE",
			   "XmTHUMB_MARK",
			   "XmROUND_MARK"};

  
   static char          *visual_labels[] = 
                         { "XmBACKGROUND_COLOR",
			   "XmFOREGROUND_COLOR",
			   "XmTROUGH_COLOR",
			   "XmSHADOWED_BACKGROUND"};

  
   XmString LabelString;
   char     name[20];

   /* Create main parent */ 
   
   n=0;
   XtSetArg(args[n], XmNdefaultPosition, False); n++;
   XtSetArg(args[n], XmNautoUnmanage, False); n++;
   XtSetArg(args[n], XmNx, 10); n++;
   XtSetArg(args[n], XmNy, 400); n++;
   FormD1 = XmCreateFormDialog (Shell1, "FormD1", args, n);
   XtManageChild (FormD1);

   LabelString = XmStringCreate("Slider mark",XmSTRING_DEFAULT_CHARSET);
   n=0;
   XtSetArg(args[n], XmNlabelString, LabelString); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   header = XmCreateLabel (FormD1, "header1", args, n);
   XtManageChild (header);
   XmStringFree(LabelString);

   /* Create Radio box to contain the Toggle widgets */
   n=0;
   XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
   XtSetArg(args[n], XmNnumColumns, 1); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNtopWidget, header); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   RowC1 = XmCreateRadioBox (FormD1, "RowC1", args, n);
   XtManageChild (RowC1);

   /* Create the different toggle widgets */

   for (i=0; i<4; i++)
     {
	LabelString = XmStringCreate(mark_labels[i],XmSTRING_DEFAULT_CHARSET);
	sprintf (name, "RCMark%d", i+1);
	n=0;
	XtSetArg(args[n], XmNlabelString, LabelString); n++;

	RCToggle[i] = XmCreateToggleButton(RowC1, name, args, n);
	XtAddCallback(RCToggle[i], XmNvalueChangedCallback, 
		      SliderMarkCB, (XtPointer) (long) i);
	XtManageChild(RCToggle[i]);
	
	XmStringFree(LabelString);

     }
   
   LabelString = XmStringCreate("Slider visual",XmSTRING_DEFAULT_CHARSET);
   n=0;
   XtSetArg(args[n], XmNlabelString, LabelString); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftWidget, RowC1); n++;
   header = XmCreateLabel (FormD1, "header2", args, n);
   XtManageChild (header);
   XmStringFree(LabelString);

   /* Create Radio box to contain the Toggle widgets */
   n=0;
   XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
   XtSetArg(args[n], XmNnumColumns, 1); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNtopWidget, header); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNleftWidget, RowC1); n++;
   RowC2 = XmCreateRadioBox (FormD1, "RowC2", args, n);
   XtManageChild (RowC2);

   /* Create the different toggle widgets */

   for (i=0; i<4; i++)
     {
	LabelString = XmStringCreate(visual_labels[i],
				     XmSTRING_DEFAULT_CHARSET);
	sprintf (name, "RCVisual%d", i+1);
	n=0;
	XtSetArg(args[n], XmNlabelString, LabelString); n++;

	RCToggle[i] = XmCreateToggleButton(RowC2, name, args, n);
	XtAddCallback(RCToggle[i], XmNvalueChangedCallback, 
		      SliderVisualCB, (XtPointer) (long) i);
	XtManageChild(RCToggle[i]);
	
	XmStringFree(LabelString);

     }
   
}


static void 
SliderMarkCB(Widget w, XtPointer client_data, XtPointer call_data)
{
   Arg       args[20];
   int       n;
   XmToggleButtonCallbackStruct * scb = 
	(XmToggleButtonCallbackStruct *) call_data ;

   if (scb->set) {
     n=0;
     XtSetArg(args[n], XmNsliderMark, (XtEnum) (int) client_data); n++;
     XtSetValues(scrollbar, args, n);
   }
}

static void 
SliderVisualCB(Widget w, XtPointer client_data, XtPointer call_data)
{
   Arg       args[20];
   int       n;
   XmToggleButtonCallbackStruct * scb = 
	(XmToggleButtonCallbackStruct *) call_data ;

   if (scb->set) {
     n=0;
     XtSetArg(args[n], XmNsliderVisual, (XtEnum) (int) client_data); n++;
     XtSetValues(scrollbar, args, n);
   }
}

