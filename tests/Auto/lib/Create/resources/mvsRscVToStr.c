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
static char rcsid[] = "$XConsortium: mvsRscVToStr.c /main/7 1995/07/14 11:22:00 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsRscVToStr.c	1.8.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   05/29/90 SJS composite changes
	   07/13/90 SJS change for XmStrings
	   10/16/90 SJS add XmStrings
	Calls:

	Summary:
		This function takes a value and converts it to a
	printable string based on the type of the resource associated
	with this particular value. "i" is an index into the resource_info
	array which contains the type code for the value being
	converted.
************************************************************************/

#include <AutoMessages.h>
#include <stdio.h>
#include "mvslib.h"

char *mvsResourceValueToString(widget_class_info, i ,value)
MvsWidgetClassInfo *widget_class_info;
int i;
MvsArgVal value;
{
    static char str[MAX_STRING_LENGTH];
    char *tmp_str;
    char msg_string[125];
    int t;

    t = widget_class_info->resource_info[i].type_code;
    switch (mvsTypeInfo[t].ref_type) {

    case RefBoolean:
        if (value)
            sprintf(str,"True");
        else
            sprintf(str,"False");
        break;

    case RefValue:
        sprintf(str,"%ld",value);
        break;

    case RefGeneric:
        sprintf(str,"%lx",value);
        break;
		    
    case RefXmString:
        tmp_str = mvsExtractString((XmString)value,
                                   widget_class_info->resource_info[i].name);
        sprintf(str,"%s", tmp_str);
        XtFree(tmp_str);
        break;
		    
    case RefString:
        sprintf(str,"%s", (char *)value);
        break;
		    
    case RefXmStringTable: /* until we know how to handle these */
        sprintf(str,"%ld",value);
        break;
		    
    case RefCallbackList:
        {
            XtCallbackList cb_list = (XtCallbackList)value;
            int k=0; 
 
            if (cb_list != NULL) {
                while (cb_list->callback != NULL) {
                    cb_list++;
                    k++;
	        }
            }
        sprintf(str,"%d callbacks",k);
	}
        break;
		    
    default:
	sprintf (msg_string,_AutoMessages[WARNMSG78],mvsTypeInfo[t].ref_type);
        AutoMessage(msg_string);
                  
        sprintf(str,"%ld",value);
        break; 
    }
    return str;

} /* End mvsResourceValueToString() */
