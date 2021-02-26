
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
#include <X11/IntrinsicP.h>

#include <Xm/XmP.h>
#include <Xm/PrimitiveP.h>
#include <Xm/GadgetP.h>
#include <Xm/ExtP.h>

/************************************************************
*	TYPEDEFS AND DEFINES
*************************************************************/

typedef struct _PixmapCache {
    Screen *screen;
    Pixmap pixmap;
    Pixel foreground, background;
    unsigned int depth;
    int ref_count;
    struct _PixmapCache *next;
} CacheEntry;

/************************************************************
*	MACROS
*************************************************************/

/************************************************************
*	GLOBAL DECLARATIONS
*************************************************************/



String xm_std_filter[] = { XmNx, XmNy, XmNwidth, XmNheight,
			   XmNdestroyCallback, XmNsensitive, XmNuserData, 
			   XmNnavigationType, NULL };

String xm_std_constraint_filter[] = { XmNx, XmNy, XmNwidth, XmNheight, 
			   XmNdestroyCallback, XmNsensitive, XmNuserData, 
			   XmNnavigationType, XmNbottomAttachment,
			   XmNbottomOffset, XmNbottomPosition, XmNbottomWidget,
			   XmNbottomAttachment, XmNtopAttachment,
			   XmNleftOffset, XmNleftPosition, XmNleftWidget,
			   XmNtopOffset, XmNtopPosition, XmNtopWidget,
			   XmNrightOffset, XmNrightPosition, XmNrightWidget,
			   XmNrightAttachment, XmNleftAttachment,
			   XmNallowResize, XmNpaneMinimum, XmNshowSash, 
			   XmNpaneMaximum, XmNpreferredPaneSize, 
			   XmNresizeToPreferred, XmNskipAdjust,
			   XmNdFieldPrefHeight, XmNdFieldMaxHeight,
			   XmNdFieldPrefWidth, XmNdFieldMaxWidth,
                           XmNdFieldMinHeight, XmNdFieldMinWidth,
			   /* CR03683 */ XmNpixmapWidth, XmNpixmapHeight,
#ifdef BXDB
			   XmNexclusive, XmNmapType, XmNmap, XmNdataSource,
                           XmNexpression, XmNquery, XmNdataType, XmNsearchable,
                           XmNreceivesData, XmNstorage,
#endif		
			   NULL };

/************************************************************
*	EXTERNAL DECLARATIONS
*************************************************************/

/************************************************************
*	STATIC DECLARATIONS
*************************************************************/

static CacheEntry *pixmapCache = NULL;

/************************************************************
*	GLOBAL CODE
*************************************************************/

/*	Function Name: _XmRequestNewSize
 *	Description:   Asks our parent for a new size.
 *	Arguments:     w - the data request tree widget.
 *                     query_only - only ask what would happen, don't 
 *                                  change anything.
 *                     width, height - size to request.
 *                     r_width, r_height - allowed size.
 *	Returns:       none.
 */

XtGeometryResult
_XmRequestNewSize(Widget w, Boolean query_only, 
		  Dimension width, Dimension height,
		  Dimension * r_width, Dimension * r_height)
{
    XtGeometryResult ret_val;
    XtWidgetGeometry request, result;

    request.width = width;
    request.height = height;
    request.request_mode = CWWidth | CWHeight;

    if (query_only)
	request.request_mode |= XtCWQueryOnly;

    ret_val = XtMakeGeometryRequest(w, &request, &result);

    if (ret_val == XtGeometryAlmost) {
	if (!query_only)
	    ret_val = XtMakeGeometryRequest(w, &result, NULL);

	*r_width = result.width;
	*r_height = result.height;
    }
    else if (ret_val == XtGeometryYes) {
	*r_width = request.width;
	*r_height = request.height;
    }
    else {
	*r_width = w->core.width;
	*r_height = w->core.height;
    }

    return(ret_val);
}

/*	Function Name: _XmHWQuery
 *	Description:   Handles much of the generic height and width query 
 *                     geometry processing.
 *	Arguments:     w - the widget to process.
 *                     intended, preferred - The values from the real query
 *                                           procedure.  It is assumed
 *                                           that preferred is already 
 *                                           filled with the correct desired
 *                                           size.
 *	Returns:       an XtGeometryResult.
 */

