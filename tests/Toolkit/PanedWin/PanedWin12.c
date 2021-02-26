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
static char rcsid[] = "$XConsortium: PanedWin12.c /main/5 1995/08/29 15:22:48 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <testlib.h>
/* the following is an experiment which should work on all platforms*/
#if defined(__STDC__)
#include <stdlib.h>
#endif
#include <Xm/SashP.h>

#define RANGE		100
#define	BUTTONS		10
#define B_X		50
#define B_Y		50

/*  Global Variables  */

static Cardinal NewInsertOrder ();

/* Test Paned Window creation with a new insertPosition function. */

void  main(argc, argv)
int     argc;
char  **argv;
{
    register int  	n, i;
    Arg			args[MAX_ARGS];
    char		name[10];
    Widget		PW, PB, PB1, PB2, PB3, PB4, PB5;
    int			b_value;
    short               get_val;

    srand((int) time(NULL));

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0");  n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget(Shell1);

    n = 0;
    XtSetArg(args[n], XmNinsertPosition, (XtOrderProc *) NewInsertOrder); n++;
    PW = XmCreatePanedWindow(Shell1, "PW", args, n);

    XtSetValues(PW, args, n); 	/* Ignored at creation? */
	
    for (i = 0; i < BUTTONS; i++) 
      {
	b_value = rand() % RANGE;
	sprintf(name, "PB%2d:%3d", i, b_value);
	    
	n = 0;
	XtSetArg(args[n], XmNuserData, b_value); n++;
	XtSetArg(args[n], XmNwidth, 150); n++;
	PB = XmCreatePushButton(PW, name, args, n);
	XtManageChild(PB);
      }
	
    XtManageChild(PW);
    CommonPause();
    XtDestroyWidget(PW);

    /* 
     * Add tests for 1.2 XmNpositionIndex functionality
     */

#ifndef MOTIF1_1

    n = 0;
    PW = XmCreatePanedWindow(Shell1, "PW", args, n);
    
    /*
     * Put some children in it
     */
    
    n = 0;
    XtSetArg(args[n], XmNwidth, 100); n++;
    PB1 = XmCreatePushButton(PW, "PB1", args, n);
    XtManageChild(PB1);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100); n++;
    PB2 = XmCreatePushButton(PW, "PB2", args, n);
    XtManageChild(PB2);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100); n++;
    PB3 = XmCreatePushButton(PW, "PB3", args, n);
    XtManageChild(PB3);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100); n++;
    PB4 = XmCreatePushButton(PW, "PB4", args, n);
    XtManageChild(PB4);
    XtManageChild(PW);
    CommonPause();

    /*
     * Change the last child first
     */
    
    n = 0;
    XtSetArg(args[n], XmNpositionIndex, 0); n++;
    XtSetValues(PB4, args, n);
    
    n = 0;
    XtSetArg(args[n], XmNpositionIndex, &get_val); n++;
    XtGetValues(PB4, args, n);
    printf("Value of PB4 XmNpositionIndex = %d\n", get_val);
     
    CommonPause();

    
    /*
     * Mix up the middle ones
     */

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, 1); n++;
    XtSetValues(PB3, args, n);

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, &get_val); n++;
    XtGetValues(PB3, args, n);
    printf("Value of PB3 XmNpositionIndex = %d\n", get_val);
    CommonPause();

    /*
     * Add a new child to the end
     */
    
    n = 0;
    XtSetArg(args[n], XmNpositionIndex, XmLAST_POSITION); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    PB5 = XmCreatePushButton(PW, "PB5", args, n);
    XtManageChild(PB5);

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, &get_val); n++;
    XtGetValues(PB5, args, n);
    printf("Value of PB5 XmNpositionIndex = %d\n", get_val);

    CommonPause();

    /*
     *  Set an illegal value for XmNpositionIndex and see if it ralphs
     */
    
    n = 0;
    XtSetArg(args[n], XmNpositionIndex, 7); n++;
    XtSetValues(PB5, args, n);

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, &get_val); n++;
    XtGetValues(PB5, args, n);
    printf("Value of PB5 XmNpositionIndex = %d\n", get_val);

    CommonPause();

    /*
     * Set XmNpositionIndex = -2 and see what happens.
     */

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, -2); n++;
    XtSetValues(PB4, args, n);

    n = 0;
    XtSetArg(args[n], XmNpositionIndex, &get_val); n++;
    XtGetValues(PB4, args, n);
    printf("Value of PB4 XmNpositionIndex = %d\n", get_val);

    CommonPause();

    CommonPause();  /* Exit */

#endif

    XtAppMainLoop(app_context);
}

/***************************************************************************
 *
 * static Cardinal
 * NewInsertOrder (w)
 *
 *   This function searches through the composite widget's list of children
 *   to find the correct insertion position for the new child.  If the
 *   new child is an ordinary child (not a subclass of XmSashWidget)
 *   the position returned will cause it to be inserted sorted based on the
 *   value of XmNuserData within the other
 *   ordinary children but before any Sashs; if the new child is a 
 *   sash the position returned will cause it to be inserted at the
 *   end of the list.  This procedure does not examine the arglist.
 *
 ************************************************************************/


static Cardinal NewInsertOrder (w)
Widget w;         /* Composite widget being inserted into */
{
   CompositeWidget cw = (CompositeWidget) XtParent(w);
   Cardinal i=0;

   if (XmIsSash(w) || XmIsSeparatorGadget(w)) 
     {
       while ((i < cw->composite.num_children) &&
	      (! XmIsSash(cw->composite.children[i])) &&
	      (! XmIsSeparatorGadget(cw->composite.children[i])))
	 i++;
     }
   else
     {
       while ((i < cw->composite.num_children) &&
	      ((long) ((XmPrimitiveWidget) w)->primitive.user_data < 
	       (long) ((XmPrimitiveWidget)
		      (cw->composite.children[i]))->primitive.user_data) &&
	      (! XmIsSash(cw->composite.children[i])) &&
	      (! XmIsSeparatorGadget(cw->composite.children[i])))
	 i++;
     }

   return (i);
}

static void ReportSize (w)
     Widget w;
{
  register int	n;
  Arg		args[2];
  Dimension	width, height;
    
  n = 0;
  XtSetArg(args[n], XmNwidth, &width); n++;
  XtSetArg(args[n], XmNheight, &height); n++;
  XtGetValues(w, args, n);
  
  printf("%dX%d\n", (int)width, (int)height);
}





