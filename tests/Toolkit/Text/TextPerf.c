/* $XConsortium: TextPerf.c /main/5 1995/07/15 21:10:19 drk $ */
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

/*
 *	file: TextPerf.c
 *
 *	Has a Multi line Scrolled Text widget under Form. 
 *      The XmNcolumns resource is being set to 80 at creation time,
 *      and XmNrows to 24. The wordWrap is off. 
 *	The file TextPerfIn.c from Motif 1.1 is read in and the
 *	memory measured.
 */

/*  Standard C headers  */
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

/*  X headers  */
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

#include <testlib.h>

#define	TEXT1_TOPCHAR	1
#define	NUM_COLUMNS	80
#define	NUM_ROWS	24
#define	IN_FILE		"TextPerfIn.c"

#define	TEXT1_X		10
#define	TEXT1_Y		10

#define	MAX_TRIALS	50

static void	fill_text_buf();
static void  	fillTextCB();
static void  	quitCB();
static void  	measureMemoryCB();
static void  	clearTextCB();
static void  	fillSmallTextCB();
static void  	destroyTextCB();
static void  	createTextCB();


/*  Global Variables  */

char *text_string;
char *small_text_string = "SMALL TEXT";

Widget Form1;
Widget Text1;
Widget	fillText;
Widget	measureMemory;
Widget	disableMalloc;
Widget	fillSmallText;
Widget	clearText;
Widget	destroyText, createText;
XmFontList	newfontlist;
XFontStruct	*newfont;

Arg args[MAX_ARGS];
int n;
FILE	*in_fp;
int		in_fd;
int		memory_measured[MAX_TRIALS];
int		num_trials = 0;
int		start_memory, allocated_memory, memory_in_use;


main (argc, argv)
int argc;
char **argv;
{

	Widget	quit;
        XmString string;

	/*  initialize toolkit  */
    CommonTestInit(argc, argv);

    n = 0;
	XtSetArg(args[n], XtNwidth, 800);  n++;
	XtSetArg(args[n], XtNheight, 500);  n++;
    XtSetValues(Shell1, args, n);
    

	/* create main form */
	n = 0;
	Form1 = XmCreateForm (Shell1, "Form1", args, n);
	XtManageChild (Form1);

	/* Read the text file into a buffer */
	fill_text_buf();

	/* create multi line text widget */
	n = 0;
	XtSetArg(args[n], XmNx, TEXT1_X); n++;
	newfont = XLoadQueryFont(XtDisplay(Shell1),"9x15");
	if (newfont != NULL) {
		newfontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(args[n], XmNfontList, newfontlist);  n++;
	}
	XtSetArg(args[n], XmNcolumns, NUM_COLUMNS);  n++;
	XtSetArg(args[n], XmNrows, NUM_ROWS);  n++;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNscrollHorizontal, False); n++;
	XtSetArg(args[n], XmNeditable, False); n++;
	Text1 = XmCreateScrolledText(Form1, "Text1", args, n);
	XtManageChild(Text1);

	XmTextSetString( Text1, text_string);

	XtRealizeWidget(Shell1);

        /*  Instruct user to rerun test - timing the display of text widget. */
        CommonPause(); 

        /*  Test scrolling by moving slider. */
        CommonPause();

        /*  Test scrolling my clicking up and down arrows. */
        CommonPause();

        /*  Exit Panel. */
        CommonPause();

	XtAppMainLoop(app_context);
}


static void	fill_text_buf()
{

	struct stat	stat_buf;
	int	filesize, bytes_read;

	/* Read the file into a text buffer */
	if ((in_fp = fopen(IN_FILE, "r")) == NULL) {
		fprintf(stderr, "Can not open %s\n", IN_FILE);
		exit(0);
	}

	in_fd = fileno(in_fp);
	fstat(in_fd, &stat_buf);
	filesize = stat_buf.st_size;

	text_string = (char *)XtMalloc(filesize + 1);
	bytes_read = fread(text_string, sizeof(char ), filesize, in_fp);
	if (bytes_read != filesize) {
		printf("filesize = %d bytes_read = %d\n", filesize, bytes_read);
		fclose(in_fp);
		exit(0);
	}
	*(text_string + filesize) = '\0';
	fclose(in_fp);

}
