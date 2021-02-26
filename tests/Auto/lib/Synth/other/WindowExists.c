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
static char rcsid[] = "$XConsortium: WindowExists.c /main/7 1995/07/14 11:37:16 drk $"
#endif
#endif
/***********************************************************************
  	@(#)WindowExists.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Determines if the specified window exists.

        INPUTS:
            window - window which may or may not exist
        
        OUTPUTS:
            none

        RETURNS:
            True if window exists
            False otherwise
************************************************************************/
#include "xislib.h"

static int weBadWindowFlag;

/**** ERROR HANDLER FOR WINDOW_EXISTS BELOW *****/

static int weErrorHandler(display_in,err_event)
Display *display_in;
XErrorEvent *err_event;
{
  if ((display_in == xisDisplay)&&(err_event->request_code == X_GetGeometry)&&
      ((err_event->error_code == BadDrawable)||(err_event->error_code == BadWindow)) )
      weBadWindowFlag = 1;
        
} /* End weErrorHandler() */

/**** WINDOW_EXISTS *****/

int xisWindowExists(window)
Window window;
{
    static char routine_name[] = "xisWindowExists";
    Window root_return;
    int x,y;
    unsigned int w,h,bw;
    unsigned int depth;

    xisUseSessionInfo(routine_name);

    weBadWindowFlag = 0;
    XSetErrorHandler(weErrorHandler);

    XGetGeometry(xisDisplay,window,&root_return,&x,&y,&w,&h,&bw,&depth);
    XSync(xisDisplay,False);

    XSetErrorHandler(NULL);

    return (!weBadWindowFlag);

} /* end xisWindowExists() */
