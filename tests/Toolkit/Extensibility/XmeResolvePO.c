/* $XConsortium: XmeResolvePO.c /main/5 1995/07/15 21:05:13 drk $ */
/*
 *  @OPENGROUP_COPYRIGHT@
 *  COPYRIGHT NOTICE
 *  Copyright (c) 1993 Open Software Foundation, Inc.
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

/*  Standard C headers  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* QATS headers */
#include <testlib.h>

/*  X headers  */
#include <X11/IntrinsicP.h>

/*  Xm headers  */
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/JoinSideT.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/CascadeBG.h>

/*  Exm headers  */
#include <Exm/CommandB.h>
#include <Exm/Simple.h>
/* String.h changed? */
#include <Exm/StringTrans.h>
#include <Exm/TabB.h>

void
DoQuit(Widget w, XtPointer ignore, XtPointer cbstruct)
{
  exit(0);
}


int 
main (int argc, char **argv)
{
  register int       n;
  Arg                args[MAX_ARGS];
  Display	     *display;
  Widget       	     tab_button, mainWindow;
  XtEnum	     open_side;
  

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  mainWindow = XtVaCreateManagedWidget("myMainWindow",
				       xmMainWindowWidgetClass, Shell1,
				       NULL);

  /* Instantiate an ExmTabButton widget. */
  tab_button = XtVaCreateManagedWidget("tabButton", exmTabButtonWidgetClass,
				   mainWindow,
				   XmNheight, 100,
				   XmNwidth, 140,
				   XmNshadowThickness, 15,
				   NULL);
  n = 0;
  XtSetArg(args[n], ExmNopenSide, &open_side);  n++;
  XtGetValues(tab_button, args, n);

  if (open_side != XmLEFT)
      printf("ERROR: open_side default is incorrect\n");
  CommonPause();

  /* Set the the open side resource and test that it works */
  n = 0;
  XtSetArg(args[n], ExmNopenSide, XmTOP);  n++;
  XtSetValues(tab_button, args, n);

  n = 0;
  XtSetArg(args[n], ExmNopenSide, &open_side);  n++;
  XtGetValues(tab_button, args, n);

  if (open_side != XmTOP)
      printf("ERROR: open_side resource has not been set properly\n");
  CommonPause();

  /* Reset the the open side resource and retest it */
  n = 0;
  XtSetArg(args[n], ExmNopenSide, XmRIGHT);  n++;
  XtSetValues(tab_button, args, n);

  n = 0;
  XtSetArg(args[n], ExmNopenSide, &open_side);  n++;
  XtGetValues(tab_button, args, n);

  if (open_side != XmRIGHT)
      printf("ERROR: open_side resource has not been set properly\n");
  CommonPause();

  CommonPause(); /* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Shell1);
}
