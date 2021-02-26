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
static char rcsid[] = "$XConsortium: CreateSimple.c /main/7 1995/07/14 11:32:43 drk $"
#endif
#endif
/***********************************************************************
  	@(#)CreateSimple.c	1.2.1.1	Date:1/22/91
  	Author: SJS
	History:
            08/24/90 SJS let's make this its own routine
	Calls:

	Summary:

            Creates the window used for focus setting. This window is
        used as the focus window when focus is set out of the window
        being validated.

        INPUTS

        OUTPUTS
            none

        RETURNS
************************************************************************/

#include "xislib.h"

void xisCreateSimple()
{
    XWMHints wm_hints;
    XSizeHints size_hints;

    xisDummyFocusWindow =
               XCreateSimpleWindow( xisDisplay, xisRootWindow,
                                    DisplayWidth(xisDisplay,xisScreen) - 50,
                                    DisplayHeight(xisDisplay,xisScreen) - 50,
                                    50,50,2,BlackPixel(xisDisplay,xisScreen),
                                    WhitePixel(xisDisplay,xisScreen));

    wm_hints.flags = (InputHint | StateHint);
    wm_hints.input = False;
    wm_hints.initial_state = NormalState;
    XSetWMHints(xisDisplay,xisDummyFocusWindow,&wm_hints);
    size_hints.flags = (USPosition | USSize);
    size_hints.x = DisplayWidth(xisDisplay,xisScreen)-50;
    size_hints.y = DisplayHeight(xisDisplay,xisScreen)-50;
    size_hints.width = 50;
    size_hints.height = 50;
    XSetWMNormalHints(xisDisplay,xisDummyFocusWindow,&size_hints);
    XMapWindow(xisDisplay,xisDummyFocusWindow);

} /* End xisCreateSimple() */
