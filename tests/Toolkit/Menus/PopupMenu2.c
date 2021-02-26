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
static char rcsid[] = "$XConsortium: PopupMenu2.c /main/9 1995/07/13 18:51:50 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>

#include <testlib.h>

Widget popup = NULL, submenu2 = NULL, red = NULL, blue = NULL,
  violet = NULL, brown = NULL, orange = NULL, submenu4 = NULL,
  child1 = NULL, child2 = NULL, submenu3 = NULL, to_submenu = NULL,
  children = NULL, no_submenu = NULL,
  yellow = NULL, green = NULL, label = NULL, title = NULL;

static void PostIt(Widget w, XtPointer p, XEvent *event, Boolean *c)
{
  Widget popup = (Widget) p;
  if(event->xbutton.button != Button3)
    {return; }
  XmMenuPosition(popup, (XButtonPressedEvent *)event);
  XtManageChild(popup);
}

static void TranslationPost(Widget w, XEvent *event, String *params,
			    Cardinal *num_params)
{
  XmMenuPosition(popup, (XButtonPressedEvent *)event);
  XtManageChild (popup);
}

static void cascading_msg(Widget w, XtPointer client_data, 
			  XtPointer call_data)
{
  fprintf(stdout, "cascading callback - %s\n",
	  XrmQuarkToString(w->core.xrm_name));
}

static void ArmCallback(Widget w, XtPointer client_data, 
		    XtPointer call_data)
{
  fprintf(stdout, "arm callback - %s\n",
	  XrmQuarkToString(w->core.xrm_name));
}

static void disArmCallback(Widget w, XtPointer client_data, 
		       XtPointer call_data)
{
  fprintf(stdout, "disarm callback - %s\n",
	  XrmQuarkToString(w->core.xrm_name));
}

static void activate_msg(Widget w, XtPointer client_data, 
					XtPointer call_data)
{
  fprintf(stdout, "activate callback - destroy %s\n",
	  XrmQuarkToString(w->core.xrm_name));
    
  XtDestroyWidget(w);
}

void PrintName_2(Widget rc, XtPointer client_data, 
		 XtPointer rc_data)
{
  XmRowColumnCallbackStruct * rc_struct = (XmRowColumnCallbackStruct *)rc_data;
  fprintf(stdout, "Widget %s was activated\n", 
	  XrmQuarkToString(rc_struct->widget->core.xrm_name));
}

static XtCallbackRec PrintName_CB[] =
{
  {PrintName_2, NULL},
  {NULL, NULL}
};

