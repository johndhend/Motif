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
static char rcsid[] = "$XConsortium: MenuBar2.c /main/8 1995/07/13 18:47:08 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <signal.h>    

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>

#include <Xm/XmP.h>

#include <testlib.h>

#define BUFSIZE 32
#define MAXBUTTONS 12

Widget	menubar = NULL, BB = NULL, BBD = NULL, defBtn = NULL;
Widget	menu1 = NULL, submenu1 = NULL, submenu2 = NULL,
        pb1 = NULL, pb2 = NULL, toggle_RC = NULL, toggle_MS = NULL,
    	toggle_CB = NULL, toggle_CBG = NULL;
Widget  LabelScale, BorderScale, ChildrenScale;
   
XmStringCharSet	CharSet = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;

void PrintMe(Widget w, XtPointer client_data, XtPointer call_data)
{
  printf ("Accelerator activated this button...\n");
}

void DoItJoe(Widget w, XtPointer client_data, XtPointer call_data)
{
  int border, num_chars, num_children;
  char buf[BUFSIZE];
  char buf2[32];
  static int created = 0;
  int n, i;
  Arg args[30];
  Widget cascadeButtons[MAXBUTTONS];
  XmString LabelString1;
  XmString LabelString2;

  if (created)
    XtDestroyWidget(menubar);

  /* get some info */

  n = 0;
  XtSetArg(args[n], XmNvalue, &border); n++;
  XtGetValues (BorderScale, args, n);

  n = 0;
  XtSetArg(args[n], XmNvalue, &num_chars); n++;
  XtGetValues (LabelScale, args, n);

  n = 0;
  XtSetArg(args[n], XmNvalue, &num_children); n++;
  XtGetValues(ChildrenScale, args, n);
   
  n = 0;
  XtSetArg (args[n], XmNborderWidth, border); n++;
  menubar = XmCreateMenuBar(BB, "menubar", args, n);

  /*
   * XmPulldownMenu: submenu1
   */
   
  n = 0; 
  submenu1 = XmCreatePulldownMenu(menubar, "submenu1", args, n);

  /*
   * XmPulldownMenu: submenu2
   */
   
  n = 0; 
  submenu2 = XmCreatePulldownMenu(menubar, "submenu2", args, n);


  /*
   * XmPushButton: toggle_MS
   */

  LabelString1 = XmStringLtoRCreate("Toggle MenuShell", CharSet); 
  LabelString2 = XmStringCreate("Ctrl-M", XmSTRING_DEFAULT_CHARSET);
  n = 0; 
  XtSetArg(args[n], XmNlabelString,LabelString1); n++;
  XtSetArg(args[n], XmNaccelerator, "Ctrl<Key>M"); n++;
  XtSetArg(args[n], XmNacceleratorText,LabelString2); n++;
  toggle_MS = XmCreatePushButton(submenu1, "toggle_MS", args, n);
  XtAddCallback (toggle_MS, XmNactivateCallback, PrintMe, NULL);

  XtManageChild(toggle_MS);
  XmStringFree (LabelString1); 
  XmStringFree (LabelString2); 
  /*
   * XmPushButton: toggle_RC
   */

  n = 0; 
  LabelString1 = XmStringLtoRCreate("Toggle RowColumn", CharSet); 
  LabelString2 = XmStringCreate("Ctrl-R", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, LabelString1); n++;
  XtSetArg(args[n], XmNaccelerator, "Ctrl<Key>R"); n++;
  XtSetArg(args[n], XmNacceleratorText, LabelString2); n++;
	   
  toggle_RC = XmCreatePushButton(submenu1, "toggle_RC", args, n);

  XtManageChild(toggle_RC);
  XmStringFree (LabelString1);
  XmStringFree (LabelString2);
  /*
   * XmPushButton: toggle_CB
   */

  n = 0; 
  toggle_CB = XmCreatePushButton(submenu1, "toggle_CB", args, n);
  XtManageChild(toggle_CB);
   
  /*
   * XmPushButton: toggle_CBG
   */

  LabelString1 = XmStringLtoRCreate("Toggle CascadeButtonGadget", CharSet);
  LabelString2 = XmStringCreate("Ctrl-G", XmSTRING_DEFAULT_CHARSET); 
  n = 0; 
  XtSetArg(args[n], XmNlabelString, LabelString1); n++;
  XtSetArg(args[n], XmNaccelerator, "Ctrl<Key>G"); n++;
  XtSetArg(args[n], XmNacceleratorText, LabelString2); n++;
	 
  toggle_CBG = XmCreatePushButton(submenu1, "toggle_CBG", args, n);
  XtManageChild(toggle_CBG);
  XmStringFree (LabelString1);
  XmStringFree (LabelString2);

  /*
   * XmCascadeButton: menu1
   */

  n = 0;
  pb1 = XmCreatePushButtonGadget (submenu2, "pb1", args, n);
  pb2 = XmCreatePushButtonGadget (submenu2, "pb2", args, n);
  XtManageChild (pb1);
  XtManageChild (pb2);
 
  printf ("num_children is %d\n", num_children); 

  /* We need several button children, let's try this */
  for (i = 0; i <= (num_children - 1); i++)
    { n = 0;
      for (n = 0; n <= (num_chars - 1); n++)
	buf[n] = '+';
      buf[n] = '\0';

      LabelString1 =  XmStringCreate (&buf[0], XmSTRING_DEFAULT_CHARSET); 
      n = 0;
      XtSetArg(args[n], XmNlabelString, LabelString1); n++;
	      
      if (i%2)
	{
	  XtSetArg(args[n], XmNsubMenuId, submenu1); n++;
	}
      else
	{
	  XtSetArg(args[n], XmNsubMenuId, submenu2); n++;
	}	
      sprintf(buf2, "CascadeButton%d", i);
      printf ("I am creating child %d\n", i);

      cascadeButtons[i] = XmCreateCascadeButton(menubar,
						buf2,
						args, n);
      XtManageChild(cascadeButtons[i]);
      XmStringFree (LabelString1);
    }

  XtManageChild(menubar);

  created = 1;

}

