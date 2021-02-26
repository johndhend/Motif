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
static char rcsid[] = "$TOG: DrawArea2.c /main/11 1999/12/01 17:53:00 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */



/****************************************
*   Automatic test program generation   *
*              Version 1.2              *
*       Wed Apr  5 09:33:51 1989        *
****************************************/
#include <X11/Xlib.h>
#include <testlib.h>
#include "DrawArea2.h"

void ForceResize (w, client_data, call_data)
Widget w;
XtPointer client_data, call_data;

{
	Arg args[2];
	int n;
	Dimension height, width;

	n = 0;
	XtSetArg (args[n], XmNheight, &height); n++;
	XtSetArg (args[n], XmNwidth, &width); n++;
	XtGetValues ((Widget) client_data, args, n);

        n = 0;
        XtSetArg (args[n], XmNheight, height + 50); n++;
   	XtSetArg (args[n], XmNwidth, width + 50); n++;
	XtSetValues ((Widget) client_data, args, n);

}
	

void DrawStuff(widget, client_data, call_data)
Widget widget;
XtPointer client_data, call_data;
{ 
  XEvent *callingEvent;
  XmDrawingAreaCallbackStruct *inputCallback;
  static drawKeepStruct fromStruct = {0, 0, 1};
  drawKeepStruct toStruct;
  GC myGC;
  Drawable myWindow;
  XtGCMask valueMask;
  XGCValues values;
  Widget drawingWidget;

  int throwaway, i;
  char buffer[256];

#ifdef DEBUG
  printf ("                                                INPUT CALLBACK\n");
#endif

  for (i = 0; i <= 255; i++)
    buffer[i] = '\0';

  drawingWidget = (Widget) DrawingArea1;
  myWindow = XtWindow(drawingWidget);
  if (myWindow == NULL) 
    {  printf ("Null window, dummy.\n");
       exit (1);
     };

  values.foreground = XBlackPixel(display, 0);
  values.background = XWhitePixel(display, 0);
  values.line_width = 1;
  valueMask = GCForeground | GCBackground | GCLineWidth;
  myGC = XCreateGC(display, myWindow, valueMask, &values);

  inputCallback = (XmDrawingAreaCallbackStruct *) call_data;
  callingEvent = (XEvent *) inputCallback->event;

  if (callingEvent != NULL)
    { 
      /* do the work on a release only */
      if (callingEvent->xbutton.type == ButtonRelease)
	{ 
	  /* ok, we're gonna fill out the toStruct with info from event*/
	  toStruct.xpos = callingEvent->xkey.x;
	  toStruct.ypos = callingEvent->xkey.y;
	  toStruct.whichButton = callingEvent->xbutton.button;
   
	  /* if it's a button1 event, draw the line */
	  if (toStruct.whichButton == 1)
	    {
	      XDrawLine (display, myWindow, myGC, fromStruct.xpos, 
			 fromStruct.ypos,
			 toStruct.xpos,
			 toStruct.ypos);
	    }      
	  fromStruct.xpos = toStruct.xpos;
	  fromStruct.ypos = toStruct.ypos;
	  fromStruct.whichButton = toStruct.whichButton;
	}
      if (callingEvent->xkey.type == KeyPress) {
	 XLookupString ((XKeyEvent *) callingEvent,
			buffer,
			sizeof (buffer),
			NULL,
			NULL);
	printf ("Received keypress event for %s (0x%x)\n",
			buffer, buffer[0]);
       }
    }
  else
    { printf ("Hmm, the event seems to be NULL.");
    }

    /* Deallocate the Graphics Context. */
    XFreeGC( display, myGC );
}

void DrawAction (w, event, params, num_params)
Widget w;
XEvent *event;
String *params;
Cardinal *num_params;

{
  static XmDrawingAreaCallbackStruct cb;
  
  cb.reason = XmCR_INPUT;
  cb.event = event;
  cb.window = XtWindow(w);

  DrawStuff (w, NULL, &cb);

}
 
void ExposeRoutine(w,d1,d2)
	Widget w;
	XtPointer d1;
	XtPointer d2;
{

printf ("An expose event has been generated\n");

}

void HelpRoutine(w,d1,d2)
	Widget w;
	XtPointer d1;
	XtPointer d2;
{

printf ("An help event has been generated\n");

}

void
ResizeRoutine(widget, client_data, call_data)
Widget widget;
XtPointer call_data, client_data;
{

printf ("The resizeCallback was called.\n");
if ((((XmDrawingAreaCallbackStruct *) call_data)->event) == NULL)
  printf ("The event is NULL. This is expected.\n");
else printf ("The event is not NULL! This is an ERROR.\n");
/* begin test for PIR 4107 */
if (widget == NULL) 
  printf ("The widget is NULL! This is an ERROR.\n");
else
  printf ("The widget value is not NULL. This is expected.\n");
/* end test for PIR 4107 */

fflush (stdout);

}

