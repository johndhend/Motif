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
static char rcsid[] = "$XConsortium: Form25.c /main/4 1995/07/13 18:08:42 drk $"
#endif
#endif
/*
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#define MAXCASE 5
#define HALFCASE 3

Widget    Form[MAXCASE];
Widget  Child1[MAXCASE];
Widget  Child2[MAXCASE];
Widget  Child3[MAXCASE];
Widget  Child4[MAXCASE];
Widget  ChildA[MAXCASE];
Widget  ChildB[MAXCASE];
Widget  ChildC[MAXCASE];
Widget  ChildD[MAXCASE];

static void die();
static void RunTest();
static void CreateForms();
static void DestroyForms();

void  main(argc, argv)
int     argc;
char    **argv;
{
  register int  n;
  Arg args[MAX_ARGS];
  
  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg (args[n], XmNwidth,  50); n++;
  XtSetArg (args[n], XmNheight, 25); n++;
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
  
  CreateForms(Shell);
  CommonPause();
    
  for (i = 0; i < HALFCASE; i++) {
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 60);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 75);                             n++;
    XtSetValues(ChildD[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 40);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 50);                             n++;
    XtSetValues(ChildC[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 20);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 25);                             n++;
    XtSetValues(ChildB[i], args, n);
  }
    
  for (i = HALFCASE; i < MAXCASE; i++) {
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);               n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);                n++;
    XtSetValues(ChildA[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++; 
    XtSetArg(args[n], XmNleftPosition, 20);                            n++; 
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 25);                             n++;
    XtSetValues(ChildB[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 40);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 50);                             n++;
    XtSetValues(ChildC[i], args, n);  
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 60);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 75);                             n++;
    XtSetValues(ChildD[i], args, n);
  } 
    
  CommonPause();
  DestroyForms();

  CreateForms(Shell);
  CommonPause();
    
  for (i = 0; i < HALFCASE; i++) {
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 60);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 75);                             n++;
    XtSetValues(ChildD[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 40);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 50);                             n++;
    XtSetValues(ChildC[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 20);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 25);                             n++;
    XtSetValues(ChildB[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetValues(ChildA[i], args, n);
  }
    
  for (i = HALFCASE; i < MAXCASE; i++) {
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);               n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);                n++;
    XtSetValues(ChildA[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++; 
    XtSetArg(args[n], XmNleftPosition, 20);                            n++; 
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++; 
    XtSetArg(args[n], XmNtopPosition, 25);                             n++;
    XtSetValues(ChildB[i], args, n);
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 40);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 50);                             n++;
    XtSetValues(ChildC[i], args, n);  
    n = 0;
    XtSetArg(args[n], XmNwidth, 100);                                  n++;
    XtSetArg(args[n], XmNheight, 100);                                 n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);           n++;
    XtSetArg(args[n], XmNleftPosition, 60);                            n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_NONE);              n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);            n++;
    XtSetArg(args[n], XmNtopPosition, 75);                             n++;
    XtSetValues(ChildD[i], args, n);
  } 
    
  CommonPause();
  DestroyForms();
}

static void CreateForms(Shell)
Widget Shell;
{
  register int  n;
  register int  case_number;
  char          label[80];
  Arg           args[MAX_ARGS];
  
  for (case_number = 0; case_number < MAXCASE; case_number++) {
    n=0;
    sprintf(label, "Case_%d", case_number);
    XtSetArg(args[n], XmNx,  0);                                 n++;
    XtSetArg(args[n], XmNy, 50 + (case_number * 40));            n++;
    XtSetArg(args[n], XmNallowOverlap, True);                      n++;
    XtSetArg(args[n], XmNresizePolicy, XmRESIZE_ANY);              n++;
    XtSetArg(args[n], XmNdialogStyle,  XmDIALOG_MODELESS);         n++;
    XtSetArg(args[n], XmNautoUnmanage, False);                     n++;
    XtSetArg(args[n], XmNdefaultPosition, False);                  n++;
    Form[case_number] = XmCreateFormDialog(Shell, label, args, n);

    n = 0;
    XtSetArg(args[n], XmNallowShellResize, True);                  n++;
    XtSetValues(XtParent(Form[case_number]), args, n);
    
    Child1[case_number] = XmCreatePushButton(Form[case_number], "", NULL, 0);
    Child2[case_number] = XmCreatePushButton(Form[case_number], "", NULL, 0);
    Child3[case_number] = XmCreatePushButton(Form[case_number], "", NULL, 0);
    Child4[case_number] = XmCreatePushButton(Form[case_number], "", NULL, 0);
    
    switch ( case_number ) {
      
    case 0:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);         n++;
      XtSetValues(Child1[case_number], args, n);

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child1[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);        n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];
      
      break;
      
    case 1:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetValues(Child1[case_number], args, n);    

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child1[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);        n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];
      
      break;
      
    case 2:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);         n++;
      XtSetValues(Child1[case_number], args, n);

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child1[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];

      break;
      
    case 3:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetValues(Child1[case_number], args, n);

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child1[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];

      break;
      
    case 4:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);        n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child4[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);         n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;
      
    case 5:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);        n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child4[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;
      
    case 6:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child4[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);         n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;
      
    case 7:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child3[case_number]);       n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNleftWidget, Child4[case_number]);       n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));   n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;

    case 8:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);          n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child3[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child4[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);         n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];

      break;

    case 9:

      sprintf(label, "Child: A 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child2[case_number]);       n++;
      XtSetValues(Child1[case_number], args, n);

      ChildA[case_number] = Child1[case_number];
      
      sprintf(label, "Child: B 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child3[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child2[case_number], args, n);

      ChildB[case_number] = Child2[case_number];
      
      sprintf(label, "Child: C 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child4[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child3[case_number], args, n);

      ChildC[case_number] = Child3[case_number];
      
      sprintf(label, "Child: D 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);         n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child4[case_number], args, n);

      ChildD[case_number] = Child4[case_number];

      break;
      
    case 10:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);         n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child1[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child2[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);          n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;
      
    case 11:

      sprintf(label, "Child: D 1");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);         n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child1[case_number], args, n);

      ChildD[case_number] = Child1[case_number];
      
      sprintf(label, "Child: C 2");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child1[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child2[case_number], args, n);

      ChildC[case_number] = Child2[case_number];
      
      sprintf(label, "Child: B 3");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child2[case_number]);       n++;
      XtSetArg(args[n], XmNleftAttachment, XmATTACH_NONE);          n++;
      XtSetValues(Child3[case_number], args, n);

      ChildB[case_number] = Child3[case_number];
      
      sprintf(label, "Child: A 4");

      n = 0;
      XtSetArg(args[n], 
               XmNlabelString,
               XmStringCreate(label, XmSTRING_DEFAULT_CHARSET));    n++;
      XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);       n++;
      XtSetArg(args[n], XmNrightWidget, Child3[case_number]);       n++;
      XtSetValues(Child4[case_number], args, n);

      ChildA[case_number] = Child4[case_number];

      break;

    }
    
    
    XtManageChild(Child1[case_number]);
    XtManageChild(Child2[case_number]);
    XtManageChild(Child3[case_number]);
    XtManageChild(Child4[case_number]);
    
    
    XtManageChild(Form[case_number]);

  }
}

static void DestroyForms()
{
  register int  case_number;
  
  
  for (case_number = 0; case_number < MAXCASE; case_number++) {

    XtDestroyWidget(XtParent(Form[case_number]));
  }
}
