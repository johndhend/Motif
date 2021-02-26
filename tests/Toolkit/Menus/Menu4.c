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
static char rcsid[] = "$XConsortium: Menu4.c /main/10 1995/07/13 18:45:14 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/StringDefs.h>
#include <X11/Vendor.h>

#include <Xm/XmP.h>
#include <Xm/RowColumnP.h>

/*************Some Globals***********************/

Widget separator;
Widget rc0, rc1, rc2;
Widget frame1, frame2;
Widget button1, button2, button3, button4, button5, button6;
Widget submenua, option1a, option2a, option3a, option4a, option5a,
  option6a, option7a;
Widget submenub, option1b, option2b, option3b, option4b, option5b, 
  option6b, option7b;
Widget option_menu1, option_menu2;
 
static void CreateOption();
static void CreateButtons();

void PrintName(Widget w,
XtPointer d1,
XtPointer d2)
{
  fprintf(stdout, "Widget %s was activated\n",
	  XrmQuarkToString(w->core.xrm_name));
}

void PrintName_2(Widget rc, XtPointer client_data, 
		 XtPointer rc_data)
{
  XmRowColumnCallbackStruct * rc_struct;
  
  rc_struct = (XmRowColumnCallbackStruct *)rc_data;

  fprintf(stdout, "Widget %s was activated\n", 
	  XrmQuarkToString(rc_struct->widget->core.xrm_name));
}

static XtCallbackRec PrintName_CB[] =
{
  {PrintName_2, NULL},
  {NULL, NULL}
};

void SetBadValues(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[2];
  int n;

  n = 0;
  XtSetArg(args[n], XmNorientation, XmNO_ORIENTATION); n++;
  XtSetArg(args[n], XmNrowColumnType, XmMENU_BAR); n++;
  XtSetValues(rc0, args, n);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  XtSetValues(option_menu1, args, n);

  XtSetSensitive(w, False);
}

void ChangeOrientation(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[1];
  int n;
  int *orientation;

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetValues(rc1, args, n);
  XtSetSensitive(w, False);
}

void ChangeUnit1(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[1];
  int n;

  n = 0;
  XtSetArg(args[n], XmNmarginHeight, 50); n++;
  XtSetValues(rc1, args, n);
  XtSetSensitive(w, False);
}

void ChangeUnit2(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[1];
  int n;

  n = 0;
  XtSetArg(args[n], XmNmarginWidth, 50); n++;
  XtSetValues(rc1, args, n);
  XtSetSensitive(w, False);
}


void ChangeUnit3(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[1];
  int n;

  n = 0;
  XtSetArg(args[n], XmNentryBorder, 10); n++;
  XtSetValues(rc1, args, n);
  XtSetSensitive(w, False);
}

void ChangeSpacing(Widget w,
XtPointer d1,
XtPointer d2)
{
  Arg args[1];
  int n;

  n = 0;
  XtSetArg(args[n], XmNspacing, 10); n++;
  XtSetValues(rc1, args, n);
  XtSetSensitive(w, False);
}

int main(int argc, char *argv[])
{
  XEvent event;
  Arg args[15];
  int n;

  CommonTestInit(argc, argv);

  /*
   * XmRowColumn: rc0
   */

  n = 0;
  XtSetArg(args[n], XmNorientation, -2); n++;
  XtSetArg(args[n], XmNpacking, -2); n++;
  XtSetArg(args[n], XmNrowColumnType, -2); n++;
  XtSetArg(args[n], XmNentryAlignment, -2); n++;
  rc0 = XmCreateRowColumn(Shell1, "rc0", args, n);
  XtManageChild(rc0);

  /*
   * XmRowColumn: rc1
   */

  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
  XtSetArg(args[n], XmNnumColumns, 3); n++;
  rc1 = XmCreateRowColumn(rc0, "rc1", (ArgList) args, n);
  XtManageChild(rc1);

  /*
   * XmSeparatorGadget: separator
   */

  separator = XmCreateSeparatorGadget(rc0, "separator", NULL, 0);
  XtManageChild(separator);
    
  /*
   * XmRowColumn: rc2
   */

  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  XtSetArg(args[n], XmNnumColumns, 1); n++;
  rc2 = XmCreateRowColumn(rc0, "rc2", (ArgList) args, n);
  XtManageChild(rc2);

  /*
   * Create the children of the first row-column manager
   */

  CreateButtons();
    
  /*
   * Create the children of the second row-column manager
   */

  CreateOption();

  /*
   * Realize the widget hierarchy
   */
   
  XtRealizeWidget (Shell1);

  CommonPause();
  CommonPause();
  CommonPause();

  XtDestroyWidget(rc0);
  CommonPause();

  XtAppMainLoop(app_context);
}

