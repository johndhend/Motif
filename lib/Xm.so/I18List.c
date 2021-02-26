
#include <localdef.h>

/*
 *    Copyright 1990, Integrated Computer Solutions, Inc.
 *
 *		       All Rights Reserved.
 *
 * AUTHOR: Chris D. Peterson
 *
 */

/************************************************************
*	INCLUDE FILES
*************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include <Xm/XmP.h>
#if (XmVERSION >= 2)
#include <Xm/DrawP.h>
#endif
#include <Xm/Ext18ListP.h>
#ifdef VMS
#include <bitmaps/gray.xbm>
#else
#include <X11/bitmaps/gray>
#endif

#include <Xm/ScrollBar.h>
#include <Xm/ExtP.h>
#include <Xm/XmP.h>
#include "XmI.h"

/************************************************************
*	TYPEDEFS AND DEFINES
*************************************************************/

#define SUPERCLASS ((WidgetClass) &xmPrimitiveClassRec)

#define NO_SELECTION -1		/* There is currently no anchor. */
#define IN_COLUMN_HEADER -2	/* The location is in the header. */
#define ENTIRE_ROW -3		/* perform operation on entire row. */

#define EXTEND	 	(1 << 0)
#define TOGGLE	 	(1 << 1)
#define OFF_TOP         (1 << 2)
#define OFF_BOTTOM      (1 << 3)
#define OFF_LEFT        (1 << 4) /* UNUSED BUT RESERVED */
#define OFF_RIGHT       (1 << 5) /* UNUSED BUT RESERVED */
#define OUTSIDE_WIDGET (OFF_TOP | OFF_BOTTOM | OFF_LEFT | OFF_RIGHT)

#define DELAY_TIME(w)  (XtGetMultiClickTime(XtDisplay(w))/3)

#define LINE_HEIGHT 2		/* Height of the separator line */
#define HORIZONTAL_SPACE 8	/* horizontal Space between Text and Text. */
#define VERTICAL_SPACE   2	/* Vertical Space between Text and Text. */

#define NoTimeout ((XtIntervalId) 0)

/*
 * DANGER:  XmeRenderTableGetDefaultFont is an undocumented 
 *          internal MOTIF(tm) function.
 */
    
#define GetDefaultFont XmeRenderTableGetDefaultFont

/************************************************************
*	MACROS
*************************************************************/

#define streq(a, b) (((a) != NULL) && ((b) != NULL) && (strcmp((a), (b)) == 0))
#define IsValidPixmap(p) (((p) != None) && ((p) != XmUNSPECIFIED_PIXMAP))

/************************************************************
*	GLOBAL DECLARATIONS
*************************************************************/

extern Boolean XmeRenderTableGetDefaultFont (XmFontList, XFontStruct **);

static Widget global_current_widget;		/* static global to hold
						   widget id for qsort. */

/************************************************************
*	STATIC FUNCTION DECLARATIONS
*************************************************************/

/******************************
 * Exported Widget Functions
 ******************************/

Boolean XmI18ListDoSearch(Widget w, String str, Boolean reset);
Xm18RowInfo *XmI18ListFindRow(Widget w, String str, int *found_column,
			      Boolean reset, Boolean do_visual);

static void ClassInitialize();
static void Initialize(Widget, Widget, ArgList, Cardinal *);
static void Realize(Widget, Mask *, XSetWindowAttributes *);
static void Resize(Widget), Redisplay(Widget, XEvent *, Region);
static void Destroy(Widget);
static Boolean SetValues(Widget, Widget, Widget, ArgList, Cardinal *);

/***********************************
 * Internal routines.
 ***********************************/
static void AdjustFirstRowAndCol( XmI18ListWidget );
static void AdjustFirstCol(Widget);
static void CalcLocations(Widget);
static void CalcColumnInfo(Widget, Boolean);
static void SetVisibleSize(Widget, Boolean);
static void DisplayList(Widget, short, short, Boolean);
static short GetListWidth(Widget);
static void HScroll(Widget, short), VScroll(Widget, short);
static short CvtPixelValToColNum(Widget, short);
static short CvtColNumToPixelVal(Widget, short);
static void CvtRowColumnToPosition(Widget, short, short, short *, short *);
static void CvtPositionToRowColumn(Widget, short, short, short *, short *);
static void ToggleRow(Widget, short), InvertArea(Widget, short, short);
static void SelectHeader(Widget, short), DrawSeparator(Widget);
static void CreateGCs(Widget), RedrawList(Widget), GetPixmapInfo(Widget);
static void DestroyGCs(Widget), Notify(Widget, Boolean);
static void ResizeSliders(Widget), SortList(Widget, Boolean);
static void SingleClick(XmI18ListWidget);
static void MoveListTimeout(XtPointer, XtIntervalId *);
static Boolean MakePositionVisible(Widget, short, short, short, int);
static void ExtendedSelect(Widget, short);

static int IsRowVisible(Widget, short);
#ifdef UNUSED_FUNCTION
static int IsColumnVisible(Widget, short);
#endif
static int QSortTest(const void *, const void *);

static void UnselectRows(Widget, short);

static Boolean Search(XmI18ListWidget ilist, XmString xms,
       int start_row, int start_column, int *found_row, int *found_column);
static int FirstSelectedRow(Widget w);
static void MakeCellVisible(Widget w, int row, int col);
static void CopyColumnTitles(XmI18ListWidget);
static void FreeColumnTitles(XmI18ListWidget);

static void SelectRow(XmI18ListWidget, int, Boolean, Boolean);
static void SelectItems(XmI18ListWidget, XmString,
			int, Boolean, Boolean);

/***********************************
 * Actions and Callback function defs.
 ***********************************/

static void HScrollCallback(Widget, XtPointer, XtPointer);
static void VScrollCallback(Widget, XtPointer, XtPointer);
static void HSlideLeftArrowCallback(Widget, XtPointer, XtPointer);
static void HSlideRightArrowCallback(Widget, XtPointer, XtPointer);

static void ButtonDownAction(Widget, XEvent *, String *, Cardinal *);
static void ButtonUpOrLeaveAction(Widget, XEvent *, String *, Cardinal *);
static void MotionAction(Widget, XEvent *, String *, Cardinal *);

/************************************************************
*	STATIC DECLARATIONS
*************************************************************/

/*
 * The Translation table routines are getting in the way here.
 * Since the implicit removal of event disallows using both:
 *
 * <Btn1Up> (2)  and   button1 <Motion> 
 *
 * in the same translation table I have to do all the work myself.
 */

static char defaultTranslations[] =
    "~Ctrl ~Shift <Btn1Down>:		ButtonDown()\n\
     Ctrl ~Shift  <Btn1Down>:		ButtonDown(Toggle)\n\
     ~Ctrl Shift  <Btn1Down>:		ButtonDown(Extend)\n\
     Button1 <Motion>:		Motion()\n\
     <Btn1Up>:			ButtonUpOrLeave()";

static XtActionsRec actionsList[] =
{
  {"ButtonDown",	ButtonDownAction},
  {"ButtonUpOrLeave",	ButtonUpOrLeaveAction},
  {"Motion",      	MotionAction},
};

/* ARGSUSED */
static void SetEntryBackground(Widget w, int offset, XrmValue *value)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    /* not really used */
    value->addr = (XtPointer) &ilist->core.background_pixel;

    /*
     * If this function is called, then the value of XmNentryBackground wasn't
     * set through a resource file specification, so override the current
     * value of True. If it was set, the value of True stays set in the widget
     * and the value of the pixel is set through the usual XtRPixel converter.
     */
    XmI18List_entry_background_use(ilist) = False;
}

static XmPartResource resources[] = {
#define offset(field) XmPartOffset(XmI18List, field)
  {XmNnumColumns, XmCNumColumns, XmRShort, sizeof(short),
     offset(num_columns), XmRImmediate, (XtPointer) 0},
  {XmNnumRows, XmCNumRows, XmRShort, sizeof(short),
     offset(num_rows), XmRImmediate, (XtPointer) 0},
  {XmNselectedColumn, XmCSelectedColumn, XmRShort, sizeof(short),
     offset(selected_header), XmRImmediate, (XtPointer) 0},
  {XmNcolumnTitles, XmCColumnTitles, XmRXmStringTable, sizeof(XmString *),
     offset(column_titles), XmRImmediate, (XtPointer) NULL},
  {XmNentryData, XmCEntryData, XmRPointer, sizeof(XtPointer),
     offset(row_data), XmRImmediate, (XtPointer) NULL},
  {XmNfirstColumnPixmaps, XmCFirstColumnPixmaps, XmRBoolean, sizeof(Boolean),
     offset(first_col_pixmaps), XmRImmediate, (XtPointer) False},
  {XmNfontList,	XmCFontList, XmRFontList, sizeof (XmFontList),
     offset (font_list), XmRImmediate, (XtPointer) NULL},
  {XmNverticalScrollBar, XmCScrollBar, XmRWidget, sizeof (Widget),
     offset (v_bar), XmRImmediate, (XtPointer) NULL},
  {XmNhorizontalScrollBar, XmCScrollBar, XmRWidget, sizeof (Widget),
     offset (h_bar), XmRImmediate, (XtPointer) NULL},
  {XmNfirstRow, XmCFirstLocation, XmRShort, sizeof(short),
     offset(first_row), XmRImmediate, (XtPointer) 0},
  {XmNfirstColumn, XmCFirstLocation, XmRShort, sizeof(short),
     offset(first_col), XmRImmediate, (XtPointer) 0},
  {XmNdoubleClickCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
     offset(double_click), XmRImmediate, (XtPointer) NULL},
  {XmNsortFunctions, XmCFunction, XmRFunction, sizeof(Xm18SortFunction **),
     offset(sort_functions), XmRImmediate, (XtPointer) NULL},
  {XmNselectionPolicy, XmCSelectionPolicy, XmRSelectionPolicy,
     sizeof(unsigned char), offset(selection_policy), 
     XmRImmediate, (XtPointer) XmEXTENDED_SELECT },
  {XmNsingleSelectionCallback, XmCCallback, XmRCallback,sizeof(XtCallbackList),
     offset(single_select), XmRImmediate, (XtPointer) NULL},
  {XmNalignment, XmCAlignment, XmRAlignment, sizeof(unsigned char),
     offset(alignment), XmRImmediate, (XtPointer) XmALIGNMENT_BEGINNING},
  {XmNstringDirection, XmCStringDirection,
     XmRStringDirection, sizeof(unsigned char),
     offset(string_direction), XmRImmediate,
     (XtPointer) XmSTRING_DIRECTION_L_TO_R},
  {XmNvisibleItemCount, XmCVisibleItemCount, XmRInt, sizeof(int),
     offset(visible_rows), XmRImmediate, (XtPointer) XmExt18List_DEFAULT_VISIBLE_COUNT},
  {XmNnewVisualStyle, XmCNewVisualStyle, XmRBoolean, sizeof(Boolean),
     offset(new_visual_style), XmRImmediate, (XtPointer) True},

  /* process this first; set the value to True */
  {"is.entry.background.set", "I.Really.Wonder", XtRBoolean, sizeof(Boolean),
     offset(entry_background_use), XmRImmediate, (XtPointer) True},
  /* now see if this resource is set in the defaults file */
  /* XmNentryBackground currently UNDOCUMENTED */
  {XmNentryBackground, XmCBackground, XtRPixel, sizeof(Pixel),
     offset(entry_background_pixel), XmRCallProc, (XtPointer) SetEntryBackground},

#undef offset
};

