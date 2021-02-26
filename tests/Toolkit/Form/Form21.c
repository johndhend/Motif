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
static char rcsid[] = "$XConsortium: Form21.c /main/4 1995/07/13 18:06:43 drk $"
#endif
#endif
/*
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#define MAXTEXT 4

Widget DialogShell;
Widget ScrollWin;
Widget Form;
Widget Text[MAXTEXT];

static void            die();
static void            RunTest();
static void            CreateForm();
static void            DestroyForm();
static void            PrintValues();

void  main(argc, argv)
int     argc;
char    **argv;
{
  register int  n;
  Arg args[MAX_ARGS];
  
  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg (args[n], XmNwidth,  50);                               n++;
  XtSetArg (args[n], XmNheight, 25);                               n++;
  XtSetValues(Shell1, args, n);
    
  XtRealizeWidget(Shell1);    

  RunTest(Shell1);

  XtAppMainLoop(app_context);
}

static void RunTest(Shell)
Widget Shell;
{
  register int  i;
  register int  n;
  Arg args[MAX_ARGS];

  CreateForm(Shell);
  CommonPause();
    
  for (i = 0; i < MAXTEXT; i++) XtUnmapWidget(Text[i]);
  CommonPause();
    
  for (i = 0; i < MAXTEXT; i++) XtMapWidget(Text[i]);
  CommonPause();
    
  DestroyForm();
  CommonPause();

  CreateForm(Shell);
  CommonPause();

  XtUnmanageChild(Text[0]);
  CommonPause();

  XtUnmanageChild(Text[1]);
  CommonPause();
    
  XtUnmanageChild(Text[2]);
  CommonPause();

  XtUnmanageChild(Text[3]);
  CommonPause();
    
  for (i = 0; i < MAXTEXT; i++) XtManageChild(Text[i]);
  CommonPause();
    
  DestroyForm();
}

static void PrintValues(w)
Widget w;
{
  unsigned int n;
  Arg          args[MAX_ARGS];
  Position     x, y;
  Dimension    width, height;
  
  n = 0;
  XtSetArg(args[n], XmNx,      &x);            n++;
  XtSetArg(args[n], XmNy,      &y);            n++;
  XtSetArg(args[n], XmNwidth,  &width);        n++;
  XtSetArg(args[n], XmNheight, &height);       n++;
  XtGetValues(w, args, n);

  printf("\n\tX: %d Y: %d W: %d H: %d\n", x, y, width, height);

  if ( XtIsManaged(w) ) 
    printf("The Widget is Managed.\n");
  else
    printf("The Widget is NOT Managed.\n");
}

static void CreateForm(Shell)
Widget Shell;
{
  register int  i;
  register int  n;
  Arg args[MAX_ARGS];

  n = 0;
  XtSetArg(args[n], XmNallowShellResize, True);                  n++;
  DialogShell = XmCreateDialogShell(Shell, "Form21", args, n);

  n = 0;
  XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);            n++;
  XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);        n++;
  ScrollWin = XmCreateScrolledWindow(DialogShell, "ScrollWin", args, n);
  
  n = 0;
  XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW);             n++;
  Form = XmCreateForm(ScrollWin, "Form", args, n);
  
  for (i = 0; i < MAXTEXT; i++) {
    n = 0;
    XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);                 n++;
    XtSetArg(args[n], XmNcolumns, 40);                                 n++;
    XtSetArg(args[n], XmNrows,    40);                                 n++;
    switch (i) {
    case 0:
      XtSetArg(args[n], XmNvalue, "This is Text0");                    n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);             n++;
      XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);              n++;
      break;
    case 1:
      n = 0;
      XtSetArg(args[n], XmNvalue, "This is Text1");                     n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);             n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);            n++;
      XtSetArg(args[n], XmNleftWidget, Text[0]);                        n++;
      XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);               n++;
      XtSetArg(args[n], XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
      XtSetArg(args[n], XmNbottomWidget, Text[0]);                      n++;
      break;
    case 2:
      n = 0;
      XtSetArg(args[n], XmNvalue, "This is Text2");                    n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);             n++;
      XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);            n++;
      XtSetArg(args[n], XmNtopWidget, Text[0]);                        n++;
      XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);           n++;
      break;
    case 3:
      n = 0;
      XtSetArg(args[n], XmNvalue, "This is Text3");                     n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);             n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);            n++;
      XtSetArg(args[n], XmNleftWidget, Text[2]);                        n++;
      XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);             n++;
      XtSetArg(args[n], XmNtopWidget, Text[1]);                         n++;
      XtSetArg(args[n], XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
      XtSetArg(args[n], XmNbottomWidget, Text[2]);                      n++;
      break;
    }
    Text[i] = XmCreateText(Form, "Text", args, n);
  }

  XtManageChildren(Text, MAXTEXT);
  XtManageChild(Form);
  XtManageChild(ScrollWin);
}

static void DestroyForm()
{
  XtDestroyWidget(DialogShell);
}
