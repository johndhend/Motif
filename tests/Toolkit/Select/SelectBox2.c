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
static char rcsid[] = "$XConsortium: SelectBox2.c /main/9 1995/07/13 19:19:40 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/* 
 * Create a selection box with menu bar and button children, as detailed in
 *  the Motif 1.2 specification
 */

#include <signal.h>
#include <testlib.h>

#define NUM_NAMES 5
#define LIBBY 1
#define THOMAS 2
#define ROGER 3
#define CARL 4
#define SUSAN 5

char *Istrings[] = {
  "Libby", "Thomas", "Roger", "Carl", "Susan"
  };

Widget sbox;            /* Selection Box widget   */
Widget pushButton, toggleButton, arrowButton, drawnButton;
Widget menuBar, cascButton1, cascButton2, pulldown1, pulldown2;
Widget buttonsa[3], buttonsb[3];
Widget drawingArea, label1, listw;

Boolean men_set = True;

/* callbacks */

static void HelpCB();

static XtCallbackRec help_cb[] = {
  { HelpCB, NULL},
  { NULL, NULL}
};


/*-------------------------------------------------------------
**      HelpCB        - callback for help button
*/

/* ARGSUSED */

static void HelpCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  printf("Help Callback received\n");
}

/* ARGSUSED */

static void pickTomCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  XmString engstr;

  engstr = XmStringCreateLtoR("Thomas", XmSTRING_DEFAULT_CHARSET);

  /*
   *  Deselect all selected items
   */

  XmListDeselectAllItems(listw);
  XmListSelectItem(listw, engstr, True);
  XmStringFree(engstr);
}


/* ARGSUSED */

static void noMenCB(Widget w, XtPointer client_data, 
		    XmToggleButtonCallbackStruct *call_data)
{

  int i,n;
  XmString namelist[3];

  i = 0;
  /* Convert the items to Xm strings */
  for (n = 1; n < NUM_NAMES - 1; n++)
    {
      namelist[i] = XmStringCreateLtoR((char *)Istrings[n],
					XmSTRING_DEFAULT_CHARSET);
      i++;
    }

  if (call_data->set == True)
    {
      men_set = False;
      XmListDeleteItems(listw, namelist, 3);
    }
  else
    {
      XmListAddItems(listw, namelist, 3, 2);
      men_set = True;
    }
}

/* ARGSUSED */

static void nextEngCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  int *position_array, position_count;
  XmListGetSelectedPos(listw, &position_array, &position_count);

  XmListDeselectAllItems(listw);

  /*
   * Select Previous one
   */

  if (position_count != 0)
    if (position_array[0] == 1) 
      XmListSelectPos(listw, 0, True);
    else
      XmListSelectPos(listw, position_array[0] - 1, True);
}

/* ARGSUSED */

static void resetTextCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Arg args[10];
  XmString tcs;

  tcs = XmStringLtoRCreate("This region contains helpful information about your favorite QA Engineer. \n\n After selecting an engineer, press OK for the info.",
			   XmSTRING_DEFAULT_CHARSET);

  XtSetArg(args[0], XmNlabelString, tcs);
  XtSetValues(label1, args, 1);

  XmStringFree(tcs);

}

/* ARGSUSED */

