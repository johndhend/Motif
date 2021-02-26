
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
static char rcsid[] = "$XConsortium: Separator.c /main/14 1996/03/25 17:53:11 barstow $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#include <stdio.h>
#include <ctype.h>
#include <X11/keysymdef.h>   
#include <X11/IntrinsicP.h>
#include "XmI.h"
#include <Xm/RowColumnP.h>
#include <Xm/SeparatorP.h>
#include "RepTypeI.h"
#include <Xm/TraitP.h>
#include <Xm/MenuT.h>
#include <Xm/DrawP.h>


/********    Static Function Declarations    ********/

static void ClassInitialize() ;
static void ClassPartInitialize( 
                        WidgetClass wc) ;
static void Initialize( 
                        Widget rw,
                        Widget nw,
                        ArgList args,
                        Cardinal *num_args) ;
static void GetSeparatorGC( 
                        XmSeparatorWidget mw) ;
static void Redisplay( 
                        Widget wid,
                        XEvent *event,
                        Region region) ;
static void Destroy( 
                        Widget wid) ;
static Boolean SetValues( 
                        Widget cw,
                        Widget rw,
                        Widget nw,
                        ArgList args,
                        Cardinal *num_args) ;

/********    End Static Function Declarations    ********/

/* Menu Savvy trait record */
static XmConst XmMenuSavvyTraitRec MenuSavvySeparatorRecord = {
    0,				/* version */
    NULL,			/* disableCallback */
    NULL,			/* getAccelerator */
    NULL,			/* getMnemonic */
    NULL,			/* getActivateCBName */
};


/* Definition for resources that need special processing in get values */

static XmSyntheticResource syn_resources[] = 
{
   {
      XmNmargin, 
      sizeof (Dimension),
      XtOffsetOf( struct _XmSeparatorRec, separator.margin),
      XmeFromHorizontalPixels,
      XmeToHorizontalPixels
   },
};


/*  Resource list for Separator  */

static XtResource resources[] = 
{
   {
      XmNseparatorType, XmCSeparatorType, XmRSeparatorType, sizeof (unsigned char),
      XtOffsetOf( struct _XmSeparatorRec, separator.separator_type),
      XmRImmediate, (XtPointer) XmSHADOW_ETCHED_IN
   },

   {
      XmNmargin, 
      XmCMargin,
      XmRHorizontalDimension, 
      sizeof (Dimension),
      XtOffsetOf( struct _XmSeparatorRec, separator.margin),
      XmRImmediate, (XtPointer)  0
   },

   {
      XmNorientation, XmCOrientation, XmROrientation, sizeof (unsigned char),
      XtOffsetOf( struct _XmSeparatorRec, separator.orientation),
      XmRImmediate, (XtPointer) XmHORIZONTAL
   },
   {
     XmNtraversalOn,
     XmCTraversalOn,
     XmRBoolean,
     sizeof (Boolean),
     XtOffsetOf( struct _XmPrimitiveRec, primitive.traversal_on),
     XmRImmediate, (XtPointer) FALSE
   },
   {
     XmNhighlightThickness,
     XmCHighlightThickness,
     XmRHorizontalDimension,
     sizeof (Dimension),
     XtOffsetOf( struct _XmPrimitiveRec, primitive.highlight_thickness),
     XmRImmediate, (XtPointer) 0
   },
   {
     XmNshadowThickness,
     XmCShadowThickness,
     XmRHorizontalDimension,
     sizeof (Dimension),
     XtOffsetOf( struct _XmPrimitiveRec, primitive.shadow_thickness),
     XmRImmediate, (XtPointer) 2
   },
};


/*  The Separator class record definition  */

