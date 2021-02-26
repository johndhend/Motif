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
static char rcsid[] = "$XConsortium: PanedWin10.c /main/4 1995/07/13 19:05:52 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

static void DoXY ();

#include <testlib.h>

#define	BUTTONS		3
#define B_WIDTH		100
#define B_HEIGHT	100
#define B_X		50
#define B_Y		50

/*  Global Variables  */

void  main(argc, argv)
int     argc;
char  **argv;
{
    register int  	n, i, j;
    Arg			args[MAX_ARGS];
    Widget		PW, PBarray[BUTTONS];
    Boolean	        resizable;
    

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0");  n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget(Shell1);

    /* Create the Paned Window and the buttons. */
    n = 0;
    PW = XmCreatePanedWindow(Shell1, "PW", args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, B_WIDTH / 2 ); n++; 
    XtSetArg(args[n], XmNheight, B_HEIGHT / 2 ); n++;  
    XtSetArg(args[n], XmNallowResize, False); n++; 

    for (i = 0; i < BUTTONS; i++) 
      {
	PBarray[i] = XmCreatePushButton(PW, "PB", args, n);
	XtManageChild(PBarray[i]);
      }
    
    XtManageChild(PW);  
    
    CommonPause();

    /* Try to resize each in turn with and without allowResize set. */

    /* With allowResize false. */
    for (i = 0; i < BUTTONS; i++)
      {
	n = 0;
	XtSetArg(args[n], XmNwidth, B_WIDTH); n++;
	XtSetArg(args[n], XmNheight, B_HEIGHT); n++;
	XtSetValues(PBarray[i], args, n);
	
      }

    CommonPause();

    /* Setting allowResize True for each button in turn. */

    for (j = 1; j <= BUTTONS; j++)
      {
	n = 0;
	XtSetArg(args[n], XmNallowResize, True); n++;
	XtSetValues(PBarray[j-1], args, n);
	    
	/* Increasing the size of each button. */
	for (i = 0; i < BUTTONS; i++)
	  {
	    n = 0;
	    XtSetArg(args[n], XmNwidth, 2 * B_WIDTH); n++;
	    XtSetArg(args[n], XmNheight, 2 * B_HEIGHT); n++;
	    XtSetValues(PBarray[i], args, n);
	
	  }

	CommonPause();
      }
    
    /* Setting allowResize False for each button in turn. */

    for (j = 1; j <= BUTTONS; j++)
      {
	n = 0;
	XtSetArg(args[n], XmNallowResize, False); n++;
	XtSetValues(PBarray[j-1], args, n);
	    
	/* Decreasing the size of each button. */
	for (i = 0; i < BUTTONS; i++)
	  {
	    n = 0;
	    XtSetArg(args[n], XmNwidth, B_WIDTH / 2 ); n++;
	    XtSetArg(args[n], XmNheight, B_HEIGHT / 2 ); n++;
	    XtSetValues(PBarray[i], args, n);
	
	  }

	CommonPause();
      }
    
    /* "Move" each in turn. */
    for (i = 0; i < BUTTONS; i++)
      {
	n = 0;
	XtSetArg(args[n], XmNx, B_X); n++;
	XtSetArg(args[n], XmNy, B_Y); n++;
	XtSetValues(PBarray[i], args, n);
	
	CommonPause();
      }

    XtDestroyWidget(PW);

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

