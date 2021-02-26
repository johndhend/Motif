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
static char rcsid[] = "$XConsortium: RegisterN.c /main/9 1995/07/14 10:52:48 drk $"
#endif
#endif

#include <MrmTest.h>

/*
 * Name of uid file
 */

String		filename_vec[] =
{
    "RegisterN.uid"
};

MrmCount	filename_num =
(sizeof(filename_vec) / sizeof(filename_vec[0]));

/*
 * Callback routines
 */

void		test1_1_proc(),
		test1_2_proc(),
		test2_1_proc(),
		test2_2_proc();

/*
 * Convenience routine
 */

void		error_proc();

/*
 * Names to register with MrmRegisterNames
 */

static MrmRegisterArg reglist_1[] = 
{
    "test1_proc",	(caddr_t) test1_1_proc,
    "test2_proc",	(caddr_t) test2_1_proc,
    "test3_var",	(caddr_t) 0,
    "test4_var",	(caddr_t) 4,
    "test5_var",	(caddr_t) 5,
};

static int reglist_1_num =
(sizeof(reglist_1) / sizeof(reglist_1[0]));

MrmRegisterArg	reglist_2[5];
int		reglist_2_num = 0;

/*
 * Local declarations
 */

MrmHierarchy	s_MrmHierarchy;
MrmType		class;
MrmCode		*type;

void	test1_1_proc(),
	test2_1_proc(),
	test1_2_proc(),
	test2_2_proc();

int	test3_var,
	test4_var,
	test5_var;

String	test6_var;

int	test1_1_called = 0,
	test2_1_called = 0,
	test1_2_called = 0,
	test2_2_called = 0;

int	test3_1_expect = 0,
	test4_1_expect = 4,
	test5_1_expect = 5,
	test3_2_expect = 999,
	test4_2_expect = 888,
	test5_2_expect = 777;

short	test3_1_return,
	test4_1_return,
	test5_1_return,
	test3_2_return,
	test4_2_return,
	test5_2_return;

int	errors = 0,
	total_errors = 0;

/*
 * Main routine
 */

