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
static char rcsid[] = "$XConsortium: PanedWin4.c /main/4 1995/07/13 19:06:57 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <X11/StringDefs.h>
Widget  PanedWindow1 = NULL;
Widget  PushButton1 = NULL;
Widget  PushButton2 = NULL;
Widget  PushButton3 = NULL;

void  main (argc, argv)
int     argc;
char  **argv;
{
    int                delay = 0;
    Boolean            mywait = False;
    register int       n;
    Arg                args[MAX_ARGS];
    XmString           tcs = NULL;
    XWindowAttributes  info;
    XEvent             DummyEvent;

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth, 400);  n++;
    XtSetArg(args[n], XmNheight,300);  n++;
    XtSetArg(args[n], XmNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
  
    XmRegisterConverters();
#ifdef  SYNCHRONIZE
    XSynchronize(display, 1);
#endif  /*  SYNCHRONIZE  */

    XtRealizeWidget(Shell1);

    mywait = True;
    while (mywait) {
        XGetWindowAttributes(XtDisplay(Shell1), XtWindow(Shell1), &info);
        if (info.map_state == IsViewable) mywait = False;
        else sleep(1);
    }

    flushEvents(delay);

    n = 0;
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

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNallowResize, False);  n++;
    XtSetValues(PushButton1, args, n);

    n = 0;
    XtSetArg(args[n], XmNpaneMinimum, 20);  n++;
    XtSetArg(args[n], XmNpaneMaximum, 50);  n++;
    XtSetValues(PushButton2, args, n);

    n = 0;
    XtSetArg(args[n], XmNskipAdjust, False);  n++;
    XtSetValues(PushButton3, args, n);

    n = 0;
    XtSetArg(args[n], XmNmarginHeight, 10);   n++;
    XtSetValues(PanedWindow1, args, n);

    CommonPause();

    XtDestroyWidget (PanedWindow1);
    n = 0;
    PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1",
                    args, n);
    XtManageChild(PanedWindow1);

    n = 0;
    XtSetArg (args[n], XmNheight, 100); n++;
    XtSetArg (args[n], XmNwidth, 100); n++;
    PushButton1 = XmCreatePushButton(PanedWindow1, "PushButton1",
                    args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg (args[n], XmNheight, 100); n++;
    PushButton2 = XmCreatePushButton(PanedWindow1, "PushButton2",
                    args, n);
    XtManageChild(PushButton2);
    XmStringFree(tcs);

    n = 0;
    XtSetArg (args[n], XmNheight, 100); n++;
    XtSetArg (args[n], XmNpaneMinimum, 50); n++;
    XtSetArg (args[n], XmNskipAdjust, True); n++;
    PushButton3 = XmCreatePushButton(PanedWindow1, "PushButton3",
                    args, n);
    XtManageChild(PushButton3);    

    CommonPause();
  
    XtAppMainLoop(app_context);
}

flushEvents(delay)
int    delay;
{
    XEvent event;


    XSync(display, False);
    while (XPending(display)) {
        XNextEvent(display, &event);
        XtDispatchEvent(&event);
    }

    sleep(delay);
}
