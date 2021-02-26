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
static char rcsid[] = "$XConsortium: mvsSetValues.c /main/7 1995/07/14 11:23:35 drk $"
#endif
#endif
/***********************************************************************
	Calls:

	Summary:
		This function sets the resource values requested and
	then calls mvsCompareResources() to verify that the requested
	changes were made.
************************************************************************/

#include "mvslib.h"

extern void NormalizePixmap();

void mvsSetValues(widget_info,args,nargs)
MvsWidgetInfoRecord *widget_info;
ArgList args;
Cardinal nargs;
{
    int i,j, n;
    XtCallbackList cb_list;
    int t, x, y;
    Arg new_args[100];
    Cardinal new_nargs = 0;
    short num_resources;
    MvsResourceInfoRecord *resource_info;
    Widget widget;
    MvsArgVal *mvs_resources;
    Arg color_args[10];
    Pixel foreground, background;
    Window root;
    int pix_x, pix_y;
    unsigned int pix_width, pix_height, pix_border, depth;
    XImage *pix_image = NULL;
    Pixel pixel1, pixel2;
    GC gc;

    num_resources = widget_info->widget_class_info->num_resources;
    resource_info = widget_info->widget_class_info->resource_info;
    widget = widget_info->widget;
    mvs_resources = widget_info->mvs_resources;

    for(i=0; i<nargs; i++) {
        for (j=0;
             (j<num_resources)&&strcmp(args[i].name,resource_info[j].name);
             j++);

        if (j<num_resources) {
            t = resource_info[j].type_code;
            switch (mvsTypeInfo[t].ref_type) {

            case RefCallbackList:
		new_args[new_nargs].name = args[i].name;
		new_args[new_nargs].value = args[i].value;
		new_nargs++;
                break;
	    case RefValue:
                if (t != T_Pixel) {
			new_args[new_nargs].name = args[i].name;
			new_args[new_nargs].value = args[i].value;
			new_nargs++;
		}
                break;
	    default:
		new_args[new_nargs].name = args[i].name;
		new_args[new_nargs].value = args[i].value;
		new_nargs++;
                break;
	    }
        }
	else {
	    /* Don't change colors on Gadgets that are not ready in
	       automation for these when recording or comparing */
	    if ((mvsGetVisualMode() != VISUAL_MODE_DONT_CHECK) &&
		(XmIsGadget(widget) && 
		(mvsGetClassCode(widget) != mvsXmIconGadgetClass) &&
		(strcmp(args[i].name, "background") == 0 ||
		 strcmp(args[i].name, "foreground") == 0 ||
		 strcmp(args[i].name, "bottomShadowColor") == 0 ||
		 strcmp(args[i].name, "highlightColor") == 0 ||
		 strcmp(args[i].name, "topShadowColor") == 0 ||
		 strcmp(args[i].name, "borderColor") == 0))) {
		;
	    }
	    else {
		new_args[new_nargs].name = args[i].name;
		new_args[new_nargs].value = args[i].value;
		new_nargs++;
	    }
	}
    } /* for() */

    /* Normalize pixmap when in record or compare mode */

    if (mvsGetVisualMode() != VISUAL_MODE_DONT_CHECK) {
	for (i = 0; i < new_nargs; i++) {
	    if ((strcmp(new_args[i].name, "labelPixmap") == 0 		  ||
		 strcmp(new_args[i].name, "labelInsensitivePixmap") == 0  ||
		 strcmp(new_args[i].name, "symbolPixmap") == 0		  ||
		 strcmp(new_args[i].name, "selectPixmap") == 0		  ||
		 strcmp(new_args[i].name, "selectInsensitivePixmap") == 0 ||
		 strcmp(new_args[i].name, "armPixmap") == 0 		  ||
		 strcmp(new_args[i].name, "backgroundPixmap") == 0	  ||
		 strcmp(new_args[i].name, "highlightPixmap") == 0         ||
		 strcmp(new_args[i].name, "borderPixmap") == 0		  ||
		 strcmp(new_args[i].name, "topShadowPixmap") == 0	  ||
		 strcmp(new_args[i].name, "bottomShadowPixmap") == 0	  ||
		 strcmp(new_args[i].name, "cascadePixmap") == 0		  ||
		 strcmp(new_args[i].name, "largeIconPixmap") == 0	  ||
		 strcmp(new_args[i].name, "largeIconMask") == 0	          ||
		 strcmp(new_args[i].name, "smallIconPixmap") == 0         ||
		 strcmp(new_args[i].name, "smallIconMask") == 0	          ||
		 strcmp(new_args[i].name, "bindingPixmap") == 0	          ||
		 strcmp(new_args[i].name, "collapsedStatePixmap") == 0	  ||
		 strcmp(new_args[i].name, "expandedStatePixmap") == 0)	  &&
		(new_args[i].value != (XtArgVal) XmUNSPECIFIED_PIXMAP) &&
		new_args[i].value != (XtArgVal) None) {

		NormalizePixmap(widget_info, new_args[i].value);
	 
	    }
	}
    }

    if (mvsGetVisualMode() == VISUAL_MODE_GENERATE_PIXMAPS)
      XtSetValues(widget, new_args, new_nargs);
/*    else
      XtSetValues(widget, args, nargs);
*/
/* Don't change colors on gadgets until automation is really updated to 2.0
   and supports colors on gadgets */
    else
	if (XmIsGadget(widget) &&  
	    (mvsGetClassCode(widget) != mvsXmIconGadgetClass))
	    XtSetValues(widget, new_args, new_nargs);
        else
	    XtSetValues(widget, args, nargs);


    mvsSetLocalValues(widget_info, args, &nargs);

} /* End mvsSetValuesNoCheck() */
