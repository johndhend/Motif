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
static char rcsid[] = "$XConsortium: SimpleM3.c /main/6 1995/07/13 18:40:41 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

/*  functions defined in this program  */

void main();
void activateCB(); /* Callback for the PushButton */

void PostIt(Widget w, XtPointer p, XEvent *event, Boolean *cont)
{
  Arg args[1];
  unsigned int whichButton;
  Widget popup = (Widget) p;
 
  XtSetArg (args[0], XmNwhichButton, &whichButton);
  XtGetValues (popup, args, 1);

  if (event->xbutton.button != whichButton)
    return;

  XmMenuPosition(popup, (XButtonPressedEvent *)event);
  XtManageChild(popup);
}

#define cs(string)  XmStringLtoRCreate(string, XmSTRING_DEFAULT_CHARSET)

static XmString XmNULL;

static void SimpleCallbackProc(Widget w,
					 XtPointer closure, XtPointer call_data)
{
  printf("selected=%d\n", (long) closure);
  switch ((long)closure) {
  case 4: exit(1);
    break;
  }
}

void main (argc,argv)
int argc;
char **argv;
{
  Widget form;
  Widget bar, option, popup, radio_box, check_box;
  Widget pd0, pd1, pd2;
  Arg args[10]; 
  register int n;

  XmNULL = cs("");

  CommonTestInit(argc, argv);

  n = 0;
  form = XmCreateForm(Shell1, "form", args, n);
  XtManageChild(form);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE); n++;
  XtSetArg(args[n], XmNbuttonCount, 3); n++; 
  bar = XmVaCreateSimpleMenuBar(form, "bar", 
				XmVaCASCADEBUTTON, cs("File"), (int) 'F',
				XmVaCASCADEBUTTON, cs("Edit"), (int) 'E',
				XmVaCASCADEBUTTON, cs("Help"), (int) 'H',
				NULL);
  XtSetValues(bar, args, n);
  XtManageChild(bar);

  pd0 = 
    XmVaCreateSimplePulldownMenu(bar, "pd0", 0, SimpleCallbackProc,
	      XmVaTITLE, cs("This is the Title"),
	      XmVaDOUBLE_SEPARATOR,
	      XmVaPUSHBUTTON, cs("New"), (int) 'N', "", XmNULL,
	      XmVaPUSHBUTTON, cs("Open..."), (int) 'O', "", XmNULL,
	      XmVaPUSHBUTTON, cs("Save"), (int) 'S', "", XmNULL,
	      XmVaPUSHBUTTON, cs("Save As..."), (int) 'A', "", XmNULL,
	      XmVaSEPARATOR,
	      XmVaPUSHBUTTON, cs("Exit"), (int) 'E', "", XmNULL, NULL);

  pd1 = XmVaCreateSimplePulldownMenu(bar, "pd1", 1, SimpleCallbackProc,
				     XmVaPUSHBUTTON, cs("Cut"), 
				     (int) 'C', "", XmNULL,
				     XmVaPUSHBUTTON, cs("Copy"), 	
				     (int) 'p', "", XmNULL,
				     XmVaPUSHBUTTON, cs("Paste"), 
				     (int) 'e', "", XmNULL,
				     NULL);

  pd2 = XmVaCreateSimplePulldownMenu(bar, "pd2", 2, (XtPointer) NULL,
				     XmVaPUSHBUTTON, cs("On Context..."), 
				     (int) ' ', "", XmNULL,
				     XmVaCHECKBUTTON, cs("On Help..."), 
				     (int) ' ', "", XmNULL,
				     XmVaRADIOBUTTON, cs("On Keys"), 
				     (int) ' ', "", XmNULL,
				     NULL);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNtopWidget, bar); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE); n++;
  option = XmVaCreateSimpleOptionMenu(form, "option", cs("MyLabel"), 
				      (KeySym) 'M', 1, SimpleCallbackProc,
				      XmVaPUSHBUTTON, cs("Red"), (int) 'R', 
				      "", XmNULL,
				      XmVaCASCADEBUTTON, cs("Help"), (int) 'H',
				      XmVaSEPARATOR,
				      XmVaPUSHBUTTON, cs("Green"), (int) 'G', 
				      "", XmNULL,
				      XmVaSEPARATOR,
				      XmVaPUSHBUTTON, cs("Blue"), (int) 'B', 
				      "", XmNULL,
				      NULL);
  XtSetValues(option, args, n);
  XtManageChild(option);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNtopWidget, option); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE); n++;
  radio_box = XmVaCreateSimpleRadioBox(form, "radio_box", 2, 
				       SimpleCallbackProc,
				       XmVaTOGGLEBUTTON, cs("Variable"), 
				       (int) 'V', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Fixed"), 
				       (int) 'F', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Times"), 
				       (int) 'T', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Courier"), 
				       (int) 'C', "", XmNULL,
				       NULL);

  XtSetValues(radio_box, args, n);
  XtManageChild(radio_box);

  n = 0;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNtopWidget, radio_box); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  check_box = XmVaCreateSimpleCheckBox(form, "check_box", SimpleCallbackProc,
				       XmVaTOGGLEBUTTON, cs("Burgers"), 
				       (int) 'B', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Fries"), 
				       (int) 'F', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Shake"), 
				       (int) 'S', "", XmNULL,
				       XmVaTOGGLEBUTTON, cs("Coke"), 
				       (int) 'C', "", XmNULL,
				       NULL);

  XtSetValues(check_box, args, n);
  XtManageChild(check_box);

  n = 0;
  popup = XmVaCreateSimplePopupMenu(form, "popup", SimpleCallbackProc,
				    XmVaTITLE, cs("This is the Title"),
				    XmVaDOUBLE_SEPARATOR,
				    XmVaPUSHBUTTON, cs("push1"), (int) 'B', 
				    "", XmNULL,
				    XmVaPUSHBUTTON, cs("push2"), (int) 'F', 
				    "", XmNULL,
				    XmVaCHECKBUTTON, cs("check1"), (int) 'S', 
				    "", XmNULL,
				    XmVaRADIOBUTTON, cs("radio1"), (int) 'C', 
				    "", XmNULL,
				    NULL);

  XtAddEventHandler(form, ButtonPressMask, False, PostIt, (XtPointer)popup);

  XtRealizeWidget(Shell1);

  CommonPause();
  CommonPause();  /* Exit */

  XtAppMainLoop(app_context);
}

