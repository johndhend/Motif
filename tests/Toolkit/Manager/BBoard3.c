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
static char rcsid[] = "$XConsortium: BBoard3.c /main/7 1995/07/13 18:25:45 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

Widget	BulletinBoard1,
	PushButtonGadget1,
	PushButtonGadget2,
	PushButtonGadget3;

void  main(argc, argv)
    int     argc;
    char  **argv;
{
    Boolean       trace = False;
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    n = 0;
    BulletinBoard1 = XmCreateBulletinBoard(Shell1, "BulletinBoard1", args, n);
    XtManageChild(BulletinBoard1);

    n = 0;
    XtSetArg(args[n], XmNborderWidth, 3);  n++;
    XtSetValues(BulletinBoard1, args, n);

    n = 0;
    XtSetArg(args[n], XmNbackground, CommonGetColor("red"));  n++;
    XtSetValues(BulletinBoard1, args, n);

    CommonPause();

    n = 0;
    PushButtonGadget1 = XmCreatePushButtonGadget(BulletinBoard1,
                                                 "PushButtonGadget1", args, n);
    XtManageChild(PushButtonGadget1);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNmarginWidth, 10);  n++;
    XtSetArg(args[n], XmNmarginHeight, 5);  n++;
    PushButtonGadget2 = XmCreatePushButtonGadget(BulletinBoard1,
                                                 "PushButtonGadget2", args, n);
    XtManageChild(PushButtonGadget2);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNx, 50);  n++;
    XtSetValues(PushButtonGadget1, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNy, 50);  n++;
    XtSetValues(PushButtonGadget1, args, n);

    CommonPause();

    XtDestroyWidget(PushButtonGadget2);

    n = 0;
    XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
    XtSetArg(args[n], XmNhighlightThickness, 1);  n++;
    PushButtonGadget3 = XmCreatePushButtonGadget(BulletinBoard1,
                                                 "PushButtonGadget3", args, n);
    XtManageChild(PushButtonGadget3);

    CommonPause();

    XtDestroyWidget(BulletinBoard1);
    CommonPause();

    XtAppMainLoop(app_context);
}










