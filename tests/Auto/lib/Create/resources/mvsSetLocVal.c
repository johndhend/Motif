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
static char rcsid[] = "$XConsortium: mvsSetLocVal.c /main/8 1995/07/14 11:22:30 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsSetLocVal.c	1.10.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   05/29/90 SJS add chanegs for composites
	   07/11/90 SJS handle XmStrings properly
	   08/01/90 SJS correct free/extract logic of XmString case
	Calls:

	Summary:
		This function sets the local copy of the resource values.
	These are what the MVS thinks the widget resource values should be.
	For pointer resources, memory is allocated and structures copied.
************************************************************************/
#include "mvslib.h"
#include <AutoMessages.h>

void mvsSetLocalValues(widget_info, args, nargs)
MvsWidgetInfoRecord *widget_info;
ArgList args;
Cardinal *nargs;
{
    int i,j,k;
    short num_resources;
    MvsResourceInfoRecord *resource_info;
    MvsArgVal *mvs_resources;
    char msg_string[125];

    num_resources = widget_info->widget_class_info->num_resources;
    resource_info = widget_info->widget_class_info->resource_info;
    mvs_resources = widget_info->mvs_resources;

    for (i=0; i<*nargs; i++) {
        for (j=0;
             (j<num_resources)&&strcmp(args[i].name,resource_info[j].name);j++);
        if (j >= num_resources)
		;
        else {
            switch (mvsTypeInfo[resource_info[j].type_code].ref_type) {
                case RefXmStringTable: /* For now until decided how to handle */
	        case RefBoolean:
	        case RefValue:
                case RefGeneric:
                    if (((resource_info[j].type_code == T_Pixel ||
                        resource_info[j].type_code == T_Pixmap  )) &&
			(mvsGetVisualMode() == VISUAL_MODE_GENERATE_PIXMAPS)) {
                     /*       if (resource_info[j].type_code == T_Pixel)
                                mvsFreeColor(args[i].value); */
                            for (k=i; k<(*nargs-1); k++) {
                                args[k].name = args[k+1].name;
                                args[k].value = args[k+1].value;
                            }
                            (*nargs)--;
                    }
		    else
			mvs_resources[j] = (MvsArgVal)args[i].value;
                    break;
   
                case RefXmString:
                    if((char *)mvs_resources[j] != (char *)NULL) {
                        XtFree( (char *)mvs_resources[j]);
                    }
                    mvs_resources[j] = (MvsArgVal)
                                      mvsExtractString((XmString)args[i].value,
                                                       args[i].name);
                    break;

	        case RefString:
                    if(mvs_resources[j]) {
                        XtFree((char *)(mvs_resources[j]));
			mvs_resources[j] = 0L;
		    }

                    if (args[i].value) {
                        mvs_resources[j] = (MvsArgVal)XtMalloc(
					       strlen((char *)args[i].value)+1);
                        strcpy((char *)mvs_resources[j],(char *)args[i].value);
                    }
                    else mvs_resources[j] = 0L;
                    break;

	        case RefCallbackList:
		{
                    XtCallbackList cb_list = (XtCallbackList)args[i].value;
                    int k=0;

                    if(mvs_resources[j]) {
                        XtFree((char *)(mvs_resources[j]));
			mvs_resources[j] = 0L;
		    }

                    if (cb_list != NULL) {
                        while (cb_list->callback != NULL) {
                            cb_list++;
                            k++;
                        }
                        cb_list = (XtCallbackList)args[i].value;

                        mvs_resources[j] = (MvsArgVal)XtMalloc(sizeof(XtCallbackRec)*(k+1));
                        memcpy((char *)mvs_resources[j],(char *)cb_list,
                               sizeof(XtCallbackRec)*(k+1));
                    }
                    else mvs_resources[j] = 0L;

                    /*** remove callback from list *****/

                    for (k=i; k<*nargs-1; k++) {
                        args[k].name = args[k+1].name;
                        args[k].value = args[k+1].value;
                    }

                    break;
		}

	        default:
		   sprintf(msg_string, _AutoMessages[WARNMSG119], 
			   mvsTypeInfo[resource_info[j].type_code].ref_type);
                   AutoMessage(msg_string);
                             
                   break;
	    }
	}
    }
    mvsSetLocalConstraints(widget_info,mvs_resources,args, *nargs);

} /* End mvsSetLocalValues() */
