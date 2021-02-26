
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: DropSMgrI.c /main/11 1995/07/14 10:30:45 drk $"
#endif
#endif
/* (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */



#include <stdio.h>
#include <Xm/DropSMgrP.h>
#include "XmI.h"
#include "DropSMgrI.h"
#include "MessagesI.h"
#include "RegionI.h"

#define MESSAGE1 _XmMMsgDropSMgrI_0001
#define MESSAGE2 _XmMMsgDropSMgrI_0002
#define MESSAGE3 _XmMMsgDropSMgrI_0003

 /********    Static Function Declarations    ********/


/********    End Static Function Declarations    ********/

externaldef(xmdsresources)
XtResource _XmDSResources[] = {
	{   XmNdropSiteType, XmCDropSiteType, XmRDropSiteType,
		sizeof(unsigned char),
		XtOffsetOf( struct _XmDSFullInfoRec, type),
		XmRImmediate, (XtPointer) XmDROP_SITE_SIMPLE
	},
	{   XmNdropSiteActivity, XmCDropSiteActivity, XmRDropSiteActivity,
		sizeof(unsigned char),
		XtOffsetOf( struct _XmDSFullInfoRec, activity),
		XmRImmediate, (XtPointer) XmDROP_SITE_ACTIVE
	},
	{   XmNimportTargets, XmCImportTargets, XmRAtomList,
		sizeof(Atom *),
		XtOffsetOf( struct _XmDSFullInfoRec, import_targets),
		XmRImmediate, (XtPointer) NULL
	},
	{   XmNnumImportTargets, XmCNumImportTargets, XmRCardinal,
		sizeof(Cardinal),
		XtOffsetOf( struct _XmDSFullInfoRec, num_import_targets),
		XmRImmediate, (XtPointer) 0
	},
	{   XmNdropSiteOperations, XmCDropSiteOperations,
		XmRDropSiteOperations, sizeof(unsigned char),
		XtOffsetOf( struct _XmDSFullInfoRec, operations), XmRImmediate,
		(XtPointer) (XmDROP_MOVE | XmDROP_COPY),
	},
	{   XmNdropRectangles, XmCDropRectangles, XmRRectangleList,
		sizeof(XRectangle *),
		XtOffsetOf( struct _XmDSFullInfoRec, rectangles),
		XmRImmediate, (XtPointer) NULL
	},
	{   XmNnumDropRectangles, XmCNumDropRectangles, XmRCardinal,
		sizeof(Cardinal),
		XtOffsetOf( struct _XmDSFullInfoRec, num_rectangles),
		XmRImmediate, (XtPointer) 1
	},
	{   XmNdragProc, XmCDragProc, XmRProc,
		sizeof(XtPointer),
		XtOffsetOf( struct _XmDSFullInfoRec, drag_proc),
		XmRImmediate, (XtPointer) NULL
	},
	{   XmNdropProc, XmCDropProc, XmRProc,
		sizeof(XtPointer),
		XtOffsetOf( struct _XmDSFullInfoRec, drop_proc),
		XmRImmediate, (XtPointer) NULL
	},
	{   XmNanimationStyle, XmCAnimationStyle, XmRAnimationStyle,
		sizeof(unsigned char),
		XtOffsetOf( struct _XmDSFullInfoRec, animation_style),
		XmRImmediate, (XtPointer) XmDRAG_UNDER_HIGHLIGHT
	},
	{   XmNanimationPixmap, XmCAnimationPixmap, XmRDynamicPixmap,
		sizeof(Pixmap),
		XtOffsetOf( struct _XmDSFullInfoRec, animation_pixmap),
		XmRImmediate, (XtPointer) XmUNSPECIFIED_PIXMAP
	},
	{   XmNanimationMask, XmCAnimationMask, XmRBitmap,
		sizeof(Pixmap),
		XtOffsetOf( struct _XmDSFullInfoRec, animation_mask),
		XmRImmediate, (XtPointer) XmUNSPECIFIED_PIXMAP
	},
	{   XmNanimationPixmapDepth, XmCAnimationPixmapDepth, XmRCardinal,
		sizeof(int),
		XtOffsetOf( struct _XmDSFullInfoRec, animation_pixmap_depth),
		XmRImmediate, (XtPointer) 0
	},
 	{   XmNclientData, XmCClientData, XmRPointer,
 		sizeof(XtPointer),
 		XtOffsetOf( struct _XmDSFullInfoRec, client_data),
 		XmRImmediate, NULL
 	},
};

