/* $XConsortium: geoTattler.h /main/4 1995/07/15 21:13:47 drk $ */
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

#define XtNgeoTattler "geoTattler"
#define XtCGeoTattler "GeoTattler"

/* not found anywhere in Xt, so define this one */
#define XtClassName(w) XtClass(w)->core_class.class_name



#if NeedFunctionPrototypes
extern Boolean _GeoIsTattled (Widget widget);
extern Boolean _GeoIsCached (Widget widget, Boolean* is_geotattled);
extern void _GeoChangeCache (Widget widget, Boolean geo_tat);
extern void _GeoCache (Widget widget, Boolean geo_tat);
extern void _GeoTabTrace (void);
extern void _GeoUnTabTrace (void);
extern void _GeoPrintTab (void);
#else
extern Boolean _GeoIsTattled ();
extern Boolean _GeoIsCached ();
extern void _GeoChangeCache ();
extern void _GeoCache ();
extern void _GeoTabTrace ();
extern void _GeoUnTabTrace ();
extern void _GeoPrintTab ();
#endif

#if NeedVarargsPrototypes
extern void _GeoPrintTrace (Widget widget, ...);
#else
extern void _GeoPrintTrace ();
#endif



/* some useful macros */

#define GMode(g)	    ((g)->request_mode)
#define IsX(g)		    (GMode (g) & CWX)
#define IsY(g)		    (GMode (g) & CWY)
#define IsWidth(g)	    (GMode (g) & CWWidth)
#define IsHeight(g)	    (GMode (g) & CWHeight)
#define IsBorder(g)	    (GMode (g) & CWBorderWidth)
#define IsWidthHeight(g)    ((GMode (g) & CWWidth) || (GMode (g) & CWHeight))
#define IsQueryOnly(g)      (GMode (g) & XtCWQueryOnly)
