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
static char rcsid[] = "$XConsortium: CheckVisual.c /main/8 1995/07/14 11:46:45 drk $"
#endif
#endif
/***********************************************************************
  	@(#)CheckVisual.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to SCCS
	Calls:

	Summary:
            Called to either compare the visual pixmap against known-good pixmap 
        record from file or to generate known-good pixmap. 

        INPUTS:
            widget - the widget whose image needs comparing or capturing
        
        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/
#include <AutoMessages.h>
#include "vislib.h"

void mvsCheckVisual(widget_info)
MvsWidgetInfoRecord *widget_info;
{

    char msg_string[125];
  
    if (XmIsGadget(widget_info->widget))
        widget_info = widget_info->parent;

    switch (mvsVisualMode) {
        case VISUAL_MODE_DONT_CHECK:
            mvsImageFd = 0;
            break;

        case VISUAL_MODE_BATCH_COMPARE:
            mvsComparePixmapBatch(widget_info);
            break;

        case VISUAL_MODE_INTERACTIVE_COMPARE:
	    mvsComparePixmapInt(widget_info);
            break;

        case VISUAL_MODE_GENERATE_PIXMAPS:
            mvsGeneratePixmap(widget_info);
            break;        

	default:
	    sprintf(msg_string, _AutoMessages[VISMSG45], mvsVisualMode);
	    AutoMessage(msg_string);
    }

} /* End mvsCheckVisual() */
