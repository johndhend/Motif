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
static char rcsid[] = "$XConsortium: mvsCpRep1Arg.c /main/7 1995/07/14 11:19:44 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsCpRep1Arg.c	1.8.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   07/31/90 SJS match index with resource by look up
	   08/01/90 SJS our internal XmStrings are regular strings and
                        XmStrings in Arg lists are *really* XmStrings
	   09/20/90 SJS use define for NON_EXISTENT
	Calls:

	Summary:
		This function places 1 argument into the args array
	used in XtSetValues() calls. If the named resource exists in
	the array, the new value replaces the old value. If the named
	resource is new, then it is added to the end of the list.
		Any resource that is replaced is appropriately freed.
	The argument being added to the list is copied into place and
	should be freed later.
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

void mvsCopyReplace1Arg(w_class_info, orig_args, orig_argcnt, new_arg_name,
			new_arg_value)
MvsWidgetClassInfo	*w_class_info;
Arg 			orig_args[];
int 			*orig_argcnt;
char 			new_arg_name[];
MvsArgVal 		new_arg_value;
{
    register int j;
    register int index;
    char msg_string[125];

    for (j=0; (j<*orig_argcnt) && strcmp(new_arg_name,orig_args[j].name); j++)
        ;

    if (j < *orig_argcnt) {
	mvsFreeResource(w_class_info, &(orig_args[j].value), 
		    mvsGetResourceNum(w_class_info, orig_args[j].name));
    }

    index = mvsGetResourceNum(w_class_info, new_arg_name);
    if(index != NON_EXISTENT) {

        /* XmStrings in Arg lists are XmStrings and needed to be treated
           as such. We can not call mvsCopyResource() because it is
           copying "internal" resources. XmStrings are represented as regular
           strings in mvs resources and are thus not valid for an Arg
           list.
        */
        if(w_class_info->resource_info[index].type_code != T_XmString) {
            XtSetArg(orig_args[j], new_arg_name,
                     mvsCopyResource(w_class_info, new_arg_value, index));
        }
        else {
            XtSetArg(orig_args[j], new_arg_name, 0); /* just fill in name */
            orig_args[j].value =
                               (MvsArgVal)XmStringCopy((XmString)new_arg_value);
        }

        if (j == *orig_argcnt) {
            (*orig_argcnt)++;
        }
    }
    else {
        sprintf (msg_string, _AutoMessages[WARNMSG66], new_arg_name);
	AutoMessage(msg_string);
    }

} /* End mvsCopyReplace1Arg() */
