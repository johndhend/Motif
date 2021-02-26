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
static char rcsid[] = "$XConsortium: ScrollList2.c /main/9 1995/07/13 18:23:21 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include "ScrollList2.h"


void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       n;
    Arg                args[MAX_ARGS];
    XmString           tcs, ItemList[NITEMS];

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  150);  			n++;
    XtSetArg(args[n], XmNheight, 300);  			n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  			n++;
    XtSetValues(Shell1, args, n);
    
    XtRealizeWidget(Shell1);

    /* convert the plain strings to Xstrings */
    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++; 
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, VITEMS); 		n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);  	n++;
    XtSetArg(args[n], XmNbackground,
    		WhitePixel(display,DefaultScreen(display))); 	n++;
    XtSetArg(args[n], XmNforeground,
    		BlackPixel(display,DefaultScreen(display))); 	n++;
    List1 = XmCreateScrolledList(Shell1, "List1", args, n);
    XtManageChild(List1);

    /* Add Callbacks */
    XtAddCallback(List1, XmNsingleSelectionCallback, SinSelCB, NULL);
    XtAddCallback(List1, XmNmultipleSelectionCallback, MulSelCB, NULL);
    XtAddCallback(List1, XmNextendedSelectionCallback, ExtSelCB, NULL);
    XtAddCallback(List1, XmNbrowseSelectionCallback, SinSelCB, NULL);

    /* Select two items, one by name and one by position */
    XmListSelectItem(List1,ItemList[14],TRUE);
    XmListSelectPos(List1,16,TRUE);

    CommonPause();

    /* Unselect the two items, one by name and one by position */
    XmListDeselectItem(List1,ItemList[14]);
    XmListDeselectPos(List1,16);

    /* Delete two items, one by name, one by position */
    XmListDeletePos(List1,5);
    XmListDeleteItem(List1,ItemList[5]);

    CommonPause();

    /* Add two items to replace deleted ones */
    XmListAddItem(List1,
		  XmStringLtoRCreate("junk01",XmSTRING_DEFAULT_CHARSET),
		  5);

    XmListSelectPos(List1, 5, FALSE);

    XmListAddItemUnselected(List1,
		  XmStringLtoRCreate("junk02",XmSTRING_DEFAULT_CHARSET),
		  6);

    CommonPause();

    /* make item #39 the 1st visible item in list */
    XmListSetPos(List1,39);

    /* select several items */
    XmListSelectPos(List1,40,FALSE);
    XmListSelectPos(List1,41,FALSE);
    XmListSelectPos(List1,42,FALSE);
    XmListSelectPos(List1,44,FALSE);

    CommonPause();

    /* unselect all items selected abive */
    XmListDeselectAllItems(List1);

    /* make first item in list the 1st visible one */
    XmListSetItem(List1,ItemList[0]);

    /* test for existance of a few items */
    if (XmListItemExists(List1,ItemList[4]))
	printf("Item %s is in the list\n",Istrings[4]);
    else
	printf("Item %s is MISSING from the list\n",Istrings[4]);
    if (XmListItemExists(List1,ItemList[0]))
	printf("Item %s is in the list\n",Istrings[0]);
    else
	printf("Item %s is MISSING from the list\n",Istrings[0]);
    if (XmListItemExists(List1,ItemList[20]))
	printf("Item %s is in the list\n",Istrings[20]);
    else
	printf("Item %s is MISSING from the list\n",Istrings[20]);
    if (XmListItemExists(List1,ItemList[12]))
	printf("Item %s is in the list\n",Istrings[12]);
    else
	printf("Item %s is MISSING from the list\n",Istrings[12]);

    CommonPause();

    /* Make the last item in the list visible. */

    XmListSetBottomPos(List1, 0);

    CommonPause();

    /* Make the first Item in the List Visible */

    XmListSetBottomItem(List1, ItemList[0]);

    CommonPause();

    XmListAddItemUnselected(List1,
		  XmStringLtoRCreate("This is a new item it is very long.",
				     XmSTRING_DEFAULT_CHARSET), 1);

    XmListSetHorizPos(List1, 20);

    CommonPause();

    XtAppMainLoop(app_context);
}


static void SinSelCB(Widget w, XtPointer client_data,
			       XtPointer call_data)

{
    XmString tcs;
    
    printf("One item selected : ");
    tcs = ((XmListCallbackStruct*)call_data)->item;
    printf("no. %d\n", ((XmListCallbackStruct*)call_data)->item_position);
}


static void MulSelCB(Widget w, XtPointer client_data,
			       XtPointer call_data)

{
    XmString tcs;
    
    printf("One or more items selected : ");
    tcs = ((XmListCallbackStruct*)call_data)->item;
    printf("no. of items is %d\n",
	   ((XmListCallbackStruct*)call_data)->selected_item_count);
    printf("    Last item selected has position no. %d\n",
	   ((XmListCallbackStruct*)call_data)->item_position);
}


static void ExtSelCB(Widget w, XtPointer client_data,
			       XtPointer call_data)

{
    XmString tcs;
    
    printf("One or more items selected : ");
    tcs = ((XmListCallbackStruct*)call_data)->item;
    printf("no. of items is %d\n",
	   ((XmListCallbackStruct*)call_data)->selected_item_count);
    printf("    Type of Selection was ");
    switch (((XmListCallbackStruct*)call_data)->selection_type) {
	case XmINITIAL      : printf("Initial\n");
			      break;
	case XmADDITION     : printf("Addition\n");
			      break;
	case XmMODIFICATION : printf("Modify\n");
			      break;
	default             : printf("not defined?\n");
    }
}
