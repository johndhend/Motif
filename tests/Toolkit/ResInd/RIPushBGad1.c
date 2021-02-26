/* $XConsortium: RIPushBGad1.c /main/4 1995/07/15 21:09:11 drk $ */
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

/****************************************
*   Automatic test program generation   *
*              Version 1.2              *
*       Wed Apr  5 12:26:41 1989        *
****************************************/

#include <testlib.h>
#include "gnu.bmp"
Pixmap gnumap;

void ActCB_MC();

/*  Global Variables  */
Widget    Frame1;
Widget    PBGadget1;

/*  Private Functions  */

void	ArmCB();
void	DisarmCB();
void	ActCB();

void  main (argc, argv)
int     argc;
char  **argv;
{
  Boolean trace = False;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;
  Dimension newH,newW;
  Pixel red_pixel;
  XmString string;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget(Shell1);

  n = 0;
  Frame1 = XmCreateFrame(Shell1, "Frame1", args, n); 
  XtManageChild(Frame1);

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, False); n++;
  XtSetArg(args[n], XmNmultiClick, XmMULTICLICK_KEEP); n++;
  string = XmStringLtoRCreate("Push Gadget Here", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelType, XmSTRING); n++; 
  XtSetArg(args[n], XmNlabelString, string); n++; 
  PBGadget1 = XmCreatePushButtonGadget(Frame1, "PBGadget", args, n);
  XtManageChild(PBGadget1);

  /* add callbacks for select, arm, disarm */
  XtAddCallback(PBGadget1, XmNactivateCallback, ActCB_MC, NULL);
  XtAddCallback(PBGadget1, XmNarmCallback, ArmCB, NULL);
  XtAddCallback(PBGadget1, XmNdisarmCallback, DisarmCB, NULL);
    
  /* Reset margins */
  n = 0;
  XtSetArg(args[n], XmNmarginHeight, 20); n++;
  XtSetArg(args[n], XmNmarginWidth, 20); n++;
  XtSetValues(PBGadget1, args, n);
  CommonPause(); /*multiclick tests */

  n = 0;
  XtSetArg(args[n], XmNmultiClick, XmMULTICLICK_DISCARD); n++;
  XtSetValues(PBGadget1, args, n);

  CommonPause();
  
  XtRemoveCallback(PBGadget1, XmNactivateCallback, ActCB_MC, NULL);
  XtAddCallback(PBGadget1, XmNactivateCallback, ActCB, NULL);

  CommonPause();

  /* change so that button displays a pixmap */
  gnumap = 
    XCreatePixmapFromBitmapData(display,
				DefaultRootWindow(display),
				gnu_bits, gnu_width, gnu_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));

  n = 0;
  XtSetArg(args[n], XmNlabelType, XmPIXMAP);  n++;
  XtSetArg(args[n], XmNlabelPixmap, gnumap);  n++;
  XtSetValues(PBGadget1, args, n);

  CommonPause();

  red_pixel = CommonGetColor("red");

  /* Change units and reset the sizes - 1 mm margins */
  n = 0;
  XtSetArg(args[n], XmNfillOnArm, True); n++;
  XtSetArg(args[n], XmNarmColor, red_pixel); n++;
  XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS); n++;
  XtSetArg(args[n], XmNmarginWidth, 100); n++;
  XtSetArg(args[n], XmNmarginHeight, 100); n++;
  XtSetValues(PBGadget1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, False); n++;
  XtSetArg(args[n], XmNshowAsDefault, TRUE); n++;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE); n++;
  XtSetArg(args[n], XmNhighlightThickness, 5); n++;
  XtSetArg(args[n], XmNunitType, XmPIXELS); n++;
  XtSetArg(args[n], XmNmarginWidth, 10); n++;
  XtSetArg(args[n], XmNmarginHeight, 10); n++;
  tcs = XmStringLtoRCreate("PBG Label", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelType, XmSTRING);  n++;
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetValues(PBGadget1, args, n);
    
  CommonPause();

  XmStringFree(tcs);

  /* Try setting some illegal values - Also set highlight off */
  n = 0;
  XtSetArg(args[n], XmNhighlightOnEnter, False); n++;
  XtSetArg(args[n], XmNhighlightThickness, 0); n++;
  XtSetArg(args[n], XmNmarginHeight, 3.14159); n++;
  XtSetValues(PBGadget1, args, n);
  n = 0;
  XtSetArg(args[n], XmNwidth, &newW); n++;
  XtSetArg(args[n], XmNheight, &newH); n++;
  XtGetValues(PBGadget1, args, n);
  printf("PBG width and height are : %d, %d\n",newW,newH);

  CommonPause();

  /* now destroy the gadget to get more coverage */
  XtDestroyWidget(PBGadget1);

  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(Frame1);
  XtDestroyWidget(PBGadget1);
}

void  ActCB_MC(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButtonGadget Activated\n");
    printf ("Number of clicks is %d\n", 
	     ((XmPushButtonCallbackStruct*)call_data)->click_count);
    printf("*********************\n");
}


void  ActCB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButtonGadget Activated\n");
}


void  ArmCB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButtonGadget Armed\n");

}

void  DisarmCB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButtonGadget Disarmed\n");
    printf("*********************\n");
}

