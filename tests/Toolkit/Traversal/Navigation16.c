/* $XConsortium: Navigation16.c /main/5 1995/07/15 21:11:54 drk $ */
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

#include <testlib.h>
#include <Xm/XmP.h>

typedef struct wstruct
{
    Widget w;
    Widget (*createFunc)(Widget, String, ArgList, Cardinal);
    char* name;
} WStruct;

#define NUM_GADGETS 5

static Widget rowcol1;

static WStruct Widgets[NUM_GADGETS] =
{
    {NULL, XmCreateLabelGadget, "labelG1"},
    {NULL, XmCreateSeparatorGadget, "separatorG1"},
    {NULL, XmCreatePushButtonGadget, "pushBG1"},
    {NULL, XmCreateToggleButtonGadget, "toggleBG1"},
    {NULL, XmCreateArrowButtonGadget, "arrowBG1"}
};

void printWidgetName(Widget w)
{
    int i;
    char* name;

    name = "Unknown widget";
    if (w == rowcol1)
       name = "rowcol1";
    else if (w == Shell1)
	name = "Shell1";
    else
	for (i = 0; i < NUM_GADGETS; i++)
	    if (w == Widgets[i].w)
		{
		    name = Widgets[i].name;
		    break;
		}
    printf("%s", name);
}

void focusCB(Widget w, XtPointer client_data, XtPointer call_data )
{
    XmFocusMovedCallbackStruct* cbs;

    cbs = (XmFocusMovedCallbackStruct*)call_data;

    printf("Focus moved from ");

    printWidgetName(cbs->old_focus);

    printf(" to ");

    printWidgetName(cbs->new_focus);

    printf("\n");
}

main (int argc, char ** argv)
{
   Arg args[10];
   int i;

   /* initialize Toolkit */
   CommonTestInit(argc, argv);

   rowcol1 = XmCreateRowColumn(Shell1, "rowcol1", args, 0);

   for (i = 0; i < NUM_GADGETS; i++) {
       Widgets[i].w
	   = Widgets[i].createFunc(rowcol1, Widgets[i].name, args, 0);
       XtManageChild(Widgets[i].w);
   }
   XtManageChild(rowcol1);

   XtRealizeWidget(Shell1);

   CommonPause();

   XmeAddFocusChangeCallback(Shell1, focusCB, NULL);

   CommonPause();

   XtAppMainLoop(app_context);
}
