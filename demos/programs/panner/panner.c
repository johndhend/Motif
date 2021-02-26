
#include <localdef.h>

/* $TOG: panner.c /main/6 1997/03/31 13:38:32 dbl $ */
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <X11/Xmd.h>
#include <Xm/TransferP.h>
#include <Xm/AtomMgr.h>
#include <Xm/CascadeB.h>
#include <Xm/DrawingA.h>
#include <Xm/Frame.h>
#include <Xm/MainW.h>
#include <Xm/MessageB.h>
#include <Xm/Notebook.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/SelectioB.h>
#include <Xm/XmStrDefs.h>

#ifdef NEVER892
/* all of this to get PackCARD32 ; mwm's not X's */
/* oops, do this and you can't use X's client data.  wow.
#include <mwm/WmGlobal.h>
#include <mwm/WmICCC.h>
#include <mwm/WmProtocol.h>

#include <mwm/WmError.h>
#include <mwm/WmFunction.h>
#include <mwm/WmKeyFocus.h>
#include <mwm/WmMenu.h>
#include <mwm/WmWinInfo.h>
#ifndef NO_WMQUERY
#include <mwm/WmEvent.h>
#endif /* NO_WMQUERY */

#include <mwm/pack.c>
*/
#endif


/*
   note:
    .  if not held, mouse1 should move window as where clicked
       if held ??
    .  if button 3 held drag one window but if not held do nothing
    .  while still dragging, it's called "tracking" and "held"
       the window should move while being dragged but in panner app
       one would only see outline dragged not the color box itself
    .  currently button1 is not used because it is implied
       if not button3 (but may become used for clarity?) 
    .  the "screen border" can be dragged but has not callback or action
    .  panner app is minimal:  it only sends request and wmp only listens
    .  wmp panning is minimal: it only requests window moves to motif or X
       it does not alter any structures

   Broken?  mouse moves arent working:  skip down to TRACKING HANDLERS
       Likely button3 flag isn't being set due to altered callback order
       which changes some logic if occurs (if perfected logic will not change)
       Panner is supposed to send WmProtocol 0's for pannerW,H while b3
       is T but it isn't supposed to get stuck as always T.
       tell tale symptom:
          . Alt-Arrows works but mouse click panning never does
          . edge panning works, but not mouse click panning
          . setting PAN_DEBUG shows pan root always gets 0's for pannerW,H 
*/

#define MAX_DISPLAY_COUNT	10
#define LOCAL			0

					    /* note sending is by byte */	
#define XC_REC_LEN		6
#define PAN_PACK_LEN		8           /* also give PanRoot x,y,w,h */
#define PAN_PACK_WIDTH		32	    /* CARD32 */
#define PAN_USE_SLIDING		True

#define WM_SELECTION_FORMAT	"WM_S%1d"
#define COLOR_COUNT             20

#define IS_PANNER               (config & 1)
#define STILL_PANNING_B3        (config & 2)
#define PANNER_B1               (!(config & 4))
#define PANNER_B3               (config & 4)
#define PANNER_EDGE             (config & 8)
#define SET_STILL_PANNING_B3    config |= 2
#define UNSET_STILL_PANNING_B3  config &= ~2

/* initially the size of thumb is set by % of screen which then sets canvas */
#define INITIAL_ZOOM		.9
#define THUMB_SMALL_MULT	.1  /* 1/8 canvas , window grab dashed line */

String fallback[] = {
  "Panner.mappedWhenManaged:		FALSE",

  "Panner.width:			325",
  "Panner.height:			290",
  "Panner*frame.marginWidth:		7",
  "Panner*frame.marginHeight:		7",
  "Panner*notebook.firstPageNumber:	0",
  "Panner*tab.shadowThickness:		1",
#ifndef ICCC_WORKS
  "Panner*NumberDialog_popup.width :		170",
  "Panner*NumberDialog_popup.height :		130",
  "Panner*NumberDialog.width :			170",
  "Panner*NumberDialog.height :			130",
  "Panner*AddDisplayDialog_popup.width :	170",
  "Panner*AddDisplayDialog_popup.height :	130",
  "Panner*AddDisplayDialog.width :		170",
  "Panner*AddDisplayDialog.height :		130",
  "Panner*HelpDialog_popup.width :		325",
  "Panner*HelpDialog_popup.height :		155",
  "Panner*HelpDialog.width :			325",
  "Panner*HelpDialog.height :			155",
#endif
  "Panner*canvas.background:		grey40",
  "Panner*canvas.foreground:		yellow",
  /* Menu entry definitions */
  "Panner*cascade1.labelString:		File",
  "Panner*cascade2.labelString:		Display",
  "Panner*cascade3.labelString:		Settings",
  "Panner*cascade4.labelString:		Help",
  "Panner*b1.labelString:		Quit",
  "Panner*b2.labelString:		Update",
  "Panner*b3.labelString:		New Display",

  "Panner*b4.labelString:		Start Edge",
  "Panner*b5.labelString:		Stop  Edge",
  "Panner*b6.labelString:		Edge Speed",
  "Panner*b7.labelString:		Edge Frequency",
  "Panner*b8.labelString:		Edge Slide",
  "Panner*b9.labelString:		Edge Multiple",
  "Panner*b10.labelString:		Pan  Multiple",
  "Panner*b11.labelString:		Zoom",

  "Panner*NumberDialog.selectionLabelString: Number:",

  "Panner*AddDisplayDialog*selectionLabelString: Display name:",

  "Panner*HelpDialog*messageString:\
Panner Demo\\n-----------\\n\
Grab or click Button1 to pan display.\\n\
Grab Button3 to drag an individual window.\\n\
Zoom using -+= (sorry not all keyboard supported)\\n\
Use 'New Display...' to view another display.",

  "Panner*WarningDialog*messageString:\
The panner window is not pinned!\\n\
Add the line:\\n\\n    \"Mwm*Panner*ClientPinned: True\"\\n\\n\
to your .Xdefaults file and restart Mwm.",

  NULL
};

    /* 
     *    DSP is global
     *    DSP = pageNumber;
     */
#define DPY_LOC		pInfoList[LOCAL].display
#define DPY_ACT		pInfoList[DSP].display
#define SCR_LOC		pInfoList[LOCAL].screen
#define SCR_ACT		pInfoList[DSP].screen
#define SCR_LOCW	pInfoList[LOCAL].screenW
#define SCR_LOCH	pInfoList[LOCAL].screenH
#define SCR_ACTW	pInfoList[DSP].screenW
#define SCR_ACTH	pInfoList[DSP].screenH

#define ADD_COLOR
#define PAN_MAX_SPEED		10000

typedef struct _PannerInfoRec
{
  Display *display;
  Screen *screen;
  Widget shell;
  Widget utmShell;              /* drawing area used for UTM */
  Widget canvas;
  int thumbX, thumbY;
  unsigned int thumbW, thumbH;  /* required for 1st XOR dash line and etc */
  unsigned int canvasW, canvasH;
  int lastEventX, lastEventY;

  int oldEventX, oldEventY;     /* required for 2nd XOR dash line */
  int screenW, screenH;         /* only used or updated for LOCAL */

  Atom WM;                      /* need selections on the correct display */
  Atom WM_PAN;
  Atom WM_GOTO;
  Atom WM_PAN_POS;
} PannerInfoRec;

typedef struct _PanPostion
{
  long x;
  long y;
} PanPosition;


typedef enum
{ MENU_QUIT, MENU_UPDATE, MENU_NEW, MENU_HELP, EDGE_START, EDGE_STOP,
  EDGE_SPEED, EDGE_FREQ, EDGE_SLIDE, EDGE_MULT, PAN_MULT, PAN_ZOOM
} MenuFunction;

typedef enum
{ UNKNOWN, VERIFYING, VERIFIED } PinState;


/*
 * 	functions Not invoked via callbacks referring to multiple display
 */

static void OpenNewDisplay (String, Widget, PannerInfoRec *);

/*
 * 	functions Not invoked via callbacks not referring to display 0
 */

static void CreateMenuBar (Widget parent);
static void MenuCB (Widget w, XtPointer clientData, XtPointer callData);
static void DoHelp ();
static void DoQuit ();
static void DoZoom ();
static void DoAddDisplay ();
static void DoAddDisplayCB (Widget, XtPointer, XtPointer);
static void DoNumEdgeCB (Widget, XtPointer, XtPointer);
	/* used as generic reset */
static void DoUpdatePanner (int);
static void DoNumEdge ();

/*
 * 	functions invoked by callback referring only to LOCAL 0 display
 */

static void panEdge (XEvent *);
static GC GetXorGC (Widget);		/* drawing is rendered LOCAL  */
static GC GetCanvasGC (Widget);
static void timeoutCB (XtPointer client_data, XtIntervalId * id);
	/* drawn only locally */
static void SetupColorsAndGCs ();
	/*  sends motion requests to mwm  */
	/*  MoveScreen gets pInfo but should not use it, see note */
static void MoveScreen (PannerInfoRec *, int, int, Time);

/*
 * 	Callbacks and functions called by callbacks (may need to find pInfo)
 */
/*
  *  these might find current display using this:
  *  PannerInfoRec *pInfo = (PannerInfoRec *) clientData;
  *  pull out DSP #
  *  if (XFindContext (propEvent->display, propEvent->window, context,
  *                 (XPointer *) & iDSP))
  *  or ask why called (so as not to respond to the wrong request) using:
  *  XPointerMovedEvent *motionEvent = (XPointerMovedEvent *) event;
  */

static void UpdatePannerCB (Widget, XtPointer, XtPointer);
static void ChangePageCB (Widget, XtPointer, XtPointer);
static void DestinationCB (Widget, XtPointer, XtPointer);
#ifdef TRY_ALLOC_ON_MULTISCREENS
static void DoneMoveScreenCB (Widget, XtPointer, XtPointer);
#endif
#ifndef ADD_PAN
static void WatchForWindowPanning (Display * dsp);
#endif
static void HandleInitialExpose (Widget, XtPointer, XEvent *, Boolean *);
static void HandlePropertyChange (XEvent * event);
static int IgnoreError (Display * dsp, XErrorEvent * event);
static Time GetTimestamp (Display * dsp);
/* track for remote but we don't pan remote see note of MoveSceen */
static void StartTracking (Widget, XtPointer, XEvent *, Boolean *);
static void DoTracking (Widget, XtPointer, XEvent *, Boolean *);
static void StopTracking (Widget, XtPointer, XEvent *, Boolean *);

/*
 *	TODO: functions which should have had PannerInfoRec
 *		panEdge - but oh well
 */


/*
 * 	Callbacks and functions called by callbacks with pInfo
 */

static void TranslateCoordinates (PannerInfoRec *,
                                  int, int, unsigned int, unsigned int,
                                  int *, int *, unsigned int *,
                                  unsigned int *);
       /* stretch fill coordinate w/zoom */
static void TranslateZoomCoordinates (PannerInfoRec *,
                                  float, float, float, float,
                                  float,
                                  float *, float*, float *, float *);
static void InverseTranslateZoomCoordinates (PannerInfoRec *,
                                  float, float, float, float,
                                  float,
                                  float *, float*, float *, float *);
static void UpdatePannerView (PannerInfoRec *, int);
static void DrawWindows (PannerInfoRec *, int);
static void DrawThumb (PannerInfoRec *, int);
static void DrawThumbSmall (PannerInfoRec *, int);

#ifndef ADD_PAN
static void SetWindowColor (PannerInfoRec *, int);
static void CheckPinnedState ();
static void ShowPinStateWarning ();
#endif

/*
 *	other functions
 */

static XtPointer PackCARD32 (XtPointer, CARD32);
static XtPointer PackCARD16 (XtPointer, CARD16);
static XtPointer PackCARD8 (XtPointer, CARD8);
/*
static CARD32 UnpackCARD32 (XtPointer);
static CARD16 UnpackCARD16 (XtPointer);
static CARD8 UnpackCARD8 (XtPointer);
*/

/*
 * 	Global variables
 */

