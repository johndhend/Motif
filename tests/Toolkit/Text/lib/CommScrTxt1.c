/* $XConsortium: CommScrTxt1.c /main/6 1995/07/15 21:10:33 drk $ */
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

Widget BBoard1;
Widget Text1, Text2;
Widget EditLabel, ToggleB1;
Arg args[MAX_ARGS];
int n;

static char new_string1[] = "\
As I was going to St. Ives\n\
I met a man with seven wives\n\
Each wife had seven sacks,\n\
Each sack had seven cats,\n\
Each cat had seven kits\n\
Kits, cats, sacks, and wives,\n\
How many were going to St. Ives?";

static char new_string2[] = "\
Jack Sprat could eat no fat\n\
His wife could eat no lean\n\
And so between them both\n\
They licked the platter clean";

static char new_string3[] = "\
john said, jack, enjoy the job";

int     EditMode;

static char font_name1[] = "8x13bold"; 
static char font_name2[] = "variable"; 

static char render_tag[] = "Render1";

static void HelpCB(Widget w, XtPointer client_data,
                                XtPointer call_data)
{
        Widget info_box = NULL;
        XmString helpString, titleString, okString;

        helpString = XmStringGenerate ("Help has arrived!",
                XmFONTLIST_DEFAULT_TAG,  XmCHARSET_TEXT, NULL );
        titleString = XmStringCreateLtoR ("Info box",
                XmSTRING_DEFAULT_CHARSET);
        okString = XmStringCreateLtoR ("Dismiss",
                XmSTRING_DEFAULT_CHARSET);
        n = 0;
        XtSetArg (args[n], XmNmessageString, helpString); n++;
        XtSetArg (args[n], XmNokLabelString, okString); n++;
        XtSetArg (args[n], XmNdialogTitle, titleString); n++;
        info_box = XmCreateInformationDialog (Shell1, "info_box", args, n);
        XtManageChild (info_box);

        XmStringFree (helpString);
        XmStringFree (titleString);
        XmStringFree (okString);
}

static void ChangeString(Widget w, XtPointer client_data,
                                XtPointer call_data)
{
        int file_length;
        unsigned char *file_string;
        XmString string;

        static int swtch = 0;

	XmTextSetString( Text1, " " );

        if( swtch++ % 2 )
        {
	  XmTextSetString( Text1, new_string2 );
        }
        else
        {
          n = 0;
	  XtSetArg( args[n], XmNvalue, new_string1 ); n++;
          XtSetValues( Text1, args, n );
        }
}


static void ChangeEditMode(Widget w, XtPointer client_data,
                                XtPointer call_data)
{
        XmString        tcs;
        int     rows;

        EditMode = XmMULTI_LINE_EDIT + XmSINGLE_LINE_EDIT - EditMode;

        n = 0;
        XtSetArg(args[n], XmNeditMode, EditMode); n++;
        XtSetArg(args[n], XmNrows, 3); n++;
        XtSetValues(Text2, args, n);

        if (EditMode == XmSINGLE_LINE_EDIT)
                tcs = XmStringCreateLtoR("XmSINGLE_LINE_EDIT",
                        XmSTRING_DEFAULT_CHARSET);
        else
                tcs = XmStringCreateLtoR("XmMULTI_LINE_EDIT",
                        XmSTRING_DEFAULT_CHARSET);

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs); n++;
        XtSetValues(w, args, n);
        XmStringFree(tcs);
}

void
main_scrtext1(int argc, char **argv)
{
        XtTranslations table1;
        static String trans_string1 = "Shift<Key>osfPageDown: activate()";
        XmString        tcs, string;
        XmRendition     rendition;
        XmRenderTable   renderTab = NULL;

        /*  initialize toolkit  */
        CommonTestInit(argc, argv);

        table1 = XtParseTranslationTable (trans_string1);

        n = 0;
        BBoard1 = XmCreateBulletinBoard (Shell1, "BBoard1", args, n);
        XtManageChild (BBoard1);

        n = 0;
        XtSetArg(args[n], XmNrows, 10);  n++;
        XtSetArg(args[n], XmNscrollVertical, True);  n++;
        XtSetArg(args[n], XmNscrollHorizontal, True);  n++;
        XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNvalue, new_string2); n++;
	XtSetArg(args[n], XmNfontList, CommonGetFontList(font_name1));  n++;
        Text1 = XmCreateScrolledText(BBoard1, "Text1", args, n);

        XtAddCallback(Text1, XmNactivateCallback, ChangeString, NULL);
        XtOverrideTranslations (Text1, table1);
        XtManageChild(Text1);

        XtRealizeWidget(Shell1);

        CommonPause();

        XtAddCallback(Text1, XmNhelpCallback, HelpCB, NULL);

        CommonPause();

        /* test case for PIR 2574, see .dat */
        CommonPause();
        /* end of test case for PIR 2574 */

        /* test case for PIR 2127 */

        n = 0;
        XtSetArg(args[n], XmNfontList, CommonGetFontList(font_name2));  n++;
        XtSetArg(args[n], XmNvalue, new_string3);  n++;
        XtSetValues(Text1, args, n);

        CommonPause();
        /* end of test case for PIR 2127 */

        /* test case for PIR 4120 */
        XtUnmanageChild(Text1);

        n = 0;
        XtSetArg(args[n], XmNeditable, True); n++;
        XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
	XtSetArg(args[n], XmNvalue, new_string1); n++;
        XtSetArg(args[n], XmNcolumns, 50); n++;
        XtSetArg(args[n], XmNrows, 3); n++;
        XtSetArg(args[n], XmNscrollHorizontal, True); n++;
        XtSetArg(args[n], XmNscrollVertical, True); n++;
        Text2 = XmCreateScrolledText(BBoard1, "Text2", args, n);
        XtManageChild (Text2);


        /* EditMode togglebutton & label */
        EditMode = XmSINGLE_LINE_EDIT;

        tcs = XmStringCreateLtoR("Current EditMode: ",
                XmSTRING_DEFAULT_CHARSET);
        n = 0;
        XtSetArg(args[n], XmNy, 95);  n++;
        XtSetArg(args[n], XmNlabelString, tcs); n++;
        EditLabel = XmCreateLabel(BBoard1, "EditLabel", args, n);
        XtManageChild(EditLabel);
        XmStringFree(tcs);

        tcs = XmStringCreateLtoR("XmSINGLE_LINE_EDIT",
                XmSTRING_DEFAULT_CHARSET);
        n = 0;
        XtSetArg(args[n], XmNy, 115);  n++;
        XtSetArg(args[n], XmNlabelString, tcs); n++;
        XtSetArg(args[n], XmNset, True); n++;
        ToggleB1 = XmCreateToggleButton(BBoard1, "ToggleB1", args, n);
        XtManageChild(ToggleB1);
        XtAddCallback(ToggleB1, XmNvalueChangedCallback,
                ChangeEditMode, NULL);
        XmStringFree(tcs);

        CommonPause();
        /* end of test case for PIR 4120 */

        XtAppMainLoop(app_context);
}
