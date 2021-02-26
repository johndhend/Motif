
#include <localdef.h>

/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */
/*   $XConsortium: XmRenderTI.h /main/5 1995/07/13 18:24:12 drk $ */
#ifndef _XmRenderTI_h
#define _XmRenderTI_h

#include <Xm/XmP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Internal types for XmRenderTable.c */

#define REND_OPTIMIZED_BITS	1
#define REND_MARK_BITS		REND_OPTIMIZED_BITS
#define REND_REFCOUNT_BITS	(16 - REND_OPTIMIZED_BITS)

/*
 * Macros for Rendition data structure access
 */

#define _XmRendRefcount(r)	((_XmRendition)*(r))->refcount
#define _XmRendFontOnly(r)	((_XmRendition)*(r))->fontOnly
#define _XmRendLoadModel(r)	((_XmRendition)*(r))->loadModel
#define _XmRendTag(r)		((_XmRendition)*(r))->tag
#define _XmRendFontName(r)	((_XmRendition)*(r))->fontName
#define _XmRendFontType(r)	((_XmRendition)*(r))->fontType
#define _XmRendFont(r)		((_XmRendition)*(r))->font
#define _XmRendDisplay(r)	((_XmRendition)*(r))->display
#define _XmRendTabs(r)		((_XmRendition)*(r))->tabs
#define _XmRendBG(r)		((_XmRendition)*(r))->background
#define _XmRendFG(r)		((_XmRendition)*(r))->foreground
#define _XmRendBGState(r)	((_XmRendition)*(r))->backgroundState
#define _XmRendFGState(r)	((_XmRendition)*(r))->foregroundState
#define _XmRendUnderlineType(r)	((_XmRendition)*(r))->underlineType
#define _XmRendStrikethruType(r)((_XmRendition)*(r))->strikethruType
#define _XmRendGC(r)		((_XmRendition)*(r))->gc
#define _XmRendTags(r)		((_XmRendition)*(r))->tags
#define _XmRendTagCount(r)	((_XmRendition)*(r))->count
#define _XmRendHadEnds(r)	((_XmRendition)*(r))->hadEnds
#define _XmRendRefcountInc(r)	++(((_XmRendition)*(r))->refcount)
#define _XmRendRefcountDec(r)	--(((_XmRendition)*(r))->refcount)

typedef struct __XmRenditionRec
{
  /* flag indicating _XmFontRenditionRec */
  unsigned int	fontOnly : REND_OPTIMIZED_BITS; 
  unsigned int	refcount : REND_REFCOUNT_BITS;
  
  unsigned char	loadModel;
  XmStringTag	tag;
  String	fontName;
  XmFontType	fontType;
  XtPointer	font;
  Display	*display;
  GC		gc;
  XmStringTag	*tags;
  unsigned int	count;
  Boolean	hadEnds;
  
  XmTabList	tabs;
  Pixel		background;
  Pixel		foreground;
  unsigned char	underlineType;
  unsigned char strikethruType;
  unsigned char backgroundState;
  unsigned char foregroundState;
  
} _XmRenditionRec, *_XmRendition;

typedef struct __XmFontRenditionRec
{
  /* flag indicating _XmFontRenditionRec */
  unsigned int	fontOnly : REND_OPTIMIZED_BITS; 
  unsigned int	refcount : REND_REFCOUNT_BITS;

  unsigned char	loadModel;
  XmStringTag	tag;
  String	fontName;
  XmFontType	fontType;
  XtPointer	font;
  Display	*display;
  GC		*gc;
  XmStringTag	*tags;
  unsigned int	count;
} _XmFontRenditionRec, *_XmFontRendition;

/* Accessor macros. */

#define _XmRTCount(rt)		((_XmRenderTable)*(rt))->count
#define _XmRTRenditions(rt)	((_XmRenderTable)*(rt))->renditions
#define _XmRTDisplay(rt)	((_XmRenderTable)*(rt))->display
#define _XmRTMark(rt)		((_XmRenderTable)*(rt))->mark
#define _XmRTRefcount(rt)	((_XmRenderTable)*(rt))->refcount
#define _XmRTRefcountInc(rt)	++(((_XmRenderTable)*(rt))->refcount)
#define _XmRTRefcountDec(rt)	--(((_XmRenderTable)*(rt))->refcount)

#define RENDITIONS_IN_STRUCT	1

typedef struct __XmRenderTableRec
{
  unsigned int			mark : REND_MARK_BITS;
  unsigned int			refcount : REND_REFCOUNT_BITS;
  unsigned short		count;
  Display			*display;
  XmRendition			renditions[RENDITIONS_IN_STRUCT];
} _XmRenderTableRec, 		*_XmRenderTable;


/********    Private Function Declarations for XmRenderTable.c    ********/

extern XmRendition _XmRenderTableFindRendition(XmRenderTable table, 
					       XmStringTag tag,
#if NeedWidePrototypes
					       int cached_tag,
					       int need_font,
					       int call,
#else
					       Boolean cached_tag,
					       Boolean need_font,
					       Boolean call,
#endif /* NeedWidePrototypes */
					       short *index); 
extern XmRendition _XmRenditionCreate(Display *display,
				      Widget widget,
				      String resname,
				      String resclass,
				      XmStringTag tag,
				      ArgList arglist,
				      Cardinal argcount,
				      Boolean *in_db); 
extern XmRendition _XmRenderTableGetMerged(XmRenderTable rt,
					   XmStringTag base,
					   XmStringTag *tags,
#if NeedWidePrototypes
					   unsigned int tag_count 
#else			
                                           unsigned short tag_count 
#endif /* NeedWidePrototypes */
					   );
extern XmRendition _XmRenditionMerge(Display *d,
				     XmRendition *scr,
				     XmRendition base_rend,
				     XmRenderTable rt,
				     XmStringTag base_tag,
				     XmStringTag *tags,
#if NeedWidePrototypes
				     unsigned int tag_count,
                                     unsigned int copy
#else			
				     unsigned short tag_count,
                                     Boolean copy
#endif /* NeedWidePrototypes */
				     ); 
extern Widget _XmCreateRenderTable(Widget parent,
				   String name,
				   ArgList arglist,
				   Cardinal argcount); 
extern Widget _XmCreateRendition(Widget parent,
				 String name,
				 ArgList arglist,
				 Cardinal argcount); 
extern Display *_XmRenderTableDisplay(XmRenderTable table);
extern XmRendition _XmRenditionCopy(XmRendition rend,
				    Boolean shared);
extern Boolean _XmRenderTableFindFallback(XmRenderTable ,
					  XmStringTag tag,
#if NeedWidePrototypes
					  int cached_tag,
#else
					  Boolean cached_tag,
#endif /* NeedWidePrototypes */
					  short *indx,
					  XmRendition *rend_ptr) ;
extern Boolean _XmRenderTableFindFirstFont(XmRenderTable rendertable,
					   short *indx,
					   XmRendition *rend_ptr);
extern XmRenderTable _XmRenderTableRemoveRenditions(XmRenderTable oldtable,
						    XmStringTag *tags,
						    int tag_count,
#if NeedWidePrototypes
						    int chk_font,
#else
						    Boolean chk_font,
#endif /* NeedWidePrototypes */
						    XmFontType type,
						    XtPointer font);

/********    End Private Function Declarations    ********/

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* _XmRenderTI_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
