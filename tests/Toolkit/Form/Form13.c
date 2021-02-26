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
static char rcsid[] = "$XConsortium: Form13.c /main/4 1995/07/13 18:02:05 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/*
 *  Create three arrows in a form such that they horizontally span
 *  the form; 10% - 30%, 40 - 60% and 70% to 90%.
 */


#include <signal.h>
#include <X11/StringDefs.h>

#include <testlib.h>

/*  Forward declarations  */

extern void FormCallback();

/*  main  */

void main (argc, argv)
int argc;
char **argv;
{
   Widget frame;
   Widget form;
   Widget arrow1;
   Widget arrow2;
   Widget arrow3;
   Arg args[10];
   int n;

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);
    
   frame = XmCreateFrame(Shell1, "frame",  NULL, 0);
   XtManageChild(frame);
   
   /*  The form creation.  Contained in an outer frame.  */

   n = 0;
   XtSetArg (args[n], XmNwidth, 200);		n++;
   XtSetArg (args[n], XmNheight, 100);		n++;
   form = XmCreateForm(frame, "form", args, n);
   XtManageChild (form);
   XtAddCallback (form, XmNhelpCallback, FormCallback, NULL);

   /*  Arguments to the first arrow.  */

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 10);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 30);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNtopPosition, 25);			n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNbottomPosition, 75);			n++;
   arrow1 = XmCreateArrowButtonGadget(form, "arrow1", args, n);
   XtManageChild(arrow1);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 40);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 60);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNtopPosition, 25);			n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNbottomPosition, 75);			n++;
   arrow2 = XmCreateArrowButtonGadget(form, "arrow2", args, n);
   XtManageChild(arrow2);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNleftPosition, 70);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNrightPosition, 90);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNtopPosition, 25);			n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_POSITION);	n++;
   XtSetArg (args[n], XmNbottomPosition, 75);			n++;
   arrow3 = XmCreateArrowButtonGadget(form, "arrow3", args, n);
   XtManageChild(arrow3);

   XtRealizeWidget (Shell1);

   CommonPause();

   XtAppMainLoop(app_context);
}

void FormCallback (fw, closure, call_data)
XmFormWidget fw;
caddr_t closure;
caddr_t call_data;

{
   int reason;

   XmAnyCallbackStruct * call_value = (XmAnyCallbackStruct *) call_data;

   reason = call_value -> reason;

   switch (reason)
   {
      case XmCR_HELP:
         printf ("Reason = XmCR_HELP\n");
      break;

      default:
         printf ("Hit the default, incorrect reason sent!!\n");
      break;
   }
}












