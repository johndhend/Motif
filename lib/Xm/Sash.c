
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: Sash.c /main/12 1995/07/13 17:51:55 drk $"
#endif
#endif
/* (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/* (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/* (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */



#include <X11/cursorfont.h>
#include "XmI.h"
#include <Xm/SashP.h>
#include <Xm/TransltnsP.h>
#include <Xm/DrawP.h>
#include <Xm/DisplayP.h>
#include "MenuStateI.h"
#include "TraversalI.h"

#define defTranslations		_XmSash_defTranslations
#define SASHSIZE 10

/********    Static Function Declarations    ********/

static void ClassPartInitialize( 
                        WidgetClass wc) ;
static void ClassInitialize( void ) ;
static void Initialize( 
                        Widget rw,
                        Widget nw,
                        ArgList args,
                        Cardinal *num_args) ;
static void HighlightSash( 
                        Widget sash) ;
static void UnhighlightSash( 
                        Widget sash) ;
static XmNavigability WidgetNavigable( 
                        Widget wid) ;
static void SashFocusIn( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void SashFocusOut( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void SashAction( 
                        Widget widget,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params) ;
static void Realize( 
                        register Widget w,
                        XtValueMask *p_valueMask,
                        XSetWindowAttributes *attributes) ;
static void Redisplay( 
                        Widget w,
                        XEvent *event,
                        Region region) ;

static void SashDisplayDestroyCallback ( 
			Widget w, 
			XtPointer client_data, 
			XtPointer call_data );
/********    End Static Function Declarations    ********/


static XtResource resources[] = {
   {XmNborderWidth, XmCBorderWidth, XmRHorizontalDimension, sizeof(Dimension),
      XtOffsetOf( struct _XmSashRec, core.border_width), XmRImmediate, (XtPointer) 0},

   {XmNcallback, XmCCallback, XmRCallback, sizeof(XtCallbackList), 
      XtOffsetOf( struct _XmSashRec, sash.sash_action), XmRPointer, NULL},

   { XmNnavigationType, XmCNavigationType, XmRNavigationType,
     sizeof (unsigned char),
     XtOffsetOf( struct _XmPrimitiveRec, primitive.navigation_type),
     XmRImmediate, (XtPointer) XmSTICKY_TAB_GROUP},
};


static XtActionsRec actionsList[] =
{
  {"SashAction",	SashAction},
  {"SashFocusIn",	SashFocusIn},
  {"SashFocusOut",	SashFocusOut},
};


static XmBaseClassExtRec SashBaseClassExtRec = {
    NULL,
    NULLQUARK,
    XmBaseClassExtVersion,
    sizeof(XmBaseClassExtRec),
    NULL,				/* InitializePrehook	*/
    NULL,				/* SetValuesPrehook	*/
    NULL,				/* InitializePosthook	*/
    NULL,				/* SetValuesPosthook	*/
    NULL,				/* secondaryObjectClass	*/
    NULL,				/* secondaryCreate	*/
    NULL,		                /* getSecRes data	*/
    { 0 },				/* fastSubclass flags	*/
    NULL,				/* get_values_prehook	*/
    NULL,				/* get_values_posthook	*/
    NULL,                               /* classPartInitPrehook */
    NULL,                               /* classPartInitPosthook*/
    NULL,                               /* ext_resources        */
    NULL,                               /* compiled_ext_resources*/
    0,                                  /* num_ext_resources    */
    FALSE,                              /* use_sub_resources    */
    WidgetNavigable,                    /* widgetNavigable      */
    XmInheritFocusChange,               /* focusChange          */
};

externaldef(xmsashclassrec) XmSashClassRec xmSashClassRec = {
   {
/* core class fields */
    /* superclass         */   (WidgetClass) &xmPrimitiveClassRec,
    /* class name         */   "XmSash",
    /* size               */   sizeof(XmSashRec),
    /* class initialize   */   ClassInitialize,
    /* class_part_init    */   ClassPartInitialize,
    /* class_inited       */   FALSE,
    /* initialize         */   Initialize,
    /* initialize_hook    */   NULL,
    /* realize            */   Realize,
    /* actions            */   actionsList,
    /* num_actions        */   XtNumber(actionsList),
    /* resourses          */   resources,
    /* resource_count     */   XtNumber(resources),
    /* xrm_class          */   NULLQUARK,
    /* compress_motion    */   TRUE,
    /* compress_exposure  */   XtExposeCompressMaximal,
    /* compress_enter/lv  */   TRUE,
    /* visible_interest   */   FALSE,
    /* destroy            */   NULL,
    /* resize             */   NULL,
    /* expose             */   Redisplay,
    /* set_values         */   NULL,
    /* set_values_hook    */   NULL,
    /* set_values_almost  */   XtInheritSetValuesAlmost,
    /* get_values_hook    */   NULL,
    /* accept_focus       */   NULL,
    /* version            */   XtVersion,
    /* callback_private   */   NULL,
    /* tm_table           */   defTranslations,
    /* query_geometry     */   NULL,
    NULL,                             /* display_accelerator   */
    (XtPointer)&SashBaseClassExtRec, /* extension             */
   },

   {
      XmInheritWidgetProc,   /* Primitive border_highlight   */
      XmInheritWidgetProc,   /* Primitive border_unhighlight */
      NULL,         /* translations                 */
      NULL,         /* arm_and_activate             */
      NULL,	    /* get resources                */
      0,	    /* num get_resources            */
      NULL,         /* extension                    */
   },

   {
      (XtPointer) NULL,         /* extension        */
   }

};

externaldef(xmsashwidgetclass) WidgetClass xmSashWidgetClass =
					         (WidgetClass) &xmSashClassRec;

/************************************************************************
 *
 *  ClassPartInitialize
 *    Set up the fast subclassing for the widget.
 *
 ************************************************************************/
static void 
ClassPartInitialize(
        WidgetClass wc )
{
   _XmFastSubclassInit(wc, XmSASH_BIT);
}

/************************************************************************
 *
 *  ClassInitialize
 *    Initialize the primitive part of class structure with 
 *    routines to do special highlight & unhighlight for Sash.
 *
 ************************************************************************/
static void 
ClassInitialize( void )
{
   xmSashClassRec.primitive_class.border_highlight =
                  HighlightSash;
   xmSashClassRec.primitive_class.border_unhighlight = 
                  UnhighlightSash;
   SashBaseClassExtRec.record_type = XmQmotif;
}

/*ARGSUSED*/
static void 
Initialize(
        Widget rw,
        Widget nw,
        ArgList args,		/* unused */
        Cardinal *num_args )	/* unused */
{
        XmSashWidget request = (XmSashWidget) rw ;
        XmSashWidget new_w = (XmSashWidget) nw ;
  if (request->core.width == 0)
     new_w->core.width += SASHSIZE;
  if (request->core.height == 0)
     new_w->core.height += SASHSIZE;
  new_w->sash.has_focus = False;
}

static void 
HighlightSash(
        Widget sash )
{
  int x, y;
  
  x = y = ((XmSashWidget) sash)->primitive.shadow_thickness;
  
  XFillRectangle( XtDisplay( sash), XtWindow( sash),
                   ((XmSashWidget) sash)->primitive.highlight_GC,
                   x,y, sash->core.width-(2*x), sash->core.height-(2*y));
}

static void 
UnhighlightSash(
        Widget sash )
{
  int x, y;
  
  x = y = ((XmSashWidget) sash)->primitive.shadow_thickness;

  XClearArea( XtDisplay( sash), XtWindow( sash),
                   x,y, sash->core.width-(2*x), sash->core.height-(2*y),
	           FALSE);
}

static XmNavigability
WidgetNavigable(
        Widget wid)
{   
  if(    _XmShellIsExclusive( wid)    )
    {
      /* Preserve 1.0 behavior.  (Why?  Don't ask me!)
       */
      return XmNOT_NAVIGABLE ;
    }
  if(    XtIsSensitive(wid)
     &&  ((XmPrimitiveWidget) wid)->primitive.traversal_on    )
    {   
      XmNavigationType nav_type = ((XmPrimitiveWidget) wid)
	                                          ->primitive.navigation_type ;
      if(    (nav_type == XmSTICKY_TAB_GROUP)
	 ||  (nav_type == XmEXCLUSIVE_TAB_GROUP)
	 ||  (    (nav_type == XmTAB_GROUP)
	      &&  !_XmShellIsExclusive( wid))    )
	{
	  return XmTAB_NAVIGABLE ;
	}
    }
  return XmNOT_NAVIGABLE ;
}

/* ARGSUSED */
static void 
SashFocusIn(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
{
    register XmSashWidget sash = (XmSashWidget) w;

    if (event->xany.type != FocusIn || !event->xfocus.send_event)
          return;

    if (_XmGetFocusPolicy( (Widget) sash) == XmEXPLICIT)
       HighlightSash(w);


    XmeDrawShadows (XtDisplay (w), XtWindow (w),
                     sash->primitive.top_shadow_GC,
                     sash->primitive.bottom_shadow_GC,
                     0,0,w->core.width, w->core.height,
                     sash->primitive.shadow_thickness,
		     XmSHADOW_OUT);

    sash->sash.has_focus = True;
}

/* ARGSUSED */
static void 
SashFocusOut(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
{
    register XmSashWidget sash = (XmSashWidget) w;

    if (event->xany.type != FocusOut || !event->xfocus.send_event)
          return;

    if (_XmGetFocusPolicy( (Widget) sash) == XmEXPLICIT)
       UnhighlightSash(w);

    XmeDrawShadows (XtDisplay (w), XtWindow (w),
                     sash->primitive.top_shadow_GC,
                     sash->primitive.bottom_shadow_GC,
                     0,0,w->core.width, w->core.height,
                     sash->primitive.shadow_thickness,
		     XmSHADOW_OUT);

    sash->sash.has_focus = False;
}

static void 
SashAction(
        Widget widget,
        XEvent *event,
        String *params,
        Cardinal *num_params )
{
    register XmSashWidget sash = (XmSashWidget) widget;
    SashCallDataRec call_data;

    call_data.event = event;
    call_data.params = params;
    call_data.num_params = *num_params;

    XtCallCallbackList(widget, sash->sash.sash_action, (XtPointer)&call_data);
}

static void 
Realize(
        register Widget w,
        XtValueMask *p_valueMask,
        XSetWindowAttributes *attributes )
{
	XmDisplay   dd = (XmDisplay) XmGetXmDisplay(XtDisplay(w));
	Cursor SashCursor = 
		((XmDisplayInfo *)(dd->display.displayInfo))->SashCursor;
	
	if (0L == SashCursor)
		{
		/* create some data shared among all instances on this 
		** display; the first one along can create it, and 
		** any one can remove it; note no reference count
		*/
        	SashCursor = 
		((XmDisplayInfo *)(dd->display.displayInfo))->SashCursor = 
			XCreateFontCursor(XtDisplay(w), XC_crosshair);
		XtAddCallback((Widget)dd, XtNdestroyCallback, 
			SashDisplayDestroyCallback, (XtPointer) NULL);
		}

	attributes->cursor = SashCursor;
	XtCreateWindow (w, InputOutput, CopyFromParent, 
		*p_valueMask | CWCursor, attributes);
}

/*ARGSUSED*/
static void 
SashDisplayDestroyCallback 
	( Widget w,
        XtPointer client_data,	/* unused */
        XtPointer call_data )	/* unused */
{
	XmDisplay   dd = (XmDisplay) XmGetXmDisplay(XtDisplay(w));
	Cursor SashCursor;
        if ((XmDisplay)NULL != dd)
	{
	  SashCursor  = 
		((XmDisplayInfo *)(dd->display.displayInfo))->SashCursor;
	    if (0L != SashCursor)
		{
			XFreeCursor(XtDisplay(w), SashCursor);
			/*
			((XmDisplayInfo *)(dd->display.displayInfo))->SashCursor= 0L;
			*/
		}
	}
}




/*************************************<->*************************************
 *
 *  Redisplay (w, event)
 *
 *   Description:
 *   -----------
 *     Cause the widget, identified by w, to be redisplayed.
 *
 *
 *   Inputs:
 *   ------
 *     w = widget to be redisplayed;
 *     event = event structure identifying need for redisplay on this
 *             widget.
 * 
 *   Outputs:
 *   -------
 *
 *   Procedures Called
 *   -----------------
 *   DrawToggle()
 *   XDrawString()
 *************************************<->***********************************/
/* ARGSUSED */
static void 
Redisplay(
        Widget w,
        XEvent *event,
        Region region )
{
   register XmSashWidget sash = (XmSashWidget) w;

     XmeDrawShadows (XtDisplay (w), XtWindow (w), 
                      sash->primitive.top_shadow_GC,
                      sash->primitive.bottom_shadow_GC, 
		      0,0,w->core.width, w->core.height,
                      sash->primitive.shadow_thickness,
		      XmSHADOW_OUT);

     if (sash->sash.has_focus) HighlightSash(w);
}
