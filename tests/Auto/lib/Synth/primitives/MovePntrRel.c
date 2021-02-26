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
static char rcsid[] = "$XConsortium: MovePntrRel.c /main/7 1995/07/14 11:41:49 drk $"
#endif
#endif
/***********************************************************************
  	@(#)MovePntrRel.c	1.5.1.1	Date:1/22/91
  	Author:
	History:
		07/18/90 PSN Fixed wrong call to non-existing procedure. Not
			     calls xisCMovePointer() correctly.
	Calls:

	Summary:
            Simulates a user moving the mouse some delta-x delta-y distance.

        INPUTS:
            delta_x - x coord of relative offset from current position
            delta_y - y coord of relative offset from current position
            direction - MoveAny, MoveUp, MoveDown, MoveLeft, MoveRight

        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

void xisMovePointerRelative(delta_x,delta_y)
int delta_x, delta_y;
{
    int curr_x,curr_y;
    XisObjectRecord *curr_object;
    XisObjectRecord *end_obj;
    Boolean valid = True;

    (*xisTraceMsg)("Got send_event_request = MovePointerRelative\n");


    /* Get current pointer location and current object over */

    xisGetPointerLocation(&curr_x,&curr_y);
    
    curr_object = xisFindObjectAtLocation(curr_x,curr_y);

/* Automation Added */

    end_obj = xisFindObjectAtLocation(curr_x + delta_x, curr_y + delta_y);

    if (end_obj == NULL) {
	AutoMessage(_AutoMessages[WARNMSG17]);
	valid = False;
    }
    /*
    else 
   	if (curr_object != end_obj)
	     AutoMessage(_AutoMessages[WARNMSG18]);
    */
	
    if (valid)
    	xisCMovePointer(curr_object, curr_x, curr_y,
			curr_x + delta_x, curr_y + delta_y);

/* End Automation Added */

} /* End xisMovePointerRelative() */
