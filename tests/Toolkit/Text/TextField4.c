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
static char rcsid[] = "$XConsortium: TextField4.c /main/6 1995/07/13 19:35:51 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Arg args[MAX_ARGS];

void main (argc, argv)
int argc;
char **argv;
{
	Widget TextF1 = NULL;
	Widget TextF2 = NULL;
	Widget Text1 = NULL;
	Widget Label1, Label2, Label3;
	Widget BBoard1;
	int n = 0;
	XmString tmp_string;

	/*  initialize toolkit  */
	CommonTestInit(argc, argv);

	n = 0;
	BBoard1 = XmCreateBulletinBoard(Shell1, "BBoard1", args, n);
	XtManageChild(BBoard1);


	n = 0;
        tmp_string = XmStringCreate("TextField1 - resizeWidth: False",
		XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNlabelString, tmp_string); n++;
	Label1 = XmCreateLabel(BBoard1, "Label1", args, n);
	XtManageChild(Label1);
        XmStringFree (tmp_string);

	n = 0;
	XtSetArg(args[n], XmNresizeWidth, False); n++;
	XtSetArg(args[n], XmNcolumns, 30); n++;
	XtSetArg(args[n], XmNy, 30); n++;
	TextF1 = XmCreateTextField(BBoard1, "TextF1", args, n);
	XtManageChild(TextF1);


	n = 0;
        tmp_string = XmStringCreate("TextField2 - resizeWidth: True", 
		                    XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNy, 80); n++;
	XtSetArg(args[n], XmNlabelString, tmp_string); n++;
	Label2 = XmCreateLabel(BBoard1, "Label2", args, n);
	XtManageChild(Label2);
        XmStringFree (tmp_string);

	n = 0;
	XtSetArg(args[n], XmNresizeWidth, True); n++;
	XtSetArg(args[n], XmNcolumns, 30); n++;
	XtSetArg(args[n], XmNy, 100); n++;
	TextF2 = XmCreateTextField(BBoard1, "TextF2", args, n);
	XtManageChild(TextF2);


	n = 0;
        tmp_string = XmStringCreate("Text1 - resizeWidth: True", 
                         	     XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNy, 140); n++;
	XtSetArg(args[n], XmNlabelString, tmp_string);
		
	Label3 = XmCreateLabel(BBoard1, "Label3", args, n);
	XtManageChild(Label3);
        XmStringFree (tmp_string);

	n = 0;
	XtSetArg(args[n], XmNresizeWidth, True); n++;
	XtSetArg(args[n], XmNcolumns, 30); n++;
	XtSetArg(args[n], XmNy, 160); n++;
	Text1 = XmCreateText(BBoard1, "Text1", args, n);
	XtManageChild(Text1);

	n = 0;
	XtSetArg(args[n], XmNallowShellResize, False); n++;
	XtSetValues(Shell1, args, n);


	XtRealizeWidget(Shell1);


	/* test case for PIR 2914, see .dat */
	CommonPause();

	CommonPause();

	/* test case for PIR 2898, see .dat */
	CommonPause();
	
	XtAppMainLoop(app_context);
}
