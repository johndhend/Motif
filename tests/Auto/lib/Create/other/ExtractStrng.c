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
static char rcsid[] = "$XConsortium: ExtractStrng.c /main/7 1995/07/14 11:15:34 drk $"
#endif
#endif
/***********************************************************************
  	@(#)ExtractStrng.c	1.7.1.2     Date:2/7/91
  	Author: SJS
	History:
            07/10/90 SJS Create
            07/12/90 SJS do proper malloc
            10/17/90 SJS check for NULL coming in
	Calls:

	Summary:
            This function extracts the "real" string out of an XmString.
        All the segments obtained are concatenated together into a single
        string. The required memory is allocated by this function
************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

char *mvsExtractString(in_string, resource_name)
XmString in_string;
char *resource_name;
{
    XmStringContext context;
    XmStringCharSet charset;
    XmStringDirection direction;
    Boolean separator;
    int length=1;                 /* Init to 1 to count Null char */
    char *string;
    char real_string[MAX_STRING_LENGTH];
    char msg_string[100];

    if (in_string == (XmString)NULL) {
        return((char *)NULL);
    }

    if (!XmStringInitContext(&context,(XmString)in_string)) {
        sprintf (msg_string, _AutoMessages[WARNMSG23], resource_name);
	AutoMessage(msg_string);
	
#define EXTRACT_STRING_ERROR_MESS "ERROR"

        string = XtMalloc(sizeof(EXTRACT_STRING_ERROR_MESS)+1) ;
        strcpy(string,EXTRACT_STRING_ERROR_MESS) ;
        return(string);
    }
    else {
        real_string[0] = '\0';
        while (XmStringGetNextSegment(context,&string,&charset, &direction,
                                      &separator)) {
            length += strlen(string);
            if (length > MAX_STRING_LENGTH) {
	    /*
	       sprintf (msg_string, _AutoMessages[WARNMSG24], resource_name, 
	                                   length - strlen(string));

	       AutoMessage (msg_string);

	    */
                break;
            }
            strcat(real_string,string);
            XtFree((char *)string);
            XtFree((char *)charset);
        }

        /* use string to save the pointer from alloc'ing space */
        string = XtMalloc(strlen(real_string)+1);
        strcpy(string, real_string);
        XmStringFreeContext(context);

        return( string);
    }

} /* End mvsExtractString() */







