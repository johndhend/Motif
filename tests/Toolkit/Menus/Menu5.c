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
static char rcsid[] = "$XConsortium: Menu5.c /main/10 1995/07/13 18:45:38 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>
#include <X11/Xlib.h>
#include "armPixft.h"
  
#include <X11/cursorfont.h>
#include <X11/StringDefs.h>
#include <X11/Vendor.h>

#include <Xm/XmP.h>
#include <Xm/RowColumnP.h>
#include "disarmPixft.h"
#include "arrowPixft.h"

/*************Some Globals***********************/

Widget mainw, menubar, separator;
Widget rc2;
Widget pdbtn1, pdbtn2, pdbtn3;
Widget toggle1, toggle2;
Widget option1, option2, option3;
Widget option1n, option2n, option1h, option2h, option3h, option1o, option2o;
Widget submenu1, submenu2, submenu3;
Widget title, separator2, popup;

Cursor sailboat, heart, man, pirate, shuttle, arrow;
Boolean CallbacksEnabled = False;
int WhichButton = 3;
int WAWhichButton = 1;

#ifdef notdef
Pixmap arm = None;
Pixmap disarm = None;
Pixmap arrowPix = None;
#endif

static void CreatePopup();
static XtTranslations translation1;

void PrintMessage(Widget widget, XtPointer client_data, XtPointer call_data)
{
  switch ((int)((XmAnyCallbackStruct *)call_data)->reason) {
  case XmCR_VALUE_CHANGED: 
    printf ("Value changed callback for toggle");
    break;
  case XmCR_ARM:
    printf ("Arm callback for toggle");
    break;
  case XmCR_DISARM: 
    printf ("Disarm callback for toggle");
    break;
  default:
    printf ("Some other callback received for toggle");
  }
  printf (" %d\n", (int)client_data);
}

void _XmRegisterHelpEvent(String event)
{
  static String action1 = ": Help()";
  static String action2 = ": help()";
  String bufr;

  if ((event == NULL) || (event[0] == '\0'))
    {
      printf ("_XmRegisterHelpEvent(): NULL event string specified\n");
      return;
    }

  bufr = XtMalloc(strlen(event) + strlen(action1) + 1);
  strcpy(bufr, event);
  strcat(bufr, action1);
  translation1 = XtParseTranslationTable(bufr);
  XtFree(bufr);
}

void _XmBindHelpAction(Widget widget, void (*func)(), XtPointer client_data,
		       Boolean recursive)
{
  int i;

  if (widget == NULL || (!XtIsWidget(widget) && !XmIsGadget(widget)))
    return;

  if (XmIsGadget(widget))
    {
      XtAddCallback(widget, XmNhelpCallback, func, client_data);
      return;
    }

  if (!XtIsShell(widget))
    {
      XtOverrideTranslations(widget, translation1);
      XtAddCallback(widget, XmNhelpCallback, func, client_data);
    }

  if (recursive)
    {
      /* Process normal descendants */
      if (XtIsComposite(widget))
	{
	  XmManagerWidget mw = (XmManagerWidget)widget;

	  for (i = 0; i < mw->composite.num_children; i++)
	    {
	      _XmBindHelpAction(mw->composite.children[i], func, client_data, 
				recursive);
	    }
	}
      
      /* Handle popup descendants */
      for (i = 0; i < widget->core.num_popups; i++)
	{
	  _XmBindHelpAction(widget->core.popup_list[i], func, client_data, 
			    recursive);
	}
    }
}

void PrintName(Widget w,
XtPointer d1,
XtPointer d2)
{
  printf ("Widget %s was activated\n", XrmQuarkToString(w->core.xrm_name));
}

void PrintName_2(Widget rc, XtPointer client_data,
		 XtPointer rc_data)
{
  XmRowColumnCallbackStruct *rc_struct;

  rc_struct = (XmRowColumnCallbackStruct *) rc_data;
  printf ("Widget %s was activated\n", 
	  XrmQuarkToString(rc_struct->widget->core.xrm_name));
}

