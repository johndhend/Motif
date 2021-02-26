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
static char rcsid[] = "$XConsortium: Navigation12.c /main/8 1995/07/13 19:41:16 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>

#define NITEMS	9

/*  Global Variables  */
Widget RowCol, PB1, PB2, PB3;
Widget    List1, TextField1, Text2;
char *Istrings[NITEMS] = {
	"Item1",
	"Item2",
	"Item3",
	"Item4",
	"Item5",
	"Item6",
	"Item7",
	"Item8",
	"Item9"
};

/*  Private Functions  */
static XtCallbackProc  SinSelCB();
static XtCallbackProc  ExtSelCB();
static XtCallbackProc  DefActCB();
static XtCallbackProc  ExtOrMulSelCB();
void WarnMe (Widget w,
             XtPointer client_data,
             XEvent *event,
             Boolean *continue_to_dispatch);


/* external functions */

void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       	n;
    register int       	i;
    Widget		Form, vertSB;
    Arg                	args[MAX_ARGS];
    XmString           	tcs, ItemList[NITEMS];
    XFontStruct        	* newfont;
    XmFontList         	newfontlist;
    int 	       	position;
    int 		position_count = 0;
    int 		*position_list = NULL;
    int			item_count = NITEMS;




    CommonTestInit(argc, argv);
    

    newfont = XLoadQueryFont(display, "9x15");
    newfontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNtextFontList, newfontlist);  		n++;
    Form = XmCreateForm (Shell1, "Form", args, n);


    /* convert the plain strings to Xstrings */
    for ( n=0; n<NITEMS; n++)
	ItemList[n]=XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);	n++;
    XtSetArg(args[n], XmNhighlightOnEnter, True); 		n++;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmVARIABLE);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS);		n++;
/*    P2063 happens with either scrollingPolicy                          */
/*    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED); n++; */
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);     n++;
    List1 = XmCreateScrolledList(Form, "List1", args, n);
    XmAddTabGroup(XtParent(List1));

    n = 0;
    XtSetArg (args[n], XmNverticalScrollBar, &vertSB); n++;
    XtGetValues ((XtParent(List1)), args, n);

    XtAddEventHandler (vertSB, ButtonPressMask, FALSE, WarnMe, 
			(XtPointer) NULL); 

    XtManageChild(List1);
 
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
    XtSetArg(args[n], XmNleftWidget, List1);                    n++;
    RowCol = XmCreateWorkArea(Form, "RowCol", args, n);

    n = 0;
    PB1 = XmCreatePushButton (RowCol, "PB1", args, n); 
    PB2 = XmCreatePushButton (RowCol, "PB2", args, n); 
    PB3 = XmCreatePushButton (RowCol, "PB3", args, n); 
    XtManageChild (PB1);
    XtManageChild (PB2);
    XtManageChild (PB3);
    
    XmAddTabGroup (RowCol);
    XtManageChild (RowCol);

    XtManageChild (Form);
    XtRealizeWidget(Shell1);

    CommonPause();

    XtDestroyWidget (RowCol);
    XtDestroyWidget (List1);

    for ( n=0; n<NITEMS; n++)
	ItemList[n]=XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);	n++;
    XtSetArg(args[n], XmNhighlightOnEnter, True); 		n++;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmVARIABLE);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS);		n++;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);     n++;
    List1 = XmCreateList(Form, "List1", args, n);

    n = 0;
    XtSetArg (args[n], XmNcolumns, 12); n++;
    XtSetArg (args[n], XmNvalue, "TAB NONE"); n++;
/*    XtSetArg (args[n], XmNnavigationType, XmNONE); n++; */
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
    XtSetArg (args[n], XmNleftWidget, List1); n++;
    TextField1 = XmCreateTextField (Form, "TextField1", args, n);

    n = 0;
    XtSetArg (args[n], XmNcolumns, 12); n++;
    XtSetArg (args[n], XmNvalue, "TAB NONE"); n++;
    XtSetArg (args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
    XtSetArg (args[n], XmNnavigationType, XmNONE); n++;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
    XtSetArg (args[n], XmNleftWidget, List1); n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
    XtSetArg (args[n], XmNtopWidget, TextField1); n++;
    Text2 = XmCreateText (Form, "Text2", args, n);

/*  begin test for PIR 4075 */
    n = 0;
    XtSetArg (args[n], XmNinitialFocus, TextField1); n++;
    XtSetValues (Form, args, n);

    XtRealizeWidget (List1);
    XtManageChild (List1);
    XtRealizeWidget (TextField1);
    XtManageChild (TextField1);
    XtRealizeWidget (Text2);
    XtManageChild (Text2);

/*  geometry bug is PIR 4076 */
    CommonPause();

    XtUnmanageChild (Form);
    XtManageChild (Form);

    CommonPause();

/*  end test for PIR 4075 */

    XtAppMainLoop(app_context);
}
void WarnMe (Widget w,
             XtPointer client_data,
             XEvent *event,
             Boolean *continue_to_dispatch)
{
	printf ("The VertSB got that press event\n"); 
	fflush (stdout);
}















