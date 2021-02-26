
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: ResInd.c /main/17 1996/06/07 11:40:05 daniel $"
#endif
#endif


/* (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#include <limits.h>
#include <ctype.h>		/* for isascii, isspace */
#include <Xm/ScreenP.h>
#include <Xm/ManagerP.h>
#include <Xm/TraitP.h>
#include <Xm/UnitTypeT.h>
#include "RepTypeI.h"
#include "ResIndI.h"
#include "ScreenI.h"
#include "XmI.h"

#ifndef NO_XP
#include "PrintSI.h"
#endif

/*********** Macros and Internal Types   ************/

#define MAKEINT(float_value) ((int) (((float_value) > 0.0) ? \
            ((float_value) + 0.5) : \
            ((float_value) - 0.5)))
 
#define FLOATABS(float_value) ((float_value) > 0.0 ? \
            (float_value) : \
            ((float_value) * -1.0))
 
#define OVERFLOW(float_value) \
            (FLOATABS(float_value) > (float) INT_MAX) ? 1 : 0

/********    Static Function Declarations    ********/

static void FromPixels(
               Widget widget,
               int offset,
               XtArgVal *value,
               unsigned char orientation);
static XmImportOperator ToPixels(
                 Widget widget,
                 int offset,
                 XtArgVal *value,
                 unsigned char orientation);
static XmParseResult ParseUnitString(
                String spec,
                float *float_value, /* RETURN */
                int *unit_type);    /* RETURN */
/********    End Static Function Declarations    ********/


/**********************************************************************
 *
 * XmConvertStringToUnits
 * Public interface to convert string <value><unit> specifications
 *     Note: The default unitType if it is not specified in the
 *			string is XmPIXELS.
 *     parse_error currently returns True for both "real" parsing
 *			errors and overflows. Its type has been declared as an
 *			XtEnum to allow returning more descriptive values in the
 *			future, if desired.
 * 
 **********************************************************************/

int
XmConvertStringToUnits(
        Screen *screen, 
        String spec,
        int orientation,
        int to_type,
        XtEnum *parse_error) /* RETURN */
{
  int value;
  _XmDisplayToAppContext(DisplayOfScreen(screen));

  _XmAppLock(app);
  value = _XmConvertStringToUnits(screen, spec, XmPIXELS,
				 orientation, to_type, parse_error);
  _XmAppUnlock(app);
  return value;
}


/**********************************************************************
 *
 * _XmConvertFloatUnitsToIntUnits
 * Given a floating point value and a units type, converts the value
 * to an integer value and unit type that minimizes information loss.
 *
 * Returns True if the conversion was a success. Returns False on 
 * overflow.
 * 
 **********************************************************************/

int
_XmConvertFloatUnitsToIntUnits(int unitType, float unitValue,
			       int *intUnitType, float *intUnitValue,
			       int default_from_type)
{
    float multiplier;

    switch (unitType) 
    {
      case XmINCHES:
	multiplier = 1000.0;
	*intUnitType = Xm1000TH_INCHES;
	break;
      case XmCENTIMETERS:
	multiplier = 1000.0;
	*intUnitType = Xm100TH_MILLIMETERS;
	break;
      case XmMILLIMETERS:
	multiplier = 100.0;
	*intUnitType = Xm100TH_MILLIMETERS;
	break;
      case XmPOINTS:
	multiplier = 100.0;
	*intUnitType = Xm100TH_POINTS;
	break;
      case XmFONT_UNITS:
	multiplier = 100.0;
	*intUnitType = Xm100TH_FONT_UNITS;
	break;
      case XmPIXELS:
	multiplier = 1.0;
	*intUnitType = XmPIXELS;
	break;
      default:
	multiplier = 1.0;
	*intUnitType = default_from_type;
	break;
    };
    
    /* Normalize to units _XmConvertUnits will understand. */
    *intUnitValue = multiplier * unitValue;
    if (OVERFLOW(*intUnitValue)) {
	return(False);
    }
    return(True);
}

/**********************************************************************
 *
 * _XmConvertStringToUnits
 * Does the real work of converting string unit specifications
 * 
 **********************************************************************/

