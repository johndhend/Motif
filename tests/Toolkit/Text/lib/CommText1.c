/* $XConsortium: CommText1.c /main/6 1995/07/15 21:10:44 drk $ */
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

static char font[] = "-adobe-courier-medium-r-normal--14-140-75-75-m-90-iso8859-1";

static char render_tag[] = "render1";

static char string0[] = "Some Text.";

static char string1[] = "\
The ittsie bittsie spider\n\
went up the water spout.\n\
Down came the rain and\n\
washed the spider out.\n\
Out came the sun and\n\
dried up all the rain.\n\
And the ittsie bittsie spider\n\
went up the spout again.";

static char string2[] = "Spider Lives!";
 
  
void
main_text1 (int argc, char **argv)
{
	Arg args[MAX_ARGS];
	int n;
	Widget SWin = NULL;
	Widget Text1 = NULL;
	unsigned char scrollingPolicy;
        XmString      tcs;
        XmRendition   rendition;
        XmRenderTable renderTab = NULL;
 	XFontStruct   *fontStruct;


	/*  initialize toolkit  */
	CommonTestInit(argc, argv);
	 
	n = 0;
	/* test case for CR 4356 */
	XtSetArg(args[n], XmNscrollingPolicy, (unsigned char) 42); n++;
	SWin = XmCreateScrolledWindow(Shell1, "SWin", args, n);
	XtManageChild (SWin);

	/* test case for CR 4356 */
	n = 0;
	XtSetArg(args[n], XmNscrollingPolicy, &scrollingPolicy); n++;
	XtGetValues(SWin, args, n);
	if (scrollingPolicy == XmAPPLICATION_DEFINED) 
	{
	    printf("GetValues of scrollingPolicy = XmAPPLICATION_DEFINED\n");
	}
	else
	{
	    printf("GetValues of scrollingPolicy = %d \n",
			scrollingPolicy);
	}


       /*  Load font used by XmCSText widget. */
        fontStruct = XLoadQueryFont( display, font );

	n = 0;
/*
 * Added as a test for PIR #768		03-14-1990
 */
        tcs = XmStringCreate( string0, XmFONTLIST_DEFAULT_TAG );
	XtSetArg(args[n], XmNrows, 4);  n++;
	XtSetArg(args[n], XmNcolumns, 28);  n++;
	XtSetArg(args[n], XmNscrollVertical, True);  n++;
	XtSetArg(args[n], XmNscrollHorizontal, True);  n++;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
     
	XtSetArg(args[n], XmNvalue, string0); n++;
	XtSetArg(args[n], XmNfontList, CommonGetFontList(font)); n++;
	Text1 = XmCreateText(SWin, "Text1", args, n);
	XtManageChild (Text1);
        XmStringFree(tcs);

	XtRealizeWidget(Shell1);
	
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
       
       /*  Test case for CR 5166. */
        tcs = XmStringCreateLtoR( string1, XmFONTLIST_DEFAULT_TAG );

        n = 0;
        XtSetArg( args[n], XmNrows, 2 ); n++;
        XtSetArg( args[n], XmNeditable, False ); n++;
	XtSetArg(args[n], XmNvalue, string1 ); n++;
        XtSetValues( Text1, args, n );
        XmStringFree(tcs);

	CommonPause();

	XmTextSetString( Text1, string2 );
         
	CommonPause();
	CommonPause();

	XtAppMainLoop(app_context);

}
