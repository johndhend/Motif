/* $XConsortium: ChRedef.h /main/4 1995/07/15 21:01:15 drk $ */
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

#ifndef TCMENU
/* Redefinitions of globals in files that are distinct from the shared
 * library versions.  These are needed to avoid conflicts with the shared
 * libraries.
 */
#define xmRowColumnWidgetClass TCxmRowColumnWidgetClass
#define XmCreateRadioBox TCXmCreateRadioBox
#define XmCreateRowColumn TCXmCreateRowColumn
#define XmCreateWorkArea TCXmCreateWorkArea
#define XmCreatePopupMenu TCXmCreatePopupMenu
#define XmCreatePulldownMenu TCXmCreatePulldownMenu
#define XmCreateOptionMenu TCXmCreateOptionMenu
#define XmCreateMenuBar TCXmCreateMenuBar
#define XmMenuPosition TCXmMenuPosition
#define XmOptionLabelGadget TCXmOptionLabelGadget
#define XmOptionButtonGadget TCXmOptionButtonGadget
#define XmGetPostedFromWidget TCXmGetPostedFromWidget
#define _XmMenuFocus TC_XmMenuFocus
#define _XmGetActiveTopLevelMenu TC_XmGetActiveTopLevelMenu
#define XmAddToPostFromList TCXmAddToPostFromList
#define XmRemoveFromPostFromList TCXmRemoveFromPostFromList
#define _XmButtonEventStatus TC_XmButtonEventStatus
#define _XmRC_GetMnemonicCharSet TC_XmRC_GetMnemonicCharSet
#define _XmRC_GetMenuAccelerator TC_XmRC_GetMenuAccelerator
#define _XmRC_GetLabelString TC_XmRC_GetLabelString
#define xmRowColumnClassRec TCxmRowColumnClassRec
#define _XmMatchBtnEvent toolchest_XmMatchBtnEvent
#define xmMenuShellWidgetClass toolchest_xmMenuShellWidgetClass
#define _XmEnterRowColumn toolchest_XmEnterRowColumn
#define XmCreateMenuShell toolchest_XmCreateMenuShell
#define xmMenuShellClassRec toolchest_xmMenuShellClassRec
#define xmCascadeButtonWidgetClass TCxmCascadeButtonWidgetClass
#define _XmArrowPixmapCacheDelete TC_XmArrowPixmapCacheDelete
#define _XmCascadingPopup TC_XmCascadingPopup
#define _XmButtonPopdownChildren TC_XmButtonPopdownChildren
#define _XmCBHelp TC_XmCBHelp
#define _XmCreateArrowPixmaps TC_XmCreateArrowPixmaps
#define XmCreateCascadeButton TCXmCreateCascadeButton
#define XmCascadeButtonHighlight TCXmCascadeButtonHighlight
#define xmCascadeButtonClassRec TCxmCascadeButtonClassRec
#endif
