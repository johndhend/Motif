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
static char rcsid[] = "$XConsortium: TrackingLocM2.c /main/6 1995/07/13 18:42:17 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include <X11/cursorfont.h>

/* forward refs */
static void Track();

Widget	BB;
Widget	Push1, Push2, Push3;
Widget	Push4, Push5, Push6;
Widget  submenu, menu, menubar;
Widget  submenu2, menu2;

Boolean confine = False;
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
    
    CommonTestInit(argc, argv);

    n = 0;

    BB = XmCreateBulletinBoard(Shell1, "BulletinBoard", args, n);
    XtManageChild(BB);

    XtAddCallback(BB, XmNhelpCallback, Track, NULL);

    n = 0;
    menubar = XmCreateMenuBar(BB, "MenuBar", NULL, 0);
    XtManageChild(menubar);

    submenu = XmCreatePulldownMenu(menubar, "Submenu1", NULL, 0);

    submenu2 = XmCreatePulldownMenu(menubar, "Submenu2", NULL, 0);

    n = 0;
    XtSetArg(args[n], XmNlabelString,
             XmStringLtoRCreate("Menu1", XmSTRING_DEFAULT_CHARSET)); 	n++;
    XtSetArg(args[n], XmNsubMenuId, submenu); 				n++;
    menu = XmCreateCascadeButton(menubar, "Cascade_Menu1", args, n);
    XtManageChild(menu);

    n = 0;
    XtSetArg(args[n], XmNlabelString,
             XmStringLtoRCreate("Menu2", XmSTRING_DEFAULT_CHARSET)); 	n++;
    XtSetArg(args[n], XmNsubMenuId, submenu2); 				n++;
    menu2 = XmCreateCascadeButton(menubar, "Cascade_Menu2", args, n);
    XtManageChild(menu2);

    n = 0;
    Push1 = XmCreatePushButton(submenu, "Push Button #1", args, n);
    XtManageChild(Push1);

    n = 0;
    Push2 = XmCreatePushButton(submenu, "Push Button #2", args, n);
    XtManageChild(Push2);

    n = 0;
    Push3 = XmCreatePushButton(submenu, "Push Button #3", args, n);
    XtManageChild(Push3);

    n = 0;
    Push4 = XmCreatePushButton(submenu2, "Push Button #4", args, n);
    XtManageChild(Push4);

    n = 0;
    Push5 = XmCreatePushButton(submenu2, "Push Button #5", args, n);
    XtManageChild(Push5);

    n = 0;
    Push6 = XmCreatePushButton(submenu2, "Push Button #6", args, n);
    XtManageChild(Push6);

    XtAddCallback(Push6, XmNactivateCallback, Track, NULL);

    XtRealizeWidget(Shell1);

    CommonPause();

    confine = True;

    CommonPause();

    XtAppMainLoop(app_context);
}

static void Track(w, client_data, call_data)
Widget   w;
XtPointer  client_data;
XtPointer  call_data;
{
    Cursor 	cursor;
    int 	n = 0;
    Arg 	args[5];
    char	to[150];
    XmString	tcs;
    Widget 	MessageB;
    Widget	widget;
	

    cursor = XCreateFontCursor (display, XC_pirate);

    if (confine)
	widget = XmTrackingLocate(BB,cursor, True);
    else
    	widget = XmTrackingLocate(Shell1, cursor, False);

    if (widget != NULL)
    { 
    	strcpy(to, begin);
    	strcat(to, XtName(widget));
    	tcs = XmStringCreateLtoR(to, XmSTRING_DEFAULT_CHARSET);
    }
    else
    {
	tcs = XmStringCreateLtoR("Error in Return Value from XmTrackingLocate()\nTry again with pointer in a widget",
			XmSTRING_DEFAULT_CHARSET);
    }

    n = 0;
    XtSetArg(args[n], XmNdefaultPosition, False);	n++;
    XtSetArg(args[n], XmNx, 0);				n++;
    XtSetArg(args[n], XmNy, 200);			n++;
    XtSetArg(args[n], XmNmessageString, tcs);		n++;
    MessageB = XmCreateInformationDialog(Shell1, "MessageB", args, n);
    XtManageChild(MessageB);

    cur_num++;
}
