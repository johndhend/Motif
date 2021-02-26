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
/*   $XConsortium: Protocol.h /main/6 1995/07/13 19:20:52 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define MAX_ARGS	100

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
	"1) A client with a menubar containing three entries will appear.\n   The entries will be labeled 'short menu', 'long menu' and\n   'no menu'.\n2) Click MB1 on 'short menu'.\n3) Select the window menu.  It should contain an additional entry,\n   'entry_1'.\n4) Choose 'entry_1' from the window menu.  The message \"entry 1\n   selected\" will be displayed in the xterm window.\n5) Click MB1 on 'short menu' again.\n6) Choose 'entry_1' from the window menu.  Nothing will be displayed\n   in the xterm window.\n7) Press the Continue button.\n",
         "1) Click MB1 on 'long menu'.  Two more entries, 'entry_2' and\n   'entry_3', will be added to the window menu.\n2) Choose 'entry_2' from the window menu.  The message \"entry 2\n   selected\" will be displayed in the xterm window.\n3) Choose 'entry_3' from the window menu.  The message \"entry 3\n   selected\" will be displayed in the xterm window.\n4) Click MB1 on 'long menu' again.  The three added entries in\n   the window menu will be deactivated (no longer boldface.)\n5) Click MB1 on 'long menu' again.  The three added entries in\n   the window menu will be reactivated (boldface.)\n6) Press the Continue button.\n",
         "1) Click MB1 on 'no menu'.  The three added entries in the window\n   menu will disappear.\n2) Test Finished -- Exit Please",
      };

int Pause_cnt = 0;
XtAppContext  app_context;
