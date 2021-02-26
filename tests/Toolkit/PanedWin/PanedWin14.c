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
static char rcsid[] = "$XConsortium: PanedWin14.c /main/4 1995/07/13 19:06:46 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <X11/StringDefs.h>
#include <Xm/XmP.h>

/*  Global  */

Widget  XmVPanedWindow1 = NULL;
Widget  PushButton1 = NULL;
Widget  PushButton2 = NULL;
Widget  PushButton3 = NULL;
Widget  Manager1 = NULL;
Widget  Manager2 = NULL;
Widget  Manager3 = NULL;

char *string1 = "\
Buttons 1 and 2 are 150 in height, Button 3 is 80.  Pane minimum\n\
is 100.  Try to resize panes smaller than their minimum. \n\
Press Alt-F8 (or pull down Size from the client's window menu)\n\
and take note fo the current height of the client.";

char *string2 = "\
 Minimums for each pane now set at their current size. You should\n\
 not be able to make any pane smaller.\n\
 Because the Paned Window's top and bottom margins were increased,\n\
 the Pane and Shell should grow by about 100 pixels to\n\
 accomodate the mimimums and margins. \n\
 Again take note of the current height of the client.";

void MakeChildUnresizable();
void PrintProcessInfo();

void  main (argc, argv)
int     argc;
char  **argv;
{
    int                delay = 0;
    register int       n;
    Arg                args[MAX_ARGS];
    XmString           tcs = NULL;
    XWindowAttributes  info;
    XEvent             DummyEvent;
    Dimension          currentHeight, currentWidth;
    Widget             ManagerKids[10];
    static int         kidCount = 0;

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
  
    XmRegisterConverters();

    n = 0;
    XmVPanedWindow1 = XmCreatePanedWindow(Shell1, "XmVPanedWindow1",
                    args, n);
    XtManageChild(XmVPanedWindow1);

    n = 0;
    XtSetArg(args[n], XmNheight,  150); n++;
    XtSetArg(args[n], XmNpaneMinimum, 100); n++;
    PushButton1 = XmCreatePushButton(XmVPanedWindow1, "PushButton1",
                    args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg(args[n], XmNheight,  150); n++;
    XtSetArg(args[n], XmNpaneMinimum, 100); n++;
    PushButton2 = XmCreatePushButton(XmVPanedWindow1, "PushButton2",
                    args, n);
    XtManageChild(PushButton2);
    XmStringFree(tcs);

    n = 0;
    XtSetArg(args[n], XmNheight,  80); n++;
    XtSetArg(args[n], XmNpaneMinimum, 100); n++;
    PushButton3 = XmCreatePushButton(XmVPanedWindow1, "PushButton3",
                    args, n);
    XtManageChild(PushButton3);
    XmStringFree(tcs);

    XtRealizeWidget(Shell1);

    CommonPause();

    /* set the minimumSize of each button to its current height */

    MakeChildUnresizable(PushButton1);
    MakeChildUnresizable(PushButton2);
    MakeChildUnresizable(PushButton3);

    /* now increase the margin on the Paned Window */

    n = 0;
    XtSetArg(args[n], XmNmarginHeight, 50);   n++;
    XtSetValues(XmVPanedWindow1, args, n);

    CommonPause();

    /* let's try other geometric deprivations and see if the paned window */
    /* can get its act together */

    n = 0;
    XtSetArg (args[n], XmNsashWidth, 20); n++;           
    XtSetArg (args[n], XmNsashHeight, 20); n++;          
    XtSetArg (args[n], XmNsashShadowThickness, 5); n++; 
    XtSetArg (args[n], XmNspacing, 20); n++;             
    XtSetValues (XmVPanedWindow1, args, n);

    CommonPause();

    /* the desired effect is the same as in panedWin.uil */
    /* the separators are OFF and the sash extends across the width of the */
    /* paned window. Gives a nice sort of bar to grab and move the sash */
  
    n = 0;
    XtSetArg (args[n], XmNwidth, &currentWidth); n++;
    XtGetValues (XmVPanedWindow1, args, n); 
      
    n = 0;
    XtSetArg (args[n], XmNsashWidth, currentWidth); n++;
    XtSetArg (args[n], XmNseparatorOn, False); n++;
    XtSetValues (XmVPanedWindow1, args, n);

    /* also, reduce minimum of buttons so we can move sashes a bit */

    n = 0;
    XtSetArg(args[n], XmNheight, &currentHeight); n++;
    XtGetValues(PushButton1, args, n);
    printf ("Current height of PushButton1 is %d\n", currentHeight);
    n = 0;
    XtSetArg(args[n], XmNallowResize, True); n++;
    XtSetArg(args[n], XmNpaneMinimum, currentHeight - 50); n++;
    printf ("   Setting paneMimimum to %d\n", currentHeight);
    XtSetValues(PushButton1, args, n);

    n = 0;
    XtSetArg(args[n], XmNheight, &currentHeight); n++;
    XtGetValues(PushButton2, args, n);
    printf ("Current height of PushButton2 is %d\n", currentHeight);
    n = 0;
    XtSetArg(args[n], XmNallowResize, True); n++;
    XtSetArg(args[n], XmNpaneMinimum, currentHeight - 50); n++;
    printf ("   Setting paneMimimum to %d\n", currentHeight);
    XtSetValues(PushButton2, args, n);

    n = 0;
    XtSetArg(args[n], XmNheight, &currentHeight); n++;
    XtGetValues(PushButton3, args, n);
    printf ("Current height of PushButton3 is %d\n", currentHeight);
    n = 0;
    XtSetArg(args[n], XmNallowResize, True); n++;
    XtSetArg(args[n], XmNpaneMinimum, currentHeight - 50); n++;
    printf ("   Setting paneMimimum to %d\n", currentHeight);
    XtSetValues(PushButton3, args, n);

    CommonPause();

    /* as discussed on motif-talk, try same stuff with manager children */
    /* First, we need to make the managers and put some stuff in 'em */
    /* Then destroy the existing children and replace them with these guys */

    /* turn separators back on  default-style*/
    n = 0;
    XtSetArg (args[n], XmNseparatorOn, True); n++;
    XtSetArg (args[n], XmNsashWidth, 10); n++;
    XtSetArg (args[n], XmNsashHeight, 10); n++;
    XtSetValues (XmVPanedWindow1, args, n);

    n = 0;
    /*    XtSetArg (args[n], XmNborderWidth, 50); n++; */
    Manager1 = XmCreateBulletinBoard (XmVPanedWindow1, "Manager1", args, n);
    
    n = 0;
    XtSetArg (args[n], XmNlabelString, 
	      XmStringCreateSimple ("A refreshing alternative")); n++;
    ManagerKids[kidCount] = XmCreateLabel (Manager1, "Label1", args, n);
    XtManageChild(ManagerKids[kidCount]);
    kidCount++; 
    
    XtDestroyWidget(PushButton1);
    XtManageChild (Manager1); 

    MakeChildUnresizable(Manager1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNresizeHeight, True); n++;
    XtSetArg(args[n], XmNvalue, string1); n++;
    Manager2 = XmCreateScrolledText(XmVPanedWindow1, "Manager2", args, n);
    
    XtDestroyWidget(PushButton2);
    XtManageChild (Manager2); 

    MakeChildUnresizable(Manager2);    

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNresizeHeight, False); n++;
    XtSetArg(args[n], XmNvalue, string2); n++;
    Manager3 = XmCreateScrolledText(XmVPanedWindow1, "Manager2", args, n);
    
    XtDestroyWidget(PushButton3);
    XtManageChild (Manager3); 

    MakeChildUnresizable(Manager3);    

    CommonPause();
  
    XtAppMainLoop(app_context);
}

