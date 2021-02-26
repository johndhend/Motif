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
static char rcsid[] = "$XConsortium: mvsDstroyWid.c /main/7 1995/07/14 11:25:35 drk $"
#endif
#endif
  /***********************************************************************
    Calls:
    
    Summary:
    This function results in the destruction of the current widget.
    The allocated colors are released and the widget info record is also
    freed. The bulk of the work is done within xisDestroyWidget()
    Formerly, the callbacks were deleted, but this can not be
    done because the widget is already destroyed in Xt.
    ************************************************************************/
  
#include "mvslib.h"
  
void mvsDestroyWidget(widget_info,check_callbacks)
MvsWidgetInfoRecord *widget_info;
int check_callbacks;
{
  extern void mvsDepthDestroy();
  extern int mvsOnlyChild();
  int i;
  MvsWidgetClassInfo *class_info;
  MvsWidgetInfoRecord *descendant;
  MvsWidgetInfoRecord *object_stack[MAX_NUM_OBJECTS];
  int stack_top=0;
  int widget_class_code, widget_class_code_2;
  Widget child = NULL;
  int PAGESCROLLER = 0;
  
  /* 
    Determine if the parent of the widget you are destroying
    is a PanedWindow. If it is and the next child is a sash
    followed by a separator gadget, then the Toolkit is going
    to destroy the sash and the separator. Take care of destroying
    the sash and the separator.
    */
  
  if (widget_info->parent->widget == NULL)
    widget_class_code = -1;
  else 
    widget_class_code = mvsGetClassCode(widget_info->parent->widget);
  
  if (widget_class_code == mvsXmPanedWindowWidgetClass) {
    if (widget_info->next_sibling != NULL) {
      if (mvsGetClassCode(widget_info->next_sibling->widget) ==
	  mvsXmSashWidgetClass) {
	widget_info->next_sibling->being_destroyed = TRUE;
	xisDestroyWidget(widget_info->next_sibling->widget);
	if (widget_info->next_sibling->next_sibling != NULL) {
	  if (mvsGetClassCode
	      (widget_info->next_sibling->next_sibling->widget) ==
	      mvsXmSeparatorGadgetClass) {
	    xisDestroyWidget
	      (widget_info->next_sibling->next_sibling->widget);
	    widget_info->next_sibling->next_sibling->being_destroyed 
	      = TRUE;
	  }
	}
      }
    }
  }
  
  class_info = widget_info->widget_class_info;

  /* See if the widget to be destroyed is a Notebook PageScroller
   * If it is, destroy it even though Notebook has begun to
   */
  if (strcmp (XtName(widget_info->widget), "PageScroller") == 0)
    PAGESCROLLER = 1;
  
  if (XtIsRealized(widget_info->widget) || (PAGESCROLLER == 1)) {
    if (mvsGetVisualMode() != VISUAL_MODE_GENERATE_PIXMAPS) {
      for (i=0; i<class_info->num_res_colors; i++) {
	if (class_info->res_color_ref[i] >= 0)
	  mvsFreeColor(widget_info->mvs_resources[class_info->res_color_ref[i]]);
      }
    }
    
    if(widget_info->c_parent) {
      if(widget_info->next_sibling)
	widget_info->next_sibling->being_destroyed = TRUE;
    }
    widget_info->being_destroyed = TRUE;
    if((widget_info->c_parent) && mvsOnlyChild(widget_info->parent)) {
      MvsWidgetInfoRecord *w_parent;
      w_parent=widget_info;
      while((w_parent != NULL) && (w_parent->c_parent) &&
	    mvsOnlyChild(w_parent->parent)) {
	w_parent = w_parent->parent;
      }
      w_parent->being_destroyed = TRUE;
      descendant = w_parent->first_child;
      xisDestroyWidget(w_parent->widget);
    }
    else {
      if(widget_info->c_parent) { /* make sure that the other children
				     assume the role of destroying the
				     parent */
	if(widget_info->next_sibling) {
	  mvsDepthDestroy(widget_info->next_sibling->first_child);
	}
      }
      descendant = widget_info->first_child;
      xisDestroyWidget(widget_info->widget);
    }
    /* Perform Depth-First Search */
    mvsDepthDestroy(descendant);
    
    /* Free widget_info and all its children widget_info's */
    
    if ((widget_info->c_parent) && mvsOnlyChild(widget_info->parent)) {
      mvsFreeWidgetInfo(widget_info->parent); 
    }
    else {
      /*
	Same as earlier, when you have an automatically destroyed
	widget (sash and separator in PanedWindow, you need to 
	free the memory associated with the sash and separator.
	*/
      if (widget_class_code == mvsXmPanedWindowWidgetClass) {
	if (widget_info->next_sibling != NULL) {
	  if (mvsGetClassCode(widget_info->next_sibling->widget) ==
	      mvsXmSashWidgetClass) {
	    if (widget_info->next_sibling->next_sibling != NULL) {
	      if (mvsGetClassCode
		  (widget_info->next_sibling->next_sibling->widget) ==
		  mvsXmSeparatorGadgetClass) {
		mvsFreeWidgetInfo
		  (widget_info->next_sibling->next_sibling);
		mvsFreeWidgetInfo(widget_info->next_sibling);
	      }
	    }
	  }
	}
      }
      mvsFreeWidgetInfo(widget_info);
    }
    
    /* Don't destroy the widget if it is a Notebook PageScroller
     * since the Notebook destroys the widget itself
     */
    if (PAGESCROLLER != 1)
	XtDestroyWidget(widget_info->widget);
    
    xisProcessEvents(NULL, 0);
    
    xisProcessObjects();
  } /* End if(XtIsRealized(widget_info->widget)) */
  
} /* End mvsDestroyWidget() */


