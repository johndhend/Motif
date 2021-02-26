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
static char rcsid[] = "$XConsortium: mvsSetUpGlob.c /main/7 1995/07/14 11:23:04 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsSetUpGlob.c	1.11.1.2     Date:2/13/91                                 
  	Author: SJS
	History:
            05/08/90 SJS Create
            09/20/90 SJS addin XmNrecomputeSize for Buttons
            10/25/90 SJS remove XmNrecomputeSize for Buttons
	Calls:

	Summary:
            This function conditionally sets up the "global" arguments
        of a widget class. We subjectively choose resource settings
        that we want to have in order to determine the effects of
        other resource changes. (For example, changing the borderPixmap
        will not have a visible effect unless the border_width is
        non-zero.) If the widget class has this resource, then it is
        added to the "global" list of resource arguments for usage later.
            This function needs to be smarter for "special" types of
        widgets.
************************************************************************/
#include "mvslib.h"

void mvsSetUpGlobalArgs(widget_class_info)
MvsWidgetClassInfo *widget_class_info;
{
    int n=0;
    static int first_time = 1;
    static XmString string1 = NULL;
    static char string2[MAX_STRING_LENGTH] = "Text Widget\n\nNew line";
    XmFontList     font_list;

    font_list = XmFontListCreate(mvsFontInfo[0].font_struct,
				     mvsFontInfo[0].char_set_name) ;
    if (first_time) {
        first_time = 0;
        string1 = XmStringCreateLtoR("Some Label",mvsGetCharSet
				     (mvsFontInfo[0].char_set_name));
    }

    if (widget_class_info->num_common_args == 0) {

        if((widget_class_info == iXmTextWidgetClass) ||
           (widget_class_info == iXmScrolledTextWidgetClass)) {

         	if(mvsGetResourceNum(widget_class_info,XmNfontList)
							!= NON_EXISTENT) 
	        {
                	XtSetArg(widget_class_info->common_args[n], 
						XmNfontList, font_list);
                	n++;
	 	}
	}

        if((widget_class_info != iXmTextWidgetClass) &&
           (widget_class_info != iXmScrolledTextWidgetClass) &&
           (widget_class_info != iXmSelectionBoxWidgetClass) &&
           (widget_class_info != iXmSelectionDialogWidgetClass) &&
           (widget_class_info != iXmCommandWidgetClass)) {

            if(mvsGetResourceNum(widget_class_info,XmNwidth) != NON_EXISTENT) {
                XtSetArg(widget_class_info->common_args[n], XmNwidth, 125);
                n++;
            }
            if(mvsGetResourceNum(widget_class_info,XmNheight) != NON_EXISTENT) {
                XtSetArg(widget_class_info->common_args[n], XmNheight, 125);
                n++;
            }
        }
        else {
            if(mvsGetResourceNum(widget_class_info,XmNvalue) != NON_EXISTENT) {
                XtSetArg(widget_class_info->common_args[n], XmNvalue, string2);
                n++;
            }
            if(mvsGetResourceNum(widget_class_info,
                                 XmNeditMode) != NON_EXISTENT) {
                XtSetArg(widget_class_info->common_args[n],XmNeditMode,
                         XmMULTI_LINE_EDIT);
                n++;
            }
        }
        if(mvsGetResourceNum(widget_class_info, XmNx) != NON_EXISTENT) {
            XtSetArg(widget_class_info->common_args[n], XmNx, 50);
            n++;
        }
        if(mvsGetResourceNum(widget_class_info, XmNy) != NON_EXISTENT) {
            XtSetArg(widget_class_info->common_args[n], XmNy, 50);
            n++;
        }
        if(mvsGetResourceNum(widget_class_info,
                             XmNshadowThickness) != NON_EXISTENT) {
            XtSetArg(widget_class_info->common_args[n], XmNshadowThickness, 10);
            n++;
        }
        if(mvsGetResourceNum(widget_class_info,
                             XmNhighlightThickness) != NON_EXISTENT) {
            XtSetArg(widget_class_info->common_args[n], XmNhighlightThickness,
                     10);
            n++;
        }
        if(mvsGetResourceNum(widget_class_info,
                             XmNlabelString) != NON_EXISTENT) {
            XtSetArg(widget_class_info->common_args[n],XmNlabelString,string1);
            n++;
        }

        widget_class_info->num_common_args = n;
    } /* End if() */

} /* End mvsSetUpGlobalArgs() */
