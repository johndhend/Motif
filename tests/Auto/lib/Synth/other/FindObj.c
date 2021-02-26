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
static char rcsid[] = "$XConsortium: FindObj.c /main/7 1995/07/14 11:32:53 drk $"
#endif
#endif
/***********************************************************************
  	@(#)FindObj.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
            08/04/90 SJS let's try some comments
	Calls:

	Summary:
            Looks up the object that matches the object type and instance.
        This object is relative to the widget passed in.

        INPUTS
            widget - Xt widget of matching object
            object_type - may be concatenated object type code
            instance - instance of this object_type

        OUTPUTS
            none

        RETURNS
            Pointer to object which matches given window id
************************************************************************/
#include "xislib.h"
#include "mvslib.h"

XisObjectRecord *xisFindObject(widget,object_type,instance)
Widget widget;
int object_type;
int instance;
{
    XisObjectRecord *object, *tmp_object;
    XisObjectRecord *object_stack[100];
    Boolean in_dir_file_list = False;
    short stack_top = 0;
    int object_type_stack[100];
    int ostack_top = 0;
    int cum_object_type = object_type;
    int tmp, tindx;
    int widget_class_code;


    /* Break up concatenated object. The concatenation is originally done
       by adding together all the object types that describe the object
       we want. (ie. ScrollBar + UpOrLeftRegion). Thus, each piece of
       the sum is taken off and put on the type stack.
    */

    while (cum_object_type > 0) {
        tmp = cum_object_type / xisNumObjectTypes;
        object_type_stack[ostack_top++] =
                                    cum_object_type - tmp * xisNumObjectTypes;
        cum_object_type = tmp;
    }

    /* Find top object with same widget. Use the requested widget as the
       base point to begin searching.
    */

    object = xisFindObjectFromWidget(widget);

    if ((object_type == 0) || (object == NULL)) {
        return(object);
    }

/* Begin Automation Added */

    widget_class_code  = mvsGetClassCode(widget);

/* End Automation Added */

    /* If the object we are looking for is the current one, return it */

    if (object->id.object_type == object_type) {
        if (object->id.instance == instance)
            return(object);
    }

    /* If the current is not the object and there are no children, then
       return NULL */

    if (object->first_child == NULL) {
        return(NULL_Object);
    }

    /* Perform Depth-First Search Looking for a match to object-instance */
    tindx = ostack_top - 1;
    object = object->first_child;

    while (1) {
        if (object->id.object_type == object_type_stack[tindx]) {
            if (tindx == 0) {
                if (object->id.instance == instance)
                    return object;
            }
/* Begin Automation Added */

/* 
   This is an ugly hack. Basically what is up is that a oFileList and
   a oDirList are children of the ScrolledWindow, and not of the
   FileSelectionBox. Beacuse of this when accessing the scrollbar
   regions, they have to be children of the ScrolledWindow not the
   FileSelectionBox. Since FileSelectionBox has two ScrolledWindows
   (and ScrolledLists) there was no way to find out if you were
   looking at the DirList scrollbar regions or the FileList scrollbar
   regions.

   Fix is to look to see if you are in a scrolledWindow. Then see
   if a FileList or a DirList is a child of the ScrolledWindow,
   if it is then adjust the object_type_stack and look at the rest
   of the children.

*/
	    if (object->id.object_type == oScrolledWindow &&
		object_type != oFileListItem &&
		object_type != oDirListItem &&
		object_type != oFileList1 &&
		object_type != oDirList1 &&
		widget_class_code == mvsXmFileSelectionBoxWidgetClass) {
	        tmp_object = object->first_child;

/* 
   Look down the scrolledWindow childrens list to see if you have a
   directory list or filelist  object code 
*/

		while (tmp_object != NULL && ! in_dir_file_list)
			if (tmp_object->id.object_type == 
			    		object_type_stack[tindx - 1])
			    in_dir_file_list = True;
			else
				tmp_object = tmp_object->next_sibling;

/* 
   If you have the dirlist of filelist then adjust the object_type
   stack. This will have the effect of ignoring the filelist or
   dirlist and continue looking down the scrolledWindows children
   list 
*/
		if (in_dir_file_list)
			tindx--;
	    }
/* End Automation Added */
            if (object->first_child != NULL) {
                object_stack[stack_top++] = object;
                object = object->first_child;
                tindx--;
                continue;
            }
        }
        if (object->next_sibling != NULL) {
            object = object->next_sibling;
	}
        else {
            object = NULL;
            while (stack_top > 0 && object == NULL) {
                object = object_stack[--stack_top]->next_sibling;
                tindx++;
	    }
            if (object == NULL)
                break;
        }       
    } /* End while(1) */

    return(NULL_Object);

} /* End xisFindObject */
