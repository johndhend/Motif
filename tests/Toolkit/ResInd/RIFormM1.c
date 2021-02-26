/* $TOG: RIFormM1.c /main/5 1999/01/14 18:11:03 jff $ */
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
/*
 * Original History:
 *
 * Revision 1.1.2.3  1992/12/10  18:14:41  shobana
 * 	merged another test in
 * 	[1992/12/10  18:13:51  shobana]
 *
 * Revision 1.1.2.2  1992/12/10  16:59:03  shobana
 * 	Test for CR 3203
 * 	[1992/12/10  16:58:48  shobana]
 * 
 */
#include <testlib.h>

/*  Forward declarations  */

extern void PushBCallback();
extern char * UserData;

/*  main  */

void main (argc, argv)
int argc;
char **argv;
{
   Widget form;
   Widget frame;
   Widget pushb;
   Widget scrollbar1;
   Widget scrollbar2;
   Arg args[10];
   int n;
   int offset;
   Dimension height;
   Dimension width;

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);


   if (UserData == NULL) {
	printf ("Usage: %s -u [early middle late]\n", argv[0]);
	printf ("Assuming late realize.\n");
   }
    
   frame = XmCreateFrame(Shell1, "frame", NULL, 0);
   XtManageChild(frame);

   if (UserData && (strcmp (UserData, "early") == 0)) {
	printf ("Early realize.\n");
	fflush (stdout);
	XtRealizeWidget (Shell1);
   }

   /*  The form creation.  Contained in an outer frame.  */

   n = 0;
   XtSetArg (args[n], XmNwidth, 4000);			n++;
   XtSetArg (args[n], XmNheight, 3000);			n++;
   XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);	n++;
   form = XmCreateForm (frame, "form", args, n);
   XtManageChild (form);

   if (UserData && (strcmp (UserData, "middle") == 0)) {
	printf ("Middle realize.\n");
	fflush (stdout);
	XtRealizeWidget (Shell1);
   }

   /*  Arguments to the first scrollbar.  */

   n = 0;
   XtSetArg (args[n], XmNheight, 750);				n++;
   XtSetArg (args[n], XmNorientation, XmVERTICAL);		n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNrightOffset, 500);			n++;
   XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);		n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   scrollbar1 = XmCreateScrollBar (form, "scrollbar1", args, n);
   XtManageChild (scrollbar1);

   /*  Arguments to the second scrollbar.  */

   n = 0;
   XtSetArg (args[n], XmNorientation, XmHORIZONTAL);		n++;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	n++;
   XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);		n++;
   XtSetArg (args[n], XmNrightWidget, scrollbar1);		n++;
   scrollbar2 = XmCreateScrollBar (form, "scrollbar2", args, n);
   XtManageChild (scrollbar2);

   /*  Set the bottom offset for scrollbar2 to 1/2 inch  */

   n = 0;
   XtSetArg (args[n], XmNbottomOffset, 500);	n++;
   XtSetValues (scrollbar2, args, n);


   if (!UserData || (strcmp (UserData, "late") == 0)) {
	printf ("Late realize.\n");
	fflush (stdout);
	XtRealizeWidget (Shell1);
   }

   /*  Get Values out of the form and scrollbars and print the results.  */

   printf ("Width\tHeight\tOffset1\tOffset2\tMode\n");

   n = 0;
   XtSetArg (args[n], XmNwidth, &width);	n++;
   XtSetArg (args[n], XmNheight, &height);	n++;
   XtGetValues (form, args, n);
   printf ("%d\t%d\t", width, height);

   n = 0;
   XtSetArg (args[n], XmNrightOffset, &offset);	n++;
   XtGetValues (scrollbar1, args, n);
   printf ("%d\t", offset);

   n = 0;
   XtSetArg (args[n], XmNbottomOffset, &offset);n++;
   XtGetValues (scrollbar2, args, n);
   printf ("%d\t", offset);

   printf ("%s\n", (UserData ? UserData : "late"));


   CommonPause();

   XtDestroyWidget (frame);


   n = 0;
   form = XmCreateForm (Shell1, "form", args, n);
   XtManageChild (form);


   /*  Arguments to the first frame.  */

   n = 0;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNwidth, 100);				n++;
   XtSetArg (args[n], XmNheight, 100);				n++;
   pushb = XmCreatePushButton (form, "pushb", args, n);
   XtManageChild (pushb);

   XtAddCallback (pushb, XmNactivateCallback, PushBCallback, form);

   XtRealizeWidget (Shell1);

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
   static Widget pb2;

   if (count == 0)
   {
      /* need to create a second child to see effect of [vert,horiz]spacing */
      /* begin test for PIR 3203 */
      n = 0;
      if (UserData != NULL)
	if (strcmp (UserData, "default") == 0) {
	  XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); 
	  n++;
	}
      pb2 = XmCreatePushButtonGadget (form, "pb2", args, n);
      XtManageChild (pb2);

      printf ("Setting the unit type to inches and setting the spacing.\n");
      n = 0;
      XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);    n++;
      XtSetArg (args[n], XmNtopWidget, pb2);                    n++;
      XtSetValues (pw, args, n);

      n = 0;
      XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);		n++;
      XtSetArg (args[n], XmNverticalSpacing, 2000);		n++;
      XtSetArg (args[n], XmNhorizontalSpacing, 2000);		n++;
      XtSetValues (form, args, n);

   }
   else if (count == 1) {
     n = 0;
     XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);      n++;
     XtSetValues (pw, args, n);

     n = 0;
     XtSetArg (args[n], XmNverticalSpacing, 200); n++;
     XtSetArg (args[n], XmNhorizontalSpacing, 200); n++;
     XtSetValues (form, args, n);

     XtDestroyWidget (pb2);
   }
   /* end test for PIR 3203 */

   count++;
}





















