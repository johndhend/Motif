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
/*   $XConsortium: PIColormap.h /main/6 1995/07/13 20:18:50 drk $ */

/*  X headers  */
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

/*  Xm headers  */
#include <Xm/MwmUtil.h>


/* 
 * Data for summary
 */

#define	PIInfo_INIT		0
#define	PIInfo_CMstart	0

#define NUM_TESTS		4
#define TEST_DESCRIP_LENGTH	60

#define			VALID_TEST1	1
#define			VALID_TEST2	2
#define			VALID_TEST3	3
#define			FINISH		4

struct TestInfo PIInfo[NUM_TESTS] = 
{
	{"Check if def_cmap is initially installed WM_COLORMAP_WINDOWS",
		True,	0},
	{"Check if cmap1 is listed as installed    WM_COLORMAP_WINDOWS",
		True,	0},
	{"Check if cmap2 is listed as installed    WM_COLORMAP_WINDOWS",
		True,	0},
	{"Check if def_cmap is listed as installed WM_COLORMAP_WINDOWS",
		True,	0},
};


/*
 * Local declarations
 */

Widget			toplevel,
				test_top,
				test1_btn1,
				test2_btn1,
				test_box;
Pixmap			test1_btn1_icon, test2_btn1_icon;

Atom			new_type;
int				new_format;
unsigned long	new_nitems,
				new_bytes_after;
unsigned char	*new_data;
Atom			test_atom;
Window			test_wdw, top_wdw;
Window			button_wdw, button_wdw2,
				test_wdw;

Window			wdw_list[5];
int				def_scrn;

Colormap		*cm_list, def_cmap, cmap1, cmap2;
int				cm_num, i, ncolors;
XColor			colors[256], new_colors[256];

int				iteration = 1;

void	test1_btn1_proc();
