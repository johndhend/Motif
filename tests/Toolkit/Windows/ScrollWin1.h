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
/*   $XConsortium: ScrollWin1.h /main/7 1995/07/13 19:48:11 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
Boolean   wait;
Widget    ContinuePopup = NULL;

static void            Pause();
static void            FlushEvents();
static Widget          CreateContinuePopup();
static XtCallbackProc  ContinueCB();
static XtCallbackProc  QuitCB();

static char *Pause_events[] = 
      {
	"1) A empty client will appear. This window is a ScrolledWindow\n   without setting the work window.\n2) Continue to set a work window.\n",
	"1) A client window containing a scrolled window with pushbuttons\n   should appear. Ten of the fifteen pushbuttons should be visible.\n   A vertical scrollbar should appear at the right side of the client.\n2) Continue for more testing.\n",
	"1) Push some pushbuttons and scroll up and down.\n2) Resize the bottom of the client window down to expose all\n   fifteen pushbuttons. The vertical scrollbar should disappear.\n3) Resize the right edge of the client left so that the pushbuttons\n   are only partially visible. A horizontal scrollbar should appear at\n   the bottom of the client window.\n4) Press MB1 on the horizontal slider. Drag the slider to the far right.\n   The pushbutton numbers should be visible.\n5) Continue for more testing.\n",
	"1) Resize bottom of the client up so that some pushbuttons\n   are clipped. The vertical scrollbar should reappear at the right\n   side of the the client window.\n2) Press and hold MB1 on the horizontal slider. Drag the slider to the\n   far right. The pushbutton numbers should be visible.\n   Release MB1.\n3) Press and hold MB1 on the vertical slider. Drag the slider to the bottom.\n   The last pushbutton numbers through 15 should be visible.\n   Release MB1.\n4) Test Finished -- Exit Please"
      };
	
int Pause_cnt = 0;
XtAppContext  app_context;
