/* $TOG: CommText6.c /main/7 1997/10/02 16:23:51 csn $ */
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


/*
 *  Global variables.
 */
Arg args[MAX_ARGS];
int n;

static char string1[] = "Sample Text";
static char string2[] = "Sample Text2";
static char string3[] =  "The <Return> key was pressed.";
static char string4[] = "Changed the string.";

static char font_name1[] = "8x13";
static char font_name2[] = "8x13bold";

static char render_tag[] = "render1";


static void ChangeString(Widget w, XtPointer client_data,
                                XtPointer call_data)
{
    XmString  tcs = (XmString)0;


      n = 0;
    XtSetArg(args[n], XmNvalue, string3 );  n++;
      XtSetValues(w, args, n);

      if ( tcs ) XmStringFree( tcs );
      
}


static void ChangeString2(Widget w, XtPointer client_data,
                                XtPointer call_data)
{
    XmString  tcs = (XmString)0;

      n = 0;
    XtSetArg(args[n], XmNvalue, string4);  n++;
      XtSetValues(w, args, n);
     
      if (tcs) XmStringFree(tcs);
}

void SetStringCB(w, client_data, call_data)
     Widget w;
     XtPointer client_data;
     XtPointer call_data;
{
     XmString  string;
     static char new_string[] = "New\nset\nvalue";
       
     XmTextSetString((Widget)client_data, new_string);
}

void InsertStringCB(w, client_data, call_data)
     Widget w;
     XtPointer client_data;
     XtPointer call_data;
{
     XmString  string;
     static char new_string[] = "+123+";
       
     XmTextInsert((Widget)client_data, 3, new_string);
}


