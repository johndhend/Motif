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
static char rcsid[] = "$XConsortium: RowCol1.c /main/8 1995/07/13 18:33:07 drk $"
#endif
#endif

/******************************************************************************
 *
 *
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include "testlib.h"

#define WIDTH 50

Widget Shell, RowColumn, Child[6];

static void EntryCallbackProc (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;
{
  printf ("The entry callback being called\n");
}

static void die();
static void RunTest();
static void CreateRowColumn();
static void DestroyRowColumn();

void  main(argc, argv)
int argc;
char **argv;
{
  register int  n;
  Arg args[MAX_ARGS];
  
  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);


  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_TIGHT); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;

  CreateRowColumn(Shell1, args, n);
  CommonPause();
  DestroyRowColumn();
  CreateRowColumn(Shell1, args, n);
  CommonPause();
  DestroyRowColumn();

  n  = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_NONE); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;

  CreateRowColumn(Shell1, args, n);
  CommonPause();
  DestroyRowColumn();
  CreateRowColumn(Shell1, args, n);
  CommonPause();
  DestroyRowColumn();
  
  XtRealizeWidget(Shell1);    
  XtAppMainLoop(app_context);
}

static void CreateRowColumn(Shell1, RCArgList, numRCArgs)
Widget Shell1;
Arg *RCArgList;
int numRCArgs;
{
  register int  n;
  register int  i;
  Arg           ChildArgList[MAX_ARGS];
  Arg           args[MAX_ARGS];
  static  short         flag = 1;
  Dimension width;
  char buf[16];
  
  n = 0;
  XtSetArg(args[n], XmNx, 200);                                  n++;
  XtSetArg(args[n], XmNy, 200);                                  n++;
  XtSetArg(args[n], XmNallowShellResize, True);                  n++;
  Shell = XmCreateDialogShell(Shell1, "RowCol1", args, n);
  
  RowColumn = XmCreateRowColumn(Shell, "RowColumn1", RCArgList, numRCArgs);
  XtAddCallback (RowColumn, XmNentryCallback, EntryCallbackProc, NULL);
  XtManageChild(RowColumn);
  

    { 
      for (i = 0; i <= 5; i++)
	{
          n = 0;
	  sprintf (buf, "Child%d", i);
	  Child[i] = XmCreatePushButton(RowColumn, buf, ChildArgList , n);
	  XtManageChild (Child[i]);
	  flag = 2;
        }
    }
    { 
      for (i = 0; i <= 5; i++)
	{   
	  n = 0;
	  sprintf (buf, "Child%d", i);
	  XtSetArg(ChildArgList[n], XmNwidth, WIDTH); n++;
	  XtSetArg(ChildArgList[n], XmNrecomputeSize, False);  n++;
	  Child[i] = XmCreatePushButton(RowColumn, buf, ChildArgList , n);
	  printf ("Width requested by child %d is %d\n", i, WIDTH);
	  XtManageChild (Child[i]);

	  n = 0;
	  XtSetArg(ChildArgList[n], XmNwidth, &width); n++;
	  XtGetValues (Child[i], ChildArgList, n);
	  printf("Width returned by GetValues for child %d is %d\n", 
		 i, (int)width);
	  flag = 1;
        }
    }
  

  XtRealizeWidget(Shell);
}

static void DestroyRowColumn()
{
  XtDestroyWidget(Shell);
}
