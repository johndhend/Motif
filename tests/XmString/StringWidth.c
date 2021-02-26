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
static char rcsid[] = "$XConsortium: StringWidth.c /main/7 1995/07/13 19:56:55 drk $"
#endif
#endif
#include        <stdio.h>
#include        <testlib.h>
 
char *test_strings[] = {"", "", "a", "a", "aaaaaa" };
Dimension expected[] = {0, 0, 9, 54, 54, 0, 0 };

#define XmSTRING_DIRECTION_REVERT 2
#define NUM_TESTS 7 

void
main( int argc, char **argv )
{
    XmString	cs, cs1, cs2, cs3, temp;
    XmFontList	fl;
    XFontStruct *font;
    register	i;
    Dimension received[NUM_TESTS];
    int test_num = 0;
 
    CommonTestInit (argc, argv);

    fl = CommonGetFontList
	      ("-adobe-courier-medium-r-normal--14-140-75-75-m-90-iso8859-1");

/*  Test 1 */ 
    cs = XmStringCreate ( test_strings[test_num], XmSTRING_DEFAULT_CHARSET );
    received[test_num++] = XmStringWidth(fl , cs );

/*  Test 2 */ 
    cs1 = XmStringCreate ( test_strings[test_num], XmSTRING_DEFAULT_CHARSET );
    for (i = 0; i < 5; i++) {
        temp = cs1;
	cs1 = XmStringConcat( cs, temp);
        XmStringFree( temp );
    }
    received[test_num++] = XmStringWidth(fl , cs1 );
    XmStringFree( cs );
    XmStringFree( cs1 );

/*  Test 3 */
    cs = XmStringSegmentCreate ( test_strings[test_num], 
		XmSTRING_DEFAULT_CHARSET,
                XmSTRING_DIRECTION_L_TO_R,
                FALSE);
    received[test_num++] = XmStringWidth(fl , cs );

/*  Test 4 */ 
    cs1 = XmStringSegmentCreate ( test_strings[test_num], 
                XmSTRING_DEFAULT_CHARSET,
                XmSTRING_DIRECTION_L_TO_R,
                FALSE);
    for (i = 0; i < 5; i++) {
        temp = cs1;
	cs1 = XmStringConcat( cs, temp);
        XmStringFree( temp );
    }
    received[test_num++] = XmStringWidth(fl , cs1 );
    XmStringFree( cs );
    XmStringFree( cs1 );

/*  Test 5 */
    cs = XmStringCreate ( test_strings[test_num], XmSTRING_DEFAULT_CHARSET );
    received[test_num++] = XmStringWidth(fl , cs );
    XmStringFree( cs );

/*  Test 6 */
    cs1 = XmStringDirectionCreate( XmSTRING_DIRECTION_L_TO_R );
    received[test_num++] = XmStringWidth(fl , cs1 );
    XmStringFree( cs1 );

/*  Test 7 */ 
    cs2 = XmStringDirectionCreate( XmSTRING_DIRECTION_REVERT );
    received[test_num++] = XmStringWidth(fl , cs2 );
    XmStringFree( cs2 );

    printf ("Summary of test results\n");
    printf ("Test #\tExpected\tReceived\tStatus\n\n");
    for (i = 0; i < test_num; i++) {
      printf ("%6d\t%8d\t%8d\t%s\n",     i + 1,
	                              (int) expected[i],
	                              (int) received[i],
	                              ((expected[i] == received[i]) 
				                   ? "PASSED\n" : "FAILED\n"));
    }

    fflush (stdout);

    CommonPause();
    XtAppMainLoop( app_context );
}

