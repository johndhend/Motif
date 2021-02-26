/* $TOG: XmeGetDefaultPixel.c /main/5 1997/03/04 17:41:05 dbl $ */
/* 
 *  @OPENGROUP_COPYRIGHT@
 *  COPYRIGHT NOTICE
 *  Copyright (c) 1993 Open Software Foundation, Inc.
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
static char rcsid[] = ""
#endif
#endif

#include <testlib.h>
#include <Xm/PushB.h>
#include <Xm/XmP.h>

Widget button;
Pixel background, foreground, top_shadow, bottom_shadow, select_color;

void
doit(w, client_data, cbs)
Widget w;
XtPointer client_data, cbs;
{
  int offset=0;
  XrmValue value, get_value;
  char *str_type_return;

  XmeGetDefaultPixel(w, XmBACKGROUND, offset, &value);
  if (*(Pixel*)value.addr != background)
    printf("ERROR: background pixel value: %d  expected: %d\n",
	   (*(Pixel*)value.addr), background);

  XmeGetDefaultPixel(w, XmFOREGROUND, offset, &value);
  if (*(Pixel*)value.addr != foreground)
    printf("ERROR: foreground pixel value: %d  expected: %d\n",
	   (*(Pixel*)value.addr), foreground);

  XmeGetDefaultPixel(w, XmTOP_SHADOW, offset, &value);
  if (*(Pixel*)value.addr != top_shadow)
    printf("ERROR: top_shadow pixel value: %d  expected: %d\n",
	   (*(Pixel*)value.addr), top_shadow);

  XmeGetDefaultPixel(w, XmBOTTOM_SHADOW, offset, &value);
  if (*(Pixel*)value.addr != bottom_shadow)
    printf("ERROR: bottom_shadow pixel value: %d  expected: %d\n",
	   (*(Pixel*)value.addr), bottom_shadow);

  XmeGetDefaultPixel(w, XmSELECT, offset, &value);
  if (*(Pixel*)value.addr != select_color)
    printf("ERROR:  select pixel value: %d  expected: %d\n",
	   (*(Pixel*)value.addr), select_color);
}

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XColor             color, unused;
  Colormap           cmap;
  Display            *display;
  Screen             *screen;
  XmString           label;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetArg(args[n], XmNborderWidth, 20);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  display = XtDisplay(Shell1);
  screen = XtScreen(Shell1);
  label = XmStringCreateLocalized("Validate");

  /* get color data */
  XtVaGetValues(Shell1, XmNcolormap, &cmap, NULL);
  XAllocNamedColor(display, cmap, "red", &color, &unused);
  background = color.pixel;
  XmGetColors(screen, cmap, background,
	      &foreground, &top_shadow, &bottom_shadow, &select_color);
  n = 0;
  XtSetArg(args[n], XmNshadowThickness, 20);  n++;
  XtSetArg(args[n], XmNbackground, background);  n++;
  XtSetArg(args[n], XmNlabelString, label);  n++;
  button = XmCreatePushButton(Shell1, "button", args, n);
  XtAddCallback(button, XmNactivateCallback, doit, (XtPointer)NULL);

  XtManageChild(button);
  CommonPause();

  XtDestroyWidget(button);
  /* get color data */
  XAllocNamedColor(display, cmap, "black", &color, &unused);
  background = color.pixel;
  XmGetColors(screen, cmap, background,
	      &foreground, &top_shadow, &bottom_shadow, &select_color);
  n = 0;
  XtSetArg(args[n], XmNshadowThickness, 20);  n++;
  XtSetArg(args[n], XmNbackground, background);  n++;
  XtSetArg(args[n], XmNlabelString, label);  n++;
  button = XmCreatePushButton(Shell1, "button", args, n);
  XmStringFree(label);
  XtAddCallback(button, XmNactivateCallback, doit, (XtPointer)NULL);

  XtManageChild(button);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
