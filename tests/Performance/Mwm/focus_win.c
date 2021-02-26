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
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: focus_win.c /main/7 1995/07/14 12:02:21 drk $"
#endif
#endif
/*
 *	file: focus_win.c
 *
 *	Attempts to warp pointer to move on the windows rapidly to check
 *	enter/leave compression by mwm.
 */

#include	<stdio.h>

#include	<X11/Xlib.h>

#define	DEFAULT_SCR_NUM	0

#define	DEFAULT_VALUE	20
#define	DEFAULT_STEP	100
#define	MAX_STEP		400
#define	DEF_MAX_MIN_XPOS	500
#define	DEF_MAX_MIN_YPOS	250
#define	DEF_MAX_MAX_XPOS	1023
#define	DEF_NUM_TRIALS	10

Display	*display;
int		scr_num;
Screen	*scr_ptr;
int		def_max_max_xpos, def_max_max_ypos;

main(argc, argv)
int		argc;
char	*argv[];
{

	Window	root_win;
	Window	root, child;
	int		root_x, root_y, win_x, win_y;
	unsigned int	key_buttons;
	XWindowAttributes	win_attrs;
	int		root_width, root_height;
	int		y_pos, x_pos, x_step, y_step, min_x, min_y, max_xpos, max_ypos;
	int		num_trials;
	int		count = 0;
	char	c;
	int		i, j;
	float	screen_aspect;
	char		d_name[44];

	strcpy(d_name,":0");
	num_trials = DEF_NUM_TRIALS;
	x_step = DEFAULT_STEP;
	x_pos = y_pos = DEFAULT_VALUE;

	if (argc > 1)
		while (--argc > 0) {

			argv++;
			c = **argv;
			if (c != '-')
				continue;
			c = *(*argv + 1);

			switch(c) {

				case 'x':
					x_pos = atoi(*++argv);
					break;
				case 'y':
					y_pos = atoi(*++argv);
					break;
				case 'n':
					num_trials = atoi(*++argv);
					break;
				case 's':
					x_step = atoi(*++argv);
					break;
				case 'X':
					max_xpos = atoi(*++argv);
					break;
				case 'Y':
					max_ypos = atoi(*++argv);
					break;
				case 'd':
					strcpy(d_name,*++argv);
					break;
				case 'h':
					print_usage();
					break;
				default:
					break;

			}
			argc--;
		}

	if ((display = XOpenDisplay(d_name)) == NULL) {
		fprintf(stderr, "Can not open display\n");
		exit(0);
	}
	scr_ptr = DefaultScreenOfDisplay(display);
	def_max_max_xpos = WidthOfScreen(scr_ptr);
	def_max_max_ypos = HeightOfScreen(scr_ptr);
	max_xpos = def_max_max_xpos;
	max_ypos = def_max_max_ypos;

	if (max_xpos <= 0)
		max_xpos = DEF_MAX_MIN_XPOS;
	if (max_xpos > def_max_max_xpos)
		max_xpos = def_max_max_xpos;
	if (max_ypos <= 0)
		max_ypos = DEF_MAX_MIN_YPOS;
	if (max_ypos > def_max_max_ypos)
		max_ypos = def_max_max_ypos;
	if (x_pos <= 0)
		x_pos = DEFAULT_VALUE;
	if (y_pos <= 0)
		y_pos = DEFAULT_VALUE;
	if (x_pos > max_xpos)
		x_pos = max_xpos;
	if (y_pos > max_ypos)
		y_pos = max_ypos;
	if (num_trials <= 0)
		num_trials = DEF_NUM_TRIALS;
	if (x_step <= 0)
		x_step = DEFAULT_STEP;
	if (x_step > MAX_STEP)
		x_step = MAX_STEP;
	screen_aspect = (float)(def_max_max_ypos) / (float)(def_max_max_xpos);
	y_step = x_step * screen_aspect;
	if (y_step <= 0)
		y_step = DEFAULT_STEP;
	if (y_step > MAX_STEP)
		y_step = MAX_STEP;
	min_x = x_pos;
	min_y = y_pos;

	root_win = RootWindow(display, DefaultScreen(display));
	XGetWindowAttributes(display, root_win, &win_attrs);
	root_width = win_attrs.width;
	root_height = win_attrs.height;

#ifdef	DEBUG
	printf("root_width = %d root_height = %d\n", root_width, root_height);
#endif

	for (i = 0; i < num_trials; i++) {

		/* Move left to right first */
		for (x_pos = min_x, y_pos = min_y; 
			 x_pos <= max_xpos && y_pos <= max_ypos; 
			 x_pos += x_step, y_pos += y_step) {
			XWarpPointer(display, None, root_win, 0, 0, root_width, 
						 root_height, x_pos, y_pos);
			XFlush(display);
			count++;
		}

		/* And then move right to left */
		for (x_pos = max_xpos, y_pos = max_ypos; 
			 x_pos >= min_x && y_pos >= min_y; 
			 x_pos -= x_step, y_pos -= y_step) {
			XWarpPointer(display, None, root_win, 0, 0, root_width, 
						 root_height, x_pos, y_pos);
			XFlush(display);
			count++;
		}

	}
#ifdef	DEBUG
	printf ("no. of warps = %d\n", count);
	XQueryPointer(display, root_win, &root, &child, &root_x, &root_y, 
				  &win_x, &win_y, &key_buttons);

	printf("root_x = %d root_y = %d win_x = %d win_y = %d key_buttons = %d\n",
		   root_x, root_y, win_x, win_y, key_buttons);
#endif

}


print_usage()
{
	printf("Usage: focus [-x startx] [-y starty] [-n trials] [-X max_xpos] [-Y max_ypos] [-s x_step] [-d display] [-h]\n");
	printf("where - \n");
	printf("\tstartx - X position from where to start moving the cursor\n");
	printf("\tstarty - Y position from where to start moving the cursor\n");
	printf("\ttrials - no. of roundtrips that the cursor will make\n");
	printf("\tmax_xpos - Max. value of X cursor will move to in forward direction\n");
	printf("\tmax_ypos - Max. value of Y cursor will move to in forward direction\n");
	printf("\tx_step - steps in no. of pixels cursor willmove in X direction\n");
	printf("\tdisplay - display name\n");
	printf("\t\"-h\" - will print out this message\n");

	exit(0);
}
