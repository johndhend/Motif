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
static char rcsid[] = "$XConsortium: ToggleBtn4.c /main/4 1995/07/13 17:32:52 drk $"
#endif
#endif

/****************************************************************************
 *
 * This program tests the indicator dimensions - Changing pixmap sizes,
 * setting the indicator dimension for pixmaps, and changing the label in
 * a pulldown menu of toggle buttons. 
 *
 ****************************************************************************/
#include <testlib.h>
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

#define xlogo32_width 32
#define xlogo32_height 32
static char xlogo32_bits[] = {
   0xff, 0x00, 0x00, 0xc0, 0xfe, 0x01, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x60,
   0xf8, 0x07, 0x00, 0x30, 0xf8, 0x07, 0x00, 0x18, 0xf0, 0x0f, 0x00, 0x0c,
   0xe0, 0x1f, 0x00, 0x06, 0xc0, 0x3f, 0x00, 0x06, 0xc0, 0x3f, 0x00, 0x03,
   0x80, 0x7f, 0x80, 0x01, 0x00, 0xff, 0xc0, 0x00, 0x00, 0xfe, 0x61, 0x00,
   0x00, 0xfe, 0x31, 0x00, 0x00, 0xfc, 0x33, 0x00, 0x00, 0xf8, 0x1b, 0x00,
   0x00, 0xf0, 0x0d, 0x00, 0x00, 0xf0, 0x0e, 0x00, 0x00, 0x60, 0x1f, 0x00,
   0x00, 0xb0, 0x3f, 0x00, 0x00, 0x98, 0x7f, 0x00, 0x00, 0x98, 0x7f, 0x00,
   0x00, 0x0c, 0xff, 0x00, 0x00, 0x06, 0xfe, 0x01, 0x00, 0x03, 0xfc, 0x03,
   0x80, 0x01, 0xfc, 0x03, 0xc0, 0x00, 0xf8, 0x07, 0xc0, 0x00, 0xf0, 0x0f,
   0x60, 0x00, 0xe0, 0x1f, 0x30, 0x00, 0xe0, 0x1f, 0x18, 0x00, 0xc0, 0x3f,
   0x0c, 0x00, 0x80, 0x7f, 0x06, 0x00, 0x00, 0xff};

#define LARGE_width 16
#define LARGE_height 16
static char LARGE_bits[] = {
   0x03, 0xc0, 0x07, 0xe0, 0x0e, 0x70, 0x1c, 0x38, 0x38, 0x1c, 0x70, 0x0e,
   0Xe0, 0x07, 0x40, 0x02, 0x40, 0x02, 0xe0, 0x07, 0x70, 0x0e, 0x38, 0x1c,
   0x1c, 0x38, 0x0e, 0x70, 0x07, 0xe0, 0x03, 0xc0};

#define grid8_width 8
#define grid8_height 8
static char grid8_bits[] = {
   0x55, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00};

Pixmap pix[3];

void pbCB (widget, togglebutton, callData)
  Widget widget;
  XtPointer togglebutton;
  XtPointer callData;
{
  Cardinal n;
  Arg args[MAX_ARGS];
  Widget tb = (Widget)togglebutton;
  static int pix_num = 0;

  pix_num = (pix_num + 1) % 3;
  n = 0;
  XtSetArg(args[n], XmNlabelPixmap, pix[pix_num]); n++;
  XtSetValues(tb, args, n);
}

void tbCB (widget, moreinfo, callData)
  Widget widget;
  XtPointer moreinfo;
  XtPointer callData;
{
  Cardinal n;
  Arg args[MAX_ARGS];
  XmString original = XmStringCreateLocalized("Button_A");
  XmString new      = XmStringCreateLocalized("A New Label");
  XmString from_tb;

  n = 0;
  XtSetArg(args[n], XmNlabelString, &from_tb); n++;
  XtGetValues(widget, args, n);

  n = 0;
  XtSetArg(args[n], XmNset, True); n++;
  if (XmStringCompare(original, from_tb))
  {
    XtSetArg(args[n], XmNlabelString, new); n++;
  }
  else if (XmStringCompare(new, from_tb))
  {
    XtSetArg(args[n], XmNlabelString, original); n++;
  }
  else
  {
    printf("A horrible error occurred.  AAACCCCKKKK!!!\n\n");
    exit(0);
  }
  XtSetValues(widget, args, n);
}
  
