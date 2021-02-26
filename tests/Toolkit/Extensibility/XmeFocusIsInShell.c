/* $XConsortium: XmeFocusIsInShell.c /main/4 1995/07/15 21:04:35 drk $ */
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
static char rcsid[] = ""
#endif
#endif

#include <testlib.h>
#include <Xm/PushB.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>

Widget button, button2, extra_shell;
Display *display;

void
button_callback(w, client_data, cbs)
Widget w;
XtPointer client_data;
XmPushButtonCallbackStruct *cbs;
{
  if (XmeFocusIsInShell(button))
    printf("OK - focus is in button\n");
  else
    printf("ERROR - focus should be in button\n");

  /* make sure that focus is NOT in button2 which is in a
     different widget tree than button */
  if (XmeFocusIsInShell(button2))
    printf("ERROR - focus is in button2\n");
  else
    printf("OK - focus should not be in button2\n");
}

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  String             dirname;
  XmString           label_str;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  display = XtDisplay(Shell1);

  /* create a button for the user to push and subsequently check
     the funtion. */
  label_str = XmStringCreateSimple("Push Me");
  button = XtVaCreateManagedWidget("button",xmPushButtonWidgetClass, Shell1,
				   XmNlabelString, label_str,
				   XmNwidth, 100,
				   XmNheight, 100,
				   NULL);
  XmStringFree(label_str);
  XtAddCallback(button, XmNactivateCallback, button_callback, NULL);

  /* Create a second independent shell for this test */
  extra_shell = XtAppCreateShell(NULL,
				 "application_class",
				 applicationShellWidgetClass,
				 display,
				 NULL, 0);

  /* create a button */
  label_str = XmStringCreateSimple("Leave me alone.");
  button2 = XtVaCreateManagedWidget("button2",xmPushButtonWidgetClass,
				    extra_shell,
				    XmNlabelString, label_str,
				    NULL);
  XmStringFree(label_str);
  XtRealizeWidget(extra_shell);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
