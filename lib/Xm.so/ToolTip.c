
#include <localdef.h>

#define BUG1232
/**
 *
 * $Id: ToolTip.c,v 1.3.2.2 2003/10/10 12:48:09 yura Exp $
 *
 **/



#include <Xm/LabelP.h>
#include <Xm/VendorSEP.h>
#include <Xm/GadgetP.h>
#include <Xm/SlideC.h>
#include "BaseClassI.h"

typedef XmVendorShellExtPart XmToolTipDataStruct;

#ifdef BUG1232
/* rws 25 Sep 2003
   If the TipLabel gets destroyed, get rid of it's Shell, and get rid
   of the dangling reference to it.
 */
static void
TipLabelDestroy(Widget label, XtPointer client_data, XtPointer call_data)
{
XmToolTipDataStruct *TipData = (XmToolTipDataStruct *)client_data;

    XtDestroyWidget(XtParent(label));
    TipData->label = NULL;
}
#endif

static XmToolTipDataStruct *
ToolTipGetData(Widget w)
{
    Widget top = w;
    XmWidgetExtData	extData;
    XmVendorShellExtObject vse;
    
    while (XtParent(top))
    {
	top = XtParent(top);
    }
    if (
#ifdef BUG1232
/* rws 25 Sep 2003
   If the VendorShell is in the process of being destroyed, do not return
   any TipData.
 */
        ! top->core.being_destroyed &&
#endif
        (extData = _XmGetWidgetExtData( (Widget) top, XmSHELL_EXTENSION)) &&
        (vse = (XmVendorShellExtObject) extData->widget))
    {
    	if (vse->vendor.label == NULL)
    	{
            Widget shell;
            
	    shell = XtVaCreateWidget("TipShell", 
                                     transientShellWidgetClass, top,
                                     XmNoverrideRedirect, True,
                                     NULL);
	    vse->vendor.label = XmCreateLabel(shell, "TipLabel", NULL, 0);
#ifdef BUG1232
/* rws 25 Sep 2003
   Make sure we know if the label disappears.
 */
	    XtAddCallback(vse->vendor.label, 
		      XmNdestroyCallback, 
		      (XtCallbackProc)TipLabelDestroy, 
		      &vse->vendor);
#endif
	    XtManageChild(vse->vendor.label);
    	}
    	return(&vse->vendor);
    }
    else
    {
    	return(NULL);
    }
}

static void
ToolTipUnpostFinish(Widget slide, XtPointer client_data, XtPointer call_data)
{
    XmToolTipDataStruct *TipData = (XmToolTipDataStruct *)client_data;
    
    if ( ! XtParent(TipData->label)->core.being_destroyed)
    {
	XtPopdown(XtParent(TipData->label));
    }
}

static void
ToolTipUnpost(XtPointer client_data, XtIntervalId *id)
{
    XmToolTipDataStruct *TipData = (XmToolTipDataStruct *)client_data;
    
    if (TipData->duration_timer)
    {
	if (! id || (id && (*id != TipData->duration_timer)))
	{
	    XtRemoveTimeOut(TipData->duration_timer);
	}
	TipData->duration_timer = (XtIntervalId)NULL;
    }
    if (TipData->slider)
    {
    	XtDestroyWidget(TipData->slider);
    	TipData->slider = NULL;
    }
    ToolTipUnpostFinish(NULL, TipData, NULL);
}

static void
ToolTipPostFinish(Widget slide, XtPointer client_data, XtPointer call_data)
{
    XmToolTipDataStruct *TipData = (XmToolTipDataStruct *)client_data;
    
    TipData->slider = NULL;
    if (TipData->post_duration > 0)
    {
    	TipData->duration_timer = 
            XtAppAddTimeOut(
                            XtWidgetToApplicationContext(TipData->label),
                            (unsigned long)TipData->post_duration,
                            (XtTimerCallbackProc)ToolTipUnpost,
                            TipData);
    }
}

