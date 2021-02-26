/* $XConsortium: GC1.c /main/4 1995/07/15 21:08:02 drk $ */
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


#include <testlib.h>
#include <Xm/PushBP.h>
#include <Xm/FormP.h>

Widget mainw, rc, drawpb, erasepb, highlightpb;
Arg    args[30];
int    n;
GC     rectangle_gc;

static void DrawRectangle();
static void EraseRectangle();
static void ChangeHighlight();

main(argc, argv)
int argc;
char *argv[];
{

  CommonTestInit (argc,argv);

  n = 0; 
  mainw = XmCreateMainWindow(Shell1, "mainw", args, n);
  XtManageChild(mainw);

  n = 0;
  XtSetArg (args[n], XmNhorizontalSpacing, 30); n++;
  XtSetArg (args[n], XmNwidth, 800); n++;
  XtSetArg (args[n], XmNheight, 300); n++;
  rc = XmCreateForm(mainw, "rc", args, n);
  XtManageChild(rc);

  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION); n++;
  XtSetArg (args[n], XmNleftPosition, 50); n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  XtSetArg (args[n], XmNheight, 100); n++;
  drawpb = XmCreatePushButton(rc, "Draw Rectangle", args, n);
  XtManageChild(drawpb);

  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
  XtSetArg (args[n], XmNleftWidget, drawpb); n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  XtSetArg (args[n], XmNheight, 100); n++;
  erasepb = XmCreatePushButton(rc, "Erase Rectangle", args, n);
  XtManageChild(erasepb);

  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
  XtSetArg (args[n], XmNleftWidget, erasepb); n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  XtSetArg (args[n], XmNheight, 100); n++;
  XtSetArg (args[n], XmNhighlightThickness, 20); n++;
  highlightpb = XmCreatePushButton(rc, "Change Highlight", args, n);
  XtManageChild(highlightpb);

  XtAddCallback(drawpb, XmNactivateCallback, DrawRectangle, NULL);
  XtAddCallback(erasepb, XmNactivateCallback, EraseRectangle, NULL);
  XtAddCallback(highlightpb, XmNactivateCallback, ChangeHighlight, NULL);

  XtRealizeWidget(Shell1);

  rectangle_gc = ((XmPushButtonWidget)highlightpb)->primitive.highlight_GC;
  XSetLineAttributes(XtDisplay(highlightpb), 
                     rectangle_gc, 5, 
                     LineSolid, CapButt, JoinMiter);

  CommonPause();
  XtAppMainLoop(app_context);

}

static void DrawRectangle(widget, data, callData)
Widget widget;
XtPointer data;
XtPointer callData;
{
  XDrawRectangle(XtDisplay(rc), XtWindow(rc), rectangle_gc, 25, 100, 100, 100);
}

static void EraseRectangle(widget, data, callData)
Widget widget;
XtPointer data;
XtPointer callData;
{
  XFillRectangle(XtDisplay(rc), XtWindow(rc), 
                 ((XmFormWidget)rc)->manager.background_GC, 
                 10, 85, 130, 130);
}

static void ChangeHighlight(widget, data, callData)
Widget widget;
XtPointer data;
XtPointer callData;
{
  int n;
  Arg args[2];

  n = 0;
  XtSetArg (args[n], XmNhighlightThickness, 20); n++;
  XtSetValues(highlightpb, args, n);
}

