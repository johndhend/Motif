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
static char rcsid[] = "$XConsortium: Label6.c /main/8 1995/07/13 19:09:18 drk $"
#endif
#endif
/*
 *  Create labels with and without font to test the correct search
 *  path for default fonts.
 */

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <testlib.h>

void main (argc, argv)
int argc;
char **argv;

{ 	
  Widget separator, menushell, bboard, bboard2, rowcolumn1, rowcolumn2;
  Widget rowcolumn3, label[15];
  Arg args[10];
  int j = 0, n;
  XmString tcs;
  XFontStruct *fnt;
  XmFontList  font1, font2, font3, font4;
  XmStringCharSet  cs = (char *) XmSTRING_DEFAULT_CHARSET;

  extern void post_menu_handler();

  /*  initialize toolkit  */
  CommonTestInit(argc, argv);

  font1 = CommonGetFontList("6x10");
  font2 = CommonGetFontList("8x13bold");
  font3 = CommonGetFontList("9x15bold");
  font4 = CommonGetFontList("8x13");

  n = 0;
  XtSetArg (args[n], XmNheight, 100 ); n++;
  XtSetArg (args[n], XmNwidth, 100 ); n++;
  bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);
  XtManageChild (bboard);

  n = 0;
  XtSetArg (args[n], XmNheight, 100 ); n++;
  XtSetArg (args[n], XmNwidth, 100 ); n++;
  XtSetArg (args[n], XmNdefaultFontList, font1);   n++;
  XtSetArg (args[n], XmNx, 300 ); n++; 
  XtSetArg (args[n], XmNy, 300 ); n++;  
  menushell= XmCreateMenuShell (bboard, "menushell", args, n);
  XtAddEventHandler(bboard, ButtonPressMask, FALSE, post_menu_handler,
		    menushell);

  n = 0;
  XtSetArg (args[n], XmNheight, 100 ); n++;
  XtSetArg (args[n], XmNwidth, 100 ); n++;
  XtSetArg (args[n], XmNx, 10 ); n++; 
  XtSetArg (args[n], XmNy, 50 ); n++;  
  rowcolumn1 = XmCreateRowColumn(bboard, "rowcolumn1", args, n);
  XtManageChild (rowcolumn1);

  n = 0;
  XtSetArg (args[n], XmNheight, 100 ); n++;
  XtSetArg (args[n], XmNwidth, 100 ); n++;
  rowcolumn2 = XmCreateRowColumn(menushell, "rowcolumn2", args, n);
  XtManageChild (rowcolumn2);

  /* labels in the menushell */

  n = 0;
  tcs = XmStringLtoRCreate("6x10", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  label[0] = XmCreateLabel (rowcolumn2, "label[0]", args, n);
  XtManageChild (label[0]);
  XmStringFree (tcs);

  n = 0;
  tcs = XmStringLtoRCreate("8x13", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  XtSetArg (args[n], XmNfontList, font4);      n++;
  label[1] = XmCreateLabel (rowcolumn2, "label[1]", args, n);
  XtManageChild (label[1]);
  XmStringFree (tcs);

  /* change fonts in the bulletinboard */
  n=0;
  XtSetArg (args[n], XmNseparatorType, XmSHADOW_ETCHED_OUT);	n++;
  separator = XmCreateSeparatorGadget (rowcolumn1, "separator", args, n);
  XtManageChild (separator);

  n = 0;
  tcs = XmStringLtoRCreate("fixed", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  label[2] = XmCreateLabel (rowcolumn1, "label[2]", args, n);
  XtManageChild (label[2]);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("8x13", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  XtSetArg (args[n], XmNfontList, font4);      n++;
  label[3] = XmCreateLabel (rowcolumn1, "label[3]", args, n);
  XtManageChild (label[3]);
  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNlabelFontList, font3); n++;
  XtSetValues(bboard, args, n);

  n = 0;
  tcs = XmStringLtoRCreate("9x15bold", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  label[4] = XmCreateLabel (rowcolumn1, "label[4]", args, n);
  XtManageChild (label[4]);
  XmStringFree(tcs);

  /* now try changing in another level of bulletin-board */

  n = 0;
  XtSetArg(args[n], XmNheight, 100 ); n++;
  XtSetArg(args[n], XmNwidth, 100 ); n++;
  bboard2 = XmCreateBulletinBoard(rowcolumn1, "bboard2", args, n);
  XtManageChild(bboard2);
    
  n = 0;
  XtSetArg(args[n], XmNheight, 100 ); n++;
  XtSetArg(args[n], XmNwidth, 100 ); n++;
  rowcolumn3 = XmCreateRowColumn(bboard2, "rowcolumn3", args, n);
  XtManageChild(rowcolumn3);

  n = 0;
  tcs = XmStringLtoRCreate("9x15bold", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);	n++;
  label[5] = XmCreateLabel (rowcolumn3, "label[5]", args, n);
  XtManageChild(label[5]);
  XmStringFree(tcs);

  n = 0;
  tcs = XmStringLtoRCreate("8x13", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);	n++;
  XtSetArg(args[n], XmNfontList, font4);      n++;
  label[6] = XmCreateLabel (rowcolumn3, "label[6]", args, n);
  XtManageChild(label[6]);
  XmStringFree(tcs);

  n = 0;
  XtSetArg(args[n], XmNlabelFontList, font2); n++;
  XtSetValues(bboard2, args, n);

  n = 0;
  tcs = XmStringLtoRCreate("8x13bold", XmSTRING_DEFAULT_CHARSET);
  XtSetArg (args[n], XmNlabelString, tcs);	n++;
  label[7] = XmCreateLabel (rowcolumn3, "label[7]", args, n);
  XtManageChild(label[7]);
  XmStringFree(tcs);
  XtRealizeWidget(Shell1);

  CommonPause();

  for (j = 0; j <=6; j++)
    {
      XtDestroyWidget(label[j]);
    }
  XtDestroyWidget(separator);
  XtDestroyWidget(rowcolumn3);
  XtDestroyWidget(bboard2);
  XtDestroyWidget(rowcolumn1);
  XtDestroyWidget(rowcolumn2);
  XtDestroyWidget(menushell);
  XtDestroyWidget(bboard);
  CommonPause();

  XtAppMainLoop(app_context);
}


void post_menu_handler (w, menu, event)
Widget w;
Widget menu;
XEvent *event;

{
   XmMenuPosition (menu, (XButtonPressedEvent *)event);
   XtManageChild(menu);
 }









