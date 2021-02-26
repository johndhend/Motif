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
static char rcsid[] = "$XConsortium: RegisterCA.c /main/8 1995/07/14 10:52:28 drk $"
#endif
#endif

#include <MrmTest.h>

#include "ABrowse.h"

/*
 * Callbacks for ABrowse widget
 */

void		abrowse_help_proc();
void		abrowse_quit_proc();

/*
 * Convenience routine
 */

extern void	nyi_proc();

/*
 * Names to register with MrmRegisterNames
 */

static MrmRegisterArg reglist[] = 
{
    "abrowse_help_proc",	(caddr_t) abrowse_help_proc,
    "abrowse_quit_proc",	(caddr_t) abrowse_quit_proc,
};

static int reglist_num =
(sizeof(reglist) / sizeof(reglist[0]));

/*
 * Data for summary
 */

#define NUM_TESTS		2
#define TEST_DESCRIP_LENGTH	49

struct TestInfo RegisterClassInfo[NUM_TESTS] = 
{
    {"Register valid Athena widget class               ", MrmSUCCESS, NULL},
    {"Fetch user-defined Athena widget (of valid class)", MrmSUCCESS, NULL},
};

/*
 * External declarations
 */

extern MrmHierarchy	s_MrmHierarchy;
extern MrmType		class;

extern Widget		toplevel,
			widgetmain;

extern String		summary();

/*
 * Local declarations
 */

#define VALID_TEST1	1
#define FINISH		2

int		iteration = 1;

Widget		test_top = NULL,
		abrowse = NULL;

Display		*dsp;
Screen		*screen;
Colormap	cmap;

Pixmap		images[5];
int		num_images = 5;

    
Pixel		image_background,
		image_foreground;

void continue_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{ 	

    String	msg_valid_tst1 = "There should now be a Athena ABrowse widget in the second\nwindow.  This widget consists of four command widgets and\na label widget displaying an image.  There are five such\nimages, and they can be seen by using the Next and Prev\nbuttons.  Note that pressing Next while viewing the last\nimage will have no effect.  This is also true for pressing\nPrev while viewing the first image.\n\nPress the continue button to continue the test.";

    Arg		args[2];
    int		nargs;

    XmString	message;

    String	summary_msg;

    if(iteration == VALID_TEST1)
    {
	iteration++;

/*
 * Create top level shell widget as parent for test_box widget
 */

	nargs = 0;
	XtSetArg(args[nargs], XtNallowShellResize, TRUE); nargs++;

	test_top = XtAppCreateShell("test_top",
				    "TEST_TOP",
				    topLevelShellWidgetClass,
				    XtDisplay(widgetmain),
				    args, nargs);

/*
 * Register valid ABrowse widget class
 */
	RegisterClassInfo[0].actual_return =
	MrmRegisterClass(URMwcUnknown,
			 "ABrowse",
			 "XtCreateABrowse",
			 XtCreateABrowse,
			 abrowseWidgetClass);

/*
 * Register the names of the ABrowse widget callback routines with Mrm
 */
    
	if(MrmRegisterNames(reglist,		/* list of names	*/
			    reglist_num)	/* number of names	*/
	   != MrmSUCCESS)
	{
	    error_proc("Can't register Browse/ABrowse widget callbacks\n");
	}
    
/*
 * Get display, screen, colormap
 */

	dsp = XtDisplay(toplevel);
	
	screen = DefaultScreenOfDisplay(dsp);

	cmap = DefaultColormap(dsp, DefaultScreen(dsp));

/*
 * Fetch background and foreground colors for images
 */

	if(MrmFetchColorLiteral(s_MrmHierarchy,
				"yellow",
				dsp,
				cmap,
				&image_foreground) != MrmSUCCESS)
	{
	    error_proc("can't fetch the color yellow");
	}
    
	if(MrmFetchColorLiteral(s_MrmHierarchy,
				"red",
				dsp,
				cmap,
				&image_background) != MrmSUCCESS)
	{
	    error_proc("can't fetch the color red");
	}
    
/*
 * Fetch images (pixmaps)
 */
	
	if(MrmFetchIconLiteral(s_MrmHierarchy,
			       "blank_icon",
			       screen,
			       dsp,
			       image_foreground,
			       image_background,
			       &images[0]) != MrmSUCCESS)
	{
	    error_proc("can't fetch blank_icon");
	}
    
	if(MrmFetchIconLiteral(s_MrmHierarchy,
			       "test1_btn1_icon",
			       screen,
			       dsp,
			       image_foreground,
			       image_background,
			       &images[1]) != MrmSUCCESS)
	{
	    error_proc("can't fetch test1_btn1_icon");
	}
	
	if(MrmFetchIconLiteral(s_MrmHierarchy,
			       "test1_btn2_icon",
			       screen,
			       dsp,
			       image_foreground,
			       image_background,
			       &images[2]) != MrmSUCCESS)
	{
	    error_proc("can't fetch test1_btn2_icon");
	}
	
	if(MrmFetchIconLiteral(s_MrmHierarchy,
			       "test2_btn1_icon",
			       screen,
			       dsp,
			       image_foreground,
			       image_background,
			       &images[3]) != MrmSUCCESS)
	{
	    error_proc("can't fetch test2_btn1_icon");
	}
	
	if(MrmFetchIconLiteral(s_MrmHierarchy,
			       "test2_btn2_icon",
			       screen,
			       dsp,
			       image_foreground,
			       image_background,
			       &images[4]) != MrmSUCCESS)
	{
	    error_proc("can't fetch test2_btn2_icon");
	}
	
/*
 * Try to fetch ABrowse widget
 */

	RegisterClassInfo[1].actual_return = MrmFetchWidget(s_MrmHierarchy,
							    "abrowse",
							    test_top,
							    &abrowse,
							    &class);

/*
 * Pass images to widget
 */

	nargs = 0;
	XtSetArg(args[nargs], XtNimages, images); nargs++;
	XtSetArg(args[nargs], XtNnumImages, num_images); nargs++;
	XtSetValues(abrowse, args, nargs);

/*
 * Manage ABrowse widget
 */

	XtManageChild(abrowse);
    
/*
 * Realize top level shell widget
 */

	XtRealizeWidget(test_top);

/*
 * Replace the instruction message with "valid test 1" message
 */

	message = XmStringCreateLtoR(msg_valid_tst1, XmSTRING_DEFAULT_CHARSET);
	
	nargs = 0;
	XtSetArg(args[nargs], XmNmessageString, message); nargs++;
	XtSetValues(widgetmain, args, nargs);
    }
    else if(iteration == FINISH)
    {
	iteration++;

	summary_msg = summary(NUM_TESTS,
			      TEST_DESCRIP_LENGTH,
			      RegisterClassInfo);
    
	message = XmStringCreateLtoR(summary_msg, XmSTRING_DEFAULT_CHARSET);
	
	nargs = 0;
	XtSetArg(args[nargs], XmNmessageString, message); nargs++;
	XtSetValues(widgetmain, args, nargs);
    }
}

/*
 * ABrowse Help procedure
 */

void abrowse_help_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{
    nyi_proc(w, "ABrowse Help", NULL);
}

/*
 * ABrowse Exit procedure
 */

void abrowse_quit_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{
    nyi_proc(w, "ABrowse Quit", NULL);
}
