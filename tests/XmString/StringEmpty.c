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
static char rcsid[] = "$XConsortium: StringEmpty.c /main/7 1995/07/13 19:55:40 drk $"
#endif
#endif

#include <stdio.h>

#include <testlib.h>

#include "String.h"

#define	NUM_TESTS 4

extern void	error_proc();

char	*description_string[NUM_TESTS] =
{
    "Test a string with a nonempty string component",
    "Test a string consisting of just a direction  ",
    "Test a string consisting of just a separator  ",
    "Test a NULL string                            "
};


main(argc, argv)
int argc;
char		*argv[];
{

    string_num = text_num = charset_num = 0;
    errors = 0;

    CommonTestInit(argc, argv);

/*
                                                      XmStringEmpty
Test  Description                                     Expect   Actual    Error
----  -----------                                     -------- --------  -----
  1   Test a string with a nonempty string component  nonempty
  2   Test a string consisting of just a direction    empty
  3   Test a string consisting of just a separator    empty
  4   Test a NULL string                              empty
*/

    fprintf(stdout, "                                                      ");
    fprintf(stdout, "XmStringEmpty\n");
    fprintf(stdout, "Test  Description                                     ");
    fprintf(stdout, "Expect   Actual    Error\n");
    fprintf(stdout, "----  -----------                                     ");
    fprintf(stdout, "-------- --------  -----\n");

/*
 * Test 1: Test a compound string with a nonempty text component
 *         
 */

    if ((string[string_num] = XmStringCreateLtoR(text[text_num],
												 charset[charset_num])) 
												 == NULL) {
		sprintf(error_string, "Can't create string%d", string_num);
		error_proc(error_string);
    }

    fprintf(stdout, "  %d   %s  nonempty ", test_num+1,
	    	description_string[test_num]);
    
    if (XmStringEmpty(string[string_num])) {
		errors++;
		fprintf(stdout, "empty       *\n");
    }
    else
		fprintf(stdout, "nonempty\n");

    string_num++;
    test_num++;
    
/*
 * Test 2: Test a string consisting of just a direction
 */

    if ((string[string_num] = 
		 XmStringDirectionCreate(XmSTRING_DIRECTION_L_TO_R)) == NULL) {
		sprintf(error_string, "Can't create string%d", string_num);
		error_proc(error_string);
    }

    fprintf(stdout, "  %d   %s  empty    ", test_num+1,
	    	description_string[test_num]);
    
    if (!XmStringEmpty(string[string_num])) {
		errors++;
		fprintf(stdout, "nonempty    *\n");
    }
    else
		fprintf(stdout, "empty\n");

    string_num++;
    test_num++;
    
/*
 * Test 3: Test a string consisting of just a separator
 */

    if ((string[string_num] = XmStringSeparatorCreate()) == NULL) {
		sprintf(error_string, "Can't create string%d", string_num);
		error_proc(error_string);
    }

    fprintf(stdout, "  %d   %s  empty    ", test_num+1,
	    	description_string[test_num]);
    
    if (!XmStringEmpty(string[string_num])) {
		errors++;
		fprintf(stdout, "nonempty    *\n");
    }
    else
		fprintf(stdout, "empty\n");

    string_num++;
    test_num++;

/*
 * Test 4: Test a NULL string
 */

    fprintf(stdout, "  %d   %s  empty    ", test_num+1,
	    	description_string[test_num]);
    
    if (!XmStringEmpty(NULL)) {
		errors++;
		fprintf(stdout, "nonempty    *\n");
    }
    else
		fprintf(stdout, "empty\n");

    summary_proc("StringEmpty", errors);

    CommonPause();
    XtAppMainLoop( app_context );

}