XmI18ListClassRec xmI18ListClassRec = {
  { /* core fields */
    /* superclass		*/	SUPERCLASS,
    /* class_name		*/	XM_I18LIST_CLASS_NAME,
    /* widget_size		*/	sizeof(XmI18ListPart),
    /* class_initialize		*/	ClassInitialize,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	actionsList,
    /* num_actions		*/	XtNumber(actionsList),
    /* resources		*/	(XtResource*)resources,
    /* num_resources		*/	XtNumber(resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	XtExposeCompressMultiple,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	Resize,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	defaultTranslations,
    /* query_geometry		*/	XtInheritQueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
  },
  { /* Xmprimitive fields */
      NULL,			/* border_highlight   */
      NULL,			/* border_unhighlight */
      XtInheritTranslations,    /* translations       */
      NULL,                     /* arm_and_activate   */
      NULL,   	    		/* syn resources      */
      (Cardinal) 0,		/* num syn_resources  */
      NULL                      /* extension          */
  },
  { /* ICS List fields */
      NULL                      /* extension          */
  }
};

WidgetClass xmI18ListWidgetClass = (WidgetClass)&xmI18ListClassRec;

XmOffsetPtr XmI18List_offsets;

/*
 * Comment on code structure.
 *
 * This code is separated into two separate coordinate spaces.
 *
 * The first is the default space defined by pixels and the X Server.
 *
 * The second is "input" space that contains all the information 
 * to display in the actual list.  This space runs from 0 -> (num_rows - 1)
 * in the y direction and 0 -> (num_cols - 1) in the x direction.  The
 * input from the application is sent in this space.
 *
 * Chris D. Peterson - ICS, Inc.
 * 10/16/90
 */

/************************************************************
*	STATIC (EXPORTED) CODE
*************************************************************/

/*      Function Name: ClassInitialize
 *      Description:   Inits class-specific data (offsets)
 *      Arguments:     none
 *      Returns:       nothing
 */
static void
ClassInitialize()
{
    XmResolveAllPartOffsets(xmI18ListWidgetClass,
			    &XmI18List_offsets,
			    NULL);
}

/*	Function Name: Initialize
 *	Description:   Called to initialize information specific
 *                     to this widget.
 *	Arguments:     req - what was originally requested.
 *                     set - what will be created (our superclassed have
 *                           already mucked with this)
 *                     args, num_args - The arguments passed to 
 *                                      the creation call.
 *	Returns:       none.
 */

/*ARGSUSED*/
static void Initialize(Widget req, Widget set, 
		       ArgList args, Cardinal * num_args)
{
    XmI18ListWidget ilist = (XmI18ListWidget) set;

#ifdef DEMO
    _XmInitialIzeConverters(req);
#endif

    XmI18List_column_widths(ilist) = NULL;
    XmI18List_left_loc(ilist) = 0;    
    XmI18List_state(ilist) = 0;
    XmI18List_timeout(ilist) = NoTimeout;
    XmI18List_working_row(ilist) = -1;
    XmI18List_end(ilist) = XmI18List_anchor(ilist) = NO_SELECTION;
    XmI18List_time(ilist) = 0L;

    XmI18List_search_column(ilist) = -1;

    if (XmI18List_font_list(ilist) == NULL)
        XmI18List_font_list(ilist) = XmeGetDefaultRenderTable(set, XmTEXT_FONTLIST);

    CopyColumnTitles(ilist);

    if (XmI18List_v_bar(ilist) != NULL) {
	XtAddCallback(XmI18List_v_bar(ilist), XmNvalueChangedCallback,
		      VScrollCallback, (XtPointer) set);
 	XtAddCallback(XmI18List_v_bar(ilist), XmNdragCallback,
 		      VScrollCallback, (XtPointer) set);
    }

    if (XmI18List_h_bar(ilist) != NULL) {
	XtAddCallback(XmI18List_h_bar(ilist), XmNvalueChangedCallback,
		      HScrollCallback, (XtPointer) set);
 	XtAddCallback(XmI18List_h_bar(ilist), XmNdragCallback,
 		      HScrollCallback, (XtPointer) set);
    }

    /*
     * Add the callbacks to handle left and right arrow selection
     */
    if (XmI18List_h_bar(ilist) != NULL)
	XtAddCallback(XmI18List_h_bar(ilist), XmNdecrementCallback,
		      HSlideLeftArrowCallback, (XtPointer) set);
    if (XmI18List_h_bar(ilist) != NULL)
	XtAddCallback(XmI18List_h_bar(ilist), XmNincrementCallback,
		      HSlideRightArrowCallback, (XtPointer) set);

    if (XtHeight(req) == 0)
    {
	SetVisibleSize(set, (XtWidth(req) == 0));
    }
}

/*	Function Name: Realize
 *	Description:   Called to realize this widget.
 *	Arguments:     w - Extended List Widget to realize.
 *                     valueMask, attributes - attributes to use when creating
 *                     this widget's window.
 *	Returns:       none.
 *
 *      This overrides the Manager's frobbing with various values.
 */

static void 
Realize(Widget w, Mask *valueMask, XSetWindowAttributes * attributes)
{
    XmI18ListWidget ilist = (XmI18ListWidget)w;

    attributes->bit_gravity = ForgetGravity;
    *valueMask |= CWBitGravity;

    CreateGCs(w);
    SortList(w, False);
    CalcColumnInfo(w, False);

    /*  get initial left location based on first column resource */
    /* have to calculate it because the columns are different widths */

    AdjustFirstRowAndCol( ilist );

    {
        XtRealizeProc realize;
        _XmProcessLock();
        realize = xmI18ListWidgetClass->core_class.superclass->core_class.realize;
        _XmProcessUnlock();
        (*realize) (w, valueMask, attributes);
    }

    {
        XtWidgetProc resize;
        _XmProcessLock();
        resize = xmI18ListWidgetClass->core_class.resize;
        _XmProcessUnlock();
        (*resize)(w);
    }
}

/*	Function Name: SetValues
 *	Description:   Called when some widget data needs to be modified on-
 *                     the-fly.
 *	Arguments:     current - the current (old) widget values.
 *                     request - before superclassed have changed things.
 *                     set - what will acutally be the new values. 
 *                     args, num_args - the arguments in the list.
 *	Returns:       none
 *
 * NOTE:  No provision is made for SetValues on the mini-icons.
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

/*ARGSUSED*/
static Boolean SetValues(Widget current, Widget request, Widget set,
			 ArgList args, Cardinal * num_args)
{
    XmI18ListWidget 	i_old = (XmI18ListWidget)current;
    XmI18ListWidget	i_set = (XmI18ListWidget)set;
    register int 	i;
    Boolean 		redisplay = False;
    Boolean		recalculate = False;
    Boolean		resort = False;
    Boolean		refreshGCs = False;
    Boolean		readjust = False;
    Boolean		check_pos = False;
    Boolean		copyTitles = False;
  
    for (i = 0; i < *num_args; i++)
    {
	String name = args[i].name;
    
	if (streq(XmNcolumnTitles, name))
	{
	    copyTitles = True;
	    redisplay = recalculate = XtIsRealized(set);
	}
    
	if (streq(XmNentryData, name)) 
	{
	    redisplay = recalculate = resort = XtIsRealized(set);
	}
    
	if (streq(XmNsortFunctions, name))
	{
	    redisplay = resort = XtIsRealized(set);
	}
    
	if (streq(XmNfirstRow, name) || streq(XmNfirstColumn,name))
	{
	    check_pos = True;
	}

	if (streq(XmNnumRows, name))
	{
	    check_pos = True;
	    /*
	    int num_rows = (XmI18List_num_rows(i_set) - 
                           XmI18List_visible_rows(i_set));
	
	    check_pos = (XmI18List_first_row(i_set) > ((num_rows < 0)
                         ? 0 
	                 : num_rows));
	    */
	}
    }
  
    if ((XmI18List_v_bar(i_set) != XmI18List_v_bar(i_old)) ||
	(XmI18List_h_bar(i_set) != XmI18List_h_bar(i_old)))
    {
	Cardinal num = 1;
	static String params[] = { "Scrollbars" };
      
	XmI18List_v_bar(i_set) = XmI18List_v_bar(i_old);
	XmI18List_h_bar(i_set) = XmI18List_h_bar(i_old);
      
	XtAppWarningMsg(XtWidgetToApplicationContext(current),
			XmNstaticResource, XmNstaticResource,
			XmCICSWidgetSetError, XmNstaticResourceMsg,
			params, &num);
    }
  
    if( XtIsSensitive(current) != XtIsSensitive(set) )
    {
	redisplay = XtIsRealized(set);
    }
  
    if (XmI18List_font_list(i_set) != XmI18List_font_list(i_old))
    {
	refreshGCs = recalculate = redisplay = XtIsRealized(set);
    }
  
    if ((i_set->primitive.foreground != i_old->primitive.foreground) ||
	(i_set->core.background_pixel != i_old->core.background_pixel))
    {
	refreshGCs = redisplay = XtIsRealized(set);
    }
  
    if (XmI18List_selected_header(i_set) != XmI18List_selected_header(i_old))
    {
	resort = redisplay = XtIsRealized(set);
    }

    /* XmNvisibleItemCount has been changed... */
    if (XmI18List_visible_rows(i_set) != XmI18List_visible_rows(i_old))
    {
	if (XmI18List_visible_rows(i_set) < 1)
	{
	    static String	params[] = { "XmI18List", 
					     "XmNvisibleItemCount" };
	    Cardinal		num = 2;

	    XmI18List_visible_rows(i_set) = 1;	/* reset value to 1 */

	    XtAppWarningMsg(XtWidgetToApplicationContext(current),
			    XmNforceGreaterThanZero, XmNforceGreaterThanZero,
			    XmCICSWidgetSetError, XmNforceGreaterThanZeroMsg,
			    params, &num);
	}

	/* Change height only... */
	SetVisibleSize(set, False);
    }
  
    /*
     * Convert the user desired column to view to pixels
     * if and only if the entry Data has been specified
     */
    if ( XmI18List_row_data(i_set) != NULL || 
	 XmI18List_row_data(i_old) != NULL ) {
#ifdef UNUSED_CODE    
	short	column;
	if (XmI18List_first_col(i_set) > XmI18List_num_columns(i_set))
	{
	    column = XmI18List_num_columns(i_set) - 1;
	}
	else if (XmI18List_first_col(i_set) <= 0)
	{
	    column = 0;
	}
	else
	{
	    column = XmI18List_first_col(i_set) - 1; 
	}
#endif
	if ((XmI18List_num_rows(i_old) != XmI18List_num_rows(i_set)) ||
	    (XmI18List_num_columns(i_old) != XmI18List_num_columns(i_set)) ||
	    (XmI18List_row_data(i_set) != XmI18List_row_data(i_old))) 
	{
	    redisplay = recalculate = XtIsRealized(set);
	}
    
    
	if ((XmI18List_first_col(i_set) != XmI18List_first_col(i_old)) ||
	    (XmI18List_first_row(i_set) != XmI18List_first_row(i_old)) || 
	    check_pos)
	{
	    redisplay = readjust = XtIsRealized(set);		
	}	
    }

    if (XmI18List_entry_background_pixel(i_set) !=
	                    XmI18List_entry_background_pixel(i_old))
    {
	/* it was explicitly set via XtSetValues, so the user knows about it */
	XmI18List_entry_background_use(i_set) = True;
	redisplay = True;
	refreshGCs = True;
    }
  
    if (refreshGCs)
    {
	DestroyGCs(current);
	CreateGCs(set);
    }
    if (XmI18List_num_columns(i_old) != XmI18List_num_columns(i_set)) 
    {
	/* CR03506 */
	recalculate = redisplay = XtIsRealized(set);
    }
    if (copyTitles)
    {
	FreeColumnTitles(i_old);
	CopyColumnTitles(i_set);
    }
  
    if (readjust && !recalculate)
    {
	AdjustFirstRowAndCol(i_set);
    }
    else if (recalculate)
    {
	CalcColumnInfo(set, True);
	CalcLocations(set);
      
	if (!readjust) AdjustFirstCol(set);
	else AdjustFirstRowAndCol( i_set );
    }
  
    if (resort) SortList(set, False);
  
    return(redisplay);   
}
  
/*	Function Name: Redisplay
 *	Description:   This function redraws the list contents.
 *	Arguments:     w - the Frame Widget widget.
 *                     event - event that caused the exposure.
 *                     region - the region containing all the exposures.
 *	Returns:       none
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

/*ARGSUSED*/
static void
Redisplay(Widget w, XEvent * event, Region region)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    short num_rows;
#ifdef notdef
    XExposeEvent * exp_event = (XExposeEvent *) &(event->xexpose);
#endif

    num_rows = XmI18List_num_rows(ilist) - XmI18List_first_row(ilist);

    /*
     * Just refresh the entire window each time.
     */
      
    DisplayList(w, XmI18List_first_row(ilist), num_rows, TRUE);
    ResizeSliders( w );
    DrawSeparator(w);
}

/*	Function Name: Resize
 *	Description:   Called when this widget has been resized.
 *	Arguments:     w - Extended List Widget to realize.
 *	Returns:       none.
 */

static void 
Resize(Widget w)
{
    if (!XtIsRealized(w))
	return;

    CalcLocations(w);
    AdjustFirstCol(w);
    ResizeSliders(w);
}

/*	Function Name: Destroy
 *	Description:   Cleans up after the widget.
 *	Arguments:     w - the widget.
 *	Returns:       none.
 */

static void
Destroy(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    DestroyGCs(w);

    FreeColumnTitles(ilist);
    XtFree((XtPointer) XmI18List_column_widths(ilist));
}


/************************************************************
 *
 * Callbacks and Action Routines.
 *
 ************************************************************/

/************************************************************
 *
 *  This Selection code is pretty confusing, but here's the skinny.
 *
 *  When the first button click comes in we call the single click
 *  call back and remember when it happened.
 *
 *  If a second click comes we see if multi click time has passed and if
 *  not then we have a double click and should call the proper callback.
 *
 *  If we move out of the current row then reset the stored time to zero since
 *  we should not call the double click callback.
 *
 *  The single click timeout takes care of initializing the extended 
 *  select code.  We know it will be executed before the motion callback
 *  ever does anything interesting because of the action defined in the
 *  previous paragraph.
 *
 ************************************************************/

/*	Function Name: ButtonDownAction
 *	Description:   Called when the user sends a button up to the ilist.
 *	Arguments:     w - the ilist widget.
 *                     event - the event that caused this action.
 *                     params, num_params - action routine parameters.
 *	Returns:       none.
 */
