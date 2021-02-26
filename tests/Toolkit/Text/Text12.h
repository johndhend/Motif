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
/*   $TOG: Text12.h /main/10 1997/09/18 11:00:08 csn $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

static char starting_string_text[] = "This is the starting string";

#ifndef	MOTIF1_1
#define NITEMS	 13
#else
#define NITEMS	 9
#endif	/* MOTIF1_1 */

#define	GetSelectionPosition	1
#define	GetSelection		2
#define	SetSelection		3
#define	ClearSelection		4
#define	Insert			5
#define	SetAddMode		6
#define	GetString		7
#define	SetString		8
#define	Replace			9

#ifndef	MOTIF1_1
#define	FindString		10
#define	GetSubstring		11
#define	DisableRedisplay	12
#define	EnableRedisplay		13
#endif	/* MOTIF1_1 */

/*  Global Variables  */

char *Textstrings[NITEMS] = {
	"XmTextGetSelectionPosition()",
	"XmTextGetSelection()",
	"XmTextSetSelection()",
	"XmTextClearSelection()",
	"XmTextInsert()",
	"XmTextSetAddMode()",
	"XmTextGetString()",
	"XmTextSetString()",
#ifndef	MOTIF1_1
	"XmTextReplace()",
	"XmTextFindString()",
	"XmTextGetSubstring()",
	"XmTextDisableRedisplay()",
	"XmTextEnableRedisplay()"
#else
	"XmTextReplace()"
#endif	/* MOTIF1_1 */
};

Widget	Scale1, Scale2;
Widget 	List1;
Widget 	Text1, StatText;
Widget	Label1, Label2, Label3, Label4, Label5;
Widget	Form;
Widget	ToggleB;
Widget 	ApplyB, ClearB;

static  int	function;
static  int	count = 0;
static  int 	scale1_val = 0;
static  int 	scale2_val = 0;
static  int    	position = 0;

static  Boolean	torf = True;

#ifndef	MOTIF1_1

Widget	Scale3, ToggleB2, Label6;
int	scale3_val = 0;
XmTextDirection	forb = XmTEXT_FORWARD;

#endif	/* MOTIF1_1 */


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
#ifndef	MOTIF1_1
static void  Scale3CB(Widget w, XtPointer client_data,
			       		XtPointer call_data);
static void  ForBCB(Widget w, XtPointer client_data,
					XtPointer call_data);
#endif	/* MOTIF1_1 */