XtGeometryResult
_XmHWQuery(Widget w, XtWidgetGeometry * intended, XtWidgetGeometry * preferred)
{
    if (intended == NULL) {
	if ((preferred->width == w->core.width) &&
 	    (preferred->height == w->core.height))
	{
	    return(XtGeometryNo);
	}
    }
    else {
	if ((intended->request_mode & CWWidth) &&
	    (intended->request_mode & CWHeight))
	{
	    if ((intended->width == preferred->width) &&
		(intended->height == preferred->height))
	    {
		return(XtGeometryYes);
	    }
	    else {
		return(XtGeometryNo);
	    }
	}
    }

    preferred->request_mode = CWWidth | CWHeight;
    return(XtGeometryAlmost);
}

/*	Function Name: _XmGadgetWarning
 *	Description: Checks to see if this is a gadget.  If it is then
 *                   print out a warning, and return True.
 *	Arguments: w - the widget to check.
 *	Returns: True if this object is a gadget.
 */

Boolean
_XmGadgetWarning(Widget w)
{
    String params[1];
    Cardinal num;

    if (!XtIsRectObj(w) || XtIsWidget(w))
	return(False);

    params[0] = XtName(XtParent(w));
    num = 1;
    
    XtAppWarningMsg(XtWidgetToApplicationContext(w),
		    XmNnoGadgetSupport, XmNnoGadgetSupport, 
		    XmCICSWidgetSetError,
		    XmNnoGadgetSupportMsg, params, &num);
    
    return(True); 
}

/*	Function Name: _XmGetFocus
 *	Description:   Gets the XmFocus.
 *	Arguments:     w - the icon button widget.
 *                     event - the event that caused this action.
 *                     params, num_params - action routine parameters.
 *	Returns:       none.
 */

/* ARGSUSED */
void
_XmGetFocus(Widget w, XEvent * event, String * params, Cardinal * num_params)
{
#ifdef VMS
    if (XtIsRealized(w))
#endif
	(void) XmProcessTraversal(w, XmTRAVERSE_CURRENT);
}

/*	Function Name: _XmFilterArgs
 *	Description: Filters certain resources out of an argument list.
 *	Arguments: args, num_args - the input argument list.
 *                 filter - the list of resources (by name) to remove.
 * RETURNED        filtered_args, num_filtered_args - new filtered list.
 *	Returns: none.
 *
 * NOTE The caller of this function is responsible for freeing "filtered_args"
 *      with XtFree() when it is no longer in use.
 */

void
_XmFilterArgs(ArgList args, Cardinal num_args, String *filter,
	      ArgList *filtered_args, Cardinal *num_filtered_args)
{
    ArgList fargs = (ArgList) XtMalloc(sizeof(Arg) * num_args);
    register int i;
    String *ptr;

    *filtered_args = fargs;
    *num_filtered_args = 0;
    for (i = 0; i < num_args; i++) {
	Boolean match = False;
	for (ptr = filter; *ptr != NULL; ptr++) {
	    if (streq(*ptr, args[i].name)) {
		match = True;
		break;
	    }
	}
	if (!match) {
	    *fargs++ = args[i];
	    (*num_filtered_args)++;
	}
    }
}

/*	Function Name: _XmSetValuesOnChildren
 *	Description: Calls setvalues on all children of this widget, 
 *                   and then recurses.
 *	Arguments: w - the widget to set.
 *                 args, num_args - arguments to set.
 *	Returns: none.
 */

void
_XmSetValuesOnChildren(Widget w, ArgList args, Cardinal num_args)
{
    Widget *childP;

    if (!XtIsSubclass(w, compositeWidgetClass))
	return;

    ForAllChildren((CompositeWidget) w, childP) {
	XtSetValues(*childP, args, num_args);
	_XmSetValuesOnChildren(*childP, args, num_args);
    }
}

/*      Function Name: _XmUtilIsSubclassByNameQ
 *      Description:   Determines whether this is a subclass of the named
 *                     class.
 *      Arguments:     w - the widget to check.
 *                     nameq - a quarkified name for the class to check.
 *      Returns:       True if this is a subclass.
 */

