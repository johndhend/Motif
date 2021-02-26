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
static char rcsid[] = "$XConsortium: TestUilInit.c /main/7 1995/07/14 10:57:36 drk $"
#endif
#endif

#include <AutoMessages.h>
#include <signal.h>
#include <X11/IntrinsicP.h>
#include "testlib.h"
  
/* This is used for checking Synchronization 
   used with performance testing */
#ifdef DEBUG
typedef struct {
  Boolean synchronous;
} SynchronRec;

SynchronRec Synch;

#define Offset(field) XtOffsetOf(SynchronRec, field)

XtResource resources[] = {
  {"synchronous", "Synchronous", XtRBoolean, sizeof(Boolean),
   Offset(synchronous), XtRImmediate, (XtPointer) FALSE}
};

#undef Offset

XrmOptionDescRec optionDesc[] = {
  {"-synchronous", "*synchronous", XrmoptionNoArg, (XtPointer) "on"}};

if (synchronous == False)  {
  OverridePerformanceMonitor = True;
}
#endif


/*************************************************************************
 *                                                                       *
 *      Name:           CommonTestUilInit()                              *
 *								 	 *
 *	Purpose:	This routine calls CommonTestInit wich  will     *
 *                      Initialize Xt, create an app context, create     *
 *			a connection to the display and create a         *
 *			toplevel application shell.  The routine also    *
 *                      sets up for Uil.                                 *
 *									 *
 *	Return:		Nothing						 *
 *									 *
 *************************************************************************/

void CommonTestUilInit(int argc, char **argv)
     
