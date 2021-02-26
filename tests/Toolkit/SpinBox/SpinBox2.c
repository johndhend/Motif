/* $XConsortium: SpinBox2.c /main/6 1996/04/30 13:56:08 schuldy $ */
/*
 *  (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 *  ALL RIGHTS RESERVED 
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

/*
 *  Global variables.
 */
Widget Parent, SpinBox1, TextF1;

void
ValueChanged(Widget w,XtPointer client_data,XtPointer call_data)
{

  int reason = ((XmSpinBoxCallbackStruct *) call_data)->reason;

  printf ("XmNvalueChangedCallback invoked ");
  
  switch (reason)
    {
    case XmCR_OK:
      printf ("reason = XmCR_OK\n\n");
      break;

    case XmCR_SPIN_NEXT:
      printf ("reason = XmCR_SPIN_NEXT\n");
      break;

    case XmCR_SPIN_PRIOR:
      printf ("reason = XmCR_SPIN_PRIOR\n");
      break;

    case XmCR_SPIN_FIRST:
      printf ("reason = XmCR_SPIN_FIRST\n");
      break;

    case XmCR_SPIN_LAST:
      printf ("reason = XmCR_SPIN_LAST\n");
      break;

    default:
      break;
   }

}

void
CrossedBound(Widget w,XtPointer client_data,XtPointer call_data)
{
  XmSpinBoxCallbackStruct *cb_struct = (XmSpinBoxCallbackStruct *)call_data;
  static  int  doit = True;

  printf("crossed_boundary = ");
  if ( cb_struct->crossed_boundary )
  {
     printf(" True\n");
     doit = (doit) ? False : True;
     cb_struct->doit = doit;
  }
  else
     printf(" False\n");
}

void
SetPosition(Widget w, XtPointer client_data, XtPointer call_data)
{
  XmSpinBoxCallbackStruct *cb_struct = (XmSpinBoxCallbackStruct *)call_data;
  Arg   args[5];
  int   n, min, max, incr, max_pos;

    n = 0;
    XtSetArg (args[n], XmNminimumValue, &min); n++;
    XtSetArg (args[n], XmNmaximumValue, &max); n++;
    XtSetArg (args[n], XmNincrementValue, &incr); n++;
    XtGetValues( TextF1, args, n );

    max_pos = ( incr > 0 ) ? ( max - min ) / incr : ( max - min ); 

    switch( cb_struct->reason )
    {
       case XmCR_SPIN_NEXT:
       case XmCR_SPIN_LAST:
            cb_struct->position = max_pos - 1;
            break;

       case XmCR_SPIN_PRIOR:
       case XmCR_SPIN_FIRST:
            cb_struct->position = max_pos;
            break;
    }
    cb_struct->doit = True;
}

void
ModifyVerify(Widget w,XtPointer client_data,XtPointer call_data)
{
  XmSpinBoxCallbackStruct *cb_struct = (XmSpinBoxCallbackStruct *)call_data;

  printf ("XmNmodifyVerifyCallback invoked, ");

  switch ( cb_struct->reason )
  {
    case XmCR_OK:
      printf ("reason = XmCR_OK\n");
      break;

    case XmCR_SPIN_NEXT:
      printf ("reason = XmCR_SPIN_NEXT\n");
      break;

    case XmCR_SPIN_PRIOR:
      printf ("reason = XmCR_SPIN_PRIOR\n");
      break;

    case XmCR_SPIN_FIRST:
      printf ("reason = XmCR_SPIN_FIRST\n");
      break;

    case XmCR_SPIN_LAST:
      printf ("reason = XmCR_SPIN_LAST\n");
      break;

    default:
      break;
    }
}

void
main (int argc, char **argv)
{
    Arg args[10];
    int n;

    CommonTestInit (argc, argv);

    n=0;
    Parent = XmCreateFrame (Shell1, "Frame", args, n);
    XtManageChild (Parent);

    n=0;
    XtSetArg (args[n], XmNarrowLayout, XmARROWS_FLAT_END); n++;
    XtSetArg (args[n], XmNrepeatDelay, 0); n++;
    XtSetArg (args[n], XmNarrowOrientation, XmHORIZONTAL); n++;
    SpinBox1 = XmCreateSpinBox (Parent, "SpinBox1", args, n);
    XtManageChild (SpinBox1);
    XtAddCallback (SpinBox1, XmNvalueChangedCallback, ValueChanged,
    (XtPointer)NULL);
    XtAddCallback (SpinBox1, XmNmodifyVerifyCallback, ModifyVerify,
    (XtPointer)0);


    n=0;
    XtSetArg (args[n], XmNspinBoxChildType, XmNUMERIC); n++;
    XtSetArg (args[n], XmNminimumValue, 1); n++;
    XtSetArg (args[n], XmNmaximumValue, 10); n++;
    XtSetArg (args[n], XmNincrementValue, 3); n++;
    XtSetArg (args[n], XmNposition, 2); n++;
    XtSetArg (args[n], XmNpositionType, XmPOSITION_INDEX); n++;
    TextF1 = XmCreateTextField (SpinBox1, "TextF1", args,n);
    XtManageChild (TextF1);

    XtRealizeWidget (Shell1);

    CommonPause();
    CommonPause();
   
    XtAddCallback( SpinBox1, XmNmodifyVerifyCallback, CrossedBound,
                   (XtPointer)0 );
    CommonPause();
    XtRemoveCallback( SpinBox1, XmNmodifyVerifyCallback, CrossedBound,
                      (XtPointer)0 );
    XtAddCallback( SpinBox1, XmNmodifyVerifyCallback, SetPosition,
                   (XtPointer)0 );
    CommonPause();
    XtRemoveCallback( SpinBox1, XmNmodifyVerifyCallback, SetPosition,
                      (XtPointer)0 );
    CommonPause();
    CommonPause();

    XtAppMainLoop (app_context);

    
}


