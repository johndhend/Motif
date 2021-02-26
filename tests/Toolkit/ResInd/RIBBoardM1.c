/* $TOG: RIBBoardM1.c /main/5 1999/01/14 18:10:07 jff $ */
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
 * Revision 1.1.2.2  92/05/05  20:38:19  msr
 * 	Created from BBoardM4.c
 * 	[1992/05/05  20:29:50  msr]
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

#include <testlib.h>

/*  Forward declarations  */

static void flushEvents();

void CheckStuff (w)
Widget w;
{
   Dimension width, height, borderWidth;
   Position x, y;
   int n;
   Arg args[5];
   
   n = 0;
   XtSetArg (args[n], XmNwidth, &width); n++;
   XtSetArg (args[n], XmNheight, &height); n++;
   XtSetArg (args[n], XmNborderWidth, &borderWidth); n++;
   XtSetArg (args[n], XmNx, &x); n++;
   XtSetArg (args[n], XmNy, &y); n++;
   XtGetValues (w, args, n);

   printf ("Height is %d\n", height);
   printf ("Width is %d\n", width);
   printf ("BorderWidth is %d\n", borderWidth);
   printf ("X is %d\n", x);
   printf ("Y is %d\n\n", y);

   fflush(stdout);

 }

void main (argc, argv)
int argc;
char **argv;
{
   Widget board, parent_board;
   Widget arrow;
   Arg args[20];
   int n;
   unsigned char unit_type;


   /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
   n = 0;
   XtSetArg(args[n], XmNx, 100); n++;
   XtSetArg(args[n], XmNy, 100); n++;
   XtSetArg(args[n], XmNborderWidth, 10); n++;
   parent_board = XmCreateBulletinBoard (Shell1, "board", args, n);


   n = 0;
   XtSetArg(args[n], XmNx, 100); n++;
   XtSetArg(args[n], XmNy, 100); n++;
   XtSetArg(args[n], XmNborderWidth, 10); n++;
   board = XmCreateBulletinBoard (parent_board, "board", args, n);


   n = 0;
   XtSetArg(args[n], XmNx, 50); n++;
   XtSetArg(args[n], XmNy, 50); n++;
   XtSetArg(args[n], XmNborderWidth, 5); n++;
   arrow = XmCreateArrowButton (board, "arrow", args, n);
   XtManageChild (arrow);
   XtManageChild (board);
   XtManageChild (parent_board);

   XtRealizeWidget (Shell1);

   flushEvents (XtDisplay(Shell1), 2);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNunitType, &unit_type);		n++;
   XtGetValues (arrow, args, n);
   PrintUnitType (unit_type);
   printf ("Resources for Parent Bulletin Board\n");
   CheckStuff (parent_board);
   printf ("Resources for Child Bulletin Board\n");
   CheckStuff (board);
   printf ("Resources for ArrowButton\n");
   CheckStuff (arrow);

   CommonPause();



   n = 0;
   XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES); n++;
   XtSetValues (board, args, n);
   XtDestroyWidget (arrow);

   n = 0;
   XtSetArg (args[n], XmNwidth, 1000); n++;
   XtSetArg (args[n], XmNheight, 1000); n++;
   arrow = XmCreateArrowButton (board, "arrow", args, n);
   XtManageChild (arrow);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNunitType, &unit_type);               n++;
   XtGetValues (arrow, args, n);
   PrintUnitType (unit_type);
   printf ("Resources for Parent Bulletin Board\n");
   CheckStuff (parent_board);
   printf ("Resources for Child Bulletin Board\n");
   CheckStuff (board);
   printf ("Resources for ArrowButton\n");
   CheckStuff (arrow);

   CommonPause();

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_MILLIMETERS); n++;
   XtSetValues (board, args, n);
   XtDestroyWidget (arrow);

   n = 0;
   XtSetArg (args[n], XmNwidth, 1000); n++;
   XtSetArg (args[n], XmNheight, 1000); n++;
   arrow = XmCreateArrowButton (board, "arrow", args, n);
   XtManageChild (arrow);
   
   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNunitType, &unit_type);               n++;
   XtGetValues (arrow, args, n);
   PrintUnitType (unit_type);
   printf ("Resources for Parent Bulletin Board\n");
   CheckStuff (parent_board);
   printf ("Resources for Child Bulletin Board\n");
   CheckStuff (board);
   printf ("Resources for ArrowButton\n");
   CheckStuff (arrow);
   CommonPause();

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_POINTS); n++;
   XtSetValues (board, args, n);
   XtDestroyWidget (arrow);

   n = 0;
   XtSetArg (args[n], XmNwidth, 1000); n++;
   XtSetArg (args[n], XmNheight, 1000); n++;
   arrow = XmCreateArrowButton (board, "arrow", args, n);
   XtManageChild (arrow);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNunitType, &unit_type);               n++;
   XtGetValues (arrow, args, n);
   PrintUnitType (unit_type);
   printf ("Resources for Parent Bulletin Board\n");
   CheckStuff (parent_board);
   printf ("Resources for Child Bulletin Board\n");
   CheckStuff (board);
   printf ("Resources for ArrowButton\n");
   CheckStuff (arrow);
   CommonPause();

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS); n++;
   XtSetValues (board, args, n);
   XtDestroyWidget (arrow);

   n = 0;
   arrow = XmCreateArrowButton (board, "arrow", args, n);
   XtManageChild (arrow);

   /*  Get the size of the widget in unit values  */
   n = 0;
   XtSetArg (args[n], XmNunitType, &unit_type);               n++;
   XtGetValues (arrow, args, n);
   PrintUnitType (unit_type);
   printf ("Resources for Parent Bulletin Board\n");
   CheckStuff (parent_board);
   printf ("Resources for Child Bulletin Board\n");
   CheckStuff (board);
   printf ("Resources for ArrowButton\n");
   CheckStuff (arrow);
   CommonPause();

   XtAppMainLoop(app_context);
}


PrintUnitType(UnitType)
int UnitType;
{

switch (UnitType) {
	case 0:	
   		printf ("unitType of the Arrow Button is %s\n\n", "XmPIXELS");
		break;
	case 1:
   		printf ("unitType of the Arrow Button is %s\n\n", "Xm100TH_MILLIMETERS");
		break;
	case 2:
   		printf ("unitType of the Arrow Button is %s\n\n", "Xm1000TH_INCHES");
		break;
	case 3:
   		printf ("unitType of the Arrow Button is %s\n\n", "Xm100TH_POINTS");
		break;
	case 4: 
		printf ("unitType of the Arrow Button is %s\n\n", "Xm100TH_FONT_UNITS");
		break;
	default:
		printf ("Not a valid Unit Type\n");
	};
}

static void flushEvents(display, delay)
Display * display;
int delay;
{
   XEvent event;
   while (XPending(display)) {
      XNextEvent(display, &event);
      XtDispatchEvent(&event);
   }
   sleep(delay);
}














