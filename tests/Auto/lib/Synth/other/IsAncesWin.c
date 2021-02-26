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
static char rcsid[] = "$XConsortium: IsAncesWin.c /main/7 1995/07/14 11:36:06 drk $"
#endif
#endif
/***********************************************************************
  	@(#)IsAncesWin.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
           05/24/90 SJS add to sccs
	Calls:

	Summary:
            Determines if the first specified window is an ancestor of the 2nd
        but not the root. It returns true if this is in fact a true statement.

        INPUTS:
            window1 - window which may be ancestor of window2 
            window2 - any window
        
        OUTPUTS:
            none

        RETURNS:
            True if window1 is not the root but is an ancestor of window2
            False otherwise
************************************************************************/
#include "xislib.h"

int xisIsAncestorWindow(window1,window2)
Window window1,window2;
{
    static char routine_name[] = "xisIsAncestorWindow():";
    Window tmp_window;
    Window root_return, parent_return;
    Window *children_return;
    unsigned int n_children;

    xisUseSessionInfo(routine_name);

    if (window1 == xisRootWindow)
        return(False);

    if((!window1) || (!window2))
        return(False);

    if((!xisWindowExists(window1)) || (!xisWindowExists(window2)))
        return(False);

    tmp_window = window2;
    while (tmp_window != xisRootWindow && tmp_window != window1) {
        if (!XQueryTree(xisDisplay,tmp_window,&root_return,&parent_return,
                        &children_return,&n_children)) {
            (*xisErrorMsg)("%s XQueryTree() failure\n", routine_name);
            exit(-1);
	}
        if (children_return != NULL)
            XFree( (caddr_t)children_return);

        tmp_window = parent_return;
    }

    if (tmp_window == window1)
        return(True);
    else
        return(False);

} /* End xisIsAncestorWindow() */
