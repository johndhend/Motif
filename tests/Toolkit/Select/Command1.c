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
static char rcsid[] = "$XConsortium: Command1.c /main/7 1995/07/13 19:16:34 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>

#define NITEMS 14
#define VITEMS 10

char *Istrings[] = {
    	"btest1a",
    	"decor00",
    	"decor06",
    	"func00",
    	"func05",
    	"func10",
    	"iplac00",
    	"iplac05",
    	"menu00",
    	"menu04",
    	"mtest1",
    	"parse00",
    	"prop00",
    	"rstest1"
};

Widget    Command1;

void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs, ItemList[NITEMS];
    Widget	  ChildW, Frame;

    CommonTestInit(argc, argv);

    n = 0;
    Frame = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame);

    /* Convert the items to Xm strings */

    for (n = 0; n < NITEMS; n++)
    	ItemList[n] = XmStringLtoRCreate(Istrings[n], XmSTRING_DEFAULT_CHARSET);

    tcs = XmStringLtoRCreate("Pick a Command",XmSTRING_DEFAULT_CHARSET);

    /* add them to the widget's list */
    n = 0;
    XtSetArg(args[n], XmNhistoryItems, ItemList); 			n++;
    XtSetArg(args[n], XmNhistoryItemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNhistoryVisibleItemCount, VITEMS); 		n++;
    XtSetArg(args[n], XmNlistLabelString, tcs); 			n++;
    XtSetArg(args[n], XmNforeground, CommonGetColor("white"));		n++;
    Command1 = XmCreateCommand(Frame, "Command1", args, n);
    XtManageChild(Command1);

    XmStringFree(tcs);

    /* Set up the initial command */

    tcs = XmStringLtoRCreate("ls ",XmSTRING_DEFAULT_CHARSET);
    XmCommandSetValue(Command1, tcs);
    XmStringFree(tcs);

    tcs = XmStringLtoRCreate("-l",XmSTRING_DEFAULT_CHARSET);
    XmCommandAppendValue(Command1, tcs);
    XmStringFree(tcs);


    /* use XtSetValues to change prompt */

    tcs = XmStringLtoRCreate(">>",XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNpromptString, tcs); 			n++;
    XtSetValues(Command1,args,n);
    XmStringFree(tcs);

    /* See about the children */

    ChildW = XmCommandGetChild(Command1,XmDIALOG_PROMPT_LABEL);
    printf("Prompt Label Child Name - %s\n", XtName(ChildW));

    ChildW = XmCommandGetChild(Command1,XmDIALOG_COMMAND_TEXT); 
    printf("Command Text Child Name - %s\n", XtName(ChildW));

    ChildW = XmCommandGetChild(Command1,XmDIALOG_HISTORY_LIST);
    printf("History List Child Name - %s\n", XtName(ChildW));

    fflush(stdout);

    /* add an error message to the list */

    tcs = XmStringLtoRCreate("erroror",XmSTRING_DEFAULT_CHARSET);
    XmCommandError(Command1,tcs);
    XmStringFree(tcs);

    /* realize widgets */

    XtRealizeWidget(Shell1);

    CommonPause();
    CommonPause();
    CommonPause();
    CommonPause();
    
    XtAppMainLoop(app_context);
}