static void CreateButtons()
{
  button1 = XmCreatePushButton(rc1, "button1", NULL, 0);
  XtAddCallback(button1, XmNactivateCallback, SetBadValues, NULL); 
  XtManageChild(button1);

  button2 = XmCreatePushButton(rc1, "button2", NULL, 0);
  XtAddCallback(button2, XmNactivateCallback, ChangeOrientation, NULL); 
  XtManageChild(button2);

  button3 = XmCreatePushButton(rc1, "button3", NULL, 0);
  XtAddCallback(button3, XmNactivateCallback, ChangeUnit1, NULL); 
  XtManageChild(button3);

  button4 = XmCreatePushButton(rc1, "button4", NULL, 0);
  XtAddCallback(button4, XmNactivateCallback, ChangeUnit2, NULL); 
  XtManageChild(button4);

  button5 = XmCreatePushButton(rc1, "button5", NULL, 0);
  XtAddCallback(button5, XmNactivateCallback, ChangeUnit3, NULL); 
  XtManageChild(button5);

  button6 = XmCreatePushButton(rc1, "button6", NULL, 0);
  XtAddCallback(button6, XmNactivateCallback, ChangeSpacing, NULL); 
  XtManageChild(button6);
}

static void CreateOption()
{
   int n;
   Arg args[5];
   XmString string;

   /*
    * XmOptionMenu: option_menu1
    */

   n = 0;
   XtSetArg(args[n], XmNentryCallback, (XtArgVal) PrintName_CB); n++;
   submenua = (Widget)XmCreatePulldownMenu(rc2, "submenua", args, n);

   option1a = XmCreatePushButtonGadget(submenua, "option1a", NULL, 0);
   option2a = XmCreatePushButtonGadget(submenua, "option2a", NULL, 0);
   option3a = XmCreatePushButtonGadget(submenua, "option3a", NULL, 0);
   option4a = XmCreatePushButtonGadget(submenua, "option4a", NULL, 0);
   option5a = XmCreatePushButtonGadget(submenua, "option5a", NULL, 0);
   option6a = XmCreatePushButtonGadget(submenua, "option6a", NULL, 0);
   option7a = XmCreatePushButtonGadget(submenua, "option7a", NULL, 0);

   XtManageChild(option1a);
   XtManageChild(option2a);
   XtManageChild(option3a);
   XtManageChild(option4a);
   XtManageChild(option5a);
   XtManageChild(option6a);
   XtManageChild(option7a);

   string = XmStringCreateLtoR("OptionMenu1: ", XmSTRING_DEFAULT_CHARSET);
   n = 0; 
   XtSetArg(args[n], XmNsubMenuId, submenua); n++;
   XtSetArg(args[n], XmNlabelString, string); n++;
   option_menu1 = XmCreateOptionMenu(rc2, "option_menu1", args, n);
   XtManageChild(option_menu1);
   XmStringFree(string);

   /*
    * XmOptionMenu: option_menu2
    */

   submenub = (Widget)XmCreatePulldownMenu(rc2, "submenub", NULL, 0);

   option1b = XmCreatePushButtonGadget(submenub, "option1b", NULL, 0);
   XtAddCallback(option1b, XmNactivateCallback, PrintName, NULL);

   option2b = XmCreatePushButtonGadget(submenub, "option2b", NULL, 0);
   XtAddCallback(option2b, XmNactivateCallback, PrintName, NULL);

   option3b = XmCreatePushButtonGadget(submenub, "option3b", NULL, 0);
   XtAddCallback(option3b, XmNactivateCallback, PrintName, NULL);

   option4b = XmCreatePushButtonGadget(submenub, "option4b", NULL, 0);
   XtAddCallback(option4b, XmNactivateCallback, PrintName, NULL);

   option5b = XmCreatePushButtonGadget(submenub, "option5b", NULL, 0);
   XtAddCallback(option5b, XmNactivateCallback, PrintName, NULL);

   option6b = XmCreatePushButtonGadget(submenub, "option6b", NULL, 0);
   XtAddCallback(option6b, XmNactivateCallback, PrintName, NULL);

   option7b = XmCreatePushButtonGadget(submenub, "option7b", NULL, 0);
   XtAddCallback(option7b, XmNactivateCallback, PrintName, NULL);

   XtManageChild(option1b);
   XtManageChild(option2b);
   XtManageChild(option3b);
   XtManageChild(option4b);
   XtManageChild(option5b);
   XtManageChild(option6b);
   XtManageChild(option7b);

   string = XmStringCreateLtoR("OptionMenu2: ", XmSTRING_DEFAULT_CHARSET);

   n = 0; 
   XtSetArg(args[n], XmNsubMenuId, submenub); n++;
   XtSetArg(args[n], XmNmenuHistory, option4b); n++;
   XtSetArg(args[n], XmNlabelString, string); n++;
   option_menu2 = XmCreateOptionMenu(rc2, "option_menu2", args, n);
   XtManageChild(option_menu2);
   XmStringFree(string);
}