int active_pInfo_rec=0;
XtAppContext app;
unsigned short DSP;             /* index of active display */
Widget notebook;
GC thumbGC, canvasGC;
XContext context;
PannerInfoRec *pInfoList;
unsigned long cells[COLOR_COUNT];
int origX, origY;
static float zoom = .9;
Boolean LOCK = False;
#ifndef ADD_PAN
PinState pinnedState = UNKNOWN;
#endif
static Boolean x_only = True; /* 64 xorg must use */
static Boolean button3 = False, button1=False;
static Boolean tracking = False, mwm_needs_notify_to_grab=False;
static Boolean panedge = False, centering=False;
static int track_count = 0;
/* GC thumbGCSmall, extraGC; */
#define thumbGCSmall thumbGC
static long which_num = 0;
static int edge_cnt = 0;
static XtIntervalId interval_id;
static float edge_update = 10;
static float edge_speed = 48;
static float edge_freq = 100;
static float edge_slide = 1;
static float b3_upd_freq = 10;
/* 0 Xme grabs many small dy / xy (smooth) before a person has the
 * chance to move the mouse quicker - causing a mandatory second or two of
 * slow panning that is "un-responsive", ignore every other mouse update helps
 */
static float pan_mult = 2;
static float edge_mult = 1;
static XEvent time_event;
/* defauls are for sluggish update for sake of bandwidth defaults
 * the methods are more hoggish the higher the freq
 */

#ifdef ADD_COLOR
static char color_fail = 0;
#endif

#ifdef TRY_ALLOC_ON_MULTISCREENS
/* ? found never freed bug X_ONLY */
static int msg_xallocs = 0;
#endif

static XtPointer transmit_data;

#ifdef ADD_COLOR
#define NUMBER_OF_COLORS 100    /* recycle if over 100 windows on dektop */
static unsigned long colorw[NUMBER_OF_COLORS + 1];
#endif


/*----------------------------------------------------------------*
 |                             main                               |
 *----------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  Widget mainWin, frame;
  XEvent event;

  int i;
  char *p;
  for (i = 1; i < argc; ++i)
  {
    if (strcmp (argv[i], "--help") == 0)
    {
      printf
        ("panner  [--help --version --zoom= --VERFIED --color-fail --screen-width= --edge-freq= --edge-update= --edge-slide= --b3_upd_freq=] --pan-mult= --b3-quirk...\n");
      return 0;
    };
    if (strcmp (argv[i], "--version") == 0)
    {
      printf ("panner 1.1\n");
      return 0;
    };
    if (strcmp (argv[i], "--x-only") == 0)
      x_only = True;
    if (strcmp (argv[i], "--color-fail") == 0)
      color_fail = 1;
/*
    if (strncmp (argv[i], "--screen-width=", 15) == 0)
    {
      p = argv[i] + 15;
      init_screen_width = atoi (p);
    }
*/
    if (strncmp (argv[i], "--edge-update=", 14) == 0)
    {
      p = argv[i] + 14;
      edge_update = atof (p);
    }
    if (strncmp (argv[i], "--b3-upd-freq=", 14) == 0)
    {
      p = argv[i] + 14;
      b3_upd_freq = atof (p);
    }
    if (strncmp (argv[i], "--edge-freq=", 12) == 0)
    {
      p = argv[i] + 12;
      edge_freq = atof (p);
    }
    if (strncmp (argv[i], "--edge-slide=", 13) == 0)
    {
      p = argv[i] + 13;
      edge_slide = atof (p);
    }
    if (strncmp (argv[i], "--edge-speed=", 13) == 0)
    {
      p = argv[i] + 13;
      edge_speed = atof (p);
    }
    if (strncmp (argv[i], "--pan-mult=", 11) == 0)
    {
      p = argv[i] + 11;
      pan_mult = atof (p);
    }
    if (strncmp (argv[i], "--edge-mult=", 12) == 0)
    {
      p = argv[i] + 12;
      edge_mult = atof (p);
    }
    if (strncmp (argv[i], "--zoom=", 7) == 0)
    {
      p = argv[i] + 7;
      zoom = atof (p);
    }
  }
  x_only=True;
  if( edge_slide == 0 ) edge_slide = 1;


#if defined(PAN_DEBUG)
  fprintf (stderr, "\npanner: x-only=%d color-fail=%d \n\
edge_update=%f edge_freq=%f ege_slide=%f edge_speed=%f pan_mult=%f edge_mult=%d\n",
x_only, color_fail, 
edge_update, edge_freq, edge_slide, edge_speed,pan_mult,(int) edge_mult);
#endif

  pInfoList = (PannerInfoRec *) XtMalloc (sizeof (PannerInfoRec) *
                                          MAX_DISPLAY_COUNT);

  /* never freed. i think X wants it in it's access region */
  transmit_data = malloc( PAN_PACK_WIDTH*(PAN_PACK_LEN+1) );
  /* 
  transmit_data = (XtPointer) XtMalloc(sizeof(CARD8) * (PAN_PACK_LEN+1));
  */
  
  if ( (pInfoList == (PannerInfoRec *) NULL) ||
       (transmit_data == (void *) NULL) )
  {
    fprintf (stderr, "cannot allocate any memory\n");
    exit (1);
  }
  for (DSP = 0; DSP < MAX_DISPLAY_COUNT; DSP++)
    DPY_ACT = NULL;
  DSP = LOCAL;


  /* motif-2.3.4 has this - new X manpages suggest - likely same here though */
  pInfoList[LOCAL].shell = XtVaOpenApplication (&app, "Panner", NULL,
                                                0, &argc, argv,
                                                fallback,
                                                sessionShellWidgetClass,
                                                NULL);

  DPY_LOC = XtDisplay (pInfoList[LOCAL].shell);


  mainWin = XmCreateMainWindow (pInfoList[LOCAL].shell, "mainWin", NULL, 0);
  XtManageChild (mainWin);
  CreateMenuBar (mainWin);

  frame = XtVaCreateManagedWidget ("frame", xmFrameWidgetClass, mainWin,
                                   NULL);
  notebook =
    XtVaCreateManagedWidget ("notebook", xmNotebookWidgetClass, frame, NULL);

  XtRealizeWidget (pInfoList[LOCAL].shell);

  context = XUniqueContext ();
  OpenNewDisplay ( /*$DISPLAY */ NULL, notebook, pInfoList);

  SetupColorsAndGCs ();

  XtAddCallback (notebook, XmNpageChangedCallback, ChangePageCB, pInfoList);
  XtAddEventHandler (notebook, ExposureMask, False, HandleInitialExpose,
                     NULL);

  XtMapWidget (pInfoList[LOCAL].shell);

  SCR_LOCW = WidthOfScreen (SCR_LOC);
  SCR_LOCH = HeightOfScreen (SCR_LOC);

  memset (&time_event, 0, sizeof (time_event));

  /* XtAppMainLoop (app); */

  for (;;)
  {
/* todo ? */
#if 0
    /*
     * event driven panEdge would be right but require XkbSelectEvents to work
     * which is useless do Alt-> if already pressing Alt (Mwm does keys)
     * this works but if ie,firefox is on edge it doesnt activate over firefox
     * (fvwm ran into same problem variously, src says, it has virt win to use)
     *
     * XkbSelectEvents(Dpy,XkbUseCoreKbd,XkbStateNotifyMask,XkbStateNotifyMask)
     * can get key events wherever focus is: but XSelectInput cannot.
     * apps consume "unused" mouse events (xterm no, but most do)
     *
     * another problem is adding complexity could cause Input headaches
     */
    if (panedge && !button3)
    {
      /* requires XPutBackEvent: if( XWindowEvent( .. PointerMotionMask .. ) */
      if (DPY_ACT != NULL && XPeekEvent (DPY_ACT, &event))
      {
        /* panEdge checks bounds too */
        if (event.type == MotionNotify)
          panEdge (&event);
        /* no good threhold for stopping starting , want refresh anyway */
        if ((++edge_cnt % edge_update) == 0)
		/* new:  must be pInfoList[n], upv is now by CB */
          UpdatePannerView (pInfoList?, DSP);
      }
    }
#endif /* 0 */

    XtAppNextEvent (app, &event);

    if (event.type == PropertyNotify)
      HandlePropertyChange (&event);

    XtDispatchEvent (&event);

  }

}


/*----------------------------------------------------------------*
 |                        OpenNewDisplay                          |
 | - Get new display connection to named display                  |
 | - callbacks get pInfoList[n], not pInfoList, use pInfo-> in CB |
 | - If display name is not NULL, create shell on the display.    |
 | - Fill in correct record in pInfoList[n]                       |
 *----------------------------------------------------------------*/

static void
OpenNewDisplay (String displayName,
                Widget notebook, PannerInfoRec * pInfoList)
{
  static int newDsp = 0;
  int argc = 0;
  char **argv = NULL;
  Dimension canvasW, canvasH;
  char selectionName[40];
  Widget tab;
  XmString tabName;
  XtCallbackList cbList;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " OpenNewDisplay%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /*
   * If NULL, then the display's already been created.
   */
  if (displayName != NULL)
  {
    XtVaGetValues (notebook, XmNlastPageNumber, &newDsp,
                   XmNpageChangedCallback, &cbList, NULL);
    newDsp++;

    if ((pInfoList[newDsp].display = XOpenDisplay (displayName)) == NULL)
    {
      fprintf (stderr, "ERROR - Can't open display \"%s\".\n", displayName);
      return;
    }

    XtDisplayInitialize (app, pInfoList[newDsp].display, "panner", "Panner",
                         NULL, 0, &argc, argv);

    /* create an unmapped shell on the remote display */
    pInfoList[newDsp].shell =
      XtVaAppCreateShell ("panner", "Panner", applicationShellWidgetClass,
                          pInfoList[newDsp].display,
                          XmNmappedWhenManaged, False, NULL);

    XtRealizeWidget (pInfoList[newDsp].shell);
  }
  /*
   * For UTM to work, there must be a drawing area or UTM saavy
   * widget.
   *
   *  We must set-up a destination callback function that
   *  does the actual transfer of the parameter info to Mwm.
   */

  pInfoList[newDsp].utmShell
    = XtVaCreateManagedWidget ("utmShell", xmDrawingAreaWidgetClass,
                               pInfoList[newDsp].shell,
                               XmNmappedWhenManaged, False, NULL);

  XtAddCallback (pInfoList[newDsp].utmShell, XmNdestinationCallback,
                 DestinationCB, &(pInfoList[newDsp]));

  /*
   * Initialize the correct record in the pInfoList.
   */
  pInfoList[newDsp].screen = XtScreen (pInfoList[newDsp].shell);

  /* store single data associated given id into X server */
  XSaveContext (pInfoList[newDsp].display,
	DefaultRootWindow (pInfoList[newDsp].display), context,
	(XPointer) (long) newDsp);

#ifndef ADD_PAN
  /*
   * setup handler to watch when Mwm changes the root property.
   * first store some data on the root window.
   */
  WatchForWindowPanning (pInfoList[newDsp].display);
#endif

  /*
   * Add another page to the notebook.
   * First must set size correctly.
   */

  /* LOCAL is always 0 - the one with main frame notebook attached */

  XtVaGetValues (pInfoList[LOCAL].shell,
                 XmNwidth, &canvasW, XmNheight, &canvasH, NULL);

  pInfoList[newDsp].canvas
    = XtVaCreateManagedWidget ("canvas", xmDrawingAreaWidgetClass, notebook,
                               XmNchildType, XmPAGE,
                               XmNpageNumber, newDsp,
                               XmNwidth, canvasW, XmNheight, canvasH, NULL);

  XtAddCallback (pInfoList[newDsp].canvas, XmNexposeCallback,
		UpdatePannerCB, &(pInfoList[LOCAL]));

  pInfoList[LOCAL].canvasW = canvasW;
  pInfoList[LOCAL].canvasH = canvasH;

  if (displayName == NULL)
    tabName = XmStringCreate ("LOCAL", XmFONTLIST_DEFAULT_TAG);
  else
    tabName = XmStringCreate (displayName, XmFONTLIST_DEFAULT_TAG);
  tab = XtVaCreateManagedWidget ("tab", xmPushButtonWidgetClass, notebook,
                                 XmNlabelString, tabName,
                                 XmNchildType, XmMAJOR_TAB, NULL);
  XmStringFree (tabName);


  /* if we take a raw coordinate system there will be centering issues
     and several coordinate systems.  it can be reduced to a single coordinate
     system by using aspect (a tall panner window will make all inside tall)

     to offer zoom and usability we must begin with and maintain aspect
     ratio so we have a consistent coordinate system from screen to thumb
     that is not a bear to keep centered and pt. for pt. mouse thumb rectangles
     desktop and canvas (which all merge with a single coordinate tranform
     if aspect is used: the (canvas|thumb) / (display|screen) ratio

     for zoom to work thumb must always have equal aspcect of canvas and
     any Translation must not change any of our 3 aspects and be current
     for however the user has resized the panner app
  */

  pInfoList[newDsp].screenW = WidthOfScreen (pInfoList[newDsp].screen);
  pInfoList[newDsp].screenH = HeightOfScreen (pInfoList[newDsp].screen);

  XtVaGetValues (pInfoList[newDsp].canvas, XmNwidth, &canvasW,
                 XmNheight, &canvasH, NULL);

  /* this is the  thumb / canvas ratio (aspect).  we create thumb with same
     aspect as canvas (which may stretch windows) and so if the Translate is
     invoked for display->thumb or display->canvas we are indifferent the
     answer is there is only one aspect translation

     thumb must have the same aspect as canvas/display , may leave the
     the issue it should be smaller than canvas as a unified zoom issue  
         canvasW * (canvasW / pInfoList[newDsp].screenW) * zoom
  
     a same aspect , 1:1 is  thumb / display = canvas / display
  */
  pInfoList[newDsp].thumbW = canvasW;
  pInfoList[newDsp].thumbH = canvasH;


  /* Setup the atoms needed to communicate with Mwm. Check screen number! */
  sprintf (selectionName, WM_SELECTION_FORMAT,
           XScreenNumberOfScreen (pInfoList[newDsp].screen));
  pInfoList[newDsp].WM = XmInternAtom (pInfoList[newDsp].display,
                                       selectionName, False);
  pInfoList[newDsp].WM_PAN = XmInternAtom (pInfoList[newDsp].display,
                                           "_MOTIF_WM_PAN", False);
  pInfoList[newDsp].WM_GOTO = XmInternAtom (pInfoList[newDsp].display,
                                            "_MOTIF_WM_GOTO", False);
  pInfoList[newDsp].WM_PAN_POS = XmInternAtom (pInfoList[newDsp].display,
                                               "_MOTIF_WM_PAN_POSITION",
                                               False);

  XtAddEventHandler (pInfoList[newDsp].canvas,
                     ButtonPressMask|KeyPressMask, False,
                     StartTracking, (XtPointer) & pInfoList[newDsp]);

  busy=False;
}



