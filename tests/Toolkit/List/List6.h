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
/*   $XConsortium: List6.h /main/9 1995/07/13 18:19:53 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define NITEMS  12

/*  Global Variables  */

char *Istrings[NITEMS] = {
	"LongItem1",
	"LongItem2",
	"LongItem3",
	"LongItem4",
	"LongItem5",
	"LongItem6",
	"LongItem7",
	"LongItem8",
	"LongItem9",
	"LongItem10",
	"LongItem11",
	"LongItem12"
	};

char *Istrings2[NITEMS] = {
	"Item1",
	"Item2",
	"Item3",
	"Item4",
	"Item5",
	"Item6",
	"Item7",
	"Item8",
	"Item9",
	"Item10",
	"Item11",
	"Item12"
	};

Widget    List1;

/*  Private Functions  */


static XtCallbackProc  DefACB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static XtCallbackProc  SSelCB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static XtCallbackProc  MSelCB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static XtCallbackProc  ESelCB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static XtCallbackProc  BSelCB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static XtCallbackProc  HelpCB(Widget w, caddr_t client_data,
			      caddr_t call_data);
static void 	       DeleteMe(Widget w, XEvent *event, 
			      String *params, Cardinal num_params);

