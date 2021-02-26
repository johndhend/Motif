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
/*   $XConsortium: ScrollWin5.h /main/7 1995/07/13 19:50:57 drk $ */
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */

#include <X11/Intrinsic.h>

Boolean   wait;
Widget    ContinuePopup = NULL;

static void            Pause();
static void            FlushEvents();
static Widget          CreateContinuePopup();
static XtCallbackProc  ResizeDrawAreaCB();
static XtCallbackProc  ContinueCB();
static XtCallbackProc  QuitCB();

static char *Pause_events[] = 
      {
      "1) A client containing a ScrolledWindow will appear. The ScrolledWindow\n\
   will contain a Form which will contain three Arrow Buttons. The Arrow\n\
   Buttons will be colored coral, violet, and yellow. The background\n\
   color of the ScrolledWindow will be AquaMarine which will apply to the\n\
   Scrollbars. The width and height of the ScrolledWindow will be 200x200.\n\
   The Coral Arrow Button will be attached to the Form on the top and the\n\
   left and will have a height of 200. The violet Arrow Button will be\n\
   attached to the Form on the top, and on the left to the coral Arrow\n\
   Button with an offset of 10. It's width will be 200. The Yellow Arrow\n\
   Button will attached to the Form on the right and on the bottom. It will\n\
   be attached on the left to the Coral Arrow Button, and on the top to the\n\
   violet Arrow Button both with offsets of 10. Its width and height will be 150.\n\
2) Continue for more testing\n",
      "1) The top and bottom offsets on the yellow Arrow Button should increase\n\
   from 10 to 25. This should cause the slider in vertical scrollbar to shrink.\n\
2) Use the horizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Continue for more testing\n",
      "1) The yellow Arrow Button should now become Unmanaged. This will cause\n\
   the Arrow Button to disappear. The Bottom of the ScrolledWindow should now\n\
   be clipped at the end of the Coral Arrow Button.\n\
2) Use the horizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Press Shift <Tab> until the highlight is in the work area with the Arrow\n\
   Buttons.\n\
4) Use the Down Arrow Key to move the highlight between the visible widgets.\n\
   You should only be able to move the highlight between the VISIBLE Buttons.\n\
5) Continue for more testing\n",
      "1) A new Arrow Button should appear. Its color will be white, and it will\n\
   be attached to the Form on the bottom, the right, and the left. It also will\n\
   be attached to the Unmanaged yellow Arrow Button on the top. All attachments\n\
   should be inforced from the Unmanaged yellow Arrow Button.\n\
2) Use the horizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Continue for more testing\n",
      "1) The yellow Arrow Button should again become Managed. This will make the\n\
   Arrow Button visible. All previous attachments should be honored. The arrow\n\
   direction of the yellow Arrow Button should have changed to XmARROW_LEFT.\n\
2) Use the horizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Continue for more testing\n",
      "1) The width and height of the ScrolledWindow should grow from 200x200\n\
   to 300x300. This will make all the Arrow Buttons visible. No Scrollbars\n\
   should be present.\n\
2) Continue for more testing\n",
      "1) The width and height of the Form should increase to 400x400. This will\n\
   cause the vertical and horizontal scrollbars to appear again. All widgets\n\
   should keep there same relative positions as before.\n\
2) Use the hoizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Continue for more testing\n",
      "1) There should be no change to the client. An attempt to change the X and\n\
   Y positions of the Form should have failed.\n\
2) Continue for more testing\n",
      "1) The width and height of the ScrolledWindow should change to 100x100.\n\
   This should cause the client to shrink and only partial amounts of the Arrow\n\
   Buttons should be visible. All widgets should keep there realtive positions\n\
   within the form.\n\
2) Use the hoizontal and vertical Scrollbars to \"Look At\" all the contents\n\
   of the Scrolled Window.\n\
3) Test Finished -- Exit Please\n"
};
	
int Pause_cnt = 0;
XtAppContext  app_context;
