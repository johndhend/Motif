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
static char rcsid[] = "$XConsortium: PanedWin11.c /main/4 1995/07/13 19:06:04 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#define CASES		4
#define	BUTTONS		3
#define B_WIDTH		100
#define B_HEIGHT	100
#define B_X		50
#define B_Y		50

/* Tests the effect of varios ways of changing the state of the child:
   unmap, map, unmanage, manage, destroy.
*/

void  main(argc, argv)
int     argc;
char  **argv;
{
    Boolean       	trace = False;
    register int  	n, i, j;
    Arg			args[MAX_ARGS], ONargs[MAX_ARGS], OFFargs[MAX_ARGS];
    int			ONn, OFFn;
    Widget		PW, PBarray[BUTTONS];

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0"); n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget(Shell1);
    
    /**	 These tests are for 1 each of 3 buttons in turn. 	**/

    /* Create the Paned Window and the buttons. */
    n = 0;
    PW = XmCreatePanedWindow(Shell1, "PW", args, n);

    n = 0;
    for (i = 0; i < BUTTONS; i++) 
      {
	PBarray[i] = XmCreatePushButton(PW, "PB", args, n);
	XtManageChild(PBarray[i]);
      }
    
    XtManageChild(PW);
    
    CommonPause();

    /* Unmap and remap each in turn. */
    for (i = 0; i < BUTTONS; i++)
      {
	n = 0;
	XtSetArg(args[n], XmNmappedWhenManaged, False); n++;
	XtSetValues(PBarray[i], args, n);
	
	CommonPause();

	n = 0;
	XtSetArg(args[n], XmNmappedWhenManaged, True); n++;
	XtSetValues(PBarray[i], args, n);

      }
    
    /* Manage and unmanage each in turn. */
    for (i = 0; i < BUTTONS; i++)
      {
	XtUnmanageChild(PBarray[i]);
	
	CommonPause();

	XtManageChild(PBarray[i]);
	
      }
    
    CommonPause();
    
    /* Destroy each of the three buttons in turn, recreating 
       window each time. */
    for (i = 0; i < BUTTONS; i++) 
      {
	n = 0;
	PW = XmCreatePanedWindow(Shell1, "PW", args, n);

	n = 0;
	XtSetArg(args[n], XmNwidth, B_WIDTH); n++;
	XtSetArg(args[n], XmNheight, 50); n++;
	for (j = 0; j < BUTTONS; j++) 
	  {
	    PBarray[j] = XmCreatePushButton(PW, "PB", args, n);
	    XtManageChild(PBarray[j]);
	  }
    
	XtManageChild(PW);
    
	CommonPause();
	XtDestroyWidget(PBarray[i]);
	
	CommonPause();
      }
     CommonPause();
      
    XtAppMainLoop(app_context);
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

