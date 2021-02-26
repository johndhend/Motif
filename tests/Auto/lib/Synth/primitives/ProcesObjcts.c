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
static char rcsid[] = "$XConsortium: ProcesObjcts.c /main/7 1995/07/14 11:42:18 drk $"
#endif
#endif
/***********************************************************************
  	@(#)ProcesObjcts.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/30/90 SJS add to sccs
            08/28/90 SJS free child_windows initially allocated by XQueryTree()
	Calls:

	Summary:
            Regenerate the graphical objects data structure.

        INPUTS
            none

        OUTPUTS
            none

        RETURNS
            nothing
************************************************************************/

#include "xislib.h"

void xisProcessObjects()
{
    static char routine_name[] = "xisProcessObjects";
    int i;

    xisUseSessionInfo(routine_name);

    /* First free all objects below the root one */

    for (i=0; i<xisMaxObjectNum; i++) {
        if(xisObjects[i].id.num_children)
            XFree( (caddr_t)xisObjects[i].id.children_windows);
        xisObjects[i].in_use = 0;
    }

    xisObjects[0].first_child = NULL_Object;
    xisObjects[0].in_use = TRUE;
    xisMaxObjectNum = 1;

    xisObjects[0].id.window_under_parent = xisRootWindow;
    xisObjects[0].id.window = xisRootWindow;
    xisObjects[0].id.widget = NULL;

    XQueryTree(xisDisplay,xisObjects[0].id.window,
               &xisObjects[0].id.root_window,
               &xisObjects[0].id.parent_window,
               &xisObjects[0].id.children_windows,
               &xisObjects[0].id.num_children);

    /* Then call function to re-generate all the objects */

    (*xisGenerateObjects)(&xisObjects[0]);    

} /* End xisProcessObjects() */
