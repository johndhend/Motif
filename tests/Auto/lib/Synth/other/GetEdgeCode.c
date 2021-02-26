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
static char rcsid[] = "$XConsortium: GetEdgeCode.c /main/7 1995/07/14 11:33:58 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetEdgeCode.c	1.3.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Return either TopEdge, BottomEdge, LeftEdge, or RightEdge to
        satisfy the definition of xisInform.edge_code (see xislib.h).  This
        field refers to the edge of the rectangular object that caused a
        pointer Enter or Leave event to occur.

        INPUTS:
            object - pointer to object record
            old_x
            old_y
            new_x
            new_y

        OUTPUTS:
            none

        RETURNS:
            TopEdge, BottomEdge, LeftEdge, or RightEdge
************************************************************************/
#include "xislib.h"

int xisGetEdgeCode(object,old_x,old_y,new_x,new_y)
XisObjectRecord *object;
int old_x,old_y;
int new_x,new_y;
{
    int itmp;

    if ( (old_x < object->x && new_x >= object->x)||
         (old_x >= object->x && new_x < object->x)  )
        return LeftEdge;

    else if ( (old_x >= (itmp = object->x + object->width) && new_x < itmp) ||
              (old_x < itmp && new_x >= itmp) )
        return RightEdge;

    else if ( (old_y < object->y && new_y >= object->y) ||
              (old_y >= object->y && new_y < object->y)   )
        return TopEdge;

    else if ( (old_y >= (itmp = object->y + object->width) && new_y < itmp) ||
              (old_y < itmp && new_y >= itmp) )
        return BottomEdge;

    else
        return UndefinedEdge;

} /* End xisGetEdgeCode() */