Boolean
_XmUtilIsSubclassByNameQ(Widget w, XrmQuark nameq)
{
    WidgetClass class;

    for (class = XtClass(w) ;
         class != NULL ; class = class->core_class.superclass)
    {
        if (nameq == XrmStringToQuark(class->core_class.class_name))
            return(True);
    }

    return(False);
}

/*	Function Name: _XmGetMBStringFromXmString
 *	Description: Given an Xm String, returns an MB string
 *	Arguments: xmstr - an Xm String.
 *	Returns: A multi byte string.
 */

String
_XmGetMBStringFromXmString(XmString xmstr)
{
    String 			text;
    XmStringContext 		context;   /* context for conversion	*/
    char			*newText;  /* new text string        	*/
    XmStringCharSet		charset;   /* dummy			*/
    XmStringDirection   	direction; /* dummy			*/
    XmStringComponentType	u_tag;	   /* is newline		*/
    int				length;    /* length of string		*/
    unsigned short		u_length;  /* bogus length		*/
    unsigned char		*u_value;  /* bogus value		*/
    XmStringComponentType 	type;	   /* type			*/
    Boolean			done, separator; /* done with it	*/

    if ( !XmStringInitContext(&context, xmstr) )
    {
      XmStringFree(xmstr);
      return(NULL);
    }

    /*
     * First path to get length.
     */
    length = 0; 
    if ( XmStringPeekNextComponent(context) == XmSTRING_COMPONENT_UNKNOWN ) {
      XmStringFree(xmstr);
      XmStringFreeContext(context);
      return(NULL);
    }

    done = False;
    while( !done ) 
    {
	newText = NULL;		/* By source code inspection I have */
	charset = NULL;		/* Determined that this will make sure */
	u_value = NULL;		/* that no memory is leaked (I hope). */

	type = XmStringGetNextComponent( context, &newText, &charset, 
		&direction, &u_tag, &u_length, &u_value );

        switch( type )
	{
    	case XmSTRING_COMPONENT_TEXT:
	case XmSTRING_COMPONENT_LOCALE_TEXT:
	    length += strlen( newText );
	    break;
 	case XmSTRING_COMPONENT_SEPARATOR:
	    length += 1;
	    break;
	case XmSTRING_COMPONENT_USER_BEGIN:
	case XmSTRING_COMPONENT_USER_END:
	case XmSTRING_COMPONENT_CHARSET:
	case XmSTRING_COMPONENT_DIRECTION:
	    break;
	case XmSTRING_COMPONENT_END:
	default:
	    done = True;
	}

	XtFree((XtPointer) newText);
	XtFree((XtPointer) charset);
	XtFree((XtPointer) u_value);
   }

    /*
     * If XmStringGetNextComponent() fails on the current xmstring,
     * try by using XmStringGetNextSegment(). AIX 4.3.2 currently
     * fails to obtain the compound string from
     * XmStringGetNextComponent. (Change Reguest: CR03841)
     */

    if(length == 0) {
	while ( XmStringGetNextSegment(context, &newText, &charset,
				       &direction, &separator) ) {

	length = strlen(newText);
	if (separator == True) {
	  length += 1;     ;
	}

	text = XtMalloc( length + 1 );
	text[0] = '\0';
	strcat(text, newText);

	if (separator == True) {
	  strcat(text, "\n");
	}

	XtFree(newText);
	XmStringFreeContext(context);

	return (text);
      }
    }

    /*
     * Failed to obtain any compound string, return with NULL pointer.
     */
    if(length == 0) return(NULL);
    
    XmStringFreeContext( context );
    text = XtMalloc( length + 1 );
    text[0] = '\0';

    /*
     * Fill in the string.
     */ 
    XmStringInitContext(&context, xmstr);

    done = False;
    while( !done ) 
    {
	newText = NULL;		/* By source code inspection I have */
	charset = NULL;		/* Determined that this will make sure */
	u_value = NULL;		/* that no memory is leaked (I hope). */

	type = XmStringGetNextComponent( context, &newText, &charset, 
		&direction, &u_tag, &u_length, &u_value );
        switch( type )
	{
    	case XmSTRING_COMPONENT_TEXT:
	case XmSTRING_COMPONENT_LOCALE_TEXT:
	    strcat(text, newText); 
	    break;
 	case XmSTRING_COMPONENT_SEPARATOR:
	    strcat(text, "\n");
	    break;
	case XmSTRING_COMPONENT_USER_BEGIN:
	case XmSTRING_COMPONENT_USER_END:
	case XmSTRING_COMPONENT_CHARSET:
	case XmSTRING_COMPONENT_DIRECTION:
	    break;
	case XmSTRING_COMPONENT_END:
	default:
	    done = True;
	}

	XtFree((XtPointer) newText);
	XtFree((XtPointer) charset);
	XtFree((XtPointer) u_value);
   }
 
    XmStringFreeContext(context);
    return(text);
}

