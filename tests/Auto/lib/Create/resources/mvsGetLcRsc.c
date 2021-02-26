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
static char rcsid[] = "$XConsortium: mvsGetLcRsc.c /main/7 1995/07/14 11:21:03 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsGetLcRsc.c	1.8.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   05/29/90 SJS add composite changes
	   07/10/90 PSN Add new function mvsGetParentResource()
	Calls:

	Summary
		This function obtains the value of a resource according
	to what MVS believes it currently to be. This may be different
	than what is really true.
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

MvsArgVal mvsGetLocalResource(widget_info, resource_name)
MvsWidgetInfoRecord *widget_info;
char resource_name[];
{
    int i;
    short num_resources;
    MvsResourceInfoRecord *resource_info;
    char msg_string[125];

    num_resources = widget_info->widget_class_info->num_resources;
    resource_info = widget_info->widget_class_info->resource_info;

    for(i=0;(i<num_resources)&&strcmp(resource_name,resource_info[i].name);i++);

    if (i >= num_resources) {
        sprintf(msg_string, _AutoMessages[WARNMSG116], resource_name);
	AutoMessage (msg_string);
        return(0);
    }
    return( widget_info->mvs_resources[i] );        

} /* End mvsGetLocalResource() */


/************************************************************************
        mvsGetParentResource()	Date:1/22/91
  	Author: PSN
	History:
	   07/10/90 PSN Add new function mvsGetParentResource()
	Calls:

	Summary:
           Gets the resource specified from the parent of the current
        widget info. Returns zero on failure
************************************************************************/

MvsArgVal mvsGetParentResource(widget_info, resource_name)
MvsWidgetInfoRecord *widget_info;
char resource_name[];
{
    MvsWidgetInfoRecord *pwidget_info = widget_info->parent;
    char msg_string[125];

    if (pwidget_info == NULL) {
        sprintf (msg_string, _AutoMessages[WARNMSG70], resource_name);
	AutoMessage(msg_string);
        return(0);
    }

    return( mvsGetLocalResource(pwidget_info, resource_name) );

} /* End mvsGetParentResource() */
