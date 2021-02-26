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
static char rcsid[] = "$XConsortium: InitRootInfo.c /main/7 1995/07/14 11:16:55 drk $"
#endif
#endif
/***********************************************************************
        @(#)InitRootInfo.c	1.3.1.1     Date:1/22/91
  	Author: TAT
	History:
	   05/14/90 TAT Create
	Calls:

	Summary:
		This functions initializes the Root widget Info
                record. 
************************************************************************/

#define DECLARE_MVSLIB_GLOBALS_HERE 
#include "mvslib.h"

MvsWidgetInfoRecord *mvsInitRootWidgetInfo()
{
    static MvsWidgetClassInfo rootWidgetClassInfo = { 0 };

    mvsNumWidgetInfos = 1;

    mvsWidgetInfos[0].in_use = 1;
    mvsWidgetInfos[0].widget_class_info = (&rootWidgetClassInfo);
    mvsWidgetInfos[0].widget_class_info->proc_SetExpectedActions = NULL;
    mvsWidgetInfos[0].widget_class_info->proc_CreateWidget = NULL;
    mvsWidgetInfos[0].widget_class_info->proc_TestBehavior = NULL;
    mvsWidgetInfos[0].widget_class_info->resource_info = NULL;
    mvsWidgetInfos[0].first_child = NULL;
    mvsWidgetInfos[0].next_sibling = NULL;
    mvsWidgetInfos[0].parent = NULL;
    mvsWidgetInfos[0].widget = NULL;

    return (&mvsWidgetInfos[0]);

} /* End mvsInitRootInfo() */
