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
static char rcsid[] = "$XConsortium: SetupWidInfo.c /main/7 1995/07/14 11:25:11 drk $"
#endif
#endif
/***********************************************************************
  	@(#)SetupWidInfo.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
	   06/17/90 TAT Add to sccs tree
	   07/31/90 PSN Fix for memory leaks
	Calls:

	Summary:
            Allocates and sets up an additional widget info record.

            INPUTS
                parent_info      - parent widget info
                widget           - Xt widget
                class_info       - class_info of widget

            OUTPUTS
                none

            RETURNS
                widget_info_record
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

#define NUMARGS	50

MvsWidgetInfoRecord *mvsSetupNewWidgetInfo(parent_info,widget,class_info)
MvsWidgetInfoRecord *parent_info;
Widget widget;
MvsWidgetClassInfo *class_info;
{
    MvsWidgetInfoRecord *widget_info;
    MvsResourceInfoRecord *resource_info;
    short *res_color_ref;
    short *res_pixmap_ref;
    short *unique_color_ref;
    int num_res_colors;
    MvsArgVal *mvs_resources;
    int widget_class_code;

    Arg args[NUMARGS];
    int nargs;
    int i,j;

    if (widget == NULL || parent_info == NULL)
        return NULL;

    for (i=0; i<NUMARGS; i++)	args[i].value = 0L;

    widget_info = mvsAllocWidgetInfo(class_info,parent_info,widget);
    widget_info->window = XtWindowOfObject(widget);
    resource_info = class_info->resource_info;
    res_color_ref = class_info->res_color_ref;
    res_pixmap_ref = class_info->res_pixmap_ref;
    unique_color_ref = widget_info->unique_color_ref;
    num_res_colors = class_info->num_res_colors;
    mvs_resources = widget_info->mvs_resources;

    mvsLoadResources(widget_info,mvs_resources);

    nargs = 0;
    if (mvsGetVisualMode() == VISUAL_MODE_GENERATE_PIXMAPS) {
        for (j=0; j<num_res_colors; j++) {
            if (res_pixmap_ref[j] >= 0 && 
                mvs_resources[res_pixmap_ref[j]] != XmUNSPECIFIED_PIXMAP) {
/* Automation Fix */
/*                XtSetArg(args[nargs],resource_info[res_pixmap_ref[j]].name,
                         XmUNSPECIFIED_PIXMAP);*/
/* End Automation Fix */
/*                nargs++;*/
	    }
	    if (res_color_ref[j] >= 0) {
		XtSetArg(args[nargs],resource_info[res_color_ref[j]].name,
			 unique_color_ref[j]);
		nargs++;
	    }
	}

        /* Make mvsSetLocalValues store color arguments locally */
        mvsSetVisualMode(VISUAL_MODE_DONT_CHECK);
        mvsSetValuesNoCheck(widget_info,args,nargs);
        mvsSetVisualMode(VISUAL_MODE_GENERATE_PIXMAPS);
    }
    else {
        for (j=0; j<num_res_colors; j++) {
	    if (res_color_ref[j] >= 0)
		if (!mvsAllocColor(mvs_resources[res_color_ref[j]])) {
		    AutoMessage(_AutoMessages[WARNMSG39]);
		}
        }
    }    

    return widget_info;

} /* End mvsSetupNewWidgetInfo() */
