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
/*   $XConsortium: PIHints.h /main/6 1995/07/13 20:20:28 drk $ */

/*  X headers  */
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

/*  Xm headers  */
#include <Xm/MwmUtil.h>

/*
 * definition for the Hints Icon
 */
#define PIIcon_width 50
#define PIIcon_height 50
static char PIIcon_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0xf0,
   0xff, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x30, 0xc0, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x30, 0x80, 0x01, 0x03, 0x00, 0x00, 0x00, 0x30, 0x80, 0x01, 0x03,
   0x00, 0x00, 0x00, 0x30, 0x80, 0x01, 0x03, 0x00, 0x00, 0x00, 0x30, 0x80,
   0x01, 0x03, 0x00, 0x00, 0x00, 0x30, 0x80, 0x01, 0x03, 0x00, 0x00, 0x00,
   0x30, 0x80, 0x01, 0x03, 0x00, 0x00, 0x00, 0x30, 0xc0, 0x01, 0x03, 0x00,
   0x00, 0x00, 0xf0, 0xff, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0x00,
   0x03, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x30,
   0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00,
   0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03,
   0x00, 0x00, 0x00, 0x30, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x30, 0x00,
   0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0x20, 0x09, 0xf2, 0xc7, 0x03, 0x00, 0x80, 0x20, 0x19, 0x82, 0x20, 0x04,
   0x00, 0x80, 0x20, 0x29, 0x82, 0x20, 0x00, 0x00, 0x80, 0x20, 0x49, 0x82,
   0x20, 0x00, 0x00, 0x80, 0x3f, 0x89, 0x82, 0xc0, 0x03, 0x00, 0x80, 0x20,
   0x09, 0x83, 0x00, 0x04, 0x00, 0x80, 0x20, 0x09, 0x82, 0x00, 0x04, 0x00,
   0x80, 0x20, 0x09, 0x82, 0x20, 0x04, 0x00, 0x80, 0x20, 0x09, 0x82, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00};

/*
 * definition for the Hints Icon Mask
 */
#define PIIcon_msk_width 50
#define PIIcon_msk_height 50
static char PIIcon_msk_bits[] = {
   0x00, 0xf0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff,
   0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x80,
   0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x1f,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xf0, 0xff, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf8,
   0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x3f,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xc0, 0xff, 0xff, 0xff,
   0xff, 0x0f, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff,
   0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x01, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x7f,
   0x00, 0x00};

/* 
 * Data for summary
 */
#define NUM_TESTS		9
#define TEST_DESCRIP_LENGTH	65

struct TestInfo PIInfo[NUM_TESTS] = 
{
	{"Change Normal Hints - position, size               WM_NORMAL_HINTS",
		True,	0},
	{"Change Normal Hints - min/max width/height         WM_NORMAL_HINTS",
		True,	0},
	{"Change WM Hints - icon pixmap for window                  WM_HINTS",
		True,	0},
	{"Change Normal Hints - width/height incrmts         WM_NORMAL_HINTS",
		True,	0},
	{"Change Normal Hints - min/max aspect ratios        WM_NORMAL_HINTS",
		True,	0},
	{"Change WM Hints - icon window for window                  WM_HINTS",
		True,	0},
#ifdef	DONT
	{"Change WM Hints - input focus for window                  WM_HINTS",
		True,	0},
#endif	/* DONT */
	{"Set TransientFor - PIHints for black_window       WM_TRANSIENT_FOR",
		True,	0},
	{"Set TransientFor - test_top for black_window      WM_TRANSIENT_FOR",
		True,	0},
	{"Set TransientFor - black_window for white_window  WM_TRANSIENT_FOR",
		True,	0},
};

/*
 * Local declarations
 */

Widget			test_top,
				test1_btn1;

Atom			new_type;
int				new_format;
unsigned long	new_nitems,
				new_bytes_after;
unsigned char	*new_data;
Atom			test_atom;

Window			test_wdw, button_wdw, top_wdw, hints_wdw, hints_icon_wdw;


Widget			test_top,
				test1_btn1;
Pixmap			test1_btn1_icon;

Window			black_window,
				white_window,
				transient_for_window,
				new_trans_for_window;

XSetWindowAttributes	win_attrs;

XSizeHints  wm_set_size, *wm_get_size;
XWMHints    wm_set_hints, *wm_get_hints;
Pixmap      hints_icon_pm, hints_icon_msk_pm;

String	hints_winname = "Hints Window";
String	black_winname = "Black Window";
String	white_winname = "White Window";

long supplied_return;
