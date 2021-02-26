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
static char rcsid[] = "$XConsortium: TestInit.c /main/10 1995/07/14 11:59:29 drk $"
#endif
#endif
#include "testlib.h"
#include <sys/timeb.h>

#define  MAX_CLASS_LEN  256

XtAppContext     app_context;	/* Global Application Context */
Display          *display;	/* Global Display variable */
Widget           Shell1;	/* Global TopLevel Application Shell */
Window		 rootWindow;	/* Global Toplevel Root Window */
Screen		 * screen;	/* Global TopLevel screen */

/* extern varaibles from CommonExtraResources */

extern Arg       CommonExtraArgs[MAX_ARGS];
extern Cardinal  CommonExtraN;
extern char		*CompleteTestName;

/* extern variable from CommonGetOptions */
extern Boolean   startup_time;
extern void  CommonGetTime();

char CommonAppClass[MAX_CLASS_LEN] = "XMcommon";

/* forward declarations */

static void             ManualSignalQuit();
static void 		ManualRegressionSignal();


/*************************************************************************
*                                                                        *
*       Name:           CommonTestInit()                                 *
*								 	 *
*	Purpose:	This routine will Initialize Xt, create a app    *
*			context, create a connnection to the display     *
*			and create an toplevel application shell. Shell1 *
*			and display are global variable and will be used *
*			in other routines.				 *
*									 *
*	Return:		Nothing						 *
*									 *
*************************************************************************/

void CommonTestInit(int argc, char **argv)

{
     int 	n, i;
     Arg 	args[MAX_ARGS];

#ifdef REGRESSION
     signal(SIGHUP,  ManualRegressionSignal);
     signal(SIGINT,  ManualRegressionSignal);
     signal(SIGQUIT, ManualRegressionSignal);
     signal(SIGKILL, ManualRegressionSignal);
     signal(SIGBUS,  ManualRegressionSignal);
     signal(SIGSEGV, ManualRegressionSignal);

     /* the following was suggested to handle cases where
	user exits via Mwm Close, but it loops infinitely.
	Fix some day. */

     /* atexit (ManualRegressionSignal); */
	
	/* open output file; if impossible, use stdout */

	output_file = fopen ("RUN_output", "a");
	if (output_file == NULL) {
		printf ("Error opening output file.\n");
		output_file = stdout;
	}

#else
     signal(SIGHUP,  ManualSignalQuit);
     signal(SIGINT,  ManualSignalQuit);
     signal(SIGQUIT, ManualSignalQuit);
     signal(SIGKILL, ManualSignalQuit);
     signal(SIGBUS,  ManualSignalQuit);
     signal(SIGSEGV, ManualSignalQuit);

     /* atexit (ManualSignalQuit); */

#endif


     n = 0;

     /*
        merge in Extra arguments in the args list for the creation
        of the application shell. Args are set by CommonExtraResources().

        Special Case: If the CommonExtraArgs[i].name is "CommonAppClass"
        then we want to change the name of the ApplicationClass and we
        will extract that value from CommonExtraArgs[i].value

     */

     if (CommonExtraN > 0) {
        for (i = 0 ; i < CommonExtraN; i++) {
                if (strcmp(CommonExtraArgs[i].name, "CommonAppClass") == 0)
                        strcpy(CommonAppClass, 
 			       (char *) CommonExtraArgs[i].value);
                else {
                        args[n].name = CommonExtraArgs[i].name;
                        args[n++].value = CommonExtraArgs[i].value;
                }
        }
     }

     /*
      *  Initialize malloc checking.  Note: a side effect of this
      *  is that the above signals will be redefined to call 
      *  MallocExit.
     */

     MallocInit();

     CommonGetOptions(&argc, argv);

     if (startup_time)
	 CommonGetTime();

     XtToolkitInitialize();
     app_context = XtCreateApplicationContext();

     display = XtOpenDisplay(app_context, NULL, argv[0], CommonAppClass,
     				NULL, 0, &argc, argv);
     if (display == NULL) {
      	  fprintf(stderr, "%s:  Can't open display\n", argv[0]);
       	  exit(1);
     }

     rootWindow = XDefaultRootWindow(display);
	
     XtSetArg(args[n], XmNallowShellResize, True);  	n++;
     Shell1 = XtAppCreateShell(argv[0], CommonAppClass, 
		          applicationShellWidgetClass, display, args, n);

     screen = XtScreen(Shell1);

}

/*************************************************************************
*                                                                        *
*       Name:           CommonTestI18NInit()                             *
*								 	 *
*	Purpose:	This routine will Initialize Xt, create an       *
*                       application context, register the language       *
*                       procedure called to set the locale, create a     *
*			connnection to the display and create a          *
*			toplevel application shell.                      *
*			Shell1 and display are global variable and will  *
*                       be used in other routines.			 *
*									 *
*	Return:		Nothing						 *
*									 *
*************************************************************************/

void CommonTestI18NInit(int argc, char **argv, XtLanguageProc proc, 
			XtPointer client_data) 

