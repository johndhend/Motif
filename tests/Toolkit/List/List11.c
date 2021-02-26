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
static char rcsid[] = "$XConsortium: List11.c /main/5 1995/07/13 18:15:32 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>

#define NITEMS  10

/*  Global Variables  */

char *Istrings[NITEMS] = {
	"Item1",
	"Item2",
	"Item3",
	"Item4",
	"Item5",
	"Item6",
	"Item7",
	"Item8",
	"Item9",
	"Item10"
	};

Widget    List1, PushB;

/*  Private Functions  */


static void  DefACB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  DefACB2(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  SSelCB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  MSelCB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  ESelCB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  BSelCB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  HelpCB(Widget w, XtPointer client_data,
			      XtPointer call_data);
static void  PushBCB(Widget w, XtPointer client_data,
		      	      XtPointer call_data);
static void  SensitiveCB(Widget w, XtPointer client_data,
		      	      XtPointer call_data);
static XtTimerCallbackProc PopupDown(XtPointer client_data);



void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       	n;
    Arg                	args[MAX_ARGS];
    XmString           	tcs[1], ItemList[NITEMS];
    Widget		mWindow;
    Widget		Text;
    Widget		sWindow, pWindow;
    XmFontList         	newfontlist;
    XrmDatabase         new_db, save_db;

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNkeyboardFocusPolicy, XmPOINTER); n++;
    XtSetValues(Shell1, args, n);

    XrmInitialize();

    new_db = XrmGetFileDatabase("List11DB");

#ifdef MOTIF1_1
    XrmMergeDatabases(new_db, &(display->db));
#else
    save_db = XtDatabase(display);
    XrmCombineDatabase(new_db, &save_db, True);
#endif

    newfontlist = CommonGetFontList(
	  "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1");

    n = 0;
    mWindow = XmCreateMainWindow(Shell1, "mWindow", args, n);
    XtManageChild (mWindow);

    n = 0;
    pWindow = XmCreatePanedWindow(mWindow, "pWindow", args, n);
    XtManageChild (pWindow);

    n = 0;
    XtSetArg(args[n], XmNshadowThickness, 0);				n++;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);	n++;
    sWindow = XmCreateScrolledWindow(pWindow, "sWindow", args, n);
    XtManageChild (sWindow);

    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			                 XmSTRING_DEFAULT_CHARSET);

    tcs[0] = XmStringLtoRCreate("Item1", XmSTRING_DEFAULT_CHARSET);

    XtRealizeWidget(Shell1);

    n = 0;
    XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);   n++;
    XtSetArg(args[n], XmNitems, ItemList);                      n++;
    XtSetArg(args[n], XmNitemCount, NITEMS);                    n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS-5);           n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmRESIZE_IF_POSSIBLE); n++;
    XtSetArg(args[n], XmNfontList, newfontlist);		n++;
    List1 = XmCreateList(sWindow, "List1", args, n);
    XtManageChild(List1);

    XtAddCallback(List1, XmNextendedSelectionCallback, ESelCB, (XtPointer)NULL);
    XtAddCallback(List1, XmNdefaultActionCallback, DefACB, (XtPointer)NULL);

    n = 0;
    XtSetArg(args[n], XmNfontList, newfontlist);		n++;
    Text = XmCreateScrolledText(pWindow, "Text1", args, n);
    XtManageChild(Text);

    CommonPause();

    XtAppMainLoop(app_context);
}

/* Begin Test code for Pir2978 */

static void DefACB2(Widget w, XtPointer client_data,
			      XtPointer call_data)

{
    Widget 	InfoDia1;
    int		n;
    Arg		args[5];

    n = 0;
    XtSetArg(args[n], XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL); n++;
    XtSetArg(args[n], XmNx, 0);				           n++;
    XtSetArg(args[n], XmNy, 0);					   n++;
    XtSetArg(args[n], XmNdefaultPosition, False);		   n++;
    InfoDia1 = XmCreateInformationDialog(Shell1, "InfoDia1", args, n);
    XtManageChild(InfoDia1);

}


static XtTimerCallbackProc PopupDown(XtPointer client_data)

{

    if (XtIsManaged((Widget) client_data)) {
    	printf("Unmanaging Dialog\n");
    	XtUnmanageChild((Widget)client_data);
    }
    else
	printf("Dialog Already Unmanaged\n");

}

/* End Test Code for Pir2978 */

static void HelpCB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("Help Callback called.\n");
}


static void BSelCB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("BrowseSelect Callback called.\n");
}


static void SSelCB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("SingleSelection Callback called.\n");
}


static void DefACB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("DefaultAction Callback called.\n");
}


static void MSelCB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("MultipleSelection Callback called\n");
}


static void ESelCB(Widget w, XtPointer client_data,
			     XtPointer call_data)

{
    printf("ExtendedSelection Callback called\n");
}