externaldef(xmseparatorclassrec) XmSeparatorClassRec xmSeparatorClassRec =
{
   {
      (WidgetClass) &xmPrimitiveClassRec, /* superclass	 	 */
      "XmSeparator",                      /* class_name	         */	
      sizeof(XmSeparatorRec),             /* widget_size         */	
      ClassInitialize,			/* class_initialize      */    
      ClassPartInitialize,              /* class_part_initialize */
      FALSE,                            /* class_inited          */	
      Initialize,                       /* initialize	         */	
      (XtArgsProc)NULL,                 /* initialize_hook       */
      XtInheritRealize,                 /* realize	         */	
      NULL,                             /* actions               */	
      0,                                /* num_actions    	 */	
      resources,                        /* resources	         */	
      XtNumber (resources),             /* num_resources         */	
      NULLQUARK,                        /* xrm_class	         */	
      TRUE,                             /* compress_motion       */	
      XtExposeCompressSeries |          /* compress_exposure     */	
	  XtExposeNoRegion,
      TRUE,                             /* compress_enterleave   */
      FALSE,                            /* visible_interest      */	
      Destroy,                          /* destroy               */	
      (XtWidgetProc)NULL,               /* resize                */	
      Redisplay,                        /* expose                */	
      SetValues,                        /* set_values	         */	
      (XtArgsFunc)NULL,                 /* set_values_hook       */
      XtInheritSetValuesAlmost,         /* set_values_almost     */
      (XtArgsProc)NULL,                 /* get_values_hook       */
      (XtAcceptFocusProc)NULL,          /* accept_focus	         */	
      XtVersion,                        /* version               */
      NULL,                             /* callback private      */
      NULL,                             /* tm_table              */
      (XtGeometryHandler)NULL,          /* query_geometry        */
      (XtStringProc)NULL,               /* display_accelerator   */
      NULL,                             /* extension             */
   },

   {
      (XtWidgetProc)NULL,               /* Primitive border_highlight   */
      (XtWidgetProc)NULL,               /* Primitive border_unhighlight */
      NULL,                             /* translations                 */
      (XtActionProc)NULL,               /* arm_and_activate             */
      syn_resources,                    /* syn resources                */
      XtNumber(syn_resources),	        /* num syn_resources            */
      NULL,                             /* extension                    */
   },

   {
      (XtPointer) NULL,                 /* extension                    */
   }
};

externaldef(xmseparatorwidgetclass) WidgetClass xmSeparatorWidgetClass =
				   (WidgetClass) &xmSeparatorClassRec;

/************************************************************************
 *
 *  ClassInitialize 
 *
 ************************************************************************/
static void 
ClassInitialize( void )
{
    /* Install the menu savvy trait. */
    XmeTraitSet((XtPointer) xmSeparatorWidgetClass, XmQTmenuSavvy,
		(XtPointer) &MenuSavvySeparatorRecord);
}

/************************************************************************
 *
 *  ClassPartInitialize
 *     Set up the fast subclassing for the widget
 *
 ************************************************************************/
static void 
ClassPartInitialize(
        WidgetClass wc )
{
   _XmFastSubclassInit (wc, XmSEPARATOR_BIT);
}

      
/************************************************************************
 *
 *  Initialize
 *     The main widget instance initialization routine.
 *
 ************************************************************************/
/*ARGSUSED*/
static void 
Initialize(
        Widget rw,
        Widget nw,
        ArgList args,		/* unused */
        Cardinal *num_args )	/* unused */
{
   XmSeparatorWidget request = (XmSeparatorWidget) rw ;
   XmSeparatorWidget new_w = (XmSeparatorWidget) nw ;
   new_w -> primitive.traversal_on = FALSE; 

   /* Force highlightThickness to zero if in a menu. */
   if (XmIsRowColumn(XtParent(new_w)) &&
       ((RC_Type(XtParent(new_w)) == XmMENU_PULLDOWN) ||
        (RC_Type(XtParent(new_w)) == XmMENU_POPUP)))
     new_w->primitive.highlight_thickness = 0;

   if(    !XmRepTypeValidValue( XmRID_SEPARATOR_TYPE,
                              new_w->separator.separator_type, (Widget) new_w)    )
   {
      new_w -> separator.separator_type = XmSHADOW_ETCHED_IN;
   }

   if(    !XmRepTypeValidValue( XmRID_ORIENTATION,
                                 new_w->separator.orientation, (Widget) new_w)    )
   {
      new_w -> separator.orientation = XmHORIZONTAL;
   }

   if (new_w->separator.orientation == XmHORIZONTAL)
   {
      if (request -> core.width == 0)
	 new_w -> core.width = 2 * new_w -> primitive.highlight_thickness +2;

      if (request -> core.height == 0)
      {
	 new_w -> core.height = 2 * new_w -> primitive.highlight_thickness;

	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE)
	    new_w -> core.height += 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.height += new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE)
	    new_w -> core.height += 5;
	 else
	    if (new_w -> core.height == 0)
	       new_w -> core.height = 1;
      }
   }
   
   if (new_w->separator.orientation == XmVERTICAL)
   {
      if (request -> core.height == 0)
	 new_w -> core.height = 2 * new_w -> primitive.highlight_thickness +2;

      if (request -> core.width == 0)
      {
	 new_w -> core.width = 2 * new_w -> primitive.highlight_thickness;

	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE)
	    new_w -> core.width += 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.width += new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE)
	    new_w -> core.width += 5;
	 else
	    if (new_w -> core.width == 0)
	       new_w -> core.width = 1;
      }
   }
   
   /*  Get the drawing graphics contexts.  */

   GetSeparatorGC (new_w);
}




