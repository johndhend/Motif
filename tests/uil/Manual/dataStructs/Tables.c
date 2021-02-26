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
static char rcsid[] = "$XConsortium: Tables.c /main/4 1995/07/13 20:34:37 drk $"
#endif
#endif

#include <stdio.h>

#include "Tables.h"

main(argc, argv)
     int argc;
     char *argv[];
{ 	
    char	mrm_err[50];

/*
 * Initialize Mrm
 */
    MrmInitialize();

/*
 *  Initialize the toolkit.  This call returns the id of the "toplevel" widget.
 */

    toplevel = XtInitialize("Simple",		/* application name	   */
			    "genericclass",	/* application class	   */
			    NULL, 0,		/* options		   */
			    &argc, argv);	/* command line parameters */

/*
 *  Open the Mrm hierarchy
 */

    if(MrmOpenHierarchy(filename_num,		/* number of files	*/
			filename_vec,		/* files		*/
			NULL,			/* os_ext_list (null)	*/
			&s_MrmHierarchy)	/* ptr to returned id	*/
       != MrmSUCCESS) 
    {
	error_proc("Can't open hierarchy\n");
    }

/*
 * Register the names of the callback routines with Mrm
 */
    
    if(MrmRegisterNames(reglist,	/* list of names	*/
			reglist_num)	/* number of names	*/
       != MrmSUCCESS)
    {
	error_proc("Can't register names\n");
    }

/*
 * Get display
 */

    dsp = XtDisplay(toplevel);

/*
 * Fetch widget which sends a table to its callback routine
 */

    for(ndx=0 ; ndx<NUM_TESTS ; ndx++)
    {

/*
 * Print header for test results
 */

	fprintf(stdout,"\n\n%s Test Results:\n\n",
		test_result_headers[ndx]);

	if(MrmFetchWidget(s_MrmHierarchy,
			  UIL_widget_names[ndx],
			  toplevel,
			  &UIL_widgets[ndx],
			  &class) != MrmSUCCESS)
	{
	    sprintf(mrm_err, "Can't fetch UIL widget %s",
		    UIL_widget_names[ndx]);
	    error_proc(mrm_err);
	}
	else
	{
	    XtCallCallbacks(UIL_widgets[ndx], XmNactivateCallback, NULL);
	}

/*
 * Print error summary
 */

	if(errors[ndx])
	{
	    fprintf(stdout,"\n%s test failed with %d errors\n\n",
		    test_result_headers[ndx], errors[ndx]);
	}
	else
	{
	    fprintf(stdout,"\n%s test passed.\n\n",
		    test_result_headers[ndx]);
	}
    }

/*
 * Close Mrm Hierarchy
 */

    MrmCloseHierarchy(s_MrmHierarchy);
}

/*
 * Callback routine to receive integer table
 */

void integer_table_proc(w, UIL_integer_table, reason)
     Widget		w;
     int		*UIL_integer_table;
     unsigned long	*reason;
{
    int			i;

/*
 * Print test result header
 */

    fprintf(stdout,"Integer Table\t Actual \tExpected\n");
    fprintf(stdout,"   Element   \t Value  \t Value  \tError\n");
    fprintf(stdout,"-------------\t--------\t--------\t-----\n");

    
    for(i=0 ; i<=4 ; i++)
    {
	fprintf(stdout,"      %1d      \t%8d\t%8d",i+1, UIL_integer_table[i],
		X_integer_table[i]);

	if(UIL_integer_table[i] != X_integer_table[i])
	{
	    errors[ndx]++;
	    
	    fprintf(stdout,"\t  *\n");
	}
	else
	{
	    fprintf(stdout,"\n");
	}
    }
}

/*
 * Callback routine to receive compound string table
 */

void compound_string_table_proc(w, UIL_compound_string_table, reason)
     Widget		w;
     XmString		*UIL_compound_string_table;
     unsigned long	*reason;
{
    XmStringContext	context;
    XmStringCharSet	charset;
    XmStringDirection	direction;
    Boolean		separator;
    char		*next_string;
    char                *the_whole_string=NULL;
    int			i;
    Boolean             valid_segment;

/*
 * Print test result header
 */

    fprintf(stdout,"Compound String\t         Actual \t        Expected\n");
    fprintf(stdout," Table Element \t         Value  \t         Value  \tError\n");
    fprintf(stdout,"---------------\t        --------\t        --------\t-----\n");

    for(i=0 ; i<=2 ; i++)
    {
	XmStringInitContext(&context, UIL_compound_string_table[i]);

	if (the_whole_string != NULL)
	    {
	    XtFree (the_whole_string);
	    the_whole_string = NULL;
	    valid_segment = True;
	    }

	valid_segment = XmStringGetNextSegment(context,
			   &next_string,
			   &charset,
			   &direction,
			   &separator);
	while (valid_segment)
	    {

		if (the_whole_string == NULL)
		    {
		    the_whole_string = XtCalloc (1, strlen(next_string) + 1);
		    strcpy (the_whole_string, next_string);
		    }
		else
		    {
		    the_whole_string = XtRealloc (the_whole_string, 
			          strlen (the_whole_string) +
				  strlen (next_string) + 1);
		    strcat (the_whole_string, next_string);
		    }
		XtFree (next_string);
	    valid_segment = XmStringGetNextSegment(context,
			       &next_string,
			       &charset,
			       &direction,
			       &separator);
	    }

	fprintf(stdout,"       %1d       \t%16s\t%16s",i+1, the_whole_string,
		X_compound_string_table[i]);

	if(strcmp(the_whole_string, X_compound_string_table[i]) != 0)
	{
	    errors[ndx]++;
	    
	    fprintf(stdout,"\t  *\n");
	}
	else
	{
	    fprintf(stdout,"\n");
	}

	XmStringFreeContext(context);
    }
}