#define CR1166
/*ARGSUSED*/
static void
ButtonDownAction(Widget w, XEvent *event, String *params, Cardinal *num_params)
{
    short row, col;
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    XButtonEvent * bevent = (XButtonEvent *) event;
#ifdef CR1166
    Boolean notify_type;
#endif /* CR1166 */
    if (*num_params > 1) {
        Cardinal num = 3;
        static String params[] = { "Extended List", "NoButton", "BtnDown" };

        XtAppWarningMsg(XtWidgetToApplicationContext(w),
                        XmNbadMotionParams, XmNbadMotionParams,
                        XmCICSWidgetSetError, XmNbadMotionParamsMsg,
                        params, &num);
        return;
    }

    if (XmI18List_selection_policy(ilist) != XmSINGLE_SELECT) {
	XmI18List_state(ilist) &= ~(EXTEND | TOGGLE);	/* remove these bits.*/

	if (*num_params == 1) {
	    switch (params[0][0]) {
	    case 'e':
	    case 'E':
		XmI18List_state(ilist) |= EXTEND;	/* set extended mode. */
		break;
	    case 't':
	    case 'T':
		XmI18List_state(ilist) |= TOGGLE;	/* set extended mode. */
		break;
	    default:
	        {
		    Cardinal num = 1;
		    XtAppWarningMsg(XtWidgetToApplicationContext(w),
				    XmNbadActionParameters,
				    XmNbadActionParameters,
				    XmCICSWidgetSetError,
				    XmNbadActionParametersMsg,
				    params, &num);
                }
	    }
	}
    }
	    
    if (event->type != ButtonPress) {
        Cardinal num = 2;
        static String params[] = { "Extended List", "BtnDown" };

        XtAppWarningMsg(XtWidgetToApplicationContext(w),
                        XmNunexpectedEvent, XmNunexpectedEvent,
                        XmCICSWidgetSetError, XmNunexpectedEventMsg,
                        params, &num);

	return;
    }

    CvtPositionToRowColumn(w, bevent->x, bevent->y, &row, &col);

    if (XmI18List_working_row(ilist) != row) {
	/*
	 * This click not in the same row as the previous one, reset time to
	 * zero so that double click will not fire.
	 */
	XmI18List_time(ilist) = 0;	
    }

    XmI18List_working_row(ilist) = row;
    XmI18List_working_col(ilist) = col;

    /*
     * Invalid row.
     */

    if ((col >= XmI18List_num_columns(ilist)) || (row >= XmI18List_num_rows(ilist)))
    {
	    XBell(XtDisplay(w), 0);
    	return;
    }

    /*
     * Click in the column headers.  No need to deal with double clicks
     * or extended selections.
     */

    if (XmI18List_working_row(ilist) == IN_COLUMN_HEADER)
    {
	    SelectHeader((Widget) ilist, XmI18List_working_col(ilist));
    	return;
    }
	else /* reset search column since user selected a new row */
		XmI18List_search_column(ilist) = -1;

    if ((event->xbutton.time - XmI18List_time(ilist)) >
	    XtGetMultiClickTime(XtDisplay(w)))
    {
    	SingleClick(ilist);
    }
#ifdef CR1166
    /*
     * Invalid row started selection.
     */

    if ((XmI18List_working_col(ilist) >= XmI18List_num_columns(ilist)) || 
       (XmI18List_working_row(ilist) >= XmI18List_num_rows(ilist))) 
    {
       return;
    }

    /*
     * Click in a row, need to handle double click.
     * notify_type == True specifies double click, False is a single click.
     */

    notify_type = ((event->xbutton.time - XmI18List_time(ilist)) <=
                  XtGetMultiClickTime(XtDisplay(w)));

    Notify(w, notify_type);

    XmI18List_time(ilist) = event->xbutton.time;
#endif /* CR1166 */
}
#undef CR1166

/*	Function Name: ButtonUpOrLeaveAction
 *	Description:   Called when the user sends a button up to the ilist.
 *	Arguments:     w - the ilist widget.
 *                     event - the event that caused this action.
 *                     params, num_params - action routine parameters.
 *	Returns:       none.
 */
#define CR1166
/*ARGSUSED*/
static void
ButtonUpOrLeaveAction(Widget w, XEvent *event, 
		      String *params, Cardinal *num_params)
{
#ifndef CR1166
    Boolean notify_type;
#endif
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    if (event->type != ButtonRelease) {
	Cardinal num = 2;
	static String params[] = { "Extended List", "BtnUp or BtnLeave" };
	
	XtAppWarningMsg(XtWidgetToApplicationContext(w),
			XmNunexpectedEvent, XmNunexpectedEvent,
			XmCICSWidgetSetError, XmNunexpectedEventMsg,
			params, &num);
	
	return;
    }

#ifndef CR1166
    /*
     * Invalid row started selection.
     */

    if ((XmI18List_working_col(ilist) >= XmI18List_num_columns(ilist)) || 
	(XmI18List_working_row(ilist) >= XmI18List_num_rows(ilist))) 
    {
	return;
    }

    /*
     * Click in a row, need to handle double click.
     * notify_type == True specifies double click, False is a single click.
     */

    notify_type = ((event->xbutton.time - XmI18List_time(ilist)) <=
		   XtGetMultiClickTime(XtDisplay(w)));

    Notify(w, notify_type);

    XmI18List_time(ilist) = event->xbutton.time;

    /*
     * Reset all these flags. 
     */
#endif /* CR1166 */
    XmI18List_state(ilist) &= ~OUTSIDE_WIDGET;
}
#undef CR1166

/*	Function Name: MotionAction
 *	Description:   Called when the user sends a button up to the ilist.
 *	Arguments:     w - the ilist widget.
 *                     event - the event that caused this action.
 *                     params, num_params - action routine parameters.
 *	Returns:       none.
 */

/*ARGSUSED*/
static void
MotionAction(Widget w, XEvent *event, String *params, Cardinal *num_params)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    XButtonEvent * bevent = (XButtonEvent *) event;
    short row, col;
    short y = bevent->y;

    /*
     * Invalid row to start selection.
     */

    if ((XmI18List_working_col(ilist) >= XmI18List_num_columns(ilist)) || 
	(XmI18List_working_row(ilist) >= XmI18List_num_rows(ilist))) 
    {
	return;
    }

    if (XmI18List_selection_policy(ilist) == XmSINGLE_SELECT) 
	return;			/* Do nothing here... */

    CvtPositionToRowColumn(w, bevent->x, y,  &row, &col); 
    
    /*
     * We have not moved to a new row, or we started in the headers then
     * do nothing.
     */
    
    if ((row == XmI18List_working_row(ilist)) || 
	(XmI18List_working_row(ilist) == IN_COLUMN_HEADER)) 
    {
	return;
    }

    /*
     * Begin reporting motion events.
     */
    
    if (y < 0) {
	if (XmI18List_state(ilist) & OFF_TOP)
	    return;		/* We are already off the top. */
	else
	    XmI18List_state(ilist) |= OFF_TOP;
    }
    else
	XmI18List_state(ilist) &= ~OFF_TOP;	/* remove this flag. */
    
    if (y > ((short) w->core.height)) {
	if (XmI18List_state(ilist) & OFF_BOTTOM)
	    return;		/* We are already off the bottom. */
	else
	    XmI18List_state(ilist) |= OFF_BOTTOM;
    }
    else
	XmI18List_state(ilist) &= ~OFF_BOTTOM;	/* remove this flag. */
    
    if (!(XmI18List_state(ilist) & OUTSIDE_WIDGET)) { /* Not outside widget.*/
	if (XmI18List_timeout(ilist) != NoTimeout) {
	    (void) XtRemoveTimeOut(XmI18List_timeout(ilist));
	    XmI18List_timeout(ilist) = NoTimeout; /* CR03695 */
        }
	ExtendedSelect(w, row);
	XmI18List_working_row(ilist) = NO_SELECTION; /* set to nothing... */
	return;
    }

    XmI18List_timeout(ilist) = XtAppAddTimeOut(XtWidgetToApplicationContext(w),
					   DELAY_TIME(w),
					   MoveListTimeout, (XtPointer) w);
}

/*	Function Name: SingleClick
 *	Description:   Called to process the single click.
 *	Arguments:     ilist - the ilist widget.
 *	Returns:       none.
 */

/*ARGSUSED*/
static void
SingleClick(XmI18ListWidget ilist)
{
    if (XmI18List_selection_policy(ilist) == XmSINGLE_SELECT)  {
	/*
	 * Unselect all rows except the working row.
	 */

	UnselectRows((Widget) ilist, XmI18List_working_row(ilist));
    }
    else {
	register short i, last;
	Xm18RowInfo * ptr;

	last = XmI18List_num_rows(ilist);
	if (!(XmI18List_state(ilist) & EXTEND)) {
	    XmI18List_end(ilist) = XmI18List_anchor(ilist) = XmI18List_working_row(ilist);

	    if (XmI18List_state(ilist) & TOGGLE)
		ToggleRow((Widget) ilist, XmI18List_working_row(ilist));
	    else		/* !EXTEND and !TOGGLE */
		UnselectRows((Widget) ilist, XmI18List_working_row(ilist));
	 
	    for (ptr = XmI18List_row_data(ilist), i = 0; i < last; i++, ptr++) 
		ptr->old_sel_state = ptr->selected;
	}
	else {
	    short l_first, l_last;

	    if (XmI18List_anchor(ilist) == NO_SELECTION) 
		return;

	    if (XmI18List_end(ilist) < XmI18List_anchor(ilist)) {
		l_first = XmI18List_end(ilist);
		l_last = XmI18List_anchor(ilist);
	    }
	    else {
		l_first = XmI18List_anchor(ilist);
		l_last = XmI18List_end(ilist);
	    }
	    
	    for (ptr = XmI18List_row_data(ilist), i = 0; i < last; i++, ptr++) {
		if ((i >= l_first) && (i <= l_last))
		    ptr->old_sel_state = FALSE;
		else
		    ptr->old_sel_state = ptr->selected;
	    }

	    if (XmI18List_state(ilist) & EXTEND)
		ExtendedSelect((Widget) ilist, XmI18List_working_row(ilist));
	}
    }
}

/*	Function Name: MoveListTimeout
 *	Description:   Called when enough time passes so that we know it 
 *                     is time to move the list.
 *	Arguments:     w_ptr - the ilist widget.
 *                     id - the interval id.
 *	Returns:       none.
 */

/*ARGSUSED*/
static void
MoveListTimeout(XtPointer w_ptr, XtIntervalId *id)
{
    short row;
    int v_inc = 0;
    Widget w = (Widget) w_ptr;
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    if (XmI18List_state(ilist) & OFF_TOP) {
	/*
	 * Scroll up if top row is not on screen.
	 */
	if ((IsRowVisible(w, 0)) != 0)
	    v_inc = -1;
    }

    if (XmI18List_state(ilist) & OFF_BOTTOM) {
	/*
	 * Scroll up if last row is not on screen.
	 */
	if ((IsRowVisible(w, XmI18List_num_rows(ilist) - 1)) != 0)
	    v_inc = 1;
    }

    if (v_inc == 0) {
	XmI18List_timeout(ilist) = NoTimeout; /* CR03695 */
	return;
    }
    VScroll(w, v_inc);
    ResizeSliders(w);	/* Reset the sliders on my scrollbars. */
    
    /*
     * Get new end point (first or last row on screen).
     */
    
    if (v_inc < 0) 
	row = XmI18List_first_row(ilist);
    else {
	register int i;
	register int row_height = XmI18List_row_height(ilist);
	register Dimension h, height = w->core.height;
	
	i = XmI18List_first_row(ilist);
	h = (XmI18List_sep_y(ilist) + VERTICAL_SPACE/2);
	
	if(XmI18List_new_visual_style(ilist))
	    h += ilist->primitive.shadow_thickness;
	else
	    h += LINE_HEIGHT;
	
	/*
	 * This used to be:
	 * for (; h < height; h += row_height, i++) {}
	 *
	 * ... sigh ...
	 */
	while(h < height) {
	    h += row_height;
	    i++;
	}

	i--;
	
	if (i > (XmI18List_num_rows(ilist) - 1))
	    row = XmI18List_num_rows(ilist) - 1;
	else
	    row = i;
    }
    
    ExtendedSelect(w, row);

    /*
     * And we can do it again...
     */

    XmI18List_timeout(ilist) = XtAppAddTimeOut(XtWidgetToApplicationContext(w),
					   DELAY_TIME(w),
					   MoveListTimeout, (XtPointer) w);    
}

/*	Function Name: Notify
 *	Description:   Calls the callbacks when a notify should happen.
 *	Arguments:     w - the ilist widget.
 *                     dclick - is this a double click?
 *	Returns:       none.
 */

static void
Notify(Widget w, Boolean dclick)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    Boolean first = True;
    static XrmQuark elist_q;
    int row;

    if (first) {
	elist_q = XrmStringToQuark(XM_EXT_18_LIST_CLASS_NAME);
	first = False;
    }

    row = (int) XmI18List_working_row(ilist);

    /*
     * If we didn't click on a row, don't call the callbacks
     */
    if(row == IN_COLUMN_HEADER)
	return;

    if( (row < XmI18List_num_rows(ilist)) &&
	(XmI18List_working_col(ilist) < XmI18List_num_columns(ilist)) )
    {
	Widget    elist = XtParent(XtParent(w));

	XtPointer cbdata;
	if(row >= 0) 
	    cbdata = (XtPointer) &(XmI18List_row_data(ilist)[row]);
	else
	    cbdata = NULL;

	/*
	 * If my parent is an extended list, then call all callbacks
	 * on its callback list. 
	 *
	 * This is a hack to get around a toolkit specification bug.
	 *
	 * Chris D. Peterson (11/25/90)
	 */

	if( dclick )
	{
	    if( _XmUtilIsSubclassByNameQ(elist, elist_q) ) 
	    {
		XtCallCallbacks(elist, XmNdoubleClickCallback, cbdata);
	    }
	    XtCallCallbackList(w, XmI18List_double_click(ilist), cbdata);
	}
	else /* Is Single notify */
	{
	    if( _XmUtilIsSubclassByNameQ(elist, elist_q) ) 
	    {
		XtCallCallbacks(elist, XmNsingleSelectionCallback, cbdata);
	    }
	    XtCallCallbackList( w, XmI18List_single_select(ilist), cbdata);
	}
    }
}

/************************************************************
 *
 * Internal routines.
 *
 ************************************************************/

/*	Function Name: GetListWidth
 *	Description:   determines total width of data in list
 *	Arguments:     w - Extended List Widget 
 *	Returns:       total width of data in list
 */

static short
GetListWidth(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i, width;

    /*
     * Get maximum width of data to display
     */
    width = HORIZONTAL_SPACE;
    for (i=0; i < XmI18List_num_columns(ilist); i++)
        width += XmI18List_column_widths(ilist)[i] + HORIZONTAL_SPACE;
 
    return((short) width);
}

/*	Function Name: AdjustFirstCol
 *	Description:   Called when this widget has been resized.
 *	Arguments:     w - Extended List Widget to realize.
 *	Returns:       none.
 */

