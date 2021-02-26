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
static char rcsid[] = "$XConsortium: GetClassName.c /main/8 1995/07/14 11:16:17 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetClassName.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/21/90 SJS add to SCCS
            06/19/90 SJS add in ToggleB & ToggleBG classes
	Calls:

	Summary:
            Returns a string pointer to the widget class name.

            INPUTS
                widget - the widget to return the class name of

            OUTPUTS
                none
  
            RETURNS
                pointer to a statically declared string which names the
                widget class
************************************************************************/

#include "mvslib.h"

static char *mvsWidgetClassName[] = { 
      /*  0 */ "vendorShellWidgetClass",
      /*  1 */ "xmArrowButtonWidgetClass",
      /*  2 */ "xmArrowButtonGadgetClass", 
      /*  3 */ "xmBulletinBoardWidgetClass",
      /*  4 */ "xmCascadeButtonWidgetClass",
      /*  5 */ "xmCascadeButtonGadgetClass", 
      /*  6 */ "xmCommandWidgetClass",
      /*  7 */ "xmDesktopObjectClass",
      /*  8 */ "xmDrawingAreaWidgetClass",
      /*  9 */ "xmDrawnButtonWidgetClass",
      /* 10 */ "xmDialogShellExtObjectClass",
      /* 11 */ "xmExtObjectClass",
      /* 12 */ "xmFileSelectionBoxWidgetClass",
      /* 13 */ "xmFormWidgetClass",
      /* 14 */ "xmFrameWidgetClass",
      /* 15 */ "xmGadgetClass",
      /* 16 */ "xmLabelWidgetClass",
      /* 17 */ "xmLabelGadgetClass",
      /* 18 */ "xmListWidgetClass",
      /* 19 */ "xmMainWindowWidgetClass",
      /* 20 */ "xmManagerWidgetClass",
      /* 21 */ "xmMenuShellWidgetClass",
      /* 22 */ "xmMessageBoxWidgetClass",
      /* 23 */ "xmPanedWindowWidgetClass",
      /* 24 */ "xmPrimitiveWidgetClass",
      /* 25 */ "xmProtocolObjectClass",
      /* 26 */ "xmPushButtonGadgetClass", 
      /* 27 */ "xmRowColumnWidgetClass",
      /* 28 */ "xmSashWidgetClass",
      /* 29 */ "xmScaleWidgetClass",
      /* 30 */ "xmScreenObjectClass",
      /* 31 */ "xmScrollBarWidgetClass",
      /* 32 */ "xmScrolledWindowWidgetClass",
      /* 33 */ "xmSelectionBoxWidgetClass",
      /* 34 */ "xmSeparatorGadgetClass", 
      /* 35 */ "xmSeparatorWidgetClass",
      /* 36 */ "xmShellExtObjectClass",
      /* 37 */ "xmTextWidgetClass",
      /* 38 */ "xmTextFieldWidgetClass",
      /* 39 */ "xmToggleButtonWidgetClass",
      /* 40 */ "xmToggleButtonGadgetClass",
      /* 41 */ "xmVendorShellExtObjectClass",
      /* 42 */ "applicationShellWidgetClass",
      /* 43 */ "compositeWidgetClass",
      /* 44 */ "coreWidgetClass",
      /* 45 */ "objectClass",
      /* 46 */ "overrideShellWidgetClass",
      /* 47 */ "rectObjClass",
      /* 48 */ "shellWidgetClass",
      /* 49 */ "topLevelShellWidgetClass",
      /* 50 */ "transientShellWidgetClass",
      /* 51 */ "wmShellWidgetClass",
      /* 52 */ "xmPushButtonWidgetClass",
#ifndef MOTIF1_1
      /* 53 */ "xmTearOffButtonWidgetClass",
#else
      /* 53 */ "xmPushButtonWidgetClass",  /* Placeholder for 1.1 */
#endif /* MOTIF1_1 */
      /* 54 */ "xmComboBoxWidgetClass",
      /* 55 */ "xmContainerWidgetClass",
      /* 56 */ "xmIconGadgetClass",
      /* 57 */ "xmNotebookWidgetClass",
      /* 58 */ "xmSpinBoxWidgetClass",
      /* 59 */ "unknownWidgetClass"
  };

char *mvsGetClassName(widget)
Widget widget;
{
    return( mvsWidgetClassName[mvsGetClassCode(widget)] );

} /* End mvsGetClassName() */
