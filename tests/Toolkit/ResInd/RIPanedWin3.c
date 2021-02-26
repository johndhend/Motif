/* $TOG: RIPanedWin3.c /main/5 1999/01/14 18:38:27 jff $ */
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
 *  Create a vpaned in unit type of font_units, and get the sizes to ensure
 *  they correspond with the initial values.
 *
 *  Create a set of push buttons within the vpane using inches as the
 *  unit type and setting various resolution independent data.  Print
 *  out the data from a get values on each button.
 */

#include <signal.h>
#include <X11/StringDefs.h>

#include <testlib.h>

/*  Forward declarations  */

static void flushEvents();

DumpButtonData (w)
Widget w;
{
   Arg args[10];
   int n;

   Dimension width, height, shadowThickness, highlightThickness;
   short marginWidth, marginHeight;

   n = 0;
   XtSetArg (args[n], XmNwidth, &width);		n++;
   XtSetArg (args[n], XmNheight, &height);		n++;
   XtSetArg (args[n], XmNshadowThickness, &shadowThickness);		n++;
   XtSetArg (args[n], XmNhighlightThickness, &highlightThickness);	n++;
   XtSetArg (args[n], XmNmarginWidth, &marginWidth);	n++;
   XtSetArg (args[n], XmNmarginHeight, &marginHeight);		n++;
   XtGetValues (w, args, n);

   printf ("Data for Button\n");
   printf ("width = %d,   height = %d\n", width, height);
   printf ("shadow = %d,   highlight = %d\n", shadowThickness, highlightThickness);
   printf ("margin width = %d,   margin height = %d\n\n",
            marginWidth, marginHeight);
   
}

/*  main  */

void main (argc, argv)
int argc;
char **argv;
{
   Widget vpane;
   Widget pbuttons[10];
   Arg args[10];
   int n, i;
   Dimension width, height;

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);
    
   /*  The vpaned creation.  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS);	n++;
   XtSetArg (args[n], XmNwidth, 3000);	n++;
   XtSetArg (args[n], XmNheight, 4000);	n++;
   vpane = XmCreatePanedWindow (Shell1, "vpane", args, n);
   XtManageChild (vpane);

   flushEvents (XtDisplay(Shell1), 0);

   XtRealizeWidget (Shell1);

   n = 0;
   XtSetArg (args[n], XmNwidth, &width);	n++;
   XtSetArg (args[n], XmNheight, &height);	n++;
   XtGetValues (vpane, args, n);
   printf ("width = %d,  height = %d\n\n", width, height);

   CommonPause();

   /*  Create a set of buttons as children of the vpane  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS);	n++;
   XtSetArg (args[n], XmNwidth, 3000);       	n++;
   XtSetArg (args[n], XmNheight, 1000);	        n++;
   XtSetArg (args[n], XmNshadowThickness, 50);	n++;
   XtSetArg (args[n], XmNhighlightThickness, 100);	n++;
   XtSetArg (args[n], XmNhighlightOnEnter, True);	n++;
   pbuttons[0] = 
      XmCreatePushButtonGadget(vpane, "pushbuttongadget1", args, n);
   XtManageChild(pbuttons[0]);

   n = 0;
   XtSetArg (args[n], XmNmarginWidth, 3000);       	n++;
   XtSetArg (args[n], XmNmarginHeight, 100);	        n++;
   XtSetValues (pbuttons[0], args, n);

   DumpButtonData(pbuttons[0]);

   CommonPause();

   /*  Create a set of buttons as children of the vpane  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS);	n++;  
   XtSetArg (args[n], XmNwidth, 3000);       	n++;
   XtSetArg (args[n], XmNheight, 750);		n++;
   XtSetArg (args[n], XmNshadowThickness, 50);	n++;
   XtSetArg (args[n], XmNhighlightThickness, 100);	n++;
   XtSetArg (args[n], XmNhighlightOnEnter, True);	n++;
   XtSetArg (args[n], XmNmarginWidth, 3000);       	n++;
   XtSetArg (args[n], XmNmarginHeight, 100);	        n++;
   pbuttons[1] = 
      XmCreatePushButtonGadget(vpane, "pushbuttongadget2", args, n);
   XtManageChild(pbuttons[1]);

   DumpButtonData(pbuttons[1]);

   CommonPause();

   /*  Create a set of buttons as children of the vpane  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS);	n++;
   XtSetArg (args[n], XmNwidth, 3000);       	n++;
   XtSetArg (args[n], XmNheight, 500);	        n++;
   XtSetArg (args[n], XmNshadowThickness, 50);	n++;
   XtSetArg (args[n], XmNhighlightThickness, 100);	n++;
   XtSetArg (args[n], XmNhighlightOnEnter, True);	n++;
   pbuttons[2] = 
      XmCreatePushButtonGadget(vpane, "pushbuttongadget3", args, n);
   XtManageChild (pbuttons[2]);

   DumpButtonData(pbuttons[2]);

   CommonPause();

   /*  Create a set of buttons as children of the vpane  */

   n = 0;
   XtSetArg (args[n], XmNunitType, Xm100TH_FONT_UNITS);	n++;  
   XtSetArg (args[n], XmNwidth, 3000);       	n++;
   XtSetArg (args[n], XmNheight, 1000);	        n++;
   XtSetArg (args[n], XmNshadowThickness, 50);	n++;
   XtSetArg (args[n], XmNhighlightThickness, 100);	n++;
   XtSetArg (args[n], XmNhighlightOnEnter, True);	n++;
   pbuttons[3] = 
      XmCreatePushButtonGadget(vpane, "pushbuttongadget4", args, n);
   XtManageChild (pbuttons[3]);
   DumpButtonData(pbuttons[3]);
   CommonPause();
   XtAppMainLoop(app_context);
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

