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
static char rcsid[] = "$XConsortium: Navigation5.c /main/7 1995/07/13 19:43:39 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

/*
 *  This test tests the XmNtraverseObsuredCallback and the XmScrollVisible
 *    function.  
 */


#include <testlib.h>

Widget PushButton1, PushButton2, PushButton3, PushButton4, PushButton5,
       PushButton6, PushButton7, PushButton8, PushButton9, PushButton10,
       PushButton11,PushButton12,PushButton13,PushButton14,PushButton15,
       ScrolledWindow1, RowColumn1, Toggle1, Text1;

static int margin = 0;

#ifndef MOTIF1_1

void traverse_cb(Widget w, XtPointer closure, 
		 XtPointer data)
{
    XmTraverseObscuredCallbackStruct *call_data = (XmTraverseObscuredCallbackStruct *)data ;
  printf("Traversing to invisible widget\n");
  if (call_data->reason != XmCR_OBSCURED_TRAVERSAL)
    printf("Callback reason incorrect!\n");

  XmScrollVisible(w,
		  call_data->traversal_destination,
		  margin,
		  margin);

}

#endif /* not MOTIF1_1 */


/*
 * This function tests the traversibility/functionality of an obscured
 * TextField.  It relaxes the packing constraint of the RowColumn
 * temporarily to NONE and restores it later.
 */

static void TestObscuredTextField( RowColumn1, Text1 )
Widget RowColumn1, Text1;
{
  register int n;
  Arg args[MAX_ARGS];
  Dimension textX, textY, textWid, textHgt;
  Dimension btnX, btnY, btnWid, btnHgt;
  unsigned char packing_type;
  Widget OB;

  n = 0;
  XtSetArg(args[n], XmNpacking, &packing_type); n++;
  XtGetValues(RowColumn1, args, n);

  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_NONE); n++;
  XtSetValues(RowColumn1, args, n);

  n = 0;
  XtSetArg(args[n], XmNx, &textX); n++;
  XtSetArg(args[n], XmNy, &textY); n++;
  XtSetArg(args[n], XmNwidth, &textWid); n++;
  XtSetArg(args[n], XmNheight, &textHgt); n++;
  XtGetValues(Text1, args, n);

  btnX = textX + textWid / 2;
  btnY = textY;
  btnWid = textWid / 5;
  btnHgt = textHgt * 3;

  n = 0;
  XtSetArg(args[n], XmNx, btnX); n++;
  XtSetArg(args[n], XmNy, btnY); n++;
  OB = XmCreatePushButton(RowColumn1, "OB", args, n);
  XtManageChild(OB);

  n = 0;
  XtSetArg(args[n], XmNwidth, btnWid); n++;
  XtSetArg(args[n], XmNheight, btnHgt); n++;
  XtSetValues(OB, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNpacking, packing_type); n++;
  XtSetValues(RowColumn1, args, n);
}

void  main(argc, argv)
int argc;
char **argv;
{

  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);
    
#ifndef MOTIF1_1
  n = 0;
  XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  n++;
  XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);  n++;
  XtSetArg(args[n], XmNvisualPolicy, XmCONSTANT); n++;
  XtSetArg(args[n], XmNshadowThickness, 4);  n++;
  ScrolledWindow1 = XmCreateScrolledWindow(Shell1, "ScrolledWindow1", 
					   args, n);

  XtAddCallback(ScrolledWindow1, XmNtraverseObscuredCallback, 
		traverse_cb, NULL);

  XtManageChild(ScrolledWindow1);
  XtRealizeWidget(Shell1);
 
  n = 0;
  RowColumn1 = XmCreateRowColumn(ScrolledWindow1, "RowColumn1", args, n);
  XtManageChild(RowColumn1);

  n = 0;
  PushButton1 = XmCreatePushButton(RowColumn1, "PushButton1", args, n);
  XtManageChild(PushButton1);

  n = 0;
  PushButton2 = XmCreatePushButton(RowColumn1, "PushButton2", args, n);
  XtManageChild(PushButton2);

  n = 0;
  PushButton3 = XmCreatePushButton(RowColumn1, "PushButton3", args, n);
  XtManageChild(PushButton3);

  n = 0;
  PushButton4 = XmCreatePushButton(RowColumn1, "PushButton4", args, n);
  XtManageChild(PushButton4);

  n = 0;
  PushButton5 = XmCreatePushButton(RowColumn1, "PushButton5", args, n);
  XtManageChild(PushButton5);

  n = 0;
  PushButton6 = XmCreatePushButton(RowColumn1, "PushButton6", args, n);
  XtManageChild(PushButton6);

  n = 0;
  PushButton7 = XmCreatePushButton(RowColumn1, "PushButton7", args, n);
  XtManageChild(PushButton7);

  n = 0;
  PushButton8 = XmCreatePushButton(RowColumn1, "PushButton8", args, n);
  XtManageChild(PushButton8);

  n = 0;
  PushButton9 = XmCreatePushButton(RowColumn1, "PushButton9", args, n);
  XtManageChild(PushButton9);

  n = 0;
  PushButton10 = XmCreatePushButton(RowColumn1, "PushButton10", args, n);
  XtManageChild(PushButton10);

  n = 0;
  PushButton11 = XmCreatePushButton(RowColumn1, "PushButton11", args, n);
  XtManageChild(PushButton11);

  n = 0;
  PushButton12 = XmCreatePushButton(RowColumn1, "PushButton12", args, n);
  XtManageChild(PushButton12);

  n = 0;
  PushButton13 = XmCreatePushButton(RowColumn1, "PushButton13", args, n);
  XtManageChild(PushButton13);

  n = 0;
  PushButton14 = XmCreatePushButton(RowColumn1, "PushButton14", args, n);
  XtManageChild(PushButton14);

  n = 0;
  PushButton15 = XmCreatePushButton(RowColumn1, "PushButton15", args, n);
  XtManageChild(PushButton15);


  CommonPause();

  /*
   * Change the layout of the RowColumn
   */

  margin+=5;

  n = 0;
  XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
  XtSetArg(args[n], XmNnumColumns, 4); n++;
  XtSetValues(RowColumn1, args, n);
  
  CommonPause();

  /*
   *  Add other children to the RowColumn to make sure
   *   the model doesn't break
   */

  margin+=5;

  n = 0;
  XtSetArg(args[n], XmNborderWidth, 1); n++;
  Toggle1 = XmCreateToggleButton(RowColumn1, "Toggle1Button", args, n); 
  XtManageChild(Toggle1);

  n = 0;
  Text1 = XmCreateTextField(RowColumn1, "Text1", args, n);
  XtManageChild(Text1);
  CommonPause();

#else  /* MOTIF1_1 */
  CommonPause();
  CommonPause();
#endif

  /* Add a button which obscures the TextField. */
  TestObscuredTextField( RowColumn1, Text1 );

  XtAppMainLoop(app_context);
}
