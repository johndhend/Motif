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
static char rcsid[] = "$XConsortium: StringDisp.c /main/6 1995/07/13 19:54:34 drk $"
#endif
#endif

/*
 *	file: StringDisp.c
 *
 *	Create Compound strings and display them as labels.
 */

#include <testlib.h>


char	*hebrew_string = "\372\347\340 \355\362\364 \365\347\354";

char	*kanji_string = "\243\261\262\363\244\316\245\257\245\352\245\303\245\257\244\307";



void main (argc, argv)
int argc;
char 			**argv;
{

	Widget	bboard;
	Widget 	rowcolumn1;
	Widget	label1, label2, label3, label4;
	Arg		args[10];
	int		j = 0, n;
	XmString	tcs;
	XmString	dir;
	XmString	newtcs;
	XFontStruct	*fnt;
	XmFontList	font1 = NULL;
	XmFontList	font2 = NULL;
	static char	not_an_XmString[] = "This is NOT an XmString";

#ifdef MOTIF1_1
	XmStringCharSet	cs = (char *) XmSTRING_DEFAULT_CHARSET;
#else
	XmFontListEntry	fixed_font = NULL;
	XmFontListEntry	fontEntry1 = NULL;
	XmFontListEntry	fontEntry2 = NULL;
	XmStringCharSet	cs = (char *) XmFONTLIST_DEFAULT_TAG;
#endif


	/*  initialize toolkit  */
    CommonTestInit(argc, argv);

#ifdef MOTIF1_1

	fnt = XLoadQueryFont(XtDisplay(Shell1), 
		 	"-Misc-Fixed-Medium-R-Normal--13-120-75-75-C-80-ISO8859-8");
	if (fnt != NULL)
		font1 = XmFontListCreate(fnt, "ISO8859-8");

	fnt = XLoadQueryFont(XtDisplay(Shell1), 
		 	"-k14-screen-medium-r-normal--14-140-75-75-m-140-jisx0208.1983-1");
	if (fnt != NULL)
		font2 = XmFontListCreate(fnt, "jisx0208.1983-1");

#else

	fixed_font = XmFontListEntryLoad(display, "fixed", XmFONT_IS_FONT, 
							 	  	 XmFONTLIST_DEFAULT_TAG);

	if ((fontEntry1 = XmFontListEntryLoad(display, 
					"-Misc-Fixed-Medium-R-Normal--13-120-75-75-C-80-ISO8859-8",
					XmFONT_IS_FONT, "ISO8859-8")) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for \
				-Misc-Fixed-Medium-R-Normal--13-120-75-75-C-80-ISO8859-8\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry1 = fixed_font;

	}
	font1 = XmFontListAppendEntry(NULL, fontEntry1);

	if ((fontEntry2 = XmFontListEntryLoad(display, 
			"-k14-screen-medium-r-normal--14-140-75-75-m-140-jisx0208.1983-1",
			XmFONT_IS_FONT, "jisx0208.1983-1")) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for \
			-k14-screen-medium-r-normal--14-140-75-75-m-140-jisx0208.1983-1\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry2 = fixed_font;

	}
	font2 = XmFontListAppendEntry(NULL, fontEntry2);

#endif

	n = 0;

#ifdef MOTIF1_1
	XtSetArg (args[n], XmNheight, 100 ); n++;
	XtSetArg (args[n], XmNwidth, 100 ); n++;
#endif

	bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);
	XtManageChild (bboard);

	n = 0;

#ifdef MOTIF1_1
	XtSetArg (args[n], XmNheight, 100 ); n++;
	XtSetArg (args[n], XmNwidth, 100 ); n++;
#endif

	XtSetArg (args[n], XmNx, 10 ); n++; 
	XtSetArg (args[n], XmNy, 50 ); n++;  
	rowcolumn1 = XmCreateRowColumn(bboard, "rowcolumn1", args, n);
	XtManageChild (rowcolumn1);

#ifdef MOTIF1_1
	tcs = XmStringCreateLtoR(hebrew_string, XmSTRING_DEFAULT_CHARSET);
#else
	tcs = XmStringCreateLtoR(hebrew_string, XmFONTLIST_DEFAULT_TAG);
#endif

	n = 0;
	XtSetArg (args[n], XmNlabelString, tcs);	n++;
	XtSetArg (args[n], XmNfontList, font1);      n++;
	label1 = XmCreateLabel (rowcolumn1, "label1", args, n);
	XtManageChild (label1);

        XmStringFree( tcs );

	dir = XmStringDirectionCreate(XmSTRING_DIRECTION_R_TO_L);

#ifdef MOTIF1_1
	tcs = XmStringCreate(hebrew_string, XmSTRING_DEFAULT_CHARSET);
#else
	tcs = XmStringCreate(hebrew_string, XmFONTLIST_DEFAULT_TAG);
#endif

	newtcs = XmStringConcat(dir, tcs);

        XmStringFree( dir );
        XmStringFree( tcs );

	n = 0;
	XtSetArg (args[n], XmNlabelString, newtcs);	n++;
	XtSetArg (args[n], XmNfontList, font1);      n++;
	label2 = XmCreateLabel (rowcolumn1, "label2", args, n);
	XtManageChild (label2);
        XmStringFree( newtcs );

	tcs = XmStringCreateLtoR(kanji_string, "jisx0208.1983-1");
	n = 0;
	XtSetArg (args[n], XmNfontList, font2);      n++;
	XtSetArg (args[n], XmNlabelString, tcs);	n++;
	label3 = XmCreateLabel (rowcolumn1, "label3", args, n);
	XtManageChild (label3);
        XmStringFree( tcs );

	dir = XmStringDirectionCreate(XmSTRING_DIRECTION_R_TO_L);
	tcs = XmStringCreate(kanji_string, "jisx0208.1983-1");
	newtcs = XmStringConcat(dir, tcs);
        XmStringFree( dir );


	n = 0;
	XtSetArg (args[n], XmNfontList, font2);      n++;
	XtSetArg (args[n], XmNlabelString, newtcs);	n++;
	label4 = XmCreateLabel (rowcolumn1, "label4", args, n);
	XtManageChild (label4);
        XmStringFree( newtcs );


	XtRealizeWidget (Shell1);

	CommonPause();

	CommonPause();

	/* Begin XmeStringValid test */

	if (XmeStringIsValid(not_an_XmString) == False) 
	    fprintf(stderr, "XmeStringValid PASSED with an invalid string.\n");
	else
	    fprintf(stderr, "XmeStringValid FAILED with an invalid string.\n");

	if (XmeStringIsValid(tcs) == True) 
	    fprintf(stderr, "XmeStringValid PASSED with a valid string.\n");
	else
	    fprintf(stderr, "XmeStringValid FAILED with a valid string.\n");

        XmStringFree( tcs );
	/* End XmeStringValid test */

	CommonPause();

        if ( fixed_font )
           XmFontListEntryFree( &fixed_font );
        if ( fontEntry1 )
           XmFontListEntryFree( &fontEntry1 );
        if ( fontEntry2 )
           XmFontListEntryFree( &fontEntry2 );

        if ( font1 )
           XmFontListFree( font1 );
        if ( font2 )
           XmFontListFree( font2 );


	XtAppMainLoop(app_context);

}