{

  CommonTestInit(argc, argv);

  MrmRegisterClass(0, NULL, "XmCreateArrowButton", 
		   ArrowButtonCreate,
		   (WidgetClass)&xmArrowButtonWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateArrowButtonGadget", 
		   ArrowButtonGadgetCreate,
		   (WidgetClass)&xmArrowButtonGadgetClass);
  MrmRegisterClass(0, NULL, "XmCreateBulletinBoard", 
		   BulletinBoardCreate,
		   (WidgetClass)&xmBulletinBoardWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateBulletinBoardDialog", 
		   BulletinBoardDialogCreate,
		   (WidgetClass)&xmBulletinBoardWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateCascadeButton", 
		   CascadeButtonCreate,
		   (WidgetClass)&xmCascadeButtonWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateCascadeButtonGadget", 
		   CascadeButtonGadgetCreate,
		   (WidgetClass)&xmCascadeButtonGadgetClass);
  MrmRegisterClass(0, NULL, "XmCreateCommand", 
		   CommandCreate,
		   (WidgetClass)&xmCommandWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateDialogShell", 
		   DialogShellCreate,
		   (WidgetClass)&xmDialogShellWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateDrawingArea", 
		   DrawingAreaCreate,
		   (WidgetClass)&xmDrawingAreaWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateDrawnButton", 
		   DrawnButtonCreate,
		   (WidgetClass)&xmDrawnButtonWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateErrorDialog", 
		   ErrorDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateMessageBox",
		   MessageBoxCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateMessageDialog",
		   MessageDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateInformationDialog",
		   InformationDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateTemplateDialog",
		   TemplateDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateQuestionDialog",
		   QuestionDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateWarningDialog",
		   WarningDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateWorkingDialog",
		   WorkingDialogCreate,
		   (WidgetClass)&xmMessageBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateFileSelectionBox",
		   FileSelectionBoxCreate,
		   (WidgetClass)&xmFileSelectionBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateFileSelectionDialog",
		   FileSelectionDialogCreate,
		   (WidgetClass)&xmFileSelectionBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateForm",
		   FormCreate,
		   (WidgetClass)&xmFormWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateFormDialog",
		   FormDialogCreate,
		   (WidgetClass)&xmFormWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateFrame",
		   FrameCreate,
		   (WidgetClass)&xmFrameWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateLabel",
		   LabelCreate,
		   (WidgetClass)&xmLabelWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateLabelGadget",
		   LabelGadgetCreate,
		   (WidgetClass)&xmLabelGadgetClass);
  MrmRegisterClass(0, NULL, "XmCreateList",
		   ListCreate,
		   (WidgetClass)&xmListWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateScrolledList",
		   ScrolledListCreate,
		   (WidgetClass)&xmListWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateMainWindow",
		   MainWindowCreate,
		   (WidgetClass)&xmMainWindowWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateMenuShell",
		   MenuShellCreate,
		   (WidgetClass)&xmMenuShellWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateMenuBar",
		   MenuBarCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateOptionMenu",
		   OptionMenuCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePopupMenu",
		   PopupMenuCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePulldownMenu",
		   PulldownMenuCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateRowColumn",
		   RowColumnCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateRadioBox",
		   RadioBoxCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateWorkArea",
		   WorkAreaCreate,
		   (WidgetClass)&xmRowColumnWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePanedWindow",
		   PanedWindowCreate,
		   (WidgetClass)&xmPanedWindowWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePromptDialog",
		   PromptDialogCreate,
		   (WidgetClass)&xmSelectionBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateSelectionBox",
		   SelectionBoxCreate,
		   (WidgetClass)&xmSelectionBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateSelectionDialog",
		   SelectionDialogCreate,
		   (WidgetClass)&xmSelectionBoxWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePushButton",
		   PushButtonCreate,
		   (WidgetClass)&xmPushButtonWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreatePushButtonGadget",
		   PushButtonGadgetCreate,
		   (WidgetClass)&xmPushButtonGadgetClass);
  MrmRegisterClass(0, NULL, "XmCreateScale",
		   ScaleCreate,
		   (WidgetClass)&xmScaleWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateScrollBar",
		   ScrollBarCreate,
		   (WidgetClass)&xmScrollBarWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateScrolledText",
		   ScrolledTextCreate,
		   (WidgetClass)&xmTextWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateText",
		   TextCreate,
		   (WidgetClass)&xmTextWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateScrolledWindow",
		   ScrolledWindowCreate,
		   (WidgetClass)&xmScrolledWindowWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateSeparator",
		   SeparatorCreate,
		   (WidgetClass)&xmSeparatorWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateSeparatorGadget",
		   SeparatorGadgetCreate,
		   (WidgetClass)&xmSeparatorGadgetClass);
  MrmRegisterClass(0, NULL, "XmCreateTextField",
		   TextFieldCreate,
		   (WidgetClass)&xmTextFieldWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateToggleButton",
		   ToggleButtonCreate,
		   (WidgetClass)&xmToggleButtonWidgetClass);
  MrmRegisterClass(0, NULL, "XmCreateToggleButtonGadget",
		   ToggleButtonGadgetCreate,
		   (WidgetClass)&xmToggleButtonGadgetClass);  
  MrmRegisterClass(0, NULL, "XmCreateComboBoxWidgetClass",
		   ComboBoxCreate,
		   (WidgetClass)&xmComboBoxWidgetClass);  
  MrmRegisterClass(0, NULL, "XmCreateSpinBoxWidgetClass",
		   SpinBoxCreate,
 		   (WidgetClass)&xmSpinBoxWidgetClass);  
  MrmRegisterClass(0, NULL, "XmCreateNotebookWidgetClass",
		   NotebookCreate,
		   (WidgetClass)&xmNotebookWidgetClass);  
  MrmRegisterClass(0, NULL, "XmCreateContainerWidgetClass",
		   ContainerCreate,
		   (WidgetClass)&xmContainerWidgetClass);  
  MrmRegisterClass(0, NULL, "XmCreateIconGadgetClass",
		   IconGadgetCreate,
		   (WidgetClass)&xmIconGadgetClass);  


/* The may be useful for checking Synchronization
   use with performance testing */
#ifdef DEBUG

     XtGetApplicationResources(Shell1, (XtPointer) &Synch, 
			       resources,
			       XtNumber(resources), (Arg *) NULL, 0 );

     printf("sync = %d\n", Synch.synchronous);

#endif /* DEBUG */

}




