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
static char rcsid[] = "$XConsortium: CloseVisual.c /main/7 1995/07/14 11:47:57 drk $"
#endif
#endif
/***********************************************************************
  	@(#)CloseVisual.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Closes the image data file.

        INPUTS
            none
  
        OUTPUTS 
            none

        RETURNS
            nothing
************************************************************************/

#include <AutoMessages.h>
#include "vislib.h"

void mvsCloseVisual()
{
    int i;
    long end_of_image_file;

    switch (mvsGetVisualMode()) {

        case VISUAL_MODE_GENERATE_PIXMAPS:
            end_of_image_file = ftell(mvsImageFd);

            VIS_trace("Writing %d record hashes out to .dat file\n",
                      mvsNumRecIds);

            fwrite_short(mvsImageFd,(unsigned int)mvsNumRecIds);
            for (i=0; i<mvsNumRecIds; i++) {
                fwrite_short(mvsImageFd,(unsigned int)mvsRecIdRecordStartCode);
                fwrite_short(mvsImageFd,(unsigned int)mvsRecIdLength[i]);
                fwrite_long(mvsImageFd,mvsFilePos[i]);
                fwrite(mvsRecIdTable[i],sizeof(char),mvsRecIdLength[i],mvsImageFd);
            }
            if (fseek(mvsImageFd,mvsBeginningOfImageFile,0) != 0) 
                AutoMessage(_AutoMessages[VISMSG33]);
            else
                fwrite_long(mvsImageFd,(unsigned long)end_of_image_file);

            fclose(mvsImageFd);
            break;

        case VISUAL_MODE_BATCH_COMPARE:
        case VISUAL_MODE_INTERACTIVE_COMPARE:

            fclose(mvsImageFd);
            break;

        default:
            /* Do absolutely nothing */
            break;
    }

} /* End mvsCloseVisual() */
