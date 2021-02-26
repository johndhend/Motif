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
static char rcsid[] = "$XConsortium: mvsAssertion.c /main/7 1995/07/14 11:18:49 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsAssertion.c	1.11.1.1	Date:1/22/91
  	Author: SJS
	History:
	   04/13/90 SJS create
	   08/07/90 SJS add Failure counting in behavior
	   09/23/90 SJS add check for same assertion
	   11/13/90 PSN print label ASSERT in the beginning of each assertion 
			line being printed
	   11/19/90 PSN print different assertion messages for test/create test

	Calls:

	Summary:
		This file contains functions that add an assertion to
	the current assertion set and that clear the set of assertions.
	The assertion contains the Page reference and a short description
	of what is currently being validated. The global assertion arrays
	holds the pointers to each assertion that applies to the current
	validation. On a failure, the contents of this array are then
	printed out. To avoid multiple copies of assertions being given
	on related failures, the assertion count is cleared when a
	failure occurs.

************************************************************************/
#include <AutoMessages.h>
#include "mvslib.h"

#define MAX_ASSERTS_PER_VALIDATION 32
static mvsAssertCnt=0;
static char *mvsAssertArray[MAX_ASSERTS_PER_VALIDATION];

/***********************************************************************
   This function adds the string/assertion into the array of assertions.
   These assertions are printed out if a part of the validation fails.
***********************************************************************/
void mvsAssertion(assertion)
char *assertion;
{
    int i;

    if(mvsAssertCnt >= MAX_ASSERTS_PER_VALIDATION) {
        AutoMessage(_AutoMessages[WARNMSG125]);
    }
    else {
        for(i=0; i<mvsAssertCnt; i++) {
            if(assertion == mvsAssertArray[i]) /* Assertion already done */
            return;
        }
        mvsAssertArray[mvsAssertCnt] = assertion;
        mvsAssertCnt++;
    }
} /* End mvsAssertion() */


/***********************************************************************
    This function zeros the assertion count. This signifies the beginning
   of a new validation set with new assertions to be filled in.
***********************************************************************/
void mvsClearAsserts()
{
    mvsAssertCnt = 0;
} /* End mvsClearAsserts() */


/***********************************************************************
    This function prints out the list of assertions associated with
   the current validation.
***********************************************************************/
void mvsFailAssert()
{
    int i;

    for(i=0; i<mvsAssertCnt; i++) {
        if(mvsInBehavior)
           msg("    ASSERT: %s\n", mvsAssertArray[i]);
	else
	   msg("    %s\n", mvsAssertArray[i]);
    }

    if(mvsInBehavior) {
        mvsFailCnt++;
    }
    mvsClearAsserts();

} /* End mvsFailAssert() */
