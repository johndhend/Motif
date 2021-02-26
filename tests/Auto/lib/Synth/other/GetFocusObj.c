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
static char rcsid[] = "$XConsortium: GetFocusObj.c /main/7 1995/07/14 11:34:08 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetFocusObj.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/31/90 SJS change return of this function
	Calls:

	Summary:
            Returns the object that is currently in focus. It does this by first
        identifying which top-most shell widget is in focus (if any are) and
        then determining which item of which tab group under that shell is
        currently in focus.

        INPUTS
            none

        OUTPUTS
            none

        RETURNS
                Object that is in keyboard focus. If the current window is not a
            recognizable widget, it then returns NULL.  If the current window
            is the root window, then it return the constant PointerRoot.
                The object returned is used as the base for calling the
            SetExpectedActions procs. The object may or may not be a "real"
            widget. It can also be a gadget.
************************************************************************/
#include "xislib.h"

XisObjectRecord *xisGetFocusObject()
{
    Window pointer_window;
    XisObjectRecord *curr_focus_object;
    int rx,ry,wx,wy;
    unsigned int button_mask;

    xisGetPointerInfo(&pointer_window,&rx,&ry,&wx,&wy,&button_mask);

    curr_focus_object = xisFindObject(xisState.focus_widget,
                                      xisState.focus_object_type,
                                      xisState.focus_instance);

    return(curr_focus_object);

} /* End xisGetFocusObject() */