static void changeTextCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  Arg args[10];
  int qa_engineer;
  XmString tcs;
  Boolean need_to_free = False;

  int *position_array, position_count;

  if (XmListGetSelectedPos(listw, &position_array, &position_count))
    need_to_free = True;
  else
    return;

  if (position_count == 0)
    return;

  /*
   * Display message
   */

  if (men_set)
    qa_engineer = position_array[0];
  else
    {
      if (position_array[0] == THOMAS)
	qa_engineer = SUSAN;
      else
	qa_engineer = position_array[0];
    }

  switch (qa_engineer) {
  
  case LIBBY:
    tcs = XmStringLtoRCreate("Libby is the fearless manager of the group and a big cat fan (no size preference though).\n  She's an excellent cook and always has delicious leftovers for lunch that we all envy.",
			     XmSTRING_DEFAULT_CHARSET);
    break;	

  case THOMAS:
    tcs = XmStringLtoRCreate("Thomas is the VTS whiz of the group and a quick \n bug finder.  He enjoys chicken patty sandwiches, fast cars, and picking on Roger.",
			     XmSTRING_DEFAULT_CHARSET);
    break;	

  case ROGER:
    tcs = XmStringLtoRCreate("M.S. Ramesh by his given name (don't ask what the M and S stand for!),\n Roger works on making Motif perform faster.",
			     XmSTRING_DEFAULT_CHARSET);
    break;	

  case CARL:
    tcs = XmStringLtoRCreate("Carl (Dr. Purz) is the bug keeper.  He can be found racing his \nBMW when he's not cranking out scripts and cranking his stereo.",
			     XmSTRING_DEFAULT_CHARSET);
    break;	

  case SUSAN:
    tcs = XmStringLtoRCreate("Susan is the Menu/memory/miscellaneous QA Engineer who created this very different test!\nShe is very fond of Jamaica and chewing on pens",
			     XmSTRING_DEFAULT_CHARSET);
    break;	
  }
    
  XtSetArg(args[0], XmNlabelString, tcs);
  XtSetValues(label1, args, 1);

  XmStringFree(tcs);

  if (need_to_free == True)
    XtFree((XtPointer) position_array);
}

/* ARGSUSED */

static void managerCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  XmString mgrstr;

  mgrstr = XmStringCreateLtoR("Libby", XmSTRING_DEFAULT_CHARSET);

  /*
   *  Deselect all selected items
   */

  XmListDeselectAllItems(listw);
  XmListSelectItem(listw, mgrstr, True);
  XmStringFree(mgrstr);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
  Arg args[10];       /*  arg list            */
  register int n;     /*  arg count           */
  XmString tcs, tcs1, namelist[NUM_NAMES], tcs2;

#ifndef MOTIF1_1

  /*  initialize toolkit */

  CommonTestInit(argc, argv);
  
  /* create selection box */

  /* Convert the items to Xm strings */
  for (n = 0; n < NUM_NAMES; n++)
    namelist[n] = XmStringCreateLtoR((char *)Istrings[n],
					XmSTRING_DEFAULT_CHARSET);
  tcs = XmStringCreateLtoR("(Enter Your Favorite QA Engineer here)",	
			   XmSTRING_DEFAULT_CHARSET);
  tcs1 = XmStringCreateLtoR("Motif QA Engineer ", 
			    XmSTRING_DEFAULT_CHARSET);
  tcs2 = XmStringCreateLtoR("Reset Text", XmSTRING_DEFAULT_CHARSET);
  
  n = 0;
  XtSetArg(args[n], XmNlistItemCount, NUM_NAMES); n++;
  XtSetArg(args[n], XmNlistItems, namelist); n++;
  XtSetArg(args[n], XmNdialogType, XmDIALOG_SELECTION); n++;
  XtSetArg(args[n], XmNcancelLabelString, tcs2); n++;
  XtSetArg(args[n], XmNhelpCallback, help_cb); n++;
  XtSetArg(args[n], XmNselectionLabelString, tcs); n++;
  XtSetArg(args[n], XmNtextString, tcs1); n++;
