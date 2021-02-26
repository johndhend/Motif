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
static char rcsid[] = "$XConsortium: FontListC.c /main/7 1995/07/13 19:52:48 drk $"
#endif
#endif

#include <stdio.h>
#include <testlib.h>

#include "FontList.h"

#define	NUM_TESTS 5

extern void	error_proc();

String		expected_result[NUM_TESTS] =
{
    "FAILURE",
    "SUCCESS",
    "FAILURE",
    "SUCCESS",
    "SUCCESS"
};

main(argc, argv)
     int argc;
     char		*argv[];
{
    
    fontlist_num = font_num = charset_num = 0;
    errors = 0;
    
    CommonTestInit(argc, argv);

/*
 * Load valid fonts into font structures
 */

    for(font_num=1 ; font_num<NUM_FONTS ; font_num++) {

		if((font[font_num] = XLoadQueryFont(display, fontname[font_num]))
	   		== NULL) {
	    	sprintf(error_string, "Can't load font \"%s\"",
		    		fontname[font_num]);
	    	error_proc("FontListC", error_string);
		}

    }

    font_num = 0;

    fprintf(stdout, "                                          Expected  ");
    fprintf(stdout, " Actual\n");
    fprintf(stdout, "Test  Font      Character Set              Result   ");
    fprintf(stdout, " Result  Error\n");
    fprintf(stdout, "----  --------  ------------------------  --------  ");
    fprintf(stdout, "-------  -----\n");
    fflush(stdout);
   
/*
                                          Expected   Actual
Test  Font      Character Set              Result    Result  Error
----  --------  ------------------------  --------  -------  -----
*/

/*************************************************************
 * Test 1: Create a font list with an invalid font structure *
 *************************************************************/

    fprintf(stdout, "  %1d   %8s  %24s   %7s", fontlist_num+1,
	    	fontname[font_num], charsetname[charset_num],
	    	expected_result[fontlist_num]);
    fflush(stdout);

/*
 * Create a font list
 */

    if ((fontlist[fontlist_num++] = XmFontListCreate(font[font_num++],
						    						 charset[charset_num]))
       												 == NULL)
		fprintf(stdout, "  FAILURE\n");
    else {
		errors++;
		fprintf(stdout, "  SUCCESS    *\n");
    }
    
/**********************************************************
 * Test 2: Create a font list with a valid font structure *
 **********************************************************/

    fprintf(stdout, "  %1d   %8s  %24s   %7s", fontlist_num+1,
	    	fontname[font_num], charsetname[charset_num],
	    	expected_result[fontlist_num]);
    fflush(stdout);

/*
 * Create a font list
 */

    if ((fontlist[fontlist_num++] = XmFontListCreate(font[font_num],
						    						 charset[charset_num++]))
       												 == NULL) {
		errors++;
		fprintf(stdout, "  FAILURE    *\n");
    }
    else
		fprintf(stdout, "  SUCCESS\n");
    
/************************************************************
 * Test 3: Create a font list with an invalid character set *
 ************************************************************/

    fprintf(stdout, "  %1d   %8s  %24s   %7s", fontlist_num+1,
	    	fontname[font_num], charsetname[charset_num],
	    	expected_result[fontlist_num]);
    fflush(stdout);

/*
 * Create a font list
 */

    if ((fontlist[fontlist_num++] = XmFontListCreate(font[font_num++],
						    						 charset[charset_num++]))
       												 == NULL)
		fprintf(stdout, "  FAILURE\n");
    else {
		errors++;
		fprintf(stdout, "  SUCCESS    *\n");
    }

/*********************************************************
 * Test 4: Create a font list with a valid character set *
 *********************************************************/

    fprintf(stdout, "  %1d   %8s  %24s   %7s", fontlist_num+1,
	    	fontname[font_num], charsetname[charset_num],
	    	expected_result[fontlist_num]);
    fflush(stdout);

/*
 * Create a font list
 */

    if ((fontlist[fontlist_num++] = XmFontListCreate(font[font_num++],
						    						 charset[charset_num++]))
       												 == NULL) {
		errors++;
		fprintf(stdout, "  FAILURE    *\n");
    }
    else
		fprintf(stdout, "  SUCCESS\n");

/***********************************************
 * Test 5: Create a font list with a character *
 *         set defined in an app-defaults file *
 ***********************************************/

    fprintf(stdout, "  %1d   %8s  %24s   %7s", fontlist_num+1,
	    	fontname[font_num], charsetname[charset_num],
	    	expected_result[fontlist_num]);
    fflush(stdout);

/*
 * Create a font list
 */

    if ((fontlist[fontlist_num++] = XmFontListCreate(font[font_num],
						    						 charset[charset_num]))
       												 == NULL) {
		errors++;
		fprintf(stdout, "  FAILURE    *\n");
    }
    else
		fprintf(stdout, "  SUCCESS\n");

    summary_proc("FontListC", errors);

    CommonPause();
    XtAppMainLoop( app_context );

}