static void 
AdjustFirstCol(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i, extra, width;

    /*   
     * Determine if the first pixel position is negative or positive
     */
    if ((0 - XmI18List_left_loc(ilist)) >= 0)
        i = 0 - XmI18List_left_loc(ilist);
    else
        i = XmI18List_left_loc(ilist);

    /*
     * If the current pixel position (signed positive) plus the core
     * width of the list is greater than the whole width of the data
     * being displayed, then we need to adjust the first pixel position
     */
    width = GetListWidth((Widget) ilist);
    extra = width - (ilist->core.width + i);
    if (extra < 0)
        XmI18List_left_loc(ilist) = 0 - (i + extra);
}

/*	Function Name: ExtendedSelect
 *	Description:   Handle the extended selection.
 *	Arguments:     w - the ilist widget.
 *                     row - current row.
 *                     extend - extend the selection.
 *	Returns:       none
 */

static void
ExtendedSelect(Widget w, short row)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register short i, first, last, end, anchor, out_first, out_last;
    Boolean state;
    Xm18RowInfo * ptr;

    if (row >= XmI18List_num_rows(ilist))
	row = XmI18List_num_rows(ilist) - 1;
    else if (row < 0)
	row = 0;

    end = XmI18List_end(ilist);	/* The old non-anchor end point. */
    anchor = XmI18List_anchor(ilist);
    XmI18List_end(ilist) = row;	/* New non-anchor end point. */
    state = (XmI18List_row_data(ilist) + anchor)->selected;

    if (XmI18List_anchor(ilist) < end) {
	out_first = anchor;
	out_last = end;
    }
    else {
	out_first = end;
	out_last = anchor;
    }

    if (row < out_first) {
	first = row;
	last = out_last;
	out_first = out_last + 1;	/* nothing removed from list. */
    }
    else if (row > out_last) {
	first = out_first;
	last = row;
	out_first = out_last + 1;	/* nothing removed from list. */
    }
    else {			/* between first and last. */
	if (out_first == anchor) {
	    first = out_first;
	    last = row;
	    out_first = row + 1;
	}
	else {
	    out_last = row - 1;
	    first = row;
	    last = out_last;
	}
    }

    /*
     * Handle the case of a jump from one side of the anchor to the other.
     */

    if (((end > anchor) && (row < anchor)) ||
	((end < anchor) && (row > anchor)))
    {
	register short t_first, t_last;

	if ((end > anchor) && (row < anchor)) {
	    t_first = anchor + 1;
	    t_last = end;
	    last = anchor;
	}
	else {  /* (end < anchor) && (row > anchor) */
	    first = anchor;
	    t_first = end;
	    t_last = anchor - 1;
	}

	/*
	 * Reset all these nodes to their previous state.
	 */

	ptr = XmI18List_row_data(ilist) + t_first;
	for (i = t_first; i <= t_last; i++, ptr++) 
	    if (ptr->old_sel_state != ptr->selected)
		ToggleRow(w, i);
    }

    /*
     * Set all these nodes to the same state as the anchor.
     */

    for (ptr = XmI18List_row_data(ilist) + first,i = first; i <= last;i++, ptr++) 
	if (ptr->selected != state)
	    ToggleRow(w, i);

    /*
     * Reset all these nodes to their previous state.
     */

    ptr = XmI18List_row_data(ilist) + out_first;
    for (i = out_first; i <= out_last;i++, ptr++) {
	if (ptr->old_sel_state != ptr->selected)
	    ToggleRow(w, i);
    }
}

/*	Function Name: VScrollCallback
 *	Description:   Called by the vert. scrollbar when it has been selected
 *                     by the user.
 *	Arguments:     w - the scrollbar widget.
 *                     client_data - the ilist widget.
 *                     call_data - information about where to scroll.
 *	Returns:       none
 */

/*ARGSUSED*/ 
static void
VScrollCallback(Widget w, XtPointer client_data, XtPointer call_data) 
{
    XmI18ListWidget ilist = (XmI18ListWidget) client_data;
    XmScrollBarCallbackStruct * scroll_info;

    scroll_info = (XmScrollBarCallbackStruct *) call_data;

    VScroll((Widget) ilist, (short) (scroll_info->value -
				     XmI18List_first_row(ilist)));
}

/*	Function Name: HScrollCallback
 *	Description:   Called by the horiz. scrollbar when it 
 *                     has been selected.
 *                     by the user.
 *	Arguments:     w - the scrollbar widget.
 *                     client_data - the ilist widget.
 *                     call_data - information about where to scroll.
 *	Returns:       none
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */
 
/*ARGSUSED*/ 
static void
HScrollCallback(Widget w, XtPointer client_data, XtPointer call_data) 
{
    XmI18ListWidget ilist = (XmI18ListWidget) client_data;
    XmScrollBarCallbackStruct *scroll_info;

    scroll_info = (XmScrollBarCallbackStruct *) call_data;

    HScroll((Widget)ilist,(short) scroll_info->value);

}
    
/*	Function Name: HSlideLeftArrowCallback
 *	Description:   handles repositioning of the window data according
 *                     to how long the user pressed on the left arrow
 *	Arguments:     w - the ilist widget.
 *                     client_data - the ilist widget.
 *                     junk - ***UNUSED***
 *	Returns:       none
 * 
 *      Added:         03/19/92 beth - for conversion to pixels
 */

/*ARGSUSED*/
static void
HSlideLeftArrowCallback(Widget w, XtPointer client_data, XtPointer junk) 
{
    XmI18ListWidget ilist = (XmI18ListWidget) client_data;

    /*
     * We are either going to left adjust the first visible column
     * so that the user is able to see the column beginning with the
     * first pixel or - if the first visible pixel is currently between
     * columns, then we will shift all columns once to the left,
     * thereby changing the first visible column.
     */

    /*
     * Don't bother if we're already as far left as we can go
     */
    if (XmI18List_left_loc(ilist) <= 0) {
        register int i, begin, end, before = 0;

        for (i=0; i < XmI18List_num_columns(ilist); i++) {
            if (i == 0) 
                begin = before = XmI18List_left_loc(ilist);
            else
                begin = before + HORIZONTAL_SPACE;
            end = begin + XmI18List_column_widths(ilist)[i];
            if (begin < 0 && end >= 0) {
                /*
                 * Leftmost column column is partially visible
                 * left adjust it including horizontal spacing
                 */
                XmI18List_left_loc(ilist) += 0 - before;
                break;
            } else if (begin >= 0 && i > 0) {
                /*
                 * Shift Leftmost column to the right once
                 */
                XmI18List_left_loc(ilist) += 0 - before + HORIZONTAL_SPACE;
                XmI18List_left_loc(ilist) += XmI18List_column_widths(ilist)[i-1];
                break;
            }
            before = end;
        }
    } else {
        XmI18List_left_loc(ilist) = 0;
    }

    XClearWindow(XtDisplay(ilist), XtWindow(ilist));
    DisplayList((Widget) ilist, XmI18List_first_row(ilist), 
                (XmI18List_num_rows(ilist) - XmI18List_first_row(ilist)), TRUE);
    DrawSeparator((Widget) ilist);
    ResizeSliders((Widget) ilist);
}

/*	Function Name: HSlideRightArrowCallback
 *	Description:   handles repositioning of the window data according
 *                     to how long the user pressed on the right arrow
 *	Arguments:     w - the ilist widget.
 *                     client_data - the ilist widget.
 *                     junk - ***UNUSED***
 *	Returns:       none
 * 
 *      Added:         03/19/92 beth - for conversion to pixels
 */

/*ARGSUSED*/
static void
HSlideRightArrowCallback(Widget w, XtPointer client_data, XtPointer junk) 
{
    XmI18ListWidget ilist = (XmI18ListWidget) client_data;
    register int i, width;

    /*
     * We are either going to left adjust the last visible column
     * so that the user is able to see the column beginning with the
     * first pixel or the entire column - if the last visible pixel
     * is currently between columns, then we will shift all columns
     * once to the right, thereby changing the last visible column.
     */
     
    if ((0 - XmI18List_left_loc(ilist)) >= 0)
        i = XmI18List_left_loc(ilist);
    else
        i = 0 - XmI18List_left_loc(ilist);

    /*
     * Don't bother if we're already as far right as we can go
     */
    width = GetListWidth((Widget) ilist);
    if ((int)width > (int)(i + ilist->core.width)) {
        register int begin, end, before = 0;

        for (i=0; i < XmI18List_num_columns(ilist); i++) {
            if (i == 0) 
                begin = before = XmI18List_left_loc(ilist);
            else
                begin = before + HORIZONTAL_SPACE;
            end = begin + XmI18List_column_widths(ilist)[i];
            if ((begin < 0 && end > 0) ||
                (begin >= 0 && i < XmI18List_num_columns(ilist))) {
                /*
                 * Leftmost column is partially visible
                 * make as much of it visible as possible
                 */
                if ((i + 1) == XmI18List_num_columns(ilist))
                    XmI18List_left_loc(ilist) = 0 - (width - ilist->core.width);
                else
                    XmI18List_left_loc(ilist) -= end;
                break;
            }
            before = end;
        }

    } else {
        XmI18List_left_loc(ilist) = 0 - (width - ilist->core.width);
    }

    XClearWindow(XtDisplay(ilist), XtWindow(ilist));
    DisplayList((Widget) ilist, XmI18List_first_row(ilist), 
                (XmI18List_num_rows(ilist) - XmI18List_first_row(ilist)), TRUE);
    DrawSeparator((Widget) ilist);
    ResizeSliders((Widget) ilist);
}

/************************************************************
 *
 * Local Code
 *
 ************************************************************/

/*	Function Name: CalcLocations
 *	Description:   Calculates the locations of the text positions.
 *	Arguments:     w - the ext list widget.
 *	Returns:       none
 */

static void CalcLocations(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    if (XmI18List_num_columns(ilist) && XmI18List_column_titles(ilist)) /* CR03506 */
    XmI18List_sep_y(ilist) = 2 * VERTICAL_SPACE
	+ XmI18List_title_row_height(ilist);
    else XmI18List_sep_y(ilist) = 0; /* CR03506 */
    if(XmI18List_new_visual_style(ilist))
	XmI18List_sep_y(ilist) += ilist->primitive.shadow_thickness;
}

