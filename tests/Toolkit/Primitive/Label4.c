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
static char rcsid[] = "$TOG: Label4.c /main/8 1999/03/18 11:39:27 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <X11/StringDefs.h>
#include <testlib.h>

/*
 *  Use XmGetImage to get a set of pixmaps created from images read from
 *  a file.  Put the images into labels for display.
 */

extern XImage * _XmGetImageFromFile();

void main (argc, argv)
int argc;
char **argv;
{
  Screen *screen;
  Widget drawarea;
  Widget label1, label2, label3, label4;
  Pixel foreground, background;
  Pixmap pixmap1, pixmap2, pixmap3, pixmap4, pixmap5;
  Arg args[10];
  int n;
  XImage *image1;

  /*  initialize toolkit  */
  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg (args[n], XmNwidth, 400); n++;
  XtSetArg (args[n], XmNheight, 400); n++;
  XtSetValues(Shell1, args, n);

  /*  The drawing area creation.  Contained in an outer frame.  */
  
  n = 0;
  XtSetArg (args[n], XmNwidth, 400);	n++;
  XtSetArg (args[n], XmNheight, 400);	n++;
  drawarea = XmCreateDrawingArea (Shell1, "drawarea", args, n);
  XtManageChild (drawarea);

  n = 0;
  XtSetArg (args[n], XmNforeground, &foreground);	n++;
  XtSetArg (args[n], XmNbackground, &background);	n++;
  XtGetValues (drawarea, args, n);

  XtRealizeWidget (Shell1);

  /*  Create a set of pixmaps to copy the images to.  */

  screen = XtScreen (Shell1);
  pixmap1 = XmGetPixmap (screen, "tie_fighter", foreground, background);
  pixmap2 = XmGetPixmap (screen, "woman", foreground, background);
  pixmap3 = XmGetPixmap (screen, "right_ptr", foreground, background);
  pixmap4 = XmGetPixmap (screen, "target", foreground, background);
  pixmap5 = XmGetPixmap (screen, "foo_bar", foreground, background);

  /*  Create 4 labels in the drawing area  */

  n = 0;
  XtSetArg (args[n], XmNx, 25);		n++;
  XtSetArg (args[n], XmNy, 25);		n++;
  XtSetArg (args[n], XmNlabelType, XmPIXMAP);	n++;
  XtSetArg (args[n], XmNlabelPixmap, pixmap1);	n++;
  label1 = XmCreateLabel (drawarea, "label1", args, n);
  XtManageChild (label1);

  n = 0;
  XtSetArg (args[n], XmNx, 250);		n++;
  XtSetArg (args[n], XmNy, 25);		n++;
  XtSetArg (args[n], XmNlabelType, XmPIXMAP);	n++;
  XtSetArg (args[n], XmNlabelPixmap, pixmap2);	n++;
  label2 = XmCreateLabel (drawarea, "label2", args, n);
  XtManageChild (label2);

  n = 0;
  XtSetArg (args[n], XmNx, 25);		n++;
  XtSetArg (args[n], XmNy, 250);		n++;
  XtSetArg (args[n], XmNlabelType, XmPIXMAP);	n++;
  XtSetArg (args[n], XmNlabelPixmap, pixmap3);	n++;
  label3 = XmCreateLabel (drawarea, "label3", args, n);
  XtManageChild (label3);

  n = 0;
  XtSetArg (args[n], XmNx, 250);		n++;
  XtSetArg (args[n], XmNy, 250);		n++;
  XtSetArg (args[n], XmNlabelType, XmPIXMAP);	n++;
  XtSetArg (args[n], XmNlabelPixmap, pixmap4);	n++;
  label4 = XmCreateLabel (drawarea, "label4", args, n);
  XtManageChild (label4);

  if (NULL != (image1 =
	_XmGetImageFromFile ("../bitmaps/tie_fighter"))) {

    if (XmInstallImage (NULL, NULL) != FALSE)
	printf ("Install of NULL should have failed.\n");

    if (XmInstallImage (image1, "foo bar") == FALSE)
	printf ("Install of image with new name should have succeeded.\n");

    if (XmInstallImage (image1, "foo bar") != FALSE)
	printf ("Install of image with same name should have failed.\n");

    if (XmInstallImage (image1, "baz") == FALSE)
	printf ("Install of image with new name should have succeeded.\n");

    if (XmUninstallImage (NULL) != FALSE)
	printf ("Uninstall of NULL should have failed.\n");

    if (XmUninstallImage (image1) == FALSE)
	printf ("Uninstall should have succeeded.\n");
  }
  else {
    printf ("Fetch of image failed.\n");
  }

  /*  Destroy a label and then uninstall the pixmaps and images  */

  CommonPause();

  XtDestroyWidget(label4);

  if (XmDestroyPixmap (XtScreen (label1), pixmap4) == FALSE)
    printf ("XmDestroy should have succeeded.\n");

  if (XmDestroyPixmap (XtScreen (label1), pixmap4) != FALSE)
    printf ("XmDestroy should have failed.\n");

  CommonPause();
   
  /* End */
  XtDestroyWidget(label3);
  XtDestroyWidget(label2);
  XtDestroyWidget(label1);
  XtDestroyWidget(drawarea);
  CommonPause();
  XtAppMainLoop(app_context);
}
