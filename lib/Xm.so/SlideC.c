
#include <localdef.h>

/**
 *
 * $Id: SlideC.c,v 1.3 2002/01/29 16:03:31 jimk Exp $
 *
 **/



#include "XmI.h"
#include "SlideCP.h"
#include <Xm/XmP.h>

/*
   Widget methods, forward declarations
 */

static void class_initialize(void);
static void class_part_initialize(WidgetClass widget_class);
static void initialize(Widget request, Widget new_w, ArgList args, Cardinal *num_args);
static void destroy(Widget w);
static Boolean set_values(Widget old, Widget request, Widget new_w, ArgList args, Cardinal *num_args);
static void get_values_hook(Widget w, ArgList args, Cardinal *num_args);

static void _XmSlideProc(Widget w);
static void targetDestroy(Widget target, XtPointer client_data, XtPointer call_data);

/*
   Widget default resources
 */

#define Offset(field) XtOffsetOf(XmSlideContextRec, slide.field)
static XtResource resources[] =
{
    {
	XmNslideFinishCallback, XtCCallback, XtRCallback,
	sizeof(XtCallbackList), Offset(slideFinishCallback),
	XtRCallback, NULL
    },
    {
	XmNslideMotionCallback, XtCCallback, XtRCallback,
	sizeof(XtCallbackList), Offset(slideMotionCallback),
	XtRCallback, NULL
    },
    {
	XmNslideWidget, XmCSlideWidget, XtRWidget,
	sizeof(Widget), Offset(slide_widget),
	XtRImmediate, NULL
    },
    {
	XmNslideInterval, XmCSlideInterval, XtRInt,
	sizeof(int), Offset(interval),
	XtRImmediate, (XtPointer)5
    },
    {
	XmNslideDestWidth, XmCSlideDestWidth, XtRDimension,
	sizeof(Dimension), Offset(dest_width),
	XtRImmediate, (XtPointer)XmUNSPECIFIED
    },
    {
	XmNslideDestHeight, XmCSlideDestHeight, XtRDimension,
	sizeof(Dimension), Offset(dest_height),
	XtRImmediate, (XtPointer)XmUNSPECIFIED
    },
    {
	XmNslideDestX, XmCSlideDestX, XtRPosition,
	sizeof(Position), Offset(dest_x),
	XtRImmediate, (XtPointer)XmUNSPECIFIED_POSITION
    },
    {
	XmNslideDestY, XmCSlideDestY, XtRPosition,
	sizeof(Position), Offset(dest_y),
	XtRImmediate, (XtPointer)XmUNSPECIFIED_POSITION
    },
};
#undef Offset

/*
   Widget class record
 */
/* *INDENT-OFF* */
XmSlideContextClassRec xmSlideContextClassRec = {
	/* Object Class Part */
	{
/* pointer to superclass ClassRec   WidgetClass       */ (WidgetClass) &objectClassRec,
/* widget resource class name       String            */ "XmSlideContext",
/* size in bytes of widget record   Cardinal          */ sizeof(XmSlideContextRec),
/* class initialization proc        XtProc            */ class_initialize,
/* dynamic initialization           XtWidgetClassProc */ class_part_initialize,
/* has class been initialized?      XtEnum            */ False,
/* initialize subclass fields       XtInitProc        */ initialize,
/* notify that initialize called    XtArgsProc        */ NULL,
/* NULL                             XtProc            */ NULL,
/* NULL                             XtPointer         */ NULL,
/* NULL                             Cardinal          */ (Cardinal)NULL,
/* resources for subclass fields    XtResourceList    */ resources,
/* number of entries in resources   Cardinal          */ XtNumber(resources),
/* resource class quarkified        XrmClass          */ NULLQUARK,
/* NULL                             Boolean           */ (Boolean)NULL,
/* NULL                             XtEnum            */ (XtEnum)NULL,
/* NULL				    Boolean           */ (Boolean)NULL,
/* NULL                             Boolean           */ (Boolean)NULL,
/* free data for subclass pointers  XtWidgetProc      */ destroy,
/* NULL                             XtProc            */ NULL,
/* NULL			            XtProc            */ NULL,
/* set subclass resource values     XtSetValuesFunc   */ set_values,
/* notify that set_values called    XtArgsFunc        */ NULL,
/* NULL                             XtProc            */ NULL,
/* notify that get_values called    XtArgsProc        */ get_values_hook,
/* NULL                             XtProc            */ NULL,
/* version of intrinsics used       XtVersionType     */ XtVersion,
/* list of callback offsets         XtPointer         */ NULL,
/* NULL                             String            */ NULL,
/* NULL                             XtProc            */ NULL,
/* NULL                             XtProc            */ NULL,
/* pointer to extension record      XtPointer         */ NULL
	},
	/* SlideContext Class Part */
	{
		NULL
	}
};
/* *INDENT-ON* */

WidgetClass xmSlideContextWidgetClass = (WidgetClass)&xmSlideContextClassRec;

static void 
class_initialize(void)
{
}

static void 
class_part_initialize(WidgetClass widget_class)
{
}

