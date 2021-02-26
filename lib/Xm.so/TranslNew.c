
#include <localdef.h>

/* $TOG: TranslNew.c /main/8 1998/10/05 16:26:39 samborn $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */


/* Define _XmConst before including TransltnsP.h or XmP.h, so that the
 * declarations will be in agreement with the definitions.
 */
#ifndef _XmConst
#if defined(__STDC__) || !defined( NO_CONST )
#define _XmConst const
#else
#define _XmConst
#endif /* __STDC__ */
#endif /* _XmConst */

#include <Xm/XmP.h>
#include <Xm/TransltnsP.h>

/* This is the new-style translation table, which is used with
 * versions of libXt that have the :-production translation fix
 * (fix-trackers seq 2797, or MIT public patch 24).
 *
 * Translations have been cleaned up and reorganized as follows:
 *  - Sort translations based roughly on the event type.  Canonical
 *	order is: Map/Unmap, Enter/Leave, Focus, Btn, Key.
 *  - Within the <Key> translations group by key, putting osfMumble
 *	keys first.
 *  - Prefix osf key translations with ':', and reorder as necessary
 *	to remove ~mod.
 */
/*** ComboBox.c ***/
externaldef(translations) 
_XmConst char _XmComboBox_defaultTranslations[] = "\
<Btn1Down>:		CBArmAndDropDownList()\n\
<Btn1Up>:		CBDisarm()";

externaldef(translations) 
_XmConst char _XmComboBox_defaultAccelerators[] = "\
\043override\n\
:c <Key>osfUp:		CBDropDownList()\n\
:<Key>osfUp:		CBListAction(Up)\n\
:c <Key>osfDown:	CBDropDownList()\n\
:<Key>osfDown:		CBListAction(Down)\n\
:c <Key>osfBeginLine:	CBListAction(ListBeginData)\n\
:c <Key>osfEndLine:	CBListAction(ListEndData)\n\
:<Key>osfPageUp:	CBListAction(ListPrevPage)\n\
:<Key>osfPageDown:	CBListAction(ListNextPage)\n";

/* TextF translations except for misc, Btn, osf*Data, osf*Up, and osf*Down. */
externaldef(translations) 
_XmConst char _XmComboBox_dropDownComboBoxAccelerators[] = "\
\043override\n\
:m <Key>osfPrimaryPaste:cut-primary()\n\
:a <Key>osfPrimaryPaste:cut-primary()\n\
:<Key>osfPrimaryPaste:	copy-primary()\n\
:m <Key>osfCut:		cut-primary()\n\
:a <Key>osfCut:		cut-primary()\n\
:<Key>osfCut:		cut-clipboard()\n\
:<Key>osfPaste:		paste-clipboard()\n\
:m <Key>osfCopy:	copy-primary()\n\
:a <Key>osfCopy:	copy-primary()\n\
:<Key>osfCopy:		copy-clipboard()\n\
:s <Key>osfBeginLine:	beginning-of-line(extend)\n\
:<Key>osfBeginLine:	beginning-of-line()\n\
:s <Key>osfEndLine:	end-of-line(extend)\n\
:<Key>osfEndLine:	end-of-line()\n\
:s <Key>osfPageLeft:	page-left(extend)\n\
:<Key>osfPageLeft:	page-left()\n\
:s <Key>osfPageRight:	page-right(extend)\n\
:<Key>osfPageRight:	page-right()\n\
:<Key>osfClear:		clear-selection()\n\
:<Key>osfBackSpace:	delete-previous-character()\n\
:s m <Key>osfDelete:	cut-primary()\n\
:s a <Key>osfDelete:	cut-primary()\n\
:s <Key>osfDelete:	cut-clipboard()\n\
:c <Key>osfDelete:	delete-to-end-of-line()\n\
:<Key>osfDelete:	delete-next-character()\n\
:c m <Key>osfInsert:	copy-primary()\n\
:c a <Key>osfInsert:	copy-primary()\n\
:s <Key>osfInsert:	paste-clipboard()\n\
:c <Key>osfInsert:	copy-clipboard()\n\
:s <Key>osfSelect:	key-select()\n\
:<Key>osfSelect:	set-anchor()\n\
:<Key>osfSelectAll:	select-all()\n\
:<Key>osfDeselectAll:	deselect-all()\n\
:<Key>osfActivate:	activate()\n\
:<Key>osfAddMode:	toggle-add-mode()\n\
:<Key>osfHelp:		Help()\n\
:<Key>osfCancel:	process-cancel()\n\
:s c <Key>osfLeft:	backward-word(extend)\n\
:c <Key>osfLeft:	backward-word()\n\
:s <Key>osfLeft:	key-select(left)\n\
:<Key>osfLeft:		backward-character()\n\
:s c <Key>osfRight:	forward-word(extend)\n\
:c <Key>osfRight:	forward-word()\n\
:s <Key>osfRight:	key-select(right)\n\
:<Key>osfRight:		forward-character()\n\
c ~m ~a <Key>slash:	select-all()\n\
c ~m ~a <Key>backslash:	deselect-all()\n\
s ~m ~a <Key>Tab:	prev-tab-group()\n\
~m ~a <Key>Tab:		next-tab-group()\n\
~s ~m ~a <Key>Return:	activate()\n\
c ~s ~m ~a <Key>space:	set-anchor()\n\
c s ~m ~a <Key>space:	key-select()\n\
s ~c ~m ~a <Key>space:	self-insert()\n\
<Key>:			self-insert()";

