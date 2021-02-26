/* $XConsortium: RIMainWin1.c /main/4 1995/07/15 21:08:55 drk $ */
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

#include <testlib.h>

Widget    MainWindow; 
Widget    MenuBar;
Widget	  Pulldown1, Pulldown2, Pulldown3;
Widget    MenuBtn1, MenuBtn2, MenuBtn3;
Widget    CommandWindow, WorkRegion; 
Widget    Button;
Widget    Separator;
Widget    VScrollBar, HScrollBar;
Widget	  CommandText;


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    register int  i;

    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg(args[n], XmNwidth,  400);  n++;
    XtSetArg(args[n], XmNheight, 300);  n++;
    XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
    XtSetValues(Shell1, args, n);
    

    n = 0;
    XtSetArg(args[n], XmNunitType, Xm1000TH_INCHES);  n++;
    XtSetArg(args[n], XmNmainWindowMarginHeight, 100);  n++;
    XtSetArg(args[n], XmNmainWindowMarginWidth, 100);  n++;
    XtSetArg(args[n], XmNshowSeparator, True);  n++;
    MainWindow = XmCreateMainWindow(Shell1, "MainWindow", args, n);
    XtManageChild(MainWindow);

    /*
    **  the menubar
    */
    n = 0;
    MenuBar = XmCreateMenuBar (MainWindow, "MenuBar", args, n);
    XtManageChild(MenuBar);

    /*  create the first level pulldowns */
    n = 0;
    Pulldown1 = XmCreatePulldownMenu (MenuBar, "Pulldown1", args, n);

    n = 0;
    Pulldown2 = XmCreatePulldownMenu (MenuBar, "Pulldown2", args, n);

    n = 0;
    XtSetArg(args[n], XmNradioBehavior, True);  n++;
    XtSetArg(args[n], XmNradioAlwaysOne, True);  n++;
    Pulldown3 = XmCreatePulldownMenu (MenuBar, "Pulldown3", args, n);

    /*  create cascade buttons for menubar  */
    n = 0;
    tcs = XmStringLtoRCreate("File", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNsubMenuId, Pulldown1);  n++;
    MenuBtn1 = XmCreateCascadeButton(MenuBar, "MenuBtn1", args, n);
    XtManageChild(MenuBtn1);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Edit", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNsubMenuId, Pulldown2);  n++;
    MenuBtn2 = XmCreateCascadeButton(MenuBar, "MenuBtn2", args, n);
    XtManageChild(MenuBtn2);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Font", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNsubMenuId, Pulldown3);  n++;
    MenuBtn3 = XmCreateCascadeButton(MenuBar, "MenuBtn3", args, n);
    XtManageChild(MenuBtn3);
    XmStringFree(tcs);

    /*
    **  Menu1
    */
    n = 0;
    tcs = XmStringLtoRCreate("New", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButton(Pulldown1, "NewButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Open...", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButton(Pulldown1, "OpenButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    Separator = XmCreateSeparator(Pulldown1, "Separator", args, n);
    XtManageChild(Separator);

    n = 0;
    tcs = XmStringLtoRCreate("Save", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButton(Pulldown1, "SaveButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    /*
    **  Menu2
    */
    n = 0;
    tcs = XmStringLtoRCreate("Cut", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButtonGadget(Pulldown2, "CutButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Copy", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButtonGadget(Pulldown2, "CopyButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Paste", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButtonGadget(Pulldown2, "PasteButton",
                                           args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    Separator = XmCreateSeparator(Pulldown2, "Separator", args, n);
    XtManageChild(Separator);

    n = 0;
    tcs = XmStringLtoRCreate("Undo", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    Button = XmCreatePushButtonGadget(Pulldown2, "UndoButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    /*
    **  Menu3
    */
    /* Convert the items to Xm strings */
    n = 0;
    tcs = XmStringLtoRCreate("Courier", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNvisibleWhenOff, False);  n++;
    XtSetArg(args[n], XmNset, True);  n++;
    Button = XmCreateToggleButtonGadget(Pulldown3, "CourierButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Times", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNvisibleWhenOff, False);  n++;
    Button = XmCreateToggleButton(Pulldown3, "TimesButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Helvetica", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNvisibleWhenOff, False);  n++;
    Button = XmCreateToggleButtonGadget(Pulldown3, "HelveticaButton", args,
                                        n);
    XtManageChild(Button);
    XmStringFree(tcs);

    n = 0;
    tcs = XmStringLtoRCreate("Geneva", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);  n++;
    XtSetArg(args[n], XmNvisibleWhenOff, False);  n++;
    Button = XmCreateToggleButton(Pulldown3, "GenevaButton", args, n);
    XtManageChild(Button);
    XmStringFree(tcs);

    /* create the command window */
    n = 0;
    CommandWindow = XmCreateCommand(MainWindow, "Command", args, n);
    XtManageChild(CommandWindow);

    CommandText = XmCommandGetChild(CommandWindow,XmDIALOG_COMMAND_TEXT);
    XtSetArg(args[0], XmNblinkRate, 0);
    XtSetValues(CommandText, args, 1);

    /* create the work region */
    n = 0;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);			n++;
    XtSetArg(args[n], XmNnumColumns, 6);				n++;
    WorkRegion = XmCreateRowColumn(MainWindow, "RowCol", args, n);
    XtManageChild(WorkRegion);

    for (i = 0; i < 10; i++) {
        char    label_string[20];

        n = 0;
        sprintf(label_string, "Push%02d", i);
        tcs = XmStringLtoRCreate(label_string, XmSTRING_DEFAULT_CHARSET);
        XtSetArg(args[n], XmNlabelString, tcs);  n++;
        Button = XmCreatePushButton(WorkRegion, label_string, args, n);
        XtManageChild(Button);
        XmStringFree(tcs);

        n = 0;
        sprintf(label_string, "PushGadget%02d", i);
        tcs = XmStringLtoRCreate(label_string, XmSTRING_DEFAULT_CHARSET);
        XtSetArg(args[n], XmNlabelString, tcs);  n++;
        Button = XmCreatePushButtonGadget(WorkRegion, label_string, args, n);
        XtManageChild(Button);
        XmStringFree(tcs);
    }

    XmMainWindowSetAreas(MainWindow, MenuBar, CommandWindow, NULL, NULL,
                         WorkRegion);

    XtRealizeWidget(Shell1);


    CommonPause();

    CommonPause();

    n = 0;
    VScrollBar = XmCreateScrollBar(MainWindow, "ScrollBar", args, n);
    XtManageChild(VScrollBar);

    n = 0;
    XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
    HScrollBar = XmCreateScrollBar(MainWindow, "ScrollBar", args, n);
    XtManageChild(HScrollBar);

    XmMainWindowSetAreas(MainWindow, MenuBar, CommandWindow,
                         HScrollBar, VScrollBar, WorkRegion);

    CommonPause();

    Separator = XmMainWindowSep1(MainWindow);
    n = 0;
    XtSetArg(args[n], XmNseparatorType, XmDOUBLE_LINE);  n++;
    XtSetValues(Separator, args, n);

    Separator = XmMainWindowSep2(MainWindow);
    n = 0;
    XtSetArg(args[n], XmNseparatorType, XmSINGLE_LINE);  n++;
    XtSetValues(Separator, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, XmPIXELS);  n++;
    XtSetArg(args[n], XmNmainWindowMarginHeight, 50);  n++;
    XtSetArg(args[n], XmNmainWindowMarginWidth, 50);  n++;
    XtSetValues(MainWindow, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);  n++;
    XtSetValues(MainWindow, args, n);

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNmainWindowMarginHeight, 100);  n++;
    XtSetArg(args[n], XmNmainWindowMarginWidth, 100);  n++;
    XtSetValues(MainWindow, args, n);

    CommonPause();

    /*
    **  hit error conditions
    */
    n = 0;
    XtSetArg(args[n], XmNmenuBar, NULL);  n++;
    XtSetArg(args[n], XmNcommandWindow, NULL);  n++;
    XtSetValues(MainWindow, args, n);

    CommonPause();

    XtDestroyWidget(MainWindow);

    
    CommonPause();

    XtAppMainLoop(app_context);
}