/*========================== CALLBACKS ==========================*/

/*----------------------------------------------------------------*
 |                        UpdatePannerCB                          |
 *----------------------------------------------------------------*/

  /*  INPUT:
   *          pInfoList is always &(pInfoList[LOCAL]) , req'ed by OpenNew
   */

static void
UpdatePannerCB (Widget w, XtPointer clientData, XtPointer callData)
{
  XmDrawingAreaCallbackStruct *cb = (XmDrawingAreaCallbackStruct *) callData;
  PannerInfoRec *pInfoList = (PannerInfoRec *) clientData;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " UpdatePannerCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (cb->reason == XmCR_EXPOSE)
  {
    XExposeEvent *event = (XExposeEvent *) cb->event;

  Window win, win2;
  XWindowAttributes attr;

    win=0;
    win2=0;
    SCR_LOCW = WidthOfScreen (SCR_LOC);
    SCR_LOCH = HeightOfScreen (SCR_LOC);
    win = XtWindow (pInfoList[LOCAL].canvas);
    XGetWindowAttributes (DPY_LOC, win, &attr);
    pInfoList[LOCAL].canvasW = attr.width;
    pInfoList[LOCAL].canvasH = attr.height;

    /* DSP is global
     * DSP = pageNumber;
     */
    SCR_ACTW = WidthOfScreen (SCR_ACT);
    SCR_ACTH = HeightOfScreen (SCR_ACT);
    win2 = XtWindow (pInfoList[DSP].canvas);
    XGetWindowAttributes (DPY_LOC, win, &attr);
    pInfoList[DSP].canvasW = attr.width;
    pInfoList[DSP].canvasH = attr.height;

    /* ? Last expose event received - do the drawing. */
/*
    if (event->count == 0)
*/
      UpdatePannerView (pInfoList, DSP);

  }
/*
  else
    UpdatePannerView (pInfoList, DSP);
*/

  busy=False;
}


/*----------------------------------------------------------------*
 |                         ChangePageCB                           |
 | Invoked just prior to notebook page change. Any drawing here   |
 | would be lost.                                                 |
 *----------------------------------------------------------------*/
static void
ChangePageCB (Widget w, XtPointer clientData, XtPointer callData)
{
  PannerInfoRec *pInfoList = (PannerInfoRec *) clientData;
  XmNotebookCallbackStruct *nbData = (XmNotebookCallbackStruct *) callData;
  int pageNumber;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " ChangePageCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  pageNumber = nbData->page_number;
  if ((pageNumber >= MAX_DISPLAY_COUNT) ||
      (pInfoList[pageNumber].display == NULL))
  {
    fprintf (stderr, "ERROR - bad display index. (%d).\n", pageNumber);
  }
  else
  {
    DSP = pageNumber;
  }

  busy=False;
}


/*----------------------------------------------------------------*
 |                        DoAddDisplayCB                          |
 *----------------------------------------------------------------*/
static void
DoAddDisplayCB (Widget w, XtPointer clientData, XtPointer callData)
{
  XmSelectionBoxCallbackStruct *cb =
    (XmSelectionBoxCallbackStruct *) callData;
  PannerInfoRec *pInfoList = (PannerInfoRec *) clientData;
  char *dspName;                /* Free when done. */
  String appName, appClass;     /* Don't free - owned by Xt. */

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoAddDisplayCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if (pInfoList == (PannerInfoRec *) NULL)
    return;

  XtGetApplicationNameAndClass (DPY_LOC, &appName, &appClass);
  XmStringGetLtoR (cb->value, XmSTRING_DEFAULT_CHARSET, &dspName);

  if (dspName && strlen(dspName) != 0)
    OpenNewDisplay (dspName, notebook, pInfoList);
  if (dspName)
    XtFree (dspName);

  busy=False;
}

/*----------------------------------------------------------------*
 |                        DoNumEdgeCB                             |
 *----------------------------------------------------------------*/

static void
DoNumEdgeCB (Widget w, XtPointer clientData, XtPointer callData)
{
  XmSelectionBoxCallbackStruct *cb =
    (XmSelectionBoxCallbackStruct *) callData;
  PannerInfoRec *pInfoList = (PannerInfoRec *) clientData;
  char *dspName;                /* Free when done. */
  String appName, appClass;     /* Don't free - owned by Xt. */
  float f;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoNumEdgeCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (pInfoList == (PannerInfoRec *) NULL)
    return;

  XtGetApplicationNameAndClass (DPY_LOC, &appName, &appClass);
  XmStringGetLtoR (cb->value, XmSTRING_DEFAULT_CHARSET, &dspName);

  if( dspName && strlen(dspName) != 0 )
  {
    f = atof (dspName);
    switch (which_num)
    {
    case EDGE_SPEED:
      edge_speed = f;
      break;
    case EDGE_FREQ:
      edge_freq = f;
      break;
    case EDGE_SLIDE:
      edge_slide = f;
      break;
    case PAN_MULT:
      pan_mult = f;
      break;
    case EDGE_MULT:
      edge_mult = f;
      break;
    case PAN_ZOOM:
      zoom = f;
      break;
    default:
      fprintf(stderr,"NumberDialog error\n");
      break;
    }
  }

  if (dspName)
    XtFree (dspName);

  busy=False;
}


/*----------------------------------------------------------------*
 |                         DestinationCB                          |
 | This function gets invoked by UTM when a sink has been estab-  |
 | lished and a request initiated against another selection.  The |
 | purpose here is to set-up the parameters and pass them to the  |
 | owner of the selection.  The parameter data has already been   |
 | allocated in the MoveScreen() function.                        |
 | clientData holds the pannerInfoRec corresponding to the right  |
 | display.                                                       |
 *----------------------------------------------------------------*/
static void
DestinationCB (Widget w, XtPointer clientData, XtPointer callData)
{
  XmDestinationCallbackStruct *dcs = (XmDestinationCallbackStruct *) callData;
  PannerInfoRec *lpInfo = (PannerInfoRec *) clientData;
  Atom target;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DestinationCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /*
   * Pass the data to free in the clientData field.
   * location_data points to the param data. This was set in
   * MoveScreen().
   */

  /* FIRST - setup the parameters to pass. */
  XmTransferSetParameters (dcs->transfer_id, dcs->location_data,  /* pointer to param data. */
                           PAN_PACK_WIDTH, PAN_PACK_LEN,  /* should be calculated. */
                           dcs->selection); /* type - don't care. */

  /* LAST - Make the transfer. */
  XmTransferValue (dcs->transfer_id, lpInfo->WM_PAN, /* target for conversion. */
#ifdef ADD_PAN
                   NULL,        /* CB proc invoked when done. */
#else
                   DoneMoveScreenCB,  /* CB proc invoked when done. */
#endif
                   dcs->location_data,  /* clientData - to be freed. */
                   dcs->time);

  busy=False;
}

/*
 * utm uses an (empty) window Motif creates which exists as a sink for
 * certain send/recv events.  i'm unsure what more utm does.  Xm XmeNamedSink ?
 */



/*----------------------------------------------------------------*
 |                       DoneMoveScreenCB                         |
 *----------------------------------------------------------------*/


static void
DoneMoveScreenCB (Widget w, XtPointer clientData, XtPointer callData)
{
  /*
   * Conversion completed. Safe to free param data.
   */

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoneMoveScreenCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* see notes at EOF */

#ifdef TRY_ALLOC_ON_MULTISCREENS
  XtFree ((char *) clientData);
  --msg_xallocs;
#if defined(ADD_PAN) && defined(PAN_DEBUG)
  fprintf (stderr, "allocs=%d\n", msg_xallocs);
  fflush (stderr);
#endif
#endif

  busy=False;

}






/*=========================== PAN-HANDLING ==========================*/


/*----------------------------------------------------------------*
 |                     WatchForWindowPanning                      |
 *----------------------------------------------------------------*/

#ifndef ADD_PAN

static void
WatchForWindowPanning (Display * dsp)
{
  XWindowAttributes attr;
  Window rwin = DefaultRootWindow (dsp);

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " WatchForWindowPanning%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (!dsp)
    return;

  /* Watch whenever the window manager's panning position changes. */
  /* Mwm stores the position in properties on the root window.     */
  /* This is stored in the _MOTIF_WM_PAN_POSITION property.        */

  XGetWindowAttributes (dsp, rwin, &attr);

  if (!(attr.your_event_mask & PropertyChangeMask))
    XSelectInput (dsp, rwin, attr.your_event_mask | PropertyChangeMask);

  busy=False;
}

#endif


/*----------------------------------------------------------------*
 |                     HandlePropertyChange                       |
 | This routine checks the property changed and if its the right  |
 | property, grab the new panning position.                       |
 *----------------------------------------------------------------*/

/* 
 * for ADD_PAN this always exits before doing anything
 * called only at startup (due to startup)
 */

static void
HandlePropertyChange (XEvent * event)
{
  XPropertyEvent *propEvent = (XPropertyEvent *) event;
  int iDSP;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " HandlePropertyChange%s ", busy?".PUNT":""); fflush(stderr);
