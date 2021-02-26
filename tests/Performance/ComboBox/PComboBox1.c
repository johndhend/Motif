/* $XConsortium: PComboBox1.c /main/5 1995/07/15 21:00:55 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */
#include <testlib.h>

#define VITEMS 		20
#define MAX_ITEMS 	20000
#define DEFAULT_ITEMS	5000

/* Global Variables */
Widget		ComboBox1;
int		nitems;
XmString	add_item;


void  
main (int argc, char **argv)
{
    register int	n;
    Arg			args[MAX_ARGS];
    char		Item[15];
    XmString		ItemList[MAX_ITEMS];

    CommonTestInit(argc, argv);

    if (UserData)  {
	nitems = atoi(UserData);
    }
    else
	nitems = DEFAULT_ITEMS;

    n = 0;
    XtSetArg(args[n], XmNwidth,  150);  			n++;
    XtSetArg(args[n], XmNheight, 300);  			n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  			n++;
    XtSetValues(Shell1, args, n);
    
    XtRealizeWidget(Shell1);

    /* 
     * generate items for list and 
     * convert the plain strings to Xmstrings 
     */
    for (n = 0; n < nitems; n++)  {
	sprintf(Item, "%s%d", "item", n);
	ItemList[n] = XmStringCreate(Item,
			  XmFONTLIST_DEFAULT_TAG);
    }

    add_item = XmStringCreate ("Added Item", XmFONTLIST_DEFAULT_TAG);

    CommonPause();

    /* now create a list with nitems and see performance */
    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNlistSizePolicy, XmVARIABLE);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, nitems); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, VITEMS); 		n++;
    ComboBox1 = XmCreateComboBox(Shell1, "ComboBox1", args, n);
    XtManageChild(ComboBox1);

    CommonPause();

    /* 
     * test performance in .scr file by scrolling from top to bottom
     * and bottom to top
     */

    CommonPause();

    /* 
     * test the performance of adding one 
     * item to the botton when:
     *	- top is visible
     */
    XmListAddItem (XtNameToWidget (ComboBox1, "*List"), add_item, nitems+1);

    CommonPause();

    /* 
     * test the performance of adding one 
     * item to the botton when:
     *	- bottom is visible
     */
    XmListAddItem (XtNameToWidget (ComboBox1, "*List"), add_item, nitems+1);

    CommonPause();

    /* 
     * test the performance of deleting one 
     * item from the bottom when:
     *	- top is visible
     */

    XmListDeleteItemsPos(XtNameToWidget (ComboBox1, "*List"), 1, nitems+2);

    CommonPause();

    /* 
     * test the performance of deleting one
     * item from the bottom when:
     * - bottom is visible
     */

    XmListDeleteItemsPos (XtNameToWidget (ComboBox1, "*List"), 1, nitems+1);

    CommonPause();


    XtAppMainLoop(app_context);
}


