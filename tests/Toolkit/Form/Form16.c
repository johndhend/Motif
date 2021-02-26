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
static char rcsid[] = "$XConsortium: Form16.c /main/4 1995/07/13 18:03:00 drk $"
#endif
#endif
/*
 *  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/*
 *  Create three PushButton in a form.  
 */

#include <signal.h>
#include <X11/StringDefs.h>
#include <testlib.h>
#
/*  Forward declarations  */

Widget frame;
Widget form;
Widget PushButton1;
Widget PushButton2;
Widget PushButton3;
static void PushButtonCallback();

/*  main  */

void main (argc, argv)
int argc;
char         *argv[];
{
  Arg args[MAX_ARGS];
  unsigned int n;
  
  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth, 1);                    n++;
  XtSetArg(args[n], XmNheight, 1);                   n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget (Shell1);
  
  /* Create frame for Form. */
  frame = XmCreateFrame(Shell1,"frame", NULL, 0);

  /* The form creation. Contained in an outer frame. */
  n = 0;
  XtSetArg (args[n], XmNverticalSpacing, 15);	n++;
  form = XmCreateForm (frame, "form", args, n);
  
  /*  Create first PushButton.  */
  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
  PushButton1 = XmCreatePushButton(form, "PushButton1", args, n);
  XtAddCallback(PushButton1, XmNactivateCallback, PushButtonCallback, NULL);
  
  
  /*  Create second PushButton.  */
  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
  XtSetArg (args[n], XmNleftWidget, PushButton1);		n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
  PushButton2 = XmCreatePushButton(form, "PushButton2", args, n);
  XtAddCallback(PushButton2, XmNactivateCallback, PushButtonCallback, NULL);

  
  /*  Create third PushButton.  */
  n = 0;
  XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
  XtSetArg (args[n], XmNleftWidget, PushButton2); 	        n++;
  XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);        n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
  XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
  PushButton3 = XmCreatePushButton(form, "PushButton3", args, n);
  XtAddCallback(PushButton3, XmNactivateCallback, PushButtonCallback, NULL);

  /* Manage widgets. */
  XtManageChild(frame);
  XtManageChild(form);
  XtManageChild(PushButton1);
  XtManageChild(PushButton2);
  XtManageChild(PushButton3);


    
  CommonPause();
  CommonPause();
  CommonPause();

  XtDestroyWidget(form);

  /*
   *  Create a generic form
   */

  n = 0;
  XtSetArg(args[n], XmNmarginHeight, 25); n++;
  XtSetArg(args[n], XmNmarginWidth, 25); n++;
  form = XmCreateForm (frame, "form", args, n);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  PushButton1 = XmCreatePushButton(form, "PushButton1", args, n);

  XtManageChild(PushButton1);
  XtManageChild(form);
  CommonPause();

  /*
   *  Now try to update verticalSpacing/horizontalSpacing. Should
   *  have no effect.
   */
   
  n = 0;
  XtSetArg(args[n], XmNverticalSpacing, 50); n++;
  XtSetArg(args[n], XmNhorizontalSpacing, 50); n++;
  XtSetValues(form, args,  n);

  CommonPause();

  /*
   *  Update marginHeight, marginWidth.  This should have an
   *	effect.
   */

  n = 0;
  XtSetArg(args[n], XmNmarginHeight, 70); n++;
  XtSetArg(args[n], XmNmarginWidth, 70); n++;
  XtSetValues(form, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNrightOffset, 20); n++;
  XtSetArg(args[n], XmNleftOffset, 20); n++;
  XtSetValues(PushButton1, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNverticalSpacing, 50); n++;
  XtSetArg(args[n], XmNhorizontalSpacing, 50); n++;
  XtSetValues(form, args,  n);

  CommonPause();

  XtAppMainLoop(app_context);
}

static void PushButtonCallback(pb, client_data, call_data)
Widget pb;
caddr_t client_data;
caddr_t call_data;
{
  XtDestroyWidget(pb);
}











