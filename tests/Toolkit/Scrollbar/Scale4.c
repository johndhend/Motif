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
static char rcsid[] = "$XConsortium: Scale4.c /main/6 1995/07/13 19:11:41 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <testlib.h>

void ScaleCallback (sw, client_data, data)
Widget sw;
XtPointer client_data;
XtPointer data;
{
XmScaleCallbackStruct *call_data=(XmScaleCallbackStruct *)data;
   printf ("	Value = %d\n", call_data->value);
}


void main (argc,argv)
int argc;
char **argv;

{
   Widget Scale1;
   Arg args[MAX_ARGS];
   register int	n;
   Widget label1, label2, label3;

    /*  initialize toolkit  */
    CommonTestInit(argc, argv);

   /*  Set up arglist and create the Scale1  */

   n = 0;
   Scale1 = XmCreateScale(Shell1, "Scale1", args, n); 
   XtManageChild (Scale1);
   XtAddCallback (Scale1, XmNvalueChangedCallback, CommonGenericCB, NULL);
   XtAddCallback (Scale1, XmNvalueChangedCallback, ScaleCallback, NULL);
   XtAddCallback (Scale1, XmNdragCallback,         CommonGenericCB, NULL);
   XtAddCallback (Scale1, XmNhelpCallback,         CommonGenericCB, NULL);
   XtAddCallback (Scale1, XmNhelpCallback,         ScaleCallback, NULL);


   /*  Create the labels for the Scale1  */

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label1 = XmCreateLabel (Scale1, "label1",  args, 0);
   XtManageChild (label1);

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label2 = XmCreateLabel (Scale1, "label2", args, 0);
   XtManageChild (label2);

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label3 = XmCreateLabel (Scale1, "label3", args, 0);
   XtManageChild (label3);


   /*  realize widgets  */

   XtRealizeWidget (Shell1);

   CommonPause();
   CommonPause();

   /* change orientation to XmHORIZONTAL for more testing */

   n = 0;
   XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
   XtSetArg (args[n], XmNscaleWidth, 250); n++;
   XtSetArg (args[n], XmNscaleHeight, 15); n++;
   XtSetValues (Scale1, args, n);

   CommonPause();
   CommonPause();

   /*  process events  */

   XtAppMainLoop(app_context);
}
