/* $TOG: UTMtransfer.h /main/6 1999/11/17 12:49:34 jff $ */
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

#ifndef _Transfer_h
#define _Transfer_h

#include <Xm/TransferP.h>

typedef struct _transferdatarec {
  Atom          target;
  Atom          type;
  unsigned long length;
  int           format;
  XtPointer     value;
} TransferDataRec, *TransferData;

typedef enum { Mprimary, Msecondary, Mclipboard } TransferMode;

extern TransferMode Tmode;

extern Widget MainW, list, target, labelV, labelN, typeOM;
extern Widget OwnPrimLG, OwnSecLG;


extern void ListSelectItemCB(Widget w, XtPointer client_data, 
			     XtPointer call_data);
extern void SetTypeCB(Widget w, XtPointer client_data, XtPointer call_data);
extern void TargetDestinationCB(Widget w, XtPointer ignore, 
				XtPointer call_data);
extern void TargetConvertCB(Widget w, XtPointer ignore, 
				XtPointer call_data);
char *GetSafeAtom(Display *display, Atom a);
char *GetStringFrom(XtEnum operation);


#endif /* _Transfer_h */

