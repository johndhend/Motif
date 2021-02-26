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
static char rcsid[] = "$XConsortium: Scale1.c /main/6 1995/07/13 19:10:45 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>

Widget  Scale1;



void  main(argc, argv)
    int     argc;
    char  **argv;
{
    Boolean       trace = False;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    XmFontList newfontlist;
    XFontStruct *newfont;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
    

    XtRealizeWidget(Shell1);

    n = 0;

    /* test case for PIR 2808 - use Italics font to show bug */
    XtSetArg(args[n], XmNfontList, CommonGetFontList("helvo18")); n++;
    /* end of test case for PIR 2808 */

    XtSetArg(args[n], XmNborderWidth, 5);  n++;
    XtSetArg(args[n], XmNhighlightThickness, 3);  n++;
    tcs = XmStringLtoRCreate("Decibels", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNtitleString, tcs);  n++;
    XtSetArg(args[n], XmNshowValue, TRUE);  n++;
    XtSetArg(args[n], XmNscaleWidth, 30);  n++;
    XtSetArg(args[n], XmNscaleHeight, 250);  n++;
    XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
    Scale1 = XmCreateScale(Shell1, "Scale1", args, n);
    XtManageChild(Scale1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 400); n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetValues(Shell1, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 140);  n++;
    XtSetArg(args[n], XmNheight, 250);  n++;
    XtSetArg(args[n], XmNdecimalPoints, 2);  n++;
    XtSetArg(args[n], XmNminimum, -100); n++;
    XtSetArg(args[n], XmNmaximum, 100); n++;
    XtSetValues(Scale1, args, n);

    
    CommonPause();

    /* test case for PIR 2808 - use Italics font to show bug HORIZONTAL */
    n = 0;
    XtSetArg(args[n], XmNdecimalPoints, 0);  n++;
    XtSetArg(args[n], XmNminimum, 0); n++;
    XtSetArg(args[n], XmNmaximum, 100); n++;
    XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
    XtSetValues(Scale1, args, n);

    CommonPause();

    XtAppMainLoop(app_context);
}
