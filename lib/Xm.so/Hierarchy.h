
#include <localdef.h>

/*
 *    Copyright 1990, Integrated Computer Solutions, Inc.
 *
 *		       All Rights Reserved.
 *
 * AUTHOR: Chris D. Peterson
 *
 */

#ifndef _Hierarchy_h
#define _Hierarchy_h

#if defined(VMS) || defined(__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Ext.h>

/************************************************************
*	INCLUDE FILES
*************************************************************/

/************************************************************
*	TYPEDEFS AND DEFINES
*************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _XmHierarchyClassRec	*XmHierarchyWidgetClass;
typedef struct _XmHierarchyRec		*XmHierarchyWidget;

typedef struct _XmHierarchyNodeStateData {
    Widget widget;
    XmHierarchyNodeState state;
} XmHierarchyNodeStateData;

/************************************************************
*	MACROS
*************************************************************/

/************************************************************
*	GLOBAL FUNCTION DECLARATIONS
*************************************************************/

/*	Function Name: XmHierarchyOpenAllAncestors
 *	Description: This function opens all ancestors of the given node.
 *	Arguments: nw - the node (widget) that will be changed.
 *	Returns: none
 */

void XmHierarchyOpenAllAncestors(
#ifndef _NO_PROTO
Widget
#endif
);

WidgetList XmHierarchyGetChildNodes(
#ifndef _NO_PROTO
Widget
#endif
);

extern WidgetClass xmHierarchyWidgetClass;

#if defined(__cplusplus)
}
#endif

#if defined(VMS) || defined(__VMS)
#include <X11/apienvrst.h>
#endif

#endif /* _Hierarchy_h */
