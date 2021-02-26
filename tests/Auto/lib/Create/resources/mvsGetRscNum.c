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
static char rcsid[] = "$XConsortium: mvsGetRscNum.c /main/7 1995/07/14 11:21:14 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsGetRscNum.c	1.7.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   05/29/90 SJS Changes for composites
	   06/15/90 PSN add function to get index of given resnam from given 
			args array.
	   09/20/90 SJS use constant NON_EXISTENT
	Calls:

	Summary:
		This function returns the index number of a resource
	within the resource_info structure. A value of "NON_EXISTENT"
        (currently -1) is returned if the requested resource name was
        not located.
************************************************************************/

#include "mvslib.h"

int mvsGetResourceNum(widget_class_info, resource_name)
MvsWidgetClassInfo *widget_class_info;
char resource_name[];
{
    int j;
    short num_resources;
    MvsResourceInfoRecord *resource_info;

    num_resources = widget_class_info->num_resources;
    resource_info = widget_class_info->resource_info;

    for (j=0;
         (j<num_resources)&&strcmp(resource_name,resource_info[j].name); j++);

    return (j<num_resources ? j : (NON_EXISTENT));
        
} /* End mvsGetResourceNum() */

int mvsGetResNumInArgs(args, nargs, resource_name)
Arg	args[];
int	nargs;
char	resource_name[];
{
    int j;

    for ( j=0 ; (j<nargs)&&strcmp(resource_name,args[j].name) ; j++ )
	;

    return (j<nargs ? j : (-1));
        
} /* End mvsGetResNumInArgs() */