/*	Function Name: DisplayList
 *	Description:   Displays the contents of the list.
 *	Arguments:     w - the extended list widget.
 *                     start_row - the first row to display
 *                     num_rows - the number of rows to display
 *                     redraw_headers - boolean flag for redrawing
 *	Returns:       none
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
DisplayList(Widget w, short start_row, short num_rows, Boolean redraw_headers)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i, j, row_height, title_row_height, y_loc, x_loc;
    register Position cur_x=0, cur_y, start_y;
    register short *col_widths, tot_width;
    XmString ptr;
    GC gc;
    Dimension width_unused, text_height;

    Dimension height = ilist->core.height;
    Dimension width = ilist->core.width;

    register short end_row = start_row + num_rows - 1;

    /*
     * The start position is always first_col, which
     * should have been set to the correct value before
     * calling this routine
     */

    if (XmI18List_left_loc(ilist) >= 0)
        XmI18List_left_loc(ilist) = HORIZONTAL_SPACE;
    cur_x = XmI18List_left_loc(ilist);

    col_widths = XmI18List_column_widths(ilist);

    tot_width = GetListWidth((Widget) ilist);

    /* 
     * Find the row height.
     */
    row_height = XmI18List_row_height(ilist) + VERTICAL_SPACE;
    title_row_height = XmI18List_title_row_height(ilist) + VERTICAL_SPACE;

    /*
     * Find the selected row, and draw in the select bar in the
     * background color.
     *
     * NOTE: this must draw exactly the same rectangle as InvertArea.
     */
    
    cur_y = (XmI18List_sep_y(ilist) + VERTICAL_SPACE/2 +
	     (start_row - XmI18List_first_row(ilist)) * row_height);
    
    if(XmI18List_new_visual_style(ilist)) {
        cur_y += ilist->primitive.shadow_thickness;
    }
    else {
	cur_y += LINE_HEIGHT;
    }

    if (XmI18List_entry_background_use(ilist))
    {
	Dimension height = ilist->core.height;
    	if(XmI18List_new_visual_style(ilist))
		height -= ilist->primitive.shadow_thickness;
	    else
		height -= LINE_HEIGHT;
	    XFillRectangle(XtDisplay(w), XtWindow(w), XmI18List_entry_background_fill_gc(ilist),
			   cur_x - HORIZONTAL_SPACE/2, cur_y,
#define MaX(a,b) (a>b?a:b)
			   (unsigned int) MaX(w->core.width,tot_width), 
#undef MaX
			   (unsigned int) height);
    }

    for (i = start_row ; i <= end_row ; i++) {
	if (XmI18List_row_data(ilist)[i].selected) {
	    XFillRectangle(XtDisplay(w), XtWindow(w), XmI18List_gc(ilist),
			   cur_x - HORIZONTAL_SPACE/2, cur_y,
			   (unsigned int) tot_width, 
			   (unsigned int) row_height);
	}
	
	cur_y += row_height;
    }

    start_y = ((XmI18List_sep_y(ilist) + VERTICAL_SPACE) +
	       (start_row - XmI18List_first_row(ilist)) * row_height);

    if(XmI18List_new_visual_style(ilist)) {
	start_y += ilist->primitive.shadow_thickness;
    }
    else {
	start_y += LINE_HEIGHT;
    }

    /*
     * Draw in the Text and icons.
     */

    for (i = 0; i < XmI18List_num_columns(ilist); i++) {
	GC entry_gc;

	if (cur_x > (int) width) 
	    return;
	
	if (redraw_headers) {

	    /*
	     * Paint the Column Header 
	     */
	    
	    if ((XmI18List_selected_header(ilist) == i) &&
		(XmI18List_sort_functions(ilist) != NULL))
	    {
		if (XtIsSensitive(w))
		    gc = XmI18List_rev_gc(ilist);
		else
		    gc = XmI18List_stippled_rev_gc(ilist);
		
		y_loc = VERTICAL_SPACE/2;
		x_loc = cur_x - HORIZONTAL_SPACE/2;
		
		XFillRectangle(XtDisplay(w), XtWindow(w), XmI18List_gc(ilist),
			       x_loc, y_loc, 
			       (unsigned int) col_widths[i] + HORIZONTAL_SPACE,
			       (unsigned int) title_row_height);
	    }
	    else {
		if (XtIsSensitive(w))
		    gc = XmI18List_gc(ilist);
		else
		    gc = XmI18List_stippled_gc(ilist);
	    }
	    
	    if (XmI18List_column_titles(ilist) != NULL)
	    {
		ptr = XmI18List_column_titles(ilist)[i];

		cur_y = VERTICAL_SPACE;

		if(XmI18List_new_visual_style(ilist))
		    cur_y += ilist->primitive.shadow_thickness;

		XmStringDraw(XtDisplay(w), XtWindow(w),
			     XmI18List_font_list(ilist), ptr, gc, cur_x, cur_y,
			     col_widths[i], XmI18List_alignment(ilist),
			     XmI18List_string_direction(ilist), NULL);
	    }
	}

	/*
	 * Put in the mini icons if this is column 0 and 
	 * first_col_pixmaps is true.
	 */
	
	if ( (XmI18List_first_col_pixmaps(ilist)) && (i == 0)) {
	    int pix_y_offset;

	    cur_y = XmI18List_sep_y(ilist) + VERTICAL_SPACE;
	    
	    if(XmI18List_new_visual_style(ilist))
		cur_y += ilist->primitive.shadow_thickness;
	    else
		cur_y += LINE_HEIGHT;

	    for (j = start_row; j <= end_row; j++) {
		if (IsValidPixmap(XmI18List_row_data(ilist)[j].pixmap)) {
		    
		    if (XmI18List_row_data(ilist)[j].selected) 
			entry_gc = XmI18List_entry_background_rev_gc(ilist);
		    else
			entry_gc = XmI18List_entry_background_gc(ilist);
		    
		    /*
		     * Copy it in.
		     */
		    pix_y_offset = 
		      (row_height - XmI18List_row_data(ilist)[j].pix_height)/2;
		    
		    if (XmI18List_row_data(ilist)[j].pix_depth == 1 ){
		      XCopyPlane(XtDisplay(w), XmI18List_row_data(ilist)[j].pixmap,
				 XtWindow(w), entry_gc, 0, 0,
				 XmI18List_row_data(ilist)[j].pix_width,
				 XmI18List_row_data(ilist)[j].pix_height,
				 cur_x, cur_y+pix_y_offset, (unsigned long) 1);
		    }
		    else {
		      XCopyArea(XtDisplay(w), XmI18List_row_data(ilist)[j].pixmap,
				 XtWindow(w), entry_gc, 0, 0,
				 XmI18List_row_data(ilist)[j].pix_width,
				 XmI18List_row_data(ilist)[j].pix_height,
				 cur_x, cur_y+pix_y_offset );
		    }
		}
		
		cur_y += row_height;
		if (cur_y > (int) height)
		    break;
	    }
	}
	else {
	    /* 
	     * Draw in the row data.
	     */
	    
	    cur_y = start_y;
	    for (j = start_row; j <= end_row; j++) {
		
		if (cur_y > (int) height)
		    break;
		
		if (XtIsSensitive(w)) {
		    if (XmI18List_row_data(ilist)[j].selected) 
			entry_gc = XmI18List_entry_background_rev_gc(ilist);
		    else
			entry_gc = XmI18List_entry_background_gc(ilist);
		}
		else {
		    if (XmI18List_row_data(ilist)[j].selected) 
			entry_gc = XmI18List_entry_background_stippled_rev_gc(ilist);
		    else
			entry_gc = XmI18List_entry_background_stippled_gc(ilist);
		}
		
		ptr = XmI18List_row_data(ilist)[j].values[i];

		XmStringExtent(XmI18List_font_list(ilist), ptr,
			       &width_unused, &text_height);

		/* to center each string within its row */
		cur_y += (int)(XmI18List_row_height(ilist) - VERTICAL_SPACE - 
			       text_height)/2;
		XmStringDraw(XtDisplay(w), XtWindow(w), 
			     XmI18List_font_list(ilist), ptr, entry_gc, cur_x, cur_y,
			     col_widths[i], XmI18List_alignment(ilist),
			     XmI18List_string_direction(ilist), NULL);
		
		cur_y -= (int)(XmI18List_row_height(ilist) - VERTICAL_SPACE -
			       text_height)/2;
		cur_y += XmI18List_row_height(ilist) + VERTICAL_SPACE;
	    }
	}
	    
	cur_x += HORIZONTAL_SPACE + col_widths[i];
    }
}

/*	Function Name: DrawSeparator
 *	Description:   Draws the line that separates the titles form the 
 *                     list elements.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none.
 */

static void
DrawSeparator(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    unsigned int width = ilist->core.width;
    unsigned int height = XmI18List_sep_y(ilist);
    GC gc;
    if (!XmI18List_num_columns(ilist) || !XmI18List_column_titles(ilist)) return; /* CR03506 */
    if(XmI18List_new_visual_style(ilist)) {
	XmeDrawShadows(XtDisplay(w), XtWindow(w),
		       ilist->primitive.top_shadow_GC,
		       ilist->primitive.bottom_shadow_GC,
		       0, 0, width,
		       height + ilist->primitive.shadow_thickness,
		       ilist->primitive.shadow_thickness,
		       XmSHADOW_OUT);
		       
		       
    }
    else
    {
	if (XtIsSensitive(w))
	    gc = XmI18List_gc(ilist);
	else
	    gc = XmI18List_stippled_gc(ilist);
	
	XFillRectangle(XtDisplay(w), XtWindow(w), gc,
		       0,
		       XmI18List_sep_y(ilist),
		       width,
		       LINE_HEIGHT);
    }
}

/*	Function Name: CreateGCs
 *	Description:   Creates the Graphics contexts.
 *	Arguments:     w - the ext list widget.
 *	Returns:       none.
 */

 /* Always create the entry_background GCs and always use them, but their 
 ** values may be different depending on whether or not to use the pixel
 ** (and may be identical to the regular GCs). We don't need new GCs for
 ** operations that don't use patterning or that don't use the background
 ** e.g. text/string draw operations.
 */

static void
CreateGCs(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;    
    XtGCMask mask, smask;
    XGCValues values;
    Arg args[2];
    Cardinal num_args = 0;                
    Pixel temp;
    Pixmap stipple;
    XFontStruct *font;

    stipple = XCreateBitmapFromData(XtDisplay(w), 
				    RootWindowOfScreen(XtScreen(w)), gray_bits,
				    gray_width, gray_height);

    XtSetArg(args[num_args], XmNforeground, &(values.foreground)); num_args++;
    XtSetArg(args[num_args], XmNbackground, &(values.background)); num_args++;
    XtGetValues(w, args, num_args);

    XmeRenderTableGetDefaultFont (XmI18List_font_list(ilist), &font);

    values.font = font->fid;
    values.stipple = stipple;
    values.fill_style = FillStippled;
    values.graphics_exposures = False;

    mask = GCForeground | GCBackground | GCFont | GCGraphicsExposures;
    smask = mask | GCStipple | GCFillStyle;
    
    XmI18List_gc(ilist) = XtGetGC(w, mask, &values);

    if (XmI18List_entry_background_use(ilist))
    {
	Pixel cache_foreground = values.foreground;
	values.foreground = XmI18List_entry_background_pixel(ilist);
    	XmI18List_entry_background_fill_gc(ilist) = XtGetGC(w, mask, &values);
	values.foreground = cache_foreground;
    }
    else
    {
	/* same as XmI18List_gc */
	/* not really used in this case */
    	XmI18List_entry_background_fill_gc(ilist) = XtGetGC(w, mask, &values);
    }

    if (XmI18List_entry_background_use(ilist))
    {
	Pixel cache_background = values.background;
	values.background = XmI18List_entry_background_pixel(ilist);
    	XmI18List_entry_background_gc(ilist) = XtGetGC(w, mask, &values);
	values.background = cache_background;
    }
    else
    {
	/* same as XmI18List_gc */
    	XmI18List_entry_background_gc(ilist) = XtGetGC(w, mask, &values);
    }

    XmI18List_stippled_gc(ilist) = XtGetGC(w, smask, &values);

    if (XmI18List_entry_background_use(ilist))
    {
	Pixel cache_background = values.background;
	values.background = XmI18List_entry_background_pixel(ilist);
    	XmI18List_entry_background_stippled_gc(ilist) = XtGetGC(w, smask, &values);
	values.background = cache_background;
    }
    else
    {
	/* same as XmI18List_stippled_gc */
    	XmI18List_entry_background_stippled_gc(ilist) = XtGetGC(w, smask, &values);
    }

    temp = values.foreground;
    values.foreground = values.background;
    values.background = temp;
    XmI18List_rev_gc(ilist) = XtGetGC(w, mask, &values);

    if (XmI18List_entry_background_use(ilist))
    {
	Pixel cache_foreground = values.foreground;
	values.foreground = XmI18List_entry_background_pixel(ilist);
    	XmI18List_entry_background_rev_gc(ilist) = XtGetGC(w, mask, &values);
	values.foreground = cache_foreground;
    }
    else
    {
	/* same as XmI18List_rev_gc */
    	XmI18List_entry_background_rev_gc(ilist) = XtGetGC(w, mask, &values);
    }

    XmI18List_stippled_rev_gc(ilist) = XtGetGC(w, smask, &values);

    if (XmI18List_entry_background_use(ilist))
    {
	Pixel cache_background = values.background;
	values.background = XmI18List_entry_background_pixel(ilist);
    	XmI18List_entry_background_stippled_rev_gc(ilist) = XtGetGC(w, smask, &values);
	values.background = cache_background;
    }
    else
    {
	/* same as XmI18List_stippled_rev_gc */
    	XmI18List_entry_background_stippled_rev_gc(ilist) = XtGetGC(w, smask, &values);
    }

    values.foreground ^= values.background;
    values.function = GXxor;
    mask = GCForeground | GCFunction;
    
    XmI18List_inv_gc(ilist) = XtGetGC(w, mask, &values);

    if (XmI18List_entry_background_use(ilist))
    {
	/* last one; we can skip caching */
	/* Pixel cache_foreground = values.foreground; */
	/* Pixel cache_background = values.background; */
	values.foreground = XmI18List_entry_background_pixel(ilist);
	values.foreground ^= values.background;
    	XmI18List_entry_background_inv_gc(ilist) = XtGetGC(w, mask, &values);
	/* values.background = cache_background; */
	/* values.foreground = cache_foreground; */
    }
    else
    {
	/* same as XmI18List_inv_gc */
    	XmI18List_entry_background_inv_gc(ilist) = XtGetGC(w, mask, &values);
    }


    XFreePixmap(XtDisplay(w), stipple);
}

/*	Function Name: DestroyGCs
 *	Description:   Destroys all GC's needed by the list.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none.
 */

static void
DestroyGCs(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    XtReleaseGC(w, XmI18List_gc(ilist));
    XtReleaseGC(w, XmI18List_rev_gc(ilist));

    XtReleaseGC(w, XmI18List_stippled_gc(ilist));
    XtReleaseGC(w, XmI18List_stippled_rev_gc(ilist));

    XtReleaseGC(w, XmI18List_inv_gc(ilist));

    XtReleaseGC(w, XmI18List_entry_background_gc(ilist));
    XtReleaseGC(w, XmI18List_entry_background_fill_gc(ilist));
    XtReleaseGC(w, XmI18List_entry_background_stippled_gc(ilist));
    XtReleaseGC(w, XmI18List_entry_background_stippled_rev_gc(ilist));
    XtReleaseGC(w, XmI18List_entry_background_inv_gc(ilist));
    XtReleaseGC(w, XmI18List_entry_background_rev_gc(ilist));
}

/*	Function Name: GetPixmapInfo
 *	Description:   Gets the information about each pixmap.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none
 */

static void
GetPixmapInfo(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i, num_rows = XmI18List_num_rows(ilist);

    for (i = 0; i < num_rows; i++) {
	int x, y;
	unsigned int width, height, bw, depth;
	Window root;

	width = height = depth = 0;

	if (IsValidPixmap(XmI18List_row_data(ilist)[i].pixmap)) {
	    XGetGeometry(XtDisplay(w), XmI18List_row_data(ilist)[i].pixmap,
			 &root, &x, &y, &width, &height, &bw, &depth);
	  }

	XmI18List_row_data(ilist)[i].pix_width = width;
	XmI18List_row_data(ilist)[i].pix_height = height;
	XmI18List_row_data(ilist)[i].pix_depth = depth;
    }
}

/*	Function Name: SetVisibleSize
 *	Description:   Calculates and sets list height (& optionally width)
 *	Arguments:     w - the ilist widget.
 *		       set_width - if true, set width
 *	Returns:       none
 */
static void
SetVisibleSize(Widget w, Boolean set_width)
{
    XmI18ListWidget	ilist = (XmI18ListWidget) w;
    Dimension		title_height, height;

    CalcColumnInfo(w, True);

    title_height = 2 * VERTICAL_SPACE +
	XmI18List_title_row_height(ilist);

    if(XmI18List_new_visual_style(ilist))
	title_height += ilist->primitive.shadow_thickness;
    else
	title_height += LINE_HEIGHT;
       
    /* If we have no rows, guess at row size with font struct info... */
    if (XmI18List_num_rows(ilist) == 0)
    {
	XFontStruct	*font = (XFontStruct *) NULL;

	XmeRenderTableGetDefaultFont(XmI18List_font_list(ilist), &font);

	if (font)
	    height = (font->ascent + font->descent + VERTICAL_SPACE) * 
		XmI18List_visible_rows(ilist);
	else
	    height = VERTICAL_SPACE * XmI18List_visible_rows(ilist);
    }
    else
    {
	height = (XmI18List_row_height(ilist) + VERTICAL_SPACE) * 
	    XmI18List_visible_rows(ilist);
    }

    /* Go ahead and set the widget's height resource... */
    ilist->core.height = title_height + height + VERTICAL_SPACE;

    if (set_width)
	ilist->core.width = GetListWidth(w);
}