/*	Function Name: _XiWoveWidget
 *	Description: Wrapper for XtMoveWidget to deal with Motif1.2
 *                   drag N drop.
 *	Arguments: w - The widget to change
 *                 x, y - The new location for this widget.
 *	Returns: none.
 */

void 
_XmMoveWidget(Widget w, Position x, Position y)
{
#if (XmVersion > 1001)
    XmDropSiteStartUpdate(w);
    XtMoveWidget(w, x, y);
    XmDropSiteEndUpdate(w);
#else
    XtMoveWidget(w, x, y);
#endif
}

/*	Function Name: _XmResizeWidget
 *	Description: Wrapper for XtResizeWidget to deal with Motif1.2
 *                   drag N drop.
 *	Arguments: w - The widget to change
 *                 width, height, bw - The new size for the widget.
 *	Returns: none.
 */

void 
_XmResizeWidget(Widget w, Dimension width, Dimension height, Dimension bw)
{
    XmDropSiteStartUpdate(w);
    XtResizeWidget(w, width, height, bw);
    XmDropSiteEndUpdate(w);
}

/*	Function Name: _XmConfigureWidget
 *	Description: Wrapper for XtConfigureWidget to deal with Motif1.2
 *                   drag N drop.
 *	Arguments: w - The widget to change
 *                 x, y - The new location for this widget.
 *                 width, height, bw - The new size for the widget.
 *	Returns: none.
 */

void 
_XmConfigureWidget(Widget w, Position x, Position y,
		   Dimension width, Dimension height, Dimension bw)
{
    /* 0x0 will sometimes result in a BadValue Error for X_ConfigureWindow */
    if (height < 1) height = 1;
    if (width < 1) width = 1;

    XmDropSiteStartUpdate(w);
    XtConfigureWidget(w, x, y, width, height, bw);
    XmDropSiteEndUpdate(w);

}

#ifdef notdef

/************************************************************
 *
 *  Some nice routines for using the context manager, 
 * 
 *  This code is currently unused.
 *
 ************************************************************/

/*	Function Name: _XmSetContextData
 *	Description: Sets context data on a widget
 *	Arguments: w - the widget to set the context data on.
 *                 context - the context to set it onto.
 *                 data - the data to set.
 *	Returns: none.
 */

void
_XmSetContextData(Widget w, XContext context, XtPointer data)
{
    int ret;
    
    ret = XSaveContext(XtDisplay(w), (Window) w, context, (XtPointer) data);

    if (ret != XCSUCCESS) {
	XtAppErrorMsg(XtWidgetToApplicationContext(w),
		      XmNcontextSaveFailed, XmNcontextSaveFailed, 
		      XmCICSWidgetSetError,
		      XmNcontextSaveFailedMsg, NULL, NULL);
    }
}

/*	Function Name: _XmGetContextData
 *	Description: Gets context data on a widget
 *	Arguments: w - the widget to get the context data from.
 *                 context - the context to find it in.
 *                 data - the data retreived.
 *	Returns: Boolean - True if the request succeeds.
 */

Boolean
_XmGetContextData(Widget w, XContext context, XtPointer *data)
{
    int ret;

    ret = XFindContext(XtDisplay(w), (Window) w, context, (XtPointer *) data);

    return(ret == XCSUCCESS);
}

/*	Function Name: _XmDeleteContextData
 *	Description: Deletes context data from a widget
 *	Arguments: w - the widget the data is set on.
 *                 context - the context to remove.
 *	Returns: none.
 */

