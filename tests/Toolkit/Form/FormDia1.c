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
static char rcsid[] = "$XConsortium: FormDia1.c /main/4 1995/07/13 18:12:47 drk $"
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
Widget push1;
Widget push2;

extern void PushBCallback();

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
   XtSetArg (args[n], XmNheight, 35); n++;
   XtSetArg (args[n], XmNwidth, 50); n++;
   form = XmCreateForm (Shell1, "form", args, n);
   XtManageChild (form);

   /*  Arguments to the first frame.  */

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   push1 = XmCreatePushButton (form, "push1", args, n);
   XtManageChild (push1);

   XtAddCallback (push1, XmNactivateCallback, PushBCallback, form);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopOffset, 10);			n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
   XtSetArg (args[n], XmNtopWidget, push1);			n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   push2 = XmCreatePushButton (form, "push2", args, n);
   XtManageChild (push2);

   /* XtAddCallback (push2, XmNactivateCallback, PushBCallback, form); */

   XtRealizeWidget (Shell1);

   CommonPause();
   CommonPause();
   CommonPause();
   CommonPause();

   XtAppMainLoop(app_context);
}

void PushBCallback (pw, form, closure)
Widget pw;
Widget form;
caddr_t closure;

{
   static count = 0;
   Arg args[10];
   int n;
   unsigned char top_attachment;

   if (count == 0)
   {
      printf ("Change push2's attach widget to NULL.\n");
      n = 0;
      XtSetArg (args[n], XmNtopAttachment, XmATTACH_NONE);	n++;
      XtSetArg (args[n], XmNtopWidget, NULL);			n++;
      XtSetValues (push2, args, n);

      n = 0;
      XtSetArg (args[n], XmNtopAttachment, &top_attachment);	n++;
      XtGetValues (push2, args, n);
      printf ("The attachment of pushbutton 2 expected 0, now %d\n", 
		(int) top_attachment);

   }      
   else if (count == 1)
   {
      printf ("change push2's top attachment to opposite of push 1\n");
      n = 0;
      XtSetArg (args[n], XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET);	n++;
      XtSetArg (args[n], XmNtopWidget, push1);				n++;
      XtSetValues (push2, args, n);
   }
   else if (count == 2)
   {
      printf ("Change push2's attach widget to NULL.\n");
      n = 0;
      XtSetArg (args[n], XmNtopWidget, NULL);			n++;
      XtSetValues (push2, args, n);
   

   }
   else if (count == 3)
   {
      printf ("change the top attachment to attach widget.\n");

      n = 0;
      XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
      XtSetArg (args[n], XmNtopWidget, push1);			n++;
      XtSetValues (push2, args, n);
      n = 0;
      XtSetArg (args[n], XmNwidth, 200);			n++;
      XtSetValues (push1, args, n);
   

   }
   else if (count == 4)
   {
      printf ("set resizable to False and change the width of the child.\n");

      n = 0;
      XtSetArg (args[n], XmNallowShellResize, False);		n++;
      XtSetValues (Shell1, args, n);

      n = 0;
      XtSetArg (args[n], XmNwidth, 300);			n++;
      XtSetValues (push2, args, n);
   }
   else if (count == 5)
   {
      printf ("Set push2 to attach opposite on left and right.\n");

      n = 0;
      XtSetArg (args[n], XmNallowShellResize, True);		n++;
      XtSetValues (Shell1, args, n);

      n = 0;
      XtSetArg (args[n], XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET);	n++;
      XtSetArg (args[n], XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET);	n++;
      XtSetArg (args[n], XmNleftWidget, push1);				n++;
      XtSetArg (args[n], XmNrightWidget, push1);			n++;
      XtSetValues (push2, args, n);
   }
   else if (count == 6)
   {
      Widget form_dialog;

      printf ("Create a form dialog\n");

      n = 0;

      form_dialog = XmCreateFormDialog (Shell1, "form_dialog", args, n);
      XtManageChild (form_dialog);
   }

   count++;
}












