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
static char rcsid[] = "$XConsortium: CompresWrite.c /main/7 1995/07/14 11:49:15 drk $"
#endif
#endif
/***********************************************************************
  	@(#)CompresWrite.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to SCCS
	Calls:

	Summary:
            This function writes out visual info in compressed form
************************************************************************/

#include "vislib.h"

void mvsCompressWrite(fp,buffer,size)
FILE *fp;
unsigned char buffer[];
int size;
{
    unsigned char *bp = buffer;
    unsigned char oldchar;
    long cnt;
    unsigned char *end_of_buffer = &buffer[size];
    unsigned char outbuf[OUTBUF_SIZE];
    int  i,j;

    oldchar = *bp++;
    cnt = 1;
    i = 0;

    /* Loop for pointer bp from beginning of buffer until 'size' bytes passed */

    while (bp < end_of_buffer) {

        /* Count number of times oldchar reappears consecutively */

        while ((bp < end_of_buffer) && (*bp == oldchar)) {
            bp++; cnt++;
        }

        /* Write out character that repeats */

        outbuf[i++] = oldchar;

        /* Then write out repeat count */
        /* Use variable length format where most-sig-bit is set in each byte  */
        /* to indicate that the next byte contains more bits.  Of course this */
        /* means that we can only use the 7 least sig bits per byte for data. */

        while (cnt > 127) {
            outbuf[i++] = (cnt & 0x7f)|(0x80); /* Force MSBit to 1 */
            cnt >>= 7;
        }
        outbuf[i++] = cnt;  /* This one is gauranteed to have MSBit set to 0 */

        if (i > OUTBUF_SIZE - 10) {  /* If buffer full, flush out to file */
            if (mvsBigChars) {
                for (j=0; j<i; j++)
                    fputc(outbuf[j],fp);
            }
            else {
                fwrite(outbuf,sizeof(char),i,fp);
            }
            i = 0;
        }
        oldchar = *bp++;  /* Get next char, store in oldchar */
        cnt = 1;          /* Reset char count to 1 */
    }

    /* Flush buffer out to file one last time */

    if (mvsBigChars) {
        for (j=0; j<i; j++)
            fputc(outbuf[j],fp);
    }
    else {
        fwrite(outbuf,sizeof(char),i,fp);
    }

} /* End mvsCompressWrite() */



