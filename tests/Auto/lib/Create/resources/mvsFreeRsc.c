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
static char rcsid[] = "$XConsortium: mvsFreeRsc.c /main/7 1995/07/14 11:20:26 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsFreeRsc.c	1.6.1.1	Date:1/22/91
  	Author: TAT
	History:
	   05/29/90 SJS Add to sccs tree
	   07/12/90 SJS free XmString type. These were XtMalloc'd upon
                        creation or loading
	   07/29/90 PSN do not do XtGetValues() for callbacks
	Calls:

	Summary:
		This function frees up all the resources associated with
	the current widget state. Only the resources which are pointers
	require any processing. The memory pointed to by the resources
	must be freed because it is dynamically allocated as each new
	widget state is entered.
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

void mvsFreeResource(widget_class_info, presource, i)
MvsWidgetClassInfo *widget_class_info;
MvsArgVal *presource;
int i;
{
    MvsResourceInfoRecord *resource_info;
    char msg_string[125];

    resource_info = widget_class_info->resource_info;

    switch (mvsTypeInfo[resource_info[i].type_code].ref_type) {

        case RefXmStringTable:  /* Here until handling of compound strings */
                                /* is determined */

	case RefValue:
        case RefGeneric:
        case RefBoolean:
	    if (presource)
	    	*presource = 0L;
            break;

	case RefXmString:     
	case RefString:
	case RefCallbackList:
            if (presource && *presource) {
                XtFree( (char *)(*presource));
	        *presource = 0L;
	    }
            break;

	default:
	    sprintf(msg_string,_AutoMessages[WARNMSG68], 
		    mvsTypeInfo[resource_info[i].type_code].ref_type);
            AutoMessage(msg_string);
                       
            break;
    }

} /* End mvsFreeResource() */

/***********************************************************************
  	Author: PSN
	History:

	Calls:

	Summary:
		This function frees up the memory associated with
	the current args array's value field depending on the type of
	resource it contains. 
************************************************************************/
void mvsFreeArgs(widget_class_info, args, nargs)
MvsWidgetClassInfo	*widget_class_info;
Arg			*args;
Cardinal		nargs;
{
    register int	i, j;
    register num_res = widget_class_info->num_resources;
    MvsResourceInfoRecord *res_info = widget_class_info->resource_info;

    for (i=0; i<nargs; i++) {
	if (args[i].name == NULL) continue;
	else for ( j=0; j<num_res; j++) {
	    if (!strcmp(args[i].name, res_info[j].name)) break;
	}

        if (j >= num_res)
		;
        else if (args[i].value)
            mvsFreeResource(widget_class_info, &(args[i].value), j);
    }
}
