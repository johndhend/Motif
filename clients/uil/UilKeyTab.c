
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: UilKeyTab.c /main/11 1995/07/14 09:34:29 drk $"
#endif
#endif



/*
*  (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */

/*
**++
**  FACILITY:
**
**      User Interface Language Compiler (UIL)
**
**  ABSTRACT:
**
**      This module contains the keyword table used by the lexical analyzer
**	to look up the keywords in the UIL.
**
**--
**/


/*
**
**  INCLUDE FILES
**
**/

#include "UilDefI.h"


/*
**
**  DEFINE and MACRO DEFINITIONS
**
**/


/*
**
**  EXTERNAL VARIABLE DECLARATIONS
**
**/


/*
**
**  GLOBAL VARIABLE DECLARATIONS
**
**/


/*
**
**  OWN VARIABLE DECLARATIONS
**
**/

/*    Keyword table pointer.    */

static key_keytable_entry_type * key_keytable_ptr;


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**	This routine searches for a symbol in the compiler's keyword table.
**	There are two arguments to the routine, the length of the symbol and
**      the address of the start of the symbol.  The routine returns the
**	address of the keyword entry found, or a NULL pointer if the
**	symbol is not found in the table.
**
**	The search for the symbol is case sensitive depending upon the
**	keytable binding that was established by the key_initialize routine.
**
**	The require file UilKeyTab.h defines and initializes the keyword
**	tables.  It is built automatically from other files, thus it should
**	not be hand editted.
**
**  FORMAL PARAMETERS:
**
**	symbol_length.rl.v : 	length of symbol to look up
**	symbol_ptr.ra.v : 	address of symbol to look up
**
**  IMPLICIT INPUTS:
**
**      key_keytable_ptr		: current keyword table
**
**  IMPLICIT OUTPUTS:
**
**      none
**
**  FUNCTION VALUE:
**
**	NULL		: if the symbol is not in the keyword table
**	otherwise	: the address of the keyword table entry for
**			  the specified symbol.
**
** SIDE EFFECTS:
**
**	none
**
**--
**/
key_keytable_entry_type *
	key_find_keyword (symbol_length, symbol_ptr)

unsigned int	symbol_length;
char		* symbol_ptr;

{
    
    int
	lower_limit,
	upper_limit;
    
/*    Check the arguments.    */

    if (symbol_length > key_k_keyword_max_length)
	return NULL;

/*    Initialize region to search.    */
    
    lower_limit = 0;
    upper_limit = key_k_keyword_count-1;
    
/*    Perform binary search on keyword index.    */
    
    do {
	int		mid_point, result;

	key_keytable_entry_type * keyword_entry_ptr;

	mid_point = (lower_limit + upper_limit) >> 1;	/* divide by 2 */

	keyword_entry_ptr = & key_keytable_ptr [mid_point];

	result = strcmp (symbol_ptr, keyword_entry_ptr -> at_name);

	if (result == 0) {
	    return keyword_entry_ptr;		/*    Found keyword.    */
	} else if (result < 0) {
	    upper_limit = mid_point - 1;	/*    Search lower half.    */
	} else {
	    lower_limit = mid_point + 1;	/*    Search upper half.    */
	}

    } while (lower_limit <= upper_limit);

/*    If we fall out of the bottom of the loop, symbol was not found.    */

    return NULL;

}

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**	This routine initializes the keyword lookup facility.  It can be
**	called multiple times during a single compilation.  It must be called
**	at least once before the keyword table is accessed.
**
**  FORMAL PARAMETERS:
**
**	none
**
**  IMPLICIT INPUTS:
**
**      uil_v_case_sensitive	: case sensitive switch, determines which
**				: keyword table to use.
**
**  IMPLICIT OUTPUTS:
**
**      key_keytable_ptr	: pointer to the keyword table to
**				  use for keyword lookups.
**
**  FUNCTION VALUE:
**
**	none
**
** SIDE EFFECTS:
**
**	none
**
**--
**/
void
	key_initialize ()

{

/*    Use the correct keyword table based on the global case
      sensitivity.   */

    if (uil_v_case_sensitive) {
	key_keytable_ptr = key_table;
    } else {
	key_keytable_ptr = key_table_case_ins;
    }

}    