/*  XtSetArg(args[n], XmNchildPlacement, XmPLACE_BELOW_SELECTION); n++; */
  sbox = XmCreateSelectionBox(Shell1, "sbox", args, n);
  XmStringFree(tcs);
  XmStringFree(tcs1);
  XmStringFree(tcs2);

  XtAddCallback(sbox, XmNokCallback, changeTextCB, NULL);
  XtAddCallback(sbox, XmNcancelCallback, resetTextCB, NULL);

  /*
   *  Get the List widget id for future use
   */

  listw = XmSelectionBoxGetChild(sbox, XmDIALOG_LIST);

  n = 0;
  XtSetArg(args[n], XmNwidth, 100); n++;
  XtSetArg(args[n], XmNheight, 100); n++;
  XtSetArg(args[n], XmNborderWidth, 8); n++;
  drawingArea = XmCreateDrawingArea(sbox, "Drawarea", args, n);
  XtManageChild(drawingArea);

  n = 0;
  tcs = XmStringLtoRCreate("This region contains helpful information about your favorite QA Engineer. \n\n After selecting an engineer, press OK for the info.",
			   XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNalignment, XmALIGNMENT_CENTER); n++;
  XtSetArg(args[n], XmNrecomputeSize, TRUE); n++;
  label1 = XmCreateLabel(drawingArea, "label1", args, n);
  XtManageChild(label1);
  XmStringFree(tcs);

  n = 0;
  pushButton = XmCreatePushButton(sbox, "Pick Tom", args, n);
  XtManageChild(pushButton);
  XtAddCallback(pushButton, XmNactivateCallback, pickTomCB, NULL);
  
  n = 0;
  tcs = XmStringLtoRCreate("No Men", XmSTRING_DEFAULT_CHARSET); 
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  XtSetArg(args[n], XmNborderWidth, 1); n++;
  toggleButton = XmCreateToggleButton(sbox, "NoMen", args, n);
  XmStringFree(tcs);
  XtManageChild(toggleButton);
  XtAddCallback(toggleButton, XmNvalueChangedCallback, 
		(XtCallbackProc) noMenCB, NULL);

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_UP); n++;
  arrowButton = XmCreateArrowButton(sbox, "arrowButton", args, n);
  XtManageChild(arrowButton);
  XtAddCallback(arrowButton, XmNactivateCallback, nextEngCB, NULL);

  n = 0;
  tcs = XmStringLtoRCreate("Select the Manager", XmSTRING_DEFAULT_CHARSET);
/*  XtSetArg(args[n], XmNheight, 25); n++; */
  XtSetArg(args[n], XmNpushButtonEnabled, True); n++;
  XtSetArg(args[n], XmNlabelString, tcs); n++;
  drawnButton = XmCreateDrawnButton(sbox, "drawnbutton", args, n);
  XmStringFree(tcs);
  XtManageChild(drawnButton);
  XtAddCallback(drawnButton, XmNactivateCallback, managerCB, NULL);

  n = 0;
  menuBar = XmCreateMenuBar(sbox, "menuBar", args, n);
  XtManageChild(menuBar); 

  n = 0;
  pulldown1 = XmCreatePulldownMenu(menuBar, "Pulldown1", args, n);
  pulldown2 = XmCreatePulldownMenu(menuBar, "Pulldown2", args, n);

  n = 0;
  XtSetArg(args[n], XmNsubMenuId, pulldown1); n++;
  cascButton1 = XmCreateCascadeButton(menuBar, "Cascade1", args, n);
  XtManageChild(cascButton1);

  n = 0;
  XtSetArg(args[n], XmNsubMenuId, pulldown2); n++;
  cascButton2 = XmCreateCascadeButton(menuBar, "Cascade2", args, n);
  XtManageChild(cascButton2);

  buttonsa[0] = XmCreatePushButton(pulldown1, "button11", NULL, 0);
  buttonsa[1] = XmCreatePushButton(pulldown1, "button12", NULL, 0);
  buttonsa[2] = XmCreatePushButton(pulldown1, "button13", NULL, 0);
  buttonsb[0] = XmCreatePushButton(pulldown2, "button21", NULL, 0);
  buttonsb[1] = XmCreateSeparator(pulldown2, "separator22", NULL, 0);
  buttonsb[2] = XmCreatePushButton(pulldown2, "button31", NULL, 0);
  XtManageChildren(buttonsa, 3);
  XtManageChildren(buttonsb, 3);

  XtManageChild(sbox);
  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_ABOVE_SELECTION); n++;
  XtSetValues(sbox, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_BELOW_SELECTION); n++;
  XtSetValues(sbox, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNchildPlacement, XmPLACE_TOP); n++;
  XtSetValues(sbox, args, n);
  CommonPause();
  CommonPause();  /* Exit */

  /*  process events  */
  XtAppMainLoop(app_context);

#else

  printf("This test is for 1.2 only\n");
  exit(0);

#endif
}
