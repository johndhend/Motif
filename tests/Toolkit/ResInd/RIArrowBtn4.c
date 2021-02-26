/* $XConsortium: RIArrowBtn4.c /main/4 1995/07/15 21:08:26 drk $ */
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

unsigned char UnitType[4] = { Xm1000TH_INCHES, 
			      Xm100TH_POINTS,
  			      Xm100TH_MILLIMETERS,
			      Xm100TH_FONT_UNITS };

void main (argc, argv)
int argc;
char **argv;
{
  Widget 	  arrow;
  Arg 		  args[20];
  int 		  n;
  Dimension	  width, height;
  unsigned char  unitType;
  int		  i;



   /*  initialize toolkit  */
  CommonTestInit(argc, argv);
    

  n = 0;
  XtSetArg(args[n], XmNwidth, 100);		n++;
  XtSetArg(args[n], XmNheight, 100);		n++;
  arrow = XmCreateArrowButton (Shell1, "arrow", args, n);
  XtManageChild (arrow);

  XtRealizeWidget (Shell1);
  flushEvents (XtDisplay(Shell1), 2);

  /*  Get the size of the widget in unit values  */
  n = 0;
  XtSetArg (args[n], XmNunitType, &unitType);	n++;
  XtSetArg (args[n], XmNwidth, &width);		n++;
  XtSetArg (args[n], XmNheight, &height);		n++;
  XtGetValues (arrow, args, n);
  PrintUnitType (unitType);
  printf("Width = %d , Height = %d\n\n", width, height);

  CommonPause();

  for (i = 0 ; i < 4; i++)
    {
      n = 0;
      XtSetArg (args[n], XmNunitType, UnitType[i]); n++;
      XtSetValues (arrow, args, n);

      /*  Get the size of the widget in unit values  */
      n = 0;
      XtSetArg (args[n], XmNunitType, &unitType);	n++;
      XtSetArg (args[n], XmNwidth, &width);		n++;
      XtSetArg (args[n], XmNheight, &height);		n++;
      XtGetValues (arrow, args, n);
      PrintUnitType (unitType);
      printf("Width = %d , Height = %d\n\n", width, height);

      CommonPause();
    }

  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(arrow);
}

PrintUnitType(UnitType)
int UnitType;
{

  switch (UnitType) {
  case 0:	
    printf ("unitType = %s\n", "XmPIXELS");
    break;
  case 1:
    printf ("unitType = %s\n", "Xm100TH_MILLIMETERS");
    break;
  case 2:
    printf ("unitType = %s\n", "Xm1000TH_INCHES");
    break;
  case 3:
    printf ("unitType = %s\n", "Xm100TH_POINTS");
    break;
  case 4: 
    printf ("unitType = %s\n", "Xm100TH_FONT_UNITS");
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
