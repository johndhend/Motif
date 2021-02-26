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
static char rcsid[] = "$XConsortium: RowCol1.c /main/9 1995/07/13 18:54:12 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.4              *
*       Thu Apr 13 16:39:54 1989        *
****************************************/

#include <testlib.h>

/*  Global Variables  */
Widget button1, button2, popup;
Widget RowColumn1;
Widget ArrowButton1;
Widget Label1;
Widget PushButton1;
Widget ToggleButton1, ToggleButton2;
Pixmap Leatherette;

/*  Private Functions  */
static Pixel GetPixel();

/*  Pixmap  */
#define Leatherette_width 16
#define Leatherette_height 16
static char Leatherette_bits[] = {
   0x00, 0xc0, 0x20, 0xc8, 0x00, 0x98, 0x80, 0xf1, 0x30, 0xc5, 0x04, 0xdd,
   0x00, 0xf9, 0x38, 0xfb, 0x60, 0xe2, 0xc1, 0xff, 0x14, 0xdf, 0x75, 0xf3,
   0x64, 0xfe, 0xec, 0xff, 0xe9, 0xfb, 0xff, 0xff
   };

void genericCallback();
void buttonCB();

int main(int argc, char **argv)
{
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  CommonTestInit(argc, argv);
    
  /* Add test for PIR 4287 */
  
  n = 0;	
  XtSetArg(args[n], XmNentryAlignment, XmALIGNMENT_CENTER); n++;
  XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNnumColumns, 1); n++;
  
  RowColumn1 = XmCreateRowColumn(Shell1, "RowColumn1", args, n);
  XtManageChild(RowColumn1);

  n = 0;
  XtSetArg(args[n], XmNwidth, 200); n++;
  XtSetArg(args[n], XmNrecomputeSize, False); n++;
  button1 = XmCreatePushButton(RowColumn1, "button1", args, n);
  XtManageChild(button1);
  XtAddCallback(button1, XmNactivateCallback, buttonCB, (XtPointer)0);

  n = 0;
  XtSetArg(args[n], XmNwidth, 200); n++;
  XtSetArg(args[n], XmNrecomputeSize, False); n++;
  button2 = XmCreatePushButton(RowColumn1, "button2", args, n);
  XtManageChild(button2);
  XtAddCallback(button2, XmNactivateCallback, buttonCB, (XtPointer)0);
  XtRealizeWidget(Shell1);

  CommonPause();

  XtDestroyWidget(RowColumn1);

  n = 0;
  XtSetArg(args[n], XmNadjustLast, FALSE);  n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
  XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);  n++;
  XtSetArg(args[n], XmNnumColumns, 2);  n++;
  XtSetArg(args[n], XmNborderWidth, 10);  n++;
  RowColumn1 = XmCreateRowColumn(Shell1, "RowColumn1", args, n);
  XtManageChild(RowColumn1);

  n = 0;
  ArrowButton1 = XmCreateArrowButton(RowColumn1, "ArrowButton1", args, n);
  XtManageChild(ArrowButton1);

  n = 0;
  Label1 = XmCreateLabel(RowColumn1, "Label1", args, n);
  XtManageChild(Label1);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, True);  n++;
  XtSetArg(args[n], XmNarmColor, CommonGetColor("red"));  n++;
  PushButton1 = XmCreatePushButton(RowColumn1, "PushButton1", args, n);
  XtManageChild(PushButton1);

  CommonPause();

  n = 0;
  ToggleButton1 = XmCreateToggleButton(RowColumn1, "ToggleButton1", args, n);
  XtManageChild(ToggleButton1);

  CommonPause();
  
  Leatherette = 
    XCreatePixmapFromBitmapData(display,
				DefaultRootWindow (display), Leatherette_bits,
				Leatherette_width, Leatherette_height,
				CommonGetColor("black"), 
				CommonGetColor("yellow"),
				DefaultDepth (display, 
					      DefaultScreen (display)));

  n = 0;
  XtSetArg(args[n], XmNbackgroundPixmap, Leatherette);  n++;
  XtSetValues(RowColumn1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNmarginWidth, 20);  n++;
  XtSetArg(args[n], XmNmarginHeight, 20);  n++;
  XtSetValues(RowColumn1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNspacing, 20);  n++;
  XtSetValues(RowColumn1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNentryBorder, 20);  n++;
  XtSetValues(RowColumn1, args, n);

  /* to test P1697, set up callbacks and have user click in entry border */

  XtAddCallback(ArrowButton1, XmNactivateCallback, genericCallback, NULL);
  XtAddCallback(PushButton1, XmNactivateCallback, genericCallback, NULL);
  XtAddCallback(ToggleButton1, XmNvalueChangedCallback, genericCallback, NULL);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNnumColumns, 4);  n++;
  XtSetValues(RowColumn1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_TIGHT);  n++;
  XtSetValues(RowColumn1, args, n);
  
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNadjustLast, TRUE);  n++;
  XtSetArg(args[n], XmNresizeWidth, FALSE);  n++;
  XtSetArg(args[n], XmNresizeHeight, FALSE);  n++;
  XtSetValues(RowColumn1, args, n);

  CommonPause();

  CommonPause();  /* Exit */

  XtAppMainLoop(app_context);
}

void buttonCB(Widget w, XtPointer client, XtPointer call)
{
  Arg arg;

  XtSetArg(arg, XmNlabelString, XmStringCreateSimple("a"));
  XtSetValues(w, &arg, 1);
  return;
}


void genericCallback(Widget w, caddr_t client_data, caddr_t call_data)
{

  if (((XmAnyCallbackStruct *)call_data)->reason == XmCR_ACTIVATE)
    printf ("Activation Callback was received.\n");

  if (((XmAnyCallbackStruct *)call_data)->reason == XmCR_VALUE_CHANGED)
    { 
      printf ("Value Changed Callback was received.\n");
      printf (" State check: button is %s\n\n",
	      ((XmToggleButtonGetState(w)) ? "ON" : "OFF"));
    }
  fflush (stdout);

}
