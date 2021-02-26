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
static char rcsid[] = "$XConsortium: GetXisState.c /main/7 1995/07/14 11:50:40 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetXisState.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
	Calls:

	Summary:
            Used to generate a compressed representation of the current
        input synthesis 
        state.

          INPUTS
            none

          OUTPUTS
            hash - array of bytes used to fill with xis state information
            num_bytes - number of bytes returned

          RETURNS
            nothing
************************************************************************/
  
#include "mvslib.h"

void mvsGetXisStateHash(hash,num_bytes)
char hash[];
short *num_bytes;
{
    int bit = 0;
    int byte = 0;
    XisStateRecord *xis_state = xisGetStateInfo();
    int root_x,root_y;
    XisObjectRecord *pointer_obj, *focus_obj, *selected_obj;
    short pointer_id_code,focus_id_code,selected_id_code;
    
    xisGetPointerLocation(&root_x,&root_y);
    pointer_obj = xisFindObjectAtLocation(root_x,root_y);
    if (pointer_obj == NULL_Object)
        pointer_id_code = 0;
    else
        pointer_id_code = pointer_obj->id_code;

    if (xis_state->focus_window == 0)
        focus_id_code = 0;
    else {
        focus_obj = xisFindObjectFromWindow(xis_state->focus_window);
        if (focus_obj == NULL_Object)
            focus_id_code = 0;
        else
            focus_id_code = focus_obj->id_code;
    }

    if (xis_state->selected_widget == 0)
        selected_id_code = 0;
    else {
        selected_obj = xisFindObject(xis_state->selected_widget,
                                     xis_state->selected_object_type,
                                     xis_state->selected_instance);
        if (selected_obj == NULL_Object)
            selected_id_code = 0;
        else
            selected_id_code = selected_obj->id_code;
    
    }

    mvsPushHashBits(hash,&byte,&bit,pointer_id_code,8);

    mvsPushHashBits(hash,&byte,&bit,focus_id_code,8);

    mvsPushHashBits(hash,&byte,&bit,selected_id_code,8);

    mvsPushHashBits(hash,&byte,&bit,xis_state->mod_button_state,16);

    if (bit == 0)
        *num_bytes = byte;
    else
        *num_bytes = byte+1;

} /* end mvsGetXisStateHash() */