static XtCallbackRec PrintName_CB[] = {
  {PrintName_2, NULL},
  {NULL, NULL}
};

void PrintNameAndChangeCursor(Widget rc, XtPointer client_data,
			      XtPointer rc_data)
{
  XmRowColumnCallbackStruct *rc_struct = (XmRowColumnCallbackStruct *)rc_data;
  if (rc_struct->data == NULL)
    {
      printf ("Widget %s was activated\n", 
	      XrmQuarkToString(rc_struct->widget->core.xrm_name));
    }
  else
    {
      Cursor cursor = (Cursor)rc_struct->data;
      XmSetMenuCursor(XtDisplay(rc), cursor);
      if (XmGetMenuCursor(XtDisplay(rc)) != cursor)
	printf("Error: problem occurred while changing menu cursor\n");
    }
}

static XtCallbackRec PrintNameAndChangeCursor_CB[] = {
   {PrintNameAndChangeCursor, NULL},
   {NULL, NULL}
};

Help(Widget w)
{
  printf ("Help requested for widget %s\n", 
	  XrmQuarkToString(w->core.xrm_name));
}

void PostIt(Widget w, XtPointer p, XEvent *event, Boolean *c)
{
  Arg args[5];
  Boolean popupEnabled;
  Widget popup = (Widget) p;

  if (popup == NULL)
    return;

  if ((event->type == ButtonPress) && (event->xbutton.button != WhichButton))
    return;

  XtSetArg(args[0], XmNpopupEnabled, &popupEnabled);
  XtGetValues(popup, args, 1);
  if (popupEnabled)
    {
      XmMenuPosition(popup, (XButtonPressedEvent *) event);
      XtManageChild(popup);
   }
}

/*************End of CALLBACK PROCEDURES****************/

int main(int argc, char **argv)
{
  Arg args[15];
  int n;
  XEvent event;

  CommonTestInit(argc, argv);

  /****************************************************************/
  /*  Create the of the top-level frame and row-column manager    */
  /****************************************************************/

  XtSetArg(args[0], XmNradioAlwaysOne, True);
  rc2 = XmCreateRadioBox(Shell1, "rc2", args, 1);
  XtManageChild(rc2);

  /****************************************************************/
  /*  Create the widget children of the second row-column manager  */
  /****************************************************************/

  toggle1 = XmCreateToggleButtonGadget(rc2, "toggle1", NULL, 0);
  XtManageChild(toggle1);
  XtAddCallback(toggle1, XmNvalueChangedCallback, PrintMessage, (XtPointer) 1);
  XtAddCallback(toggle1, XmNarmCallback, PrintMessage, (XtPointer) 1);
  XtAddCallback(toggle1, XmNdisarmCallback, PrintMessage, (XtPointer) 1);

  toggle2 = XmCreateToggleButtonGadget(rc2, "toggle2", NULL, 0);
  XtManageChild(toggle2);
  XtAddCallback(toggle2, XmNvalueChangedCallback, PrintMessage, (XtPointer) 2);
  XtAddCallback(toggle2, XmNarmCallback, PrintMessage, (XtPointer) 2);
  XtAddCallback(toggle2, XmNdisarmCallback, PrintMessage, (XtPointer) 2);

  /**************************/
  /*  Create the popup menu */
  /**************************/

  CreatePopup();
  sailboat = XCreateFontCursor (display, XC_sailboat);
  heart = XCreateFontCursor (display, XC_heart);
  man = XCreateFontCursor (display, XC_man);
  pirate =  XCreateFontCursor (display, XC_pirate);
  shuttle = XCreateFontCursor (display, XC_shuttle);
  arrow = XCreateFontCursor (display, XC_arrow);

  XmSetMenuCursor(display, man);


  /****************************************************************/
  /*  Realize the widget hierarchy, and enter mainloop processing */
  /****************************************************************/

  XtRealizeWidget (Shell1);

/*    _XmRegisterHelpEvent("<Key>F8");
    _XmBindHelpAction(Shell1, Help, NULL, True); */

  CommonPause();

#ifdef WORKAROUND 
  XtDestroyWidget(submenu3);
  XtDestroyWidget(submenu1);
  XtDestroyWidget(submenu2);
  XtDestroyWidget(popup);
#endif	

  XtDestroyWidget(rc2);  
  CommonPause();
  XtAppMainLoop(app_context);
}