int main(int argc, char *argv[])
{
  Arg args[20];
  XmString tcs;
  int n;
  int border;

  CommonTestInit(argc, argv);
    
  /* create a dialog shell to run things */
  /* a scale for border width, a scale for number of chars in label */
  /* and an okay button to make things go! */

  n = 0;
  XtSetArg(args[n], XmNautoUnmanage, False); n++;
  BBD = XmCreateFormDialog (Shell1, "BBD", args, n);

  n = 0;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  tcs = XmStringCreateSimple("Set 'em up, Joe");
  XtSetArg (args[n], XmNlabelString, tcs); n++;
  defBtn = XmCreatePushButtonGadget (BBD, "defBtn", args, n);
  XtManageChild (defBtn);
  XmStringFree(tcs);
  XtAddCallback (defBtn, XmNactivateCallback, DoItJoe, NULL);

  n = 0;
  XtSetArg (args[n], XmNdefaultButton, defBtn);
  XtSetValues (BBD, args, n);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNshowValue, True); n++;
  tcs = XmStringCreateSimple("Border Width");
  XtSetArg(args[n], XmNtitleString, tcs); n++;
  XtSetArg(args[n], XmNminimum, 0); n++;
  XtSetArg(args[n], XmNmaximum, 40); n++;
  XtSetArg(args[n], XmNvalue, 0); n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg (args[n], XmNtopWidget, defBtn); n++;
  XtSetArg (args[n], XmNtopOffset, 10); n++;
  BorderScale = XmCreateScale (BBD, "BorderScale", args, n);
  XmStringFree(tcs);
  XtManageChild (BorderScale);
   
  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNshowValue, True); n++;
  tcs = XmStringCreateSimple("# Chars in Label");
  XtSetArg(args[n], XmNtitleString, tcs); n++;
  XtSetArg(args[n], XmNminimum, 1); n++;
  XtSetArg(args[n], XmNmaximum, BUFSIZE - 1); n++;
  XtSetArg(args[n], XmNvalue, 1); n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg (args[n], XmNtopWidget, BorderScale); n++;
  XtSetArg (args[n], XmNtopOffset, 10); n++;
  LabelScale = XmCreateScale (BBD, "LabelScale", args, n);
  XtManageChild (LabelScale);
  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNshowValue, True); n++;
  tcs = XmStringCreateSimple("# Children");
  XtSetArg(args[n], XmNtitleString, tcs); n++;
  XtSetArg(args[n], XmNminimum, 1); n++;
  XtSetArg(args[n], XmNmaximum, MAXBUTTONS - 1); n++;
  XtSetArg(args[n], XmNvalue, 1); n++;
  XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg (args[n], XmNtopWidget, LabelScale); n++;
  XtSetArg (args[n], XmNtopOffset, 10); n++;
  ChildrenScale = XmCreateScale (BBD, "ChildrenScale", args, n);
  XtManageChild (ChildrenScale);
  XmStringFree(tcs);

  XtManageChild (BBD);

  /*
   * XmMenuBar: menubar
   */

  n = 0;
  XtSetArg (args[n], XmNheight, 400); n++;
  XtSetArg (args[n], XmNwidth, 300); n++;
  BB = XmCreateBulletinBoard (Shell1, "BB", args, n);

  /* call the callback */

  XtManageChild (BB);
  XtRealizeWidget(Shell1);

  CommonPause();
 
  XtAppMainLoop(app_context);
}










