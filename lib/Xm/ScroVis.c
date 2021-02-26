
#include <localdef.h>

/* $XConsortium: ScroVis.c /main/6 1995/09/19 23:07:44 cde-sun $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */



#include <Xm/ScrolledWP.h>
#include <Xm/NavigatorT.h>
#include "ScrollFramTI.h"
#include "MessagesI.h"
#include "XmI.h"

#define SWMessage1      _XmMMsgScrollVis_0000 

/************************************************************************
 *									*
 * XmScrollVisible -  TraverseObscureCallback helper                    *
 *									*
 ************************************************************************/
void
XmScrollVisible(
		Widget      	scrw,
		Widget          wid,
		Dimension       hor_margin, 
		Dimension       ver_margin)
/*********************
 * A function that makes visible a unvisible or partially visible descendant 
 * of an AUTOMATIC scrolledwindow workwindow.
 *********************
 * - scrw is the ScrolledWindow whose workwindow act as the origin of the move.
 * - wid is the widget to be made visible.
 * - hor_margin, ver_margin are the margins between the widget in its new 
 *   position and the scrolledwindow clipwindow.
**********************/
{
    XmScrolledWindowWidget sw = (XmScrolledWindowWidget) scrw ;
    register 
    Position newx, newy,      /* new workwindow position */
             wx, wy  ;        /* current workwindow position */
    register 
    unsigned short tw, th,         /* widget sizes */
              cw, ch ;        /* clipwindow sizes */
    Position dx, dy ;         /* position inside the workwindow */
    Position src_x, src_y, dst_x, dst_y ;
    Widget w ;
    XmScrolledWindowConstraint swc;
    XmNavigatorDataRec nav_data ;
    _XmWidgetToAppContext(scrw);

    _XmAppLock(app);
    /* check param */
    if (!((scrw) && (XmIsScrolledWindow(scrw)) &&
	  (sw->swindow.ScrollPolicy == XmAUTOMATIC))) {
	XmeWarning(scrw, SWMessage1);
	_XmAppUnlock(app);
	return ;
    }

    /* loop up in search for a "workwindow" */
    w = wid;
    while (w && (XtParent(w) != (Widget) sw->swindow.ClipWindow))
      w = XtParent(w);
    if (!w) {
	XmeWarning(scrw, SWMessage1);
	_XmAppUnlock(app);
	return ;
    }

    /* w is the potentially scrollable ascendant of wid that needs to 
       be scrolled, its parent is the clip window */
    /* In the new scheme, w might not be able to scroll at all,
       or even in the direction the margins point to. There is
       nothing much we can do about that except document that
       traversing to an unvisible kid of unscrollable workwindow will
       not scroll it, resulting in unvisible focus widget. We could
       check for NO_SCROLL in w, but since we cannot check for SCROLL_HOR
       or SCROLL_VERT - depend on the traversal layout - I'd rather do 
       nothing */

    /* we need to get the position of wid relative to w, 
       so we use 2 XtTranslateCoords */
    
    XtTranslateCoords(wid, 0, 0, &src_x, &src_y);
    XtTranslateCoords(w, 0, 0, &dst_x, &dst_y);
    dx = src_x - dst_x ;
    dy = src_y - dst_y ;

    swc = GetSWConstraint(w);
   
    /* get the other positions and sizes */
    cw = XtWidth((Widget) sw->swindow.ClipWindow) ;
    ch = XtHeight((Widget) sw->swindow.ClipWindow) ;
    wx = swc->orig_x - XtX(w) ;  
    wy = swc->orig_y - XtY(w) ; /* both always positive */
    tw = XtWidth(wid) ;
    th = XtHeight(wid) ;
    
    /* find out the zone where the widget lies and set newx,newy (neg) for
       the workw */
    /* if the widget is bigger than the clipwindow, we put it on
       the left, top or top/left, depending on the zone it was */

    if (dy < wy) {                                       /* North */
	newy = dy - (Position)ver_margin ;      /* stuck it on top + margin */
    } else 
    if ((dy + th) <= (ch - XtY(w))) {
	newy = wy ;               /* in the middle : don't move y */
    } else {                                             /* South */
	if (th > ch)
	    newy = dy - (Position)ver_margin ; /* stuck it on top if too big */
	else
	    newy = swc->orig_y + dy - ch + th + (Position)ver_margin;
    } 
	
    if (dx < wx) {                              /* West */
	newx = dx - (Position)hor_margin ; /* stuck it on left + margin */
    } else
    if ((dx + tw) <= (cw - XtX(w))) {
	newx = wx ;  /* in the middle : don't move x */
    } else {                                     /* East */
	if (tw > cw)
	    newx = dx - (Position)hor_margin ; /* stuck it on left if too big */
	else
	    newx = swc->orig_x + dx - cw + tw + (Position)hor_margin;
    } 

    /* a last check */
    if (newx > sw->swindow.hmax - sw->swindow.hExtent) 
	newx = sw->swindow.hmax - sw->swindow.hExtent;
    if (newy > sw->swindow.vmax - sw->swindow.vExtent) 
	newy = sw->swindow.vmax - sw->swindow.vExtent;
    if (newx < sw->swindow.hmin) newx =  sw->swindow.hmin ;
    if (newy < sw->swindow.vmin) newy =  sw->swindow.vmin ;

    nav_data.valueMask = NavValue ;
    nav_data.value.x = newx ;
    nav_data.value.y = newy ;
    nav_data.dimMask = NavigDimensionX|NavigDimensionY ;
    _XmSFUpdateNavigatorsValue((Widget)sw, &nav_data, True);
    _XmAppUnlock(app);
}
