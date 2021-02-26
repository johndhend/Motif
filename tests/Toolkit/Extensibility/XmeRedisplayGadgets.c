/* $XConsortium: XmeRedisplayGadgets.c /main/4 1995/07/15 21:05:02 drk $ */
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
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  int                status;
  Arg                args[MAX_ARGS];
  String             dirname;
  Widget             rc, g1, g2, g3, g4;
  Pixel              black;
  XEvent             event;
  Display            *display;
  Window             window;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

printf("creating widget\n");
  n = 0;
/*  black=BlackPixel(display, DefaultScreen(display));
  XtSetArg(args[n], XmNbackground, black);  n++;*/
  rc = XmCreateRowColumn(Shell1, "rc", args, n);

printf("creating gadgets\n");
  n = 0;
  g1 = XmCreatePushButtonGadget(rc, "Gadget1", args, n);
  g2 = XmCreatePushButtonGadget(rc, "Gadget2", args, n);
  g3 = XmCreatePushButtonGadget(rc, "Gadget3", args, n);
  g4 = XmCreatePushButtonGadget(rc, "Gadget4", args, n);

printf("managing widgets and gadgets\n");
  XtManageChild(rc);
  display = XtDisplay(Shell1);
  window = XtWindow(rc);
  XtManageChild(g1);
  XtManageChild(g2);
  XtManageChild(g3);
  XtManageChild(g4);
  CommonPause();

printf("clear the window\n");
  status = XClearWindow(display, window);
  if ( status == BadMatch)
    printf("ERROR: XClearWindow failed - BadMatch\n");
  else if ( status == BadWindow)
    printf("ERROR: XClearWindow failed - BadWindow\n");
  CommonPause();

printf("XmeRedisplayGadgets\n");
  event.type = Expose;
  event.xexpose.display = display;
  event.xexpose.window = window;
  event.xexpose.send_event = False;
  event.xexpose.x = 0;
  event.xexpose.y = 0;
  event.xexpose.width = 100;
  event.xexpose.height = 100;
  XmeRedisplayGadgets(rc, &event, NULL);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