#endif
/* see note on recursion callbacks
  if( busy )
    return ;
  busy=True;
*/

  /* Get the correct info record stored with the context manager. */
  if (XFindContext (propEvent->display, propEvent->window, context,
                    (XPointer *) & iDSP))
    return;

  /* should not happen unless a bug or type is in code */
  if ((pInfoList == (PannerInfoRec *) NULL) || (DPY_LOC == NULL))
    return;

  /*
   * infrequently here - probably a resize - nice time to update canvasW
   * and size and such
   */
  if (iDSP == DSP || iDSP == LOCAL)
    DoUpdatePanner (iDSP);

  /* ? pan250 does updating differntly and ignores "pinned" statuses */

#ifndef ADD_PAN

  /* check if this is the right one. Othersize, we'll update when another
   * display changes.
   */
  if (propEvent && propEvent->atom != pInfoList[iDSP].WM_PAN_POS)
    return;

  /* if the display doesn't match the current one, then punt. */
  if (iDSP == DSP)
  {
    if (pinnedState == VERIFIED)
      UpdatePannerView (NULL, iDSP);
    else
    {
      Window rWin, child;
      int x, y, newX, newY;
      unsigned int width, height, bWidth, depth;

      /* Get position of the top-level shell */
      XGetGeometry (DPY_LOC,
                    XtWindow (pInfoList[LOCAL].shell), &rWin, &x, &y, &width,
                    &height, &bWidth, &depth);

      XTranslateCoordinates (DPY_LOC,
                             XtWindow (pInfoList[LOCAL].shell),
                             rWin, x, y, &newX, &newY, &child);
      if ((newX == origX) && (newY == origY))
        pinnedState = VERIFIED;
      else
        ShowPinStateWarning ();
    }
  }

#endif

  LOCK = False;

#ifdef PAN_DEBUG
  fprintf (stderr, " unLOCK "); fflush (stderr);
#endif

  busy=False;
}




/*============================ DRAWING ===========================*/

/*----------------------------------------------------------------*
 |                         UpdatePannerView                       |
 *----------------------------------------------------------------*/
static void
UpdatePannerView (PannerInfoRec * pInfoList, int iDSP)
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " UpdatePannerView%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if ((pInfoList == (PannerInfoRec *) NULL)
      || (pInfoList[iDSP].canvas == NULL))
    return;

#ifndef ADD_PAN
  XClearArea (DPY_LOC,
              XtWindow (pInfoList[iDSP].canvas), 0, 0, 0, 0, False);
#endif

  DrawWindows (pInfoList, iDSP);
  DrawThumb (pInfoList, iDSP);
  busy=False;
}


/*----------------------------------------------------------------*
 |                          DrawWindows                           |
 *----------------------------------------------------------------*/
/* 
 * recognize while many things are per display that draw is local only
 * (also we choose that gc are allocated local and no tranfer of remote images)
 *
 */

static void
DrawWindows (PannerInfoRec * pInfo, int iDSP)
{
  Window realRoot, root, parent, win, *child = NULL;
  XWindowAttributes attr;
  int i, c_i;
  unsigned int childCount;
  int (*oldHandler) ();
  float xaspect,yaspect;
  XWindowAttributes cattr;
  XGCValues values;
  XSetWindowAttributes xswa;
  Window tmpwin, realRoot2, win2;
  Pixmap pixmap;
  float x,y,width,height;
  int once;


  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DrawWindows%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  /* should check every function at entry in that case */
  if ((pInfo == (PannerInfoRec *) NULL) || (DPY_ACT == NULL))
    return;

  /* where to query for win rects */
  realRoot = RootWindow (pInfo->display, XScreenNumberOfScreen (pInfo->screen));
  /* where to render win rects */
  realRoot2 = RootWindow (DPY_LOC, XScreenNumberOfScreen (SCR_LOC));

  if (!XQueryTree (DPY_ACT, realRoot, &root, &parent, &child, &childCount))
    return;

  win = XtWindow (pInfoList[LOCAL].canvas);

  win2 = XtWindow (pInfo->canvas);

  /*
   * pixmap is on server, drawing is created on server, client says how to draw
   * user sees flashing if drawing is on mapped visible win (the canvas)
   * to have spare and invisilbe pixmap must have a unmapped win: create it
   * (Xt easier? would map and manage it - unsure how to Xt prevent that)
   */

  pixmap = (Pixmap) NULL;
  XGetWindowAttributes (DPY_LOC, win, &cattr);
  XtVaGetValues (pInfoList[LOCAL].canvas, XmNforeground, &values.foreground,
                 XmNbackground, &values.background, NULL);
  memset (&xswa, 0, sizeof (xswa));
  xswa.background_pixmap = ParentRelative;
  xswa.background_pixel = values.background;
  xswa.border_pixel = 0;
  xswa.bit_gravity = 0;
  xswa.win_gravity = 0;
  xswa.backing_planes = 0;
  xswa.backing_pixel = 0;
  xswa.save_under = False;
  xswa.event_mask = 0;
  xswa.do_not_propagate_mask = True;
  xswa.override_redirect = True;
  xswa.colormap = DefaultColormapOfScreen (pInfo->screen);
  xswa.cursor = None;
  /* let prog exit if it fails */
  tmpwin = XCreateWindow (DPY_LOC,
                          win,
                          0, 0,
                          cattr.width, cattr.height, 0,
                          CopyFromParent, CopyFromParent, CopyFromParent,
                          0, &xswa);
  pixmap =
    XCreatePixmap (DPY_LOC, realRoot2, cattr.width, cattr.height,
                   cattr.depth);
  XSetForeground (DPY_LOC, canvasGC, values.background);
  XFillRectangle (DPY_LOC, pixmap, canvasGC, 0, 0, cattr.width, cattr.height);

  /* loop XQueryTree return , drawing on pixmap as we go */

  /* 
   * We need to install an error handler since the window-tree may
   * become invalid while where still processing the list.
   */
  oldHandler = XSetErrorHandler (IgnoreError);
  once = 0;
  c_i = 0;
  for (i = 0; i < childCount; i++)
  {
    /* get the box size of the child/rectangle into local var attr */
    XGetWindowAttributes (pInfo->display, child[i], &attr);
    if (attr.map_state == IsViewable)
    {
      once = 1;
      /* translate coord of child box from display coord to canvas|thumb coord
         and store in local vars width,height
      */
#ifdef ADD_COLOR
      if (color_fail == 2)
        XSetForeground (DPY_LOC, canvasGC, colorw[++c_i % NUMBER_OF_COLORS]);
      else
#endif
        XSetForeground (DPY_LOC, canvasGC, cells[(++c_i + 1) % COLOR_COUNT]);

      /* this is the image of the window, streched so 1:1 display screen fills
         the canvas however the user has re-sized the canvas
       */
      TranslateZoomCoordinates (pInfo,
                              (float) attr.x, (float) attr.y,
                              (float) attr.width, (float) attr.height,
                              zoom,
                              &x, &y, &width, &height);

      XFillRectangle (DPY_LOC, pixmap, canvasGC, x, y, width, height);
    }
  }

  if (once)
    XCopyArea (DPY_LOC, pixmap, win2, canvasGC, 0, 0, cattr.width,
               cattr.height, 0, 0);
  XFreePixmap (DPY_LOC, pixmap);
  XDestroyWindow (DPY_LOC, tmpwin);

  XSetErrorHandler (oldHandler);

  if (child != NULL)
    XFree ((char *) child);

  busy=False;
}

/* if thumb is zoomed smaller than canvas then x,y moves right
   later, MoveScreen will also need to translate mouse x,y the same
 */
/*
      TranslateCoordinates (pInfo,
                            attr.x, attr.y, attr.width, attr.height,
                            &x, &y, &width, &height);

      this would make a "correct image" (never squashed) after which
      we'd have to squash it and then zoom it (it's senseless to use it)

      how zoom works is we do it ony once (when drawing) and for mouse
      click when calculating "where mouse clicked", so only 2 places in
      code support all the otherwise difficult work
*/

/*
 * proabably the above could use stippling or translucense but doing so
 * uncarefully would quickly lead to confusing or ugly graphics
 * obviously images could be sampled from real desktop, wow, cpu temp
 */


/*----------------------------------------------------------------*
 |                          DrawThumb                             |
 *----------------------------------------------------------------*/

static void
DrawThumb (PannerInfoRec * pInfo, int iDSP)
{ 
  /* it's a shortcoming/todo that pInfo is always LOCAL */
  PannerInfoRec * lpInfo = &(pInfoList[iDSP]);
  float xaspect,yaspect, x,y,width,height;
 
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DrawThumb%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if (!lpInfo)
    return;
  
    TranslateZoomCoordinates (lpInfo,
      0,0, (float) lpInfo->screenW, (float) lpInfo->screenH,
      zoom,
      &x, &y, &width, &height);
  
  /* always draw on LOCAL though */
  XDrawRectangle (XtDisplay (pInfo->canvas), XtWindow (pInfo->canvas),
        thumbGC, x, y, width, height);

  busy=False;
}


/*----------------------------------------------------------------*
 |                          DrawThumbSmall                        |
 *----------------------------------------------------------------*/
 /* 
  *   follwing mouse can be greatly simplified by using the canvas/display
  *   aspect (we don't zoom or squash mouse box, always same size)
  */

static void
DrawThumbSmall (PannerInfoRec * pInfo, int iDSP)
{
  PannerInfoRec * lpInfo = &(pInfoList[iDSP]);
  int x,y;
  unsigned width,height;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DrawThumb%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if (!lpInfo)
    return;

  TranslateCoordinates (lpInfo,
      lpInfo->oldEventX,
      lpInfo->oldEventY,
      lpInfo->screenW, lpInfo->screenH,
      &x, &y, &width, &height);

  /* always draw on LOCAL though */
  XDrawRectangle (XtDisplay (pInfo->canvas), XtWindow (pInfo->canvas),
        thumbGCSmall,
        lpInfo->oldEventX - (width * THUMB_SMALL_MULT) / 2,
        lpInfo->oldEventY - (height * THUMB_SMALL_MULT) / 2,
        width * THUMB_SMALL_MULT,
        height * THUMB_SMALL_MULT);

  busy=False;
}


/*----------------------------------------------------------------*
 |                       SetupColorsAndGCs                        |
 | Called once at the beginning to setup some drawing stuff.      |
 *----------------------------------------------------------------*/
static void
SetupColorsAndGCs ()
{
  int i;
  XColor color;
  Colormap cmap;
  Time time;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " SetupColorsAndGCs%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if ((pInfoList == (PannerInfoRec *) NULL)
      || (pInfoList[LOCAL].canvas == NULL))
    return;

  cmap = DefaultColormapOfScreen (SCR_LOC);

  /*
   * set-up the global GCs.
   */
#if 0
  thumbGCSmall = GetXorGC (pInfoList[LOCAL].canvas);
  extraGC = GetCanvasGC (pInfoList[LOCAL].canvas);
#endif
  thumbGC = GetXorGC (pInfoList[LOCAL].canvas);
  canvasGC = GetCanvasGC (pInfoList[LOCAL].canvas);

  time = GetTimestamp (DPY_ACT);
  /* srand (time (NULL)); avoid new headers */
  srand ((unsigned) time);

  /*
   * Allocate the global color cells for the drawing of each windows.
   * The more random the colors, the better.
   */

  if (XAllocColorCells (DPY_LOC, cmap, False, NULL, 0, cells, COLOR_COUNT))
  {
    for (i = 0; i < COLOR_COUNT; i++)
    {
      color.red = rand () % 65535;
      color.blue = rand () % 65535;
      color.green = rand () % 65535;
      color.pixel = cells[i];
      XStoreColor (DPY_LOC, cmap, &color);
    }
  }
#ifdef ADD_COLOR
  else
  {
    int i, max;
    unsigned long color;
    color_fail |= 2;
    int depth;                  /* ie, 16bit */
    float fmul;
    XGCValues values;
    fprintf (stderr, "panner: no color map, will use depth values\n");
    XtVaGetValues (pInfoList[LOCAL].canvas, XmNforeground, &values.foreground,
                   XmNbackground, &values.background, NULL);
    /* make random color, tuned to screen depth */
    depth = DefaultDepth (DPY_LOC, DefaultScreen (DPY_LOC));
    if (depth == 0)
      depth = 8;                /* err ok */
    depth = pow (2, depth);
    fmul = (float) depth / (float) RAND_MAX;
    if (fmul == 0)
      fmul = 1;
    for (i = 0; i < NUMBER_OF_COLORS; ++i)
    {
      max=10000;
      while ( --max )
      {
        color = (unsigned long) (float) rand () * fmul;
        if( color != values.background )
          break;
      }
      colorw[i] = color;
    }
  }