void main_text6 (argc, argv)
     int argc;
     char **argv;
{
	Widget PanedWindow;
	Widget Text1;
	Widget Text2;
        Widget BBoard1;
	XtTranslations new_table;
	static String new_translation = "Ctrl<Key>r: activate()";
        XmString tcs;
        void *ret_val;
        Widget SetStringPB = NULL;
        Widget InsertStringPB = NULL;
        XmString string;
	char temp_string[100], *text2_return;
        XmStringContext *context;
        XmStringCharSet tag;
        XmStringDirection direction;
        XmStringComponentType unknown_tag;
        unsigned short        unknown_length;
        unsigned char         unknown_value;

	/*  initialize toolkit  */
	CommonTestInit(argc, argv);
	
	n = 0;
	XtSetArg(args[n], XmNwidth, 400);  n++;
	XtSetArg(args[n], XmNheight, 300);  n++;
	XtSetValues(Shell1, args, n);
	
	/* test case for PIR 3677 - realized here, not after children mngd */
	XtRealizeWidget(Shell1);
	/* end of test case for PIR 3677 */

	n = 0;
	PanedWindow = XmCreatePanedWindow(Shell1, "PanedWindow", args, n);
	XtManageChild(PanedWindow);

	n = 0;
	XtSetArg(args[n], XmNvalue, string1);  n++;
	XtSetArg(args[n], XmNfontList, CommonGetFontList(font_name1));  n++;
	Text1 = XmCreateText(PanedWindow, "Text1", args, n);
	XtManageChild (Text1);

	n = 0;
	XtSetArg(args[n], XmNfontList, CommonGetFontList(font_name2));  n++;
	XtSetArg(args[n], XmNvalue, string2);  n++;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	Text2 = XmCreateText(PanedWindow, "Text2", args, n);
	XtManageChild (Text2);

	/* begin test for CR */
	CommonPause(); 

	/* The instructions ask the user to change Text1 in a way that
	   can mess up the focus, then modify Text2 by adding a "2" at
	   the end.

	   Check the contents of the strings and print out a warning if
	   the value of the second string is not now "Sample Text22" */

	ret_val = XmTextGetString(Text2);

	text2_return = (char *)ret_val;

	if (!strcmp(text2_return, "The Sample Text2") == 0) 
	   printf ("\n+++\n.Test FAILS. String in Text2 does not match expected value.\n+++\n");
	else printf ("+++\nTest PASSES. No error.\n");
	fflush(stdout);

	XtFree ((char *)ret_val);

	CommonPause();

	/* end test for CR */

	XtAddCallback(Text1, XmNactivateCallback, CommonGenericCB, NULL);
	XtAddCallback(Text1, XmNactivateCallback, ChangeString, NULL);
	XtAddCallback(Text2, XmNactivateCallback, ChangeString2, NULL);

	/* test case for PIR 3677 - this realize is commented out
	XtRealizeWidget (Shell1);
	*/

	CommonPause();
	CommonPause();

	n=0;
	new_table = XtParseTranslationTable (new_translation);
	XtSetArg(args[n], XmNtranslations, new_table); n++;
	XtSetValues (Text2, args, n);

	CommonPause();

	/* test case for PIR 1772, PIR 1058 */
	XtAddCallback(Text1, XmNvalueChangedCallback, CommonGenericCB, NULL);
	XtAddCallback(Text1, XmNmodifyVerifyCallback, CommonGenericCB, NULL);

	CommonPause();
	/* end of test case for PIR 1772, PIR 1058 */

        /*  Begin testing CR 6141 */

        XtDestroyWidget( PanedWindow );

        n = 0;
        XtSetArg(args[n], XmNallowShellResize, True); n++;
        XtSetValues( Shell1, args, n );

        n = 0;
        XtSetArg(args[n], XmNwidth, 200); n++;
        XtSetArg(args[n], XmNheight, 200); n++;
        BBoard1 = XmCreateBulletinBoard( Shell1, "BBoard1", args, n );
        XtManageChild( BBoard1 );

        string = XmStringCreate("", XmFONTLIST_DEFAULT_TAG );

        n = 0;
        XtSetArg( args[n], XmNx, 0 ); n++;
        XtSetArg( args[n], XmNy, 0 ); n++;
        XtSetArg( args[n], XmNrows, 5 ); n++;
        XtSetArg( args[n], XmNcolumns, 40 ); n++;
        XtSetArg( args[n], XmNeditMode, XmMULTI_LINE_EDIT ); n++;
	XtSetArg( args[n], XmNvalue, "" ); n++;
        Text1 = XmCreateText( BBoard1, "Text1", args, n );
        XtManageChild( Text1 );

        string = XmStringCreate("Set String", XmFONTLIST_DEFAULT_TAG );

        n = 0;
        XtSetArg( args[n], XmNx, 0 ); n++;
        XtSetArg( args[n], XmNy, 100 ); n++;
        XtSetArg( args[n], XmNwidth, 100 ); n++;
        XtSetArg( args[n], XmNheight, 30 ); n++;
        XtSetArg( args[n], XmNlabelString, string ); n++;
        SetStringPB = XmCreatePushButton(BBoard1, "SetStringPB", args, n);
        XtAddCallback(SetStringPB, XmNactivateCallback, SetStringCB, Text1);
        XtManageChild (SetStringPB);

        XmStringFree( string );

        string = XmStringCreate("Insert", XmFONTLIST_DEFAULT_TAG );

        n = 0;
        XtSetArg( args[n], XmNx, 110 ); n++;
        XtSetArg( args[n], XmNy, 100 ); n++;
        XtSetArg( args[n], XmNwidth, 90 ); n++;
        XtSetArg( args[n], XmNheight, 30 ); n++;
        XtSetArg( args[n], XmNlabelString, string ); n++;
        InsertStringPB = XmCreatePushButton(BBoard1, "InsertStringPB", args, n);
        XtAddCallback(InsertStringPB, XmNactivateCallback,
                                      InsertStringCB, Text1);
        XtManageChild (InsertStringPB);

        XmStringFree( string );

        CommonPause();
       /*  End testing CR 6141 */

        CommonPause();

	XtAppMainLoop(app_context);
}
