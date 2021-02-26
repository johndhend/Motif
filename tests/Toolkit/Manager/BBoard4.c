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
static char rcsid[] = "$XConsortium: BBoard4.c /main/7 1995/07/13 18:26:11 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */



#include <testlib.h>
 
Widget       Bb, Sel,Button, Dial;

 
void act (Widget, XtPointer, XtPointer);
int SelExists;



main(int argc, char *argv[])
{
    Arg          args[10];
    int         n;


    CommonTestInit (argc, argv); 

    n = 0;
    XtSetArg(args[n], XmNwidth, 400); n++;
    XtSetArg(args[n], XmNheight, 400); n++;
    Bb = XmCreateBulletinBoard(Shell1, "Bb", args, n);
    XtManageChild(Bb);
 
    n = 0;
    Sel = XmCreateSelectionBox(Bb, "Sel", args, n);
    XtManageChild(Sel);
    SelExists = 1;
 
    n = 0;
    XtSetArg(args[n], XmNautoUnmanage, False); n++;
    Dial = XmCreateFormDialog(Shell1, "Dial", args, n);
    
    n = 0;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNlabelString, XmStringCreateSimple("Destroy")); n++;
    Button = XmCreatePushButton(Dial, "Button", args, n);
    XtAddCallback(Button, XmNactivateCallback, act, NULL);

    XtManageChild(Button);
    XtManageChild(Dial);

    XtRealizeWidget(Shell1);
    XtAppMainLoop(app_context);
}


void act(Widget w,XtPointer client_data, XtPointer call_data)

{
  char *new_button;
  XmString xms;
  Arg args[10];
  int n;

  if (SelExists) 
    {
	printf("Destroying selection box\n");
	XtDestroyWidget(Sel);
	new_button = "Create";
	SelExists = 0;
    }
  else 
    {
	printf("Creating selection box\n");
	n = 0;
	Sel = XmCreateSelectionBox(Bb, "Sel", args, n);
	XtManageChild(Sel);
	new_button = "Destroy";
	SelExists = 1;
    }
    
   xms = XmStringCreateSimple(new_button);
  
   n=0;
   XtSetArg (args[n], XmNlabelString, xms); n++;
   XtSetValues(w, args, n);
   XmStringFree(xms);
}

