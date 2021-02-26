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
static char rcsid[] = "$XConsortium: SimpleM1.c /main/6 1995/07/13 18:39:06 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

int activation_count;

char  *name[] = {  "button 1",     "button 2",     "button 3"};
char  *cname[] = { "cascade 1",    "cascade 2",    "cascade 3"};
char  *pname[] = { "popup push",   "popup toggle", "popup radio",
                   "popup cascade","popup sep",    "popup 2sep",
                   "popup title"};

XmButtonType button_type[] = {XmPUSHBUTTON,XmTOGGLEBUTTON,XmRADIOBUTTON,
				XmCASCADEBUTTON,XmSEPARATOR,
				XmDOUBLE_SEPARATOR,XmTITLE};

Widget simple_pulldown = NULL,
  second_pulldown = NULL, alternate_simple_pulldown = NULL;

/*
 * Toggle the option menu's associated pulldown between 
 * two different pulldown menus 
 */

void change_option_menu(Widget widget, XtPointer option_menu,
			XtPointer call_data)
{
 Arg args[1];
 XtSetArg(args[0],XmNsubMenuId,alternate_simple_pulldown);
 XtSetValues((Widget) option_menu,args,1);

 /* 
  * Desensitize the push button
  */

 XtSetArg(args[0], XmNsensitive, False);
 XtSetValues(widget, args, 1);
}

/* print activation information to stdout */

void simple_activation(Widget widget, XtPointer client_data,
		       XtPointer call_data)
{
 printf("Simple activate called from widget %ld; client data %ld.\n",
	(long int) widget, (long int) client_data);
}

void pop_handler(Widget widget, XtPointer client_data, XEvent *the_event,
		 Boolean *continue_to_dispatch)
{
  printf("Event handler called with ");
  printf("button = %d\n", the_event->xbutton.button);

  if (the_event->xbutton.button == 3)
    {	
      XmMenuPosition(client_data, (XButtonPressedEvent *)the_event);
      XtManageChild((Widget) client_data);
    }
}

/* popup the popup menu passed as client data */

void pop(Widget widget, XtPointer client_data, XtPointer call_data)
{
  printf("Callback Proc called\n");
  XmMenuPosition((Widget) client_data, 
	   (XButtonPressedEvent *) ((XmAnyCallbackStruct *)call_data)->event);
  XtManageChild((Widget) client_data);
}

/* add a cascade button gadget to the menubar passed as client_data */

void add_cascade_gadget(Widget widget, XtPointer client_data, 
			XtPointer call_data)
{
  Arg args[2];
  int n;
  XtSetArg(args[0], XmNsubMenuId, second_pulldown);
  XtManageChild(XmCreateCascadeButtonGadget((Widget) client_data,
					    "new_cascade",
					    args,1));
  n=0;
  XtSetArg(args[n], XmNpostFromButton, 3); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  second_pulldown = XmCreateSimplePulldownMenu((Widget) client_data, 
					       "second", args, n);
}

