/* $XConsortium: XmeCursor.c /main/4 1995/07/15 21:04:21 drk $ */
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
#include <time.h>
#include <Xm/PushB.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>
#define BUFSIZE 40
#define MSLEEP 999999L

void
Sleep(w, client_data, cbs)
Widget w;
XtPointer client_data, cbs;
{
  time_t             tval;
  struct tm          *tmptr;
  char               buf[BUFSIZE], buf2[BUFSIZE];
  int                start, stop, duration;

  /* Start a timer test */
  tval = time(NULL);
  tmptr = localtime(&tval);
  strftime(buf,BUFSIZE, "%S", tmptr);

  /* sleep for 4 seconds approximately */
  if (XmeMicroSleep(MSLEEP) == -1)
    printf("ERROR: XmeMicroSleep failed\n");
  if (XmeMicroSleep(MSLEEP) == -1)
    printf("ERROR: XmeMicroSleep failed\n");
  if (XmeMicroSleep(MSLEEP) == -1)
    printf("ERROR: XmeMicroSleep failed\n");
  if (XmeMicroSleep(MSLEEP) == -1)
    printf("ERROR: XmeMicroSleep failed\n");

  tval = time(NULL);
  tmptr = localtime(&tval);
  strftime(buf2,BUFSIZE, "%S", tmptr);

  /* verify the results (either 4 or 5 is correct) */
  sscanf(buf,"%d",&start);
  sscanf(buf2,"%d",&stop);
  if (stop < start)
    stop += 60;
  duration = stop - start;

  if (duration != 4 && duration !=5) 
    printf("ERROR: sleep duration is not in the correct range\n");
  else
    printf("OK: sleep test passes\n");
}

void
PushMe(w, client_data, cbs)
Widget w;
XtPointer client_data, cbs;
{
  printf("Button Press received\n");
}

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  int                status;
  Arg                args[MAX_ARGS];
  String             dirname;
  Widget             rc, button, button2;
  Display            *display;
  Window             window;
  Cursor             null_cursor;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  /* set up push button widgets */
  n = 0;
  rc = XmCreateRowColumn(Shell1, "RowC", args, n);
  XtManageChild(rc);
  window = XtWindow(rc);
  display = XtDisplay(rc);

  /* create buttons for test */
  n = 0;
  button = XmCreatePushButton(rc, "Start Sleep", args, n);
  button2 = XmCreatePushButton(rc, "Validate", args, n);
  XtAddCallback(button, XmNactivateCallback, Sleep, (XtPointer)1);
  XtAddCallback(button2, XmNactivateCallback, PushMe, NULL);
  XtManageChild(button);
  XtManageChild(button2);
  CommonPause();

  /* reset the callback */
  XtRemoveCallback(button, XmNactivateCallback, Sleep, (XtPointer)1);
  XtAddCallback(button, XmNactivateCallback, PushMe, (XtPointer)2);

  /* set Null cursor */
  null_cursor = XmeGetNullCursor(Shell1);
  status = XDefineCursor(display, window, null_cursor);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