static void CreatePopup()
{
  int n;
  Arg args[10];

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
  XtSetArg(args[n], XmNwhichButton, 3); n++;
  popup = XmCreatePopupMenu(rc2, "popup", args, n);
  XtAddEventHandler(rc2, ButtonPressMask, False, PostIt, (XtPointer) popup);

  title = XmCreateLabelGadget(popup, "Title", NULL, 0);
  separator2 =XmCreateSeparatorGadget(popup, "separator2", NULL, 0);

  option1 = XmCreatePushButtonGadget(popup, "option1", args, 0);
  XtAddCallback(option1, XmNactivateCallback, PrintName, NULL);

  option2 = XmCreatePushButtonGadget(popup, "option2", args, 0);
  XtAddCallback(option2, XmNactivateCallback, PrintName, NULL);

  option3 = XmCreatePushButtonGadget(popup, "option3", args, 0);
  XtAddCallback(option3, XmNactivateCallback, PrintName, NULL);
  XtManageChild(title);
  XtManageChild(separator2);
  XtManageChild(option1);
  XtManageChild(option2);
  XtManageChild(option3);

  submenu2 = (Widget)XmCreatePulldownMenu(popup, "submenu2", NULL, 0);
  option1h = XmCreatePushButtonGadget(submenu2, "option1h", NULL, 0);
  XtAddCallback(option1h, XmNactivateCallback, PrintName, NULL);

  option2h = XmCreatePushButtonGadget(submenu2, "option2h", NULL, 0);
  XtAddCallback(option2h, XmNactivateCallback, PrintName, NULL);

  option3h = XmCreatePushButtonGadget(submenu2, "option3h", NULL, 0);
  XtAddCallback(option3h, XmNactivateCallback, PrintName, NULL);
  XtManageChild(option1h);
  XtManageChild(option2h);
  XtManageChild(option3h);

  submenu1 = (Widget)XmCreatePulldownMenu(submenu2, "submenu1", NULL, 0);

  option1n =XmCreatePushButtonGadget(submenu1, "option1n", NULL, 0);
  XtAddCallback(option1n, XmNactivateCallback, PrintName, NULL);

  option2n =XmCreatePushButtonGadget(submenu1, "option2n", NULL, 0);
  XtAddCallback(option2n, XmNactivateCallback, PrintName, NULL);
  XtManageChild(option1n);
  XtManageChild(option2n);

  submenu3 = XmCreatePulldownMenu(submenu1, "submenu3", NULL, 0);

  option1o =XmCreatePushButtonGadget(submenu3, "option1o", NULL, 0);
  XtAddCallback(option1o, XmNactivateCallback, PrintName, NULL);

  option2o =XmCreatePushButtonGadget(submenu3, "option2o", NULL, 0);
  XtAddCallback(option2o, XmNactivateCallback, PrintName, NULL);
  XtManageChild(option1o);
  XtManageChild(option2o);

  n = 0; 
  XtSetArg(args[n], XmNsubMenuId, submenu3); n++;
  pdbtn1 = XmCreateCascadeButtonGadget(submenu1, "pdbtn1", args, n);
  XtManageChild(pdbtn1);

  n = 0; 
  XtSetArg(args[n], XmNsubMenuId, submenu1); n++;
  pdbtn2 = XmCreateCascadeButton(submenu2, "pdbtn2", args, n);
  XtManageChild(pdbtn2);

  n = 0; 
  XtSetArg(args[n], XmNsubMenuId, submenu2); n++;
  pdbtn3 = XmCreateCascadeButton(popup, "pdbtn3", args, n);
  XtManageChild(pdbtn3);
}
