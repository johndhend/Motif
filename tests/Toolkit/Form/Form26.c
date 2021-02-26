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
static char rcsid[] = "$XConsortium: Form26.c /main/4 1995/07/13 18:09:14 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <signal.h>
#include <X11/StringDefs.h>

#include <testlib.h>

/*  Forward declarations  */

extern void FormCallback();
static void report();


void main (argc, argv)
int argc;
char **argv;
{
   Widget 	form;
   Display 	*display;
   Widget 	Scroll_Text;
   Widget	mess_dia;
   Arg 		args[20];
   int  	n;
   char         *string = "This is a Scrolled Text in\na Form with left and top attachments\nIt should be displayed on\nthree lines\n";

   CommonTestInit(argc, argv);

   n = 0;
   XtSetArg (args[n], XmNx, 0);					n++;
   XtSetArg (args[n], XmNy, 0);					n++;
   form = XmCreateForm(Shell1,"form", NULL, 0);
   XtManageChild(form);

   n = 0;
   XtSetArg(args[n], XmNgeometry, "+0+500"); n++;
   XtSetArg(args[n], XmNdefaultPosition, False);		n++;
   mess_dia = XmCreateMessageDialog(form, "MessageDia", args, n);
   XtManageChild(mess_dia);

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT);		n++;
   XtSetArg (args[n], XmNbackground, CommonGetColor("ForestGreen"));	n++;
   XtSetArg (args[n], XmNcolumns, 20);				n++;
   XtSetArg (args[n], XmNborderWidth, 8);			n++;
   XtSetArg (args[n], XmNvalue, string);			n++;
   XtSetArg (args[n], XmNwordWrap, True);			n++;
   XtSetArg (args[n], XmNrows, 3);				n++;
   XtSetArg (args[n], XmNscrollLeftSide, True);			n++;
   XtSetArg (args[n], XmNshadowThickness, 8);			n++;
   XtSetArg (args[n], XmNblinkRate, 0);				n++;
   Scroll_Text = XmCreateScrolledText(form, "ScrollText1", args, n);
   XtManageChild(Scroll_Text);

   XtAddCallback(Scroll_Text, XmNfocusCallback, report, "focusCallback");
   XtAddCallback(Scroll_Text, XmNvalueChangedCallback, report, "valueChanged");

   XtRealizeWidget (Shell1);

   CommonPause();

   /* begin test for PIR 2486 */
   n = 0;
   XtSetArg(args[n], XmNwidth, 200); n++;
   XtSetArg(args[n], XmNheight, 50); n++;
   XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
   XtSetValues(Scroll_Text, args, n);

   /* end test for PIR 2486 */

   CommonPause();
   CommonPause(); /* exit */

   XtAppMainLoop(app_context);
}


void myQuit()
{
     printf("Begin exiting ... please standby ... \n");
     fflush(stdout);
     exit(0);
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














static void report( widget, tag, callback_data )
Widget  widget;
char    *tag;
XmAnyCallbackStruct *callback_data;
{
	printf("%s callback made\n", tag);
}