static void
ToolTipPost(XtPointer client_data, XtIntervalId *id)
{
    Widget w = (Widget)client_data;
    XmToolTipDataStruct *TipData = ToolTipGetData(w);
    int rx, ry, x, y;
    unsigned int key;
    Window root, child;
    XtWidgetGeometry geo;
    Position destX, destY;
    
    /*
      printf("%s:%s(%d) - %s\n", __FILE__, __FUNCTION__, __LINE__,
      XtName(w));
    */
#ifdef BUG1232
/* rws 25 Sep 2003
   protect against NULL TipData
 */
#endif
    if (TipData)
    {
	TipData->timer = (XtIntervalId)NULL;
	XQueryPointer(XtDisplay(w),
		      XtWindow(w),
		      &root,
		      &child,
		      &rx, &ry,
		      &x, &y,
		      &key);
	if (TipData->duration_timer != (XtIntervalId)NULL)
	{
	    XtRemoveTimeOut(TipData->duration_timer);
	    TipData->duration_timer = (XtIntervalId)NULL;
	}
	if (XmIsPrimitive(w))
	{
	    XtVaSetValues(TipData->label,
			  XmNlabelString, 
			  ((XmPrimitiveWidget)w)->primitive.tool_tip_string,
			  NULL);
	}
	else if (XmIsGadget(w))
	{
	    XtVaSetValues(TipData->label,
			  XmNlabelString, ((XmGadget)w)->gadget.tool_tip_string,
			  NULL);
	}
	else
	{
	    XmString string;
	    
	    string = XmStringCreateLocalized(XtName(w));
	    XtVaSetValues(TipData->label,
			  XmNlabelString, string,
			  NULL);
	    XmStringFree(string);
	}
	XtQueryGeometry(TipData->label, NULL, &geo);
#if 1
	/* rws 25 Feb 2001
	   Fix for Bug #1153
	   Don't let the tip be off the right/bottom of the screen
	*/
	destX = rx + (XmIsGadget(w) ? XtX(w) : 0) - x + XtWidth(w) / 2;
	if (destX + geo.width > WidthOfScreen(XtScreen(w)))
	{
	    destX = WidthOfScreen(XtScreen(w)) - geo.width;
	}
	destY = ry + (XmIsGadget(w) ? XtY(w) : 0) - y + XtHeight(w);
	if (destY + geo.height > HeightOfScreen(XtScreen(w)))
	{
	    destY = ry + (XmIsGadget(w) ? XtY(w) : 0) - y - geo.height;
	}
#endif
	XtVaSetValues(XtParent(TipData->label),
		      XmNx, rx + 1,
		      XmNy, ry + 1,
		      XmNwidth, 1,
		      XmNheight, 1,
		      NULL);
	TipData->slider = XtVaCreateWidget("ToolTipSlider", 
					   xmSlideContextWidgetClass,
					   XmGetXmDisplay(XtDisplay(w)),
					   XmNslideWidget, 
					   XtParent(TipData->label),
					   XmNslideDestX, destX,
					   XmNslideDestY, destY,
					   XmNslideDestWidth, geo.width,
					   XmNslideDestHeight, geo.height,
					   NULL);
	XtAddCallback(TipData->slider, 
		      XmNslideFinishCallback, 
		      (XtCallbackProc)ToolTipPostFinish, 
		      TipData);
	XtPopup(XtParent(TipData->label), XtGrabNone);
    }
}

void 
_XmToolTipEnter(Widget wid,
                XEvent *event,
                String *params,
                Cardinal *num_params)
{
    XmToolTipDataStruct *TipData;
    
    /*
      printf("%s:%s(%d) - %s %s %i\n", 
      __FILE__, __FUNCTION__, __LINE__,
      XtName(wid),
      XmIsPrimitive(wid) ? "Primitive" : 
      (XmIsGadget(wid) ? "Gadget" : "Unknown"),
      event ? event->type : 0);
    */
    if ((XmIsPrimitive(wid) && 
         ((XmPrimitiveWidget)wid)->primitive.tool_tip_string) ||
        (XmIsGadget(wid) && ((XmGadget)wid)->gadget.tool_tip_string))
    {
	TipData = ToolTipGetData(wid);
	if (TipData && TipData->enable && ! TipData->timer)
	{
            unsigned long delay;
            
	    if (event && 
                (event->xcrossing.time - 
                 TipData->leave_time < TipData->post_delay))
	    {
		delay = 0;
	    }
	    else
	    {
		delay = (unsigned long)TipData->post_delay;
	    }
	    if (TipData->duration_timer)
	    {
		XtRemoveTimeOut(TipData->duration_timer);
		TipData->duration_timer = (XtIntervalId)NULL;
	    }
	    TipData->timer = XtAppAddTimeOut(XtWidgetToApplicationContext(wid),
                                             delay,
                                             (XtTimerCallbackProc)ToolTipPost,
                                             wid);
	}
    }
}

void 
_XmToolTipLeave(Widget wid,
                XEvent *event,
                String *params,
                Cardinal *num_params)
{
    XmToolTipDataStruct *TipData = ToolTipGetData(wid);
    
    /*
      printf("%s:%s(%d) - %s\n",
      __FILE__, __FUNCTION__, __LINE__, XtName(wid));
    */
    if (TipData)
    {
	if (TipData->timer)
	{
	    XtRemoveTimeOut(TipData->timer);
	    TipData->timer = (XtIntervalId)NULL;
	}
	else
	{
	    if (event && 
                (TipData->duration_timer || TipData->post_duration == 0))
	    {
		TipData->leave_time = event->xcrossing.time;
	    }
	    ToolTipUnpost(TipData, NULL);
	}
    }
}

Widget 
XmToolTipGetLabel(Widget wid)
{
    XmToolTipDataStruct *TipData = ToolTipGetData(wid);
    
#ifdef BUG1232
/* rws 25 Sep 2003
   protect against NULL TipData
 */
#endif
    return(TipData ? TipData->label : NULL);
}
