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
static char rcsid[] = "$XConsortium: IsWidInFocus.c /main/7 1995/07/14 11:40:35 drk $"
#endif
#endif
/***********************************************************************
  	@(#)IsWidInFocus.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/30/90 SJS add to sccs
	Calls:

	Summary:
            Returns True if widget is in keyboard focus.

        INPUTS:
            none
        
        OUTPUTS:
            none

        RETURNS:
            True = widget is in keyboard focus
            False = widget is not in keyboard focus
************************************************************************/

#include <AutoMessages.h>
#include "xislib.h"

int xisIsWidgetInKeyboardFocus(bool)
int bool;
{
    int result;

    XisObjectRecord *focus_object = xisGetFocusObject();

    if (!xisInform.is_valid) 
       AutoMessage (_AutoMessages[WARNMSG56]);

    if (focus_object->id.widget == xisInform.current_obj->id.widget)
        result = bool;
    else
        result = (!bool);

    return (result);

} /* End xisIsWidgetInKeyboardFocus() */

/***********************************************************************
  	Author: PSN
	History:
            08/29/90 PSN first cut
	Calls:

	Summary:
            Returns True if widget's parent is in keyboard focus.

        INPUTS:
            none
        
        OUTPUTS:
            none

        RETURNS:
            True = widget's parent is in keyboard focus
            False = widget's parent is not in keyboard focus
************************************************************************/

int xisIsParentWidgetInKeyboardFocus(bool)
int bool;
{
    int result;

    XisObjectRecord *focus_object = xisGetFocusObject();

    if (!xisInform.is_valid) 
       AutoMessage(_AutoMessages[WARNMSG57]);

    if (focus_object->id.widget == XtParent(xisInform.current_obj->id.widget))
        result = bool;
    else
        result = (!bool);

    return (result);

} /* End xisIsParentWidgetInKeyboardFocus() */
