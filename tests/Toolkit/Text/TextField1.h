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
/*   $XConsortium: TextField1.h /main/9 1995/07/13 19:34:19 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

static char starting_string_text[] = "This is the starting string";

#define NITEMS	 10

#define	GetEditable		1
#define	SetEditable		2
#define	GetMaxLength		3
#define	SetMaxLength		4
#define	GetLastPosition		5
#define	SetInsertionPosition	6
#define	GetBaseline		7
#define	XYToPos			8
#define	PosToXY			9

/*  Global Variables  */

char *Istrings[NITEMS] = {
	"XmTextFieldGetEditable()",
	"XmTextFieldSetEditable()",
	"XmTextFieldGetMaxLength()",
	"XmTextFieldSetMaxLength()",
	"XmTextFieldGetLastPosition()",
	"XmTextFieldSetInsertionPosition()",
	"XmTextFieldGetBaseline()",
	"XmTextFieldXYToPos()",
	"XmTextFieldPosToXY()",
};


Widget	  Scale1, Scale2;
Widget    List1;
Widget    TextF1, StatText;
Widget	  Label1, Label2, Label3, Label4, Label5;
Widget	  Form;
Widget	  ToggleB;
Widget 	  ApplyB, ClearB;

static int	  function;
static int	  count = 0;
static int 	  scale1_val = 0;
static int 	  scale2_val = 0;
static int       position = 0;

static Boolean	  torf = True;

/*  Private Functions  */


static void  SSelCB_List1(Widget w, XtPointer client_data,
			    	XtPointer call_data);
static void  MulSelCB_List2(Widget w, XtPointer client_data,
			     	XtPointer call_data);
static void  ApplyCB(Widget w, XtPointer client_data,
		       		XtPointer call_data);
static void  ClearCB(Widget w, XtPointer client_data,
		       		XtPointer call_data);
static void  Scale1CB(Widget w, XtPointer client_data,
		       		XtPointer call_data);
static void  Scale2CB(Widget w, XtPointer client_data,
		       		XtPointer call_data);
static void  TorFCB(Widget w, XtPointer client_data,
		       		XtPointer call_data);

