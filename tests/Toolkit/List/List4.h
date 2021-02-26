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
/*   $XConsortium: List4.h /main/9 1995/07/13 18:18:45 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#ifndef MOTIF1_1
#define NITEMS	 4
#else
#define NITEMS	 2
#endif /* MOTIF1_1 */

#define NITEMS2  5
#define NITEMS3  4

/*  Global Variables  */

#ifndef MOTIF1_1
char *Istrings[NITEMS] = {
	"XmListReplaceItems()",
	"XmListReplaceItemPos()",
	"XmListReplaceItemsUnselected()",
	"XmListReplaceItemPosUnselected()"
};
#else
char *Istrings[NITEMS] = {
	"XmListReplaceItems()",
	"XmListReplaceItemPos()"
};
#endif /* MOTIF1_1 */

char *Istrings2[NITEMS2] = {
	"Item1",
	"Item2",
	"Item3",
	"Item4",
	"Item5"
	};

char *Istrings3[NITEMS3] = {
	"Item6",
	"Item7",
	"Item8",
	"Item9"
	};

Widget	  Scale;
Widget    List1;
Widget    List2;
Widget    List3;
Widget	  Label1;
Widget	  Label2;
Widget	  Label3;
Widget	  Form;
Widget 	  ApplyB;
Widget 	  ClearB;
XmString  CS_ItemList1[50];
XmString  CS_ItemList2[50];
int	  count1 = 0;
int	  count2 = 0;
int 	  arg_count = 0;
int	  function = 0;

/*  Private Functions  */


static void  SSelCB_List1(Widget w, XtPointer client_data,
				    XtPointer call_data);
static void  MulSelCB_List1(Widget w, XtPointer client_data,
				    XtPointer call_data);
static void  MulSelCB_List2(Widget w, XtPointer client_data,
				    XtPointer call_data);
static void  ApplyCB(Widget w, XtPointer client_data,
				    XtPointer call_data);
static void  ClearCB(Widget w, XtPointer client_data,
				    XtPointer call_data);
static void  ScaleCB(Widget w, XtPointer client_data,
				    XtPointer call_data);

