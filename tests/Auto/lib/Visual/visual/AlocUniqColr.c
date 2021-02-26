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
static char rcsid[] = "$XConsortium: AlocUniqColr.c /main/7 1995/07/14 11:46:20 drk $"
#endif
#endif
/***********************************************************************
  	@(#)AlocUniqColr.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to SCCS
	Calls:

	Summary:
            This function is used for providing simple "hard-wired" color index
        values for use during the visual generate run of a test.  It keeps 
        track of the lowest unique color index values and which ones are 
        already in use so that new additional color index values may
        be obtained at any time.

        INPUTS
            none
 
        OUTPUTS
            none
 
        RETURNS
            none
************************************************************************/

#include <AutoMessages.h>
#include "vislib.h"

#define COLOR	256
#define MONO 	2
#define GRAY	5

Pixel mvsAllocUniqueColor(widget_info,color_ref)
MvsWidgetInfoRecord *widget_info;
int color_ref;
{
    Pixel i;

/* 
   Changed for Automation. No longer allocate into global array
   mvsUniqueColorAllocInfo, now each widget will carry around a
   representation of this array and the comparison and generation
   routines will be modified.

 */

/*

    for (i=0; i<MAX_COLORS; i++) {
       	 if (mvsUniqueColorAllocInfo[i].in_use == 0)
            break;
    }

    if (i == MAX_COLORS) {
        AutoError(_AutoMessages[VISMSG23]);
        
    }

    mvsUniqueColorAllocInfo[i].in_use = 1;
    mvsUniqueColorAllocInfo[i].widget_info = widget_info;
    mvsUniqueColorAllocInfo[i].color_ref = color_ref;

*/

/* 
   Check for MonoChrome server an if so only return 0 or 1. If
   color return anything up to 256 and then cycle through colors
   again. If GRAY scale, retrun 0-5 and cycle through the rest.
*/


    if (mvsVisualInfo.depth == 1) 
    	return(color_ref % MONO);    
    else if ((mvsVisualInfo.class == StaticGray) ||
             (mvsVisualInfo.class == GrayScale))
	return(color_ref % GRAY);
    else
	return(color_ref % COLOR);


} /* End mvsAllocUniqueColor() */
