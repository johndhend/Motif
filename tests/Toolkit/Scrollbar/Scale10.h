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
/*   $XConsortium: Scale10.h /main/6 1995/07/13 19:11:16 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
Boolean   wait;
Widget    ContinuePopup = NULL;

/*  Private Functions  */
static void            Pause();
static void            FlushEvents();
static void 	       Quit();
static Widget          CreateContinuePopup();
static XtCallbackProc  ContinueCB();
static XtCallbackProc  QuitCB();

static char *Pause_events[] = 
   {
"\
1) A client with two Scales and four PushButtons contained\n\
   in a Bulletin Board should appear.  The horizontal scale\n\
   is 375 pixels wide and 30 pixels high and has an initial\n\
   value of 44.  The vertical scale is 30 pixels wide and 375\n\
   pixels high and has an initial value of 66.\n\
2) Throughout all of the following operations, the value label\n\
   for each scale widget should remain directly above (horizontal\n\
   scale) or to the left (vertical scale) of the slider.\n\
3) Click MB1 in the PushButton labeled \"Horiz scaleHeight to 50\".\n\
   The horizontal scale should grow to a scaleHeight of 50.\n\
4) Click MB1 in the PushButton labeled \"Vert scaleHeight to 50\".\n\
   The vertical scale should shrink to a scaleHeight of 50.\n\
5) Click MB1 in the PushButton labeled \"Horiz scaleWidth to 50\".\n\
   The horizontal scale should shrink to a scaleWidth of 50.\n\
6) Click MB1 in the PushButton labeled \"Vert scaleWidth to 50\".\n\
   The vertical scale should grow to a scaleWidth of 50.\n\
7) Move the horizontal scale slider several times and look at the\n\
   values printed in the stdout window.  The old and new values\n\
   should reflect the direction and amount of movement.\n\
8) Click MB1 on the slider of the horizontal scale without\n\
   moving it.  The old and new values printed should be the same.\n\
9) Test Finished -- Exit Please"
   };

int Pause_cnt = 0;
XtAppContext  app_context;