/*	Function Name: CalcColumnInfo
 *	Description:   Calculates the layout info for the columns.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none
 */
static void
CalcColumnInfo(Widget w, Boolean force)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i, j;
    int max_width = 0, max_title_height = 0, max_height = 0;
    Dimension width, height;
    XmString ptr;

    register int num_cols = XmI18List_num_columns(ilist);
    register int num_rows = XmI18List_num_rows(ilist);

    if (XmI18List_first_col_pixmaps(ilist)) 
	GetPixmapInfo(w);

    if (((XmI18List_column_widths(ilist) == NULL) || force) && (num_cols != 0))
    {
	if (force)
	    XtFree((XtPointer) XmI18List_column_widths(ilist));
	XmI18List_column_widths(ilist) = (short *) XtMalloc(sizeof(short) *
							num_cols);
    }

    for (i = 0 ; i < num_cols; i++) {
	if (XmI18List_column_titles(ilist) != NULL)
	{
	    ptr = XmI18List_column_titles(ilist)[i];
	    XmStringExtent(XmI18List_font_list(ilist), ptr, &width, &height);

	    /* the max height for the title row */
	    if ((int) height > max_title_height) max_title_height = height;

	    /* find the max width for just this column */
	    max_width = width;
	}

	if (XmI18List_first_col_pixmaps(ilist) && (i == 0)) {
	    for (j = 0 ; j < num_rows; j++) {
		if( (int)(height =XmI18List_row_data(ilist)[j].pix_height) >
		    (int)max_height )
		    max_height = height;
		
		if ( (int)(width = XmI18List_row_data(ilist)[j].pix_width) >
		     (int)max_width )
		    max_width = width;
	    }
	}
	else {
	    for (j = 0 ; j < num_rows; j++) {
		ptr = XmI18List_row_data(ilist)[j].values[i];
		XmStringExtent(XmI18List_font_list(ilist), ptr, &width, &height);
		if ((int)width > (int)max_width)
		    max_width = width;
		if ((int)height > (int)max_height)
		    max_height = height;
	    }
	}

	XmI18List_column_widths(ilist)[i] = max_width;
    }
    XmI18List_row_height(ilist) = max_height;
    if (XmI18List_num_columns(ilist) && XmI18List_column_titles(ilist)) /* CR03506 */
    XmI18List_title_row_height(ilist) = max_title_height;
    else XmI18List_title_row_height(ilist) = 0; /* CR03506 */
}

/*	Function Name: ResizeSliders
 *	Description:   Resizes the thumbs of the v and h scrollbars.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
ResizeSliders(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;    
    Arg args[5];
    Cardinal num_args=0;
    register int i, height, max_width, rows_per_screen;
    register int slide_pos, slide_size, col_width=0, min=0;

    /*
     * Get maximum width of data to display
     */
    max_width = HORIZONTAL_SPACE;
    for (i=0; i < XmI18List_num_columns(ilist); i++) {
        if (XmI18List_column_widths(ilist)[i] > col_width)
            col_width = XmI18List_column_widths(ilist)[i];
        max_width += XmI18List_column_widths(ilist)[i] + HORIZONTAL_SPACE;
    }

    if (((col_width + HORIZONTAL_SPACE) != 0) &&
	(XmI18List_h_bar(ilist) != NULL)) 
    {
        /*
         * Adjust the slider size and page increment values
         * The size and position (returned and set) are relative to
         * the number of columns of data that we have - BUT, we
         * have to convert this information to pixels for correct
         * processing.
         */
        slide_size = ilist->core.width;
        if (slide_size < 1)
            slide_size = 1;
        if (slide_size > max_width)
            slide_size = max_width;

        /*
         * Adjust slider position according to new size
         * and location of first pixel of display data
         */
        if (XmI18List_left_loc(ilist) >= 0)
            slide_pos = 1;
        else {
            i = (0 - XmI18List_left_loc(ilist)) + ilist->core.width;
            if (i >= max_width)
                slide_pos = max_width - slide_size;
            else if (i < max_width)
                slide_pos = i - slide_size;
        }

        if (slide_pos < 1)
            slide_pos = 1;
        if (slide_pos > (max_width - slide_size))
            slide_pos = max_width - slide_size;

	XtSetArg(args[num_args], XmNvalue, slide_pos);           num_args++;
	XtSetArg(args[num_args], XmNmaximum, max_width);         num_args++;
	XtSetArg(args[num_args], XmNsliderSize, slide_size);     num_args++;
	XtSetArg(args[num_args], XmNpageIncrement, slide_size);  num_args++;
	XtSetValues(XmI18List_h_bar(ilist), args, num_args);
    }

    height = ilist->core.height - 
	     (2 * VERTICAL_SPACE + XmI18List_title_row_height(ilist));

    if(XmI18List_new_visual_style(ilist))
	height -= ilist->primitive.shadow_thickness;
    else
	height -= LINE_HEIGHT;

    if ((height > 0) && (XmI18List_v_bar(ilist) != NULL)) {
	int max_first;

	rows_per_screen = height / (XmI18List_row_height(ilist) + VERTICAL_SPACE);
	max_first = XmI18List_num_rows(ilist) - rows_per_screen;

	if (max_first < XmI18List_first_row(ilist)) {
	    if (max_first > 0)
		XmI18List_first_row(ilist) = max_first;
	    else
		XmI18List_first_row(ilist) = 0;
	}

        /*
         * Set up the scroll bars resources
         * MUST BE very thorough, otherwise warnings are issued.
         */
        slide_size = rows_per_screen;
        max_width = XmI18List_num_rows(ilist);
	slide_pos = XmI18List_first_row(ilist);
        if (max_width <= 1)
            max_width = 1;

        if (slide_size > max_width)
            slide_size = max_width;

        if (slide_pos > (max_width - slide_size))
            slide_pos = (max_width - slide_size);

        if (slide_pos < min)
            slide_pos = min;

	num_args = 0;
	XtSetArg(args[num_args], XmNminimum, min);              num_args++;
	XtSetArg(args[num_args], XmNvalue, slide_pos);          num_args++;
	XtSetArg(args[num_args], XmNmaximum, max_width);        num_args++;
	XtSetArg(args[num_args], XmNsliderSize, slide_size);    num_args++;
	XtSetArg(args[num_args], XmNpageIncrement, slide_size); num_args++;
	XtSetValues(XmI18List_v_bar(ilist), args, num_args);
    }
}

/*	Function Name: VScroll
 *	Description:   Scrolls the window a given number of
 *                     rows up or down (up is negative)
 *	Arguments:     w - the ICS list widget.
 *                     amount - the number of rows to scroll, negative
 *                              values scroll backward.
 *	Returns:       none
 */

static void
VScroll(Widget w, short amount)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    int y_start;
    short num_rows;

    XmI18List_first_row(ilist) += amount;
    if (XmI18List_first_row(ilist) < 0)
	XmI18List_first_row(ilist) = 0;

    y_start = XmI18List_sep_y(ilist);

    if(XmI18List_new_visual_style(ilist))
	y_start += ilist->primitive.shadow_thickness;
    else
	y_start += LINE_HEIGHT;

    XClearArea(XtDisplay(w), XtWindow(w), 0, y_start,
	       (unsigned int) 0, (unsigned int) 0, FALSE);

    num_rows = XmI18List_num_rows(ilist) - XmI18List_first_row(ilist);
    DisplayList(w, XmI18List_first_row(ilist), num_rows, TRUE);
}


/*	Function Name: CvtColNumToPixelVal
 *	Description:   determines which is the first visible pixel
 *                     in the passed column number
 *	Arguments:     w - the ilist widget data to retrieve info from
 *                     col - the column number to search in
 *	Returns:       the pixel value
 * 
 *      Added:         03/17/92 beth
 */

static short
CvtColNumToPixelVal(Widget w, short col)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i;
    short value=0;

    /*
     * Sum up the widest pixel values in each column
     * until we reach the passed in column
     */
    for (i = 0; i < col && i < XmI18List_num_columns(ilist); i++)
        value += XmI18List_column_widths(ilist)[i] + HORIZONTAL_SPACE;

    return(value);
}

/*	Function Name: CvtPixelValToColNum
 *	Description:   determines which is the visible column
 *                     corresponding to the passed pixel value
 *	Arguments:     w - the ilist widget data to retrieve info from
 *                     x - the x pixel value to look for
 *	Returns:       the column number
 * 
 *      Added:         03/17/92 beth
 */

static short
CvtPixelValToColNum(Widget w, short x)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register int i=0;
    short cur_col;

    /*
     * Sum up the widest pixel values in each column
     * and see where the passed in x pixel value falls
     */
    cur_col = XmI18List_left_loc(ilist);
    for (; i < XmI18List_num_columns(ilist); i++) {
        cur_col += XmI18List_column_widths(ilist)[i] + HORIZONTAL_SPACE;
        if (cur_col > x)
            break;
    }

    return((short) i);
}

/*	Function Name: HScroll
 *	Description:   Scrolls the window a given number of pixels/
 *                     columns left or right (left is negative)
 *	Arguments:     w - the ICS list widget.
 *                     amount - the pixel amount to scroll.
 *	Returns:       none
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
HScroll(Widget w, short amount)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    int y_start;
    unsigned int title_height;
    short num_rows;

    if ((0 - amount) >= 0)
        XmI18List_left_loc(ilist) = amount;
    else
        XmI18List_left_loc(ilist) = 0 - amount;

    title_height = XmI18List_sep_y(ilist);
    y_start = XmI18List_sep_y(ilist);

    if(XmI18List_new_visual_style(ilist))
	y_start += ilist->primitive.shadow_thickness;
    else
	y_start += LINE_HEIGHT;

    XClearArea(XtDisplay(w), XtWindow(w), 0, 0, 
	       (unsigned int) 0, title_height, FALSE);
    XClearArea(XtDisplay(w), XtWindow(w), 0, y_start, 
	       (unsigned int) 0, (unsigned int) 0, FALSE);

    num_rows = XmI18List_num_rows(ilist) - XmI18List_first_row(ilist);
    DisplayList(w, XmI18List_first_row(ilist), num_rows, TRUE);
}

/*	Function Name: CvtPositionToRowColumn
 *	Description:   Converts an X location to a row and column.
 *	Arguments:     w - the ilist widget.
 *                     x, y - the location in the window in pixel space.
 *  RETURNED           row, column - the location of this point in list space.
 *	Returns:       none.
 *
 * NOTE:  This functions can return cells the are off the end of
 *        the current space.  It is up to the caller to check
 *        to be sure he does not run off then end of an array.
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
CvtPositionToRowColumn(Widget w, short x, short y, short * row, short * column)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    int title_extra;

    if(XmI18List_new_visual_style(ilist))
	title_extra = ilist->primitive.shadow_thickness;
    else
	title_extra = LINE_HEIGHT;

    /*
     * See if the y pixel value passed is located in the header
     * or a row visible within the clip window or not visible at all
     */
    if (y < 0) {
        *row = IN_COLUMN_HEADER + y/(XmI18List_row_height(ilist) + VERTICAL_SPACE);
    } else if (y < (XmI18List_sep_y(ilist) + title_extra)) {
        *row = IN_COLUMN_HEADER;
    } else {
        y -= XmI18List_sep_y(ilist) + title_extra + VERTICAL_SPACE/2;

        *row = XmI18List_first_row(ilist) + y/(XmI18List_row_height(ilist) +
                                           VERTICAL_SPACE);
    }

    *column = CvtPixelValToColNum((Widget) w, x);
}

/*	Function Name: CvtRowColumnToPosition
 *	Description:   Converts a row and column to an X Window Position.
 *                     the coord's are of the upper left corner of the cell.
 *	Arguments:     w - the ilist widget.
 *                     row, column - the location of this point in list space.
 *    RETURNED         x, y - the location in the window in pixel space.
 *	Returns:       none.
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
CvtRowColumnToPosition(Widget w, short row, short column, short * x, short * y)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    int title_extra;

    if(XmI18List_new_visual_style(ilist))
	title_extra = ilist->primitive.shadow_thickness;
    else
	title_extra = LINE_HEIGHT;

    if (row == IN_COLUMN_HEADER) 
	*y = VERTICAL_SPACE/2;
    else {
	*y = (XmI18List_sep_y(ilist) + title_extra + 
	      (row - XmI18List_first_row(ilist)) * 
	      (XmI18List_row_height(ilist) + VERTICAL_SPACE) + VERTICAL_SPACE/2);
    }

    *x = CvtColNumToPixelVal((Widget) ilist, column);
}

/*	Function Name: ToggleRow
 *	Description:   Toggles the state of the given row.
 *	Arguments:     w - the ilist widget.
 *                     row - the row to select.
 *	Returns:       none
 */

static void
ToggleRow(Widget w, short row)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    XmI18List_row_data(ilist)[row].selected = !XmI18List_row_data(ilist)[row].selected;

    if (IsRowVisible(w, row) >= 0)
	InvertArea(w, row, ENTIRE_ROW);
}

/*	Function Name: UnselectRows
 *	Description:   Unselects some rows (see below) and returns the
 *                     row that was left selected.
 *	Arguments:     w - the ilist widget.
 *                     row - row to leave selected.
 *	Returns:       none.
 */

