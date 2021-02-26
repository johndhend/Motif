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
static char rcsid[] = "$XConsortium: GetPntrInfo.c /main/7 1995/07/14 11:35:07 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetPntrInfo.c	1.3.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Returns the current mouse pointer location relative to the root and
        the lowest containing window in the window heirarchy.
           
        INPUTS:
            none
        
        OUTPUTS:
            ptr_window        - window id of lowest containing window in
                                heirarchy
            root_x,root_y     - position of pointer relative to the root window
            window_x,window_y - position of pointer relative to ptr_window
            button_mask       - current state of mouse buttons using
                                Button1Mask,etc.

        RETURNS:
            void
************************************************************************/
#include "xislib.h"

void xisGetPointerInfo(ptr_window,root_x,root_y,window_x,window_y,button_mask)

Window *ptr_window;
int *root_x,*root_y,*window_x,*window_y;
unsigned int *button_mask;
{
    static char routine_name[] = "xisGetPointerInfo";
    Window root_return, tmp_window = xisRootWindow, save_window = xisRootWindow;

    xisUseSessionInfo(routine_name);

    while (tmp_window != None) {

        save_window = tmp_window;

        if (!XQueryPointer(xisDisplay,save_window,&root_return,
                           &tmp_window,root_x,root_y,
                           window_x,window_y,button_mask)) {
            (*xisErrorMsg)("Pointer not on root window anymore!!\n");
            exit(-1);
        }
    }

    *button_mask = xisState.mod_button_state;

    *ptr_window = save_window;

} /* End xisGetPointerInfo() */
