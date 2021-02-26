/* $XConsortium: XmeCreateClassDialog.c /main/4 1995/07/15 21:04:17 drk $ */
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
#include <Xm/PushB.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>

Widget rc, button, list;

char *items[] = {
  "File","Open","Quit"
};

void
goodbye(w, client_data, cbs)
Widget w;
XtPointer client_data, cbs;
{
  XtPopdown(XtParent(w));
}

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n, cnt = XtNumber(items);
  Arg                args[MAX_ARGS];
  String             dirname;
  XmStringTable      str_list;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetArg(args[n], XmNmappedWhenManaged, False); n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  n = 0;
  rc = XmCreateRowColumn(Shell1, "rc", args, n);

  n = 0;
  XtSetArg(args[n], XmNwidth,  160);  n++;
  XtSetArg(args[n], XmNheight, 80);  n++;
  button = XmeCreateClassDialog(xmPushButtonWidgetClass,
				rc, "button", args, n);
  XtAddCallback(button, XmNactivateCallback, goodbye, NULL);
  XtManageChild(button);
  CommonPause();

  /* prepare string list for list widget */
  str_list = (XmStringTable)XtMalloc(cnt * sizeof(XmString *));
  for (n=0; n<cnt; n++)
    str_list[n] = XmStringCreateSimple(items[n]);

  n = 0;
  XtSetArg(args[n], XmNwidth,  160);  n++;
  XtSetArg(args[n], XmNvisibleItemCount, cnt);  n++;
  XtSetArg(args[n], XmNitemCount, cnt);  n++;
  XtSetArg(args[n], XmNitems, str_list);  n++;
  list = XmeCreateClassDialog(xmListWidgetClass,
			      rc, "list", args, n);
  XtAddCallback(list, XmNdefaultActionCallback, goodbye, NULL);
  XtManageChild(list);

  for (n=0; n<cnt; n++)
    XmStringFree(str_list[n]);
  XtFree(str_list);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