/*
 * Callback routine to receive asciz string table
 */

void asciz_string_table_proc(w, UIL_asciz_string_table, reason)
     Widget		w;
     String		*UIL_asciz_string_table;
     unsigned long	*reason;
{
    int			i;
    
/*
 * Print test result header
 */

    fprintf(stdout,"Asciz String   \t         Actual \t        Expected\n");
    fprintf(stdout,"Table Element  \t         Value  \t         Value  \tError\n");
    fprintf(stdout,"-------------  \t        --------\t        --------\t-----\n");

    for(i=0 ; i<=3 ; i++)
    {
	fprintf(stdout,"       %1d       \t%16s\t%16s",i+1,
		UIL_asciz_string_table[i], X_asciz_string_table[i]);

	if(strcmp(UIL_asciz_string_table[i], X_asciz_string_table[i]) != 0)
	{
	    errors[ndx]++;
	    
	    fprintf(stdout,"\t  *\n");
	}
	else
	{
	    fprintf(stdout,"\n");
	}
    }
}

/*
 * Callback routine to receive font table
 */

void font_table_proc(w, UIL_font_table, reason)
     Widget		w;
     XmFontList		UIL_font_table;
     unsigned long	*reason;
{
    XFontStruct		*X_font;
    XmFontContext	context;
    XmStringCharSet     char_set;
    XFontStruct		*font;
    
    int			i,
    			font_errors = 0;

    XmFontListInitFontContext(&context, UIL_font_table);
    
/*
 * Print test result header
 */

    fprintf(stdout,"Font Table\n");
    fprintf(stdout," Element  \t       Font Name\tError\n");
    fprintf(stdout,"----------\t       ---------\t-----\n");

    for(i=0 ; i<=2 ; i++)
    {
	fprintf(stdout,"      %1d     \t%16s",i+1, X_font_names[i]);

	if((X_font = XLoadQueryFont(dsp,			 /* display  */
				    X_font_names[i])) == NULL)	/* font list */
	{
	    fprintf(stdout, "Can't fetch X font %s", X_font_names[i]);
	}
	else
	{
	    XmFontListGetNextFont(context, &char_set, &font);
	    compare_fonts(font, X_font, &font_errors, NULL);
	    UIL_font_table++;
	}
	

	if(font_errors)
	{
	    errors[ndx]++;
	    
	    fprintf(stdout,"\tFonts differ\n");
	}
	else
	{
	    fprintf(stdout,"\n");
	}
    }
}

/*
 * Callback routine to receive identifier data type
 */

void identifier_proc(w, ident_tag, reason)
     Widget		w;
     int		ident_tag;
     unsigned long	*reason;
{
    int		i,
    		nargs = 0;

    short	ident_resource = 0;

    Arg	args[1];
    
    fprintf(stdout, "                                   \tActual\tExpected\n");
    fprintf(stdout, "Identifier Use                     \tValue \t Value  \t");
    fprintf(stdout, "Error\n");
    fprintf(stdout, "--------------                     \t------\t--------\t");
    fprintf(stdout, "-----\n");

    i = 0;

/*
 * Identifier as widget resource value
 */

    nargs = 0;
    XtSetArg(args[nargs], XmNx, &ident_resource); nargs++;
    XtGetValues(w, args, nargs);
    
    fprintf(stdout, "%35s\t%6d\t%8d", ident_type[i], ident_resource,
	    expected_ident[i]);

    if(ident_resource != expected_ident[i])
    {
	errors[ndx]++;
	
	fprintf(stdout, "\t  *\n");
    }
    else
    {
	fprintf(stdout, "\n");
    }

    i++;
    
/*
 * Identifier as callback tag value
 */
    
    fprintf(stdout, "%35s\t%6d\t%8d", ident_type[i], ident_tag,
	    expected_ident[i]);

    if(ident_tag != expected_ident[i])
    {
	errors[ndx]++;
	
	fprintf(stdout, "\t  *\n");
    }
    else
    {
	fprintf(stdout, "\n");
    }

}

/*
 * Error handling
 */

void error_proc(error_string)
     String	error_string;
{
    fprintf(stdout,"Mrm error: %s\n", error_string);
    fflush(stdout);
}
