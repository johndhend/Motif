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
static char rcsid[] = "$XConsortium: List3.c /main/9 1995/07/13 18:17:25 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include "List3.h"

/* 
   Test of PIR792 - When specifing selectedItems and items in a resource
		    file, overlaping of the arrays occured causing a memory
		    fault. 
   Test of PIR872 - Memory fault due to short allocation in ResConvert.c
*/

static void HowMany(Widget w, XtPointer client_data,
			      XtPointer call_data)

{
    short 		whichCallback;
    Arg 		args[2];
    int 		count, n;
    XmStringTable       my_items;

    n = 0;
    XtSetArg (args[n], XmNselectedItemCount, &count);		n++;
    XtSetArg (args[n], XmNselectedItems, &my_items);		n++;
    XtGetValues (w, args, n);

    whichCallback = (short) client_data;

    if (whichCallback) { 	/* default action */
   	printf ("Default Action callback, selectedItemCount is %d\n", count);
    }
    else 			/* selectionCallback */
   	printf ("Selection callback, selectedItemCount is %d\n", count);

}


void  main (argc, argv)
    int     argc;
    char  **argv;
{
    register int       n;
    Arg                args[MAX_ARGS];
    XmString           tcs, ItemList[NITEMS], SelectionList[NITEMS];
    XrmDatabase        new_db, save_db;

    CommonTestInit(argc, argv);

    XrmInitialize();

    new_db = XrmGetFileDatabase("List3DB");

#ifdef MOTIF1_1
    XrmMergeDatabases(new_db, &(display->db));
#else
    save_db = XtDatabase(display);
    XrmCombineDatabase(new_db, &save_db, True);
#endif

    for (n = 0; n < NITEMS; n++)
	ItemList[n] = XmStringLtoRCreate(Istrings[n],
			                 XmSTRING_DEFAULT_CHARSET);

    for (n = 0; n < NITEMS - 1; n++)
	SelectionList[n] = XmStringLtoRCreate(Istrings[n],
			              XmSTRING_DEFAULT_CHARSET);

    /* Create a List with no resources set. Control all resources
       in a separate resource file for this test */

    n = 0;
    List1 = XmCreateList(Shell1, "List1", args, n);
    XtManageChild(List1);

    /* 
       do this so Automation will work properly. ChangedManaged()
       routine in Shell is the problem.
    */

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 6);			n++;
    XtSetValues(List1, args, n);

    XtRealizeWidget(Shell1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNselectedItems, SelectionList); 	n++;
    XtSetArg(args[n], XmNselectedItemCount, NITEMS - 1); 	n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS);		n++;
    XtSetArg(args[n], XmNshadowThickness, 10);			n++;
    XtSetArg(args[n], XmNlistSpacing, 10); 			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 20);			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 20);			n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT);	n++;
    XtSetArg(args[n], XmNheight, 200);				n++;
    XtSetArg(args[n], XmNwidth, 200);				n++;
    XtSetValues(List1, args, n);

    XtAddCallback (List1, XmNmultipleSelectionCallback, HowMany, (XtPointer)0);
    XtAddCallback (List1, XmNdefaultActionCallback, HowMany, (XtPointer)1);

    CommonPause();

    XtAppMainLoop(app_context);
}
