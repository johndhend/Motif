
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
 * 
 */
/* 
 * HISTORY
*/ 
/*   $TOG: DNDDemo.h /main/7 1997/03/31 13:33:51 dbl $ */
/*
*  (c) C o pyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *    file: DNDDemo.h
 *
 *	Header file for the program DNDDemo.
 */

#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Xproto.h>
#include <Xm/Xm.h>
#include <Xm/AtomMgr.h>
#include <Xm/MainW.h>
#include <Xm/DrawingA.h>
#include <Xm/SeparatoG.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>
#include <Xm/DragDrop.h>
#include <Xm/Screen.h>
#include <Xm/TransferP.h>


/* The following is used to layout the color labels */
#define BOX_WIDTH       85
#define BOX_HEIGHT      25
#define BOX_X_OFFSET    95
#define BOX_Y_OFFSET    35
#define BOX_X_MARGIN    10
#define BOX_Y_MARGIN    10

/* The following are used in setting up the drag icons */
#define ICON_WIDTH          32
#define ICON_HEIGHT         32
#define SMALL_ICON_WIDTH    16
#define SMALL_ICON_HEIGHT   16
#define ICON_X_HOT          0
#define ICON_Y_HOT          0

/* Some scales or text entry field could be added to change this value */
#define RECT_WIDTH  20
#define RECT_HEIGHT 50

/* The following defines could be setup as application resources */
#define RECT_START_COLOR    "black"
#define HIGHLIGHT_THICKNESS 3
#define HIGHLIGHT_COLOR     "Black"   /* this is equivalent to gray60
                                         in the R5 rgb.txt */
#define DRAW_AREA_BG_COLOR "white"
#define DRAW_AREA_FG_COLOR "black"     /* 5127 fix */
#define LABEL1_COLOR       "#ff5026"     /* a slight softer shade of red,
                                            red was too dark */
#define LABEL2_COLOR    "orange"
#define LABEL3_COLOR    "yellow"
#define LABEL4_COLOR    "violet"
#define LABEL5_COLOR    "#00C3ff"           /* a blue green color,
                                               blue was too dark */
#define LABEL6_COLOR    "green"

#define VALID_CURSOR_FG_COLOR   "black"
#define INVALID_CURSOR_FG_COLOR "maroon"
#define NONE_CURSOR_FG_COLOR    "maroon"


/*
 * This struct is used to contain information about each rectangle 
 * to use in the dislay routines
 */
typedef struct _RectStruct {
  CARD32 x;
  CARD32 y;
  CARD32 width;
  CARD32 height;
  CARD32 color;
  CARD32 pixmap;   /* currently not in use */
} RectStruct, *RectPtr;

/* This struct is used to hold global application information */
typedef struct _AppInfoRec {
    GC rectGC;              /* graphic context used to draw the rectangles */
    Pixel currentColor;     /* color that is currently in the GC */
    RectPtr *rectDpyTable;  /* the rectangle display table */
    int rectsAllocd;        /* keeps track of how much the above
                               table has been alloc'd */
    int numRects;           /* the number of rects that are visible */
    RectPtr highlightRect;  /* the current highlighted rectangle */
    RectPtr clearRect;      /* the rectangle that is being moved */
    Boolean doMove;         /* indicates that a move is being performed */
    Boolean creatingRect;   /* indicates that a rect create is being 
                               performed */
    unsigned char operation;/* indicates the drop help operation */
    unsigned int maxCursorWidth;  /* the maximum allowable cursor width */
    unsigned int maxCursorHeight; /* the maximum allowable cursor height */
    Position rectX;
    Position rectY;
    Position rectX2;
    Position rectY2;
} AppInfoRec, *AppInfo;

/*
 * This struct is used to pass information
 * from the dropProc to the transferProc
 */
typedef struct _DropTransferRec {
    Widget widget;
    Position x;
    Position y;
} DropTransferRec, *DropTransfer;

/*
 * This struct is used to pass information
 * from the rectangle dragStart proc to it's associated
 * callback procs.
 */
typedef struct _DragConvertRec {
    Widget widget;
    RectPtr rect;
} DragConvertRec, *DragConvertPtr;



extern void     InitializeAppInfo(void );
extern void     StartRect(Widget , XEvent *, String *, Cardinal *);
extern void     ExtendRect(Widget , XEvent *, String *, Cardinal *);
extern void     EndRect(Widget , XEvent *, String *, Cardinal *);
extern RectPtr  RectCreate(Position , Position , Dimension ,
                          Dimension , Pixel , Pixmap );
extern RectPtr  RectFind(Position , Position );
extern void     RectSetColor(RectPtr , Display *, Window , Pixel );
extern Pixel    RectGetColor(RectPtr );
extern Pixmap   GetBitmapFromRect(Widget , RectPtr , Pixel , Pixel ,
                                  Dimension *, Dimension *);
extern void     RectHide(Display *, Window , RectPtr );
extern void     RectFree(RectPtr );
extern void     RedrawRectangles(Widget );
extern void     RectDrawStippled(Display *, Window , RectPtr );
extern void     RectHighlight(Widget , RectPtr );
extern void     RectUnhighlight(Widget );
extern void     RectSetPixmap(RectPtr , Display *, Window , Pixmap );
extern void     RectRegister(RectPtr , Position , Position );
extern void     InitializeRectDpyTable(void );
extern void     CreateLayout(void );
extern void     CreateRectGC(void );
extern Pixel    GetColor(char *);
extern void     ColorRect(Widget , XEvent *, String *, Cardinal *);
extern void     RectConvert(Widget, XtPointer, XmConvertCallbackStruct*);
extern void	ColorConvert(Widget, XtPointer, XmConvertCallbackStruct*);
extern void	handleDestination(Widget, XtPointer, XtPointer);


/* The following character arrays hold the bits for
 * the source and state icons for both 32x32 and 16x16 drag icons.
 * The source is a color palatte icon and the state is a paint brush icon.
 */
extern unsigned char SOURCE_ICON_BITS[];
extern unsigned char SOURCE_ICON_MASK[];
extern unsigned char STATE_ICON_BITS[];
extern unsigned char STATE_ICON_MASK[];
extern unsigned char INVALID_ICON_BITS[];
extern unsigned char SMALL_SOURCE_ICON_BITS[];
extern unsigned char SMALL_SOURCE_ICON_MASK[];
extern unsigned char SMALL_STATE_ICON_BITS[];
extern unsigned char SMALL_STATE_ICON_MASK[];
extern unsigned char SMALL_INVALID_ICON_BITS[];

/* The folowing character arrays are for use with the drop help
 * dialogs.  For internationalization, message catalogs should
 * replace these static declarations.
 */
extern char HELP_MSG1[];
extern char HELP_MSG2[];
extern char HELP_MSG3[];
extern char HELP_MSG4[];
extern char HELP_MSG5[];


/* Globals variables */
extern AppInfo      appInfo;
extern Widget       topLevel;
extern Widget       drawingArea;
extern Widget       helpDialog;
extern Widget       helpLabel, helpMenu;
extern XtAppContext appContext;