main(argc, argv)
     int argc;
     char *argv[];
{
    Arg		args[10];
    int		nargs;

    Widget	toplevel = NULL,
    		widgetmain_1 = NULL,
		widgetmain_2 = NULL;

/*
 * Initialize Mrm
 */
    MrmInitialize();

/*
 *  Initialize the toolkit.
 */

    toplevel = XtInitialize("RegisterNames",	/* application name        */
			    "genericclass",	/* application class	   */
			    NULL, 0,		/* options		   */
			    &argc, argv);	/* command line parameters */

    nargs = 0;
    XtSetArg(args[nargs], XtNallowShellResize, TRUE); nargs++;
    XtSetValues(toplevel, args, nargs) ;

/*
 *  Open the Mrm hierarchy
 */

    if(MrmOpenHierarchy(filename_num,		/* number of files	*/
			filename_vec,		/* files		*/
			NULL,			/* os_ext_list (null)	*/
			&s_MrmHierarchy)	/* ptr to returned id	*/
       != MrmSUCCESS) 
    {
	error_proc("Can't open hierarchy\n");
    }

    fprintf(stdout,"Part 1:\n\n");

/*
 * Register the names of the callback routines and variables with Mrm
 */
    
    if(MrmRegisterNames(reglist_1,	/* list of names	*/
			reglist_1_num)	/* number of names	*/
       != MrmSUCCESS)
    {
	error_proc("Can't register names\n");
    }

/*
 * Fetch widget with callbacks test1_1_proc() and test2_1_proc()
 */
    
    if(MrmFetchWidget(s_MrmHierarchy,	/* id of uid hierarchy	   */
		      "S_MAIN_WIDGET_1",/* uil name of widget	   */
		      toplevel,		/* parent of widget	   */
		      &widgetmain_1,	/* ptr to widget id	   */
		      &class)		/* ptr to widget class	   */
       != MrmSUCCESS)
    {
	error_proc("Can't fetch main widget\n");
    }

/*
 * Call the callback routines for widgetmain_1
 */

    XtCallCallbacks(widgetmain_1, XmNactivateCallback, NULL);
    XtCallCallbacks(widgetmain_1, XmNarmCallback, NULL);
    
/*
 * See if test1_1_proc() and test2_1_proc() were called
 */

    if(!test1_1_called)
    {
	errors++;

	fprintf(stdout, "RegisterN: failed to properly register callback routine test1_1_proc.\n");
    }

    if(!test2_1_called)
    {
	errors++;
	
	fprintf(stdout, "RegisterN: failed to properly register callback routine test2_1_proc().\n");
    }

/*
 * Get the values associated with widgetmain_1 which were set using the
 * values of test[345]_var
 */

    nargs = 0;
    XtSetArg(args[nargs], XmNmarginBottom, &test3_1_return ); nargs++;
    XtSetArg(args[nargs], XmNmarginTop, &test4_1_return ); nargs++;
    XtSetArg(args[nargs], XmNmarginLeft, &test5_1_return ); nargs++;
    XtGetValues(widgetmain_1, args, nargs);
	
/*
 * See if the values were set correctly
 */

    if(test3_1_return != test3_1_expect)
    {
	errors++;
	
	fprintf(stdout,"RegisterN: failed to properly register literal test3_1_var.\n");
    }
    
    if(test4_1_return != test4_1_expect)
    {
	errors++;
	    
	fprintf(stdout,"RegisterN: failed to properly register literal test4_1_var.\n");
    }

    if(test5_1_return != test5_1_expect)
    {
	errors++;
	
	fprintf(stdout,"RegisterN: failed to properly register literal test5_1_var.\n");
    }

/*
 * Print total number of errors for part 1 of this test
 */

    if(errors)
    {
	total_errors += errors;

	fprintf(stdout, "\nPart 1 of the RegisterN test failed with %d errors\n\n",
		errors);
    }

/*
 * Part 2: change the values of the variables test[3456]_var
 */

    fprintf(stdout,"Part 2:\n\n");

/*
 * Set the arguments to be sent
 */

    reglist_2[reglist_2_num].name = "test1_proc";
    reglist_2[reglist_2_num].value = (XtPointer) test1_2_proc; reglist_2_num++;

    reglist_2[reglist_2_num].name = "test2_proc";
    reglist_2[reglist_2_num].value = (XtPointer) test2_2_proc; reglist_2_num++;

    reglist_2[reglist_2_num].name = "test3_var";
    reglist_2[reglist_2_num].value = (XtPointer)(long) test3_2_expect;
							       reglist_2_num++;

    reglist_2[reglist_2_num].name = "test4_var";
    reglist_2[reglist_2_num].value = (XtPointer)(long) test4_2_expect;
							       reglist_2_num++;

    reglist_2[reglist_2_num].name = "test5_var";
    reglist_2[reglist_2_num].value = (XtPointer)(long) test5_2_expect;
							       reglist_2_num++;

/*
 * Register the names of the callback routines and variables with Mrm
 */

    if(MrmRegisterNames(reglist_2,	/* list of names	*/
			reglist_2_num)	/* number of names	*/
       != MrmSUCCESS)
    {
	error_proc("Can't register names\n");
    }

/*
 * Fetch widget with callbacks test1_2_proc() and test2_2_proc()
 */
    
    if(MrmFetchWidget(s_MrmHierarchy,	/* id of uid hierarchy	   */
		      "S_MAIN_WIDGET_2",/* uil name of widget	   */
		      toplevel,		/* parent of widget	   */
		      &widgetmain_2,	/* ptr to widget id	   */
		      &class)		/* ptr to widget class	   */
       != MrmSUCCESS)
    {
	error_proc("Can't fetch main widget\n");
    }

/*
 * Call the callback routines for widgetmain_2
 */

    XtCallCallbacks(widgetmain_2, XmNactivateCallback, NULL);
    XtCallCallbacks(widgetmain_2, XmNarmCallback, NULL);
    
/*
 * See if test1_2_proc() and test2_2_proc() were called
 */

    errors = 0;

    if(!test1_2_called)
    {
	errors++;

	fprintf(stdout, "RegisterN: failed to properly register callback routine test1_2_proc.\n");
    }

    if(!test2_2_called)
    {
	errors++;
	
	fprintf(stdout, "RegisterN: failed to properly register callback routine test2_2_proc().\n");
    }

/*
 * Get the values associated with widgetmain_2 which were set using the
 * values of test[345]_var
 */

    nargs = 0;
    XtSetArg(args[nargs], XmNmarginBottom, &test3_2_return ); nargs++;
    XtSetArg(args[nargs], XmNmarginTop, &test4_2_return ); nargs++;
    XtSetArg(args[nargs], XmNmarginLeft, &test5_2_return ); nargs++;
    XtGetValues(widgetmain_2, args, nargs);
	
/*
 * See if the values were set correctly
 */

    if(test3_2_return != test3_2_expect)
    {
	errors++;
	
	fprintf(stdout,"RegisterN: failed to properly register literal test3_2_var.\n");
    }
    
    if(test4_2_return != test4_2_expect)
    {
	errors++;
	    
	fprintf(stdout,"RegisterN: failed to properly register literal test4_2_var.\n");
    }

    if(test5_2_return != test5_2_expect)
    {
	errors++;
	
	fprintf(stdout,"RegisterN: failed to properly register literal test5_2_var.\n");
    }
    
/*
 * Print total number of errors for part 2 of this test
 */

    if(errors)
    {
	total_errors += errors;

	fprintf(stdout, "\nPart 2 of the RegisterN test failed with %d errors\n\n", errors);
    }

    if(total_errors)
    {
	fprintf(stdout, "RegisterN: test failed.\n");
    }
    else
    {
	fprintf(stdout, "RegisterN: all tests passed.\n");
    }
}

/*
 * Callback routines
 */

void test1_1_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{ 	
    test1_1_called++;
}

void test2_1_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{ 	
    test2_1_called++;
}

void test1_2_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{ 	
    test1_2_called++;
}

void test2_2_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{ 	
    test2_2_called++;
}

/*
 * Error handling
 */

void error_proc(error_string)
     String	error_string;
{
    fprintf(stdout,"Mrm error: %s\n", error_string);
    fflush(stdout);
}

