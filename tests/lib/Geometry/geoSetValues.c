/* $XConsortium: geoSetValues.c /main/4 1995/07/15 21:13:32 drk $ */
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

#include "IntrinsicI.h"
#include "StringDefs.h"
  
#include "geoTattler.h"

/*
 *	XtSetValues(), XtSetSubvalues()
 */


extern void _XtCopyFromArg();
extern XrmResourceList* _XtCreateIndirectionTable();

static void SetValues(base, res, num_resources, args, num_args)
  char*			base;		/* Base address to write values to   */
  XrmResourceList*	res;		/* The current resource values.      */
  register Cardinal	num_resources;	/* number of items in resources      */
  ArgList 		args;		/* The resource values to set        */
  Cardinal		num_args;	/* number of items in arg list       */
{
    register ArgList		arg;
    register int 	        i;
    register XrmName		argName;
    register XrmResourceList*   xrmres;

    /* Resource lists are assumed to be in compiled form already via the
       initial XtGetResources, XtGetSubresources calls */

    for (arg = args ; num_args != 0; num_args--, arg++) {
	argName = StringToName(arg->name);
	for (xrmres = res, i = 0; i < num_resources; i++, xrmres++) {
	    if (argName == (*xrmres)->xrm_name) {
		_XtCopyFromArg(arg->value,
		    base - (*xrmres)->xrm_offset - 1,
		    (*xrmres)->xrm_size);
		break;
	    }
	}
    }
} /* SetValues */

static Boolean CallSetValues (class, current, request, new, args, num_args)
    WidgetClass class;
    Widget      current, request, new;
    ArgList     args;
    Cardinal    num_args;
{
    Boolean redisplay = FALSE;

    if (class->core_class.superclass != NULL)
        redisplay = CallSetValues(
	  class->core_class.superclass, current, request, new, args, num_args);
    if (class->core_class.set_values != NULL)
        redisplay |= (*class->core_class.
		      set_values) (current, request, new, args, &num_args);
    if (class->core_class.set_values_hook != NULL)
	redisplay |=
	    (*class->core_class.set_values_hook) (new, args, &num_args);
    return (redisplay);
}

static Boolean
CallConstraintSetValues (class, current, request, new, args, num_args)
    ConstraintWidgetClass class;
    Widget      current, request, new;
    ArgList     args;
    Cardinal    num_args;
{
    Boolean redisplay = FALSE;

    if ((WidgetClass)class != constraintWidgetClass) {
	if (class == NULL)
	    XtAppErrorMsg(XtWidgetToApplicationContext(current),
		    "invalidClass","constraintSetValue",XtCXtToolkitError,
                 "Subclass of Constraint required in CallConstraintSetValues",
                  (String *)NULL, (Cardinal *)NULL);
	redisplay = CallConstraintSetValues(
	    (ConstraintWidgetClass) (class->core_class.superclass),
	    current, request, new, args, num_args);
    }
    if (class->constraint_class.set_values != NULL)
        redisplay |= (*class->constraint_class.
		      set_values) (current, request, new, args, &num_args);
    return (redisplay);
}

void XtSetSubvalues(base, resources, num_resources, args, num_args)
  XtPointer             base;           /* Base address to write values to   */
  register XtResourceList resources;    /* The current resource values.      */
  register Cardinal     num_resources;  /* number of items in resources      */
  ArgList               args;           /* The resource values to set        */
  Cardinal              num_args;       /* number of items in arg list       */
{
      register XrmResourceList*   xrmres;
      xrmres = _XtCreateIndirectionTable (resources, num_resources);
      SetValues((char*)base,xrmres,num_resources, args, num_args);
      XtFree((char *)xrmres);
}


