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
static char rcsid[] = "$XConsortium: postSW3.c /main/7 1995/07/14 12:03:32 drk $"
#endif
#endif
/*
 *	file: postSW3.c
 *
 *	Program posting a scrolled window with a Drawing Area child having
 *	an arrow button as *its* child.
 */

#include <testlib.h>


Widget  ScrolledWindow1;
Widget  ArrowB1;
Widget	dialog;


static void postit(w,cad,cld)
Widget w;
XtPointer cad;
XtPointer cld;
{
	XtManageChild(ScrolledWindow1);
	XtManageChild(dialog);
}


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
	Widget		  pb;

    
    CommonTestInit(argc, argv);

	n = 0;
	pb = XmCreatePushButton(Shell1, "pb", args, n);
	XtManageChild(pb);
	XtAddCallback(pb, XmNactivateCallback, postit, NULL);

	n = 0;
	dialog = XmCreateBulletinBoardDialog(Shell1, "BBDialog", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  	n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);  n++;
    XtSetArg(args[n], XmNshadowThickness, 2);  			n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmTOP_LEFT); 	n++;
    XtSetArg(args[n], XmNdefaultPosition, False);		n++;
    XtSetArg(args[n], XmNspacing, 20);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("white"));	n++;
    XtSetArg(args[n], XmNwidth,  300);  			n++;
    XtSetArg(args[n], XmNheight, 300);  			n++;
    ScrolledWindow1 = XmCreateScrolledWindow
				(dialog, "ScrolledWindow1", args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 500);				n++;
    XtSetArg(args[n], XmNheight, 500);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("coral"));	n++;
    XtSetArg(args[n], XmNforeground, CommonGetColor("black"));	n++;
    ArrowB1 = XmCreateArrowButton(ScrolledWindow1, "ArrowButton1", args, n);
    XtManageChild(ArrowB1);

    XtRealizeWidget(Shell1);
 
    XtAppMainLoop(app_context);
}