int
_XmConvertStringToUnits(
        Screen *screen,
        String spec,
        int default_from_type,
        int orientation,
        int to_type,
        XtEnum *parse_error) /* RETURN */
{
    float floatValue, convertValue;
    int unitType, fromType;  /* the type that we will pass to XmConvertUnits */
 
    if (parse_error)
      *parse_error = False;
 
    switch (ParseUnitString (spec, &floatValue, &unitType))
      {
      default:
      case XmPARSE_ERROR:
	if (parse_error)
	  *parse_error = True;
        return 0;

      case XmPARSE_NO_UNITS:
	fromType = default_from_type;
	convertValue = floatValue;
	if (OVERFLOW(convertValue)) {
	    return 0;
	}
	break;
 
      case XmPARSE_UNITS_OK:
	if (unitType == to_type)  /* No conversion required */
	  return (MAKEINT(floatValue));
	if (_XmConvertFloatUnitsToIntUnits(unitType, floatValue,
					   &fromType, &convertValue,
					   default_from_type) == False)
	  return 0;
      }
    return _XmConvertUnits(screen, orientation, fromType,
			   MAKEINT(convertValue), to_type);
}

/**********************************************************************
 *
 * XmeParseUnits
 *
 **********************************************************************/
XmParseResult
XmeParseUnits(String spec, int *unitType)
{
  /*
   * Figure out which unit type was specified using same
   * method used in ResConvert.c. The performance of this
   * could be improved, but the readability of the code
   * would suffer. Test cases on a Sparc II indicate in
   * the worst case, the tests below take up about 30%
   * of the total conversion time.
   */
  
  /* an empty string here means unit_type wasn't specified */
  if (*spec == '\0')
    return XmPARSE_NO_UNITS;
  else if (XmeNamesAreEqual (spec, "pix") ||
	   XmeNamesAreEqual (spec, "pixel") ||
	   XmeNamesAreEqual (spec, "pixels"))
    *unitType = XmPIXELS;
  else if ( XmeNamesAreEqual (spec, "in") ||
	   XmeNamesAreEqual (spec, "inch") ||
	   XmeNamesAreEqual (spec, "inches"))
    *unitType = XmINCHES;
  else if ( XmeNamesAreEqual (spec, "cm") ||
	   XmeNamesAreEqual (spec, "centimeter") ||
	   XmeNamesAreEqual (spec, "centimeters"))
    *unitType = XmCENTIMETERS;
  else if ( XmeNamesAreEqual (spec, "mm") ||
	   XmeNamesAreEqual (spec, "millimeter") ||
	   XmeNamesAreEqual (spec, "millimeters"))
    *unitType = XmMILLIMETERS;
  else if ( XmeNamesAreEqual (spec, "pt") ||
	   XmeNamesAreEqual (spec, "point") ||
	   XmeNamesAreEqual (spec, "points"))
    *unitType = XmPOINTS;
  else if ( XmeNamesAreEqual (spec, "fu") ||
	   XmeNamesAreEqual (spec, "font_unit") ||
	   XmeNamesAreEqual (spec, "font_units"))
    *unitType = XmFONT_UNITS;
  else
    return XmPARSE_ERROR;

  return XmPARSE_UNITS_OK;
}


/**********************************************************************
 *
 * ParseUnitString
 * Internal routine for parsing <float><units> specifications
 *
 **********************************************************************/

 
static XmParseResult
ParseUnitString(
    String spec,
    float *float_value, /* RETURN */
    int *unit_type)     /* RETURN */
{
  char * string = spec;
  double power;
  int sign;
  char c;
  
  /* Skip leading whitespace */
  while ((isascii(c=*string)) && (isspace(c))) string++;
  
  /* Check for sign */
  sign = (*string == '-')? -1 : 1;
  if ((*string == '+') || (*string == '-'))
    string++;
  
  /*
   * Do floating point arithmetic here whether we have a decimal
   * point or not to avoid parsing an extra time.
   */
  
  /* Parse digits left of decimal point */
  *float_value = 0;
  while ((*string >= '0') && (*string <= '9')) {
    *float_value = 10.0 * *float_value + (*string - '0');
    string++;
  }
  
  /* Handle decimal point */
  if (*string == '.')
    string++;
  
  /* Parse digits right of decimal point */
  power = 1.0;
  while ((*string >= '0') && (*string <= '9')) {
    *float_value = 10.0 * *float_value + (*string - '0');
    power *= 10;
    string++;
  }
  
  *float_value = sign * *float_value / power;
  
  /* Skip whitespace between float and unit */
  while ((isascii(c=*string)) && (isspace(c))) string++;
  
  return(XmeParseUnits(string, unit_type));
}


 
/**********************************************************************
 *
 * _XmConvertUnits
 * Does the real work of conversion.
 * 
 **********************************************************************/
