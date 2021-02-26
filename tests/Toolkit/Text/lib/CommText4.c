/* $XConsortium: CommText4.c /main/6 1995/07/15 21:11:14 drk $ */
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

static char string1[] =	"One fish\nTwo fish\nRed fish\nBlue fish"; 
static char string2[] = "1234567890";

static void ShowPosition( Widget w, XtPointer client_data,
                                XtPointer call_data)
{
  printf ("The new cursor position is %d\n",
	  ((XmTextVerifyCallbackStruct *)call_data)->newInsert); 
}


void main_text4 (argc, argv)
     int argc;
     char **argv;
{
	Widget PanedWindow1;
	Widget Text1, Text2;
	Widget RowColumn1;
	Widget PButton1, PButton2, PButton3;
	Pixel red_pixel;
	Arg args[MAX_ARGS];
	int n;
        XmString tcs;

	/*  initialize toolkit  */
	CommonTestInit(argc, argv);
	 
	n = 0;
	PanedWindow1 = XmCreatePanedWindow(Shell1, "PanedWindow1", args, n);
	XtManageChild(PanedWindow1);

	n = 0;
	XtSetArg(args[n], XmNallowResize, True); n++;
	XtSetArg(args[n], XmNborderWidth, 0); n++;
	RowColumn1 = XmCreateRowColumn(PanedWindow1, "RowColumn1", args, n);
	XtManageChild(RowColumn1);

	red_pixel = CommonGetColor("red");

	n = 0;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNhighlightColor, red_pixel); n++;
	XtSetArg(args[n], XmNallowResize, True); n++;
	XtSetArg(args[n], XmNblinkRate, 0);  n++;
	XtSetArg(args[n], XmNresizeWidth, True); n++;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNrows, 5); n++;
	XtSetArg(args[n], XmNvalue, string1 ); n++;
	XtSetArg(args[n], XmNcursorPosition, 5); n++;
	Text1 = XmCreateText(PanedWindow1, "Text1", args, n);
	XtManageChild(Text1);

	XtAddCallback(Text1, XmNlosingFocusCallback, CommonGenericCB, NULL);

	n = 0;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNhighlightColor, red_pixel); n++;
	XtSetArg(args[n], XmNallowResize, True); n++;
	XtSetArg(args[n], XmNvalue, string2 );n++;
	Text2 = XmCreateText(PanedWindow1, "Text2", args, n);
	XtManageChild(Text2);

	XtAddCallback(Text2, XmNlosingFocusCallback, CommonGenericCB, NULL);
	XtAddCallback(Text2, XmNmotionVerifyCallback, ShowPosition, 
                             NULL);

	n = 0;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNhighlightColor, red_pixel); n++;
	XtSetArg(args[n], XmNtraversalOn, True); n++;
	PButton1 = XmCreatePushButton(RowColumn1, "PButton1", args, n);
	XtManageChild(PButton1);

	n = 0;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNhighlightColor, red_pixel); n++;
	XtSetArg(args[n], XmNtraversalOn, True); n++;
	PButton2 = XmCreatePushButton(RowColumn1, "PButton2", args, n);
	XtManageChild(PButton2);

	n = 0;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNhighlightColor, red_pixel); n++;
	XtSetArg(args[n], XmNtraversalOn, True); n++;
	PButton3 = XmCreatePushButton(RowColumn1, "PButton3", args, n);
	XtManageChild(PButton3);

	XmAddTabGroup(Text1);
	XmAddTabGroup(Text2);
	XmAddTabGroup(RowColumn1);

	XtRealizeWidget(Shell1);

	CommonPause();	/* tab groups, losingFocus, test for PIR 3143 */
	CommonPause();	/* grow text widget 1 */

	XtAppMainLoop(app_context);
}
