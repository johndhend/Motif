
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
static char rcsid[] = "$XConsortium: UilCmd.c /main/11 1995/07/14 09:32:29 drk $"
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
**      Command line interpreter for the
**
**--
**/

/*
**
**  INCLUDE FILES
**
**/


#include "UilDefI.h"
#include "UilCmdDef.h"


/*
**
**  GLOBAL DECLARATIONS
**
**/

externaldef(uil_comp_glbl) cmd_command_line_type Uil_cmd_z_command = {
	NULL, 	/* *ac_source_file */
	NULL, 	/* *ac_resource_file */
	NULL, 	/* *ac_listing_file */
	0, 	/* include_dir_count */
	NULL, 	/* **ac_include_dir */
	1, 	/* v_listing_file */
	1, 	/* v_resource_file */
	1, 	/* v_show_machine_code */
	1, 	/* v_report_info_msg */
	1, 	/* v_report_warn_msg */
	1, 	/* v_parse_tree */
	1, 	/* v_issue_summary */
	0, 	/* status_update_delay */
	NULL, 	/* (*message_cb)() */
	NULL, 	/* *message_data */
	NULL,	/* (*status_cb)() */
	NULL,	/* *status_data */
	1,	/* v_use_setlocal */
	NULL,	/* *ac_database */
	1	/* v_database */
};



/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This procedure parses the command line and places the
**	results of the parse in the global structure "Uil_cmd_z_command".
**
**  FORMAL PARAMETERS:
**
**      l_arg_count:	number of command arguments
**	rac_arg_value:	array of pointers to null terminated character strings
**			each of which is one of the command line arguments
**
**  IMPLICIT INPUTS:
**
**      none
**
**  IMPLICIT OUTPUTS:
**
**      Uil_cmd_z_command:	respository for command line info
**
**  FUNCTION VALUE:
**
**      void
**
**  SIDE EFFECTS:
**
**      Uil_cmd_z_command is set
**
**--
**/
void	cmd_decode_command_line( l_arg_count, rac_arg_value )
int 	l_arg_count;
char 	*rac_arg_value[ ];

