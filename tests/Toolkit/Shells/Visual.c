/* $XConsortium: Visual.c /main/5 1995/07/15 21:09:39 drk $ */
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

/* Test created to check the setting of the resource XmNvisual in the Shell
   widget
*/

#include <testlib.h>
#include <string.h>

void
doit()
{
    Screen * screen;
    XrmValue args[10];
    Cardinal num_args = 0;
    Boolean result;
    static char string[100];
    static char * visual_class[] = { "StaticGray",
			      "StaticColor",
			      "TrueColor",
			      "GrayScale",
			      "PseudoColor",
			      "DirectColor" };
    int visual_found[6];
    int i = 0;
    static Visual * visual[6];
    Display * display;
    XrmValue fromVal;
    XrmValue toVal;
    Arg shell_args[10];
    Cardinal num_shell_args = 0;
    Visual * ret_visual;
    int depth;
    int size;
    char buf[512];
    char tmp[256];

    screen = XtScreen(Shell1);
    display = DisplayOfScreen(screen);
    depth = DefaultDepthOfScreen(screen);
    args[0].addr = (XPointer) &screen;
    args[0].size = sizeof(Screen *);
    num_args++;
    args[1].addr = (XPointer) &depth;
    args[1].size = sizeof(int);
    num_args++;
    sprintf(buf, 
	    "\nVisual Class\tVisual Found\n------------\t------------\n\n");
    for (i = 0; i < 6; i++) {
	strcpy(string, XrmQuarkToString(XrmStringToQuark(visual_class[i])));
	size = strlen((char *)string);
	fromVal.addr = (XPointer)string;
	fromVal.size = sizeof(size);
	toVal.addr = (XPointer) &visual[i];
	toVal.size = sizeof(Visual);
	result = XtCallConverter(display, XtCvtStringToVisual, args, num_args,
				 &fromVal, &toVal, NULL);
	if (result == False) {
	    sprintf(tmp, "%s\tNo\n", visual_class[i]);
	    strcat(buf, tmp);
	    visual_found[i] = False;
	}
	else {
	    sprintf(tmp, "%s\tYes\n", visual_class[i]);
	    strcat(buf, tmp);
	    visual_found[i] = True;
	}
    }
    printf("%s\n", buf);
    for (i = 0; i < 6 ; i++) {
	if (!visual_found[i])
	    continue;
	num_shell_args = 0;
	printf("For visual class %s...\n\n", visual_class[i]);
	XtSetArg(shell_args[0], XmNvisual, &ret_visual); num_shell_args++;
	XtGetValues(Shell1, shell_args, num_shell_args);
	printf("original visual: %x\n", ret_visual);
	printf("replacement visual: %x\n", visual[i]);
	num_shell_args = 0;
	XtSetArg(shell_args[0], XmNvisual, visual[i]); num_shell_args++;
	XtSetValues(Shell1, shell_args, num_shell_args);
	num_shell_args = 0;
	XtSetArg(shell_args[0], XmNvisual, &ret_visual); num_shell_args++;
	XtGetValues(Shell1, shell_args, num_shell_args);
	if (visual[i] != ret_visual) {
	    printf("Error. Incorrect visual value returned. Visual class: %s\n\n",
		   visual_class[i]);
	}
	else {
	    printf("Visual successfully modified\n\n");
	}
    }

  }

void
main (int argc, char **argv)
{

  Arg args[10];
  int n;

  CommonTestInit (argc,argv);

  n=0;
  XtSetArg (args[n], XmNiconName, "TESTING"); n++;
  XtSetArg (args[n], XmNwidth,100); n++;
  XtSetArg (args[n], XmNheight,100); n++;
  XtSetValues (Shell1, args, n);

  XtRealizeWidget (Shell1);

  CommonPause();
  
  doit();

  CommonPause();
  CommonPause();

  XtAppMainLoop (app_context);

}