void main (argc, argv)
int argc;
char **argv;
{
  Cardinal n;
  Arg args[MAX_ARGS];
  Widget rc, tb1, pb1;
  Widget menubar, pulldown, tb[4], cb1;
  static char labelstring[9] = "Button_A";
  XmString tcs;

  CommonTestInit(argc, argv);

/* Begin test for 4998 - Change the pixmaps to verify that the indicator
 * size changes to match the size of the new pixmap.
 */ 
  
  rc = XmCreateRowColumn(Shell1, "rc", NULL, 0);
  XtManageChild(rc);

  pix[0] = XCreatePixmapFromBitmapData(display, DefaultRootWindow(display),
				 grid8_bits, grid8_width, grid8_height,
				 WhitePixel(display, DefaultScreen(display)),
				 BlackPixel(display, DefaultScreen(display)),
				 DefaultDepth(display,DefaultScreen(display)));

  pix[1] = XCreatePixmapFromBitmapData(display, DefaultRootWindow(display),
                                 LARGE_bits, LARGE_width, LARGE_height,
                                 WhitePixel(display, DefaultScreen(display)),
                                 BlackPixel(display, DefaultScreen(display)),
                                 DefaultDepth(display,DefaultScreen(display)));

  pix[2] = XCreatePixmapFromBitmapData(display, DefaultRootWindow(display),
                                 xlogo32_bits, xlogo32_width, xlogo32_height,
                                 WhitePixel(display, DefaultScreen(display)),
                                 BlackPixel(display, DefaultScreen(display)),
                                 DefaultDepth(display,DefaultScreen(display)));

  n = 0;
  XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
  XtSetArg(args[n], XmNlabelPixmap, pix[0]); n++;
  tb1 = XmCreateToggleButton(rc, "tb1", args, n);
  XtManageChild(tb1);

  n = 0;
  tcs = XmStringCreateSimple("Cycle Pixmaps");
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  pb1 = XmCreatePushButton(rc, "pb1", args, n);
  XtManageChild(pb1);
  XtAddCallback(pb1, XmNactivateCallback, pbCB, (XtPointer)tb1);
  XmStringFree(tcs);

  XtRealizeWidget(Shell1);

  CommonPause();

  XtDestroyWidget(rc);

/* End Test for 4998 */

/*
 * Begin test for 5203: Create a pulldown menu of toggle buttons.
 * Add a callback to the first toggle button which will cause a change 
 * in its label.  Verify that the indicator size stays the same after 
 * the change.
 */

  n = 0;
  menubar = XmCreateMenuBar(Shell1, "menubar", args, n);

  n = 0;
  pulldown = XmCreatePulldownMenu(menubar, "pulldown", args, n);

  for (n = 0; n < 4; n++)
  {
    labelstring[strlen(labelstring) - 1] = 'A' + n;
    tcs = XmStringCreateLocalized(labelstring);
    XtSetArg(args[0], XmNlabelString, tcs);
    XtSetArg(args[1], XmNset, True);  
    tb[n] = XmCreateToggleButton(pulldown, labelstring, args, 2);
    XmStringFree(tcs);
  }
  XtManageChildren(tb, 4);
  XtAddCallback(tb[0], XmNvalueChangedCallback, tbCB, NULL);

  n = 0;
  XtSetArg(args[n], XmNsubMenuId, pulldown); n++;
  cb1 = XmCreateCascadeButton(menubar, "MENU", args, n);
  XtManageChild(cb1);
  XtManageChild(menubar); 
  CommonPause();

  CommonPause(); /* exit */
  XtAppMainLoop(app_context);
}