void MakeChildUnresizable (child)
Widget child;
{
  Dimension currentHeight;
  int n;
  Arg args[10];
  XtGeometryResult result;
  XtWidgetGeometry preferred;
  Boolean setValuesMethod;
  Dimension one_pixel = (Dimension) 1;

  if ((!XmIsManager(child)) && !(XmIsScrolledWindow(XtParent(child)))) {
    setValuesMethod = True;
    n = 0;
    XtSetArg(args[n], XmNheight, &currentHeight); n++;
    XtGetValues(child, args, n);

  }
  else {
    setValuesMethod = False;
    result = XtQueryGeometry(child, NULL, &preferred);
    currentHeight = preferred.height;
  }

  printf ("Current height of child is %d\n", currentHeight);
  n = 0;
  XtSetArg(args[n], XmNallowResize, True); n++;
  XtSetArg(args[n], XmNpaneMinimum, currentHeight); n++;
  XtSetArg(args[n], XmNpaneMaximum, currentHeight); n++;
  XtSetValues(child, args, n);

  printf ("Using the %s method...\n", 
	  (setValuesMethod == True ? "setValues" : "queryGeometry"));

  n = 0;
  XtSetArg(args[n], XmNpaneMinimum, &currentHeight); n++;
  XtGetValues(child, args, n);
  printf ("Have set paneMinimum to %d ", currentHeight);

  n = 0;
  XtSetArg(args[n], XmNpaneMaximum, &currentHeight); n++;
  XtGetValues(child, args, n);
  printf ("and paneMaximum to %d\n\n", currentHeight);

}

void PrintProcessInfo ()
{

char thingie[15];

sprintf (thingie, "-v#%d", getpid());

if (fork () != 0) /* parent */
  wait ((int *) 0);
else
  {  execl ("/bin/ps", "ps", thingie, (char *) 0);
     exit (0);
   }

}
