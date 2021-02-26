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
static char rcsid[] = "$XConsortium: FindCorrRsc.c /main/7 1995/07/14 11:44:44 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FindCorrRsc.c	1.7.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/29/90 SJS add to sccs
	Calls:

	Summary:
            This function locates the resource that corresponds to the
        resource that is refered to by index i in the widget's
        resource_info array.

	The index of the corresponding resource in the resource_info 
        array is returned if found. Otherwise, return (-1)
************************************************************************/
#include "vislib.h"

int mvsFindCorrespondingResource(widget_class_info, i, remove_str, add_str)
MvsWidgetClassInfo *widget_class_info;
int i;
char remove_str[], add_str[];
{
    int k;
    char name[MAX_RESOURCE_NAME_LENGTH];
    MvsResourceInfoRecord *resource_info;
    int name_length,remove_length;

    resource_info = widget_class_info->resource_info;
    name_length = strlen(resource_info[i].name);
    remove_length = strlen(remove_str);

    /* Grab root resource name (without suffix) */
    k = name_length - remove_length;
    if (strcmp(&resource_info[i].name[k],remove_str) != 0) {
        msg_warning("mvsFindCorrespondinResource():Remove_string '%s' not found in '%s'\n",
                    remove_str,resource_info[i].name);
        k = name_length;
    }
    strncpy(name,resource_info[i].name,k);
    name[k] = '\0';

    /* Instead, concatenate add_str */
    strcat(name,add_str);

    /* Find this resource number */
    return( mvsGetResourceNum(widget_class_info, name));

} /* End mvsFindCorrespondingResource() */
