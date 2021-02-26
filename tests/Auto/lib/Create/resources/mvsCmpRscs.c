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
static char rcsid[] = "$XConsortium: mvsCmpRscs.c /main/7 1995/07/14 11:19:20 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsCmpRscs.c	1.20.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to the sccs tree
	   04/13/90 SJS change msg_error to msg_failure for future
	                addition of Assertions.
	   05/29/90 SJS changes for composites
	   06/11/90 SJS add compare for XmStrings
	   06/26/90 SJS can not check any callbacks at all (damn it)
	   07/11/90 SJS XmStrings are internally justy strings, compare them
                        like Strings
	   07/29/90 PSN initialize args, parameter changes
	   09/04/90 SJS check for gettability
	   11/12/90 PSN don't print addresses (RefGeneric) on failed 
			comparisons & also number failures.
	Calls:

	Summary:
		This function compares a set of resource values with the
	values contained in the current widget. Comparisons are done
	according to the type of the resource. (For example, in comparing
	strings, the contents of the string pointers are compared, NOT the
	pointers themselves.)

************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

void mvsCompareResources(widget_info)
MvsWidgetInfoRecord *widget_info;
{
    MvsArgVal resources2[MAX_RESOURCES];
    MvsArgVal *resources;
    Widget widget;
    MvsResourceInfoRecord *resource_info;
    short num_resources;
    int i;
    char msg_string[100];

    resources = widget_info->mvs_resources;
    num_resources = widget_info->widget_class_info->num_resources;
    resource_info = widget_info->widget_class_info->resource_info;

    for (i=0; i<MAX_RESOURCES; i++) resources2[i] = NULL;

    mvsLoadResources(widget_info,resources2);

    for (i=0; i<num_resources; i++) {
        if(!(resource_info[i].access & GET)) {
            continue;
        }
        switch (mvsTypeInfo[resource_info[i].type_code].ref_type) {
            case RefXmStringTable: /* Do nothing for now */
                break;

	    case RefBoolean:
                if ( ((resources[i] == 0)&&(resources2[i] != 0)) ||
                     ((resources[i] != 0)&&(resources2[i] == 0)) ) {
                    msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected %d, received %d\n",
                       i, resource_info[i].name,resources[i], resources2[i]);
                    resources[i] = resources2[i];
                }
                break;

	    case RefValue:
                if (resources[i] != resources2[i]) {
                    msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected %d, received %d\n",
                       i, resource_info[i].name,resources[i], resources2[i]);
                    resources[i] = resources2[i];
                }
                break;

            case RefGeneric:
                if (resources[i] != resources2[i]) {
                    msg_failure("1000.%d: Resource 'XmN%s' mismatch.\n", i,
				resource_info[i].name); /* Don't print addresses */
                    resources[i] = resources2[i];
                }
		break;

            case RefXmString: /* XmStrings loaded & stored internally as
                                 "normal" strings */
	    case RefString:
                if (resources[i] == NULL)
                    if (resources2[i] != NULL) {
                        if (strcmp(resources2[i],"") != 0) {
                            msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected NULL, received '%s'\n",
                                        i, resource_info[i].name,resources2[i]);
                            resources[i] =
                                 mvsCopyResource(widget_info->widget_class_info,
                                                 resources2[i],i);
                        }
		    }
                    else
                        /* do nothing since both are NULL */;
                else 
                    if (resources2[i] == NULL) {
                        if (strcmp(resources[i],"") != 0) {
                            msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected '%s', received NULL\n",
                                        i, resource_info[i].name,resources[i]);
                            resources[i] =
                                 mvsCopyResource(widget_info->widget_class_info,
                                                 resources2[i],i);
                        }
                    }
                    else { /* both are non-null */
                        if (strcmp(resources[i],resources2[i]) != 0) {
                            msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected '%s' received '%s'\n",
                                        i, resource_info[i].name,
                                        resources[i],resources2[i]);
                            resources[i] =
                                 mvsCopyResource(widget_info->widget_class_info,
                                                 resources2[i],i);
                        }
                    }
                break; 

            case RefCallbackList:
                widget = widget_info->widget;
                if ((resources[i] == NULL) ||
                    (((XtCallbackRec *)resources[i])->callback == NULL))
            /** cannot do this check since Xt & Xm put funcs on cb list --    **/
            /**                                                               **/
            /**     if(XtHasCallbacks(widget,resource_info[i].name) !=        **/
            /**                                         XtCallbackHasNone)    **/
            /**        msg_failure("Resource 'XmN%s' mismatch: expected empty **/
            /**               callback list, received non-empty status\n",    **/
            /**               resource_info[i].name);                         **/
            /**     else                                                      **/
                        /* do nothing since both are NULL */;
                else { 
                    if(XtHasCallbacks(widget,resource_info[i].name) !=
                                                            XtCallbackHasSome)
                        msg_failure("1000.%d: Resource 'XmN%s' mismatch:\n\t\texpected non-empy callback list, received empty list\n",
                            i, resource_info[i].name);
                    else { /* both are non-null, test check sum if available */
                        if (mvsCallbackEnum >= 0) {
                            mvsCallbackSum = 0;
            /** cannot do this check since Xt & Xm put funcs on cb list -- **/
            /**                                                            **/
            /**           XtCallCallbacks(widget,resource_info[i].name,0); **/
            /**if (mvsCallbackSum != mvsCallbacksCheckSum[mvsCallbackEnum])**/
            /**    msg_failure("Resource 'XmN%s' mismatch: enumerated      **/
            /**                callback list #%d differs\n",               **/
            /**                resource_info[i].name,mvsCallbackEnum);     **/
                        }
		    }
		}
                break;

	    default:
		sprintf (msg_string, _AutoMessages[WARNMSG64]), 
		         mvsTypeInfo[resource_info[i].type_code].ref_type);
                AutoMessage(msg_string);
                          
	 }
    } /* End for(i<num_resources) */
    mvsFreeResources(widget_info->widget_class_info, resources2);    

} /* End mvsCompareResources() */