static void
UnselectRows(Widget w, short sel_row)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    register short row;
    Xm18RowInfo *ptr = XmI18List_row_data(ilist);

    XmI18List_end(ilist) = XmI18List_anchor(ilist) = sel_row;

    for (row = 0; row < XmI18List_num_rows(ilist); row++, ptr++) {
	/*
	 * if the row is correct and it is unselected 
	 * or if the row incorrect and it is selected then toggle the row.
	 */
	if (ptr->selected != (row == sel_row))
	    ToggleRow(w, row);
    }
}

/*	Function Name: SelectHeader
 *	Description:   Sets the header corrosponding to the column passed in.
 *	Arguments:     w - the ilist widget.
 *                     column - the column header to select.
 *	Returns:       none
 */

static void
SelectHeader(Widget w, short column)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    if ((XmI18List_selected_header(ilist) == column) ||
	(XmI18List_sort_functions(ilist) == NULL))
    {
	return;
    }

    XmI18List_selected_header(ilist) = column;

    SortList(w, True);		/* Causes a rediplay. */
}

/*	Function Name: SortList
 *	Description:   Sorts the elements in the list.
 *	Arguments:     w - the ilist widget.
 *                     redisplay - redraw the ilist widget.
 *	Returns:       none.
 */

static void
SortList(Widget w, Boolean redisplay)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    if (XmI18List_sort_functions(ilist) != NULL) {
	global_current_widget = w;
	qsort(XmI18List_row_data(ilist), XmI18List_num_rows(ilist),sizeof(Xm18RowInfo),
	      QSortTest);
	if (redisplay)
	    RedrawList(w);
    }
         /* this is kind of unnecessary, instead should just update headers */
    else RedrawList(w);    
}

/*	Function Name: QSortTest
 *	Description:   Takes the internal data, and the calls the 
 *                     appropriate sort routine supplied by the client.
 *	Arguments:     str1, str2 - the two values to compare.
 *	Returns:       
 */

static int 
QSortTest(const void * row1, const void * row2)
{
    XmI18ListWidget ilist = (XmI18ListWidget) global_current_widget;
    short col = XmI18List_selected_header(ilist);
    Xm18SortFunction sort_f = XmI18List_sort_functions(ilist)[(int)col];

    return ((*sort_f) (col, row1, row2));
}    


/*	Function Name: InvertArea
 *	Description:   Inverts the the area specified.
 *	Arguments:     w - the ilist widget.
 *                     row, column - row/column to invert.
 *	Returns:       none.
 *
 * NOTE:  The value IN_COLUMN_HEADER for the row means the area
 *        to be inverted is in the column header.
 *
 *        The value ENTIRE_ROW for the column causes the entire row to
 *        be inverted.
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
InvertArea(Widget w, short row, short column)
{
  XmI18ListWidget ilist = (XmI18ListWidget) w;
  unsigned int width, height;
  short x, y, pix_y_offset;
  GC gc_to_use;
  
  if (!XtIsRealized(w)) return; 

  if ((row == NO_SELECTION) || (column == NO_SELECTION))
    return;
  
  if (column == ENTIRE_ROW) {
    CvtRowColumnToPosition(w, row, 0, &x, &y);
    
    x = XmI18List_left_loc(ilist) - HORIZONTAL_SPACE/2;
    width = GetListWidth((Widget) ilist);
  }
  else {
    CvtRowColumnToPosition(w, row, column, &x, &y);
    width = HORIZONTAL_SPACE + XmI18List_column_widths(ilist)[column];
  }
  
  if (row == IN_COLUMN_HEADER)
  {
    height = XmI18List_title_row_height(ilist) + VERTICAL_SPACE;
    gc_to_use = XmI18List_inv_gc(ilist);
  }
  else
  {
    height = XmI18List_row_height(ilist) + VERTICAL_SPACE;
    gc_to_use = XmI18List_entry_background_inv_gc(ilist);
  }
  
  XFillRectangle(XtDisplay(w), XtWindow(w), gc_to_use,
		 (int) x, (int) y, width, height);
  
  if ( (XmI18List_first_col_pixmaps(ilist)) && 
       (XmI18List_row_data(ilist)[row].pix_depth != 1 ) &&
       IsValidPixmap(XmI18List_row_data(ilist)[row].pixmap) )
  {
      pix_y_offset = (height - XmI18List_row_data(ilist)[row].pix_height)/2;
      XCopyArea(XtDisplay(w), XmI18List_row_data(ilist)[row].pixmap,
		XtWindow(w), XmI18List_entry_background_gc(ilist), 0, 0,
		XmI18List_row_data(ilist)[row].pix_width,
		XmI18List_row_data(ilist)[row].pix_height,
		XmI18List_left_loc(ilist), y+pix_y_offset );
  }
}


/*	Function Name: RedrawList
 *	Description:   Redraws the current list contents.
 *	Arguments:     w - the ilist widget.
 *	Returns:       none.
 * 
 *      Modified:      03/17/92 beth - converted to pixels
 */

static void
RedrawList(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    short num_rows;

    if (XtIsRealized(w)) {
        XClearWindow(XtDisplay(w), XtWindow(w));

        num_rows = XmI18List_num_rows(ilist) - XmI18List_first_row(ilist);
        DisplayList(w, XmI18List_first_row(ilist), num_rows, TRUE);
        DrawSeparator(w);
    }
}

/*	Function Name: IsRowVisible
 *	Description:   returns 0 if the row is visable. Otherwise returns
 * 		the number of rows down we have to scroll (- values for up) 
 *		to make the row visible.
 *	Arguments:     w - the ilist widget.
 *                     row - the row to check.
 *	Returns:       none.
 */
 
static int
IsRowVisible(Widget w, short row)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    short r_row, r_col;

    if (row < XmI18List_first_row(ilist))
	return(row - XmI18List_first_row(ilist));
   
    CvtPositionToRowColumn((Widget) w, 0, (short) (ilist->core.height + 1),
			   &r_row, &r_col);
 
    if (row >= r_row)
	return(row - r_row + 1);
   
    return(0);
}

#ifdef UNUSED_FUNCTION
/*  Function Name: IsColumnVisible
 *  Description:   returns 0 if the column is visable. Otherwise returns
 *		the number of PIXELS right we have to scroll (- values for left)
 *		to make the column visible.
 *  Arguments:     w - the ilist widget.
 *                     column - the column to check.
 *  Returns:       none.
 */
static int
IsColumnVisible(Widget w, short column)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
	short r_col;	/* right-most column being displayed */
	short col, r_row;
	int pixel_shift = 0; /* return value */

    if (column < XmI18List_first_col(ilist))
      {
	for (col = column; col < XmI18List_first_col(ilist); col++)
	  pixel_shift -= XmI18List_column_widths(ilist)[col] + HORIZONTAL_SPACE;
	
	return (pixel_shift);
      }

    CvtPositionToRowColumn(w, (short) ilist->core.width, 0, &r_row, &r_col);


    if (column >= r_col)
      {
    	for (col = r_col+1; col <= column; col++)
	  pixel_shift += XmI18List_column_widths(ilist)[col] + HORIZONTAL_SPACE;
	
	return (pixel_shift);
      }
    
    return(0);
}
#endif

/*	Function Name: AdjustVisiblePosition
 *	Description:   makes the string found by find, visible
 *	Arguments:     w - the ilist widget.
 *                     position - the new position for lef_loc
 *                     check - whether we should check the new position
 *                             to see if it's valid
 *                     value - the amount to check the position against
 *	Returns:       none
 *
 *      Added:         03/17/92 beth - for conversion to pixels
 */

static void
AdjustVisiblePosition(Widget w, short position, Boolean check, short value)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    /*
     * Check to make sure that we can move the amount requested
     */
    if (check && position > value)
        position = 0 - value;
    else
        position = 0 - position;

    XmI18List_left_loc(ilist) += position;
    HScroll(w, XmI18List_left_loc(ilist));
    AdjustFirstCol(w);
    ResizeSliders(w);
}


static void
AdjustFirstRowAndCol( XmI18ListWidget ilist )
{
  Dimension total_width, height;
  int rows_per_screen, new_left_loc;
  register int j;
  int title_extra;
  
  if(XmI18List_new_visual_style(ilist))
      title_extra = ilist->primitive.shadow_thickness;
  else
      title_extra = LINE_HEIGHT;
  
  new_left_loc = 0;	
  for (j=0;  j < XmI18List_first_col(ilist); j++){
    new_left_loc -=  (XmI18List_column_widths(ilist)[j] + 
		      HORIZONTAL_SPACE);
  }

  total_width = GetListWidth((Widget)ilist);

  if (ilist->core.width > total_width ){
    XmI18List_left_loc(ilist) = 0;
  }
  else if (new_left_loc < (int)((int)ilist->core.width-
				(int)total_width)){
    XmI18List_left_loc(ilist) = (int)((int)ilist->core.width-
				  (int)total_width);
  }
  else XmI18List_left_loc(ilist) = new_left_loc;
  
  
  height = ilist->core.height - 
    (2 * VERTICAL_SPACE + XmI18List_title_row_height(ilist) +  title_extra);
  
  rows_per_screen = (int)height/(int)(XmI18List_row_height(ilist)+ VERTICAL_SPACE);
  
  if (XmI18List_num_rows(ilist) < rows_per_screen)
  {
      XmI18List_first_row(ilist) = 0;
  }
  else if (XmI18List_first_row(ilist) > (XmI18List_num_rows(ilist) - 
				     rows_per_screen))
  {
      XmI18List_first_row(ilist) = (XmI18List_num_rows(ilist) - rows_per_screen);
  }

}


/*	Function Name: MakePositionVisible
 *	Description:   makes sure that the string found by the find
 *                     procedure, is as visible (length) as possible
 *	Arguments:     w - the ilist widget.
 *                     row - the row to make visible.
 *                     start - the start pixel of the string
 *                     last - the last pixel of the string
 *                     width - the width of the display data
 *	Returns:       status (True if search and move worked).
 *
 *      Modified:      03/17/92 beth - converted to pixels
 */

static Boolean
MakePositionVisible(Widget w, short row, short start, short last, int width)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    short amount, before = 0;

    if ((amount = IsRowVisible(w, row)) != 0)
        VScroll(w, amount);

    /*
     * Adjust the start and last values for better viewing
     */
    if (start >= HORIZONTAL_SPACE)
        start -= HORIZONTAL_SPACE;
    last += HORIZONTAL_SPACE;

    /*
     * Convert the start pixel we want to see to visible pixels.
     * This involves comparing the start pixel location within
     * the visible window and seeing if it's possible to move
     * the visible window to contain the pixels we wish to see.
     */
    if (XmI18List_left_loc(ilist) < 0)
        before -= XmI18List_left_loc(ilist);

    if (XmI18List_left_loc(ilist) < 0 && before >= start) {
        /*
         * The start pixel is to the left of the visible window
         * pass a negative value - it will be converted to positive later
         */
        AdjustVisiblePosition((Widget) ilist, (0 - (before - start)), False, 0);
        return(TRUE);

    } else if (start >= before && start <= width) {
        short move, begin, end;

        if ((int)start <= (int)(before + ilist->core.width)) {
            /*
             * The start pixel is inside the visible window
             */

            begin = (before + ilist->core.width) - start;
            end = last - start;
            if (begin < end)
                move = end - begin;
            else
                move = 0;
        } else {
            /*
             * The start pixel is to the right of the visible window
             */
            move = last - (before + ilist->core.width);
        }

        if (move != 0)
            AdjustVisiblePosition((Widget) ilist, move, True, 
                                  (width - (before + ilist->core.width)));
        return(TRUE);
    }

    return(FALSE);
}

/************************************************************
 *
 * Exported Functions.
 *
 ************************************************************/

/* -kat 1/18/91
 * Function Name: XmI18ListGetSelectedRows
 * Description:   Takes an IList and returns a NULL terminated array 
 *                of pointers to selected rows
 * Arguments:     w - the ilist widget
 * Returns:       A NULL terminated array of the row info structures.
 *                NULL is returned if nothing is selected.
 */

Xm18RowInfo **
XmI18ListGetSelectedRows(Widget w)
{
    register int i, j;
    register Xm18RowInfo *row_data, **ptr;
    Xm18RowInfo **ret_rows = NULL;
    XmI18ListWidget ilist = (XmI18ListWidget) w;

    row_data = XmI18List_row_data(ilist);
    for (i = j = 0; j < XmI18List_num_rows(ilist); j++, row_data++) { 
	if (row_data->selected) 
	    i++;
    }
    
    if (i != 0) {
	ptr = ret_rows = (Xm18RowInfo **) XtMalloc(sizeof(Xm18RowInfo *) * 
						   (i + 1));
	ret_rows[i] = NULL;
	
	row_data = XmI18List_row_data(ilist);
	for (j = 0; j < XmI18List_num_rows(ilist); j++, row_data++) { 
	    if (row_data->selected) 
		*ptr++ = row_data;
	}
    }

    return(ret_rows);
}

/*  Function Name: XmI18ListDoSearch.
 *  Description:   Performs a search for the specified string.
 *  Arguments:     w - the ilist widget.
 *                     str - the string to search for.
 *                     reset - indicates if we are searching for
 *                             something new
 *  Returns:       status (True if search worked).
 *
 *      Rewritten:      11/17/93 dave - works for I18List now
 */

Boolean
XmI18ListDoSearch(Widget w, String str, Boolean reset)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    Boolean foundit;
    XmString xms = XmStringCreateLocalized(str);
    int found_row, found_column, search_column;

    int first_selected_row = FirstSelectedRow(w);

    if ( reset ) XmI18List_search_column(ilist) = -1;

	/*
	 * If we've searched last, be sure to start at NEXT column.
	 * Otherwise start at first (0th) column
	 */
    search_column = XmI18List_search_column(ilist) + 1;

    if ( first_selected_row == -1 ) first_selected_row = 0;

    foundit = Search(ilist, xms, 
		     first_selected_row, search_column,
		     &found_row, &found_column);

    if ( foundit )
    {
	XmI18List_search_column(ilist) = found_column;
	UnselectRows(w, found_row);
	MakeCellVisible(w, found_row, found_column);
    }
    else
    {
	XmI18List_search_column(ilist) = -1;
    }
    return (foundit);
}

