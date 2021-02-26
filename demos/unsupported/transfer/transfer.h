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
static char *rcsidtransferH = "$XConsortium: transfer.h /main/6 1995/07/14 09:47:34 drk $";
#endif
#endif

#ifndef _Transfer_h
#define _Transfer_h

typedef enum { Mprimary, Msecondary, Mclipboard, Mnamed } TransferMode;

#define _NAMED "NAMED_TRANSFER_ATOM"

extern TransferMode Tmode;

extern Widget editBox;
extern Widget toplevel, list, target, text1, text2, typeOM;
extern Widget op, omd, onamed, defer, text_display;
extern Widget format_om, format_s, format_l, format_t,
  format_cs, format_id, format_ih;

extern void targetDestinationCallback(Widget w, XtPointer ignore,
				      XmDestinationCallbackStruct *cs);
extern void targetConvertCallback(Widget w, XtPointer ignore,
				  XmConvertCallbackStruct *cs);
extern void inputCallback(Widget w, XtPointer ignore,
			  XmDrawingAreaCallbackStruct *cbstruct);
extern void ListSelectItem(Widget w, XtPointer ignore, 
			   XmListCallbackStruct *listcb);
extern void SetType(Widget w, char *in, XtPointer ignore);
extern void SetFormat(Widget, char, XtPointer);
extern void SetValue(Widget widget, char *ignore, 
		     XmAnyCallbackStruct *callback_data);
extern void RemoveValue(Widget widget, char *ignore, 
		     XmAnyCallbackStruct *callback_data);
extern void quitCB(Widget widget, char *ignore, 
		     XmAnyCallbackStruct *callback_data);
extern void setMode(Widget widget, int param, XmAnyCallbackStruct *);
extern void cut(Widget widget, char *ignore, XmAnyCallbackStruct *);
extern void copy(Widget widget, char *ignore, XmAnyCallbackStruct *);
extern void paste(Widget widget, char *ignore, XmAnyCallbackStruct *);
extern void pasteMove(Widget widget, char *ignore, XmAnyCallbackStruct *);
extern void deferCB(Widget widget, char *ignore,
		    XmToggleButtonCallbackStruct *callback_data);
extern char* GetSafeAtom(Display *display, Atom a);
extern char* ConvertXmStringToString(XmString);
extern void EditItem(Widget w, int param, XtPointer ignore);
extern void unmanageCB(Widget, Widget, XtPointer);
extern void manageCB(Widget, Widget, XtPointer);

typedef struct _transferdatarec {
  Atom		target;
  Atom		type;
  unsigned long	length;
  int		format;
  XtPointer	value;
  Boolean	deferred;
} TransferDataRec, *TransferData;



extern Widget create_mainWindow_widget(char * name,
				       Widget parent);
extern Widget create_editbox_widget(char * name,
				    Widget parent);

#endif /* _Transfer_h */
