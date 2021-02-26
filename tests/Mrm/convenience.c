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
static char rcsid[] = "$XConsortium: convenience.c /main/8 1995/07/14 10:53:23 drk $"
#endif
#endif

#include <MrmTest.h>

/*
 * Structures declared in main.c file
 */

extern MrmHierarchy	s_MrmHierarchy;
extern Widget		widgetmain;
extern MrmType		class;

/*
 * Local declarations
 */

void	nyi_proc();

/*
 * Error handling
 */

void error_proc(error_string)
     String	error_string;
{
    fprintf(stdout,"%s\n", error_string);
    fflush(stdout);
}

/*
 * Exit
 */

void exit_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{
    fprintf(stdout,"Exiting\n");
    fflush(stdout);
    MrmCloseHierarchy(s_MrmHierarchy);
    exit(0);
}

/*
 * Help
 */

void help_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{
    nyi_proc(w, "help", NULL);
}

/*
 * Not Yet Implemented - fetches InformationDialog widget
 */

void nyi_proc(w, tag, reason)
     Widget		w;
     int		*tag;
     unsigned long	*reason;
{

    Arg		args[2];
    int		nargs;
    char	buf[80];
    XmString	message;
    Widget	nyi = NULL;
    
    sprintf(buf, "The %s utility is not yet implemented", tag);
    message = XmStringCreateLtoR(buf, XmSTRING_DEFAULT_CHARSET);

    nargs = 0;
    XtSetArg(args[nargs], XmNmessageString, message); nargs++;

    if(MrmFetchWidgetOverride(s_MrmHierarchy,	/* id of uid hierarchy	   */
			      "nyi",		/* uil name of widget	   */
			      widgetmain,	/* parent of widget	   */
			      NULL,		/* override name	   */
			      args,		/* override arg list	   */
			      nargs,		/* number of override args */
			      &nyi,		/* ptr to widget id	   */
			      &class)		/* ptr to widget class	   */
       != MrmSUCCESS)
    {
	error_proc("Can't fetch nyi widget\n");
    }
    else
    {
	XtManageChild(nyi);
    }
}
