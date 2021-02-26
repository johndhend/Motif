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
static char rcsid[] = "$XConsortium: TranslationsUil.c /main/4 1995/07/13 20:35:10 drk $"
#endif
#endif

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/TextF.h>
#include <Xm/TextFP.h>
#include <Mrm/MrmPublic.h>


static void actSetTextCb();
static void actquit();

static void SetTextCb();
static void quit();
static MrmHierarchy mrmId;
static char *mrmVec[]={"tst.uid"};
static MrmCode mrmClass;
static MRMRegisterArg mrmNames[] = {
  {"SetTextCb", (caddr_t)SetTextCb },
  {"quit", (caddr_t)quit }
};	

static  XtActionsRec  actions[] = {
  { "actSetTextCb", actSetTextCb },
  { "actquit",  actquit }, 
};

static XtAppContext  appContext;

static Widget appMain;
  
main(argc, argv)
     int argc;
     char *argv[];
{

  Widget shell;
  Display *display;
  char *uid;


  MrmInitialize ();


  XtToolkitInitialize();
  appContext = XtCreateApplicationContext();
  display = XtOpenDisplay(appContext, NULL, "test", "Test",
			  NULL, 0, &argc, argv);
  if (display == NULL) {
    fprintf(stderr, "%s:  Can't open display\n", argv[0]);
    exit(1);
  }

  shell = XtAppCreateShell("Uil Version", NULL, applicationShellWidgetClass,
			   display, NULL, 0);

  uid = XtMalloc (strlen (argv[0]) + 5);
  sprintf (uid, "%s.uid", argv[0]); 
  if (MrmOpenHierarchy (1, &uid, NULL, &mrmId) != MrmSUCCESS) exit(0);
  MrmRegisterNames(mrmNames, XtNumber(mrmNames));
  MrmFetchWidget (mrmId, "appMain", shell, &appMain, &mrmClass);
  XtManageChild(appMain);

  XtAppAddActions(appContext, actions, XtNumber(actions));
  
  XtRealizeWidget(shell);

  XtInstallAccelerators(XtNameToWidget(appMain, "text"),
                        XtNameToWidget(appMain, "squeeze"));
  
  XtAppMainLoop(appContext);


}

static void SetTextCb(w, id, cb)
     Widget w;
     char *id;
     XtPointer cb;
{
  Widget text = XtNameToWidget(appMain, id);
  char *value = XmTextFieldGetString (text);
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
  XtGetValues (XtNameToWidget(appMain, "squeeze"), args, n);
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




  