externaldef(translations) 
_XmConst char _XmComboBox_dropDownListTranslations[] = "\
\043override\n\
:c <Key>osfDown:	CBDropDownList()\n\
:c <Key>osfUp:		CBDropDownList()\n\
:<Key>osfCancel:	CBCancel()\n\
:<Key>osfActivate:	CBActivate()\n\
~s ~m ~a<Key>Return:	CBActivate()";

externaldef(translations) 
_XmConst char _XmComboBox_textFocusTranslations[] = "\
\043override\n\
<FocusOut>:		CBTextFocusOut()";


/*** Container.c ***/
externaldef(translations) _XmConst char _XmContainer_defaultTranslations[] = "\
~c ~s ~m ~a <Btn1Down>:	ContainerHandleBtn1Down(ContainerBeginSelect,Copy)\n\
 c ~s ~m ~a <Btn1Down>:	ContainerHandleBtn1Down(ContainerBeginToggle,Copy)\n\
 c  s ~m ~a <Btn1Down>:	ContainerHandleBtn1Down(ContainerNoop,Link)\n\
~c  s ~m ~a <Btn1Down>:	ContainerHandleBtn1Down(ContainerBeginExtend,Move)\n\
<Btn1Motion>:		ContainerHandleBtn1Motion(ContainerButtonMotion)\n\
~c ~s ~m ~a <Btn1Up>:	ContainerHandleBtn1Up(ContainerEndSelect)\n\
 c ~s ~m ~a <Btn1Up>:	ContainerHandleBtn1Up(ContainerEndToggle)\n\
~c  s ~m ~a <Btn1Up>:	ContainerHandleBtn1Up(ContainerEndExtend)\n\
 c  s ~m ~a <Btn1Down>:	ContainerHandleBtn1Down(ContainerBeginExtend)\n\
 c  s ~m ~a <Btn1Up>:	ContainerHandleBtn1Up(ContainerEndExtend)\n\
~c ~s ~m ~a <Btn2Down>:	ContainerHandleBtn2Down(ContainerStartTransfer,Copy)\n\
 c  s ~m ~a <Btn2Down>:	ContainerHandleBtn2Down(ContainerStartTransfer,Link)\n\
~c  s ~m ~a <Btn2Down>:	ContainerHandleBtn2Down(ContainerStartTransfer,Move)\n\
<Btn2Motion>:		ContainerHandleBtn2Motion(ContainerButtonMotion)\n\
~m ~a <Btn2Up>:		ContainerHandleBtn2Up(ContainerEndTransfer)\n\
:c  s  a <Key>osfInsert:	ContainerPrimaryLink()\n\
:c  s  m <Key>osfInsert:	ContainerPrimaryLink()\n\
:a <Key>osfInsert:		ContainerPrimaryCopy()\n\
:m <Key>osfInsert:		ContainerPrimaryCopy()\n\
:s  a <Key>osfDelete:		ContainerPrimaryMove()\n\
:s  m <Key>osfDelete:		ContainerPrimaryMove()\n\
:<Key>osfCancel:		ContainerCancel()\n\
:s <Key>osfSelect:		ContainerExtend()\n\
:<Key>osfSelect:		ContainerSelect()\n\
:<Key>osfSelectAll:		ContainerSelectAll()\n\
:<Key>osfDeselectAll:		ContainerDeselectAll()\n\
:<Key>osfAddMode:		ContainerToggleMode()\n\
:<Key>osfActivate:		ContainerActivate()\n\
 s ~c ~m ~a <Key>space:		ContainerExtend()\n\
~s ~c ~m ~a <Key>space:		ContainerSelect()\n\
~s ~c ~m ~a <Key>Return:	ContainerActivate()\n\
~s  c ~m ~a <Key>slash:		ContainerSelectAll()\n\
~s  c ~m ~a <Key>backslash:	ContainerDeselectAll()";

