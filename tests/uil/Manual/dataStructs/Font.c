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
static char rcsid[] = "$XConsortium: Font.c /main/4 1995/07/13 20:33:46 drk $"
#endif
#endif

#include "Font.h"
XmStringCharSet get_charset( );

main(argc, argv)
     int argc;
     char *argv[];
{ 	
    int		i,
    		badfont,
    		badfontlist[4],
    		total_errors = 0,
    		total_errors_1 = 0,
    		total_errors_2 = 0;

    char	mrm_err[25];

    String	null_str = "";

    Arg		args[1];
    int		nargs;

/*
 * Initialize Mrm
 */
    MrmInitialize();

/*
 *  Initialize the toolkit.  This call returns the id of the "toplevel" widget.
 */

    toplevel = XtInitialize("Font",		/* application name	   */
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
 * Get display
 */

    dsp = XtDisplay(toplevel);

/*
 * Print header for test results
 */

    fprintf(stdout,"\n\nFont Test Results:\n\n");

/*
 * Part 1
 */

    fprintf(stdout,"Part 1: XLoadQueryFont() Xlib function\n");
    fprintf(stdout,"------           vs\n");
    fprintf(stdout,"        FONT function in UIL.\n\n");

/*
 * Fetch UIL font literals and test against
 * equivalent Xlib-generated fonts
 */
    for(i=0 ; i<=3 ; i++)
    {
	strcpy(error_message, null_str);

	badfont = 0;
	badfontlist[i] = 0;
	
/*
 * Fetch font from UID
 */

	if(MrmFetchLiteral(s_MrmHierarchy,		/* hierarchy id	     */
			   UIL_font_names[i],		/* UIL name for font */
			   dsp,				/* display	     */
			   (XtPointer) &UIL_font[i],		/* font list	     */
			   &type) != MrmSUCCESS)	/* type		     */

	{
	    sprintf(mrm_err, "Can't fetch UIL font %s", UIL_font_names[i]);
	    error_proc(mrm_err);
       badfontlist[i] = 1 ;
	    badfont++;
	}
		
/*
 * Fetch UIL widget
 */

	if(MrmFetchWidget(s_MrmHierarchy,		/* hierarchy id	     */
			   UIL_widget_names[i],		/* UIL name for font */
			   toplevel,			/* display	     */
			   &UIL_widget[i],		/* font list	     */
			   &class) != MrmSUCCESS)	/* type		     */

	{
	    sprintf(mrm_err, "Can't fetch widget %s", UIL_widget_names[i]);
	    error_proc(mrm_err);
	}
	else
	{

/*
 * Get UIL font list from widget
 */

	    nargs = 0;
	    XtSetArg(args[nargs], XmNfontList, &UIL_fontlist[i]); nargs++;
	    XtGetValues(UIL_widget[i], args, nargs);
	}
/*
 * Load X font
 */

	if((X_font = XLoadQueryFont(dsp,			  /* display */
				    X_font_names[i/2])) == NULL) /* font
								    list     */
	{
	    fprintf(stdout, "Can't fetch X font %s", X_font_names[i]);
       badfontlist[i] = 1 ;
	    badfont++;
	}
	else
	{
	    if(i == 3)
	    {
		X_fontlist[i] = XmFontListCreate(X_font,	 /* font     */
						 X_charsets[1]); /* char set */
	    }
	    else
	    {
		X_fontlist[i] = XmFontListCreate(X_font,	 /* font     */
						 X_charsets[0]); /* char set */
	    }
	    
	}

/*
 * Create X font list
 */

	if(!badfont)
	{
	    compare_fonts(UIL_font[i], X_font, &errors, error_message);
	} else {
		total_errors_1 += badfont;
	}
/*
 * If there were any errors, print error messages
 */

	if(errors)
	{
	    if(!total_errors_1)
	    {
		fprintf(stdout,"\nThe following are list(s) of the field(s) ");
		fprintf(stdout,"of the XFontStruct structure which\ndiffer ");
		fprintf(stdout,"between fonts generated by the ");
		fprintf(stdout,"XLoadQueryFont() Xlib function and the\nFONT");
		fprintf(stdout," function in UIL, both using the same font ");
		fprintf(stdout,"name.\n");
	    }

	    fprintf(stdout, "\nTest %d: Font name = %s\n\n", i+1,
		    X_font_names[i/2]);
	
	    fprintf(stdout, "                   \t  Xlib  \t  UIL\n");
	    fprintf(stdout, "Field              \t Value  \t Value\n");
	    fprintf(stdout, "-------------------\t--------\t--------\n\n");

	    fprintf(stdout, "%s\n", error_message);

	    total_errors_1 += errors;
	} 

/*
 * Free fonts
 */

	XFreeFont(dsp, X_font);
	} 
    
/*
 * Print final results for Part 1
 */

    if(total_errors_1)
    {
	total_errors += total_errors_1;
	
	fprintf(stdout, "\nPart 1: Test failed with %d error(s).\n\n",
		total_errors_1);
    }
    else
    {
	fprintf(stdout,"        Test passed.\n\n");
    }

/*
 * Part 2
 */

    fprintf(stdout,"\nPart 2: FONT function in UIL without character set");
    fprintf(stdout," declared\n");
    fprintf(stdout,"------                         vs\n");
    fprintf(stdout,"        FONT function in UIL with character set ");
    fprintf(stdout,"declared\n\n");

/*
 * Compare UIL fonts created both with and without a
 * character set declared.  There should be no difference.
 */

    for(i=0 ; i<= 2 ; i+=2)
    {
	strcpy(error_message, null_str);

/*
 * Only do comparison if both fonts were successfully fetched above
 */

	if(!badfontlist[i] && !badfontlist[i+1])
	{
	    compare_fonts(UIL_font[i], UIL_font[i+1], &errors, error_message);

/*
 * If there were any errors, print error messages
 */

	    if(errors)
	    {
		if(!total_errors_2)
		{
		    fprintf(stdout,"\nThe following are list(s) of the ");
		    fprintf(stdout,"field(s) of the XFontStruct structure ");
		    fprintf(stdout,"which\ndiffer between fonts generated ");
		    fprintf(stdout,"by the FONT function in UIL both with ");
		    fprintf(stdout,"and\nwithout a character set declared.\n");
		}

		fprintf(stdout, "\nTest %d: Font name = %s\n\n", (i+2)/2,
			X_font_names[i/2]);
	
		fprintf(stdout, "                   \tWithout \t  With\n");
		fprintf(stdout, "Field              \tChar Set\tChar Set\n");
		fprintf(stdout, "-------------------\t--------\t--------\n\n");

		fprintf(stdout, "%s\n", error_message);

		total_errors_2 += errors;
	    }
	} else {
		 errors++;
		total_errors_2 += errors;
	}
	}	/* End 'for i' loop */
    
/*
 * Print final results for Part 2
 */

    if(total_errors_2)
    {
	total_errors += total_errors_2;

	fprintf(stdout, "\nPart 2: Test failed with %d error(s).\n\n",
		total_errors_2);
    }
    else
    {
	fprintf(stdout,"        Test passed.\n\n");
    }

/*
 * Part 3
 */

    fprintf(stdout,"\nPart 3: XmFontlistCreate() Xlib function\n");
    fprintf(stdout,"------           vs\n");
    fprintf(stdout,"        FONT function in UIL.\n\n");

/*
 * Compare font lists created by XmFontListCreate to font lists created
 * by the FONT function in UIL and passed back as arguments to a widget
 */

    strcpy(error_message, null_str);

    for(i=0 ; i<= 3 ; i++)
    {

/*
 * Only do comparison if UIL font list was successfully fetched above
 */

	if(!badfontlist[i])
	{
		if(strcmp(get_charset(X_fontlist[i]), get_charset(UIL_fontlist[i])) != 0)
	    {
		errors++;
		
		sprintf(err_msg,"  %1d \t%9s\t%9s\n", i+1,
		get_charset(X_fontlist[i]), get_charset(UIL_fontlist[i]));
		strcat(error_message, err_msg);
	    }
	} else {
		 errors++;
	}
    }

/*
 * If there were any errors, print error messages
 *
 * Print final results for Part 3
 */

    if(errors)
    {
	total_errors += errors;
	
	fprintf(stdout,"\nThe following are the character set names of the");
	fprintf(stdout," XmFontList structures\ngenerated by the ");
	fprintf(stdout,"XmFontListCreate() Xlib function and the FONT");
	fprintf(stdout," function in UIL.\n\n");

	fprintf(stdout, "    \t  Xlib  \t  UIL\n");
	fprintf(stdout, "Test\t Value  \t Value\n");
	fprintf(stdout, "----\t--------\t--------\n\n");

	fprintf(stdout, "%s\n", error_message);

	fprintf(stdout, "\nPart 3: Test failed with %d error(s).\n\n",
		errors);
    }
    else
    {
	fprintf(stdout,"        Test passed.\n\n");
    }

/*
 * Part 4
 */

    fprintf(stdout,"\nPart 4: FONT function in UIL without character set");
    fprintf(stdout," declared\n");
    fprintf(stdout,"------                         vs\n");
    fprintf(stdout,"        FONT function in UIL with character set ");
    fprintf(stdout,"\"iso_latin1\" declared\n\n");

/*
 * Compare font lists created by the FONT function in UIL with the
 * characterset "iso_latin1" declared and with no character set declared
 */

    strcpy(error_message, null_str);

/*
 * Only do comparison if UIL font list was successfully fetched above
 */

    errors = 0;
    
	if(!badfontlist[0] && !badfontlist[1])
	{
		if(strcmp(get_charset(UIL_fontlist[0]),get_charset(UIL_fontlist[1])) != 0)
		{
			errors++;
			sprintf(err_msg,"  1 \t%9s\t%9s\n", get_charset(UIL_fontlist[0]),
			get_charset(UIL_fontlist[1]));
			strcat(error_message, err_msg);
		} 
	} else {
		errors++;
	}

/*
 * If there were any errors, print error messages
 *
 * Print final results for Part 4
 */

    if(errors)
    {
	total_errors += errors;
	
	fprintf(stdout,"\nThe following are the character set names of the");
	fprintf(stdout," XmFontList structures generated\nby the ");
	fprintf(stdout,"FONT function in UIL without a character set ");
	fprintf(stdout,"declared and with the\ncharacter set \"iso_latin1\"");
	fprintf(stdout," declared.\n\n");

	fprintf(stdout, "    \tWithout \t  With\n");
	fprintf(stdout, "Test\tChar Set\tChar Set\n");
	fprintf(stdout, "----\t--------\t--------\n\n");

	fprintf(stdout, "%s\n", error_message);

	fprintf(stdout, "\nPart 4: Test failed with %d error(s).\n\n",
		errors);
    }
    else
    {
	fprintf(stdout,"        Test passed.\n\n");
    }

/*
 * Print error totals
 */

    if(total_errors)
    {
	fprintf(stdout, "\nFont: test failed with %d errors.\n\n",
		total_errors);
    }
    else
    {
	fprintf(stdout, "\nFont: all tests passed.\n\n");
    }

/*
 * Close Mrm Hierarchy
 */

    MrmCloseHierarchy(s_MrmHierarchy);

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

XmStringCharSet get_charset( fontlist)
	XmFontList fontlist;
{
XmFontListEntry f_list_entry;
XmFontContext   *context;
XmStringCharSet charset;
Boolean   font_valid;

	if ( fontlist == NULL ) {
		return NULL;
	}
	context = (XmFontContext *) XtMalloc (sizeof (XmFontContext));
	font_valid = XmFontListInitFontContext(context, fontlist);
	if ( font_valid == False ) {
		return NULL;
	}
	f_list_entry = XmFontListNextEntry(*context);
	charset = XmFontListEntryGetTag(f_list_entry);
	return(charset);

}

