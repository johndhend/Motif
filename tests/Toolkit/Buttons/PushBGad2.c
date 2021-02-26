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
static char rcsid[] = "$XConsortium: PushBGad2.c /main/8 1995/07/13 17:29:25 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <testlib.h>

void activate_msg(w, client_data, call_data)
Widget w;
XtPointer client_data;
XtPointer call_data; 
{
  int n;
  short show_as_default;
  Arg args[20];

  n=0;
  XtSetArg(args[n], XmNshowAsDefault, &show_as_default); n++; 
  XtGetValues(w, args, n);

  n=0;
  if (show_as_default == 5)
    {
      XtSetArg(args[n], XmNshowAsDefault,10); n++; 
    }
  else
    {
      XtSetArg(args[n], XmNshowAsDefault, 5); n++; 
    }
  XtSetValues(w, args, n);
}

void main (argc, argv)
int argc;
char **argv;

{
  Widget bboard;
  Widget pushbutton;
  Arg args[20];
  XmString string;
  int n;

  /* callback lists */

  static XtCallbackRec activateCBs[] =
    {
      { activate_msg, NULL },
      { NULL, NULL },
    };

  CommonTestInit(argc, argv);
    
  n=0;
  XtSetArg(args[n], XmNwidth, 200); n++;
  XtSetArg(args[n], XmNheight,200); n++;
  bboard = XmCreateFrame(Shell1,"bboard", args, n);

  n=0;
  XtSetArg(args[n], XmNwidth,100); n++; 
  XtSetArg(args[n], XmNheight,100); n++; 
  string = XmStringLtoRCreate("Push Here", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNactivateCallback, activateCBs); n++; 
  XtSetArg(args[n], XmNlabelType, XmSTRING); n++; 
  XtSetArg(args[n], XmNlabelString, string); n++; 
  pushbutton = XmCreatePushButtonGadget(bboard,"pushbutton" ,args,n); 

  XtManageChild (bboard);
  XtManageChild (pushbutton);

  XtRealizeWidget (Shell1);
   
  CommonPause(); /* now change background color of manager */

  n = 0;
  XtSetArg(args[n], XmNbackground, CommonGetColor("yellow")); n++;
  XtSetValues(bboard, args, n);

  CommonPause();

  XtAppMainLoop(app_context);
  XmStringFree(string);
  XtDestroyWidget(bboard);
  XtDestroyWidget(pushbutton);
}
