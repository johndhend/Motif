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
static char rcsid[] = "$XConsortium: PushHashBits.c /main/7 1995/07/14 11:44:53 drk $"
#endif
#endif
/***********************************************************************
  	@(#)PushHashBits.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/21/90 SJS add to sccs
	Calls:

	Summary:
            Used in GetStateHash to append a long value (bits) of arbitrary
            precision (num_bits) onto an array of bytes (hash) of arbitrary
            precision.  

          INPUTS
            hash - list of bytes to append more bits to
            byte_num - current appendable byte number (0...) in hash byte list
            bit_num - current bit to append next (0...7)
            bits - long value of arbitrary precision to append onto hash list
            num_bits - precision of bits

          OUTPUTS
            hash - altered by appending bits
            byte_num - altered to represent new current byte num
            bit_num - altered to represent new current bit num

          RETURNS
            nothing
************************************************************************/

#include "vislib.h"

void mvsPushHashBits(hash,byte_num,bit_num,bits,num_bits)
char hash[];
int *byte_num;
int *bit_num;
long bits;
int num_bits;
{
    int i;

    for (i=0; i<num_bits; i++) {
        hash[*byte_num] <<= 1;
        hash[*byte_num] |= bits & 1;
        *bit_num = (*bit_num) + 1;
        if (*bit_num == 8) {
            *bit_num = 0;
            *byte_num = *byte_num + 1;
        }
        bits >>= 1;
    }

} /* End mvsPushHashBits() */