{
     int 	n, i;
     Arg 	args[MAX_ARGS];

#ifdef REGRESSION
     signal(SIGHUP,  ManualRegressionSignal);
     signal(SIGINT,  ManualRegressionSignal);
     signal(SIGQUIT, ManualRegressionSignal);
     signal(SIGKILL, ManualRegressionSignal);
     signal(SIGBUS,  ManualRegressionSignal);
     signal(SIGSEGV, ManualRegressionSignal);

     /* the following was suggested to handle cases where
	user exits via Mwm Close, but it loops infinitely.
	Fix some day. */

     /* atexit (ManualRegressionSignal); */
	
	/* open output file; if impossible, use stdout */

	output_file = fopen ("RUN_output", "a");
	if (output_file == NULL) {
		printf ("Error opening output file.\n");
		output_file = stdout;
	}

#else
     signal(SIGHUP,  ManualSignalQuit);
     signal(SIGINT,  ManualSignalQuit);
     signal(SIGQUIT, ManualSignalQuit);
     signal(SIGKILL, ManualSignalQuit);
     signal(SIGBUS,  ManualSignalQuit);
     signal(SIGSEGV, ManualSignalQuit);

     /* atexit (ManualSignalQuit); */

#endif


     n = 0;

     /*
        merge in Extra arguments in the args list for the creation
        of the application shell. Args are set by CommonExtraResources().

        Special Case: If the CommonExtraArgs[i].name is "CommonAppClass"
        then we want to change the name of the ApplicationClass and we
        will extract that value from CommonExtraArgs[i].value

     */

     if (CommonExtraN > 0) {
        for (i = 0 ; i < CommonExtraN; i++) {
                if (strcmp(CommonExtraArgs[i].name, "CommonAppClass") == 0)
                        strcpy(CommonAppClass, 
 			       (char *) CommonExtraArgs[i].value);
                else {
                        args[n].name = CommonExtraArgs[i].name;
                        args[n++].value = CommonExtraArgs[i].value;
                }
        }
     }

     /*
      *  Initialize malloc checking.  Note: a side effect of this
      *  is that the above signals will be redefined to call 
      *  MallocExit.
     */

     MallocInit();

     XtToolkitInitialize();
     app_context = XtCreateApplicationContext();
     
     /*
      * Register the language procedure called to set the locale.
      */

     XtSetLanguageProc(NULL, proc, client_data);

     display = XtOpenDisplay(app_context, NULL, argv[0], CommonAppClass,
     				NULL, 0, &argc, argv);
     if (display == NULL) {
      	  fprintf(stderr, "%s:  Can't open display\n", argv[0]);
       	  exit(1);
     }

     CommonGetOptions(&argc, argv);

     rootWindow = XDefaultRootWindow(display);
	
     XtSetArg(args[n], XmNallowShellResize, True);  	n++;
     Shell1 = XtAppCreateShell(argv[0], CommonAppClass, 
		          applicationShellWidgetClass, display, args, n);

     screen = XtScreen(Shell1);

}
	
static void  ManualSignalQuit(sig, code, scp)
int sig, code;
struct sigcontext *scp;
{
     char sigstring[256];

     switch (sig) {
	case SIGHUP:	strcpy(sigstring, "hangup");
			break;
	case SIGINT:	strcpy(sigstring, "interrupt");
			break;
	case SIGQUIT:	strcpy(sigstring, "quit");
			break;
	case SIGKILL:	strcpy(sigstring, "kill");
			break;
	case SIGSEGV:	strcpy(sigstring, "segmentation violation");
			break;
	case SIGBUS:	strcpy(sigstring, "bus error");
			break;
	default:	strcpy(sigstring, "undetermined");
			break;
     }
     printf("%s signal received: Begin exiting ... please standby ... \n",
	    sigstring);

     fflush(stdout);

     exit(0);
}

static void  ManualRegressionSignal(sig, code, scp)
int sig, code;
struct sigcontext *scp;
{
     char sigstring[256];

     switch (sig) {
	case SIGHUP:	strcpy(sigstring, "hangup");
			break;
	case SIGINT:	strcpy(sigstring, "interrupt");
			break;
	case SIGQUIT:	strcpy(sigstring, "quit");
			break;
	case SIGKILL:	strcpy(sigstring, "kill");
			break;
	case SIGSEGV:	strcpy(sigstring, "segmentation violation");
			break;
	case SIGBUS:	strcpy(sigstring, "bus error");
			break;
	default:	strcpy(sigstring, "undetermined");
			break;
     }

     printf("WARNING: %s signal received from test %s\n            Begin exiting ... please standby ... \n", sigstring, TestName);

     /* flush stdout */

     fflush(stdout);

     fprintf(output_file, "WARNING: %s signal received from test %s\n            Begin exiting ... please standby ... \n", sigstring, CompleteTestName);

     /* flush output_file */

     fflush(output_file);

     /* even on an interrupt, write out summary */

     if (InstructionBox != NULL) 
     	XtCallCallbacks (XmMessageBoxGetChild(InstructionBox,
                                              XmDIALOG_CANCEL_BUTTON),
                         XmNactivateCallback, NULL);
     else
	exit(0);

}


