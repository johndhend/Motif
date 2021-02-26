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
static char rcsid[] = "$XConsortium: List1.c /main/9 1995/07/13 18:14:01 drk $"
#endif
#endif

/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include "List1.h"


void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       	n;
    Arg                	args[MAX_ARGS];
    XmString           	tcs, ItemList[NITEMS],
		       	new_items[2], old_items[2],
    	    		*selected_items;
    XmString		new_items_2[15];
    int		       	selected_item_count;
    int			i;
    int			*position_list, position_count;
    Boolean		selected;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  350);  		n++;
    XtSetArg(args[n], XmNheight, 300);  		n++;
    XtSetValues(Shell1, args, n);
    
    XtRealizeWidget(Shell1);

    /* convert the plain strings to fancy Xstrings */
    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmVARIABLE);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNbackground,
    		WhitePixel(display,DefaultScreen(display))); 	n++;
    XtSetArg(args[n], XmNforeground,
    		BlackPixel(display,DefaultScreen(display))); 	n++;
    List1 = XmCreateList(Shell1, "List1", args, n);
    XtManageChild(List1);

    /* Add Callbacks */
    XtAddCallback(List1, XmNsingleSelectionCallback, SinSelCB, NULL);
    XtAddCallback(List1, XmNmultipleSelectionCallback, MulSelCB, NULL);
    XtAddCallback(List1, XmNextendedSelectionCallback, ExtSelCB, NULL);
    XtAddCallback(List1, XmNbrowseSelectionCallback, SinSelCB, NULL);
    XtAddCallback(List1, XmNdefaultActionCallback, DefActCB, NULL);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 4);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);  	n++;
    XtSetValues(List1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNselectionPolicy, XmBROWSE_SELECT);  	n++;
    XtSetValues(List1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);  	n++;
    XtSetValues(List1, args, n);

    /* Remove callbacks, and try interactions again */

    CommonPause();

    XtRemoveAllCallbacks(List1, XmNsingleSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNbrowseSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNmultipleSelectionCallback);
    XtRemoveAllCallbacks(List1, XmNextendedSelectionCallback);
    XtRemoveCallback(List1, XmNdefaultActionCallback, DefActCB, NULL);

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 5); 			n++;
    XtSetArg(args[n], XmNselectionPolicy, XmSINGLE_SELECT); 	n++;
    XtSetArg(args[n], XmNtraversalOn, True); 			n++;
    XtSetArg(args[n], XmNhighlightOnEnter, True); 		n++;
    XtSetArg(args[n], XmNhighlightThickness, 1); 		n++;
    XtSetValues(List1, args, n);

    CommonPause();

    /* Begin Test for Pir2661 */

    old_items[0] = XmStringLtoRCreate("List", XmSTRING_DEFAULT_CHARSET);
    new_items[0] = XmStringLtoRCreate("NEWList", XmSTRING_DEFAULT_CHARSET);

    XmListReplaceItems(List1, old_items, 1, new_items);

    n = 0;
    XtSetArg(args[n], XmNselectedItemCount, &selected_item_count); 	n++;
    XtSetArg(args[n], XmNselectedItems, &selected_items);      		n++;
    XtGetValues(List1, args, n);

    if (selected_item_count == 0) 
	printf("Please make a selection in the List\n");
    else
    	printf("SelectedItemCount = %d, SelectedItems = %s\n", 
			selected_item_count, CommonCsToRs(selected_items[0]));

    printf("\n");

    fflush(stdout);

    /* End Test for Pir2661 */

    CommonPause();

    /* Begin Test for Pir2800 */

    n = 0;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);		n++;
    XtSetValues(List1, args, n);

    /* Begin Test for Pir 2817 */

    XmListDeleteAllItems(List1);

    n = 0;
    XtSetArg(args[n], XmNselectedItemCount, &selected_item_count);	n++;
    XtSetArg(args[n], XmNselectedItems, &selected_items);		n++;
    XtGetValues(List1, args, n);

    printf("SelectedItemCount = %d\nSelectedItems are:\n", selected_item_count);
    if (selected_items == NULL)
	printf("NULL\n");
    else
    	for (i = 0; i < selected_item_count ; i++)
		printf("%s\n", CommonCsToRs(selected_items[i]));

    /* End Test for Pir2817 */

    n = 0;
    XtSetArg(args[n], XmNselectedItemCount, 0);				n++;
    XtSetArg(args[n], XmNselectedItems, NULL);				n++;
    XtSetValues(List1, args, n);

    new_items_2[0] = XmStringCreateLtoR("Same Item", 
					  XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNitems, new_items_2);				n++;
    XtSetArg(args[n], XmNitemCount, 1);					n++;
    XtSetArg(args[n], XmNvisibleItemCount, 10);				n++;
    XtSetValues(List1, args, n);

    CommonPause();

    for (i = 0; i < 9 ; i++)
    	XmListAddItem(List1, new_items_2[0], 0);

    selected = XmListGetSelectedPos(List1, &position_list, &position_count);

    if (selected) {
	printf("Selected Positions are:\n\t");
    	for (i = 0 ; i < position_count ; i++)
		printf("%d ", position_list[i]);
    	printf("\n");
    }
    else
	printf("No Selected Items\n");

    n = 0; 
    XtSetArg(args[n], XmNselectedItemCount, &selected_item_count);	n++;
    XtGetValues(List1, args, n);

    printf("SelectedItemCount = %d\n", selected_item_count);

    XtFree((char *) position_list);

    fflush(stdout);

    CommonPause();

    /* End Test for Pir2800 */

    /* Begin Test for CR5228 */

    selected = XmListGetSelectedPos(List1, &position_list, &position_count);

    if (selected) {
	    printf("Selected Positions are:\n\t");
    	for (i = 0 ; i < position_count ; i++)
		printf("%d ", position_list[i]);
    	printf("\n");
    }
    else {
	    printf("\nNo Selected Items\n");
		printf("Position count from XmListGetSelectedPos = %d\n\n",
			   position_count);
	}

    CommonPause();

    /* End Test for CR5228 */

#ifndef MOTIF1_1

    /* Begin Test for Pir3308 */

    n = 0;
    XtSetArg(args[n], XmNsensitive, False);				n++;
    XtSetValues(List1, args, n);

    CommonPause();

#endif /* MOTIF1_1 */

    /* End Test for Pir3308 */

    /* Begin Test for CR5833 */
    n = 0;
    XtSetArg(args[n], XmNsensitive, True);				n++;
    XtSetArg(args[n], XmNselectionPolicy, XmSINGLE_SELECT); 	n++;
    XtSetValues(List1, args, n);

    XmListSelectItem(List1, new_items_2[0], True);
    XmListAddItem(List1, new_items_2[0], 0);
    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 11);				n++;
    XtSetValues(List1, args, n);
    CommonPause();

    XmListDeselectAllItems(List1);
    /* End Test for CR5833 */

    CommonPause();

    XtAppMainLoop(app_context);
}


static void SinSelCB(Widget w, XtPointer client_data, 
			       XtPointer call_data)

{
    char **text;
    XmString tcs;
    
    printf("One item selected : ");
    tcs = ((XmListCallbackStruct*)call_data)->item;
    printf("no. %d\n", ((XmListCallbackStruct*)call_data)->item_position);
}


static void DefActCB (Widget w, XtPointer client_data,
				XtPointer call_data)

{

    printf ("Default Action selected...\n");

}

static void MulSelCB(Widget w, XtPointer client_data,
			       XtPointer call_data)

{
    char **text;
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
    char **text;
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
