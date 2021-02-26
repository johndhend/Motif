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
static char rcsid[] = "$XConsortium: focus_icon.c /main/7 1995/07/14 12:02:11 drk $"
#endif
#endif
/*
 *	file: focus_icon.c
 *
 *	Attempts to warp pointer to move on the icons rapidly to check
 *	enter/leave compression by mwm.
 */

#include	<stdio.h>

#include	<X11/Xlib.h>

#define	DEFAULT_VALUE	20
#define	DEFAULT_STEP	95
#define	DEF_MAX_MIN_XPOS	500
#define	DEF_MAX_MAX_XPOS	800
#define	DEF_NUM_TRIALS	10

Display	*display;

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
	int		y_decr, x_pos, x_step, min_x, y_pos, max_xpos;
	int		num_trials;
	int		count = 0;
	char	c;
	int		i, j;
	char		d_name[44];


	num_trials = DEF_NUM_TRIALS;
	x_step = DEFAULT_STEP;
	x_pos = y_decr = DEFAULT_VALUE;
	max_xpos = DEF_MAX_MAX_XPOS;
	strcpy(d_name,":0");

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
					y_decr = atoi(*++argv);
					break;
				case 'n':
					num_trials = atoi(*++argv);
					break;
				case 's':
					x_step = atoi(*++argv);
					break;
				case 'm':
					max_xpos = atoi(*++argv);
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
	if (x_pos <= 0)
		x_pos = DEFAULT_VALUE;
	if (y_decr <= 0)
		y_decr = DEFAULT_VALUE;
	if (num_trials <= 0)
		num_trials = DEF_NUM_TRIALS;
	if (x_step <= 0)
		x_step = DEFAULT_STEP;
	if (max_xpos <= 0)
		max_xpos = DEF_MAX_MIN_XPOS;
	if (max_xpos > DEF_MAX_MAX_XPOS)
		max_xpos = DEF_MAX_MAX_XPOS;
	min_x = x_pos;

	if ((display = XOpenDisplay(d_name)) == NULL) {
		fprintf(stderr, "Can not open display\n");
		exit(0);
	}
	root_win = RootWindow(display, DefaultScreen(display));
	XGetWindowAttributes(display, root_win, &win_attrs);
	root_width = win_attrs.width;
	root_height = win_attrs.height;
	y_pos = root_height - y_decr;

#ifdef	DEBUG
	printf("root_width = %d root_height = %d\n", root_width, root_height);
#endif

	for (i = 0; i < num_trials; i++) {

		/* Move left to right first */
		for (x_pos = min_x; x_pos <= max_xpos; x_pos += x_step) {
			XWarpPointer(display, None, root_win, 0, 0, root_width, 
						 root_height, x_pos, y_pos);
			XFlush(display);
			count++;
		}

		/* And then move right to left */
		for (x_pos = max_xpos; x_pos >= min_x; x_pos -= x_step) {
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
	printf("Usage: focus [-x startx] [-y y_decr] [-n trials] [-m max_xpos] [-s x_step] [-d display] [-h]\n");
	printf("where - \n");
	printf("\tstartx - X position from where to start moving the cursor\n");
	printf("\ty_decr - Y value to be subtracted from screen height to get y pos.\n");
	printf("\ttrials - no. of roundtrips that the cursor will make\n");
	printf("\tmax_xpos - Max. value of X cursor will move to in forward direction\n");
	printf("\tx_step - steps in no. of pixels cursor willmove in X direction\n");
	printf("\tdisplay - display name\n");
	printf("\t\"-h\" - will print out this message\n");

	exit(0);
}
