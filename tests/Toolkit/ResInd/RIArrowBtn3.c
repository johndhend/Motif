/* $XConsortium: RIArrowBtn3.c /main/4 1995/07/15 21:08:22 drk $ */
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
/* 
 * Original History:
 *
 *   Revision 1.5.2.2  92/05/19  18:12:39  tomm
 * 	  Ansi changes.
 * 	  [1992/05/19  18:03:17  tomm]
 * 
 *   Revision 1.5  1992/03/13  16:57:34  devsrc
 * 	  Converted to ODE
 * 
*/ 

/**************************************************************************
 *
 *  Create an arrow using inches and setting the width and height. 
 *  Reset the size, change the unit type, set the size again.
 *
 **************************************************************************/

#include <signal.h>
#include <X11/StringDefs.h>
#include <Xm/XmP.h>
#include <testlib.h>

/*  Global Variables  */
Widget arrow;
/* forward declarations */
void LoopThruValues();
static XtCallbackProc PrintSizes();

void main (argc, argv)
int argc;
char **argv;
{
   Arg args[20];
   int n, k;
   Dimension width, height;
   Widget frame;

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);

   n = 0;
   frame = XmCreateFrame (Shell1, "frame", args, n);

   printf ("Setting the unit type to inches and size to (2000, 1000).\n");
   n = 0;
   XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);	n++;
   XtSetArg (args[n], XmNwidth, 2000);			n++;
   XtSetArg (args[n], XmNheight, 1000);			n++;
   arrow = XmCreateArrowButton (frame, "arrow", args, n);
   XtManageChild (arrow);
   XtManageChild (frame);
   printf ("Setting the unit type to inches\n");

   XtRealizeWidget (Shell1);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNwidth, &width);			n++;
   XtSetArg (args[n], XmNheight, &height);			n++;
   XtGetValues (arrow, args, n);
   printf ("width = %d,   height = %d\n\n", (int)width, (int)height);
   width = 0; height = 0;
   CommonPause();

   LoopThruValues (arrow, 1, 4);

   CommonPause();

   /*  Change the unit type of the widget  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_MILLIMETERS);	n++;
   XtSetValues (arrow, args, n);
   printf ("Setting the unit type to millimeters\n");

   LoopThruValues (arrow, 1, 4);

   CommonPause();

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_MILLIMETERS);	n++;
   XtSetValues (arrow, args, n);

   printf ("Setting the size to (2000, 1000).\n");
   n = 0;
   XtSetArg (args[n], XmNwidth, 2000);			n++;
   XtSetArg (args[n], XmNheight, 1000);			n++;
   XtSetValues (arrow, args, n);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNwidth, &width);			n++;
   XtSetArg (args[n], XmNheight, &height);			n++;
   XtGetValues (arrow, args, n);
   printf ("width = %d,   height = %d\n\n", (int)width, (int)height);

   CommonPause();

   XtAppMainLoop(app_context);
   XtDestroyWidget(frame);
   XtDestroyWidget(arrow);
}

void LoopThruValues (widget, start, finish)
Widget widget;
int start, finish;
{
int k;
Dimension width, height;
Arg args[2];
int n;

   printf ("Expected\tReturned\t\n");
   for (k = start; k <= finish; k++) {
   /*  Set the size of the widget in millimeters  */
   n = 0;
   XtSetArg (args[n], XmNwidth, k * 1000); n++;
   XtSetArg (args[n], XmNheight, k * 1500); n++;
   XtSetValues (widget, args, n);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNwidth, &width);			n++;
   XtSetArg (args[n], XmNheight, &height);			n++;
   XtGetValues (widget, args, n);
   printf ("%d  %d\t%d  %d\n", k*1000, k*1500, 
	                           (int)width, (int)height);
   width = 0; height = 0;
   sleep (4);
   }
   printf ("\n");
   fflush (stdout);

}

static XtCallbackProc PrintSizes(widget, client_data, call_data)
    Widget   widget;
    caddr_t  client_data;
    caddr_t  call_data;
{
  Arg args[2];
  Dimension height, width;

  XtSetArg (args[0], XmNheight, &height);
  XtSetArg (args[1], XmNwidth, &width);
  XtGetValues (arrow, args, 2);

  printf ("User requested size...width %d...height %d\n", width, height);
  fflush (stdout);

}







