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
static char rcsid[] = "$XConsortium: mvsCpRsc.c /main/7 1995/07/14 11:20:13 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsCpRsc.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree.
	   05/29/90 SJS changes for composites
	   07/29/90 PSN parameter changes, memory fixes
	Calls:

	Summary:
		This file contains function which copy resources.
	The method of copying is based on the type of each resource and
	a pointer/value is returned based on this type.
************************************************************************/

#include "mvslib.h"

/************************************************************************
*   This function copies One resource. The resource is copied           *
*   based on its type and a pointer/value is returned.                  *
************************************************************************/
MvsArgVal mvsCopyResource(widget_class_info, src_resource, i) 
MvsWidgetClassInfo *widget_class_info;
MvsArgVal src_resource; 
int i;
{ 
    MvsArgVal dst_resource;
    MvsResourceInfoRecord *resource_info;

    resource_info = widget_class_info->resource_info;

    switch (mvsTypeInfo[resource_info[i].type_code].ref_type) {

	    case RefXmStringTable: /* Here until handling of compound strings */
	                           /* becomes clear */
	    case RefValue: 	 
            case RefGeneric:
            case RefBoolean: 
                dst_resource = src_resource; 
                break;

	    case RefXmString:
	    case RefString: 
            { 
                char *str = (char *)src_resource; 
                if (str != NULL) { 
                    dst_resource = (MvsArgVal)XtMalloc(strlen(str)+1);
                    strcpy((char *)dst_resource,str); 
                } 
                else dst_resource = 0L; 
                break; 	 
            }

	    case RefCallbackList: 	 
            { 
                XtCallbackList cb_list = (XtCallbackList)src_resource; 
                int j=0; 
                if (cb_list != NULL) { 
                    while (cb_list->callback != NULL) { 
                        cb_list++; j++; 
                    } 
                    cb_list = (XtCallbackList)src_resource; 
                    dst_resource = (MvsArgVal)XtMalloc(sizeof(XtCallbackRec)*(j+1));
                    memcpy((char *)dst_resource,cb_list,sizeof(XtCallbackRec)*(j+1));
                }
                else dst_resource = 0L;
                break;
   	    } 

	    default: 
                dst_resource = src_resource; 
                msg_error("bad resource type code=%d in mvsCopyResource\n",
                          mvsTypeInfo[resource_info[i].type_code].ref_type);
                break;
    }

    return (dst_resource);
} /* End mvsCopyResource() */


/*************************************************************************
*  This function copies all resources. The entire list of resources is   *
* looped through and each resource is copied using mvsCopyResource().    *
*************************************************************************/
void mvsCopyResources(widget_class_info, dst_resource,src_resource)
MvsWidgetClassInfo *widget_class_info;
MvsArgVal dst_resource[],
src_resource[]; 
{ 
    int i;

    for (i=0; i<widget_class_info->num_resources; i++)
        dst_resource[i] = mvsCopyResource(widget_class_info, src_resource[i],i);

} /* End mvsCopyResource() */

