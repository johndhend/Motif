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
static char rcsid[] = "$XConsortium: CloseH.c /main/10 1995/07/14 10:46:24 drk $"
#endif
#endif

#include <MrmTest.h> 
#include <testlib.h>

/* 
 * Data for summary
 */

#define NUM_TESTS    4
#define TEST_DESCRIP_LENGTH    	60

struct TestInfo CloseHierarchyInfo[NUM_TESTS] = 
{
    {"Close a valid hierarchy                                     ",
        MrmSUCCESS,	0},
    {"Close an empty hierarchy                                    ",
        MrmBAD_HIERARCHY,	0},
#ifdef	BADTEST
    {"Close a already closed hierarchy                            ",
        MrmBAD_HIERARCHY,	0},
#endif 	/* BADTEST */
    {"Close a garbage hierarchy                                   ",
        MrmBAD_HIERARCHY,	0},
    {"Close a valid hierarchy opened from three files             ",
        MrmSUCCESS,	0},
};
int    CH_info_cnt = 0;

/*
 * External declarations
 */
extern String	summary();

/*
 * Local declarations
 */
FILE	*CH_logfile;
#define	LOGFILE_NAME	"CH_log"

void main (argc,argv)
int argc;
char **argv;
{ 



    Arg	args[4];
    int	nargs;

    XmString	message;

    String	summary_msg;

    MrmHierarchy	OpenHierarchy[3];
    int			emptyhier = 1;
    String		OH_filename_vec[3];
    MrmCount	OH_filename_num = 0;

    char	uidname[3][80];
    int		fetch_return, open_return;
    int		i;


    MrmHierarchy	s_MrmHierarchy;
    MrmType		class;

    char	uidnameMain[80];

    

    String          filename_vec[1];
    MrmCount        filename_num = 0;

    String          testname;



    Widget	test_box,
	        CH_test[8];

    int	        CH_test_cnt = 0;





    CommonTestUilInit(argc,argv);
    MrmInitialize();


     /* 
        * Open the Mrm hierarchy
        */
    testname=argv[0];

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


    

    MrmFetchWidget(
                       s_MrmHierarchy,
                       "test_box",
		       Shell1,
                       &test_box,
                       &class);
    
    XtManageChild(test_box);
    XtRealizeWidget(Shell1);

    CommonPause();

    /*
     * Close a valid hierarchy
     */
    sprintf(uidname[0], "OpenH_vh");
    OH_filename_num = 0;
    OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
    
    OpenHierarchy[0] = NULL;
    open_return = MrmOpenHierarchy(
                               OH_filename_num,
                               OH_filename_vec,
                               NULL,
                               &OpenHierarchy[0]);
    
    if (open_return == MrmSUCCESS)
     {
       CH_test[CH_test_cnt] = NULL;
       fetch_return = MrmFetchWidget(
                               OpenHierarchy[0],
                               "OH_vh",
                               test_box,
                               &CH_test[CH_test_cnt],
                               &class);
       if (fetch_return == MrmSUCCESS)
        {
          XtManageChild(CH_test[CH_test_cnt]);
          CH_test_cnt++;
        }
     }
     CloseHierarchyInfo[CH_info_cnt].actual_return =
                 MrmCloseHierarchy(OpenHierarchy[0]);
     CH_info_cnt++;
    
    /*
     * Close an empty hierarchy
     */
	/* just pass it an address that has junk in it */
     CloseHierarchyInfo[CH_info_cnt].actual_return =
         MrmCloseHierarchy((MrmHierarchy)&emptyhier);
     CH_info_cnt++;

#ifdef    BADTEST
    /*
     * Close a already closed hierarchy
     */

     CloseHierarchyInfo[CH_info_cnt].actual_return =
            MrmCloseHierarchy(OpenHierarchy[0]);
     CH_info_cnt++;
#endif /* BADTEST */
    
    /*
     * Close a garbage hierarchy
     */
     OH_filename_num = 0;
     sprintf(uidname[0], "OpenH_if");
     OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
    
     OpenHierarchy[0] = NULL;
     open_return = MrmOpenHierarchy(
                               OH_filename_num,
                               OH_filename_vec,
                               NULL,
                               &OpenHierarchy[0]);
    
      if (open_return == MrmSUCCESS)
        {    /* This will never happen, not a valid hierarchy */
            CH_test[CH_test_cnt] = NULL;
            fetch_return = MrmFetchWidget(
                               OpenHierarchy[0],
                               "OH_if",
                               test_box,
                               &CH_test[CH_test_cnt],
                               &class);
            if (fetch_return == MrmSUCCESS)
            {
                XtManageChild(CH_test[CH_test_cnt]);
                CH_test_cnt++;
            }
        }
      CloseHierarchyInfo[CH_info_cnt].actual_return =
            MrmCloseHierarchy(OpenHierarchy[0]);
      CH_info_cnt++;
    

      CommonPause();
   
    
    /*
     * Close a valid hierarchy opened from three files
     */
     OH_filename_num = 0;
     sprintf(uidname[0], "OpenH_mf1");
     OH_filename_vec[OH_filename_num] = uidname[0]; OH_filename_num++;
     sprintf(uidname[1], "OpenH_mf2");
     OH_filename_vec[OH_filename_num] = uidname[1]; OH_filename_num++;
     sprintf(uidname[2], "OpenH_mf3");
     OH_filename_vec[OH_filename_num] = uidname[2]; OH_filename_num++;
    
     OpenHierarchy[0] = NULL;
     open_return = MrmOpenHierarchy(
                               OH_filename_num,
                               OH_filename_vec,
                               NULL,
                               &OpenHierarchy[0]);
     if (open_return == MrmSUCCESS)
       {
         CH_test[CH_test_cnt] = NULL;
         fetch_return = MrmFetchWidget(
                            OpenHierarchy[0],
                            "OH_mf1",
                            test_box,
                            &CH_test[CH_test_cnt],
                            &class);
          if (fetch_return == MrmSUCCESS)
            {
                XtManageChild(CH_test[CH_test_cnt]);
                CH_test_cnt++;
            }
         CH_test[CH_test_cnt] = NULL;
         fetch_return = MrmFetchWidget(
                            OpenHierarchy[0],
                            "OH_mf2",
                            test_box,
                            &CH_test[CH_test_cnt],
                            &class);
         if (fetch_return == MrmSUCCESS)
            {
                XtManageChild(CH_test[CH_test_cnt]);
                CH_test_cnt++;
            }
         CH_test[CH_test_cnt] = NULL;
         fetch_return = MrmFetchWidget(
                            OpenHierarchy[0],
                            "OH_mf3",
                            test_box,
                            &CH_test[CH_test_cnt],
                            &class);
         if (fetch_return == MrmSUCCESS)
            {
                XtManageChild(CH_test[CH_test_cnt]);
                CH_test_cnt++;
            }
        }
        CloseHierarchyInfo[CH_info_cnt].actual_return =
            MrmCloseHierarchy(OpenHierarchy[0]);
        CH_info_cnt++;

        CommonPause();
    
        summary_msg = summary(NUM_TESTS,
                      TEST_DESCRIP_LENGTH,
                      CloseHierarchyInfo);

        fprintf (stdout, summary_msg);

        CommonPause();
}
