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
static char rcsid[] = "$XConsortium: AllocColorSt.c /main/7 1995/07/14 11:45:23 drk $"
#endif
#endif
/***********************************************************************
  	@(#)AllocColorSt.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   09/17/90 SJS split library
	Calls:

	Summary:
            Allocate one unqiue RGB color from the locol color cache.

        INPUTS
            color  - requested RGB color value

        OUTPUTS
            none
 
        RETURNS
            Status where 0=failed, ~0=succeeded
************************************************************************/
#include <AutoMessages.h>
#include "vislib.h"

Status mvsAllocColorStruct(color)
XColor color;
{
    int i;
    Status status;
    
    /* record pixel choice in current_color_info array */
    /* see if pixel is already in color_alloc array */

    for (i=0;
             i<MAX_COLORS &&
             ( mvsColorAllocInfo[i].alloc_cnt == 0     ||
               mvsColorAllocInfo[i].pixel != color.pixel );
         i++);

    if (i != MAX_COLORS) /* Yes it exists. Just increment its allocation cnt */ {
        mvsColorAllocInfo[i].alloc_cnt++;
        status = 1;
    }

    else { /* No, it does not exist. Create a new entry for it */

        /* find next available color_alloc slot */

        for (i=0; i<MAX_COLORS && mvsColorAllocInfo[i].alloc_cnt != 0; i++);
        if (i == MAX_COLORS) {
            AutoMessage(_AutoMessages[VISMSG1]);
            return 0;
        }

        /* transfer info to this slot */

        mvsColorAllocInfo[i].pixel = color.pixel;
        mvsColorAllocInfo[i].red = color.red;
        mvsColorAllocInfo[i].green = color.green;
        mvsColorAllocInfo[i].blue = color.blue;
        mvsColorAllocInfo[i].alloc_cnt = 1;

        status = XAllocColor(visDisplay,mvsVisualInfo.colormap_id,&color);
    }
    return status;

} /* End mvsAllocColorStruct() */













