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
/*   $XConsortium: PINames.h /main/6 1995/07/13 20:23:15 drk $ */

/*  X headers  */
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

/*  Xm headers  */
#include <Xm/MwmUtil.h>


/* 
 * Data for summary
 */

#define NUM_TESTS		5
#define TEST_DESCRIP_LENGTH	60

struct TestInfo PIInfo[NUM_TESTS] = 
{
	{"Change the window name of a window (WM_NAME)          ",
		True,	0},
	{"Check for a ***** default name                        ",
		True,	0},
	{"Change the icon name of a window (WM_ICON_NAME)       ",
		True,	0},
	{"Change the window name of ***** (WM_NAME)             ",
		True,	0},
	{"Change the class name structure of a window (WM_CLASS)",
		True,	0},
};


Widget			test_top,
				label_box;

Atom			new_type;
int				new_format;
unsigned long	new_nitems,
				new_bytes_after;
unsigned char	*new_data;
Atom			test_atom;
Window			test_wdw, top_wdw;
Window          normal_wdw;

XClientMessageEvent     ClientMsg_ev;

String	new_winname = "New Window Name";
String	look_at_name = "Window name should be \"New Window Name\".";
String	new_iconname = "PI Icon";
String	look_at_icon = "Icon name should be \"PI Icon\".";
String	look_at_classname =
					"Window name should be \"NEWER Window Class Name\".";

char	class_buf[80];			/* string for WM_CLASS prop */
int		l_name, l_class;		/* temp length vars */

String	new_class_name = "NEWER Window Class Name";
String	new_class_class = "PINewClass";
String	new_winname2 = "Second New Name";
String	old_winname2 = "*****";
char	*new_name;
XClassHint	class_hints;
XWMHints	wm_set_hints;