void
_XmDeleteContextData(Widget w, XContext context)
{
    (void) XDeleteContext(XtDisplay(w), (Window) w, context);
}

#endif				/* Context manager stuff */

/************************************************************
 *
 *  This code is taken from the MIT X Consortium's Xmu 
 *  Utility Library.
 *
 ************************************************************/

/* 
 * Copyright 1988 by the Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided 
 * that the above copyright notice appear in all copies and that both that 
 * copyright notice and this permission notice appear in supporting 
 * documentation, and that the name of M.I.T. not be used in advertising
 * or publicity pertaining to distribution of the software without specific, 
 * written prior permission. M.I.T. makes no representations about the 
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 */

#define  XK_LATIN1
#include <X11/keysymdef.h>

/*
 * ISO Latin-1 case conversion routine
 */

/*
 * Function:
 *	XmCompareISOLatin1(first, second)
 * Description:
 *	Compares two ISO Latin 1 strings to determine if they are equivalent.
 *	Case is not considered for the comparison.
 * Input:
 *	first  : char * - the first ISO Latin 1 String
 *	second : char * - the second ISO Latin 1 String
 * Output:
 *	int - (-1) -> first < second
 *            ( 0) -> first == second
 *            ( 1) -> first > second
 */
int
#ifndef _NO_PROTO
XmCompareISOLatin1(char *first, char *second)
#else
XmCompareISOLatin1(first, second)
    char *first, *second;
#endif
{
    register unsigned char *ap, *bp;

    for (ap = (unsigned char *) first, bp = (unsigned char *) second;
         *ap && *bp; ap++, bp++) {
        register unsigned char a, b;

        if ((a = *ap) != (b = *bp)) {
            /* try lowercasing and try again */

            if ((a >= XK_A) && (a <= XK_Z))
		a += (XK_a - XK_A);
            else if ((a >= XK_Agrave) && (a <= XK_Odiaeresis))
              a += (XK_agrave - XK_Agrave);
            else if ((a >= XK_Ooblique) && (a <= XK_Thorn))
              a += (XK_oslash - XK_Ooblique);

            if ((b >= XK_A) && (b <= XK_Z))
              b += (XK_a - XK_A);
            else if ((b >= XK_Agrave) && (b <= XK_Odiaeresis))
              b += (XK_agrave - XK_Agrave);
            else if ((b >= XK_Ooblique) && (b <= XK_Thorn))
              b += (XK_oslash - XK_Ooblique);

            if (a != b) break;
        }
    }
    return (((int) *bp) - ((int) *ap));
}

void
XmCopyISOLatin1Lowered(dst, src)
    char *dst, *src;
{
    register unsigned char *dest, *source;

    for (dest = (unsigned char *)dst, source = (unsigned char *)src;
	 *source;
	 source++, dest++)
    {
	if ((*source >= XK_A) && (*source <= XK_Z))
	    *dest = *source + (XK_a - XK_A);
	else if ((*source >= XK_Agrave) && (*source <= XK_Odiaeresis))
	    *dest = *source + (XK_agrave - XK_Agrave);
	else if ((*source >= XK_Ooblique) && (*source <= XK_Thorn))
	    *dest = *source + (XK_oslash - XK_Ooblique);
	else
	    *dest = *source;
    }
    *dest = '\0';
}

/*
 *	Creates a stippled pixmap of specified depth
 *	caches these so that multiple requests share the pixmap
 */

#define pixmap_width 2
#define pixmap_height 2

