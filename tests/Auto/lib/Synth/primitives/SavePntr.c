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
static char rcsid[] = "$XConsortium: SavePntr.c /main/7 1995/07/14 11:42:53 drk $"
#endif
#endif
/***********************************************************************
  	@(#)SavePntr.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/30/90/SJS add to sccs
            08/07/90/SJS do not allow pointer to start off the
                         display (ie. x or y < 0)
	Calls:

	Summary:
            Initializes xisSavePointerX and xisSavePointerY with the start
        position of the pointer.  This routine should be called at the
        beginning of the application and xisRestorePointer() should be
        called at the end of an input synthesis session. We need to start
        the validation out with the pointer over a valid object. The
        object chosen is the root window.

        INPUTS:
            none
        
        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/

#include "xislib.h"

void xisSavePointer()
{
    static char routine_name[] = "xisSavePointer";
    int x,y;
    unsigned int button_mask;
    Window root_return,tmp_window;

    /* NOTE: Some window managers may change focus to our application
       at application window creation time because of the use of a
       particular focus policy. */

    xisUseSessionInfo(routine_name);

    XGetInputFocus(xisDisplay,&xisSaveFocusWindow,&xisSaveFocusRevert);

    if (!XQueryPointer(xisDisplay,xisRootWindow,&root_return,
                       &tmp_window,&xisSavePointerX,&xisSavePointerY,
                       &x,&y,&button_mask)) {
        (*xisErrorMsg)("Pointer not on root window anymore!!\n");
        exit(-1);
    }

    if((xisSaveFocusWindow == None) || (xisSaveFocusWindow == PointerRoot))
        xisSaveFocusWindow = xisRootWindow;

    xisPointerSaved = True;

    /* On the DecStations, it is possible to move the pointer "off" the
       display. This is a problem because we do not have any objects off
       the display. So, let's move the pointer on the display.
    */
    if( (xisSavePointerX < 0) || (xisSavePointerY < 0) ) {
        xisSavePointerX = 0;
        xisSavePointerY = 0;
        XWarpPointer(xisDisplay,None,xisRootWindow,0,0,0,0, 0, 0);
    }

} /* End xisSavePointer() */
