/* $XConsortium: Notebook3.h /main/5 1995/07/15 21:07:33 drk $ */
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



/* This is the header file for the test Notebook1.c */



#define TRUE 1
#define FALSE 0
#define NUM_PAGE 30
#define NUM_MAJOR_TAB 60
#define NUM_MINOR_TAB 60
#define NUM_STATUS_AREA 60
#define NUM_PAGE_SCROLLER 60



/* This is an enumeration of values for the "client_data" parameter to the
   routine SetNotebookValues. */

enum             { CURRENT_PAGE_NUMBER = 0,
		   FIRST_PAGE_NUMBER,
		   LAST_PAGE_NUMBER,
		   BACK_PAGE_NUMBER,
		   BACK_PAGE_SIZE,
		   BINDING_WIDTH,
		   INNER_MARGIN_WIDTH,
		   INNER_MARGIN_HEIGHT,
		   MAJOR_TAB_SPACING,
		   MINOR_TAB_SPACING,
		   ORIENTATION,
		   BACK_PAGE_PLACEMENT,
		   BINDING_TYPE,
		   BACK_PAGE_FOREGROUND,
		   BACK_PAGE_BACKGROUND,
		   FRAME_BACKGROUND,
		   FRAME_SHADOW_THICKNESS,
		   SET_VALUES_NOTEBOOK } ClientDataNotebook;


/* This is an enumeration of values for the "client_data" parameter to
   the function "CreateAndSetChildValues" */
enum               {
                     CHILD_TYPE=0,
		     PAGE_NUMBER,
		     RESIZABLE,
		     CREATE_CHILD,
		     SET_VALUES_CHILD
		     
		     } ClientDataChild;


/* This is an enumenration of the possible values for the resource 
   XmNorientation. */

enum               { HORIZONTAL = 0,
		     VERTICAL } Orientation_Types;


/* This is an enumenration of the possible values for the resource 
   XmNbackPagePlacement. */

enum                { BOTTOM_RIGHT = 0,
		      BOTTOM_LEFT,
		      TOP_RIGHT,
		      TOP_LEFT } Back_Page_Placement_Types;


/* This is an enumenration of the possible values for the resource 
   XmNbindingType. */

enum                 { NONE = 0,
		       SOLID,
		       SPIRAL,
		       PIXMAP,
		       PIXMAP_OVERLAP_ONLY } Binding_Types;


/* This is an enumeration of possible values for the resource XmNchildType */

enum                  {  PAGE = 0,
			 MAJOR_TAB,
			 MINOR_TAB,
			 STATUS_AREA,
			 PAGE_SCROLLER
		       } ChildTypes;


/* This is an enumeration of offsets for the array of scales */
enum                   { CurrentPageNumber = 0,
			 FirstPageNumber,
			 LastPageNumber,
			 BackPageNumber,
			 BackPageSize,
			 BindingWidth,
			 InnerMarginWidth,
			 InnerMarginHeight,
			 MajorTabSpacing,
			 MinorTabSpacing,
			 FrameShadowThickness
			} Scale_Offsets;


/* Mechanism used to get the creation function associated with a widget. */
typedef struct {
                 char *name;
		 Widget (*CreateFunction) (Widget, char *, ArgList, Cardinal);
	       } WidgetItem;



WidgetItem WidgetStruct[] =  {
                   "XmArrowButton", XmCreateArrowButton,   
                   "XmArrowButtonGadget", XmCreateArrowButtonGadget,  
		   "XmDrawnButton", XmCreateDrawnButton,   
		   "XmDrawingArea", XmCreateDrawingArea,
                   "XmFileSelectionBox",XmCreateFileSelectionBox,
                   "XmForm", XmCreateForm,
		   "XmFrame", XmCreateFrame,
		   "XmLabel", XmCreateLabel,  
		   "XmLabelGadget", XmCreateLabelGadget,   
                   "XmList", XmCreateList  ,
		   "XmMainWindow", XmCreateMainWindow,
                   "XmMessageBox", XmCreateMessageBox,   
		   "XmPanedWindow",XmCreatePanedWindow,
                   "XmPushButton",   XmCreatePushButton,
		   "XmPushButtonGadget", XmCreatePushButtonGadget,  
		   "XmRowColumn", XmCreateRowColumn,
		   "XmScale", XmCreateScale,
                   "XmScrollBar", XmCreateScrollBar,  
		   "XmScrolledText", XmCreateScrolledText,
                   "XmSelectionBox", XmCreateSelectionBox,  
		   "XmSeparator", XmCreateSeparator,                     
                   "XmSeparatorGadget",XmCreateSeparatorGadget, 
		   "XmText", XmCreateText,
                   "XmTextField", XmCreateTextField,   
		   "XmToggleButton", XmCreateToggleButton,   
                   "XmToggleButtonGadget", XmCreateToggleButtonGadget,  
		   "XmScrolledWindow", XmCreateScrolledWindow
		   };




char *WidgetNames[] = {
                   "XmArrowButton",   
                   "XmArrowButtonGadget",   
		   "XmDrawnButton",   
		   "XmDrawingArea",
                   "XmFileSelectionBox",
                   "XmForm",
		   "XmFrame",
		   "XmLabel",   
		   "XmLabelGadget",   
                   "XmList",   
		   "XmMainWindow",
                   "XmMessageBox",   
		   "XmPanedWindow",
                   "XmPushButton",   
		   "XmPushButtonGadget",   
		   "XmRowColumn",
		   "XmScale",
                   "XmScrollBar",   
		   "XmScrolledText",
                   "XmSelectionBox",   
		   "XmSeparator",                      
                   "XmSeparatorGadget",   
		   "XmText",
                   "XmTextField",   
		   "XmToggleButton",   
                   "XmToggleButtonGadget",  
		   "XmScrolledWindow",

		   };


int num_widgets = XtNumber(WidgetNames);



