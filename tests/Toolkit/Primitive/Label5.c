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
static char rcsid[] = "$TOG: Label5.c /main/8 1999/01/29 13:48:09 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *  Read a set of pixmaps using XmGetPixmap, then create a drawing area
 *  with a set of labels containing the pixmaps.
 */

#include <testlib.h>

static char *bitmapNames[8] = {
	"../bitmaps/tie_fighter",
	"../bitmaps/gnu.bmp",
	"../bitmaps/warning",
	"../bitmaps/mtn.bmp",
	"../bitmaps/smiley.bmp",
	"../bitmaps/dp.bmp",
	"../bitmaps/circles1.bmp",
	""
};

void main (argc, argv)
int argc;
char **argv;

{
  Widget drawarea;
  Widget separator;
  static char *label_names[15] = {"label1","label2","label3","label4",
		            "label5","label6","label7","label8",
		            "label9","label10","label11","label12",
		            "label13","label14","label15"};
  static Widget labels[15] = 
    {NULL, NULL,NULL, NULL,NULL, NULL,NULL, NULL,NULL, NULL,
       NULL, NULL,NULL, NULL,NULL};
  Pixmap pixmap;
  Arg args[10];
  int j = 0, n;
  XmString tcs;
  Pixel foreground, background;

  CommonTestInit(argc, argv);

  /*  The drawing area creation.  Contained in an outer frame.  */

  n = 0;
  XtSetArg (args[n], XmNmarginWidth, 10);	n++;
  XtSetArg (args[n], XmNmarginHeight, 10); 	n++;
  drawarea = XmCreateRowColumn (Shell1, "drawarea", args, n);
  XtManageChild (drawarea);
  XtRealizeWidget (Shell1);

  n = 0;
  XtSetArg (args[n], XmNforeground, &foreground);	n++;
  XtSetArg (args[n], XmNbackground, &background); 	n++;
  XtGetValues(drawarea, args, n);

  while (bitmapNames[j][0]) {

    n = 0;
    tcs = XmStringLtoRCreate("Oops! error", XmSTRING_DEFAULT_CHARSET);
    XtSetArg (args[n], XmNlabelString, tcs);	n++;
    labels[j] = XmCreateLabel (drawarea, label_names[j], args, n);
    XtManageChild (labels[j]);
    XmStringFree (tcs);
    
    printf ("Reading image %s\n", bitmapNames[j]);

    if ((pixmap = XmGetPixmap (XtScreen(drawarea), bitmapNames[j],
				foreground, background)) == NULL)
      {
	printf ("No pixmap returned from XmGetPixmap.\n");
	j++;
	continue;
      }
   
    n = 0;
    XtSetArg (args[n], XmNx, j * 20 + 5);	n++;
    XtSetArg (args[n], XmNlabelType, XmPIXMAP);	n++;
    XtSetArg (args[n], XmNlabelPixmap, pixmap);	n++;
    XtSetValues (labels[j], args, n);
    XtManageChild (labels[j]);

    n = 0;
    XtSetArg (args[n], XmNseparatorType, XmSHADOW_ETCHED_OUT);	n++;
    separator = XmCreateSeparatorGadget (drawarea, "separator", args, n);
    XtManageChild (separator);

    CommonPause();

    j++; 
  }

  j = 0;

  while (labels[j] != NULL)
    {
      XtDestroyWidget(labels[j]);
      j++;
    }

  XmDestroyPixmap(XtScreen(drawarea), pixmap);
 
  CommonPause();

  XtAppMainLoop(app_context);
}
