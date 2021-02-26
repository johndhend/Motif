
#include <localdef.h>

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
static char rcsid[] = "$TOG: Mrminit.c /main/14 1999/05/19 15:25:33 mgreess $"
#endif
#endif

/*                                                                      *
 * (c) Copyright 1996 Hewlett-Packard Company                           *
 * (c) Copyright 1996 International Business Machines Corp.             *
 * (c) Copyright 1996 Sun Microsystems, Inc.                            *
 * (c) Copyright 1996 Novell, Inc.                                      *
 * (c) Copyright 1989, 1990, 1996 Digital Equipment Corporation.	*
 * (c) Copyright 1996 FUJITSU LIMITED.					*
 * (c) Copyright 1996 Hitachi.						*
 */

/*
 *++
 *  FACILITY:
 *
 *      UIL Resource Manager (URM):
 *
 *  ABSTRACT:
 *
 *	This contains only the top-level routine MrmIntialize. It can be 
 *	modified by vendors as needed to add or remove widgets being \
 *	initialized for URM facilities. This routine is normally accessible to
 *	and used by an application at runtime to access URM facilities.
 *
 *--
 */


/*
 *
 *  INCLUDE FILES
 *
 */

#include <Mrm/MrmAppl.h>
#include <Mrm/Mrm.h>

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <X11/CompositeP.h>
#include <X11/ConstrainP.h>
#include <X11/ShellP.h>
#include <X11/VendorP.h>
#include <X11/RectObjP.h>

#ifdef DXM_V11
#include <DXm/DXmHelpB.h>
#include <DXm/DXmHelpBp.h>
#endif

#include <Xm/XmP.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/LabelGP.h>
#include <Xm/LabelP.h>
#include <Xm/BulletinB.h>
#include <Xm/BulletinBP.h>
#include <Xm/RowColumn.h>
#include <Xm/RowColumnP.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>
#include <Xm/ArrowBGP.h>
#include <Xm/ArrowBP.h>
#include <Xm/AtomMgr.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/CascadeBGP.h>
#include <Xm/CascadeBP.h>
#include <Xm/SelectioBP.h>
#include <Xm/SelectioB.h>
#include <Xm/Command.h>
#include <Xm/CommandP.h>
#include <Xm/CutPaste.h>
#include <Xm/DialogS.h>
#include <Xm/DialogSP.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawingAP.h>
#include <Xm/DrawnB.h>
#include <Xm/DrawnBP.h>
#include <Xm/FileSB.h>
#include <Xm/FileSBP.h>
#include <Xm/Form.h>
#include <Xm/FormP.h>
#include <Xm/Frame.h>
#include <Xm/FrameP.h>
#include <Xm/List.h>
#include <Xm/ListP.h>
#include <Xm/MainW.h>
#include <Xm/MainWP.h>
#include <Xm/MenuShell.h>
#include <Xm/MenuShellP.h>
#include <Xm/MessageB.h>
#include <Xm/MessageBP.h>
#include <Xm/PanedW.h>
#include <Xm/PanedWP.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/PushBGP.h>
#include <Xm/PushBP.h>
#include <Xm/SashP.h>
#include <Xm/Scale.h>
#include <Xm/ScaleP.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrollBarP.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrolledWP.h>
#include <Xm/SeparatoG.h>
#include <Xm/SeparatoGP.h>
#include <Xm/Separator.h>
#include <Xm/SeparatorP.h>
#include <Xm/Text.h>
#include <Xm/TextFP.h>
#include <Xm/TextP.h>
#include <Xm/TextOutP.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/ToggleBGP.h>
#include <Xm/ToggleBP.h>
#include <Xm/ComboBoxP.h>
#include <Xm/ContainerP.h>
#include <Xm/NotebookP.h>
#include <Xm/SpinBP.h>
#include <Xm/SSpinBP.h>
#include <Xm/IconGP.h>

#include <Xm/XmRenderTI.h>
#include <Xm/XmTabListI.h>


/*
 *
 *  TABLE OF CONTENTS
 *
 *	MrmInitialize			Initialize URM internals before use
 *
 */


/*
 *
 *  OWN VARIABLE DECLARATIONS
 *
 */

/*
 * The following flag is set to indicate successful URM initialization
 */
static	Boolean	urm__initialize_complete = FALSE;


/*
 *++
 *  PROCEDURE DESCRIPTION:
 *
 *	MrmInitialize must be called in order to prepare an application to
 *	use URM widget fetching facilities. It initializes the internal data
 *	structures (creating the mapping from class codes to the creation
 *	routine for each builtin widget class) which URM needs in order to 
 *	successfully perform type conversion on arguments, and successfully 
 *	access widget creation facilities. MrmInitialize must be called before
 *	any widgets are	created, whether by URM's fetch mechanisms or directly
 *	by the application. It may be called before or after XtInitialize, and
 *	multiple calls after the first one are benign (no-ops).
 *
 *  FORMAL PARAMETERS:
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

void MrmInitialize (void)
{

  /*
   *  Local variables
   */

  _MrmProcessLock();
  /*
   * Initialize only once
   */
  if ( urm__initialize_complete ) 
    {
      _MrmProcessUnlock();
      return ;
    }
 
  /*
   * Initialize the class descriptors for all the known widgets.
   */
#ifdef DXM_V11
  MrmRegisterClass
    (0, NULL, "DXmCreateHelpWidget", DXmCreateHelp,
     (WidgetClass)&dxmhelpwidgetclassrec);
