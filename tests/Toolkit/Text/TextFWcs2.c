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
static char rcsid[] = "$XConsortium: TextFWcs2.c /main/7 1995/07/13 19:33:20 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#ifndef	MOTIF1_1

Arg args[MAX_ARGS];
static char starting_string[] = "Sample Text ";

static void ModifyVerifyCB (Widget w, XtPointer client_data,
	XtPointer call_data)
{
	XmTextVerifyCallbackStructWcs  *modify_verify;
	static char c = 'A';
	static wchar_t wc;
	static int position = 12;
	static int nbytes;

	modify_verify = (XmTextVerifyCallbackStructWcs *)call_data;

	if (modify_verify->event == NULL)
		printf("Null event in ModifyVerify callback\n");

	if (modify_verify->text->wcsptr != NULL) 
	{
		/* Make sure that it is not a BS */
		nbytes = mbtowc(&wc, &c, 1);
		modify_verify->startPos = position++;
		modify_verify->endPos = modify_verify->startPos;
		modify_verify->text->wcsptr[0] = wc;
		modify_verify->text->length = nbytes;
	}

	c += 1;
	if (c > 'Z')
		c = 'A';
}

#endif	/* MOTIF1_1 */

void main (argc, argv)
int argc;
char **argv;
{
	Widget Text1 = NULL;
	int n = 0;
	wchar_t	*starting_wchar;
	int	num_chars;

#ifndef	MOTIF1_1

	/*  initialize toolkit  */
	CommonTestInit(argc, argv);

	n = 0;
	XtSetArg(args[n], XmNwidth, 10); n++;
	XtSetArg(args[n], XmNheight, 10); n++;
	XtSetValues(Shell1, args, n);
	XtRealizeWidget(Shell1);

	num_chars = strlen(starting_string);
	starting_wchar =
		(wchar_t *)XtMalloc((unsigned)
			(num_chars + 1) * sizeof(wchar_t));
	mbstowcs(starting_wchar, starting_string, num_chars + 1);

	n = 0;
	XtSetArg(args[n], XmNfontList, CommonGetFontList("fixed"));  n++;
	XtSetArg(args[n], XmNcursorPosition, 12);  n++;
	XtSetArg(args[n], XmNvalueWcs, starting_wchar);  n++;
	XtSetArg(args[n], XmNforeground, CommonGetColor("Red"));  n++;
	XtSetArg(args[n], XmNbackground, CommonGetColor("White"));  n++;
	Text1 = XmCreateTextField(Shell1, "Text1", args, n);
	XtFree((char *)starting_wchar);

	XtManageChild(Text1);
	XtRealizeWidget(Shell1);

	n = 0;
	XtSetArg(args[n], XmNresizeWidth, False);  n++;
	XtSetArg(args[n], XmNcolumns, 40);  n++;
	XtSetValues(Text1, args, n);

	XtAddCallback(Text1, XmNmodifyVerifyCallbackWcs, ModifyVerifyCB, NULL);

	CommonPause();
	
	XtAppMainLoop(app_context);

#else	/* MOTIF1_1 */

	printf("This is not a Motif 1.1 test.\n");
	exit(0);

#endif	/* MOTIF1_1 */
}
