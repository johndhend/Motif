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
/*   $XConsortium: List9.h /main/8 1995/07/13 18:22:24 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define NITEMS	 4
#define NITEMS2  15

#define	GetKbdItemPos		1
#define	SetKbdItemPos		2
#define PosSelected		3
#define PosToBounds		4

/*  Global Variables  */

char *Istrings[NITEMS] = {
	"XmListGetKbdItemPos()",
	"XmListSetKbdItemPos()",
	"XmListPosSelected()",
	"XmListPosToBounds()"
};


char *Istrings2[NITEMS2] = {
	"1)  Item1",
	"2)  Item2",
	"3)  Item3",
	"4)  Item4",
	"5)  Item5",
	"6)  Item6",
	"7)  Item7",
	"8)  Item8",
	"9)  Item9",
	"10) Item10",
	"11) Item11",
	"12) Item12",
	"13) Item13",
	"14) Item14",
	"15) Item15"
	};

Widget	  Scale;
Widget    List1, List2;
Widget	  Label1, Label2;
Widget	  Form;
Widget	  Frame;
Widget	  RowCol;
Widget 	  ApplyB, ClearB;
Widget	  Toggle_AddMode;
Widget	  Label_Selection, Label_Position, Label_Bounds;
Widget    Single, Multiple, Browse, Extended;
Widget 	  RadioBox;

int	  function;
int	  count = 0;
int 	  arg_count = 0;
int       position = 0;

/*  Private Functions  */


static void 	SSelCB_List1(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	ApplyCB(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	ClearCB(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	ScaleCB(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	NotifyCB(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	AddModeCB(Widget w, XtPointer client_data, 
						XtPointer call_data);
static void  	CHSPolicyCB(Widget w, unsigned char client_data, 
			    			XtPointer call_data);
static void  	MulSelCB_List2(Widget w, XtPointer client_data, 
			    			XtPointer call_data);
static Widget	CreateToggle(Widget parent, char *label);

