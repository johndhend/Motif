/* $XConsortium: PushBGadM1.c /main/5 1995/07/15 21:06:23 drk $ */
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


#include <testlib.h>

/*  Global Variables  */
Widget    Frame1;
Widget    PBGadget1;
Widget    PBWidget1;



static void ArmCB(Widget, XtPointer, XtPointer);
static void DisarmCB(Widget, XtPointer, XtPointer);
static void ActCB(Widget, XtPointer, XtPointer);


void  
main (int argc, char **argv)
{

  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;
  XmString string;

  CommonTestInit(argc, argv);
    
  


  n = 0;
  Frame1 = XmCreateFrame(Shell1, "Frame1", args, n); 
  XtManageChild(Frame1);

  /* tests for CR 4891, 5130 */

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, False); n++;
  string = XmStringLtoRCreate("Push Gadget Here", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelType, XmSTRING); n++; 
  XtSetArg(args[n], XmNlabelString, string); n++; 
  XtSetArg(args[n], XmNheight, 200); n++; 
  XtSetArg(args[n], XmNwidth, 200); n++; 
  XtSetArg (args[n], XmNhighlightThickness, 25); n++;
  PBGadget1 = XmCreatePushButtonGadget(Frame1, "PBGadget", args, n);
  XtManageChild(PBGadget1);

  /* add callbacks for select, arm, disarm */
  XtAddCallback(PBGadget1, XmNactivateCallback, ActCB, NULL);
  XtAddCallback(PBGadget1, XmNarmCallback, ArmCB, NULL);
  XtAddCallback(PBGadget1, XmNdisarmCallback, DisarmCB, NULL);

  XtRealizeWidget(Shell1);
 
  CommonPause();
  CommonPause();

  XtDestroyWidget(PBGadget1);

  /* test for CR 5130. */

  n = 0;
  XtSetArg(args[n], XmNfillOnArm, False); n++;
  string = XmStringLtoRCreate("Push Widget Here", XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelType, XmSTRING); n++; 
  XtSetArg(args[n], XmNlabelString, string); n++; 
  XtSetArg(args[n], XmNheight, 200); n++; 
  XtSetArg(args[n], XmNwidth, 200); n++; 
  XtSetArg (args[n], XmNhighlightThickness, 25); n++;
  PBWidget1 = XmCreatePushButton(Frame1, "PBWidget", args, n);
  XtManageChild(PBWidget1);

  CommonPause();


  XtAppMainLoop(app_context);

}

static void  
ActCB(Widget w, XtPointer client_data, XtPointer call_data)
{
    printf("PushButtonGadget Activated\n");
}


static void  
ArmCB(Widget w, XtPointer client_data, XtPointer call_data)
{
    printf("PushButtonGadget Armed\n");

}


static void  
DisarmCB(Widget w, XtPointer client_data, XtPointer call_data)
{
    printf("PushButtonGadget Disarmed\n");
    printf("*********************\n");
}

