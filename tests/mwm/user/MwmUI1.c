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
static char rcsid[] = "$XConsortium: MwmUI1.c /main/5 1995/07/13 20:25:28 drk $"
#endif
#endif

/*
 *	file: MwmUI1.c
 *	
 *	Program to test the basic UI of mwm.
 *
 */

#include <testlib.h>

char	*test_string = "THIS IS JUST A TEST STRING";


void main (argc, argv)
int argc;
char 			**argv;
{

	Widget	bboard;
	Widget 	rowcolumn1;
	Widget	label1, label2, label3, label4, label5, label6, label7, label8;
	Arg		args[10];
	int		j = 0, n;
	XmString	tcs;
	XmString	dir;
	XmString	newtcs;
	XFontStruct	*fnt;
	XmFontList	font1 = NULL;
	XmFontList	font2 = NULL;
	XmFontList	font3 = NULL;
	XmFontList	font4 = NULL;
#ifdef MOTIF1_1
	XmStringCharSet	cs = (char *) XmSTRING_DEFAULT_CHARSET;
#else
	XmFontListEntry	fixed_font = NULL;
	XmFontListEntry	fontEntry1 = NULL;
	XmFontListEntry	fontEntry2 = NULL;
	XmFontListEntry	fontEntry3 = NULL;
	XmFontListEntry	fontEntry4 = NULL;
	XmStringCharSet	cs = (char *) XmFONTLIST_DEFAULT_TAG;
#endif


	/*  initialize toolkit  */
    CommonTestInit(argc, argv);

#ifdef MOTIF1_1
	fnt = XLoadQueryFont(XtDisplay(Shell1), "9x15bold");
	if (fnt != NULL) {
		font1 = XmFontListCreate(fnt, cs);
	}

	fnt = XLoadQueryFont(XtDisplay(Shell1), "12x24");
	if (fnt != NULL)
		font2 = XmFontListCreate(fnt, cs);

	fnt = XLoadQueryFont(XtDisplay(Shell1), "6x12");
	if (fnt != NULL)
		font3 = XmFontListCreate(fnt, cs);

	fnt = XLoadQueryFont(XtDisplay(Shell1), "courb24");
	if (fnt != NULL)
		font4 = XmFontListCreate(fnt, cs);
#else
	fixed_font = XmFontListEntryLoad(display, "fixed", XmFONT_IS_FONT, 
							 	  	 XmFONTLIST_DEFAULT_TAG);

	if ((fontEntry1 = XmFontListEntryLoad(display, "9x15bold", XmFONT_IS_FONT, 
									 XmFONTLIST_DEFAULT_TAG)) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for 9x15bold\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry1 = fixed_font;


	}
        font1 = XmFontListAppendEntry( NULL, fontEntry1 );
	if ((fontEntry2 = XmFontListEntryLoad(display, "12x24", XmFONT_IS_FONT,
									 XmFONTLIST_DEFAULT_TAG)) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for 12x24\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry2 = fixed_font;

	}
        font2 = XmFontListAppendEntry( NULL, fontEntry2 );
	if ((fontEntry3 = XmFontListEntryLoad(display, "6x12", XmFONT_IS_FONT, 
									 XmFONTLIST_DEFAULT_TAG)) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for 6x12\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry3 = fixed_font;

	}
        font3 = XmFontListAppendEntry( NULL, fontEntry3 );
	if ((fontEntry4 = XmFontListEntryLoad(display, "courb24", XmFONT_IS_FONT, 
									 XmFONTLIST_DEFAULT_TAG)) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for courb24\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		fontEntry4 = fixed_font;

	}
        font4 = XmFontListAppendEntry( NULL, fontEntry4 );
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

/* change fonts in the bulletinboard */

#ifdef MOTIF1_1
	tcs = XmStringCreate(test_string, XmSTRING_DEFAULT_CHARSET);
#else
	tcs = XmStringCreate(test_string, XmFONTLIST_DEFAULT_TAG);
#endif
	XtRealizeWidget (Shell1);

	CommonPause();

	n = 0;
	XtSetArg (args[n], XmNlabelString, tcs);	n++;
	XtSetArg (args[n], XmNfontList, font1);      n++;
	label1 = XmCreateLabel (rowcolumn1, "label1", args, n);
	XtManageChild (label1);

	CommonPause();

	n = 0;
	XtSetArg (args[n], XmNfontList, font2);      n++;
	XtSetValues(label1, args, n);

	CommonPause();

												/* BeginPIR2939 */
	n = 0;
	XtSetArg (args[n], XmNfontList, font3);      n++;
	XtSetValues(label1, args, n);

	CommonPause();

	n = 0;
	XtSetArg (args[n], XmNfontList, font4);      n++;
	XtSetValues(label1, args, n);

	CommonPause();
												/* EndPIR2939 */

	CommonPause();								/* PIR4141 */

	CommonPause();

	XtAppMainLoop(app_context);

}
