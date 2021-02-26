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
static char rcsid[] = "$XConsortium: FontListA.c /main/8 1995/07/13 19:52:33 drk $"
#endif
#endif

#include <stdio.h>
#include <testlib.h>

#include "FontList.h"

#define	NUM_TESTS 7

extern void	error_proc();

String		expected_return[NUM_TESTS] =
{
    "fontlist1",
    "fontlist3",
    "fontlist3",
    "fontlist5",
    "fontlist6",
    "fontlist7",
    "NULL",
};

String		oldlist[NUM_TESTS] =
{
    "fontlist1",
    "fontlist2",
    "fontlist3",
    "fontlist4",
    "fontlist5",
    "fontlist6",
    "NULL",
};

main(argc, argv)
int argc;
char	*argv[];
{

    int   i;

    fontlist_num = font_num = charset_num = 0;
    errors = 0;
    
    CommonTestInit(argc, argv);

	/*
 	 * Load valid fonts into font structures
 	 */
    for (font_num = 1; font_num < NUM_FONTS; font_num++) {

		if ((font[font_num] = XLoadQueryFont(display, 
											 fontname[font_num])) == NULL) {
			sprintf(error_string, "Can't load font \"%s\"", fontname[font_num]);
	    	error_proc("FontListA", error_string);
		}
    }

    font_num = 0;

	/*
 	 * Create a font list
 	 */

    if ((fontlist[fontlist_num] = XmFontListCreate(font[font_num+1],
						  						   charset[charset_num])) 
												   == NULL)
		error_proc("FontListA", "Can't create fontlist1\n");

    fontlist_num++;

    fprintf(stdout, "         Old                                         ");
    fprintf(stdout, "Expected   Actual\n");
    fprintf(stdout, "Test  Font List  Font      Character Set             ");
    fprintf(stdout, "Return     Return    Error\n");
    fprintf(stdout, "----  ---------  --------  ------------------------  ");
    fprintf(stdout, "---------  --------- -----\n");
    fflush(stdout);
   
/*
         Old                                         Expected   Actual
Test  Font List  Font      Character Set             Return     Return    Error
----  ---------  --------  ------------------------  ---------  --------- -----
*/

/********************************************************************
 * Test 1: Add a font with an invalid font structure to a font list *
 ********************************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num++], 
										   charset[charset_num]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1])
		fprintf(stdout, "  fontlist1\n");
    else if (fontlist[fontlist_num] == NULL) {

		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else {
		errors++;
		fprintf(stdout, "  fontlist2   *\n");
    }

    fontlist_num++;
   
/*****************************************************
 * Test 2: Add a valid font to an existing font list *
 *****************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num], 
										   charset[charset_num++]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1]) {
		errors++;
		fprintf(stdout, "  fontlist2   *\n");
    }
    else if (fontlist[fontlist_num] == NULL) {

		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else
		fprintf(stdout, "  fontlist3\n");
   
    fontlist_num++;
   
/*******************************************************************
 * Test 3: Add a font with an invalid character set to a font list *
 *******************************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num++], 
										   charset[charset_num++]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1])
		fprintf(stdout, "  fontlist3\n");
    else if (fontlist[fontlist_num] == NULL) {

		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else {
		errors++;
		fprintf(stdout, "  fontlist4   *\n");
    }
   
    fontlist_num++;

/****************************************************************
 * Test 4: Add a font with a valid character set to a font list *
 ****************************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num++], 
										   charset[charset_num++]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1]) {
		errors++;
		fprintf(stdout, "  fontlist4   *\n");
    }
    else if (fontlist[fontlist_num] == NULL) {

		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else
		fprintf(stdout, "  fontlist5\n");
   
    fontlist_num++;
   
/***************************************************
 * Test 5: Add a font with a character set defined *
 *         in an app-defaults file to a font list  *
 ***************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num], 
										   charset[charset_num]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1]) {
		errors++;
		fprintf(stdout, "  fontlist5   *\n");
    }
    else if (fontlist[fontlist_num] == NULL) {
	
		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else
		fprintf(stdout, "  fontlist6\n");
   
    fontlist_num++;
   
/*************************************************
 * Test 6: Add the same font to a fontlist twice *
 *************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    fontlist[fontlist_num] = XmFontListAdd(fontlist[fontlist_num-1],
					   					   font[font_num], 
										   charset[charset_num]);
   
    if (fontlist[fontlist_num] == fontlist[fontlist_num-1]) {
		errors++;
		fprintf(stdout, "  fontlist6   *\n");
    }
    else if (fontlist[fontlist_num] == NULL) {

		errors++;
		fprintf(stdout, "       NULL   *\n");
		fontlist[fontlist_num] = fontlist[0];

    }
    else
		fprintf(stdout, "  fontlist7\n");
   
    fontlist_num++;
   
/*******************************************************
 * Test 7: Add a valid font to a nonexistent font list *
 *******************************************************/

    fprintf(stdout, "  %1d   %9s  %8s  %24s  %9s", fontlist_num,
	    	oldlist[fontlist_num-1], fontname[font_num],
	    	charsetname[charset_num], expected_return[fontlist_num-1]);
    fflush(stdout);

/*
 * Add to a fontlist
 */

    if ((fontlist[fontlist_num] = XmFontListAdd(NULL, font[font_num],
					       						charset[charset_num])) 
												== NULL)
		fprintf(stdout, "       NULL\n");
    else {
		errors++;
		fprintf(stdout, "  fontlist8   *\n");
    }
   
    fontlist_num++;

    summary_proc("FontListA", errors);

    if ( fontlist[fontlist_num - 1] )
          XmFontListFree( fontlist[fontlist_num - 1] );

    CommonPause();
    XtAppMainLoop( app_context );

}
