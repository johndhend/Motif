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
static char rcsid[] = "$XConsortium: FetchSV.c /main/9 1995/07/14 10:48:13 drk $"
#endif
#endif

#include <testlib.h>
#include <MrmTest.h> 

/* 
 * Data for summary
 */


#define NUM_TESTS		6
#define TEST_DESCRIP_LENGTH	64


/*
 * External declarations
 */

extern String		summary();


/*
 * Local declarations
 */

struct TestInfo FetchSetValueInfo[NUM_TESTS] = 
	{
	  {"Fetch undefined background color - Salmon                       ",
                                MrmNOT_FOUND,   0},
	  {"Fetch one valid value, shadow thickness for button2             ",
                                MrmSUCCESS,     0},
	  {"Fetch value from bad hierarchy, shadow thickness                ",
                                MrmBAD_HIERARCHY,       0},
	  {"Fetch two valid values, topshadow=blue, bottomshadow=black      ",
                                MrmSUCCESS,     0},
	  {"Fetch two values, one found, topshadow=white, bottomshadow=Coral",
                                MrmPARTIAL_SUCCESS,     0},
	  {"Fetch a value not valid for widget, selectColor for pushbutton  ",
                                MrmSUCCESS,     0},
 };



void main (argc,argv)
int argc;
char **argv;

{


      int		FSV_info_cnt = 0;
      Widget	test_box,
                buttons[3],
		badwidget1;

      Arg		args[4];
      int		nargs;

  
      String	        summary_msg;
      Pixel	        fg, bg;
      int		widgetwidth = 0;



      String      filename_vec[1];
      MrmCount    filename_num = 0;
      String      testname;

      char        uidname[80];
                

      MrmHierarchy        s_MrmHierarchy;
      MrmType             class;







      CommonTestUilInit (argc,argv);
      MrmInitialize();


/*
 *  Open the UID hierarchy
 */
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
 * Fetch valid test_box widget
 */
	test_box = NULL;
	MrmFetchWidget( s_MrmHierarchy,
			"test_box",
			Shell1,
			&test_box,
			&class);
/*
 * Fetch undefined background color - Salmon
 */
	nargs = 0;
	XtSetArg(args[nargs], XmNbackground, "Salmon"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						s_MrmHierarchy,
						buttons[0],
						args,
						nargs);
	FSV_info_cnt++;

/*
 * Fetch one valid value, shadow thickness for button2
 */
	buttons[0] = NULL;
	MrmFetchWidget(
				s_MrmHierarchy,
				"button2",
				test_box,
				&buttons[0],
				&class);
	nargs = 0;
	XtSetArg(args[nargs], XmNshadowThickness, "wideshadow"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						s_MrmHierarchy,
						buttons[0],
						args,
						nargs);
	FSV_info_cnt++;


	XtManageChild(test_box);
	XtManageChild(buttons[0]);
	XtRealizeWidget(Shell1);

/*
 * Fetch value from bad hierarchy, shadow thickness
 */
	nargs = 0;
	XtSetArg(args[nargs], XmNshadowThickness, "wideshadow"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						NULL,
						buttons[0],
						args,
						nargs);
	FSV_info_cnt++;

        CommonPause();

/*
 * Fetch second two button widgets
 */

/* 
 * Fetch two valid values, topshadow=blue, bottomshadow=black
 */
	buttons[1] = NULL;
        MrmFetchWidget(s_MrmHierarchy,
		       "button3",
			test_box,
			&buttons[1],
		        &class);
	nargs = 0;
	XtSetArg(args[nargs], XmNtopShadowColor, "blue"); nargs++;
	XtSetArg(args[nargs], XmNbottomShadowColor, "black"); nargs++;
	XtSetArg(args[nargs], XmNshadowThickness, "wideshadow"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						s_MrmHierarchy,
						buttons[1],
						args,
						nargs);
	FSV_info_cnt++;


/* 
 * Fetch two values, one found, topshadow=white, bottomshadow=Coral
 */
	buttons[2] = NULL;
	MrmFetchWidget( s_MrmHierarchy,
			"button4",
			test_box,
			&buttons[2],
			&class);
	nargs = 0;
	XtSetArg(args[nargs], XmNtopShadowColor, "white"); nargs++;
	XtSetArg(args[nargs], XmNbottomShadowColor, "Coral"); nargs++;
	XtSetArg(args[nargs], XmNshadowThickness, "wideshadow"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						s_MrmHierarchy,
						buttons[2],
						args,
						nargs);
	FSV_info_cnt++;

/* 
 * Fetch a value not valid for widget, selectColor for pushbutton
 */
	nargs = 0;
	XtSetArg(args[nargs], XmNselectColor, "white"); nargs++;
	FetchSetValueInfo[FSV_info_cnt].actual_return = MrmFetchSetValues(
						s_MrmHierarchy,
						buttons[2],
						args,
						nargs);
	FSV_info_cnt++;

/*
 * Manage button widgets
 */

	XtManageChildren(&buttons[1], 2);
	
        CommonPause();

/*
 * Replace the instruction message with test end message
 */

	summary_msg = summary(NUM_TESTS,
			      TEST_DESCRIP_LENGTH,
			      FetchSetValueInfo);

	fprintf (stdout, summary_msg);

        CommonPause();
}