void XtSetValues(w, args, num_args)
    register Widget   w;
	     ArgList  args;
	     Cardinal num_args;
{
    register Widget oldw, reqw;
    /* need to use strictest alignment rules possible in next two decls. */
    double	    oldwCache[100], reqwCache[100];
    double	    oldcCache[20], reqcCache[20];
    Cardinal	    widgetSize, constraintSize;
    Boolean	    redisplay, cleared_rect_obj = False;
    XtGeometryResult result;
    XtWidgetGeometry geoReq, geoReply;
    WidgetClass     wc = XtClass(w);
    ConstraintWidgetClass cwc;
    Boolean	    hasConstraints;
    Cardinal i ;

    /* Editres hack: 
       editres uses XtGetResourceList to get the resource list of a widget,
       and geoTattler can't be in the list, so we use "traversalOn", which
       is in all Motif subclasses. 
    
    for (i = 0 ; i < num_args ; i++) {
	if (strcmp(args[i].name, "traversalOn") == 0) {
	    _GeoChangeCache(w, (Boolean)args[i].value);
	    return ;
	}
    }
    remove that code, scale turns in on by default */


    if ((args == NULL) && (num_args != 0)) {
        XtAppErrorMsg(XtWidgetToApplicationContext(w),
		"invalidArgCount","xtSetValues",XtCXtToolkitError,
                "Argument count > 0 on NULL argument list in XtSetValues",
                 (String *)NULL, (Cardinal *)NULL);
    }

    /* Allocate and copy current widget into old widget */

    widgetSize = wc->core_class.widget_size;
    oldw = (Widget) XtStackAlloc(widgetSize, oldwCache);
    reqw = (Widget) XtStackAlloc (widgetSize, reqwCache);
    bcopy((char *) w, (char *) oldw, (int) widgetSize);

    /* Set resource values */

    SetValues((char*)w, (XrmResourceList *) wc->core_class.resources,
	wc->core_class.num_resources, args, num_args);

    bcopy ((char *) w, (char *) reqw, (int) widgetSize);

    /* assert: !XtIsShell(w) => (XtParent(w) != NULL) */
    hasConstraints = (!XtIsShell(w) && XtIsConstraint(XtParent(w)));

    /* Some widget sets apparently do ugly things by freeing the
     * constraints on some children, thus the extra test here */
    if (hasConstraints) {
	cwc = (ConstraintWidgetClass) XtClass(w->core.parent);
	if (w->core.constraints)
	    constraintSize = cwc->constraint_class.constraint_size;
	else constraintSize = 0;
    } else constraintSize = 0;
	
    if (constraintSize) {
	/* Allocate and copy current constraints into oldw */
	oldw->core.constraints = XtStackAlloc(constraintSize, oldcCache);
	reqw->core.constraints = XtStackAlloc(constraintSize, reqcCache);
	bcopy((char *) w->core.constraints, 
		(char *) oldw->core.constraints, (int) constraintSize);

	/* Set constraint values */
	SetValues((char*)w->core.constraints,
	    (XrmResourceList *)(cwc->constraint_class.resources),
	    cwc->constraint_class.num_resources, args, num_args);
	bcopy((char *) w->core.constraints,
	      (char *) reqw->core.constraints, (int) constraintSize);
    }

    /* Inform widget of changes, then inform parent of changes */
    redisplay = CallSetValues (wc, oldw, reqw, w, args, num_args);
    if (hasConstraints) {
	redisplay |= CallConstraintSetValues(cwc, oldw, reqw, w, args, num_args);
    }

    if (XtIsRectObj(w)) {
	/* Now perform geometry request if needed */
	geoReq.request_mode = 0;
	if (oldw->core.x	!= w->core.x) {
	    geoReq.x		= w->core.x;
	    w->core.x		= oldw->core.x;
	    geoReq.request_mode |= CWX;
	}
	if (oldw->core.y	!= w->core.y) {
	    geoReq.y		= w->core.y;
	    w->core.y		= oldw->core.y;
	    geoReq.request_mode |= CWY;
	}
	if (oldw->core.width	!= w->core.width) {
	    geoReq.width	= w->core.width;
	    w->core.width	= oldw->core.width;
	    geoReq.request_mode |= CWWidth;
	}
	if (oldw->core.height	!= w->core.height) {
	    geoReq.height	= w->core.height;
	    w->core.height	= oldw->core.height;
	    geoReq.request_mode |= CWHeight;
	}
	if (oldw->core.border_width != w->core.border_width) {
	    geoReq.border_width	    = w->core.border_width;
	    w->core.border_width    = oldw->core.border_width;
	    geoReq.request_mode	    |= CWBorderWidth;
	}
    
	if (geoReq.request_mode != 0) {
 	    /* Pass on any requests for unchanged geometry values */
 	    if (geoReq.request_mode !=
 		(CWX | CWY | CWWidth | CWHeight | CWBorderWidth)) {
 		for ( ; num_args != 0; num_args--, args++) {
 		    if (! (geoReq.request_mode & CWX) &&
 			strcmp(XtNx, args->name) == 0) {
 			geoReq.x = w->core.x;
 			geoReq.request_mode |= CWX;
 		    } else if (! (geoReq.request_mode & CWY) &&
 			       strcmp(XtNy, args->name) == 0) {
 			geoReq.y = w->core.y;
 			geoReq.request_mode |= CWY;
 		    } else if (! (geoReq.request_mode & CWWidth) &&
 			       strcmp(XtNwidth, args->name) == 0) {
 			geoReq.width = w->core.width;
 			geoReq.request_mode |= CWWidth;
 		    } else if (! (geoReq.request_mode & CWHeight) &&
 			       strcmp(XtNheight, args->name) == 0) {
 			geoReq.height = w->core.height;
 			geoReq.request_mode |= CWHeight;
 		    } else if (! (geoReq.request_mode & CWBorderWidth) &&
 			       strcmp(XtNborderWidth, args->name) == 0) {
 			geoReq.border_width = w->core.border_width;
 			geoReq.request_mode |= CWBorderWidth;
 		    }
 		}
 	    }

	    _GeoPrintTab();  /* newline */
	    _GeoPrintTrace(w,"XtSetValues sees some geometry changes for \"%s\".\n", XtName(w));
	    _GeoTabTrace();

	    do {
		result = _XtMakeGeometryRequest(w, &geoReq, &geoReply, 
						&cleared_rect_obj);
		if (result == XtGeometryYes || result == XtGeometryDone)
		    break;

		/* An Almost or No reply.  Call widget and let it munge
		   request, reply */
		if (wc->core_class.set_values_almost == NULL) {
		    XtAppWarningMsg(XtWidgetToApplicationContext(w),
			    "invalidProcedure","set_values_almost",
			  XtCXtToolkitError,
			  "set_values_almost procedure shouldn't be NULL",
			  (String *)NULL, (Cardinal *)NULL);
		    break;
		}
		if (result == XtGeometryNo) geoReply.request_mode = 0;

		_GeoPrintTrace(w,"calling SetValuesAlmost.\n");
	    
		(*(wc->core_class.set_values_almost))
		    (oldw, w, &geoReq, &geoReply);
	    } while (geoReq.request_mode != 0);

	    /* call resize proc if we changed size and parent
	     * didn't already invoke resize */
	    if (((w->core.width != oldw->core.width ||
		 w->core.height != oldw->core.height)
		&& result != XtGeometryDone))  {

		_GeoPrintTrace(w,"XtSetValues calls \"%s\"'s resize proc.\n",
			    XtName(w));
		
		if (wc->core_class.resize) (*(wc->core_class.resize))(w);
	    }

	    _GeoUnTabTrace();
	}

	/* Redisplay if needed.  No point in clearing if the window is
	 * about to disappear, as the Expose event will just go straight
	 * to the bit bucket. */
        if (XtIsWidget(w)) {
            /* widgets can distinguish between redisplay and resize, since
             the server will cause an expose on resize */
            if (redisplay && XtIsRealized(w) && !w->core.being_destroyed) {

		_GeoPrintTrace(w,"XtSetValues calls ClearArea on \"%s\".\n",XtName(w));
		
                XClearArea (XtDisplay(w), XtWindow(w), 0, 0, 0, 0, TRUE);
	    }
        } else { /*non-window object */
	  if (redisplay && ! cleared_rect_obj ) {
	      Widget pw = _XtWindowedAncestor(w);
	      if (XtIsRealized(pw) && !pw->core.being_destroyed) {
		  RectObj r = (RectObj)w;
		  int bw2 = r->rectangle.border_width << 1;

		  _GeoPrintTrace(w,"XtSetValues calls ClearArea on \"%s\"'s parent \"%s\".\n",
			      XtName(w),XtName(pw));
		
		  XClearArea (XtDisplay (pw), XtWindow (pw),
		      r->rectangle.x, r->rectangle.y,
		      r->rectangle.width + bw2,r->rectangle.height + bw2,TRUE);
	      }
	  }
        }
    }


    /* Free dynamic storage */
    if (constraintSize) {
        XtStackFree(oldw->core.constraints, oldcCache);
        XtStackFree(reqw->core.constraints, reqcCache);
    }
    XtStackFree((XtPointer)oldw, oldwCache);
    XtStackFree((XtPointer)reqw, reqwCache);

} /* XtSetValues */