/************************************************************************
 *
 *  GetSeparatorGC
 *     Get the graphics context used for drawing the separator.
 *
 ************************************************************************/
static void 
GetSeparatorGC(
        XmSeparatorWidget mw )
{
   XGCValues values;
   XtGCMask  valueMask;

   valueMask = GCForeground | GCBackground;

   values.foreground = mw -> primitive.foreground;
   values.background = mw -> core.background_pixel;

   if (mw -> separator.separator_type == XmSINGLE_DASHED_LINE ||
       mw -> separator.separator_type == XmDOUBLE_DASHED_LINE)
   {
      valueMask = valueMask | GCLineStyle;
      values.line_style = LineDoubleDash;
   }

   mw -> separator.separator_GC = XtGetGC ((Widget) mw, valueMask, &values);
}




/************************************************************************
 *
 *  Redisplay
 *     Invoke the application exposure callbacks.
 *
 ************************************************************************/
/*ARGSUSED*/
static void 
Redisplay(
        Widget wid,
        XEvent *event,
        Region region )
{
     XmSeparatorWidget mw = (XmSeparatorWidget) wid ;

    XmeDrawSeparator(XtDisplay(wid), XtWindow(wid),
                  mw->primitive.top_shadow_GC,
                  mw->primitive.bottom_shadow_GC,
                  mw->separator.separator_GC,
                  mw->primitive.highlight_thickness,
                  mw->primitive.highlight_thickness,
                  mw->core.width - 2*mw->primitive.highlight_thickness,
                  mw->core.height - 2*mw->primitive.highlight_thickness,
                  mw->primitive.shadow_thickness,
                  mw->separator.margin,
                  mw->separator.orientation,
                  mw->separator.separator_type);
}




/************************************************************************
 *
 *  Destroy
 *	Remove the callback lists.
 *
 ************************************************************************/
static void 
Destroy(
        Widget wid )
{
   XtReleaseGC (wid, ((XmSeparatorWidget) wid)->separator.separator_GC);
}




/************************************************************************
 *
 *  SetValues
 *
 ************************************************************************/
