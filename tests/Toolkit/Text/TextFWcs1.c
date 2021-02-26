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
static char rcsid[] = "$XConsortium: TextFWcs1.c /main/7 1995/07/13 19:32:28 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include "TextFWcs1.h"

int	n;
Arg	args[MAX_ARGS];


void main (argc, argv)
int	argc;
char	**argv;
{
#ifdef	MOTIF1_1

	printf("This is a 1.2 test only.\n");
	exit(0);

#else	/* MOTIF1_1 */

	XmString	tcs, ItemList[NITEMS];
	XmFontList 	newfontlist;
	wchar_t		*starting_wchar;
	int		num_chars = 0;

	CommonTestInit(argc, argv);

	newfontlist = CommonGetFontList("variable");

	n = 0;
	XtSetArg(args[n], XmNmarginHeight, 15); n++;
	XtSetArg(args[n], XmNmarginWidth, 15); n++;
	Form = XmCreateForm(Shell1, "Form", args, n);
	XtManageChild (Form);

	/* build the list of Functions Label and List */
	tcs = XmStringCreateLtoR("Functions:", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	Label1 = XmCreateLabel(Form, "Label1", args, n);
	XtManageChild(Label1);

	XmStringFree(tcs);

	n = 0;
	/* convert the plain strings to XmStrings */
	for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Label1); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNresizable, True); n++;
	XtSetArg(args[n], XmNselectionPolicy, XmBROWSE_SELECT); n++;
	XtSetArg(args[n], XmNhighlightOnEnter, False); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNitems, ItemList); n++;
	XtSetArg(args[n], XmNitemCount, NITEMS); n++;
	XtSetArg(args[n], XmNforeground, CommonGetColor("white")); n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("darkorchid")); n++;
	List1 = XmCreateScrolledList(Form, "List1", args, n);
	XtManageChild(List1);

	XtAddCallback(List1, XmNbrowseSelectionCallback, SSelCB_List1, NULL);


	/* build the Action Label and TextField */
	tcs = XmStringCreateLtoR("Action TextField:", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	Label3 = XmCreateLabel(Form, "Label3", args, n);
	XtManageChild(Label3);

	XmStringFree(tcs);

	num_chars = strlen(starting_string);
	starting_wchar =
		(wchar_t *)XtMalloc((unsigned)
			(num_chars + 1) * sizeof(wchar_t));
	mbstowcs(starting_wchar, starting_string, num_chars + 1);

	n = 0;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNtopWidget, Label3); n++;
	XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNhighlightThickness, 2); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNcolumns, 32); n++;
	XtSetArg(args[n], XmNrows, 1); n++;
	XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("wheat")); n++;
	XtSetArg(args[n], XmNvalueWcs, starting_wchar); n++;
	Text1 = XmCreateTextField(Form, "Text1", args, n);
	XtManageChild(Text1);
	XtFree((char *)starting_wchar);

	/* build the Control Panel Label */
	tcs = XmStringCreateLtoR("Control Panel:", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Text1); n++;
	XtSetArg(args[n], XmNtopOffset, 25); n++;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	Label5 = XmCreateLabel(Form, "Label5", args, n);
	XtManageChild(Label5);

	XmStringFree(tcs);


	/* build the Call Function pushbutton */
	tcs = XmStringCreateLtoR("Call Function", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Label5); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	ApplyB = XmCreatePushButton(Form, "ApplyB", args, n);
	XtManageChild(ApplyB);

	XtAddCallback(ApplyB, XmNactivateCallback, ApplyCB, NULL);

	XmStringFree(tcs);


	/* build the Clear Args pushbutton */
	tcs = XmStringCreateLtoR("Clear Args", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, ApplyB); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Label5); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	ClearB = XmCreatePushButton(Form, "ClearB", args, n);
	XtManageChild(ClearB);

	XtAddCallback(ClearB, XmNactivateCallback, ClearCB, NULL);

	XmStringFree(tcs);


	/* build the Num Arg 1 Scale */
	tcs = XmStringLtoRCreate("Num Arg 1", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, ApplyB); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString, tcs); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNmaximum, 40); n++;
	Scale1 = XmCreateScale(Form, "Scale1", args, n);
	XtManageChild(Scale1);

	XtAddCallback(Scale1, XmNvalueChangedCallback, Scale1CB, NULL);

	XmStringFree(tcs);


	/* build the Num Arg 2 Scale */
	tcs = XmStringLtoRCreate("Num Arg 2", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Scale1); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString, tcs); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNmaximum, 40); n++;
	Scale2 = XmCreateScale(Form, "Scale2", args, n);
	XtManageChild(Scale2);

	XtAddCallback(Scale2, XmNvalueChangedCallback, Scale2CB, NULL);

	XmStringFree(tcs);


	/* build the Num Arg 3 Scale */
	tcs = XmStringLtoRCreate("Num Arg 3", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Scale2); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString, tcs); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNmaximum, 40); n++;
	Scale3 = XmCreateScale(Form, "Scale3", args, n);
	XtManageChild(Scale3);

	XtAddCallback(Scale3, XmNvalueChangedCallback, Scale3CB, NULL);

	XmStringFree(tcs);


	/* build the True/False Label and ToggleButton */
	tcs = XmStringCreateLtoR("True", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Scale3); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	XtSetArg(args[n], XmNselectColor, CommonGetColor("darkorchid")); n++;
	XtSetArg(args[n], XmNset, True); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	ToggleB = XmCreateToggleButton(Form, "ToggleB", args, n);
	XtManageChild(ToggleB);

	XtAddCallback(ToggleB, XmNvalueChangedCallback, TorFCB, NULL);

	XmStringFree(tcs);

	tcs = XmStringCreateLtoR("True/False Arg", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, ToggleB); n++;
	XtSetArg(args[n], XmNtopOffset, 0); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	Label2 = XmCreateLabel(Form, "Label2", args, n);
	XtManageChild(Label2);

	XmStringFree(tcs);


	starting_wchar =
		(wchar_t *)XtMalloc(2 * sizeof(wchar_t));
	mbstowcs(starting_wchar, "", 2);

	/* build the Status/Input Label and Text */
	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, Label2); n++;
	XtSetArg(args[n], XmNtopOffset, 15); n++;
	XtSetArg(args[n], XmNcolumns, 25); n++;
	XtSetArg(args[n], XmNrows, 1); n++;
	XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("yellow")); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNvalueWcs, starting_wchar); n++;
	StatText = XmCreateScrolledText(Form, "StatText", args, n);
	XtManageChild(StatText);
	XtFree((char *)starting_wchar);

	tcs = XmStringCreateLtoR("Status/Input", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget, List1); n++;
	XtSetArg(args[n], XmNleftOffset, 15); n++;
	XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNtopWidget, StatText); n++;
	XtSetArg(args[n], XmNtopOffset, 0); n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNfontList, newfontlist); n++;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	Label4 = XmCreateLabel(Form, "Label4", args, n);
	XtManageChild(Label4);

	XmStringFree(tcs);

	XtRealizeWidget(Shell1);

	/* test of:
		XmTextFieldGetSelectionWcs()
	*/
	n = 0;
	XtSetArg(args[n], XmNvisibleItemCount, 1); n++;
	XtSetArg(args[n], XmNtopItemPosition, GetSelectionWcs); n++;
	XtSetValues(List1, args, n);

	CommonPause();

	/* test of:
		XmTextFieldInsertWcs()
	*/

	n = 0;
	XtSetArg(args[n], XmNvisibleItemCount, 1); n++;
	XtSetArg(args[n], XmNtopItemPosition, InsertWcs); n++;
	XtSetValues(List1, args, n);

	CommonPause();

	/* test of:
		XmTextFieldGetStringWcs()
		XmTextFieldSetStringWcs()
		XmTextFieldReplaceWcs()
	*/
	n = 0;
	XtSetArg(args[n], XmNvisibleItemCount, 3); n++;
	XtSetArg(args[n], XmNtopItemPosition, GetStringWcs); n++;
	XtSetValues(List1, args, n);

	CommonPause();

	/* test of:
		XmTextFieldGetSubstringWcs()
	*/
	n = 0;
	XtSetArg(args[n], XmNvisibleItemCount, 1); n++;
	XtSetArg(args[n], XmNtopItemPosition, GetSubstringWcs); n++;
	XtSetValues(List1, args, n);

	CommonPause();

	XtAppMainLoop(app_context);