static void 
initialize(Widget request, Widget new_w, ArgList args, Cardinal *num_args)
{
    /*
    printf("%s:%s(%d) - %s %li\n", __FILE__, __FUNCTION__, __LINE__,
    	XtName(new_w),
    	Slide_Interval(new_w));
    	*/

    if (Slide_Widget(new_w) == NULL)
    {
	_XmWarningMsg(new_w, 
	    "Invalid parameter",
	    XmNslideWidget " must be specified during creation",
	    NULL, 0);
    }
    else
    {
	if (Slide_DestWidth(new_w) == (Dimension)XmUNSPECIFIED)
	{
	    Slide_DestWidth(new_w) = XtWidth(Slide_Widget(new_w));
	}
	if (Slide_DestHeight(new_w) == (Dimension)XmUNSPECIFIED)
	{
	    Slide_DestHeight(new_w) = XtHeight(Slide_Widget(new_w));
	}
	if (Slide_DestX(new_w) == XmUNSPECIFIED_POSITION)
	{
	    Slide_DestX(new_w) = XtX(Slide_Widget(new_w));
	}
	if (Slide_DestY(new_w) == XmUNSPECIFIED_POSITION)
	{
	    Slide_DestY(new_w) = XtY(Slide_Widget(new_w));
	}
	Slide_Id(new_w) = XtAppAddTimeOut(XtWidgetToApplicationContext(new_w),
		Slide_Interval(new_w),
		(XtTimerCallbackProc)_XmSlideProc,
		new_w);
	XtAddCallback(Slide_Widget(new_w), XmNdestroyCallback, (XtCallbackProc)targetDestroy, new_w);
    }
}

static void 
destroy(Widget w)
{
    if (Slide_Id(w) != (XtIntervalId)NULL)
    {
    	XtRemoveTimeOut(Slide_Id(w));
	Slide_Id(w) = (XtIntervalId)NULL;
    }
    XtRemoveCallback(Slide_Widget(w), XmNdestroyCallback, (XtCallbackProc)targetDestroy, w);
}

static Boolean 
set_values(Widget old, Widget request, Widget new_w, ArgList args, Cardinal *num_args)
{
    if (Slide_Widget(old) != Slide_Widget(new_w))
    {
	XtRemoveCallback(Slide_Widget(old), XmNdestroyCallback, (XtCallbackProc)targetDestroy, old);
	XtAddCallback(Slide_Widget(new_w), XmNdestroyCallback, (XtCallbackProc)targetDestroy, new_w);
    }
    return(False);
}

static void 
get_values_hook(Widget w, ArgList args, Cardinal *num_args)
{
}

static void
targetDestroy(Widget target, XtPointer client_data, XtPointer call_data)
{
Widget w = (Widget)client_data;

    XtDestroyWidget(w);
}

static void
_XmSlideProc(Widget w)
{
Dimension width, height;
Position x, y;

    /*
    printf("%s:%s(%d) - %s %li\n", __FILE__, __FUNCTION__, __LINE__,
    	XtName(w),
    	Slide_Interval(w));
    	*/

    if (Slide_Interval(w) == 0)
    {
	width = Slide_DestWidth(w);
	height = Slide_DestHeight(w);
	x = Slide_DestX(w);
	y = Slide_DestY(w);
    }
    else
    {
	width = XtWidth(Slide_Widget(w));
	height = XtHeight(Slide_Widget(w));
	x = XtX(Slide_Widget(w));
	y = XtY(Slide_Widget(w));
	{
	    height = height - (((height - Slide_DestHeight(w)) * 10) / 100);
	    if (height < Slide_DestHeight(w))
	    {
		height++;
	    }
	    if (height > Slide_DestHeight(w))
	    {
		height--;
	    }
	    width = width - (((width - Slide_DestWidth(w)) * 10) / 100);
	    if (width < Slide_DestWidth(w))
	    {
		width++;
	    }
	    if (width > Slide_DestWidth(w))
	    {
		width--;
	    }
	}
	{
	    y = y - ((((y - Slide_DestY(w)) * 10) / 100) + 0);
	    if (y < Slide_DestY(w))
	    {
		y++;
	    }
	    if (y > Slide_DestY(w))
	    {
		y--;
	    }
	    x = x - ((((x - Slide_DestX(w)) * 10) / 100) + 0);
	    if (x < Slide_DestX(w))
	    {
		x++;
	    }
	    if (x > Slide_DestX(w))
	    {
		x--;
	    }
	}
    }
    /*
    XtCallCallbackList(w, Slide_MotionCallback(w), NULL);
    */
    XtVaSetValues(Slide_Widget(w),
    	XmNx, x,
    	XmNy, y,
    	XmNwidth, width,
    	XmNheight, height,
    	NULL);
    if (Slide_DestX(w) == XtX(Slide_Widget(w)) &&
        Slide_DestY(w) == XtY(Slide_Widget(w)) &&
        Slide_DestWidth(w) == XtWidth(Slide_Widget(w)) &&
        Slide_DestHeight(w) == XtHeight(Slide_Widget(w)))
    {
    	XtCallCallbackList(w, Slide_FinishCallback(w), NULL);
	XtRemoveCallback(Slide_Widget(w), XmNdestroyCallback, (XtCallbackProc)targetDestroy, w);
    	XtDestroyWidget(w);
    }
    else
    {
    	Slide_Id(w) = XtAppAddTimeOut(XtWidgetToApplicationContext(w),
    		Slide_Interval(w),
    		(XtTimerCallbackProc)_XmSlideProc,
    		w);
    }
}
