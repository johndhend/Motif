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
static char rcsid[] = "$XConsortium: PopupMenu1.c /main/10 1995/07/13 18:51:11 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */


#include <testlib.h>

#define PUSHBUTTON 1
#define TOGGLEBUTTON 2
#define CASCADEBUTTON 3

Widget Label, PopupMenu1, Label1, Separator1, PushBtn1;
Widget ToggleBtn1, PullDown2, CascadeBtn1, Label2, Separator3;
Widget Separator2, ToggleBtn2, PullDown3, CascadeBtn2, Separator4;
Widget PushBtn2, Label3, PullDown4, CascadeBtn3;
Widget PushBtn3, PushBtn4, ToggleBtn3, Label4;

void CBHandler(Widget w, XtPointer client_data, XtPointer call_data)
{
  char *myname;
  CoreWidget  *tmpwidget;

  switch ( ((XmAnyCallbackStruct *)call_data)->reason)
    {    
    case XmCR_ARM:    
      printf ("Arm ");
      break;
    case XmCR_ACTIVATE:   
      printf ("Activate ");
      break;
    case XmCR_DISARM:
      printf ("Disarm ");
      break;
    case XmCR_VALUE_CHANGED:
      printf ("ValueChanged ");
      break;
    case XmCR_CASCADING:
      printf ("Cascading ");
      break;
    default:
      printf ("Other Callback ");
    }

  printf ("%s\n", XtName(w));
  XFlush(display);
  fflush(stdout);
}

static Widget CreateLabel(char *label, Widget parent)
{
    Widget widget;
    register int n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreateLabel(parent, label, args, n);
    XtManageChild(widget);
    XmStringFree(tcs);
    return(widget);
}

static Widget CreatePushButton(char *label, Widget parent)
{
    Widget widget;
    register int n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreatePushButton(parent, label, args, n);
    XtManageChild(widget);
    XtAddCallback (widget, XmNactivateCallback, CBHandler, 
		   (XtPointer) PUSHBUTTON);
    XtAddCallback (widget, XmNdisarmCallback, CBHandler, 
		   (XtPointer) PUSHBUTTON);
    XtAddCallback (widget, XmNarmCallback, CBHandler, 
		   (XtPointer) PUSHBUTTON);
    XmStringFree(tcs);
    return(widget);
}

static Widget CreateToggle(char *label, Widget parent)
{
    Widget widget;
    register int n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    widget = XmCreateToggleButton(parent, label, args, n);
    XtManageChild(widget);
    XtAddCallback (widget, XmNvalueChangedCallback, CBHandler, 
		   (XtPointer) TOGGLEBUTTON);
    XtAddCallback (widget, XmNdisarmCallback, CBHandler, 
		   (XtPointer) TOGGLEBUTTON);
    XtAddCallback (widget, XmNarmCallback, CBHandler, 
		   (XtPointer) TOGGLEBUTTON);
    XmStringFree(tcs);
    return(widget);
}

static Widget CreateSeparator(Widget parent, char *name)
{
    Widget widget;
    widget = XmCreateSeparator(parent, name, NULL, 0);
    XtManageChild(widget);
    return(widget);
}

static Widget CreatePullDown(Widget parent, char *name)
{
    Widget widget;
    widget = XmCreatePulldownMenu (parent, name, NULL, 0);
    return(widget);
}

static Widget CreateCascade(char *label, Widget submenu, Widget parent)
{
    Widget widget;
    register int n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNsubMenuId, submenu); n++;
    widget = XmCreateCascadeButton(parent, label, args,n);
    XtManageChild(widget);
    XtAddCallback(widget, XmNactivateCallback, CBHandler, 
		  (XtPointer) CASCADEBUTTON);
    XtAddCallback(widget, XmNcascadingCallback, CBHandler, 
		  (XtPointer) CASCADEBUTTON);
    XmStringFree(tcs);
    return(widget);
}

void PostMenu(Widget w, XtPointer popup, XEvent *event, Boolean *c)
{
  if (event->xbutton.button != Button3)
    return;

  XmMenuPosition((Widget) popup, (XButtonEvent *) event);
  XtManageChild((Widget) popup);
}

int main(int argc, char **argv)
{
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;
  XrmDatabase new_db, sav_db;

  CommonTestInit(argc, argv);
    
  /* Code for Pir2716 */

  XrmInitialize();

  new_db = XrmGetFileDatabase("PopupMenu1.db");
  
#ifdef MOTIF1_1
  XrmMergeDatabases(new_db, &(display->db));
#else
  sav_db = XtDatabase(display);
  XrmCombineDatabase(new_db, &sav_db, True);
#endif

  /* End code for Pir2716 */

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 40);   n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget(Shell1);

  Label = CreateLabel("SelectMe", Shell1);

  /*
   **  PopupMenu1
   */

  n = 0;
  PopupMenu1 = XmCreatePopupMenu(Label, "popMenu", args, n);
  XtAddEventHandler(Label, ButtonPressMask, False, PostMenu, 
		    (XtPointer) PopupMenu1);

  /*
   **  Menu1
   */

  Label1       = CreateLabel("Menu1", PopupMenu1);
  Separator1   = CreateSeparator(PopupMenu1, "Separator1");
  PushBtn1     = CreatePushButton("PushButton1", PopupMenu1);
  ToggleBtn1   = CreateToggle("Toggle1", PopupMenu1);
  PullDown2    = CreatePullDown(PopupMenu1, "Pulldown2");
  CascadeBtn1  = CreateCascade("Cascade1", PullDown2, PopupMenu1);

  /*
   **  Menu2
   */

  Label2       = CreateLabel("Menu2", PullDown2);
  Separator2   = CreateSeparator(PullDown2, "Separator2");
  ToggleBtn2   = CreateToggle("Toggle2", PullDown2);
  Separator3   = CreateSeparator(PullDown2, "Separator3");
  PullDown3    = CreatePullDown(PullDown2, "PullDown3");
  CascadeBtn2  = CreateCascade("Cascade2", PullDown3, PullDown2);
  Separator4   = CreateSeparator(PullDown2, "Separator4");
  PushBtn2     = CreatePushButton("PushButton2", PullDown2);

  /*
   **  Menu3
   */

  Label3       = CreateLabel("Menu3", PullDown3);
  PullDown4    = CreatePullDown(PullDown3, "PullDown4");
  CascadeBtn3  = CreateCascade("Cascade3", PullDown4, PullDown3);
  PushBtn3     = CreatePushButton("PushButton3", PullDown3);
  ToggleBtn3   = CreateToggle("Toggle3", PullDown3);

  /*
   **  Menu4
   */

  Label4       = CreateLabel("Menu4", PullDown4);
  PushBtn4     = CreatePushButton("PushButton4", PullDown4);

  CommonPause();
  CommonPause();
  CommonPause();
  CommonPause();

  XtAppMainLoop(app_context);
}