int 
_XmConvertUnits(
        Screen *screen,
        int dimension,
        register int from_type,
        register int from_val,
        register int to_type )
{
  /*
   * from_val_in_mm is actually from_val_in_1000thmillimeters for accuracy
   *     likewise for mm_per_pixel
   */
  register int from_val_in_mm = 0;
  register int mm_per_pixel = 0 ; /* time 100000 */
  int font_unit;
  
  
  /*  Do error checking  */
  
  if (!XmRepTypeValidValue(XmRID_ORIENTATION, 
			   (unsigned char) dimension, 
			   (Widget) NULL))
    return (0);
  
  if (!XmRepTypeValidValue( XmRID_UNIT_TYPE, from_type, (Widget)NULL))
    return (0);
  
  if (!XmRepTypeValidValue( XmRID_UNIT_TYPE, to_type, (Widget)NULL))
    return (0);
  
  if (screen == NULL)
    return (0);
  
  /*  Check for type to same type conversions  */
  
  if (from_type == to_type)
    return (from_val);
  
  /*  Get the screen dimensional data  */
  
#ifndef NO_XP
  /* specialize for printing */
  _XmProcessLock();
  /* if there is at least one print shell around, look if this
     screen is from it and get the proper resolution */
  if (_XmPrintShellCounter) {
      XmPrintShellWidget pshell = NULL ;

      XFindContext(DisplayOfScreen(screen), (XID)screen, 
		   _XmPrintScreenToShellContext, (XPointer *) &pshell);
      if (pshell)
	  mm_per_pixel = 25400/ pshell->print.print_resolution ;
  }
  _XmProcessUnlock();
#endif

  if (!mm_per_pixel) {
      if (dimension == XmHORIZONTAL)
	  mm_per_pixel = (WidthMMOfScreen(screen) * 1000) / 
	      WidthOfScreen(screen);
      else
	  mm_per_pixel = (HeightMMOfScreen(screen) * 1000) / 
	      HeightOfScreen(screen);
  }


  if (from_type == XmPIXELS)
    from_val_in_mm = from_val * mm_per_pixel ;
  else if (from_type == Xm100TH_POINTS)
    from_val_in_mm = (from_val * 353) / 100;
  else if (from_type == XmPOINTS)
    from_val_in_mm = (from_val * 353) ;
  else if (from_type == Xm1000TH_INCHES)
    from_val_in_mm = (from_val * 254) / 10;
  else if (from_type == XmINCHES)
    from_val_in_mm = (from_val * 254) * 100;
  else if (from_type == Xm100TH_MILLIMETERS)
    from_val_in_mm = from_val * 10;
  else if (from_type == XmMILLIMETERS)
    from_val_in_mm = from_val * 1000;
  else if (from_type == XmCENTIMETERS)
    from_val_in_mm = from_val * 10000;
  else if (from_type == Xm100TH_FONT_UNITS)
    {
      font_unit = _XmGetFontUnit (screen, dimension);
      from_val_in_mm = from_val * font_unit * mm_per_pixel / 100;
    }
  else if (from_type == XmFONT_UNITS)
    {
      font_unit = _XmGetFontUnit (screen, dimension);
      from_val_in_mm = from_val * font_unit * mm_per_pixel ;
    }
  
  
  if (to_type == XmPIXELS)
    return (from_val_in_mm / mm_per_pixel);
  else if (to_type == Xm100TH_POINTS)
    return ((from_val_in_mm * 100) / 353);
  else if (to_type == XmPOINTS)
    return ((from_val_in_mm ) / 353);
  else if (to_type == Xm1000TH_INCHES)
    return ((from_val_in_mm * 10) / 254);
  else if (to_type == XmINCHES)
    return ((from_val_in_mm / 100) / 254);
  else if (to_type == Xm100TH_MILLIMETERS)
    return (from_val_in_mm / 10);
  else if (to_type == XmMILLIMETERS)
    return (from_val_in_mm / 1000);
  else if (to_type == XmCENTIMETERS)
    return (from_val_in_mm / 10000);
  else  if (to_type == Xm100TH_FONT_UNITS)
    {
      font_unit = _XmGetFontUnit (screen, dimension);
      return ((from_val_in_mm * 100) / (mm_per_pixel * font_unit));
    }
  else /* to_type == XmFONT_UNITS */
    {
      font_unit = _XmGetFontUnit (screen, dimension);
      return ((from_val_in_mm ) / (mm_per_pixel * font_unit));
    }
}




