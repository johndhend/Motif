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
static char rcsid[] = "$XConsortium: ArrowBGad2.c /main/9 1995/07/13 17:27:29 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *  Create a drawing area with a set of arrow gadgets within it.
 *  Turn the highlight_thickness and highlight_on_enter resources on.
 *  Change the highlight color of the manager to see if it gets reflected
 *  in the gadgets.
 */

#include <signal.h>
#include <X11/StringDefs.h>
#include <testlib.h>

static void flushEvents();

void main (argc, argv)
int argc;
char **argv;
{
  Widget drawarea;
  Widget arrow[16];
  Arg args[10];
  Arg args2[10];
  int n, i;
  int x, y;
  char buf[32];
  Pixel top_shadow_color;


  CommonTestInit(argc, argv);

  /* Set the focus-policy to pointer mode for the shell */
  n = 0;
  XtSetArg (args[n], XmNkeyboardFocusPolicy, XmPOINTER);   n++;  
  XtSetValues (Shell1, args, n);

  /*  The drawing area creation.  Contained in an outer frame.  */
  i = 0;
  n = 0;
  XtSetArg (args[n], XmNwidth, 400);	n++;
  XtSetArg (args[n], XmNheight, 400);	n++;
  drawarea = XmCreateDrawingArea (Shell1, "drawarea", args, n);
  XtManageChild (drawarea);

  XtRealizeWidget (Shell1);

  /*  Create a matrix of arrows  */

  for (y = 10; y <= 175; y += 50) {
    for (x = 10; x <= 175; x += 50)	{
	n = 0;
	XtSetArg (args[n], XmNx, x); n++;
	XtSetArg (args[n], XmNy, y); n++;
	XtSetArg (args[n], XmNhighlightThickness, 4); n++;
	XtSetArg (args[n], XmNhighlightOnEnter, True); n++;
	sprintf(buf, "arrowButton%d", i );
	arrow[i] = XmCreateArrowButtonGadget(drawarea, buf, args, n);
	XtManageChild(arrow[i]);
        i = i + 1;
      }
  }	

  n = 0;
  XtSetArg (args[n], XmNtopShadowColor, &top_shadow_color);	n++;
  XtGetValues (drawarea, args, n);
  
  n = 0;
  XtSetArg (args2[n], XmNhighlightColor, top_shadow_color); 	n++;
  XtSetValues (drawarea, args2, n);

  CommonPause();

  XtAppMainLoop(app_context);

}
