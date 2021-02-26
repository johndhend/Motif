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
static char rcsid[] = "$XConsortium: DNDList1.c /main/9 1995/07/14 11:54:15 drk $"
#endif
#endif
/*
 *	File:	DNDList1.c
 *
 *	A program to be run as one of the clients to test Drag and Drop
 *
 */

#include <testlib.h>

#define NITEMS 9

/*  Global Variables  */

char *Istrings[] = {
    "DrawnButton",
	"Label",
    "List",
	"PushButton",
    "Separator",
	"ArrowButton",
    "ScrollBar",
	"Text",
    "ToggleButton"
};

Widget    List1;

Boolean	use_instruction_box;

void  main (argc, argv)
int		argc;
char	**argv;
{

    register int       	n;
    Arg                	args[MAX_ARGS];
    XmString           	ItemList[NITEMS];


	use_instruction_box = True;

    CommonTestInit(argc, argv);

	if (UserData != NULL)
		ProcessCommandArgs();

    /* convert the plain strings to fancy Xstrings */
    for (n = 0; n < NITEMS; n++)
		ItemList[n] = XmStringLtoRCreate(Istrings[n], 
										 XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 5); n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2); n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2); n++;
    XtSetArg(args[n], XmNitems, ItemList); n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); n++;
    XtSetArg(args[n], XmNvisibleItemCount, NITEMS); n++;
    XtSetArg(args[n], XmNselectionPolicy, XmMULTIPLE_SELECT); n++;
    List1 = XmCreateList(Shell1, "List1", args, n);
    XtManageChild(List1);

    for (n = 0; n < NITEMS; n++)
		XmStringFree(ItemList[n]);

    XtRealizeWidget(Shell1);

	if (use_instruction_box == True) {

		CommonPause();

		CommonPause();

	}

    XtAppMainLoop(app_context);

}


#define	WORD_LEN	32

ProcessCommandArgs()
{

	char	*user_data;
	char	next_word[WORD_LEN + 1];
	int     num_spaces;

	user_data = UserData;

	while (*user_data != '\0') {

		get_next_word(user_data, next_word, &num_spaces);
		user_data += (strlen(next_word) + num_spaces);

		if (strcmp(next_word, "-noinstruct") == 0) {
			use_instruction_box = False;
			continue;

		}

	}

	free(UserData);

}


get_next_word(source, dest, spaces)
char	*source;
char	*dest;
int		*spaces;
{

	int	n;
	int	space_count;

	space_count = 0;

	while (isspace(*source)) {
		source++;
		space_count++;
	}

	n = 0;
	while (!isspace(*source) && *source != '\0' && n < WORD_LEN) {
		*dest++ = *source++;
		n++;
	}
	*dest = '\0';
	*spaces = space_count;

}
