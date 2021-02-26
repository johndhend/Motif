/* $XConsortium: HorPanedWin1.c /main/5 1995/07/15 21:08:07 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */
#include <testlib.h>


Widget  PanedWindow1 = NULL;
Widget  PushButton1 = NULL;
Widget  PushButton2 = NULL;
Widget  PushButton3 = NULL;

/*
 * This is a test for Horizontal PanedWindow
 */

void  
main (int argc, char **argv)
{
    int  n;
    Arg  args[MAX_ARGS];
    XmString           tcs = NULL;


    /*  
     * initialize toolkit  
     */

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth, 400);  n++;
    XtSetArg(args[n], XmNheight,300);  n++;
    XtSetArg(args[n], XmNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
  

    n = 0;
    XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
    XtSetArg (args[n], XmNmarginWidth, 20); n++;
    XtSetArg (args[n], XmNmarginHeight, 20); n++;
    XtSetArg (args[n], XmNsashWidth, 10); n++;
    XtSetArg (args[n], XmNsashHeight, 10); n++;
    XtSetArg (args[n], XmNsashIndent, 15); n++;
    XtSetArg (args[n], XmNsashShadowThickness, 5); n++;
    XtSetArg (args[n], XmNseparatorOn, True); n++;
    XtSetArg (args[n], XmNspacing, 25); n++;
    
    
    PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1",
                    args, n);
    XtManageChild(PanedWindow1);

    n = 0;
    PushButton1 = XmCreatePushButton(PanedWindow1, "PushButton1",
                    args, n);
    XtManageChild(PushButton1);

    n = 0;
    PushButton2 = XmCreatePushButton(PanedWindow1, "PushButton2",
                    args, n);
    XtManageChild(PushButton2);
    XmStringFree(tcs);

    n = 0;
    PushButton3 = XmCreatePushButton(PanedWindow1, "PushButton3",
                    args, n);
    XtManageChild(PushButton3);
    XmStringFree(tcs);

    XtRealizeWidget(Shell1);


    CommonPause();
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNallowResize, True);  n++;
    XtSetValues(PushButton1, args, n);

    n = 0;
    XtSetArg(args[n], XmNpaneMinimum, 100);  n++;
    XtSetArg(args[n], XmNpaneMaximum, 150);  n++;
    XtSetValues(PushButton2, args, n);

    n = 0;
    XtSetArg(args[n], XmNskipAdjust, True);  n++;
    XtSetValues(PushButton3, args, n);


    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 250); n++;
    XtSetArg(args[n], XmNheight, 250); n++;
    XtSetValues(PushButton1, args, n);

    CommonPause();

    XtAppMainLoop(app_context);
  }

