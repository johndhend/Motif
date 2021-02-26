/* $XConsortium: PIConfig2.c /main/5 1995/07/15 21:13:57 drk $ */
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

#include <X11/Xlib.h>
#include <testlib.h>


/* test for CR 5217 */
void
main (int argc, char **argv)
{
   Display    *mydisplay;
   int        erster_aufruf=1; 
   Window     win_fix_pos, win_toggle;
   XEvent     event;
   XSizeHints hint;

   CommonTestInit (argc,argv);


   
   win_fix_pos = XCreateSimpleWindow (display, DefaultRootWindow(display),
                           50, 50, 200, 200, 0, 0, 1);

   win_toggle = XCreateSimpleWindow (display, DefaultRootWindow(display),
                           500, 500, 200, 200, 0, 0, 0);
 
   hint.flags = (USPosition | USSize | PMinSize | PMaxSize |
                 PResizeInc | PBaseSize | PAspect);

   hint.x = 50;
   hint.y = 50;
   hint.width  = 200; 
   hint.height = 200;
   hint.max_width  = 200;
   hint.max_height = 200;
   hint.min_width  = 200;
   hint.min_height = 200;
   hint.width_inc  = 1;
   hint.height_inc = 1;
   hint.base_width = hint.min_width;
   hint.base_height = hint.min_height;

   hint.min_aspect.x = hint.max_width;
   hint.min_aspect.y = hint.max_height;
   hint.max_aspect.x = hint.min_width;
   hint.max_aspect.y = hint.min_height;

   XSetStandardProperties (display, win_fix_pos, "win_fix_pos", "win_fix_pos",   None, None, None, &hint);

   hint.max_width  = 400;
   hint.max_height = 400;
   hint.x = 500;
   hint.y = 500;

   XSetStandardProperties( display, win_toggle, "win_toggle", "win_toggle",
                           None, None, None, &hint);

   XSelectInput (display, win_toggle, StructureNotifyMask);
   XMapWindow (display, win_toggle);
   XMapWindow (display, win_fix_pos);

   CommonPause();


   if (erster_aufruf == 1)
     {
       XMoveWindow (display, win_toggle, 50, 50);
       printf ("\nMove after Maximize was executed\n");
       erster_aufruf=0;
     }
    


CommonPause();

XtAppMainLoop(app_context);
}


