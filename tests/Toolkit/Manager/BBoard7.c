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
static char rcsid[] = "$XConsortium: BBoard7.c /main/8 1995/07/13 18:27:13 drk $"
#endif
#endif
/*
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget          Shell;
Widget  BulletinBoard;
Widget         Child1;
Widget         Child2;
Widget         Child3;
Widget         Child4;

static void            die();
static void            RunTest();
static void            CreateBulletinBoard();
static void            DestroyBulletinBoard();

void  main(argc, argv)
     int     argc;
     char    **argv;
{
  register int  n;
  Arg           args[MAX_ARGS];
  
  CommonTestInit(argc, argv);

  RunTest(Shell1);

  XtRealizeWidget(Shell1);    

  XtAppMainLoop(app_context);
}

static void RunTest(Shell1)
Widget Shell1;
{
  register int  i;
  register int  n;
  Arg           args[MAX_ARGS];
  
    
    CreateBulletinBoard(Shell1);
    
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNx, 0);                                    n++;
    XtSetArg(args[n], XmNy, 0);                                    n++;
    XtSetValues(Child1, args, n);
        
    n = 0;
    XtSetArg(args[n], XmNx, 200);                                  n++;
    XtSetArg(args[n], XmNy, 0);                                    n++;
    XtSetValues(Child2, args, n);
    
    n = 0;
    XtSetArg(args[n], XmNx, 0);                                    n++;
    XtSetArg(args[n], XmNy, 200);                                  n++;
    XtSetValues(Child3, args, n);
    
    n = 0;
    XtSetArg(args[n], XmNx, 200);                                  n++;
    XtSetArg(args[n], XmNy, 200);                                  n++;
    XtSetValues(Child4, args, n);
    
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                              n++;
    XtSetArg(args[n], XmNheight, 100);                             n++;
    XtSetValues(Child1, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                              n++;
    XtSetArg(args[n], XmNheight, 100);                             n++;
    XtSetValues(Child2, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                              n++;
    XtSetArg(args[n], XmNheight, 100);                             n++;
    XtSetValues(Child3, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                              n++; 
    XtSetArg(args[n], XmNheight, 100);                             n++;
    XtSetValues(Child4, args, n);
    
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 200);                              n++;
    XtSetArg(args[n], XmNheight, 200);                             n++;
    XtSetValues(Child1, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 200);                              n++;
    XtSetArg(args[n], XmNheight, 200);                             n++;
    XtSetValues(Child2, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 200);                              n++;
    XtSetArg(args[n], XmNheight, 200);                             n++;
    XtSetValues(Child3, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 200);                              n++;
    XtSetArg(args[n], XmNheight, 200);                             n++;
    XtSetValues(Child4, args, n);
    
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 300);                              n++;
    XtSetArg(args[n], XmNheight, 300);                             n++;
    XtSetValues(Child1, args, n); 

    n = 0;
    XtSetArg(args[n], XmNwidth, 300);                              n++;
    XtSetArg(args[n], XmNheight, 300);                             n++;
    XtSetValues(Child2, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 300);                              n++;
    XtSetArg(args[n], XmNheight, 300);                             n++;
    XtSetValues(Child3, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 300);                              n++;
    XtSetArg(args[n], XmNheight, 300);                             n++;
    XtSetValues(Child4, args, n);
    
    CommonPause();

    CommonPause();

    DestroyBulletinBoard();
  
}

static void CreateBulletinBoard(Shell1)
Widget Shell1;
{
  register int  n;
  Arg           args[MAX_ARGS];
  
  n = 0;
  XtSetArg(args[n], XmNx, 200);                                  n++;
  XtSetArg(args[n], XmNy, 200);                                  n++;
  XtSetArg(args[n], XmNallowShellResize, True);                  n++;
  Shell = XmCreateDialogShell(Shell1, "BBoard7", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNwidth, 200);                              n++;
  XtSetArg(args[n], XmNheight, 200);                             n++;
  XtSetArg(args[n], XmNautoUnmanage, False);                     n++;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_ANY);              n++;
  XtSetArg(args[n], XmNallowOverlap, False);                     n++;
  BulletinBoard = XmCreateBulletinBoard(Shell, "BBoard", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNx, 0);                                    n++;
  XtSetArg(args[n], XmNy, 0);                                    n++;
  Child1 = XmCreatePushButton(BulletinBoard, "Child1", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 100);                                  n++;
  XtSetArg(args[n], XmNy, 0);                                    n++;
  Child2 = XmCreatePushButton(BulletinBoard, "Child2", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 0);                                    n++;
  XtSetArg(args[n], XmNy, 100);                                  n++;
  Child3 = XmCreatePushButton(BulletinBoard, "Child3", args, n);

  n = 0;
  XtSetArg(args[n], XmNx, 100);                                  n++;
  XtSetArg(args[n], XmNy, 100);                                  n++;
  Child4 = XmCreatePushButton(BulletinBoard, "Child4", args, n);
  
  XtManageChild(Child1);
  XtManageChild(Child2);
  XtManageChild(Child3);
  XtManageChild(Child4);
  
  XtManageChild(BulletinBoard);
  XtRealizeWidget(Shell);
}

static void DestroyBulletinBoard()
{
  XtDestroyWidget(Shell);
}
