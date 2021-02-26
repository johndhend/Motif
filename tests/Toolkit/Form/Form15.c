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
static char rcsid[] = "$XConsortium: Form15.c /main/4 1995/07/13 18:02:35 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *  Create 2 push buttons in a form.  SetValues on the constraints to
 *  try out the difference attachment types.  Also type some invalid
 *  conditions.
 */


#include <signal.h>
#include <X11/StringDefs.h>
#include <testlib.h>

Widget form;
Widget scale1;
Widget push1;
Widget push2;

static void CreateBBPopup();

void doIt (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;
{
  Arg args[1];
  int whichButton, scaleValue;
  static int toggleIsOn = 1;

  whichButton = (int) (long)client_data;

  XtSetArg (args[0], XmNvalue, &scaleValue);
  XtGetValues (scale1, args, 1);

  switch (whichButton)
    {
    case 1 :   XtSetArg(args[0], XmNwidth, scaleValue);
      XtSetValues(push1, args, 1);
      break;

    case 2 :   XtSetArg(args[0], XmNwidth, scaleValue);
      XtSetValues(push2, args, 1);
      break;

    case 3 :   /* if the toggle's on, set Shell allowResize: False */
      if (toggleIsOn)
	{	XtSetArg(args[0], XmNallowShellResize, False);
		XtSetValues(Shell1, args, 1);
		toggleIsOn = 0;
	      }
      else /* toggleOn is false, so we making resizable */
	{	XtSetArg(args[0], XmNallowShellResize, True);
		XtSetValues(Shell1, args, 1);
		toggleIsOn = 1;
	      };
      break;

    default:   printf("How did I get here?\n");
      break;

    }
}

/*  main  */

void main (argc, argv)
int argc;
char **argv;
{
   Arg args[10];
   int n;

   /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
   /*  The form creation.  Contained in an outer frame.  */

   n = 0;
   /* XtSetArg (args[n], XmNheight, 35); n++;
      XtSetArg (args[n], XmNwidth, 50); n++; */

   form = XmCreateForm (Shell1, "form", args, n);
   XtManageChild (form);

   /*  Arguments to the first frame.  */

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   push1 = XmCreatePushButton (form, "push1", args, n);
   XtManageChild (push1);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopOffset, 10);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
   XtSetArg (args[n], XmNtopWidget, push1);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   push2 = XmCreatePushButton (form, "push2", args, n);
   XtManageChild (push2);

   XtRealizeWidget (Shell1);

   CreateBBPopup();
   CommonPause();

   XtAppMainLoop(app_context);
}

static void CreateBBPopup()
{
    Widget        BBD;
    Widget	  pb1, pb2, tb1;
    Arg           args[MAX_ARGS];
    register int  n;

    n = 0;
    XtSetArg (args[n], XmNdefaultPosition, False); n++;
    XtSetArg (args[n], XmNy, 500); n++;
    XtSetArg (args[n], XmNheight, 400); n++;
    XtSetArg (args[n], XmNwidth, 400); n++;
    XtSetArg (args[n], XmNautoUnmanage, False); n++;
    BBD = XmCreateBulletinBoardDialog(Shell1, "BBD", args, n);

    n = 0; 
    XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
    XtSetArg (args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
    XtSetArg (args[n], XmNshowValue, True); n++;
    XtSetArg (args[n], XmNminimum, 1); n++;
    XtSetArg (args[n], XmNmaximum, 600); n++;
    XtSetArg (args[n], XmNvalue, 200); n++;
    XtSetArg (args[n], XmNwidth, 200); n++;
    XtSetArg (args[n], XmNx, 20); n++;
    XtSetArg (args[n], XmNy, 10); n++;
    scale1 = XmCreateScale (BBD, "scale1", args, n);
    XtManageChild (scale1);

    n = 0;
    XtSetArg (args[n], XmNx, 20); n++;
    XtSetArg (args[n], XmNy, 100); n++;
    XtSetArg (args[n], XmNlabelString,
     XmStringCreateLtoR ("Resize PB1", XmSTRING_DEFAULT_CHARSET)); n++;
    pb1 = XmCreatePushButton (BBD, "pb1", args, n);
    XtAddCallback (pb1, XmNactivateCallback, doIt, (XtPointer) 1);

    n = 0;
    XtSetArg (args[n], XmNx, 100); n++;
    XtSetArg (args[n], XmNy, 100); n++;
    XtSetArg (args[n], XmNlabelString,
     XmStringCreateLtoR ("Resize PB2", XmSTRING_DEFAULT_CHARSET)); n++;
    pb2 = XmCreatePushButton (BBD, "pb2", args, n);
    XtAddCallback (pb2, XmNactivateCallback, doIt, (XtPointer) 2);

    n = 0;
    XtSetArg (args[n], XmNx, 200); n++;
    XtSetArg (args[n], XmNy, 100); n++;
    XtSetArg (args[n], XmNset, True); n++;
    XtSetArg (args[n], XmNlabelString,
     XmStringCreateLtoR ("Shell Resizable", XmSTRING_DEFAULT_CHARSET)); n++;
    tb1 = XmCreateToggleButton (BBD, "tb1", args, n);
    XtAddCallback (tb1, XmNvalueChangedCallback, doIt, (XtPointer) 3);

    XtManageChild (pb1);
    XtManageChild (pb2);
    XtManageChild (tb1);

    XtManageChild (BBD); 
}








