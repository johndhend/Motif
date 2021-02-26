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
static char rcsid[] = "$XConsortium: Values.c /main/4 1995/07/13 20:35:28 drk $"
#endif
#endif

/*      This Test will produce failures. The reason for this is that    */
/*      indentifiers and values pass different types. Identifiers       */
/*      pass Pointer to an integer and values pass the integer value    */
/*	to MrmFetchLiteral. Pir 2089.					*/

#include <stdio.h>

#include <Mrm/MrmAppl.h>

#define EXPECTED_VALUE		1
#define EXPECTED_IDENTIFIER	1

/*
 * Name of uid file
 */

String		filename_vec[] =
{
    "Values.uid"
};

MrmCount	filename_num =
(sizeof(filename_vec) / sizeof(filename_vec[0]));

/*
 * Convenience routine
 */

void		error_proc();
void            create_proc_iden();
void            create_proc_value();

/*
 * Local declarations
 */

MrmHierarchy	s_MrmHierarchy;
MrmType		class;
MrmCode		type;

Widget		toplevel = NULL;
Widget          widgetmain = NULL;

Display		*dsp;
Colormap	cmap;

int		return_value;

/* MRMRegisterArg idList; */
static MrmRegisterArg reglist[] = {
  {"CBdata0", (caddr_t)1},
  {"create_proc_iden", (caddr_t)create_proc_iden},
  {"create_proc_value", (caddr_t)create_proc_value}
};

static int reglist_num = (sizeof (reglist) / sizeof (reglist[0]));

main(argc, argv)
     int argc;
     char *argv[];
{ 	
    int	i,
    	errors = 0;

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
     *		Register all Mrm functions
     */	


    if (MrmRegisterNames (reglist, reglist_num)
			!= MrmSUCCESS)
			{
			    printf("Can't register names\n");
			    exit(1);
			}

/*
 * Get display, colormap
 */

    dsp = XtDisplay(toplevel);

    cmap = DefaultColormap(dsp, DefaultScreen(dsp));

/*
 * Print header for test results
 */

    fprintf(stdout,"\n\nValue Test Results:\n\n");
    fprintf(stdout,"         Test\t  Identifier \t    Value    \tStatus\n");
    fprintf(stdout,"         ----\t-------------\t-------------\t-----\n");

/*
 * Fetch UIL Boolean literals and test against equivalent Xt value
 */
	if(MrmFetchLiteral(s_MrmHierarchy,
			   "CBdata1",
			   dsp,
			   (XtPointer ) &return_value,
			   &type) != MrmSUCCESS)
	{
	    error_proc("Can't fetch the value literal");
	}



        if (MrmFetchWidget (s_MrmHierarchy,
			"S_MAIN_WIDGET",
			toplevel,
			&widgetmain,
			&class)
			!= MrmSUCCESS)
			{
			    printf("Can't fetch interface\n");
			    exit(1);
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


void create_proc_value(w, client_data, call_data)
Widget w;
caddr_t client_data, call_data;

{

int x;

x =  *(int *)client_data;

fprintf (stdout, "%13s\t%13d\t%13d\t%s", "Comparison", EXPECTED_VALUE, x, 
                          ((EXPECTED_VALUE == x) ? "Passed\n" : "Failed\n"));

}

void create_proc_iden(w, client_data, call_data)
Widget w;
caddr_t client_data, call_data;

{

int x;

x = (int) client_data;

fprintf (stdout, "%13s\t%13d\t%13d\t%s", "Comparison", EXPECTED_IDENTIFIER, x, 
                       ((EXPECTED_IDENTIFIER == x) ? "Passed\n" : "Failed\n"));

}

