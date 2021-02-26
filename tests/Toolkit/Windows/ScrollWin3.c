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
static char rcsid[] = "$XConsortium: ScrollWin3.c /main/8 1995/07/13 19:49:07 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>

Widget  DrawingArea1;
Widget  ScrolledWindow2;
Widget  vertSB, horizSB;
Widget	Text1;
Widget	Clip1;

static void  ResizeDrawAreaCB();
static void  ChangeCallback();

#define	SLIDER_SIZE	10


void CreateScrollBars(parent)
Widget parent;
{
    Arg args[10];
    int n;

    n = 0;
    XtSetArg (args[n], XmNorientation, XmVERTICAL);  n++;
    XtSetArg (args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg (args[n], XmNmaximum, 60);  n++;
    XtSetArg (args[n], XmNminimum, 0);  n++;
    XtSetArg (args[n], XmNtraversalOn, True);  n++;
    XtSetArg (args[n], XmNhighlightOnEnter, True);  n++;
    XtSetArg (args[n], XmNhighlightThickness, 2);  n++;
    XtSetArg (args[n], XmNsliderSize, SLIDER_SIZE);  n++;
    vertSB = XmCreateScrollBar (parent, "vertSB", args, n);
    XtManageChild (vertSB);

    XtAddCallback (vertSB, XmNvalueChangedCallback, ChangeCallback , NULL);

    n = 0;
    XtSetArg (args[n], XmNorientation, XmHORIZONTAL);  n++;
    XtSetArg (args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg (args[n], XmNmaximum, 59);  n++;
    XtSetArg (args[n], XmNminimum, 0);  n++;
    XtSetArg (args[n], XmNtraversalOn, True);  n++;
    XtSetArg (args[n], XmNhighlightOnEnter, True);  n++;
    XtSetArg (args[n], XmNhighlightThickness, 2);  n++;
    XtSetArg (args[n], XmNsliderSize, SLIDER_SIZE);  n++;
    horizSB = XmCreateScrollBar (parent, "horizSB", args, n);

    XtAddCallback (horizSB, XmNvalueChangedCallback, ChangeCallback , NULL);

    XtManageChild (horizSB);
}

static void ChangeCallback(w, client_data, call_data)
Widget   w;
XtPointer client_data;
XtPointer call_data;
{
    int val_h, val_v, val;
    Arg args[5];
    int n = 0;

    n = 0;
    XtSetArg(args[n], XmNvalue, &val_h);  n++;
    XtGetValues (horizSB, args, n);

    n = 0;
    XtSetArg(args[n], XmNvalue, &val_v);  n++;
    XtGetValues (vertSB, args, n);

    val = (51 * (val_v / SLIDER_SIZE)) + val_h;

    n = 0;
    XtSetArg(args[n], XmNcursorPosition, val);  n++;
    XtSetValues (Text1, args, n);
}

void TranslationProc(w, ev, p, np)
Widget w;
XEvent *ev;
String *p;
Cardinal *np;
{

#ifndef BESTCASE
    XmProcessTraversal(ScrolledWindow2, XmTRAVERSE_CURRENT);
#endif  /* BESTCASE */

    printf("Translation successfully set.\n");
}

static XtActionsRec actions[] =
{
    {"TranslationProc", TranslationProc}
};


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    Pixel         colorVal;
    Dimension	  height, width;
    char	  *value = "This is a long string which will test the         \nscrolling Features of an Application created      \nwith XmNscrollingPolicy set to XmAPPLICTION_      \nDEFINED. It should be contained on four lines     \nwith very long text horizontally. It will not     \nbe editable so dont try to modify any text!!!     ";
    static String translations = "<Key>t: TranslationProc()";
    XtTranslations new_table;

    CommonTestInit(argc, argv);
    
    /* test case for PIR 3180 */
    XtAppAddActions(app_context, actions, XtNumber(actions));

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);  n++; 
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmTOP_RIGHT);  n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    ScrolledWindow2 = XmCreateScrolledWindow(Shell1, "ScrolledWindow2", 
        args, n);
    XtManageChild(ScrolledWindow2);
    /* end of test case for PIR 3180 */
  
    /* test case for PIR 2945 */
    n = 0;
    XtSetArg(args[n], XmNclipWindow, &Clip1);  n++;
    XtGetValues(ScrolledWindow2, args, n);
  
    /* add some translations to that widget */
    new_table = XtParseTranslationTable(translations);
    XtOverrideTranslations(Clip1, new_table);
    /* end of test case for PIR 2945 */
    
    XtRealizeWidget(Shell1);

    CommonPause();

    XtDestroyWidget(ScrolledWindow2);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);  n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmBOTTOM_RIGHT);  n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    ScrolledWindow2 = XmCreateScrolledWindow(Shell1, "ScrolledWindow2", 
	args, n);
    XtManageChild(ScrolledWindow2);

    n=0;
    XtSetArg (args[n], XmNbackground, CommonGetColor("green"));  n++;
    DrawingArea1 = XmCreateDrawingArea
		(ScrolledWindow2, "DrawingArea1", args , n);
    XtManageChild (DrawingArea1);

    n = 0;
    XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
    XtSetArg (args[n], XmNeditable, False);  n++;
    XtSetArg (args[n], XmNrows, 4);  n++;
    XtSetArg (args[n], XmNcolumns, 30);  n++;
    XtSetArg (args[n], XmNwordWrap, False);  n++;
    XtSetArg (args[n], XmNvalue, value);  n++;
    Text1 = XmCreateText(DrawingArea1, "Text1", args, n);
    XtManageChild (Text1);

    CreateScrollBars (ScrolledWindow2);
    XmScrolledWindowSetAreas (ScrolledWindow2, horizSB, vertSB, DrawingArea1);


    CommonPause();
    CommonPause();

    XtDestroyWidget(ScrolledWindow2);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);  n++;
    XtSetArg(args[n], XmNvisualPolicy, XmCONSTANT);  n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);  n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmTOP_RIGHT);  n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    ScrolledWindow2 = XmCreateScrolledWindow(Shell1, "ScrolledWindow2", 
	args, n);
    XtManageChild(ScrolledWindow2);

    n=0;
    XtSetArg (args[n], XmNbackground, CommonGetColor("green"));  n++;
    DrawingArea1 = XmCreateDrawingArea
		(ScrolledWindow2, "DrawingArea1", args , n);
    XtManageChild (DrawingArea1);

    n = 0;
    XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
    XtSetArg (args[n], XmNeditable, False);  n++;
    XtSetArg (args[n], XmNrows, 4);  n++;
    XtSetArg (args[n], XmNcolumns, 30);  n++;
    XtSetArg (args[n], XmNwordWrap, False);  n++;
    XtSetArg (args[n], XmNvalue, value);  n++;
    Text1 = XmCreateText(DrawingArea1, "Text1", args, n);
    XtManageChild (Text1);

    CreateScrollBars (ScrolledWindow2);
    XmScrolledWindowSetAreas (ScrolledWindow2, horizSB, vertSB, DrawingArea1);

    CommonPause();

    XtDestroyWidget(ScrolledWindow2);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);  n++;
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);  n++;
    XtSetArg(args[n], XmNscrollBarPlacement, XmBOTTOM_LEFT);  n++; 
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    ScrolledWindow2 = XmCreateScrolledWindow(Shell1, "ScrolledWindow2", 
	args, n);
    XtManageChild(ScrolledWindow2);

    n=0;
    XtSetArg (args[n], XmNbackground, CommonGetColor("green"));  n++;
    DrawingArea1 = XmCreateDrawingArea
		(ScrolledWindow2, "DrawingArea1", args , n);
    XtManageChild (DrawingArea1);

    n = 0;
    XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
    XtSetArg (args[n], XmNeditable, False);  n++;
    XtSetArg (args[n], XmNrows, 4);  n++;
    XtSetArg (args[n], XmNcolumns, 30);  n++;
    XtSetArg (args[n], XmNwordWrap, False);  n++;
    XtSetArg (args[n], XmNvalue, value);  n++;
    Text1 = XmCreateText(DrawingArea1, "Text1", args, n);
    XtManageChild (Text1);

    CreateScrollBars (ScrolledWindow2);
    XmScrolledWindowSetAreas (ScrolledWindow2, horizSB, vertSB, DrawingArea1);

    CommonPause();

    XtDestroyWidget(ScrolledWindow2);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);  n++; 
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);  n++; 
    XtSetArg(args[n], XmNscrollBarPlacement, XmBOTTOM_LEFT);  n++;
    XtSetArg(args[n], XmNbackground, CommonGetColor("aquamarine"));  n++;
    XtSetArg(args[n], XmNspacing, 10);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginHeight, 20);  n++;
    XtSetArg(args[n], XmNscrolledWindowMarginWidth, 20);  n++;
    ScrolledWindow2 = XmCreateScrolledWindow(Shell1, "ScrolledWindow2", 
	args, n);
    XtManageChild(ScrolledWindow2);

    n=0;
    XtSetArg (args[n], XmNbackground, CommonGetColor("green"));  n++;
    DrawingArea1 = XmCreateDrawingArea
		(ScrolledWindow2, "DrawingArea1", args , n);
    XtManageChild (DrawingArea1);

    n = 0;
    XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
    XtSetArg (args[n], XmNeditable, False);  n++;
    XtSetArg (args[n], XmNrows, 4);  n++;
    XtSetArg (args[n], XmNcolumns, 30);  n++;
    XtSetArg (args[n], XmNwordWrap, False);  n++;
    XtSetArg (args[n], XmNvalue, value);  n++;
    Text1 = XmCreateText(DrawingArea1, "Text1", args, n);
    XtManageChild (Text1);

/*    CreateScrollBars (ScrolledWindow2); */
    XmScrolledWindowSetAreas (ScrolledWindow2, NULL, NULL, DrawingArea1);

    CommonPause();

    XtAppMainLoop(app_context);
}