#endif	/* MOTIF1_1 */
}

#ifndef	MOTIF1_1

static void Scale1CB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	scale1_val = ((XmScaleCallbackStruct*)call_data)->value;
}

static void Scale2CB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	scale2_val = ((XmScaleCallbackStruct*)call_data)->value;
}

static void Scale3CB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	scale3_val = ((XmScaleCallbackStruct*)call_data)->value;
}


static void SSelCB_List1(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	function = ((XmListCallbackStruct*)call_data)->item_position;

	switch (function) {
	/* these don't use any controls */
	case GetSelectionWcs:
		n = 0;
		XtSetArg(args[n], XmNsensitive, False); n++;
		XtSetValues(Scale1, args, n);
		XtSetValues(Scale2, args, n);
		XtSetValues(Scale3, args, n);
		XtSetValues(ToggleB, args, n);

		break;

	/* these use the Scale1 and StatText controls */
	case InsertWcs:
		n = 0;
		XtSetArg(args[n], XmNsensitive, True); n++;
		XtSetValues(Scale1, args, n);

		n = 0;
		XtSetArg(args[n], XmNsensitive, False); n++;
		XtSetValues(Scale2, args, n);
		XtSetValues(Scale3, args, n);
		XtSetValues(ToggleB, args, n);

		break;

	/* these use only the StatText control */
	case GetStringWcs:
	case SetStringWcs:
		n = 0;
		XtSetArg(args[n], XmNsensitive, False); n++;
		XtSetValues(Scale1, args, n);
		XtSetValues(Scale2, args, n);
		XtSetValues(Scale3, args, n);
		XtSetValues(ToggleB, args, n);

		break;

	/* these use the Scale1, Scale2 and StatText controls */
	case ReplaceWcs:
		n = 0;
		XtSetArg(args[n], XmNsensitive, True); n++;
		XtSetValues(Scale1, args, n);
		XtSetValues(Scale2, args, n);

		n = 0;
		XtSetArg(args[n], XmNsensitive, False); n++;
		XtSetValues(Scale3, args, n);
		XtSetValues(ToggleB, args, n);

		break;

	/* these use the Scale1, Scale2, Scale3 and StatText controls */
	case GetSubstringWcs:
		n = 0;
		XtSetArg(args[n], XmNsensitive, True); n++;
		XtSetValues(Scale1, args, n);
		XtSetValues(Scale2, args, n);
		XtSetValues(Scale3, args, n);

		n = 0;
		XtSetArg(args[n], XmNsensitive, False); n++;
		XtSetValues(ToggleB, args, n);

		break;

	default:
		printf("Not a valid function\n");
	}
}


