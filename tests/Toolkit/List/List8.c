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
static char rcsid[] = "$XConsortium: List8.c /main/7 1995/07/13 18:21:19 drk $"
#endif
#endif

/* Test for Pir 2511 */

#include <testlib.h>

static void listCallback(list, p1, p2) 
Widget list;
XtPointer p1;
XtPointer p2; 
{
    XmString	strs[10];
    Cardinal	i, n;
    Arg		args[5];
    int		itemCnt;

    XtSetArg(args[0], XmNitemCount, &itemCnt);
    XtGetValues(list, args, 1);

    if (itemCnt >= 10) 
	itemCnt = 1;
    else 
	itemCnt = 10;

    printf("Switching to %d items\n", itemCnt);

    for (i = 0; i < itemCnt; ++i) 
	strs[i] = XmStringCreateSimple("foobar is as foobar does");

    n = 0;
    XtSetArg(args[n], XmNitems, strs); 			n++;
    XtSetArg(args[n], XmNitemCount, itemCnt); 		n++;
    XtSetArg(args[n], XmNselectedItemCount, 0); 	n++;
    XtSetValues(list, args, n);

    for (i = 0; i < itemCnt; ++i) 
	XmStringFree(strs[i]);

}


main(argc, argv)
int 	argc;
char	*argv[];
{
    Cardinal		n, i;
    Arg			args[5];
    Widget		list;
    XmString		strs[10];
    Widget		parent;
    int			count;
    Dimension		h;
    Boolean		manage_sooner = False; 

    CommonTestInit(argc, argv);

    if (UserData && (strcmp (UserData, "sooner") == 0)) 
	manage_sooner = True;

    for (i = 0; i < 10; ++i) 
	strs[i] = XmStringCreateSimple("foobar is as foobard does");

    n = 0;
    XtSetArg(args[n], XmNitems, strs); 					n++;
    XtSetArg(args[n], XmNitemCount, 10); 				n++;
    XtSetArg(args[n], XmNfontList, CommonGetFontList("8x13bold"));	n++;
    list = XmCreateList(Shell1, "List1", args, n);
    XtManageChild(list);

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 10);				n++;
    XtSetValues(list, args, n);

    XtAddCallback(list, XmNbrowseSelectionCallback, listCallback, NULL);
    XtAddCallback(list, XmNdefaultActionCallback, listCallback, NULL);
    XtAddCallback(list, XmNextendedSelectionCallback, listCallback, NULL);
    XtAddCallback(list, XmNmultipleSelectionCallback, listCallback, NULL);
    XtAddCallback(list, XmNsingleSelectionCallback, listCallback, NULL);


    XtRealizeWidget(Shell1);

    CommonPause();

    /* begin Test for  PIR 4014 */

    XtDestroyWidget (list);
    
    n = 0;
    XtSetArg (args[n], XmNheight, 75); n++;
/*    parent = XmCreateForm (Shell1, "parent", args, n); */
    parent = XmCreateBulletinBoard (Shell1, "parent", args, n);
    if (manage_sooner) 
       XtManageChild (parent);
    
    n = 0;
    XtSetArg(args[n], XmNitems, strs); 					n++;
    XtSetArg(args[n], XmNitemCount, 10); 				n++;
    XtSetArg(args[n], XmNfontList, CommonGetFontList("8x13bold"));	n++;
/*    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++; */
    list = XmCreateList(parent, "List1", args, n);
    XtManageChild(list);
    if (!manage_sooner)
	XtManageChild (parent);

    n = 0;
    XtSetArg (args[n], XmNvisibleItemCount, &count); n++;
    XtGetValues (list, args, n);
    printf ("Visible item count is %d\n", count); 
    n = 0;
    XtSetArg (args[n], XmNvisibleItemCount, count); n++;
    XtSetValues (list, args, n);

    n = 0;
    XtSetArg (args[n], XmNheight, &h); n++;
    XtGetValues (parent, args, n);
    printf ("Height of form is %d\n", (int) h);


    CommonPause();
  
    /* end test for PIR 4014 */
 
    for (i = 0; i < 10; ++i) 
	XmStringFree(strs[i]);
    XtAppMainLoop(app_context);
}
