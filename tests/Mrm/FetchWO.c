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
static char rcsid[] = "$XConsortium: FetchWO.c /main/9 1995/07/14 10:49:00 drk $"
#endif
#endif

#include <MrmTest.h> 
#include <testlib.h>

/* 
 * Data for summary
 */

#include <Xm/XmP.h>			/* needed to get definition of XtName() */

#define NUM_TESTS		8
#define TEST_DESCRIP_LENGTH	60
#define	TEST_WIDTH		200

/*
 * External declarations.
 */

extern String		summary();


/*
 * Local declarations.
 */

struct TestInfo FetchWidgetOverrideInfo[NUM_TESTS] = 
{
    {"Fetch valid parent widget, override width                 ",
				MrmSUCCESS,	0},
    {"Fetch valid widget, override pixmap                       ",
				MrmSUCCESS,	0},
    {"Check override of parent widget width inherited by child  ",
				False,	0},
    {"Fetch nonexistent widget, override name, pixmap           ",
				MrmNOT_FOUND,	0},
    {"Fetch previously fetched widget, override pixmap          ",
				MrmSUCCESS,	0},
    {"Fetch valid widget, override name but no args             ",
				MrmSUCCESS,	0},
	{"Check override of name on valid widget fetch              ",
				True,	0},
    {"Fetch widget, override shadow thickness not set already   ",
				MrmSUCCESS,	0},
};




void main(argc,argv)
     int argc;
     char **argv;
{ 	
/*
 * External declarations
 */

  MrmHierarchy	s_MrmHierarchy;
  MrmType	class;

  Widget	test_box,
                buttons[4],
		badwidget1,
		badwidget2;

  Arg		args[2];
  int		nargs;

  String        filename_vec[1];
  char          uidname[80];
  String        testname;


  String	summary_msg;
  Pixel	        fg, bg;
  Pixmap	button_icon[2];
  int		widgetwidth = 0;


  int		FWO_info_cnt = 0;

  MrmCount      filename_num = 0;




    MrmInitialize();
    CommonTestUilInit (argc,argv);

    testname=argv[0];

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
 * Fetch valid test_box widget, set the width to see if the children
 * inherit it later on.
 * Fetch valid parent widget, override width
 */
	nargs = 0;
	XtSetArg(args[nargs], XmNwidth, TEST_WIDTH); nargs++;

	test_box = NULL;
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"test_box",
						Shell1,
						NULL,
						args,
						nargs,
						&test_box,
						&class);
	FWO_info_cnt++;

	XtManageChild(test_box);

/*
 * Fetch the button widgets, and override the pixmaps - good conditions,
 * should be no errors
 * Fetch valid widget, override pixmap
 */
	/* get some default for the bg and fg */
	nargs = 0;
    XtSetArg(args[nargs], XmNforeground, &fg); nargs++;
    XtSetArg(args[nargs], XmNbackground, &bg); nargs++;
    XtGetValues(Shell1, args, nargs);

	/* get the right pixmap for button2 */
    MrmFetchIconLiteral(s_MrmHierarchy,
                        "test1_btn2_icon",
                        XtScreen(Shell1),
						XtDisplay(Shell1),
                        fg, bg,
                        &button_icon[1]);

    nargs = 0;
    XtSetArg(args[nargs], XmNlabelPixmap, button_icon[1]); nargs++;

	buttons[1] = NULL;
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"button2",
						test_box,
						NULL,
						args,
						nargs,
						&buttons[1],
						&class);
	FWO_info_cnt++;

	nargs = 0;
	XtSetArg(args[nargs], XmNwidth, &widgetwidth); nargs++;
	XtGetValues(buttons[1], args, nargs);

/*
 * Check override of parent widget width inherited by child
 */
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		(widgetwidth == TEST_WIDTH);
	FWO_info_cnt++;


	XtManageChildren(&buttons[1], 1);
	XtRealizeWidget(Shell1);

    CommonPause();
			       
/*
 * Fetch nonexistent widget, override name, pixmap
 */
    nargs = 0;
    XtSetArg(args[nargs], XmNlabelPixmap, button_icon[1]); nargs++;

	badwidget1 = NULL;
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"badwidget1",
						Shell1,
						"BAD_WIDGET",
						args,
						nargs,
						&badwidget1,
						&class);
	FWO_info_cnt++;
	
/*
 * Try to fetch a widget which has already been fetched, and override
 * it's pixmap
 * Fetch previously fetched widget, override pixmap
 */
	badwidget1 = NULL;
	badwidget1 = XtNameToWidget(test_box, "button1");
	
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"button1",
						test_box,
						NULL,
						args, 
						nargs,
						&badwidget1,
						&class);
	FWO_info_cnt++;


/*
 * Fetch second two button widgets
 */

/*
 * Override the name and then check to see if it actually worked.
 * Fetch valid widget, override name but no args
 */
	buttons[2] = NULL;
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"button3",
						test_box,
						"button3new",
						NULL,
						0,
						&buttons[2],
						&class);
	FWO_info_cnt++;

/*
 * Check override of name on valid widget fetch
 */
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		!strcmp("button3new", XtName(buttons[2]));
	FWO_info_cnt++;

/*
 * Override the shadow thickness which is a value that was not previously set.
 * Fetch widget, override shadow thickness not set already
 */
	nargs = 0;
        XtSetArg(args[nargs], XmNshadowThickness, 6); nargs++;
	buttons[3] = NULL;
	FetchWidgetOverrideInfo[FWO_info_cnt].actual_return =
		MrmFetchWidgetOverride(
						s_MrmHierarchy,
						"button4",
						test_box,
						NULL,
						args,
						nargs,
						&buttons[3],
						&class);
	FWO_info_cnt++;


	XtManageChildren(&buttons[2], 2);

        CommonPause();
	
        /*
	 * Generate summary message.
	 */

	summary_msg = summary(NUM_TESTS,
			      TEST_DESCRIP_LENGTH,
			      FetchWidgetOverrideInfo);

	fprintf (stdout, summary_msg);

        CommonPause();

    
}
