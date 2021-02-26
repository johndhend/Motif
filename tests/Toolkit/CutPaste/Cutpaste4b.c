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
static char rcsid[] = "$XConsortium: Cutpaste4b.c /main/7 1995/07/13 17:57:00 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <X11/Xatom.h>
#include <testlib.h>

Arg	args[20];
Atom	target;

static void GetCBSelection();

#define XA_TIMESTAMP ( XmInternAtom( display, "TIMESTAMP", False ))
#define XA_TARGETS ( XmInternAtom( display, "TARGETS", False ))
#define XA_CLIPBOARD ( XInternAtom( display, "CLIPBOARD", False ))

/*
 * This function is called when the selection value is returned by the
 * Toolkit.  It will try to use the cut buffer if no X selection is found.
 */

static void PasteCallBack(w, closure, selection, type, value, length, format)
     Widget	w;
     XtPointer	closure;
     Atom	*selection,
     		*type;
     XtPointer	value;
     unsigned long *length;
     int	*format;
{
    Widget	text = (Widget) closure;
    char	string[20];

    if (*type == XA_STRING)
    {
	char *text_string;
	char *text_value = (char *)value;

	text_string = (char *) XtMalloc (strlen(text_value) + 12);
	sprintf(text_string, "%s", text_value);
	XmTextSetString(text, text_string);
    }
    else   if (*type == None)
    {
	fprintf(stdout, "Retrieve Failed, No Clipboard selection.\n");
    }
    else
    {
	fprintf(stdout, "Incorrect selection type\n");
    }
} 


static void GetCBSelection (button, client_data, call_data)
     Widget	button;
     XtPointer	client_data,
     		call_data;
{
    Widget 		text = (Widget) client_data;
    XmAnyCallbackStruct	*cb = (XmAnyCallbackStruct *)call_data;

    XtGetSelectionValue(text, XA_CLIPBOARD, XA_STRING, PasteCallBack,
			text, cb->event->xbutton.time);
}


void main (argc, argv)
int argc;
char **argv;
{
    Widget	PanedWindow,
    		PushButton1,
    		Label,
    		Text;
    int		n;

    CommonTestInit(argc, argv);

/*
 * Paned window to hold pushbutton, labels and text widgets
 */

    n = 0;
    PanedWindow = XmCreatePanedWindow(Shell1, "PanedWindow", args, n);
    XtManageChild(PanedWindow);

    n = 0;
    XtSetArg(args[n], XmNlabelString,
	     XmStringCreateLtoR("Get Values", XmSTRING_DEFAULT_CHARSET)); n++;
    PushButton1 = XmCreatePushButton(PanedWindow, "PushButton1", args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg(args[n], XmNlabelString,
	     XmStringCreateLtoR("String", XmSTRING_DEFAULT_CHARSET)); n++;
    Label = XmCreateLabel(PanedWindow, "Label", args, n);
    XtManageChild(Label);

    n = 0;
    XtSetArg(args[n], XmNresizeWidth, False);  n++;
    XtSetArg(args[n], XmNresizeHeight, False);  n++;
    XtSetArg(args[n], XmNrows, 1);  n++;
    XtSetArg(args[n], XmNcolumns, 15);  n++;
    XtSetArg(args[n], XmNfontList, CommonGetFontList("6x10"));  n++;

    Text = XmCreateText(PanedWindow, "Text", args, n);
    XtManageChild(Text);

    XtAddCallback (PushButton1, XmNactivateCallback, GetCBSelection, 
		   (XtPointer) Text);

    XtRealizeWidget(Shell1);

    XtSetSelectionTimeout(20000); 

    XtAppMainLoop(app_context);
}
