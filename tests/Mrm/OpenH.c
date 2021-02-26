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
static char rcsid[] = "$XConsortium: OpenH.c /main/10 1995/07/14 10:49:58 drk $"
#endif
#endif

#include <testlib.h>
#include <MrmTest.h> 

/* 
 * Data for summary
 */

#define NUM_TESTS		9
#define TEST_DESCRIP_LENGTH	60

struct TestInfo OpenHierarchyInfo[NUM_TESTS] = 
{
    {"Open a valid hierarchy with complete relative pathname      ",
				MrmSUCCESS,	0},
    {"Open a valid hierarchy from three different files           ",
				MrmSUCCESS,	0},
    {"Open a valid hierarchy using $UIDPATH with 1 element        ",
				MrmSUCCESS,	0},
    {"Open a valid hierarchy using $UIDPATH with >1 elements      ",
				MrmSUCCESS,	0},
    {"Open a nonexistent filename                                 ",
				MrmNOT_FOUND,	0},
    {"Open an invalid file (not a .uid file)                      ",
				MrmFAILURE,	0},
    {"Open a file/hierarchy by referring to it WITH a .uid suffix ",
				MrmSUCCESS,	0},
    {"Open a hierarchy from three files with one bad .uid file    ",
				MrmNOT_FOUND,	0},
    {"Open a hierarchy from three files with one nonexistent file ",
				MrmNOT_FOUND,	0},
};
int			OH_info_cnt = 0;

/*
 * External declarations
 */

extern String		summary();

/*
 * Local declarations
 */


#define	MEM_LOOP_CNT	10

Widget		test_box,
		OH_test[8];
int		OH_test_cnt = 0;


FILE	*OH_logfile;
#define	LOGFILE_NAME	"OH_log"

