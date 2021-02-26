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
static char rcsid[] = "$XConsortium: main.c /main/8 1995/07/14 10:53:35 drk $"
#endif
#endif

#include <MrmTest.h>

/*
 * Callback routines
 */

extern void	continue_proc();
extern void	exit_proc();
extern void	help_proc();
extern void	nyi_proc();

/*
 * Convenience routines
 */

extern void	error_proc();

/*
 * Names to register with MrmRegisterNames
 */

static MrmRegisterArg reglist[] = 
{
    "continue_proc",	(caddr_t) continue_proc,
    "exit_proc",	(caddr_t) exit_proc,
    "help_proc",	(caddr_t) help_proc,
    "nyi_proc",		(caddr_t) help_proc,
};

static int reglist_num =
(sizeof(reglist) / sizeof(reglist[0]));

/*
 * Local declarations
 */

MrmHierarchy	s_MrmHierarchy;
MrmType		class;

Widget		toplevel = NULL,
		widgetmain = NULL;

String		testname;

/*
 * Main routine
 */

main(argc, argv)
     int argc;
     char *argv[];
{
    Arg		args[10];
    int		nargs;

    XmString	message;
    
    String	filename_vec[1];
    MrmCount	filename_num = 0;

    char	message_begin[120],
    		uidname[80];

/*
 * Initialize Mrm
 */
    MrmInitialize();

/*
 *  Initialize the toolkit.
 */

    testname = argv[0];

    toplevel = XtInitialize(testname,		/* application name	   */
			    "genericclass",	/* application class	   */
			    NULL, 0,		/* options		   */
			    &argc, argv);	/* command line parameters */

    nargs = 0;
    XtSetArg(args[nargs], XmNallowShellResize, TRUE); nargs++;
    XtSetValues(toplevel, args, nargs) ;

/*
 *  Open the UID hierarchy
 */

    sprintf(uidname, "%s.uid", testname);
    filename_vec[filename_num] = uidname; filename_num++;

    if(MrmOpenHierarchy(filename_num,		/* number of files	*/
			filename_vec,		/* files		*/
			NULL,			/* os_ext_list (null)	*/
			&s_MrmHierarchy)	/* ptr to returned id	*/
       != MrmSUCCESS) 
    {
	error_proc("Can't open hierarchy\n");
    }

/*
 * Register the names of the callback routines with Mrm
 */
    
    if(MrmRegisterNames(reglist,	/* list of names	*/
			reglist_num)	/* number of names	*/
       != MrmSUCCESS)
    {
	error_proc("Can't register names\n");
    }
    
/*
 *  Fetch and create the topmost widget and any children.  For these tests,
 * this will always be an XmMessageBox widget.
 */

/*
 * String to be displayed.
 */

    sprintf(message_begin, "This is the %s test.\nPress the continue button to start the test.", argv[0]);

    message = XmStringCreateLtoR(message_begin, XmSTRING_DEFAULT_CHARSET);
    
    nargs = 0;
    XtSetArg(args[nargs], XmNmessageString, message); nargs++;

    if(MrmFetchWidgetOverride(s_MrmHierarchy,	/* id of uid hierarchy	   */
			      "S_MAIN_WIDGET",	/* uil name of widget	   */
			      toplevel,		/* parent of widget	   */
			      NULL,		/* override name	   */
			      args,		/* override arg list	   */
			      nargs,		/* number of override args */
			      &widgetmain,	/* ptr to widget id	   */
			      &class)		/* ptr to widget class	   */
       != MrmSUCCESS)
    {
	error_proc("Can't fetch main widget\n");
    }

/*
 *  Manage the topmost widget in the UID hierarchy.
 */

    XtManageChild(widgetmain);
    
/*
 *  Realize the toplevel widget.
 */

    XtRealizeWidget(toplevel);

/*
 *  Loop and process events.
 */

    XtMainLoop();
}