Pixmap 
XiCreateStippledPixmap(Screen *screen, 
		       Pixel fore, Pixel back, unsigned int depth)
{
    register Display *display = DisplayOfScreen(screen);
    CacheEntry *cachePtr;
    Pixmap stippled_pixmap;
    static unsigned char pixmap_bits[] = {
	0x02, 0x01,
    };

    /* see if we already have a pixmap suitable for this screen */
    for (cachePtr = pixmapCache; cachePtr; cachePtr = cachePtr->next) {
	if (cachePtr->screen == screen && cachePtr->foreground == fore &&
	    cachePtr->background == back && cachePtr->depth == depth)
	    return( cachePtr->ref_count++, cachePtr->pixmap );
    }

    stippled_pixmap = XCreatePixmapFromBitmapData (display,
			RootWindowOfScreen(screen), (char *)pixmap_bits, 
			pixmap_width, pixmap_height, fore, back, depth);

    /* and insert it at the head of the cache */
    cachePtr = XtNew(CacheEntry);
    cachePtr->screen = screen;
    cachePtr->foreground = fore;
    cachePtr->background = back;
    cachePtr->depth = depth;
    cachePtr->pixmap = stippled_pixmap;
    cachePtr->ref_count = 1;
    cachePtr->next = pixmapCache;
    pixmapCache = cachePtr;

    return( stippled_pixmap );
}

void 
XiReleaseStippledPixmap(Screen *screen, Pixmap pixmap)
{
    register Display *display = DisplayOfScreen(screen);
    CacheEntry *cachePtr, **prevP;
    for (prevP = &pixmapCache, cachePtr = pixmapCache; cachePtr;) {
	if (cachePtr->screen == screen && cachePtr->pixmap == pixmap) {
	    if (--cachePtr->ref_count == 0) {
		XFreePixmap( display, pixmap );
		*prevP = cachePtr->next;
		XtFree( (char*)cachePtr );
		break;
	    }
	}
	prevP = &cachePtr->next;
	cachePtr = *prevP;
    }
}

/*
 * Function:
 *	XmCompareXtWidgetGeometryToWidget(geom, widget)
 * Description:
 *	This function compares an XtWidgetGeometry structure to the
 *	actual values contained in a widget.
 * Input:
 *	geom   : XtWidgetGeometry* - the geometry to test against the widget
 *	widget : Widget            - the widget to use in the comparison
 * Output:
 *	Boolean - True if the geometry fits the specified widget, else False
 */
Boolean
XmCompareXtWidgetGeometryToWidget(XtWidgetGeometry *geom, Widget widget)
{
    if( (geom->request_mode & CWX && geom->x != widget->core.x) ||
        (geom->request_mode & CWY && geom->y != widget->core.y) ||
        (geom->request_mode & CWWidth && geom->width != XtHeight(widget)) ||
        (geom->request_mode & CWHeight && geom->height != XtHeight(widget)) ||
        (geom->request_mode & CWBorderWidth && geom->border_width !=
	 widget->core.border_width) ) return( False );

    return( True );
}

/*
 * Function:
 *	XmCompareXtWidgetGeometry(geom1, geom2)
 * Description:
 *	Compares to XtWidgetGeometry structures to check for equality.
 * Input:
 *	geom1 : XtWidgetGeometry* - geometry to compare
 *	geom2 : XtWidgetGeometry* - geometry to compare
 * Output:
 *	Boolean - True if both the request_mode and values match, else False
 */
Boolean
XmCompareXtWidgetGeometry(XtWidgetGeometry *geom1, XtWidgetGeometry *geom2)
{
    if( geom1->request_mode != geom2->request_mode ) return( False );

    if( (geom1->request_mode & CWX && (geom1->x != geom2->x)) ||
        (geom1->request_mode & CWY && (geom1->y != geom2->y)) ||
        (geom1->request_mode & CWWidth && (geom1->width != geom2->width)) ||
        (geom1->request_mode & CWHeight && (geom1->height != geom2->height)) ||
        (geom1->request_mode & CWBorderWidth &&
	 (geom1->border_width != geom2->border_width)) ||
        (geom1->request_mode & CWSibling &&
	 (geom1->sibling != geom2->sibling)) ||
        (geom1->request_mode & CWStackMode &&
	 (geom1->stack_mode != geom2->stack_mode)) ) return( False );

    return( True );
}

/************************************************************
 *
 *  Static functions
 *
 ************************************************************/

void
_XmInitialIzeConverters(Widget w)
{
    fprintf(stderr,
    "What does this next line do?  - rhartley\nfilename: %s, line: %d",  __FILE__, __LINE__);
/*    _XiPostInitialIzeConverters(w, "ICS Enhancement Pak 4.0"); */
}

#include <Xm/XmP.h>

