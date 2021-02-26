/* $XConsortium: Navigation15.c /main/5 1995/07/15 21:11:49 drk $ */
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

#include <testlib.h>

void FocusEvent (Widget w, XtPointer client_data, XEvent *event, Boolean *c)
{
    if (event->type == FocusIn)
	printf ("A FocusIn Event happened for %s\n", (char*)client_data);
}


main (int argc, char ** argv)
{
   Arg args[10];
   int n;
   Widget form, drawarea1, textfield1, textfield2, drawarea2, sep;

   /* initialize Toolkit */
   CommonTestInit(argc, argv);

   /* malloc space for pkids */

   n = 0;
   XtSetArg(args[n], XmNheight, 300); n++;
   XtSetArg(args[n], XmNwidth, 100); n++;
   form = XmCreateForm(Shell1, "form", args, n);
  
   n = 0;
   XtSetArg(args[n], XmNheight, 150); n++;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
   drawarea1 = XmCreateDrawingArea(form, "drawarea1", args, n);
  
   n = 0;
   XtSetArg(args[n], XmNx, 20); n++;
   XtSetArg(args[n], XmNy, 40); n++;
   XtSetArg(args[n], XmNheight, 30); n++;
   XtSetArg(args[n], XmNwidth, 50); n++;
   textfield1 = XmCreateTextField(drawarea1, "textfield1", args, n);

   n = 0;
   XtSetArg(args[n], XmNx, 20); n++;
   XtSetArg(args[n], XmNy, 80); n++;
   XtSetArg(args[n], XmNheight, 30); n++;
   XtSetArg(args[n], XmNwidth, 50); n++;
   textfield2 = XmCreateTextField(drawarea1, "textfield2", args, n);

   n = 0;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNtopWidget, drawarea1); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
   sep = XmCreateSeparator(form, "sep", args, n);

   n = 0;
   XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
   XtSetArg(args[n], XmNtopWidget, sep); n++;
   XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
   XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
   drawarea2 = XmCreateDrawingArea(form, "drawarea2", args, n);
  
   XtManageChild(textfield1);
   XtManageChild(textfield2);
   XtManageChild(drawarea1);
   XtManageChild(form);
   XtManageChild(sep);
   XtManageChild(drawarea2);
   XtManageChild(form);

   n = 0;
   XtSetArg(args[n], XmNheight, 300); n++;
   XtSetArg(args[n], XmNwidth, 100); n++;
   XtSetValues(form, args, n);

   XtRealizeWidget(Shell1);

   CommonPause ();

   XtAddEventHandler(form, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"form"); 
   XtAddEventHandler(drawarea1, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"drawarea1"); 
   XtAddEventHandler(textfield1, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"textfield1"); 
   XtAddEventHandler(textfield2, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"textfield2"); 
   XtAddEventHandler(sep, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"seperator"); 
   XtAddEventHandler(drawarea2, FocusChangeMask, FALSE, FocusEvent,
		     (XtPointer)"drawarea2"); 
   n = 0;
   XtSetArg(args[n], XmNinitialFocus, NULL); n++;
   XtSetValues(drawarea1, args, n);
   XtSetValues(drawarea2, args, n);

   CommonPause ();

   n = 0;
   XtSetArg(args[n], XmNinitialFocus, 1); n++;
   XtSetValues(drawarea1, args, n);
   XtSetValues(drawarea2, args, n);

   CommonPause ();

   XtAppMainLoop (app_context);
}



