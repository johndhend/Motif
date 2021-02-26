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
static char rcsid[] = "$XConsortium: TranslationsXt.c /main/4 1995/07/13 20:35:20 drk $"
#endif
#endif
  
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/PushB.h>
#include <Xm/ArrowB.h>
  
static void actSetTextCb();
static void actquit();

static void enter();
static void leave();

String button_trans = "<Btn1Down>, <Btn1Up>: actSetTextCb() \n\
                       Ctrl<Key>q: actquit()";
     
String appMain_trans = "Ctrl<Key>q: actquit()";
     
String text_trans = "Ctrl<Key>q: actquit() \n\
                     Ctrl<Key>b: beginning-of-line() \n\
                     Ctrl<Key>e: end-of-line() ";
     
String done_trans = "<Btn1Down>: actquit() \n\
                     Ctrl<Key>q: actquit()";
     
static  XtActionsRec  actions[] = {
  { "actSetTextCb", actSetTextCb },
  { "actquit",  actquit },
};
     
     
static XtAppContext  appContext;
     
static Widget appMain, shell, textfd, button, done; 
     
     
main(argc, argv)
     int argc;
     char *argv[];
{
  
  Display *display;
  Arg args[10];
  Boolean size;
  int n;
  XtAccelerators accels;
  
  
  XtToolkitInitialize();
  appContext = XtCreateApplicationContext();
  display = XtOpenDisplay(appContext, NULL, "test", "Test",
			  NULL, 0, &argc, argv);
  if (display == NULL) {
    fprintf(stderr, "%s:  Can't open display\n", argv[0]);
    exit(1);
  }
  
  
  shell = XtAppCreateShell("Xt Version", NULL, applicationShellWidgetClass,
			   display, NULL, 0);
  
  appMain = XmCreateForm(shell, "form", NULL, 0);
  XtOverrideTranslations(appMain, XtParseTranslationTable(appMain_trans)); 
  XtManageChild(appMain);
 
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNtopPosition, 0); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNbottomPosition, 100); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNleftPosition, 10);n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNrightPosition, 40); n++;
  
  textfd = XmCreateTextField(appMain, "text", args, n);
  XtOverrideTranslations(textfd, XtParseTranslationTable(text_trans)); 
  XtManageChild(textfd);
  
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNtopPosition, 0); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNbottomPosition, 100); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNleftPosition, 50);n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNrightPosition, 80); n++;
  
  button = XmCreatePushButton(appMain, "Change My Label", args, n);
  n = 0;
  XtSetArg(args[n], XmNdefaultButton, button); n++;
  XtSetValues(appMain, args, n);
  XtOverrideTranslations(button, XtParseTranslationTable(button_trans)); 
  XtManageChild(button);
  
  
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNtopPosition, 0); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNbottomPosition, 100); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNleftPosition, 85);n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_POSITION); n++;
  XtSetArg(args[n], XmNrightPosition, 95); n++;
  
  
  done = XmCreatePushButton(appMain, "Done", args, n);
  XtOverrideTranslations(done, XtParseTranslationTable(done_trans)); 
  XtManageChild(done);
  
  XtAppAddActions(appContext, actions, XtNumber(actions));
  
  XtRealizeWidget(shell);

  XtInstallAccelerators(textfd, button);
  
  XtAppMainLoop(appContext);
  
  
}

static void SetTextCb(w, id, cb)
     Widget w;
     char *id;
     XtPointer cb;
{
  Widget txt = XtNameToWidget(appMain, id); 
  char *value = XmTextFieldGetString (txt);
  XmString label = XmStringCreate (value, XmSTRING_DEFAULT_CHARSET); 
  Arg args[1];
  
  XtSetArg (args[0], XmNlabelString, label);
  XtSetValues (w, args, 1);
  XmStringFree (label);
}

static void quit(w, client_data, call_data )
     Widget w;
     XtPointer client_data;
     XtPointer call_data;
{
  Widget tw, fw;
  char *cp, *value;
  XmString label;
  Arg args[10];
  int n;
  
  cp = (char *)client_data;
  tw = XtNameToWidget(appMain, cp);
  value =  XmTextFieldGetString (tw);
  
  n = 0;
  XtSetArg (args[n], XmNlabelString, &label); n++;
  XtGetValues (button, args, n);
  XmStringGetLtoR(label, XmSTRING_DEFAULT_CHARSET, &cp);
  
  fw = XtParent(w);
  XtDestroyWidget(XtParent(fw));
  
  
  printf("\nThe current text field string : %s \n\n", value);
  
  printf("\nThe current Shift button label : %s \n\n", cp);
  
  
  exit(0);
}

static void actSetTextCb(w, event, pars, num_pars)
     Widget w;
     XEvent *event;
     String *pars;
     Cardinal *num_pars;
{
  SetTextCb(w, "*text", NULL);
  
}

static void actquit(w, event, pars, num_pars)
     Widget w;
     XEvent *event;
     String *pars;
     Cardinal *num_pars;
{
  
  quit(w, "*text", NULL);
  
}




