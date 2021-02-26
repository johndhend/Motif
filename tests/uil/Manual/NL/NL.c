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
static char rcsid[] = "$XConsortium: NL.c /main/4 1995/07/13 20:31:34 drk $"
#endif
#endif


#include <stdio.h>
#include <Mrm/MrmAppl.h>

typedef struct {
  char *valid_string1;
  char *valid_string2;
  char *uid_path;
  char *mrm_file1;
  char *mrm_file2;
  int   mrm_file_count;
} AppData, *pAppData;


int def_mrm_count = 1;

XtResource myResources[] = {
  {"validString1","ValidString",XtRString,sizeof(char *),
   XtOffset(pAppData,valid_string1),XtRString,(caddr_t)"string1"},
  {"validString2","ValidString",XtRString,sizeof(char *),
   XtOffset(pAppData,valid_string2),XtRString,(caddr_t)"string2"},
  {"uidPath","UidPath",XtRString,sizeof(char *),
   XtOffset(pAppData,uid_path),XtRString,(caddr_t)"%U\
%S"},
  {"mrmFile1","MrmFile",XtRString,sizeof(char *),
   XtOffset(pAppData,mrm_file1),XtRString,(caddr_t)"file1"},
  {"mrmFile2","MrmFile",XtRString,sizeof(char *),
   XtOffset(pAppData,mrm_file2),XtRString,(caddr_t)"file2"},
  {"mrmFileCount","MrmFileCount",XtRInt,sizeof(int),
   XtOffset(pAppData,mrm_file_count),XtRInt,(caddr_t)&def_mrm_count}
};

XrmOptionDescRec options[] = {
  {"-valid1","*validString1",XrmoptionSepArg,NULL},
  {"-valid2","*validString2",XrmoptionSepArg,NULL},
  {"-uidpath","*uidPath",XrmoptionSepArg,NULL},
  {"-file1","*mrmFile1",XrmoptionSepArg,NULL},
  {"-file2","*mrmFile2",XrmoptionSepArg,NULL},
  {"-filecount","*mrmFileCount",XrmoptionSepArg,NULL}
};

void main (argc, argv)
int argc;
char **argv;
{
   AppData myData;
   Widget toplevel;
   MrmCount filecount;
   MrmHierarchy	s_MrmHierarchy;
   MrmCode	type;
   String        UIL_string_literal;
   char *filenames[2];
   char envstring[120];
   Display *dsp;

   MrmInitialize();
   toplevel = XtInitialize (argv[0], "PathnameTest", options, 
			    XtNumber(options), &argc, argv);

   /* get app resources */
   XtGetApplicationResources(toplevel, &myData,
			     myResources, XtNumber(myResources),
			     NULL, 0);

   filecount = myData.mrm_file_count;
   filenames[0] = myData.mrm_file1;
   filenames[1] = myData.mrm_file2;

   dsp = XtDisplay(toplevel);

   sprintf(envstring,"UIDPATH=%s",myData.uid_path);
   putenv(envstring);

   if(myData.mrm_file_count==1){
     printf("uid path: %s\nvalid string: %s\nmrm filename: %s \n",
	  myData.uid_path,
	  myData.valid_string1,
	  myData.mrm_file1);
   }
   if(myData.mrm_file_count==2){
     printf("uid path: %s\nvalid string1: %s\nmrm filename1: %s \nvalid string2: %s\nmrm filename2: %s \n",
	  myData.uid_path,
	  myData.valid_string1,
	  myData.mrm_file1,
	  myData.valid_string2,
	  myData.mrm_file2);
   }
   if(MrmOpenHierarchy(filecount,/* number of files	*/
		       filenames,	 /* files		*/
		       NULL,		 /* os_ext_list (null)	*/
		       &s_MrmHierarchy) /* ptr to returned id	*/
      != MrmSUCCESS) {
     fprintf(stdout,"Open hierarchy FAILED\n");
     exit(1);
   }

   fprintf(stdout,"Open hierarchy call passed.\n");

   /* Fetch string literal to verify that correct uid file was opened */
   if(MrmFetchLiteral(s_MrmHierarchy,
		      "string1",
		      dsp,
		      (XtPointer)&UIL_string_literal,
		      &type) != MrmSUCCESS){
     fprintf(stdout,"Fetch literal FAILED\n");
     exit(2);
   }
   if(strcmp(UIL_string_literal, myData.valid_string1) != 0)
     fprintf(stdout,"Fetch literal FAILED: fetched string is %s\n",
	     UIL_string_literal);
   else
     fprintf(stdout,"Fetch literal passed with fetched string %s\n",
	     UIL_string_literal);


   if(filecount==2){
     /* Fetch string literal to verify that correct uid file was opened */
     if(MrmFetchLiteral(s_MrmHierarchy,
			"string2",
			dsp,
			(XtPointer)&UIL_string_literal,
			&type) != MrmSUCCESS){
       fprintf(stdout,"Second fetch literal FAILED\n");
       exit(3);
     }
     if(strcmp(UIL_string_literal, myData.valid_string2) != 0)
       fprintf(stdout,"Second fetch FAILED: fetched string is %s\n",
	       UIL_string_literal);
     else
       fprintf(stdout,"Second fetch passed with fetched string %s\n",
	       UIL_string_literal);
   }

   MrmCloseHierarchy(s_MrmHierarchy);
}