#endif

  busy=False;
}


/*
 * color is broken i beleive it works for Pallete base only
 */



/*----------------------------------------------------------------*
 |                           GetXorGC                             |
 *----------------------------------------------------------------*/
static GC
GetXorGC (Widget w)
{
  GC gc;
  XGCValues values;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " GetXorGC%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return (NULL);
  busy=True;

  XtVaGetValues (w, XmNforeground, &values.foreground,
                 XmNbackground, &values.background, NULL);

  values.foreground = values.foreground ^ values.background;
  values.function = GXxor;
  values.line_style = LineOnOffDash;

  gc = XtGetGC (w,
                GCForeground | GCBackground | GCFunction | GCLineStyle,
                &values);

  busy=False;

  return (gc);
}


/*----------------------------------------------------------------*
 |                         GetCanvasGC                            |
 *----------------------------------------------------------------*/
static GC
GetCanvasGC (Widget w)
{
  GC gc;
  XGCValues values;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " GetCanvasGC%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return (NULL);
  busy=True;

  XtVaGetValues (w, XmNforeground, &values.foreground,
                 XmNbackground, &values.background, NULL);

  values.foreground = values.background;
  values.function = GXcopy;

  gc = XtGetGC (w, GCForeground | GCBackground | GCFunction, &values);

  busy=False;

  return (gc);
}


#ifndef ADD_PAN

/*----------------------------------------------------------------*
 |                       SetWindowColor                           |
 *----------------------------------------------------------------*/
static void
SetWindowColor (PannerInfoRec * pInfo, int i)
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " SetWindowColor%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  /* should not happen unless a bug or type is in code */
  if ((pInfo == (PannerInfoRec *) NULL) || (pInfo->display == NULL))
    return;

#ifdef ADD_COLOR
  if (color_fail == 2)
    XSetForeground (pInfo->display, canvasGC, colorw[i % NUMBER_OF_COLORS]);
  else
#endif
    XSetForeground (pInfo->display, canvasGC, cells[(i + 1) % COLOR_COUNT]);

  busy=False;
}

#endif

/*----------------------------------------------------------------*
 |                     TranslateCoordinates                       |
 *----------------------------------------------------------------*/


static void
TranslateCoordinates (PannerInfoRec * pInfo,
                      int x1, int y1, unsigned int width1,
                      unsigned int height1, int *x2, int *y2,
                      unsigned int *width2, unsigned int *height2)
{
  int rootW, rootH;
  float xaspect,yaspect;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " TranslateCoordinates%s ", busy?".PUNT":""); fflush(stderr);
#endif
 
  /* should not happen unless a bug or type is in code */
  if (!pInfo)
    return;

  /* see note on recursion callbacks */
  while( busy ) { ; }

  rootW = pInfo->screenW;
  rootH = pInfo->screenH;
  if( !rootW ) rootW = 1;
  if( !rootH ) rootH = 1;
  if( !pInfo->thumbX ) pInfo->thumbX = 1;
  if( !pInfo->thumbY ) pInfo->thumbY = 1;

  /*
  printf("\n BF:  1(%d,%d %u,%u) 2(%d,%d %u,%u) \n",
  x1,y1,width1,height1, *x2,*y2,*width2,*height2 );
  */

  /* this is the  (thumb|canvas) / display ratio (aspect).
     we created thumb with same aspect as canvas (which may stretch windows)
     and so if the Translate is invoked for display->thumb or display->canvas
     we are indifferent don't need to know, the answer is there is only one
     aspect translation
   */

  *x2 = (float) x1 * (float) pInfo->thumbW / (float) rootW
        + (float) pInfo->thumbX;
  *y2 = (float) y1 * (float) pInfo->thumbH / (float) rootH
        + (float) pInfo->thumbY;
  *width2 = (float) width1 * (float) pInfo->thumbW / (float) rootW;
  *height2 = (float) height1 * (float) pInfo->thumbH / (float) rootH;

  /*
  printf("\n AF:  1(%d,%d %u,%u) 2(%d,%d %u,%u) \n",
  x1,y1,width1,height1, *x2,*y2,*width2,*height2 );
  */

  busy=False;
}

/*----------------------------------------------------------------*
 |                     TranslateZoomCoordinates  stretch/fill     |
 *----------------------------------------------------------------*/

static void
TranslateZoomCoordinates ( PannerInfoRec * pInfo,
                         float x1, float y1, float width1, float height1,
                         float zoom1,
                         float *x2, float *y2, float *width2, float *height2 )
{
  float xaspect,yaspect, x,y,width,height,W,H;
  static int busy=False;

  if( !pInfo )
    return;

  /* see note on recursion callbacks */
  while( busy ) { ; }

  W = pInfo->canvasW;
  H = pInfo->canvasH;
  xaspect=1.0;yaspect=1.0;

  if ( pInfo->screenW )
    xaspect = W / (float)pInfo->screenW ;
  if ( pInfo->screenH )
    yaspect = H / (float)pInfo->screenH ;

  /* map points from display onto canvas */
  x = x1 * xaspect;
  y = y1 * yaspect;
  width = width1 * xaspect;
  height = height1 * yaspect;

  /* now apply zoom */
  *x2 = (x * zoom1) + ( W * (1.0 - zoom1) / 2.0 ); 
  *y2 = (y * zoom1) + ( H * (1.0 - zoom1) / 2.0 );
  *width2 = width * zoom1;
  *height2 = height * zoom1;

  busy=False;
}

/*----------------------------------------------------------------*
 |              InverseTranslateZoomCoordinates  stretch/fill     |
 *----------------------------------------------------------------*/

static void
InverseTranslateZoomCoordinates ( PannerInfoRec * pInfo,
                         float x1, float y1, float width1, float height1,
                         float zoom1,
                         float *x2, float *y2, float *width2, float *height2 )
{
  float xaspect,yaspect, x,y,width,height,W,H;
  static int busy=False;

  if( !pInfo )
    return;

  /* see note on recursion callbacks */
  while( busy ) { ; }

  W = pInfo->canvasW;
  H = pInfo->canvasH;
  xaspect=1;yaspect=1;

  if ( pInfo->screenW )
    xaspect = W / (float)pInfo->screenW ;
  if ( pInfo->screenH )
    yaspect = H / (float)pInfo->screenH ;
  if ( xaspect==0 || yaspect==0 || zoom1 == 0)
    return ;

  /* undo zoom - our divisions will chop accuracy, but ok */
  x = (x1 - (W * (1.0 - zoom1) / 2.0)) / zoom1;
  y = (y1 - (H * (1.0 - zoom1) / 2.0)) / zoom1;

  width = width1 / zoom1;
  height = height1 / zoom1;

  /* map points from canvas onto display */
  *x2 = x / xaspect;
  *y2 = y / yaspect;
  *width2 = width / xaspect;
  *height2 = height / yaspect;

  busy=False;
}


/*----------------------------------------------------------------*
 |                          IgnoreError                           |
 *----------------------------------------------------------------*/
static int
IgnoreError (Display * dsp, XErrorEvent * event)
{
  /*
   * Do Nothing...
   * This is needed since we will may be updating the list of window
   * while one of them goes away.  Ie: the window list received from
   * XQueryTree may not be valid for the entire loop where we get each
   * window's geometry.
   */
  return 0;                     /* make compiler happy */
}



/*======================= TRACKING HANDLERS ======================*/


/*----------------------------------------------------------------*
 |                          panEdge                            |
 *----------------------------------------------------------------*/

 /* no aspect cals here - we only set dx dy to constants */

static void
panEdge (XEvent * event)
{
  int x, y, rootW, rootH, config;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " panEdge%s ", busy?".PUNT":""); fflush(stderr);
#endif
/*  see note on recursion callbacks
  if( busy )
    return ;
  busy=True;
*/

  if (tracking)
  {
#ifdef PAN_DEBUG
  fprintf (stderr, " PE! "); fflush (stderr);
#endif
    return;
  }
  if (DPY_ACT == NULL)
    return;
  if (SCR_ACT == NULL)
    return;

  /* if (event->xmotion.type == MotionNotify ) */
/* see discussion in MoveScreen
  if (pInfo == NULL )
    return ;
  rootW = pInfo->screenW;
  rootH = pInfo->screenH;
*/
  rootW = SCR_ACTW;
  rootH = SCR_ACTH;

#ifdef PAN_DEBUG
  fprintf (stderr, " PE(%d,%d %d,%d) ",
           event->xmotion.x_root, event->xmotion.y_root, rootW, rootH);
  fflush (stderr);
#endif

  x = 0;
  y = 0;
  if (event->xmotion.x_root <= 0)
    x = edge_speed;
  if (event->xmotion.x_root >= rootW - 1)
    x = -edge_speed;
  if (event->xmotion.y_root <= 0)
    y = edge_speed;
  if (event->xmotion.y_root >= rootH - 1)
    y = -edge_speed;
  if (!x && !y)
    return;

  /* expects 1 if panner is calling, always 1 */
  config = 1;
  config |= 8;

  {
   /* see discussion in MoveScreen */
    Display *display;
    Time time;
    XPointerMovedEvent *motionEvent = (XPointerMovedEvent *) event;
    Window window;
    Atom MY_PANNER_PROP;

    int i;
    float f;

    /*
    display = pInfo->display;
    window = pInfo->canvas;
    */
    display = XtDisplay (notebook);
    window = XtWindow (notebook);

    time = GetTimestamp (DPY_ACT);

    f = edge_slide;
    if ( fabs((float) x / f) < 1 && fabs((float) y / f) < 1)
      f = 1;
    x = (float) x / f;
    y = (float) y / f;
    i = f;
    for (; i > 0; --i)
    {

      /* XPutBackEvent(DPY_ACT, &event); return; */
      /* MoveScreen (pInfoList[LOCAL], x, y, motionEvent->time); elsewhere */

      {
        unsigned char * uc = transmit_data;
        /* memset(transmit_data, 0, (PAN_PACK_WIDTH/8)*PAN_PACK_LEN); */
        /* maybe superstition but don't send X alloc'ed memory to libc */
        PackCARD32 (uc, (float) x * edge_mult );
        uc+=4;
        PackCARD32 (uc, (float) y * edge_mult );
        uc+=4;
        PackCARD32 (uc, config);
        uc+=4;
        PackCARD32 (uc, 0);
        uc+=4;
        PackCARD32 (uc, 0);
        uc+=4;
        PackCARD32 (uc, (4294967296 / 2 - 1776)); /* signature */
      }

      if (x_only)
      {
        MY_PANNER_PROP = XInternAtom (display, "MY_PANNER_PROP", False);

        XChangeProperty (display, window, MY_PANNER_PROP, MY_PANNER_PROP,
                         PAN_PACK_LEN, PropModeReplace,
                         (unsigned char *) transmit_data, 4 * XC_REC_LEN);

        XConvertSelection (DPY_ACT, pInfoList[DSP].WM, pInfoList[DSP].WM_PAN,
                           MY_PANNER_PROP, window, time);

        /* motionEvent->time */
      }
      /* pInfoList is the same as &(pInfoList[LOCAL]) using C */
      if ((++edge_cnt % (int) edge_update) == 0)
        UpdatePannerView (pInfoList, DSP);
    }
  }

  busy=False;
}

/*----------------------------------------------------------------*
 |                          CenterScreen                            |
 *----------------------------------------------------------------*/

static void
CenterScreen (Widget w,
              XtPointer clientData, XEvent * event, Boolean * dispatch)
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " CenterScreen%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

