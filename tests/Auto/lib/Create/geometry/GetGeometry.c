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
static char rcsid[] = "$XConsortium: GetGeometry.c /main/8 1995/07/14 10:58:40 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetGeometry.c	1.8.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/21/90 SJS add to sccs
            06/22/90 SJS do not get geometry of widgets that are
                         being destroyed. (Send back 0 geo)
            07/20/90 PSN Fixed geometry calculation for XmRowColumn parenatage
	Calls:

	Summary:
            Returns the specified widget's position and size on the screen.    
           
            INPUTS:
                widget
        
            OUTPUTS:
                x,y           - position of widget relative to root window in
                                pixels
                width,height  - size of widget in pixels

            RETURNS:
                nothing
************************************************************************/


#include <AutoMessages.h>
#include "mvslib.h"

void mvsGetWidgetGeometry(widget,x,y,width,height,border_width)
Widget widget;
int *x, *y, *width, *height, *border_width;
{
    Window window;
    MvsWidgetInfoRecord *w_info;
    int window_x, window_y, tmp_x, tmp_y;
    Position g_x,g_y;
    Dimension g_h, g_w, g_bw;
    unsigned char g_unit_type;
    Arg args[8];
    int n=0;
    int being_destroyed;
    Window root_return,child_return;
    unsigned int tmp_d;

    if (widget == NULL) {
        AutoMessage(_AutoMessages[WARNMSG61]);
        return;
    }
    else
        window = XtWindowOfObject(widget);

    w_info = mvsWidgetToWidgetInfo(widget);
    if(w_info == NULL)
        being_destroyed = False; /* The widget is just being created and is
                                    not in our hierarchy yet */
    else
        being_destroyed = w_info->being_destroyed;
    
    if(!being_destroyed && XtIsRealized(widget)) {
        if (!XGetGeometry(mvsDisplay,window,&root_return,&tmp_x, &tmp_y,
                          (unsigned int *)width, (unsigned int *)height,
                          (unsigned int *)border_width,
                          (unsigned int *) &tmp_d)) {
            AutoError(_AutoMessages[WARNMSG62]);
            
        }

        window_x = 0;
        window_y = 0;

        if( !(XtIsWidget(widget)) ) {  /* Is this a Gadget? */
            XtSetArg(args[n], XmNheight, &g_h); n++;
            XtSetArg(args[n], XmNwidth, &g_w); n++;
            XtSetArg(args[n], XmNx, &g_x); n++;
            XtSetArg(args[n], XmNy, &g_y); n++;
            XtSetArg(args[n], XmNborderWidth, &g_bw); n++;
	    XtSetArg(args[n], XmNunitType, &g_unit_type); n++;
            XtGetValues(widget, args, n);

/* Automation Added - get proper value in pixels */

	    g_h = XmConvertUnits
			(widget, XmVERTICAL, g_unit_type, g_h, XmPIXELS);
	    g_y = XmConvertUnits
			(widget, XmVERTICAL, g_unit_type, g_y, XmPIXELS);
	    g_w = XmConvertUnits
			(widget, XmHORIZONTAL, g_unit_type, g_w, XmPIXELS);
	    g_x = XmConvertUnits
			(widget, XmHORIZONTAL, g_unit_type, g_x, XmPIXELS);
	    g_bw = XmConvertUnits
			(widget, XmHORIZONTAL, g_unit_type, g_bw, XmPIXELS);

/* End Automation Added */

            window_x += (int)g_x;
            window_y += (int)g_y;

	    if (!mvsIsParentRowColumn(w_info)) {
	    /* This is not added because XmRowColumn adds entryBorder to its
	     * children, which is part of widget's window! - weard! */
            	window_x += *border_width;
            	window_y += *border_width;
	    }

            *width = (int)g_w;
            *height = (int)g_h;
            *border_width = (int)g_bw;
        }

        if (!XTranslateCoordinates(mvsDisplay,window,
                                   DefaultRootWindow(mvsDisplay),
                                   window_x,window_y,x,y,&child_return)) {
            AutoMessage(_AutoMessages[WARNMSG63]);
            exit(-1);
        }
    }
    else {
        *x = *y = *width = *height = *border_width = 0;
    } /* End if(!being_destroyed) */

} /* End mvsGetWidgetGeometry() */
