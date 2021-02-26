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
static char rcsid[] = "$XConsortium: Cutpaste3.c /main/7 1995/07/13 17:55:51 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <signal.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/StringDefs.h>


#include <testlib.h>

Widget Text3;
Arg args[20];

/* 
 * function to exit gracefully
 */


/*
 * Copy the selected string to the clipboard
 */

static void CopyToClipboard (button, client_data, call_data)
Widget button;
XtPointer client_data, call_data;
{
    Widget w = (Widget) client_data;
    XmAnyCallbackStruct *cb = (XmAnyCallbackStruct *) call_data; 
    char *selected_string = NULL;
    int num_tries = 0, status = 0;
    long item_id = 0;
    long data_id = 0;
    XmString	start_string;

    start_string = XmStringCreateLtoR ("CP_Test2", XmSTRING_DEFAULT_CHARSET);

    selected_string = XmTextGetSelection (w);

    if (selected_string != NULL)
    {
       while (status != ClipboardSuccess && num_tries < 10) {
         status = XmClipboardStartCopy (XtDisplay(w), XtWindow(w), start_string,
				    cb->event->xbutton.time, w, NULL, &item_id);
	 if (num_tries == 10) {
		printf("Begin Copy Failed. Status = %d\n", status);
		fflush(stdout);
		return;
         }
	 num_tries++;
       }

       num_tries = status = 0;
       while (status != ClipboardSuccess && num_tries < 10) {
         status = XmClipboardCopy (XtDisplay(w), XtWindow(w), item_id,
	     			     "STRING", selected_string,
				     (long) strlen(selected_string) + 1, 0,
				     &data_id);
	 if (num_tries == 10) {
		printf("Copy Failed. Status = %d\n", status);
		fflush(stdout);
         }
	 num_tries++;
       }

       num_tries = status = 0;
       while (status != ClipboardSuccess && num_tries < 10) {
         status = XmClipboardEndCopy (XtDisplay(w), XtWindow(w), item_id);
	 if (num_tries == 10) {
		printf("End Copy Failed. Status = %d\n", status);
		fflush(stdout);
         }
	 num_tries++;
       }
    }
    XmTextSetString(Text3, "Copied to Clipboard");
}

/*
 * Copy the string from the clipboard
 */

static void CopyFromClipboard (button, client_data, call_data)
Widget button;
XtPointer client_data, call_data;
{
    Widget w = (Widget) client_data;
    XmAnyCallbackStruct *cb = (XmAnyCallbackStruct *) call_data; 
    char buffer[1000];
    unsigned long outlength = 0;
    long private_id = 0;
    int num_tries = 0, status = 0;

    while (status != ClipboardSuccess && num_tries < 10) {
      status = XmClipboardStartRetrieve(XtDisplay(w), XtWindow(w), 
					cb->event->xbutton.time);

      if (num_tries == 10) {
	  printf("Start Retrieve Failed. Status = %d\n", status);
	  fflush(stdout);
	  return;
      }
      num_tries++;
    }

    status = num_tries = 0;

    while (status != ClipboardSuccess && num_tries < 10) {
      status = XmClipboardRetrieve (XtDisplay(w), XtWindow(w), 
				    "STRING", buffer, 1000, 
				    &outlength, &private_id);

      if (num_tries == 10) {
	  printf("Retrieve Failed. Status = %d\n", status);
	  fflush(stdout);
	  return;
      }
      num_tries++;
    }

    status = num_tries = 0;

    while (status != ClipboardSuccess && num_tries < 10) {
      status = XmClipboardEndRetrieve(XtDisplay(w), XtWindow(w));

    if (num_tries == 10) {
	  printf("End Retrieve Failed. Status = %d\n", status);
	  fflush(stdout);
	  return;
      }
      num_tries++;
    }

    XmTextSetString(Text3, buffer);
}

void main (argc, argv)
int argc;
char **argv;
{
   Widget RowColumn;
   Widget PushButton1;
   Widget PushButton2;
   Widget PushButton3;
   Widget Text1;
   Widget Text2;
   int n;


   /*  initialize toolkit  */
    CommonTestInit(argc, argv);

   n = 0;
   XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
   XtSetArg(args[n], XmNnumColumns, 3); n++;
   RowColumn = XmCreateRowColumn(Shell1, "RowColumn", args, n);
   XtManageChild(RowColumn);
   
   n = 0;
   XtSetArg(args[n], XmNlabelString,
	    XmStringCreateLtoR("Copy From Text1", XmSTRING_DEFAULT_CHARSET));
   n++;
   PushButton1 = XmCreatePushButton(RowColumn, "PushButton1", args, n);
   XtManageChild(PushButton1);
 
   n = 0;
   XtSetArg(args[n], XmNresizeWidth, False);  n++;
   XtSetArg(args[n], XmNresizeHeight, False);  n++;
   XtSetArg(args[n], XmNvalue, "Test Text1");  n++;
   XtSetArg(args[n], XmNfontList, CommonGetFontList("variable"));  n++;
   Text1 = XmCreateText(RowColumn, "Text1", args, n);
   XtManageChild(Text1);

   n = 0;
   XtSetArg(args[n], XmNlabelString,
	    XmStringCreateLtoR("Copy From Text2", XmSTRING_DEFAULT_CHARSET));
   n++;
   PushButton2 = XmCreatePushButton(RowColumn, "PushButton2", args, n);
   XtManageChild(PushButton2);

   n = 0;
   XtSetArg(args[n], XmNresizeWidth, False);  n++;
   XtSetArg(args[n], XmNresizeHeight, False);  n++;
   XtSetArg(args[n], XmNvalue, "Test Text2");  n++;
   XtSetArg(args[n], XmNfontList, CommonGetFontList("variable"));  n++;
   Text2 = XmCreateText(RowColumn, "Text2", args, n);
   XtManageChild(Text2);

   n = 0;
   XtSetArg(args[n], XmNlabelString,
	 XmStringCreateLtoR("Paste Contents", XmSTRING_DEFAULT_CHARSET));  n++;
   PushButton3 = XmCreatePushButton(RowColumn, "PushButton3", args, n);
   XtManageChild(PushButton3);

   n = 0;
   XtSetArg(args[n], XmNresizeWidth, False);  n++;
   XtSetArg(args[n], XmNresizeHeight, False);  n++;
   XtSetArg(args[n], XmNfontList, CommonGetFontList("variable"));  n++;
   Text3 = XmCreateText(RowColumn, "Text3", args, n);
   XtManageChild(Text3);

   XtAddCallback (PushButton1, XmNactivateCallback, CopyToClipboard, 
		  (XtPointer) Text1);
   XtAddCallback (PushButton2, XmNactivateCallback, CopyToClipboard, 
		  (XtPointer) Text2);
   XtAddCallback (PushButton3, XmNactivateCallback, CopyFromClipboard, 
		  (XtPointer) Text1);

   XtRealizeWidget(Shell1);

   CommonPause();
   CommonPause();
   
   XtAppMainLoop(app_context);
}
