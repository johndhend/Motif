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
static char rcsid[] = "$XConsortium: GetObjName.c /main/7 1995/07/14 11:34:44 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetObjName.c	1.3.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Returns a pointer to a statically declared string naming the
        specified object.

        INPUTS:
            object     - object pointer
        
        OUTPUTS:
            none

        RETURNS:
            string object name
************************************************************************/
#include "xislib.h"

char *xisGetObjectName(object)
XisObjectRecord *object;
{
    static char name[255];
    static char other_string[] = "Other";
    static char root_string[] = "Root Window";
    static char sync_string[] = "Sync Window";
    static char empty_string[] = "Windowless,Widgetless";

    if (object == NULL)
        return other_string;

    if (object->id.widget != NULL) {
        sprintf(name,"%s #%d %s of class %s",
                    (*xisGetObjectTypeName)(object->id.object_type),
                    object->id.instance,
                    XtName(object->id.widget),
                    (*xisGetWidgetClassName)(object->id.widget));

        return name;
    }

    else {
        if (!object->id.window)
            return empty_string;

        else {
            if (object->id.window == xisRootWindow)
                return root_string;
            else if (object->id.window == xisSyncWindow)
                return sync_string;
            else
                return other_string;
        }
    }

} /* End xisGetObjectName() */
