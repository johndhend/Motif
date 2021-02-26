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
static char rcsid[] = "$XConsortium: AllocNaColor.c /main/7 1995/07/14 11:45:33 drk $"
#endif
#endif
/***********************************************************************
  	@(#)AllocNaColor.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	Calls:

	Summary:
            Allocate one unqiue named color from the locol color cache.

        NOTE: This routine, unlike mvsAllocColor() and mvsAllocColorStruct()
        does not add the pixel value to the mvsColorAllocInfo list.  So you
        must call mvsAllocColor() or mvsAllocColorStruct() after you return
        with the pixel value from this routine.                            

        INPUTS
            name  - requested RGB color name (one of the mvsColorTable names)

        OUTPUTS
            pixel - pixel color index value returned
 
        RETURNS
            Status where 0=failed, ~0=succeeded
************************************************************************/
#include <AutoMessages.h>
#include "vislib.h"

#define SQR(x) (temp=(x), temp*temp)

Status mvsAllocNamedColor(name, pixel)
char name[];
Pixel *pixel;
{
    int i,j;
    XColor nearest;
    Status status;
    unsigned long heuristic_val, lowest_heuristic_value = 0xFFFFFFFFL;
    int best_match_pixel_num;
    unsigned long temp;

    /* look up name in our color table */

    for (i=0; i<mvsNumTableColors && 
              mvsStringCompare(name,mvsColorTable[i].name1) != 0 &&
              mvsStringCompare(name,mvsColorTable[i].name2) != 0    ;
         i++);
    
    if (i == mvsNumTableColors) { /* if not found... */
        VIS_error("Color name '%s' not found in color table!\n",name);
        exit(1);
    }

    /* look-up which mvsColorAllocInfo slot will be used when we alloc it 
       later in mvsSetValuesNoCheck.                                       */

    nearest.red   = mvsColorTable[i].red<<8;
    nearest.green = mvsColorTable[i].green<<8;
    nearest.blue  = mvsColorTable[i].blue<<8;
    nearest.flags = (DoRed | DoGreen | DoBlue);

    status = XAllocColor(visDisplay,mvsVisualInfo.colormap_id,&nearest);

    if (status == 0) { /* XAllocColor failed! */

        /* In practice, this path should never occur if XServer implemented  */
        /* correctly (i.e., there is always a "nearest" color.               */

        AutoMessage(_AutoMessages[VISMSG18]);
	AutoMessage(_AutoMessages[VISMSG19]);
        

        /* find pixel in currently allocated set with nearest rgb */

        for (j=0; j<MAX_COLORS; j++) {

          if (mvsColorAllocInfo[j].alloc_cnt > 0) {
            heuristic_val = /* geometric distance in 3-space */
                SQR((mvsColorTable[i].red<<6)   - (mvsColorAllocInfo[j].red>>2))
              + SQR((mvsColorTable[i].green<<6) - (mvsColorAllocInfo[j].green>>2))
              + SQR((mvsColorTable[i].blue<<6)  - (mvsColorAllocInfo[j].blue>>2));

            /* NOTE: the above values have been scaled so that the result
               will always fit into an unsigned long variable.               */

            if (heuristic_val < lowest_heuristic_value) {
                lowest_heuristic_value = heuristic_val;
                best_match_pixel_num = j;
            }
          }
        }

        if (lowest_heuristic_value == 0xFFFFFFFFL) {
            *pixel = WhitePixel(visDisplay,DefaultScreen(visDisplay)); /* be safe */
            AutoMessage(_AutoMessages[VISMSG20]);
            return 0; /* could not find an allocated pixel close to request */
        }

        j = best_match_pixel_num;
        nearest.pixel = mvsColorAllocInfo[j].pixel;
        nearest.red = mvsColorAllocInfo[j].red;
        nearest.green = mvsColorAllocInfo[j].green;
        nearest.blue = mvsColorAllocInfo[j].blue;
    }

    *pixel = nearest.pixel;

    return 1;

} /* End mvsAllocNamedColor() */
