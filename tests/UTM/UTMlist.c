/* $TOG: UTMlist.c /main/7 1999/11/17 12:49:08 jff $ */
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

#include <Xm/XmP.h>
#include <Xm/TransferP.h>
#include "UTMtransfer.h"

extern TransferDataRec datums[];
extern unsigned int num_datums;

Atom type = None;

void 
SetTypeCB(Widget w, XtPointer client_data, XtPointer call_data)
{
  char *in;

  in = (char *) client_data;

  if (strlen(in) == 0)
    type = XmeGetEncodingAtom(w);
  else if (strcmp(in, "NONE") == 0)
    type = None;
  else
    type = XInternAtom(XtDisplay(w), in, False);
}
/*******************************************************************
 * FindRightButton
 * 
 * picks the correct button for the type option menu to display
 * note that the names are ATOMNAMEbutton,  so it prepends a 
 * '*' in front and 'button' after the name before looking up
 * the button.
 ******************************************************************/

static Widget
FindRightButton(char* atom_string)
{
  char buffer[80];

  strcpy(buffer, "*");
  strcat(buffer, atom_string);
  strcat(buffer, "button");

  return(XtNameToWidget(MainW, buffer));
}

/* Put a 32bit or larger value into the Label widget */

static void 
Display32bit(XtPointer value)
{
  char temp[80];
  XmString strtmp;
  unsigned long data;
  int n;
  Arg args[2];
  
  data = * (unsigned long *) value;

  sprintf(temp, "0x%lx", data);

  strtmp = XmStringCreateLocalized(temp);

  n = 0;
  XtSetArg(args[n], XmNlabelString, strtmp); n++;
  XtSetValues(labelV, args, n);

  XmStringFree(strtmp);
}

/*********************************************************************
 * ListSelectItem
 * 
 * this is called when the user selects an item in the list.  It takes
 * the type of the item and decides how to display it in the Label
 * widget
 *********************************************************************/

void 
ListSelectItemCB(Widget w, XtPointer ignore, XtPointer call_data)
{
  XmListCallbackStruct *listcb;

  int index;
  Atom XA_COMPOUND_TEXT = XInternAtom(XtDisplay(w), XmSCOMPOUND_TEXT, False),
       XA_PIXEL = XInternAtom(XtDisplay(w), "PIXEL", False),
       XA_LOCALE_TEXT = XmeGetEncodingAtom(w),
       XA_MOTIF_CS = XInternAtom(XtDisplay(w), 
                                 XmS_MOTIF_COMPOUND_STRING, False),
       XA_MOTIF_RT = XInternAtom(XtDisplay(w), 
                                 XmS_MOTIF_RENDER_TABLE, False);
  Widget mem = (Widget) NULL;
  char *targetname;
  XmString tmp;
  int n;
  Arg args[2];

  listcb = (XmListCallbackStruct *) call_data;

  index = listcb -> item_position;
  if (index < 1) return;

  index --;

  /* Put name of target into display field */
  targetname = GetSafeAtom(XtDisplay(w), datums[index].target);

  if (targetname == NULL) targetname = XtNewString("Unknown");

  tmp = XmStringCreateLocalized(targetname);

  n = 0;
  XtSetArg(args[n], XmNlabelString, tmp); n++;
  XtSetValues(labelN, args, n);

  XmStringFree(tmp);
  tmp = NULL;

  XtFree(targetname);

  /* Put type of target into display field */
  type = datums[index].type;

  if (type == XA_ATOM ||
      type == XInternAtom(XtDisplay(w), "ATOM_PAIR", False)) {
    char str[80];
    Atom *alist = (Atom *) datums[index].value;

    mem = FindRightButton("ATOM");

    if (type == XA_ATOM) {
      sprintf(str, "%s", GetSafeAtom(XtDisplay(w), alist[0]));
    } else {
      sprintf(str, "%s %s", 
              GetSafeAtom(XtDisplay(w), alist[0]),
              GetSafeAtom(XtDisplay(w), alist[1]));
    }
    
    tmp = XmStringCreateLocalized(str);

  } else if (type == XA_INTEGER || type == XA_PIXEL) {
    if (type == XA_INTEGER)
      mem = FindRightButton("INTEGER");
    else
      mem = FindRightButton("PIXEL");

    Display32bit(datums[index].value );

  } else if (type == XInternAtom(XtDisplay(w), "SPAN", False)) {
    unsigned long *data = (unsigned long *) datums[index].value;
    char str[80];
    
    sprintf(str, "%ld %ld", data[0], data[1]);

    tmp = XmStringCreateLocalized(str);

  } else if (type == XA_STRING) {
    mem = FindRightButton("STRING");
    
    tmp = XmStringCreateLocalized(datums[index].value);

  } else if (type == XA_COMPOUND_TEXT) {
    char *str;
    mem = FindRightButton("COMPOUND_TEXT");

    str = XtMalloc(datums[index].length + 1);
    strncpy(str, datums[index].value, datums[index].length);
    str[datums[index].length] = 0;

    tmp = XmCvtCTToXmString(str);
    XtFree((XtPointer) str);


  } else if (type == XA_LOCALE_TEXT) {
    mem = FindRightButton("LOCALE_TEXT");

    tmp = XmStringCreateLocalized(datums[index].value);

  } else if (type == XA_DRAWABLE || type == XA_WINDOW ||
             type == XA_COLORMAP) {
    if (type == XA_DRAWABLE)
      mem = FindRightButton("DRAWABLE");
    else if (type == XA_COLORMAP)
      mem = FindRightButton("COLORMAP");
    else
      mem = FindRightButton("WINDOW");

    if (type != XA_COLORMAP)
      Display32bit(&(datums[index].value));
    else
      Display32bit(datums[index].value);
  } else if (type == XA_MOTIF_CS) {
    mem = FindRightButton("_MOTIF_COMPOUND_STRING");

    tmp = XmCvtByteStreamToXmString(datums[index].value);


  } else {
    char *typestring;
    char buffer[80];

    mem = FindRightButton("unknown");

    typestring = GetSafeAtom(XtDisplay(w), type);
    sprintf(buffer, "Unknown type %s (%d) found", typestring, type);
    XFree(typestring);

    tmp = XmStringCreateLocalized(buffer);

  }

  if (NULL != tmp) {
	  n = 0;
	  XtSetArg(args[n], XmNlabelString, tmp); n++;
	  XtSetValues(labelV, args, n);

	  XmStringFree(tmp);
  }

  if (mem != (Widget) NULL)
    XtVaSetValues(typeOM, XmNmenuHistory, mem, NULL);
}