static void ClearCB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	XmString	tcs;
	wchar_t 	*tmp_wstr;

	XmListDeselectAllItems(List1);
	function = -1;

	n = 0;
	XtSetArg(args[n], XmNvalue, 0); n++;
	XtSetValues(Scale1, args, n);
	XtSetValues(Scale2, args, n);
	XtSetValues(Scale3, args, n);

	tcs = XmStringCreateLtoR("True", XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	XtSetArg(args[n], XmNset, True); n++;
	XtSetValues(ToggleB, args, n);
	XmStringFree(tcs);

	torf = True;

	tmp_wstr = (wchar_t *)XtMalloc(2 * sizeof(wchar_t));
	mbstowcs(tmp_wstr, "", 2);
	XmTextSetStringWcs(StatText, tmp_wstr);
	XtFree((char *)tmp_wstr);
}


#define NO_SELECT_MSG		"No selection found"
#define CP_FAIL_MSG		"Return: XmCOPY_FAILED"
#define CP_TRUNC_MSG		"(XmCOPY_TRUNCATED) "

static void ApplyCB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	char	stat_str[25];
	int	left, right;
	Position	x, y;
	wchar_t	*tmp_wstr;
	XmAnyCallbackStruct *c_d;
	int	num_chars = 0;
	int	retval;

	c_d = (XmAnyCallbackStruct *) call_data;

	switch (function) {
	case GetSelectionWcs:
		tmp_wstr = NULL;
		tmp_wstr = XmTextFieldGetSelectionWcs(Text1);
		if (tmp_wstr == NULL)
			{
			num_chars = strlen(NO_SELECT_MSG);
			tmp_wstr = (wchar_t *)XtMalloc((unsigned)
				(num_chars + 1) * sizeof(wchar_t));
			mbstowcs(tmp_wstr,
				NO_SELECT_MSG, num_chars + 1);
			XmTextSetStringWcs(StatText, tmp_wstr);
			}
		else
			XmTextSetStringWcs(StatText, tmp_wstr);
		XtFree((char *)tmp_wstr);
		break;
	case InsertWcs:
		XmTextFieldInsertWcs(Text1, (XmTextPosition)scale1_val,
			XmTextGetStringWcs(StatText));
		break;
	case GetStringWcs:
		tmp_wstr = XmTextFieldGetStringWcs(Text1);
		XmTextSetStringWcs(StatText, tmp_wstr);
		break;
	case SetStringWcs:
		XmTextFieldSetStringWcs(Text1, XmTextGetStringWcs(StatText));
		break;
	case ReplaceWcs:
		XmTextFieldReplaceWcs(Text1, scale1_val, scale2_val,
			XmTextGetStringWcs(StatText));
		break;
	case GetSubstringWcs:
		tmp_wstr = (wchar_t *)XtMalloc((unsigned)
			(scale3_val + 1) * sizeof(wchar_t));
		retval = XmTextFieldGetSubstringWcs(Text1,
			(XmTextPosition)scale1_val,
			scale2_val, scale3_val, tmp_wstr);
		switch (retval)
		{
		case XmCOPY_SUCCEEDED:
			XmTextSetStringWcs(StatText, tmp_wstr);
			break;
		case XmCOPY_FAILED:
			num_chars = strlen(CP_FAIL_MSG);
			tmp_wstr = (wchar_t *)XtMalloc((unsigned)
				(num_chars + 1) * sizeof(wchar_t));
			mbstowcs(tmp_wstr, CP_FAIL_MSG, num_chars + 1);
			XmTextSetStringWcs(StatText, tmp_wstr);
			break;
		case XmCOPY_TRUNCATED:
			/* display the truncated text first */
			XmTextSetStringWcs(StatText, tmp_wstr);
			/* then, insert the warning msg before it */
			num_chars = strlen(CP_TRUNC_MSG);
			tmp_wstr = (wchar_t *)XtMalloc((unsigned)
				(num_chars + 1) * sizeof(wchar_t));
			mbstowcs(tmp_wstr, CP_TRUNC_MSG, num_chars + 1);
			XmTextInsertWcs(StatText, (XmTextPosition)0, tmp_wstr);
			break;
		default:
			printf(
			"XmTextFieldGetSubstringWcs() returned bad value: %d\n",
				retval);
		};
		XtFree((char *)tmp_wstr);
		break;
	default:
		printf("Please select a valid function.\n");
	};
}


static void TorFCB(Widget w, XtPointer client_data,
				XtPointer call_data)
{
	XmString	tcs;

	torf = ((XmToggleButtonCallbackStruct*)call_data)->set;
	if (torf)
		tcs = XmStringCreateLtoR("True", XmSTRING_DEFAULT_CHARSET);
	else
		tcs = XmStringCreateLtoR("False", XmSTRING_DEFAULT_CHARSET);

	n = 0;
	XtSetArg(args[n], XmNlabelString, tcs); n++;
	XtSetValues(w, args, n);

	XmStringFree(tcs);
}

#endif	/* MOTIF1_1 */
