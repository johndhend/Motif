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
static char rcsid[] = "$XConsortium: Form10.c /main/4 1995/07/13 18:00:48 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.4              *
*       Tue May  9 15:22:45 1989        *
****************************************/

#include <testlib.h>

Widget Form1, ArrowBtn1, ArrowBtn2, ArrowBtn3;
void  main(argc, argv)
int     argc;
char  **argv;
{
    Boolean       trace = False;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    n = 0;
    Form1 = XmCreateForm(Shell1, "Form1", args, n);
    XtManageChild(Form1);

    n = 0;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);  n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);  n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);  n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);  n++;

    ArrowBtn1 = XmCreateArrowButton(Form1, "ArrowBtn1", args, n);
    XtManageChild(ArrowBtn1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNtopOffset, 10);  n++;
    XtSetArg(args[n], XmNbottomOffset, 30);  n++;
    XtSetArg(args[n], XmNleftOffset, 20);  n++;
    XtSetArg(args[n], XmNrightOffset, 40);  n++;
    XtSetValues(ArrowBtn1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION);  n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_POSITION);  n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_POSITION);  n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION);  n++;
    XtSetArg(args[n], XmNleftPosition, 10);  n++;
    XtSetArg(args[n], XmNrightPosition, 90);  n++;
    XtSetArg(args[n], XmNtopPosition, 25);  n++;
    XtSetArg(args[n], XmNbottomPosition, 75);  n++;
    XtSetValues(ArrowBtn1, args, n);

    CommonPause();

   /* 
      Note: either unmanaging and remanaging the Form, or unrealizing
      and realizing the Shell, will fix the ugly Shell sizing problem
      shown herein, PIR 1581.
   */

    n = 0;
    XtSetArg(args[n], XmNtopPosition, 3);  n++;
    XtSetArg(args[n], XmNbottomPosition, 8);  n++;
    XtSetArg(args[n], XmNleftPosition, 1);  n++;
    XtSetArg(args[n], XmNrightPosition, 9);  n++;
    XtSetValues(ArrowBtn1, args, n);

    n = 0;
    XtSetArg(args[n], XmNfractionBase, 10);  n++;
    XtSetValues(Form1, args, n);

    CommonPause();
  
    XtDestroyWidget (ArrowBtn1);

    n = 0;
    XtSetArg(args[n], XmNfractionBase, 100);  n++;
    XtSetValues(Form1, args, n);
   
   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 10);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 30);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNtopOffset, 20);			n++;
   XtSetArg (args[n], XmNwidth, 100);		n++;
   XtSetArg (args[n], XmNheight, 100);		n++;
   ArrowBtn1 = XmCreateArrowButton(Form1, "ArrowBtn1", args, n);
   XtManageChild(ArrowBtn1);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 40);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 60);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNtopOffset, 0);				n++;
   XtSetArg (args[n], XmNwidth, 100);		n++;
   XtSetArg (args[n], XmNheight, 100);		n++;
   ArrowBtn2 = XmCreateArrowButton(Form1, "ArrowBtn2", args, n);
   XtManageChild(ArrowBtn2);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 70);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 90);			n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNbottomOffset, 5);			n++;
   XtSetArg (args[n], XmNwidth, 100);		n++;
   XtSetArg (args[n], XmNheight, 100);		n++;
   ArrowBtn3 = XmCreateArrowButton(Form1, "ArrowBtn3", args, n);
   XtManageChild(ArrowBtn3);

   XtRealizeWidget (Shell1);

   CommonPause();

   XtAppMainLoop(app_context);
}