/*
    pInfoList[LOCAL].thumbX = pInfoList[LOCAL].canvasW  / 2;
    pInfoList[LOCAL].thumbY = pInfoList[LOCAL].canvasH  / 2;
    pInfoList[DSP].thumbX = pInfoList[DSP].canvasW  / 2;
    pInfoList[DSP].thumbY = pInfoList[DSP].canvasH  / 2;
*/

  busy=False;
}


/*----------------------------------------------------------------*
 |                         StartTracking                          |
 *----------------------------------------------------------------*/
static void
StartTracking (Widget w,
               XtPointer clientData, XEvent * event, Boolean * dispatch)
{
  PannerInfoRec *pInfo = (PannerInfoRec *) clientData;
  XPointerMovedEvent *motionEvent = (XPointerMovedEvent *) event;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " StartTracking%s ", busy?".PUNT":""); fflush(stderr);
#endif
/* see note on recursion callbacks
  if( busy )
    return ;
  busy=True;
*/

  /* if we're already tracking, ignore, recursive and or erroneous signal */
  if (tracking)
  {
#ifdef PAN_DEBUG
  fprintf (stderr, " ST! ");
  fflush (stderr);
#endif
    return;
  }

switch ( event->type )
{
  case KeyPress:
  case KeyRelease:
  {
    /*
    KeySym ks;
    FuncKey *key;
    int len;
    unsigned int modifier;
    */

    Boolean once2=False;
    char buffer[2];

    XLookupString(&(event->xkey), buffer, sizeof(buffer), NULL, NULL);

    /* very poor support for "+" and "-" i'd say */
    switch (buffer[0])
    {
      case 45: /* - */
      case 95: /* shift pressed */
        zoom = zoom - .1 ;
        once2=True;
        break;
      case 61: /* + */
      case 43: /* shift pressed */
        zoom = zoom + .1 ;
        once2=True;
        break;
      case 48: /* 1 */
      case 49: /* shift pressed */
        zoom = 1 ;
        once2=True;
        break;
    }

    if( once2 )
    {
      UpdatePannerView (pInfoList, LOCAL);
      if( LOCAL != DSP )
        UpdatePannerView (pInfoList, DSP);
    }
      /*
      modifier = (Event.xkey.state & mods_used);
      ks = XLookupKeysym((XKeyEvent *) &Event, 0);
      */
  }
  break;

  case ButtonPress:
  if (event->xbutton.button == Button1 || event->xbutton.button == Button3)
  {
    if (event->xbutton.button == Button3)
    {
      button3 = True;
      /* whether to create a tracking callback ie support sliding */
      tracking = PAN_USE_SLIDING;
      track_count = 0;
      pInfo->oldEventX = event->xbutton.x;
      pInfo->oldEventY = event->xbutton.y;
      /* if we yet told mwm to choose a window for sliding, do only 1x */
      mwm_needs_notify_to_grab=True;
    }
    /* refuse to do two trackings at once to KISS */
    if (event->xbutton.button == Button1)
    {
      button1 = True;
      tracking = PAN_USE_SLIDING;
      track_count = 0;
      if( button3 == True)
      {
        button3 = False;
        tracking = False;
      }
    }

    pInfo->lastEventX = event->xbutton.x;
    pInfo->lastEventY = event->xbutton.y;

    XtAddEventHandler (w, ButtonReleaseMask, False, StopTracking, clientData);

    if( tracking )
    {
    if (button1)
      XtAddEventHandler (w, Button1MotionMask, False, DoTracking, clientData);
    if (button3)
      XtAddEventHandler (w, Button3MotionMask, False, DoTracking, clientData);
    }

  }
  break;

}
  busy=False;
}

/* why track button1 if it takes single click only ?
   because the border is dragged and will not be cleaned up
   maybe somday the screen border drag will be used for something
*/


/*----------------------------------------------------------------*
 |                          DoTracking                            |
 *----------------------------------------------------------------*/

static void
DoTracking (Widget w,
            XtPointer clientData, XEvent * event, Boolean * dispatch)
{
  PannerInfoRec *pInfo = (PannerInfoRec *) clientData;
  XPointerMovedEvent *motionEvent = (XPointerMovedEvent *) event;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoTracking%s ", busy?".PUNT":""); fflush(stderr);
#endif
/*  see note on recursion callbacks
  if( busy )
    return ;
  busy=True;
*/

  /* should not happen unless a bug or type is in code */
  if (pInfo == (PannerInfoRec *) NULL)
    return;

  /* if we never got a BeginTracking , ignore */
  if (!tracking)
  {
#ifdef PAN_DEBUG
  fprintf (stderr, " ST! ");
  fflush (stderr);
#endif
    return;
  }

  /* WARNING SOME X might call CB resursive entry or more than once
   * because of that we can't use track_count as whether we began drag
   * technically panner should "check Busy" on every of it's functions
   * that do anything "bad" when recursively entered (if you don't know
   * what that means then check Busy if you change anything)
   */

  ++track_count;

  if( !button3 )
    if( (track_count % (int) pan_mult) != 0 )
      return;

#ifdef PAN_DEBUG
  fprintf (stderr, " DoTracking(%d,%d)(%d,%d) ",
           event->xbutton.x, event->xbutton.y,
           pInfo->lastEventX, pInfo->lastEventX );
  fflush (stderr);
#endif

  MoveScreen (pInfo, event->xbutton.x, event->xbutton.y,
              motionEvent->time);

  pInfo->lastEventX = event->xbutton.x;
  pInfo->lastEventY = event->xbutton.y;

  busy=False;
}


/*----------------------------------------------------------------*
 |                         StopTracking                           |
 *----------------------------------------------------------------*/

static void
StopTracking (Widget w,
              XtPointer clientData, XEvent * event, Boolean * dispatch)
{

/* take option of allowing recursive request to remove Handlers
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " StopTracking%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;
*/

  /* if we never got a BeginTracking , ignore */
  if (!tracking)
  {
#ifdef PAN_DEBUG
  fprintf (stderr, " STT! ");
  fflush (stderr);
#endif
/*
    return;
*/
  }

  if (event->xbutton.button == Button1)
  {
    XtRemoveEventHandler (w, Button1MotionMask, False, DoTracking,
                          clientData);
  }
  /* ?? note: spurious does NOT mean button3 is up or drag is done */
  if (event->xbutton.button == Button3)
  {
    XtRemoveEventHandler (w, Button3MotionMask, False, DoTracking,
                          clientData);
  }
  CenterScreen (w, clientData, event, dispatch);

  XtRemoveEventHandler (w, ButtonReleaseMask, False, StopTracking,
                        clientData);

  UpdatePannerView (pInfoList, DSP);

  if( tracking )
  {
    button3 = False;
    button1 = False;
    tracking = False;
    track_count = 0;
    mwm_needs_notify_to_grab=False;
  }

  /* busy=False; */

}



/*----------------------------------------------------------------*
 |                          MoveScreen                            |
 *----------------------------------------------------------------*/
/* or move single window for button3 */
/* callers:  DoTracking if button3 , StartTracking also if button1 */

static void
MoveScreen (PannerInfoRec * pInfo, int newX, int newY, Time time)
{

  /* static int offsetX=0, offsetY=0; */
  Window win;
#ifdef TRY_ALLOC_ON_MULTISCREENS
  static XtPointer msg;
#endif
  XWindowAttributes attr;
  unsigned config;
  float panDx, panDy;
  float x, y, width,height;
  float xold, yold, widthold,heightold;
  unsigned long size;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " MoveScreen%s ", busy?".PUNT":""); fflush(stderr);
#endif

  if( busy )
    return ;
  busy=True;

  if (!button1 && !button3 )
  {
#if defined(ADD_PAN) && defined(PAN_DEBUG)
    fprintf (stderr, " MSNOB "); fflush (stderr);
#endif
    return;
  }

  /* should not happen unless a bug or type is in code */
  if ((pInfo == (PannerInfoRec *) NULL) || (pInfo->display == NULL))
    return;
  if (button3 && (DPY_LOC == NULL))
    return;

  /* this erases old window dashed line by XOR drawning in same place */
  if (button3 && track_count!=0)
    DrawThumbSmall (pInfo, DSP);
  else
    DrawThumb (pInfo, DSP);

  if (button3 && (track_count % (int) b3_upd_freq == 0))
    UpdatePannerView (pInfo, DSP);

  /* to be simple, put both in screen coord. then make dx,dy mwmpan needs */
  InverseTranslateZoomCoordinates (pInfo,
                                   newX, newY,
                                   pInfo->canvasW, pInfo->canvasH,
                                   zoom,
                                   &x, &y, &width, &height);

  InverseTranslateZoomCoordinates (pInfo,
                                   pInfo->lastEventX,pInfo->lastEventY,
                                   pInfo->canvasW, pInfo->canvasH,
                                   zoom,
                                   &xold, &yold, &widthold, &heightold);

  panDx = x - xold;
  panDy = y - yold;

  if (!button3)
  {
    pInfo->thumbX = newX;
    pInfo->thumbY = newY;
  }
  pInfo->oldEventX = pInfo->lastEventX;
  pInfo->oldEventY = pInfo->lastEventY;

  /* this erases old dashed line by XOR drawning in same place */
  if (button3)
    DrawThumbSmall (pInfo, DSP);
  else
    DrawThumb (pInfo, DSP);

  /* expects 1 if panner is calling, always 1 */
  config = 1;

  /* expects 1 if panner is calling, always 1 */
  config = 1;
  if ( ! mwm_needs_notify_to_grab )
    config |= 2; /* STILL PANNING */
  if (button3) /* else is B1 */
    config |= 4;
  /* 8 if panEdge */


#if 0
  if (button3)
  {
    win = XtWindow (pInfo->canvas);
    XGetWindowAttributes (DPY_LOC, win, &attr);
    fprintf (stderr, "canvasWH(%d,%d)\n", attr.width, attr.height);
  }
  fprintf (stderr, " BTN(%d,%d,%d)\n", (int)button1,(int)button3,(int)tracking);
  fprintf (stderr, "dxy=(%d,%d)\tnewXY=(%d,%d)\tthumbXY=(%d,%d)\n",
           dx, dy, (int)x, (int)y, (int)xold,(int)yold);
  fprintf (stderr, "panDxy=(%d,%d)\tthumbWH=(%d,%d)\n",
           (unsigned) panDx, (unsigned) panDy, pInfo->thumbW, pInfo->thumbH);
  fprintf (stderr, "lastEventXY(%d,%d)\t",
           pInfo->lastEventX, pInfo->lastEventY);
  fprintf (stderr, "dragXY=(%d,%d)\ttr_cnt=%d\n", x, y,track_count);
  fflush (stderr);
#endif

  /*
   * Send Pan message to mwm.
   *   there's a 2nd method one could try but that "needs work" - see EOF
   */

  /* because byte order of hosts likely differ (and mwm uses UnpackCARD32)
   * (pan could be run from rhost -display thishost ) */

  {
    unsigned char * uc = transmit_data;
    PackCARD32 (uc, panDx );
    uc+=4;
    PackCARD32 (uc, panDy );
    uc+=4;
    PackCARD32 (uc, config);
    uc+=4;
/*
    if ( mwm_needs_notify_to_grab )
*/
    if ( button3 )
    {
      PackCARD32 (uc, x);
      uc+=4;
      PackCARD32 (uc, y);
      uc+=4;
      PackCARD32 (uc, (4294967296 / 2 - 1776)); /* signature */
      mwm_needs_notify_to_grab = False;
#ifdef PAN_DEBUG
fprintf (stderr, "\n MWM NOTIFIED \n");
fflush (stderr);
#endif
    }
    else
    {
      PackCARD32 (uc, 0);
      uc+=4;
      PackCARD32 (uc, 0);
      uc+=4;
      PackCARD32 (uc, (4294967296 / 2 - 1776)); /* signature */
    }
  }
  centering = False;
  
#if 0
  { int ik,x; unsigned char *uc;
  for( ik=0; ik<7*4; ++ik)
{
uc = (unsigned char *) transmit_data;
uc += ik;
x = (int) *uc;
fprintf (stderr, "_%d_", x);
fflush (stderr);
}
  }
