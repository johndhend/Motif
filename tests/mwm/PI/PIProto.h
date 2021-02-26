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
/*   $XConsortium: PIProto.h /main/6 1995/07/13 20:24:06 drk $ */

/*  X headers  */
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

/*  Xm headers  */
#include <Xm/MwmUtil.h>


/* 
 * Data for summary
 */

#ifdef SHOW_P899
#define NUM_TESTS		7
#else
#define NUM_TESTS		6
#endif /* P899 */

#define TEST_DESCRIP_LENGTH	60

#define PIInfo_DW1  0
#define PIInfo_DW2  1
#ifdef  DONT
#define PIInfo_SY   2
#define PIInfo_TF   3
#endif  /* DONT */
#define PIInfo_MM   2
#define PIInfo_CB   3

#ifdef SHOW_P899

#define PIInfo_CB2a 4
#define PIInfo_CB2r 5
#define PIInfo_CB3  6

#else

#define PIInfo_CB2r 4
#define PIInfo_CB3  5

#endif /* P899 */

struct TestInfo PIInfo[NUM_TESTS] = 
{
	{"Check if ClientMessage sent for f.kill      WM_DELETE_WINDOW",
		True,	0},
	{"Check if window is not deleted after f.kill WM_DELETE_WINDOW",
		True,	0},
#ifdef  DONT
	{"Check ClientMessage sent for state change   WM_SAVE_YOURSELF",
		True,   0},
	{"Check ClientMessage sent for take focus        WM_TAKE_FOCUS",
		True,   0},
#endif
	{"Check ClientMessage sent for motif message _MOTIF_WM_MESSAGE",
		True,	0},
	{"Check callback sent for motif message      _MOTIF_WM_MESSAGE",
		True,	0},
#ifdef SHOW_P899
	{"Check callback sent for menu item 2 (added)   _MOTIF_WM_MENU",
		True,	0},
#endif /* P899 */
	{"Check callback sent for menu item 2 (replaced)_MOTIF_WM_MENU",
		True,	0},
	{"Check callback sent for menu item 3 (grayed)  _MOTIF_WM_MENU",
		False,	0},
};

#define MSG_NUMBER      1024
#define MSG_NUMBER2     2024
#define MSG_NUMBER3     3024

#define			VALID_TEST1	1
#define			VALID_TEST2	2
#define			VALID_TEST3	3
#define			VALID_TEST4	4
#define			FINISH		5


Widget			test_top,
				test_top2,
				test1_btn1,
				test2_btn1;
Pixmap			test1_btn1_icon, test2_btn1_icon;

Atom			new_type;
int				new_format;
unsigned long	new_nitems,
				new_bytes_after;
unsigned char	*new_data;
Atom			test_atom;
Window			test_wdw, test_wdw2, top_wdw;
Atom            proto_atom, delwin_atom, savylf_atom,
				takfoc_atom, menu_atom, motif_msg_atom;

XWMHints	wm_set_hints;
XWindowAttributes	win_attrs;
Status	ret_stat;
int		msg_num;
char	menu_item[80];
char	menu_item2[300];

int				iteration = 1;

char	*send_msg1 = "Send_Message _M Alt<Key>F6 f.send_msg 1024";
char	*send_msg2 = "Send_Message2 _e Alt<Key>F7 f.send_msg 2024";
char	*send_msg3 = "Send_Message _M Alt<Key>F6 f.send_msg 1024 \n Send_Message2 _e Alt<Key>F7 f.send_msg 2024 \n Send_Message3 _d Alt<Key>F8 f.send_msg 3024";
