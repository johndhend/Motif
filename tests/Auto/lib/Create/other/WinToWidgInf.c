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
static char rcsid[] = "$XConsortium: WinToWidgInf.c /main/7 1995/07/14 11:18:02 drk $"
#endif
#endif
/***********************************************************************
  	@(#)WinToWidgInf.c	1.3.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/21/90 SJS add to sccs
	Calls:

	Summary:
            Looks up the widget_info record associated with the specified window

            INPUTS
                window  - window to match

            OUTPUTS
                none

            RETURNS
                Pointer to widget_info record associated with the specified
                window
************************************************************************/

#include "mvslib.h"

MvsWidgetInfoRecord *mvsWindowToWidgetInfo(window)
Window window;
{
    MvsWidgetInfoRecord *widget_info = mvsRootWidgetInfo->first_child;
    MvsWidgetInfoRecord *widget_info_stack[100];
    short stack_top = 0;

    while ( widget_info != mvsRootWidgetInfo && 
            window != XtWindowOfObject(widget_info->widget) ) {

        if (widget_info->first_child != NULL) {
            widget_info_stack[stack_top++] = widget_info;
            widget_info = (MvsWidgetInfoRecord *)widget_info->first_child;
        }
        else 
            if (widget_info->next_sibling != NULL)
                widget_info = (MvsWidgetInfoRecord *)widget_info->next_sibling;
            else {
                widget_info = NULL;
                while (stack_top > 0 && widget_info == NULL)
                    widget_info = (MvsWidgetInfoRecord *)
                                  widget_info_stack[--stack_top]->next_sibling;

                if (stack_top == 0)
                    break;
            } 
    } /* End while() */

    return widget_info;

} /* End mvsWindowToWidgetInfo() */
