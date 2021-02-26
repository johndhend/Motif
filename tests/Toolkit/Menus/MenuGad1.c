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
static char rcsid[] = "$XConsortium: MenuGad1.c /main/9 1995/07/13 18:48:11 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

/*  Widgets */
Widget   MenuBar1, PullDown1, PullDown2, PullDown3, MenuBtn1, MenuBtn2;
Widget   MenuBtn3, Label1, Separator1, PushBtn1, ToggleBtn1, PullDown1A;
Widget   CascadeBtn1, Label2, Separator2, ToggleBtn2, PullDown2A;
Widget   Separator3, Separator4;
Widget   CascadeBtn2, PushBtn2, Label3, ToggleBtn3, PullDown3A;
Widget 	 CascadeBtn3, PushBtn3, Label1A, Separator1A, PushBtn1A, PushBtn1B;
Widget   PushBtn1C, Label2A, Separator2A, ToggleBtn2A, ToggleBtn2B,Label3A;
Widget   ToggleBtn2C, Separator3A, PullDown3AA, PullDown3BA, PullDown3CA;
Widget   CascadeBtn3A, CascadeBtn3B, CascadeBtn3C, Label3AA, Separator3AA;
Widget   PushBtn3AA, Label3BA, Separator3BA, ToggleBtn3BA, Label3CA;
Widget   Separator3CA, PullDown3CAA, CascadeBtn3CA, Label3CAA;

static Widget CreateMenuBar(Widget parent, char *name)
{
  Widget widget;

  widget = XmCreateMenuBar(parent, name, NULL, 0);
  XtManageChild(widget);

  return(widget);
}

