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
static char rcsid[] = "$XConsortium: AutoWrappers.c /main/11 1995/07/14 11:29:16 drk $"
#endif
#endif

#include <AutoMessages.h>

#include "mvslib.h"
#include "xislib.h"
#include "Automation.h"

#include <X11/IntrinsicP.h>
#include <X11/Core.h>
#include <X11/CoreP.h>

extern MvsWidgetInfoRecord      *Shell_info;

Boolean	HaveScrolledWindow = False;	/* Variable to note creation of Scrolled
					   Window for ClickKey events with
					   Clip Winodw */


static Widget CreateWidget(
                        Widget p,
                        char *name,
                        ArgList args,
                        Cardinal n,
                        MvsWidgetClassInfo *class);



static Widget
CreateWidget(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n,
        MvsWidgetClassInfo *class )
{
    MvsWidgetInfoRecord *w_info = NULL;
    MvsWidgetInfoRecord *widget_info = NULL;

    w_info = mvsWidgetToWidgetInfo(p);

    if (w_info == NULL)
	AutoMessage(_AutoMessages[WARNMSG7]);

    widget_info = mvsCreateWidget(class, w_info, name, DontUseCommonArgs, 
       				  args, n, NULL);	
    return(widget_info->widget);
}


Widget
ArrowButtonCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmArrowButtonWidgetClass));
}



Widget
ArrowButtonGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmArrowButtonGadgetClass));
}


Widget
BulletinBoardCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmBulletinBoardWidgetClass));
}


Widget
BulletinBoardDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmBulletinBoardDialogWidgetClass));
}


Widget
CascadeButtonCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmCascadeButtonWidgetClass));
}


Widget
CascadeButtonGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmCascadeButtonGadgetClass));
}


Widget
ComboBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmComboBoxWidgetClass));
}


Widget
DropDownComboBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmDropDownComboBoxWidgetClass));
}


Widget
DropDownListComboBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmDropDownListComboBoxWidgetClass));
}


Widget
NotebookCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmNotebookWidgetClass));
}

Widget
SpinBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmSpinBoxWidgetClass));
}

Widget
ContainerCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmContainerWidgetClass));
}


Widget
IconGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmIconGadgetClass));
}


Widget
CommandCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmCommandWidgetClass));
}


Widget
DialogShellCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmDialogShellWidgetClass));
}


Widget
DrawingAreaCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmDrawingAreaWidgetClass));
}


Widget
DrawnButtonCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmDrawnButtonWidgetClass));
}


Widget
ErrorDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmErrorDialogWidgetClass));
}


Widget
FileSelectionBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmFileSelectionBoxWidgetClass));
}


Widget
FileSelectionDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmFileSelectionDialogWidgetClass));
}


Widget
FormCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmFormWidgetClass));
}


Widget
FormDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmFormDialogWidgetClass));
}


Widget
FrameCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmFrameWidgetClass));
}


Widget
InformationDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmInformationDialogWidgetClass));
}


Widget
LabelCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmLabelWidgetClass));
}


Widget
LabelGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmLabelGadgetClass));
}


Widget
ListCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmListWidgetClass));
}


Widget
MainWindowCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmMainWindowWidgetClass));
}


Widget
MenuBarCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmMenuBarWidgetClass));
}


Widget
MenuShellCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmMenuShellWidgetClass));
}


Widget
MessageBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmMessageBoxWidgetClass));
}


Widget
MessageDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmMessageDialogWidgetClass));
}


Widget
OptionMenuCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmOptionMenuWidgetClass));
}


Widget
PanedWindowCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPanedWindowWidgetClass));
}


Widget
PopupMenuCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPopupMenuWidgetClass));
}


Widget
PromptDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPromptDialogWidgetClass));
}


Widget
PulldownMenuCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPulldownMenuWidgetClass));
}


Widget
PushButtonCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPushButtonWidgetClass));
}


Widget
PushButtonGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmPushButtonGadgetClass));
}


Widget
QuestionDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmQuestionDialogWidgetClass));
}


Widget
RadioBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmRadioBoxWidgetClass));
}


Widget
RowColumnCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmRowColumnWidgetClass));
}


Widget
ScaleCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmScaleWidgetClass));
}


Widget
ScrollBarCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmScrollBarWidgetClass));
}


