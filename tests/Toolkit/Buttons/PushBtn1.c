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
static char rcsid[] = "$XConsortium: PushBtn1.c /main/9 1995/07/13 17:30:13 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*       Mon Mar 27 08:42:59 1989        *
****************************************/

#include <testlib.h>

#include "mtn.bmp"
#include "gnu.bmp"

Pixmap px_disarm, px_armed, pixmap1;
static Pixel GetPixel();


#define wwang_width 16
#define wwang_height 16
static char wwang_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
   0x80, 0x01, 0x80, 0x01, 0xf0, 0x0f, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
   0x80, 0x01, 0x80, 0x01, 0xfe, 0x7f, 0x00, 0x00};

Widget  PushButton1 = NULL, da = NULL, oneButton = NULL, twoButton;
Boolean mywait;

void  HelpPB();
void  ArmPB();
void  DisarmPB();
void  ActPB();

void click1CB( Widget w, XtPointer d1, XtPointer d2)
{
  Arg args[10];
  int n = 0;

  XtSetArg(args[0], XmNbackgroundPixmap, pixmap1);
  XtSetValues(da, args, 1);
}

void clickCB( Widget w, XtPointer d1, XtPointer d2)
{
  Arg args[10];
  int n = 0;
  XtSetArg(args[0], XmNbackgroundPixmap, XmUNSPECIFIED_PIXMAP);
  XtSetValues(da, args, 1);
}


void  main (argc, argv)
int     argc;
char  **argv;
{
  int                delay = 0;
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XWindowAttributes  info;
  XEvent             DummyEvent;
  Pixel 	     fg, bg;
  XmString           string;
  int		     width, height, x_hot, y_hot;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);
    
  XtRealizeWidget(Shell1);

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, False);  n++;
  PushButton1 = XmCreatePushButton(Shell1, "PushButton1", args, n);
  XtManageChild(PushButton1);
  
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, TRUE);  n++;
  XtSetArg(args[n], XmNarmColor, CommonGetColor("yellow")); n++;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE); n++;
  XtSetArg(args[n], XmNhighlightThickness, 20); n++;
  XtSetValues(PushButton1, args, n);

  /* add callbacks for help, select, arm, disarm */
  XtAddCallback(PushButton1, XmNhelpCallback, HelpPB, NULL);
  XtAddCallback(PushButton1, XmNactivateCallback, ActPB, NULL);
  XtAddCallback(PushButton1, XmNarmCallback, ArmPB, NULL);
  XtAddCallback(PushButton1, XmNdisarmCallback, DisarmPB, NULL);
    
  CommonPause();

  /* change so that button displays a pixmap on arm */

  px_disarm =
    XCreatePixmapFromBitmapData(display, 
				DefaultRootWindow(display),
				mtn_bits, mtn_width, mtn_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));
  px_armed = 
    XCreatePixmapFromBitmapData(display, 
				DefaultRootWindow(display),
				gnu_bits, gnu_width, gnu_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));
  n = 0;
  XtSetArg(args[n], XmNlabelType, XmPIXMAP);  n++;
  XtSetArg(args[n], XmNlabelPixmap, px_disarm);  n++;
  XtSetArg(args[n], XmNarmPixmap, px_armed);  n++;
  XtSetArg(args[n], XmNhighlightOnEnter, False); n++;
  XtSetArg(args[n], XmNhighlightThickness, 0); n++;
  XtSetArg(args[n], XmNwidth, 100 );
  XtSetArg(args[n], XmNheight, 60 );
  XtSetValues(PushButton1, args, n);

  CommonPause();

  XtDestroyWidget(PushButton1);

  fg = BlackPixel(display, DefaultScreen(display));
  bg = WhitePixel(display, DefaultScreen(display));
  pixmap1 = XCreatePixmapFromBitmapData(display, 
		   XDefaultRootWindow(display), wwang_bits,
		   16, 16, fg, bg, 
		   DefaultDepth(display, DefaultScreen(display)));

  n = 0;
  XtSetArg(args[n], XmNwidth, 400); n++;
  XtSetArg(args[n], XmNheight, 400); n++;
  XtSetArg(args[n], XmNbackgroundPixmap, pixmap1); n++;
  da = XmCreateDrawingArea(Shell1, "da", args, n);
  XtManageChild(da);

  n = 0;
  string = XmStringCreate("Push to change to XmUNSPECIFIED_PIXMAP", 
			  XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, string); n++;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 90); n++;
  XtSetArg(args[n], XmNhighlightThickness, 7); n++;
  oneButton = XmCreatePushButton(da, "oneButton", args, n);
  XtAddCallback(oneButton, XmNactivateCallback, clickCB, NULL);
  XtManageChild(oneButton);
  XmStringFree(string);

  n = 0;
  string = XmStringCreate("Push to change to the pixmap",
			  XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, string); n++;
  XtSetArg(args[n], XmNx, 10); n++;
  XtSetArg(args[n], XmNy, 200); n++;
  twoButton = XmCreatePushButton(da, "twoButton", args, n);
  XtAddCallback(twoButton, XmNactivateCallback, click1CB, NULL);
  XtManageChild(twoButton);
  XmStringFree(string);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNshadowThickness, 10); n++;
  XtSetValues(oneButton, args, n);
  XtSetValues(twoButton, args, n);

  XmChangeColor(oneButton, CommonGetColor("Red"));
  XmChangeColor(twoButton, CommonGetColor("Red"));

  CommonPause();

  XmChangeColor(oneButton, CommonGetColor("Green"));
  XmChangeColor(twoButton, CommonGetColor("Green"));

  CommonPause();

  XmChangeColor(oneButton, CommonGetColor("Blue"));
  XmChangeColor(twoButton, CommonGetColor("Blue"));

  CommonPause();

  XmChangeColor(oneButton, CommonGetColor("Yellow"));
  XmChangeColor(twoButton, CommonGetColor("Yellow"));

  CommonPause();

  XmChangeColor(oneButton, CommonGetColor("Pink"));
  XmChangeColor(twoButton, CommonGetColor("Pink"));

  CommonPause();

  XtAppMainLoop(app_context);
}

static void  flushEvents(delay)
int    delay;
{
  XEvent event;

  XSync(display, False);
  while (XtAppPending(app_context)) {
    XtAppNextEvent(app_context, &event);
    XtDispatchEvent(&event);
  }

  sleep(delay);
}

void  HelpPB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("HELP: Just click on the button to select,\n");
    printf("      Press on the button to arm.\n");
}

void  ActPB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    XmAnyCallbackStruct *cb;
    XEvent *ev;

    cb = (XmAnyCallbackStruct *) call_data;
    ev = cb->event;

    if (cb->event == NULL)
	printf ("Event is NULL!\n");
    else
	printf ("Event is %d.\n", ev->type);

}

void  ArmPB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButton Armed\n");
}

void  DisarmPB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;
{
    printf("PushButton Disarmed\n");
}


