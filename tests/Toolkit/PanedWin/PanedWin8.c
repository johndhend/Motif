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
static char rcsid[] = "$XConsortium: PanedWin8.c /main/4 1995/07/13 19:07:48 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

static void DoXY ();

#define	BUTTONS		3
#define B_X		50
#define B_Y		50
#include <testlib.h>

/* Test what happens when initial X and Y of children are set and 
   when XmNseparatorOn is set false. */

void  main(argc, argv)
int     argc;
char  **argv;
{
    Boolean       	trace = False;
    register int  	n, i;
    Arg			args[MAX_ARGS];

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0");  n++;
    XtSetValues(Shell1, args, n);
    XtRealizeWidget(Shell1);

    for (i = 0; i < BUTTONS; i++) 
      {
	DoXY(i);
      }
    
    CommonPause();
   
    XtAppMainLoop(app_context);
}

static void DoXY(i)
int i;
{
  register int  	n, j;
  Arg			args[MAX_ARGS];
  Widget		PW, PB;

  /* Set X. */
  n = 0;
  XtSetArg(args[n], XmNseparatorOn, False); n++; 
  PW = XmCreatePanedWindow(Shell1, "PW", args, n);
  
  for (j = 0; j < BUTTONS; j++) 
    {
      n = 0;
      PB = XmCreatePushButton(PW, "PB1", args, n);
      XtManageChild(PB);
    }

  XtManageChild(PW);

  CommonPause();
  
  XtDestroyWidget(PW);
  
  /* Set Y. */
  n = 0;
  PW = XmCreatePanedWindow(Shell1, "PW", args, n);
  
  for (j = 0; j < BUTTONS; j++)
    {
      n = 0;
      
      if (j == i) 
	{
	  XtSetArg(args[n], XmNy, B_Y); n++;  
	}
      
      PB = XmCreatePushButton(PW, "PB1", args, n);

      XtManageChild(PB);
    }

  XtManageChild(PW);
  
  CommonPause();
  
  XtDestroyWidget(PW);
  
  /* Set both. */
  n = 0;
  PW = XmCreatePanedWindow(Shell1, "PW", args, n);
  
  for (j = 0; j < BUTTONS; j++)
    {
      n = 0;

      if (j == 1) 
	{
	  XtSetArg(args[n], XmNx, B_X); n++;  
	  XtSetArg(args[n], XmNy, B_Y); n++;  
	}
      
      PB = XmCreatePushButton(PW, "PB1", args, n);

      XtManageChild(PB);
    }
  
  XtManageChild(PW);

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

