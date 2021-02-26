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
static char rcsid[] = "$XConsortium: List12.c /main/5 1995/07/13 18:16:08 drk $"
#endif
#endif
  
#include <testlib.h>

#define NITEMS 8

char *Istrings[] = {
    "Item1",  "Item2",
    "Item3",  "Item4",
    "Item5",  "Item6",
    "Item6",  "Item8"
};


static void PushButtonCB(Widget w, Widget l,
			 XtPointer call_data)
{
  int num;
  int* sel;
  int i;
  
  if (!XmListGetSelectedPos(l, &sel, &num))
    return;
  for (i = 0; i < num; i++)
    /* correct for having deleted some already */
    XmListDeletePos(l, sel[i] - i);
}

main(argc, argv)
     int    argc;
     char **argv;
{
  register int n;
  Arg args[MAX_ARGS];
  XmString ItemList[NITEMS];
  Widget RC, List1, PushButton;
  
  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  350);  		n++;
  XtSetArg(args[n], XmNheight, 300);  		n++;
  XtSetArg(args[n], XmNallowShellResize, TRUE); n++;
  XtSetValues(Shell1, args, n);
  XtRealizeWidget(Shell1);

  n = 0;
  RC = XmCreateRowColumn(Shell1, "RC", args, n);
  XtManageChild (RC);

  for (n = 0; n < NITEMS; n++)
    ItemList[n] = XmStringLtoRCreate(Istrings[n],
				     XmSTRING_DEFAULT_CHARSET);

  n = 0;
  XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
  XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
  XtSetArg(args[n], XmNlistMarginHeight, 2);  		        n++;
  XtSetArg(args[n], XmNlistSizePolicy, XmVARIABLE);  		n++;
  XtSetArg(args[n], XmNitems, ItemList); 			n++;
  XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
  XtSetArg(args[n], XmNvisibleItemCount, NITEMS); 		n++;
  XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);     n++;
  XtSetArg(args[n], XmNbackground,
	   WhitePixel(display,DefaultScreen(display))); 	n++;
  XtSetArg(args[n], XmNforeground,
	   BlackPixel(display,DefaultScreen(display))); 	n++;
  List1 = XmCreateList(RC, "List1", args, n);
  XtManageChild(List1);

  n = 0;

  PushButton = XmCreatePushButton (RC, "PushButton", args, n);
  XtManageChild(PushButton);

  XtAddCallback(PushButton, XmNactivateCallback, 
		(XtCallbackProc) PushButtonCB, List1);

  CommonPause();
  CommonPause();  /* Exit */

  XtAppMainLoop(app_context);
}
