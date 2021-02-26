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
static char rcsid[] = "$XConsortium: FreeUniqColr.c /main/7 1995/07/14 11:49:43 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FreeUniqColr.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Frees up one of the unique color index values for pixmap
        generate mode.

        INPUTS
            none

        OUTPUTS
            none

        RETURNS
            nothing
************************************************************************/
#include <AutoMessages.h>
#include "vislib.h"

/* 
   Changed for Automation to look at widgetUniqueColorInfo from the
   widget (via the widget_info struct, and not the global array
   (now not used)
*/

void mvsFreeUniqueColor(winfo, pixel)
MvsWidgetInfoRecord *winfo;
Pixel pixel;
{
  char msg_string[125];
  
    if (pixel >= MAX_COLORS) {
       sprintf(msg_string, _AutoMessages[VISMSG36], pixel);
       AutoMessage(msg_string); } 
    else {
        if (winfo->widgetUniqueColorInfo[pixel].in_use == 0){
       sprintf(msg_string, _AutoMessages[VISMSG37], pixel);
       AutoMessage(msg_string); } 

        winfo->widgetUniqueColorInfo[pixel].in_use = 0;
        winfo->widgetUniqueColorInfo[pixel].widget_info = NULL;
        winfo->widgetUniqueColorInfo[pixel].color_ref = 0;
    }
} /* End mvsFreeUniqueColor() */
