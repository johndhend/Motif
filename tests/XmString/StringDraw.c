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
static char rcsid[] = "$XConsortium: StringDraw.c /main/5 1995/07/13 19:55:17 drk $"
#endif
#endif

/*
 *	file: StringDraw.c
 *
 *	Test XmStringDraw with/without clipping.
 *
 */

#include <testlib.h>

													/*BeginPIR4294*/
#define CLIP_MARGIN   40
#define INITIAL_X     30
#define INITIAL_Y     30
#define CLIP_HEIGHT   5

char	*clip_string = "TEST STRING FOR CLIPPING";
													/*EndPIR4294*/


void main (argc, argv)
int argc;
char 			**argv;
{

	Widget		bboard;
	Widget 		drawArea;
	Window		window;
	Arg			args[MAX_ARGS];
	Cardinal	n;
	XmString	tcs = (XmString)0;
	XFontStruct	*fnt;
	XmFontList	fontList1 = NULL;
#ifdef MOTIF1_1
	XmStringCharSet	cs = (char *) XmSTRING_DEFAULT_CHARSET;
#else
	XmFontListEntry	fixed_font = NULL;
	XmFontListEntry	font1 = NULL;
	XmStringCharSet	cs = (char *) XmFONTLIST_DEFAULT_TAG;
	XmFontType		type_ret;
#endif
    Dimension 	width;
    Dimension 	height;
	Position	x;
	Position	y;
    XRectangle 	clip;
    static GC 	gc;
    XGCValues 	gcv;


	/*  initialize toolkit  */
    CommonTestInit(argc, argv);

#ifdef MOTIF1_1
	if ((fnt = XLoadQueryFont(XtDisplay(Shell1), "9x15bold")) == NULL) {

		fprintf(stderr, "Cannot find 9x15bold font. Trying fixed font\n");
		if ((fnt = XLoadQueryFont(XtDisplay(Shell1), "fixed")) == NULL) {
			fprintf(stderr, "Cannot find fixed font\n");
			exit(0);
		}

	}
	fontList1 = XmFontListCreate(fnt, cs);

#else
	fixed_font = XmFontListEntryLoad(display, "fixed", XmFONT_IS_FONT, 
							 	  	 XmFONTLIST_DEFAULT_TAG);

	if ((font1 = XmFontListEntryLoad(display, "9x15bold", XmFONT_IS_FONT, 
									 XmFONTLIST_DEFAULT_TAG)) == NULL) {

		fprintf(stderr, "Cannot create FontEntry for 9x15bold\n");
		if (fixed_font == NULL) {
			fprintf(stderr, "Cannot fallback to fixed font\n");
			exit(0);
		}
		font1 = fixed_font;

	}

	fontList1 = XmFontListAppendEntry(NULL, font1);

#endif

	n = 0;
#ifdef MOTIF1_1
	XtSetArg (args[n], XmNheight, 100 ); n++;
	XtSetArg (args[n], XmNwidth, 100 ); n++;
#endif
	bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);
	XtManageChild (bboard);

	n = 0;
	XtSetArg (args[n], XmNx, 10 ); n++; 
	XtSetArg (args[n], XmNy, 50 ); n++;  
	XtSetArg(args[n], XmNwidth,  300); n++;
	XtSetArg(args[n], XmNheight, 200); n++;
	drawArea = XmCreateDrawingArea(bboard, "drawArea", args, n);
	XtManageChild (drawArea);

	XtRealizeWidget (Shell1);

	CommonPause();

	window = XtWindow(drawArea);

#ifdef MOTIF1_1
	tcs = XmStringCreateLtoR(clip_string, XmSTRING_DEFAULT_CHARSET);
#else
	tcs = XmStringCreateLtoR(clip_string, XmFONTLIST_DEFAULT_TAG);
#endif

    n = 0;
    XtSetArg(args[n], XmNforeground, &gcv.foreground); n++;
    XtSetArg(args[n], XmNbackground, &gcv.background); n++;
    XtGetValues(drawArea, args, n);

#ifdef MOTIF1_1
    gcv.font = font1->fid;
#else
	fnt = (XFontStruct *)XmFontListEntryGetFont(font1, &type_ret);
	gcv.font = fnt->fid;
#endif

    gc = XCreateGC(display, window, GCFont | GCForeground | GCBackground,
				   &gcv);

    XmStringExtent(fontList1, tcs, &width, &height);

	x = INITIAL_X;
	y = INITIAL_Y;

	/* No clipping */
    clip.x = x;
    clip.y = y;
    clip.width  = width;
    clip.height = height;

    XmStringDraw(display, window, fontList1, tcs, gc,
         		 x, y, width, XmALIGNMENT_BEGINNING, 
				 XmSTRING_DIRECTION_L_TO_R, &clip);

	x = INITIAL_X;
	y = 2 * INITIAL_Y;

													/*BeginPIR4294*/
	/* Horizontal clipping, no vertical clipping */
    clip.x = x + CLIP_MARGIN;
    clip.y = y;
    clip.width  = width - 2 * CLIP_MARGIN;
    clip.height = height;

    XmStringDraw(display, window, fontList1, tcs, gc,
         		 x, y, width, XmALIGNMENT_BEGINNING, 
				 XmSTRING_DIRECTION_L_TO_R, &clip);
													/*EndPIR4294*/

	x = INITIAL_X;
	y = 3 * INITIAL_Y;

	/* Vertical clipping, no horizontal clipping */
    clip.x = x;
    clip.y = y;
    clip.width  = width;
    clip.height = height - CLIP_HEIGHT;

    XmStringDraw(display, window, fontList1, tcs, gc,
         		 x, y, width, XmALIGNMENT_BEGINNING, 
				 XmSTRING_DIRECTION_L_TO_R, &clip);

	x = INITIAL_X;
	y = 4 * INITIAL_Y;

	/* Both vertical and horizontal clipping */
    clip.x = x + CLIP_MARGIN;
    clip.y = y;
    clip.width  = width - 2 * CLIP_MARGIN;
    clip.height = height - CLIP_HEIGHT;

    XmStringDraw(display, window, fontList1, tcs, gc,
         		 x, y, width, XmALIGNMENT_BEGINNING, 
				 XmSTRING_DIRECTION_L_TO_R, &clip);

	CommonPause();

      if ( fixed_font )
         XmFontListEntryFree( &fixed_font );
      if ( font1 )
         XmFontListEntryFree( &font1 );
      if ( fontList1 )
         XmFontListFree( fontList1 );
      if ( fnt )
         XFreeFont( display, fnt );
      XmStringFree( tcs );


	XtAppMainLoop(app_context);
}
