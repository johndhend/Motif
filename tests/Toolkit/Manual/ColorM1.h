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
/*   $TOG: ColorM1.h /main/9 1999/11/03 15:05:49 jff $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */

#include <string.h>

#include <Mrm/MrmAppl.h>


#define NULLW ((Widget)0)
#define NULLCB ((XmAnyCallbackStruct *)0)

#define MAX_ENTRY_SIZE 500
/* scales show between 0 and 255, color values are between 0 and 65535 */
#define COLOR_PCT_MULTIPLIER 256

#define XtNfontText "fontText"
#define XtNrgbTextFile "rgbTextFile"
#define XtNmreTypeFile "mreTypeFile"
#define XtNprintHierarchy "printHierarchy"
#define XtNmergeOnSave "mergeOnSave"
#define XtNinternalPixmaps "internalPixmaps"
#define XtCFontText "FontText"
#define XtCRgbTextFile "RgbTextFile"
#define XtCMreTypeFile "MreTypeFile"
#define XtCPrintHierarchy "PrintHierarchy"
#define XtCMergeOnSave "MergeOnSave"
#define XtCInternalPixmaps "InternalPixmaps"
#define XmStringDefCreate(s) XmStringLtoRCreate((s),XmSTRING_DEFAULT_CHARSET)

typedef struct {
  Pixel fg;
  char *font_text;
  char *rgb_text_file;
  char *mre_type_file;
  Boolean print_hierarchy;
  Boolean merge_on_save;
  Boolean internal_pixmaps;
  } ApplicationData, *ApplicationDataPtr;

Colormap cmap;
Display *dpy;
Widget main_selection_box_id;
Widget popped_by;   
MrmHierarchy	s_MrmHierarchy;		
ApplicationData data;
Boolean no_colors_available;