void FocusRoutine(w,d1,d2)
	Widget w;
	XtPointer d1;
	XtPointer d2;
{
printf ("An focus event has been generated\n");
}

void  main (argc, argv)
    int     argc;
    char  **argv;
{
    Boolean            trace = False;
    register int       n;
    Arg                args[MAX_ARGS];
    XmString           tcs;
    Widget             BulletinBoard, PushButton, Frame;
    Widget             popupshell, msg_widget, DrawingArea2;
    static XtActionsRec actions[] = {{ "DrawAction", DrawAction}};
    static char translation_table[] = "<ButtonPress>: DrawAction()\n\
                                       <KeyPress>: DrawAction()";

   /* test for PIR 3062 (will be fixed in 1.2) */

    XFontStruct *newfont;
    XmFontList newfontlist;



    CommonTestInit(argc, argv);

    n = 0;
    BulletinBoard = XmCreateBulletinBoard(Shell1, "BulletinBoard", args, n);

    n = 0;
    PushButton = XmCreatePushButton (BulletinBoard, "PushButton", args, n);
   
    n = 0;
    XtSetArg(args[n], XmNshadowType, XmSHADOW_ETCHED_IN); n++;
    XtSetArg(args[n], XmNshadowThickness, 1); n++;
    XtSetArg(args[n], XmNy, 40); n++;
    Frame = XmCreateFrame (BulletinBoard, "Frame", args, n);

    n = 0;
   /* the following resource currently has no effect */
   /* the drawing area does not have a drawing routine to support it */

    XtSetArg (args[n], XmNshadowThickness, 10); n++;

    XtSetArg (args[n], XmNx, 0); n++;
    XtSetArg (args[n], XmNy, 200); n++;
    XtSetArg (args[n], XmNheight, 300); n++;
    XtSetArg (args[n], XmNwidth, 300); n++;
    DrawingArea1 = XmCreateDrawingArea(Frame, "DrawingArea1", args, n);
    XtAddCallback (DrawingArea1, XmNexposeCallback, ExposeRoutine, NULL);
    XtAddCallback (DrawingArea1, XmNinputCallback, DrawStuff, NULL);
    XtAddCallback (DrawingArea1, XmNhelpCallback, HelpRoutine, NULL);
/*    focus callback is not supported for Drawing Area                    */
/*    XtAddCallback (DrawingArea1, XmNfocusCallback, FocusRoutine, NULL); */
    XtAddCallback (DrawingArea1, XmNresizeCallback, ResizeRoutine, NULL);

   XtAddCallback (PushButton, XmNactivateCallback, ForceResize, (XtPointer)
	DrawingArea1);

    XtManageChild(DrawingArea1);
    XtManageChild(Frame);
    XtManageChild(PushButton);
    XtManageChild(BulletinBoard);
    XtRealizeWidget(Shell1);
    
    CommonPause(); /* list instructions */

    XtRemoveCallback(DrawingArea1, XmNinputCallback, DrawStuff, NULL);


    XtAppAddActions(app_context, actions, 1);
    XtOverrideTranslations(DrawingArea1,
			   XtParseTranslationTable(translation_table));    

    CommonPause();

    /* start test for PIR 2772 */
    /* test for P3062 */

    newfont = XLoadQueryFont(XtDisplay(Shell1), "variable");
    newfontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);


    n = 0;
    XtSetArg(args[n], XmNwidth, 200); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    popupshell = XtCreatePopupShell("Shell2", topLevelShellWidgetClass,
				       Shell1, args, n);

    n = 0;
    DrawingArea2 = XmCreateDrawingArea (popupshell, "DrawingArea2", 
					args, n);

    n = 0;
    XtSetArg(args[n], XmNlabelString,
	   XmStringCreate("Put the focus in this window.", 
			  XmSTRING_DEFAULT_CHARSET)); n++;
/* test for P3062 */

    XtSetArg(args[n], XmNfontList, newfontlist); n++;

    msg_widget = XmCreateLabelGadget (DrawingArea2, "msg_widget", args, n);

    XtManageChild(msg_widget);
    XtManageChild(DrawingArea2);
    XtRealizeWidget(popupshell);
    XtPopup(popupshell, XtGrabNone);

    CommonPause();

    /* end test for PIR 2772 */

    XtAppMainLoop(app_context);
}
