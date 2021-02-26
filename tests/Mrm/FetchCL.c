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
static char rcsid[] = "$XConsortium: FetchCL.c /main/9 1995/07/14 10:46:51 drk $"
#endif
#endif

#include <testlib.h>
#include <MrmTest.h>

/*
 * Data for summary
 */

#define NUM_TESTS		7
#define TEST_DESCRIP_LENGTH	38


struct TestInfo FetchColorLiteralInfo[NUM_TESTS] = 
{
    {"Fetch non-exported color              ", MrmNOT_FOUND,	0},
    {"Fetch nonexistent color               ", MrmNOT_FOUND,	0},
    {"Fetch color from nonexistent hierarchy", MrmBAD_HIERARCHY,0},
    {"Fetch valid color                     ", MrmSUCCESS,	0},
    {"Fetch valid color                     ", MrmSUCCESS,	0},
    {"Fetch valid color                     ", MrmSUCCESS,	0},
    {"Fetch valid color                     ", MrmSUCCESS,	0},
};




/*
 * External declarations
 */

extern String		summary();


void main (argc, argv)
int argc;
char **argv;
{ 	


    Arg		args[2];
    int		nargs;

    Pixel	blue,
		white,
    		red,
    		yellow,
    		bad_color;


    String	summary_msg;

    int		i;

    Colormap	cmap;

    Widget	button1 = NULL,
		button2 = NULL,
		test_box = NULL;


    String testname;

    String	filename_vec[1];
    MrmCount	filename_num = 0;

    char	uidname[80];
    		

    MrmHierarchy	s_MrmHierarchy;
    MrmType	        class;





    CommonTestUilInit (argc,argv);

    MrmInitialize();


   /* tell the user what test it is. */

    

    testname = argv[0];
    sprintf(uidname, "%s.uid", testname);
    filename_vec[filename_num] = uidname; filename_num++;

    if(MrmOpenHierarchy(filename_num,		/* number of files	*/
			filename_vec,		/* files		*/
			NULL,			/* os_ext_list (null)	*/
			&s_MrmHierarchy)	/* ptr to returned id	*/
       != MrmSUCCESS) 
    {
	printf("Can't open hierarchy\n");
    }

    
    CommonPause();



/*
 * Get display, colormap
 */

		
	cmap = DefaultColormap(display, DefaultScreen(display));

/*
 * Try to fetch a color which is not exported
 */

	FetchColorLiteralInfo[0].actual_return = 
	MrmFetchColorLiteral(s_MrmHierarchy,
			    "bad_color1",
			     display,
			     cmap,
			     &bad_color);
	
/*
 * Try to fetch a color which is nonexistent
 */

	FetchColorLiteralInfo[1].actual_return = 
	MrmFetchColorLiteral(s_MrmHierarchy,
			    "bad_color2",
			     display,
			     cmap,
			     &bad_color);
	
/*
 * Try to fetch a color from a NULL hierarchy
 */

	FetchColorLiteralInfo[2].actual_return = 
	MrmFetchColorLiteral(NULL,
			    "red",
			     display,
			     cmap,
			     &bad_color);

/*
 * Fetch test_box widget
 */




    if(MrmFetchWidget         (s_MrmHierarchy,	/* id of uid hierarchy	   */
			      "test_box",	/* uil name of widget	   */
			      Shell1,		/* parent of widget	   */
			      &test_box,	/* ptr to widget id	   */
			      &class)		/* ptr to widget class	   */
       != MrmSUCCESS)
      {
	printf ("Can't fetch test_box widget!\n");
      }


/*
 * Get ID's of button widgets
 */

	button1 = XtNameToWidget(test_box, "button1");
	button2 = XtNameToWidget(test_box, "button2");

/*
 * Fetch the colors for the buttons for valid test 1
 */

	FetchColorLiteralInfo[3].actual_return =
	MrmFetchColorLiteral(s_MrmHierarchy,
			     "red",
			     display,
			     cmap,
			     &red);
	
	FetchColorLiteralInfo[4].actual_return =
	MrmFetchColorLiteral(s_MrmHierarchy,
			     "yellow",
			     display,
			     cmap,
			     &yellow);

/*
 * Set background and foreground colors for button widgets
 */

	nargs = 0;
	XtSetArg(args[nargs], XmNbackground, red); nargs++;
	XtSetArg(args[nargs], XmNforeground, yellow); nargs++;
	XtSetValues(button1, args, nargs);
	XtSetValues(button2, args, nargs);

/*
 * Manage test_box widget
 */

	XtManageChild(test_box);

/*
 * Realize top level shell widget
 */

	XtRealizeWidget(Shell1);

CommonPause();


/*
 * Fetch the colors for the buttons for valid test 1
 */

	FetchColorLiteralInfo[5].actual_return =
	MrmFetchColorLiteral(s_MrmHierarchy,
			     "blue",
			     display,
			     cmap,
			     &blue);
	
	FetchColorLiteralInfo[6].actual_return =
	MrmFetchColorLiteral(s_MrmHierarchy,
			     "white",
			     display,
			     cmap,
			     &white);

/*
 * Set background and foreground colors for button widgets
 */

	nargs = 0;

	XtSetArg(args[nargs], XmNbackground, blue ); nargs++;
	XtSetArg(args[nargs], XmNforeground, white ); nargs++;
	XtSetValues(button1, args, nargs);
	XtSetValues(button2, args, nargs);
	
CommonPause();

/*
 * Replace the instruction message with test end message
 */

	summary_msg = summary(NUM_TESTS,
			      TEST_DESCRIP_LENGTH,
			      FetchColorLiteralInfo);

	fprintf (stdout, summary_msg);


CommonPause();
}