#endif
#if defined(PAN_DEBUG)
        fprintf(stderr,
        "# PannerSend: (%d,%d) (%d,%d) (%d,%d) SP %u B13 %u EDG %u\n",
        (int)panDx,(int)panDy, (int)x,(int)y,  pInfo->thumbW,pInfo->thumbH,
        (unsigned) (config&2), (unsigned) (config&4), (unsigned) (config&8)) ;
        fflush(stderr);
#endif

  if (x_only)
  {
    Display *display;
    Window window;
    Atom MY_PANNER_PROP;

    display = XtDisplay (notebook); /* notebook just happens to be a global. */
    window = XtWindow (notebook);

    MY_PANNER_PROP = XInternAtom (display, "MY_PANNER_PROP", False);
    LOCK = False;
    if (!LOCK)
    {
      /* lock means wait for CB before sending another */
      LOCK = True;

      XChangeProperty (display, window, MY_PANNER_PROP, MY_PANNER_PROP,
                       PAN_PACK_LEN, PropModeReplace,
                       (unsigned char *) transmit_data, 4 * XC_REC_LEN);

      XConvertSelection (pInfo->display, pInfo->WM, pInfo->WM_PAN,
                       MY_PANNER_PROP, window, time);

#ifdef PAN_DEBUG
  fprintf (stderr, " MS LOCK "); fflush (stderr);
#endif

    }
  }

  busy = False;

}

/*
                       PAN_PACK_LEN*PAN_PACK_WIDTH / 8);
*/


/*----------------------------------------------------------------*
 |                      PACKING FUNCTIONS                         |
 *----------------------------------------------------------------*/

/* 
    NOTE! mwm is unpacking and mwm does NOT use X's card functions
    for it's Pack Unpack (also - we don't know if Xorg cancel cultured
    the pack routines for "improved ones")
	see include at EOF
*/

/*
  X sends a stream of data, the reciever reads stream by ++prt
  for that to preserve numbers the ptr size (and maybe byte order)
  must be handled properly (prepared) on both ends
*/

/*      Function Name: UnpackCARD32
 *      Description: Unpacks an 32 bit value from the protocol data stream.
 *      Arguments: data - Pointer to the data stream.
 *      Returns: the CARD32 from the data stream.
 *
 * NOTE: data is modified to point to the next empty location in the stream.
 */

/*
CARD32
UnpackCARD32 (XtPointer data_ptr)
{
    CARD32 val = UnpackCARD16(data_ptr) << 16;

    val |= UnpackCARD16(data_ptr);
    return(val);
}
CARD16
UnpackCARD16 (XtPointer data_ptr)
{
    CARD16 val = UnpackCARD8(data_ptr) << 8;

    val |= UnpackCARD8(data_ptr);
    return(val);
}
CARD8
UnpackCARD8 (XtPointer data_ptr)
{
    CARD8 val = *((char *) *data_ptr);

    *data_ptr = ((char *) *data_ptr) + 1;
    return(val);
}
*/

/*      Function Name: PackCARD32
 *      Description: Packs an 32 bit value into the data stream.
 *      Arguments: data - The data stream to pack into.
 *                 val - The 32 bit value to pack.
 *      Returns: data - A pointer into the next empty location in the
 *                      data stream.
 */

static XtPointer
PackCARD32 (XtPointer data, CARD32 val)
{
  CARD16 bottom = val & (0xFFFF);
  CARD16 top = val >> 16;

  data = PackCARD16 (data, top);
  data = PackCARD16 (data, bottom);
  return (data);
}
static XtPointer
PackCARD16 (XtPointer data, CARD16 val)
{
  CARD8 bottom = val & (0xFF);
  CARD8 top = val >> 8;

  data = PackCARD8 (data, top);
  data = PackCARD8 (data, bottom);
  return (data);
}
static XtPointer
PackCARD8 (XtPointer data, CARD8 val)
{
  CARD8 *ptr = (CARD8 *) data;

  *ptr = (CARD8) val;
  data = ((char *) data) + 1;
  return (data);
}




/*======================= USER INTERFACE ======================*/

/*----------------------------------------------------------------*
 |                         CreateMenuBar                          |
 *----------------------------------------------------------------*/
static void
CreateMenuBar (Widget parent)
{
  Cardinal n;
  Arg args[10];
  Widget menuBar;
  Widget cascade1, cascade2, cascade3, cascade4;
  Widget menuPane1, menuPane2, menuPane3;
  Widget b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " CreateMenuBar%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  menuBar = XmCreateMenuBar (parent, "menuBar", NULL, 0);

  menuPane1 = XmCreatePulldownMenu (menuBar, "menuPane1", NULL, 0);
  menuPane2 = XmCreatePulldownMenu (menuBar, "menuPane2", NULL, 0);
  menuPane3 = XmCreatePulldownMenu (menuBar, "menuPane3", NULL, 0);

  b1 =
    XtCreateManagedWidget ("b1", xmPushButtonWidgetClass, menuPane1, NULL, 0);

  XtAddCallback (b1, XmNactivateCallback, MenuCB, (XtPointer) MENU_QUIT);

  b2 =
    XtCreateManagedWidget ("b2", xmPushButtonWidgetClass, menuPane2, NULL, 0);

  XtAddCallback (b2, XmNactivateCallback, MenuCB, (XtPointer) MENU_UPDATE);

  b3 =
    XtCreateManagedWidget ("b3", xmPushButtonWidgetClass, menuPane2, NULL, 0);

  XtAddCallback (b3, XmNactivateCallback, MenuCB, (XtPointer) MENU_NEW);

#ifdef ADD_PAN
  b4 =
    XtCreateManagedWidget ("b4", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b4, XmNactivateCallback, MenuCB, (XtPointer) EDGE_START);

  b5 =
    XtCreateManagedWidget ("b5", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b5, XmNactivateCallback, MenuCB, (XtPointer) EDGE_STOP);

  b6 =
    XtCreateManagedWidget ("b6", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b6, XmNactivateCallback, MenuCB, (XtPointer) EDGE_SPEED);

  b7 =
    XtCreateManagedWidget ("b7", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b7, XmNactivateCallback, MenuCB, (XtPointer) EDGE_FREQ);

  b8 =
    XtCreateManagedWidget ("b8", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b8, XmNactivateCallback, MenuCB, (XtPointer) EDGE_SLIDE);

  b9 =
    XtCreateManagedWidget ("b9", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b9, XmNactivateCallback, MenuCB, (XtPointer) PAN_MULT);

  b10 =
    XtCreateManagedWidget ("b10", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b10, XmNactivateCallback, MenuCB, (XtPointer) PAN_MULT);

  b11 =
    XtCreateManagedWidget ("b11", xmPushButtonWidgetClass, menuPane3, NULL, 0);
  XtAddCallback (b11, XmNactivateCallback, MenuCB, (XtPointer) PAN_ZOOM);

#endif

  n = 0;
  XtSetArg (args[n], XmNsubMenuId, menuPane1);
  n++;
  cascade1 = XmCreateCascadeButton (menuBar, "cascade1", args, n);
  XtManageChild (cascade1);

  n = 0;
  XtSetArg (args[n], XmNsubMenuId, menuPane2);
  n++;
  cascade2 = XmCreateCascadeButton (menuBar, "cascade2", args, n);
  XtManageChild (cascade2);

  n = 0;
  XtSetArg (args[n], XmNsubMenuId, menuPane3);
  n++;
  cascade3 = XmCreateCascadeButton (menuBar, "cascade3", args, n);
  XtManageChild (cascade3);

  n = 0;
  cascade4 = XmCreateCascadeButton (menuBar, "cascade4", args, n);
  XtAddCallback (cascade4, XmNactivateCallback, MenuCB,
                 (XtPointer) MENU_HELP);
  XtManageChild (cascade4);

  n = 0;
  XtSetArg (args[n], XmNmenuHelpWidget, cascade4);
  n++;
  XtSetValues (menuBar, args, n);

  XtManageChild (menuBar);

  busy=False;
}


/*----------------------------------------------------------------*
 |                             timeoutCB                             |
 *----------------------------------------------------------------*/
static void
timeoutCB (XtPointer client_data, XtIntervalId * id)
{
  Widget w = (Widget) client_data;
  Window root_return, child_return;
  int root_x_return, root_y_return, win_x_return, win_y_return;
  unsigned int mask_return;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " timeoutCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (panedge)
    if (XQueryPointer (DPY_ACT, DefaultRootWindow (DPY_ACT), &root_return,
                       &child_return, &root_x_return, &root_y_return,
                       &win_x_return, &win_y_return, &mask_return))
    {
      time_event.xmotion.x_root = root_x_return;
      time_event.xmotion.y_root = root_y_return;
      panEdge (&time_event);
    }
  XtRemoveTimeOut (interval_id);
  if (panedge)
    interval_id = XtAppAddTimeOut (app, edge_freq, timeoutCB, client_data);

  busy=False;
}
/* we'd prefer this but since panEdge pans only LOCAL it's not necessary
   the following is not allowed (a differnt way would need to be found)
timeoutCB (XtPointer client_data, XtIntervalId * id, int pInfoRecNum)
 ... panEdge (&time_event, &(pInfoList[pInfoRecNum]) );
*/

/*----------------------------------------------------------------*
 |                             MenuCB                             |
 *----------------------------------------------------------------*/
static void
MenuCB (Widget w, XtPointer clientData, XtPointer callData)
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " MenuCB%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  switch ((long) clientData)
  {
  case MENU_UPDATE:
    DoUpdatePanner (active_pInfo_rec);
    break;
  case MENU_NEW:
    DoAddDisplay ();
    break;
  case MENU_QUIT:
    DoQuit ();
    break;
  case MENU_HELP:
    DoHelp ();
    break;
  case EDGE_SPEED:
  case EDGE_FREQ:
  case EDGE_SLIDE:
  case EDGE_MULT:
  case PAN_MULT:
  case PAN_ZOOM:
    which_num = (long) clientData;
    DoNumEdge ();
    break;
  case EDGE_START:
    if (!panedge) /* && DPY_ACT != NULL */
    {
      panedge = True;
      interval_id = XtAppAddTimeOut (app, edge_freq, timeoutCB, clientData);
      /* XSelectInput(DPY_ACT,DefaultRootWindow(DPY_ACT),PointerMotionMask); */
    }
    break;
  case EDGE_STOP:
    /* if(panedge)
     *   XSelectInput(DPY_ACT,DefaultRootWindow(DPY_ACT),NoEventMask); */
    panedge = False;
    break;
  }

  busy=False;
}


/*----------------------------------------------------------------*
 |                         DoUpdatePanner                         |
 *----------------------------------------------------------------*/

/* called from main menu, a good place to reset uncertain states */
/* called from HandlePropertyChange */

static void
DoUpdatePanner (int iDSP)
{
  Window win, win2;
  XWindowAttributes attr;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoUpdatePanner%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

#ifdef ADD_PAN
  /* mouse must have gone up, so */
  button3 = False;
  button1 = False;
  /* tracking = False; but maybe CB hasn't gotten back yet, don't prevent */
  track_count = 0;
  mwm_needs_notify_to_grab=False;
#endif
  LOCK = False;
#ifdef PAN_DEBUG
  fprintf (stderr, " unLOCK "); fflush (stderr);
#endif

/* UpdatePannerView ... callback does it */

  busy=False;
}

/*
  XClearArea (DPY_LOC, XtWindow (pInfoList[DSP].canvas), 0, 0, 0, 0, False);
  DrawWindows (pInfoList);
  DrawThumb (&pInfoList[DSP]);
*/

/*----------------------------------------------------------------*
 |                          DoAddDisplay                          |
 *----------------------------------------------------------------*/
static void
DoAddDisplay ()
{
  static Widget dlog = NULL;
  Arg args[3];
  int n;
  Object obj, objp;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoAddDisplay%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (dlog == NULL)
  {
    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);
    n++;
    dlog = XmCreatePromptDialog (pInfoList[LOCAL].shell, "AddDisplayDialog",
                                 args, n);

    XtAddCallback (dlog, XmNokCallback, DoAddDisplayCB, &(pInfoList[LOCAL]));

    XtUnmanageChild (XmSelectionBoxGetChild (dlog, XmDIALOG_HELP_BUTTON));
  }

  XtManageChild (dlog);

  busy=False;
}
#if 0
  fprintf(stderr,"panner managechild: wait... \n");fflush(stderr);
  fprintf(stderr,"panner managechild: back \n");fflush(stderr);
