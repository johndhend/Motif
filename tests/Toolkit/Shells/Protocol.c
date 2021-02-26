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
static char rcsid[] = "$XConsortium: Protocol.c /main/8 1995/07/13 19:20:41 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget  	RowCol;
Widget 		ShortMenu, LongMenu, NoMenu;
Atom		mwm_messages;

XmString 	text;

XFontStruct *fnt;
XmFontList 	font;

#define ENTRY_1		1
#define ENTRY_2		2
#define ENTRY_3		3

static void addShortMenu();
static void addLongMenu();
static void addNoMenu();


static Widget ShellAncestor(widget)
Widget widget;
{

    Widget topWidget;

   topWidget = widget;
   while (widget != NULL && !XtIsShell(topWidget))
    	topWidget = XtParent(topWidget);
   return(topWidget);

}


static void EntrySelected(w, client_data, call_data)
Widget	    w;
XtPointer	client_data, call_data;
{
    printf("entry %d selected\n", (int)(long)client_data);
}


static void addShortMenu(w, client_data, call_data)
Widget		w;
XtPointer	client_data;
XtPointer	call_data;
{

	Widget	shell;
	Arg		args[1];
	int			n;
	static Atom	atoms[1];
	static int 	status = 0;
	static String	menu = "entry_1	f.send_msg 1";

    atoms[0] = (Atom)ENTRY_1;

	shell = ShellAncestor(w);
	
	n = 0;
	XtSetArg(args[n], XmNmwmMenu, menu); n++;
	XtSetValues(Shell1, args, n);

	switch(status) {

  		case 0:
			XmAddProtocols(Shell1, mwm_messages, atoms, XtNumber(atoms));

			XmAddProtocolCallback(Shell1, mwm_messages, ENTRY_1, 
								  EntrySelected, (XtPointer) ENTRY_1);

			if (XtIsRealized(Shell1)) {
				XtUnmapWidget(Shell1);
				XtMapWidget(Shell1);
			}
			status = 1;
			break;
	
		case 1:
			XmRemoveProtocolCallback(Shell1, mwm_messages, ENTRY_1, 
									 EntrySelected, (XtPointer) ENTRY_1);
			status = 2;
			break;
	
		case 2:
			XmAddProtocolCallback(Shell1, mwm_messages, ENTRY_1, 
								  EntrySelected, (XtPointer) ENTRY_1);
			status = 1;
			break;

		default:

			break;

	}

}


static void addLongMenu(w, client_data, call_data)
Widget      w;
XtPointer   client_data;
XtPointer   call_data;
{

    Widget		shell;
    Arg			arg;
    static String	menu = 
      "entry_1	f.send_msg  1 \n\
       entry_2	f.send_msg  2 \n\
       entry_3	f.send_msg  3";
    static Atom		atoms[] = { (Atom)ENTRY_1, (Atom)ENTRY_2, (Atom)ENTRY_3};
    static int status = 0;

    shell = ShellAncestor(w);

    XtSetArg(arg, XmNmwmMenu, menu);
    XtSetValues(Shell1, &arg, 1);

    switch(status) {

    	case 0:
    		XmAddProtocols(Shell1, mwm_messages, atoms, XtNumber(atoms));

    		XmAddProtocolCallback(Shell1, mwm_messages, ENTRY_1, 
								  EntrySelected, (XtPointer) ENTRY_1);
    		XmAddProtocolCallback(Shell1, mwm_messages, ENTRY_2, 
								  EntrySelected, (XtPointer) ENTRY_2);
    		XmAddProtocolCallback(Shell1, mwm_messages, ENTRY_3, 
								  EntrySelected, (XtPointer) ENTRY_3);
        
    		status = 1;
			break;
	
    	case 1:
			XmDeactivateWMProtocol(Shell1, mwm_messages);

			status = 2;
			break;

    	case 2:
			XmActivateWMProtocol(Shell1, mwm_messages);

			status = 1;
			break;

    	default:

			break;

    }

    if (XtIsRealized(Shell1)) {
		XtUnmapWidget(Shell1);
		XtMapWidget(Shell1);
    }

}


