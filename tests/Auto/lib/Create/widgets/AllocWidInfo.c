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
static char rcsid[] = "$XConsortium: AllocWidInfo.c /main/7 1995/07/14 11:24:11 drk $"
#endif
#endif
/***********************************************************************
  	@(#)AllocWidInfo.c	1.7.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/18/90 SJS add to SCCS
            06/21/90 SJS add being_destroyed & convenience parent
	Calls:

	Summary:
            Allocates a widget info record and connects the pointers in the
            widget info hierarchy appropriately. This function does not
            perform color resource set up. (See mvsSetupWidgetInfo() )

            INPUTS
                widget_class_info  - Pointer to the mvs widget class info
                                     record that
                                     you want this widget info record to point
                                     to

                parent_widget_info - Pointer to the parent widget info record

                widget             - The Xt widget id
  
            OUTPUTS
                none

            RETURNS
                Pointer to newly alloc'ed widget info record.
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

MvsWidgetInfoRecord *mvsAllocWidgetInfo(wc_info, pinfo, widget)
MvsWidgetClassInfo *wc_info;
MvsWidgetInfoRecord *pinfo;
Widget widget;
{
    int i,j;
    MvsWidgetInfoRecord *winfo;

    for (i=1; i<=mvsNumWidgetInfos; i++) {
        if (i >= MAX_NUM_WIDGET_INFOS) {
            AutoMessage(_AutoMessages[WARNMSG120]);
            exit(-1);
        }

        if (!mvsWidgetInfos[i].in_use) {
            mvsWidgetInfos[i].in_use = 1;
            mvsWidgetInfos[i].being_destroyed = False;
            mvsWidgetInfos[i].c_parent = False;

            if (i == mvsNumWidgetInfos)
                mvsNumWidgetInfos++;

            mvsWidgetInfos[i].parent = pinfo;
            if (pinfo != NULL) {
                winfo = mvsWidgetInfos[i].parent->first_child;
                if (winfo == NULL)
                    mvsWidgetInfos[i].parent->first_child = &mvsWidgetInfos[i];
                else {
                    while (winfo->next_sibling != NULL)
                        winfo = winfo->next_sibling;
                    winfo->next_sibling = &mvsWidgetInfos[i];
                }
	    }

            mvsWidgetInfos[i].widget = widget;
            mvsWidgetInfos[i].widget_class_info = wc_info;
            mvsWidgetInfos[i].callbacks_setup = 0;
            mvsWidgetInfos[i].first_child = NULL;
            mvsWidgetInfos[i].next_sibling = NULL;


            if (wc_info != NULL) {
                for (j=0; j<wc_info->num_res_colors; j++) {
                    mvsWidgetInfos[i].unique_color_ref[j] 
                        	= mvsAllocUniqueColor(&mvsWidgetInfos[i],j);
/* Automation Added */
		    mvsWidgetInfos[i].widgetUniqueColorInfo[j].in_use 
				= True;
		    mvsWidgetInfos[i].widgetUniqueColorInfo[j].widget_info 
				= &mvsWidgetInfos[i];
		    mvsWidgetInfos[i].widgetUniqueColorInfo[j].color_ref 
				= j;
/* End Automation Added */
		}
            }

            break;
	}
    } /* End for(i<=mvsNumWidgetInfos) */

    return (&mvsWidgetInfos[i]);

} /* End mvsAllocWidgetInfo() */
