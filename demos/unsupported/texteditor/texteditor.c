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
static char rcsid[] = "$XConsortium: texteditor.c /main/6 1995/07/14 09:44:58 drk $"
#endif
#endif

/************************************************************
 *
 *      textedit.c -- simple text editor
 *              Ellis S. Cohen
 *         Open Software Foundation
 *
 *   This simple text editor allows a single file at a time to
 *   be edited in one or more panes, and also allows the file to
 *   be saved, saved under a new name, copied, moved, or removed
 *
 *   The code in this file is used to initialize the application,
 *   to define localizable strings, and to create widgets.
 *   It does so by using the Mrm library to read UID files (compiled
 *   UIL files).  The code in this file hides Mrm from the rest
 *   of the application.
 *
 ************************************************************/

#include <X11/Intrinsic.h>

#include <Xm/Xm.h>
#include <Xm/CSText.h>
#include <Xm/FileSB.h>

#include <Mrm/MrmPublic.h>

#include <Xmd/Help.h>
#include <Xmd/Print.h>

#include "dlg.h"
#include "tk.h"

extern char *appString;
extern XmString openFileString, openString,
                saveFileString, saveString,
                copyFileString, copyString,
                moveFileString, moveString,
                warnOpenString, warnWriteString, warnRemoveString;

XtAppContext app_context;
extern Display *dpy;
extern Widget toplevel, panedWindow, textFirst, textStore;
extern Widget fileDialog, saveDialog, warnDialog, questionDialog;
extern Widget helpDialog, printDialog;
extern Widget openToggle, saveToggle, copyToggle, moveToggle;
extern Widget formatMenu;

static  char *mrmfiles[] = { "textedit.uid" };
static XmRenderTable renditions;

#define MAX_ARGS 10
static Arg args[MAX_ARGS];
static int n;

static MrmHierarchy muid;
static MrmType type;

#define APP_CLASS "XmdTextEditor"
char *fallback_resources[] = {
  "*text.rows: 24",
  "*text.columns: 80",
  "*print_manager.printerList: lp,./texteditor.txt",
  "*selectColor:	XmDEFAULT_SELECT_COLOR",
  NULL
  };


 /************************************************************
 *     Create Text Pane
 ************************************************************/

      /* Called to create another text pane in the PanedWindow.
         "paneht" is its desired height. */

Widget
DemoTextPaneCreate(int paneht)
{
  Widget w = NULL;

  /* Each time "textPane" is fetched, a new text widget is created.
     Its source is obtained from textStore.
     We set paneMinimum (as well as height) to paneHt to ensure
     it will actually get that size */

  n = 0;
  XtSetArg( args[n], XmNsource, XmCSTextGetSource( textStore ) ); n++; 
  XtSetArg( args[n], XmNheight, paneht ); n++;
  XtSetArg( args[n], XmNpaneMinimum, paneht ); n++;
  XtSetArg( args[n], XmNrenderTable, renditions ); n++;
  MrmFetchWidgetOverride( muid, "textPane", panedWindow,
			 NULL, args, n,  &w, &type);
  
  XtManageChild( w );

  /* Now that "textPane" is managed, we can reset paneMinimum */

  n = 0;
  XtSetArg( args[n], XmNpaneMinimum, 20 ); n++;
  XtSetValues( XtParent(w), args, n );
  return w;
}

/************************************************************
 *     Initialize the Application
 ************************************************************/

