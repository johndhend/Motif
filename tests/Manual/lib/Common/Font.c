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
static char rcsid[] = "$XConsortium: Font.c /main/8 1995/07/14 11:59:11 drk $"
#endif
#endif
#include "testlib.h"

/*************************************************************************
*									 *
*	Name:		CommonGetFontList()				 *
*									 *
*	Purpose:	This function will given a name of a font        *
*			and return a appropriate Font List. If the font  *
*			cannot be found, the default font will be	 *
*			used. default_font is either read from the       *
*			command line or from testlib.h (DEFAULT_FONT)	 *
*									 *
*	Return:		Appropriate font list corresponding to string    *
*			input.						 *
*									 *
*************************************************************************/

XmFontList CommonGetFontList(char *fontstr)

{

#ifdef MOTIF1_1
    XFontStruct   *newfont;
#else
    static XmFontListEntry fixed_font = NULL;
    XmFontListEntry fontlistEntry;
#endif
    XmFontList    fontlist;

#ifdef MOTIF1_1

    if (!(newfont = XLoadQueryFont (display, fontstr)))
    	newfont = XLoadQueryFont (display, default_font);
    fontlist = XmFontListCreate (newfont, XmSTRING_DEFAULT_CHARSET);

#else

    if (!fixed_font) {
        fixed_font = XmFontListEntryLoad(display, "fixed", XmFONT_IS_FONT,
                                         XmFONTLIST_DEFAULT_TAG);
    }

    if ((fontlistEntry = XmFontListEntryLoad(display, fontstr, XmFONT_IS_FONT,
                                        XmFONTLIST_DEFAULT_TAG)) == NULL)
      {
	fontlist = XmFontListAppendEntry(NULL, fixed_font);
      }
    else
      {
	fontlist = XmFontListAppendEntry(NULL, fontlistEntry);
	XmFontListEntryFree(&fontlistEntry);
      }

#endif

	return(fontlist);

}

/*************************************************************************
*									 *
*	Name:		CommonGetFontListWithCharset()			 *
*									 *
*	Purpose:	This function will be given the name of a 	 *
*			desired font and the desired charset name	 *
*			and will return the appropriate Font List. If 	 *
*			the font cannot be found, the default font will  *
*			be used. default_font is either read from the 	 *
*			command line or from testlib.h (DEFAULT_FONT)	 *
*									 *
*	Return:		Appropriate font list                            *
*									 *
*************************************************************************/

XmFontList CommonGetFontListWithCharset(char *fontstr, char *charset)

{

#ifdef MOTIF1_1
    XFontStruct   *newfont;
#else
    static XmFontListEntry fixed_font = NULL;
    XmFontListEntry fontlistEntry;
#endif
    XmFontList    fontlist;

#ifdef MOTIF1_1

    if (!(newfont = XLoadQueryFont (display, fontstr)))
    	newfont = XLoadQueryFont (display, default_font);
    fontlist = XmFontListCreate (newfont, charset);


#else

    if (!fixed_font) {
        fixed_font = XmFontListEntryLoad(display, "fixed", XmFONT_IS_FONT,
                                         charset);
    }

    if ((fontlistEntry = XmFontListEntryLoad(display, fontstr, XmFONT_IS_FONT,
                                        charset)) == NULL)
      {
	fontlist = XmFontListAppendEntry(NULL, fixed_font);
      }
    else
      {
	fontlist = XmFontListAppendEntry(NULL, fontlistEntry);
	XmFontListEntryFree(&fontlistEntry);
      }

#endif

	return(fontlist);

}
