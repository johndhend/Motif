/* $XConsortium: XmeQueryGeo.c /main/5 1995/07/15 21:04:58 drk $ */
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

/*  Standard C headers  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* QATS headers */
#include <testlib.h>

/*  X headers  */
#include <X11/IntrinsicP.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>

/*  Xm headers  */
#include <Xm/Xm.h>

/*  Exm headers  */
#include <Exm/CommandB.h>
#include <Exm/Grid.h>

static int ProtoError();

Widget		butt1, butt2;
Widget		xmDisplay;
XmString	default_str1, default_str2;

int 
main (int argc, char **argv)
{
  register int       n;
  Arg                args[MAX_ARGS];
  Widget       	     grid;
  unsigned char      alignment;
  XtGeometryResult   geo_result;
  XtWidgetGeometry   intended, preferred;
  Dimension	     width, height;

  XSetErrorHandler(ProtoError);

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  50);  n++;
  XtSetArg(args[n], XmNheight, 50);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  grid = XtVaCreateManagedWidget("Grid",
				 exmGridWidgetClass, Shell1, 
				 XmNwidth,  50,
				 XmNheight, 50,
				 XmNrows, 1,
				 XmNcolumns, 2,
				 NULL); 

  default_str1 = XmStringCreateLocalized("ONE");
  butt1 = XtVaCreateManagedWidget("butt1",
				   exmCommandButtonWidgetClass, grid, 
				   XmNwidth, 50,
				   XmNheight, 50,
				   XmNalignment, XmALIGNMENT_CENTER,
				   ExmNcompoundString, default_str1,
				   NULL);

  default_str2 = XmStringCreateLocalized("TWO");
  butt2 = XtVaCreateManagedWidget("butt2",
				   exmCommandButtonWidgetClass, grid, 
				   XmNwidth, 50,
				   XmNheight, 50,
				   ExmNcompoundString, default_str2,
				   XmNalignment, XmALIGNMENT_CENTER,
				   NULL);

  /* pause here to let the user read the description*/
  CommonPause();

  intended.height = 200;
  intended.width = 200;
  intended.request_mode = CWWidth | CWHeight;
  geo_result = XtQueryGeometry(grid, &intended, &preferred);

  if (geo_result != XtGeometryNo)
    printf("ERROR: unexpected result from query_geometry method\n");
  CommonPause();

  intended.height = 70;
  intended.width = 120;
  intended.request_mode = CWWidth | CWHeight;
  geo_result = XtQueryGeometry(grid, &intended, &preferred);

  if (geo_result != XtGeometryYes)
    printf("ERROR: unexpected result from query_geometry method\n");
  CommonPause();

  /* force new size on the grid widget */
  n = 0;
  XtSetArg(args[n], XmNheight, 100);  n++;
  XtSetArg(args[n], XmNwidth, 200);  n++;
  XtSetValues(grid, args, n);

  intended.height = 170;
  intended.width = 230;
  intended.request_mode = CWWidth | CWHeight;
  geo_result = XtQueryGeometry(grid, &intended, &preferred);

  if (geo_result != XtGeometryAlmost)
    printf("ERROR: unexpected result from query_geometry method\n");
  CommonPause();

  /* clean up */
  XmStringFree(default_str1);
  XmStringFree(default_str2);

  CommonPause(); /* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}

static int ProtoError(dpy, ev)
Display		*dpy;
XErrorEvent	*ev;
{
	fprintf(stderr, "Proto Error:");
	switch (ev->error_code) {
	case BadAccess:
	  fprintf(stderr,"\tBadAccess\n"); break;
	case BadAlloc:
	  fprintf(stderr,"\tBadAlloc\n"); break;
	case BadAtom:
	  fprintf(stderr,"\tBadAtom\n"); break;
	case BadColor:
	  fprintf(stderr,"\tBadColor\n"); break;
	case BadCursor:
	  fprintf(stderr,"\tBadCursor\n"); break;
	case BadDrawable:
	  fprintf(stderr,"\tBadDrawable\n"); break;
	case BadFont:
	  fprintf(stderr,"\tBadFont\n"); break;
	case BadGC:
	  fprintf(stderr,"\tBadGC\n"); break;
	case BadIDChoice:
	  fprintf(stderr,"\tBadIDChoice\n"); break;
	case BadImplementation:
	  fprintf(stderr,"\tBadImplementation\n"); break;
	case BadLength:
	  fprintf(stderr,"\tBadLength\n"); break;
	case BadMatch:
	  fprintf(stderr,"\tBadMatch\n"); break;
	case BadName:
	  fprintf(stderr,"\tBadName\n"); break;
	case BadPixmap:
	  fprintf(stderr,"\tBadPixmap\n"); break;
	case BadRequest:
	  fprintf(stderr,"\tBadRequest\n"); break;
        case BadValue:
	  fprintf(stderr,"\tBadValue\n"); break;
	case BadWindow:
	  fprintf(stderr,"\tBadWindow\n"); break;
	default:
	  fprintf(stderr,"\tUnknown error_code\n"); break;
	}
#ifdef DEBUG
	fflush(outfp);
	fclose(outfp);
#endif
	exit(0);
}
