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
/*   $XConsortium: ABrowseP.h /main/8 1995/07/14 10:45:22 drk $ */

/************************************************************
 * ABrowseP.h: Private header file for ABrowse Widget Class *
 ************************************************************/

#ifndef _ABrowseP_h
#define _ABrowseP_h

#include <X11/FormP.h>
#include <X11/ConstrainP.h>

#include "ABrowse.h"

/*
 * ABrowse widget part of class record
 */

typedef struct _ABrowseClassPart
{
    int	empty;
} ABrowseClassPart;

/*
 * ABrowse widget full class record
 */

typedef struct _ABrowseClassRec
{
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    FormClassPart		form_class;
    ABrowseClassPart		abrowse_class;
} ABrowseClassRec;

extern ABrowseClassRec	abrowseClassRec;

/*
 * ABrowse widget part of instance record
 */

typedef struct _ABrowsePart
{
    Pixmap		*images;		/* images to view	  */
    Cardinal		num_images;		/* number of images	  */
    Pixel		image_background;	/* image background color */
    Pixel		image_foreground;	/* image foreground color */
    Pixel		button_background;	/* image background color */
    Pixel		button_foreground;	/* image foreground color */
    XtCallbackList	help_callback;		/* help callback proc	  */
    XtCallbackList	quit_callback;		/* quit callback proc	  */

    int			current_image;		/* image being displayed  */
    Widget		prev;			/* prev button		  */
    Widget		next;			/* next button		  */
    Widget		help;			/* help button		  */
    Widget		quit;			/* quit button		  */
    Widget		image;			/* image display	  */
} ABrowsePart;

/*
 * ABrowse widget full instance record
 */

typedef struct _ABrowseRec
{
    CorePart		core;
    CompositePart	composite;
    ConstraintPart	constraint;
    FormPart		form;
    ABrowsePart		abrowse;
} ABrowseRec;

#endif _ABrowseP_h
