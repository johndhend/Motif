/* $XConsortium: Text13.c /main/5 1995/07/15 21:10:14 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */

#include <testlib.h>

#define NUM_FONTS 3

static char *font_names[] = {
  "6x12", "fixed", "9x15" };

static char string1[] =
"Some meaningless text with which to test       \n\
123456781234567812345678123456781234567812345678\n\
the insertion of tabs into an XmText widget     \n\
123456781234567812345678123456781234567812345678\n\
totally, meaningless, garbage...................";

Widget Text1;

void
SetNewFont( Widget w, XtPointer client_data, XtPointer call_data )
{
	char *new_font = (char *)client_data;
	XmToggleButtonCallbackStruct *cb_data = 
                         (XmToggleButtonCallbackStruct *)call_data;
	Arg	args[25];
	int	n;

	if ( cb_data->set )
        {
           n = 0;
           XtSetArg( args[n], XmNfontList, CommonGetFontList( new_font )); n++;
           XtSetValues( Text1, args, n );
        }
}
           

void
ResetString( Widget w, XtPointer client_data, XtPointer call_data )
{
	Widget  text = (Widget)client_data;
	Arg	args[25];
	int	n;

        XmTextSetString( text, string1 );
	return;
}

void
main( int argc, char *argv[] )
{
	Widget	  Form, RowColumn, ToggleB[NUM_FONTS], PushB;
	Arg   	  args[25];
	int	  n, i;
	XmString  tmp_string;
	char      buffer[25];

	CommonTestInit( argc, argv );

	n = 0;
	XtSetArg( args[n], XmNallowShellResize, True ); n++;
        XtSetValues( Shell1, args, n );

	n = 0;
        Form = XmCreateForm( Shell1, "Form", args, n );
	XtManageChild( Form );

	n = 0;
	XtSetArg( args[n], XmNtopAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNrightAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNresizeWidth, True ); n++;
	XtSetArg( args[n], XmNcolumns, 48 ); n++;
	XtSetArg( args[n], XmNrows, 4 ); n++;
        XtSetArg( args[n], XmNvalue, string1 ); n++;
        XtSetArg( args[n], XmNeditMode, XmMULTI_LINE_EDIT ); n++;
        XtSetArg( args[n], XmNfontList, CommonGetFontList("6x12")); n++;
        Text1 = XmCreateScrolledText( Form, "Text1", args, n );
	XtManageChild( Text1 );

	n = 0;
	XtSetArg( args[n], XmNtopAttachment, XmATTACH_WIDGET ); n++;
	XtSetArg( args[n], XmNtopWidget, Text1 ); n++;
	XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNrightAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNradioBehavior, True ); n++;
	RowColumn = XmCreateRowColumn( Form, "RowColumn", args, n );
	XtManageChild( RowColumn );

	for ( i = 0; i < NUM_FONTS; i++ )
        {
	    tmp_string = XmStringGenerate( font_names[i], 
                                           XmFONTLIST_DEFAULT_TAG,
		                           XmCHARSET_TEXT, NULL );

	    n = 0;
            XtSetArg( args[n], XmNlabelString, tmp_string ); n++; 
            XtSetArg( args[n], XmNselectColor, CommonGetColor("green")); n++; 
            if ( i == 0 )
            {
              XtSetArg( args[n], XmNset, True ); n++; 
            }
            sprintf( buffer, "ToggleB%d", i );
	    ToggleB[i] = XmCreateToggleButton( RowColumn, buffer, args, n );
	    XtAddCallback( ToggleB[i], XmNvalueChangedCallback,
                           SetNewFont, (XtPointer)font_names[i] );
          
            XmStringFree( tmp_string );
        }

	XtManageChildren( ToggleB, NUM_FONTS );

	tmp_string = XmStringGenerate( "Reset String", 
                                       XmFONTLIST_DEFAULT_TAG,
	                               XmCHARSET_TEXT, NULL );

	n = 0;
	XtSetArg( args[n], XmNtopAttachment, XmATTACH_WIDGET ); n++;
	XtSetArg( args[n], XmNtopWidget, RowColumn ); n++;
	XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
	XtSetArg( args[n], XmNrightAttachment, XmATTACH_FORM ); n++;
        XtSetArg( args[n], XmNlabelString, tmp_string ); n++;
	PushB = XmCreatePushButton( RowColumn, "PushB", args, n );
	XtManageChild( PushB );

	XtAddCallback( PushB, XmNactivateCallback, ResetString, Text1 );

	XtRealizeWidget( Shell1 );

	CommonPause();

       /*
        *  Shrink the width of the Text widget.
        */
        n = 0; 
	XtSetArg( args[n], XmNcolumns, 20 ); n++;
	XtSetArg( args[n], XmNresizeWidth, False ); n++;
	XtSetValues( Text1, args, n );

	CommonPause();
	CommonPause();


	XtAppMainLoop( app_context );
}