/*************************************************************************/
/* The following code is snipped directly from OSF Motif 1.2.4           */
/* DEC did not compile this correctly (ALIGN_SUBCLASS_PARTS was not def- */
/* ined) on all versions of Motif for Digital Unix.  We include it here  */
/* to get correct behavior.                                              */
/*************************************************************************/
/* and now there's a fix added; refer to OSF contact number 24617 for
** details 
*/
/* And rewritten to support manual alignment.  HP/UX aligns doubles to
** 8 bytes, but everthing else to 4.  There is NO WAY to discover at
** runtime whether or not a structure contains doubles.  It cannot be
** done, period; thus, the OSF mechanism won't work for PA-RISC
** processors.  We get around that by specifying an extra flag (see
** XiResolvePartOffsets64) saying "align my subpart (only) to 8
** bytes".  This is needed in EPak only for the XiPanner widget.
** Note, this mechanism does NOT work for subclasses of 8-byte-aligned
** subparts.  We'd need to provide a "copy my parents offset array"
** flag for that.  Since EPak doesn't need it, we don't.  Beware...
*/

#define ALIGN_SUBCLASS_PARTS

#ifdef ALIGN_SUBCLASS_PARTS
#define _ALIGN(size) (((size) + (sizeof(double)-1)) & ~(sizeof(double)-1))
#else
#define _ALIGN(size) (size)
#endif

/*
 *  FIX for 5178: remove dependency on Xt private data 
 */
static Boolean
IsSubclassOf(
	WidgetClass wc,
	WidgetClass sc)
{
	WidgetClass p = wc;

	for(; (p) && (p != sc); p = p->core_class.superclass);
	return (p == sc);
}


#define XtIsConstraintClass(wc) IsSubclassOf(wc, constraintWidgetClass)
/*
 *  end FIX for 5178.
 */