externaldef(translations) 
_XmConst char _XmContainer_traversalTranslations[] = "\
<FocusOut>:		ManagerFocusOut()\n\
<FocusIn>:		ManagerFocusIn()\n\
:c s <Key>osfBeginLine:	ContainerExtendCursor(First)\n\
:c s <Key>osfEndLine:	ContainerExtendCursor(Last)\n\
:c <Key>osfBeginLine:	ContainerMoveCursor(First)\n\
:c <Key>osfEndLine:	ContainerMoveCursor(Last)\n\
:c <Key>osfLeft:	ContainerExpandOrCollapse(Left)\n\
:c <Key>osfRight:	ContainerExpandOrCollapse(Right)\n\
:s <Key>osfUp:		ContainerExtendCursor(Up)\n\
:s <Key>osfDown:	ContainerExtendCursor(Down)\n\
:s <Key>osfLeft:	ContainerExtendCursor(Left)\n\
:s <Key>osfRight:	ContainerExtendCursor(Right)\n\
:<Key>osfUp:		ContainerMoveCursor(Up)\n\
:<Key>osfDown:		ContainerMoveCursor(Down)\n\
:<Key>osfLeft:		ContainerMoveCursor(Left)\n\
:<Key>osfRight:		ContainerMoveCursor(Right)\n\
 s ~m ~a <Key>Tab:	ManagerGadgetPrevTabGroup()\n\
~s ~m ~a <Key>Tab:	ManagerGadgetNextTabGroup()";

/*** GrabShell.c ***/
externaldef(translations) _XmConst char _XmGrabShell_translations [] = "\
<BtnUp>:		GrabShellBtnUp()\n\
<BtnDown>:		GrabShellBtnDown()";


/*** Notebook.c ***/
externaldef(translations) _XmConst char _XmNotebook_TabAccelerators[] = "\
\043override\n\
:c <Key>osfBeginLine:           TraverseTab(Home)\n\
:<Key>osfBeginLine:             TraverseTab(Home)\n\
:c <Key>osfEndLine:             TraverseTab(End)\n\
:<Key>osfEndLine:               TraverseTab(End)\n\
:<Key>osfUp:                    TraverseTab(Previous)\n\
:<Key>osfDown:                  TraverseTab(Next)\n\
:<Key>osfLeft:                  TraverseTab(Previous)\n\
:<Key>osfRight:                 TraverseTab(Next)\n\
";

externaldef(translations) _XmConst char _XmNotebook_manager_translations[] = "\
:c <Key>osfBeginLine:           TraverseTab(Home)\n\
:<Key>osfBeginLine:             TraverseTab(Home)\n\
:c <Key>osfEndLine:             TraverseTab(End)\n\
:<Key>osfEndLine:               TraverseTab(End)\n\
:<Key>osfUp:                    TraverseTab(Previous)\n\
:<Key>osfDown:                  TraverseTab(Next)\n\
:<Key>osfLeft:                  TraverseTab(Previous)\n\
:<Key>osfRight:                 TraverseTab(Next)\n\
:s <Key>Tab:                    ManagerGadgetPrevTabGroup()\n\
:<Key>Tab:                      ManagerGadgetNextTabGroup()\n\
<EnterWindow>:                  ManagerEnter()\n\
<LeaveWindow>:                  ManagerLeave()\n\
<FocusOut>:                     ManagerFocusOut()\n\
<FocusIn>:                      ManagerFocusIn()\n\
";


/*** SpinB.c ***/
_XmConst char _XmSpinB_defaultTranslations[] = "\
<Btn1Down>:		SpinBArm()\n\
<Btn1Up>:		SpinBDisarm()\n\
<EnterWindow>:		SpinBEnter()\n\
<LeaveWindow>:		SpinBLeave()\n\
:<Key>osfUp:		SpinBNext()\n\
:<Key>osfDown:		SpinBPrior()\n\
:<Key>osfLeft:		SpinBLeft()\n\
:<Key>osfRight:		SpinBRight()\n\
:<KeyUp>osfUp:		SpinBDisarm()\n\
:<KeyUp>osfDown:	SpinBDisarm()\n\
:<KeyUp>osfLeft:	SpinBDisarm()\n\
:<KeyUp>osfRight:	SpinBDisarm()\n\
:<Key>osfBeginLine:	SpinBFirst()\n\
:<Key>osfEndLine:	SpinBLast()";

_XmConst char _XmSpinB_defaultAccelerators[] =
  "\043override\n\
<Key>osfUp:		SpinBNext()\n\
<Key>osfDown:		SpinBPrior()\n\
<KeyUp>osfUp:		SpinBDisarm()\n\
<KeyUp>osfDown:		SpinBDisarm()\n\
<Key>osfLeft:		SpinBLeft()\n\
<Key>osfRight:		SpinBRight()\n\
<KeyUp>osfLeft:		SpinBDisarm()\n\
<KeyUp>osfRight:	SpinBDisarm()\n\
<Key>osfBeginLine:	SpinBFirst()\n\
<Key>osfEndLine:	SpinBLast()";

