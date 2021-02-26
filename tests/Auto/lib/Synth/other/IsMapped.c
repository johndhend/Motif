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
static char rcsid[] = "$XConsortium: IsMapped.c /main/7 1995/07/14 11:36:20 drk $"
#endif
#endif
/***********************************************************************
  	@(#)IsMapped.c	1.8.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
            06/27/90 PSN add new function xisIsWidgetMapped()
            08/17/90 PSN add new function xisIsViewable()
	Calls:

	Summary:
            Determines if the specified window is mapped or not.

        INPUTS:
            window - window which may be mapped or not
        
        OUTPUTS:
            none

        RETURNS:
            True if window is mapped
            False otherwise
************************************************************************/
#include "xislib.h"

int xisIsMapped(window)
Window window;
{
    static char routine_name[] = "xisIsMapped()";
    XWindowAttributes wattr;

    xisUseSessionInfo(routine_name);

    XGetWindowAttributes(xisDisplay,window,&wattr);

    return(wattr.map_state != IsUnmapped); 

} /* End xisIsMapped() */


int xisIsViewable(window)
Window window;
{
    static char routine_name[] = "xisIsViewable()";
    XWindowAttributes wattr;

    xisUseSessionInfo(routine_name);

    XGetWindowAttributes(xisDisplay,window,&wattr);

    return(wattr.map_state == IsViewable); 

} /* End xisIsViewable() */


/*
 * Return status of widget being mapped or unmapped
 */
int xisIsWidgetMapped(widget)
Widget	widget;
{
    XisObjectRecord	*object = xisGetObjectFromWidget(widget);

    return (xisIsMapped(object->id.window));

} /* End xisIsWidgetMapped() */
