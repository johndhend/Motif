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
static char rcsid[] = "$XConsortium: ScrollList3.c /main/9 1995/07/13 18:23:50 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/*	
	This file contains test code for the following PIRS:

		- 705 - ScrolledList in Form
		- 718, 755 - Adobe Font hightlights
		- 390, 707, 722, 741, 753 - XmListDeletePos deletions
		- 782 - Scrolling behavior
		- 770 - height of 0

*/

#include <testlib.h>
#include "ScrollList3.h"

int counter = 0;

static void addCB(Widget w, XtPointer client_data, XtPointer call_data)
{
    Arg args[4];
    int count;
    int n;
    XmString str;
    XmString *items;

    n = 0; 
    XtSetArg(args[n], XmNitemCount, &count); 	n++;
    XtSetArg(args[n], XmNitems, &items);	n++;
    XtGetValues(client_data, args, n);

    switch (counter) {
	case 0:
    		XmListDeleteItemsPos(client_data, count, 1);
		break;
	case 1:
		XmListDeleteItems(client_data, items, count);
		break;
	case 2:
		for (n = 0 ; n < count ; n++)
			XmListDeletePos(List1, 1);
		break;
	default:
		printf("Out of test cases\n");
		break;
    }
		
    str = XmStringCreateSimple("Yet another");
    XmListAddItem(client_data, str, 0);

}


static void add1CB(Widget w, XtPointer client_data, XtPointer call_data)
{
  XmString str;

  str = XmStringCreateLtoR("an item\n  2nd line", XmSTRING_DEFAULT_CHARSET);
  XmListAddItem(client_data, str, 0);

}


void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       n, i;
    Arg                args[MAX_ARGS];
    XmString           tcs, ItemList[NITEMS];
    XmFontList         newfontlist;
    Widget	       Push1, Push2;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth, 300); 				n++;
    XtSetArg(args[n], XmNheight, 200);				n++;
    Form1 = XmCreateForm(Shell1, "Form1", args, n);
    XtManageChild(Form1);

    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			  XmSTRING_DEFAULT_CHARSET);

    newfontlist = CommonGetFontList("10x20");

    n = 0;
    XtSetArg(args[n], XmNfontList, newfontlist);  		n++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNleftOffset, 50); 			n++;
    XtSetArg(args[n], XmNrightOffset, 50); 			n++;
    XtSetArg(args[n], XmNlistSpacing, 10);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 10);  		n++;
    XtSetArg(args[n], XmNlistMarginHeight, 10);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, 5); 			n++;
    XtSetArg(args[n], XmNselectionPolicy, XmSINGLE_SELECT); 	n++;
    XtSetArg(args[n], XmNbackground,
    		WhitePixel(display,DefaultScreen(display))); 	n++;
    XtSetArg(args[n], XmNforeground,
    		BlackPixel(display,DefaultScreen(display))); 	n++;

    List1 = XmCreateScrolledList(Form1, "List1", args, n);
    XtManageChild(List1);

    XtRealizeWidget(Shell1);

    CommonPause();

    XtAddCallback(List1, XmNsingleSelectionCallback, (XtCallbackProc) SinSelCB,
		  NULL);

    CommonPause();  /* all list objects now gone */

    for (i = 0; i <= (NITEMS - 1); i++)
    { 
	XmListAddItem (List1, XmStringCreate(Istrings[i], 
		       XmSTRING_DEFAULT_CHARSET), 0);
        XmListSetBottomPos (List1, 0);
    }
    
    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNheight, 0);				n++;
    XtSetValues (List1, args, n);

    CommonPause();

    n = 0;
    XtSetArg (args[n], XmNheight, 500);				n++;
    XtSetValues (List1, args, n);

    CommonPause();

    /* Begin Test for Pir 3475 */

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNitemCount, 0);				n++;
    XtSetArg(args[n], XmNitems, NULL);				n++;
    XtSetArg(args[n], XmNvisibleItemCount, 3); 			n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC); 	n++;
    XtSetValues(List1, args, n);

    tcs = XmStringCreateSimple("Push to Delete and Add");

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); 	n++;
    XtSetArg(args[n], XmNtopWidget, List1); 			n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNlabelString, tcs);			n++;
    XtSetArg(args[n], XmNbackground,
    		WhitePixel(display,DefaultScreen(display))); 	n++;
    XtSetArg(args[n], XmNforeground,
    		BlackPixel(display,DefaultScreen(display))); 	n++;
    Push1 = XmCreatePushButton(Form1, "Push1", args, n);
    XtManageChild(Push1);

    XtAddCallback(Push1, XmNactivateCallback, addCB, (XtPointer) List1);
    XmStringFree(tcs);
    
    tcs = XmStringCreateSimple("Push to Add one Item");

    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); 	n++;
    XtSetArg(args[n], XmNtopWidget, Push1); 			n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); 	n++;
    XtSetArg(args[n], XmNlabelString, tcs);			n++;
    XtSetArg(args[n], XmNbackground,
    		WhitePixel(display,DefaultScreen(display))); 	n++;
    XtSetArg(args[n], XmNforeground,
    		BlackPixel(display,DefaultScreen(display))); 	n++;
    Push2 = XmCreatePushButton(Form1, "Push2", args, n);
    XtManageChild(Push2);

    XtAddCallback(Push2, XmNactivateCallback, add1CB, List1);
    XmStringFree(tcs);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNitemCount, 0);				n++;
    XtSetArg(args[n], XmNitems, NULL);				n++;
    XtSetArg(args[n], XmNvisibleItemCount, 3); 			n++;
    XtSetValues(List1, args, n);

    counter++;

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNitemCount, 0);				n++;
    XtSetArg(args[n], XmNitems, NULL);				n++;
    XtSetArg(args[n], XmNvisibleItemCount, 3); 			n++;
    XtSetValues(List1, args, n);

    counter++;

    CommonPause();

    /* End Test for Pir 3475 */

    XtAppMainLoop(app_context);
}


static void SinSelCB(Widget w, XtPointer client_data, XtPointer call_data)

{
    int 	item_count;
    int 	n;
    Arg 	args[1];

    XmListDeletePos(w, 0);

    n = 0;
    XtSetArg(args[n], XmNitemCount, &item_count); n++;
    XtGetValues(w, args, n);

    if (item_count == 0) {
	printf("The List is now Empty - \n");
	printf("\tNo Scrollbars or items should be visible\n");
    }

}
