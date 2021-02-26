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
static char rcsid[] = "$TOG: TrackingLocM1.c /main/9 1999/11/22 18:16:36 jff $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include <X11/cursorfont.h>

/* forward refs */
static void TrackCB();

Widget  Dialog;
Widget 	PanedW;
Widget	Toggle1, Toggle2, Toggle3;
Widget  List;
Widget	Push1, Push2, Push3, Push4;
Widget  Arrow1, Arrow2, Arrow3;
Widget 	w_id;

int   	cur_num = 1;
char 	begin[50] = "Help has arrived (via XmTrackingLocate) for ";


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    Pixel         colorVal;
    XmString      list_items[2];
    

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 400); n++;
    XtSetArg (args[n], XmNheight, 500); n++;
    XtSetArg (args[n], XmNmappedWhenManaged, False); n++;
    XtSetValues(Shell1, args, n);
    
    XtRealizeWidget(Shell1);

    n = 0;
    XtSetArg (args[n], XmNautoUnmanage, False); n++;
    XtSetArg (args[n], XmNgeometry, "+0+0"); n++;
    Dialog = XmCreateBulletinBoardDialog (Shell1, "Dialog", args, n);


    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 20);			n++;
    XtSetArg(args[n], XmNmarginHeight, 20);			n++;
    PanedW = XmCreatePanedWindow(Dialog, "PanedWindow", args, n);
    XtManageChild(PanedW);

#ifndef BESTCASE                            /* to get us around P2986 */
    XtManageChild (Dialog);
#endif

    n = 0;
    Push1 = XmCreatePushButton(PanedW, "Push1", args, n);
    XtManageChild(Push1);

    n = 0;
    Push2 = XmCreatePushButton(PanedW, "Push2", args, n);
    XtManageChild(Push2);

    n = 0;
    Push3 = XmCreatePushButton(PanedW, "Push3", args, n);
    XtManageChild(Push3);

    n = 0;
    Toggle1 = XmCreateToggleButton(PanedW, "Toggle1", args, n);
    XtManageChild(Toggle1);

    n = 0;
    Toggle2 = XmCreateToggleButton(PanedW, "Toggle2", args, n);
    XtManageChild(Toggle2);

    n = 0;
    Toggle3 = XmCreateToggleButton(PanedW, "Toggle3", args, n);
    XtManageChild(Toggle3);

    list_items[0] = XmStringCreateSimple("List item 1");
    list_items[1] = XmStringCreateSimple("List item 2");

    n = 0;
    XtSetArg(args[n], XmNx, 5), n++;
    XtSetArg(args[n], XmNy, 50), n++;
    XtSetArg(args[n], XmNitems, list_items), n++;
    XtSetArg(args[n], XmNitemCount, XtNumber(list_items)), n++;
    XtSetArg(args[n], XmNvisibleItemCount, 5), n++;
    List = XmCreateScrolledList(PanedW, "List", args, n);
    XtManageChild(List);

    n = 0;
    Arrow1 = XmCreateArrowButton(PanedW, "Arrow1", args, n);
    XtManageChild(Arrow1);

    n = 0;
    Arrow2 = XmCreateArrowButton(PanedW, "Arrow2", args, n);
    XtManageChild(Arrow2);

    n = 0;
    Arrow3 = XmCreateArrowButton(PanedW, "Arrow3", args, n);
    XtManageChild(Arrow3);

    tcs = XmStringCreateLtoR("Push To Turn on Tracking Locate", 
			XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNbackground, CommonGetColor("Yellow"));  	n++;
    XtSetArg(args[n], XmNlabelString, tcs);			n++;
    Push4 = XmCreatePushButton(PanedW, "Push4", args, n);
    XtManageChild(Push4);

    XtAddCallback(Push4, XmNactivateCallback, TrackCB, (XtPointer) 0);

    XmStringFree(tcs);

#ifdef BESTCASE
    XtManageChild (Dialog);
#endif

    CommonPause();
    CommonPause();
    CommonPause();
    CommonPause();

    XtRemoveCallback(Push4, XmNactivateCallback, TrackCB, (XtPointer) 0);
    XtAddCallback(Push4, XmNactivateCallback, TrackCB, (XtPointer) 1);

    CommonPause();


    XtAppMainLoop(app_context);
}


static void TrackCB(w, client_data, call_data)
    Widget   w;
    XtPointer  client_data;
    XtPointer  call_data;
{
    Cursor 	cursor;
	

    switch (cur_num) {
	case 1: 	cursor = XCreateFontCursor (display, XC_pirate);
			break;
	case 2:		cursor = XCreateFontCursor (display, XC_heart);
			break;
	case 3:		cursor = XCreateFontCursor (display, XC_man);
			break;
	case 4:		cursor = XCreateFontCursor (display, XC_shuttle);
			break;
	default:	cursor = XCreateFontCursor (display, XC_arrow);
			break;
    };
    w_id = XmTrackingLocate(Dialog, cursor, FALSE);

    /* support two modes. Help() for regular testing; XtCallActionProc
       illustrates PIR 3133 */

    if ((long) client_data == 0)
       Help(w_id);
    else {
      if (w_id)
        XtCallActionProc (w_id, "Help", 
			  ((XmAnyCallbackStruct *)call_data)->event, NULL, 0);
    }

    cur_num++;
}


Help(widget)
Widget widget;
{
    int 	n = 0;
    Arg 	args[5];
    char	to[150];
    XmString	tcs;
    Widget 	MessageB;

    if (widget == NULL)
      return NULL;
    else {
       strcpy(to, begin);
       strcat(to, XtName(widget));

       tcs = XmStringCreateLtoR(to, XmSTRING_DEFAULT_CHARSET);
       n = 0;
       XtSetArg(args[n], XmNx, 0);			n++;
       XtSetArg(args[n], XmNy, 0);			n++;
       XtSetArg(args[n], XmNmessageString, tcs);	n++;
       MessageB = XmCreateInformationDialog(Shell1, "MessageB", args, n);
       XtManageChild(MessageB);
    }
}
