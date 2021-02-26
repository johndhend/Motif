/* $XConsortium: RIArrowBGad5.c /main/4 1995/07/15 21:08:17 drk $ */
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
/*
 *  Create a drawing area with an arrow gadget within it.
 *  Initialize it with some invalid data.
 *  SetValues for the unit type, and x and y.
 */

#include <signal.h>
#include <X11/StringDefs.h>
#include <testlib.h>


Boolean	show_geom_bug;				/*PIR4250*/

void Destroy();

void main (argc, argv)
int argc;
char **argv;

{
  Widget drawarea;
  Widget arrow;
  Arg args[10];
  int n;

  show_geom_bug = False;				/*PIR4250*/

  CommonTestInit(argc, argv);

  if (UserData != NULL)
    ProcessCommandArgs();
    
  n = 0;
  XtSetArg (args[n], XmNwidth, 400);	n++;
  XtSetArg (args[n], XmNheight, 400);	n++;
  XtSetArg (args[n], XmNallowShellResize, False);	n++; 
  XtSetValues (Shell1, args, n);

  if (show_geom_bug == True)				/*PIR4250*/
    XtRealizeWidget (Shell1);

  /*  The drawing area creation.  Contained in an outer frame.  */
  n = 0;
  XtSetArg (args[n], XmNwidth, 400);	n++;
  XtSetArg (args[n], XmNheight, 400);	n++;
  drawarea = XmCreateDrawingArea (Shell1, "drawarea", args, n);

  if (show_geom_bug == True)				/*PIR4250*/
    XtRealizeWidget (drawarea);
  XtManageChild (drawarea);

  /*  Create the arrow */

  n = 0;
  XtSetArg (args[n], XmNx, 40);	n++;
  XtSetArg (args[n], XmNy, 40);	n++;
  XtSetArg (args[n], XmNunitType, 18);			n++;
  arrow = XmCreateArrowButtonGadget (drawarea, "arrow", args, n);

  if (show_geom_bug == True)				/*PIR4250*/
    XtRealizeWidget (arrow);
  XtManageChild (arrow);
  XtAddCallback (arrow, XmNactivateCallback, Destroy, NULL);

  n = 0;
  XtSetArg (args[n], XmNx, 100);			n++;
  XtSetArg (args[n], XmNy, 250);			n++;
  XtSetArg (args[n], XmNunitType, Xm1000TH_INCHES);	n++;
  XtSetValues (arrow, args, n);

  XtRealizeWidget (Shell1);
  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(drawarea);
}

void Destroy (w, client_data, call_data)
Widget w;
caddr_t client_data;
caddr_t call_data;

{
   XtDestroyWidget (w);
}


#define	WORD_LEN	32

ProcessCommandArgs()
{

	char	*user_data;
	char	next_word[WORD_LEN + 1];
	int     num_spaces;

	user_data = UserData;

	while (*user_data != '\0') {

		get_next_word(user_data, next_word, &num_spaces);
		user_data += (strlen(next_word) + num_spaces);

		if (strcmp(next_word, "-show_geom_bug") == 0) {

			show_geom_bug = True;
			user_data += (strlen(next_word) + num_spaces);
			continue;

		}

	}

	free(UserData);

}


get_next_word(source, dest, spaces)
char	*source;
char	*dest;
int		*spaces;
{

	int	n;
	int	space_count;

	space_count = 0;

	while (isspace(*source)) {
		source++;
		space_count++;
	}

	n = 0;
	while (!isspace(*source) && *source != '\0' && n < WORD_LEN) {
		*dest++ = *source++;
		n++;
	}
	*dest = '\0';
	*spaces = space_count;

}