static void addNoMenu(w, client_data, call_data)
Widget      w;
XtPointer     client_data;
XtPointer     call_data;
{

    Widget	shell;
    Arg		args[1];
	int		n;

    shell = ShellAncestor(w);
	 
	n = 0;
    XtSetArg(args[n], XmNmwmMenu, ""); n++;
    XtSetValues(Shell1, args, n);

    if (XtIsRealized(Shell1)) {
		XtUnmapWidget(Shell1);
		XtMapWidget(Shell1);
    }

}


void main(argc, argv)
int argc;
char **argv;
{

    Cardinal	n;
    Arg			args[MAX_ARGS];


    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNallowShellResize, True); n++;
	XtSetValues(Shell1, args, n);

    /*
     * intern the atoms and add mwm_messages to wm_protocols so that
     * mwm will look for mwm_messages property changes.
     */
    mwm_messages = XmInternAtom(XtDisplay(Shell1), _XA_MWM_MESSAGES, False);
    XmAddWMProtocols(Shell1, &mwm_messages, 1);

	font = CommonGetFontList("6x13");

    n = 0;
    XtSetArg(args[n], XmNborderWidth, 2); n++;
    XtSetArg(args[n], XmNshadowThickness, 0); n++;
    RowCol = XmCreateRowColumn(Shell1, "RowCol", args, n);
    XtManageChild(RowCol);

    n = 0;    
#ifdef MOTIF1_1
    text = XmStringCreateLtoR("ShortMenu", XmSTRING_DEFAULT_CHARSET);
#else
    text = XmStringCreateLtoR("ShortMenu", XmFONTLIST_DEFAULT_TAG);
#endif
    XtSetArg(args[n], XmNfontList, font); n++;
    XtSetArg(args[n], XmNlabelString, text); n++;
    XtSetArg(args[n], XmNlabelType, XmSTRING); n++;
    ShortMenu = XmCreatePushButton(RowCol, "ShortMenu", args, n);
    XtManageChild(ShortMenu);
	XtAddCallback (ShortMenu, XmNactivateCallback, addShortMenu, NULL);

    n = 0;    
#ifdef MOTIF1_1
    text = XmStringCreateLtoR("LongMenu", XmSTRING_DEFAULT_CHARSET);
#else
    text = XmStringCreateLtoR("LongMenu", XmFONTLIST_DEFAULT_TAG);
#endif
    XtSetArg(args[n], XmNfontList, font); n++;
    XtSetArg(args[n], XmNlabelString, text); n++;
    XtSetArg(args[n], XmNlabelType, XmSTRING); n++;
    LongMenu = XmCreatePushButton(RowCol, "LongMenu", args, n);
    XtManageChild(LongMenu);
	XtAddCallback (LongMenu, XmNactivateCallback, addLongMenu, NULL);
    
    n = 0;    
#ifdef MOTIF1_1
    text = XmStringCreateLtoR("NoMenu", XmSTRING_DEFAULT_CHARSET);
#else
    text = XmStringCreateLtoR("NoMenu", XmFONTLIST_DEFAULT_TAG);
#endif
    XtSetArg(args[n], XmNfontList, font); n++;
    XtSetArg(args[n], XmNlabelString, text); n++;
    XtSetArg(args[n], XmNlabelType, XmSTRING); n++;
    NoMenu = XmCreatePushButton(RowCol, "NoMenu", args, n);
    XtManageChild(NoMenu);
	XtAddCallback (NoMenu, XmNactivateCallback, addNoMenu, NULL);

	XmStringFree(text);

    n = 0;
    XtSetArg(args[n], XmNdeleteResponse, XmUNMAP); n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    CommonPause();

    CommonPause();

    CommonPause();

    CommonPause();

    CommonPause();

    XtPopup(Shell1, XtGrabNone);

    CommonPause();

    XtPopup(Shell1, XtGrabNone);

    CommonPause();

    CommonPause();

    XtAppMainLoop(app_context);

}
