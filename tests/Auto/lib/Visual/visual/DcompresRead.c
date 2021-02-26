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
static char rcsid[] = "$XConsortium: DcompresRead.c /main/7 1995/07/14 11:49:24 drk $"
#endif
#endif
/***********************************************************************
  	@(#)DcompresRead.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to SCCS
	Calls:

	Summary:
            This function reads in information about visual images
        that was previously written to the data file. This information
        was in compressed form and needs to be decompressed
************************************************************************/

#include "vislib.h"

void mvsDecompressRead(fp,buffer,size)
FILE *fp;
unsigned char buffer[];
int size;
{
    unsigned char *bp = buffer;
    unsigned char byte,curchar;
    long cnt;
    unsigned char cnt_comp[10];
    short num_cnt_comps;
    unsigned char *end_of_buffer = &buffer[size];
    unsigned char inbuf[INBUF_SIZE];
    int  i,j;

    mvsGetCh((FILE *)0, (unsigned char *)0,
             (unsigned char *)0); /* initialize mvsGetCh */

    /* Loop to read one byte at a time from buffer until 'size' bytes read */

    while ((bp < end_of_buffer) && (mvsGetCh(fp,inbuf,&curchar))) {

        /* New character read in while loop above */

        /* Now read the variable length count below */

        cnt = 0;
        if (mvsGetCh(fp,inbuf,&byte)) {

            num_cnt_comps = 0;

            /* Repeatedly read bytes int cnt_comp[] until MSBit is 0 */

            do {
                cnt_comp[num_cnt_comps++] = (byte & 0x7f);
            } while ((byte & 0x80) && (mvsGetCh(fp,inbuf,&byte)));

            /* Reconstruct count; start with MSbyte last back to LSbyte first */

            for (j=num_cnt_comps-1; j>=0; j--) {
                cnt <<=7;
                cnt |= cnt_comp[j];
            }
        }

        /* Now output that many instances of curchar in the image buffer */

        for (i=0; i<cnt; i++) {
            *bp++ = curchar;
        }
    } /* End while() */

} /* End mvsDecompressRead() */
