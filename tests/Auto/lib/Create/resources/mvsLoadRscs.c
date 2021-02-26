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
static char rcsid[] = "$XConsortium: mvsLoadRscs.c /main/7 1995/07/14 11:21:50 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsLoadRscs.c	1.11.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   05/29/90 SJS add changes for composites
	   07/11/90 SJS make XmStrings be stored internally as regular strings
	   07/12/90 PSN add singular load resource function all other functions
  		  	here are rearranged to use same function common*
	Calls:

	Summary:
		This function loads the real values of the widget
	resources. It also copies the information pointed to by those
	resources that are pointers.
************************************************************************/
#include <AutoMessages.h>
#include "mvslib.h"

void commonLoadResources(widget_info, resources, num_resources, resource_info) 
MvsWidgetInfoRecord  *widget_info; 
MvsArgVal resources[];
int num_resources;
MvsResourceInfoRecord *resource_info;
{ 
    Arg args[MAX_RESOURCES];
    Widget widget;
    int i,j;
    char msg_string[125];

    widget = widget_info->widget;

    if (XtIsManaged(widget))  {

    	for (i=0, j=0; i<num_resources; i++) {
		if(resource_info[i].access & GET) {
       	    		XtSetArg(args[j],resource_info[i].name,&resources[i]);
	   		j++;
		}
    	}

    	XtGetValues(widget,args,j);

    	for (i=0; i<num_resources; i++) 
        	resources[i] =
		      mvsConvertToType(resources[i],resource_info[i].type_code);

    	for (i=0; i<num_resources; i++) {

        	switch (mvsTypeInfo[resource_info[i].type_code].ref_type) {

            	case RefXmStringTable: /* Here until handling of compound string
                                      tables is determined */
	    	case RefValue: 	 
            	case RefGeneric:
            	case RefBoolean: 
	    	case RefString: 
               		 /* Do nothing since it already copied the value */ 
                break;

	    	case RefXmString:
                	if ((XmString)resources[i] != (XmString)NULL) {
                    		XmString save_str = (XmString)resources[i];

                    		resources[i] = (MvsArgVal)
                              	        mvsExtractString((XmString)resources[i],
                                                         resource_info[i].name);
				XmStringFree(save_str);
                	}
                	break;

	    	case RefCallbackList:
                	if (resources[i]) 	/* MEMLEAK fix */
				XtFree( (char *)(resources[i]));
                	resources[i] = 0; /* can't get this resource this way */
                	break;

	    	default: 
		        sprintf (msg_string, _AutoMessages[WARNMSG117], 
			    mvsTypeInfo[resource_info[i].type_code].ref_type); 
                	AutoMessage(msg_string);
                             
                	break; 	
        	} 
    	}  /* End for(i<num_resources) */
    }

} /* End commonLoadResources() */


/***********************************************************************
  	Author: PSN
	History:
	   07/12/90 PSN add singular load resource function all other
                        functions here are rearranged to use same
                        function common
	Calls:

	Summary:
 	    Make mvsLoadResources() do the right thing
***********************************************************************/

void mvsLoadResources(widget_info, resources) 
MvsWidgetInfoRecord  *widget_info; 
MvsArgVal resources[];
{ 
    int num_resources;
    MvsResourceInfoRecord *resource_info;

    num_resources = (int)widget_info->widget_class_info->num_resources;
    resource_info = widget_info->widget_class_info->resource_info;

    commonLoadResources(widget_info, resources, num_resources, resource_info);

} /* End mvsLoadResources() */


/***********************************************************************
  	Author: PSN
	History:
	   07/12/90 PSN add singular load resource function all other
                        functions here are rearranged to use same
                        function common
	Summary:
	    Singular mvsLoadResource() loads only one resource specified
        by res_name. Also, returns that value to the caller
***********************************************************************/

MvsArgVal mvsLoadResource(widget_info, res_name)
MvsWidgetInfoRecord  	*widget_info; 
char			res_name[];
{ 
    int 	res_index;
    MvsArgVal	resource;
    MvsResourceInfoRecord *resource_info;
    char msg_string[125];

    res_index = mvsGetResourceNum(widget_info->widget_class_info, res_name);
    if(res_index == -1) {
        sprintf (msg_string, _AutoMessages[WARNMSG117], res_name);
        AutoMessage(msg_string);
	return (MvsArgVal)(-1);	/* Don't know what to return */
    }

    resource_info = &(widget_info->widget_class_info->resource_info[res_index]);

    commonLoadResources(widget_info, &resource, (int)1, resource_info);

    return (resource); 	/* WARNING: since commonLoadResources() does */
			/* not return error code on failure this will */
			/* return unspecified value!? */ 

} /* End mvsLoadResource() */
