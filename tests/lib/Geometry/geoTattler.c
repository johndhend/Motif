/* $XConsortium: geoTattler.c /main/4 1995/07/15 21:13:42 drk $ */
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
#include "IntrinsicI.h"      /* for the class_name field */
#include "VarargsI.h"        /* for _GeoPrintTrace */
#include <X11/StringDefs.h>  /* XtRBoolean .. */
#include "geoTattler.h"


/**************************************************************************
 GeoTattler API:
  
  if those lines are found in the resource database:

    myapp*draw.XmScale.geoTattler: ON
    *XmScrollBar.geoTattler:ON
    *XmRowColumn.exit_button.geoTattler:ON

   then:

    all the XmScale children of the widget named draw,
    all the XmScrollBars,
    the widget named exit_button in any XmRowColumn

   will return True to the function _GeoIsTattled(), and will generate
   outlined trace in stdout.

*************************************************************************/

typedef struct {   Boolean   geo_tattler ;} GeoDataRec ;


static XtResource geo_resources[] = {
    { XtNgeoTattler, XtCGeoTattler, XtRBoolean, sizeof(Boolean),
      XtOffsetOf(GeoDataRec, geo_tattler), 
      XtRImmediate, (caddr_t) False }
};

/* Now define a simple cache mechanism to be used in the main function */

typedef struct _GeoTatCache
{
   Widget widget;
   String widget_name;
   String class_name;
   Boolean is_geotattled ;
   struct _GeoTatCache * next;
} GeoTatCache;

static GeoTatCache * geotat_cache = NULL;




/****************************************************************
  This function return True is the widget is already in the cache,
  False otherwise. It also return the current value if True */
Boolean 
#if NeedFunctionPrototypes
_GeoIsCached (Widget widget, Boolean* is_geotattled)
#else
_GeoIsCached (widget, is_geotattled)
Widget widget;
Boolean * is_geotattled ;
#endif
{
    register GeoTatCache * cache_ptr;
    
    for (cache_ptr = geotat_cache; cache_ptr; cache_ptr = cache_ptr->next) {
	if ((cache_ptr->widget == widget) &&
	    (strcmp (cache_ptr->widget_name, XtName(widget)) == 0)  &&
	    (strcmp (cache_ptr->class_name, XtClassName(widget)) == 0)) {
	    /* if something found return its state and True */

	    *is_geotattled = cache_ptr->is_geotattled ;
	    return (True);
	}
    }
    
    return (False);
}


/****************************************************************
   This function looks for a widget in the cache and if found, assigns
   a new value for the is_geotattled field 
   It is used for dynamic change (e.g. editres stuff) */
void 
#if NeedFunctionPrototypes
_GeoChangeCache (Widget widget, Boolean geo_tat)
#else
_GeoChangeCache (widget, geo_tat)
Widget widget;
Boolean geo_tat ;
#endif
{
    register GeoTatCache * cache_ptr;

    for (cache_ptr = geotat_cache; cache_ptr; cache_ptr = cache_ptr->next) {
	if ((cache_ptr->widget == widget) &&
	    (strcmp (cache_ptr->widget_name, XtName(widget)) == 0)  &&
	    (strcmp (cache_ptr->class_name, XtClassName(widget)) == 0)) {
	    /* if something found, change the value */

	    cache_ptr->is_geotattled = geo_tat;
	    return ;
	}
    }
    
    return ;
}

/****************************************************************
   This function adds an entry in the cache, based on the given widget
   and bool */

void 
#if NeedFunctionPrototypes
_GeoCache (Widget widget, Boolean geo_tat)
#else
_GeoCache (widget, geo_tat)
Widget widget;
Boolean geo_tat ;
#endif
{
    register GeoTatCache * cache_ptr;

    /* create a new entry in the geo cache */

    cache_ptr = XtNew (GeoTatCache);
    cache_ptr->next = geotat_cache;
    geotat_cache = cache_ptr;

    /* fill it, please, regular */

    cache_ptr->widget = widget ;
    cache_ptr->widget_name = XtNewString(XtName(widget));
    cache_ptr->class_name = XtNewString(XtClassName(widget));
    cache_ptr->is_geotattled = geo_tat ;
}

/************************************************************************
  This function uses XtGetSubresources to find out if a widget
  needs to be geo-spied by the caller.
  Since XtGetSubresources is expensive, it also uses a cache. */

Boolean 
#if NeedFunctionPrototypes
_GeoIsTattled (Widget widget)
#else
_GeoIsTattled (widget)
Widget widget;
#endif
{
    GeoDataRec geo_data ;
    Boolean is_geotattled, cach ;

       /* First check for a matching widget  */
    if (_GeoIsCached (widget, &is_geotattled)) return is_geotattled ;

       /* no widget found in the cache, look in the database and cache */
    XtGetSubresources(widget, (XtPointer)&geo_data,
                      (String)NULL, (String)NULL, 
		      geo_resources, XtNumber(geo_resources), 
		      NULL, 0);
    
       /* add in the cache */
    _GeoCache(widget, geo_data.geo_tattler) ;

    return geo_data.geo_tattler;

}  /* _GeoIsTattled */


/************************************************************************
  Trace stuff now */

static n_tab = 0 ;

void 
#if NeedFunctionPrototypes
_GeoTabTrace (void)
#else
_GeoTabTrace ()
#endif
{
    n_tab ++ ;
}


void
#if NeedFunctionPrototypes
_GeoUnTabTrace (void)
#else
_GeoUnTabTrace ()
#endif
{
    n_tab -- ;
}


void 
#if NeedFunctionPrototypes
_GeoPrintTab (void)
#else
_GeoPrintTab ()
#endif
{
    int i ;

    for (i=0; i<n_tab; i++) printf("     ");
}


void 
#if NeedVarargsPrototypes
_GeoPrintTrace (Widget widget, ...)
#else
_GeoPrintTrace (widget, va_alist)
Widget widget;
va_dcl
#endif
{
    va_list args;
    char *fmt;

    if (_GeoIsTattled(widget)) {
	Va_start(args, widget);
	fmt = va_arg(args, char *);
	_GeoPrintTab ();
	(void) vprintf(fmt, args);
	va_end(args);
    }
}