/*ARGSUSED*/
static Boolean 
SetValues(
        Widget cw,
        Widget rw,
        Widget nw,
        ArgList args,		/* unused */
        Cardinal *num_args )	/* unused */
{
        XmSeparatorWidget current = (XmSeparatorWidget) cw ;
        XmSeparatorWidget request = (XmSeparatorWidget) rw ;
        XmSeparatorWidget new_w = (XmSeparatorWidget) nw ;
   Boolean flag = FALSE;   

   /*
    * We never allow our traversal flags to be changed during SetValues();
    * this is enforced by our superclass.
    */

   /*  Force traversal_on to FALSE */
   new_w -> primitive.traversal_on = FALSE;

   /* Force highlightThickness to zero if in a menu. */
   if (XmIsRowColumn(XtParent(new_w)) &&
       ((RC_Type(XtParent(new_w)) == XmMENU_PULLDOWN) ||
        (RC_Type(XtParent(new_w)) == XmMENU_POPUP)))
     new_w->primitive.highlight_thickness = 0;
 
   if(    !XmRepTypeValidValue( XmRID_SEPARATOR_TYPE,
                              new_w->separator.separator_type, (Widget) new_w)    )
   {
      new_w -> separator.separator_type = current -> separator.separator_type;
   }

   if(    !XmRepTypeValidValue( XmRID_ORIENTATION,
                                 new_w->separator.orientation, (Widget) new_w)    )
   {
      new_w -> separator.orientation = current -> separator.orientation;
   }

   if (new_w -> separator.orientation == XmHORIZONTAL)
   {
      if (request -> core.width == 0)
	 new_w -> core.width = 2 * new_w->primitive.highlight_thickness + 2;

      if (request -> core.height == 0)
      {
	 new_w -> core.height = 2 * new_w -> primitive.highlight_thickness;

	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE)
	    new_w -> core.height += 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.height += new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE)
	    new_w -> core.height += 5;
	 else
	    if (new_w -> core.height == 0)
	       new_w -> core.height = 1;
      }

      if ((new_w -> separator.separator_type != current -> separator.separator_type ||
           new_w -> primitive.shadow_thickness != current -> primitive.shadow_thickness ||
           new_w -> primitive.highlight_thickness != current -> primitive.highlight_thickness) &&
	   request -> core.height == current -> core.height)
      {
	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE) 
	    new_w -> core.height = 2 * new_w -> primitive.highlight_thickness + 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.height = 2 * new_w -> primitive.highlight_thickness +
				       new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE) 
	    new_w -> core.height = 2 * new_w -> primitive.highlight_thickness + 5;
      }
   } 

   if (new_w -> separator.orientation == XmVERTICAL)
   {
      if (request -> core.height == 0)
	 new_w -> core.height = 2 * new_w->primitive.highlight_thickness + 2;

      if (request -> core.width == 0)
      {
	 new_w -> core.width = 2 * new_w -> primitive.highlight_thickness;

	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE)
	    new_w -> core.width += 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.width += new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE)
	    new_w -> core.width += 5;
	 else
	    if (new_w -> core.width == 0)
	       new_w -> core.width = 1;
      }

      if ((new_w -> separator.separator_type != current -> separator.separator_type ||
           new_w -> primitive.shadow_thickness != current -> primitive.shadow_thickness ||
           new_w -> primitive.highlight_thickness != current -> primitive.highlight_thickness) &&
	   request -> core.width == current -> core.width)
      {
	 if (new_w -> separator.separator_type == XmSINGLE_LINE ||
	     new_w -> separator.separator_type == XmSINGLE_DASHED_LINE) 
	    new_w -> core.width = 2 * new_w -> primitive.highlight_thickness + 3;
	 else if (new_w -> separator.separator_type == XmSHADOW_ETCHED_IN ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_IN_DASH ||
		  new_w -> separator.separator_type == XmSHADOW_ETCHED_OUT_DASH)
	    new_w -> core.width = 2 * new_w -> primitive.highlight_thickness +
				       new_w -> primitive.shadow_thickness;
	 else if (new_w -> separator.separator_type == XmDOUBLE_LINE ||
		  new_w -> separator.separator_type == XmDOUBLE_DASHED_LINE) 
	    new_w -> core.width = 2 * new_w -> primitive.highlight_thickness + 5;
      }
   } 

   if (new_w -> separator.orientation != current -> separator.orientation ||
       new_w -> separator.margin != current -> separator.margin ||
       new_w -> primitive.shadow_thickness != current -> primitive.shadow_thickness) 
      flag = TRUE;

   if (new_w -> separator.separator_type != current -> separator.separator_type  ||
       new_w -> core.background_pixel != current -> core.background_pixel    ||
       new_w -> primitive.foreground != current -> primitive.foreground)
   {
      XtReleaseGC ((Widget) new_w, new_w -> separator.separator_GC);
      GetSeparatorGC (new_w);
      flag = TRUE;
   }

   return (flag);
}

/************************************************************************
 *
 *  XmCreateSeparator
 *	Create an instance of a separator and return the widget id.
 *
 ************************************************************************/
Widget 
XmCreateSeparator(
        Widget parent,
        char *name,
        ArgList arglist,
        Cardinal argcount )
{
   return (XtCreateWidget (name, xmSeparatorWidgetClass, 
                           parent, arglist, argcount));
}
