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
static char rcsid[] = "$XConsortium: Scale9.c /main/6 1995/07/13 19:13:08 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a scale with three labels in it.
 *
 ************************************************************************/
#include <testlib.h>

/*  Forward declarations  */

static void ButtonCallback1();
static void ButtonCallback2();
static void ButtonCallback3();

Widget scale;
int max;
int min;


void main (argc,argv)
int argc;
char **argv;
{
   Arg args[MAX_ARGS];
   register int	n;
   Widget label1, label2, label3;
   Widget b;


   /*  initialize toolkit  */
    CommonTestInit(argc, argv);

   /*  Set up arglist and create the scale  */

   n = 0;
   scale = XmCreateScale(Shell1, "scaleWidget", args, n); 
   XtManageChild (scale);

   /* Get Maximum value of slider */

   n = 0;
   XtSetArg (args[n], XmNmaximum, &max); n++;
   XtSetArg (args[n], XmNminimum, &min); n++;
   XtGetValues (scale, args, n);

   /*  Create the push button labels for the scale  */

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label1 = XmCreatePushButton (scale, "Push_5_More", args, 0);
   XtManageChild (label1);

   XtAddCallback (label1, XmNactivateCallback, ButtonCallback1, NULL);

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label2 = XmCreatePushButton (scale, "Push_Max", args, 0);
   XtManageChild (label2);

   XtAddCallback (label2, XmNactivateCallback, ButtonCallback2, NULL);

   n = 0;
   XtSetArg (args[n], XmNborderWidth, 1);	n++;
   label3 = XmCreatePushButton (scale, "Push_Min", args, 0);
   XtManageChild (label3);

   XtAddCallback (label3, XmNactivateCallback, ButtonCallback3, NULL);

   /*  realize widgets  */

   XtRealizeWidget (Shell1);

   CommonPause();

   /* Change orientation to HORIZONTAL and repeat testing */

   n = 0;
   XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
   XtSetArg (args[n], XmNscaleWidth, 250); n++;
   XtSetArg (args[n], XmNscaleHeight, 15); n++;
   XtSetValues (scale, args, n);

   CommonPause();

   /*  process events  */

   XtAppMainLoop(app_context);
}
                                   

static void ButtonCallback1 (sw, closure, call_data)
Widget sw;
caddr_t closure;
caddr_t call_data;
{
   int slider;

   XmScaleGetValue (scale, &slider);

   printf ("new slider = %d\n", slider + 5);

/* This used to be XmScaleSetSlider() */
   XmScaleSetValue (scale, slider + 5);
}


static void ButtonCallback2 (sw, closure, call_data)
Widget sw;
caddr_t closure;
caddr_t call_data;
{
/* This used to be XmScaleSetSlider() */

   XmScaleSetValue (scale, max);
}


static void ButtonCallback3 (sw, closure, call_data)
Widget sw;
caddr_t closure;
caddr_t call_data;
{
/* This used to be XmScaleSetSlider() */

   XmScaleSetValue (scale, min);
}
