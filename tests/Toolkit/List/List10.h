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
/*   $XConsortium: List10.h /main/8 1995/07/13 18:15:17 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#define NITEMS 28

char *Istrings[] = {
    "1) DrawnButton",           "2) Label",
    "3) List",                  "4) PushButton",
    "5) Separator",             "6) ArrowButton",
    "7) ScrollBar",             "8) Text",
    "9) ScrolledText",          "10) DrawnButton",
    "11) DrawingArea",          "12) MainWindow",
    "13) ScrolledWindow",       "14) Scale",
    "15) Command",              "16) FileSelectionBox",
    "17) MessageBox",           "18) QuestionDialog",
    "19) BulletinBoard",        "20) Form",
    "21) RowColumn",            "22) ScrolledList",
    "23) ToggleButton",         "24) ToggleButtonGadget",
    "25) PushButtonGadget",     "26) ArrowButtonGadget",
    "27) TextField",            "28) PanedWindow"
};

XmString   ItemList[NITEMS];
XmString   my_selected[5];

/*  Global Variables  */

Widget    	List1;
Widget    	Label_List1, Label_Selected_List;
Widget	  	Form;
Widget		TextF_AddSL, TextF_AddIL;
Widget		Label_AddSL, Label_AddIL;
Widget 	  	Browse, Single, Multiple, Extended;
Widget	  	Constant, Variable, VariableP, Possible;
Widget	  	Selected_List, Selected_ListSV;
Widget	  	Label_Selected_Count, Label_Select_Type, Label_Item_Pos;
Widget	  	Label_Item, Label_Reason, Label_Item_Count, Label_RowCol;
Widget	  	Label_Selected_Items, Label_Selected, Label_Resources;
Widget	  	RowCol1, RowCol2, Destroy_Push;
Widget		Frame1, Frame2;
Widget		Selected_List;
Widget		Toggle_Selected;
Widget	  	PushB_Update, PushB_GetSelected, RadioBox;

XmFontList 	font_list;

Boolean		Add_Unselected = False;

/*  Private Functions  */


static void  	BrSiDeSelCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	ExtSelCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	MulSelCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	ChangeFontCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	CHSPolicyCB(Widget w, unsigned char client_data, 
			    caddr_t call_data);
static void  	UpdateCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	SelectedCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	AddSLCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	AddILCB(Widget w, caddr_t client_data, caddr_t call_data);
static void  	ToggleCB(Widget w, caddr_t client_data, caddr_t call_data);
static void	Update_selected_items(XmString *item_list, int item_count,
				       Boolean single_or_browse,
				       int *selected_pos);
static void 	CreateOptions();
static void 	CreateCallbackInfo();
static void 	ChangeLabel(Widget w, char string[50]);
static Widget   CreateToggleButton(Widget parent, char *label);
static Widget   CreatePushButton(Widget parent, char *label);

