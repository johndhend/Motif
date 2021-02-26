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
static char rcsid[] = "$XConsortium: CommandLine.c /main/10 1995/07/14 11:57:59 drk $"
#endif
#endif
#include "testlib.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#if defined(__STDC__)
#include <stdlib.h>		/* for malloc */
#include <unistd.h>
#endif

#define DEFAULT_FONT    "fixed"
#define TEST_FONT       "fixed"
#define PAUSE_LEN       60
#define USER_DATA_LEN   64

extern Boolean   startup_time;		        /* Measure startup time ?? */
extern Boolean   startup_exit;		        /* Measure startup time
						   and exit ?? */

Boolean          instructions = True;		/* Use instructions?? */
char             *UserData;		        /* Passable string data */
char             *instruct_file_name;           /* Alternate instruction file */
char             *instruct_file_name_orig;      /* Alternate instruction file */
int              pause_len = PAUSE_LEN;		/* Width of MessageBox */
char             test_font[MAX_FONT_LEN];	/* Font for MessageBox */
char             default_font[MAX_FONT_LEN];	/* Default Font for failures */
char		 *TestName;			/* Name of this test */
char		 *CompleteTestName;			/* Complete Name of this test */


/*************************************************************************
*									 *
*	Name:		CommonUsage()				     	 *
*									 *
*	Purpose:	This function will print to stdout the current   *
*			flags that are valid for the test suite 	 *
*									 *
*	Returns:	Nothing						 *
*									 *
*	Current Flags:							 *
*			-l  : Disables Message Box explanations of test  *
*			-I  : Read in alternate instruction file. The    *
*			      Current file read is <test_name>.dat 	 *
*			-h  : Prints the usage message		         *
*			-w  : Controls the width of the Message Box	 *
*			-u  : User Data. Input that can be given to be   *
*			      used by testers programs.			 *
*			-f  : Default Font. Specify a font you would     *
*			      like to use if your request for a font     *
*			      does not succeed (font is not available).  *
*			-p  : MessageBox font. Specify the font you wish *
*			      the instruction's MessageBox to be.	 *
*			-s  : Measure startup time.                      *
*			-z  : Measure startup time and exit.             *
*									 *
*************************************************************************/

void CommonUsage(char *test_name)

{
    fprintf(stdout, 
	    "Usage: %s:\n", test_name);
    fprintf(stdout,
	    "          [-I <instruction_file_name>] [-l <no_instructions>]\n");
    fprintf(stdout,
	    "          [-w <width_of_instructions>] [-u <string_user_data>]\n");
    fprintf(stdout,
	    "          [-f <default_font>] [-p <pause_instructions_font>]\n");
    fprintf(stdout,
	    "          [-help] [-s] [-z] [X Options]\n");

}


/*************************************************************************
*									 *
*	Name:		CommonGetOptions()				 *
*									 *
* 	Purpose:	This function will extract from the command all  *
*			options used by the test suite and will set all  *
*			appropriate flags for those argumennts. All      *
*			arguments that are not valid for the test suite  *
*			are passed on so that X can properly act on 	 *
*			them. This routine will also set the instruction *
*			file name to be used, User Data, help flag, and  *
*			width of the Message Box used for intructions.	 *
*									 *
*	Current Flags:							 *
*			-l  : Disables Message Box explanations of test  *
*			-I  : Read in alternate instruction file. The    *
*			      Current file read is <test_name>.dat 	 *
*			-h  : Prints the usage message		         *
*			-w  : Controls the width of the Message Box	 *
*			-u  : User Data. Input that can be given to be   *
*			      used by testers programs.			 *
*			-f  : Default Font. Specify a font you would     *
*			      like to use if your request for a font     *
*			      does not succeed (font is not available).  *
*			-p  : MessageBox font. Specify the font you wish *
*			      the instruction's MessageBox to be.	 *
*			-s  : Measure startup time.                      *
*			-z  : Measure startup time and exit.             *
*									 *
*	Returns:	Nothing						 *
*									 *
*************************************************************************/
/* globals */

extern char *optarg;             /* supplied by getopt */
extern int optind, opterr;

void  CommonGetOptions (int *argc, char **argv)