int main(int argc, char *argv[])
{
  Arg args[20];
  int n;
  XmString tcs;

  XmStringCharSet CharSet = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;

  /* for use in the later test of P1791 */
  static XtActionsRec actionTable[] = {{"PostPopupMenu", TranslationPost}};
  static char menuTranslations[] = "<Btn1Down>: PostPopupMenu()";

  CommonTestInit(argc, argv);
    
  XtAppAddActions(app_context, actionTable, 1);

  n = 0;
  XtSetArg(args[n], XtNwidth, 200); n++;
  XtSetArg(args[n], XtNheight, 40); n++;
  XtSetArg(args[n], XtNallowShellResize, True); n++;
  XtSetValues(Shell1, args, n);

  n = 0; 
  tcs = XmStringLtoRCreate("Popup Menu on MB2", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  label = XmCreateLabel(Shell1, "top_label", args, n);
  XtManageChild(label);
  XmStringFree(tcs);
  XtRealizeWidget(Shell1);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  XtSetArg(args[n], XmNwhichButton, 3); n++;
  popup = XmCreatePopupMenu(label, "popup", args, n);
  XtAddEventHandler(label, ButtonPressMask, False, PostIt, (XtPointer) popup);

  n = 0; 
  tcs = XmStringLtoRCreate("PopupMenu", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  title = XmCreateLabel(popup, "Title", args, n);
  XtManageChild(title);
  XmStringFree(tcs);

  n = 0; 
  tcs = XmStringLtoRCreate("Red (W)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  red = XmCreatePushButton(popup, "red", args, n);
  XtAddCallback(red, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(red, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(red, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(red);
  XmStringFree(tcs);

  n = 0; 
  tcs = XmStringLtoRCreate("Blue (G)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  blue = XmCreatePushButtonGadget(popup, "blue", args, n);
  XtAddCallback(blue, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(blue, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(blue, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(blue);
  XmStringFree(tcs);
    
  n = 0; 
  tcs = XmStringLtoRCreate ("Yellow (W)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  yellow = XmCreatePushButton(popup, "yellow", args, n);
  XtAddCallback(yellow, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(yellow, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(yellow, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(yellow);
  XmStringFree(tcs);

  n = 0; 
  XtSetArg(args[n], XmNentryCallback, (XtArgVal)PrintName_CB); n++;
  submenu2 = (Widget)XmCreatePulldownMenu(popup, "submenu2", args, n);

  n = 0; 
  tcs = XmStringLtoRCreate("Green (W)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  green = XmCreatePushButton(submenu2, "green", args, n);
  XtAddCallback(green, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(green, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(green, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(green);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("Violet (G)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  violet = XmCreatePushButtonGadget(submenu2, "violet", args, n);
  XtAddCallback(violet, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(violet, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(violet, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(violet);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("Brown (G)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  brown = XmCreatePushButtonGadget(submenu2, "brown", args, n);
  XtAddCallback(brown, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(brown, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(brown, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(brown);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("Orange (W)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  orange = XmCreatePushButton(submenu2, "orange", args, n);
  XtAddCallback(orange, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(orange, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(orange, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(orange);
  XmStringFree(tcs);

  n = 0;
  submenu4 = (Widget)XmCreatePulldownMenu(popup, "submenu4", args, n);

  n = 0;
  tcs = XmStringLtoRCreate("Child1 (G)", CharSet); 
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  child1 = XmCreatePushButtonGadget(submenu4, "child1", args, n);
  XtAddCallback(child1, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(child1, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(child1, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(child1);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("Child2 (W)", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  child2 = XmCreatePushButton(submenu4, "child2", args, n);
  XtAddCallback(child2, XmNarmCallback, ArmCallback, NULL);
  XtAddCallback(child2, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(child2, XmNdisarmCallback, disArmCallback, NULL);
  XtManageChild(child2);
  XmStringFree(tcs);

  n = 0;
  submenu3 = (Widget)XmCreatePulldownMenu(popup, "submenu3", args, n);

  n = 0;
  tcs = XmStringLtoRCreate("To Submenu", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNsubMenuId, submenu2); n++;
  to_submenu = XmCreateCascadeButton(popup, "to_submenu", args, n);
  XtAddCallback(to_submenu, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(to_submenu, XmNcascadingCallback, cascading_msg, NULL);
  XtManageChild(to_submenu);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("Children", CharSet); 
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNsubMenuId, submenu4); n++;
  children = XmCreateCascadeButton(popup, "children", args, n);
  XtAddCallback(children, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(children, XmNcascadingCallback, cascading_msg, NULL);
  XtManageChild(children);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("No Submenu", CharSet);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNsubMenuId, submenu3); n++;
  no_submenu = XmCreateCascadeButton(popup, "no_submenu", args, n);
  XtAddCallback(no_submenu, XmNactivateCallback, activate_msg, NULL);
  XtAddCallback(no_submenu, XmNcascadingCallback, cascading_msg, NULL);
  XtManageChild(no_submenu);
  XmStringFree(tcs);

  CommonPause();

  XtRemoveEventHandler(label, ButtonPressMask, False, PostIt, popup);

  /* instead, install a translation that will pop it up */

  n = 0;
  tcs = XmStringCreateSimple ("Popup Menu on MB1");
  XtSetArg (args[n], XmNlabelString, tcs); n++;
  XtSetValues (label, args, n);

  n = 0;
  XtSetArg (args[n], XmNwhichButton, 1); n++;
  XtSetValues (popup, args, n);

  XtOverrideTranslations (label, XtParseTranslationTable(menuTranslations));

  CommonPause();

  XtAppMainLoop(app_context);
  return(1);
}
