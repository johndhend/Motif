/* $XConsortium: sgi_visual.h /main/5 1995/07/15 21:01:43 drk $ */
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


#include <X11/Intrinsic.h>
/* #include <X11/Shell.h>
/* #include <X11/StringDefs.h>
/* #include <stdio.h>
/** **/

/* STATUS RETURNS */
#	define SG_VISUAL_SUCCESS	1
#	define SG_VISUAL_DEFAULT	(SG_VISUAL_SUCCESS + 1)

#	define SG_NO_VISUAL		(-1)
#	define SG_BAD_DISPLAY		(SG_NO_VISUAL-1)
#	define SG_NO_TYPE_AND_CLASS	(SG_BAD_DISPLAY-1)
#	define SG_NO_SUCH_VISUAL	(SG_NO_TYPE_AND_CLASS-1)


/* Visual types */
#	define SG_DEFAULT_PLANES	0	/* matches resource default */
#	define SG_UNDERLAY_PLANES	1
#	define SG_NORMAL_PLANES		2
#	define SG_OVERLAY_PLANES	3
#	define SG_POPUP_PLANES		4
#	define SG_MAX_TYPES		(SG_POPUP_PLANES + 1)


/* External declarations */

    extern int	    _SG_defaultDepthAndTypeResources
	( Display *display, int screen, int *requestedClass,
	  char *requestedType, int *requestedTypeV, int *requestedDepth,
	  Visual **requestedVisual, Colormap *requestedColormap,
	  Drawable *requestedDrawable);
    extern Colormap _SG_getDefaultColormap
	(Display *dpy, int scr, Visual *vsl);
    extern int      _SG_getDefaultDepth
	(Display *dpy, int scr, int *class, int type);
    extern XVisualInfo *_SG_getMatchingVisual
	(Display *dpy, int scr, VisualID vsl, int *class, int type, int depth);
    extern int      _SG_getMaxDepth
	(Display *dpy, int scr, int *class, int type);
    extern int      _SG_getNormalArgs
	(Display *dpy, int scr, ArgList args, int *n);
    extern int     _SG_getOverlayArgs
	(Display *dpy, int scr, ArgList args, int *n);
    extern int     _SG_getOverlay2Args
	(Display *dpy, int scr, ArgList args, int *n);
    extern int     _SG_getOverlay4Args
	(Display *dpy, int scr, ArgList args, int *n);
    extern int      _SG_getPopupArgs
	(Display *dpy, int scr, ArgList args, int *n);
    extern int      _SG_getUnderlayArgs
	(Display *dpy, int scr, ArgList args, int *n);
    extern int      _SG_getVisualArgs
	(Display *dpy, int scr, int dpth, int *class, int type, ArgList args, int *n);