{ 
     int c;
     char 	*char_val;
     Boolean    name_given = False;
     Boolean 	test_font_used = False;
     Boolean 	default_font_used = False;
     int	fd_stdout, fd_stderr, ret;
     static char 	test_name[MAX_FILE];
#ifdef REGRESSION
     static char 	complete_test_name[MAX_FILE];
	int	argc_count;
	int	arg_index = 0;
#endif


     static int errflag = 0;

     /* initializations */

     instructions = True;
     pause_len = 0;
     UserData = NULL;
     instruct_file_name = NULL;
     startup_time = False;

     opterr = 0;            /* disable automatic warnings */

#ifdef REGRESSION
	 argc_count = *argc;
     strcpy (complete_test_name, argv[0]);
	 arg_index = 1;
	 while (arg_index < argc_count) {
		strcat (complete_test_name, " ");
		strcat (complete_test_name, argv[arg_index]);
		arg_index++;
	 }
     CompleteTestName = complete_test_name;
#endif

     strcpy (test_name, argv[0]);
     TestName = test_name;

     if (*argc > 1) {
       while ((c = getopt
		(*argc, argv, "szalhrmcTWC:D:V:S:O:w:u:f:p:I:")) != EOF) {

       switch (c) {

	  case 'p':
			if (strlen (optarg) >= MAX_FONT_LEN) {
			  printf ("Error: file name %s too long\n",
				  optarg);
			  errflag++;
			  break;
			}
			test_font_used = True;
			strcpy (test_font, optarg);
			break;

	  case 'I':
			if (strlen (optarg) >= (MAX_FILE - 1)) {
			  printf ("Error: file name %s too long\n",
				  optarg);
			  errflag++;
			  break;
			}
			name_given = True;
			instruct_file_name = (char *) malloc((sizeof (char)) *
							     MAX_FILE);
			strcpy (instruct_file_name, optarg);
			break;

	  case 'f':	if (strlen (optarg) >= MAX_FONT_LEN) {
			  printf ("Error: file name %s too long\n",
				  optarg);
			  errflag++;
			  break;
			}
			default_font_used = True;
			strcpy (default_font, optarg);
			break;

	  case 'u':	if (strlen (optarg) >= USER_DATA_LEN) {
			  printf ("Error: file name %s too long\n",
				  optarg);
			  errflag++;
			  break;
			}
			UserData = (char *) malloc((sizeof(char))
						    * USER_DATA_LEN);
			strcpy (UserData, optarg);
			break;
	  case 'l':
     			instructions = False;
               		break;
	  case 'h':
    			CommonUsage(test_name);
     			exit(0);
			break;

          case 'w':
			pause_len = atoi (optarg);
			if (!pause_len) {
			  printf 
			    ("Illegal or zero value provided for width.\n");
			  printf ("Using default %d.\n, PAUSE_LEN");
			  pause_len = PAUSE_LEN;
			}
			break;

	  case 's': 
			startup_time = True;
			break;

	  case 'z': 
			startup_time = True;
			startup_exit = True;
			break;

	 /* for all these automation-only switches, do nothing */
          case 'a':
          case 'r':
          case 'm':
          case 'c':
	  case 'W':
	  case 'D':
          case 'T':
          case 'C':
          case 'S':
	  case 'V':
          case 'O':     break;

          } /*switch */
       if (optind >= *argc) break;
     } /* while getopt */
   } /* if *argc >= 1 */
     
    if (errflag) {
      CommonUsage(test_name);
      exit (1);
    }
     		
    if (!name_given) {
	instruct_file_name = (char *) malloc((sizeof (char)) *
			      MAX_FILE);
        strcpy (instruct_file_name, test_name);
        strcat (instruct_file_name, ".Dat");

        instruct_file_name_orig = (char *) malloc((sizeof (char)) *
                              MAX_FILE);
        strcpy (instruct_file_name_orig, test_name);
        strcat (instruct_file_name_orig, ".dat");
    }

    if (!default_font_used) 
	strcpy(default_font, DEFAULT_FONT);

    if (!test_font_used) 
	strcpy(test_font, TEST_FONT);

    if (pause_len == 0)
	pause_len = PAUSE_LEN;

#ifdef DEBUG
    printf ("Using pause width %d\n", pause_len);
#endif

}