externaldef(xmnumdsresources)
Cardinal _XmNumDSResources = XtNumber(_XmDSResources);

void 
_XmDSIAddChild(
        XmDSInfo parentInfo,
        XmDSInfo childInfo,
        Cardinal childPosition )
{
	unsigned short i;
	unsigned short num_children;

	if ((parentInfo == NULL) || (childInfo == NULL))
		return;

	num_children = GetDSNumChildren(parentInfo);

	if (GetDSType(parentInfo) != XmDROP_SITE_COMPOSITE)
	{
		XmeWarning(GetDSWidget(childInfo), MESSAGE1 );
	}

	if (childPosition > num_children)
	{
		XmeWarning(GetDSWidget(parentInfo), MESSAGE2);
		childPosition = num_children;
	}

	if (num_children == GetDSMaxChildren(parentInfo))
	{
		SetDSMaxChildren(parentInfo, num_children + CHILDREN_INCREMENT);
		SetDSChildren(parentInfo, (XtPointer *) XtRealloc(
				(char *) GetDSChildren(parentInfo),
				sizeof(XmDSInfo) * GetDSMaxChildren(parentInfo)));
	}

	for (i = num_children; i > childPosition; i--)
		GetDSChildren(parentInfo)[i] = GetDSChildren(parentInfo)[i-1];
	
	GetDSChildren(parentInfo)[childPosition] = (XtPointer) childInfo;
	SetDSNumChildren(parentInfo, (num_children + 1));
	SetDSParent(childInfo, (XtPointer) parentInfo);

	SetDSLeaf(parentInfo, False);
}

void 
_XmDSIRemoveChild(
        XmDSInfo parentInfo,
        XmDSInfo childInfo )
{
	int i;
	unsigned short num_children;
	Cardinal position;

	if ((parentInfo == NULL) || (childInfo == NULL))
		return;

	num_children = GetDSNumChildren(parentInfo);

	/* Find the child to be Removed */
	position = _XmDSIGetChildPosition(parentInfo, childInfo);
	
	/*
	 * Take it out of the list by writing over its location and
	 * reducing the child count.
	 */
	for (i = position + 1; i < num_children; i++)
		GetDSChildren(parentInfo)[i - 1] = GetDSChildren(parentInfo)[i];
	
	SetDSNumChildren(parentInfo, --num_children);

	if (!num_children)
		SetDSLeaf(parentInfo, True);
}


Cardinal 
_XmDSIGetChildPosition(
        XmDSInfo parentInfo,
        XmDSInfo childInfo )
{
	int i;
	unsigned short num_children;

	if ((parentInfo == NULL) || (childInfo == NULL))
		return(0);

	num_children = GetDSNumChildren(parentInfo);

	if (GetDSParent(childInfo) != (XtPointer) parentInfo)
	{
		char buf[256];
		sprintf(buf, MESSAGE3,
			XrmQuarkToString(GetDSWidget(childInfo)->core.xrm_name),
			XrmQuarkToString(GetDSWidget(parentInfo)->core.xrm_name));
		XmeWarning(GetDSWidget(parentInfo), buf);
		return(num_children);
	}

	for (i = 0; i < num_children; i++)
		if (GetDSChildren(parentInfo)[i] == (XtPointer) childInfo)
			break;

	if (i == num_children)
	{
		char buf[256];
		sprintf(buf, MESSAGE3,
			XrmQuarkToString(GetDSWidget(childInfo)->core.xrm_name),
			XrmQuarkToString(GetDSWidget(parentInfo)->core.xrm_name));
		XmeWarning(GetDSWidget(parentInfo), buf);
	}
	
	return(i);
}

