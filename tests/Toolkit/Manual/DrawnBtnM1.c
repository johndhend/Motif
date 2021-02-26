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
static char rcsid[] = "$XConsortium: DrawnBtnM1.c /main/7 1995/07/13 18:35:38 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <signal.h>
#include "dp.bmp"

static void ReDrawCB(Widget w, XtPointer client_data, XtPointer call_data);

Widget RowColumn1 = NULL;
Widget DrawnButton1 = NULL;
Widget Separator1 = NULL;
Widget DrawnButton2 = NULL;
Widget Separator2 = NULL;
Widget DrawnButton3 = NULL;
Widget Separator3 = NULL;
Widget DrawnButton4 = NULL;
Widget Separator4 = NULL;

Pixmap nopanic;
GC db4gc;
XGCValues db4gcv;

static void ReDrawCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Arg args[MAX_ARGS];
  int n;
  static int srcx,srcy,destx,desty,pwid,phite;
  static int firstime = 1;
  int drawsize, border;
  Dimension bwidt, w_width, w_height;
  short hlthick, shthick;

  printf("ReDrawCB\n");

  /* if event was resize, or if this is the first time thru,
   * we need to recalculate the coordinates
   */

  if (((XmAnyCallbackStruct*)call_data)->reason == XmCR_RESIZE ||
      firstime ) 
    {
      firstime = 1;
      /* Get new size of widget */
      n=0;
      XtSetArg(args[n],XmNwidth,&w_width); n++;
      XtSetArg(args[n],XmNheight,&w_height); n++;
      XtSetArg(args[n],XmNborderWidth,&bwidt); n++;
      XtSetArg(args[n],XmNhighlightThickness,&hlthick); n++;
      XtSetArg(args[n],XmNshadowThickness,&shthick); n++;
      XtGetValues(w,args,n);

      /* calculate available drawing area, width 1st */
      border = bwidt + hlthick + shthick;
      
      /* 
       * See if window is bigger than pixmap (center it),
       *  or if pixmap is bigger (clip it) 
       */

      drawsize = w_width- 2*border;
      pwid = dont_panic_width;
      phite = dont_panic_height;

      if (drawsize > dont_panic_width){
	srcx = 0; 
	destx = (drawsize-dont_panic_width)/2 + border;
      }
      else {
	destx = border; 
	srcx = (dont_panic_width - drawsize)/2;
      }

      drawsize = w_height - 2*border;
      if (drawsize > dont_panic_height){
	srcy = 0;
	desty = (drawsize-dont_panic_height)/2 + border;
      }
      else {
	desty = border; 
	srcy = (dont_panic_height - drawsize)/2;
      }
    }

  /* now copy pixmap to widget window. */

  XCopyArea(XtDisplay(w),nopanic,XtWindow(w),db4gc,
	    srcx,srcy,pwid,phite,destx,desty);
}

void main (int argc, char **argv)
{
  register int       n;
  Arg                args[MAX_ARGS];
  XmString           tcs;
  XmFontList         fontlist;
  XFontStruct        *newfont;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++;
  XtSetArg(args[n], XmNheight, 100);  n++;
  XtSetValues(Shell1, args, n);
    
  newfont = XLoadQueryFont(display, "12x24");
  fontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);

  XtRealizeWidget(Shell1);

  /*   Define the pixmap from data */
  nopanic = 
    XCreatePixmapFromBitmapData(display,
				DefaultRootWindow(display), dont_panic_bits,
				dont_panic_width, dont_panic_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));
    
  n = 0;
  XtSetArg(args[n], XmNwidth, 100);  n++;
  XtSetArg(args[n], XmNheight, 100);  n++;
  XtSetArg(args[n], XmNpushButtonEnabled, TRUE);  n++;
  XtSetArg(args[n], XmNshadowThickness, 50); n++;
  XtSetArg(args[n], XmNfontList, fontlist); n++;
  tcs = XmStringCreateLtoR("supercalifragalixspelling", 
			   XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  DrawnButton4 = XmCreateDrawnButton(Shell1, "DrawnButton4", args, n);
  XtManageChild(DrawnButton4);
  
  /* add expose and resize callbacks */
  XtAddCallback(DrawnButton4,XmNexposeCallback,ReDrawCB,NULL);
  XtAddCallback(DrawnButton4,XmNresizeCallback,ReDrawCB,NULL);
    
  /* Get the graphics context needed by the callback */
  db4gc = XtGetGC(DrawnButton4, GCForeground | GCBackground, &db4gcv);
  
  CommonPause();
  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(DrawnButton4);
}
