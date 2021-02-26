/* $XConsortium: XmeConfigureObject.c /main/5 1995/07/15 21:04:12 drk $ */
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


/*#include <sys/file.h>*/

/*  Standard C headers  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* QATS headers */
#include <testlib.h>

/*  X headers  */
#include <X11/IntrinsicP.h>

/*  Xm headers  */
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>

int 
main (int argc, char **argv)
{
  Widget             workRegion, simpleWidget, simpleGadget;
  register int       n;
  Arg                args[MAX_ARGS];
  Position           x, y;
  Dimension          width, height, border_width;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  /* set up a manager */
  n = 0;
  XtSetArg(args[n],XmNnoResize, True);  n++;
  XtSetArg(args[n],XmNresizePolicy, XmRESIZE_NONE);  n++;
  XtSetArg(args[n],XmNwidth, 200);  n++;
  XtSetArg(args[n],XmNheight, 200);  n++;
  workRegion = XmCreateBulletinBoard(Shell1,"WorkRegion", args, n);

  XtManageChild(workRegion);

  /* Instantiate a PushButton widget. */
  n = 0;
  XtSetArg(args[n],XmNrecomputeSize, False);  n++;
  XtSetArg(args[n],XmNshadowThickness, 5);  n++;
  XtSetArg(args[n],XmNmarginWidth, 5);  n++;
  XtSetArg(args[n],XmNx, 5);  n++;
  XtSetArg(args[n],XmNy, 5);  n++;
  XtSetArg(args[n],XmNborderWidth, 5);  n++;
  XtSetArg(args[n],XmNwidth, 90);  n++;
  XtSetArg(args[n],XmNheight, 50);  n++;
  simpleWidget = XmCreatePushButton(workRegion,"Widget", args, n);
  XtManageChild(simpleWidget);
  CommonPause();

  /* move the child widget */
  XmeConfigureObject(simpleWidget, 30, 30, 90, 50, 5);
  XtVaGetValues(simpleWidget,
		XmNx, &x,
		XmNy, &y,
		NULL);
  if (x != 30 || y !=30)
    printf("ERROR: incorrect position values\n");
  CommonPause();

  /* change the child widget's border */
  XmeConfigureObject(simpleWidget, 30, 30, 90, 50, 25);
  XtVaGetValues(simpleWidget,
		XmNborderWidth, &border_width,
		NULL);
  if (border_width != 25)
    printf("ERROR: incorrect border value\n");
  CommonPause();

  /* change the size of the widget */
  XmeConfigureObject(simpleWidget, 30, 30, 150, 100, 5);
  XtVaGetValues(simpleWidget,
		XmNheight, &height,
		XmNwidth, &width,
		NULL);
  if (width != 150 || height != 100)
    printf("ERROR: incorrect size values\n");
  CommonPause();

  /* Instantiate a PushButton gadget. */
  XtDestroyWidget(simpleWidget);
  n = 0;
  XtSetArg(args[n],XmNrecomputeSize, False);  n++;
  XtSetArg(args[n],XmNshadowThickness, 5);  n++;
  XtSetArg(args[n],XmNmarginWidth, 5);  n++;
  XtSetArg(args[n],XmNx, 5);  n++;
  XtSetArg(args[n],XmNy, 5);  n++;
  XtSetArg(args[n],XmNborderWidth, 5);  n++;
  XtSetArg(args[n],XmNwidth, 90);  n++;
  XtSetArg(args[n],XmNheight, 50);  n++;
  simpleGadget = XmCreatePushButtonGadget(workRegion,"Gadget", args, n);
  XtManageChild(simpleGadget);
  CommonPause();

  /* move the child gadget */
  XmeConfigureObject(simpleGadget, 80, 30, 90, 50, 5);
  XtVaGetValues(simpleGadget,
		XmNx, &x,
		XmNy, &y,
		NULL);
  if (x != 80 || y !=30)
    printf("ERROR: incorrect position values\n");
  CommonPause();

  /* change the child gadget's border */
  XmeConfigureObject(simpleGadget, 30, 30, 90, 50, 25);
  XtVaGetValues(simpleGadget,
		XmNborderWidth, &border_width,
		NULL);
  if (border_width != 25)
    printf("ERROR: incorrect border value: %d\n",border_width);
  CommonPause();

  /* change the size of the gadget */
  XmeConfigureObject(simpleGadget, 30, 30, 150, 100, 5);
  XtVaGetValues(simpleGadget,
		XmNheight, &height,
		XmNwidth, &width,
		NULL);
  if (width != 150 || height != 100)
    printf("ERROR: incorrect size values\n");
  CommonPause();

  CommonPause(); /* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
