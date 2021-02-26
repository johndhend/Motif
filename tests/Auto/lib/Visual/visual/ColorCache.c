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
static char rcsid[] = "$XConsortium: ColorCache.c /main/7 1995/07/14 11:48:38 drk $"
#endif
#endif
/***********************************************************************
  	@(#)ColorCache.c	1.2.1.1	Date:1/22/91
  	Author: PSN
	History:
	   11/12/90 PSN Add to sccs tree
	Calls:

	Summary:
            This file contains the function visLookUpColorCache &
	visAddToColorCache which looks-up local color cache for 
	existance of already looked up pixel, if present use the cache
	value otherwise do XQueryColor for the given pixel and save that
	XColor returned.
	      
        INPUTS
            Pointer to XColor that contains correct pixel value for 
	visLookUpColorCache & visAddToColorCache; but also contains
	other fields correctly initialized for visAddToColorCache.

        OUTPUTS
            XColor initialized by visLookUpColorCache.
	    Cache updated by visAddToColorCache.
 
        RETURNS
            <0 failed, >=0 succeeded for visLookUpColorCache.
************************************************************************/

#include <AutoMessages.h>
#include "vislib.h"

int visLookUpColorCache(color)
XColor	*color;
{
    int	   i;
    Pixel  pixel = color->pixel;

    for (i=0; i<cache_pointer && i<MAX_COLORS; i++)
	if (color_cache[i].pixel == pixel) {
	   *color = color_cache[i];
	   return (i);
	}
    return(-1);

} /* End visLookUpColorCache() */

void visAddToColorCache(color)
XColor	*color;
{
    if (cache_pointer < MAX_COLORS)
	color_cache[cache_pointer++] = *color;
    else
      AutoMessage(_AutoMessages[WARNMSG60]);

} /* End visAddToColorCache() */

/* 
 * Clear cache pointer so that it effectively clears the color cache
 */
void visClearColorCache()
{
    cache_pointer = 0;
} /* End visClearColorCache() */



