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
static char rcsid[] = "$XConsortium: PanedWin7.c /main/4 1995/07/13 19:07:35 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <testlib.h>

/* Tests what happens when children's intial sizes are larger than */
/* paned windows initial size. */

#define	BUTTONS		3
#define B_WIDTH		100
#define B_HEIGHT	100
#define W_MARGIN	-25

/* Internal functions. */
static void DoTheButtons();
static void DoTheWindows(); 
static void ReportSize(); 

void  main(argc, argv)
int     argc;
char  **argv;
{
    Boolean       	trace = False;
    register int  	n, i;
    Arg			args[MAX_ARGS], PWargs[MAX_ARGS];
    int			PWn;

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0");  n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget(Shell1);
    
    /* Do all cases for 1 to BUTTONS. */
    for (i = 0; i < BUTTONS; i++) 
      {
	/* Paned window with nothing set. */
	PWn = 0;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with width set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNwidth, B_WIDTH + W_MARGIN); PWn++;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with height set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNheight, (B_HEIGHT + W_MARGIN) * i ); PWn++;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with both set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNwidth, B_WIDTH + W_MARGIN); PWn++;
	XtSetArg(PWargs[PWn], XmNheight, (B_HEIGHT + W_MARGIN) * i ); PWn++;
	DoTheButtons(i, PWargs, PWn);

      }
    
    CommonPause();
    XtAppMainLoop(app_context);
}

static void DoTheButtons(num, PWargs, PWn)
     int 	num;
     Arg	PWargs[];
     int	PWn;
{
  Arg          	PBargs[MAX_ARGS];
  int		PBn;
  
  /* Nothing set. */
  PBn = 0;
  
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);
  
  /* Width set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNwidth, B_WIDTH); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

  /* Height set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNheight, B_HEIGHT); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

  /* Both set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNwidth, B_WIDTH); PBn++;
  XtSetArg(PBargs[PBn], XmNheight, B_HEIGHT); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

}

static void DoTheWindows(num, PWargs, PWn, PBargs, PBn)
     int	num;
     Arg	PWargs[];
     int	PWn;
     Arg	PBargs[];
     int	PBn;
{
  register int	i;
  Widget	PW, PB;
  
  PW = XmCreatePanedWindow(Shell1, "PW", PWargs, PWn);
  for (i = 0; i <= num; i++)
    {
      PB = XmCreatePushButton(PW, "PB", PBargs, PBn);
      XtManageChild(PB);
    }
  XtManageChild(PW);
  ReportSize(PW);
  CommonPause();
  XtDestroyWidget(PW);
  
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