int
main(int argc, char *argv[])
{
    Widget mainWindow;
    Widget viewMenu;
    Widget tmp_wid;
    Widget menuBar;

      /* Initialize Mrm and Xt */

    MrmInitialize();

    toplevel = XtVaAppInitialize(&app_context, APP_CLASS, NULL, 0, &argc, argv,
				 fallback_resources, 0);
    dpy = XtDisplay(toplevel);

      /* Associate callback names to be obtained from UIL files
         with callback routines in the application, and open
         the UIL database */

    TkRegisterCallbacks();
    MrmOpenHierarchy( 1, mrmfiles, NULL, &muid );

      /* Get string names (which may be locale-specific) */

    MrmFetchLiteral( muid, "appString", dpy, (XtPointer)&appString, &type );
    MrmFetchLiteral( muid, "openFileString", dpy, (XtPointer)&openFileString, &type );
    MrmFetchLiteral( muid, "openLabelString", dpy, (XtPointer)&openString, &type );
    MrmFetchLiteral( muid, "saveFileString", dpy, (XtPointer)&saveFileString, &type );
    MrmFetchLiteral( muid, "saveLabelString", dpy, (XtPointer)&saveString, &type );
    MrmFetchLiteral( muid, "copyFileString", dpy, (XtPointer)&copyFileString, &type );
    MrmFetchLiteral( muid, "copyLabelString", dpy, (XtPointer)&copyString, &type );
    MrmFetchLiteral( muid, "moveFileString", dpy, (XtPointer)&moveFileString, &type );
    MrmFetchLiteral( muid, "moveLabelString", dpy, (XtPointer)&moveString, &type );
    MrmFetchLiteral( muid, "warnOpenString", dpy, (XtPointer)&warnOpenString, &type );
    MrmFetchLiteral( muid, "warnWriteString", dpy, (XtPointer)&warnWriteString, &type );
    MrmFetchLiteral( muid, "warnRemoveString", dpy, (XtPointer)&warnRemoveString, &type );

      /* Instantiate and Manage MainWindow widget hierarchy */

    mainWindow = NULL;
    /* Need to exit cleanly here if this fails. */
    MrmFetchWidget( muid, "mainWindow", toplevel, &mainWindow, &type);
    if (mainWindow == NULL) exit(1);
    
    /* Modify the menuBar from its initial state. */
    menuBar = XtNameToWidget(mainWindow, "*menuBar");
    viewMenu = XtNameToWidget(menuBar, "*viewMenu");
    
    XtUnmanageChild(XtNameToWidget(viewMenu, "*changeViewButton"));
    XtUnmanageChild(XtNameToWidget(viewMenu, "*newWindowButton"));
    
    MrmFetchWidget(muid, "splitButton", viewMenu, &tmp_wid, &type);
    XtManageChild(tmp_wid);
    MrmFetchWidget(muid, "removePaneButton", viewMenu, &tmp_wid, &type);
    XtManageChild(tmp_wid);
    MrmFetchWidget(muid, "onePaneButton", viewMenu, &tmp_wid, &type);
    XtManageChild(tmp_wid);

    XtManageChild( mainWindow );
    XtRealizeWidget( toplevel );

      /* Locate the PanedWindow and its initial text pane */

    panedWindow = XtNameToWidget( mainWindow, "*panedWindow" );
    textFirst = XtNameToWidget( panedWindow, "*textFirst" );

    /* Updated renderTable based on Renditions menu. */
    XtVaGetValues(textFirst, XmNrenderTable, &renditions, NULL);
    renditions = TkUpdateRenditions(textFirst, renditions);

    XtVaSetValues(textFirst, XmNrenderTable, renditions, NULL);
    
    XtVaSetValues(XtNameToWidget(mainWindow, "*colorsMenu"),
		  XmNrenderTable, renditions, NULL);
    
      /* The unmanaged text widget textStore will hold onto the
         "source" shared by all the text panes */

/* $$$ comment the following code out */

    n = 0;
    XtSetArg( args[n], XmNsource, XmCSTextGetSource( textFirst ) ); n++; 
    textStore = NULL;
    MrmFetchWidgetOverride( muid, "textStore", toplevel,
                                  NULL, args, n,  &textStore, &type);

    XtRealizeWidget( textStore );

/* $$$ and replace it by

    textStore = textFirst;

    $$$ to get errors without the complication of shared sources */

      /* Instantiate FileSelectionBox widget hierarchy, but leave unmanaged */

    fileDialog = NULL;
    MrmFetchWidget( muid, "fileDialog", toplevel, &fileDialog, &type );

      /* Locate various toggle buttons placed in the FileSelectionBox,
         so that their toggle state can be set when necessary */

    openToggle = XtNameToWidget( fileDialog, "*openToggle" );
    saveToggle = XtNameToWidget( fileDialog, "*saveToggle" );
    copyToggle = XtNameToWidget( fileDialog, "*copyToggle" );
    moveToggle = XtNameToWidget( fileDialog, "*moveToggle" );

    /* Locate format menu so that it's current state can be read. */
    formatMenu = XtNameToWidget(fileDialog, "*formatMenu");
    
      /* Instantiate other dialogs, but leave unmanaged */

    saveDialog = NULL;
    warnDialog = NULL;
    questionDialog = NULL;
    MrmFetchWidget( muid, "saveDialog", toplevel, &saveDialog, &type );
    MrmFetchWidget( muid, "warnDialog", toplevel, &warnDialog, &type );
    MrmFetchWidget( muid, "questionDialog", toplevel, &questionDialog, &type );

    /* Help Dialog */
    n = 0;
    XtSetArg(args[n], XmNrenderTable, renditions); n++;
    XtSetArg(args[n], XmdNhelpFile, "texteditor"); n++;
    helpDialog = (Widget)XmdCreateHelpDialog(toplevel, "HelpDialog", args, n);
    
    /* Print Dialog */
    printDialog = XmdCreatePrintDialog(toplevel, "PrintDialog", NULL, 0);
    XtAddCallback(printDialog, XmdNprintCallback,
		  (XtCallbackProc)DlgPrintCB, NULL);

      /* Initialize the toolkit-specific layer */

    TkInit();

      /* Wait for events to trigger callbacks */

    XtAppMainLoop(app_context);
}



