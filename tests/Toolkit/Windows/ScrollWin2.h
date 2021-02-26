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
/*   $XConsortium: ScrollWin2.h /main/7 1995/07/13 19:48:50 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
Boolean   wait;
Widget    ContinuePopup = NULL;

/*  Private Functions  */
static void            Pause();
static void            FlushEvents();
static Widget          CreateContinuePopup();
static XtCallbackProc  ContinueCB();
static XtCallbackProc  QuitCB();

static char *Pause_events[] = 
      {
	"1) A client with a scrolled window should appear. Ten and\n   a half pushbutton gadgets and pushbuttons should be visible.\n   A vertical scrollbar should appear at the left side of the client.\n2) Continue for more testing.\n",
	"1) Move the client to the top of the screen. Resize\n   the bottom of the client window down to the bottom of the screen.\n   Most or all of the following should be visible:\n      PushButtonGadget1 - PushButtonGadget6 (black foregrounds)\n      PushButton1 - PushButton8 (green foregrounds)\n      five ArrowButtonGadgets (red foregrounds)\n      five ArrowButtons (black foregrounds)\n   If all are visible, scrollbars should disappear.\n2) Continue for more testing.\n",
	"1) Resize the right edge of the client window left so that\n   widgets and gadgets are only partially visible. The\n   horizontal scrollbar should appear at the top of the client.\n2) Press and hold MB1 on the horizontal slider. Drag the slider to\n   the far right. The pushbutton gadget numbers should be visible.\n3) Resize the bottom of the client up so that some widgets and\n   gadgets are clipped. The vertical scrollbar should reappear\n   at on the left of the client.\n4) Continue for more testing.\n",
	"1) Press and hold MB1 on the vertical slider. Drag the slider \n   to the bottom. Release MB1.\n2) Press and hold MB1 on the horizontal slider. Drag the slider\n   to the middle. Release MB1. Depending on how small you resized the window,\n   some number of the green and red arrow buttons should be visible.\n3) Iconify the client. Normalize the client.\n4) Test Finished -- Exit Please"
      };
	
int Pause_cnt = 0;
XtAppContext  app_context;
