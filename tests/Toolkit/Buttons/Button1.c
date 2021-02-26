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
static char rcsid[] = "$XConsortium: Button1.c /main/6 1995/07/13 17:28:44 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

void arm();
void disarm();
void expose();

int main(argc, argv)
int argc;
char *argv[];
{
  Widget rc, arr, pb, tog;
  Arg args[20] ;
  int n;
  XEvent *ev;

  ev = (XEvent *) XtCalloc (1, sizeof(XEvent));

  CommonTestInit(argc, argv);
  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True);  n++;
  XtSetArg(args[n], XmNwidth, 300);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetValues(Shell1, args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth, 200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtManageChild(rc = XmCreateRowColumn(Shell1, "bulletin", args, n));

  n=0;
  XtSetArg(args[n], XmNheight, 100);  n++;
  XtManageChild(arr=XmCreateArrowButton(rc, "ArrowButton", args, n));
  XtManageChild(pb=XmCreatePushButton(rc, "PushButton", args, n));
  XtManageChild(tog=XmCreateToggleButton(rc, "ToggleButton", args, n));

  XtRealizeWidget(Shell1);

  CommonPause();

  /*  Arm */
  printf("=> ARM %s\n", XtName((Widget)arr));
  printf("=> ARM %s\n", XtName((Widget)pb));
  printf("=> ARM %s\n", XtName((Widget)tog)); 
  XtCallActionProc((Widget)arr, "Arm", ev, NULL, 5000);
  XtCallActionProc((Widget)pb, "Arm", ev, NULL, 5000);
  XtCallActionProc((Widget)tog, "Arm", ev, NULL, 5000);
  CommonPause();

/*  Activate */
  printf("=> ACTIVATE %s\n", XtName((Widget)arr));
  printf("=> ACTIVATE %s\n", XtName((Widget)pb));
  printf("=> ACTIVATE %s\n", XtName((Widget)tog)); 
  XtCallActionProc((Widget)arr, "Activate", ev, NULL, 5000);
  XtCallActionProc((Widget)pb, "Activate", ev, NULL, 5000);
  XtCallActionProc((Widget)tog, "Select", ev, NULL, 5000);
  CommonPause();

  /*  Disarm */
  printf("=> DISARM %s\n", XtName((Widget)arr));
  printf("=> DISARM %s\n", XtName((Widget)pb));
  printf("=> DISARM %s\n", XtName((Widget)tog));
  XtCallActionProc((Widget)arr, "Disarm", ev, NULL, 5000);
  XtCallActionProc((Widget)pb, "Disarm", ev, NULL, 5000);
  XtCallActionProc((Widget)tog, "Disarm", ev, NULL, 5000);
  CommonPause();

  /*  Expose */

  printf("=> EXPOSE %s\n", XtName((Widget)arr));
  printf("=> EXPOSE %s\n", XtName((Widget)pb));
  printf("=> EXPOSE %s\n", XtName((Widget)tog));
  XClearArea(XtDisplayOfObject((Widget)arr), XtWindowOfObject((Widget)arr), 
		0, 0, 0, 0, True);
  XClearArea(XtDisplayOfObject((Widget)pb), XtWindowOfObject((Widget)pb), 
		0, 0, 0, 0, True);
  XClearArea(XtDisplayOfObject((Widget)tog), XtWindowOfObject((Widget)tog), 
		0, 0, 0, 0, True);

  CommonPause();
  XtFree((char *) ev);

  XtMainLoop();
}