/*  Function Name: XmI18ListFindRow
 *  Description:   Performs a search for the specified string.
 *  Arguments:     w - the ilist widget.
 *                 str - the string to search for.
 *                 reset - indicates if we are searching for
 *                         something new
 *		   do_visual - whether or not to toggle selected rows...
 *  Returns:       Xm18RowInfo of matching row (or NULL if no match found)
 *
 */
Xm18RowInfo *XmI18ListFindRow(Widget w, String str, int *found_column,
			      Boolean reset, Boolean do_visual)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    Xm18RowInfo *ptr = XmI18List_row_data(ilist);
    Boolean foundit;
    XmString xms = XmStringCreateLocalized(str);
    int found_row, search_column;
    int first_selected_row = FirstSelectedRow(w);

    if (reset)
	XmI18List_search_column(ilist) = -1;

    /*
     * If we've searched last, be sure to start at NEXT column.
     * Otherwise start at first (0th) column
     */
    search_column = XmI18List_search_column(ilist) + 1;

    if (first_selected_row == -1)
	first_selected_row = 0;

    foundit = Search(ilist, xms, first_selected_row,
		     search_column, &found_row, found_column);

    if (do_visual)
    {
	if (foundit)
	{
	    XmI18List_search_column(ilist) = *found_column;
	    UnselectRows(w, found_row);
	    MakeCellVisible(w, found_row, *found_column);
	}
	else
	    XmI18List_search_column(ilist) = -1;
    }

    return (Xm18RowInfo *)(foundit ? &ptr[found_row] : NULL);
}

static int
FirstSelectedRow(Widget w)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    Xm18RowInfo *ptr = XmI18List_row_data(ilist);
	int i;

	for (i=0;i<XmI18List_num_rows(ilist);i++)
	{
		if (ptr[i].selected)
		return (i);
	}

	/* fell thru. Nothing selected */
	return (-1);
}

static Boolean
Search(XmI18ListWidget ilist, XmString xms,
       int start_row, int start_column,
       int *found_row, int *found_column)
{
	int row, column;
	XmString value;

	/*
	 * First a quick check.  If we have no columns or rows then
	 * we cannot find anything.
	 */
	if( XmI18List_num_columns(ilist) == 0 || XmI18List_num_rows(ilist) == 0 )
	{
	    return( False );
	}

	for (row=start_row ; row < XmI18List_num_rows(ilist); row++)
	{
		for (column=start_column; column < XmI18List_num_columns(ilist);
			 column++)
		  {
		  if ((column != 0) || (!XmI18List_first_col_pixmaps(ilist))){
		    value = XmI18List_row_data(ilist)[row].values[column];
			if (XmStringHasSubstring(value, xms))
			  {
			    /* found it! */
			    *found_row = row;
			    *found_column = column;
			    return (True);
			  }
		  }
		}
		start_column = 0; /* all but the first start at zero */
	}

	/* didn't find it. Wrap search around */
	for (row=0; row <= start_row; row++)
        for (column=0; column < XmI18List_num_columns(ilist); column++)
	  if ((column != 0) || (!XmI18List_first_col_pixmaps(ilist))){
	    value = XmI18List_row_data(ilist)[row].values[column];
            if (XmStringHasSubstring(value, xms))
	      {
                /* found it! */
                *found_row = row;
                *found_column = column;
                return (True);
	      }
	  }
	/* fell thru. It's not there */
	return (False);
}

static void
MakeCellVisible(Widget w, int row, int col)
{
    XmI18ListWidget ilist = (XmI18ListWidget) w;
    short width = GetListWidth(w);     /* total width of list data */
    short start = CvtColNumToPixelVal(w, (short) col); /* LHS of col */
    short end;                                         /* RHS of col */

    if (!XtIsRealized(w))
	return; 

    if (col >= XmI18List_num_columns(ilist))
    	end = width;
    else 
    	end = XmI18List_column_widths(ilist)[col] + start;

    (void) MakePositionVisible(w, row, start, end, width);

    ResizeSliders(w);
}



/*
 *
 * Public Convenience Routines
 *
 */



/*  Function Name: Xm18IListUnselectAllItems
 *  Description:   Unselects all rows
 *  Arguments:     w - the ilist widget.
 *  Returns:       none
 */
void
Xm18IListUnselectAllItems( Widget w )
{
  register int row;
  XmI18ListWidget ilist = (XmI18ListWidget) w;
  Xm18RowInfo *ptr = XmI18List_row_data(ilist);

  for (row = 0; row < XmI18List_num_rows(ilist); row++, ptr++) {
    if (ptr->selected)
      ToggleRow(w, row);
  }
}


/*  Function Name: Xm18IListUnselectItem
 *  Description:   Unselects the row passed in
 *  Arguments:     w - the ilist widget.
 *                 row_info - ptr to the row passed in
 *  Returns:       none
 */
void
Xm18IListUnselectItem( Widget w, Xm18RowInfo *row_info )
{
  register int row=0;
  XmI18ListWidget ilist = (XmI18ListWidget) w;
  Xm18RowInfo *ptr = XmI18List_row_data(ilist);
  Boolean done=False;

  while (row < XmI18List_num_rows(ilist) && !done){
    if (ptr == row_info){
      if (ptr->selected)
	ToggleRow( w, row);
      done = True;
    }
    else {
      ptr++;
      row++;
    }
  }
}


/*  Function Name: XmI18ListToggleRow
 *  Description:   Toggles the selection state of a specified row
 *  Arguments:     w - the ilist widget.
 *  Returns:       none
 */
void
XmI18ListToggleRow(Widget w, short row)
{
      ToggleRow(w, row);
}

/*
 * Function:
 *	CopyColumnTitles(ilist)
 * Description:
 *	This function copies the XmStringTable that is the column titles
 *	into local (widget controled) memory.
 * Input:
 *	ilist : XmI18ListWidget - the widget to copy titles
 * Output:
 *	None.
 */
static void
CopyColumnTitles(XmI18ListWidget ilist)
{
    int           i;
    XmStringTable copy;

    if( XmI18List_num_columns(ilist) == 0 ||
        XmI18List_column_titles(ilist) == NULL )
    {
	copy = (XmStringTable) NULL;
    }
    else
    {
	copy = (XmStringTable)
	    XtMalloc(sizeof(XmString) * XmI18List_num_columns(ilist));

	for( i = 0; i < XmI18List_num_columns(ilist); ++i )
	{
	    copy[i] = XmStringCopy(XmI18List_column_titles(ilist)[i]);
	}
    }
    XmI18List_column_titles(ilist) = copy;
}

/*
 * Function:
 *	FreeColumnTitles(ilist)
 * Description:
 *	This function frees the memory associated with the column titles
 *	for the list.
 * Input:
 *	ilist : XmI18ListWidget - the widget to copy titles
 * Output:
 *	None.
 */
static void
FreeColumnTitles(XmI18ListWidget ilist)
{
    int           i;

    if( XmI18List_num_columns(ilist) == 0 || XmI18List_column_titles(ilist) == NULL )
    {
	return;
    }

    for( i = 0; i < XmI18List_num_columns(ilist); ++i )
    {
	XmStringFree(XmI18List_column_titles(ilist)[i]);
    }
    XtFree((XtPointer) XmI18List_column_titles(ilist));
    XmI18List_column_titles(ilist) = (XmStringTable) NULL;
}

/*  Function Name: GetSelectedRows
 *  Description:   Creates an array of integers which are selected row #'s
 *  Arguments:     i18list - the extended list widget
 *		   rows - pointer to the array of selected row #'s
 *		   num_rows - pointer to the number of selected rows
 *  Returns:       rows
 */
static int *
GetSelectedRows(XmI18ListWidget i18list, int *num_rows)
{
    Xm18RowInfo	*row_info = XmI18List_row_data(i18list);
    int		*rows, i;

    rows = NULL;

    for (*num_rows = 0, i = 0; i < XmI18List_num_rows(i18list); i++)
	if (row_info[i].selected)
	    (*num_rows)++;

    if (*num_rows > 0)
    {
	int	j;

	rows = (int *) XtMalloc(*num_rows * sizeof(int));

	for (i = 0, j = 0; i < XmI18List_num_rows(i18list); i++)
	    if (row_info[i].selected)
		rows[j++] = i;
    }

    return rows;
}

/*  Function Name: SelectRow
 *  Description:   Set selection state of row
 *  Arguments:     i18list - the extended list widget
 *		   row - the row to select/unselect
 *		   select - True/False
 *		   notify - if True, call XmNsingleSelectionCallback
 *  Returns:       none
 */
static void
SelectRow(XmI18ListWidget i18list, int row,
	  Boolean select, Boolean notify)
{
    Xm18RowInfo	*rows = XmI18List_row_data(i18list);

    if ((row >= 0) && (rows[row].selected != select))
    {
	ToggleRow((Widget) i18list, row);
    }

    /* Call the appropriate notification callbacks...
     */
    if (notify)
	Notify((Widget) i18list, False);
}

/*  Function Name: SelectItems
 *  Description:   Set selection state by matching column entries to XmString
 *  Arguments:     i18list - the extended list widget
 *		   item - XmString to use as selection key (NULL matches all)
 *		   column - column number (0 - N) to match (or XmANY_COLUMN)
 *		   select - True/False whether or not to select matching rows
 *		   notify - if True, call XmNsingleSelectionCallback
 *  Returns:       none
 */
static void
SelectItems(XmI18ListWidget i18list, XmString item,
	    int column, Boolean select, Boolean notify)
{
    Xm18RowInfo	*rows = XmI18List_row_data(i18list);
    int	i, j;
    int	rowcount, colcount, colstart;

    colstart = (XmI18List_first_col_pixmaps(i18list) ? 1 : 0);

    rowcount = XmI18List_num_rows(i18list);
    colcount = XmI18List_num_columns(i18list);

    for (i = 0; i < rowcount; i++)
	for (j = colstart; j < colcount; j++)
	    /* Check indiviual column entries against XmString, item...
	     * If XmString item matches column etnry (or item is NULL), then
	     * set the selection state of the row
	     */
	    if ((((column == XmANY_COLUMN) || (column == j)) &&
		 XmStringCompare(item, rows[i].values[j])) || !item)
	    {
		if (rows[i].selected != select)
		{
		    ToggleRow((Widget) i18list, i);
		}

		/* Call the appropriate notification callbacks...
		 */
		if (notify)
		    Notify((Widget) i18list, False);

		break;
	    }
}

/*  Function Name: XmI18ListSelectItems
 *  Description:   Set selection state by matching column entries to XmString
 *  Arguments:     i18list - the extended list widget
 *		   item - XmString to use as selection key
 *		   column - column number (0 - N) to match (or XmANY_COLUMN)
 *		   notify - if True, call XmNsingleSelectionCallback
 *  Returns:       none
 */
void
XmI18ListSelectItems(XmI18ListWidget i18list,
		     XmString item, int column, Boolean notify)
{
    SelectItems(i18list, item, column, True, notify);
}

/*  Function Name: XmI18ListDeselectItems
 *  Description:   Set selection state by matching column entries to XmString
 *  Arguments:     i18list - the extended list widget
 *		   item - XmString to use as selection key
 *		   column - column number (0 - N) to match (or XmANY_COLUMN)
 *  Returns:       none
 */
void
XmI18ListDeselectItems(XmI18ListWidget i18list,
		      XmString item, int column)
{
    SelectItems(i18list, item, column, False, False);
}

/*  Function Name: XmI18ListSelectAllItems
 *  Description:   Set selection state by matching column entries to XmString
 *  Arguments:     i18list - the extended list widget
 *		   item - XmString to use as selection key
 *		   column - column number (0 - N) to match (or XmANY_COLUMN)
 *		   notify - if True, call XmNsingleSelectionCallback
 *  Returns:       none
 */
void
XmI18ListSelectAllItems(XmI18ListWidget i18list, Boolean notify)
{
    SelectItems(i18list, NULL, XmANY_COLUMN, True, notify);
}

/*  Function Name: XmI18SelectRow
 *  Description:   Set selection state of row
 *  Arguments:     i18list - the extended list widget
 *		   row - the row to select
 *		   notify - if True, call XmNsingleSelectionCallback
 *  Returns:       none
 */
void
XmI18ListSelectRow(XmI18ListWidget i18list, int row, Boolean notify)
{
    SelectRow(i18list, row, True, notify);
}

/*  Function Name: XmI18DeselectRow
 *  Description:   Set selection state of row
 *  Arguments:     i18list - the extended list widget
 *		   row - the row to deselect
 *  Returns:       none
 */
void
XmI18ListDeselectRow(XmI18ListWidget i18list, int row)
{
    SelectRow(i18list, row, False, False);
}

/*  Function Name: XmI18ListGetSelectedRowArray
 *  Description:   Creates an array of integers which are selected row #'s
 *  Arguments:     i18list - the extended list widget
 *		   rows - pointer to the array of selected row #'s
 *		   num_rows - pointer to the number of selected rows
 *  Returns:       selected rows array
 */
int *
XmI18ListGetSelectedRowArray(XmI18ListWidget i18list,
			     int *num_rows)
{
    return GetSelectedRows(i18list, num_rows);
}

/*  Function Name: XmI18ListMakeRowVisible
 *  Description:   Shifts the visible extended list rows as desired
 *  Arguments:     i18list - the extended list widget
 *		   row - the row number wished to be made visible
 *  Returns:       none
 */
void
XmI18ListMakeRowVisible(XmI18ListWidget i18list, int row)
{
    /* Use column zero as a rule when making a row visible... */
    MakeCellVisible((Widget) i18list, row, 0);
}
