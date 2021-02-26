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
static char rcsid[] = "$XConsortium: Command2.c /main/8 1995/07/13 19:16:48 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>

static XmString	stringList[15];
static int	enter_count = 0,
		change_count = 0;

static void EnterCB();
static XtCallbackRec enter_cb[] = {
    {  EnterCB, NULL},
    { NULL, NULL},
};

static void EnterCB (w, client_data, call_data)
     Widget	w;
     caddr_t	client_data;
     caddr_t	call_data;
{
    static XmString	str = NULL,
    			str2 = NULL,
    			badString = NULL;

    Arg			al[10];                  /*  arg list             */
    register int	ac;                      /*  arg count            */
    Widget		noChild;

    if(str == NULL)
    {
	str = XmStringLtoRCreate("setValue", XmSTRING_DEFAULT_CHARSET);
    }
    
    if(str2 == NULL)
    {
	str2 = XmStringLtoRCreate("errorValue", XmSTRING_DEFAULT_CHARSET);
    }

    if(badString == NULL)
    {
	badString = XmStringDirectionCreate(XmSTRING_DIRECTION_R_TO_L);
    }

    switch(enter_count)
    {
      case 0:

        ac = 0;
        XtSetArg (al[ac], XmNmustMatch, True);                    ac++;
        XtSetArg (al[ac], XmNdialogType, XmDIALOG_ERROR);         ac++;
        XtSetArg (al[ac], XmNhistoryMaxItems, -1);                ac++;
        XtSetValues (w, al, ac);
	break;

      case 1:
	
        noChild = XmCommandGetChild(w, XmDIALOG_OK_BUTTON);
	break;

      case 2:

        XmCommandSetValue (w, NULL);
        XmCommandSetValue (w, badString);
	break;

      case 3:

        XmCommandError (w, NULL); 
        XmCommandError (w, badString); 
	change_count = 1;
	break;
    }

    enter_count++;
}


static void ChangeCB();
static XtCallbackRec change_cb[] = {
    {  ChangeCB, NULL},
    { NULL, NULL},
};

static void ChangeCB (w, client_data, call_data)
     Widget	w;
     caddr_t	client_data;
     caddr_t	call_data;
{
    static		i = 0;
    static XmString	str = NULL,
    			badStr = NULL;

    if (str == NULL) 
        str = XmStringLtoRCreate("addValue", XmSTRING_DEFAULT_CHARSET);

    if (badStr == NULL)
        badStr = XmStringDirectionCreate(XmSTRING_DIRECTION_L_TO_R);

    if(change_count)
    {
        XmCommandAppendValue (w, NULL);
        XmCommandAppendValue (w, badStr);
    }
    i++;
}


void main (argc,argv)
int argc;
char **argv;
{
    Widget        command;                 /*  Command widget       */
    Arg           args[10];                /*  arg list             */
    register int  n;                       /*  arg count            */
    Widget        unManageList[5];
    XmString      stringList[15];
    XmString      commandString;
    Widget	  Frame;


    /*  initialize toolkit  */
    CommonTestInit(argc, argv);

    n = 0;
    Frame = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame);

/* 
 * set up XmStrings for list
 */

    stringList[0] = XmStringLtoRCreate ("one", XmSTRING_DEFAULT_CHARSET);
    stringList[1] = XmStringLtoRCreate ("two", XmSTRING_DEFAULT_CHARSET);
    stringList[2] = XmStringLtoRCreate ("three", XmSTRING_DEFAULT_CHARSET);
    stringList[3] = XmStringLtoRCreate ("four", XmSTRING_DEFAULT_CHARSET);
    stringList[4] = XmStringLtoRCreate ("five", XmSTRING_DEFAULT_CHARSET);
    stringList[5] = XmStringLtoRCreate ("six", XmSTRING_DEFAULT_CHARSET);
    stringList[6] = NULL;

    commandString = XmStringLtoRCreate ("next", XmSTRING_DEFAULT_CHARSET);

/*
 * create Command
 */

    n = 0;
    XtSetArg (args[n], XmNcommand, commandString);             n++;
    XtSetArg (args[n], XmNhistoryItems, stringList);           n++;
    XtSetArg (args[n], XmNhistoryItemCount, 6);                n++;
    XtSetArg (args[n], XmNcommandEnteredCallback, enter_cb);   n++;
    XtSetArg (args[n], XmNcommandChangedCallback, change_cb);  n++;

    command = XmCreateCommand(Frame, "command", args, n);
    XtManageChild (command);

/*
 * realize widgets
 */

    XtRealizeWidget (Shell1);

/*
 * CommonPauses for message boxes
 */

    CommonPause();
    CommonPause();

/*
 * process events
 */

    XtAppMainLoop(app_context);
}