static Widget CreateLabelGadget(char *label, Widget parent)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  widget = XmCreateLabelGadget(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

static Widget CreatePushButtonGadget(char *label, char mnemonic,
				     Widget parent)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
  widget = XmCreatePushButtonGadget(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

static Widget CreateToggleGadget(char *label, char mnemonic, Widget parent)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
  widget = XmCreateToggleButtonGadget(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

static Widget CreateSeparatorGadget(Widget parent, char *name)
{
  Widget widget;
  widget = XmCreateSeparatorGadget(parent, name, NULL, 0);
  XtManageChild(widget);
  return(widget);
}

static Widget CreatePullDown(Widget parent, char *name)
{
  Widget  widget;
  widget = XmCreatePulldownMenu (parent, name, NULL, 0);
  return(widget);
}

static Widget CreateCascade(char *label, char mnemonic, Widget submenu,
			    Widget parent)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
  XtSetArg(args[n], XmNsubMenuId, submenu); n++;
  widget = XmCreateCascadeButton(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);
  return(widget);
}

static Widget CreateCascadeGadget(char *label, char mnemonic,
				  Widget submenu, Widget parent)
{
  Widget widget;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
  XtSetArg(args[n], XmNsubMenuId, submenu); n++;
  widget = XmCreateCascadeButtonGadget(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

int main(int argc, char **argv)
{
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 40);   n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget(Shell1);

  /*
   **  MenuBar1
   */

  MenuBar1 = CreateMenuBar(Shell1, "MenuBar1");
  PullDown1     = CreatePullDown(MenuBar1, "PullDown1");
  MenuBtn1      = CreateCascade("Menu1", '1', PullDown1, MenuBar1);
  PullDown2     = CreatePullDown(MenuBar1, "PullDown2");
  MenuBtn2      = CreateCascade("Menu2", '2', PullDown2, MenuBar1);
  PullDown3     = CreatePullDown(MenuBar1, "PullDown3");
  MenuBtn3      = CreateCascade("Menu3", '3', PullDown3, MenuBar1);

  /*
   **  Menu1
   */

  Label1 = CreateLabelGadget("Menu1", PullDown1);
  Separator1    = CreateSeparatorGadget(PullDown1, "Separator1");
  PushBtn1      = CreatePushButtonGadget("pushbutton1", 'p', PullDown1);
  ToggleBtn1    = CreateToggleGadget("toggle1", 't', PullDown1);
  PullDown1A    = CreatePullDown(PullDown1, "PullDown1A");
  CascadeBtn1   = CreateCascadeGadget("cascade1", 'c', PullDown1A, PullDown1);

  /*
   **  Menu2
   */

  Label2 = CreateLabelGadget("Menu2", PullDown2);
  Separator2    = CreateSeparatorGadget(PullDown2, "Separator2");
  ToggleBtn2    = CreateToggleGadget("toggle2", 't', PullDown2);
  Separator3    = CreateSeparatorGadget(PullDown2, "Separator3");
  PullDown2A    = CreatePullDown(PullDown2, "PullDown2A");
  CascadeBtn2   = CreateCascadeGadget("cascade2", 'c', PullDown2A, PullDown2);
  Separator4    = CreateSeparatorGadget(PullDown2, "Separator4");
  PushBtn2      = CreatePushButtonGadget("pushButton2", 'p', PullDown2);

  /*
   **  Menu3
   */

  Label3        = CreateLabelGadget("Menu3", PullDown3);
  PullDown3A    = CreatePullDown(PullDown3, "PullDown3A");
  CascadeBtn3   = CreateCascadeGadget("cascade3", 'c', PullDown3A, PullDown3);
  PushBtn3      = CreatePushButtonGadget("pushbutton3", 'p', PullDown3);
  ToggleBtn3    = CreateToggleGadget("toggle3", 't', PullDown3);

  /*
   **  Menu1A
   */

  Label1A       = CreateLabelGadget("Menu1A", PullDown1A);
  Separator1A   = CreateSeparatorGadget(PullDown1A, "Separator1A");
  PushBtn1A     = CreatePushButtonGadget("pushbutton1A", 'A', PullDown1A);
  PushBtn1B     = CreatePushButtonGadget("pushbutton1B", 'B', PullDown1A);
  PushBtn1C     = CreatePushButtonGadget("pushbutton1C", 'C', PullDown1A);

  /*
   **  Menu2A
   */

  Label2A       = CreateLabelGadget("Menu2A", PullDown2A);
  Separator2A   = CreateSeparatorGadget(PullDown2A, "Separator2A");
  ToggleBtn2A   = CreateToggleGadget("toggle2A", 'A', PullDown2A);
  ToggleBtn2B   = CreateToggleGadget("toggle2B", 'B', PullDown2A);
  ToggleBtn2C   = CreateToggleGadget("toggle2C", 'C', PullDown2A);

  /*
   **  Menu3A
   */

  Label3A       = CreateLabelGadget("Menu3A", PullDown3A);
  Separator3A   = CreateSeparatorGadget(PullDown3A, "Separator3A");
  PullDown3AA   = CreatePullDown(PullDown3A, "PullDown3AA");
  CascadeBtn3A  = CreateCascadeGadget("cascade3A", 'A', PullDown3AA,
				      PullDown3A);
  PullDown3BA   = CreatePullDown(PullDown3A, "PullDown3BA");
  CascadeBtn3B  = CreateCascadeGadget("cascade3B", 'B', PullDown3BA,
				      PullDown3A);
  PullDown3CA   = CreatePullDown(PullDown3A, "PullDown3CA");
  CascadeBtn3C  = CreateCascadeGadget("cascade3C", 'C', PullDown3CA,
				      PullDown3A);

  /*
   **  Menu3AA
   */

  Label3AA      = CreateLabelGadget("Menu3AA", PullDown3AA);
  Separator3AA  = CreateSeparatorGadget(PullDown3AA, "Separator3AA");
  PushBtn3AA    = CreatePushButtonGadget("pushbutton3AA", 'p', PullDown3AA);

  /*
   **  Menu3BA
   */

  Label3BA      = CreateLabelGadget("Menu3BA", PullDown3BA);
  Separator3BA  = CreateSeparatorGadget(PullDown3BA, "Separator3BA");
  ToggleBtn3BA  = CreateToggleGadget("toggle3BA", 't', PullDown3BA);

  /*
   **  Menu3CA
   */

  Label3CA      = CreateLabelGadget("Menu3CA", PullDown3CA);
  Separator3CA  = CreateSeparatorGadget(PullDown3CA, "Separator3CA");
  PullDown3CAA  = CreatePullDown(PullDown3CA, "PullDown3CAA");
  CascadeBtn3CA = CreateCascadeGadget("cascade3CA", 'c', PullDown3CAA,
				      PullDown3CA);

  /*
   **  Menu3CAA
   */

  Label3CAA     = CreateLabelGadget("Menu3CAA", PullDown3CAA);

  CommonPause();
  CommonPause();
  CommonPause();
  CommonPause();

  XtAppMainLoop(app_context);
}














