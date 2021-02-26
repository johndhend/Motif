/* $TOG: CommText7.c /main/7 1997/10/02 16:26:40 csn $ */
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

Widget manager = NULL;
Arg args[MAX_ARGS];
static char string1[] = "Sample Text";

static char font_name1[] = "fixed";

static char render_tag[] = "render1";

static Widget makeTextWidget(Widget mgr, char *name)
{
        XmString tcs = (XmString)0;
        Widget Text;
	int n = 0;

	XtSetArg(args[n], XmNresizeWidth, False);  n++;
	XtSetArg(args[n], XmNresizeHeight, False);  n++;
	XtSetArg(args[n], XmNcolumns, 40);  n++;
	XtSetArg(args[n], XmNrows, 1);  n++;
	XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
	XtSetArg(args[n], XmNcursorPosition, 5);  n++;
	XtSetArg(args[n], XmNvalue, string1);  n++;
	XtSetArg(args[n], XmNfontList, CommonGetFontList("fixed"));  n++;
	XtSetArg(args[n], XmNforeground, CommonGetColor("Red"));  n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("White"));  n++;
        Text = XmCreateText(mgr, name, args, n);
        if ( tcs ) XmStringFree(tcs);
	return(Text);
}

void main_text7(argc, argv)
     int argc;
     char **argv;
{
	Widget Text1 = NULL;
	Widget PB1 = NULL;
	int n = 0;
	XmString tcs;

	/*  initialize toolkit  */
	CommonTestInit(argc, argv);
	 
	n = 0;
	XtSetArg (args[n], XmNwidth, 50); n++;
	XtSetArg (args[n], XmNheight, 50); n++;
	XtSetValues(Shell1, args, n);
	 
	XtRealizeWidget(Shell1);

	n = 0;
	XtSetArg (args[n], XmNwidth, 400); n++;
	XtSetArg (args[n], XmNheight, 400); n++;
	manager = XmCreateBulletinBoard (Shell1, "manager", args, n);


	Text1 = makeTextWidget(manager, "Text1");
	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);

	XtManageChild(manager);
	XtManageChild(Text1);

	CommonPause();

	n = 0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNrows, 4); n++;
	XtSetValues (Text1, args, n);

	CommonPause();

	XtDestroyWidget (manager);

	XtSetArg (args[n], XmNwidth, 400); n++;
	XtSetArg (args[n], XmNheight, 400); n++;
	manager = XmCreateForm(Shell1, "manager", args, n);

	Text1 = makeTextWidget(manager, "Text1");
	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);

	XtManageChild(manager);
	XtManageChild(Text1);

	CommonPause ();

	n = 0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNrows, 4); n++;
	XtSetValues (Text1, args, n);

	CommonPause();

	XtDestroyWidget (manager);

	XtSetArg (args[n], XmNwidth, 400); n++;
	XtSetArg (args[n], XmNheight, 400); n++;
	manager = XmCreateFormDialog(Shell1, "manager", args, n);

	Text1 = makeTextWidget(manager, "Text1");
	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);

	XtManageChild(manager);
	XtManageChild(Text1);

	CommonPause();

	n = 0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNrows, 4); n++;
	XtSetValues (Text1, args, n);

	CommonPause();

	XtDestroyWidget (manager);

	XtSetArg (args[n], XmNwidth, 400); n++;
	XtSetArg (args[n], XmNheight, 400); n++;
	manager = XmCreateBulletinBoardDialog(Shell1, "manager", args, n);

	Text1 = makeTextWidget(manager, "Text1");

	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);

	XtManageChild(manager);
	XtManageChild(Text1);

	CommonPause();

	n = 0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); 		n++;
	XtSetArg(args[n], XmNrows, 4); 				n++;
	XtSetValues (Text1, args, n);

	CommonPause();

	/* Begin test for Pir 2693 */

	XtDestroyWidget (manager);

	tcs = XmStringCreateLtoR("Modeless Window", XmSTRING_DEFAULT_CHARSET);

	XtSetArg (args[n], XmNallowOverlap, False); 			n++;
	XtSetArg (args[n], XmNdialogStyle, XmDIALOG_MODELESS); 	n++;
	XtSetArg (args[n], XmNdialogTitle, tcs); 			n++;
	XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW); 		n++;
	manager = XmCreateFormDialog(Shell1, "manager", args, n);
	XtManageChild(manager);

	XmStringFree(tcs);

	n = 0;
	XtSetArg(args[n], XmNforeground, CommonGetColor("Red"));  	n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("White"));  	n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
	XtSetArg(args[n], XmNtopOffset, 15);				n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_WIDGET);	n++;
	XtSetArg(args[n], XmNbottomWidget, PB1);			n++;
	XtSetArg(args[n], XmNbottomOffset, 15);			n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);		n++;
	XtSetArg(args[n], XmNleftOffset, 5);				n++;
	XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
	XtSetArg(args[n], XmNrightOffset, 5);			n++;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);		n++;
	XtSetArg(args[n], XmNcolumns, 20);				n++;
	XtSetArg(args[n], XmNrows, 2);				n++;
	XtSetArg(args[n], XmNmaxLength, 200);			n++;
	XtSetArg(args[n], XmNresizeWidth, True);			n++;
	XtSetArg(args[n], XmNresizeHeight, False);			n++;
	XtSetArg(args[n], XmNfontList, CommonGetFontList("fixed"));	n++;
	Text1 = XmCreateText(manager, "Text1", args, n);
	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);
	XtManageChild(Text1);

	/* End test for Pir 2693 */

	CommonPause();

	XtAppMainLoop(app_context);
	/* end of test */
}
