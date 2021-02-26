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
/*   $XConsortium: Scale5.h /main/6 1995/07/13 19:12:09 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define MAX_ARGS 	100

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
"\
1) A client with a vertical scale will appear. The scale\n\
   will have two labels that say '0' and '100'. Both labels\n\
   will have thin black borders and the '100' will be at the bottom.\n\
2) Press MB1 on the slider and drag the slider. The callback\n\
   reason and value should be printed in the term window.\n\
3) Press MB1 in the area above the slider. The callback reason and\n\
   value should be printed in the term window.\n\
4) Resize the client window larger. The labels should spread out\n\
   and remain on the left side, the scale area should span the right side.\n\
5) Resize the client window smaller.\n\
6) Continue to have the scale change orientation to HORIZONTAL.\n\
",
"\
1) A client with a horizontal scale will appear. The scale\n\
   will have two labels that say '0' and '100'. Both labels\n\
   will have thin black borders and the '100' will be on the right.\n\
2) Press MB1 on the slider and drag the slider. The callback\n\
   reason and value should be printed in the term window\n\
3) Press MB1 in area to the left of the slider. The callback\n\
   reason and value should be printed in the term window.\n\
4) Resize the client window larger. The label should spread out\n\
   and remain on the top, the scale area should span the bottom.\n\
5) Resize the client window smaller.\n\
6) Test Finished -- Exit Please\
"
      };
	
int Pause_cnt = 0;
XtAppContext  app_context;
