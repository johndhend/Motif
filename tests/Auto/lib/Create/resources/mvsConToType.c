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
static char rcsid[] = "$XConsortium: mvsConToType.c /main/8 1995/07/14 11:19:33 drk $"
#endif
#endif
/***********************************************************************
  	@(#)mvsConToType.c	1.11.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   04/20/90 SJS Add XmNavigationType
	   05/29/90 SJS Add more types
	   07/23/90 SJS Eliminate the silliness of OXmNavigationType
	Calls:

	Summary:
		This function converts the value contained in an
	MvsArgVal type variable into the requested type.
	An MvsArgVal is the sizeof the largest data type in a widget
	resource set, so it is necessary to type cast in order to
	extract values. The type casting is done so as to extract the
	appropriate value.
************************************************************************/
#include <AutoMessages.h>
#include "mvslib.h"

MvsArgVal mvsConvertToType(value, type)
MvsArgVal value;
int type;
{
    MvsArgVal return_value;
    char msg_string[125];

    switch(type) {
      case T_XtTranslations:
        return_value = (MvsArgVal)(*((XtTranslations *)&value));
        break;
      case T_Boolean:       
        return_value = (MvsArgVal)(*((Boolean *)&value));
        break;
      case T_Pixel:         
        return_value = (MvsArgVal)(*((Pixel *)&value));
        break;
      case T_XtProc:        /* This type needs fixing!!! AES */
        return_value = (MvsArgVal)(*((caddr_t *)&value));
        break;
      case T_Pixmap:        
        return_value = (MvsArgVal)(*((Pixmap *)&value));
        break;
      case T_Dimension:     
        return_value = (MvsArgVal)(*((Dimension *)&value));
        break;
      case T_Colormap:      
        return_value = (MvsArgVal)(*((Colormap *)&value));
        break;
      case T_XtCallbackList:
        return_value = (MvsArgVal)(*((XtCallbackList *)&value));
        break;
      case T_XtEnum:
        return_value = (MvsArgVal)(*((XtEnum *)&value));
        break;
      case T_Pointer:        
        return_value = (MvsArgVal)(*((Pointer *)&value));
        break;
      case T_Position:      
        return_value = (MvsArgVal)(*((Position *)&value));
        break;
      case T_Integer:     
        return_value = (MvsArgVal)(*((Integer *)&value));
        break;
      case T_caddr_t:       
        return_value = (MvsArgVal)(*((caddr_t *)&value));
        break;
      case T_unsigned_char:       
        return_value = (MvsArgVal)(*((unsigned char *)&value));
        break;
      case T_short:       
        return_value = (MvsArgVal)(*((short *)&value));
        break;
      case T_String:
        return_value = (MvsArgVal)(*((String *)&value));       
        break;
      case T_Widget_ref:       
        return_value = (MvsArgVal)(*((Widget *)&value));       
        break;
      case T_XmFontList:       
        return_value = (MvsArgVal)(*((XmFontList *)&value));       
        break;
      case T_XmString:       
        return_value = (MvsArgVal)(*((XmString *)&value));
        break;
      case T_XmStringTable:       
        return_value = (MvsArgVal)(*((XmStringTable *)&value));
        break;
      case T_char:       
        return_value = (MvsArgVal)(*((char *)&value));
        break;
      case T_XmNavigationType:       
        return_value = (MvsArgVal)(*((XmNavigationType *)&value));
        break;
      case T_XmStringDirection:       
        return_value = (MvsArgVal)(*((XmStringDirection *)&value));
        break;
      case T_KeySym:       
        return_value = (MvsArgVal)(*((KeySym *)&value));
        break;
      case T_WidgetClass_ref:
        return_value = (MvsArgVal)(*((WidgetClass *)&value));
        break;
      case T_Cardinal:
        return_value = (MvsArgVal)(*((Cardinal *)&value));
        break;
      case T_WidgetList:      
        return_value = (MvsArgVal)(*((WidgetList *)&value));
        break;
      case T_XmFunction:        /* This type needs fixing!!! AES */
        return_value = (MvsArgVal)(*((caddr_t *)&value));
        break;
      case T_XmTextSource:        /* This type needs fixing!!! AES */
        return_value = (MvsArgVal)(*((WidgetClass *)&value));
        break;
      case T_XmTextPosition:        
        return_value = (MvsArgVal)(*((XmTextPosition *)&value));
        break;
      case T_XtAccelerators:
        return_value = (MvsArgVal)(*((XtAccelerators *)&value));
        break;
      case T_XmDirection:
	return_value = (MvsArgVal)(*((XmDirection *)&value));
	break;
      case T_XmRenderTable:
	return_value = (MvsArgVal)(*((XmRenderTable *)&value));
	break;
/*  Removed from Xm source
 *    case T_XmBitArray:
 *	return_value = (MvsArgVal)(*((XmBitArray *)&value));
 *	break;
 */
      case T_XmTabList:
	return_value = (MvsArgVal)(*((XmTabList *)&value));
	break;
      case T_XmViewType:
	return_value = (MvsArgVal)(*((unsigned char *)&value));
	break;
      case T_XmVisualEmphasis:
	return_value = (MvsArgVal)(*((unsigned char *)&value));
	break;
      case T_unsigned_int:
	return_value = (MvsArgVal)(*((unsigned int *)&value));
	break;
      default:
	sprintf (msg_string, _AutoMessages[WARNMSG65], type);
        AutoMessage(msg_string);
        return_value = value;
        break;
    } /* End switch() */

    return(return_value);

} /* End mvsConvertToType() */
