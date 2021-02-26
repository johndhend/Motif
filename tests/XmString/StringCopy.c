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
static char rcsid[] = "$XConsortium: StringCopy.c /main/7 1995/07/13 19:54:14 drk $"
#endif
#endif

#include <stdio.h>

#include <testlib.h>

#include "String.h"


#define	NUM_TESTS 3

extern void	error_proc();

char	*description_string[NUM_TESTS] =
{
    "Create a compound string, make a copy if it, and\n\
     compare the two strings with XmStringByteCompare",
    "Create a compound string, make a copy if it, and\n\
     compare the two strings with XmStringCompare    ",
    "Copy a NULL string to a non-NULL string         "
};

main(argc, argv)
int argc;
char		*argv[];
{

    string_num = text_num = charset_num = test_num = 0;
    errors = 0;

    CommonTestInit(argc, argv);

/*
                                                       Copy     Compare
Test Description                                       Result   Result    Error
---- -----------                                       -------  --------- -----
*/

    fprintf(stdout, "Test Description                                       ");
    fprintf(stdout, "Result   Result    Error\n");
    fprintf(stdout, "---- -----------                                       ");
    fprintf(stdout, "-------  --------- -----\n");

/*
 * Test 1: Create a compound string, make a copy of it, and
 *         compare the two strings with XmStringByteCompare
 */

    if ((string[string_num] = XmStringCreateLtoR(text[text_num],
												 charset[charset_num])) 
												 == NULL) {
		sprintf(error_string, "Can't create string%d", string_num);
		error_proc(error_string);
    }

    string_num++;
    
    if ((string[string_num] = XmStringCopy(string[string_num-1])) == NULL) {
		sprintf(error_string, "Can't copy string%d to string%d", string_num-1,
				string_num);
		error_proc(error_string);
    }

    fprintf(stdout, "  %d  %s  success  ", test_num+1, 
			description_string[test_num]);
	
    if (!XmStringByteCompare(string[string_num - 1], string[string_num])) {
		errors++;
		fprintf(stdout, "different    *\n");
    }
    else
		fprintf(stdout, "identical\n");

    string_num++;
    text_num++;
    charset_num = charset_num+2;
    test_num++;
    
/*
 * Test 2: Create a compound string, make a copy of it, and
 *         compare the two strings with XmStringCompare
 */

    if ((string[string_num] = XmStringCreate(text[text_num],
					    					 charset[charset_num])) 
											 == NULL) {
		sprintf(error_string, "Can't create string%d", string_num);
		error_proc(error_string);
    }

    string_num++;
    
    if ((string[string_num] = XmStringCopy(string[string_num-1])) == NULL) {
		sprintf(error_string, "Can't copy string%d to string%d", string_num-1,
				string_num);
		error_proc(error_string);
    }
	
    fprintf(stdout, "\n  %d  %s  success  ", test_num+1,
	    	description_string[test_num]);
	
    if (!XmStringCompare(string[string_num - 1], string[string_num])) {
		errors++;
		fprintf(stdout, "mismatch     *\n");
    }
    else
		fprintf(stdout, "match\n");

    test_num++;
    
/*
 * Test 3: Copy a NULL string to a valid string
 */

    fprintf(stdout, "\n  %d  %s  ", test_num+1,
	    	description_string[test_num]);
	
    if ((string[string_num] = XmStringCopy(NULL)) != NULL) {
		errors++;
		fprintf(stdout, "nonNULL      *\n");
    }
    else
		fprintf(stdout, "NULL\n");
	
    summary_proc("StringCopy", errors);

    CommonPause();
    XtAppMainLoop( app_context );

}
