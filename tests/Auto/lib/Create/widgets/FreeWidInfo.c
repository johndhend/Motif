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
static char rcsid[] = "$XConsortium: FreeWidInfo.c /main/8 1995/07/14 11:24:34 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FreeWidInfo.c	1.7.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/18/90 SJS add to SCCS
            07/25/90 SJS free resources associated with the widget
                         info
            07/29/90 PSN parameter changes
	Calls:

	Summary:
            Frees a widget info record and disconnects the pointers in the
            widget info hierarchy appropriately.

            INPUTS
                widget_info  - Pointer to the mvs widget info record that
                               is to be freed

            OUTPUTS
                none

            RETURNS
                noting
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

void mvsFreeWidgetInfo(widget_info)
MvsWidgetInfoRecord *widget_info;
{
    int i;
    MvsWidgetInfoRecord *winfo;
    
    if (widget_info == NULL || !widget_info->in_use) {
      AutoMessage(_AutoMessages[WARNMSG38]);
    }
    else {
        mvsFreeResources(widget_info->widget_class_info, widget_info->mvs_resources);
        widget_info->in_use = 0;
        if (widget_info->widget_class_info != NULL) {
            for (i=0; i<widget_info->widget_class_info->num_res_colors; i++) {
              mvsFreeUniqueColor(widget_info, i);
            }
        }
  
        if( (widget_info->parent == NULL) ||
            (widget_info->parent->first_child == NULL)) {
            AutoMessage(_AutoMessages[WARNMSG38]);
        }
        else {        
            winfo = widget_info->parent->first_child;
            if (winfo == widget_info) {
                widget_info->parent->first_child = widget_info->next_sibling;
            }
            else {
                while ( winfo->next_sibling != NULL && 
                        winfo->next_sibling != widget_info )
                    winfo = winfo->next_sibling;

                if (winfo == NULL || winfo->next_sibling != widget_info) {
                   AutoMessage(_AutoMessages[WARNMSG86]);
                }
                else {
                    winfo->next_sibling = widget_info->next_sibling;
                }
            }
            for ( winfo=widget_info->first_child; 
                  winfo != NULL; 
                  winfo = winfo->next_sibling ) {
                
                mvsFreeWidgetInfo(winfo);
	    }
	} /* End if (parent == NULL) || parent->first_child == NULL)) */

    } /* End if((widget_info == NULL || !widget_info->in_use) */

} /* End mvsFreeWidgetInfo() */