void main(int argc, char **argv)
{
  Widget mainwin,  bboard,  menubar, pb,  om,  popup;
  XmString xmsarray[3];
  XmString pull_xmsarray[3];
  XmString alternate_xmsarray[3];
  XmString radio_xmsarray[3];
  XmString work_xmsarray[3];
  XmString popup_xmsarray[7];
  XmString acceltextarray[3];
  String accelarray[3];
  Arg args[10];
  int n, x;

  CommonTestInit(argc,  argv);

  mainwin = XmCreateMainWindow(Shell1, "mainwin", NULL, 0);
  XtManageChild(mainwin);

  for(x = 0; x < 7; x++) {
    popup_xmsarray[x] = XmStringCreate(pname[x], "");
  }

  for(x = 0; x < 3; x++) {
    char temp[20];
    sprintf(temp, "cascade %d", x);
    xmsarray[x] = XmStringCreate(temp, "");
    sprintf(temp, "pulldown %d", x);
    pull_xmsarray[x] = XmStringCreate(temp, "");
    sprintf(temp, "alternate %d", x);
    alternate_xmsarray[x] = XmStringCreate(temp, "");
    sprintf(temp, "radio %d", x);
    radio_xmsarray[x] = XmStringCreate(temp, "");
    sprintf(temp, "work %d", x);
    work_xmsarray[x] = XmStringCreate(temp, "");
    sprintf(temp, "Ctrl<Key>%d", x);
    accelarray[x] = XtCalloc(strlen(temp)+1, sizeof(char));
    strcpy(accelarray[x], temp);
    sprintf(temp, "Ctrl+%d", x);
    acceltextarray[x] = XmStringCreate(temp, "");
  }

  n=0;
  XtSetArg(args[n], XmNbuttons, xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;

  /*add this when certain of mnemonic behavior */
  /*XtSetArg(args[n], XmNbuttonMnemonics, mnemarray); n++;*/

  menubar = XmCreateSimpleMenuBar(mainwin, "menubar", args, n);
  XtManageChild(menubar);

  bboard = XmCreateBulletinBoard(mainwin, "bboard", NULL, 0);
  XtManageChild(bboard);

  n=0;
  XtSetArg(args[n], XmNbuttons, pull_xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  XtSetArg(args[n], XmNpostFromButton, 1); n++;
  XtSetArg(args[n], XmNbuttonAccelerators, accelarray); n++;
  XtSetArg(args[n], XmNbuttonAcceleratorText, acceltextarray); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  simple_pulldown = XmCreateSimplePulldownMenu(menubar, "simple", args, n);

  n=0;
  XtSetArg(args[n], XmNbuttons, alternate_xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  alternate_simple_pulldown = 
    XmCreateSimplePulldownMenu(bboard, "alternate_simple", args, n);

  n=0;
  XtSetArg(args[n], XmNbuttons, xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  XtSetArg(args[n], XmNoptionLabel, XmStringCreate("options", "")); n++;
  XtManageChild(om=XmCreateSimpleOptionMenu(bboard, "option", args, n));

  n=0;
  XtSetArg(args[n], XmNy, 60); n++;
  XtManageChild(pb=XmCreatePushButton(bboard, "Pop Simple Popup Menu 1", 
				      args, n));

  n=0;
  XtSetArg(args[n], XmNbuttons, popup_xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 7); n++;
  XtSetArg(args[n], XmNbuttonType, button_type); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  popup=XmCreateSimplePopupMenu(bboard, "popup", args, n);

  XtAddEventHandler(bboard, ButtonPressMask, FALSE, pop_handler, popup);
  XtAddCallback(pb, XmNactivateCallback, pop, popup);

  n=0;
  XtSetArg(args[n], XmNx, 290); n++;
  XtSetArg(args[n], XmNy, 60); n++;
  XtManageChild(pb=XmCreatePushButton(bboard, "Change Option Menu", args, n));
  XtAddCallback(pb, XmNactivateCallback, change_option_menu, om);

  n=0;
  XtSetArg(args[n], XmNx, 420); n++;
  XtSetArg(args[n], XmNy, 60); n++;
  XtManageChild(pb=XmCreatePushButton(bboard, 
				      "Add CascGadget to Menubar", args, n));
  XtAddCallback(pb, XmNactivateCallback, add_cascade_gadget, menubar);

  n=0;
  XtSetArg(args[n], XmNy, 90); n++;
  XtSetArg(args[n], XmNbuttons, radio_xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  XtSetArg(args[n], XmNbuttonSet, 1); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  XtManageChild(XmCreateSimpleRadioBox(bboard, "popup", args, n));

  n=0;
  XtSetArg(args[n], XmNy, 90); n++;
  XtSetArg(args[n], XmNx, 150); n++;
  XtSetArg(args[n], XmNbuttons, work_xmsarray); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++;
  XtSetArg(args[n], XmNsimpleCallback, simple_activation); n++;
  XtManageChild(XmCreateSimpleCheckBox(bboard, "popup", args, n));

  for(x = 0; x < 7; x++) {
    XmStringFree(popup_xmsarray[x]);
  }

  for(x = 0; x < 3; x++) {
    XmStringFree(xmsarray[x]);
    XmStringFree(pull_xmsarray[x]);
    XmStringFree(alternate_xmsarray[x]);
    XmStringFree(radio_xmsarray[x]);
    XmStringFree(work_xmsarray[x]);
    XtFree(accelarray[x]);
    XmStringFree(acceltextarray[x]);
  }

  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();
  CommonPause();

  CommonPause();
  CommonPause();
  CommonPause();

  CommonPause();
  CommonPause();
  CommonPause();

  XtAppMainLoop(app_context);
}











