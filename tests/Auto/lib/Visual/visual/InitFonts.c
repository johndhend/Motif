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
static char rcsid[] = "$XConsortium: InitFonts.c /main/7 1995/07/14 11:50:52 drk $"
#endif
#endif
/***********************************************************************
  	@(#)InitFonts.c	1.9.1.1	Date:1/22/91
  	Author: TAT
	History:
            06/13/90 SJS init font_list struct
            08/28/90 SJS make non-existance of fonts an error condition
	Calls:

	Summary:
            This function initializes the font_info array and mvsFontList.

************************************************************************/

#include <AutoMessages.h>
#include "mvslib.h"

/* 
 * Reduced the size of the font_info array to just 1 for the final fallback
 * font for automation.
 */
void mvsInitFonts()
{


    XmFontList font_list;
    char msg_string[125];

    font_list = (XmFontList)NULL;

    mvsFontInfo[0].font_struct = XLoadQueryFont(mvsDisplay,
                                                mvsFontInfo[0].font_name);

    if (mvsFontInfo[0].font_struct == NULL) {
        sprintf (msg_string, _AutoMessages[VISMSG41], mvsFontInfo[0].font_name);
        AutoMessage(msg_string);
                    
        AutoError (_AutoMessages[VISMSG13]);

	}
	else {

    	mvsNumLoadedFonts = 1; 
    	font_list = XmFontListCreate(mvsFontInfo[0].font_struct,
                                 	 mvsFontInfo[0].char_set_name);
    	mvsFontList = font_list;

	}

} /* End mvsInitFonts() */
