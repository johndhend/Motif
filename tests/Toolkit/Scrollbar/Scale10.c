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
static char rcsid[] = "$XConsortium: Scale10.c /main/8 1995/07/13 19:11:04 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/* 
	The problems: (Pirs 865, 902)

	* setting scaleHeight of horizontal widget shrinks
	  width down to 100; 

	* setting scaleWidth of vertical widget shrinks
	  height down to 100; 
*/


/* Scale set value test */

#include <testlib.h>

Arg args[MAX_ARGS];
int	n;

static void set_scale_height (Widget w, XtPointer client_data, XtPointer
	call_data) 
{
   n = 0;
   XtSetArg(args[n], XmNscaleHeight, 50);  n++;
   XtSetValues((Widget)client_data, args, n);
}


static void set_scale_width(Widget w, XtPointer client_data, XtPointer
	call_data) 
{
   n = 0;
   XtSetArg(args[n], XmNscaleWidth, 50);  n++;
   XtSetValues((Widget)client_data, args, n);
}

static void valueChangedProc(Widget w, XtPointer client_data, XtPointer
	call_data) 
{
	XmScaleCallbackStruct *eventStruct;
	static int oldValue = 0;
	int newValue;

	eventStruct = (XmScaleCallbackStruct *) call_data;
	newValue = eventStruct->value;
	printf ("Old value was %d, new value is %d\n", oldValue, newValue);
	oldValue = newValue;
	fflush (stdout);
}


void main (argc, argv)
int argc;
char **argv;
{
   Widget bb, scale1, scale2;
   Widget pb1, pb2, pb3, pb4;
   Display *display;
   XmString	tcs;


   CommonTestInit(argc, argv);
    

   n=0;
   XtSetArg(args[n], XmNwidth, 455);  n++;
   XtSetArg(args[n], XmNheight, 490);  n++;
   bb = XmCreateBulletinBoard(Shell1, "bb", args, n);
   XtManageChild(bb);

   n = 0;
   XtSetArg(args[n], XmNwidth, 375);  n++;
   XtSetArg(args[n], XmNheight, 75);  n++;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
   XtSetArg(args[n], XmNshowValue, True);  n++;
   XtSetArg(args[n], XmNvalue, 44);  n++;
   XtSetArg(args[n], XmNscaleWidth, 375);  n++;
   XtSetArg(args[n], XmNscaleHeight, 30);  n++;
   scale1 = XmCreateScale(bb, "scale1", args, n);
   XtManageChild(scale1);

   XtAddCallback(scale1, XmNvalueChangedCallback, 
		 (XtCallbackProc) valueChangedProc, NULL);

   n = 0;
   XtSetArg(args[n], XmNy, 100); n++;
   XtSetArg(args[n], XmNwidth, 75);  n++;;
   XtSetArg(args[n], XmNheight, 375);  n++;;
   XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;;
   XtSetArg(args[n], XmNshowValue, True); n++;
   XtSetArg(args[n], XmNvalue, 66); n++;
   XtSetArg(args[n], XmNscaleWidth, 30);  n++;;
   XtSetArg(args[n], XmNscaleHeight, 375);  n++;;
   scale2 = XmCreateScale(bb, "scale2", args, n);
   XtManageChild(scale2);

   tcs = XmStringCreateLtoR("Horiz scaleHeight to 50",
	XmSTRING_DEFAULT_CHARSET);
   n = 0;
   XtSetArg(args[n], XmNx, 100);  n++;;
   XtSetArg(args[n], XmNy, 100);  n++;;
   XtSetArg(args[n], XmNlabelString, tcs);  n++;
   pb1 = XmCreatePushButton(bb, "pb1", args, n);
   XtManageChild(pb1);
   XtAddCallback(pb1, XmNactivateCallback,
	set_scale_height, (XtPointer)scale1);
   XmStringFree(tcs);

   tcs = XmStringCreateLtoR("Vert scaleHeight to 50",
	XmSTRING_DEFAULT_CHARSET);
   n = 0;
   XtSetArg(args[n], XmNx, 100);  n++;;
   XtSetArg(args[n], XmNy, 130);  n++;;
   XtSetArg(args[n], XmNlabelString, tcs);  n++;
   pb2 = XmCreatePushButton(bb, "pb2", args, n);
   XtManageChild(pb2);
   XtAddCallback(pb2, XmNactivateCallback,
	set_scale_height, (XtPointer)scale2);
   XmStringFree(tcs);

   tcs = XmStringCreateLtoR("Horiz scaleWidth to 50",
	XmSTRING_DEFAULT_CHARSET);
   n = 0;
   XtSetArg(args[n], XmNy, 100);  n++;;
   XtSetArg(args[n], XmNx, 300);  n++;;
   XtSetArg(args[n], XmNlabelString, tcs);  n++;
   pb3 = XmCreatePushButton(bb, "pb3", args, n);
   XtManageChild(pb3);
   XtAddCallback(pb3, XmNactivateCallback,
	set_scale_width, (XtPointer)scale1);
   XmStringFree(tcs);

   tcs = XmStringCreateLtoR("Vert scaleWidth to 50",
	XmSTRING_DEFAULT_CHARSET);
   n=0;
   XtSetArg(args[n], XmNy, 130);  n++;;
   XtSetArg(args[n], XmNx, 300);  n++;;
   XtSetArg(args[n], XmNlabelString, tcs);  n++;
   pb4 = XmCreatePushButton(bb, "pb4", args, n);
   XtManageChild(pb4);
   XtAddCallback(pb4, XmNactivateCallback,
	set_scale_width, (XtPointer)scale2);
   XmStringFree(tcs);

   XtRealizeWidget(Shell1);

   CommonPause();

   XtAppMainLoop(app_context);
}
