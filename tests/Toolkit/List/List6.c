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
static char rcsid[] = "$XConsortium: List6.c /main/9 1995/07/13 18:19:32 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include "List6.h"

void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       	n;
    Arg                	args[MAX_ARGS];
    XmString           	tcs[1], ItemList[NITEMS],
    			ItemList2[NITEMS];
    Widget		BulletinB, List2, sw, horiz_sb, vert_sb; 
    XmFontList         	newfontlist;
    Dimension		width;

    static XtActionsRec actions[] = {{"DeleteMe", (XtActionProc) DeleteMe}};
    static char translation_table[] = "<Key>d: DeleteMe()";

    CommonTestInit(argc, argv);
    
    newfontlist = CommonGetFontList("9x15bold");

    n = 0;
    XtSetArg(args[n], XmNtextFontList, newfontlist);			n++;
    BulletinB = XmCreateBulletinBoard (Shell1, "BulletinB", args, n);
    XtManageChild (BulletinB);

    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    for (n = 0; n < NITEMS; n++)
	ItemList2[n] = XmStringLtoRCreate(Istrings2[n],
			  XmSTRING_DEFAULT_CHARSET);

    tcs[0] = XmStringLtoRCreate("Item1", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNwidth, 75);				n++;
    XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);	n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS - 2);		n++;
    XtSetArg(args[n], XmNselectedItems, tcs);			n++;
    XtSetArg(args[n], XmNselectedItemCount, 1);			n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);	n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);		n++;
    List1 = XmCreateScrolledList(BulletinB, "List1", args, n);
    XtManageChild(List1);

    XtAddCallback(List1, XmNmultipleSelectionCallback, 
		  (XtCallbackProc) MSelCB, NULL);
    XtAddCallback(List1, XmNextendedSelectionCallback, 
		  (XtCallbackProc) ESelCB, NULL);
    XtAddCallback(List1, XmNdefaultActionCallback, 
		  (XtCallbackProc) DefACB, NULL);
    XtAddCallback(List1, XmNsingleSelectionCallback, 
		  (XtCallbackProc) SSelCB, NULL);
    XtAddCallback(List1, XmNbrowseSelectionCallback, 
		  (XtCallbackProc) BSelCB, NULL);
    XtAddCallback(List1, XmNhelpCallback, 
		  (XtCallbackProc) HelpCB, NULL);

    n = 0;
    XtSetArg(args[n], XmNhorizontalScrollBar, &horiz_sb);	n++;
    XtSetArg(args[n], XmNverticalScrollBar, &vert_sb);		n++;
    XtGetValues(XtParent(List1), args, n);

    n = 0;
    XtSetArg(args[n], XmNrepeatDelay, 50);			n++;
    XtSetArg(args[n], XmNinitialDelay, 250);			n++;
    XtSetValues(horiz_sb, args, n);
    XtSetValues(vert_sb, args, n);

    XtRealizeWidget (Shell1);

    sw = XtParent(List1);

    n = 0;
    XtSetArg(args[n], XmNwidth, &width);			n++;
    XtGetValues(sw, args, n);

    printf("ScrolledWindow: width = %d\n", width);

    XmListSetAddMode(List1, True);  

    CommonPause();
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 400);				n++;
    XtSetArg(args[n], XmNheight, 200);				n++;
    XtSetValues(List1, args, n);

    CommonPause();

    XtRemoveAllCallbacks(List1, XmNmultipleSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNextendedSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNdefaultActionCallback);
    XtRemoveAllCallbacks(List1, XmNsingleSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNbrowseSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNhelpCallback);

    XtUnmanageChild(List1);

    n = 0;
    XtSetArg(args[n], XmNwidth, 400);				n++;
    XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);	n++;
    XtSetArg(args[n], XmNitems, ItemList2); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS - 2);		n++;
    XtSetArg(args[n], XmNselectedItems, tcs);			n++;
    XtSetArg(args[n], XmNselectedItemCount, 1);			n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);		n++;
    List2 = XmCreateList(BulletinB, "List2", args, n);
    XtManageChild(List2);

    if (!XmProcessTraversal(List2, XmTRAVERSE_CURRENT))
	printf("XmProcessTraversal (XmTRAVERSE_CURRENT) did not work\n");

    XtAddCallback(List2, XmNmultipleSelectionCallback, 
		  (XtCallbackProc) MSelCB, NULL);
    XtAddCallback(List2, XmNextendedSelectionCallback, 
		  (XtCallbackProc) ESelCB, NULL);
    XtAddCallback(List2, XmNdefaultActionCallback, 
		  (XtCallbackProc) DefACB, NULL);
    XtAddCallback(List2, XmNsingleSelectionCallback, 
		  (XtCallbackProc) SSelCB, NULL);
    XtAddCallback(List2, XmNbrowseSelectionCallback, 
		  (XtCallbackProc) BSelCB, NULL);
    XtAddCallback(List2, XmNhelpCallback, 
		  (XtCallbackProc) HelpCB, NULL);

    CommonPause();

/* Begin Test for Pir2512 */

    XtAppAddActions(app_context, actions, 1);
    XtOverrideTranslations(List2, XtParseTranslationTable(translation_table));

    CommonPause();

/* End Test for Pir2512 */

    XtAppMainLoop(app_context);
}

static XtCallbackProc HelpCB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("Help Callback called.\n");
}


static XtCallbackProc BSelCB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("BrowseSelect Callback called.\n");
}


static XtCallbackProc SSelCB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("SingleSelection Callback called.\n");
}


static XtCallbackProc DefACB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("DefaultAction Callback called.\n");
}


static XtCallbackProc MSelCB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("MultipleSelection Callback called\n");
}


static XtCallbackProc ESelCB(Widget w, caddr_t client_data,
			     caddr_t call_data)

{
	printf("ExtendedSelection Callback called\n");
}


static void DeleteMe(Widget w, XEvent *event, String *params, 
		     Cardinal num_params)
{
    XmString 	*sel_item;
    Arg 	args[2];
    int 	n, sel_item_count;

    n = 0;
    XtSetArg(args[n], XmNselectedItems, &sel_item);		n++;
    XtSetArg(args[n], XmNselectedItemCount, &sel_item_count);	n++;
    XtGetValues(w, args, n);


    if ( sel_item_count != 0 ) 
    	XmListDeleteItem(w, sel_item[0]);
    else
	printf("No Seleted Items, please make a selection\n");

}
