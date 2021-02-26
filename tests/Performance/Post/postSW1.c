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
static char rcsid[] = "$XConsortium: postSW1.c /main/7 1995/07/14 12:03:11 drk $"
#endif
#endif
/*
 *	file: postSW1.c
 *
 *	Program posting a scrolled window with no children.
 */

#include	<testlib.h>

Widget dialog;
Widget SW;
Widget horizontal;
Widget vertical;

static void postit(w,cad,cld)
Widget w;
XtPointer cad;
XtPointer cld;
{
	XtManageChild(SW);
	XtManageChild(dialog);
}

main(argc, argv) 
int argc;
char *argv[];
{
	Widget pb;
	Arg args[20];
	int n;

    CommonTestInit(argc, argv);
    
	
	n = 0;
	pb = XmCreatePushButton(Shell1, "pb", args, n);
	XtManageChild(pb);
	XtAddCallback(pb, XmNactivateCallback, postit, NULL);

	n = 0;
	XtSetArg(args[n], XmNwidth, 100); n++;
	XtSetArg(args[n], XmNheight, 100); n++;
	dialog = XmCreateBulletinBoardDialog(Shell1, "dialog", args, n);

	n = 0;
	XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED); n++;
	XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC); n++;
	XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE); n++;
	SW = XmCreateScrolledWindow(dialog, "SW", args, n);

	n = 0;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	horizontal = XmCreateScrollBar(SW, "Horizontal", args, n);
	XtManageChild(horizontal);
	n = 0;
	XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
	vertical = XmCreateScrollBar(SW, "Vertical", args, n);
	XtManageChild(vertical);

	n = 0;
	XtSetArg(args[n], XmNhorizontalScrollBar, horizontal); n++;
	XtSetArg(args[n], XmNverticalScrollBar, vertical); n++;
	XtSetValues(SW, args, n);

	XtRealizeWidget(Shell1);

	XtAppMainLoop(app_context);
}

