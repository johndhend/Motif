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
static char rcsid[] = "$TOG: VenShellM2.c /main/6 1999/01/29 16:34:55 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */


#include <testlib.h>
#include <Xm/Xm.h>


/*  Global Variables  */

void
main(int argc, char **argv)
{

    Display            *display;
    XtAppContext       app_context;
    Widget             vshell;
    Widget             manager, label, button, scale;

    XmFontListEntry     fl_0, fl_1, fl_2;
    XmFontList          dfl, bfl, lfl;
    XmString            string;
    Cardinal    	n;
    Arg         	args[MAX_ARGS];

    /* 
       NOTE: This test specifically does not call CommonTestInit() and 
       other Common functions. Its purpose is to test the creation of
       fontList resources outside of the normal flow of automated tests.
    */

    XtToolkitInitialize();
    app_context = XtCreateApplicationContext ();
    display = XtOpenDisplay (app_context, NULL, "VenShellM2", "XMCommon",
			     NULL, 0, (int *)&argc, argv);

    if (display == NULL) {
      printf ("Couldn't open display. Exiting.\n"); exit (1);
    }
    
    /*  Load some fonts using XmFontListEntryLoad */

    fl_0 = XmFontListEntryLoad (display, "fixed", 
				XmFONT_IS_FONT, XmFONTLIST_DEFAULT_TAG);
    fl_1 = XmFontListEntryLoad (display, "6x10",
				XmFONT_IS_FONT, "button_tag");
    fl_2 = XmFontListEntryLoad (display, "8x13bold",
				XmFONT_IS_FONT, "label_tag");

    /* create the fontLists to be passed to Vendor Shell */
    /* these will be used to set up the default fonts at create time */


    dfl = XmFontListAppendEntry (NULL, fl_0);
    bfl = XmFontListAppendEntry (NULL, fl_1);
    lfl = XmFontListAppendEntry (NULL, fl_2);
    
    XmFontListEntryFree (&fl_0);
    XmFontListEntryFree (&fl_1);
    XmFontListEntryFree (&fl_2);

    n = 0;
    XtSetArg (args[n], XmNdefaultFontList, dfl); n++;
    XtSetArg (args[n], XmNbuttonFontList, bfl); n++;
    XtSetArg (args[n], XmNlabelFontList, lfl); n++;
    vshell = XtAppCreateShell ("VenShellM2", "XMcommon", 
			       applicationShellWidgetClass,
			       display,
			       args, n);

    n = 0;
    XtSetArg (args[n], XmNheight, 100); n++;
    XtSetArg (args[n], XmNwidth, 200); n++;
    manager = XmCreateBulletinBoard (vshell, "manager", args, n);

    string = XmStringCreateLtoR ("button contents", "button_tag");
    n = 0;
    XtSetArg (args[n], XmNlabelString, string); n++;
    XtSetArg (args[n], XmNx, 10); n++;
    XtSetArg (args[n], XmNy, 10); n++;
    button = XmCreatePushButton (manager, "button", args, n);

    string = XmStringCreateLtoR ("label contents", "label_tag");
    n = 0;
    XtSetArg (args[n], XmNlabelString, string); n++;
    XtSetArg (args[n], XmNx, 50); n++;
    XtSetArg (args[n], XmNy, 50); n++;
    label = XmCreateLabel (manager, "label", args, n);

    XmStringFree (string);

    /* just print instructions to standard out for this simple test. */

    printf ("If the button uses 6x10 font and the label string 8x13bold,\n");
    printf ("   then this test has passed.\n");
    fflush (stdout);

    XtManageChild (label);
    XtManageChild (button);
    XtManageChild (manager);
    XtRealizeWidget(vshell);

    XtAppMainLoop(app_context);

}