void 
_XiResolveAllPartOffsets(
        WidgetClass w_class,
        XmOffsetPtr *offset,
        XmOffsetPtr *constraint_offset,
	Boolean     align64)
{
    WidgetClass c, super = w_class->core_class.superclass;
    ConstraintWidgetClass cc = NULL, scc = NULL;
    int i, classcount = 0;
    XmPartResource *pr;
    
    Boolean do_align = False;
    
    if (sizeof(int) != sizeof(void*))
	do_align = True;
    
    /*
     *  Set up constraint class pointers
     */
    if (XtIsConstraintClass(super))
    {
	cc = (ConstraintWidgetClass)w_class;
	scc = (ConstraintWidgetClass)super;
    }
    
    /*
     *  Update the part size value (initially, it is the size of this part)
     */
    
    if (do_align)
    {
	w_class->core_class.widget_size =
	    w_class->core_class.widget_size
	    + _ALIGN(super->core_class.widget_size);
	w_class->core_class.widget_size =
	    _ALIGN(w_class->core_class.widget_size);
    }
    else
    {
	w_class->core_class.widget_size =
	    w_class->core_class.widget_size + super->core_class.widget_size;
    }

    /*
     * Another nasty hack.  Just plain old DON'T allow the size to be
     * a multiple of anything smaller than 4.  This causes bus errors on
     * most platforms when the constraint record is appended (by Xt)
     * to the widget struct.  Just round up.
     * The do_align flag above does the same thing, but only on 8 byte
     * boundaries on 64 bit systems.  All of this code desperately
     * needs to be re-written.
     */
    if(w_class->core_class.widget_size & 3) {
	int size = w_class->core_class.widget_size;
	w_class->core_class.widget_size = 4 * ((size / 4) + 1);
    }

    if (cc && scc)
    {
	if (do_align)
	{
	    cc->constraint_class.constraint_size =
		cc->constraint_class.constraint_size
		+ _ALIGN(scc->constraint_class.constraint_size);
	    cc->constraint_class.constraint_size =
		_ALIGN(cc->constraint_class.constraint_size);
	}
	else
	    cc->constraint_class.constraint_size =
		cc->constraint_class.constraint_size +
		scc->constraint_class.constraint_size;
    }

    /*
     *  Count the number of superclasses and allocate the offset record(s)
     */
    for (c = w_class; c != NULL; c = c->core_class.superclass) classcount++;
    
    *offset = (XmOffsetPtr) XtMalloc(classcount * sizeof(XmOffset));
    if (cc)
	*constraint_offset = (XmOffsetPtr) XtMalloc(classcount 
						    * sizeof(XmOffset));
    else 
	if(constraint_offset != NULL) *constraint_offset = NULL;
    
    /*
     *  Fill in the offset table(s) with the offset of all parts
     */
    for (i = classcount-1, c = super; i > 0; c = c->core_class.superclass, i--)
    {
	/*
	 * The do_align flag is true iff _all_ subparts must be 8-byte
	 * aligned (e.g. on an Alpha).
	 *
	 * align64 is true only if the _current_ widget part must be
	 * 8-byte aligned (e.g. subparts containing doubles on HP/UX)
	 */
	if (do_align ||
	    (c == super && align64))
	    (*offset)[i] = (long)_ALIGN((c->core_class.widget_size));	
	else
	    (*offset)[i] = (long)(c->core_class.widget_size);
    }
    
    (*offset)[0] = 0;
    
    if (constraint_offset != NULL && *constraint_offset != NULL) {
	for (i = classcount-1, scc = (ConstraintWidgetClass) super; i > 0; 
	     scc = (ConstraintWidgetClass)(scc->core_class.superclass), i--)
	    if (XtIsConstraintClass((WidgetClass)scc))
	    {
		if (do_align)
		    (*constraint_offset)[i] = 
			(long)_ALIGN((scc->constraint_class.constraint_size));
		else
		    (*constraint_offset)[i] = 
			(long)(scc->constraint_class.constraint_size);
	    }
	    else
		(*constraint_offset)[i] = 0;
	
	(*constraint_offset)[0] = 0;
    }
    
    /*
     *  Update the resource list(s) offsets in place
     */
    for (i = 0; i < w_class->core_class.num_resources; i++) 
    {
	pr = (XmPartResource *) &w_class->core_class.resources[i];
	
	/* The next line updates this in place--be careful */
	
	w_class->core_class.resources[i].resource_offset =
	    XmGetPartOffset(pr, offset);
    }
    
    if (cc)
	for (i = 0; i < cc->constraint_class.num_resources; i++) 
	{
	    pr = (XmPartResource *) &cc->constraint_class.resources[i];
	    
	    /* The next line updates this in place--be careful */
	    
	    cc->constraint_class.resources[i].resource_offset =
		XmGetPartOffset(pr, constraint_offset);
	}
}

void 
XiResolveAllPartOffsets(
        WidgetClass w_class,
        XmOffsetPtr *offset,
        XmOffsetPtr *constraint_offset )
{
    _XiResolveAllPartOffsets( w_class, offset, constraint_offset, False );
}

void 
XmResolveAllPartOffsets64(
        WidgetClass w_class,
        XmOffsetPtr *offset,
        XmOffsetPtr *constraint_offset )
{
#ifdef XM_ALIGN_64
    _XiResolveAllPartOffsets( w_class, offset, constraint_offset, True );
#else
    _XiResolveAllPartOffsets( w_class, offset, constraint_offset, False );
#endif
}


/* -------------------------------------------------------------------------- */
 



/************************************************************************
 *
 *  The border highlighting and unhighlighting routines.
 *
 *  These routines were originally in Primitive.c but not used anywhere.
 *
 ************************************************************************/

void 
_XmExtHighlightBorder(
        Widget w )
{
    if(    XmIsPrimitive( w)    ) {   
        (*(xmPrimitiveClassRec.primitive_class.border_highlight))( w) ;
    }  else  {   
	if(    XmIsGadget( w)    ) {   
	    (*(xmGadgetClassRec.gadget_class.border_highlight))( w) ;
	} 
    } 
    return ;
} 

void 
_XmExtUnhighlightBorder(
        Widget w )
{
    if(    XmIsPrimitive( w)    )
    {   
        (*(xmPrimitiveClassRec.primitive_class.border_unhighlight))( w) ;
        } 
    else
    {   if(    XmIsGadget( w)    )
        {   
            (*(xmGadgetClassRec.gadget_class.border_unhighlight))( w) ;
            } 
        } 
    return ;
    }