Widget
ScrolledListCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmScrolledListWidgetClass));
}


Widget
ScrolledTextCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmScrolledTextWidgetClass));
}


Widget
ScrolledWindowCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    HaveScrolledWindow = True;
    return(CreateWidget(p, name, args, n, iXmScrolledWindowWidgetClass));
}


Widget
SelectionBoxCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmSelectionBoxWidgetClass));
}


Widget
SelectionDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmSelectionDialogWidgetClass));
}


Widget
SeparatorCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmSeparatorWidgetClass));
}


Widget
SeparatorGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmSeparatorGadgetClass));
}


Widget
TemplateDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmTemplateDialogWidgetClass));
}


Widget
TextCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmTextWidgetClass));
}


Widget
TextFieldCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmTextFieldWidgetClass));
}


Widget
ToggleButtonCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmToggleButtonWidgetClass));
}


Widget
ToggleButtonGadgetCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmToggleButtonGadgetClass));
}


Widget
WarningDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmWarningDialogWidgetClass));
}


Widget
WorkingDialogCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmWorkingDialogWidgetClass));
}


Widget
WorkAreaCreate(
        Widget p,
        char *name,
        ArgList args,
        Cardinal n )
{
    return(CreateWidget(p, name, args, n, iXmWorkAreaWidgetClass));
}


Widget
PopupShellCreate(
        String name,
        WidgetClass widget_class,
        Widget parent,
        ArgList args,
        Cardinal num_args )
{
    MvsWidgetInfoRecord *w_info = NULL;
    MvsWidgetInfoRecord *widget_info = NULL;

    w_info = mvsWidgetToWidgetInfo(parent);

    if (w_info == NULL) 
	AutoMessage(_AutoMessages[WARNMSG8]);

    widget_info = mvsCreateWidget(iXmPopupShellWidgetClass, w_info, name,
                                  DontUseCommonArgs, args, num_args, 
				  widget_class);

    return(widget_info->widget);
}


Widget
AppShellCreate(
        String app_name,
        String app_class,
        WidgetClass widget_class,
        Display *display_in,
        ArgList args,
        Cardinal num_args )
{
    MvsWidgetInfoRecord *widget_info = NULL;
    MvsWidgetInfoRecord *mvsRootWidgetInfo2 = NULL;

    mvsRootWidgetInfo2 = mvsInitRootWidgetInfo();

    widget_info = mvsCreateWidget(iXmApplicationShellWidgetClass,
				  mvsRootWidgetInfo2, 
				  app_name, DontUseCommonArgs, args, num_args,
				  widget_class);

    return(widget_info->widget);
}


void
AppMainLoop(
        XtAppContext app )
{
     /* Only will be called if CommonPause does not clean up */

     AutoParseAndGenerateCommands();
     AutoExit();

}


void
SetValues(
        register Widget w,
        ArgList args,
        Cardinal num_args )
{
    MvsWidgetInfoRecord *w_info = NULL;

    w_info = mvsWidgetToWidgetInfo(w);

    if (w_info == NULL && w == NULL) 
	AutoMessage(_AutoMessages[WARNMSG9]);

    if (w != NULL && w_info == NULL) {
	XtSetValues(w, args, num_args);
	xisProcessObjects();
	xisUpdateObjectAttributes();
    }
    else
    	mvsSetValues(w_info, args, num_args);
}


void
DestroyWidget(
        Widget widget )
{
    WidgetClass widget_class, parent_class;
    Widget parent;
    MvsWidgetInfoRecord *w_info = NULL;

    /* if widget is a XmSeparatorGadget and the parent
     * is a XmScale, do nothing - we never saved info
     * about the XmSeparatorGadget children beause we don't
     * need to
     */

    widget_class = XtClass(widget);
    parent = XtParent(widget);
    parent_class = XtClass(parent);
    if 	(((strcmp (widget_class->core_class.class_name, "XmSeparatorGadget")) != 0) &&
	 ((strcmp (parent_class->core_class.class_name, "XmScale")) != 0))  {


	w_info = mvsWidgetToWidgetInfo(widget);

	if (w_info == NULL)
		AutoMessage(_AutoMessages[WARNMSG10]);

	mvsDestroyWidget(w_info, DontCheckCallbacks);
    }
    else
	return;
}
