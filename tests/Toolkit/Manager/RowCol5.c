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
static char rcsid[] = "$XConsortium: RowCol5.c /main/6 1995/07/13 18:33:55 drk $"
#endif
#endif

/******************************************************************************
 *
 *
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#define MAXKID 10

Widget BBoard;
Widget RowColumn;
Widget Kid[MAXKID], newKid1, newKid2;

static void CreateRowColumn();

void  main(argc, argv)
int argc;
char **argv;
{
  register int  n;
  register int i;
  Arg args[MAX_ARGS];
  char label[80];
    
  CommonTestInit(argc, argv);

  CreateRowColumn(Shell1);
  XtRealizeWidget(Shell1);    

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, XmLAST_POSITION); n++;
  for (i = MAXKID - 2; i >= 0; i--)
    XtSetValues(Kid[i], args, n);
    
  CommonPause();
	

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 3); n++;
  newKid1 = XmCreatePushButton(RowColumn, "NewKid1", args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 9); n++;
  newKid2 = XmCreatePushButton(RowColumn, "NewKid2", args, n);
  CommonPause();
    
  
  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 0); n++;
  XtSetValues(newKid1, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 1); n++;
  XtSetValues(newKid2, args, n);

  n = 0;
  XtSetArg(args[n], XmNpositionIndex, XmLAST_POSITION); n++;
  XtSetValues(Kid[5], args, n);

  CommonPause();

  XtDestroyWidget(RowColumn);
  
  CommonPause();

  XtAppMainLoop(app_context);
}


static void CreateRowColumn(Widget Shell1)
{
  register int i;
  register int n;
  Arg args[MAX_ARGS];
  char label[80];


  n = 0;
  XtSetArg(args[n], XmNdefaultPosition, False); n++;
  BBoard = XmCreateBulletinBoardDialog(Shell1, "RowCol3", args, n);

  n = 0;
  XtSetArg(args[n], XmNpacking,    XmPACK_COLUMN); n++;
  XtSetArg(args[n], XmNnumColumns, 30); n++;
  XtSetArg (args[n], XmNtraversalOn, True); n++;
  RowColumn = XmCreateRowColumn(BBoard, "RowColumn", args, n);

  n = 0;  
  for (i = 0; i < MAXKID; i++) {
    sprintf(label, "Child%d", i);
    Kid[i] = XmCreatePushButton(RowColumn, label, args, n);
  }
  
  XtManageChildren(Kid, MAXKID);
  
  XtManageChild(RowColumn);
  XtManageChild(BBoard);
}