void main (argc,argv)
int argc;
char **argv;
{ 	



        Arg		args[4];
        int		nargs;

        XmString	message;

        String	summary_msg;

        MrmHierarchy	OpenHierarchy[3];
        String	        OH_filename_vec[3];
        MrmCount	OH_filename_num = 0;

        char	        uidname[3][80];
        int		fetch_return;
        int		i;


        MrmHierarchy	s_MrmHierarchy;
        MrmType		class;


        char            uidnameMain[80];

	String          filename_vec[1];
	MrmCount        filename_num = 0;

        String          testname;
       



        CommonTestUilInit (argc,argv);
	MrmInitialize();

	testname=argv[0];

       /* 
	* Open the Mrm hierarchy
	*/

          sprintf(uidnameMain, "%s.uid", testname);
          filename_vec[filename_num] = uidnameMain; filename_num++;

          if(MrmOpenHierarchy(filename_num,       /* number of files      */
                              filename_vec,       /* files                */
                              NULL,               /* os_ext_list (null)   */
                              &s_MrmHierarchy)    /* ptr to returned id   */
          != MrmSUCCESS) 
         {
            printf("Can't open hierarchy\n");
         }


	/*
	 * Fetch valid test_box widget
	 */
         test_box = NULL;
         MrmFetchWidget (s_MrmHierarchy,
		        "test_box",
		        Shell1,
		        &test_box,
		        &class);
	
	
         XtManageChild(test_box);
	 XtRealizeWidget(Shell1);

	/*
	 * Open a valid hierarchy with a full local path name
	 */
	 sprintf(uidname[0], "OpenH_vh");
	 OH_filename_num = 0;
	 OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
	 OpenHierarchy[0] = NULL;
	 OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
	
	  if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
	      {
		OH_test[OH_test_cnt] = NULL;
		fetch_return = MrmFetchWidget(
					       OpenHierarchy[0],
					       "OH_vh",
					        test_box,
						&OH_test[OH_test_cnt],
						&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
	/*
	 * Open a valid hierarchy from three different files
	 */
		OH_filename_num = 0;
		sprintf(uidname[0], "OpenH_mf1");
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
		sprintf(uidname[1], "OpenH_mf2");
		OH_filename_vec[OH_filename_num] = uidname[1]; OH_filename_num++;
		sprintf(uidname[2], "OpenH_mf3");
		OH_filename_vec[OH_filename_num] = uidname[2]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
	
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_mf1",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_mf2",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_mf3",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
    
    CommonPause();
	
	/*
	 * Open a valid hierarchy using the environment variable UIDPATH to
	 * help decipher the name.
	 */

	/* set up the $UIDPATH var */
		putenv("UIDPATH=./OpenHLang/%U\
%S");			

		sprintf(uidname[0], "OpenH_vhev");
		OH_filename_num = 0;
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_vhev",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;

	/*
	 * Open a valid hierarchy using the environment variable UIDPATH to
	 * help decipher the name.  UIDPATH has more than one element in it.
	 */

  	 /* set up the $UIDPATH var */
		putenv("UIDPATH=./OpenHLang/%U:./OpenHLang/%U\
%S");	

		sprintf(uidname[0], "OpenH_evl");
		OH_filename_num = 0;
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_vhevl",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
		putenv("UIDPATH=%U");	/* set up the $UIDPATH var */
	
	/*
	 * Open a nonexistent filename
	 */
		sprintf(uidname[0], "OpenH_nef");
		OH_filename_num = 0;
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
	/*
	 * Open an invalid file (not a .uid file)
	 */
		sprintf(uidname[0], "OpenH_if");
		OH_filename_num = 0;
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
	/*
	 * Open a valid file/hierarchy by referring to it WITH a .uid suffix 
	 * on the filename.
	 */
		sprintf(uidname[0], "OpenH_vhws.uid");
		OH_filename_num = 0;
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidget(
							OpenHierarchy[0],
							"OH_vhws",
							test_box,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
	/*
	 * Open a hierarchy from three files with one bad .uid file
	 */
		OH_filename_num = 0;
		sprintf(uidname[0], "OpenH_mf1");
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
		sprintf(uidname[1], "OpenH_if");
		OH_filename_vec[OH_filename_num] = uidname[1]; OH_filename_num++;
		sprintf(uidname[2], "OpenH_mf3");
		OH_filename_vec[OH_filename_num] = uidname[2]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
	
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			message = XmStringCreateLtoR("OH_mf1 *A* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_mf1",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			message = XmStringCreateLtoR("OH_if *A* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_if",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			message = XmStringCreateLtoR("OH_mf3 *A* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_mf3",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
	/*
	 * Open a hierarchy from three files with one nonexistent file
	 */
		OH_filename_num = 0;
		sprintf(uidname[0], "OpenH_mf1");
		OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
		sprintf(uidname[1], "OpenH_nef");
		OH_filename_vec[OH_filename_num] = uidname[1]; OH_filename_num++;
		sprintf(uidname[2], "OpenH_mf3");
		OH_filename_vec[OH_filename_num] = uidname[2]; OH_filename_num++;
	
		OpenHierarchy[0] = NULL;
		OpenHierarchyInfo[OH_info_cnt].actual_return = MrmOpenHierarchy(
							OH_filename_num,
							OH_filename_vec,
							NULL,
							&OpenHierarchy[0]);
	
		if (OpenHierarchyInfo[OH_info_cnt].actual_return == MrmSUCCESS)
		{
			/* 
			 * For each widget, change the label string and the 
			 * position so that it is visually distinguished from 
			 * the other instances of the same widget.
			 */
			message = XmStringCreateLtoR("OH_mf1 *B* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			XtSetArg(args[nargs], XmNtopOffset, 62); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_mf1",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			message = XmStringCreateLtoR("OH_nef *B* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			XtSetArg(args[nargs], XmNtopOffset, 87); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_nef",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			message = XmStringCreateLtoR("OH_mf3 *B* is completed.  ",
							XmSTRING_DEFAULT_CHARSET);
			nargs = 0;
			XtSetArg(args[nargs], XmNlabelString, message); nargs++;
			XtSetArg(args[nargs], XmNtopOffset, 112); nargs++;
			OH_test[OH_test_cnt] = NULL;
			fetch_return = MrmFetchWidgetOverride(
							OpenHierarchy[0],
							"OH_mf3",
							test_box,
							NULL,
							args,
							nargs,
							&OH_test[OH_test_cnt],
							&class);
			if (fetch_return == MrmSUCCESS)
			{
				XtManageChild(OH_test[OH_test_cnt]);
				OH_test_cnt++;
			}
			XmStringFree(message);

			MrmCloseHierarchy(OpenHierarchy[0]);
		}
		OH_info_cnt++;
	
           CommonPause();
	
		summary_msg = summary(NUM_TESTS,
				      TEST_DESCRIP_LENGTH,
				      OpenHierarchyInfo);

		fprintf (stdout, summary_msg);

           CommonPause();


}
