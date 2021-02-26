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
static char rcsid[] = "$XConsortium: Form22.c /main/4 1995/07/13 18:07:07 drk $"
#endif
#endif
/*
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#define MAXTEXT 4

Widget Form;
Widget ScrolledList;
Widget PushButton1;
Widget PushButton2;

static void die();
static void RunTest();
static void CreateForm();
static void DestroyForm();

void  main(argc, argv)
int argc;
char **argv;
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

  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_NONE);                 n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);              n++;
  XtSetValues(PushButton1, args, n);
  XtSetValues(PushButton2, args, n);
  CommonPause();

  DestroyForm();
  CreateForm(Shell);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_NONE);                 n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);   		n++;
  XtSetValues(PushButton1, args, n);
  XtSetValues(PushButton2, args, n);
  CommonPause();

  DestroyForm();
}

static void CreateForm(Shell)
Widget Shell;
{
  register int  i;
  register int  n;
  Arg           args[MAX_ARGS];
  char          label[25];
  XmString      items[20];
  int           nitems = 20;

  for (i = 0; i < nitems; i++) {
    sprintf(label, "Item: %d", i);
    items[i] = XmStringCreate(label, XmSTRING_DEFAULT_CHARSET);
  }
  
  n = 0;
  XtSetArg(args[n], XmNautoUnmanage, False);                           n++;
  XtSetArg(args[n], XmNallowShellResize, True);                        n++;
  Form = XmCreateFormDialog(Shell, "Form", args, n);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);                 n++;
  PushButton1 = XmCreatePushButton(Form, "PushButton1", args, n);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);               n++;
  XtSetArg(args[n], XmNleftWidget, PushButton1);                       n++;
  XtSetArg(args[n], XmNitemCount, nitems);                             n++;
  XtSetArg(args[n], XmNitems, items);                                  n++;
  XtSetArg(args[n], XmNvisibleItemCount, 10);                          n++;
  ScrolledList = XmCreateScrolledList(Form, "ScrolledList", args, n);

  n = 0;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);                n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);               n++;
  XtSetArg(args[n], XmNleftWidget, XtParent(ScrolledList));            n++;
  PushButton2 = XmCreatePushButton(Form, "PushButton2", args, n);

  XtManageChild(PushButton1);
  XtManageChild(PushButton2);
  XtManageChild(ScrolledList);
  XtManageChild(Form);
}

static void DestroyForm()
{
  XtDestroyWidget(Form);
}
