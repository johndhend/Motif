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
static char rcsid[] = "$XConsortium: IsParent.c /main/7 1995/07/14 11:17:14 drk $"
#endif
#endif

/***********************************************************************
  	@(#)IsParent.c	1.6.1.1	Date:1/22/91
  	Author: SJS
	History:
            06/05/90 SJS create
            06/25/90 SJS check the parent *not* the current
            06/26/90 SJS add IsParentShell()
            07/03/90 PSN add IsParentRowColumn()
            07/23/90 SJS fix all the functions to do the right error checks
	Calls:

	Summary:
            This file contains functions which determine the parentage of
        a widget. This is based on the class code of the parent. The
	basic assumption is that we have a widget info hierarchy that
	accurately reflects the widgets we have created. This is true,
	EXCEPT when a widget is first being created. The widget exists
	and its parents exist, but their relationship is not yet known
	in the widget info hierarchy. This relationship is established
	upon updating the objects/widget hierarchy.
	    The further implication is that the geometry of RowColumn
	children will be initially incorrect because of RowColumns
	handling of entry border. (IE. We can't do "the right thing"
	with the geometry because we don't know the parent is a RowColumn.
	Thus, mvsIsRowColumnParent() incorrectly returnds FALSE when a
	RowColumn's chilren are first created. Later on, when an update is
	done, the geometry is corrected)

        INPUTS (all functions)
            widget_info - the widget info record in question

        OUTPUTS
            none
 
        RETURNS
            class code
************************************************************************/

#include "mvslib.h"

/************************************************************************/
/*  This function determines if the parent of a widget is a Shell       */
/************************************************************************/
int mvsIsParentShell(widget_info)
MvsWidgetInfoRecord *widget_info;
{
    Widget widget;

    if(widget_info != NULL) {
        widget = XtParent(widget_info->widget);
        if (widget != (Widget)NULL) {
            if(XtIsShell(widget)) {
                return(TRUE);
            }
        }
    }

    return(FALSE);

} /* End mvsIsParentShell() */


/************************************************************************/
/*  This function determines if the parent of a widget is a DialogShell */
/************************************************************************/
int mvsIsParentDialogShell(widget_info)
MvsWidgetInfoRecord *widget_info;
{
    Widget widget;
    int class_code;

    if(widget_info != NULL) {
        widget = XtParent(widget_info->widget);
        if (widget != (Widget)NULL) {
    	    class_code = mvsGetClassCode(widget);
    	    if(class_code == mvsXmDialogShellWidgetClass) {
        	return(TRUE);
    	    }
        }
    }

    return(FALSE);

} /* End mvsIsParentDialogShell() */


/************************************************************************/
/*  This function determines if the parent of a widget is a RowColumn   */
/* RowColumn draws the entryBorder *INSIDE* its child windows. I am     */
/* not especially sure that this is correct from a design standpoint,   */
/* but it seems that no one is going to make this change at such a late */
/* stage in Motif development.                                          */
/************************************************************************/
int mvsIsParentRowColumn(widget_info)
MvsWidgetInfoRecord *widget_info;
{
    Widget widget;
    int class_code;

    if(widget_info != NULL) {
        widget = XtParent(widget_info->widget);
        if (widget != (Widget)NULL) {
    	    class_code = mvsGetClassCode(widget);
    	    if(class_code == mvsXmRowColumnWidgetClass) {
        	return(TRUE);
    	    }
        }
    }

    return(FALSE);

} /* End mvsIsParentRowColumn() */
