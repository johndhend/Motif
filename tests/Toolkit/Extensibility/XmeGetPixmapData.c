/* $TOG: XmeGetPixmapData.c /main/5 1998/09/24 13:20:52 samborn $ */
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
static char rcsid[] = ""
#endif
#endif

#include <testlib.h>
#include <Xm/LabelG.h>
#include <Xm/RowColumn.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>

Widget rowcol;
Pixmap pixmap;
Pixel fg, bg;

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  String             dirname;
  char               *image_name;
  int                depth;
  Pixel              foreground, background;
  int                hot_x, hot_y;
  unsigned int       width, height;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);
  rowcol = XtVaCreateWidget("rowcol",xmRowColumnWidgetClass, Shell1,
			    XmNpacking, XmPACK_COLUMN,
			    NULL);

  /* get the values for the foreground and background colors */
  XtVaGetValues(rowcol,
		XmNforeground, &fg,
		XmNbackground, &bg,
		NULL);

  pixmap = XmGetPixmap(XtScreen(Shell1),"../bitmaps/xlogo64.xbm",fg,bg);
  if (pixmap == XmUNSPECIFIED_PIXMAP) {
    printf("ERROR - couldn't load image - xlogo64.xbm\n");
    exit(1);
  } else
    XtVaCreateManagedWidget("xlogo64", xmLabelGadgetClass, rowcol,
			    XmNlabelType, XmPIXMAP,
			    XmNlabelPixmap, pixmap,
			    NULL);
  XtManageChild(rowcol);

  /* call the function */
  if (!XmeGetPixmapData(XtScreen(Shell1), pixmap,
			&image_name, &depth, &foreground,
			&background, &hot_x, &hot_y,
			&width, &height))
      printf("ERROR: image not in the image cache\n");

  /* Verify the data returned */
  if (strcmp(image_name, "../bitmaps/xlogo64.xbm"))
    printf("ERROR - image name: %s\n",image_name);
  if (depth != 8)
    printf("ERROR - incorrect depth: %d\n",depth);
  if (hot_x != -1)
    printf("ERROR - incorrect hot_x: %d\n",hot_x);
  if (hot_y != -1)
    printf("ERROR - incorrect hot_y: %d\n",hot_y);
  if (width != 64)
    printf("ERROR - incorrect depth: %d\n",width);
  if (height != 64)
    printf("ERROR - incorrect depth: %d\n",height);
  if (foreground != fg)
    printf("ERROR - foreground color doesn't match\n");
  if (background != bg)
    printf("ERROR - background color doesn't match\n");
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