/***********************************************************************
  Author: SJS
  History:
  08/20/90 SJS re-use depth-first search code.
  Calls:
  
  Summary:
  This function marks the passed in widget info and all
  of its descendants as being destroyed. The current Motif
  implementation does not follow the AES. Specifically, MenuShells
  are created in a "cascading" chain in a Convenience function
  manner. However, these parents are not deleted when the child is
  destroyed as is customary for all other Convenience created
  widgets.
  ***********************************************************************/

void mvsDepthDestroy(w_info)
     MvsWidgetInfoRecord *w_info;
{
  MvsWidgetInfoRecord *descendant;
  MvsWidgetInfoRecord *object_stack[MAX_NUM_OBJECTS];
  int stack_top=0;
  
  descendant = w_info;
  /* Perform Depth-First Search */
  while (descendant) {
    descendant->being_destroyed = TRUE;
    if(descendant->widget != NULL)
      xisDestroyWidget(descendant->widget);
    if (descendant->first_child != NULL) {
      object_stack[stack_top++] = descendant;
      descendant = descendant->first_child;
    }
    else if (descendant->next_sibling != NULL) {
      descendant = descendant->next_sibling;
    }
    else {
      descendant = NULL;
      while (stack_top > 0 && descendant == NULL)
	descendant = object_stack[--stack_top]->next_sibling;
    }       
  } /* End while() */
} /* End mvsDepthDestroy() */


/***********************************************************************
  Author: SJS
  History:
  08/21/90 SJS Create for menus
  Calls:
  
  Summary:
  This function checks to see if the 'Convenience'
  created parent has had any other children assigned to it.
  ***********************************************************************/

int mvsOnlyChild(w_info)
     MvsWidgetInfoRecord *w_info;
{
  MvsWidgetInfoRecord *tmp_info;
  
  if(w_info->first_child != (MvsWidgetInfoRecord *)NULL) {
    tmp_info = w_info->first_child->next_sibling;
    while(tmp_info != (MvsWidgetInfoRecord *)NULL) {
      if(!tmp_info->being_destroyed)
	if (tmp_info->widget != w_info->first_child->widget)
	  return(FALSE);
      tmp_info = tmp_info->next_sibling;
    }
  }
  return(TRUE);
  
} /* End mvsOnlyChild() */
