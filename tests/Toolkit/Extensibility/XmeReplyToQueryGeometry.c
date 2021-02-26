/* $XConsortium: XmeReplyToQueryGeometry.c /main/4 1995/07/15 21:05:08 drk $ */
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
#include <Xm/BulletinB.h>
#include <Xm/XmP.h>

void  main (argc, argv)
int argc;
char **argv;
{
  register int       n;
  Arg                args[MAX_ARGS];
  Widget             bboard;
  XtWidgetGeometry   *desired, *intended;
  XtGeometryResult   geo_result;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  n = 0;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_NONE);  n++;
  bboard = XmCreateBulletinBoard(Shell1, "BBoard", args, n);

  XtManageChild(bboard);

  /* set up desired XtWidgetGeometry struct */
  desired = (XtWidgetGeometry *) XtMalloc (sizeof (XtWidgetGeometry));
  desired->width = (Dimension) 50;
  desired->height = (Dimension) 50;
  desired->request_mode = (CWWidth | CWHeight);

  intended = (XtWidgetGeometry *) XtMalloc (sizeof (XtWidgetGeometry));
  intended->width = (Dimension) 50;
  intended->height = (Dimension) 50;
  intended->request_mode = (CWWidth | CWHeight);

  /* check if 1) the desired and intended values match and 
              2) the widget intends to use these values (request_mode
	         is set for width and height) */
  if (XmeReplyToQueryGeometry(bboard, intended, desired) == XtGeometryYes)
    printf("Case1: passed\n");
  else
    printf("ERROR: incorrect result returned\n");
  CommonPause();

  /* check if the desired and intended values are the same. */
  desired->width = (Dimension) 200;
  desired->height = (Dimension) 200;
  if (XmeReplyToQueryGeometry(bboard, intended, desired) == XtGeometryNo)
    printf("Case2: passed\n");
  else
    printf("ERROR: incorrect result returned\n");
  CommonPause();

  /* Check the remaining case when the previous cases don't apply. */
  desired->width = (Dimension) 100;
  if (XmeReplyToQueryGeometry(bboard, intended, desired) == XtGeometryAlmost)
    printf("Case3: passed\n");
  else
    printf("ERROR: incorrect result returned\n");
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