#endif

  MrmRegisterClass
    (0, NULL, "XmCreateArrowButton", XmCreateArrowButton,
     (WidgetClass)&xmArrowButtonClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateArrowButtonGadget", XmCreateArrowButtonGadget,
     (WidgetClass)&xmArrowButtonGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateBulletinBoard", XmCreateBulletinBoard,
     (WidgetClass)&xmBulletinBoardClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateBulletinBoardDialog", XmCreateBulletinBoardDialog,
     (WidgetClass)&xmBulletinBoardClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateCascadeButton", XmCreateCascadeButton,
     (WidgetClass)&xmCascadeButtonClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateCascadeButtonGadget", XmCreateCascadeButtonGadget,
     (WidgetClass)&xmCascadeButtonGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateCommand", XmCreateCommand,
     (WidgetClass)&xmCommandClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateCommandDialog", XmCreateCommandDialog,
     (WidgetClass)&xmCommandClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateDialogShell", XmCreateDialogShell,
     (WidgetClass)&xmDialogShellClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateDrawingArea", XmCreateDrawingArea,
     (WidgetClass)&xmDrawingAreaClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateDrawnButton", XmCreateDrawnButton,
     (WidgetClass)&xmDrawnButtonClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateFileSelectionBox", XmCreateFileSelectionBox,
     (WidgetClass)&xmFileSelectionBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateFileSelectionDialog", XmCreateFileSelectionDialog,
     (WidgetClass)&xmFileSelectionBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateForm", XmCreateForm,
     (WidgetClass)&xmFormClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateFormDialog", XmCreateFormDialog,
     (WidgetClass)&xmFormClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateFrame", XmCreateFrame,
     (WidgetClass)&xmFrameClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateLabel", XmCreateLabel,
     (WidgetClass)&xmLabelClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateLabelGadget", XmCreateLabelGadget,
     (WidgetClass)&xmLabelGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateList", XmCreateList,
     (WidgetClass)&xmListClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateScrolledList", XmCreateScrolledList,
     (WidgetClass)&xmListClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateMainWindow", XmCreateMainWindow,
     (WidgetClass)&xmMainWindowClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateMenuShell", XmCreateMenuShell,
     (WidgetClass)&xmMenuShellClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateMessageBox", XmCreateMessageBox,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateMessageDialog", XmCreateMessageDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateErrorDialog", XmCreateErrorDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateInformationDialog", XmCreateInformationDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateQuestionDialog", XmCreateQuestionDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateTemplateDialog", XmCreateTemplateDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateWarningDialog", XmCreateWarningDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateWorkingDialog", XmCreateWorkingDialog,
     (WidgetClass)&xmMessageBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePushButton", XmCreatePushButton,
     (WidgetClass)&xmPushButtonClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePushButtonGadget", XmCreatePushButtonGadget,
     (WidgetClass)&xmPushButtonGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateRowColumn", XmCreateRowColumn,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateWorkArea", XmCreateWorkArea,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateRadioBox", XmCreateRadioBox,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateMenuBar", XmCreateMenuBar,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateOptionMenu", XmCreateOptionMenu,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePopupMenu", XmCreatePopupMenu,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePulldownMenu", XmCreatePulldownMenu,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSimpleCheckBox", XmCreateSimpleCheckBox,
     (WidgetClass)&xmRowColumnClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateScale", XmCreateScale,
     (WidgetClass)&xmScaleClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateScrolledWindow", XmCreateScrolledWindow,
     (WidgetClass)&xmScrolledWindowClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateScrollBar", XmCreateScrollBar,
     (WidgetClass)&xmScrollBarClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSelectionBox", XmCreateSelectionBox,
     (WidgetClass)&xmSelectionBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSelectionDialog", XmCreateSelectionDialog,
     (WidgetClass)&xmSelectionBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePromptDialog", XmCreatePromptDialog,
     (WidgetClass)&xmSelectionBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSeparator", XmCreateSeparator,
     (WidgetClass)&xmSeparatorClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSeparatorGadget", XmCreateSeparatorGadget,
     (WidgetClass)&xmSeparatorGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateText", XmCreateText,
     (WidgetClass)&xmTextClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateTextField", XmCreateTextField,
     (WidgetClass)&xmTextFieldClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateScrolledText", XmCreateScrolledText,
     (WidgetClass)&xmTextClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateToggleButton", XmCreateToggleButton,
     (WidgetClass)&xmToggleButtonClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateToggleButtonGadget", XmCreateToggleButtonGadget,
     (WidgetClass)&xmToggleButtonGadgetClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreatePanedWindow", XmCreatePanedWindow,
     (WidgetClass)&xmPanedWindowClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateComboBox", XmCreateComboBox,
     (WidgetClass)&xmComboBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateContainer", XmCreateContainer,
     (WidgetClass)&xmContainerClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateNotebook", XmCreateNotebook,
     (WidgetClass)&xmNotebookClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSpinBox", XmCreateSpinBox,
     (WidgetClass)&xmSpinBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateSimpleSpinBox", XmCreateSimpleSpinBox,
     (WidgetClass)&xmSimpleSpinBoxClassRec);

  MrmRegisterClass
    (0, NULL, "XmCreateIconGadget", XmCreateIconGadget,
     (WidgetClass)&xmIconGadgetClassRec);

  MrmRegisterClassWithCleanup
    (0, NULL, "_XmCreateRenderTable", _XmCreateRenderTable,
     (WidgetClass)NULL, XmRenderTableFree);

  MrmRegisterClassWithCleanup
    (0, NULL, "_XmCreateRendition", _XmCreateRendition,
     (WidgetClass)NULL, XmRenditionFree);

  MrmRegisterClass
    (0, NULL, "_XmCreateTabList", _XmCreateTabList,
     (WidgetClass)NULL);

  MrmRegisterClass
    (0, NULL, "_XmCreateTab", _XmCreateTab,
     (WidgetClass)NULL);


  /*
   * Initialization complete
   */
  urm__initialize_complete = TRUE ;
  _MrmProcessUnlock();

}
