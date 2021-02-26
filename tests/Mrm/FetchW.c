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
static char rcsid[] = "$XConsortium: FetchW.c /main/9 1995/07/14 10:48:34 drk $"
#endif
#endif

#include <MrmTest.h>
#include <testlib.h>

/*
 * Data for summary
 */

#define NUM_TESTS		5
#define TEST_DESCRIP_LENGTH	41



/*
 * External declarations
 */




extern String		summary();

/*
 * Local declarations
 */

struct TestInfo FetchWidgetInfo[NUM_TESTS] = 
{
    {"Fetch valid widget                       ", MrmSUCCESS,	0},
    {"Fetch nonexistent widget                 ", MrmNOT_FOUND,	0},
    {"Fetch previously fetched widget          ", MrmSUCCESS,	0},
    {"Fetch valid widget                       ", MrmSUCCESS,	0},
    {"Fetch valid widget                       ", MrmSUCCESS,	0},
};




void main(argc,argv)
       int argc;
       char **argv;

{ 	


MrmHierarchy	s_MrmHierarchy;
MrmType		class;

Widget		test_top = NULL,
		test_box = NULL,
		button1 = NULL,
		button2 = NULL,
		badwidget1 = NULL,
		badwidget2 = NULL;

String      filename_vec[1];
char        uidname[80];
String      testname;

Arg	    args[2];
int	    nargs;

String	    summary_msg;


MrmCount    filename_num=0;







   MrmInitialize();
   CommonTestUilInit (argc,argv);


   testname = argv[0];
   sprintf(uidname, "%s.uid", testname);
   filename_vec[filename_num] = uidname; filename_num++;

    if(MrmOpenHierarchy(filename_num,           /* number of files      */
                        filename_vec,           /* files                */
                        NULL,                   /* os_ext_list (null)   */
                        &s_MrmHierarchy)        /* ptr to returned id   */
       != MrmSUCCESS) 
    {
        printf("Can't open hierarchy\n");

      }

CommonPause();

/*
 * Fetch vaild test_box widget
 */
	FetchWidgetInfo[0].actual_return = MrmFetchWidget(s_MrmHierarchy,
							  "test_box",
							  Shell1,
							  &test_box,
							  &class);

/*
 * Manage button widgets
 */

	XtManageChild(test_box);
    
/*
 * Realize top level shell widget
 */

	XtRealizeWidget(Shell1);

   CommonPause();			       
/*
 * Try to fetch a nonexistent widget
 */

	FetchWidgetInfo[1].actual_return = MrmFetchWidget(s_MrmHierarchy,
							  "badwidget1",
							  Shell1,
							  &badwidget1,
							  &class);



/*
 * Fetch second two button widgets
 */

	FetchWidgetInfo[3].actual_return = MrmFetchWidget(s_MrmHierarchy,
							  "button3",
							  test_box,
							  &button1,
							  &class);

	FetchWidgetInfo[4].actual_return = MrmFetchWidget(s_MrmHierarchy,
							  "button4",
							  test_box,
							  &button2,
							  &class);
/*
 * Try to fetch a widget which has already been fetched
 */

	badwidget1 = NULL;
	badwidget1 = XtNameToWidget(test_box, "button1");
	
	FetchWidgetInfo[2].actual_return = MrmFetchWidget(s_MrmHierarchy,
							  "button1",
							  Shell1,
							  &badwidget1,
							  &class);

/*
 * Manage button widgets
 */

	XtManageChild(button1);
	XtManageChild(button2);
	
  CommonPause();

/*
 * Replace the instruction message with test end message
 */

	summary_msg = summary(NUM_TESTS,
			      TEST_DESCRIP_LENGTH,
			      FetchWidgetInfo);

	fprintf (stdout, summary_msg);

	CommonPause();
}