/**********************************************************************
 *
 *  XmConvertUnits
 *  Convert a value in from_type representation to a value in
 *  to_type representation using the screen to look up the screen
 *  resolution and the dimension to denote whether to use the
 *  horizontal or vertical resolution data.
 *
 **********************************************************************/
int 
XmConvertUnits(
        Widget widget,
        int dimension,
        register int from_type,
        register int from_val,
        register int to_type )
{
  int value;
  Screen *screen;
  _XmWidgetToAppContext(widget);
    
  _XmAppLock(app);
  screen = XtScreen(widget);
  value = _XmConvertUnits(screen, dimension, from_type, from_val, to_type);
  _XmAppUnlock(app);
  return value;
}



/*********************************************************************
 *
 *  XmCvtToVerticalPixels
 *      Convert from a specified unit type to pixel type using
 *      the vertical resolution of the screen.
 *
 *********************************************************************/
int 
XmCvtToHorizontalPixels(
        Screen *screen,
        register int from_val,
        register int from_type )
{
  int value;
  _XmDisplayToAppContext(DisplayOfScreen(screen));

  _XmAppLock(app);
  value = _XmConvertUnits(screen, XmHORIZONTAL, from_type, from_val, XmPIXELS);
  _XmAppUnlock(app);
  return value;
}

/**********************************************************************
 *
 *  ToPixels
 *  Convert from a non-pixel unit type to pixels using the 
 *  horizontal orientation/resolution of the screen.
 *
 **********************************************************************/
/*ARGSUSED*/
static XmImportOperator 
ToPixels(
        Widget widget,
        int offset,		/* unused */
        XtArgVal *value,
    unsigned char orientation )
{
  Screen * screen = XtScreen (widget);
  register unsigned char unit_type;
  
  /*  Get the unit type of the widget  */
  unit_type = _XmGetUnitType(widget) ;
  
  /*  Check for type to same type conversions  */
  if (unit_type == XmPIXELS) return XmSYNTHETIC_LOAD;
  
  /* otherwise, let _XmConvertUnits do the work */
  *value = (XtArgVal) _XmConvertUnits (screen,
				       (int) orientation,
				       unit_type,
				       (int) (*value),
				       XmPIXELS);
  return XmSYNTHETIC_LOAD;
}

/**********************************************************************
 *
 *  XmeToHorizontalPixels
 *  Convert from a non-pixel unit type to pixels using the 
 *  horizontal resolution of the screen.  This function is
 *  accessed from a widget.
 *
 **********************************************************************/
XmImportOperator 
XmeToHorizontalPixels(
        Widget widget,
        int offset,
        XtArgVal *value )
{
   XmImportOperator ret_value;
   _XmWidgetToAppContext(widget);

   _XmAppLock(app);
   ret_value = ToPixels(widget, offset, value, XmHORIZONTAL) ;
   _XmAppUnlock(app);
   return ret_value;
}

/*********************************************************************
 *
 *  XmCvtToVerticalPixels
 *      Convert from a specified unit type to pixel type using
 *      the vertical resolution of the screen.
 *
 *********************************************************************/
int 
XmCvtToVerticalPixels(
        Screen *screen,
        register int from_val,
        register int from_type )
{
  int value;
  _XmDisplayToAppContext(DisplayOfScreen(screen));

  _XmAppLock(app);
  value = _XmConvertUnits(screen, XmVERTICAL, from_type, from_val, XmPIXELS);
  _XmAppUnlock(app);
  return value;
}



/********************************************************************
 *
 *  XmeToVerticalPixels
 *  Convert from non-pixel unit type to pixels using the 
 *  vertical resolution of the screen.  This function is
 *  accessed from a widget.
 *
 **********************************************************************/
XmImportOperator 
XmeToVerticalPixels(
        Widget widget,
        int offset,
        XtArgVal *value )
{
  XmImportOperator ret_value;
  _XmWidgetToAppContext(widget);

  _XmAppLock(app);
  ret_value = ToPixels(widget, offset, value, XmVERTICAL) ;
  _XmAppUnlock(app);
  return ret_value;
}


/*********************************************************************
*
*
*  XmCvtFromHorizontalPixels
*      Convert from a pixel unit type to specified type using
*      the horizontal resolution of the screen.
*
 **********************************************************************/
int 
XmCvtFromHorizontalPixels(
        Screen *screen,
        register int from_val,
        register int to_type )
{
  int value;
  _XmDisplayToAppContext(DisplayOfScreen(screen));

  _XmAppLock(app);
  value = _XmConvertUnits(screen, XmHORIZONTAL, XmPIXELS, from_val, to_type);
  _XmAppUnlock(app);
  return value;
}

