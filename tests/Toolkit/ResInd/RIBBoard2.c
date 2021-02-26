/* $XConsortium: RIBBoard2.c /main/4 1995/07/15 21:08:31 drk $ */
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
 * Revision 1.4.2.4  1992/12/08  15:26:56  shobana
 * 	*** empty log message ***
 * 	[1992/12/08  15:26:37  shobana]
 *
 * Revision 1.4.2.3  1992/12/07  17:58:48  shobana
 * 	changed code to compile on Sun platform
 * 	[1992/12/07  17:58:31  shobana]
 * 
 * Revision 1.4.2.2  1992/10/11  18:28:37  shobana
 * 	Incorporated test for CR 5209
 * 	[1992/10/11  18:28:08  shobana]
 * 
 * Revision 1.4  92/03/13  17:03:19  devsrc
 * 	Converted to ODE
 * 
*/ 

#include <testlib.h>

Widget	BulletinBoard1,
	ArrowButton1,
	PushButton1,
	PushButton2,
        PushButton3,
        FileSelect1;
Widget FormDialog1;


int SelExists;

 
void act ();


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



    n = 0;
    BulletinBoard1 = XmCreateBulletinBoard(Shell1, "BulletinBoard1", args, n);
    XtManageChild(BulletinBoard1);

    n = 0;
    XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);  n++;
    XtSetArg(args[n], XmNmarginWidth, 200);  n++;
    XtSetArg(args[n], XmNmarginHeight, 200);  n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("pink"));  n++;
    XtSetValues(BulletinBoard1, args, n);

    XtRealizeWidget(Shell1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);  n++;
    XtSetArg(args[n], XmNborderWidth, 2);  n++;
    XtSetArg(args[n], XmNmarginWidth, 10);  n++;
    XtSetArg(args[n], XmNmarginHeight, 10);  n++;
    XtSetValues(BulletinBoard1, args, n);

    n = 0;
    ArrowButton1 = XmCreateArrowButton(BulletinBoard1, "ArrowButton1", args,
                                       n);
    XtManageChild(ArrowButton1);

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNx, 50);  n++;
    XtSetArg(args[n], XmNy, 050);  n++;
    PushButton1 = XmCreatePushButton(BulletinBoard1, "PushButton1", args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNx, 100);  n++;
    XtSetArg(args[n], XmNy, 100);  n++;
    PushButton2 = XmCreatePushButton(BulletinBoard1, "PushButton2", args, n);
    XtManageChild(PushButton2);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNborderWidth, 5);  n++;
    XtSetValues(PushButton2, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNheight, 48);  n++;
    XtSetValues(PushButton2, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNwidth, 120);  n++;
    XtSetValues(PushButton2, args, n);
   
    CommonPause();

    XtDestroyWidget (PushButton1);
    XtDestroyWidget (PushButton2);
    XtDestroyWidget (ArrowButton1);

    /* Begin test for CR 5209 */

    n = 0;
    FileSelect1 = XmCreateSelectionBox(BulletinBoard1, 
				       "FileSelect1", args, n);
    XtManageChild(FileSelect1);
    SelExists = 1;
 
    n = 0;
    XtSetArg(args[n], XmNautoUnmanage, False); n++;
    FormDialog1 = XmCreateFormDialog(Shell1, "FormDialog1", 
				     args, n);
    
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNlabelString, 
	     XmStringCreateSimple("Destroy")); n++;
    PushButton3 = XmCreatePushButton(FormDialog1, 
				     "PushButton3", args, n);
    XtAddCallback(PushButton3, XmNactivateCallback, act, NULL);

    XtManageChild(PushButton3);
    XtManageChild(FormDialog1);
    
    XtManageChild (BulletinBoard1);

    CommonPause();

/* end test for CR 5209 */
    XtAppMainLoop(app_context);
}


void act(w, client_data, call_data)
Widget w;
XtPointer call_data;
XtPointer client_data;

{
  char *new_button;
  XmString xms;
  Arg args[10];
  int n;

  if (SelExists) 
    {
	printf("Destroying selection box\n");
	XtDestroyWidget(FileSelect1);
	new_button = "Create";
	SelExists = 0;
    }
  else 
    {
	printf("Creating selection box\n");
	n = 0;
	FileSelect1 = XmCreateSelectionBox(BulletinBoard1, "FileSelect1", 
	                                   args, n);
	XtManageChild(FileSelect1);
	new_button = "Destroy";
	SelExists = 1;
    }
    
   xms = XmStringCreateSimple(new_button);
  
   n=0;
   XtSetArg (args[n], XmNlabelString, xms); n++;
   XtSetValues(w, args, n);
   XmStringFree(xms);
}