void 
_XmDSIReplaceChild(
        XmDSInfo oldChildInfo,
        XmDSInfo newChildInfo )
{
	int i;
	unsigned short num_children;
	XmDSInfo parentInfo;

	if ((oldChildInfo == NULL) ||
		(newChildInfo == NULL))
		return;
	
	if ((parentInfo = (XmDSInfo) GetDSParent(oldChildInfo)) == NULL)
		return;

	num_children = GetDSNumChildren(parentInfo);

	for (i=0; i < num_children; i++)
	{
		if (GetDSChildren(parentInfo)[i] == (XtPointer) oldChildInfo)
			GetDSChildren(parentInfo)[i] = (XtPointer) newChildInfo;
	}

	SetDSParent(oldChildInfo, NULL);

	if ((GetDSParent(newChildInfo)) &&
		(GetDSParent(newChildInfo) != (XtPointer) parentInfo))
		_XmDSIRemoveChild(parentInfo, newChildInfo);
	else
		SetDSParent(newChildInfo, parentInfo);
}


void 
_XmDSISwapChildren(
        XmDSInfo parentInfo,
		Cardinal position1,
		Cardinal position2 )
{
	XmDSInfo tmp_info;
	unsigned short num_children;

	if (parentInfo == NULL)
		return;

	num_children = GetDSNumChildren(parentInfo);

	if ((position1 > num_children) || (position2 > num_children))
		return;

	tmp_info = (XmDSInfo) GetDSChildren(parentInfo)[position1];

	GetDSChildren(parentInfo)[position1] =
		GetDSChildren(parentInfo)[position2];
	GetDSChildren(parentInfo)[position2] = (XtPointer) tmp_info;
}

void 
_XmDSIDestroy(
        XmDSInfo info,
#if NeedWidePrototypes
                        int substructures )
#else
                        Boolean substructures )
#endif /* NeedWidePrototypes */
{
	if (info != NULL)
	{

		if ((GetDSType(info) == XmDROP_SITE_COMPOSITE) &&
			(GetDSChildren(info) != NULL) &&
			(substructures))
			XtFree( (char *) GetDSChildren(info));

		if (GetDSRegion(info) && (substructures))
			_XmRegionDestroy(GetDSRegion(info));

		XtFree( (char *) info);
	}
}

Dimension
_XmDSIGetBorderWidth(
        XmDSInfo info)
{
	if (info == NULL)
		return(0);

	if (GetDSRemote(info))
	{
		switch (GetDSAnimationStyle(info))
		{
			case XmDRAG_UNDER_NONE:
			{
				XmDSRemoteNoneStyleRec *sr =
					(XmDSRemoteNoneStyleRec *)
						GetDSRemoteAnimationPart(info);
				
				return(sr->border_width);
			}
			case XmDRAG_UNDER_HIGHLIGHT:
			{
				XmDSRemoteHighlightStyleRec *sr =
					(XmDSRemoteHighlightStyleRec *)
						GetDSRemoteAnimationPart(info);
				
				return(sr->border_width);
			}
			case XmDRAG_UNDER_SHADOW_IN:
			case XmDRAG_UNDER_SHADOW_OUT:
			{
				XmDSRemoteShadowStyleRec *sr =
					(XmDSRemoteShadowStyleRec *)
						GetDSRemoteAnimationPart(info);
				
				return(sr->border_width);
			}
			case XmDRAG_UNDER_PIXMAP:
			{
				XmDSRemotePixmapStyleRec *sr =
					(XmDSRemotePixmapStyleRec *)
						GetDSRemoteAnimationPart(info);
				
				return(sr->border_width);
			}
			default:
				/* Shouldn't be here */
				return 0;
			/*NOTREACHED*/
			break;
		}
	}
	else
	{
		Widget w = GetDSWidget(info);

		return(XtBorderWidth(w));
	}
}

