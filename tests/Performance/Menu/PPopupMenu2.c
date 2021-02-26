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
static char rcsid[] = "$XConsortium: PPopupMenu2.c /main/7 1995/07/14 12:01:40 drk $"
#endif
#endif
#include <testlib.h>

#define	MAX_BUTTONS	40

/*  Global Variables  */
Widget    Label;
Widget    PopupMenu1;
Widget    Label1;
Widget    Separator1;
Widget    PushBtn1;
Widget    ToggleBtn1;
Widget    PullDown2;
Widget    CascadeBtn1;
Widget    Label2;
Widget    Separator2;
Widget    ToggleBtn2;
Widget    PullDown3;
Widget    CascadeBtn2;
Widget    PushBtn2;
Widget    Label3;
Widget    PullDown4;
Widget    CascadeBtn3;
Widget    PushBtn3;
Widget    ToggleBtn3;
Widget    Label4;

Widget	push_btns[MAX_BUTTONS];

char	*btn_labels[MAX_BUTTONS] = {

			"PushButton1",
			"PushButton2",
			"PushButton3",
			"PushButton4",
			"PushButton5",
			"PushButton6",
			"PushButton7",
			"PushButton8",
			"PushButton9",
			"PushButton10",
			"PushButton11",
			"PushButton12",
			"PushButton13",
			"PushButton14",
			"PushButton15",
			"PushButton16",
			"PushButton17",
			"PushButton18",
			"PushButton19",
			"PushButton20",
			"PushButton21",
			"PushButton22",
			"PushButton23",
			"PushButton24",
			"PushButton25",
			"PushButton26",
			"PushButton27",
			"PushButton28",
			"PushButton29",
			"PushButton30",
			"PushButton31",
			"PushButton32",
			"PushButton33",
			"PushButton34",
			"PushButton35",
			"PushButton36",
			"PushButton37",
			"PushButton38",
			"PushButton39",
			"PushButton40"

		};
Widget    PushBtn4;
Widget    PushBtn5;
Widget    PushBtn6;
Widget    PushBtn7;
Widget    PushBtn8;
Widget    PushBtn9;
Widget    PushBtn10;
Widget    PushBtn11;
Widget    PushBtn12;
Widget    PushBtn13;
Widget    PushBtn14;
Widget    PushBtn15;
Widget    PushBtn16;
Widget    PushBtn17;
Widget    PushBtn18;
Widget    PushBtn19;
Widget    PushBtn20;

/*  Private Functions  */
static void  Quit();
static XtCallbackProc  quitCB();

#define PUSHBUTTON 1
#define TOGGLEBUTTON 2
#define CASCADEBUTTON 3

XtCallbackProc CBHandler (w, client_data, call_data)
Widget w;
caddr_t client_data, call_data;

{
char *myname;
CoreWidget  *tmpwidget;

switch ( ((XmAnyCallbackStruct *)call_data)->reason)
  {    case XmCR_ARM:    printf ("Arm ");
                         break;
       case XmCR_ACTIVATE:    printf ("Activate ");
                         break;
       case XmCR_DISARM: printf ("Disarm ");
                         break;
       case XmCR_VALUE_CHANGED:  printf ("ValueChanged ");
                         break;
       case XmCR_CASCADING:  printf ("Cascading ");
                         break;
       default:           printf ("Other Callback ");
  }

printf ("%s\n", XtName(w));
XFlush(display);
fflush(stdout);

/*
tmpwidget = (CoreWidget)w;
*/

/* myname = ((CoreWidget *)w)->name;
   if (*myname != NULL) printf ("%s\n", myname);
*/

}


static Widget  CreateLabel(label, parent)
    char   *label;
    Widget  parent;
{
    Widget        widget;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;


    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreateLabel(parent, "label", args, n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}


static Widget  CreatePushButton(label, parent)
    char   *label;
    Widget  parent;
{
    Widget        widget;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;


    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreatePushButton(parent, "pushButton", args, n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}

static Widget  CreateToggle(label, parent)
    char   *label;
    Widget  parent;
{
    Widget        widget;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;


    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreateToggleButton(parent, "toggle", args, n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}


static Widget  CreateSeparator(parent)
	Widget parent ;
{
    Widget  widget;


    widget = XmCreateSeparator(parent, "separator", NULL, 0);
    XtManageChild(widget);

    return(widget);
}


static Widget  CreatePullDown(parent)
	Widget parent ;
{
    Widget  widget;
    

    widget = XmCreatePulldownMenu (parent, "pulldown", NULL, 0);

    return(widget);
}


static Widget  CreateCascade(label, submenu, parent)
    char   *label;
    Widget  submenu;
    Widget  parent;
{
    Widget        widget;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;


    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNsubMenuId, submenu); n++;
    widget = XmCreateCascadeButton(parent, "cascade", args,n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}


void  PostMenu (w, popup, event,c)
    Widget         w;
    XtPointer         popup;
    XEvent  *event;
    Boolean *c;
{
    if (event->xbutton.button != Button3)
        return;

    XmMenuPosition((Widget) popup, (XButtonPressedEvent *)event);
    XtManageChild ((Widget) popup);
}



void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
	int			num_buttons;
	int			i;



    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  200);  n++;
    XtSetArg(args[n], XmNheight, 40);   n++;
    XtSetValues(Shell1, args, n);
    

    XtRealizeWidget(Shell1);


    Label = CreateLabel("Select Me", Shell1);


    /*
    **  PopupMenu1
    */
    PopupMenu1 = XmCreatePopupMenu(Label, "popMenu", NULL, 0);
    XtAddEventHandler(Label, ButtonPressMask, False, PostMenu, (XtPointer) PopupMenu1);


    /*
    **  Menu1
    */
    Label1       = CreateLabel("Menu1", PopupMenu1);

    Separator1   = CreateSeparator(PopupMenu1);

	num_buttons = MAX_BUTTONS; /* to be modified to take from command line */
	for (i = 0; i < num_buttons; i++)
		push_btns[i] = CreatePushButton(btn_labels[i], PopupMenu1);
    ToggleBtn1   = CreateToggle("Toggle1", PopupMenu1);

    XtAppMainLoop(app_context);
}




static XtCallbackProc  quitCB(w, client_data, call_data)
    Widget   w;
    caddr_t  client_data;
    caddr_t  call_data;

{
	printf("Exiting...Please Standby...\n");
	exit(0);
}


