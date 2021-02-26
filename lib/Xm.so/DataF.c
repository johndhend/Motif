
#include <localdef.h>

/* 
 * (c) Copyright 1989, 1990, 1991, 1992, 1993, 1994 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2.4
*/ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$RCSfile: DataF.c,v $ $Revision: 1.8.2.2 $ $Date: 2003/08/20 11:22:27 $"
#endif
#endif
/**  (c) Copyright 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <Xm/XmosP.h>
#include <X11/Xatom.h>
#include <X11/ShellP.h>
#include <X11/VendorP.h>
#include <X11/keysym.h>
#include <X11/Xresource.h>
#include <Xm/AtomMgr.h>
#include <Xm/CutPaste.h>
#include <Xm/DragC.h>
#include <Xm/DragIcon.h>
#include <Xm/DropSMgr.h>
#include <Xm/DropTrans.h>
#include <Xm/Display.h>
#include <Xm/ManagerP.h>
#include <Xm/ScreenP.h>
#include <Xm/DragIconP.h>
#include <Xm/TransltnsP.h>
#include <Xm/DrawP.h>

#include <Xm/Ext.h>
#include <Xm/DataFSelP.h>
#include <Xm/DataFP.h>
#include "XmI.h"

/*
 * Stuff from various internal motif headers that we need to declare
 */

#define TEXT_MAX_INSERT_SIZE 64    /* Size of buffer for XLookupString. */
/*
 * Various DataField messages macro
 */
#define MSG1	        _XmMsgDataF_0000
#define MSG2	        _XmMsgDataF_0001
#define MSG3	        _XmMsgDataF_0002
#define MSG4	        _XmMsgDataF_0003
#define MSG5	        _XmMsgDataF_0004
#define MSG6	        _XmMsgDataF_0005
#define MSG7	        _XmMsgDataF_0006
#define WC_MSG1	        _XmMsgDataFWcs_0000
#define WC_MSG2	        _XmMsgDataFWcs_0001
#define GRABKBDERROR	_XmMsgRowColText_0024

#ifdef _XmConst
       #undef _XmConst
       #define _XmConst
#else
       #define _XmConst
#endif

static _XmConst char _XmMsgRowColText_0024[] =
   "XtGrabKeyboard failed";

static _XmConst char _XmMsgDataF_0000[] =
   "Invalid cursor position, must be >= 0.";

static _XmConst char _XmMsgDataF_0001[] =
   "Invalid columns, must be > 0.";

static _XmConst char _XmMsgDataF_0002[] =
   "XmFontListInitFontContext Failed.";

static _XmConst char _XmMsgDataF_0003[] =
   "XmFontListGetNextFont Failed.";

static _XmConst char _XmMsgDataF_0004[] =
   "Character '%c', not supported in font.  Discarded.";

static _XmConst char _XmMsgDataF_0005[] =
   "Traversal_on must always be true.";

static _XmConst char _XmMsgDataF_0006[] =
   "Invalid columns, must be >= 0.";

static _XmConst char _XmMsgDataFWcs_0000[] =
   "Character '%s', not supported in font.  Discarded.";

static _XmConst char _XmMsgDataFWcs_0001[] =
   "Cannot use multibyte locale without a fontset.  Value discarded.";

#ifdef _NO_PROTO
extern Boolean _XmParentProcess();
extern Boolean _XmMgrTraversal();
extern unsigned char _XmGetFocusPolicy();
extern void _XmPrimitiveFocusIn();
extern void _XmPrimitiveEnter();
extern void _XmPrimitiveLeave();
extern Boolean _XmGetImage();
extern Boolean _XmGetIconControlInfo();
extern Boolean _XmInstallPixmap();
extern unsigned char _XmGetAudibleWarning();
extern void _XmSetDestination();
extern XtGeometryResult _XmGMReplyToQueryGeometry();
#else
extern Boolean _XmParentProcess(Widget, XmParentProcessData);
extern Boolean _XmMgrTraversal(Widget, XmTraversalDirection);
extern unsigned char _XmGetFocusPolicy(Widget);
extern void _XmPrimitiveFocusIn(Widget, XEvent *, String *, Cardinal *);
extern void _XmPrimitiveEnter(Widget, XEvent *, String *, Cardinal *);
extern void _XmPrimitiveLeave(Widget, XEvent *, String *, Cardinal *);
extern Boolean _XmGetImage(Screen *, char *, XImage **);
extern Boolean _XmGetIconControlInfo( 
                        Screen *screen,
                        Boolean *useMaskRtn,
                        Boolean *useMultiColorIconsRtn,
                        Boolean *useIconFileCacheRtn) ;
extern Boolean _XmInstallPixmap(Pixmap, Screen *, char *, Pixel, Pixel);
extern unsigned char _XmGetAudibleWarning(Widget);
extern void _XmSetDestination(Display *, Widget);
extern XtGeometryResult _XmGMReplyToQueryGeometry(Widget, XtWidgetGeometry *,
						  XtWidgetGeometry *);
#endif

/*
 * Back to the original XmTextField code
 */
#define TEXT_INCREMENT 32
#define PRIM_SCROLL_INTERVAL 100
#define SEC_SCROLL_INTERVAL 200
#define XmDYNAMIC_BOOL 255

#define EventBindings1  _XmDataF_EventBindings1
#define EventBindings2  _XmDataF_EventBindings2
#define EventBindings3  _XmDataF_EventBindings3

static char _XmDataF_EventBindings1[] = "\
:m <Key>osfPrimaryPaste:cut-primary()\n\
:a <Key>osfPrimaryPaste:cut-primary()\n\
:<Key>osfPrimaryPaste:copy-primary()\n\
:m <Key>osfCut:cut-primary()\n\
:a <Key>osfCut:cut-primary()\n\
:<Key>osfCut:cut-clipboard()\n\
:<Key>osfPaste:paste-clipboard()\n\
:m <Key>osfCopy:copy-primary()\n\
:a <Key>osfCopy:copy-primary()\n\
:<Key>osfCopy:copy-clipboard()\n\
:s <Key>osfBeginLine:beginning-of-line(extend)\n\
:<Key>osfBeginLine:beginning-of-line()\n\
:s <Key>osfEndLine:end-of-line(extend)\n\
:<Key>osfEndLine:end-of-line()\n\
:s <Key>osfPageLeft:page-left(extend)\n\
:<Key>osfPageLeft:page-left()\n\
:s c<Key>osfPageUp:page-left(extend)\n\
:c <Key>osfPageUp:page-left()\n\
:s <Key>osfPageRight:page-right(extend)\n\
:<Key>osfPageRight:page-right()\n\
:s c <Key>osfPageDown:page-right(extend)\n\
:c <Key>osfPageDown:page-right()\n\
:<Key>osfClear:clear-selection()\n\
:<Key>osfBackSpace:delete-previous-character()\n\
:s m <Key>osfDelete:cut-primary()\n\
:s a <Key>osfDelete:cut-primary()\n\
:s <Key>osfDelete:cut-clipboard()\n\
:c <Key>osfDelete:delete-to-end-of-line()\n\
:<Key>osfDelete:delete-next-character()\n";

static char _XmDataF_EventBindings2[] = "\
:c m <Key>osfInsert:copy-primary()\n\
:c a <Key>osfInsert:copy-primary()\n\
:s <Key>osfInsert:paste-clipboard()\n\
:c <Key>osfInsert:copy-clipboard()\n\
:s <Key>osfSelect:key-select()\n\
:<Key>osfSelect:set-anchor()\n\
:<Key>osfActivate:activate()\n\
:<Key>osfAddMode:toggle-add-mode()\n\
:<Key>osfHelp:Help()\n\
:<Key>osfCancel:process-cancel()\n\
:s c <Key>osfLeft:backward-word(extend)\n\
:c <Key>osfLeft:backward-word()\n\
:s <Key>osfLeft:key-select(left)\n\
:<Key>osfLeft:backward-character()\n\
:s c <Key>osfRight:forward-word(extend)\n\
:c <Key>osfRight:forward-word()\n\
:s <Key>osfRight:key-select(right)\n\
:<Key>osfRight:forward-character()\n\
:<Key>osfUp:traverse-prev()\n\
:<Key>osfDown:traverse-next()\n\
c ~m ~a <Key>slash:select-all()\n\
c ~m ~a <Key>backslash:deselect-all()\n\
s ~m ~a <Key>Tab:prev-tab-group()\n\
~m ~a <Key>Tab:next-tab-group()\n\
~s ~m ~a <Key>Return:activate()\n\
c ~s ~m ~a <Key>space:set-anchor()\n\
c s ~m ~a <Key>space:key-select()\n\
s ~c ~m ~a <Key>space:self-insert()\n\
<Key>:self-insert()\n";

static char _XmDataF_EventBindings3[] = "\
<Unmap>:unmap()\n\
<Enter>:enter()\n\
<Leave>:leave()\n\
<FocusIn>:focusIn()\n\
<FocusOut>:focusOut()\n\
~c s ~m ~a <Btn1Down>:extend-start()\n\
c ~s ~m ~a <Btn1Down>:move-destination()\n\
~c ~s ~m ~a <Btn1Down>:grab-focus()\n\
~c ~m ~a <Btn1Motion>:extend-adjust()\n\
~c ~m ~a <Btn1Up>:extend-end()\n\
<Btn2Down>:process-bdrag()\n\
m ~a <Btn2Motion>:secondary-adjust()\n\
~m a <Btn2Motion>:secondary-adjust()\n\
~s <Btn2Up>:copy-to()\n\
~c <Btn2Up>:move-to()";

static char df_translations[] = 
"s ~m ~a <Key>Tab:ValidateAndMove(prev)\n\
~m ~a<Key>Tab:ValidateAndMove(next)";

typedef struct {
    Boolean has_destination;
    XmTextPosition position;
    int replace_length;
    Boolean quick_key;
} TextFDestDataRec, *TextFDestData;

typedef struct {
    XmDataFieldWidget tf;
} TextFGCDataRec, *TextFGCData;


/********    Static Function Declarations    ********/
#ifdef _NO_PROTO

static void df_ValidateAndMove() ;
static int _XmDataFieldCountCharacters() ;
static void df_MakeCopy() ;
static void df_WcsMakeCopy() ;
static void df_FreeContextData() ;
static TextFDestData df_GetTextFDestData() ;
static void df_SetDropContext() ;
static void df_DeleteDropContext() ;
static TextFGCData df_GetTextFGCData() ;
static _XmHighlightRec * df_FindHighlight() ;
static void df_InsertHighlight() ;
static void DataFieldSetHighlight() ;
static Boolean df_GetXYFromPos() ;
static Boolean df_CurrentCursorState() ;
static void df_PaintCursor() ;
static int _XmGetImage();
static void df_BlinkInsertionPoint() ;
static void df_HandleTimer() ;
static void df_ChangeBlinkBehavior() ;
static void df_GetRect() ;
static void df_CheckHasRect() ;
static void df_XmSetFullGC() ;
static void df_XmSetMarginGC() ;
static void df_XmResetSaveGC() ;
static void df_XmSetNormGC() ;
static void df_XmSetInvGC() ;
static void df_DrawText() ;
static int df_FindPixelLength() ;
static void df_DrawTextSegment() ;
static void df_RedisplayText() ;
static void df_ComputeSize() ;
static XtGeometryResult df_TryResize() ;
static Boolean df_AdjustText() ;
static void df_AdjustSize() ;
static Boolean df_ModifyVerify() ;
static void df_ResetClipOrigin() ;
static void df_InvertImageGC() ;
static void df_ResetImageGC() ;
static void df_SetCursorPosition() ;
static void df_VerifyBounds() ;
static XmTextPosition df_GetPosFromX() ;
static XmTextPosition RightAlignedGetPosFromX() ;
static Boolean df_SetDestination() ;
static Boolean df_VerifyLeave() ;
static Boolean _XmDataFieldIsWordBoundary() ;
static int _XmGetImage(Screen *, char *, XImage **);
static Boolean _XmDataFieldIsWSpace() ;
static void df_FindWord() ;
static void df_FindPrevWord() ;
static void df_FindNextWord() ;
static void df_CheckDisjointSelection() ;
static Boolean df_NeedsPendingDelete() ;
static Boolean df_NeedsPendingDeleteDisjoint() ;
static Time df_GetServerTime() ;
static void df_InsertChar() ;
static void df_InsertString() ;
static void df_DeletePrevChar() ;
static void df_DeleteNextChar() ;
static void df_DeletePrevWord() ;
static void df_DeleteNextWord() ;
static void df_DeleteToEndOfLine() ;
static void df_DeleteToStartOfLine() ;
static void df_ProcessCancel() ;
static void df_Activate() ;
static void df_SetAnchorBalancing() ;
static void df_SetNavigationAnchor() ;
static void df_CompleteNavigation() ;
static void df_SimpleMovement() ;
static void df_BackwardChar() ;
static void df_ForwardChar() ;
static void df_BackwardWord() ;
static void df_ForwardWord() ;
static void df_EndOfLine() ;
static void df_BeginningOfLine() ;
static void df_SetSelection() ;
static void df_ProcessHorizontalParams() ;
static void df_ProcessSelectParams() ;
static void df_KeySelection() ;
static void df_TextFocusIn() ;
static void df_TextFocusOut() ;
static void df_SetScanIndex() ;
static void df_ExtendScanSelection() ;
static void df_SetScanSelection() ;
static void df_StartPrimary() ;
static void df_MoveDestination() ;
static void df_ExtendPrimary() ;
static void df_ExtendEnd() ;
static void df_DoExtendedSelection() ;
static void df_DoSecondaryExtend() ;
static void df_BrowseScroll() ;
static Boolean df_CheckTimerScrolling() ;
static void df_RestorePrimaryHighlight() ;
static void df_StartDrag() ;
static void df_StartSecondary() ;
static void df_ProcessBDrag() ;
static void df_ExtendSecondary() ;
static void df_DoStuff() ;
static void df_Stuff() ;
static void df_HandleSelectionReplies() ;
static void df_SecondaryNotify() ;
static void df_HandleTargets() ;
static void df_ProcessBDragRelease() ;
static void df_ProcessCopy() ;
static void df_ProcessMove() ;
static void df_DeleteSelection() ;
static void df_ClearSelection() ;
static void df_PageRight() ;
static void df_PageLeft() ;
static void df_CopyPrimary() ;
static void df_CutPrimary() ;
static void df_SetAnchor() ;
static void df_ToggleOverstrike() ;
static void df_ToggleAddMode() ;
static void df_SelectAll() ;
static void df_DeselectAll() ;
static void df_VoidAction() ;
static void df_CutClipboard() ;
static void df_CopyClipboard() ;
static void df_PasteClipboard() ;
static void df_TraverseDown() ;
static void df_TraverseUp() ;
static void df_TraverseHome() ;
static void df_TraverseNextTabGroup() ;
static void df_TraversePrevTabGroup() ;
static void df_TextEnter() ;
static void df_TextLeave() ;
static void df_ClassPartInitialize() ;
static void df_Validates() ;
static Boolean df_LoadFontMetrics() ;
static void df_ValidateString() ;
static void df_InitializeTextStruct() ;
static Pixmap df_GetClipMask() ;
static void df_LoadGCs() ;
static void df_MakeIBeamOffArea() ;
static void df_MakeIBeamStencil() ;
static void df_MakeAddModeCursor() ;
static void df_MakeCursors() ;
static void df_DropDestroyCB() ;
static void df_DropTransferCallback() ;
static void df_HandleDrop() ;
static void df_DragProcCallback() ;
static void df_DropProcCallback() ;
static void df_RegisterDropSite() ;
static void df_Initialize() ;
static void df_Realize() ;
static void df_Destroy() ;
static void df_Resize() ;
static XtGeometryResult df_QueryGeometry() ;
static void DataFieldExpose() ;
static Boolean df_SetValues() ;
static Boolean DataFieldGetBaselines() ;
static Boolean DataFieldGetDisplayRect() ;
static void DataFieldMarginsProc() ;
static Boolean DataFieldRemove();
static void PictureVerifyCallback();
static void ClassInit();
#else
static void df_ValidateAndMove(
			       Widget w,
			       XEvent *ev,
			       String *args,
			       Cardinal *nargs) ;
static int _XmDataFieldCountCharacters( 
                        XmDataFieldWidget tf,
                        char *ptr,
                        int n_bytes) ;
static void df_MakeCopy( 
                        Widget w,
                        int n,
                        XtArgVal *value) ;
static void df_WcsMakeCopy( 
                        Widget w,
                        int n,
                        XtArgVal *value) ;
static void df_FreeContextData( 
                        Widget w,
                        XtPointer clientData,
                        XtPointer callData) ;
static TextFDestData df_GetTextFDestData( 
                        Widget w) ;
static void df_SetDropContext( 
                        Widget w) ;
static void df_DeleteDropContext( 
                        Widget w) ;
static TextFGCData df_GetTextFGCData( 
                        Widget w) ;
static _XmHighlightRec * df_FindHighlight( 
                        XmDataFieldWidget w,
                        XmTextPosition position) ;
static void df_InsertHighlight( 
                        XmDataFieldWidget w,
                        XmTextPosition position,
                        XmHighlightMode mode) ;
static void DataFieldSetHighlight( 
                        XmDataFieldWidget tf,
                        XmTextPosition left,
                        XmTextPosition right,
                        XmHighlightMode mode) ;
static Boolean df_GetXYFromPos( 
                        XmDataFieldWidget tf,
                        XmTextPosition position,
                        Position *x,
                        Position *y) ;
static Boolean df_CurrentCursorState( 
                        XmDataFieldWidget tf) ;
static void df_PaintCursor( 
                        XmDataFieldWidget tf) ;
static void df_BlinkInsertionPoint( 
                        XmDataFieldWidget tf) ;
static void df_HandleTimer( 
                        XtPointer closure,
                        XtIntervalId *id) ;

static void df_ChangeBlinkBehavior( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int turn_on) ;
#else
                        Boolean turn_on) ;
#endif /* NeedWidePrototypes */

static void df_GetRect( 
                        XmDataFieldWidget tf,
                        XRectangle *rect) ;
static void df_CheckHasRect( 
                        XmDataFieldWidget tf) ;
static void df_XmSetFullGC( 
                        XmDataFieldWidget tf,
                        GC gc) ;
static void df_XmSetMarginGC( 
                        XmDataFieldWidget tf,
                        GC gc) ;
static void df_XmResetSaveGC( 
                        XmDataFieldWidget tf,
                        GC gc) ;
static void df_XmSetNormGC( 
                        XmDataFieldWidget tf,
                        GC gc,
#if NeedWidePrototypes
                        int change_stipple,
                        int stipple) ;
#else
                        Boolean change_stipple,
                        Boolean stipple) ;
#endif /* NeedWidePrototypes */

static void df_XmSetInvGC( 
                        XmDataFieldWidget tf,
                        GC gc) ;
static void df_DrawText( 
                        XmDataFieldWidget tf,
                        GC gc,
                        int x,
                        int y,
                        char *string,
                        int length) ;
static int df_FindPixelLength( 
                        XmDataFieldWidget tf,
                        char *string,
                        int length) ;

static void df_DrawTextSegment( 
                        XmDataFieldWidget tf,
                        XmHighlightMode mode,
                        XmTextPosition prev_seg_start,
                        XmTextPosition seg_start,
                        XmTextPosition seg_end,
                        XmTextPosition next_seg,
#if NeedWidePrototypes
                        int stipple,
#else
                        Boolean stipple,
#endif /* NeedWidePrototypes */
                        int y,
                        int *x) ;

static void df_RedisplayText( 
                        XmDataFieldWidget tf,
                        XmTextPosition start,
                        XmTextPosition end) ;
static void df_ComputeSize( 
                        XmDataFieldWidget tf,
                        Dimension *width,
                        Dimension *height) ;

static XtGeometryResult df_TryResize( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int width,
                        int height) ;
#else
                        Dimension width,
                        Dimension height) ;
#endif /* NeedWidePrototypes */

static Boolean df_AdjustText( 
                        XmDataFieldWidget tf,
                        XmTextPosition position,
#if NeedWidePrototypes
                        int flag) ;
#else
                        Boolean flag) ;
#endif /* NeedWidePrototypes */

static void df_AdjustSize( 
                        XmDataFieldWidget tf) ;
static Boolean df_ModifyVerify( 
                        XmDataFieldWidget tf,
                        XEvent *event,
                        XmTextPosition *replace_prev,
                        XmTextPosition *replace_next,
                        char **insert,
                        int *insert_length,
			XmTextPosition *newInsert,
			int *free_insert) ;

static void df_ResetClipOrigin( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int clip_mask_reset) ;
#else
                        Boolean clip_mask_reset) ;
#endif /* NeedWidePrototypes */

static void df_InvertImageGC( 
                        XmDataFieldWidget tf) ;
static void df_ResetImageGC( 
                        XmDataFieldWidget tf) ;
static void df_SetCursorPosition( 
                        XmDataFieldWidget tf,
                        XEvent *event,
                        XmTextPosition position,
#if NeedWidePrototypes
                        int adjust_flag,
                        int call_cb,
			int set_dest) ;
#else
                        Boolean adjust_flag,
                        Boolean call_cb,
                        Boolean set_dest) ;
#endif /* NeedWidePrototypes */

static void df_VerifyBounds( 
                        XmDataFieldWidget tf,
                        XmTextPosition *from,
                        XmTextPosition *to) ;
static XmTextPosition df_GetPosFromX( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int x) ;
#else
                        Position x) ;
#endif /* NeedWidePrototypes */

static XmTextPosition RightAlignedGetPosFromX( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int x) ;
#else
                        Position x) ;
#endif /* NeedWidePrototypes */

static Boolean df_SetDestination( 
                        Widget w,
                        XmTextPosition position,

#if NeedWidePrototypes
                        int disown,
#else
                        Boolean disown,
#endif /* NeedWidePrototypes */
                        Time set_time) ;

static Boolean df_VerifyLeave( 
                        XmDataFieldWidget tf,
                        XEvent *event) ;
static Boolean _XmDataFieldIsWordBoundary( 
                        XmDataFieldWidget tf,
                        XmTextPosition pos1,
                        XmTextPosition pos2) ;
static Boolean _XmDataFieldIsWSpace( 
                        wchar_t wide_char,
                        wchar_t *white_space,
                        int num_entries) ;
static void df_FindWord( 
                        XmDataFieldWidget tf,
                        XmTextPosition begin,
                        XmTextPosition *left,
                        XmTextPosition *right) ;
static void df_FindPrevWord( 
                        XmDataFieldWidget tf,
                        XmTextPosition *left,
                        XmTextPosition *right) ;
static void df_FindNextWord( 
                        XmDataFieldWidget tf,
                        XmTextPosition *left,
                        XmTextPosition *right) ;
static void df_CheckDisjointSelection( 
                        Widget w,
                        XmTextPosition position,
                        Time sel_time) ;
static Boolean df_NeedsPendingDelete( 
                        XmDataFieldWidget tf) ;
static Boolean df_NeedsPendingDeleteDisjoint( 
                        XmDataFieldWidget tf) ;
static Time df_GetServerTime( 
                        Widget w) ;
static void df_InsertChar( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_InsertString( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeletePrevChar( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeleteNextChar( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeletePrevWord( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeleteNextWord( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeleteToEndOfLine( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeleteToStartOfLine( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ProcessCancel( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_Activate( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_SetAnchorBalancing( 
                        XmDataFieldWidget tf,
                        XmTextPosition position) ;

static void df_SetNavigationAnchor( 
                        XmDataFieldWidget tf,
                        XmTextPosition position,
#if NeedWidePrototypes
                        int extend) ;
#else
                        Boolean extend) ;
#endif /* NeedWidePrototypes */

static void df_CompleteNavigation( 
                        XmDataFieldWidget tf,
                        XEvent *event,
                        XmTextPosition position,
                        Time time,
#if NeedWidePrototypes
                        int extend) ;
#else
                        Boolean extend) ;
#endif /* NeedWidePrototypes */

static void df_SimpleMovement( 
                        Widget w,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params,
                        XmTextPosition cursorPos,
                        XmTextPosition position) ;
static void df_BackwardChar( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ForwardChar( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_BackwardWord( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ForwardWord( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_EndOfLine( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_BeginningOfLine( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;

static void df_SetSelection( 
                        XmDataFieldWidget tf,
                        XmTextPosition left,
                        XmTextPosition right,
#if NeedWidePrototypes
                        int redisplay) ;
#else
                        Boolean redisplay) ;
#endif /* NeedWidePrototypes */

static void df_ProcessHorizontalParams( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params,
                        XmTextPosition *left,
                        XmTextPosition *right,
                        XmTextPosition *position) ;
static void df_ProcessSelectParams( 
                        Widget w,
                        XEvent *event,
                        XmTextPosition *left,
                        XmTextPosition *right,
                        XmTextPosition *position) ;
static void df_KeySelection( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TextFocusIn( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TextFocusOut( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_SetScanIndex( 
                        XmDataFieldWidget tf,
                        XEvent *event) ;
static void df_ExtendScanSelection( 
                        XmDataFieldWidget tf,
                        XEvent *event) ;
static void df_SetScanSelection( 
                        XmDataFieldWidget tf,
                        XEvent *event) ;
static void df_StartPrimary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_MoveDestination( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ExtendPrimary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ExtendEnd( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DoExtendedSelection( 
                        Widget w,
                        Time time) ;
static void df_DoSecondaryExtend( 
                        Widget w,
                        Time ev_time) ;
static void df_BrowseScroll( 
                        XtPointer closure,
                        XtIntervalId *id) ;
static Boolean df_CheckTimerScrolling( 
                        Widget w,
                        XEvent *event) ;
static void df_RestorePrimaryHighlight( 
                        XmDataFieldWidget tf,
                        XmTextPosition prim_left,
                        XmTextPosition prim_right) ;
static void df_StartDrag( 
                        Widget w,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params) ;
static void df_StartSecondary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ProcessBDrag( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ExtendSecondary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DoStuff( 
                        Widget w,
                        XtPointer closure,
                        Atom *seltype,
                        Atom *type,
                        XtPointer value,
                        unsigned long *length,
                        int *format) ;
static void df_Stuff( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_HandleSelectionReplies( 
                        Widget w,
                        XtPointer closure,
                        XEvent *event,
                        Boolean *cont) ;
static void df_SecondaryNotify( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_HandleTargets( 
                        Widget w,
                        XtPointer closure,
                        Atom *seltype,
                        Atom *type,
                        XtPointer value,
                        unsigned long *length,
                        int *format) ;
static void df_ProcessBDragRelease( 
                        Widget w,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params) ;
static void df_ProcessCopy( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ProcessMove( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeleteSelection( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ClearSelection( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_PageRight( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_PageLeft( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_CopyPrimary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_CutPrimary( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_SetAnchor( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ToggleOverstrike( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_ToggleAddMode( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_SelectAll( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_DeselectAll( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_VoidAction( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_CutClipboard( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_CopyClipboard( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_PasteClipboard( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TraverseDown( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TraverseUp( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TraverseHome( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TraverseNextTabGroup( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TraversePrevTabGroup( 
                        Widget w,
                        XEvent *event,
                        char **params,
                        Cardinal *num_params) ;
static void df_TextEnter( 
                        Widget w,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params) ;
static void df_TextLeave( 
                        Widget w,
                        XEvent *event,
                        String *params,
                        Cardinal *num_params) ;
static void df_ClassPartInitialize( 
                        WidgetClass w_class) ;
static void df_Validates( 
                        XmDataFieldWidget tf) ;
static Boolean df_LoadFontMetrics( 
                        XmDataFieldWidget tf) ;

static void df_ValidateString( 
                        XmDataFieldWidget tf,
                        char *value,
#if NeedWidePrototypes
                        int is_wchar) ;
#else
                        Boolean is_wchar) ;
#endif /* NeedWidePrototypes */

static void df_InitializeTextStruct( 
                        XmDataFieldWidget tf) ;
static Pixmap df_GetClipMask( 
                        XmDataFieldWidget tf,
                        char *pixmap_name) ;
static void df_LoadGCs( 
                        XmDataFieldWidget tf,
                        Pixel background,
                        Pixel foreground) ;

static void df_MakeIBeamOffArea( 
                        XmDataFieldWidget tf,
#if NeedWidePrototypes
                        int width,
                        int height) ;
#else
                        Dimension width,
                        Dimension height) ;
#endif /* NeedWidePrototypes */

static void df_MakeIBeamStencil( 
                        XmDataFieldWidget tf,
                        int line_width) ;
static void df_MakeAddModeCursor( 
                        XmDataFieldWidget tf,
                        int line_width) ;
static void df_MakeCursors( 
                        XmDataFieldWidget tf) ;
static void df_DropDestroyCB( 
                        Widget w,
                        XtPointer clientData,
                        XtPointer callData) ;
static void df_DropTransferCallback( 
                        Widget w,
                        XtPointer closure,
                        Atom *seltype,
                        Atom *type,
                        XtPointer value,
                        unsigned long *length,
                        int *format) ;
static void df_HandleDrop( 
                        Widget w,
                        XmDropProcCallbackStruct *cb) ;
static void df_DragProcCallback( 
                        Widget w,
                        XtPointer client,
                        XtPointer call) ;
static void df_DropProcCallback( 
                        Widget w,
                        XtPointer client,
                        XtPointer call) ;
static void df_RegisterDropSite( 
                        Widget w) ;
static void df_Initialize( 
                        Widget request,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args) ;
static void df_Realize( 
                        Widget w,
                        XtValueMask *valueMask,
                        XSetWindowAttributes *attributes) ;
static void df_Destroy( 
                        Widget wid) ;
static void df_Resize( 
                        Widget w) ;
static XtGeometryResult df_QueryGeometry( 
                        Widget w,
                        XtWidgetGeometry *intended,
                        XtWidgetGeometry *reply) ;
static void DataFieldExpose( 
                        Widget w,
                        XEvent *event,
                        Region region) ;
static Boolean df_SetValues( 
                        Widget old,
                        Widget request,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args) ;
static Boolean DataFieldGetBaselines( 
                        Widget w,
                        Dimension **baselines,
                        int *line_count) ;
static Boolean DataFieldGetDisplayRect( 
                        Widget w,
                        XRectangle *display_rect) ;
static void DataFieldMarginsProc( 
                        Widget w,
                        XmBaselineMargins *margins_rec) ;
static Boolean DataFieldRemove(Widget w,
			       XEvent *event);
static void PictureVerifyCallback(Widget w,
    XtPointer call_d, XtPointer client_d);
static void ClassInit(void);

#endif /* _NO_PROTO */

/***************** End Static Function Declarations  ************/

static XmTextScanType df_sarray[] = {
    XmSELECT_POSITION, XmSELECT_WORD, XmSELECT_LINE
};

static int df_sarraysize = XtNumber(df_sarray);

static XContext _XmDataFDestContext = 0;
static XContext _XmDataFGCContext = 0;
static XContext _XmDataFDNDContext = 0;


/* default translations and action recs */

static XtActionsRec data_actions[] = {
/* ICS DataField actions */
  {"ValidateAndMove",           df_ValidateAndMove},
/* Text Replacing Bindings */
  {"self-insert",		df_InsertChar},
  {"insert-string",		df_InsertString},
  {"delete-previous-character",	df_DeletePrevChar},
  {"delete-next-character",	df_DeleteNextChar},
  {"delete-previous-word",	df_DeletePrevWord},
  {"delete-next-word",		df_DeleteNextWord},
  {"delete-to-end-of-line",	df_DeleteToEndOfLine},
  {"delete-to-start-of-line",	df_DeleteToStartOfLine},
/* Miscellaneous Bindings */
  {"activate",			df_Activate},
  {"process-cancel",		df_ProcessCancel},
  {"process-bdrag",		df_ProcessBDrag},
/* Motion Bindings */
  {"backward-character",	df_BackwardChar},
  {"forward-character",		df_ForwardChar},
  {"backward-word",		df_BackwardWord},
  {"forward-word",		df_ForwardWord},
  {"end-of-line",		df_EndOfLine},
  {"beginning-of-line",		df_BeginningOfLine},
  {"page-left",			df_PageLeft},
  {"page-right",		df_PageRight},
/* Selection Bindings */
  {"key-select",		df_KeySelection},
  {"grab-focus",		df_StartPrimary},
  {"move-destination",		df_MoveDestination},
  {"extend-start",		df_ExtendPrimary},
  {"extend-adjust",		df_ExtendPrimary},
  {"extend-end",		df_ExtendEnd},
  {"delete-selection",		df_DeleteSelection},
  {"clear-selection",		df_ClearSelection},
  {"cut-primary",		df_CutPrimary},
  {"copy-primary",		df_CopyPrimary},
  {"set-anchor",		df_SetAnchor},
  {"toggle-overstrike",		df_ToggleOverstrike},
  {"toggle-add-mode",		df_ToggleAddMode},
  {"select-all",		df_SelectAll},
  {"deselect-all",		df_DeselectAll},
/* Quick Cut and Paste Bindings */
  {"secondary-start",		df_StartSecondary},
  {"secondary-adjust",		df_ExtendSecondary},
  {"copy-to",			df_ProcessCopy},
  {"move-to",			df_ProcessMove},
  {"quick-cut-set",		df_VoidAction},
  {"quick-copy-set",		df_VoidAction},
  {"do-quick-action",		df_VoidAction},
/* Clipboard Bindings */
  {"cut-clipboard",		df_CutClipboard},
  {"copy-clipboard",		df_CopyClipboard},
  {"paste-clipboard",		df_PasteClipboard},
/* Traversal */
  {"traverse-next",		df_TraverseDown},
  {"traverse-prev",		df_TraverseUp},
  {"traverse-home",		df_TraverseHome},
  {"next-tab-group",		df_TraverseNextTabGroup},
  {"prev-tab-group",		df_TraversePrevTabGroup},
/* Focus */
  {"focusIn",			df_TextFocusIn},
  {"focusOut",			df_TextFocusOut},
  {"enter",			df_TextEnter},
  {"leave",			df_TextLeave},
};

#define offset(f) XmPartOffset(XmTextField, f)
#define doffset(f) (XmPartOffset(XmDataField, f) + sizeof(XmTextFieldPart))

static XtResource resources[] =
{
    {
      XmNpicture, XmCPicture, XmRString, sizeof(String),
      doffset(picture_source), XmRImmediate,
      (XtPointer) NULL
    },
    {
      XmNautoFill, XmCAutoFill, XmRBoolean, sizeof(Boolean),
      doffset(auto_fill), XmRImmediate,
      (XtPointer) True
    },
    {
      XmNalignment, XmCAlignment, XmRAlignment, sizeof(unsigned char),
      doffset(alignment), XmRImmediate,
      (XtPointer) XmALIGNMENT_BEGINNING
    },
    {
      XmNpictureErrorCallback, XmCCallback, XmRCallback,
      sizeof(XtCallbackList), doffset(picture_error_cb), XmRCallback,
      (XtPointer) NULL
    },
    {
      XmNvalidateCallback, XmCCallback, XmRCallback,
      sizeof(XtCallbackList), doffset(validate_cb), XmRCallback,
      (XtPointer) NULL
    },

	/* the following are undocumented overrides of XmTextField resources */
    {
      XmNactivateCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      offset(activate_callback),
      XmRCallback, NULL
    },
    {
      XmNlosingFocusCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      offset(losing_focus_callback),
      XmRCallback, NULL
    },
    {
      XmNfocusCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      offset(focus_callback),
      XmRCallback, NULL
    },
    {
      XmNmodifyVerifyCallback, XmCCallback, XmRCallback,
      sizeof(XtCallbackList),
      offset(modify_verify_callback),
      XmRCallback, NULL
    },
    {
      XmNmodifyVerifyCallbackWcs, XmCCallback, XmRCallback,
      sizeof(XtCallbackList),
      offset(wcs_modify_verify_callback),
      XmRCallback, NULL
    },
    {
      XmNmotionVerifyCallback, XmCCallback, XmRCallback,
      sizeof(XtCallbackList),
      offset(motion_verify_callback),
      XmRCallback, NULL
    },
    {
      XmNgainPrimaryCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      offset(gain_primary_callback),
      XmRCallback, NULL
    },
    {
      XmNlosePrimaryCallback, XmCCallback, XmRCallback, sizeof(XtCallbackList),
      offset(lose_primary_callback),
      XmRCallback, NULL
    },
    {
      XmNvalueChangedCallback, XmCCallback, XmRCallback,
      sizeof(XtCallbackList),
      offset(value_changed_callback),
      XmRCallback, NULL
    },
    {
      XmNvalue, XmCValue, XmRString, sizeof(String),
      offset(value),
      XmRString, ""
    },
    {
      XmNvalueWcs, XmCValueWcs, XmRValueWcs, sizeof(wchar_t*),
      offset(wc_value),
      XmRString, NULL
    },
    {
      XmNmarginHeight, XmCMarginHeight, XmRVerticalDimension,
      sizeof(Dimension),
      offset(margin_height),
      XmRImmediate, (XtPointer) 5
    },
    {
      XmNmarginWidth, XmCMarginWidth, XmRHorizontalDimension,
      sizeof(Dimension),
      offset(margin_width),
      XmRImmediate, (XtPointer) 5
    },
    {
      XmNcursorPosition, XmCCursorPosition, XmRTextPosition,
      sizeof (XmTextPosition),
      offset(cursor_position),
      XmRImmediate, (XtPointer) 0
    },
    {
      XmNcolumns, XmCColumns, XmRShort, sizeof(short),
      offset(columns),
      XmRImmediate, (XtPointer) 20
    },
    {
      XmNmaxLength, XmCMaxLength, XmRInt, sizeof(int),
      offset(max_length),
      XmRImmediate, (XtPointer) INT_MAX
    },
    {
      XmNblinkRate, XmCBlinkRate, XmRInt, sizeof(int),
      offset(blink_rate),
      XmRImmediate, (XtPointer) 500
    },
    {
      XmNfontList, XmCFontList, XmRFontList, sizeof(XmFontList),
      offset(font_list),
      XmRString, NULL
    },
    {
      XmNselectionArray, XmCSelectionArray, XmRPointer,
      sizeof(XtPointer),
      offset(selection_array),
      XmRImmediate, (XtPointer) df_sarray
    },
    {
      XmNselectionArrayCount, XmCSelectionArrayCount, XmRInt, sizeof(int),
      offset(selection_array_count),
      XmRInt, (XtPointer) &df_sarraysize
    },
    {
      XmNresizeWidth, XmCResizeWidth, XmRBoolean, sizeof(Boolean),
      offset(resize_width),
      XmRImmediate, (XtPointer) False
    },
    {
      XmNpendingDelete, XmCPendingDelete, XmRBoolean, sizeof(Boolean),
      offset(pending_delete),
      XmRImmediate, (XtPointer) True
    },
    {
      XmNeditable, XmCEditable, XmRBoolean, sizeof(Boolean),
      offset(editable),
      XmRImmediate, (XtPointer) True
    },
    {
      XmNcursorPositionVisible, XmCCursorPositionVisible, XmRBoolean,
      sizeof(Boolean),
      offset(cursor_position_visible),
      XmRImmediate, (XtPointer) True
    },
   {
     XmNverifyBell, XmCVerifyBell, XmRBoolean, sizeof(Boolean),
     offset(verify_bell),
     XmRImmediate, (XtPointer) XmDYNAMIC_BOOL
   },
   {
     XmNselectThreshold, XmCSelectThreshold, XmRInt, sizeof(int),
     offset(threshold),
     XmRImmediate, (XtPointer) 5
   },
   {
     XmNnavigationType, XmCNavigationType, XmRNavigationType,
     sizeof (unsigned char),
     XmPartOffset(XmPrimitive, navigation_type),
     XmRImmediate, (XtPointer) XmTAB_GROUP
   },
};

/* Definition for resources that need special processing in get values */
static XmSyntheticResource syn_resources[] =
{
   {
     XmNmarginWidth,
     sizeof(Dimension),
     offset(margin_width),
     _XmFromHorizontalPixels,
     _XmToHorizontalPixels
   },

   {
     XmNmarginHeight,
     sizeof(Dimension),
     offset(margin_height),
     _XmFromVerticalPixels,
     _XmToVerticalPixels
   },

   {
     XmNvalue,
     sizeof(char *),
     offset(value),
     df_MakeCopy,
     NULL
   },

   {
     XmNvalueWcs,
     sizeof(wchar_t *),
     offset(wc_value),
     df_WcsMakeCopy,
     NULL
   },

};
#undef offset

XmPrimitiveClassExtRec _XmDataFPrimClassExtRec = {
    NULL,
    NULLQUARK,
    XmPrimitiveClassExtVersion,
    sizeof(XmPrimitiveClassExtRec),
    DataFieldGetBaselines,		/* widget_baseline        */
    DataFieldGetDisplayRect,		/* widget_display_rect    */
    DataFieldMarginsProc,		/* get/set widget margins */
};


externaldef(xmdatafieldclassrec) XmDataFieldClassRec xmDataFieldClassRec =
{
   {
      (WidgetClass) &xmPrimitiveClassRec,       /* superclass         */
      "XmDataField",				/* class_name         */
      sizeof(XmTextFieldPart) 
      + sizeof(XmDataFieldPart),		/* widget_size        */
      ClassInit,		                /* class_initialize   */
      df_ClassPartInitialize,			/* class_part_initiali*/
      FALSE,					/* class_inited       */
      df_Initialize,				/* initialize         */
      (XtArgsProc)NULL,				/* initialize_hook    */
      df_Realize,				/* realize            */
      data_actions,				/* actions            */
      XtNumber(data_actions),			/* num_actions        */
      resources,				/* resources          */
      XtNumber(resources),			/* num_resources      */
      NULLQUARK,				/* xrm_class          */
      TRUE,					/* compress_motion    */
      XtExposeCompressMaximal,			/* compress_exposure  */
      TRUE,					/* compress_enterleave*/
      FALSE,					/* visible_interest   */
      df_Destroy,				/* destroy            */
      df_Resize,				/* resize             */
      DataFieldExpose,				/* expose             */
      df_SetValues,				/* set_values         */

#ifdef sco    /* ICS -pwc 7/28/93 */
      NULL,					/* set_values_hook    */
#else
      (XtArgsFunc)NULL,				/* set_values_hook    */
#endif        /* sco */

      XtInheritSetValuesAlmost,			/* set_values_almost  */
      (XtArgsProc)NULL,				/* get_values_hook    */

#ifdef sco		/* ICS - pwc 7/28/93 */
      NULL,					/* accept_focus       */
#else
      (XtAcceptFocusProc)NULL,			/* accept_focus       */
#endif /* sco */

      XtVersion,			/* version            */
      NULL,					/* callback_private   */
      NULL,					/* tm_table           */
      df_QueryGeometry,				/* query_geometry     */
      (XtStringProc)NULL,			/* display accel      */
      NULL,					/* extension          */
   },

   {  	                          		/* Xmprimitive        */
      XmInheritBorderHighlight,        		/* border_highlight   */
      XmInheritBorderUnhighlight,              	/* border_unhighlight */
      NULL,					/* translations	      */
      (XtActionProc)NULL,             		/* arm_and_activate   */
      syn_resources,            		/* syn resources      */
      XtNumber(syn_resources),  		/* num syn_resources  */
      (XtPointer) &_XmDataFPrimClassExtRec,	/* extension          */
   },
   {                            		/* text classs        */
      NULL,                     		/* extension          */
   }
};

externaldef(xmdatafieldwidgetclass) WidgetClass xmDataFieldWidgetClass =
					 (WidgetClass) &xmDataFieldClassRec;

XmOffsetPtr XmDataField_offsets;

static void
#ifdef _NO_PROTO
ClassInit()
#else
ClassInit(void)
#endif
{
    XmDataFieldClassRec* wc = &xmDataFieldClassRec;
    int i;

    XmResolveAllPartOffsets(xmDataFieldWidgetClass,
			    &XmDataField_offsets,
			    NULL);

    _XmProcessLock(); 
    for(i=0; i<wc->primitive_class.num_syn_resources; i++) {
        (wc->primitive_class.syn_resources)[i].resource_offset =
            XmGetPartOffset(wc->primitive_class.syn_resources + i,
                            &XmDataField_offsets);
    }
    _XmProcessUnlock(); 
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ValidateAndMove(w, ev, args, nargs)
     Widget w;
     XEvent *ev;
     String *args;
     Cardinal *nargs;
#else
df_ValidateAndMove(
    Widget w,
    XEvent *ev,
    String *args,
    Cardinal *nargs)
#endif
{
    XmDataFieldCallbackStruct cbs;
    
    /*
     * We are guaranteed that the picture will have accepted the string, so
     * just call the verify callbacks.
     */
    cbs.w      = w;
    cbs.text   = XmDataFieldGetString(w);
    cbs.accept = True;
    XtCallCallbackList(w, XmDataField_validate_cb(w), (XtPointer)&cbs);
    XtFree(cbs.text);
    
    /*
     * Make sure we accepted it
     */
    if(cbs.accept == False)
    {
	XBell(XtDisplay(w), 0);
	return;
    }

    /*
     * Otherwise just give up the focus and process the traversal as
     * normal
     */
    if(*nargs > 0 && strncasecmp(args[0], "prev", 4) == 0) {
	(void) XmProcessTraversal(w, XmTRAVERSE_PREV_TAB_GROUP);
    } else {
	(void) XmProcessTraversal(w, XmTRAVERSE_NEXT_TAB_GROUP);
    }
}



/* ARGSUSED */
static void
#ifdef _NO_PROTO
PictureVerifyCallback(w, client_d, call_d)
    Widget w;
    XtPointer client_d;
    XtPointer call_d;
#else
PictureVerifyCallback(
    Widget w,
    XtPointer client_d,
    XtPointer call_d )
#endif /* _NO_PROTO */
{
    XmTextVerifyCallbackStruct *cbs = 
	(XmTextVerifyCallbackStruct*) call_d;
    char *curr, *newptr, *changed = NULL;
    int src, dst, i;
    XmPictureState ps;
    Boolean done = False;

    /*
     * If we're just backspacing, allow the change irregarless
     */
    if(cbs->startPos < cbs->currInsert || cbs->text->length == 0)
	return;
    
    /*
     * Get the current string, and splice in the intended changes
     */
    curr = XmDataFieldGetString(w);
    
    newptr = XtMalloc((cbs->text->length + strlen(curr) + 2) * 
		      sizeof(char *));
    
    dst = 0;
    
    /* Copy in the stuff before the modification */
    for(src=0; src<cbs->startPos; src++, dst++)
 	newptr[dst] = curr[src];

    /* Then the modification text */
    if(cbs->text->ptr) {
	for(src=0; src<cbs->text->length; src++, dst++)
	    newptr[dst] = cbs->text->ptr[src];
    }
    /* Then the last bit */
    if(cbs->endPos > cbs->startPos) {
	for(dst = cbs->endPos + cbs->text->length;
	    src<cbs->endPos;
	    src++, dst++)
	    newptr[dst] = curr[src];
    }
    /* And stick a null in for good measure and sanity in debugging */
    newptr[dst] = '\0';

    /*
     * Run it through the picture, and bail if it isn't accepted 
     */
    ps = XmGetNewPictureState(XmDataField_picture(w));

    for(i=0; i<strlen(newptr); i++) {
	changed = XmPictureProcessCharacter(ps, newptr[i], &done);
	if(changed == NULL || done) break;
    }
	
    if(changed == NULL) {
	cbs->doit = False;
	XtCallCallbackList(w, XmDataField_picture_error_cb(w), NULL);
	return;
    }


    /*
     * And now try autofilling
     */
    if(XmDataField_auto_fill(w)) {
	changed = XmPictureDoAutoFill(ps);
    } else {
	changed = XmPictureGetCurrentString(ps);
    }

    /*
     * Now the hard part:  we may have been auto-filled, so we have to
     * massage the callback struct to reflect what's happened
     */

    cbs->startPos = 0;
    /* CR03686 cbs->endPos = strlen(newptr); */
    cbs->text->ptr = strdup(changed);
    cbs->text->length = strlen(changed);

    XtFree(newptr);
    XmPictureDeleteState(ps);
}


/* USE ITERATIONS OF mblen TO COUNT THE NUMBER OF CHARACTERS REPRESENTED
 * BY n_bytes BYTES POINTED TO BY ptr, a pointer to char*.
 * n_bytes does not include NULL terminator (if any), nor does return.
 */

/* ARGSUSED */
static int
#ifdef _NO_PROTO
_XmDataFieldCountCharacters( tf, ptr, n_bytes )
        XmDataFieldWidget tf ;
        char *ptr ;
        int n_bytes ;
#else
_XmDataFieldCountCharacters(
        XmDataFieldWidget tf,
        char *ptr,
        int n_bytes )
#endif /* _NO_PROTO */
{
   char * bptr;
   int count = 0;
   int char_size = 0;

   if (n_bytes <= 0 || ptr == NULL || *ptr == '\0')
      return 0;

   if (XmTextF_max_char_size(tf) == 1)
      return n_bytes;

   bptr = ptr;

   for (bptr = ptr; n_bytes > 0; count++, bptr+= char_size){
      char_size = mblen(bptr, XmTextF_max_char_size(tf));
      if (char_size < 0) break; /* error */
      n_bytes -= char_size;
   }
   return count;
}

/* USE ITERATIONS OF wctomb TO COUNT THE NUMBER OF BYTES REQUIRED FOR THE
 * MULTI-BYTE REPRESENTION OF num_chars WIDE CHARACTERS IN wc_value.
 * COUNT TERMINATED IF NULL ENCOUNTERED IN THE STRING.
 * NUMBER OF BYTES IS RETURNED.
 */

/* ARGSUSED */
int
#ifdef _NO_PROTO
_XmDataFieldCountBytes( tf, wc_value, num_chars )
	XmDataFieldWidget tf;
	wchar_t * wc_value; 
	int num_chars;
#else /* _NO_PROTO */
_XmDataFieldCountBytes(
	XmDataFieldWidget tf,
	wchar_t * wc_value, 
	int num_chars)
#endif /* _NO_PROTO */
{
   wchar_t 	* wc_ptr;
   char 	tmp[MB_LEN_MAX];  /* defined in limits.h: max in any locale */
   int 		n_bytes = 0;

   if (num_chars <= 0 || wc_value == NULL || *wc_value == (wchar_t)0L)
      return 0;

   if (XmTextF_max_char_size(tf) == 1)
      return num_chars;

   wc_ptr = wc_value;
   while ((num_chars > 0) && (*wc_ptr != (wchar_t)0L)){
      n_bytes += wctomb(tmp, *wc_ptr);
      num_chars--;
      wc_ptr++;
   }
   return n_bytes;
}

/*ARGSUSED*/
static void 
#ifdef _NO_PROTO
df_MakeCopy( w, n, value )
        Widget w ;
	int n;
        XtArgVal *value ;
#else
df_MakeCopy(
        Widget w,
	int n,
        XtArgVal *value )
#endif /* _NO_PROTO */
{
    (*value) = (XtArgVal) XmDataFieldGetString (w);
}

/*ARGSUSED*/
static void 
#ifdef _NO_PROTO
df_WcsMakeCopy( w, n, value )
        Widget w ;
	int n;
        XtArgVal *value ;
#else
df_WcsMakeCopy(
        Widget w,
	int n,
        XtArgVal *value )
#endif /* _NO_PROTO */
{
    (*value) = (XtArgVal) XmDataFieldGetStringWcs (w);
}

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_FreeContextData(w, clientData, callData)
    Widget w;
    XtPointer clientData;
    XtPointer callData;
#else
df_FreeContextData( 
	Widget w,
	XtPointer clientData,
	XtPointer callData )
#endif /* _NO_PROTO */
{
    XmTextContextData ctx_data = (XmTextContextData) clientData;
    Display *display = DisplayOfScreen(ctx_data->screen);
    XtPointer data_ptr;

    if (XFindContext(display, (Window) ctx_data->screen,
                     ctx_data->context, (char **) &data_ptr)) {

       if (ctx_data->type == _XM_IS_PIXMAP_CTX) {
          XFreePixmap(display, (Pixmap) data_ptr);
       } else if (ctx_data->type != '\0') {
          if (data_ptr)
             XtFree((char *) data_ptr);
       }

       XDeleteContext (display, (Window) ctx_data->screen, ctx_data->context);
    }

    XtFree ((char *) ctx_data);
}

static TextFDestData 
#ifdef _NO_PROTO
df_GetTextFDestData( w )
        Widget w ;
#else
df_GetTextFDestData(
        Widget w )
#endif /* _NO_PROTO */
{
   static TextFDestData dest_data;
   Display *display = XtDisplay(w);
   Screen *screen = XtScreen(w);

   if (_XmDataFDestContext == 0)
      _XmDataFDestContext = XUniqueContext();

   if (XFindContext(display, (Window) screen,
                    _XmDataFDestContext, (char **) &dest_data)) {
       XmTextContextData ctx_data;
       Widget xm_display = (Widget) XmGetXmDisplay(display);

       ctx_data = (XmTextContextData) XtMalloc(sizeof(XmTextContextDataRec));

       ctx_data->screen = screen;
       ctx_data->context = _XmDataFDestContext;
       ctx_data->type = _XM_IS_DEST_CTX;

       dest_data = (TextFDestData) XtCalloc(1, sizeof(TextFDestDataRec));

       XtAddCallback(xm_display, XmNdestroyCallback, 
                     (XtCallbackProc) df_FreeContextData, (XtPointer) ctx_data);

       XSaveContext(XtDisplay(w), (Window) screen,
                    _XmDataFDestContext, (XPointer)dest_data);
   }

   return dest_data;
}

static void
#ifdef _NO_PROTO
df_SetDropContext( w )
        Widget w ;
#else
df_SetDropContext(
        Widget w )
#endif /* _NO_PROTO */
{
   Display *display = XtDisplay(w);
   Screen *screen = XtScreen(w);

   if (_XmDataFDNDContext == 0)
      _XmDataFDNDContext = XUniqueContext();

   XSaveContext(display, (Window)screen,
                _XmDataFDNDContext, (XPointer)w);
}


static void
#ifdef _NO_PROTO
df_DeleteDropContext( w )
        Widget w ;
#else
df_DeleteDropContext(
        Widget w )
#endif /* _NO_PROTO */
{
   Display *display = XtDisplay(w);
   Screen *screen = XtScreen(w);

   XDeleteContext(display, (Window)screen, _XmDataFDNDContext);
}


Widget
#ifdef _NO_PROTO
_XmDataFieldGetDropReciever( w )
        Widget w ;
#else
_XmDataFieldGetDropReciever(
        Widget w )
#endif /* _NO_PROTO */
{
   Widget widget;

   if (_XmDataFDNDContext == 0) return NULL;

   if (!XFindContext(XtDisplay(w), (Window) XtScreen(w),
                     _XmDataFDNDContext, (char **) &widget)) {
      return widget;
   } 

   return NULL;
}



static TextFGCData 
#ifdef _NO_PROTO
df_GetTextFGCData( w )
        Widget w ;
#else
df_GetTextFGCData(
        Widget w )
#endif /* _NO_PROTO */
{
   static TextFGCData gc_data;
   Display *display = XtDisplay(w);
   Screen *screen = XtScreen(w);

   if (_XmDataFGCContext == 0)
      _XmDataFGCContext = XUniqueContext();

   if (XFindContext(display, (Window)screen,
                    _XmDataFGCContext, (char **)&gc_data)) {
       XmTextContextData ctx_data;
       Widget xm_display = (Widget) XmGetXmDisplay(display);

       ctx_data = (XmTextContextData) XtMalloc(sizeof(XmTextContextDataRec));

       ctx_data->screen = screen;
       ctx_data->context = _XmDataFGCContext;
       ctx_data->type = _XM_IS_GC_DATA_CTX;

       gc_data = (TextFGCData) XtCalloc(1, sizeof(TextFGCDataRec));

       XtAddCallback(xm_display, XmNdestroyCallback, 
                     (XtCallbackProc) df_FreeContextData, (XtPointer) ctx_data);

       XSaveContext(display, (Window)screen, _XmDataFGCContext, 
		    (XPointer)gc_data);
       gc_data->tf = (XmDataFieldWidget) w;
   }

   if (gc_data->tf == NULL) gc_data->tf = (XmDataFieldWidget) w;

   return gc_data;
}

void
#ifdef _NO_PROTO
_XmDataFToggleCursorGC( widget )
        Widget widget;
#else
_XmDataFToggleCursorGC(
        Widget widget )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) widget;
    XGCValues values;
    unsigned long valuemask = GCFillStyle|GCFunction|GCForeground|GCBackground;

    if (!XtIsRealized(widget)) return;

    if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

    if (XmTextF_overstrike(tf)) {
      if (!XmTextF_add_mode(tf) && XtIsSensitive(widget) &&
	  (XmTextF_has_focus(tf) || XmTextF_has_destination(tf))) {
	values.fill_style = FillSolid;
      } else {
	values.fill_style = FillTiled;
      }
      values.foreground = values.background =
	tf->primitive.foreground ^ tf->core.background_pixel;
      values.function = GXxor;
    } else {
      if (XtIsSensitive(widget) && !XmTextF_add_mode(tf) &&
	  (XmTextF_has_focus(tf) || XmTextF_has_destination(tf))) {
	if (XmTextF_cursor(tf) == XmUNSPECIFIED_PIXMAP) return;
	values.stipple = XmTextF_cursor(tf);
      } else {
	if (XmTextF_add_mode_cursor(tf) == XmUNSPECIFIED_PIXMAP) return;
	values.stipple = XmTextF_add_mode_cursor(tf);
      }
      values.fill_style = FillStippled;
      values.function = GXcopy;
      if (XmTextF_have_inverted_image_gc(tf)){
	values.background = tf->primitive.foreground;
	values.foreground = tf->core.background_pixel;
      } else {
	values.foreground = tf->primitive.foreground;
	values.background = tf->core.background_pixel;
      }
      valuemask |= GCStipple;
    }
    XChangeGC(XtDisplay(widget), XmTextF_image_gc(tf), valuemask, &values);
}

/*
 * Find the highlight record corresponding to the given position.  Returns a
 * pointer to the record.  The third argument indicates whether we are probing
 * the left or right edge of a highlighting range.
 */
static _XmHighlightRec * 
#ifdef _NO_PROTO
df_FindHighlight( w, position )
        XmDataFieldWidget w ;
        XmTextPosition position ;
#else
df_FindHighlight(
        XmDataFieldWidget w,
        XmTextPosition position )
#endif /* _NO_PROTO */
{
    _XmHighlightRec *l = XmTextF_highlight(w).list;
    int i;

    for (i=XmTextF_highlight(w).number - 1 ; i>=0 ; i--)
        if (position >= l[i].position) {
            l = l + i;
            break;
        }

    return(l);
}

static void 
#ifdef _NO_PROTO
df_InsertHighlight( w, position, mode )
        XmDataFieldWidget w ;
        XmTextPosition position ;
        XmHighlightMode mode ;
#else
df_InsertHighlight(
        XmDataFieldWidget w,
        XmTextPosition position,
        XmHighlightMode mode )
#endif /* _NO_PROTO */
{
    _XmHighlightRec *l1;
    _XmHighlightRec *l = XmTextF_highlight(w).list;
    int i, j;

    l1 = df_FindHighlight(w, position);
    if (l1->position == position)
       l1->mode = mode;
    else {
       i = (l1 - l) + 1;
       XmTextF_highlight(w).number++;
       if (XmTextF_highlight(w).number > XmTextF_highlight(w).maximum) {
          XmTextF_highlight(w).maximum = XmTextF_highlight(w).number;
          l = XmTextF_highlight(w).list = (_XmHighlightRec *)XtRealloc((char *) l,
              (unsigned)(XmTextF_highlight(w).maximum * sizeof(_XmHighlightRec)));
       }
       for (j=XmTextF_highlight(w).number-1 ; j>i ; j--)
           l[j] = l[j-1];
       l[i].position = position;
       l[i].mode = mode;
    }
}

static void 
#ifdef _NO_PROTO
DataFieldSetHighlight( tf, left, right, mode )
        XmDataFieldWidget tf ;
        XmTextPosition left ;
        XmTextPosition right ;
        XmHighlightMode mode ;
#else
DataFieldSetHighlight(
        XmDataFieldWidget tf,
        XmTextPosition left,
        XmTextPosition right,
        XmHighlightMode mode )
#endif /* _NO_PROTO */
{
    _XmHighlightRec *l;
    XmHighlightMode endmode;
    int i, j;

    if (left >= right || right <= 0) return;

    _XmDataFieldDrawInsertionPoint(tf, False);
    endmode = df_FindHighlight(tf, right)->mode;
    df_InsertHighlight(tf, left, mode);
    df_InsertHighlight(tf, right, endmode);
    l = XmTextF_highlight(tf).list;
    i = 1;
    while (i < XmTextF_highlight(tf).number) {
        if (l[i].position >= left && l[i].position < right)
            l[i].mode = mode;
        if (l[i].mode == l[i-1].mode) {
            XmTextF_highlight(tf).number--;
            for (j=i ; j<XmTextF_highlight(tf).number ; j++)
                l[j] = l[j+1];
        } else i++;
    }
    if (XmTextF_cursor_position(tf) > left && XmTextF_cursor_position(tf) < right){
       if (mode == XmHIGHLIGHT_SELECTED){
          df_InvertImageGC(tf);
       } else if (mode != XmHIGHLIGHT_SELECTED){
          df_ResetImageGC(tf);
       }
    }
    XmTextF_refresh_ibeam_off(tf) = True;
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/*
 * Get x and y based on position.
 */
static Boolean 
#ifdef _NO_PROTO
df_GetXYFromPos( tf, position, x, y )
        XmDataFieldWidget tf ;
        XmTextPosition position ;
        Position *x ;
        Position *y ;
#else
df_GetXYFromPos(
        XmDataFieldWidget tf,
        XmTextPosition position,
        Position *x,
        Position *y )
#endif /* _NO_PROTO */
{
    int	x1, x2;

    /* initialize the x and y positions to zero */
    if (XmDataField_alignment(tf) == XmALIGNMENT_BEGINNING)
    {
	*x = 0;
	*y = 0;

	if (position > XmTextF_string_length(tf)) return False;

	if (XmTextF_max_char_size(tf) != 1) {
	    x1 = df_FindPixelLength(tf, (char*)XmTextF_wc_value(tf), (int)position);
	} else {
	    x1 = df_FindPixelLength(tf, XmTextF_value(tf), (int)position);
	}
    }
    else
    {
	int	length;

	*x = tf->core.width - (XmTextF_margin_width(tf) +
			       tf->primitive.highlight_thickness +
			       tf->primitive.shadow_thickness);
	*y = 0;

	length = XmTextF_string_length(tf) - position;

	if (length < 0) return False;

	if (XmTextF_max_char_size(tf) != 1) {
	    x1 = df_FindPixelLength(tf, (char*)(XmTextF_wc_value(tf) + position),
				 length);
	} else {
	    x1 = df_FindPixelLength(tf, XmTextF_value(tf) + position, length);
	}
    }

    *y += tf->primitive.highlight_thickness + tf->primitive.shadow_thickness
	  + XmTextF_margin_top(tf) + XmTextF_font_ascent(tf);
    x2 = (Position) XmTextF_h_offset(tf);

    if (XmDataField_alignment(tf) == XmALIGNMENT_BEGINNING)
    {
	*x += x1 + x2;
    }
    else
    {
	*x -= (x1 - x2);
    }

    return True;
}

static Boolean 
#ifdef _NO_PROTO
df_CurrentCursorState( tf )
        XmDataFieldWidget tf ;
#else
df_CurrentCursorState(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
    if (XmTextF_cursor_on(tf) < 0) return False;
    if (XmTextF_blink_on(tf) || !XtIsSensitive((Widget)tf))
        return True;
    return False;
}

/*
 * Paint insert cursor
 */
static void 
#ifdef _NO_PROTO
df_PaintCursor( tf )
        XmDataFieldWidget tf ;
#else
df_PaintCursor(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
    Position x, y;
    XmTextPosition position;

    if (!XmTextF_cursor_position_visible(tf)) return;

    if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

    position = XmTextF_cursor_position(tf);
    (void) df_GetXYFromPos(tf, position, &x, &y);

    if (!XmTextF_overstrike(tf))
      x -=(XmTextF_cursor_width(tf) >> 1) + 1; /* "+1" for 1 pixel left of char */
    else {
      int pxlen;
      if (XmTextF_max_char_size(tf) != 1) 
	pxlen = df_FindPixelLength(tf, (char*)&(XmTextF_wc_value(tf)[position]), 1);
      else 
	pxlen = df_FindPixelLength(tf, &(XmTextF_value(tf)[position]), 1);
      if (pxlen > XmTextF_cursor_width(tf))
	x += (pxlen - XmTextF_cursor_width(tf)) >> 1;
    }
    y = (y + (Position) XmTextF_font_descent(tf)) -
	 (Position) XmTextF_cursor_height(tf);

/* If time to paint the I Beam... first capture the IBeamOffArea, then draw
 * the IBeam */

    if (XmTextF_refresh_ibeam_off(tf) == True){ /* get area under IBeam first */
      /* Fill is needed to realign clip rectangle with gc */
       XFillRectangle(XtDisplay((Widget)tf), XtWindow((Widget)tf),
                         XmTextF_save_gc(tf), 0, 0, 0, 0);

       XCopyArea(XtDisplay(tf), XtWindow(tf), XmTextF_ibeam_off(tf), 
		 XmTextF_save_gc(tf), x, y, XmTextF_cursor_width(tf), 
		 XmTextF_cursor_height(tf), 0, 0);
       XmTextF_refresh_ibeam_off(tf) = False;
    }

    if ((XmTextF_cursor_on(tf) >= 0) && XmTextF_blink_on(tf)) {
       XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_image_gc(tf), x, y,
		      XmTextF_cursor_width(tf), XmTextF_cursor_height(tf));
    } else {
       XCopyArea(XtDisplay(tf), XmTextF_ibeam_off(tf), XtWindow(tf), 
		 XmTextF_save_gc(tf), 0, 0, XmTextF_cursor_width(tf), 
		 XmTextF_cursor_height(tf), x, y);
    }
}

void 
#ifdef _NO_PROTO
_XmDataFieldDrawInsertionPoint( tf, turn_on )
        XmDataFieldWidget tf ;
        Boolean turn_on ;
#else
_XmDataFieldDrawInsertionPoint(
        XmDataFieldWidget tf,
        Boolean turn_on )
#endif /* _NO_PROTO */
{

    if (turn_on == True) {
       XmTextF_cursor_on(tf) += 1;
       if (XmTextF_blink_rate(tf) == 0 || !XmTextF_has_focus(tf))
	  XmTextF_blink_on(tf) = True;
    } else {
       if (XmTextF_blink_on(tf) && (XmTextF_cursor_on(tf) == 0))
	  if (XmTextF_blink_on(tf) == df_CurrentCursorState(tf) &&
	      XtIsRealized((Widget)tf)){
	     XmTextF_blink_on(tf) = !XmTextF_blink_on(tf);
             df_PaintCursor(tf);
       }
       XmTextF_cursor_on(tf) -= 1;
    }

    if (XmTextF_cursor_on(tf) < 0 || !XtIsRealized((Widget) tf))
        return;

    df_PaintCursor(tf);
}

static void 
#ifdef _NO_PROTO
df_BlinkInsertionPoint( tf )
        XmDataFieldWidget tf ;
#else
df_BlinkInsertionPoint(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
    if ((XmTextF_cursor_on(tf) >= 0) &&
	XmTextF_blink_on(tf) == df_CurrentCursorState(tf) &&
	XtIsRealized((Widget)tf)) {
       XmTextF_blink_on(tf) = !XmTextF_blink_on(tf);
       df_PaintCursor(tf);
    }
}



/*
 * Handle blink on and off
 */
/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_HandleTimer( closure, id )
        XtPointer closure ;
        XtIntervalId *id ;
#else
df_HandleTimer(
        XtPointer closure,
        XtIntervalId *id )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) closure;

    if (XmTextF_blink_rate(tf) != 0)
        XmTextF_timer_id(tf) =
		 XtAppAddTimeOut(XtWidgetToApplicationContext((Widget)tf),
				 (unsigned long)XmTextF_blink_rate(tf),
                                 df_HandleTimer,
                                 (XtPointer) closure);
    if (XmTextF_has_focus(tf) && XtIsSensitive((Widget)tf))
	df_BlinkInsertionPoint(tf);
}


/*
 * Change state of blinking insert cursor on and off
 */
static void 
#ifdef _NO_PROTO
df_ChangeBlinkBehavior( tf, turn_on )
        XmDataFieldWidget tf ;
        Boolean turn_on ;
#else
df_ChangeBlinkBehavior(
        XmDataFieldWidget tf,
#if NeedWidePrototypes
        int turn_on )
#else
        Boolean turn_on )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{

    if (turn_on) {
        if (XmTextF_blink_rate(tf) != 0 && XmTextF_timer_id(tf) == (XtIntervalId)0)
            XmTextF_timer_id(tf) =
                XtAppAddTimeOut(XtWidgetToApplicationContext((Widget)tf),
			        (unsigned long)XmTextF_blink_rate(tf),
                                df_HandleTimer,
                                (XtPointer) tf);
        XmTextF_blink_on(tf) = True;
    } else {
        if (XmTextF_timer_id(tf))
            XtRemoveTimeOut(XmTextF_timer_id(tf));
        XmTextF_timer_id(tf) = (XtIntervalId)0;
    }
}

static void 
#ifdef _NO_PROTO
df_GetRect( tf, rect )
        XmDataFieldWidget tf ;
        XRectangle *rect ;
#else
df_GetRect(
        XmDataFieldWidget tf,
        XRectangle *rect )
#endif /* _NO_PROTO */
{
  Dimension margin_width = XmTextF_margin_width(tf) +
	                   tf->primitive.shadow_thickness +
			   tf->primitive.highlight_thickness;
  Dimension margin_top = XmTextF_margin_top(tf) + tf->primitive.shadow_thickness +
			 tf->primitive.highlight_thickness;
  Dimension margin_bottom = XmTextF_margin_bottom(tf) +
			    tf->primitive.shadow_thickness +
			    tf->primitive.highlight_thickness;

  if (margin_width < tf->core.width)
     rect->x = margin_width;
  else
     rect->x = tf->core.width;

  if (margin_top  < tf->core.height)
     rect->y = margin_top;
  else
     rect->y = tf->core.height;

  if ((int)(2 * margin_width) < (int)tf->core.width)
     rect->width = (int) tf->core.width - (2 * margin_width);
  else
     rect->width = 0;

  if ((int)(margin_top + margin_bottom) < (int)tf->core.height)
     rect->height = (int) tf->core.height - (margin_top + margin_bottom);
  else
     rect->height = 0;
}

static void
#ifdef _NO_PROTO
df_CheckHasRect( tf )
        XmDataFieldWidget tf ;
#else
df_CheckHasRect(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
 /*
  * Make sure the cached GC has the clipping rectangle
  * set to the current widget.
  */
  if (!XmTextF_has_rect(tf)) {
     TextFGCData gc_data = df_GetTextFGCData((Widget)tf);
     XmTextF_has_rect(gc_data->tf) = False;
     gc_data->tf = tf;
     XmTextF_has_rect(tf) = True;
  }
}

static void 
#ifdef _NO_PROTO
df_XmSetFullGC( tf, gc )
        XmDataFieldWidget tf ;
        GC gc ;
#else
df_XmSetFullGC(
        XmDataFieldWidget tf,
        GC gc )
#endif /* _NO_PROTO */
{
  XRectangle ClipRect;

 /* adjust clip rectangle to allow the cursor to paint into the margins */
  ClipRect.x = tf->primitive.shadow_thickness +
               tf->primitive.highlight_thickness;
  ClipRect.y = tf->primitive.shadow_thickness +
               tf->primitive.highlight_thickness;
  ClipRect.width = tf->core.width - (2 * (tf->primitive.shadow_thickness +
                                          tf->primitive.highlight_thickness));
  ClipRect.height = tf->core.height - (2 * (tf->primitive.shadow_thickness +
                                           tf->primitive.highlight_thickness));

  XSetClipRectangles(XtDisplay(tf), gc, 0, 0, &ClipRect, 1,
                     Unsorted);
}

static void 
#ifdef _NO_PROTO
df_XmSetMarginGC( tf, gc )
        XmDataFieldWidget tf ;
        GC gc ;
#else
df_XmSetMarginGC(
        XmDataFieldWidget tf,
        GC gc )
#endif /* _NO_PROTO */
{
  XRectangle ClipRect;

  df_GetRect(tf, &ClipRect);
  XSetClipRectangles(XtDisplay(tf), gc, 0, 0, &ClipRect, 1,
                     Unsorted);
}


static void
#ifdef _NO_PROTO
df_XmResetSaveGC( tf, gc )
        XmDataFieldWidget tf ;
        GC gc ;
#else
df_XmResetSaveGC(
        XmDataFieldWidget tf,
        GC gc )
#endif /* _NO_PROTO */
{
  XSetClipMask(XtDisplay(tf), gc, None);
}

/*
 * Set new clipping rectangle for text field.  This is
 * done on each focus in event since the text field widgets
 * share the same GC.
 */
void 
#ifdef _NO_PROTO
_XmDataFieldSetClipRect( tf )
        XmDataFieldWidget tf ;
#else
_XmDataFieldSetClipRect(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
  XGCValues values;
  unsigned long valuemask = (unsigned long) 0;
  

 /*
  * Make sure the cached GC has the clipping rectangle
  * set to the current widget.
  */
  df_CheckHasRect(tf);

  df_XmSetMarginGC(tf, XmTextF_gc(tf));
  df_XmSetFullGC(tf, XmTextF_image_gc(tf));

  df_ResetClipOrigin(tf, False);


 /* Restore cached save gc to state correct for this instantiation */
  if (XmTextF_save_gc(tf)){
     valuemask = (GCFunction | GCBackground | GCForeground);
     values.function = GXcopy;
     values.foreground = tf->primitive.foreground ;
     values.background = tf->core.background_pixel;
     XChangeGC(XtDisplay(tf), XmTextF_save_gc(tf), valuemask, &values);
  }

 /* Restore cached text gc to state correct for this instantiation */

  if (XmTextF_gc(tf)){
     if (!XmTextF_have_fontset(tf) && (XmTextF_font(tf) != NULL)){
        valuemask |= GCFont;
        values.font = XmTextF_font(tf)->fid;
     }
     valuemask |= GCGraphicsExposures;
     values.graphics_exposures = (Bool) True;
     values.foreground = tf->primitive.foreground ^ tf->core.background_pixel;
     values.background = 0;
     XChangeGC(XtDisplay(tf), XmTextF_gc(tf), valuemask, &values);
  }

 /* Restore cached image gc to state correct for this instantiation */
  if (XmTextF_image_gc(tf)){
     valuemask = (GCForeground | GCBackground);
     if (XmTextF_overstrike(tf)) {
       values.background = values.foreground = 
	 tf->core.background_pixel ^ tf->primitive.foreground;
     } else if (XmTextF_have_inverted_image_gc(tf)){
       values.background = tf->primitive.foreground;
       values.foreground = tf->core.background_pixel;
     } else {
       values.foreground = tf->primitive.foreground;
       values.background = tf->core.background_pixel;
     }
     XChangeGC(XtDisplay(tf), XmTextF_image_gc(tf), valuemask, &values);
  }

  _XmDataFToggleCursorGC((Widget)tf);
}

static void 
#ifdef _NO_PROTO
df_XmSetNormGC( tf, gc, change_stipple, stipple )
        XmDataFieldWidget tf ;
        GC gc ;
	Boolean change_stipple;
	Boolean stipple;
#else
df_XmSetNormGC(
        XmDataFieldWidget tf,
        GC gc,
#if NeedWidePrototypes
	int change_stipple,
        int stipple)
#else
	Boolean change_stipple,
        Boolean stipple)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    unsigned long valueMask = (GCForeground | GCBackground);
    XGCValues values;

    if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
    values.foreground = tf->primitive.foreground;
    values.background = tf->core.background_pixel;
    if (change_stipple) {
       valueMask |= GCTile | GCFillStyle;
       values.tile = XmTextF_stipple_tile(tf);
       if (stipple) values.fill_style = FillTiled;
       else values.fill_style = FillSolid;
    }

    XChangeGC(XtDisplay(tf), gc, valueMask, &values);
}

static void 
#ifdef _NO_PROTO
df_XmSetInvGC( tf, gc )
        XmDataFieldWidget tf ;
        GC gc ;
#else
df_XmSetInvGC(
        XmDataFieldWidget tf,
        GC gc )
#endif /* _NO_PROTO */
{
    unsigned long valueMask = (GCForeground | GCBackground);
    XGCValues values;

    if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
    values.foreground = tf->core.background_pixel;
    values.background = tf->primitive.foreground;

    XChangeGC(XtDisplay(tf), gc, valueMask, &values);
}

static void
#ifdef _NO_PROTO
df_DrawText( tf, gc, x, y, string, length )
        XmDataFieldWidget tf ;
        GC gc ;
        int x ;
        int y ;
        char * string ;
        int length ;
#else
df_DrawText(
        XmDataFieldWidget tf,
        GC  gc,
        int x,
        int y,
        char * string,
        int length )
#endif /* _NO_PROTO */
{
   if (XmTextF_have_fontset(tf)){
      if (XmTextF_max_char_size(tf) != 1) 
         XwcDrawString (XtDisplay(tf), XtWindow(tf), (XFontSet)XmTextF_font(tf),
			gc, x, y, (wchar_t*) string, length);

      else  /* one byte chars */
         XmbDrawString (XtDisplay(tf), XtWindow(tf), (XFontSet)XmTextF_font(tf),
			gc, x, y, string, length);

   } else { /* have a font struct, not a font set */
      if (XmTextF_max_char_size(tf) != 1) { /* was passed a wchar_t*  */
	 char stack_cache[400], *tmp;
	 wchar_t tmp_wc;
	 wchar_t *wc_string = (wchar_t*)string;
	 int num_bytes = 0;
	 /* ptr = tmp = XtMalloc((int)(length + 1)*sizeof(wchar_t)); */
	 tmp = XmStackAlloc((Cardinal) ((length + 1)*sizeof(wchar_t)),
				    stack_cache);
	 tmp_wc = wc_string[length];
	 wc_string[length] = 0L;
	 num_bytes = wcstombs(tmp, wc_string,
			      (int)((length + 1) * sizeof(wchar_t)));
	 wc_string[length] = tmp_wc;
	 if (num_bytes >= 0)
            XDrawString (XtDisplay(tf), XtWindow(tf), gc, x, y, tmp, num_bytes);
	 XmStackFree((char *)tmp, stack_cache);
      } else /* one byte chars */
         XDrawString (XtDisplay(tf), XtWindow(tf), gc, x, y, string, length);
   }
}

static int
#ifdef _NO_PROTO
df_FindPixelLength( tf, string, length)
        XmDataFieldWidget tf ;
        char * string ;
        int length ;
#else
df_FindPixelLength(
        XmDataFieldWidget tf,
        char * string,
        int length )
#endif /* _NO_PROTO */
{
   if (XmTextF_have_fontset(tf)) {
      if (XmTextF_max_char_size(tf) != 1)
         return (XwcTextEscapement((XFontSet)XmTextF_font(tf), 
                                   (wchar_t *) string, length));
      else /* one byte chars */
         return (XmbTextEscapement((XFontSet)XmTextF_font(tf), string, length));
   } else { /* have font struct, not a font set */
      if (XmTextF_max_char_size(tf) != 1) { /* was passed a wchar_t*  */
	 wchar_t *wc_string = (wchar_t*)string;
	 wchar_t wc_tmp = wc_string[length];
	 char stack_cache[400], *tmp;
	 int num_bytes, ret_len = 0;

	 wc_string[length] = 0L;
         tmp = XmStackAlloc((Cardinal)((length + 1) * sizeof(wchar_t)),
				   stack_cache);
         num_bytes = wcstombs(tmp, wc_string, 
			      (int)((length + 1)*sizeof(wchar_t)));
	 wc_string[length] = wc_tmp;
	 if (num_bytes >= 0)
            ret_len = XTextWidth(XmTextF_font(tf), tmp, num_bytes);
         XmStackFree((char *)tmp, stack_cache);
	 return (ret_len);
      } else /* one byte chars */
         return (XTextWidth(XmTextF_font(tf), string, length));
   }
}

static void
#ifdef _NO_PROTO
df_DrawTextSegment( tf, mode, prev_seg_start, seg_start, seg_end, next_seg,
		 stipple, y, x)
        XmDataFieldWidget tf ;
        XmHighlightMode mode;
	XmTextPosition prev_seg_start;
	XmTextPosition seg_start;
	XmTextPosition seg_end;
	XmTextPosition next_seg;
	Boolean stipple;
        int y ;
        int *x ;
#else
df_DrawTextSegment(
        XmDataFieldWidget tf,
        XmHighlightMode mode,
	XmTextPosition prev_seg_start,
	XmTextPosition seg_start,
	XmTextPosition seg_end,
	XmTextPosition next_seg,
#if NeedWidePrototypes
        int stipple,
#else
        Boolean stipple,
#endif /* NeedWidePrototypes */
        int y,
        int *x)
#endif /* _NO_PROTO */
{
    int x_seg_len;

#if PWC_DEBUG
    {
	char seg[256];

	memset((char *)seg, 256, 0);
	strncpy(seg, (char *)(XmTextF_value(tf) + seg_start),
		seg_end - seg_start);

	seg[seg_end] = '\0';

	printf("df_DrawText(\"%s\" - %s) :: [start(%d), end(%d), x(%d), offset(%d)]\n",
	       seg, (mode == XmHIGHLIGHT_NORMAL ? "NORMAL" : "HIGHLIGHT"),
	       seg_start, seg_end, *x, XmTextF_h_offset(tf));
    }
#endif

    /* update x position up to start position */
    if (XmTextF_max_char_size(tf) != 1) {
       *x += df_FindPixelLength(tf, (char*)(XmTextF_wc_value(tf) + prev_seg_start),
                                 (int)(seg_start - prev_seg_start));
       x_seg_len = df_FindPixelLength(tf, (char*)(XmTextF_wc_value(tf) + seg_start),
                                           (int)seg_end - (int)seg_start);
    } else {
       *x += df_FindPixelLength(tf, XmTextF_value(tf) + prev_seg_start,
                                 (int)(seg_start - prev_seg_start));
       x_seg_len = df_FindPixelLength(tf, XmTextF_value(tf) + seg_start,
                                           (int)seg_end - (int)seg_start);
    }
    if (mode == XmHIGHLIGHT_SELECTED) {
      /* Draw the selected text using an inverse gc */
       df_XmSetNormGC(tf, XmTextF_gc(tf), False, False);
       XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf), *x, 
		      y - XmTextF_font_ascent(tf), x_seg_len,
		      XmTextF_font_ascent(tf) + XmTextF_font_descent(tf));
       df_XmSetInvGC(tf, XmTextF_gc(tf));
    } else {
       df_XmSetInvGC(tf, XmTextF_gc(tf));
       XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf), *x, 
		      y - XmTextF_font_ascent(tf), x_seg_len,
		      XmTextF_font_ascent(tf) + XmTextF_font_descent(tf));
       df_XmSetNormGC(tf, XmTextF_gc(tf), True, stipple);
    }

    if (XmTextF_max_char_size(tf) != 1) {
       df_DrawText(tf, XmTextF_gc(tf), *x, y, (char*) (XmTextF_wc_value(tf) + seg_start),
                                           (int)seg_end - (int)seg_start);
    } else {
       df_DrawText(tf, XmTextF_gc(tf), *x, y, XmTextF_value(tf) + seg_start,
                                           (int)seg_end - (int)seg_start);
    }
    if (stipple) df_XmSetNormGC(tf, XmTextF_gc(tf), True, !stipple);
   
    if (mode == XmHIGHLIGHT_SECONDARY_SELECTED)
       XDrawLine(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf), *x, y,
                              *x + x_seg_len - 1, y);

   /* update x position up to the next highlight position */
    if (XmTextF_max_char_size(tf) != 1)
       *x += df_FindPixelLength(tf, (char*) (XmTextF_wc_value(tf) + seg_start),
				    (int)(next_seg - (int)seg_start));
    else
       *x += df_FindPixelLength(tf, XmTextF_value(tf) + seg_start,
				    (int)(next_seg - (int)seg_start));
}


/*
 * Redisplay the new adjustments that have been made the the text
 * field widget.
 */
static void 
#ifdef _NO_PROTO
df_RedisplayText( tf, start, end )
        XmDataFieldWidget tf ;
        XmTextPosition start ;
        XmTextPosition end ;
#else
df_RedisplayText(
        XmDataFieldWidget tf,
        XmTextPosition start,
        XmTextPosition end )
#endif /* _NO_PROTO */
{
  _XmHighlightRec *l = XmTextF_highlight(tf).list;
  XRectangle rect;
  int x, y, i;
  Dimension margin_width = XmTextF_margin_width(tf) +
	                   tf->primitive.shadow_thickness +
			   tf->primitive.highlight_thickness;
  Dimension margin_top = XmTextF_margin_top(tf) + tf->primitive.shadow_thickness +
			 tf->primitive.highlight_thickness;
  Dimension margin_bottom = XmTextF_margin_bottom(tf) +
	                    tf->primitive.shadow_thickness +
			    tf->primitive.highlight_thickness;
  Boolean stipple = False;

  if (!XtIsRealized((Widget)tf)) return;

  if (XmTextF_in_setvalues(tf)) {
     XmTextF_redisplay(tf) = True;
     return;
  }

  if ((int)tf->core.width - (int)(2 * margin_width) <= 0)
    return;
  if ((int)tf->core.height - (int)(margin_top + margin_bottom) <= 0)
    return;

 /*
  * Make sure the cached GC has the clipping rectangle
  * set to the current widget.
  */
  if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

  _XmDataFieldDrawInsertionPoint(tf, False);

 /* Get the current rectangle.
  */
  df_GetRect(tf, &rect);

  y = margin_top + XmTextF_font_ascent(tf);
  
  if (XmDataField_alignment(tf) == XmALIGNMENT_END)
  {
      x = tf->core.width - margin_width + XmTextF_h_offset(tf);

      if (XmTextF_max_char_size(tf) != 1)
	  x -= df_FindPixelLength(tf, (char*)(XmTextF_wc_value(tf) + l[0].position),
			       XmTextF_string_length(tf) - l[0].position);
      else 
	  x -= df_FindPixelLength(tf, XmTextF_value(tf) + l[0].position,
			       XmTextF_string_length(tf) - l[0].position);

      /* PWC - alignment requires we draw all characters to the left of end */
      start = 0;
  }
  else
      x = (int) XmTextF_h_offset(tf);

  if (!XtIsSensitive((Widget)tf)) stipple = True;

  /* search through the highlight array and draw the text */
  for (i = 0; i + 1 < XmTextF_highlight(tf).number; i++) {
#if PWC_DEBUG
      printf("XmTextF_value(\"%s\")::Highlight #%d = pos(%d), start(%d), end(%d)\n",
	     (char *)XmTextF_value(tf), i, l[i].position, start, end);
#endif
     /* make sure start is within current highlight */
      if (l[i].position <= start && start < l[i+1].position &&
          l[i].position < end) {

         if (end > l[i+1].position) {
	    
	    df_DrawTextSegment(tf, l[i].mode, l[i].position, start,
			    l[i+1].position, l[i+1].position, stipple, y, &x);

           /* update start position to the next highlight position */
            start = l[i+1].position;

         } else {

	    df_DrawTextSegment(tf, l[i].mode, l[i].position, start,
			    end, l[i+1].position, stipple, y, &x);
            start = end;
         }
      }
      else
      { /* start not within current record */
	  if (XmTextF_max_char_size(tf) != 1)
	  {
	      x += df_FindPixelLength(tf, (char *) (XmTextF_wc_value(tf)
						 + l[i].position),
				   (int)(l[i+1].position - l[i].position));
	  }
	  else
	  {
	      x += df_FindPixelLength(tf, XmTextF_value(tf) + l[i].position,
				   (int)(l[i+1].position - l[i].position));
	  }
     }
  }  /* end for loop */

  if (l[i].position < end)
  {
      /* complete the drawing of the text to the end of the line */
      df_DrawTextSegment(tf, l[i].mode, l[i].position, start, end,
		      XmTextF_string_length(tf), stipple, y, &x);
  } else {
      if (XmTextF_max_char_size(tf) != 1)
	 x += df_FindPixelLength(tf, (char*) (XmTextF_wc_value(tf) + l[i].position),
			      XmTextF_string_length(tf) - (int)l[i].position);
     else 
	 x += df_FindPixelLength(tf, XmTextF_value(tf) + l[i].position,
			      XmTextF_string_length(tf) - (int)l[i].position);
  }

  if (x < (int)(rect.x + rect.width)) {
     df_XmSetInvGC(tf, XmTextF_gc(tf));
     XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf), x, rect.y,
                    rect.x + rect.width - x, rect.height);
  }

  XmTextF_refresh_ibeam_off(tf) = True;
  _XmDataFieldDrawInsertionPoint(tf, True);
}


/*
 * Use the font along with the resources that have been set
 * to determine the height and width of the text field widget.
 */
static void 
#ifdef _NO_PROTO
df_ComputeSize( tf, width, height )
        XmDataFieldWidget tf ;
        Dimension *width ;
        Dimension *height ;
#else
df_ComputeSize(
        XmDataFieldWidget tf,
        Dimension *width,
        Dimension *height )
#endif /* _NO_PROTO */
{
    Dimension tmp = 0;

    if (XmTextF_resize_width(tf) &&
	XmTextF_columns(tf) < XmTextF_string_length(tf)){

       if (XmTextF_max_char_size(tf) != 1) 
          tmp = df_FindPixelLength(tf, (char *)XmTextF_wc_value(tf),
	                        XmTextF_string_length(tf));
       else
          tmp = df_FindPixelLength(tf, XmTextF_value(tf), XmTextF_string_length(tf));

       
       *width = tmp + (2 * (XmTextF_margin_width(tf) + 
			    tf->primitive.shadow_thickness + 
			    tf->primitive.highlight_thickness));
    } else {
	*width = XmTextF_columns(tf) * XmTextF_average_char_width(tf) +
	    2 * (XmTextF_margin_width(tf) + tf->primitive.shadow_thickness +
		 tf->primitive.highlight_thickness);
    }

    if (height != NULL)
	*height = XmTextF_font_descent(tf) + XmTextF_font_ascent(tf) +
	    2 * (XmTextF_margin_height(tf) + tf->primitive.shadow_thickness +
		 tf->primitive.highlight_thickness);
}


/*
 * df_TryResize - Attempts to resize the width of the text field widget.
 * If the attempt fails or is ineffective, return GeometryNo.
 */
static XtGeometryResult 
#ifdef _NO_PROTO
df_TryResize( tf, width, height )
        XmDataFieldWidget tf ;
        Dimension width ;
        Dimension height ;
#else
df_TryResize(
        XmDataFieldWidget tf,
#if NeedWidePrototypes
        int width,
        int height )
#else
        Dimension width,
        Dimension height )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    Dimension reswidth, resheight;
    Dimension origwidth = tf->core.width;
    XtGeometryResult result;

    result = XtMakeResizeRequest((Widget)tf, width, height,
                                 &reswidth, &resheight);

    if (result == XtGeometryAlmost) {
        result = XtMakeResizeRequest((Widget)tf, reswidth, resheight,
				     &reswidth, &resheight);

        if (reswidth == origwidth)
           result = XtGeometryNo;
        return result;
    }

   /*
    * Caution: Some geometry managers return XtGeometryYes
    *	        and don't change the widget's size.
    */
    if (tf->core.width != width && tf->core.height != height)
        result = XtGeometryNo;

    return result;
}


/*
 * Function df_AdjustText
 *
 * df_AdjustText ensures that the character at the given position is entirely
 * visible in the Text Field widget.  If the character is not already entirely
 * visible, df_AdjustText changes the Widget's h_offsetring appropriately.  If
 * the text must be redrawn, df_AdjustText calls df_RedisplayText.
 *
 */
static Boolean 
#ifdef _NO_PROTO
df_AdjustText( tf, position, flag )
        XmDataFieldWidget tf ;
        XmTextPosition position ;
        Boolean flag ;
#else
df_AdjustText(
        XmDataFieldWidget tf,
        XmTextPosition position,
#if NeedWidePrototypes
        int flag )
#else
        Boolean flag )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
  int left_edge = 0;
  int diff;
  Dimension margin_width = XmTextF_margin_width(tf) +
			      tf->primitive.shadow_thickness +
                              tf->primitive.highlight_thickness;
  Dimension thickness    = 2 * (tf->primitive.shadow_thickness +
                              tf->primitive.highlight_thickness);
  Dimension temp;
  
  if (XmDataField_alignment(tf) == XmALIGNMENT_END)
  {
    if (XmTextF_max_char_size(tf) != 1)
    {
      left_edge = tf->core.width - margin_width + XmTextF_h_offset(tf) -
                  df_FindPixelLength(tf, (char *)(XmTextF_wc_value(tf) + position),
                                  XmTextF_string_length(tf) - (int) position);
    } 
    else
    {
      left_edge = tf->core.width - margin_width + XmTextF_h_offset(tf) -
                  df_FindPixelLength(tf, XmTextF_value(tf) + position,
                                  XmTextF_string_length(tf) - (int) position);
    }
  }
  else
  {
    if (XmTextF_max_char_size(tf) != 1)
    {
      left_edge = df_FindPixelLength(tf, (char *) XmTextF_wc_value(tf),
                                  (int)position) + (int) XmTextF_h_offset(tf);
    } 
    else
    {
      left_edge = df_FindPixelLength(tf, XmTextF_value(tf), (int)position) +
		                  (int) XmTextF_h_offset(tf);
    }
  }

 /*
  * Make sure the cached GC has the clipping rectangle
  * set to the current widget.
  */
  if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

  if ((diff = left_edge - margin_width) < 0) {
    /* We need to scroll the string to the right. */
     if (!XtIsRealized((Widget)tf)) {
       XmTextF_h_offset(tf) -= diff;
       return True;
     }
     _XmDataFieldDrawInsertionPoint(tf, False);
     XmTextF_h_offset(tf) -= diff;
     df_XmSetInvGC(tf, XmTextF_gc(tf));
     df_XmSetFullGC(tf, XmTextF_gc(tf));
     if (tf->core.height <= thickness)
       temp = 0;
     else
       temp = tf->core.height - thickness;
     XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf),
		    tf->primitive.shadow_thickness +
                    tf->primitive.highlight_thickness,
		    tf->primitive.shadow_thickness +
                    tf->primitive.highlight_thickness,
                    XmTextF_margin_width(tf),
                    temp);
     df_XmSetMarginGC(tf, XmTextF_gc(tf));
     df_RedisplayText(tf, 0, XmTextF_string_length(tf)); 
     _XmDataFieldDrawInsertionPoint(tf, True);
     return True;
   } else if ((diff = ( left_edge -
		       (int)(tf->core.width - margin_width))) > 0) {
           /* We need to scroll the string to the left. */
            if (!XtIsRealized((Widget)tf)) {
              XmTextF_h_offset(tf) -= diff;
              return True;
            }
            _XmDataFieldDrawInsertionPoint(tf, False);
            XmTextF_h_offset(tf) -= diff;
            df_XmSetInvGC(tf, XmTextF_gc(tf));
            df_XmSetFullGC(tf, XmTextF_gc(tf));
	    if (tf->core.width <= thickness)
	      temp = 0;
	    else
	      temp = tf->core.width - thickness;
            XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf),
                           tf->core.width - margin_width,
		           tf->primitive.shadow_thickness +
                           tf->primitive.highlight_thickness,
                           XmTextF_margin_width(tf),
			   temp);
             df_XmSetMarginGC(tf, XmTextF_gc(tf));
             df_RedisplayText(tf, 0, XmTextF_string_length(tf)); 
             _XmDataFieldDrawInsertionPoint(tf, True);
             return True;
  }

  if (flag) df_RedisplayText(tf, position, XmTextF_string_length(tf)); 

  return False;
}

/*
 * df_AdjustSize
 *
 * Adjust size will resize the text to ensure that all the text is visible.
 * It will also adjust text that is shrunk.  Shrinkage is limited to the
 * size determined by the XmNcolumns resource.
 */
static void 
#ifdef _NO_PROTO
df_AdjustSize( tf )
        XmDataFieldWidget tf ;
#else
df_AdjustSize(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
  XtGeometryResult result = XtGeometryYes;
  int left_edge = 0;
  int diff;
  Boolean redisplay = False;
  Dimension margin_width = XmTextF_margin_width(tf) +
			      tf->primitive.shadow_thickness +
                              tf->primitive.highlight_thickness;

  if (XmTextF_max_char_size(tf) != 1) {
      left_edge = df_FindPixelLength(tf, (char *) XmTextF_wc_value(tf), 
				  XmTextF_string_length(tf)) + margin_width;
  } else {
      left_edge = df_FindPixelLength(tf, XmTextF_value(tf), 
				  XmTextF_string_length(tf)) + margin_width;
  }

  if ((diff = (left_edge - (tf->core.width - (margin_width)))) > 0) {
     if (XmTextF_in_setvalues(tf)) {
	tf->core.width += diff;
	if (XmDataField_alignment(tf) == XmALIGNMENT_END)
	    XmTextF_new_h_offset(tf) = diff;
	else
	    XmTextF_new_h_offset(tf) = margin_width - diff;
	return;
     }
    /* Attempt to resize.  If it doesn't succeed, do scrolling.  */
     result = df_TryResize(tf, tf->core.width + diff, tf->core.height);
     if (result == XtGeometryYes) {
        XtWidgetProc resize;
           
        _XmProcessLock(); 
        resize = tf->core.widget_class->core_class.resize;
        _XmProcessUnlock();

        (*resize)((Widget)tf);
        return;
     } else
	 /* We need to scroll the string to the left. */
	 if (XmDataField_alignment(tf) == XmALIGNMENT_END)
	     XmTextF_h_offset(tf) = diff;	     
	 else
	     XmTextF_h_offset(tf) = margin_width - diff;
  } else {
     Dimension width;

    /* If the new size is smaller than core size, we need
     * to shrink.  Note: new size will never be less than the
     * width determined by the columns resource.
     */
     df_ComputeSize(tf, &width, NULL);
     if (width < tf->core.width) {
        if (XmTextF_in_setvalues(tf)) {
	   tf->core.width = width;
	   return;
        }
        result = df_TryResize(tf, width, tf->core.height);
        if (result == XtGeometryYes) {
           XtWidgetProc resize;
           
           _XmProcessLock(); 
           resize = tf->core.widget_class->core_class.resize;
           _XmProcessUnlock();

           (*resize)((Widget)tf);
           return;
        }
     }
  }

  redisplay = df_AdjustText(tf, XmTextF_cursor_position(tf), False);

  if (!redisplay)
     df_RedisplayText(tf, 0, XmTextF_string_length(tf));
}

/* If MB_CUR_MAX == 1, insert is a char* pointer; else, it is a wchar_t *
 * pointer and must be appropriately cast.  In all cases, insert_length
 * is the number of characters, not the number of bytes pointed to by
 * insert
 */
static Boolean 
#ifdef _NO_PROTO
df_ModifyVerify( tf, event, replace_prev, replace_next,
	      insert, insert_length, newInsert, free_insert )
        XmDataFieldWidget tf ;
        XEvent *event ;
        XmTextPosition *replace_prev ;
        XmTextPosition *replace_next ;
        char **insert ;
        int *insert_length ;
        XmTextPosition *newInsert ;
        int *free_insert ;
#else
df_ModifyVerify(
        XmDataFieldWidget tf,
        XEvent *event,
        XmTextPosition *replace_prev,
        XmTextPosition *replace_next,
        char **insert,
        int *insert_length,
        XmTextPosition *newInsert,
	int *free_insert )
#endif /* _NO_PROTO */
{
     XmTextVerifyCallbackStruct vcb;
     XmTextVerifyCallbackStructWcs wcs_vcb;
     XmTextBlockRec newblock;
     XmTextBlockRecWcs wcs_newblock;
     Boolean do_free = False;
     Boolean wcs_do_free = False;
     int count;
     wchar_t *wptr;
     
     *newInsert = XmTextF_cursor_position(tf);
     *free_insert = (int)False;

    /* if there are no callbacks, don't waste any time... just return  True */
     if (!XmTextF_modify_verify_callback(tf) && !XmTextF_wcs_modify_verify_callback(tf))
	return(True);

     newblock.format = XmFMT_8_BIT;
     newblock.length = *insert_length * XmTextF_max_char_size(tf);

     if (*insert_length) {
	 if (XmTextF_modify_verify_callback(tf)){
            newblock.ptr = (char *) XtMalloc((unsigned) newblock.length + 
					     XmTextF_max_char_size(tf));
	    if (XmTextF_max_char_size(tf) == 1) {
              (void)memcpy((void*)newblock.ptr, (void*)*insert,
			   newblock.length);
	      newblock.ptr[newblock.length]='\0';
	    } else {
	       count = (int) wcstombs(newblock.ptr, (wchar_t*)*insert,
				                newblock.length);
	       if (count < 0) { /* bad wchar; don't pass anything */
		  newblock.ptr[0] = '\0';
		  newblock.length = 0;
	       } else if (count == newblock.length) {
		  newblock.ptr[newblock.length] = '\0';
	       } else {
		  newblock.ptr[count] = '\0';
		  newblock.length = count;
	       }
	    }
            do_free = True;
	 } else 
            newblock.ptr = NULL;
     } else 
	newblock.ptr = NULL;
	
    /* Fill in the appropriate structs */
     vcb.reason = XmCR_MODIFYING_TEXT_VALUE;
     vcb.event = (XEvent *) event;
     vcb.doit = True;
     vcb.currInsert = XmTextF_cursor_position(tf);
     vcb.newInsert = XmTextF_cursor_position(tf);
     vcb.text = &newblock;
     vcb.startPos = *replace_prev;
     vcb.endPos = *replace_next;

     /* Call the modify verify callbacks. */
     if (XmTextF_modify_verify_callback(tf))
        XtCallCallbackList((Widget) tf, XmTextF_modify_verify_callback(tf),
			   (XtPointer) &vcb);

     if (XmTextF_wcs_modify_verify_callback(tf) && vcb.doit){
	if (do_free){ /* there is a char* modify verify callback; the data we
		       * want is in vcb struct */
	   wcs_newblock.wcsptr = (wchar_t *) XtMalloc((unsigned) 
				      (vcb.text->length + 1) * sizeof(wchar_t));
	   wcs_newblock.length = mbstowcs(wcs_newblock.wcsptr, vcb.text->ptr,
				          vcb.text->length);
	   if (wcs_newblock.length < 0) { /* bad value; don't pass anything */
	      wcs_newblock.wcsptr[0] = 0L;
	      wcs_newblock.length = 0;
           } else 
	      wcs_newblock.wcsptr[wcs_newblock.length] = 0L;
	} else { /* there was no char* modify verify callback; use data
		  * passed in from caller instead of that in vcb struct. */
	  wcs_newblock.wcsptr = (wchar_t *) XtMalloc((unsigned) 
				       (*insert_length + 1) * sizeof(wchar_t));
	  if (XmTextF_max_char_size(tf) == 1) 
	    wcs_newblock.length = mbstowcs(wcs_newblock.wcsptr, *insert,
				          *insert_length);
	  else {
	    wcs_newblock.length = *insert_length;
	    (void)memcpy((void*)wcs_newblock.wcsptr, (void*)*insert,
			 *insert_length * sizeof(wchar_t));
	  }	    
	  if (wcs_newblock.length < 0) { /* bad value; don't pass anything */
	    wcs_newblock.wcsptr[0] = 0L;
	    wcs_newblock.length = 0;
	  } else 
	    wcs_newblock.wcsptr[wcs_newblock.length] = 0L;

	}
	wcs_do_free = True;
	wcs_vcb.reason = XmCR_MODIFYING_TEXT_VALUE;
	wcs_vcb.event = (XEvent *) event;
	wcs_vcb.doit = True;
	wcs_vcb.currInsert = vcb.currInsert;
	wcs_vcb.newInsert = vcb.newInsert;
	wcs_vcb.text = &wcs_newblock;
	wcs_vcb.startPos = vcb.startPos;
	wcs_vcb.endPos = vcb.endPos;

        XtCallCallbackList((Widget) tf, XmTextF_wcs_modify_verify_callback(tf),
			   (XtPointer) &wcs_vcb);

     }
     
     /* 
      * copy the newblock.ptr, length, start, and 
      * end to the pointers passed
      */

     if (XmTextF_wcs_modify_verify_callback(tf)) 
     { /* use wcs_vcb data */
	 *insert_length = wcs_vcb.text->length; /* length is char count*/
	 if (wcs_vcb.doit) 
	 {
	     if (XmTextF_max_char_size(tf) == 1)
	     { /* caller expects char */
		 wcs_vcb.text->wcsptr[wcs_vcb.text->length] = 0L;
		 if (*insert_length > 0) 
		 {
		     *insert = XtMalloc((unsigned) (*insert_length + 1) \
					* sizeof(wchar_t));
		     *free_insert = (int)True;
		     count = wcstombs(*insert, wcs_vcb.text->wcsptr,
				      *insert_length + 1);
		     if (count < 0) 
		     {
			 (*insert)[0] = 0;
			 *insert_length = 0;
		     }
		 }        
	     } 
	     else 
	     {  /* callback struct has wchar*; caller expects wchar* */
		 if (*insert_length > 0) 
		 {
		     *insert = XtMalloc((unsigned)(*insert_length + 1) \
					* sizeof(wchar_t));
		     *free_insert = (int)True;
		     (void)memcpy((void*)*insert, (void*)wcs_vcb.text->wcsptr,
				  *insert_length * sizeof(wchar_t));
		     wptr = (wchar_t*) *insert;
		     wptr[*insert_length] = 0L;
		 }	
	     }	

	     *replace_prev = wcs_vcb.startPos;
	     *replace_next = wcs_vcb.endPos;
	     *newInsert = wcs_vcb.newInsert;
	 }
     } 
     else 
     { /* use vcb data */
	 if (vcb.doit) 
	 {
	     if (XmTextF_max_char_size(tf) == 1)
	     {  /* caller expects char* */
		 *insert_length =  vcb.text->length;
		 if (*insert_length > 0) 
		 {
		     *insert = XtMalloc((unsigned) *insert_length + 1);
		     *free_insert = (int)True;
		     (void)memcpy((void*)*insert, (void*)vcb.text->ptr,
				  *insert_length);
		     (*insert)[*insert_length] = 0;
		 }
	     } 
	     else 
	     {	/* caller expects wchar_t* back */
		 *insert_length =  
		     _XmDataFieldCountCharacters(tf, vcb.text->ptr,
						 vcb.text->length);
		 if (*insert_length > 0) 
		 {
		     *insert = 
			 XtMalloc((unsigned)(*insert_length + 1) * 
				  sizeof(wchar_t));
		     *free_insert = (int)True;
		     count = mbstowcs((wchar_t*)*insert, vcb.text->ptr,
				      *insert_length);
		     wptr = (wchar_t*) *insert;
		     if (count < 0) {
			 wptr[0] = 0L;
			 *insert_length = 0;
		     } 
		     else
		     {
			 wptr[count] = 0L;
		     }
		 }	
	     }
	     *replace_prev = vcb.startPos;
	     *replace_next = vcb.endPos;
	     *newInsert = vcb.newInsert;
	 }
     }

     if (do_free) {
	 XtFree(newblock.ptr);
     }
     if (wcs_do_free) {
	 XtFree((char*)wcs_newblock.wcsptr);
     }
        
     /* If doit becomes False, then don't allow the change. */
     if (XmTextF_wcs_modify_verify_callback(tf))
        return wcs_vcb.doit;
     else
        return vcb.doit;
}

static void 
#ifdef _NO_PROTO
df_ResetClipOrigin(tf, clip_mask_reset)
	XmDataFieldWidget tf;
	Boolean clip_mask_reset;
#else /* _NO_PROTO */
df_ResetClipOrigin(
	XmDataFieldWidget tf, 
#if NeedWidePrototypes
        int clip_mask_reset)
#else
        Boolean clip_mask_reset)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
   unsigned long valuemask = (GCTileStipXOrigin | GCTileStipYOrigin |
			     GCClipXOrigin | GCClipYOrigin);
   XGCValues values;
   int x, y, clip_mask_x, clip_mask_y;
   Position x_pos, y_pos;
   (void) df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &x_pos, &y_pos);

   if (!XtIsRealized((Widget)tf)) return;

   if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
   x = (int) x_pos; y = (int) y_pos;

   x -=(XmTextF_cursor_width(tf) >> 1) + 1;

   clip_mask_y = y = (y + XmTextF_font_descent(tf)) - XmTextF_cursor_height(tf);

   if (x < (int)(tf->primitive.highlight_thickness + 
       tf->primitive.shadow_thickness + XmTextF_margin_width(tf))){
	  clip_mask_x = tf->primitive.highlight_thickness +
          tf->primitive.shadow_thickness + (int)(XmTextF_margin_width(tf));
   } else
     clip_mask_x = x; 

   if (clip_mask_reset) {
      values.ts_x_origin = x;
      values.ts_y_origin = y;
      values.clip_x_origin = clip_mask_x;
      values.clip_y_origin = clip_mask_y;
      XChangeGC(XtDisplay(tf), XmTextF_image_gc(tf), valuemask, &values);
   }
   else 
      XSetTSOrigin(XtDisplay(tf), XmTextF_image_gc(tf), x, y);
}

static void
#ifdef _NO_PROTO
df_InvertImageGC (tf)
	XmDataFieldWidget tf ;
#else
df_InvertImageGC (
	XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
   unsigned long valuemask = (GCForeground | GCBackground);
   XGCValues values;
   Display *dpy = XtDisplay(tf);

   if (XmTextF_have_inverted_image_gc(tf)) return;

   if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

   if (!XmTextF_overstrike(tf)) {
     values.background = tf->primitive.foreground;
     values.foreground = tf->core.background_pixel;
     
     XChangeGC(dpy, XmTextF_image_gc(tf), valuemask, &values);
   }

   XmTextF_have_inverted_image_gc(tf) = True;
}

static void
#ifdef _NO_PROTO
df_ResetImageGC (tf)
        XmDataFieldWidget tf ;
#else
df_ResetImageGC (
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
   unsigned long valuemask = (GCForeground | GCBackground);
   XGCValues values;
   Display *dpy = XtDisplay(tf);

   if (!XmTextF_have_inverted_image_gc(tf)) return;

   if (!XmTextF_has_rect(tf)) 
   {
       _XmDataFieldSetClipRect(tf);
   }

   if (!XmTextF_overstrike(tf)) 
   {
       values.foreground = tf->primitive.foreground;
       values.background = tf->core.background_pixel;
     
       XChangeGC(dpy, XmTextF_image_gc(tf), valuemask, &values);
   }

   XmTextF_have_inverted_image_gc(tf) = False;
}

/*
 * Calls the motion verify callback.  If the doit flag is true,
 * then reset the cursor_position and call df_AdjustText() to
 * move the text if need be.
 */

void 
#ifdef _NO_PROTO
_XmDataFielddf_SetCursorPosition( tf, event, position,
			      adjust_flag, call_cb)
        XmDataFieldWidget tf ;
        XEvent *event ;
        XmTextPosition position ;
        Boolean adjust_flag ;
        Boolean call_cb ;
#else
_XmDataFielddf_SetCursorPosition(
        XmDataFieldWidget tf,
        XEvent *event,
        XmTextPosition position,
#if NeedWidePrototypes
        int adjust_flag,
        int call_cb)
#else
        Boolean adjust_flag,
        Boolean call_cb)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
  df_SetCursorPosition(tf, event, position, adjust_flag, call_cb, True);
}

static void 
#ifdef _NO_PROTO
df_SetCursorPosition( tf, event, position,
		  adjust_flag, call_cb, set_dest)
        XmDataFieldWidget tf ;
        XEvent *event ;
        XmTextPosition position ;
        Boolean adjust_flag ;
        Boolean call_cb ;
        Boolean set_dest;
#else
df_SetCursorPosition(
        XmDataFieldWidget tf,
        XEvent *event,
        XmTextPosition position,
#if NeedWidePrototypes
        int adjust_flag,
        int call_cb, 
	int set_dest)
#else
        Boolean adjust_flag,
        Boolean call_cb,
        Boolean set_dest)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    XmTextVerifyCallbackStruct cb;
    Boolean flag = False;
    XPoint xmim_point;
    _XmHighlightRec *hl_list = XmTextF_highlight(tf).list;
    int i;

    if (position < 0) position = 0;

    if (position > XmTextF_string_length(tf))
       position = XmTextF_string_length(tf);

    if (XmTextF_cursor_position(tf) != position && call_cb) {
      /* Call Motion Verify Callback before Cursor Changes Positon */
       cb.reason = XmCR_MOVING_INSERT_CURSOR;
       cb.event  = event;
       cb.currInsert = XmTextF_cursor_position(tf);
       cb.newInsert = position;
       cb.doit = True;
       XtCallCallbackList((Widget) tf, XmTextF_motion_verify_callback(tf),
			  (XtPointer) &cb);

       if (!cb.doit) {
          if (XmTextF_verify_bell(tf)) XBell(XtDisplay((Widget)tf), 0);
	  return;
       }
    }
    _XmDataFieldDrawInsertionPoint(tf, False);

    XmTextF_cursor_position(tf) = position;

    if (!XmTextF_add_mode(tf) && XmTextF_pending_off(tf) && XmTextF_has_primary(tf)) {
       df_SetSelection(tf, position, position, True);
       flag = True;
    }

   /* Deterimine if we need an inverted image GC or not.  Get the highlight
    * record for the cursor position.  If position is on a boundary of
    * a highlight, then we always display cursor in normal mode (i.e. set
    * normal image GC).  If position is within a selected highlight rec,
    * then make sure the image GC is inverted.  If we've moved out of a
    * selected highlight region, restore the normal image GC. */

    for (i = XmTextF_highlight(tf).number - 1; i >= 0; i--){
       if (position >= hl_list[i].position || i == 0)
	  break;
    }

    if (position == hl_list[i].position)
       df_ResetImageGC(tf);
    else if (hl_list[i].mode != XmHIGHLIGHT_SELECTED)
       df_ResetImageGC(tf);
    else 
       df_InvertImageGC(tf);

    if (adjust_flag) (void) df_AdjustText(tf, position, flag);

    df_ResetClipOrigin(tf, False);

    XmTextF_refresh_ibeam_off(tf) = True;
    _XmDataFieldDrawInsertionPoint(tf, True);

    (void) df_GetXYFromPos(tf, XmTextF_cursor_position(tf),
			&xmim_point.x, &xmim_point.y);
    XmImVaSetValues((Widget)tf, XmNspotLocation, &xmim_point, NULL);

    if (set_dest)
      (void) df_SetDestination((Widget) tf, XmTextF_cursor_position(tf), False, 
			    XtLastTimestampProcessed(XtDisplay((Widget)tf)));
}


/*
 * This routine is used to verify that the positions are within the bounds
 * of the current DataField widgets value.  Also, it ensures that left is
 * less than right.
 */
static void 
#ifdef _NO_PROTO
df_VerifyBounds( tf, from, to )
        XmDataFieldWidget tf ;
        XmTextPosition *from ;
        XmTextPosition *to ;
#else
df_VerifyBounds(
        XmDataFieldWidget tf,
        XmTextPosition *from,
        XmTextPosition *to )
#endif /* _NO_PROTO */
{
  XmTextPosition tmp;

    if (*from < 0) 
       *from = 0;
    else if (*from > XmTextF_string_length(tf)) {
       *from = XmTextF_string_length(tf);
    }
    if (*to < 0 ) 
       *to = 0;
    else if (*to > XmTextF_string_length(tf)) {
       *to = XmTextF_string_length(tf);
    }
    if (*from > *to) {
       tmp = *to;
       *to = *from;
       *from = tmp;
    }
}

/*
 * Function _XmDataFieldReplaceText
 *
 * _XmDataFieldReplaceText is a utility function for the text-modifying
 * action procedures below (df_InsertChar, df_DeletePrevChar, and so on). 
 * _XmDataFieldReplaceText does the real work of editing the string,
 * including:
 *
 *   (1) invoking the modify verify callbacks,
 *   (2) allocating more memory for the string if necessary,
 *   (3) doing the string manipulation,
 *   (4) moving the selection (the insertion point), and
 *   (5) redrawing the text.
 *
 * Though the procedure claims to take a char* argument, MB_CUR_MAX determines
 * what the different routines will actually pass to it.  If MB_CUR_MAX is
 * greater than 1, then "insert" points to wchar_t data and we must set up
 * the appropriate cast.  In all cases, insert_length is the number of
 * characters (not bytes) to be inserted.
 */
Boolean 
#ifdef _NO_PROTO
_XmDataFieldReplaceText( tf, event, replace_prev, replace_next,
		         insert, insert_length, move_cursor )
        XmDataFieldWidget tf ;
        XEvent *event ;
        XmTextPosition replace_prev ;
        XmTextPosition replace_next ;
        char *insert ;
        int insert_length ;
	Boolean move_cursor ;
#else
_XmDataFieldReplaceText(
        XmDataFieldWidget tf,
        XEvent *event,
        XmTextPosition replace_prev,
        XmTextPosition replace_next,
        char *insert,
        int insert_length,
	Boolean move_cursor )
#endif /* _NO_PROTO */
{
  int replace_length, i;
  char *src, *dst;
  wchar_t *wc_src, *wc_dst;
  int delta = 0;
  XmTextPosition cursorPos, newInsert;
  XmTextPosition old_pos = replace_prev;
  int free_insert = (int)False;
  Position	x1, y1, x2, y2;

  df_VerifyBounds(tf, &replace_prev, &replace_next);

  if (!XmTextF_editable(tf)) {
     if (XmTextF_verify_bell(tf)) XBell(XtDisplay((Widget)tf), 0);
     return False;
  }

  replace_length = (int) (replace_next - replace_prev);
  delta = insert_length - replace_length;

 /* Disallow insertions that go beyond max length boundries.
  */
  if ((delta >= 0) && 
      ((XmTextF_string_length(tf) + delta) - (XmTextF_max_length(tf)) > 0)) { 
      if (XmTextF_verify_bell(tf)) 
      {
	  XBell(XtDisplay(tf), 0);
      }
      return False;
  }	

  if (XmDataField_alignment(tf) == XmALIGNMENT_END)
  {
      df_GetXYFromPos(tf, 0, &x1, &y1);
  }

 /* If there are modify verify callbacks, verify that we want to continue
  * the action.
  */
  newInsert = XmTextF_cursor_position(tf);

  if (XmTextF_modify_verify_callback(tf) || XmTextF_wcs_modify_verify_callback(tf)) {
    /* If the function df_ModifyVerify() returns false then don't
     * continue with the action.
     */
     if (!df_ModifyVerify(tf, event, &replace_prev, &replace_next,
		       &insert, &insert_length, &newInsert, &free_insert)) {
        if (XmTextF_verify_bell(tf)) XBell(XtDisplay(tf), 0);
	if (free_insert) XtFree(insert);
	return False;
     } else {
        df_VerifyBounds(tf, &replace_prev, &replace_next);
        replace_length = (int) (replace_next - replace_prev);
        delta = insert_length - replace_length;

       /* Disallow insertions that go beyond max length boundries.
        */
        if ((delta >= 0) && 
	    ((XmTextF_string_length(tf) + delta) - (XmTextF_max_length(tf)) > 0)) { 
            if (XmTextF_verify_bell(tf)) XBell(XtDisplay(tf), 0);
	    if (free_insert) XtFree(insert);
            return False;
        }

     }
  }

 /* make sure selections are turned off prior to changeing text */
  if (XmTextF_has_primary(tf) &&
      XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf))
     XmDataFieldSetHighlight((Widget)tf, XmTextF_prim_pos_left(tf),
			     XmTextF_prim_pos_right(tf), XmHIGHLIGHT_NORMAL);

  _XmDataFieldDrawInsertionPoint(tf, False);

  /* Allocate more space if we need it.
   */
  if (XmTextF_max_char_size(tf) == 1){
  if (XmTextF_string_length(tf) + insert_length - replace_length >=
      XmTextF_size_allocd(tf))
    {
      XmTextF_size_allocd(tf) += MAX(insert_length + TEXT_INCREMENT,
                                        (XmTextF_size_allocd(tf) * 2));
      XmTextF_value(tf) = (char *) XtRealloc((char*)XmTextF_value(tf), 
		              (unsigned) (XmTextF_size_allocd(tf) * sizeof(char)));
    }
  } else {
  if ((XmTextF_string_length(tf) + insert_length - replace_length) *
                                        sizeof(wchar_t) >= XmTextF_size_allocd(tf))
    {
      XmTextF_size_allocd(tf) +=
			  MAX((insert_length + TEXT_INCREMENT)*sizeof(wchar_t),
                              (XmTextF_size_allocd(tf) * 2));
      XmTextF_wc_value(tf) = (wchar_t *) XtRealloc((char*)XmTextF_wc_value(tf), 
		           (unsigned) XmTextF_size_allocd(tf));
    }
  }

  if (XmTextF_has_primary(tf) && replace_prev < XmTextF_prim_pos_right(tf) &&
			      replace_next > XmTextF_prim_pos_left(tf)) {
     if (replace_prev <= XmTextF_prim_pos_left(tf)) {
	if (replace_next < XmTextF_prim_pos_right(tf)) {
          /* delete encompasses left half of the selection
	   * so move left endpoint
           */
	   XmTextF_prim_pos_left(tf) = replace_next;
	} else {
          /* delete encompasses the selection so set selection to NULL */
	   XmTextF_prim_pos_left(tf) = XmTextF_prim_pos_right(tf);
	}
     } else {
	if (replace_next > XmTextF_prim_pos_right(tf)) {
	  /* delete encompasses the right half of the selection
	   * so move right endpoint
	   */
	   XmTextF_prim_pos_right(tf) = replace_next;
	} else {
	  /* delete is completely within the selection
	   * so set selection to NULL
	   */
	   XmTextF_prim_pos_right(tf) = XmTextF_prim_pos_left(tf);
	}
     }
  }

  if (XmTextF_max_char_size(tf) == 1) {
     if (replace_length > insert_length)
       /* We need to shift the text at and after replace_next to the left. */
       for (src = XmTextF_value(tf) + replace_next,
            dst = src + (insert_length - replace_length),
            i = (int) ((XmTextF_string_length(tf) + 1) - replace_next);
            i > 0;
            ++src, ++dst, --i)
         *dst = *src;
     else if (replace_length < insert_length)
       /* We need to shift the text at and after replace_next to the right. */
       /* Need to add 1 to string_length to handle the NULL terminator on */
       /* the string. */
       for (src = XmTextF_value(tf) + XmTextF_string_length(tf),
            dst = src + (insert_length - replace_length),
            i = (int) ((XmTextF_string_length(tf) + 1) - replace_next);
            i > 0;
            --src, --dst, --i)
         *dst = *src;

    /* Update the string.
     */
     if (insert_length != 0) {
        for (src = insert,
             dst = XmTextF_value(tf) + replace_prev,
             i = insert_length;
             i > 0;
             ++src, ++dst, --i)
          *dst = *src;
     }
   } else {  /* have wchar_t* data */
     if (replace_length > insert_length)
       /* We need to shift the text at and after replace_next to the left. */
       for (wc_src = XmTextF_wc_value(tf) + replace_next,
            wc_dst = wc_src + (insert_length - replace_length),
            i = (int) ((XmTextF_string_length(tf) + 1) - replace_next);
            i > 0;
            ++wc_src, ++wc_dst, --i)
         *wc_dst = *wc_src;
     else if (replace_length < insert_length)
       /* We need to shift the text at and after replace_next to the right. */
       /* Need to add 1 to string_length to handle the NULL terminator on */
       /* the string. */
       for (wc_src = XmTextF_wc_value(tf) + XmTextF_string_length(tf),
            wc_dst = wc_src + (insert_length - replace_length),
            i = (int) ((XmTextF_string_length(tf) + 1) - replace_next);
            i > 0;
            --wc_src, --wc_dst, --i)
         *wc_dst = *wc_src;

    /* Update the string.
     */
     if (insert_length != 0) {
        for (wc_src = (wchar_t *)insert,
             wc_dst = XmTextF_wc_value(tf) + replace_prev,
             i = insert_length;
             i > 0;
             ++wc_src, ++wc_dst, --i)
          *wc_dst = *wc_src;
     }
   }

  if (XmTextF_has_primary(tf) &&
      XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)) {
     if (replace_prev <= XmTextF_prim_pos_left(tf)) {
        XmTextF_prim_pos_left(tf) += delta;
        XmTextF_prim_pos_right(tf) += delta;
     }
     if (XmTextF_prim_pos_left(tf) > XmTextF_prim_pos_right(tf))
	XmTextF_prim_pos_right(tf) = XmTextF_prim_pos_left(tf);
  }

 /* make sure the selection are redisplay, since 
  * they were turned off earlier 
  */
  if (XmTextF_has_primary(tf) &&
      XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf))
  {
     XmDataFieldSetHighlight((Widget)tf, XmTextF_prim_pos_left(tf),
			     XmTextF_prim_pos_right(tf), 
			     XmHIGHLIGHT_SELECTED);
  }
  XmTextF_string_length(tf) += insert_length - replace_length;

  if (move_cursor) {
     if (XmTextF_cursor_position(tf) != newInsert) {
        if (newInsert > XmTextF_string_length(tf)) {
	   cursorPos = XmTextF_string_length(tf);
	} else if (newInsert < 0) {
           cursorPos = 0;
        } else {
           cursorPos = newInsert;
        }
     } else
       cursorPos = replace_next + (insert_length - replace_length);
     if (event != NULL) {
        (void)df_SetDestination((Widget)tf, cursorPos, False, event->xkey.time);
     } else {
        (void) df_SetDestination((Widget)tf, cursorPos, False,
			      XtLastTimestampProcessed(XtDisplay((Widget)tf)));
     }
     _XmDataFielddf_SetCursorPosition(tf, event, cursorPos, False, True);
  }

  if (XmDataField_alignment(tf) == XmALIGNMENT_END)
  {
      df_GetXYFromPos(tf, 0, &x2, &y2);

      y2 -= XmTextF_font_ascent(tf);

      if ((x2 > 0) && (x1 < x2) && (y2 < y1))
      {
          if (x1 < 0) x1 = 0;

          /* PWC - Erase leading space (delta of old & new first position) */
          df_XmSetInvGC(tf, XmTextF_gc(tf));
          XFillRectangle(XtDisplay(tf), XtWindow(tf), XmTextF_gc(tf),
	                 x1, y2, x2, y1);
#if PWC_DEBUG
          printf("Fill Rectangle :: x1(%d), y1(%d) - x2(%d), y2(%d)\n",
                 x1, y2, x2, y1);
#endif
      }
  }

  if (XmTextF_resize_width(tf) && XmTextF_do_resize(tf)) 
  {
     df_AdjustSize(tf);
  } else {
     df_AdjustText(tf, XmTextF_cursor_position(tf), False);
     df_RedisplayText(tf, old_pos, XmTextF_string_length(tf));
  }

  _XmDataFieldDrawInsertionPoint(tf, True);
  if (free_insert) {
      XtFree(insert);
  }

  return True;
}


/*
 * Reset selection flag and selection positions and then display
 * the new settings.
 */
void 
#ifdef _NO_PROTO
_XmDataFieldDeselectSelection( w, disown, sel_time )
        Widget w ;
        Boolean disown ;
        Time sel_time ;
#else
_XmDataFieldDeselectSelection(
        Widget w,
#if NeedWidePrototypes
        int disown,
#else
        Boolean disown,
#endif /* NeedWidePrototypes */
        Time sel_time )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;

  if (disown)
  {
    /*
     * Disown the primary selection (This function is a no-op if
     * this widget doesn't own the primary selection)
     */
     XtDisownSelection(w, XA_PRIMARY, sel_time);
  }
  if (tf != NULL) {
     _XmDataFieldDrawInsertionPoint(tf, False);
     XmTextF_has_primary(tf) = False;
     DataFieldSetHighlight(tf, XmTextF_prim_pos_left(tf),
			   XmTextF_prim_pos_right(tf), XmHIGHLIGHT_NORMAL);
     XmTextF_prim_pos_left(tf) = XmTextF_prim_pos_right(tf) =
	       XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);

     if (!XmTextF_has_focus(tf)) 
     {
	 XmDataFieldSetAddMode(w, False);
     }
     df_RedisplayText(tf, 0, XmTextF_string_length(tf));

     _XmDataFieldDrawInsertionPoint(tf, True);
  }
}

/*
 * Finds the cursor position from the given X value.
 */
static XmTextPosition 
#ifdef _NO_PROTO
df_GetPosFromX( tf, x )
        XmDataFieldWidget tf ;
        Position x ;
#else
df_GetPosFromX(
        XmDataFieldWidget tf,
#if NeedWidePrototypes
        int x )
#else
        Position x )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    XmTextPosition position;
    int temp_x = 0;
    int next_char_width = 0;

    if (XmDataField_alignment(tf) == XmALIGNMENT_END)
        return RightAlignedGetPosFromX(tf, x);

   /* Decompose the x to equal the length of the text string */
    temp_x += (int) XmTextF_h_offset(tf);

   /* Next width is an offset allowing button presses on the left side 
    * of a character to select that character, while button presses
    * on the rigth side of the character select the  NEXT character.
    */

    if (XmTextF_string_length(tf) > 0) {

       if (XmTextF_max_char_size(tf) != 1) {
          next_char_width = df_FindPixelLength(tf, (char*)XmTextF_wc_value(tf), 1);
       } else {
          next_char_width = df_FindPixelLength(tf, XmTextF_value(tf), 1);
       }
    }

    for (position = 0; temp_x + next_char_width/2 < (int) x &&
	               position < XmTextF_string_length(tf); position++){

       temp_x+=next_char_width;    /* 
				    * We still haven't reached the x pos.
				    * Add the width and find the next chars
				    * width. 
				    */

	/*
	 * If there is a next position, find its width.  Otherwise, use the
	 * current "next" width.
	 */

       if (XmTextF_string_length(tf) > position + 1) {
          if (XmTextF_max_char_size(tf) != 1) {
             next_char_width = df_FindPixelLength(tf,
				  (char*)(XmTextF_wc_value(tf) + position + 1), 1);
	  } else {
             next_char_width = df_FindPixelLength(tf,
				           XmTextF_value(tf) + position + 1, 1);
	  }
       } 
    } /* for */

    return position;
}

/*
 * Finds the cursor position from the given X value.
 */
static XmTextPosition 
#ifdef _NO_PROTO
RightAlignedGetPosFromX( tf, x )
    XmDataFieldWidget tf ;
    Position x ;
#else
RightAlignedGetPosFromX( XmDataFieldWidget tf,
#if NeedWidePrototypes
    int x )
#else
    Position x )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    XmTextPosition position;
    int margin_width = XmTextF_margin_width(tf) +
                        tf->primitive.highlight_thickness +
                        tf->primitive.shadow_thickness;
    int temp_x;
    int next_char_width = 0;

    position = XmTextF_string_length(tf);

    temp_x = tf->core.width - margin_width + XmTextF_h_offset(tf);

    if (XmTextF_string_length(tf) > 0) {

       if (XmTextF_max_char_size(tf) != 1) {
          next_char_width = df_FindPixelLength(tf, (char*)XmTextF_wc_value(tf) + 
					    position - 1, 1);
       } else {
          next_char_width = df_FindPixelLength(tf, XmTextF_value(tf) +
					    position - 1, 1);
       }
    }

    for (; x < (temp_x - next_char_width / 2) && (position > 0); position--)
    {
        temp_x -= next_char_width; /* 
				    * We still haven't reached the x pos.
				    * Add the width and find the next chars
				    * width. 
				    */

	/*
	 * If there is a next position, find its width.  Otherwise, use the
	 * current "next" width.
	 */
        if (position > 1)
        {
            if (XmTextF_max_char_size(tf) != 1) {
                next_char_width = df_FindPixelLength(tf,
		    (char*)(XmTextF_wc_value(tf) + position - 2), 1);
	    } else {
                next_char_width = df_FindPixelLength(tf,
		    XmTextF_value(tf) + position - 2 , 1);
            }
        } 
    } /* for */

#if PWC_DEBUG
    printf("CursorPos(%d), x(%d)\n", position, x);
#endif

    return position;
}

/* ARGSUSED */
static Boolean 
#ifdef _NO_PROTO
df_SetDestination( w, position, disown, set_time )
        Widget w ;
        XmTextPosition position ;
        Boolean disown ;
        Time set_time ;
#else
df_SetDestination(
        Widget w,
        XmTextPosition position,
#if NeedWidePrototypes
        int disown,
#else
        Boolean disown,
#endif /* NeedWidePrototypes */
        Time set_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Boolean result = TRUE;
    Atom MOTIF_DESTINATION = XmInternAtom(XtDisplay(w),
                                        "MOTIF_DESTINATION", False);

    if (!XtIsRealized(w)) return False;

    _XmDataFieldDrawInsertionPoint(tf, False);

    if (!disown) {
        if (!XmTextF_has_destination(tf)) {
	    if (!set_time) set_time = df_GetServerTime(w);
            result = XtOwnSelection(w, MOTIF_DESTINATION, set_time,
                                    _XmDataFieldConvert,
				    _XmDataFieldLoseSelection,
                                    (XtSelectionDoneProc) NULL);
            XmTextF_dest_time(tf) = set_time;
            XmTextF_has_destination(tf) = result;

            if (result) _XmSetDestination(XtDisplay(w), w);
      	    _XmDataFToggleCursorGC(w);
        }
    } else {
        if (XmTextF_has_destination(tf))
	   if (!set_time) set_time = df_GetServerTime(w);
           XtDisownSelection(w, MOTIF_DESTINATION, set_time);

          /* Call XmGetDestination(dpy) to get widget that last had
             destination cursor. */
           if (w == XmGetDestination(XtDisplay(w)))
              _XmSetDestination(XtDisplay(w), (Widget)NULL);

           XmTextF_has_destination(tf) = False;
      	   _XmDataFToggleCursorGC(w);
    }

    _XmDataFieldDrawInsertionPoint(tf, True);

    return result;
}

Boolean 
#ifdef _NO_PROTO
_XmDataFielddf_SetDestination( w, position, set_time )
        Widget w ;
        XmTextPosition position ;
        Time set_time ;
#else
_XmDataFielddf_SetDestination(
        Widget w,
        XmTextPosition position,
        Time set_time )
#endif /* _NO_PROTO */
{
   Boolean result;

   result = df_SetDestination(w, position, False, set_time);

   return result;
}


/*
 * Calls the losing focus verify callback to verify that the application
 * want to traverse out of the text field widget.  Returns the result.
 */
static Boolean 
#ifdef _NO_PROTO
df_VerifyLeave( tf, event )
        XmDataFieldWidget tf ;
        XEvent *event ;
#else
df_VerifyLeave(
        XmDataFieldWidget tf,
        XEvent *event )
#endif /* _NO_PROTO */
{
    XmTextVerifyCallbackStruct  cbdata;

    cbdata.reason = XmCR_LOSING_FOCUS;
    cbdata.event = event;
    cbdata.doit = True;
    cbdata.currInsert = XmTextF_cursor_position(tf);
    cbdata.newInsert = XmTextF_cursor_position(tf);
    cbdata.startPos = XmTextF_cursor_position(tf);
    cbdata.endPos = XmTextF_cursor_position(tf);
    cbdata.text = NULL;
    XtCallCallbackList((Widget) tf, XmTextF_losing_focus_callback(tf), 
		       (XtPointer) &cbdata);
    return(cbdata.doit);
}

/* This routine is used to determine if two adjacent wchar_t characters
 * constitute a word boundary */
/* ARGSUSED */
static Boolean
#ifdef _NO_PROTO
_XmDataFieldIsWordBoundary( tf, pos1, pos2 )
	XmDataFieldWidget tf ;
	XmTextPosition pos1 ;
	XmTextPosition pos2 ;
#else
_XmDataFieldIsWordBoundary(
	XmDataFieldWidget tf,
	XmTextPosition pos1 ,
	XmTextPosition pos2 )
#endif /* _NO_PROTO */
{
   int size_pos1 = 0;
   int size_pos2 = 0;
   char s1[MB_LEN_MAX];
   char s2[MB_LEN_MAX];

/* if positions aren't adjacent, return False */
   if(pos1 < pos2 && ((pos2 - pos1) != 1)) 
      return False;
   else if(pos2 < pos1 && ((pos1 - pos2) != 1)) 
      return False;

   if (XmTextF_max_char_size(tf) == 1) { /* data is char* and one-byte per char */
      if (isspace((int)(unsigned char)XmTextF_value(tf)[pos1]) || 
	  isspace((int)(unsigned char)XmTextF_value(tf)[pos2])) return True;
   } else {
      size_pos1 = wctomb(s1, XmTextF_wc_value(tf)[pos1]);
      size_pos2 = wctomb(s2, XmTextF_wc_value(tf)[pos2]);
      if (size_pos1 == 1 && (size_pos2 != 1 || 
			     isspace((int)(unsigned char)*s1)))
	return True;
      if (size_pos2 == 1 && (size_pos1 != 1 || 
			     isspace((int)(unsigned char)*s2)))
	return True;
   }
   return False;
}

/* This routine accepts an array of wchar_t's containing wchar encodings
 * of whitespace characters (and the number of array elements), comparing
 * the wide character passed to each element of the array.  If a match
 * is found, we got a white space.  This routine exists only because
 * iswspace(3c) is not yet standard.  If a system has isw* available,
 * calls to this routine should be changed to iswspace(3c) (and callers
 * should delete initialization of the array), and this routine should
 * be deleted.  Its a stop gap measure to avoid allocating an instance
 * variable for the white_space array and/or declaring a widget wide
 * global for the data and using a macro.  Its ugly, but it works and 
 * in the long run will be replaced by standard functionality. */

/* ARGSUSED */
static Boolean
#ifdef _NO_PROTO
_XmDataFieldIsWSpace( wide_char, white_space, num_entries )
	wchar_t wide_char ;
	wchar_t * white_space ;
	int num_entries ;
#else
_XmDataFieldIsWSpace(
	wchar_t wide_char,
	wchar_t * white_space ,
	int num_entries )
#endif /* _NO_PROTO */
{
   int i;

   for (i=num_entries; i > 0; i--){
      if (wide_char == white_space[i]) return True;
   }
   return False;
}

static void 
#ifdef _NO_PROTO
df_FindWord( tf, begin, left, right )
        XmDataFieldWidget tf ;
        XmTextPosition begin ;
        XmTextPosition *left ;
        XmTextPosition *right ;
#else
df_FindWord(
        XmDataFieldWidget tf,
        XmTextPosition begin,
        XmTextPosition *left,
        XmTextPosition *right )
#endif /* _NO_PROTO */
{
    XmTextPosition start, end;
    wchar_t white_space[3];

    if (XmTextF_max_char_size(tf) == 1) {
       for (start = begin; start > 0; start--) {
          if (isspace((int)(unsigned char)XmTextF_value(tf)[start - 1])) {
	     break;
          }
       }
       *left = start;

       for (end = begin; end <= XmTextF_string_length(tf); end++) {
          if (isspace((int)(unsigned char)XmTextF_value(tf)[end])) {
             end++;
             break;
          }
       }
       *right = end - 1;
    } else { /* check for iswspace and iswordboundary in each direction */
       (void)mbtowc(&white_space[0], " ", 1);
       (void)mbtowc(&white_space[1], "\n", 1);
       (void)mbtowc(&white_space[2], "\t", 1);
       for (start = begin; start > 0; start --) {
          if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[start-1],white_space, 3)
	      || _XmDataFieldIsWordBoundary(tf, (XmTextPosition) start - 1, 
					    start)) {
		 break;
	  }
       }
       *left = start;

       for (end = begin; end <= XmTextF_string_length(tf); end++) {
	   if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[end], white_space, 3)){
	      end++;
	      break;
	   } else if (end < XmTextF_string_length(tf)) {
	      if (_XmDataFieldIsWordBoundary(tf, end, (XmTextPosition)end + 1)){
	         end += 2; /* want to return position of next word; end + 1 */
		 break;    /* is that position && *right = end - 1... */
              }
           }
       }
       *right = end - 1;
   }
}

static void 
#ifdef _NO_PROTO
df_FindPrevWord( tf, left, right )
        XmDataFieldWidget tf ;
        XmTextPosition *left ;
        XmTextPosition *right ;
#else
df_FindPrevWord(
        XmDataFieldWidget tf,
        XmTextPosition *left,
        XmTextPosition *right )
#endif /* _NO_PROTO */
{

    XmTextPosition start = XmTextF_cursor_position(tf);
    wchar_t white_space[3];

    if (XmTextF_max_char_size(tf) != 1) {
       (void)mbtowc(&white_space[0], " ", 1);
       (void)mbtowc(&white_space[1], "\n", 1);
       (void)mbtowc(&white_space[2], "\t", 1);
    }


    if (XmTextF_max_char_size(tf) == 1) {
       if ((start > 0) && 
	   (isspace((int)(unsigned char)XmTextF_value(tf)[start - 1]))) {
           for (; start > 0; start--) {
               if (!isspace((int)(unsigned char)XmTextF_value(tf)[start - 1])) {
                  start--;
                  break;
               }
           }
       }
       df_FindWord(tf, start, left, right);
    } else { 
       if ((start > 0) && (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[start - 1],
						white_space, 3))) {
          for (; start > 0; start--) {
	     if (!_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[start -1], 
				       white_space, 3)){
		start--;
		break;
             }
          }
       } else if ((start > 0) && 
		  _XmDataFieldIsWordBoundary(tf, (XmTextPosition) start - 1, 
					     start)){
          start--;
       }
       df_FindWord(tf, start, left, right);
    }
}

static void 
#ifdef _NO_PROTO
df_FindNextWord( tf, left, right )
        XmDataFieldWidget tf ;
        XmTextPosition *left ;
        XmTextPosition *right ;
#else
df_FindNextWord(
        XmDataFieldWidget tf,
        XmTextPosition *left,
        XmTextPosition *right )
#endif /* _NO_PROTO */
{

    XmTextPosition end = XmTextF_cursor_position(tf);
    wchar_t white_space[3];

    if (XmTextF_max_char_size(tf) != 1) {
       (void)mbtowc(&white_space[0], " ", 1);
       (void)mbtowc(&white_space[1], "\n", 1);
       (void)mbtowc(&white_space[2], "\t", 1);
    }


    if(XmTextF_max_char_size(tf) == 1) {
       if (isspace((int)(unsigned char)XmTextF_value(tf)[end])) {
           for (end = XmTextF_cursor_position(tf);
                end < XmTextF_string_length(tf); end++) {
               if (!isspace((int)(unsigned char)XmTextF_value(tf)[end])) {
                  break;
               }
           }
       }
       df_FindWord(tf, end, left, right);
      /*
       * Set right to the last whitespace following the end of the
       * current word.
       */
       while (*right < XmTextF_string_length(tf) &&
              isspace((int)(unsigned char)XmTextF_value(tf)[(int)*right]))
             *right = *right + 1;
       if (*right < XmTextF_string_length(tf))
          *right = *right - 1;
   } else {
      if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[end], white_space, 3)) {
	 for ( ; end < XmTextF_string_length(tf); end ++) {
	   if (!_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[end], white_space, 3)) {
	       break;
           }
         }
      } else { /* if for other reasons at word boundry, advance to next word */
	 if ((end < XmTextF_string_length(tf)) && 
	      _XmDataFieldIsWordBoundary(tf, end, (XmTextPosition) end + 1))
	      end++;
      }
      df_FindWord(tf, end, left, right);
      /*
       * If word boundary caused by whitespace, set right to the last 
       * whitespace following the end of the current word.
       */
      if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[(int)*right], white_space, 3))      {
         while (*right < XmTextF_string_length(tf) &&
               _XmDataFieldIsWSpace(XmTextF_wc_value(tf)[(int)*right], 
				    white_space, 3)) {
            *right = *right + 1;
	 }
	 if (*right < XmTextF_string_length(tf))
            *right = *right - 1;
      }
   }
}

static void 
#ifdef _NO_PROTO
df_CheckDisjointSelection( w, position, sel_time )
        Widget w ;
        XmTextPosition position ;
        Time sel_time ;
#else
df_CheckDisjointSelection(
        Widget w,
        XmTextPosition position,
        Time sel_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition left = 0, right = 0;

    if (XmTextF_add_mode(tf) || 
        (XmDataFieldGetSelectionPosition(w, &left, &right) && left != right &&
         position >= left && position <= right))
       XmTextF_pending_off(tf) = FALSE;
    else
       XmTextF_pending_off(tf) = TRUE;

    if (left == right) {
       (void) df_SetDestination(w, position, False, sel_time);
       XmTextF_prim_anchor(tf) = position;
    } else {
       (void) df_SetDestination(w, position, False, sel_time);
       if (!XmTextF_add_mode(tf)) XmTextF_prim_anchor(tf) = position;
    }
}

static Boolean 
#ifdef _NO_PROTO
df_NeedsPendingDelete( tf )
        XmDataFieldWidget tf ;
#else
df_NeedsPendingDelete(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
   return (XmTextF_add_mode(tf) ?
	   (XmTextF_pending_delete(tf) &&
	    XmTextF_has_primary(tf) &&
	    XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf) &&
	    XmTextF_prim_pos_left(tf) <= XmTextF_cursor_position(tf) &&
	    XmTextF_prim_pos_right(tf) >= XmTextF_cursor_position(tf)) :
	   (XmTextF_has_primary(tf) &&
	    XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)));
}

static Boolean 
#ifdef _NO_PROTO
df_NeedsPendingDeleteDisjoint( tf )
        XmDataFieldWidget tf ;
#else
df_NeedsPendingDeleteDisjoint(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
  return (XmTextF_pending_delete(tf) &&
	  XmTextF_has_primary(tf) &&
	  XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf) &&
	  XmTextF_prim_pos_left(tf) <= XmTextF_cursor_position(tf) &&
	  XmTextF_prim_pos_right(tf) >= XmTextF_cursor_position(tf));
}

static Time
#ifdef _NO_PROTO
df_GetServerTime( w )
        Widget w ;
#else
df_GetServerTime(
        Widget w )
#endif /* _NO_PROTO */
{
  XEvent event;
  EventMask shellMask;

  while(!XtIsShell(w)) w = XtParent(w);

  shellMask =  XtBuildEventMask(w);

  if (!(shellMask & PropertyChangeMask))
     XSelectInput(XtDisplay(w), XtWindow(w),
                  (long)(shellMask | PropertyChangeMask));

  XChangeProperty(XtDisplay(w), XtWindow(w), XA_WM_HINTS, XA_WM_HINTS,
                  32, PropModeAppend, (unsigned char *)NULL, 0);


  XWindowEvent(XtDisplay(w), XtWindow(w), PropertyChangeMask, &event);

  if (!(shellMask & PropertyChangeMask))
     XSelectInput(XtDisplay(w), XtWindow(w), (long)shellMask);

  return (event.xproperty.time);
}


/****************************************************************
 *
 * Input functions defined in the action table.
 *
 ****************************************************************/

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_InsertChar( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_InsertChar(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  char insert_string[TEXT_MAX_INSERT_SIZE];
  XmTextPosition cursorPos, nextPos;
  wchar_t * wc_insert_string;
  int insert_length, i;
  int num_chars;
  Boolean replace_res;
  Boolean pending_delete = False;
  Status status_return;
  XmAnyCallbackStruct cb;

  /* Determine what was pressed.
  */
  insert_length = XmImMbLookupString(w, (XKeyEvent *) event, insert_string, 
		                     TEXT_MAX_INSERT_SIZE, (KeySym *) NULL, 
				     &status_return);

  if (insert_length > 0 && !XmTextF_editable(tf)) {
     if (XmTextF_verify_bell(tf)) XBell(XtDisplay((Widget)tf), 0);
     return;
  }

 /* If there is more data than we can handle, bail out */
  if (status_return == XBufferOverflow || insert_length > TEXT_MAX_INSERT_SIZE)
  {
     return;
  }

 /* *LookupString in some cases can return the NULL as a character, such
  * as when the user types <Ctrl><back_quote> or <Ctrl><@>.  Text widget
  * can't handle the NULL as a character, so we dump it here.
  */

  for (i=0; i < insert_length; i++)
     if (insert_string[i] == 0) insert_length = 0; /* toss out input string */
     
  if (insert_length > 0) {
   /* do not insert non-printing characters */
    if (XmTextF_have_fontset(tf)){
       if (!XmbTextEscapement((XFontSet)XmTextF_font(tf), insert_string, 
			      insert_length)) 
          return;
    } else {
      if (!XTextWidth(XmTextF_font(tf), insert_string, insert_length)) 
	 return;
    }

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (df_NeedsPendingDeleteDisjoint(tf)){
       if (!XmDataFieldGetSelectionPosition(w, &cursorPos, &nextPos) ||
            cursorPos == nextPos) {
          XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
       }
       pending_delete = True;

       XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);

    } else {
       cursorPos = nextPos = XmTextF_cursor_position(tf);
    }


    if (XmTextF_max_char_size(tf) == 1) {
       if (XmTextF_overstrike(tf)) nextPos += insert_length;
       if (nextPos > XmTextF_string_length(tf)) nextPos = XmTextF_string_length(tf);
       replace_res = _XmDataFieldReplaceText(tf, (XEvent *) event, cursorPos,
					     nextPos, insert_string,
					     insert_length, True);
    } else {
       char stack_cache[100];
       insert_string[insert_length] = '\0'; /* NULL terminate for mbstowcs */
       wc_insert_string = (wchar_t*)XmStackAlloc((Cardinal)(insert_length+1) *						     sizeof(wchar_t), stack_cache);
       num_chars = mbstowcs( wc_insert_string, insert_string, insert_length+1);
       if (XmTextF_overstrike(tf)) nextPos += num_chars;
       if (nextPos > XmTextF_string_length(tf)) nextPos = XmTextF_string_length(tf);
       replace_res = _XmDataFieldReplaceText(tf, (XEvent *) event, cursorPos,
					     nextPos, (char*) wc_insert_string,
					     num_chars, True);
       XmStackFree((char *)wc_insert_string, stack_cache);
    }

    if (replace_res) {
        if (pending_delete) {
           XmDataFieldSetSelection(w, XmTextF_cursor_position(tf),
                               XmTextF_cursor_position(tf), event->xkey.time);
        }
        df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			       event->xkey.time);
        _XmDataFielddf_SetCursorPosition(tf, event, XmTextF_cursor_position(tf), 
				      False, True);
        cb.reason = XmCR_VALUE_CHANGED;
        cb.event = event;
        XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		           (XtPointer) &cb);
    }
    _XmDataFieldDrawInsertionPoint(tf, True);
  }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_InsertString( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_InsertString(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  char insert_string[TEXT_MAX_INSERT_SIZE];
  XmTextPosition cursorPos, nextPos;
  wchar_t * wc_insert_string;
  int insert_length;
  int num_chars;
  Boolean replace_res;
  Boolean pending_delete = False;
  register int i;

  if (!XmTextF_editable(tf)) {
     if (XmTextF_verify_bell(tf)) XBell(XtDisplay((Widget)tf), 0);
  }

  for (i = 0; i < *num_params; i++)  {
      strcpy(insert_string, params[i]);
      insert_length = strlen(insert_string);
     
      if (insert_length > 0) {
	  /* do not insert non-printing characters */
	  if (XmTextF_have_fontset(tf)){
	      if (!XmbTextEscapement((XFontSet)XmTextF_font(tf), insert_string, 
				     insert_length)) 
		  return;
	  } else {
	      if (!XTextWidth(XmTextF_font(tf), insert_string, insert_length)) 
		  return;
	  }

	  _XmDataFieldDrawInsertionPoint(tf, False);
	  if (df_NeedsPendingDeleteDisjoint(tf)){
	      if (!XmDataFieldGetSelectionPosition(w, &cursorPos, &nextPos) ||
		  cursorPos == nextPos) {
		  XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
	      }
	      pending_delete = True;
	      
	      XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
	      
	  } else {
	      cursorPos = nextPos = XmTextF_cursor_position(tf);
	  }

	  
	  if (XmTextF_overstrike(tf)) {
	      if (nextPos != XmTextF_string_length(tf)) nextPos++;
	  }
	  if (XmTextF_max_char_size(tf) == 1) {
	      replace_res =
		  _XmDataFieldReplaceText(tf, (XEvent *) event, cursorPos,
					  nextPos, insert_string,insert_length,
					  True);
	  } else {
	      insert_string[insert_length] = '\0'; /* NULL terminate for mbstowcs */
	      wc_insert_string = (wchar_t*)XtMalloc((unsigned)(insert_length+1) *						     sizeof(wchar_t));
	      num_chars = mbstowcs( wc_insert_string, insert_string, insert_length+1);
	      replace_res = _XmDataFieldReplaceText(tf, (XEvent *) event, cursorPos,
						    nextPos, (char*) wc_insert_string,
						    num_chars, True);
	      XtFree((char *)wc_insert_string);
	  }

	  if (replace_res) {
	      if (pending_delete) {
		  XmDataFieldSetSelection(w, XmTextF_cursor_position(tf),
					  XmTextF_cursor_position(tf), event->xkey.time);
	      }
	      df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
				     event->xkey.time);
	      _XmDataFielddf_SetCursorPosition(tf, event, 
					    XmTextF_cursor_position(tf), False, True);
	  }
	  _XmDataFieldDrawInsertionPoint(tf, True);
      }
  }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeletePrevChar( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeletePrevChar(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmAnyCallbackStruct cb;

  /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else { 
     if (XmTextF_has_primary(tf) &&
         XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)) {
        if (XmTextF_cursor_position(tf) - 1 >= 0)
           if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf) - 1,
                                     XmTextF_cursor_position(tf), NULL, 0, True)) {
              df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
	               event->xkey.time);
              _XmDataFielddf_SetCursorPosition(tf, event,
					    XmTextF_cursor_position(tf),
					    False, True);
              cb.reason = XmCR_VALUE_CHANGED;
              cb.event = event;
              XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                 (XtPointer) &cb);
           }
      } else if (XmTextF_cursor_position(tf) - 1 >= 0) {
        if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf) - 1,
                                    XmTextF_cursor_position(tf), NULL, 0, True)) {
            df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
	             event->xkey.time);
            _XmDataFielddf_SetCursorPosition(tf, event, XmTextF_cursor_position(tf), 
					  False, True);
            cb.reason = XmCR_VALUE_CHANGED;
            cb.event = event;
            XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		               (XtPointer) &cb);
        }
      }  
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeleteNextChar( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeleteNextChar(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmAnyCallbackStruct cb;

 /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else { 
      if (XmTextF_has_primary(tf) &&
           XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)) {
          if (XmTextF_cursor_position(tf) < XmTextF_string_length(tf))
             if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf),
                                 XmTextF_cursor_position(tf) + 1, NULL, 0, True)) {
                 df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			                event->xkey.time);
                 _XmDataFielddf_SetCursorPosition(tf, event, 
					       XmTextF_cursor_position(tf), 
					       False, True);
                 cb.reason = XmCR_VALUE_CHANGED;
                 cb.event = event;
                 XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                    (XtPointer) &cb);
             }
       } else if (XmTextF_cursor_position(tf) < XmTextF_string_length(tf))
          if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf),
				      XmTextF_cursor_position(tf) + 1, 
				      NULL, 0, True)) 
	  {
              df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
					event->xkey.time);
              _XmDataFielddf_SetCursorPosition(tf, event, 
					    XmTextF_cursor_position(tf),
					    False, True);
              cb.reason = XmCR_VALUE_CHANGED;
              cb.event = event;
              XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                 (XtPointer) &cb);
          }
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeletePrevWord( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeletePrevWord(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition left, right;
  XmAnyCallbackStruct cb;

 /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else { 
       df_FindPrevWord(tf, &left, &right);
       if (XmTextF_has_primary(tf) &&
           XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)) 
       {
	   if (_XmDataFieldReplaceText(tf, event, 
				       left, XmTextF_cursor_position(tf),
				       NULL, 0, True)) 
	   {
	       df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
					 event->xkey.time);
	       _XmDataFielddf_SetCursorPosition(tf, event, 
						XmTextF_cursor_position(tf), 
						False, True);
	       cb.reason = XmCR_VALUE_CHANGED;
	       cb.event = event;
	       XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
				  (XtPointer) &cb);
	   }	
       } else if (XmTextF_cursor_position(tf) - 1 >= 0)
          if (_XmDataFieldReplaceText(tf, event, left, XmTextF_cursor_position(tf),
				      NULL, 0, True)) {
              df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			             event->xkey.time);
              _XmDataFielddf_SetCursorPosition(tf, event,
					    XmTextF_cursor_position(tf),
					    False, True);
              cb.reason = XmCR_VALUE_CHANGED;
              cb.event = event;
              XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                 (XtPointer) &cb);
          }
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeleteNextWord( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeleteNextWord(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition left, right;
  XmAnyCallbackStruct cb;

 /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else { 
       df_FindNextWord(tf, &left, &right);
       if (XmTextF_has_primary(tf) &&
           XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf)) {
          if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf),
				      right, NULL, 0, True)){
             df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
				    event->xkey.time);
             _XmDataFielddf_SetCursorPosition(tf, event,
					   XmTextF_cursor_position(tf),
					   False, True);
             cb.reason = XmCR_VALUE_CHANGED;
             cb.event = event;
             XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                (XtPointer) &cb);
          }
       } else if (XmTextF_cursor_position(tf) < XmTextF_string_length(tf))
          if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf),
				      right, NULL, 0, True)){
              df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			             event->xkey.time);
              _XmDataFielddf_SetCursorPosition(tf, event, 
					    XmTextF_cursor_position(tf), 
					    False, True);
              cb.reason = XmCR_VALUE_CHANGED;
              cb.event = event;
              XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		                 (XtPointer) &cb);
          }
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeleteToEndOfLine( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeleteToEndOfLine(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmAnyCallbackStruct cb;
    
 /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else if (XmTextF_cursor_position(tf) < XmTextF_string_length(tf)) {
     if (_XmDataFieldReplaceText(tf, event, XmTextF_cursor_position(tf),
                                 XmTextF_string_length(tf), NULL, 0, True)) {
         df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			        event->xkey.time);
         _XmDataFielddf_SetCursorPosition(tf, event, XmTextF_cursor_position(tf),
				       False, True);
         cb.reason = XmCR_VALUE_CHANGED;
         cb.event = event;
         XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		            (XtPointer) &cb);
       }
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeleteToStartOfLine( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeleteToStartOfLine(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmAnyCallbackStruct cb;
    
 /* if pending delete is on and there is a selection */
  _XmDataFieldDrawInsertionPoint(tf, False);
  if (df_NeedsPendingDelete(tf)) (void) DataFieldRemove(w, event);
  else if (XmTextF_cursor_position(tf) - 1 >= 0) {
    if (_XmDataFieldReplaceText(tf, event, 0, 
			        XmTextF_cursor_position(tf), NULL, 0, True)) {
        df_CheckDisjointSelection(w, XmTextF_cursor_position(tf),
			       event->xkey.time);
        _XmDataFielddf_SetCursorPosition(tf, event, XmTextF_cursor_position(tf),
				      False, True);
        cb.reason = XmCR_VALUE_CHANGED;
        cb.event = event;
        XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		           (XtPointer) &cb);
       }
  }
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ProcessCancel( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ProcessCancel(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    XmParentInputActionRec  p_event ;

    p_event.process_type = XmINPUT_ACTION ;
    p_event.action = XmPARENT_CANCEL ;
    p_event.event = event ;/* Pointer to XEvent. */
    p_event.params = params ; /* Or use what you have if   */
    p_event.num_params = num_params ;/* input is from translation.*/

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (XmTextF_has_secondary(tf)) {
       XmTextF_cancel(tf) = True;
       _XmDataFieldSetSel2(w, 0, 0, False, event->xkey.time);
       XmTextF_has_secondary(tf) = False;
       XtUngrabKeyboard(w, CurrentTime);
    }

    if (XmTextF_has_primary(tf) && XmTextF_extending(tf)) {
       XmTextF_cancel(tf) = True;
      /* reset orig_left and orig_right */
       XmDataFieldSetSelection(w, XmTextF_orig_left(tf),
			       XmTextF_orig_right(tf), event->xkey.time);
    }

    if (!XmTextF_cancel(tf))
       (void) _XmParentProcess(XtParent(tf), (XmParentProcessData) &p_event);

    if (XmTextF_select_id(tf)) {
       XtRemoveTimeOut(XmTextF_select_id(tf));
       XmTextF_select_id(tf) = 0;
    }
    _XmDataFieldDrawInsertionPoint(tf, True);

}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_Activate( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_Activate(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmAnyCallbackStruct cb;
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmParentInputActionRec  p_event ;

    p_event.process_type = XmINPUT_ACTION ;
    p_event.action = XmPARENT_ACTIVATE ;
    p_event.event = event ;/* Pointer to XEvent. */
    p_event.params = params ; /* Or use what you have if   */
    p_event.num_params = num_params ;/* input is from translation.*/

    cb.reason = XmCR_ACTIVATE;
    cb.event  = event;
    XtCallCallbackList(w, XmTextF_activate_callback(tf), (XtPointer) &cb);

    (void) _XmParentProcess(XtParent(w), (XmParentProcessData) &p_event);
}

static void
#ifdef _NO_PROTO
df_SetAnchorBalancing(tf, position)
XmDataFieldWidget tf;
XmTextPosition position;
#else
df_SetAnchorBalancing(
        XmDataFieldWidget tf,
        XmTextPosition position)
#endif /* _NO_PROTO */
{
    XmTextPosition left, right;
    float bal_point;

    if (!XmDataFieldGetSelectionPosition((Widget)tf, &left, &right) ||
	left == right) {
          XmTextF_prim_anchor(tf) = position;
    } else {
          bal_point = (float)(((float)(right - left) / 2.0) + (float)left);

         /* shift anchor and direction to opposite end of the selection */
          if ((float)position < bal_point) {
             XmTextF_prim_anchor(tf) = XmTextF_orig_right(tf);
          } else if ((float)position > bal_point) {
             XmTextF_prim_anchor(tf) = XmTextF_orig_left(tf);
          }
    }
}

static void
#ifdef _NO_PROTO
df_SetNavigationAnchor(tf, position, extend)
XmDataFieldWidget tf;
XmTextPosition position;
Boolean extend;
#else
df_SetNavigationAnchor(
        XmDataFieldWidget tf,
        XmTextPosition position,
#if NeedWidePrototypes
        int extend )
#else
        Boolean extend )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    XmTextPosition left, right;

    if (!XmTextF_add_mode(tf)) {
       if (extend) {
          df_SetAnchorBalancing(tf, position);
       } else {
         if (XmDataFieldGetSelectionPosition((Widget)tf, &left, &right) &&
            left != right) {
           df_SetSelection(tf, position, position, True);
           XmTextF_prim_anchor(tf) = position;
         }
       }
    } else if (extend) {
       df_SetAnchorBalancing(tf, position);
    }
}

static void
#ifdef _NO_PROTO
df_CompleteNavigation(tf, event, position, time, extend)
XmDataFieldWidget tf;
XEvent *event;
XmTextPosition position;
Time time;
Boolean extend;
#else
df_CompleteNavigation(
        XmDataFieldWidget tf,
	XEvent *event,
        XmTextPosition position,
        Time time,
#if NeedWidePrototypes
        int extend )
#else
        Boolean extend )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
    XmTextPosition left, right;
    Boolean     backward = False;

    if ((XmTextF_add_mode(tf) &&
	 XmDataFieldGetSelectionPosition((Widget)tf, &left, &right) &&
         position >= left && position <= right) || extend)
       XmTextF_pending_off(tf) = FALSE;
    else
       XmTextF_pending_off(tf) = TRUE;

    _XmDataFielddf_SetCursorPosition(tf, event, position, True, True);

    if (extend) {
       if (XmTextF_prim_anchor(tf) > position) {
          left = position;
          right = XmTextF_prim_anchor(tf);
          backward = True;
       } else {
          left = XmTextF_prim_anchor(tf);
          right = position;
       }
       XmDataFieldSetSelection((Widget)tf, left, right, time);

    /*  Begin fix for CR 5994 */
    if ( backward ) 
      _XmDataFielddf_SetCursorPosition(tf, event, position, False, False);
    /*  End fix for CR 5994 */

       XmTextF_orig_left(tf) = left;
       XmTextF_orig_right(tf) = right;
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_SimpleMovement( w, event, params, num_params, cursorPos, position )
        Widget w ;
        XEvent *event ;
        String *params ;
        Cardinal *num_params ;
        XmTextPosition cursorPos ;
        XmTextPosition position ;
#else
df_SimpleMovement(
        Widget w,
        XEvent *event,
        String *params,
        Cardinal *num_params,
        XmTextPosition cursorPos,
        XmTextPosition position )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  Boolean extend = False;

  if (*num_params > 0 && !strcmp(*params, "extend")) extend = True;

  _XmDataFieldDrawInsertionPoint(tf, False);
  df_SetNavigationAnchor(tf, cursorPos, extend);
  df_CompleteNavigation(tf, event, position, event->xkey.time, extend);
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_BackwardChar( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_BackwardChar(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition cursorPos, position;

    cursorPos = XmTextF_cursor_position(tf);

    if (cursorPos > 0) {
       _XmDataFieldDrawInsertionPoint(tf, False);
       position = cursorPos - 1;
       df_SimpleMovement((Widget) tf, event, params, num_params,
		      cursorPos, position);
       _XmDataFieldDrawInsertionPoint(tf, True);
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ForwardChar( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ForwardChar(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition cursorPos, position;

    cursorPos = XmTextF_cursor_position(tf);

    if (cursorPos < XmTextF_string_length(tf)) {
       _XmDataFieldDrawInsertionPoint(tf, False);
       position = cursorPos + 1;
       df_SimpleMovement((Widget) tf, event, params, num_params,
		      cursorPos, position);
       _XmDataFieldDrawInsertionPoint(tf, True);
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_BackwardWord( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_BackwardWord(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmTextPosition cursorPos, position, dummy;

   cursorPos = XmTextF_cursor_position(tf);

   if (cursorPos > 0) {
      _XmDataFieldDrawInsertionPoint(tf, False);
      df_FindPrevWord(tf, &position, &dummy);
      df_SimpleMovement((Widget) tf, event, params, num_params,
		     cursorPos, position);
      _XmDataFieldDrawInsertionPoint(tf, True);
   }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ForwardWord( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ForwardWord(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition cursorPos, position, dummy;
    wchar_t white_space[3];

    if (XmTextF_max_char_size(tf) != 1) {
       (void)mbtowc(&white_space[0], " ", 1);
       (void)mbtowc(&white_space[1], "\n", 1);
       (void)mbtowc(&white_space[2], "\t", 1);
    }

    cursorPos = XmTextF_cursor_position(tf);

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (cursorPos < XmTextF_string_length(tf)) {
       if (XmTextF_max_char_size(tf) == 1) {
         if (isspace((int)(unsigned char)XmTextF_value(tf)[cursorPos]))
	    df_FindWord(tf, cursorPos, &dummy, &position);
         else
            df_FindNextWord(tf, &dummy, &position);
          if(isspace((int)(unsigned char)XmTextF_value(tf)[position])){
	     for (;position < XmTextF_string_length(tf); position++){
	        if (!isspace((int)(unsigned char)XmTextF_value(tf)[position]))
	   	break;
             }
          }
       } else {
	  if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[cursorPos],
				   white_space, 3))
	     df_FindWord(tf, cursorPos, &dummy, &position);
	  else
	     df_FindNextWord(tf, &dummy, &position);
          if (_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[position],
				   white_space, 3)){
	     for (; position < XmTextF_string_length(tf); position++) {
		if (!_XmDataFieldIsWSpace(XmTextF_wc_value(tf)[position], 
					  white_space, 3))
		   break;
	     }
	  }
       }
       df_SimpleMovement((Widget) tf, event, params, num_params,
		      cursorPos, position);
    }
    _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_EndOfLine( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_EndOfLine(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmTextPosition cursorPos, position;

   cursorPos = XmTextF_cursor_position(tf);

   if (cursorPos < XmTextF_string_length(tf)) {
      _XmDataFieldDrawInsertionPoint(tf, False);
      position = XmTextF_string_length(tf);
      df_SimpleMovement((Widget) tf, event, params, num_params,
		     cursorPos, position);
      _XmDataFieldDrawInsertionPoint(tf, True);
   }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_BeginningOfLine( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_BeginningOfLine(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmTextPosition cursorPos, position;

   cursorPos = XmTextF_cursor_position(tf);

   if (cursorPos > 0) {
      position = 0;
      _XmDataFieldDrawInsertionPoint(tf, False);
      df_SimpleMovement((Widget) tf, event, params, num_params,
		     cursorPos, position);
      _XmDataFieldDrawInsertionPoint(tf, True);
   }
}

static void 
#ifdef _NO_PROTO
df_SetSelection( tf, left, right, redisplay )
        XmDataFieldWidget tf ;
        XmTextPosition left ;
        XmTextPosition right ;
        Boolean redisplay ;
#else
df_SetSelection(
        XmDataFieldWidget tf,
        XmTextPosition left,
        XmTextPosition right,
#if NeedWidePrototypes
        int redisplay )
#else
        Boolean redisplay )
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
   XmTextPosition display_left, display_right;
   XmTextPosition old_prim_left, old_prim_right;

   if (left < 0) left = 0;
   if (right < 0) right = 0;

   if (left > XmTextF_string_length(tf))
      left = XmTextF_string_length(tf);
   if (right > XmTextF_string_length(tf))
      right = XmTextF_string_length(tf);

   if (left == right && XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf))
      XmDataFieldSetAddMode((Widget)tf, False);
   if (left == XmTextF_prim_pos_left(tf) && right == XmTextF_prim_pos_right(tf))
      return;

   DataFieldSetHighlight(tf, XmTextF_prim_pos_left(tf),
		         XmTextF_prim_pos_right(tf), XmHIGHLIGHT_NORMAL);

   old_prim_left = XmTextF_prim_pos_left(tf);
   old_prim_right = XmTextF_prim_pos_right(tf);

   if (left > right) {
      XmTextF_prim_pos_left(tf) = right;
      XmTextF_prim_pos_right(tf) = left;
   } else {
      XmTextF_prim_pos_left(tf) = left;
      XmTextF_prim_pos_right(tf) = right;
   }

   DataFieldSetHighlight(tf, XmTextF_prim_pos_left(tf),
	                    XmTextF_prim_pos_right(tf), XmHIGHLIGHT_SELECTED);

   if (redisplay) {
      if (old_prim_left > XmTextF_prim_pos_left(tf)) {
         display_left = XmTextF_prim_pos_left(tf);
      } else if (old_prim_left < XmTextF_prim_pos_left(tf)) {
         display_left = old_prim_left;
      } else
         display_left = (old_prim_right > XmTextF_prim_pos_right(tf)) ?
		        XmTextF_prim_pos_right(tf) : old_prim_right;

      if (old_prim_right < XmTextF_prim_pos_right(tf)) {
         display_right = XmTextF_prim_pos_right(tf);
      } else if (old_prim_right > XmTextF_prim_pos_right(tf)) {
         display_right = old_prim_right;
      } else
         display_right = (old_prim_left < XmTextF_prim_pos_left(tf)) ?
		         XmTextF_prim_pos_left(tf) : old_prim_left;

      df_RedisplayText(tf, display_left, display_right);
   }
   XmTextF_refresh_ibeam_off(tf) = True;
}


/*
 * Begin the selection by gaining ownership of the selection
 * and setting the selection parameters.
 */
void 
#ifdef _NO_PROTO
_XmDataFieldStartSelection( tf, left, right, sel_time )
        XmDataFieldWidget tf ;
        XmTextPosition left ;
        XmTextPosition right ;
        Time sel_time ;
#else
_XmDataFieldStartSelection(
        XmDataFieldWidget tf,
        XmTextPosition left,
        XmTextPosition right,
        Time sel_time )
#endif /* _NO_PROTO */
{
  if (!XtIsRealized((Widget)tf)) return;

  /* if we don't already own the selection */
  if (!XmTextF_has_primary(tf)) {
    /*
     * Try to gain ownership. This function identifies the
     * XtConvertSelectionProc and the XtLoseSelectionProc.
     */
     if (XtOwnSelection((Widget)tf, XA_PRIMARY, sel_time, _XmDataFieldConvert, 
		      _XmDataFieldLoseSelection, (XtSelectionDoneProc) NULL)) {
       XmAnyCallbackStruct cb;

       XmTextF_prim_time(tf) = sel_time;
       _XmDataFieldDrawInsertionPoint(tf, False);
       XmTextF_has_primary(tf) = True; 
       XmTextF_prim_pos_left(tf) = XmTextF_prim_pos_right(tf) =
			   XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
      /*
       * Set the selection boundries for highlighting the text,
       * and marking the selection.
       */
       df_SetSelection(tf, left, right, True);

       _XmDataFieldDrawInsertionPoint(tf, True);

      /* Call the gain selection callback */
       cb.reason = XmCR_GAIN_PRIMARY;
       cb.event = NULL;
       XtCallCallbackList((Widget) tf, XmTextF_gain_primary_callback(tf), 
			  (XtPointer) &cb);

    } else 
     /*
      * Failed to gain ownership of the selection so make sure
      * the text does not think it owns the selection.
      * (this might be overkill)
      */
       _XmDataFieldDeselectSelection((Widget)tf, True, sel_time);
  } else {
       _XmDataFieldDrawInsertionPoint(tf, False);
       XmDataFieldSetHighlight((Widget)tf, XmTextF_prim_pos_left(tf),
		          XmTextF_prim_pos_right(tf), XmHIGHLIGHT_NORMAL);
       XmTextF_prim_pos_left(tf) = XmTextF_prim_pos_right(tf) =
			   XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
      /*
       * Set the new selection boundries for highlighting the text,
       * and marking the selection.
       */
       df_SetSelection(tf, left, right, True);

       _XmDataFieldDrawInsertionPoint(tf, True);
  }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ProcessHorizontalParams( w, event, params, num_params, left, right, position )
        Widget w ;
        XEvent *event ;
        char **params ;
	Cardinal *num_params;
	XmTextPosition *left ;
	XmTextPosition *right ;
	XmTextPosition *position ;
#else
df_ProcessHorizontalParams(
        Widget w,
        XEvent *event,
        char **params,
	Cardinal *num_params,
	XmTextPosition *left,
	XmTextPosition *right,
        XmTextPosition *position )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition old_cursorPos = XmTextF_cursor_position(tf);

    *position = XmTextF_cursor_position(tf);

    if (!XmDataFieldGetSelectionPosition(w, left, right) || *left == *right) {
        XmTextF_orig_left(tf) = XmTextF_orig_right(tf) = XmTextF_prim_anchor(tf);
        *left = *right = old_cursorPos;
    }

    if (*num_params > 0 && !strcmp(*params, "right")) {
       if (*position >= XmTextF_string_length(tf)) return;
       (*position)++;
    } else if (*num_params > 0 && !strcmp(*params, "left")) {
       if (*position <= 0) return;
       (*position)--;
    }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ProcessSelectParams( w, event, left, right, position )
        Widget w ;
        XEvent *event ;
        XmTextPosition *left ;
        XmTextPosition *right ;
        XmTextPosition *position ;
#else
df_ProcessSelectParams(
        Widget w,
        XEvent *event,
        XmTextPosition *left,
        XmTextPosition *right,
        XmTextPosition *position )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   *position = XmTextF_cursor_position(tf);

   if (!XmDataFieldGetSelectionPosition(w, left, right) || *left == *right) {
      if (*position > XmTextF_prim_anchor(tf)) {
        *left = XmTextF_prim_anchor(tf);
        *right = *position;
      } else {
        *left = *position;
        *right = XmTextF_prim_anchor(tf);
      }
   }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_KeySelection( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_KeySelection(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmTextPosition position, left, right;
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition cursorPos;

  _XmDataFieldDrawInsertionPoint(tf,False); /* Turn off I beam blink
					       during selection */

  XmTextF_orig_left(tf) = XmTextF_prim_pos_left(tf);
  XmTextF_orig_right(tf) = XmTextF_prim_pos_right(tf);

  cursorPos = XmTextF_cursor_position(tf);
  if (*num_params > 0 && (!strcmp(*params,"right") || !strcmp(*params, "left")))
     df_SetAnchorBalancing(tf, cursorPos);

  XmTextF_extending(tf) = True;

  if (*num_params == 0) {
     position = cursorPos;
     df_ProcessSelectParams(w, event, &left, &right, &position);
  } else if (*num_params > 0 && (!strcmp(*params, "right") ||
				 !strcmp(*params, "left"))) {
     df_ProcessHorizontalParams(w, event, params, num_params, &left,
			     &right, &position);
  }

  cursorPos = position;

  if (position < 0 || position > XmTextF_string_length(tf)) {
     _XmDataFieldDrawInsertionPoint(tf,True); /* Turn on I beam now
						 that we are done */
     return;
  }

 /* shift anchor and direction to opposite end of the selection */
  if (position > XmTextF_prim_anchor(tf)) {
     right = cursorPos = position;
     left = XmTextF_prim_anchor(tf);
  } else {
     left = cursorPos = position;
     right = XmTextF_prim_anchor(tf);
  }

  if (left > right) {
     XmTextPosition tempIndex = left;
     left = right;
     right = tempIndex;
  }

  if (XmTextF_has_primary(tf))
     df_SetSelection(tf, left, right, True);
  else
     _XmDataFieldStartSelection(tf, left, right, event->xbutton.time);

  XmTextF_pending_off(tf) = False;

  _XmDataFielddf_SetCursorPosition(tf, event, cursorPos, True, True);
  (void) df_SetDestination(w, cursorPos, False, event->xkey.time);

  XmTextF_orig_left(tf) = XmTextF_prim_pos_left(tf);
  XmTextF_orig_right(tf) = XmTextF_prim_pos_right(tf);

  _XmDataFieldDrawInsertionPoint(tf,True); /* Turn on I beam now
					      that we are done */

}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TextFocusIn( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TextFocusIn(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmAnyCallbackStruct cb;
   XPoint xmim_point;
   XtWidgetProc bhl;

   if (event->xfocus.send_event && !(XmTextF_has_focus(tf))) {
      if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
      XmTextF_has_focus(tf) = True;
      if (XtIsSensitive(w)) _XmDataFToggleCursorGC(w);
      _XmDataFieldDrawInsertionPoint(tf, False);
      XmTextF_blink_on(tf) = False;

      XmTextF_refresh_ibeam_off(tf) = True;
      
      if (_XmGetFocusPolicy(w) == XmEXPLICIT) {

         _XmProcessLock(); 
         bhl = ((XmDataFieldWidgetClass)XtClass(w))->primitive_class.border_highlight;
         _XmProcessUnlock();

         if (bhl)
         {   
            (*bhl)(w);
         } 

         if (!XmTextF_has_destination(tf))
         {
            (void) df_SetDestination(w, XmTextF_cursor_position(tf), False, XtLastTimestampProcessed(XtDisplay(w)));
         }
      }
      if (tf->core.sensitive) df_ChangeBlinkBehavior(tf, True);
      _XmDataFieldDrawInsertionPoint(tf, True);
      (void) df_GetXYFromPos(tf, XmTextF_cursor_position(tf),
			  &xmim_point.x, &xmim_point.y);
      XmImVaSetFocusValues(w, XmNspotLocation, &xmim_point, NULL);

      cb.reason = XmCR_FOCUS;
      cb.event = event;
      XtCallCallbackList (w, XmTextF_focus_callback(tf), (XtPointer) &cb);
   }

   _XmPrimitiveFocusIn(w, event, params, num_params);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TextFocusOut( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TextFocusOut(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XtWidgetProc buhl;

   if (event->xfocus.send_event && XmTextF_has_focus(tf)) {
      XmTextF_has_focus(tf) = False;
      df_ChangeBlinkBehavior(tf, False);
      _XmDataFieldDrawInsertionPoint(tf, False);
      _XmDataFToggleCursorGC(w);
      XmTextF_blink_on(tf) = True;
      _XmDataFieldDrawInsertionPoint(tf, True);

      _XmProcessLock();
      buhl = ((XmDataFieldWidgetClass) XtClass(tf))->primitive_class.border_unhighlight;
      _XmProcessUnlock();

      if(buhl)
      {
          (*buhl)( (Widget) tf) ;
      } 
      XmImUnsetFocus(w);
   }

   /* If traversal is on, then the leave verification callback is called in
      the traversal event handler */
   if (event->xfocus.send_event && !XmTextF_traversed(tf) &&
       _XmGetFocusPolicy(w) == XmEXPLICIT) {
        if (!df_VerifyLeave(tf, event)) {
           if (XmTextF_verify_bell(tf)) XBell(XtDisplay(w), 0);
           return;
        }
   } else
        if (XmTextF_traversed(tf)) {
	   XmTextF_traversed(tf) = False;
        }
}

static void 
#ifdef _NO_PROTO
df_SetScanIndex( tf, event )
        XmDataFieldWidget tf ;
        XEvent *event ;
#else
df_SetScanIndex(
        XmDataFieldWidget tf,
        XEvent *event )
#endif /* _NO_PROTO */
{
   Time sel_time;

   if (event->type == ButtonPress) sel_time = event->xbutton.time;
   else sel_time = event->xkey.time;
	
	
   if (sel_time > XmTextF_last_time(tf) &&
	sel_time - XmTextF_last_time(tf) < XtGetMultiClickTime(XtDisplay(tf))) {
/*
 * Fix for HaL DTS 9841 - Increment the sarray_index first, then check to 
 *			  see if it is greater that the count.  Otherwise,
 *			  an error will occur.
 */
       XmTextF_sarray_index(tf)++;
       if (XmTextF_sarray_index(tf) >= XmTextF_selection_array_count(tf)) {
	  XmTextF_sarray_index(tf) = 0;
       }
/*
 * End fix for HaL DTS 9841
 */
    } else
       XmTextF_sarray_index(tf) = 0;

    XmTextF_last_time(tf) = sel_time;
}
    
static void 
#ifdef _NO_PROTO
df_ExtendScanSelection( tf, event )
        XmDataFieldWidget tf ;
        XEvent *event ;
#else
df_ExtendScanSelection(
        XmDataFieldWidget tf,
        XEvent *event )
#endif /* _NO_PROTO */
{
   XmTextPosition pivot_left, pivot_right;
   XmTextPosition left, right;
   XmTextPosition new_position = df_GetPosFromX(tf, (Position) event->xbutton.x);
   XmTextPosition cursorPos = XmTextF_cursor_position(tf);
   Boolean pivot_modify = False;
   float bal_point;

   if (!XmDataFieldGetSelectionPosition((Widget)tf, &left, &right) ||
       left == right) {
       XmTextF_orig_left(tf) = XmTextF_orig_right(tf) =
	   XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
       bal_point = (float)XmTextF_orig_left(tf);
   } else
        bal_point = (float)(((float)(right - left) / 2.0) + (float)left);

   if (!XmTextF_extending(tf))
   {
      if ((float)new_position < bal_point) {
         XmTextF_prim_anchor(tf) = XmTextF_orig_right(tf);
      } else if ((float)new_position > bal_point) {
         XmTextF_prim_anchor(tf) = XmTextF_orig_left(tf);
      }
  }

   XmTextF_extending(tf) = True;

   switch (XmTextF_selection_array(tf)[XmTextF_sarray_index(tf)]) {
       case XmSELECT_POSITION:
      	   if (XmTextF_has_primary(tf))
	      df_SetSelection(tf, XmTextF_prim_anchor(tf), new_position, True);
           else if (new_position != XmTextF_prim_anchor(tf))
     	      _XmDataFieldStartSelection(tf, XmTextF_prim_anchor(tf),
			     new_position, event->xbutton.time);
           XmTextF_pending_off(tf) = False;
           cursorPos = new_position;
           break;
       case XmSELECT_WHITESPACE:
       case XmSELECT_WORD:
	   df_FindWord(tf, new_position, &left, &right);
           df_FindWord(tf, XmTextF_prim_anchor(tf),
		    &pivot_left, &pivot_right);
           XmTextF_pending_off(tf) = False;
           if (left != pivot_left || right != pivot_right) {
              if (left > pivot_left)
                 left = pivot_left;
              if (right < pivot_right)
                 right = pivot_right;
              pivot_modify = True;
           }
      	   if (XmTextF_has_primary(tf))
              df_SetSelection(tf, left, right, True);
      	   else
     	      _XmDataFieldStartSelection(tf, left, right, event->xbutton.time);

           if (pivot_modify) {
              if ((((right - left) / 2) + left) <= new_position) {
                 cursorPos = right;
              } else
                 cursorPos = left;
           } else {
	      if (left >= XmTextF_cursor_position(tf))
                 cursorPos = left;
              else
                 cursorPos = right;
           }
           break;
       default:
	   break;
   }
   if (cursorPos != XmTextF_cursor_position(tf)) {
      (void) df_SetDestination((Widget)tf, cursorPos, False, event->xkey.time);
      _XmDataFielddf_SetCursorPosition(tf, event, cursorPos, True, True);
   }
}

static void 
#ifdef _NO_PROTO
df_SetScanSelection( tf, event )
        XmDataFieldWidget tf ;
        XEvent *event ;
#else
df_SetScanSelection(
        XmDataFieldWidget tf,
        XEvent *event )
#endif /* _NO_PROTO */
{
   XmTextPosition left, right;
   XmTextPosition new_position = 0;
   XmTextPosition cursorPos = XmTextF_cursor_position(tf);
   Position dummy = 0;
   Boolean update_position = False;
  
   df_SetScanIndex(tf, event);

   if (event->type == ButtonPress)
       new_position = df_GetPosFromX(tf, (Position) event->xbutton.x);
   else
       new_position = XmTextF_cursor_position(tf);

   _XmDataFieldDrawInsertionPoint(tf,False); /* Turn off I beam
						blink during selection */

   switch (XmTextF_selection_array(tf)[XmTextF_sarray_index(tf)]) {
       case XmSELECT_POSITION:
           XmTextF_prim_anchor(tf) = new_position;
      	   if (XmTextF_has_primary(tf)) {
              df_SetSelection(tf, new_position, new_position, True);
              XmTextF_pending_off(tf) = False;
           }
           cursorPos = new_position;
	   update_position = True;
           break;
       case XmSELECT_WHITESPACE:
       case XmSELECT_WORD:
	   df_FindWord(tf, XmTextF_cursor_position(tf), &left, &right);
      	   if (XmTextF_has_primary(tf))
              df_SetSelection(tf, left, right, True);
      	   else
     	      _XmDataFieldStartSelection(tf, left, right, event->xbutton.time);
           XmTextF_pending_off(tf) = False;
           if ((((right - left) / 2) + left) <= new_position)
              cursorPos = right;
           else
              cursorPos = left;
           break;
       case XmSELECT_LINE:
       case XmSELECT_PARAGRAPH:
       case XmSELECT_ALL:
      	   if (XmTextF_has_primary(tf))
              df_SetSelection(tf, 0, XmTextF_string_length(tf), True);
      	   else
              _XmDataFieldStartSelection(tf, 0, XmTextF_string_length(tf),
			     event->xbutton.time);
           XmTextF_pending_off(tf) = False;
   	   if (event->type == ButtonPress)
           {
              if ((XmTextF_string_length(tf)) / 2 <= new_position)
                 cursorPos = XmTextF_string_length(tf);
              else
                 cursorPos = 0;
          }
           break;
       case XmSELECT_OUT_LINE:
           break;
   }

   (void) df_SetDestination((Widget)tf, cursorPos, False, event->xkey.time);
   if (cursorPos != XmTextF_cursor_position(tf) || update_position) {
      _XmDataFielddf_SetCursorPosition(tf, event, cursorPos, True, True);
   }
   df_GetXYFromPos(tf, cursorPos, &(XmTextF_select_pos_x(tf)),
                &dummy);
   _XmDataFieldDrawInsertionPoint(tf,True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_StartPrimary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_StartPrimary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;

  if (!XmTextF_has_focus(tf) && _XmGetFocusPolicy(w) == XmEXPLICIT)
     (void) XmProcessTraversal(w, XmTRAVERSE_CURRENT);

  _XmDataFieldDrawInsertionPoint(tf,False);
  df_SetScanSelection(tf, event); /* use scan type to set the selection */
  _XmDataFieldDrawInsertionPoint(tf,True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_MoveDestination( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_MoveDestination(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition left, right;
  XmTextPosition new_position;
  Boolean old_has_focus = XmTextF_has_focus(tf);
  Boolean reset_cursor = False;

  new_position = df_GetPosFromX(tf, (Position) event->xbutton.x);

  _XmDataFieldDrawInsertionPoint(tf, False);
  if (XmDataFieldGetSelectionPosition(w, &left, &right) && (right != left))
     (void) df_SetDestination(w, new_position, False, event->xbutton.time);

  XmTextF_pending_off(tf) = False;

  if (!XmTextF_has_focus(tf) && _XmGetFocusPolicy(w) == XmEXPLICIT)
     (void) XmProcessTraversal(w, XmTRAVERSE_CURRENT);

  /* Doing the the df_MoveDestination caused a traversal into my, causing
   * me to gain focus... Cursor is now on when it shouldn't be. */
  if ((reset_cursor = !old_has_focus && XmTextF_has_focus(tf)) != False)
     _XmDataFieldDrawInsertionPoint(tf, False);

  _XmDataFielddf_SetCursorPosition(tf, event, new_position,
				True, True);
  if (new_position < left && new_position > right)
     XmTextF_pending_off(tf) = True;

  /*
   * if cursor was turned off as a result of the focus state changing
   * then we need to undo the decrement to the cursor_on variable
   * by redrawing the insertion point.
   */
  if (reset_cursor)
     _XmDataFieldDrawInsertionPoint(tf, True);
  _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ExtendPrimary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ExtendPrimary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;

  if (XmTextF_cancel(tf)) return;

  _XmDataFieldDrawInsertionPoint(tf, False);
  XmTextF_do_drop(tf) = False;

  if (!df_CheckTimerScrolling(w, event)){
     if (event->type == ButtonPress)
        df_DoExtendedSelection(w, event->xbutton.time);
     else
        df_DoExtendedSelection(w, event->xkey.time);
  } else
     df_ExtendScanSelection(tf, event); /* use scan type to set the selection */

  _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ExtendEnd( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ExtendEnd(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;


  if (XmTextF_prim_pos_left(tf) == 0 && XmTextF_prim_pos_right(tf) == 0)
     XmTextF_orig_left(tf) = XmTextF_orig_right(tf) = XmTextF_cursor_position(tf);
  else {
     XmTextF_orig_left(tf) = XmTextF_prim_pos_left(tf);
     XmTextF_orig_right(tf) = XmTextF_prim_pos_right(tf);
     XmTextF_cancel(tf) = False;
  }

  if (XmTextF_select_id(tf)) {
     XtRemoveTimeOut(XmTextF_select_id(tf));
     XmTextF_select_id(tf) = 0;
  }
    XmTextF_select_pos_x(tf) = 0;
    XmTextF_extending(tf) = False;
}

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DoExtendedSelection(w, time)
        Widget w;
        Time time;
#else
df_DoExtendedSelection(
        Widget w,
        Time time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition position, left, right, cursorPos;
    XmTextPosition pivot_left, pivot_right;
    Boolean pivot_modify = False;
    float bal_point;

    if (XmTextF_cancel(tf)) {
          if (XmTextF_select_id(tf)) XtRemoveTimeOut(XmTextF_select_id(tf));
          XmTextF_select_id(tf) = 0;
          return;
    }

    cursorPos = XmTextF_cursor_position(tf);
    _XmDataFieldDrawInsertionPoint(tf, False);
    if (!(XmDataFieldGetSelectionPosition(w, &left, &right)) || left == right) {
        XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
        left = right = XmTextF_cursor_position(tf);
        XmTextF_orig_left(tf) = XmTextF_orig_right(tf) = XmTextF_prim_anchor(tf);
        bal_point = (float)XmTextF_prim_anchor(tf);
    } else
        bal_point = (float)(((float)(XmTextF_orig_right(tf) - XmTextF_orig_left(tf))
                                     / 2.0) + (float)XmTextF_orig_left(tf));

    position = XmDataFieldXYToPos(w, XmTextF_select_pos_x(tf), 0);

   if (!XmTextF_extending(tf))
   {
      if ((float)position < bal_point) {
         XmTextF_prim_anchor(tf) = XmTextF_orig_right(tf);
      } else if ((float)position > bal_point) {
         XmTextF_prim_anchor(tf) = XmTextF_orig_left(tf);
      }
  }
   XmTextF_extending(tf) = True;

    /* Extend selection in same way as ExtendScan would do */

   switch (XmTextF_selection_array(tf)[XmTextF_sarray_index(tf)]) {
       case XmSELECT_POSITION:
           if (XmTextF_has_primary(tf))
              df_SetSelection(tf, XmTextF_prim_anchor(tf), position, True);
           else if (position != XmTextF_prim_anchor(tf))
              _XmDataFieldStartSelection(tf, XmTextF_prim_anchor(tf),
                             position, time);
           XmTextF_pending_off(tf) = False;
           cursorPos = position;
           break;
       case XmSELECT_WHITESPACE:
       case XmSELECT_WORD:
           df_FindWord(tf, position, &left, &right);
           df_FindWord(tf, XmTextF_prim_anchor(tf),
                    &pivot_left, &pivot_right);
           XmTextF_pending_off(tf) = False;
           if (left != pivot_left || right != pivot_right) {
              if (left > pivot_left)
                 left = pivot_left;
              if (right < pivot_right)
                 right = pivot_right;
              pivot_modify = True;
           }
           if (XmTextF_has_primary(tf))
              df_SetSelection(tf, left, right, True);
           else
              _XmDataFieldStartSelection(tf, left, right, time);

           if (pivot_modify) {
              if ((((right - left) / 2) + left) <= position) {
                 cursorPos = right;
              } else
                 cursorPos = left;
           } else {
              if (left >= XmTextF_cursor_position(tf))
                 cursorPos = left;
              else
                 cursorPos = right;
           }
           break;
       default:
           break;
   }
   if (cursorPos != XmTextF_cursor_position(tf)) {
      (void) df_SetDestination((Widget)tf, cursorPos, False, time);
      _XmDataFielddf_SetCursorPosition(tf, NULL, cursorPos, True, True);
   }
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DoSecondaryExtend(w, ev_time)
        Widget w;
        Time ev_time;
#else
df_DoSecondaryExtend(
        Widget w,
        Time ev_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    XmTextPosition position = XmDataFieldXYToPos(w, XmTextF_select_pos_x(tf), 0);

    if (XmTextF_cancel(tf)) return;

    if (position < XmTextF_sec_anchor(tf)) {
       if (XmTextF_sec_pos_left(tf) > 0)
          _XmDataFieldSetSel2(w, position, XmTextF_sec_anchor(tf), False, ev_time);
       XmDataFieldShowPosition(w, XmTextF_sec_pos_left(tf));
    } else if (position > XmTextF_sec_anchor(tf)) {
       if (XmTextF_sec_pos_right(tf) < XmTextF_string_length(tf))
       _XmDataFieldSetSel2(w, XmTextF_sec_anchor(tf), position, False, ev_time);
       XmDataFieldShowPosition(w, XmTextF_sec_pos_right(tf));
    } else {
       _XmDataFieldSetSel2(w, position, position, False, ev_time);
       XmDataFieldShowPosition(w, position);
    }
    df_ResetClipOrigin(tf, False);

    XmTextF_sec_extending(tf) = True;
}



/************************************************************************
 *                                                                      *
 * df_BrowseScroll - timer proc that scrolls the list if the user has left *
 *              the window with the button down. If the button has been *
 *              released, call the standard click stuff.                *
 *                                                                      *
 ************************************************************************/
/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_BrowseScroll( closure, id )
        XtPointer closure ;
        XtIntervalId *id ;
#else
df_BrowseScroll(
        XtPointer closure,
        XtIntervalId *id )
#endif /* _NO_PROTO */
{
    Widget w = (Widget) closure ;
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (XmTextF_cancel(tf)) {
       XmTextF_select_id(tf) = 0;
       return;
    }

    if (!XmTextF_select_id(tf)) return;

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (XmTextF_sec_extending(tf))
      df_DoSecondaryExtend(w, XtLastTimestampProcessed(XtDisplay(w)));
    else if (XmTextF_extending(tf))
      df_DoExtendedSelection(w, XtLastTimestampProcessed(XtDisplay(w)));

    XSync (XtDisplay(w), False);

    _XmDataFieldDrawInsertionPoint(tf, True);

    XmTextF_select_id(tf) = XtAppAddTimeOut(XtWidgetToApplicationContext(w),
                                 (unsigned long) PRIM_SCROLL_INTERVAL,
                                 df_BrowseScroll, (XtPointer) w);
}


/* ARGSUSED */
static Boolean
#ifdef _NO_PROTO
df_CheckTimerScrolling( w, event )
        Widget w ;
        XEvent *event ;
#else
df_CheckTimerScrolling(
        Widget w,
        XEvent *event )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Dimension margin_size = XmTextF_margin_width(tf) +
                               tf->primitive.shadow_thickness +
                               tf->primitive.highlight_thickness;
    Dimension top_margin = XmTextF_margin_height(tf) +
                            tf->primitive.shadow_thickness +
                            tf->primitive.highlight_thickness;

    XmTextF_select_pos_x(tf) = event->xmotion.x;

    if ((event->xmotion.x > (int) margin_size) &&
      (event->xmotion.x < (int) (tf->core.width - margin_size))  &&
      (event->xmotion.y > (int) top_margin) &&
        (event->xmotion.y < (int) (top_margin + XmTextF_font_ascent(tf) +
                                 XmTextF_font_descent(tf)))) {

       if (XmTextF_select_id(tf)) {
          XtRemoveTimeOut(XmTextF_select_id(tf));
          XmTextF_select_id(tf) = 0;
       }
    } else {
       /* to the left of the text */
        if (event->xmotion.x <= (int) margin_size)
           XmTextF_select_pos_x(tf) = (Position) (margin_size -
                                          (XmTextF_average_char_width(tf) + 1));
       /* to the right of the text */
      else if (event->xmotion.x >= (int) (tf->core.width - margin_size))
           XmTextF_select_pos_x(tf) = (Position) ((tf->core.width - margin_size) +
                                           XmTextF_average_char_width(tf) + 1);
       if (!XmTextF_select_id(tf))
          XmTextF_select_id(tf) = XtAppAddTimeOut(XtWidgetToApplicationContext(w),
                                       (unsigned long) SEC_SCROLL_INTERVAL,
                                       df_BrowseScroll, (XtPointer) w);
       return True;
    }
    return False;
}

static void 
#ifdef _NO_PROTO
df_RestorePrimaryHighlight( tf, prim_left, prim_right )
        XmDataFieldWidget tf ;
        XmTextPosition prim_left ;
        XmTextPosition prim_right ;
#else
df_RestorePrimaryHighlight(
        XmDataFieldWidget tf,
        XmTextPosition prim_left,
        XmTextPosition prim_right )
#endif /* _NO_PROTO */
{
   if (XmTextF_sec_pos_right(tf) >= prim_left &&
       XmTextF_sec_pos_right(tf) <= prim_right) {
     /* secondary selection is totally inside primary selection */
      if (XmTextF_sec_pos_left(tf) >= prim_left) {
         DataFieldSetHighlight(tf, prim_left, XmTextF_sec_pos_left(tf),
                            XmHIGHLIGHT_SELECTED);
         DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf),
                               XmTextF_sec_pos_right(tf),
                               XmHIGHLIGHT_NORMAL);
         DataFieldSetHighlight(tf, XmTextF_sec_pos_right(tf), prim_right,
                               XmHIGHLIGHT_SELECTED);
     /* right side of secondary selection is inside primary selection */
      } else {
         DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf), prim_left,
                               XmHIGHLIGHT_NORMAL);
         DataFieldSetHighlight(tf, prim_left, XmTextF_sec_pos_right(tf),
                               XmHIGHLIGHT_SELECTED);
      }
   } else {
     /* left side of secondary selection is inside primary selection */
      if (XmTextF_sec_pos_left(tf) <= prim_right &&
	  XmTextF_sec_pos_left(tf) >= prim_left) {
         DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf), prim_right,
                               XmHIGHLIGHT_SELECTED);
         DataFieldSetHighlight(tf, prim_right, XmTextF_sec_pos_right(tf),
                               XmHIGHLIGHT_NORMAL);
      } else  {
       /* secondary selection encompasses the primary selection */
        if (XmTextF_sec_pos_left(tf) <= prim_left &&
            XmTextF_sec_pos_right(tf) >= prim_right){
           DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf), prim_left,
                                 XmHIGHLIGHT_NORMAL);
           DataFieldSetHighlight(tf, prim_left, prim_right,
                                 XmHIGHLIGHT_SELECTED);
           DataFieldSetHighlight(tf, prim_right, XmTextF_sec_pos_right(tf),
                                 XmHIGHLIGHT_NORMAL);
     /* secondary selection is outside primary selection */
        } else {
           DataFieldSetHighlight(tf, prim_left, prim_right,
                                 XmHIGHLIGHT_SELECTED);
           DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf),
                                 XmTextF_sec_pos_right(tf),
                                 XmHIGHLIGHT_NORMAL);
        }
      }
   }
}

void 
#ifdef _NO_PROTO
_XmDataFieldSetSel2( w, left, right, disown, sel_time )
        Widget w ;
        XmTextPosition left ;
        XmTextPosition right ;
        Boolean disown ;
        Time sel_time ;
#else
_XmDataFieldSetSel2(
        Widget w,
        XmTextPosition left,
        XmTextPosition right,
        Boolean disown,
        Time sel_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Boolean result;

    if (XmTextF_has_secondary(tf)) {
       XmTextPosition prim_left, prim_right;

       if (left == XmTextF_sec_pos_left(tf) && right == XmTextF_sec_pos_right(tf))
          return;

      /* If the widget has the primary selection, make sure the selection
       * highlight is restored appropriately.
       */
       if (XmDataFieldGetSelectionPosition(w, &prim_left, &prim_right))
          df_RestorePrimaryHighlight(tf, prim_left, prim_right);
       else
          DataFieldSetHighlight(tf, XmTextF_sec_pos_left(tf),
		                  XmTextF_sec_pos_right(tf), XmHIGHLIGHT_NORMAL);
    }

    if (left < right) {
       if (!XmTextF_has_secondary(tf)) {
          result = XtOwnSelection(w, XA_SECONDARY, sel_time, 
				  _XmDataFieldConvert,
			          _XmDataFieldLoseSelection,
				  (XtSelectionDoneProc) NULL);
          XmTextF_sec_time(tf) = sel_time;
          XmTextF_has_secondary(tf) = result;
          if (result) {
             XmTextF_sec_pos_left(tf) = left;
             XmTextF_sec_pos_right(tf) = right;
          } 
       } else {
          XmTextF_sec_pos_left(tf) = left;
          XmTextF_sec_pos_right(tf) = right;
       }
       XmTextF_sec_drag(tf) = True;
   } else {
       XmTextF_sec_pos_left(tf) = XmTextF_sec_pos_right(tf) = left;
       if (disown) {
          XtDisownSelection(w, XA_SECONDARY, sel_time);
          XmTextF_has_secondary(tf) = False;
       }
   }

   DataFieldSetHighlight((XmDataFieldWidget) w, XmTextF_sec_pos_left(tf),
		      XmTextF_sec_pos_right(tf), XmHIGHLIGHT_SECONDARY_SELECTED);

  /* This can be optimized for performance enhancement */

    df_RedisplayText(tf, 0, XmTextF_string_length(tf));
}

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_StartDrag( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        String *params ;
        Cardinal *num_params ;
#else
df_StartDrag(
        Widget w,
        XEvent *event,
        String *params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Atom targets[4];
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    XTextProperty tmp_prop;
    int status = 0;
    Cardinal num_targets = 0;
    Widget drag_icon;
    Arg args[10];
    int n;

    tmp_prop.value = NULL;
    status = XmbTextListToTextProperty(XtDisplay(w), &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       targets[num_targets++] = tmp_prop.encoding;
    else
       targets[num_targets++] = 99999; /* XmbTextList...  should never fail
                                        * for XPCS characters.  But just in
                                        * case someones Xlib is broken,
                                        * this prevents a core dump.
                                        */
    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

    targets[num_targets++] = XmInternAtom(XtDisplay(w), "COMPOUND_TEXT", False);
    targets[num_targets++] = XA_STRING;
    targets[num_targets++] = XmInternAtom(XtDisplay(w), "TEXT", False);

    drag_icon = _XmGetTextualDragIcon(w);

    n = 0;
    XtSetArg(args[n], XmNcursorBackground, tf->core.background_pixel);  n++;
    XtSetArg(args[n], XmNcursorForeground, tf->primitive.foreground);  n++;
    XtSetArg(args[n], XmNsourceCursorIcon, drag_icon);  n++;
    XtSetArg(args[n], XmNexportTargets, targets);  n++;
    XtSetArg(args[n], XmNnumExportTargets, num_targets);  n++;
    XtSetArg(args[n], XmNconvertProc, _XmDataFieldConvert);  n++;
    XtSetArg(args[n], XmNclientData, w);  n++;
    if (XmTextF_editable(tf)) {
       XtSetArg(args[n], XmNdragOperations, (XmDROP_MOVE | XmDROP_COPY)); n++;
    } else {
       XtSetArg(args[n], XmNdragOperations, XmDROP_COPY); n++;
    }
    (void) XmDragStart(w, event, args, n);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_StartSecondary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_StartSecondary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition position = df_GetPosFromX(tf, (Position) event->xbutton.x);
  int status;

  XmTextF_sec_anchor(tf) = position;
  XmTextF_selection_move(tf) = FALSE;

  status = XtGrabKeyboard(w, False, GrabModeAsync, GrabModeAsync,
			  event->xbutton.time);

  if (status != GrabSuccess)
     XmeWarning(w, GRABKBDERROR);
}


/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_ProcessBDrag( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ProcessBDrag(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition position, left, right;
    Position left_x, right_x, dummy;

    position = df_GetPosFromX(tf, (Position) event->xbutton.x);

    XmTextF_sec_pos_left(tf) = position;

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (XmDataFieldGetSelectionPosition(w, &left, &right) && 
	left != right) {
        if ((position > left && position < right) ||
	  /* Take care of border conditions */
	   (position == left &&
            df_GetXYFromPos(tf, left, &left_x, &dummy) &&
	    event->xbutton.x > left_x) ||
	   (position == right &&
            df_GetXYFromPos(tf, right, &right_x, &dummy) &&
	    event->xbutton.x < right_x)) {
           XmTextF_sel_start(tf) = False;
           df_StartDrag(w, event, params, num_params);
	} else {
	   XmTextF_sel_start(tf) = True;
	   XAllowEvents(XtDisplay(w), AsyncBoth, event->xbutton.time);
	   df_StartSecondary(w, event, params, num_params);
	}
    } else {
       XmTextF_sel_start(tf) = True;
       XAllowEvents(XtDisplay(w), AsyncBoth, event->xbutton.time);
       df_StartSecondary(w, event, params, num_params);
    }
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ExtendSecondary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ExtendSecondary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XmTextPosition position = df_GetPosFromX(tf, (Position) event->xbutton.x);

  if (XmTextF_cancel(tf)) return;

  _XmDataFieldDrawInsertionPoint(tf, False);
  if (position < XmTextF_sec_anchor(tf)) {
     _XmDataFieldSetSel2(w, position, XmTextF_sec_anchor(tf),
			 False, event->xbutton.time);
  } else if (position > XmTextF_sec_anchor(tf)) {
     _XmDataFieldSetSel2(w, XmTextF_sec_anchor(tf), position, 
			 False, event->xbutton.time);
  } else {
     _XmDataFieldSetSel2(w, position, position, False, event->xbutton.time);
  }

  XmTextF_sec_extending(tf) = True;

  if (!df_CheckTimerScrolling(w, event))
     df_DoSecondaryExtend(w, event->xmotion.time);

  _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DoStuff( w, closure, seltype, type, value, length, format )
        Widget w ;
        XtPointer closure ;
        Atom *seltype ;
        Atom *type ;
        XtPointer value ;
        unsigned long *length ;
        int *format ;
#else
df_DoStuff(
        Widget w,
        XtPointer closure,
        Atom *seltype,
        Atom *type,
        XtPointer value,
        unsigned long *length,
        int *format )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    _XmTextPrimSelect *prim_select = (_XmTextPrimSelect *) closure;
    Atom NULL_ATOM = XmInternAtom(XtDisplay(w), "NULL", False);
    XmTextPosition right, left;
    int prim_char_length = 0;
    Boolean replace_res = False;
    XTextProperty tmp_prop;
    int i, status;
    int malloc_size;
    int num_vals;
    char **tmp_value;
    XmAnyCallbackStruct cb;

    if (!XmTextF_has_focus(tf) && _XmGetFocusPolicy(w) == XmEXPLICIT)
       (void) XmProcessTraversal(w, XmTRAVERSE_CURRENT);

    if (!(*length) && *type != NULL_ATOM ) {
      /* Backwards compatibility for 1.0 Selections */
       if (prim_select->target == XmInternAtom(XtDisplay(w), "TEXT", False)) {
          prim_select->target = XA_STRING;
          XtGetSelectionValue(w, XA_PRIMARY, XA_STRING, df_DoStuff,
                           (XtPointer)prim_select, prim_select->time);
       }
       XtFree((char *)value);
       value = NULL;
       return;
    }

   /* if length == 0 and *type is the NULL atom we are assuming
    * that a DELETE target is requested.
    */
    if (*type == NULL_ATOM ) {
       if (prim_select->num_chars > 0 && XmTextF_selection_move(tf)) {
          prim_char_length = prim_select->num_chars;
          XmDataFieldSetSelection(w, prim_select->position,
				  prim_select->position + prim_char_length,
				  prim_select->time);
          XmTextF_prim_anchor(tf) = prim_select->position;
          (void) df_SetDestination(w, XmTextF_cursor_position(tf),
				False, prim_select->time);
       }
    } else {
       int max_length = 0;
       Boolean local = XmTextF_has_primary(tf);

       if (XmTextF_selection_move(tf) && local) {
          max_length = XmTextF_max_length(tf);
          XmTextF_max_length(tf) = INT_MAX;
       }

       if (*type == XmInternAtom(XtDisplay(w), "COMPOUND_TEXT", False) ||
           *type == XA_STRING) {
	  tmp_prop.value = (unsigned char *) value;
	  tmp_prop.encoding = *type;
	  tmp_prop.format = *format;
	  tmp_prop.nitems = *length;
	  num_vals = 0;
	  status = XmbTextPropertyToTextList(XtDisplay(w), &tmp_prop,
					     &tmp_value, &num_vals);
	 /* if no conversion, num_vals is not changed */
	 /* status will be >0 if some characters could not be converted */
	  if (num_vals && (status == Success || status > 0)) {
	     if (XmTextF_max_char_size(tf) == 1){
		char * total_tmp_value;

		for (i = 0, malloc_size = 1; i < num_vals ; i++)
		   malloc_size += strlen(tmp_value[i]);
		prim_select->num_chars = malloc_size - 1;
		total_tmp_value = XtMalloc ((unsigned) malloc_size);
		total_tmp_value[0] = '\0';
		for (i = 0; i < num_vals ; i++)
		   strcat(total_tmp_value, tmp_value[i]);
		replace_res = _XmDataFieldReplaceText(tf, NULL, 
						      prim_select->position,
						      prim_select->position, 
						      total_tmp_value,
						      strlen(total_tmp_value),
						      False);
		XFreeStringList(tmp_value);
		XtFree(total_tmp_value);
	     } else {
		wchar_t * wc_value;

		prim_select->num_chars = 0;
		for (i = 0, malloc_size = sizeof(wchar_t); i < num_vals ; i++)
		   malloc_size += strlen(tmp_value[i]) * sizeof(wchar_t);
		wc_value = (wchar_t*)XtMalloc ((unsigned) malloc_size);
		for (i = 0; i < num_vals ; i++)
		   prim_select->num_chars +=
		                    mbstowcs(wc_value + prim_select->num_chars,
				             tmp_value[i],
				             (size_t)malloc_size -
					     prim_select->num_chars);
		replace_res = _XmDataFieldReplaceText(tf, NULL, 
						      prim_select->position,
						      prim_select->position,
						      (char*)wc_value, 
						      prim_select->num_chars,
						      False);
		XtFree((char*)wc_value);
	     }
	  } else { /* initialize prim_select values for possible delete oper */
	     prim_select->num_chars = 0;
	  }
       } else {
	     if (XmTextF_max_char_size(tf) == 1){
               /* Note: *length may be truncated during cast to int */
		prim_select->num_chars = (int) *length;
		replace_res = _XmDataFieldReplaceText(tf, NULL, 
						      prim_select->position,
						      prim_select->position, 
						      (char *) value, 
						      prim_select->num_chars,
						      False);
	     } else {
		wchar_t * wc_value;

		wc_value = (wchar_t*)XtMalloc ((unsigned)
                                               (*length * sizeof(wchar_t)));
		prim_select->num_chars = mbstowcs(wc_value, (char *) value,
					 (size_t) *length);
		replace_res = _XmDataFieldReplaceText(tf, NULL, 
						      prim_select->position,
						      prim_select->position,
						      (char*)wc_value, 
						      prim_select->num_chars,
						      False);
		XtFree((char*)wc_value);
	     }
       }

       if (replace_res) {
          XmTextPosition cursorPos;

          XmTextF_pending_off(tf) = FALSE;
          cursorPos = prim_select->position + prim_select->num_chars; 
	  if (prim_select->num_chars > 0 && !XmTextF_selection_move(tf)){
		(void) df_SetDestination(w, cursorPos, False, prim_select->time);
		_XmDataFielddf_SetCursorPosition(tf, NULL, cursorPos, 
					      True, True);
	  }
	  if (XmDataFieldGetSelectionPosition(w, &left, &right)) {
             if (XmTextF_selection_move(tf) && left < prim_select->position)
                prim_select->position -= prim_select->num_chars;
             if (left <= cursorPos && right >= cursorPos)
                XmTextF_pending_off(tf) = TRUE;
          } else {
             if (!XmTextF_selection_move(tf) && !XmTextF_add_mode(tf) &&
                 prim_select->num_chars != 0)
                XmTextF_prim_anchor(tf) = prim_select->position;
          }
	  if (XmTextF_selection_move(tf)) {
              prim_select->ref_count++;
              XtGetSelectionValue(w, XA_PRIMARY,
                                  XmInternAtom(XtDisplay(w), "DELETE", False),
                                  df_DoStuff, (XtPointer)prim_select,
                                  prim_select->time);
           }
           cb.reason = XmCR_VALUE_CHANGED;
           cb.event = (XEvent *)NULL;
           XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		              (XtPointer) &cb);
       }

       if (XmTextF_selection_move(tf) && local) {
          XmTextF_max_length(tf) = max_length;
       }
    }

    XtFree((char *)value);
    value = NULL;
    if (--prim_select->ref_count == 0)
       XtFree((char*)prim_select);
}



/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_Stuff( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_Stuff(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  _XmTextActionRec *tmp = (_XmTextActionRec*)XtMalloc(sizeof(_XmTextActionRec));

/* Request targets from the selection owner so you can decide what to
 * request.  The decision process and request for the selection is
 * taken care of in df_HandleTargets().
 */

  tmp->event = (XEvent *) XtMalloc(sizeof(XEvent));
  memcpy((void *)tmp->event, (void *)event, sizeof(XEvent));

  tmp->params = params;
  tmp->num_params = num_params;

  XtGetSelectionValue(w, XA_PRIMARY,
		      XmInternAtom(XtDisplay(w), "TARGETS", False),
		      df_HandleTargets,
		      (XtPointer)tmp, event->xbutton.time);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_HandleSelectionReplies( w, closure, event, cont )
        Widget w ;
        XtPointer closure ;
        XEvent *event ;
        Boolean *cont ;
#else
df_HandleSelectionReplies(
        Widget w,
        XtPointer closure,
        XEvent *event,
        Boolean *cont )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   Atom property = (Atom) closure;
   TextFDestData dest_data;
   XmTextPosition left, right;
   int adjustment = 0;
   XmAnyCallbackStruct cb;

   if (event->type != SelectionNotify) return;

   XtRemoveEventHandler(w, (EventMask) NULL, TRUE,
                        df_HandleSelectionReplies,
		       (XtPointer) XmInternAtom(XtDisplay(w),
						"_XM_TEXT_I_S_PROP", False));

   dest_data = df_GetTextFDestData(w);

   if (event->xselection.property == None) {
      (void) _XmDataFieldSetSel2(w, 0, 0, False, event->xselection.time);
      XmTextF_selection_move(tf) = False;
   } else {
      if (dest_data->has_destination) {
         adjustment = (int) (XmTextF_sec_pos_right(tf) - XmTextF_sec_pos_left(tf));

         XmDataFieldSetHighlight(w, XmTextF_sec_pos_left(tf),
		                 XmTextF_sec_pos_right(tf), XmHIGHLIGHT_NORMAL);
         if (dest_data->position <= XmTextF_sec_pos_left(tf)) {
            XmTextF_sec_pos_left(tf) += adjustment - dest_data->replace_length;
            XmTextF_sec_pos_right(tf) += adjustment - dest_data->replace_length;
         } else if (dest_data->position > XmTextF_sec_pos_left(tf) &&
                    dest_data->position < XmTextF_sec_pos_right(tf)) {
            XmTextF_sec_pos_left(tf) -= dest_data->replace_length;
            XmTextF_sec_pos_right(tf) += adjustment - dest_data->replace_length;
         }
      }

      left = XmTextF_sec_pos_left(tf);
      right = XmTextF_sec_pos_right(tf);

      (void) _XmDataFieldSetSel2(w, 0, 0, False, event->xselection.time);
      XmTextF_has_secondary(tf) = False;

      if (XmTextF_selection_move(tf)) {
         if (_XmDataFieldReplaceText(tf, event, left, right, NULL, 0, False)) {
           if (dest_data->has_destination && XmTextF_cursor_position(tf) > right){
              XmTextPosition cursorPos;
              cursorPos = XmTextF_cursor_position(tf) - (right - left);
              if (!dest_data->quick_key)
                _XmDataFielddf_SetCursorPosition(tf, event, cursorPos,
					      True, True);
              (void) df_SetDestination((Widget) tf, cursorPos, False,
                                                       event->xselection.time);
           }
           if (!dest_data->has_destination) {
               XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
               XmDataFieldSetAddMode(w, False);	
           }
           cb.reason = XmCR_VALUE_CHANGED;
           cb.event = event;
           XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		              (XtPointer) &cb);
         }
         XmTextF_selection_move(tf) = False;
      }
   }

   XDeleteProperty(XtDisplay(w), event->xselection.requestor, property);
}


/*
 * Notify the primary selection that the secondary selection
 * wants to insert it's selection data into the primary selection.
 */
   /* REQUEST TARGETS FROM SELECTION RECEIVER; THEN CALL HANDLETARGETS
    * WHICH LOOKS AT THE TARGET LIST AND DETERMINE WHAT TARGET TO PLACE 
    * IN THE PAIR.  IT WILL THEN DO ANY NECESSARY CONVERSIONS BEFORE 
    * TELLING THE RECEIVER WHAT TO REQUEST AS THE SELECTION VALUE.
    * THIS WILL GUARANTEE THE BEST CHANCE AT A SUCCESSFUL EXCHANGE.
    */
/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_SecondaryNotify( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_SecondaryNotify(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Atom XM_TEXT_PROP = XmInternAtom(XtDisplay(w), "_XM_TEXT_I_S_PROP", False);
    Atom CS_OF_LOCALE; /* to be initialized by XmbTextListToTextProperty */
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    TextFDestData dest_data;
    XTextProperty tmp_prop;
    _XmTextInsertPair tmp_pair[1];
    _XmTextInsertPair *pair = tmp_pair;
    XmTextPosition left, right;
    int status = 0;

    if (XmTextF_selection_move(tf) == TRUE && XmTextF_has_destination(tf) &&
        XmTextF_cursor_position(tf) >= XmTextF_sec_pos_left(tf) &&
        XmTextF_cursor_position(tf) <= XmTextF_sec_pos_right(tf)) {
       (void) _XmDataFieldSetSel2(w, 0, 0, False, event->xbutton.time);
       return;
    }

    status = XmbTextListToTextProperty(XtDisplay(w), &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       CS_OF_LOCALE = tmp_prop.encoding;
    else
       CS_OF_LOCALE = 99999; /* XmbTextList... should never fail for XPCS
                                 * characters.  But just in case someones
                                 * Xlib is broken, this prevents a core dump.
                                 */
    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

   /*
    * Determine what the reciever supports so you can tell 'em what to
    * request.
    */

   /* fill in atom pair */
    pair->selection = XA_SECONDARY;
    pair->target = CS_OF_LOCALE;

   /* add the insert selection property on the text field widget's window */
    XChangeProperty(XtDisplay(w), XtWindow(w), XM_TEXT_PROP, 
    		    XmInternAtom(XtDisplay(w), "ATOM_PAIR", False),
		    32, PropModeReplace, (unsigned char *)pair, 2);

    dest_data = df_GetTextFDestData(w);

    dest_data->has_destination = XmTextF_has_destination(tf);
    dest_data->position = XmTextF_cursor_position(tf);
    dest_data->replace_length = 0;

    if (*(num_params) == 1) dest_data->quick_key = True;
    else dest_data->quick_key = False;

    if (XmDataFieldGetSelectionPosition(w, &left, &right) && left != right) {
       if (dest_data->position >= left && dest_data->position <= right)
          dest_data->replace_length = (int) (right - left);
    }

   /* add an event handler to handle selection notify events */
    XtAddEventHandler(w, (EventMask) NULL, TRUE,
		      df_HandleSelectionReplies, (XtPointer)XM_TEXT_PROP);

   /*
    * Make a request for the primary selection to convert to 
    * type INSERT_SELECTION as per ICCCM.
    */ 
    XConvertSelection(XtDisplay(w),
    		      XmInternAtom(XtDisplay(w), "MOTIF_DESTINATION", False),
    		      XmInternAtom(XtDisplay(w), "INSERT_SELECTION", False),
                      XM_TEXT_PROP, XtWindow(w), event->xbutton.time);
}

   /*
    * LOOKS AT THE TARGET LIST AND DETERMINE WHAT TARGET TO PLACE 
    * IN THE PAIR.  IT WILL THEN DO ANY NECESSARY CONVERSIONS BEFORE 
    * TELLING THE RECEIVER WHAT TO REQUEST AS THE SELECTION VALUE.
    * THIS WILL GUARANTEE THE BEST CHANCE AT A SUCCESSFUL EXCHANGE.
    */

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_HandleTargets( w, closure, seltype, type, value, length, format )
        Widget w ;
        XtPointer closure ;
        Atom *seltype ;
        Atom *type ;
        XtPointer value ;
        unsigned long *length ;
        int *format ;
#else
df_HandleTargets(
        Widget w,
        XtPointer closure,
        Atom *seltype,
        Atom *type,
        XtPointer value,
        unsigned long *length,
        int *format )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Atom CS_OF_LOCALE; /* to be initialized by XmbTextListToTextProperty */
    Atom COMPOUND_TEXT = XmInternAtom(XtDisplay(w),"COMPOUND_TEXT", False);
    XmTextPosition left, right;
    Boolean supports_locale_data = False;
    Boolean supports_CT = False;
    Atom *atom_ptr;
    _XmTextActionRec *tmp_action = (_XmTextActionRec *) closure;
    _XmTextPrimSelect *prim_select;
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    XTextProperty tmp_prop;
    int status = 0;
    Atom targets[2];
    XmTextPosition select_pos;
    int i;

    if (!length) {
       XtFree((char *)value);
       value = NULL;
       XtFree((char *)tmp_action->event);
       XtFree((char *)tmp_action);
       return; /* Supports no targets, so don't bother sending anything */
    }

    atom_ptr = (Atom *)value;

    status = XmbTextListToTextProperty(XtDisplay(w), &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       CS_OF_LOCALE = tmp_prop.encoding;
    else
       CS_OF_LOCALE = 99999; /* XmbTextList... should never fail for XPCS
                                 * characters.  But just in case someones
                                 * Xlib is broken, this prevents a core dump.
                                 */

    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

    for (i = 0; i < *length; i++, atom_ptr++) {
      if (*atom_ptr == CS_OF_LOCALE) {
         supports_locale_data = True;
	 break;
      }
      if (*atom_ptr == COMPOUND_TEXT)
         supports_CT = True;
    }


  /*
   * Set stuff position to the x and y position of
   * the button pressed event for primary pastes.
   */
   if (tmp_action->event->type == ButtonRelease) {
      select_pos =  df_GetPosFromX(tf, (Position)tmp_action->event->xbutton.x);
   } else {
      select_pos = XmTextF_cursor_position(tf);
   }

   if (XmDataFieldGetSelectionPosition(w, &left, &right) &&
       left != right && select_pos > left && select_pos < right) {
      XtFree((char *)value);
      value = NULL;
      XtFree((char *)tmp_action->event);
      XtFree((char *)tmp_action);
      return;
   }

   prim_select = (_XmTextPrimSelect *)
		  XtMalloc((unsigned) sizeof(_XmTextPrimSelect));

   prim_select->position = select_pos;

   if (tmp_action->event->type == ButtonRelease) {
      prim_select->time = tmp_action->event->xbutton.time;
   } else {
      prim_select->time = tmp_action->event->xkey.time;
   }

   prim_select->num_chars = 0;

   if (supports_locale_data)
      prim_select->target = targets[0] = XmInternAtom(XtDisplay(w), "TEXT",
						      False);
   else if (supports_CT)
      prim_select->target = targets[0] = COMPOUND_TEXT;
   else
      prim_select->target = targets[0] = XA_STRING;

   prim_select->ref_count = 1;
   /* Make request to call df_DoStuff() with the primary selection. */
   XtGetSelectionValue(w, XA_PRIMARY, targets[0], df_DoStuff,
                          (XtPointer)prim_select, 
			  tmp_action->event->xbutton.time);

   XtFree((char *)value);
   value = NULL;
   XtFree((char *)tmp_action->event);
   XtFree((char *)tmp_action);
}

static void
#ifdef _NO_PROTO
df_ProcessBDragRelease( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        String *params ;
        Cardinal *num_params ;
#else
df_ProcessBDragRelease(
        Widget w,
        XEvent *event,
        String *params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XButtonEvent      *ev = (XButtonEvent *) event;
    XmTextPosition position;

   /* Work around for intrinsic bug.  Remove once bug is fixed. */
    XtUngrabPointer(w, ev->time);

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (!XmTextF_cancel(tf)) XtUngrabKeyboard(w, CurrentTime);

    position = df_GetPosFromX(tf, (Position) event->xbutton.x);

    if (XmTextF_sel_start(tf)) {
       if (XmTextF_has_secondary(tf) &&
	       XmTextF_sec_pos_left(tf) != XmTextF_sec_pos_right(tf)) {
          if (ev->x > (int)tf->core.width || ev->x < 0 ||
	      ev->y > (int)tf->core.height || ev->x < 0) {
             _XmDataFieldSetSel2(w, 0, 0, False, event->xkey.time);
             XmTextF_has_secondary(tf) = False;
          } else {
	     df_SecondaryNotify(w, event, params, num_params);
          }
       } else if (!XmTextF_sec_drag(tf) && !XmTextF_cancel(tf) &&
		  XmTextF_sec_pos_left(tf) == position) {
	  XmTextF_stuff_pos(tf) =  df_GetPosFromX(tf, (Position) event->xbutton.x);
	/*
	 * Copy contents of primary selection to the stuff position found above.
	 */
	  df_Stuff(w, event, params, num_params);
       }
    }

    if (XmTextF_select_id(tf)) {
       XtRemoveTimeOut(XmTextF_select_id(tf));
       XmTextF_select_id(tf) = 0;
    }

    XmTextF_sec_extending(tf) = False;

    XmTextF_sec_drag(tf) = False;
    XmTextF_sel_start(tf) = False;
    XmTextF_cancel(tf) = False;
    _XmDataFieldDrawInsertionPoint(tf, True);
}

static void 
#ifdef _NO_PROTO
df_ProcessCopy( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ProcessCopy(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    XmTextF_selection_move(tf) = FALSE;
    df_ProcessBDragRelease(w, event, params, num_params);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

static void 
#ifdef _NO_PROTO
df_ProcessMove( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ProcessMove(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    XmTextF_selection_move(tf) = TRUE;
    df_ProcessBDragRelease(w, event, params, num_params);
    _XmDataFieldDrawInsertionPoint(tf, True);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeleteSelection( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeleteSelection(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    (void) DataFieldRemove(w, event);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ClearSelection( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ClearSelection(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition left = XmTextF_prim_pos_left(tf);
    XmTextPosition right = XmTextF_prim_pos_right(tf);
    int num_spaces = 0;
    XmAnyCallbackStruct cb;
    Boolean rep_result = False;

    if (left < right)
       num_spaces = (int)(right - left);
    else
       num_spaces = (int)(left - right);

    if (num_spaces) {
       _XmDataFieldDrawInsertionPoint(tf, False);
       if (XmTextF_max_char_size(tf) == 1){
          char spaces_cache[100];
          Cardinal spaces_size;
          char *spaces;
          int i;

          spaces_size = num_spaces + 1;

          spaces = XmStackAlloc(spaces_size, spaces_cache);

          for (i = 0; i < num_spaces; i++) spaces[i] = ' ';
          spaces[num_spaces] = 0;

	  rep_result = _XmDataFieldReplaceText(tf, (XEvent *)event, left, right,
				               spaces, num_spaces, False);
          if (XmTextF_cursor_position(tf) > left)
	     df_ResetClipOrigin(tf, False);     
          XmStackFree((char *)spaces, spaces_cache);
       } else {
          wchar_t *wc_spaces;
          int i;

          wc_spaces = (wchar_t *)XtMalloc((unsigned)
                                          (num_spaces + 1) * sizeof(wchar_t));

          for (i = 0; i < num_spaces; i++){
             (void)mbtowc(&wc_spaces[i], " ", 1);
          }
          
	  rep_result = _XmDataFieldReplaceText(tf, (XEvent *)event, left, right,
					       (char*)wc_spaces, num_spaces,
					       False);
          if (XmTextF_cursor_position(tf) > left)
	     df_ResetClipOrigin(tf, False);     

          XtFree((char*)wc_spaces);
       }
       if (rep_result) {
          cb.reason = XmCR_VALUE_CHANGED;
          cb.event = event;
          XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		             (XtPointer) &cb);
       }
       _XmDataFieldDrawInsertionPoint(tf, True);
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_PageRight( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_PageRight(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    Position x, y;
    int length = 0;
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Dimension margin_width = XmTextF_margin_width(tf) +
	                     tf->primitive.shadow_thickness +
			     tf->primitive.highlight_thickness;

    if (XmTextF_max_char_size(tf) != 1){
       length = df_FindPixelLength(tf, (char*)XmTextF_wc_value(tf),
				XmTextF_string_length(tf));
    } else {
       length = df_FindPixelLength(tf, XmTextF_value(tf), XmTextF_string_length(tf));
    }

    _XmDataFieldDrawInsertionPoint(tf, False);

    if (*num_params > 0 && !strcmp(*params, "extend"))
       df_SetAnchorBalancing(tf, XmTextF_cursor_position(tf));

    df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &x, &y);

    if (length - ((int)(tf->core.width - (2 * margin_width)) -
	 XmTextF_h_offset(tf)) > (int)(tf->core.width - (2 * margin_width)))
       XmTextF_h_offset(tf) -= tf->core.width - (2 * margin_width);
    else
       XmTextF_h_offset(tf) = -(length - (tf->core.width - (2 * margin_width)));

    df_RedisplayText(tf, 0, XmTextF_string_length(tf));
    _XmDataFielddf_SetCursorPosition(tf, event, df_GetPosFromX(tf, x), 
				  True, True);

    if (*num_params > 0 && !strcmp(*params, "extend"))
       df_KeySelection(w, event, params, num_params);

    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_PageLeft( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_PageLeft(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    Position x, y;
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    int margin_width = (int)XmTextF_margin_width(tf) +
	                     tf->primitive.shadow_thickness +
			     tf->primitive.highlight_thickness;

    _XmDataFieldDrawInsertionPoint(tf, False);

    if (*num_params > 0 && !strcmp(*params, "extend"))
       df_SetAnchorBalancing(tf, XmTextF_cursor_position(tf));

    df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &x, &y);
    if (margin_width  <= XmTextF_h_offset(tf) +
			    ((int)tf->core.width - (2 * margin_width)))
       XmTextF_h_offset(tf) = margin_width;
    else
       XmTextF_h_offset(tf) += tf->core.width - (2 * margin_width);

    df_RedisplayText(tf, 0, XmTextF_string_length(tf));
    _XmDataFielddf_SetCursorPosition(tf, event, df_GetPosFromX(tf, x),
				  True, True);

    if (*num_params > 0 && !strcmp(*params, "extend"))
       df_KeySelection(w, event, params, num_params);

    _XmDataFieldDrawInsertionPoint(tf, True);
}

static void 
#ifdef _NO_PROTO
df_CopyPrimary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_CopyPrimary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    XmTextF_selection_move(tf) = False;

   /* perform the primary paste action */
    df_Stuff(w, event, params, num_params);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

static void 
#ifdef _NO_PROTO
df_CutPrimary( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_CutPrimary(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    XmTextF_selection_move(tf) = True;
    df_Stuff(w, event, params, num_params);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_SetAnchor( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_SetAnchor(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition left, right;

    XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
    (void) df_SetDestination(w, XmTextF_prim_anchor(tf), False, event->xkey.time);
    if (XmDataFieldGetSelectionPosition(w, &left, &right)) {
       _XmDataFieldStartSelection(tf, XmTextF_prim_anchor(tf),
                                  XmTextF_prim_anchor(tf), event->xkey.time);
       XmDataFieldSetAddMode(w, False);
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ToggleOverstrike( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ToggleOverstrike(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    XmTextF_overstrike(tf) = !XmTextF_overstrike(tf);
    XmTextF_refresh_ibeam_off(tf) = True;
    if (XmTextF_overstrike(tf))
      XmTextF_cursor_width(tf) = XmTextF_cursor_height(tf) >> 1;
    else {
      XmTextF_cursor_width(tf) = 5;
      if (XmTextF_cursor_height(tf) > 19) 
	XmTextF_cursor_width(tf)++;
      df_ResetClipOrigin(tf, False);
    }
    _XmDataFToggleCursorGC(w);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_ToggleAddMode( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_ToggleAddMode(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition left, right;

    _XmDataFieldDrawInsertionPoint(tf, False);

    XmDataFieldSetAddMode(w, !XmTextF_add_mode(tf));	
    if (XmTextF_add_mode(tf) &&
        (!(XmDataFieldGetSelectionPosition(w, &left, &right)) ||
	 left == right))
       XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);

    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_SelectAll( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_SelectAll(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    if (XmTextF_has_primary(tf))
       df_SetSelection(tf, 0, XmTextF_string_length(tf), True);
    else
       _XmDataFieldStartSelection(tf, 0, XmTextF_string_length(tf),
           	      		  event->xbutton.time);

    /* Call _XmDataFielddf_SetCursorPosition to force image gc to be updated
     * in case the i-beam is contained within the selection */

    XmTextF_pending_off(tf) = False;

    _XmDataFielddf_SetCursorPosition(tf, NULL, XmTextF_cursor_position(tf),
				  False, False);
    XmTextF_prim_anchor(tf) = 0;

    (void) df_SetDestination(w, XmTextF_cursor_position(tf),
			  False, event->xkey.time);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_DeselectAll( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_DeselectAll(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    df_SetSelection(tf, XmTextF_cursor_position(tf), XmTextF_cursor_position(tf), True);
    XmTextF_pending_off(tf) = True;
    _XmDataFielddf_SetCursorPosition(tf, event, XmTextF_cursor_position(tf),
				  True, True);
    XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
    (void) df_SetDestination(w, XmTextF_cursor_position(tf),
			  False, event->xkey.time);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_VoidAction( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_VoidAction(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
  /* Do Nothing */
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_CutClipboard( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_CutClipboard(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    _XmDataFieldDrawInsertionPoint((XmDataFieldWidget)w, False);
    (void) XmDataFieldCut(w, event->xkey.time);
    _XmDataFieldDrawInsertionPoint((XmDataFieldWidget)w, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_CopyClipboard( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_CopyClipboard(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldDrawInsertionPoint(tf, False);
    (void) XmDataFieldCopy(w, event->xkey.time);
    (void) df_SetDestination(w, XmTextF_cursor_position(tf), False, event->xkey.time);
    _XmDataFieldDrawInsertionPoint(tf, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_PasteClipboard( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_PasteClipboard(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    _XmDataFieldDrawInsertionPoint((XmDataFieldWidget)w, False);
    (void) XmDataFieldPaste(w);
    _XmDataFieldDrawInsertionPoint((XmDataFieldWidget)w, True);
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TraverseDown( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TraverseDown(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (tf->primitive.navigation_type == XmNONE && df_VerifyLeave(tf, event)) {
       XmTextF_traversed(tf) = True;
       if (!_XmMgrTraversal(w, XmTRAVERSE_DOWN))
          XmTextF_traversed(tf) = False;
    }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TraverseUp( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TraverseUp(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (tf->primitive.navigation_type == XmNONE && df_VerifyLeave(tf, event)) {
       XmTextF_traversed(tf) = True;
       if (!_XmMgrTraversal(w, XmTRAVERSE_UP))
          XmTextF_traversed(tf) = False;
    }
}

/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TraverseHome( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TraverseHome(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

   /* Allow the verification routine to control the traversal */
    if (tf->primitive.navigation_type == XmNONE && df_VerifyLeave(tf, event)) {
       XmTextF_traversed(tf) = True;
       if (!_XmMgrTraversal(w, XmTRAVERSE_HOME))
          XmTextF_traversed(tf) = False;
    }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TraverseNextTabGroup( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TraverseNextTabGroup(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

   /* Allow the verification routine to control the traversal */
    if (df_VerifyLeave(tf, event)) {
       XmTextF_traversed(tf) = True;
       if (!_XmMgrTraversal(w, XmTRAVERSE_NEXT_TAB_GROUP))
          XmTextF_traversed(tf) = False;
    }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TraversePrevTabGroup( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        char **params ;
        Cardinal *num_params ;
#else
df_TraversePrevTabGroup(
        Widget w,
        XEvent *event,
        char **params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

   /* Allow the verification routine to control the traversal */
    if (df_VerifyLeave(tf, event)) {
       XmTextF_traversed(tf) = True;
       if (!_XmMgrTraversal(w, XmTRAVERSE_PREV_TAB_GROUP))
          XmTextF_traversed(tf) = False;
    }
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TextEnter( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        String *params ;
        Cardinal *num_params ;
#else
df_TextEnter(
        Widget w,
        XEvent *event,
        String *params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmAnyCallbackStruct cb;
    XPoint xmim_point;

    /* Use != NotifyInferior along with event->xcrossing.focus to avoid
     * sending input method info if reason for the event is pointer moving
     * from TextF widget to over-the-spot window (case when over-the-spot
     * is child of TextF widget). */
    if (_XmGetFocusPolicy(w) != XmEXPLICIT && !(XmTextF_has_focus(tf)) &&
	event->xcrossing.focus &&
        (event->xcrossing.detail != NotifyInferior)) {
       if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
       _XmDataFieldDrawInsertionPoint(tf, False);
       XmTextF_blink_on(tf) = False;
       XmTextF_has_focus(tf) = True;
       _XmDataFToggleCursorGC(w);
       if (XtIsSensitive(w)) df_ChangeBlinkBehavior(tf, True);
       _XmDataFieldDrawInsertionPoint(tf, True);
       df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &xmim_point.x, 
		    &xmim_point.y);
       XmImVaSetFocusValues(w, XmNspotLocation, &xmim_point, NULL);
       cb.reason = XmCR_FOCUS;
       cb.event = event;
       XtCallCallbackList (w, XmTextF_focus_callback(tf), (XtPointer) &cb);
    }

    _XmPrimitiveEnter(w, event, params, num_params);
}


/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_TextLeave( w, event, params, num_params )
        Widget w ;
        XEvent *event ;
        String *params ;
        Cardinal *num_params ;
#else
df_TextLeave(
        Widget w,
        XEvent *event,
        String *params,
        Cardinal *num_params )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   /* use detail!= NotifyInferior to handle focus change due to pointer
    * wandering into over-the-spot input window - we don't want to change
    * IM's focus state in this case. */
   if (_XmGetFocusPolicy(w) != XmEXPLICIT && XmTextF_has_focus(tf) &&
       event->xcrossing.focus &&
       (event->xcrossing.detail != NotifyInferior)) {
      if (tf->core.sensitive) df_ChangeBlinkBehavior(tf, False);
      _XmDataFieldDrawInsertionPoint(tf, False);
      XmTextF_has_focus(tf) = False;
      _XmDataFToggleCursorGC(w);
      XmTextF_blink_on(tf) = True;
      _XmDataFieldDrawInsertionPoint(tf, True);
      (void) df_VerifyLeave(tf, event);
      XmImUnsetFocus(w);
   }

   _XmPrimitiveLeave(w, event, params, num_params);
}

/****************************************************************
 *
 * Private definitions.
 *
 ****************************************************************/

/*
 * df_ClassPartInitialize sets up the fast subclassing for the widget.i
 * It also merges translation tables.
 */
static void 
#ifdef _NO_PROTO
df_ClassPartInitialize( w_class )
        WidgetClass w_class ;
#else
df_ClassPartInitialize(
        WidgetClass w_class )
#endif /* _NO_PROTO */
{
    char *event_bindings;

    /*
     *    _XmFastSubclassInit (w_class, XmTEXT_FIELD_BIT);
     */
    event_bindings = (char *)XtMalloc((unsigned) (strlen(EventBindings1) +
                                      strlen(EventBindings2) +
                                      strlen(EventBindings3) + strlen("\n") +
				      strlen(df_translations) + 1));

    strcpy(event_bindings, df_translations);
    strcat(event_bindings, "\n");
    strcat(event_bindings, EventBindings1);
    strcat(event_bindings, EventBindings2);
    strcat(event_bindings, EventBindings3);

    _XmProcessLock(); 
    w_class->core_class.tm_table = (String) XtParseTranslationTable(event_bindings);
    _XmProcessUnlock();

    XtFree(event_bindings);
}

/****************************************************************
 *
 * Private functions used in df_Initialize.
 *
 ****************************************************************/

/*
 * Verify that the resource settings are valid.  Print a warning
 * message and reset the s if the are invalid.
 */
static void 
#ifdef _NO_PROTO
df_Validates( tf )
        XmDataFieldWidget tf ;
#else
df_Validates(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
    XtPointer temp_ptr;

    if (XmTextF_cursor_position(tf) < 0) {
	  XmeWarning ((Widget)tf, MSG1);
          XmTextF_cursor_position(tf) = 0;
    }

    if (XmTextF_columns(tf) <= 0) {
	  XmeWarning ((Widget)tf, MSG2);
	  XmTextF_columns(tf) = 20;
    }

    if (XmTextF_selection_array(tf) == NULL) 
       XmTextF_selection_array(tf) = (XmTextScanType *) df_sarray;

    if (XmTextF_selection_array_count(tf) <= 0) 
       XmTextF_selection_array_count(tf) = XtNumber(df_sarray);

/*
 * Fix for HaL DTS 9841 - copy the selectionArray into dedicated memory.
 */
    temp_ptr = (XtPointer)XmTextF_selection_array(tf);
    XmTextF_selection_array(tf) = NULL;
    
    XmTextF_selection_array(tf) = (XmTextScanType *)XtMalloc (
		 XmTextF_selection_array_count(tf) * sizeof(XmTextScanType));
    memcpy((void *)XmTextF_selection_array(tf), (void *)temp_ptr,
	   (XmTextF_selection_array_count(tf) * sizeof(XmTextScanType)));
/*
 * End fix for HaL DTS 9841
 */
}

static Boolean 
#ifdef _NO_PROTO
df_LoadFontMetrics( tf )
        XmDataFieldWidget tf ;
#else
df_LoadFontMetrics(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
    XmFontContext context;
    XmFontListEntry next_entry;
    XmFontType type_return = XmFONT_IS_FONT;
    XtPointer tmp_font;
    Boolean have_font_struct = False;
    Boolean have_font_set = False;
    XFontSetExtents *fs_extents;
    XFontStruct *font;
    unsigned long charwidth = 0;
    char* font_tag = NULL;
    Boolean return_val = 1; /* non-zero == success */

    if (!XmFontListInitFontContext(&context, XmTextF_font_list(tf)))
       XmeWarning ((Widget)tf, MSG3);

    do {
       next_entry = XmFontListNextEntry(context);
       if (next_entry) {
          tmp_font = XmFontListEntryGetFont(next_entry, &type_return);
          if (type_return == XmFONT_IS_FONTSET) { 
	     font_tag = XmFontListEntryGetTag(next_entry);
	     if (!have_font_set){ /* this saves the first fontset found, just in
                                   * case we don't find a default tag set.
                                   */
	        XmTextF_have_fontset(tf) = True;
	        XmTextF_font(tf) = (XFontStruct *)tmp_font;
	        have_font_struct = True; /* we have a font set, so no need to 
                                          * consider future font structs */
	        have_font_set = True;    /* we have a font set. */

	        if (!strcmp(XmFONTLIST_DEFAULT_TAG, font_tag))
	           break; /* Break out!  We've found the one we want. */

	     } else if (!strcmp(XmFONTLIST_DEFAULT_TAG, font_tag)){
                XmTextF_font(tf) = (XFontStruct *)tmp_font;
	        have_font_set = True;    /* we have a font set. */
	        break; /* Break out!  We've found the one we want. */
	     }
          } else if (!have_font_struct){/* return_type must be XmFONT_IS_FONT */
	     XmTextF_have_fontset(tf) = False;
	     XmTextF_font(tf)=(XFontStruct*)tmp_font; /* save the first font
                                                     * struct in case no font 
                                                     * set is found */
	     have_font_struct = True;                     
          }
       }
    } while(next_entry != NULL);

    if (!have_font_struct && !have_font_set)
          XmeWarning ((Widget)tf, MSG4);

    if (XmTextF_max_char_size(tf) > 1 && !have_font_set){
     /*XmeWarning((Widget)tf, MSGnnn); */
     /* printf ("You've got the wrong font baby, Uh-Huh!\n"); */
     /* Must have a font set, as text will be rendered only with new R5 calls 
      * If df_LoadFontMetrics is called from df_SetValues and set
      * values will retain use of old fontlist (which is presumed correct
      * for the current locale). */

       return_val = 0; /* tell caller that this font won't work for MB_CUR_MAX*/
    }
    XmFontListFreeFontContext(context);

    if(XmTextF_have_fontset(tf)){
       fs_extents = XExtentsOfFontSet((XFontSet)XmTextF_font(tf));
	charwidth = (unsigned long)fs_extents->max_ink_extent.width;
       /* max_ink_extent.y is number of pixels from origin to top of
        * rectangle (i.e. y is negative) */
       XmTextF_font_ascent(tf) = -fs_extents->max_ink_extent.y;
       XmTextF_font_descent(tf) = fs_extents->max_ink_extent.height +
                               fs_extents->max_ink_extent.y;
    } else {
       font = XmTextF_font(tf);
       if ((!XGetFontProperty(font, XA_QUAD_WIDTH, &charwidth)) ||
            charwidth == 0) {
          if (font->per_char && font->min_char_or_byte2 <= '0' &&
                                font->max_char_or_byte2 >= '0')
              charwidth = font->per_char['0' - font->min_char_or_byte2].width;
          else
              charwidth = font->max_bounds.width;
       }
       XmTextF_font_ascent(tf) = font->max_bounds.ascent;
       XmTextF_font_descent(tf) = font->max_bounds.descent;
    }
    XmTextF_average_char_width(tf) = (Dimension) charwidth;
    return (return_val);
}


/* df_ValidateString makes the following assumption:  if MB_CUR_MAX == 1, value
 * is a char*, otherwise value is a wchar_t*.  The Boolean "is_wchar" indicates
 * if value points to char* or wchar_t* data.
 *
 * It is df_ValidateString's task to verify that "value" contains only printing
 * characters; all others are discarded.  df_ValidateString then mallocs data
 * to store the value and assignes it to XmTextF_value(tf) (if MB_CUR_MAX == 1)
 * or to XmTextF_wc_value(tf) (if MB_CUR_MAX != 1), setting the opposite
 * pointer to NULL.  It is the callers responsibility to free data before
 * calling df_ValidateString.
 */
static void 
#ifdef _NO_PROTO
df_ValidateString( tf, value, is_wchar )
        XmDataFieldWidget tf ;
        char *value ;
	Boolean is_wchar;
#else
df_ValidateString(
        XmDataFieldWidget tf,
        char *value,
#if NeedWidePrototypes
	int is_wchar)
#else
	Boolean is_wchar)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
   /* if value is wchar_t *, must count the characters; else use strlen */

   int str_len = 0;
   int i, j;
   char stack_cache[400];

   if (!is_wchar) {
      char *temp_str, *curr_str, *start_temp;

      str_len = strlen(value);
      temp_str = XmStackAlloc((Cardinal)str_len + 1, stack_cache);
      start_temp = temp_str;
      curr_str = value;

      for (i = 0; i < str_len;) {
         if (XmTextF_max_char_size(tf) == 1){
            if (df_FindPixelLength(tf, curr_str, 1)) {
               *temp_str = *curr_str;
               temp_str++;
            } else {
               char warn_str[52];
               sprintf(warn_str, MSG5, *curr_str);
               XmeWarning ((Widget)tf, warn_str);
            }
	    curr_str++;
	    i++;
	 } else {
	    wchar_t tmp;
	    int num_conv;
	    num_conv = mbtowc(&tmp, curr_str, XmTextF_max_char_size(tf));
            if (num_conv >= 0 && df_FindPixelLength(tf, (char*) &tmp, 1)) {
	       for (j = 0; j < num_conv; j++) {
                  *temp_str = *curr_str;
                  temp_str++;
		  curr_str++;
		  i++; 
		}
            } else {
               char warn_str[52];
               sprintf(warn_str, MSG5, *curr_str);
               XmeWarning ((Widget)tf, warn_str);
	       curr_str++;
	       i++;
            }
	 }
      }
      *temp_str = '\0';

      /* value contains validated string; now stuff it into the proper
       * instance pointer. */
      if (XmTextF_max_char_size(tf) == 1) {
         XmTextF_string_length(tf) = strlen(start_temp);
        /* malloc the space for the text value */
         XmTextF_value(tf) = (char *) memcpy(
			     XtMalloc((unsigned)(XmTextF_string_length(tf) + 30)),
			       (void *)start_temp, XmTextF_string_length(tf) + 1);
         XmTextF_size_allocd(tf) = XmTextF_string_length(tf) + 30;
         XmTextF_wc_value(tf) = NULL;
      } else { /* Need wchar_t* data to set as the widget's value */
         /* count number of wchar's */
         str_len = strlen(start_temp);
         XmTextF_string_length(tf) = str_len;

         XmTextF_size_allocd(tf) = (XmTextF_string_length(tf) + 30)*sizeof(wchar_t);
         XmTextF_wc_value(tf) = (wchar_t*)XtMalloc((unsigned)XmTextF_size_allocd(tf));
         XmTextF_string_length(tf) = mbstowcs(XmTextF_wc_value(tf), start_temp,
                                           XmTextF_string_length(tf) + 30);
         XmTextF_value(tf) = NULL;
      }
      XmStackFree((char *)start_temp, stack_cache);
   } else {  /* pointer passed points to wchar_t* data */
      wchar_t *wc_value, *wcs_temp_str, *wcs_start_temp, *wcs_curr_str;
      char scratch[8];
      int new_len = 0;
      int csize = 1;

      wc_value = (wchar_t *) value;
      for (str_len = 0, i = 0; *wc_value != (wchar_t)0L; str_len++)
          wc_value++; /* count number of wchars */
      wcs_temp_str=(wchar_t *)XmStackAlloc((Cardinal)
					   ((str_len+1) * sizeof(wchar_t)),
					   stack_cache);
      wcs_start_temp = wcs_temp_str;
      wcs_curr_str = (wchar_t *) value;

      for (i = 0; i < str_len; i++, wcs_curr_str++) {
	 if (XmTextF_max_char_size(tf) == 1){
	    csize = wctomb(scratch, *wcs_curr_str);
	    if (csize >= 0 && df_FindPixelLength(tf, scratch, csize)) {
	       *wcs_temp_str = *wcs_curr_str;
	       wcs_temp_str++;
	       new_len++;
	    } else {
	       char warn_str[52];
	       scratch[csize]= '\0';
	       sprintf(warn_str, WC_MSG1, scratch);
	       XmeWarning ((Widget)tf, warn_str);
	    }
	 } else {
	    if (df_FindPixelLength(tf, (char*)wcs_curr_str, 1)) {
	       *wcs_temp_str = *wcs_curr_str;
	       wcs_temp_str++;
	       new_len++;
	    } else {
               char warn_str[52];
               csize = wctomb(scratch, *wcs_curr_str);
	       if (csize >= 0)
                  scratch[csize]= '\0';
	       else
		  scratch[0] = '\0';
               sprintf(warn_str, WC_MSG1, scratch);
               XmeWarning ((Widget)tf, warn_str);
	    }
	 }
      } 
      str_len = new_len;

      *wcs_temp_str = (wchar_t)0L; /* terminate with a wchar_t NULL */

      XmTextF_string_length(tf) = str_len; /* This is *wrong* if MB_CUR_MAX > 2
					 * with no font set... but what can
					 * ya do? Spec says let it dump core. */

      XmTextF_size_allocd(tf) = (str_len + 30) * sizeof(wchar_t);
      if (XmTextF_max_char_size(tf) == 1) { /* Need to store data as char* */
         XmTextF_value(tf) = XtMalloc((unsigned)XmTextF_size_allocd(tf));
         (void)wcstombs(XmTextF_value(tf), wcs_start_temp, XmTextF_size_allocd(tf));
         XmTextF_wc_value(tf) = NULL;
      } else { /* Need to store data as wchar_t* */
         XmTextF_wc_value(tf) = (wchar_t*)memcpy(XtMalloc((unsigned)
						       XmTextF_size_allocd(tf)),
                                              	       (void*)wcs_start_temp,
                                                       (1 + str_len) *
						       sizeof(wchar_t));
         XmTextF_value(tf) = NULL;
      }
      XmStackFree((char *)wcs_start_temp, stack_cache);
   }
}

/* The following is a hack to overcome the buggy Motif from SGI on IM */
#if defined(__sgi)
static void /* CR03685 */
#ifdef _NO_PROTO
SGI_hack_XmImRegister(w)
  Widget w;
#else
SGI_hack_XmImRegister(
  Widget w )
#endif /* _NO_PROTO */
{
  _XmProcessLock();
  w->core.widget_class = xmTextFieldWidgetClass;
  _XmProcessUnlock();

  XmImRegister(w, NULL);

  _XmProcessLock();
  w->core.widget_class = xmDataFieldWidgetClass;
  _XmProcessUnlock();
}  
#endif
/*
 * df_Initialize the s in the text fields instance record.
 */
static void 
#ifdef _NO_PROTO
df_InitializeTextStruct( tf )
        XmDataFieldWidget tf ;
#else
df_InitializeTextStruct(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
   /* Flag used in losing focus verification to indicate that a traversal
    * key was pressed.  Must be initialized to False.
    */
    Arg args[6];  /* To set initial values to input method */
    Cardinal n = 0;
    XPoint xmim_point;

    XmTextF_traversed(tf) = False;
    
    XmTextF_add_mode(tf) = False;
    XmTextF_has_focus(tf) = False;
    XmTextF_blink_on(tf) = True;
    XmTextF_cursor_on(tf) = 0;
    XmTextF_has_rect(tf) = False;
    XmTextF_has_primary(tf) = False;
    XmTextF_has_secondary(tf) = False;
    XmTextF_has_destination(tf) = False;
    XmTextF_overstrike(tf) = False;
    XmTextF_selection_move(tf) = False;
    XmTextF_sel_start(tf) = False;
    XmTextF_pending_off(tf) = True;
    XmTextF_fontlist_created(tf) = False;
    XmTextF_cancel(tf) = False;
    XmTextF_extending(tf) = False;
    XmTextF_prim_time(tf) = 0;
    XmTextF_dest_time(tf) = 0;
    XmTextF_select_id(tf) = 0;
    XmTextF_select_pos_x(tf) = 0;
    XmTextF_sec_extending(tf) = False;
    XmTextF_sec_drag(tf) = False;
    XmTextF_changed_visible(tf) = False;
    XmTextF_refresh_ibeam_off(tf) = True;
    XmTextF_in_setvalues(tf) = False;
    XmTextF_do_resize(tf) = True;
    XmTextF_have_inverted_image_gc(tf) = False;
    XmTextF_margin_top(tf) = XmTextF_margin_height(tf);
    XmTextF_margin_bottom(tf) = XmTextF_margin_height(tf);

    /* copy over the font list */
    if (XmTextF_font_list(tf) == NULL) {
       XmTextF_font_list(tf) = _XmGetDefaultFontList((Widget)tf,
				              (unsigned char) XmTEXT_FONTLIST);
       XmTextF_fontlist_created(tf) = True;
    }

    XmTextF_font_list(tf) = (XmFontList)XmFontListCopy(XmTextF_font_list(tf));

    XmTextF_max_char_size(tf) = MB_CUR_MAX;

    (void)df_LoadFontMetrics(tf);

    XmTextF_gc(tf) = NULL;
    XmTextF_image_gc(tf) = NULL;
    XmTextF_save_gc(tf) = NULL;

    if (XmDataField_alignment(tf) == XmALIGNMENT_END)
	XmTextF_new_h_offset(tf) = XmTextF_h_offset(tf) = 0;
    else
	XmTextF_new_h_offset(tf) = XmTextF_h_offset(tf) = XmTextF_margin_width(tf) +
	    tf->primitive.shadow_thickness + tf->primitive.highlight_thickness;

    /* df_ValidateString will verify value contents, convert to appropriate
     * storage form (i.e. char* or wchar_t*), place in the appropriate
     * location (text.value or text.wc_value), and null out opposite
     * pointer.  */

    if (XmTextF_wc_value(tf) != NULL) { /* XmNvalueWcs was set - it rules */
       XmTextF_value(tf) = NULL;
       df_ValidateString(tf, (char*)XmTextF_wc_value(tf), True);
    } else if (XmTextF_value(tf) != NULL)
       df_ValidateString(tf, XmTextF_value(tf), False);
    else /* XmTextF_value(tf) is null pointer */
       df_ValidateString(tf, "", False);

    if (XmTextF_cursor_position(tf) > XmTextF_string_length(tf))
       XmTextF_cursor_position(tf) = XmTextF_string_length(tf);

    XmTextF_orig_left(tf) = XmTextF_orig_right(tf) = XmTextF_prim_pos_left(tf) =
     XmTextF_prim_pos_right(tf) = XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);

    XmTextF_sec_pos_left(tf) = XmTextF_sec_pos_right(tf) =
     	XmTextF_sec_anchor(tf) = XmTextF_cursor_position(tf);

    XmTextF_stuff_pos(tf) = XmTextF_cursor_position(tf);

    XmTextF_cursor_height(tf) = XmTextF_cursor_width(tf) = 0;
    XmTextF_stipple_tile(tf) = None;
    XmTextF_add_mode_cursor(tf) = XmUNSPECIFIED_PIXMAP;
    XmTextF_cursor(tf) = XmUNSPECIFIED_PIXMAP;
    XmTextF_ibeam_off(tf) = XmUNSPECIFIED_PIXMAP;
    XmTextF_image_clip(tf) = XmUNSPECIFIED_PIXMAP;

    XmTextF_last_time(tf) = 0;

    XmTextF_sarray_index(tf) = 0;

   /* df_Initialize highlight elements */
    XmTextF_highlight(tf).number = XmTextF_highlight(tf).maximum = 1;
    XmTextF_highlight(tf).list = (_XmHighlightRec *)XtMalloc((unsigned)
						 sizeof(_XmHighlightRec));
    XmTextF_highlight(tf).list[0].position = 0;
    XmTextF_highlight(tf).list[0].mode = XmHIGHLIGHT_NORMAL;

    XmTextF_timer_id(tf) = (XtIntervalId)0;

    if(XmDataField_picture_source(tf)) {
	XmDataField_picture_source(tf) = XtNewString(XmDataField_picture_source(tf));
	XmDataField_picture(tf) = XmParsePicture(XmDataField_picture_source(tf));
        XtAddCallback((Widget)tf, XmNmodifyVerifyCallback,
			  PictureVerifyCallback, NULL);
    } else {
	/* No picture specified */
	XmDataField_picture(tf) = NULL;
    }

    XmDataFieldSetEditable((Widget)tf, XmTextF_editable(tf));

    if (XmTextF_editable(tf)){
#if defined(__sgi)
      /* CR03685 */
      SGI_hack_XmImRegister((Widget)tf);
#else
      XmImRegister((Widget)tf, (unsigned int) NULL);
#endif
      df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &xmim_point.x, &xmim_point.y);
      n = 0;
      XtSetArg(args[n], XmNfontList, XmTextF_font_list(tf)); n++;
      XtSetArg(args[n], XmNbackground, tf->core.background_pixel); n++;
      XtSetArg(args[n], XmNforeground, tf->primitive.foreground); n++;
      XtSetArg(args[n], XmNbackgroundPixmap,tf->core.background_pixmap);n++;
      XtSetArg(args[n], XmNspotLocation, &xmim_point); n++;
      XtSetArg(args[n], XmNlineSpace, 
               XmTextF_font_ascent(tf)+ XmTextF_font_descent(tf)); n++;
      XmImSetValues((Widget)tf, args, n);
    }
}

static Pixmap 
#ifdef _NO_PROTO
df_GetClipMask( tf, pixmap_name)
        XmDataFieldWidget tf ;
        char *pixmap_name ;
#else
df_GetClipMask(
        XmDataFieldWidget tf,
        char *pixmap_name)
#endif /* _NO_PROTO */
{
   Display *dpy = XtDisplay(tf);
   Screen *screen = XtScreen(tf);
   XGCValues values;
   GC fillGC;
   Pixmap clip_mask;

   clip_mask = XCreatePixmap(dpy, RootWindowOfScreen(screen), 
			     XmTextF_cursor_width(tf), XmTextF_cursor_height(tf), 1);

   values.foreground = 1;
   values.background = 0;
   fillGC = XCreateGC(dpy, clip_mask, GCForeground | GCBackground, &values);

   XFillRectangle(dpy, clip_mask, fillGC, 0, 0, XmTextF_cursor_width(tf),
		  XmTextF_cursor_height(tf));

  /* Install the clipmask for pixmap caching */
   (void) _XmInstallPixmap(clip_mask, screen, pixmap_name, 1, 0);

   XFreeGC(XtDisplay(tf), fillGC);

   return(clip_mask);
}

/*
 * Get the graphics context for filling the background, and for drawing
 * and inverting text.  Used a unique pixmap so all text field widgets
 * share common GCs.
 */
static void 
#ifdef _NO_PROTO
df_LoadGCs( tf, background, foreground )
        XmDataFieldWidget tf ;
        Pixel background ;
        Pixel foreground ;
#else
df_LoadGCs(
        XmDataFieldWidget tf,
        Pixel background,
        Pixel foreground )
#endif /* _NO_PROTO */
{
   Display *display = XtDisplay((Widget)tf);
   Screen *screen = XtScreen((Widget)tf);
   XGCValues values;
   static XContext context = 0;
   static Pixmap tf_cache_pixmap;
   unsigned long value_mask = (GCFunction | GCForeground | GCBackground | 
			      GCClipMask | GCArcMode);
   unsigned long dynamic_mask;

   if (XmTextF_stipple_tile(tf) != None)
       XmDestroyPixmap(XtScreen(tf), XmTextF_stipple_tile(tf));
       
   XmTextF_stipple_tile(tf) = (Pixmap)
       XmGetPixmapByDepth(XtScreen(tf),"50_foreground",
			  tf->primitive.foreground, tf->core.background_pixel,
			  tf->core.depth);

   if (context == 0)
      context = XUniqueContext();

   if (XFindContext(display, (Window)screen, 
		    context, (char **) &tf_cache_pixmap)){
     XmTextContextData ctx_data;
     Widget xm_display = (Widget) XmGetXmDisplay(display);

     ctx_data = (XmTextContextData) XtMalloc(sizeof(XmTextContextDataRec));

     ctx_data->screen = screen;
     ctx_data->context = context;
     ctx_data->type = _XM_IS_PIXMAP_CTX;

    /* Get the Pixmap identifier that the X Toolkit uses to cache our */
    /* GC's.  We never actually use this Pixmap; just so long as it's */
    /* a unique identifier. */
     tf_cache_pixmap =  XCreatePixmap(display,
				     (Drawable) RootWindowOfScreen(screen),
				     (unsigned int) 1, (unsigned int) 1,
				     (unsigned int) 1);

     XtAddCallback(xm_display, XmNdestroyCallback, 
                   (XtCallbackProc) df_FreeContextData, (XtPointer) ctx_data);

     XSaveContext(display, (Window)screen, context, (XPointer) tf_cache_pixmap);
   }

   /* Used to be: values.clip_mask = tf_cache_pixmap; */
   values.clip_mask = 0;    /* use in caching Text Field gc's */
   values.arc_mode = ArcPieSlice; /* Used in differentiating from Text
				     widget GC caching */

   if (XmTextF_has_rect(tf)) {
      TextFGCData gc_data = df_GetTextFGCData((Widget)tf);
      XmTextF_has_rect(gc_data->tf) = False;
      gc_data->tf = NULL;
   }

  /*
   * Get GC for saving area under the cursor.
   */
   values.function = GXcopy;
   values.foreground = tf->primitive.foreground ;
   values.background = tf->core.background_pixel;
   if (XmTextF_save_gc(tf) != NULL)
       XtReleaseGC((Widget)tf, XmTextF_save_gc(tf)); 
   dynamic_mask = (GCClipMask);
   XmTextF_save_gc(tf) = XtAllocateGC((Widget) tf,
	tf->core.depth, value_mask,
	&values, dynamic_mask, 0); 

   df_XmResetSaveGC(tf, XmTextF_save_gc(tf));
  /*
   * Get GC for drawing text.
   */

   if (!XmTextF_have_fontset(tf)){
      value_mask |= GCFont | GCGraphicsExposures;
      values.font = XmTextF_font(tf)->fid;
   } else {
      value_mask |= GCGraphicsExposures;
   }
   values.graphics_exposures = (Bool) TRUE;
   values.foreground = foreground ^ background;
   values.background = 0;
   if (XmTextF_gc(tf) != NULL)
   	XtReleaseGC((Widget)tf, XmTextF_gc(tf)); 
   dynamic_mask |=  GCForeground | GCBackground | GCFillStyle | GCTile;
   XmTextF_gc(tf) = XtAllocateGC((Widget) tf,
	tf->core.depth, value_mask,
	&values, dynamic_mask, 0); 

   /* Create a temporary GC - change it later in make IBEAM */
   value_mask |= GCTile;
   values.tile = XmTextF_stipple_tile(tf);
   if (XmTextF_image_gc(tf) != NULL)
   	XtReleaseGC((Widget)tf, XmTextF_image_gc(tf)); 
   dynamic_mask = (GCForeground | GCBackground | GCStipple | GCFillStyle |
                   GCTileStipXOrigin | GCTileStipYOrigin | GCFunction |
                   GCClipMask | GCClipXOrigin | GCClipYOrigin);
   XmTextF_image_gc(tf) = XtAllocateGC((Widget) tf,
	                   tf->core.depth, value_mask,
                           &values, dynamic_mask, 0); 

}

static void 
#ifdef _NO_PROTO
df_MakeIBeamOffArea( tf, width, height )
        XmDataFieldWidget tf ;
        Dimension width ;
        Dimension height ;
#else
df_MakeIBeamOffArea(
        XmDataFieldWidget tf,
#if NeedWidePrototypes
        int width,
        int height)
#else
        Dimension width,
        Dimension height)
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */
{
   Display *dpy = XtDisplay(tf);
   Screen  *screen = XtScreen(tf);
   GC fillGC;

  /* Create a pixmap for storing the screen data where the I-Beam will 
   * be painted */

   XmTextF_ibeam_off(tf) = XCreatePixmap(dpy, RootWindowOfScreen(screen), width,
				      height, tf->core.depth);

  /* Create a GC for drawing 0's into the pixmap */
   fillGC = XCreateGC(dpy, XmTextF_ibeam_off(tf), 0, (XGCValues *) NULL);

  /* df_Initialize the pixmap to 0's */
   XFillRectangle(dpy, XmTextF_ibeam_off(tf), fillGC, 0, 0, width, height);

  /* Free the GC */
   XFreeGC(XtDisplay(tf), fillGC);
}

static void 
#ifdef _NO_PROTO
df_MakeIBeamStencil( tf, line_width )
        XmDataFieldWidget tf ;
        int line_width ;
#else
df_MakeIBeamStencil(
        XmDataFieldWidget tf,
        int line_width )
#endif /* _NO_PROTO */
{
   Screen *screen = XtScreen(tf);
   char pixmap_name[17];
   XGCValues values;
   unsigned long valuemask;

   if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
   sprintf(pixmap_name, "_XmDataF_%d_%d", XmTextF_cursor_height(tf), line_width);
   XmTextF_cursor(tf) = (Pixmap) XmGetPixmapByDepth(screen, pixmap_name, 1, 0, 1);

   if (XmTextF_cursor(tf) == XmUNSPECIFIED_PIXMAP) {
      Display *dpy = XtDisplay(tf);
      GC fillGC;
      XSegment segments[3];
      XRectangle ClipRect;

     /* Create a pixmap for the I-Beam stencil */
      XmTextF_cursor(tf) = XCreatePixmap(dpy, XtWindow(tf), XmTextF_cursor_width(tf),
				      XmTextF_cursor_height(tf), 1);

     /* Create a GC for "cutting out" the I-Beam shape from the pixmap in
      * order to create the stencil.
      */
      fillGC = XCreateGC(dpy, XmTextF_cursor(tf), 0, (XGCValues *)NULL);

     /* Fill in the stencil with a solid in preparation
      * to "cut out" the I-Beam
      */
      XFillRectangle(dpy, XmTextF_cursor(tf), fillGC, 0, 0, XmTextF_cursor_width(tf),
		     XmTextF_cursor_height(tf));

     /* Change the GC for use in "cutting out" the I-Beam shape */
      values.foreground = 1;
      values.line_width = line_width;
      XChangeGC(dpy, fillGC, GCForeground | GCLineWidth, &values);

     /* Draw the segments of the I-Beam */
     /* 1st segment is the top horizontal line of the 'I' */
      segments[0].x1 = 0;
      segments[0].y1 = line_width - 1;
      segments[0].x2 = XmTextF_cursor_width(tf);
      segments[0].y2 = line_width - 1;

     /* 2nd segment is the bottom horizontal line of the 'I' */
      segments[1].x1 = 0;
      segments[1].y1 = XmTextF_cursor_height(tf) - 1;
      segments[1].x2 = XmTextF_cursor_width(tf);
      segments[1].y2 = XmTextF_cursor_height(tf) - 1;

     /* 3rd segment is the vertical line of the 'I' */
      segments[2].x1 = XmTextF_cursor_width(tf) >> 1;
      segments[2].y1 = line_width;
      segments[2].x2 = XmTextF_cursor_width(tf) >> 1;
      segments[2].y2 = XmTextF_cursor_height(tf) - 1;

     /* Set the clipping rectangle of the image GC from drawing */
      ClipRect.width = XmTextF_cursor_width(tf);
      ClipRect.height = XmTextF_cursor_height(tf);
      ClipRect.x = 0;
      ClipRect.y = 0;

      XSetClipRectangles(XtDisplay(tf), fillGC, 0, 0, &ClipRect, 1, Unsorted);

     /* Draw the segments onto the cursor */
      XDrawSegments(dpy, XmTextF_cursor(tf), fillGC, segments, 3);

    /* Install the cursor for pixmap caching */
      (void) _XmInstallPixmap(XmTextF_cursor(tf), XtScreen(tf), pixmap_name, 1, 0);

     /* Free the fill GC */
      XFreeGC(XtDisplay(tf), fillGC);
   }

  /* Get/create the image_gc used to paint the I-Beam */

    sprintf(pixmap_name, "_XmText_CM_%d", XmTextF_cursor_height(tf));
    XmTextF_image_clip(tf) = XmGetPixmapByDepth(XtScreen(tf), pixmap_name,
					     1, 0, 1);
    if (XmTextF_image_clip(tf) == XmUNSPECIFIED_PIXMAP)
       XmTextF_image_clip(tf) = df_GetClipMask(tf, pixmap_name);

    valuemask = (GCClipMask | GCStipple | GCForeground | GCBackground | 
		 GCFillStyle);
    if (!XmTextF_overstrike(tf)) {
      values.foreground = tf->primitive.foreground;
      values.background = tf->core.background_pixel;
    } else 
      values.background = values.foreground = 
	tf->core.background_pixel ^ tf->primitive.foreground;
    values.clip_mask = XmTextF_image_clip(tf);
    values.stipple = XmTextF_cursor(tf);
    values.fill_style = FillStippled;
    XChangeGC(XtDisplay(tf), XmTextF_image_gc(tf), valuemask, &values);

}


/* The IBeam Stencil must have already been created before this routine
 * is called.
 */

static void 
#ifdef _NO_PROTO
df_MakeAddModeCursor( tf, line_width )
        XmDataFieldWidget tf ;
        int line_width ;
#else
df_MakeAddModeCursor(
        XmDataFieldWidget tf,
        int line_width )
#endif /* _NO_PROTO */
{
   Screen *screen = XtScreen(tf);
   char pixmap_name[25];

   if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);
   sprintf(pixmap_name, "_XmDataF_AddMode_%d_%d",
	   XmTextF_cursor_height(tf), line_width);

   XmTextF_add_mode_cursor(tf) = (Pixmap) XmGetPixmapByDepth(screen, pixmap_name,
							  1, 0, 1);

   if (XmTextF_add_mode_cursor(tf) == XmUNSPECIFIED_PIXMAP) {
      GC fillGC;
      XtGCMask  valueMask;
      XGCValues values;
      unsigned int pix_width, pix_height, unused;
      Display *dpy = XtDisplay(tf);
      Pixmap stipple;
      XImage *image;
      Pixmap pixmap;
      int unused_origin;
      Window	root;
      
      pixmap = XmGetPixmapByDepth(screen, "50_foreground",
				   1, 0, 1);
      
      if (pixmap != XmUNSPECIFIED_PIXMAP) {
      	XGetGeometry(XtDisplay(tf), pixmap, &root, &unused_origin, 
		     &unused_origin, &pix_width, &pix_height, 
		     &unused, &unused);
      	image = XGetImage(XtDisplay(tf), (Drawable)pixmap, 0, 0,
			  pix_width, pix_height, AllPlanes,
			  XYPixmap);
			

      	stipple = XCreatePixmap(dpy, XtWindow(tf), 
				image->width, image->height,1);

        XmTextF_add_mode_cursor(tf) =  XCreatePixmap(dpy, XtWindow(tf),
						     XmTextF_cursor_width(tf),
			                             XmTextF_cursor_height(tf), 
						     1);

        fillGC = XCreateGC(dpy, XmTextF_add_mode_cursor(tf), 0, 
			   (XGCValues *)NULL);

        XPutImage(dpy, stipple, fillGC, image, 0, 0, 0, 0, image->width, 
	   	  image->height);

        XCopyArea(dpy, XmTextF_cursor(tf), XmTextF_add_mode_cursor(tf), 
	          fillGC, 0, 0, XmTextF_cursor_width(tf), 
                  XmTextF_cursor_height(tf), 0, 0);

        valueMask = (GCTile | GCFillStyle | GCForeground |
		     GCBackground | GCFunction);
        values.function = GXand;
        values.tile = stipple;
        values.fill_style = FillTiled;
        values.foreground = tf->primitive.foreground; 
        values.background = tf->core.background_pixel;

        XChangeGC(XtDisplay(tf), fillGC, valueMask, &values);

        XFillRectangle(dpy, XmTextF_add_mode_cursor(tf), fillGC,
		       0, 0, XmTextF_cursor_width(tf), 
                       XmTextF_cursor_height(tf));

        /* Install the pixmap for pixmap caching */
        _XmInstallPixmap(XmTextF_add_mode_cursor(tf),
		         XtScreen(tf), pixmap_name, 1, 0);

        XFreePixmap(dpy, stipple);
        XFreeGC(dpy, fillGC);
     }
  }
}

static void 
#ifdef _NO_PROTO
df_MakeCursors( tf )
        XmDataFieldWidget tf ;
#else
df_MakeCursors(
        XmDataFieldWidget tf )
#endif /* _NO_PROTO */
{
   Screen *screen = XtScreen(tf);
   int line_width = 1;

   if (!XtIsRealized((Widget) tf)) return;

   XmTextF_cursor_width(tf) = 5;
   XmTextF_cursor_height(tf) = XmTextF_font_ascent(tf) + XmTextF_font_descent(tf);

  /* setup parameters to make a thicker I-Beam */
   if (XmTextF_cursor_height(tf) > 19) {
      XmTextF_cursor_width(tf)++;
      line_width = 2;
   }

  /* Remove old ibeam off area */
   if (XmTextF_ibeam_off(tf) != XmUNSPECIFIED_PIXMAP)
      XFreePixmap(XtDisplay((Widget)tf), XmTextF_ibeam_off(tf));

  /* Remove old insert cursor */
   if (XmTextF_cursor(tf) != XmUNSPECIFIED_PIXMAP) {
       (void) XmDestroyPixmap(screen, XmTextF_cursor(tf));
       XmTextF_cursor(tf) = XmUNSPECIFIED_PIXMAP;
   }

  /* Remove old add mode cursor */
   if (XmTextF_add_mode_cursor(tf) != XmUNSPECIFIED_PIXMAP) {
       (void) XmDestroyPixmap(screen, XmTextF_add_mode_cursor(tf));
       XmTextF_add_mode_cursor(tf) = XmUNSPECIFIED_PIXMAP;
   }

  /* Remove old image_clip pixmap */
   if (XmTextF_image_clip(tf) != XmUNSPECIFIED_PIXMAP) {
       (void) XmDestroyPixmap(screen, XmTextF_image_clip(tf));
       XmTextF_image_clip(tf) = XmUNSPECIFIED_PIXMAP;
   }

  /* Create area in which to save text located underneath I beam */
   df_MakeIBeamOffArea(tf, MAX(XmTextF_cursor_height(tf)>>1, XmTextF_cursor_height(tf)),
		    XmTextF_cursor_height(tf));

  /* Create a new i-beam cursor */
   df_MakeIBeamStencil(tf, line_width);

  /* Create a new add_mode cursor */
   df_MakeAddModeCursor(tf, line_width);

   df_ResetClipOrigin(tf, False);

   if (XmTextF_overstrike(tf))
     XmTextF_cursor_width(tf) = XmTextF_cursor_height(tf) >> 1;
}

/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DropDestroyCB(w, clientData, callData)
    Widget      w;
    XtPointer   clientData;
    XtPointer   callData;
#else
df_DropDestroyCB(
    Widget      w,
    XtPointer   clientData,
    XtPointer   callData )
#endif /* NO_PROTO */
{
    df_DeleteDropContext(w);
    XtFree((char *)clientData);
}


/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DropTransferCallback( w, closure, seltype, type, value, length, format )
        Widget w ;
        XtPointer closure ;
        Atom *seltype ;
        Atom *type ;
        XtPointer value ;
        unsigned long *length ;
        int *format ;
#else
df_DropTransferCallback(
        Widget w,
        XtPointer closure,
        Atom *seltype,
        Atom *type,
        XtPointer value,
        unsigned long *length,
        int *format )
#endif /* _NO_PROTO */
{
    _XmTextDropTransferRec *transfer_rec = (_XmTextDropTransferRec *) closure;
    XmDataFieldWidget tf = (XmDataFieldWidget) transfer_rec->widget;
    Atom COMPOUND_TEXT = XmInternAtom(XtDisplay(w), "COMPOUND_TEXT", False);
    Atom CS_OF_LOCALE;
    XmTextPosition insertPosLeft, insertPosRight, left, right, cursorPos;
    int max_length = 0;
    Boolean local = XmTextF_has_primary(tf);
    char * total_tmp_value;
    wchar_t * wc_total_tmp_value;
    char ** tmp_value;
    int malloc_size = 0;
    int num_vals, status;
    Arg args[8];
    Cardinal n, i;
    unsigned long total_length = 0;
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    XTextProperty tmp_prop;
    Boolean replace = False;
    XmAnyCallbackStruct cb;

   /* When type = NULL, we are assuming a DELETE request has been requested */
    if (*type == XmInternAtom(XtDisplay(transfer_rec->widget), "NULL", False)) {
       if (transfer_rec->num_chars > 0 && transfer_rec->move) {
          XmTextF_prim_anchor(tf) = transfer_rec->insert_pos;
          cursorPos = transfer_rec->insert_pos + transfer_rec->num_chars;
          _XmDataFielddf_SetCursorPosition(tf, NULL, cursorPos,
					False, True);
          (void) df_SetDestination((Widget)tf, XmTextF_cursor_position(tf),
                                False, transfer_rec->timestamp);
          XmDataFieldSetSelection((Widget)tf, XmTextF_prim_anchor(tf),
				  XmTextF_cursor_position(tf),
                                  transfer_rec->timestamp);
       }
       if (value) {
	  XtFree((char *)value);
          value = NULL;
       }
       return;
    }

    status = XmbTextListToTextProperty(XtDisplay(transfer_rec->widget),
				      &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       CS_OF_LOCALE = tmp_prop.encoding;
    else
       CS_OF_LOCALE = 99999; /* XmbTextList... should never fail for XPCS
                              * characters.  But just in case someones
                              * Xlib is broken, this prevents a core dump.
                              */

    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

    if (!value || (*type != CS_OF_LOCALE && *type != COMPOUND_TEXT &&
                   *type != XA_STRING )) {
        n = 0;
        XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
        XtSetArg(args[n], XmNnumDropTransfers, 0); n++;
        XtSetValues(w, args, n);
        if (value) {
	   XtFree((char *)value);
	   value = NULL;
        }
        return;
    }

    insertPosLeft = insertPosRight = transfer_rec->insert_pos;

    if (*type == XA_STRING || *type == COMPOUND_TEXT) {
       /* value NEEDS TO BE FREED */
       tmp_prop.value = (unsigned char *) value; 
       tmp_prop.encoding = *type;
       tmp_prop.format = 8;
       tmp_prop.nitems = *length;
       status = 0;

       status = XmbTextPropertyToTextList(XtDisplay(transfer_rec->widget),
					  &tmp_prop, &tmp_value, &num_vals);

      /* if no conversion, num_vals is not changed */
       if (num_vals && (status == Success || status > 0)) {
          for (i = 0; i < num_vals ; i++)
              malloc_size += strlen(tmp_value[i]);

          total_tmp_value = XtMalloc ((unsigned) malloc_size + 1);
          total_tmp_value[0] = '\0';
          for (i = 0; i < num_vals ; i++)
             strcat(total_tmp_value, tmp_value[i]);
          total_length = strlen(total_tmp_value);
	  XFreeStringList(tmp_value);
       } else  {
          if (value) {
	     XtFree((char *)value);
	     value = NULL;
          }
          return;
       }
    } else {
       total_tmp_value = (char *)value;
       total_length = *length;
    }

    if (XmTextF_pending_delete(tf) && XmTextF_has_primary(tf) &&
       XmTextF_prim_pos_left(tf) != XmTextF_prim_pos_right(tf) &&
       insertPosLeft > XmTextF_prim_pos_left(tf) &&
       insertPosRight < XmTextF_prim_pos_right(tf)) {
      insertPosLeft = XmTextF_prim_pos_left(tf);
      insertPosRight = XmTextF_prim_pos_right(tf);
    }

    transfer_rec->num_chars = _XmDataFieldCountCharacters(tf, total_tmp_value, 
							  (int)total_length);

    _XmDataFieldDrawInsertionPoint(tf, False);

    if (transfer_rec->move && local) {
       max_length = XmTextF_max_length(tf);
       XmTextF_max_length(tf) = INT_MAX;
    }

    if (XmTextF_max_char_size(tf) == 1) {
       if (_XmDataFieldReplaceText(tf, NULL, insertPosLeft, insertPosRight,
				   (char *) total_tmp_value,
				   (int)total_length, False))
	  replace = True;
    } else {
       wc_total_tmp_value = (wchar_t*)XtMalloc((unsigned)
					       total_length * sizeof(wchar_t));
      /* Note: casting total_length to an int may result in a truncation. */
       total_length = mbstowcs(wc_total_tmp_value, total_tmp_value,
			       (int)total_length);
       if (_XmDataFieldReplaceText(tf, NULL, insertPosLeft, insertPosRight,
				   (char *) wc_total_tmp_value,
				   (int)total_length, False))
	  replace = True;
       XtFree((char*)wc_total_tmp_value);
    }

    if (replace) {
       XmTextF_pending_off(tf) = FALSE;
       if (transfer_rec->num_chars > 0 && !transfer_rec->move) {
          cursorPos = transfer_rec->insert_pos + transfer_rec->num_chars;
          _XmDataFielddf_SetCursorPosition(tf, NULL, cursorPos, 
					False, True);
          df_SetDestination((Widget)tf, XmTextF_cursor_position(tf), False,
			 transfer_rec->timestamp);
       }
       if (XmDataFieldGetSelectionPosition((Widget)tf, &left, &right)) {
          if (transfer_rec->move && left < transfer_rec->insert_pos)
	     transfer_rec->insert_pos -= transfer_rec->num_chars;
          if (XmTextF_cursor_position(tf) < left ||
	      XmTextF_cursor_position(tf) > right)
	     XmTextF_pending_off(tf) = TRUE;
       } else {
          if (!transfer_rec->move && !XmTextF_add_mode(tf) &&
              transfer_rec->num_chars != 0)
	     XmTextF_prim_anchor(tf) = insertPosLeft;
       }
       if (transfer_rec->move) {
          XmDropTransferEntryRec transferEntries[1];

          transferEntries[0].client_data = (XtPointer) transfer_rec;
          transferEntries[0].target = XmInternAtom(XtDisplay(w),"DELETE",False);
          XmDropTransferAdd(w, transferEntries, 1);
       }
       cb.reason = XmCR_VALUE_CHANGED;
       cb.event = (XEvent *)NULL;
       XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		          (XtPointer) &cb);
    }

    if (transfer_rec->move && local) {
       XmTextF_max_length(tf) = max_length;
    }

    XtFree(total_tmp_value);
    _XmDataFieldDrawInsertionPoint(tf, True);
}


static void
#ifdef _NO_PROTO
df_HandleDrop(w, cb)
        Widget w;
        XmDropProcCallbackStruct *cb;
#else
df_HandleDrop(
        Widget w,
        XmDropProcCallbackStruct *cb )
#endif /* _NO_PROTO */
{
    static XtCallbackRec dropdf_DestroyCB[] = { {df_DropDestroyCB, NULL},
                                             {(XtCallbackProc)NULL, NULL} };
    Widget drag_cont, initiator;
    Cardinal numExportTargets, n;
    Atom *exportTargets;
    Arg args[10];
    XmTextPosition insert_pos, left, right;
    Display *display = XtDisplay(w);

    drag_cont = cb->dragContext;

    n = 0;
    XtSetArg(args[n], XmNsourceWidget, &initiator); n++;
    XtSetArg(args[n], XmNexportTargets, &exportTargets); n++;
    XtSetArg(args[n], XmNnumExportTargets, &numExportTargets); n++;
    XtGetValues((Widget) drag_cont, args, n);
    
    insert_pos = df_GetPosFromX((XmDataFieldWidget) w, cb->x);

    if (cb->operation & XmDROP_MOVE && w == initiator &&
        XmDataFieldGetSelectionPosition(w, &left, &right) &&
        left != right && insert_pos >= left && insert_pos <= right) {
       XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
       XtSetArg(args[n], XmNnumDropTransfers, 0); n++;
    } else {
       XmDropTransferEntryRec transferEntries[2];
       XmDropTransferEntryRec *transferList = NULL;
       Atom TEXT = XmInternAtom(display, "TEXT", False);
       Atom COMPOUND_TEXT = XmInternAtom(display, "COMPOUND_TEXT", False);
       Atom CS_OF_LOCALE;
       char * tmp_string = "ABC"; /* these are characters in XPCS, so... safe */
       XTextProperty tmp_prop;
       _XmTextDropTransferRec *transfer_rec;
       Cardinal numTransfers = 0;
       Boolean locale_found = False;
       Boolean c_text_found = False;
       Boolean string_found = False;
       Boolean text_found = False;
       int status;

       status = XmbTextListToTextProperty(display, &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
       if (status == Success)
	  CS_OF_LOCALE = tmp_prop.encoding;
       else
	  CS_OF_LOCALE = 99999; /* XmbTextList... should never fail for XPCS
				 * characters.  But just in case someones
				 * Xlib is broken, this prevents a core dump.
				 */
       if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);


      /* intialize data to send to drop transfer callback */
       transfer_rec = (_XmTextDropTransferRec *)
		       XtMalloc(sizeof(_XmTextDropTransferRec));
       transfer_rec->widget = w;
       transfer_rec->insert_pos = insert_pos;
       transfer_rec->num_chars = 0;
       transfer_rec->timestamp = cb->timeStamp;
       transfer_rec->move = False;

       if (cb->operation & XmDROP_MOVE) {
          transfer_rec->move = True;
       } else {
          transfer_rec->move = False;
       }
          
       transferEntries[0].client_data = (XtPointer) transfer_rec;
       transferList = transferEntries;
       numTransfers = 1;

       for (n = 0; n < numExportTargets; n++) {
	 if (exportTargets[n] == CS_OF_LOCALE) {
	   transferEntries[0].target = CS_OF_LOCALE;
	   locale_found = True;
	   break;
	 }
	 if (exportTargets[n] == COMPOUND_TEXT) c_text_found = True;
	 if (exportTargets[n] == XA_STRING) string_found = True;
	 if (exportTargets[n] == TEXT) text_found = True;
       }
       
       n = 0;
       if (locale_found || c_text_found || string_found || text_found) {
	 if (!locale_found) {
	   if (c_text_found)
	     transferEntries[0].target = COMPOUND_TEXT;
	   else if (string_found)
	     transferEntries[0].target = XA_STRING;
	   else
	     transferEntries[0].target = TEXT;
	 }

	 if (cb->operation & XmDROP_MOVE || cb->operation & XmDROP_COPY) {
		XtSetArg(args[n], XmNdropTransfers, transferList); n++;
		XtSetArg(args[n], XmNnumDropTransfers, numTransfers); n++;
	 } else {
		XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
		XtSetArg(args[n], XmNnumDropTransfers, 0); n++;
	 }

       } else {
	 XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
	 XtSetArg(args[n], XmNnumDropTransfers, 0); n++;
       }

       dropdf_DestroyCB[0].closure = (XtPointer) transfer_rec;
       XtSetArg(args[n], XmNdestroyCallback, dropdf_DestroyCB); n++;
       XtSetArg(args[n], XmNtransferProc, df_DropTransferCallback); n++;
    }
    df_SetDropContext(w);
    XmDropTransferStart(drag_cont, args, n);
}


/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DragProcCallback(w, client, call)
        Widget w;
        XtPointer client;
        XtPointer call;
#else
df_DragProcCallback(
        Widget w,
        XtPointer client,
        XtPointer call )
#endif /* _NO_PROTO */
{
    XmDragProcCallbackStruct *cb = (XmDragProcCallbackStruct *)call;
    Widget drag_cont;
    Atom targets[4];
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    XTextProperty tmp_prop;
    Arg args[10];
    Atom *exp_targets;
    Cardinal num_exp_targets, n;
    int status = 0;

    status = XmbTextListToTextProperty(XtDisplay(w), &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       targets[0] = tmp_prop.encoding;
    else
       targets[0] = 99999; /* XmbTextList... should never fail for XPCS
                            * characters.  But just in case someones
                            * Xlib is broken, this prevents a core dump.
                            */
    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

    targets[1] = XmInternAtom(XtDisplay(w), "COMPOUND_TEXT", False);
    targets[2] = XA_STRING;
    targets[3] = XmInternAtom(XtDisplay(w), "TEXT", False);

    drag_cont = cb->dragContext;

    n = 0;
    XtSetArg(args[n], XmNexportTargets, &exp_targets); n++;
    XtSetArg(args[n], XmNnumExportTargets, &num_exp_targets); n++;
    XtGetValues(drag_cont, args, n);

    switch(cb->reason) {
      case XmCR_DROP_SITE_ENTER_MESSAGE:
	  if (XmTargetsAreCompatible(XtDisplay(drag_cont), exp_targets,
			      	     num_exp_targets, targets, 4))
             cb->dropSiteStatus = XmVALID_DROP_SITE;
          else
             cb->dropSiteStatus = XmINVALID_DROP_SITE;
          break;
      case XmCR_DROP_SITE_LEAVE_MESSAGE:
      case XmCR_DROP_SITE_MOTION_MESSAGE:
      case XmCR_OPERATION_CHANGED:
         /* we currently don't care about these messages */
	  break;
      default:
	/* other messages we consider invalid */
          cb->dropSiteStatus = XmINVALID_DROP_SITE;
	  break;
    }
}


/* ARGSUSED */
static void
#ifdef _NO_PROTO
df_DropProcCallback(w, client, call)
        Widget w;
        XtPointer client;
        XtPointer call;
#else
df_DropProcCallback(
        Widget w,
        XtPointer client,
        XtPointer call )
#endif /* _NO_PROTO */
{
    XmDropProcCallbackStruct *cb = (XmDropProcCallbackStruct *) call;

    if (cb->dropAction != XmDROP_HELP) {
       df_HandleDrop(w, cb);
    } else {
       Arg args[2];

       XtSetArg(args[0], XmNtransferStatus, XmTRANSFER_FAILURE);
       XtSetArg(args[1], XmNnumDropTransfers, 0);
       XmDropTransferStart(cb->dragContext, args, 2);
    }
}

static void
#ifdef _NO_PROTO
df_RegisterDropSite(w)
        Widget w ;
#else
df_RegisterDropSite(
        Widget w )
#endif /* _NO_PROTO */
{
    Atom targets[4];
    Arg args[10];
    int n;
    char * tmp_string = "ABC";  /* these are characters in XPCS, so... safe */
    XTextProperty tmp_prop;
    int status = 0;

    status = XmbTextListToTextProperty(XtDisplay(w), &tmp_string, 1,
                                      (XICCEncodingStyle)XTextStyle, &tmp_prop);
    if (status == Success)
       targets[0] = tmp_prop.encoding;
    else
       targets[0] = 99999; /* XmbTextList... should never fail for XPCS
                            * characters.  But just in case someones
                            * Xlib is broken, this prevents a core dump.
                            */
    if (tmp_prop.value != NULL) XFree((char *)tmp_prop.value);

    targets[1] = XmInternAtom(XtDisplay(w), "COMPOUND_TEXT", False);
    targets[2] = XA_STRING;
    targets[3] = XmInternAtom(XtDisplay(w), "TEXT", False);

    n = 0;
    XtSetArg(args[n], XmNimportTargets, targets); n++;
    XtSetArg(args[n], XmNnumImportTargets, 4); n++;
    XtSetArg(args[n], XmNdropProc, df_DragProcCallback); n++;
    XtSetArg(args[n], XmNdropProc, df_DropProcCallback); n++;
    XmDropSiteRegister(w, args, n);
}

/*
 * df_Initialize
 *    Intializes the text data and ensures that the data in new
 * is valid.
 */
/* ARGSUSED */
static void 
#ifdef _NO_PROTO
df_Initialize( request, new_w, args, num_args )
        Widget request ;
        Widget new_w ;
        ArgList args ;
        Cardinal *num_args ;
#else
df_Initialize(
        Widget request,
        Widget new_w,
        ArgList args,
        Cardinal *num_args )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget req_tf = (XmDataFieldWidget) request;
    XmDataFieldWidget new_tf = (XmDataFieldWidget) new_w;
    Dimension width, height;
  
    df_Validates(new_tf);

    df_InitializeTextStruct(new_tf);

    df_LoadGCs(new_tf, new_tf->core.background_pixel, 
	    new_tf->primitive.foreground ); 

    df_ComputeSize(new_tf, &width, &height);
  
    if (req_tf->core.width == 0)
       new_tf->core.width = width;
    if (req_tf->core.height == 0)
       new_tf->core.height = height;

    df_RegisterDropSite(new_w);
 
    if (XmTextF_verify_bell(new_tf) == (Boolean) XmDYNAMIC_BOOL)
    {
      if (_XmGetAudibleWarning(new_w) == XmBELL) 
	XmTextF_verify_bell(new_tf) = True;
      else
	XmTextF_verify_bell(new_tf) = False;
    }

#ifdef DEMO
    /* put up the guilt screen, if this is a demo version */
    _XmInitialIzeConverters( request );
#endif
}

static void 
#ifdef _NO_PROTO
df_Realize( w, valueMask, attributes )
        Widget w ;
        XtValueMask *valueMask ;
        XSetWindowAttributes *attributes ;
#else
df_Realize(
        Widget w,
        XtValueMask *valueMask,
        XSetWindowAttributes *attributes )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   XtCreateWindow(w, (unsigned int) InputOutput,
                   (Visual *) CopyFromParent, *valueMask, attributes);
   df_MakeCursors(tf);
   _XmDataFieldSetClipRect(tf);
}

static void 
#ifdef _NO_PROTO
df_Destroy( wid )
        Widget wid ;
#else
df_Destroy(
        Widget wid )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) wid ;
    Widget dest = XmGetDestination(XtDisplay(wid));

    if (dest == wid)
       _XmSetDestination(XtDisplay(wid), NULL); 

    if (XmTextF_timer_id(tf))
	XtRemoveTimeOut(XmTextF_timer_id(tf));

    if (XmTextF_has_rect(tf)) {
       TextFGCData gc_data = df_GetTextFGCData(wid);
       gc_data->tf = NULL;
    }

    if (XmTextF_max_char_size(tf) == 1)
       XtFree(XmTextF_value(tf));
    else
       XtFree((char *)XmTextF_wc_value(tf));

    XmDestroyPixmap(XtScreen(tf), XmTextF_stipple_tile(tf));

    XtReleaseGC(wid, XmTextF_gc(tf));
    XtReleaseGC(wid, XmTextF_image_gc(tf));
    XtReleaseGC(wid, XmTextF_save_gc(tf)); 

    XtFree((char *)XmTextF_highlight(tf).list);

    if (XmTextF_fontlist_created(tf))
       XmFontListFree((XmFontList)XmTextF_font_list(tf));

    if (XmTextF_add_mode_cursor(tf) != XmUNSPECIFIED_PIXMAP)
       (void) XmDestroyPixmap(XtScreen(tf), XmTextF_add_mode_cursor(tf));

    if (XmTextF_cursor(tf) != XmUNSPECIFIED_PIXMAP)
       (void) XmDestroyPixmap(XtScreen(tf), XmTextF_cursor(tf));

    if (XmTextF_ibeam_off(tf) != XmUNSPECIFIED_PIXMAP)
       XFreePixmap(XtDisplay((Widget)tf), XmTextF_ibeam_off(tf));

    if (XmTextF_image_clip(tf) != XmUNSPECIFIED_PIXMAP)
       XmDestroyPixmap(XtScreen(tf), XmTextF_image_clip(tf));

/*
 * Fix for HaL DTS 9841 - release the data for the selectionArray.
 */
    XtFree((char *)XmTextF_selection_array(tf));

    XtRemoveAllCallbacks(wid, XmNactivateCallback);
    XtRemoveAllCallbacks(wid, XmNlosingFocusCallback);
    XtRemoveAllCallbacks(wid, XmNfocusCallback);
    XtRemoveAllCallbacks(wid, XmNmodifyVerifyCallback);
    XtRemoveAllCallbacks(wid, XmNmotionVerifyCallback);
    XtRemoveAllCallbacks(wid, XmNvalueChangedCallback);
    XtRemoveAllCallbacks(wid, XmNgainPrimaryCallback);
    XtRemoveAllCallbacks(wid, XmNlosePrimaryCallback);

    XmImUnregister(wid);

    XtFree((char*)XmDataField_picture_source(tf));
    if(XmDataField_picture(tf)) 
	    XmPictureDelete(XmDataField_picture(tf));
}

static void 
#ifdef _NO_PROTO
df_Resize( w )
        Widget w ;
#else
df_Resize(
        Widget w )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;

  XmTextF_do_resize(tf) = False;

  _XmDataFieldSetClipRect(tf);

  if (XmDataField_alignment(tf) == XmALIGNMENT_END)
      XmTextF_h_offset(tf) = 0;
  else
      XmTextF_h_offset(tf) = XmTextF_margin_width(tf) +
	  tf->primitive.shadow_thickness + tf->primitive.highlight_thickness;

  XmTextF_refresh_ibeam_off(tf) = True;

  (void) df_AdjustText(tf, XmTextF_cursor_position(tf), True);

  XmTextF_do_resize(tf) = True;
}
 

/************************************************************************
 *
 *  df_QueryGeometry
 *
 ************************************************************************/
static XtGeometryResult 
#ifdef _NO_PROTO
df_QueryGeometry( widget, intended, desired )
        Widget widget ;
        XtWidgetGeometry *intended ;
        XtWidgetGeometry *desired ;
#else
df_QueryGeometry(
        Widget widget,
        XtWidgetGeometry *intended,
        XtWidgetGeometry *desired )
#endif /* _NO_PROTO */
{
    /* this function deals with resizeWidth False */
    df_ComputeSize((XmDataFieldWidget) widget, 
		&desired->width, &desired->height);

    return _XmGMReplyToQueryGeometry(widget, intended, desired) ;
}


/*
 * Redisplay will redraw shadows, borders, and text.
 */
/* ARGSUSED */
static void 
#ifdef _NO_PROTO
DataFieldExpose( w, event, region )
        Widget w ;
        XEvent *event ;
        Region region ;
#else
DataFieldExpose(
        Widget w,
        XEvent *event,
        Region region )
#endif /* _NO_PROTO */
{
  XmDataFieldWidget tf = (XmDataFieldWidget) w;
  XGCValues values;
  

  if (event->xany.type != Expose) return;

  XmTextF_do_resize(tf) = False;

  if (!XmTextF_has_rect(tf)) _XmDataFieldSetClipRect(tf);

  /* I can get here even though the widget isn't visible (i.e. my parent is
   * sized so that I have nothing visible.  In this case, capturing the putback
   * area yields garbage...  And if this area is not in an area where text
   * will be drawn (i.e. forcing something new/valid to be there next time I
   * go to capture it) the garbage persists.  To prevent this, initialize the
   * putback area and then update it to a solid background color.
   */

  XmTextF_refresh_ibeam_off(tf) = False;
  values.foreground = tf->core.background_pixel;
  XChangeGC(XtDisplay(w), XmTextF_save_gc(tf), GCForeground, &values);
  XFillRectangle(XtDisplay(w), XmTextF_ibeam_off(tf), XmTextF_save_gc(tf), 0, 0,
		    XmTextF_cursor_width(tf), XmTextF_cursor_height(tf));
  values.foreground = tf->primitive.foreground;
  XChangeGC(XtDisplay(w), XmTextF_save_gc(tf), GCForeground, &values);

  _XmDataFieldDrawInsertionPoint(tf, False);

  if (XtIsRealized((Widget)tf)) {
     if (tf->primitive.shadow_thickness > 0)
       XmeDrawShadows(XtDisplay(tf), XtWindow(tf),
             tf->primitive.bottom_shadow_GC, 
             tf->primitive.top_shadow_GC,
             (int) tf->primitive.highlight_thickness,
             (int) tf->primitive.highlight_thickness,
             (int) (tf->core.width - (2 * tf->primitive.highlight_thickness)),
             (int) (tf->core.height - (2 * tf->primitive.highlight_thickness)),
             (int) tf->primitive.shadow_thickness,
             XmSHADOW_OUT);

     if (tf->primitive.highlighted)
     {
         XtWidgetProc bhl;

         _XmProcessLock();
         bhl = ((XmDataFieldWidgetClass) XtClass(tf))->primitive_class.border_highlight;
         _XmProcessUnlock();
         
         if(bhl)
         {   
             (*bhl)( (Widget) tf) ;
         } 
     } 
     else
     {
         XtWidgetProc buhl;

         _XmProcessLock();
         buhl = ((XmDataFieldWidgetClass) XtClass(tf))->primitive_class.border_unhighlight;
         _XmProcessUnlock();

         if(buhl)
         {
            (*buhl)( (Widget) tf) ;
         } 
     } 

     df_RedisplayText(tf, 0, XmTextF_string_length(tf));
  }

  XmTextF_refresh_ibeam_off(tf) = True;

  _XmDataFieldDrawInsertionPoint(tf, True);

  XmTextF_do_resize(tf) = True;
}

/*
 *
 * df_SetValues
 *    Checks the new text data and ensures that the data is valid.
 * Invalid values will be rejected and changed back to the old
 * values.
 *
 */
/* ARGSUSED */
static Boolean 
#ifdef _NO_PROTO
df_SetValues( old, request, new_w, args, num_args )
        Widget old ;
        Widget request ;
        Widget new_w ;
        ArgList args ;
        Cardinal *num_args ;
#else
df_SetValues(
        Widget old,
        Widget request,
        Widget new_w,
        ArgList args,
        Cardinal *num_args )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget new_tf = (XmDataFieldWidget) new_w;
    XmDataFieldWidget old_tf = (XmDataFieldWidget) old;
    Boolean cursor_pos_set = False;
    Boolean new_size = False;
    Boolean redisplay = False;
    Boolean redisplay_text = False;
    Boolean new_font = False;
    Boolean mod_ver_ret = False;
    Boolean diff_values = False;
    Dimension new_width = new_tf->core.width;
    Dimension new_height = new_tf->core.height;
    Arg im_args[6];
    XPoint xmim_point;
    XmTextPosition new_position = 0;
    XmTextPosition newInsert;
    int n = 0;

    if (new_w->core.being_destroyed) return False;

    XmTextF_in_setvalues(new_tf) = True;
    XmTextF_redisplay(new_tf) = False;

     /************************************
     * ICS DataField specific stuff here *
     ************************************/
    
    /*
     * This is a patch-around to a bug we seem to have exposed.
     * The special redisplay handling has been broken somehow with the
     * end result that the DataField doesn't redisplay itself
     * correctly when its XmNvalue is set.  This just hacks around the
     * problem.
     */
    if(XmTextF_value(old_tf) != XmTextF_value(new_tf)) {
	redisplay = True;
    }

    if (XmDataField_picture_source(old_tf) != XmDataField_picture_source(new_tf))
    {
	/*
	 * Delete what's there
	 */
	XtFree((char*)XmDataField_picture_source(old_tf));
	XmDataField_picture_source(new_tf) = XtNewString(XmDataField_picture_source(new_tf));
	if(XmDataField_picture(new_tf)) {
	    XmPictureDelete(XmDataField_picture(new_tf));
	    XmDataField_picture(new_tf) = NULL;
	}

	/*
	 * And make a new one if we have to
	 */
	if(XmDataField_picture_source(new_tf)) {
	    XmDataField_picture(new_tf) = XmParsePicture(XmDataField_picture_source(new_tf));
	}

	/*
	 * Finally register (or remove) the callback
	 */
	if(XmDataField_picture(new_tf)) {
	    XtAddCallback((Widget)new_tf, XmNmodifyVerifyCallback,
			  PictureVerifyCallback, NULL);
	} else {
	    XtRemoveCallback((Widget)new_tf, XmNmodifyVerifyCallback,
			     PictureVerifyCallback, NULL);
	}


    }

    if (XmDataField_alignment(old_tf) != XmDataField_alignment(new_tf))
    {
	if (XmDataField_alignment(new_tf) == XmALIGNMENT_END)
	    XmTextF_h_offset(new_tf) = XmTextF_new_h_offset(new_tf) = 0;
	else
	    XmTextF_h_offset(new_tf) = XmTextF_new_h_offset(new_tf) = 
		XmTextF_margin_width(new_tf) +
		new_tf->primitive.shadow_thickness +
		new_tf->primitive.highlight_thickness;

	redisplay = True;
    }

   /* If new cursor position, copy the old cursor pos to the new widget
    * so that when we turn off the i-beam, the current location (old
    * widget) is used, but the new i-beam parameters (on/off, state, ...)
    * are utilized.  Then move the cursor.  Otherwise, just turn off
    * the i-beam. */

    if (XmTextF_cursor_position(new_tf) != XmTextF_cursor_position(old_tf)) {
       new_position = XmTextF_cursor_position(new_tf) ;
       XmTextF_cursor_position(new_tf) = XmTextF_cursor_position(old_tf);
       _XmDataFieldDrawInsertionPoint(old_tf, False);
       XmTextF_blink_on(new_tf) = XmTextF_blink_on(old_tf);
       XmTextF_cursor_on(new_tf) = XmTextF_cursor_on(old_tf);
       _XmDataFielddf_SetCursorPosition(new_tf, NULL, new_position,
				     True, True);
       (void) df_SetDestination(new_w, XmTextF_cursor_position(new_tf), False,
			     XtLastTimestampProcessed(XtDisplay(new_w)));
       cursor_pos_set = True;
    } else {
      int ix;
      
      for (ix = 0; ix < *num_args; ix++)
	if (strcmp(args[ix].name, XmNcursorPosition) == 0) {
	  cursor_pos_set = True;
	  new_position = XmTextF_cursor_position(new_tf);
	  break;
	}
      
      _XmDataFieldDrawInsertionPoint(old_tf, False);
      XmTextF_blink_on(new_tf) = XmTextF_blink_on(old_tf);
      XmTextF_cursor_on(new_tf) = XmTextF_cursor_on(old_tf);
    }

    if (new_w->core.sensitive == False &&
        XmTextF_has_destination(new_tf)) {
       (void) df_SetDestination(new_w, XmTextF_cursor_position(new_tf),
			     True, XtLastTimestampProcessed(XtDisplay(new_w)));
    }

    if (XmTextF_selection_array(new_tf) == NULL) 
       XmTextF_selection_array(new_tf) = XmTextF_selection_array(old_tf);

    if (XmTextF_selection_array_count(new_tf) <= 0) 
       XmTextF_selection_array_count(new_tf) = XmTextF_selection_array_count(old_tf);

/*
 * Fix for HaL DTS 9841 - If the new and old selectionArrays do not match,
 *			  free the old array and then copy the new array.
 */
    if (XmTextF_selection_array(new_tf) != XmTextF_selection_array(old_tf))
    {
      XtPointer temp_ptr;

      XtFree((char *)XmTextF_selection_array(old_tf));
      temp_ptr = (XtPointer)XmTextF_selection_array(new_tf);
      XmTextF_selection_array(new_tf) = (XmTextScanType *)XtMalloc (
                 XmTextF_selection_array_count(new_tf) * sizeof(XmTextScanType));
      memcpy((void *)XmTextF_selection_array(new_tf), (void *)temp_ptr,
             (XmTextF_selection_array_count(new_tf) * sizeof(XmTextScanType)));
    }
/*
 * End fix for HaL DTS 9841
 */


   /* Make sure the new_tf cursor position is a valid value.
    */
    if (XmTextF_cursor_position(new_tf) < 0) {
       XmeWarning (new_w, MSG1);
       XmTextF_cursor_position(new_tf) = XmTextF_cursor_position(old_tf);
       cursor_pos_set = False;
    }

    if (XmTextF_font_list(new_tf)!= XmTextF_font_list(old_tf)) {
       new_font = True;
       if (XmTextF_font_list(new_tf) == NULL)
          XmTextF_font_list(new_tf) = _XmGetDefaultFontList(new_w, XmTEXT_FONTLIST);
       XmTextF_font_list(new_tf) =
			    (XmFontList)XmFontListCopy(XmTextF_font_list(new_tf));
       if (!df_LoadFontMetrics(new_tf)){ /* Fails if font set required but not
                                       * available. */
          XmFontListFree((XmFontList)XmTextF_font_list(new_tf));
          XmTextF_font_list(new_tf) = XmTextF_font_list(old_tf);
          (void)df_LoadFontMetrics(new_tf); /* it *was* correct, so re-use it */
          new_font = False;
       } else {
          XtSetArg(im_args[n], XmNfontList, XmTextF_font_list(new_tf)); n++;
          redisplay = True;
       }
    }

    /* Four cases to handle for value:
     *   1. user set both XmNvalue and XmNwcValue.
     *   2. user set the opposite resource (i.e. value is a char*
     *      and user set XmNwcValue, or vice versa).
     *   3. user set the corresponding resource (i.e. value is a char*
     *      and user set XmNValue, or vice versa).
     *   4. user set neither XmNValue nor XmNwcValue
     */

    /* OSF says:  if XmNvalueWcs set, it overrides all else */

     if (XmTextF_max_char_size(new_tf) == 1) {  
       /* wc_value on new will be NULL unless XmNvalueWcs was set.   */
        if (XmTextF_wc_value(new_tf) != NULL){ /* must be new if MB_CUR... == 1 */
           df_ValidateString(new_tf, (char*) XmTextF_wc_value(new_tf), True);
           diff_values = True;
        } else if (XmTextF_value(new_tf) != XmTextF_value(old_tf)) {
           diff_values = True;
           if (XmTextF_value(new_tf) == NULL) {
              df_ValidateString(new_tf, "", False);
           } else
              df_ValidateString(new_tf, XmTextF_value(new_tf), False);
        } /* else, no change so don't do anything */
     } else {
        if (XmTextF_wc_value(new_tf) != XmTextF_wc_value(old_tf)) {
           diff_values = True;
           if (XmTextF_wc_value(new_tf) == NULL) {
              XmTextF_wc_value(new_tf) = (wchar_t*) XtMalloc(sizeof(wchar_t));
              *XmTextF_wc_value(new_tf) = (wchar_t)NULL;
           }
           df_ValidateString(new_tf, (char*)XmTextF_wc_value(new_tf), True);
        } else if (XmTextF_value(new_tf) != XmTextF_value(old_tf)) {
           /* Someone set XmNvalue */
           diff_values = True;
           if (XmTextF_value(new_tf) == NULL)
              df_ValidateString(new_tf, "", True);
           else
              df_ValidateString(new_tf, XmTextF_value(new_tf), False);

        } /* else, no change so don't do anything */
     }

    if (diff_values) { /* old value != new value */
       Boolean do_it = True;
      /* If there are modify verify callbacks, verify that we want to continue
       * the action.
       */
       if (XmTextF_modify_verify_callback(new_tf) || 
	   XmTextF_wcs_modify_verify_callback(new_tf)) {
         /* If the function df_ModifyVerify() returns false then don't
          * continue with the action.
          */
	  char *temp, *old;
	  int free_insert;
          XmTextPosition fromPos = 0, toPos;
          toPos = XmTextF_string_length(old_tf);
	  if (XmTextF_max_char_size(new_tf) == 1) {
	     temp = XmTextF_value(new_tf);
	     mod_ver_ret = df_ModifyVerify(new_tf, NULL, &fromPos, &toPos,
					&temp, &XmTextF_string_length(new_tf),
					&newInsert, &free_insert);
	  } else {
	     old = temp = XtMalloc((unsigned)((XmTextF_string_length(new_tf) + 1) *
					      XmTextF_max_char_size(new_tf)));
	     (void)wcstombs(temp, XmTextF_wc_value(new_tf), 
	         (XmTextF_string_length(new_tf) + 1) * XmTextF_max_char_size(new_tf));
	     mod_ver_ret = df_ModifyVerify(new_tf, NULL, &fromPos, &toPos, &temp,
					&XmTextF_string_length(new_tf), &newInsert,
					&free_insert);
	     if (old != temp) XtFree (old);
          }
	  if (free_insert) XtFree(temp);
          if (!mod_ver_ret) {
             if (XmTextF_verify_bell(new_tf)) XBell(XtDisplay(new_w), 0);
	     if (XmTextF_max_char_size(new_tf) == 1) {
                XmTextF_value(new_tf) = (char *) memcpy(
					   XtRealloc(XmTextF_value(new_tf),
                                           (unsigned)XmTextF_size_allocd(old_tf)),
                                           (void*)XmTextF_value(old_tf),
					   XmTextF_string_length(old_tf) + 1);
                XmTextF_string_length(new_tf) = XmTextF_string_length(old_tf);
                XmTextF_size_allocd(new_tf) = XmTextF_size_allocd(old_tf);
                XtFree(XmTextF_value(old_tf));
             } else {
		/* realloc to old size, cast to wchar_t*, and copy the data */
		XmTextF_wc_value(new_tf) = (wchar_t*)memcpy(
		       XtRealloc((char *)XmTextF_wc_value(new_tf),
                       (unsigned)XmTextF_size_allocd(old_tf)),
                       (void*)XmTextF_wc_value(old_tf),
		       (unsigned) XmTextF_size_allocd(old_tf));

                XmTextF_string_length(new_tf) = XmTextF_string_length(old_tf);
                XmTextF_size_allocd(new_tf) = XmTextF_size_allocd(old_tf);
                XtFree((char *)XmTextF_wc_value(old_tf));
	     }
             do_it = False;
          }
       }


       if (do_it) {
          XmAnyCallbackStruct cb;

	  if (XmTextF_max_char_size(new_tf) == 1)
             XtFree(XmTextF_value(old_tf));
	  else
             XtFree((char *)XmTextF_wc_value(old_tf));

          XmDataFieldSetHighlight(new_w, XmTextF_prim_pos_left(new_tf),
			          XmTextF_prim_pos_right(new_tf),
				  XmHIGHLIGHT_NORMAL);

          XmTextF_pending_off(new_tf) = True;    

	  /* if new_position was > XmTextF_string_length(old_tf), last time
	   * the df_SetCursorPosition didn't take.
	   */
          if (!cursor_pos_set || new_position > XmTextF_string_length(old_tf)){
             _XmDataFielddf_SetCursorPosition(new_tf, NULL, new_position,
					   True, False);
             if (XmTextF_has_destination(new_tf))
                (void) df_SetDestination(new_w, XmTextF_cursor_position(new_tf),
			     False, XtLastTimestampProcessed(XtDisplay(new_w)));
	  }

          if (XmTextF_resize_width(new_tf) && XmTextF_do_resize(new_tf))
             df_AdjustSize(new_tf);
          else {
	      if (XmDataField_alignment(new_tf) == XmALIGNMENT_END)
		  XmTextF_h_offset(new_tf) = 0;
	      else
		  XmTextF_h_offset(new_tf) = XmTextF_margin_width(new_tf) + 
		      new_tf->primitive.shadow_thickness +
		      new_tf->primitive.highlight_thickness;

             if (!df_AdjustText(new_tf, XmTextF_cursor_position(new_tf), False))
                redisplay_text = True;
          }

          cb.reason = XmCR_VALUE_CHANGED;
          cb.event = NULL;
          XtCallCallbackList(new_w, XmTextF_value_changed_callback(new_tf),
			     (XtPointer) &cb);

       }
    }

    if (new_tf->primitive.foreground != old_tf->primitive.foreground ||
        XmTextF_font_list(new_tf)!= XmTextF_font_list(old_tf) ||
        new_tf->core.background_pixel != old_tf->core.background_pixel) {
       df_LoadGCs(new_tf, new_tf->primitive.foreground,
			 new_tf->core.background_pixel);
       df_MakeCursors(new_tf);
       _XmDataFieldSetClipRect(new_tf);
       if (XmTextF_have_inverted_image_gc(new_tf)){
	  XmTextF_have_inverted_image_gc(new_tf) = False;
          df_InvertImageGC(new_tf);
       }
       redisplay = True;
       XtSetArg(im_args[n], XmNbackground, new_tf->core.background_pixel); n++;
       XtSetArg(im_args[n], XmNforeground, new_tf->primitive.foreground); n++;
    }

    if (XmTextF_has_focus(new_tf) && XtIsSensitive((Widget)new_tf) &&
        XmTextF_blink_rate(new_tf) != XmTextF_blink_rate(old_tf)) {

        if (XmTextF_blink_rate(new_tf) == 0) {
            XmTextF_blink_on(new_tf) = True;
            if (XmTextF_timer_id(new_tf)) {
                XtRemoveTimeOut(XmTextF_timer_id(new_tf));
                XmTextF_timer_id(new_tf) = (XtIntervalId)0;
            }
        } else if (XmTextF_timer_id(new_tf) == (XtIntervalId)0) {
           XmTextF_timer_id(new_tf) =
		 XtAppAddTimeOut(XtWidgetToApplicationContext(new_w),
				 (unsigned long)XmTextF_blink_rate(new_tf),
                                 df_HandleTimer,
                                 (XtPointer) new_tf);
        }
        df_BlinkInsertionPoint(new_tf);
    }

    if (XmTextF_margin_height(new_tf) != XmTextF_margin_height(old_tf)) {
       XmTextF_margin_top(new_tf) = XmTextF_margin_height(new_tf);
       XmTextF_margin_bottom(new_tf) = XmTextF_margin_height(new_tf);
    }

    new_size = XmTextF_margin_width(new_tf) != XmTextF_margin_width(old_tf) ||
               XmTextF_margin_height(new_tf) != XmTextF_margin_height(old_tf) ||
               XmTextF_font_list(new_tf) != XmTextF_font_list(old_tf) ||
	       new_tf->primitive.highlight_thickness !=
		 old_tf->primitive.highlight_thickness ||
	       new_tf->primitive.shadow_thickness !=
		 old_tf->primitive.shadow_thickness;
    

    if (XmTextF_columns(new_tf) < 0) {
       XmeWarning (new_w, MSG7);
       XmTextF_columns(new_tf) = XmTextF_columns(old_tf);
    }

    if (!(new_width != old_tf->core.width &&
	  new_height != old_tf->core.height)) {
       if (XmTextF_columns(new_tf) != XmTextF_columns(old_tf) || new_size) {
	  Dimension width, height;

	  df_ComputeSize(new_tf, &width, &height);
	  df_AdjustText(new_tf, 0, False);

	  if (new_width == old_tf->core.width)
	     new_w->core.width = width;
	  if (new_height == old_tf->core.height)
	     new_w->core.height = height;

	  if (XmDataField_alignment(new_tf) == XmALIGNMENT_END)
	      XmTextF_h_offset(new_tf) = 0;
	  else
	      XmTextF_h_offset(new_tf) = XmTextF_margin_width(new_tf) +
		  new_tf->primitive.shadow_thickness +
		  new_tf->primitive.highlight_thickness;

	  redisplay = True;
       }
    } else {
       if (new_width != new_tf->core.width)
          new_tf->core.width = new_width;
       if (new_height != new_tf->core.height)
          new_tf->core.height = new_height;
    }

    XmTextF_refresh_ibeam_off(new_tf) = 1; /* force update of putback area */

    _XmDataFieldDrawInsertionPoint(new_tf, True);

    if (XtIsSensitive((Widget)new_tf) != XtIsSensitive((Widget)old_tf)) {
       if (XtIsSensitive(new_w)) {
          _XmDataFieldDrawInsertionPoint(new_tf, False);
          XmTextF_blink_on(new_tf) = False;
          _XmDataFToggleCursorGC(new_w);
         _XmDataFieldDrawInsertionPoint(new_tf, True);
       } else {
          if (XmTextF_has_focus(new_tf)) {
             XmTextF_has_focus(new_tf) = False;
             df_ChangeBlinkBehavior(new_tf, False);
             _XmDataFieldDrawInsertionPoint(new_tf, False);
             _XmDataFToggleCursorGC(new_w);
             XmTextF_blink_on(new_tf) = True;
             _XmDataFieldDrawInsertionPoint(new_tf, True);
          }
       }
       if (XmTextF_string_length(new_tf) > 0) redisplay = True;
    }

    df_GetXYFromPos(new_tf, XmTextF_cursor_position(new_tf), &xmim_point.x, 
		 &xmim_point.y);

    if (XmTextF_editable(old_tf) != XmTextF_editable(new_tf)) {
       Boolean editable = XmTextF_editable(new_tf);
       XmTextF_editable(new_tf) = XmTextF_editable(old_tf);
       XmDataFieldSetEditable(new_w, editable);
    }

    XtSetArg(im_args[n], XmNbackgroundPixmap,
	     new_tf->core.background_pixmap); n++;
    XtSetArg(im_args[n], XmNspotLocation, &xmim_point); n++;
    XtSetArg(im_args[n], XmNlineSpace, 
	     XmTextF_font_ascent(new_tf) + XmTextF_font_descent(new_tf)); n++;
    XmImSetValues((Widget)new_tf, im_args, n);

    if (new_font) XmFontListFree((XmFontList)XmTextF_font_list(old_tf));

    if (!redisplay) redisplay = XmTextF_redisplay(new_tf);

    /* If I'm forced to redisplay, then actual widget won't be updated
     * until the expose proc.  Force the ibeam putback to be refreshed
     * at expose time so that it reflects true visual state of the
     * widget.  */

    if (redisplay) XmTextF_refresh_ibeam_off(new_tf) = True;

    XmTextF_in_setvalues(new_tf) = False;

    /* 
     * Force new clip rectangles to be computed during redisplay,
     * *after* XtSetValues decides on final geometry. 
     */
    if (redisplay) XmTextF_has_rect(new_tf) = False; 

    if ((!XmTextF_editable(new_tf) || !XtIsSensitive(new_w)) &&
        XmTextF_has_destination(new_tf))
       (void) df_SetDestination(new_w, 0, False, (Time)0);

    /* don't shrink to nothing */
    if (new_tf->core.width == 0) new_tf->core.width = old_tf->core.width;
    if (new_tf->core.height == 0) new_tf->core.height = old_tf->core.height;

    if (!redisplay && redisplay_text) 
      df_RedisplayText(new_tf, 0, XmTextF_string_length(new_tf));

    return redisplay;
}

static Boolean 
#ifdef _NO_PROTO
DataFieldRemove( w, event)
        Widget w ;
        XEvent *event ;
#else
DataFieldRemove(
        Widget w,
	XEvent *event)
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmTextPosition left, right;
   XmAnyCallbackStruct cb;

   if (XmTextF_editable(tf) == False)
      return False;

   if (!XmDataFieldGetSelectionPosition(w, &left, &right) || left == right) {
      XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);
      return False;
   }

   if (_XmDataFieldReplaceText(tf, event, left, right, NULL, 0, True)){
      XmDataFieldSetSelection(w, XmTextF_cursor_position(tf),
                              XmTextF_cursor_position(tf),
			      XtLastTimestampProcessed(XtDisplay(w)));
      cb.reason = XmCR_VALUE_CHANGED;
      cb.event = event;
      XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		         (XtPointer) &cb);
   }
   XmTextF_prim_anchor(tf) = XmTextF_cursor_position(tf);

   return True;
}

/***********************************<->***************************************

 *                              Public Functions                             *
 ***********************************<->***************************************/

char * 
#ifdef _NO_PROTO
XmDataFieldGetString( w )
        Widget w ;
#else
XmDataFieldGetString(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    char *temp_str;
    int ret_val = 0;

    if (XmTextF_string_length(tf) > 0) 
    {
	if (XmTextF_max_char_size(tf) == 1) 
	{
	    temp_str = XtNewString(XmTextF_value(tf));
	    return(temp_str);
	} 
	else 
	{
	    temp_str = (char *) XtMalloc((unsigned) XmTextF_max_char_size(tf) * 
					 (XmTextF_string_length(tf) + 1));
	    ret_val = wcstombs(temp_str, XmTextF_wc_value(tf), 
			       (XmTextF_string_length(tf) + 1) * 
			       XmTextF_max_char_size(tf));
	    if (ret_val < 0) 
	    {
		temp_str[0] = '\0';
	    }
	    return temp_str;
	}
    } else 
    {
      return(XtNewString(""));
    }
}

int 
#ifdef _NO_PROTO
XmDataFieldGetSubstring( widget, start, num_chars, buf_size, buffer )
        Widget widget;
        XmTextPosition start;
        int num_chars;
        int buf_size;
        char *buffer;
#else
XmDataFieldGetSubstring(
	Widget widget,
        XmTextPosition start,
        int num_chars,
        int buf_size,
        char *buffer )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) widget;
    int ret_value = XmCOPY_SUCCEEDED;
    int n_bytes = 0;
    int wcs_ret = 0;

    if (XmTextF_max_char_size(tf) != 1)
    {
	n_bytes = _XmDataFieldCountBytes(tf, XmTextF_wc_value(tf)+start, num_chars);
    }
    else
    {
	n_bytes = num_chars; 
    }

    if (buf_size < n_bytes + 1 )
    {
	return XmCOPY_FAILED;
    }

    if (start + num_chars > XmTextF_string_length(tf)) 
    {
	num_chars = (int) (XmTextF_string_length(tf) - start);
	if (XmTextF_max_char_size(tf) != 1)
	{
	    n_bytes = _XmDataFieldCountBytes(tf, XmTextF_wc_value(tf)+start,
					     num_chars);
	}
	else
	{
	    n_bytes = num_chars; 
	}
	ret_value = XmCOPY_TRUNCATED;
    }
      
    if (num_chars > 0) {
	if (XmTextF_max_char_size(tf) == 1) 
	{
	    (void)memcpy((void*)buffer, (void*)&XmTextF_value(tf)[start], num_chars);
	} 
	else 
	{
	    wcs_ret = wcstombs(buffer, &XmTextF_wc_value(tf)[start], 
			       n_bytes);
	    if (wcs_ret < 0) n_bytes = 0;
	}
	buffer[n_bytes] = '\0';
    } 
    else
    {
	ret_value = XmCOPY_FAILED;
    }

    return (ret_value);
}


wchar_t *
#ifdef _NO_PROTO
XmDataFieldGetStringWcs( w )
        Widget w ;
#else
XmDataFieldGetStringWcs(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    wchar_t *temp_wcs;
    int num_wcs = 0;

    if (XmTextF_string_length(tf) > 0) 
    {
	temp_wcs = (wchar_t*) XtMalloc((unsigned) sizeof(wchar_t) *
				       (XmTextF_string_length(tf) + 1));
	if (XmTextF_max_char_size(tf) != 1) 
	{
	    (void)memcpy((void*)temp_wcs, (void*)XmTextF_wc_value(tf), 
			 sizeof(wchar_t) * (XmTextF_string_length(tf) + 1));
	} 
	else 
	{
	    num_wcs = mbstowcs(temp_wcs, XmTextF_value(tf),
			       XmTextF_string_length(tf) + 1);
	}
	return temp_wcs;
    } 
    else 
    {
	temp_wcs = (wchar_t*) XtMalloc((unsigned) sizeof(wchar_t));
	temp_wcs[0] = (wchar_t)0L; /* put a wchar_t NULL in position 0 */
	return temp_wcs;
    }
}

int 
#ifdef _NO_PROTO
XmDataFieldGetSubstringWcs( widget, start, num_chars, buf_size, buffer )
        Widget widget;
        XmTextPosition start;
        int num_chars;
        int buf_size;
        wchar_t *buffer;
#else
XmDataFieldGetSubstringWcs(
	Widget widget,
        XmTextPosition start,
        int num_chars,
        int buf_size,
        wchar_t *buffer )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) widget;
    int ret_value = XmCOPY_SUCCEEDED;
    int num_wcs = 0;

    if (start + num_chars > XmTextF_string_length(tf)) 
    {
	num_chars = (int) (XmTextF_string_length(tf) - start);
	ret_value = XmCOPY_TRUNCATED;
    }
      
    if (buf_size < num_chars + 1 ) 
    {
	return XmCOPY_FAILED;
    }

    if (num_chars > 0) 
    {
	if (XmTextF_max_char_size(tf) == 1) 
	{
	    num_wcs = mbstowcs(buffer, &XmTextF_value(tf)[start], num_chars);
	    if (num_wcs < 0) num_chars = 0;
	} 
	else 
	{
	    (void)memcpy((void*)buffer, (void*)&XmTextF_wc_value(tf)[start], 
			 (size_t) num_chars * sizeof(wchar_t));
	}
	buffer[num_chars] = '\0';
    } else if (num_chars == 0) {
	buffer[num_chars] = '\0';
    } 
    else
    {
      ret_value = XmCOPY_FAILED;
    }

   return (ret_value);
}


XmTextPosition 
#ifdef _NO_PROTO
XmDataFieldGetLastPosition( w )
        Widget w ;
#else
XmDataFieldGetLastPosition(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition ret_val;

    ret_val = XmTextF_string_length(tf);

   return(ret_val);
}

void 
#ifdef _NO_PROTO
XmDataFieldSetString( w, value )
        Widget w ;
        char *value ;
#else
XmDataFieldSetString(
        Widget w,
        char *value )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmAnyCallbackStruct cb;
    XmTextPosition fromPos, toPos, newInsert;
    int length;
    int free_insert = False;
    int ret_val = 0;
    char * tmp_ptr;
    char * mod_value = NULL;

    fromPos = 0;

    if (value == NULL) value = "";
    toPos = XmTextF_string_length(tf);

    if (XmTextF_max_char_size(tf) == 1)
    {
	length = strlen(value);
    }
    else
    {
	length = mbstowcs(NULL, value, 0);
    }

    if (tf->core.sensitive && XmTextF_has_focus(tf)) 
    {
        df_ChangeBlinkBehavior(tf, False);
    }
    _XmDataFieldDrawInsertionPoint(tf, False);

    if (XmTextF_modify_verify_callback(tf) || 
	XmTextF_wcs_modify_verify_callback(tf)) 
    {
	/* 
	 * If the function df_ModifyVerify() returns 
	 * false then don't continue with the action.
	 */
	if (!df_ModifyVerify(tf, NULL, &fromPos, &toPos,
			     &value, &length, &newInsert, &free_insert)) 
	{
	    if (XmTextF_verify_bell(tf)) XBell(XtDisplay(w), 0);
	    if (free_insert) XtFree(value);
	    return;
	}
    }

    XmDataFieldSetHighlight(w, 0, XmTextF_string_length(tf),
			    XmHIGHLIGHT_NORMAL);

    if (XmTextF_max_char_size(tf) == 1) 
    {
	XtFree(XmTextF_value(tf));
    }
    else   /* convert to wchar_t before calling df_ValidateString */
    {
	XtFree((char *)XmTextF_wc_value(tf));
    }

    df_ValidateString(tf, value, False);
    XmTextF_pending_off(tf) = True;    

    df_SetCursorPosition(tf, NULL, 0, True, True, False);

    if (XmTextF_resize_width(tf) && XmTextF_do_resize(tf))
    {
	df_AdjustSize(tf);
    }
    else 
    {
	if (XmDataField_alignment(tf) == XmALIGNMENT_END)
	{
	    XmTextF_h_offset(tf) = 0;
	} 
	else
	{
	    XmTextF_h_offset(tf) = XmTextF_margin_width(tf) + 
		tf->primitive.shadow_thickness +
		tf->primitive.highlight_thickness;
	}
	if (!df_AdjustText(tf, XmTextF_cursor_position(tf), False)) 
	{
	    df_RedisplayText(tf, 0, XmTextF_string_length(tf));
	}    
    }

    cb.reason = XmCR_VALUE_CHANGED;
    cb.event = NULL;
    XtCallCallbackList(w, XmTextF_value_changed_callback(tf), (XtPointer) &cb);

    XmTextF_refresh_ibeam_off(tf) = True;
    
    if (tf->core.sensitive && XmTextF_has_focus(tf))
    {
        df_ChangeBlinkBehavior(tf, True);
    }
    
    _XmDataFieldDrawInsertionPoint(tf, True);
    if (free_insert) XtFree(value);
}

void 
#ifdef _NO_PROTO
XmDataFieldSetStringWcs( w, wc_value )
        Widget w ;
        wchar_t *wc_value ;
#else
XmDataFieldSetStringWcs(
        Widget w,
        wchar_t *wc_value )
#endif /* _NO_PROTO */
{

   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   char * tmp;
   wchar_t *tmp_wc;
   int num_chars = 0;
   int result;

    for (num_chars = 0, tmp_wc = wc_value; *tmp_wc != (wchar_t)0L; num_chars++)
        tmp_wc++;  /* count number of wchar_t's */

   tmp = XtMalloc((unsigned) (num_chars + 1) * XmTextF_max_char_size(tf));
   result = wcstombs(tmp, wc_value, (num_chars + 1) * XmTextF_max_char_size(tf));

   if (result == (size_t) -1) /* if wcstombs fails, it returns (size_t) -1 */
       tmp = "";               /* if invalid data, pass in the empty string */

   XmDataFieldSetString(w, tmp);
   
   XtFree(tmp);
}


void 
#ifdef _NO_PROTO
XmDataFieldReplace( w, from_pos, to_pos, value )
        Widget w ;
        XmTextPosition from_pos ;
        XmTextPosition to_pos ;
        char *value ;
#else
XmDataFieldReplace(
        Widget w,
        XmTextPosition from_pos,
        XmTextPosition to_pos,
        char *value )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    int save_maxlength = XmTextF_max_length(tf);
    Boolean save_editable = XmTextF_editable(tf);
    Boolean deselected = False;
    Boolean rep_result = False;
    wchar_t *wc_value;
    int length = 0;
    XmAnyCallbackStruct cb;

    if (value == NULL) value = "";

    df_VerifyBounds(tf, &from_pos, &to_pos);

    if (XmTextF_has_primary(tf)) {
       if ((XmTextF_prim_pos_left(tf) > from_pos && 
              XmTextF_prim_pos_left(tf) < to_pos) || 
           (XmTextF_prim_pos_right(tf) >from_pos && 
              XmTextF_prim_pos_right(tf) < to_pos) ||
           (XmTextF_prim_pos_left(tf) <= from_pos && 
              XmTextF_prim_pos_right(tf) >= to_pos)) {
                _XmDataFieldDeselectSelection(w, False,
			                XtLastTimestampProcessed(XtDisplay(w)));
		deselected = True;
       }
    }

    XmTextF_editable(tf) = True;
    XmTextF_max_length(tf) = INT_MAX;
    if (XmTextF_max_char_size(tf) == 1) {
       length = strlen(value);
       rep_result = _XmDataFieldReplaceText(tf, NULL, from_pos, 
				            to_pos, value, length, False);
    } else { /* need to convert to wchar_t* before calling Replace */
       wc_value = (wchar_t *) XtMalloc((unsigned) sizeof(wchar_t) *
				       (1 + strlen(value)));
       length = mbstowcs(wc_value, value, (unsigned) (strlen(value) + 1));
       rep_result = _XmDataFieldReplaceText(tf, NULL, from_pos, to_pos, 
				      (char*)wc_value, length, False);
       XtFree((char *)wc_value);
    }
    if (from_pos <= XmTextF_cursor_position(tf)) {
      XmTextPosition cursorPos;
      /* Replace will not move us, we still want this to happen */
      if (XmTextF_cursor_position(tf) < to_pos) {
	if (XmTextF_cursor_position(tf) - from_pos <= length)
	  cursorPos = XmTextF_cursor_position(tf);
	else
	  cursorPos = from_pos + length;
      } else {
	cursorPos = XmTextF_cursor_position(tf) - (to_pos - from_pos) + length;
      }
      XmDataFieldSetInsertionPosition((Widget)tf, cursorPos);
    }
    XmTextF_editable(tf) = save_editable;
    XmTextF_max_length(tf) = save_maxlength;

    /* 
     * Replace Text utilizes an optimization in deciding which text to redraw;
     * in the case that the selection has been changed (as above), this can
     * cause part/all of the replaced text to NOT be redrawn.  The following
     * df_AdjustText call ensures that it IS drawn in this case.
     */

    if (deselected)
       df_AdjustText(tf, from_pos, True);

    (void) df_SetDestination(w, XmTextF_cursor_position(tf), False,
			  XtLastTimestampProcessed(XtDisplay(w)));
    if (rep_result) {
       cb.reason = XmCR_VALUE_CHANGED;
       cb.event = (XEvent *)NULL;
       XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		          (XtPointer) &cb);
    }
}

/* TOM - XmDataFieldReplaceWcs not converted */
void 
#ifdef _NO_PROTO
XmDataFieldReplaceWcs( w, from_pos, to_pos, wc_value )
        Widget w ;
        XmTextPosition from_pos ;
        XmTextPosition to_pos ;
        wchar_t *wc_value ;
#else
XmDataFieldReplaceWcs(
        Widget w,
        XmTextPosition from_pos,
        XmTextPosition to_pos,
        wchar_t *wc_value )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    int save_maxlength = XmTextF_max_length(tf);
    Boolean save_editable = XmTextF_editable(tf);
    Boolean deselected = False;
    Boolean rep_result = False;
    wchar_t *tmp_wc;
    char *tmp;
    int wc_length = 0;
    XmAnyCallbackStruct cb;

    if (wc_value == NULL) wc_value = (wchar_t*)"";

    df_VerifyBounds(tf, &from_pos, &to_pos);

    if (XmTextF_has_primary(tf)) {
       if ((XmTextF_prim_pos_left(tf) > from_pos &&
              XmTextF_prim_pos_left(tf) < to_pos) ||
           (XmTextF_prim_pos_right(tf) >from_pos &&
              XmTextF_prim_pos_right(tf) < to_pos) ||
           (XmTextF_prim_pos_left(tf) <= from_pos &&
              XmTextF_prim_pos_right(tf) >= to_pos)) {
                _XmDataFieldDeselectSelection(w, False,
			                XtLastTimestampProcessed(XtDisplay(w)));
                deselected = True;
       }
    }

   /* Count the number of wide chars in the array */
    for (wc_length = 0, tmp_wc = wc_value; *tmp_wc != (wchar_t)0L; wc_length++)
	tmp_wc++;  /* count number of wchar_t's */

    XmTextF_editable(tf) = True;
    XmTextF_max_length(tf) = INT_MAX;

    if (XmTextF_max_char_size(tf) != 1) 
    {
	rep_result = _XmDataFieldReplaceText(tf, NULL, from_pos, to_pos,
					     (char*)wc_value, wc_length, False);
    } 
    else 
    {     /* need to convert to char* before calling Replace */
	tmp = XtMalloc((unsigned) (wc_length + 1) * XmTextF_max_char_size(tf));
	wc_length = wcstombs(tmp, wc_value, 
			     (wc_length + 1) * XmTextF_max_char_size(tf));

       if (wc_length == (size_t) -1){ /* if wcstombs fails, it returns -1 */
          tmp = "";                   /* if invalid data, pass in the empty 
                                       * string */
          wc_length = 0;
       }
       rep_result = _XmDataFieldReplaceText(tf, NULL, from_pos, to_pos,
                                            (char*)tmp, wc_length, False);
       XtFree(tmp);
    }
    if (from_pos <= XmTextF_cursor_position(tf)) {
      XmTextPosition cursorPos;
      /* Replace will not move us, we still want this to happen */
      if (XmTextF_cursor_position(tf) < to_pos) {
	if (XmTextF_cursor_position(tf) - from_pos <= wc_length)
	  cursorPos = XmTextF_cursor_position(tf);
	else
	  cursorPos = from_pos + wc_length;
      } else {
	cursorPos = XmTextF_cursor_position(tf) - (to_pos - from_pos) + wc_length;
      }
      XmDataFieldSetInsertionPosition((Widget)tf, cursorPos);
    }
    XmTextF_editable(tf) = save_editable;
    XmTextF_max_length(tf) = save_maxlength;

    /*
     * Replace Text utilizes an optimization in deciding which text to redraw;
     * in the case that the selection has been changed (as above), this can
     * cause part/all of the replaced text to NOT be redrawn.  The following
     * df_AdjustText call ensures that it IS drawn in this case.
     */

    if (deselected)
       df_AdjustText(tf, from_pos, True);

    (void) df_SetDestination(w, XmTextF_cursor_position(tf), False,
			  XtLastTimestampProcessed(XtDisplay(w)));
    if (rep_result) {
       cb.reason = XmCR_VALUE_CHANGED;
       cb.event = (XEvent *)NULL;
       XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
		          (XtPointer) &cb);
    }
}


void 
#ifdef _NO_PROTO
XmDataFieldInsert( w, position, value )
        Widget w ;
        XmTextPosition position ;
        char *value ;
#else
XmDataFieldInsert(
        Widget w,
        XmTextPosition position,
        char *value )
#endif /* _NO_PROTO */
{
    /* XmDataFieldReplace takes care of converting to wchar_t* if needed */
    XmDataFieldReplace(w, position, position, value);
}

void 
#ifdef _NO_PROTO
XmDataFieldInsertWcs( w, position, wcstring )
        Widget w ;
        XmTextPosition position ;
        wchar_t *wcstring ;
#else
XmDataFieldInsertWcs(
        Widget w,
        XmTextPosition position,
        wchar_t *wcstring )
#endif /* _NO_PROTO */
{
    /* XmDataFieldReplaceWcs takes care of converting to wchar_t* if needed */
    XmDataFieldReplaceWcs(w, position, position, wcstring);
}

void 
#ifdef _NO_PROTO
XmDataFieldSetAddMode( w, state )
        Widget w ;
        Boolean state ;
#else
XmDataFieldSetAddMode(
        Widget w,
        Boolean state )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   if (XmTextF_add_mode(tf) == state) 
   {
       return;
   }

   _XmDataFieldDrawInsertionPoint(tf, False);
   XmTextF_add_mode(tf) = state;
   _XmDataFToggleCursorGC(w);
   _XmDataFieldDrawInsertionPoint(tf, True);
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldGetAddMode( w )
        Widget w ;
#else
XmDataFieldGetAddMode(
        Widget w )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   Boolean ret_val;

   ret_val = XmTextF_add_mode(tf);
    
   return (ret_val);
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldGetEditable( w )
        Widget w ;
#else
XmDataFieldGetEditable(
        Widget w )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   Boolean ret_val;

   ret_val = XmTextF_editable(tf);    

   return ret_val;

}

void 
#ifdef _NO_PROTO
XmDataFieldSetEditable( w, editable )
        Widget w ;
        Boolean editable ;
#else
XmDataFieldSetEditable(
        Widget w,
        Boolean editable )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XPoint xmim_point;
    Arg args[6];  /* To set initial values to input method */
    Cardinal n = 0;

    /* if widget previously wasn't editable, no input method has yet been */
    /* registered.  So, if we're making it editable now, register the IM  */
    /* give the IM the relevent values.                                   */

    if (!XmTextF_editable(tf) && editable)
    { 
#if defined(__sgi)
	/* CR03685 */
	SGI_hack_XmImRegister((Widget)tf);
#else
	XmImRegister((Widget)tf, (unsigned int) NULL);
#endif
	df_GetXYFromPos(tf, XmTextF_cursor_position(tf), &xmim_point.x, 
		   &xmim_point.y);
	n = 0;
	XtSetArg(args[n], XmNfontList, XmTextF_font_list(tf)); n++;
	XtSetArg(args[n], XmNbackground, tf->core.background_pixel); n++;
	XtSetArg(args[n], XmNforeground, tf->primitive.foreground); n++;
	XtSetArg(args[n], XmNbackgroundPixmap,tf->core.background_pixmap);n++;
	XtSetArg(args[n], XmNspotLocation, &xmim_point); n++;
	XtSetArg(args[n], XmNlineSpace,
		 XmTextF_font_ascent(tf)+ XmTextF_font_descent(tf)); n++;
	XmImSetValues((Widget)tf, args, n);
    } else if (XmTextF_editable(tf) && !editable){
	XmImUnregister(w);
    }

    XmTextF_editable(tf) = editable;

    n = 0;
    if (editable) {
	XtSetArg(args[n], XmNdropSiteActivity, XmDROP_SITE_ACTIVE); n++;
    } else {
	XtSetArg(args[n], XmNdropSiteActivity, XmDROP_SITE_INACTIVE); n++;
    }	

    XmDropSiteUpdate((Widget)tf, args, n);
}

int 
#ifdef _NO_PROTO
XmDataFieldGetMaxLength( w )
        Widget w ;
#else
XmDataFieldGetMaxLength(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    int ret_val;
    
    ret_val = XmTextF_max_length(tf);
    
    return ret_val;
}

void 
#ifdef _NO_PROTO
XmDataFieldSetMaxLength( w, max_length )
        Widget w ;
        int max_length ;
#else
XmDataFieldSetMaxLength(
        Widget w,
        int max_length )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   XmTextF_max_length(tf) = max_length;
}

XmTextPosition 
#ifdef _NO_PROTO
XmDataFieldGetCursorPosition( w )
        Widget w ;
#else
XmDataFieldGetCursorPosition(
        Widget w )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   XmTextPosition ret_val;
   
   ret_val = XmTextF_cursor_position(tf);

   return ret_val;
}

XmTextPosition 
#ifdef _NO_PROTO
XmDataFieldGetInsertionPosition( w )
        Widget w ;
#else
XmDataFieldGetInsertionPosition(
        Widget w )
#endif /* _NO_PROTO */
{
    XmTextPosition ret_val;

    ret_val = XmDataFieldGetCursorPosition(w);
   
    return ret_val;
}

/* Obsolete - shouldn't be here ! */
void 
#ifdef _NO_PROTO
XmDataFielddf_SetCursorPosition( w, position )
        Widget w ;
        XmTextPosition position ;
#else
XmDataFielddf_SetCursorPosition(
        Widget w,
        XmTextPosition position )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    df_SetCursorPosition(tf, NULL, position, True, False, False);
}

void 
#ifdef _NO_PROTO
XmDataFieldSetInsertionPosition( w, position )
        Widget w ;
        XmTextPosition position ;
#else
XmDataFieldSetInsertionPosition(
        Widget w,
        XmTextPosition position )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   df_SetCursorPosition(tf, NULL, position, True, True, False);
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldGetSelectionPosition( w, left, right )
        Widget w ;
        XmTextPosition *left ;
        XmTextPosition *right ;
#else
XmDataFieldGetSelectionPosition(
        Widget w,
        XmTextPosition *left,
        XmTextPosition *right )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;

   if (!XmTextF_has_primary(tf)) {
       return False;
   }

   *left = XmTextF_prim_pos_left(tf);
   *right = XmTextF_prim_pos_right(tf);

   return True;
}

char * 
#ifdef _NO_PROTO
XmDataFieldGetSelection( w )
        Widget w ;
#else
XmDataFieldGetSelection(
        Widget w )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   size_t length, num_chars;
   char *value;

    if (XmTextF_prim_pos_left(tf) == XmTextF_prim_pos_right(tf))
    {
	return NULL;
    }

    num_chars = (size_t) (XmTextF_prim_pos_right(tf) \
			  - XmTextF_prim_pos_left(tf));
    length = num_chars;

    if (XmTextF_max_char_size(tf) == 1) 
    {
	value = XtMalloc((unsigned) num_chars + 1);
	(void) memcpy((void*)value, 
		      (void*)(XmTextF_value(tf) + 
			      XmTextF_prim_pos_left(tf)), num_chars);
    } 
    else 
    {
	value = XtMalloc((unsigned) ((num_chars + 1) * XmTextF_max_char_size(tf)));
	length = wcstombs(value, XmTextF_wc_value(tf) + XmTextF_prim_pos_left(tf), 
			  (num_chars + 1) * XmTextF_max_char_size(tf));
	if (length == (size_t) -1) 
	{
	    length = 0;
	} 
	else 
	{
	    for (length = 0;num_chars > 0; num_chars--) 
	    {
		length += mblen(&value[length], XmTextF_max_char_size(tf));
	    }
	}
    }
    value[length] = (char)'\0';

    return value;
}

wchar_t *
#ifdef _NO_PROTO
XmDataFieldGetSelectionWcs( w )
        Widget w ;
#else
XmDataFieldGetSelectionWcs(
        Widget w )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   size_t length;
   wchar_t *wc_value;
   int return_val;

   if (XmTextF_prim_pos_left(tf) == XmTextF_prim_pos_right(tf))
   {
       return NULL;
   }

   length = (size_t)(XmTextF_prim_pos_right(tf) - 
		     XmTextF_prim_pos_left(tf));

   wc_value = (wchar_t*)XtMalloc((unsigned) (length + 1) * sizeof(wchar_t));

   if (XmTextF_max_char_size(tf) == 1) 
   {
       return_val = mbstowcs(wc_value, XmTextF_value(tf) + 
			     XmTextF_prim_pos_left(tf), length);
       if (return_val < 0) length = 0;
   } 
   else 
   {
      (void)memcpy((void*)wc_value, 
		   (void*)(XmTextF_wc_value(tf) + XmTextF_prim_pos_left(tf)), 
		   length * sizeof(wchar_t));
   }
   wc_value[length] = (wchar_t)0L;

   return (wc_value);
}


Boolean 
#ifdef _NO_PROTO
XmDataFieldRemove( w )
        Widget w ;
#else
XmDataFieldRemove(
        Widget w )
#endif /* _NO_PROTO */
{
    Boolean ret_val;
    
    ret_val = DataFieldRemove(w, NULL);
    
    return ret_val;
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldCopy( w, clip_time )
        Widget w ;
        Time clip_time ;
#else
XmDataFieldCopy(
        Widget w,
        Time clip_time )
#endif /* _NO_PROTO */
{
    /* XmDataFieldGetSelection gets char* rep of data, so no special handling
     * needed
     */
    char * selected_string = XmDataFieldGetSelection(w); /* text selection */
    long item_id = 0L;                      /* clipboard item id */
    long data_id = 0;                        /* clipboard data id */
    int status = 0;                         /* clipboard status  */
    XmString clip_label;
    XTextProperty tmp_prop;
    Display *display = XtDisplay(w);
    Window window = XtWindow(w);
    char *atom_name;

    /* using the clipboard facilities, copy the selected text to the clipboard */
    if (selected_string != NULL) 
    {
	clip_label = XmStringCreateLtoR ("XM_TEXT_FIELD",
					 XmFONTLIST_DEFAULT_TAG);

	/* start copy to clipboard */
	status = XmClipboardStartCopy(display, window, clip_label, clip_time,
				      w, (XmCutPasteProc)NULL, &item_id);

	if (status != ClipboardSuccess) 
	{
	    XtFree(selected_string);
	    XmStringFree(clip_label);
	    return False;
	}

	status = XmbTextListToTextProperty(display, &selected_string, 1,
					   (XICCEncodingStyle)XStdICCTextStyle,
					   &tmp_prop);

	if (status != Success && status <= 0) 
	{
	    XmClipboardCancelCopy(display, window, item_id);
	    XtFree(selected_string);
	    XmStringFree(clip_label);
	    return False;
	}

	atom_name = XGetAtomName(display, tmp_prop.encoding);

	/* move the data to the clipboard */
	status = XmClipboardCopy(display, window, item_id, atom_name,
				 (XtPointer)tmp_prop.value, tmp_prop.nitems,
				 0, &data_id);

	XtFree(atom_name);
	
	if (status != ClipboardSuccess) 
	{
	    XmClipboardCancelCopy(XtDisplay(w), XtWindow(w), item_id);
	    XtFree(selected_string);
	    XmStringFree(clip_label);
	    return False;
	}

	/* end the copy to the clipboard */
	status = XmClipboardEndCopy(display, window, item_id);
	
	XtFree((char*)tmp_prop.value);
	XmStringFree(clip_label);

	if (status != ClipboardSuccess) 
	{
	    XtFree (selected_string);

	    return False;
	}
	
    }	 
    else
    {
	return False;
    }

    if (selected_string != NULL)
    {
	XtFree (selected_string);
    }

    return True;
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldCut( w, clip_time )
        Widget w ;
        Time clip_time ;
#else
XmDataFieldCut(
        Widget w,
        Time clip_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Boolean success = False;

    if (XmTextF_editable(tf) == False)
    {
	return False;
    }

    if (XmDataFieldCopy(w, clip_time))
    {
	if (XmDataFieldRemove(w))
	{
	    success = True;
	}
    }

    return success;
}


/*
 * Retrieves the current data from the clipboard
 * and paste it at the current cursor position
 */
Boolean 
#ifdef _NO_PROTO
XmDataFieldPaste( w )
        Widget w ;
#else
XmDataFieldPaste(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition sel_left = 0;
    XmTextPosition sel_right = 0;
    XmTextPosition paste_pos_left, paste_pos_right;
    int status = 0;                            /* clipboard status        */
    char* buffer;                              /* temporary text buffer   */
    unsigned long length;                      /* length of buffer        */
    unsigned long outlength = 0L;              /* length of bytes copied  */
    long private_id = 0;                       /* id of item on clipboard */
    Boolean dest_disjoint = True;
    Boolean rep_status = False;                /* did Replace succeed? */
    Display *display = XtDisplay(w);
    Window window = XtWindow(w);
    Boolean get_ct = False;
    XTextProperty tmp_prop;
    int malloc_size = 0;
    int num_vals;
    char **tmp_value;
    int i;
    XmAnyCallbackStruct cb;

    if (XmTextF_editable(tf) == False) 
    {
	return False;
    }

    paste_pos_left = paste_pos_right = XmTextF_cursor_position(tf);

    status = XmClipboardInquireLength(display, window, "STRING", &length);

    if (status == ClipboardNoData || length == 0) 
    {
	status = XmClipboardInquireLength(display, 
					  window, "COMPOUND_TEXT",
					  &length);
	if (status == ClipboardNoData || length == 0) 
	{
	    return False;
	}
	get_ct = True;
   }

   /* malloc length of clipboard data */
   buffer = XtMalloc((unsigned) length);

   if (!get_ct) 
   {
       status = XmClipboardRetrieve(display, window, "STRING", buffer,
				    length, &outlength, &private_id);
   } 
   else 
   {
       status = XmClipboardRetrieve(display, window, "COMPOUND_TEXT", buffer,
				    length, &outlength, &private_id);
   }	

   if (status != ClipboardSuccess) 
   {
       XmClipboardEndRetrieve(display, window);
       XtFree(buffer);
       return False;
   }

   if (XmDataFieldGetSelectionPosition(w, &sel_left, &sel_right)) 
   {
       if (XmTextF_pending_delete(tf) &&
	   paste_pos_left >= sel_left && paste_pos_right <= sel_right) 
       {
	   paste_pos_left = sel_left;
	   paste_pos_right = sel_right;
	   dest_disjoint = False;
       }
   }

   tmp_prop.value = (unsigned char *) buffer;

   if (!get_ct)
   {
       tmp_prop.encoding = XA_STRING;
   }
   else
   {
       tmp_prop.encoding = XmInternAtom(display, "COMPOUND_TEXT", False);
   }

   tmp_prop.format = 8;
   tmp_prop.nitems = outlength;
   num_vals = 0;

   status = XmbTextPropertyToTextList(display, &tmp_prop, &tmp_value,
				      &num_vals);

  /* add new text */
   if (num_vals && (status == Success || status > 0)) 
   {
       if (XmTextF_max_char_size(tf) == 1)
       {
	   char * total_tmp_value;

	   for (i = 0, malloc_size = 1; i < num_vals ; i++) 
	   {
	       malloc_size += strlen(tmp_value[i]);
	   }
	   total_tmp_value = XtMalloc ((unsigned) malloc_size);
	   total_tmp_value[0] = '\0';
	   for (i = 0; i < num_vals ; i++)
	   {
	       strcat(total_tmp_value, tmp_value[i]);
	   }
	   rep_status = _XmDataFieldReplaceText(tf, NULL, paste_pos_left,
						paste_pos_right, 
						total_tmp_value,
						strlen(total_tmp_value), True);
	   XFreeStringList(tmp_value);
	   if (malloc_size) XtFree(total_tmp_value);
       } else {
	 wchar_t * wc_value;
         int num_chars = 0;

	 for (i = 0, malloc_size = sizeof(wchar_t); i < num_vals ; i++)
	 {
	     malloc_size += strlen(tmp_value[i]);
	 }
	 wc_value = (wchar_t*)XtMalloc((unsigned)malloc_size * sizeof(wchar_t));
	 /* change malloc_size to the number of wchars available in wc_value */
	 for (i = 0; i < num_vals ; i++)
	     num_chars +=
		 mbstowcs(wc_value + num_chars, tmp_value[i],
			  (size_t)malloc_size - num_chars);
	 rep_status = _XmDataFieldReplaceText(tf, NULL, paste_pos_left,
					      paste_pos_right,
					      (char*)wc_value, 
					      num_chars, True);
	 if (malloc_size) XtFree((char*)wc_value);
       }
   }

   if (rep_status) {
       XmTextF_prim_anchor(tf) = sel_left;
       (void) df_SetDestination(w, XmTextF_cursor_position(tf), False,
				XtLastTimestampProcessed(display));
       if (sel_left != sel_right) 
       {
           if (!dest_disjoint || !XmTextF_add_mode(tf)) 
	   {
	       XmDataFieldSetSelection(w, XmTextF_cursor_position(tf),
				       XmTextF_cursor_position(tf),
				       XtLastTimestampProcessed(display));
           }
       }
       cb.reason = XmCR_VALUE_CHANGED;
       cb.event = (XEvent *)NULL;
       XtCallCallbackList((Widget) tf, XmTextF_value_changed_callback(tf),
     		          (XtPointer) &cb);
   }
   XtFree(buffer);
   return True;
}

void 
#ifdef _NO_PROTO
XmDataFielddf_ClearSelection( w, sel_time )
        Widget w ;
        Time sel_time ;
#else
XmDataFielddf_ClearSelection(
        Widget w,
        Time sel_time )
#endif /* _NO_PROTO */
{
    _XmDataFieldDeselectSelection(w, False, sel_time);
}

void 
#ifdef _NO_PROTO
XmDataFieldSetSelection( w, first, last, sel_time )
        Widget w ;
        XmTextPosition first ;
        XmTextPosition last ;
        Time sel_time ;
#else
XmDataFieldSetSelection(
        Widget w,
        XmTextPosition first,
        XmTextPosition last,
        Time sel_time )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    _XmDataFieldStartSelection(tf, first, last, sel_time);
    XmTextF_pending_off(tf) = False;
    df_SetCursorPosition(tf, NULL, last, True, True, False);
}

/* ARGSUSED */
XmTextPosition 
#ifdef _NO_PROTO
XmDataFieldXYToPos( w, x, y )
        Widget w ;
        Position x ;
        Position y ;
#else
XmDataFieldXYToPos(
        Widget w,
        Position x,
        Position y )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    XmTextPosition ret_val;

    ret_val = df_GetPosFromX(tf, x);

    return(ret_val);
}

Boolean 
#ifdef _NO_PROTO
XmDataFieldPosToXY( w, position, x, y )
     Widget w ;
     XmTextPosition position ;
     Position *x ;
     Position *y ;
#else  
XmDataFieldPosToXY(
		   Widget w,
		   XmTextPosition position,
		   Position *x,
		   Position *y )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Boolean ret_val;

    ret_val = df_GetXYFromPos(tf, position, x, y);

    return(ret_val);
}

/*
 * Force the given position to be displayed.  If position < 0, then don't force
 * any position to be displayed.
 */
void 
#ifdef _NO_PROTO
XmDataFieldShowPosition( w, position )
        Widget w ;
        XmTextPosition position ;
#else
XmDataFieldShowPosition(
        Widget w,
        XmTextPosition position )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (position < 0) {
	return;
    }

    df_AdjustText(tf, position, True);
}

/* ARGSUSED */
void 
#ifdef _NO_PROTO
XmDataFieldSetHighlight( w, left, right, mode )
        Widget w ;
        XmTextPosition left ;
        XmTextPosition right ;
        XmHighlightMode mode ;
#else
XmDataFieldSetHighlight(
        Widget w,
        XmTextPosition left,
        XmTextPosition right,
        XmHighlightMode mode )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (left >= right || right <= 0) {

	return;
    }

    if (left < 0) left = 0;

    if (right > XmTextF_string_length(tf)) 
    {
	right = XmTextF_string_length(tf);
    }

    DataFieldSetHighlight(tf, left, right, mode);

    df_RedisplayText(tf, left, right);

}

/* ARGSUSED */
static Boolean 
#ifdef _NO_PROTO
DataFieldGetBaselines( w, baselines, line_count )
        Widget w ;
        Dimension ** baselines;
        int *line_count;
#else
DataFieldGetBaselines(
        Widget w,
        Dimension ** baselines,
        int *line_count )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Dimension *base_array;

    *line_count = 1;
    base_array = (Dimension *) XtMalloc(sizeof(Dimension));
    base_array[0] = XmTextF_margin_top(tf) + tf->primitive.shadow_thickness +
	tf->primitive.highlight_thickness + XmTextF_font_ascent(tf);

    *baselines = base_array;

    return (TRUE);
}

int 
#ifdef _NO_PROTO
XmDataFieldGetBaseline( w )
        Widget w ;
#else
XmDataFieldGetBaseline(
        Widget w )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;
    Dimension margin_top;
    int ret_val;

    margin_top = XmTextF_margin_top(tf) +
	tf->primitive.shadow_thickness +
	tf->primitive.highlight_thickness;

    ret_val = (int) margin_top + (int) XmTextF_font_ascent(tf);
    
    return(ret_val);
}

static Boolean
#ifdef _NO_PROTO
DataFieldGetDisplayRect( w, display_rect )
        Widget w;
        XRectangle * display_rect;
#else
DataFieldGetDisplayRect(
        Widget w,
        XRectangle * display_rect )
#endif /* _NO_PROTO */
{
   XmDataFieldWidget tf = (XmDataFieldWidget) w;
   Position margin_width = XmTextF_margin_width(tf) +
	               	   tf->primitive.shadow_thickness +
		       	   tf->primitive.highlight_thickness;
   Position margin_top = XmTextF_margin_top(tf) + tf->primitive.shadow_thickness +
                       	 tf->primitive.highlight_thickness;
   Position margin_bottom = XmTextF_margin_bottom(tf) +
			    tf->primitive.shadow_thickness +
                       	    tf->primitive.highlight_thickness;
   (*display_rect).x = margin_width;
   (*display_rect).y = margin_top;
   (*display_rect).width = tf->core.width - (2 * margin_width);
   (*display_rect).height = tf->core.height - (margin_top + margin_bottom);

   return(TRUE);
}


/* ARGSUSED */
static void
#ifdef _NO_PROTO
DataFieldMarginsProc( w, margins_rec )
        Widget w ;
        XmBaselineMargins *margins_rec;
#else
DataFieldMarginsProc(
        Widget w,
        XmBaselineMargins *margins_rec )
#endif /* _NO_PROTO */
{
    XmDataFieldWidget tf = (XmDataFieldWidget) w;

    if (margins_rec->get_or_set == XmBASELINE_SET) {
       XmTextF_margin_top(tf) = margins_rec->margin_top;
       XmTextF_margin_bottom(tf) = margins_rec->margin_bottom;
    } else {
       margins_rec->margin_top = XmTextF_margin_top(tf);
       margins_rec->margin_bottom = XmTextF_margin_bottom(tf);
       margins_rec->text_height = XmTextF_font_ascent(tf) + XmTextF_font_descent(tf);
       margins_rec->shadow = tf->primitive.shadow_thickness;
       margins_rec->highlight = tf->primitive.highlight_thickness;
    }
}

/*
 * Text Field w creation convienence routine.
 */

Widget 
#ifdef _NO_PROTO
XmCreateDataField( parent, name, arglist, argcount )
        Widget parent ;
        char *name ;
        ArgList arglist ;
        Cardinal argcount ;
#else
XmCreateDataField(
        Widget parent,
        char *name,
        ArgList arglist,
        Cardinal argcount )
#endif /* _NO_PROTO */
{
    return (XtCreateWidget(name, xmDataFieldWidgetClass,
                           parent, arglist, argcount));
}

/****************************************************************/
/****************************************************************/
