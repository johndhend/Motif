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
static char rcsid[] = "$XConsortium: ScrollWin4.c /main/10 1995/07/13 19:49:47 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>

Widget DrawingArea1;
Widget ScrolledWindow1;
Widget ArrowB1, ArrowB2;
Widget vert, horiz;
Widget Frame1;

static void actCB(Widget w, XtPointer client_data,
	XtPointer call_data)
{
	printf("Activate Callback made for %s\n", (char *)client_data);
}

void main(argc, argv)
int argc;
char **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    
    CommonTestInit(argc, argv);

#ifdef	MOTIF1_1
    n = 0;
    XtSetArg(args[n], XmNwidth, 10); n++;
    XtSetArg(args[n], XmNheight, 10); n++;
    XtSetValues(Shell1, args, n);
#endif
    XtRealizeWidget(Shell1);

    n = 0;
    Frame1 = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame1);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  	n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);  n++;
    XtSetArg(args[n], XmNshadowThickness, 2);  			n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmTOP_LEFT); 	n++;
    XtSetArg(args[n], XmNspacing, 20);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("white"));	n++;
    XtSetArg(args[n], XmNwidth,  300);  			n++;
    XtSetArg(args[n], XmNheight, 300);  			n++;
    ScrolledWindow1 = XmCreateScrolledWindow(Frame1,
	"ScrolledWindow1", args, n);

    XtRealizeWidget(ScrolledWindow1);
    XtManageChild(ScrolledWindow1);

/* test case for PIR 4276 */
/* 
 * Removed explicit calls to set traversalOn to True
 * that were added at the beginning of 1.2 - shouldn't
 * need them.
 */
/* end of test case for PIR 4276 */

    n = 0;
    DrawingArea1 = XmCreateDrawingArea
				(ScrolledWindow1, "DrawingArea", args, n); 
    XtManageChild(DrawingArea1);

    n = 0;
    XtSetArg(args[n], XmNwidth, 250);				n++;
    XtSetArg(args[n], XmNheight, 250);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("coral"));	n++;
    XtSetArg(args[n], XmNforeground, CommonGetColor("black"));	n++;
    ArrowB1 = XmCreateArrowButton(DrawingArea1, "ArrowButton1", args, n);
    XtManageChild(ArrowB1);

    XtAddCallback(ArrowB1, XmNactivateCallback, actCB, 
		  (XtPointer) "ArrowB1");

    n = 0;
    XtSetArg(args[n], XmNy, 260);				n++;
    XtSetArg(args[n], XmNwidth, 250);				n++;
    XtSetArg(args[n], XmNheight, 250);				n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("violet"));	n++;
    XtSetArg(args[n], XmNforeground, CommonGetColor("black"));	n++;
    XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);		n++;
    ArrowB2 = XmCreateArrowButton(DrawingArea1, "ArrowButton2", args, n);
    XtManageChild(ArrowB2);

    XtAddCallback(ArrowB2, XmNactivateCallback, (XtCallbackProc) actCB, 
		  (XtPointer) "ArrowB2");
 
    CommonPause();  

    n = 0;
    XtSetArg(args[n], XmNwidth, 500);			n++;
    XtSetArg(args[n], XmNheight, 500);			n++;
    XtSetValues(ArrowB1, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 500);			n++;
    XtSetArg(args[n], XmNheight, 500);			n++;
    XtSetArg(args[n], XmNy, 510);			n++;
    XtSetValues(ArrowB2, args, n);			

    CommonPause();  

    XtUnmanageChild(ArrowB1);

    CommonPause();

    XtUnmanageChild(ArrowB2);
    XtUnmanageChild(DrawingArea1);

    CommonPause();

    XtManageChild(DrawingArea1);
    XtManageChild(ArrowB1);
    XtManageChild(ArrowB2);
  
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 175);		n++;
    XtSetArg(args[n], XmNheight, 175);		n++;
    XtSetValues(ArrowB1, args, n);

    XtSetArg(args[n], XmNy, 185);		n++;
    XtSetValues(ArrowB2, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 125);		n++;
    XtSetArg(args[n], XmNheight, 125);		n++;
    XtSetValues(ScrolledWindow1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 250);		n++;
    XtSetArg(args[n], XmNheight, 250);		n++;
    XtSetValues(ScrolledWindow1, args, n);

    n = 0;
    XtSetArg(args[n], XmNwidth, 100);		n++;
    XtSetArg(args[n], XmNheight, 100);		n++;
    XtSetValues(ArrowB1, args, n);

    XtSetArg(args[n], XmNy, 110);		n++;
    XtSetValues(ArrowB2, args, n);

    CommonPause();

    XtUnmapWidget(DrawingArea1);

    CommonPause();

    XtMapWidget(DrawingArea1);

    CommonPause();

    /* test case for PIR 3580 */
    n = 0;
    XtSetArg(args[n], XmNwidth, 300);           n++;
    XtSetArg(args[n], XmNheight, 300);          n++;
    XtSetValues(ArrowB1, args, n);

    XtSetArg(args[n], XmNy, 310);		n++;
    XtSetValues(ArrowB2, args, n);

    n = 0;
    XtSetArg(args[n], XmNverticalScrollBar, &vert);		n++;
    XtSetArg(args[n], XmNhorizontalScrollBar, &horiz);		n++;
    XtGetValues(ScrolledWindow1, args, n);

    n = 0;
    XtSetArg(args[n], XmNtraversalOn, False);	n++;
    XtSetValues(vert, args, n);
    XtSetValues(horiz, args, n);

    CommonPause();

    /* end of test case for PIR 3580 */


    XtAppMainLoop(app_context);
}
