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
/*   $XConsortium: List7.h /main/9 1995/07/13 18:20:42 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#ifndef MOTIF1_1
#define NITEMS	 14
#else
#define NITEMS	 13
#endif /* MOTIF1_1 */

#define NITEMS2  15

#define	AddItems		1
#define	AddItem			2
#define	AddItemUnselected	3
#define	DeleteItem		4
#define	DeleteItems		5
#define	DeleteItemsPos		6
#define	DeletePos		7
#define	DeleteAllItems		8
#define	DeselectAllItems	9
#define	DeselectItem		10
#define	DeselectPos		11
#define	SelectItem		12
#define	SelectPos		13

#ifndef MOTIF1_1
#define	AddItemsUnselected	14
#endif /* MOTIF1_1 */

/*  Global Variables  */

char *Istrings[NITEMS] = {
	"XmListAddItems()",
	"XmListAddItem()",
	"XmListAddItemUnselected()",
	"XmListDeleteItem()",
	"XmListDeleteItems()",
	"XmListDeleteItemsPos()",
	"XmListDeletePos()",
	"XmListDeleteAllItems()",
	"XmListDeselectAllItems()",
	"XmListDeselectItem()",
	"XmListDeselectPos()",
	"XmListSelectItem()",
	"XmListSelectPos()",
#ifndef MOTIF1_1
	"XmListAddItemsUnselected()"
#endif /* MOTIF1_1 */
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
Widget	  ToggleB;
Widget 	  ApplyB, ClearB;

XmString  CS_ItemList[50];

int	  function;
int	  count = 0;
int 	  arg_count = 0;
int       position = 0;

Boolean	  notify = True;

/*  Private Functions  */


static void  SSelCB_List1(Widget w, XtPointer client_data,
				    	XtPointer call_data);
static void  MulSelCB_List2(Widget w, XtPointer client_data,
				     	XtPointer call_data);
static void  ApplyCB(Widget w, XtPointer client_data,
			       		XtPointer call_data);
static void  ClearCB(Widget w, XtPointer client_data,
			       		XtPointer call_data);
static void  ScaleCB(Widget w, XtPointer client_data,
			       		XtPointer call_data);
static void  NotifyCB(Widget w, XtPointer client_data,
			       		XtPointer call_data);

