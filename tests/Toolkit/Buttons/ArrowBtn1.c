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
static char rcsid[] = "$XConsortium: ArrowBtn1.c /main/7 1995/07/13 17:28:12 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.2              *
*       Tue Apr  4 12:26:53 1989        *
****************************************/

#include <testlib.h>

Widget ArrowButton1;

static void do_activate(w, client, call)
Widget w;
XtPointer client, call;
{
  XmAnyCallbackStruct *cb;

  cb = (XmAnyCallbackStruct *) call;
  if (cb->event == NULL)
    printf ("ACTIVATED. Error! Event is NULL!\n");
  else
    printf ("ACTIVATED.\n");
}

static void do_arm(w, client, call)
Widget w;
XtPointer client, call;
{
  printf("armed\n");
}

static void do_disarm(w, client, call)
Widget w;
XtPointer client, call;
{
  printf("disarmed\n");
}

static XtCallbackRec activate_selected[] = { do_activate, NULL, NULL, NULL };
static XtCallbackRec arm_selected[]      = { do_arm,      NULL, NULL, NULL };
static XtCallbackRec disarm_selected[]   = { do_disarm,   NULL, NULL, NULL };

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XmString           tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  n = 0;
  ArrowButton1 = XmCreateArrowButton(Shell1, "ArrowButton1", args, n);
  XtManageChild(ArrowButton1);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_LEFT);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_RIGHT);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, 0);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  printf("trying illegal arrow direction\n");
  n = 0;
  XtSetArg(args[n], XmNarrowDirection, 100);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  printf("trying illegal arrow direction\n");
  n = 0;
  XtSetArg(args[n], XmNarrowDirection, 5);  n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  printf("trying to set up activate callback\n");
  n = 0;
  XtSetArg(args[n], XmNactivateCallback, activate_selected); n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  printf("trying to set up arm callback\n");
  n = 0;
  XtSetArg(args[n], XmNarmCallback, arm_selected); n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  printf("trying to set up disarm callback\n");
  n = 0;
  XtSetArg(args[n], XmNdisarmCallback, disarm_selected); n++;
  XtSetValues(ArrowButton1, args, n);
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(ArrowButton1);
}






































