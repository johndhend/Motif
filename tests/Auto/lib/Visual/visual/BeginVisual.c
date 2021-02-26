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
static char rcsid[] = "$XConsortium: BeginVisual.c /main/7 1995/07/14 11:46:32 drk $"
#endif
#endif
/***********************************************************************
  	@(#)BeginVisual.c	1.2.1.1	Date:1/22/91
  	Author: SJS
	History:
            09/14/90 SJS create, part of visual/mvslib split
	Calls:

	Summary:
            Initializes the visual library local copies of visual
	related structures. Set up other visual related items

        INPUTS:
            display_in     -  the display that is connected to
            trace_msg_func - a function which prints out a trace message
            warning_msg_func - a function which prints out a warning message
            error_msg_func - a function which prints out an error message
        
        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/
#define DECLARE_VISLIB_GLOBALS_HERE

#include <AutoMessages.h>
#include "vislib.h"

void  visBeginVisual(display_in, trace_msg_func, warning_msg_func,
                     error_msg_func)
Display *display_in;
void (*trace_msg_func)();      /* These three funcs have params like printf */
void (*warning_msg_func)();
void (*error_msg_func)();
{
    static char routine_name[] = "visBeginVisual():";
    char msg_string[125];
    /* Validate incoming parameters */

    visDisplay = display_in;
    visTraceMsg = trace_msg_func;
    visWarningMsg = warning_msg_func;
    visErrorMsg = error_msg_func;

    if (error_msg_func == 0) {
      
        fprintf(stderr, "%s called with NULL error_msg_func\n", routine_name);
        exit(-1);
    }

    if (display_in == 0) {
        sprintf (msg_string, _AutoMessages[VISMSG3], routine_name);
	AutoError(msg_string);
        
    }
    if (trace_msg_func == 0) {
        sprintf (msg_string, _AutoMessages[VISMSG4], routine_name);
	AutoError(msg_string);

    }
    if (warning_msg_func == 0) {
        sprintf (msg_string, _AutoMessages[VISMSG5], routine_name);
	AutoError(msg_string);
    }

    mvsOpenVisual();

} /* end visBeginVisual() */
