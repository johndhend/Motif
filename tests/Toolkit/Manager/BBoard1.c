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
static char rcsid[] = "$XConsortium: BBoard1.c /main/8 1995/07/13 18:25:20 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget	BulletinBoard1, BulletinBoard2, BulletinBoard3,
	PushButton1,
	PushButton2;
Widget	ScrollBar1,
	ArrowButton1,
	ArrowButton2;



void myHelpProc (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{
printf ("A help callback was issued.\n");

}

void  main(argc, argv)
    int     argc;
    char  **argv;
{
    Boolean       trace = False;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    static char translation1[] = "#augment \n\
                                  <Key>F1:     Help() ";
    /* if this is F1, the help callback is not made ! */

    static char translation2[]=  "Ctrl<Key>p:  ManagerGadgetActivate() ";

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    n = 0;
    XtSetArg (args[n], XmNtranslations, XtParseTranslationTable(translation1));
    n++;
    BulletinBoard1 = XmCreateBulletinBoard(Shell1, "BulletinBoard1", args, n);
    XtManageChild(BulletinBoard1);
    XmAddTabGroup(BulletinBoard1);
    XtAddCallback (BulletinBoard1, XmNhelpCallback, myHelpProc, NULL);

    n = 0;
    XtSetArg(args[n], XmNmarginWidth, 0);  n++;
    XtSetValues(BulletinBoard1, args, n);

    n = 0;
    XtSetArg(args[n], XmNmarginHeight, 0);  n++;
    XtSetValues(BulletinBoard1, args, n);
   
    n = 0;
    PushButton1 = XmCreatePushButtonGadget(BulletinBoard1, 
					   "PushButton1", args, n);
    XtManageChild(PushButton1);

    n = 0;
    XtSetArg(args[n], XmNx, 50);  n++;
    XtSetArg(args[n], XmNy, 150);  n++;
    PushButton2 = XmCreatePushButtonGadget(BulletinBoard1, 
					   "PushButton2", args, n);
    XtManageChild(PushButton2);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNy, 25);  n++;
    XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
    ScrollBar1 = XmCreateScrollBar(BulletinBoard1, "ScrollBar1", args, n);
    XtManageChild(ScrollBar1);

    n = 0;
    XtSetArg(args[n], XmNx, 100);  n++;
    XtSetArg(args[n], XmNy, 10); n++;		/* leave room for big hilite */
    XtSetArg(args[n], XmNwidth, 50);  n++;
    XtSetArg(args[n], XmNheight, 50);  n++;
    ArrowButton1 = XmCreateArrowButton(BulletinBoard1, 
				       "ArrowButton1", args, n);
    XtManageChild(ArrowButton1);
    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNx, 120);  n++;
    XtSetArg(args[n], XmNy, 230);  n++;
    ArrowButton2 = XmCreateArrowButton(BulletinBoard1, "ArrowButton2", args,
                                       n);
    XtManageChild(ArrowButton2);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);  n++;
    XtSetArg(args[n], XmNy, 20);  n++;
    XtSetArg(args[n], XmNheight, 29);  n++;
    XtSetArg(args[n], XmNwidth, 40);  n++;
    XtSetValues(ArrowButton2, args, n);

    n = 0;
    XtSetArg(args[n], XmNheight, 25);  n++;
    XtSetArg(args[n], XmNvalue, 70);  n++;
    XtSetArg(args[n], XmNsliderSize, 30);  n++;
    XtSetValues(ScrollBar1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNwidth, 150);  n++;
    XtSetArg(args[n], XmNheight, 42);  n++;
    XtSetValues(PushButton2, args, n);

    CommonPause();

    /* begin test for PIR 3256 */

    XtDestroyWidget (PushButton1);
    XtDestroyWidget (PushButton2);
    XtDestroyWidget (ScrollBar1);
    XtDestroyWidget (ArrowButton1);
    XtDestroyWidget (ArrowButton2);

    n = 0;
    XtSetArg (args[n], XmNshadowThickness, 10); n++;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    BulletinBoard2 = XmCreateBulletinBoard (BulletinBoard1, 
					    "BulletinBoard2", args, n);

    n = 0;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    XtSetArg (args[n], XmNx, 105); n++;
    BulletinBoard3 = XmCreateBulletinBoard (BulletinBoard1,
					    "BulletinBoard3", args, n);

  
    XtManageChild (BulletinBoard2);
    XtManageChild (BulletinBoard3);  
  
    CommonPause();

    XtDestroyWidget (BulletinBoard2);
    XtDestroyWidget (BulletinBoard3);

    n = 0;
    XtSetArg (args[n], XmNshadowThickness, 10); n++;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    BulletinBoard2 = XmCreateFrame (BulletinBoard1, 
				    "BulletinBoard2", args, n);

    n = 0;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    XtSetArg (args[n], XmNx, 105); n++;
    BulletinBoard3 = XmCreateFrame (BulletinBoard1,
				    "BulletinBoard3", args, n);

  
    XtManageChild (BulletinBoard2);
    XtManageChild (BulletinBoard3);  

    CommonPause();

    /* end test for PIR 3256 */

    XtAppMainLoop(app_context);
}