{
    static char	    *include_list	[Uil_k_max_include_dir_count];
    int	i;

    Uil_cmd_z_command.ac_source_file = NULL;
    Uil_cmd_z_command.ac_resource_file = NULL;
    Uil_cmd_z_command.ac_listing_file = NULL;
    Uil_cmd_z_command.include_dir_count = 0;
    Uil_cmd_z_command.ac_include_dir = (char **)include_list;
    Uil_cmd_z_command.v_resource_file = TRUE;
    Uil_cmd_z_command.v_listing_file = FALSE;
    Uil_cmd_z_command.v_show_machine_code = FALSE;
    Uil_cmd_z_command.v_report_info_msg = TRUE;
    Uil_cmd_z_command.v_report_warn_msg = TRUE;
    Uil_cmd_z_command.v_parse_tree = FALSE;
    Uil_cmd_z_command.v_use_setlocale = FALSE;
    Uil_cmd_z_command.status_update_delay = 0;
    Uil_cmd_z_command.message_cb = (Uil_continue_type(*)())NULL;
    Uil_cmd_z_command.status_cb = (Uil_continue_type(*)())NULL;
    Uil_cmd_z_command.ac_database = NULL;
    Uil_cmd_z_command.v_database = FALSE;

#if debug_version
    uil_v_dump_tokens = FALSE;
    uil_v_dump_symbols = FALSE;
#endif

    /* traverse the options on the command line */

    for (i = 1;  i < l_arg_count;  i++)
    {
	/* check for an output file  */

	if ( strcmp("-o", rac_arg_value[ i ]) == 0 )
	{
	    /* the next argument is the output file name  */

	    /* check next field is not an option */

            if (((i+1) >= l_arg_count) ||
                ( '-' == rac_arg_value[ i+1 ][ 0 ] ))
	    {
		diag_issue_diagnostic
			( d_miss_opt_arg, 
			  diag_k_no_source, diag_k_no_column,
			  rac_arg_value[ i ],
			  "output file"
			);
		continue;
	    }

	    if (Uil_cmd_z_command.ac_resource_file == NULL)
	        Uil_cmd_z_command.ac_resource_file = rac_arg_value[ i+1 ];
	    else
		diag_issue_diagnostic
		    ( d_dupl_opt, 
		      diag_k_no_source, diag_k_no_column,
		      rac_arg_value[ i ]
		    );
	    i = i + 1;
	}
	    
	/* check for a binary database file */

	else if ( strcmp("-wmd", rac_arg_value[ i ]) == 0 )
	{
	    /* the next argument is the binary database file name  */

	    /* check next field is not an option */

            if (((i+1) >= l_arg_count) ||
                ( '-' == rac_arg_value[ i+1 ][ 0 ] ))
	    {
		diag_issue_diagnostic
			( d_miss_opt_arg, 
			  diag_k_no_source, diag_k_no_column,
			  rac_arg_value[ i ],
			  "binary database file"
			);
		continue;
	    }

	    if (!Uil_cmd_z_command.v_database)
	    {
	        Uil_cmd_z_command.v_database = TRUE;
	        Uil_cmd_z_command.ac_database = rac_arg_value[ i+1 ];
	    }
	    else
		diag_issue_diagnostic
		    ( d_dupl_opt, 
		      diag_k_no_source, diag_k_no_column,
		      rac_arg_value[ i ]
		    );
	    i = i + 1;
	}

	/* check for an listing file */

	else if ( strcmp("-v", rac_arg_value[ i ]) == 0 )
	{
	    /* the next argument is the listing file name  */

	    /* check next field is not an option */

            if (((i+1) >= l_arg_count) ||
                ( '-' == rac_arg_value[ i+1 ][ 0 ] ))
	    {
		diag_issue_diagnostic
			( d_miss_opt_arg, 
			  diag_k_no_source, diag_k_no_column,
			  rac_arg_value[ i ],
			  "listing file"
			);
		continue;
	    }

	    if (!Uil_cmd_z_command.v_listing_file)
	    {
	        Uil_cmd_z_command.v_listing_file = TRUE;
	        Uil_cmd_z_command.ac_listing_file = rac_arg_value[ i+1 ];
	    }
	    else
		diag_issue_diagnostic
		    ( d_dupl_opt, 
		      diag_k_no_source, diag_k_no_column,
		      rac_arg_value[ i ]
		    );
	    i = i + 1;
	}
	    
	/* check for the machine code option */

	else if ( strcmp("-m", rac_arg_value[ i ]) == 0 )
	{
	        Uil_cmd_z_command.v_show_machine_code = TRUE;
	}
	    
	/* check if warnings are to be supressed */

	else if ( strcmp("-w", rac_arg_value[ i ]) == 0 )
	{
	        Uil_cmd_z_command.v_report_info_msg = FALSE;
	        Uil_cmd_z_command.v_report_warn_msg = FALSE;
	}

	/* check if setlocale is to be enabled */

	else if ( strcmp("-s", rac_arg_value[ i ]) == 0 )
	{
	  Uil_cmd_z_command.v_use_setlocale = TRUE;
	}
	
	/* check for an unexpected option */

	else if ( '-' == rac_arg_value[ i ][ 0 ] )
	{

	/* check for an include directory */

	    if ( 'I' == rac_arg_value[ i ][ 1 ] )
	    {
		if (Uil_cmd_z_command.include_dir_count < Uil_k_max_include_dir_count)
		    
		    include_list[Uil_cmd_z_command.include_dir_count++] = 
			& rac_arg_value[i] [2];
		else
		    diag_issue_diagnostic
		        ( d_too_many_dirs, 
		          diag_k_no_source, diag_k_no_column,
		          rac_arg_value[ i ], Uil_k_max_include_dir_count
		        );
	    } else
	    {
		diag_issue_diagnostic
		    ( d_unknown_opt, 
		      diag_k_no_source, diag_k_no_column,
		      rac_arg_value[ i ]
		    );
	    }
	}

	/* assume it is a UIL source file specification
	 * validation of the file spec is done when file is opened */

	else
	{
	    if (Uil_cmd_z_command.ac_source_file == NULL)
	       Uil_cmd_z_command.ac_source_file = rac_arg_value[ i ];
	    else
		diag_issue_diagnostic
		    ( d_add_source, 
		      diag_k_no_source, diag_k_no_column,
		      rac_arg_value[ i ]
		    );
	}
    }

    /*
    **	Check for a source file - otherwise issue a diagnostic.
    */

    if (Uil_cmd_z_command.ac_source_file == NULL)
	diag_issue_diagnostic
	    ( d_no_source, diag_k_no_source, diag_k_no_column );

    if (Uil_cmd_z_command.ac_resource_file == NULL)
	{
        Uil_cmd_z_command.ac_resource_file = XtMalloc (strlen ("a.uid") + 1);
        strcpy (Uil_cmd_z_command.ac_resource_file,"a.uid");
        }

    /*
    **	Machine code listing only makes sense if listing is set.
    */
    
    Uil_cmd_z_command.v_show_machine_code =
        ( Uil_cmd_z_command.v_listing_file & 
	  Uil_cmd_z_command.v_show_machine_code);
}