#endif
  /*
   * ie, in any app here is were you get 5 sec block/hang if Mwm does
   * not Handle Configure Notify when Xt does XConfigureWindow then
   * sets property XSetWMNormalHints on (almost) final dialog box which
   * needs a WM wrapping
   */

/*----------------------------------------------------------------*
 |                              DoHelp                            |
 *----------------------------------------------------------------*/
static void
DoHelp ()
{
  static Widget dlog = NULL;
  Arg args[3];
  int n;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoHelp%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (dlog == NULL)
  {
    dlog = XmCreateInformationDialog (pInfoList[LOCAL].shell, "HelpDialog",
                                      NULL, 0);
    XtUnmanageChild (XmMessageBoxGetChild (dlog, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild (XmMessageBoxGetChild (dlog, XmDIALOG_CANCEL_BUTTON));
  }

  XtManageChild (dlog);

  busy=False;
}


/*----------------------------------------------------------------*
 |                              DoQuit                            |
 *----------------------------------------------------------------*/
static void
DoQuit ()
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoQuit%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  XSync (DPY_LOC, False);
  XCloseDisplay (DPY_LOC);

  busy=False;

  exit (0);
}

#ifdef ADD_PAN

/*----------------------------------------------------------------*
 |                          DoNumEdge                             |
 *----------------------------------------------------------------*/

static void
DoNumEdge ()
{
  static Widget dlog = NULL;
  Arg args[3];
  int n;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " DoNumEdge%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (dlog == NULL)
  {
    n = 0;
    XtSetArg (args[n], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);
    n++;
    dlog = XmCreatePromptDialog (pInfoList[LOCAL].shell, "NumberDialog", args, n);
	/* to open dialog box to set global variable */
	/* does not create an edge pan CB */
    XtAddCallback (dlog, XmNokCallback, DoNumEdgeCB, &(pInfoList[LOCAL]) );
    XtUnmanageChild (XmSelectionBoxGetChild (dlog, XmDIALOG_HELP_BUTTON));
  }
  XtManageChild (dlog);

  busy=False;
}
#endif


/*----------------------------------------------------------------*
 |                         GetTimeStamp                           |
 *----------------------------------------------------------------*/
Time
GetTimestamp (Display * dsp)
{
  XEvent event;
  XWindowAttributes attr;
  Atom timeProp = XInternAtom (dsp, "_MOTIF_CURRENT_TIME", False);
  Window rwin = DefaultRootWindow (dsp);

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " GetTimeStamp%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return (0);
  busy=True;

  XGetWindowAttributes (dsp, rwin, &attr);

  if (!(attr.your_event_mask & PropertyChangeMask))
    XSelectInput (dsp, rwin, attr.your_event_mask | PropertyChangeMask);

  XChangeProperty (dsp, rwin, timeProp, timeProp, 8, PropModeAppend, NULL, 0);

  XWindowEvent (dsp, rwin, PropertyChangeMask, &event);

  if (!(attr.your_event_mask & PropertyChangeMask))
    XSelectInput (dsp, rwin, attr.your_event_mask);

  busy=False;

  return (event.xproperty.time);
}


/*----------------------------------------------------------------*
 |                      CheckPinnedState                          |
 *----------------------------------------------------------------*/
/* always pinned and WM has no pin supp. */
#ifndef ADD_PAN
static void
CheckPinnedState ()
{
  static int panDx = 0, panDy = -1;
  XtPointer msg;
  unsigned long size;
  Window rWin, child;
  int x, y;
  unsigned int width, height, bWidth, depth;
  Time time = GetTimestamp (DPY_LOC);

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " CheckPinnedState%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (pinnedState == VERIFIED)
    return;

  panDy = -panDy;

  pinnedState = VERIFYING;

  /* Get position of the top-level shell */
  XGetGeometry (DPY_LOC, XtWindow (pInfoList[LOCAL].shell),
                &rWin, &x, &y, &width, &height, &bWidth, &depth);

  XTranslateCoordinates (DPY_LOC,
                         XtWindow (pInfoList[LOCAL].shell), rWin, x, y,
                         &origX, &origY, &child);

  size = sizeof (CARD32);       /* panDx */
  size += sizeof (CARD32);      /* panDy */
  size += sizeof (CARD8);       /* config */

  msg = transmit_data = (XtPointer) XtMalloc (sizeof (CARD8) * size);

  msg = PackCARD32 (msg, panDx);
  msg = PackCARD32 (msg, panDy);
  msg = PackCARD8 (msg, True);

  if (!XmeNamedSink (pInfoList[LOCAL].utmShell,
                     pInfoList[LOCAL].WM, XmCOPY, (XtPointer) transmit_data, time)
     )
    printf ("Error - UTM Transfer failed.\n");

  busy=False;
}

/*----------------------------------------------------------------*
 |                      ShowPinStateWarning                       |
 *----------------------------------------------------------------*/
static void
ShowPinStateWarning ()
{
  static Widget dlog = NULL;
  Arg args[3];
  int n;

  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " ShowPinStateWarning%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  if (dlog == NULL)
  {
    dlog = XmCreateWarningDialog (pInfoList[LOCAL].shell, "WarningDialog",
                                  NULL, 0);
    XtUnmanageChild (XmMessageBoxGetChild (dlog, XmDIALOG_HELP_BUTTON));
    XtUnmanageChild (XmMessageBoxGetChild (dlog, XmDIALOG_CANCEL_BUTTON));
  }
  XtManageChild (dlog);

  busy=False;
}

#endif /* ! ADD_PAN */


/*----------------------------------------------------------------*
 |                       HandleInitialExpose                      |
 *----------------------------------------------------------------*/
static void
HandleInitialExpose (Widget w,
                     XtPointer clientData, XEvent * event, Boolean * cont)
{
  static int busy=False;
#if defined(PAN_DEBUG)
  fprintf(stderr, " HandleInitialExpose%s ", busy?".PUNT":""); fflush(stderr);
#endif
  if( busy )
    return ;
  busy=True;

  XtRemoveEventHandler (w, ExposureMask, False, HandleInitialExpose, NULL);
#ifndef ADD_PAN
  CheckPinnedState ();
#endif

  busy=False;
}

#ifdef ADD_PAN

/* KNOWN ISSUES
   click and windows don't move:
      .  usually due button3 never becomes false due to never called back
      .  was seen due to CARDS sizes or XmeNameSink - but have 2 kinds
 */

  /* NOTES */
  /* XtFree never called for X_ONLY
   * i'd prefer "trash cards" to memory climbs - never just assume someone
   * is calling back and its ok to free memory 1-1 that way
   *   1) store on server 1-at-a-time in clobber mode per host per client
   *   4) oops Xme says static is ok.  do that.
   */
  /* this is only free of msg = transmit_data, location_data
   * i dont at all like the idea of hoping for callback to free
   * since that means crashing X or PC if anything is intermittent
   * also: XmTransferValue says this callback should aid in data not free it
   * callback NULL (ie, esp for XtFree) remember callback (message)
   * -->
   * could be lost or even sent 2x X is client server client should be
   * autonomous from server state (changes) or goofs as much as possible
   */
/*
 * ADD_PAN ? gets _MOTIF_WM_PAN_POSITION but doesnt sent any back out
 *   extra complexity of the either waiting for or tangling with is unnecessary
 *   a "real deal" includes timestamping, real order, lost msg handling,
 *   to do that right.  a better referee to be simple: ask server
 */

    /*
     * Note 1 - to really make this work across multiple displays,
     * the window argument must reside on the same display as WM_Si.
     */
    /*
     * Use a lock to make sure the property was read by Mwm.
     * When the pan-property is updated, it's safe to make another
     * conversion.
     */
    /* see also HandlePropertyChange */
    /* for TRY_ALLOC_ON_MULTISCREENS transmit_data is XtFreed
     * in HandlePropertyChange (which is NOT guaranteed)
     */
#endif

/* ----------------SKIP------------------------------------*/

#if 0

/* note how this requires calling XtFree on memory we did not
   definitely allocate */

#if defined(TRY_ALLOC_ON_MULTISCREENS) || !defined(ADD_PAN)

  /* for PAN SKIP THIS SECTION */

/*   there's a 2nd method one could try but that "needs work" - see EOF
/* 
 * tries to alloc per screen relies on callback to free for X_ONLY
 * but that might not happen (using ADD_PAN: never happens)
 * instead just make memory global and simple
 */
  size = sizeof (CARD32);       /* panDx */
  size += sizeof (CARD32);      /* panDy */
#ifndef ADD_PAN
  size += sizeof (CARD8);       /* config */
#else
  size += sizeof (CARD32);      /* config */
  size += sizeof (CARD32);      /* panDy */
  size += sizeof (CARD32);      /* panDy */
  size += sizeof (CARD32);      /* panDy */
  size += sizeof (CARD32);      /* panDy */
#endif
  /* IGNORE */
#if defined(ADD_PAN) && defined(PAN_DEBUG)
  fprintf (stderr, "allocs=%d\n", msg_xallocs);
  fflush (stderr);
#endif
  if (msg_xallocs)
  {
    XtFree ((char *) transmit_data);
    transmit_data = NULL;
    --msg_xallocs;
  }
  ++msg_xallocs;
#ifndef ADD_PAN
  msg = transmit_data = (XtPointer) XtMalloc (sizeof (CARD8) * size);
#else
  msg = transmit_data = (XtPointer) XtMalloc (sizeof (CARD32) * size);
#endif
#ifndef ADD_PAN
  msg = PackCARD32 (msg, panDx);
  msg = PackCARD32 (msg, panDy);
  msg = PackCARD32 (msg, config);
  msg = PackCARD32 (msg, config);
#else
  msg = PackCARD32 (msg, 1);
#endif
  /* IGNORE */
#ifdef ADD_PAN
  if ( mwm_needs_notify_to_grab )
  {
    /* wmp needs to know this extra info to find the drag child/window */
    msg = PackCARD32 (msg, x);
    msg = PackCARD32 (msg, y);
    msg = PackCARD32 (msg, pInfo->thumbW);
    msg = PackCARD32 (msg, pInfo->thumbH);
    mwm_needs_notify_to_grab=False;
  }
  else
  {
    /* else only relative motion offsets were needed */
    msg = PackCARD32 (msg, 0);
    msg = PackCARD32 (msg, 0);
    msg = PackCARD32 (msg, 0);
    msg = PackCARD32 (msg, 0);
  }
#endif
#endif /* TRY_ALLOC_ON_MULTISCREENS SKIP */

/* then replace the changprop call with this */

      XChangeProperty (display, window, MY_PANNER_PROP, MY_PANNER_PROP,
                       PAN_PACK_WIDTH, PropModeReplace,
                       (unsigned char *) transmit_data[data_rot],
                       size);
                       /* elsewhere PAN_SIZE was used */

/* -----------------------------------------------------*/

.  i can't get this to work i don't think it worked fully in last release
   of panner - perhaps there are tricks to know

  if (x_only)
  { /* XChangeProp ... */ ; }
  else
  {
    /* this gets a callback from Xme so append is ignored , taken care of */

    if (!XmeNamedSink (pInfo->utmShell, /* widget with destination callback */
                       pInfo->WM, /* named selection - ie. Window Manager */
                       XmCOPY,  /* operation to perform on the data */
                       (XtPointer) transmit_data,  /* pointer to param data, */
                       time ) /*  free n TransferDone proc. */
      )
      printf ("Error - UTM Transfer failed.\n");
  }

/* -----------------------------------------------------*/

#endif
/* if 0, skip section */

/*  see note on recursion callbacks
	NOTE !  i was told (some) CB for X and or Motif work by recursion
	(unsure if it over-runs stack but it is required)
	(we always punt if we don't allow)
*/
