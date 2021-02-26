/* $XConsortium: RIScale2.c /main/4 1995/07/15 21:09:16 drk $ */
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
/* 
 * Original History:
 *
 * Revision 1.3.2.2  1993/04/27  17:24:48  shobana
 * 	HaL fix for CR 5523
 * 	[1993/04/27  17:24:29  shobana]
 *
 * Revision 1.3  1992/03/13  17:44:26  devsrc
 * 	Converted to ODE
 * 
*/ 
#include <testlib.h>

Widget  Scale1;

void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
    

    XtRealizeWidget(Shell1);

    tcs = XmStringLtoRCreate("Noise Level", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNborderWidth, 5);  n++;
    XtSetArg(args[n], XmNhighlightThickness, 3);  n++;
    /*
    XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);  n++;
    */
    XtSetArg(args[n], XmNshowValue, TRUE);  n++;
    XtSetArg(args[n], XmNvalue, -10);  n++;
    XtSetArg(args[n], XmNmaximum, 0);  n++;
    XtSetArg(args[n], XmNminimum, 100);  n++;
    XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
    XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_TOP);  n++;
    XtSetArg(args[n], XmNtitleString, tcs);  n++;
    XtSetArg(args[n], XmNscaleWidth, 30);  n++;
    XtSetArg(args[n], XmNscaleHeight, 250);  n++;
    XtSetArg(args[n], XmNshadowThickness, 0);  n++;
    XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
    Scale1 = XmCreateScale(Shell1, "Scale1", args, n);
    XtManageChild(Scale1);

    XmStringFree(tcs);

    CommonPause();

    /* test case for PIR 2688 */
    n = 0;
    XtSetArg(args[n], XmNtitleString, &tcs);	n++;
    XtGetValues(Scale1, args, n);

    printf("XmNtitleString = %s\n", CommonCsToRs(tcs));
/* Fix for CR 5523 */
    XmStringFree(tcs);
/* End Fix for CR 5523 */
    fflush(stdout);

    /* end of test case for PIR 2688 */

    CommonPause();

    tcs = XmStringLtoRCreate("Decibels", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNmaximum, 0);  n++;
    XtSetArg(args[n], XmNminimum, 100);  n++;
    XtSetArg(args[n], XmNvalue, -10);  n++;
    XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_BOTTOM);  n++;
    XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);  n++;
    XtSetArg(args[n], XmNscaleWidth, 500); n++;
    XtSetArg(args[n], XmNscaleHeight, 2000); n++;
    XtSetArg(args[n], XmNtitleString, tcs);  n++;
    XtSetValues(Scale1, args, n);

    XmStringFree(tcs);

    CommonPause();

    XtDestroyWidget(Scale1);

    CommonPause();

    XtAppMainLoop(app_context);
}
