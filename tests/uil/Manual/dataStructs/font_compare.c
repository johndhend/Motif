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
static char rcsid[] = "$XConsortium: font_compare.c /main/4 1995/07/13 20:35:53 drk $"
#endif
#endif

#include <stdio.h>

#include <X11/Intrinsic.h>
#include <X11/Xlib.h>

#define MIN(a, b)   ((a) < (b) ? (a) : (b))

void	add_err_msg();

void compare_fonts(font1, font2, errors, error_message)
     XFontStruct	*font1,
     			*font2;
     int		*errors;
     String		error_message;
{
    int		per_char_errors = 0,
    		num1, num2,
    		i;

    char	err_msg[80];
    
    XCharStruct	*ptr1,
    		*ptr2;

    *errors = 0;

    if((font1 == NULL) || (font2 == NULL))
    {
	sprintf(err_msg,"NULL font(s)       \t");
	add_err_msg(error_message, err_msg);
	
	if(font1 == NULL)
	{
	    (*errors)++;

	    sprintf(err_msg,"  NULL  \t");
	}
	else
	{
	    sprintf(err_msg,"non-NULL\t");
	}
	add_err_msg(error_message, err_msg);

	if(font2 == NULL)
	{
	    (*errors)++;

	    sprintf(err_msg,"  NULL  \n");
	}
	else
	{
	    sprintf(err_msg,"non-NULL\n");
	}
	add_err_msg(error_message, err_msg);

	return;
    }

    if(font1->direction != font2->direction)
    {
	(*errors)++;

	sprintf(err_msg,"direction          \t%8u\t%8u\n",
		font1->direction, font2->direction);
	add_err_msg(error_message, err_msg);
    }
	    
    if(font1->min_char_or_byte2 != font2->min_char_or_byte2)
    {
	(*errors)++;

	sprintf(err_msg,"min_char_or_byte2  \t%8u\t%8u\n",
		font1->min_char_or_byte2, font2->min_char_or_byte2);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_char_or_byte2 != font2->max_char_or_byte2)
    {
	(*errors)++;

	sprintf(err_msg,"max_char_or_byte2  \t%8u\t%8u\n",
		font1->max_char_or_byte2, font2->max_char_or_byte2);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_byte1 != font2->min_byte1)
    {
	(*errors)++;

	sprintf(err_msg,"min_byte1          \t%8u\t%8u\n",
		font1->min_byte1, font2->min_byte1);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_byte1 != font2->max_byte1)
    {
	(*errors)++;

	sprintf(err_msg,"max_byte1          \t%8u\t%8u\n",
		font1->max_byte1, font2->max_byte1);
	add_err_msg(error_message, err_msg);
    }

    if(font1->all_chars_exist != font2->all_chars_exist)
    {
	(*errors)++;

	sprintf(err_msg,"all_chars_exist    \t%8d\t%8d\n",
		font1->all_chars_exist, font2->all_chars_exist);
	add_err_msg(error_message, err_msg);
    }

    if(font1->default_char != font2->default_char)
    {
	(*errors)++;

	sprintf(err_msg,"default_char       \t%8u\t%8u\n",
		font1->default_char, font2->default_char);
	add_err_msg(error_message, err_msg);
    }

    if(font1->n_properties != font2->n_properties)
    {
	(*errors)++;

	sprintf(err_msg,"n_properties       \t%8d\t%8d\n",
		font1->n_properties, font2->n_properties);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_bounds.lbearing != font2->min_bounds.lbearing)
    {
	(*errors)++;

	sprintf(err_msg,"min_bounds.lbearing\t%8d\t%8d\n",
		font1->min_bounds.lbearing, font2->min_bounds.lbearing);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_bounds.rbearing != font2->min_bounds.rbearing)
    {
	(*errors)++;

	sprintf(err_msg,"min_bounds.rbearing\t%8d\t%8d\n",
		font1->min_bounds.rbearing, font2->min_bounds.rbearing);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_bounds.width != font2->min_bounds.width)
    {
	(*errors)++;

	sprintf(err_msg,"min_bounds.width   \t%8d\t%8d\n",
		font1->min_bounds.width, font2->min_bounds.width);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_bounds.ascent != font2->min_bounds.ascent)
    {
	(*errors)++;

	sprintf(err_msg,"min_bounds.ascent  \t%8d\t%8d\n",
		font1->min_bounds.ascent, font2->min_bounds.ascent);
	add_err_msg(error_message, err_msg);
    }

    if(font1->min_bounds.descent != font2->min_bounds.descent)
    {
	(*errors)++;

	sprintf(err_msg,"min_bounds.descent \t%8d\t%8d\n",
		font1->min_bounds.descent, font2->min_bounds.descent);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_bounds.lbearing != font2->max_bounds.lbearing)
    {
	(*errors)++;

	sprintf(err_msg,"max_bounds.lbearing\t%8d\t%8d\n",
		font1->max_bounds.lbearing, font2->max_bounds.lbearing);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_bounds.rbearing != font2->max_bounds.rbearing)
    {
	(*errors)++;

	sprintf(err_msg,"max_bounds.rbearing\t%8d\t%8d\n",
		font1->max_bounds.rbearing, font2->max_bounds.rbearing);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_bounds.width != font2->max_bounds.width)
    {
	(*errors)++;

	sprintf(err_msg,"max_bounds.width   \t%8d\t%8d\n",
		font1->max_bounds.width, font2->max_bounds.width);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_bounds.ascent != font2->max_bounds.ascent)
    {
	(*errors)++;

	sprintf(err_msg,"max_bounds.ascent  \t%8d\t%8d\n",
		font1->max_bounds.ascent, font2->max_bounds.ascent);
	add_err_msg(error_message, err_msg);
    }

    if(font1->max_bounds.descent != font2->max_bounds.descent)
    {
	(*errors)++;

	sprintf(err_msg,"max_bounds.descent \t%8d\t%8d\n",
		font1->max_bounds.descent, font2->max_bounds.descent);
	add_err_msg(error_message, err_msg);
    }

    if(font1->ascent != font2->ascent)
    {
	(*errors)++;

	sprintf(err_msg,"ascent           \t%8d\t%8d\n",
		font1->ascent, font2->ascent);
	add_err_msg(error_message, err_msg);
    }

    if(font1->descent != font2->descent)
    {
	(*errors)++;

	sprintf(err_msg,"descent          \t%8d\t%8d\n",
		font1->descent, font2->descent);
	add_err_msg(error_message, err_msg);
    }

    ptr1 = font1->per_char;
    ptr2 = font2->per_char;

    /*
     * Don't do any more testing if the per_char is null on both. 
     */

    if((ptr1 == NULL) && (ptr2 == NULL))
    {
   	return;
    }

    if((ptr1 == NULL) || (ptr2 == NULL))
    {
	per_char_errors++;
    }
    else
    {
	num1 = font1->max_char_or_byte2 - font1->min_char_or_byte2;
	num2 = font2->max_char_or_byte2 - font2->min_char_or_byte2;

	for(i=0 ; i<MIN(num1, num2) ; ptr1++, ptr2++, i++)
	{
	    if((ptr2->lbearing != ptr1->lbearing) ||
	       (ptr2->rbearing != ptr1->rbearing) ||
	       (ptr2->width != ptr1->width) ||
	       (ptr2->ascent != ptr1->ascent) ||
	       (ptr2->descent != ptr1->descent))
	    {
		per_char_errors++;
	    }
	}
    }
    
    if(num1 != num2)
    {
	per_char_errors++;
    }
    
    if(per_char_errors)
    {
	*errors += per_char_errors;

	sprintf(err_msg, "per_char        \t different per_char data\n");
	add_err_msg(error_message, err_msg);
    }
}

void add_err_msg(error_message, err_msg)
     String	error_message,
     		err_msg;
{

    if(error_message != NULL)
    {
	strcat(error_message, err_msg);
    }
}