/**********************************************************************
 *
 *  FromPixels
 *  Convert from a pixel unit type to a non-pixels using the 
 *  given orientation/resolution of the screen.
 *
 **********************************************************************/
/*ARGSUSED*/
static void 
FromPixels(
        Widget widget,
        int offset,		/* unused */
        XtArgVal *value,
    unsigned char orientation)
{
  Screen * screen = XtScreen (widget);
  unsigned char unit_type;
  
  /*  Get the unit type of the widget  */
  unit_type = _XmGetUnitType(widget);
  
  /*  Check for type to same type conversions  */
  if (unit_type == XmPIXELS) return;
  
  /* otherwise, let _XmConvertUnits do the work */
  *value = (XtArgVal) _XmConvertUnits (screen,
				       (int) orientation,
				       XmPIXELS,
				       (int) (*value),
				       unit_type);
}


/**********************************************************************
 *
 *  XmeFromHorizontalPixels
 *  Convert from a pixel unit type to a non-pixels using the 
 *  horizontal resolution of the screen.  This function is
 *  accessed from a getvalues hook table.
 *
 **********************************************************************/
void 
XmeFromHorizontalPixels(
        Widget widget,
        int offset,
        XtArgVal *value )
{
  _XmWidgetToAppContext(widget);
  _XmAppLock(app);
  FromPixels(widget, offset, value, XmHORIZONTAL);
  _XmAppUnlock(app);
}


/*********************************************************************
*
*
*  XmCvtFromVerticalPixels
*      Convert from a pixel unit type to specified type using
*      the horizontal resolution of the screen.
*
 **********************************************************************/
int 
XmCvtFromVerticalPixels(
        Screen *screen,
        register int from_val,
        register int to_type )
{
  int value;
  _XmDisplayToAppContext(DisplayOfScreen(screen));

  _XmAppLock(app);
  value = _XmConvertUnits(screen, XmVERTICAL, XmPIXELS, from_val, to_type);
  _XmAppUnlock(app);
  return value;
}



/**********************************************************************
 *
 *  XmeFromVerticalPixels
 *  Convert from pixel unit type to non-pixels using the 
 *  vertical resolution of the screen.  This function is
 *  accessed from a getvalues hook table.
 *
 **********************************************************************/
void 
XmeFromVerticalPixels(
        Widget widget,
        int offset,
        XtArgVal *value )
{
  _XmWidgetToAppContext(widget);
  _XmAppLock(app);
  FromPixels(widget, offset, value, XmVERTICAL);
  _XmAppUnlock(app);
}



/**********************************************************************
 *
 * _XmUnitTypeDefault
 * This procedure is called as the resource default XtRCallProc
 * to default the unit type resource.  This procedure supports 
 * the propagation of unit type from parent to child.
 *
 **********************************************************************/
/*ARGSUSED*/
void 
_XmUnitTypeDefault(
        Widget widget,
        int offset,		/* unused */
        XrmValue *value )
{
  static unsigned char unit_type;
  
  value->size = sizeof(unit_type);
  value->addr = (XPointer) &unit_type;
  
  if (XmIsManager(widget->core.parent))
    unit_type = 
      ((XmManagerWidget)(widget->core.parent))->manager.unit_type;
  else
    unit_type = XmPIXELS;
}

/**********************************************************************
 *
 * _XmGetUnitType
 * This function takes care of the class of the widget being passed
 * and look in the appropriate field.
 *
 **********************************************************************/
unsigned char
_XmGetUnitType(
        Widget widget)
{
    XmSpecUnitTypeTrait trait;

    if ((trait = (XmSpecUnitTypeTrait) 
	 XmeTraitGet((XtPointer) XtClass(widget), 
		     XmQTspecifyUnitType)) != NULL)
      {
	return trait->getUnitType(widget) ;
      }
    else if (XmIsExtObject(widget))
      {
	/* CR 8952: Look on the real widget class too. */
	XmExtObject extObj = (XmExtObject)widget;
	Widget	    parent = extObj->ext.logicalParent;

	if ((trait = (XmSpecUnitTypeTrait) 
	     XmeTraitGet((XtPointer) XtClass(parent),
			 XmQTspecifyUnitType)) != NULL)
	  return trait->getUnitType(parent);
      }

    return XmPIXELS ;
}
