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
static char rcsid[] = "$XConsortium: ArrowBtn2.c /main/9 1995/07/13 17:28:29 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/****************************************
*   Automatic test program generation   *
*              Version 1.2              *
*       Tue Apr  4 15:41:13 1989        *
****************************************/

#include <testlib.h>

Widget ArrowButton2, ArrowButton1;
Widget parent1, parent2;

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False;
  register int       n;
  Arg                args[MAX_ARGS];
  XmString           tcs;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetArg(args[n],  XmNkeyboardFocusPolicy, XmPOINTER);  n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget(Shell1);

  n = 0;
  ArrowButton2 = XmCreateArrowButton(Shell1, "ArrowButton2", args, n);
  XtManageChild(ArrowButton2);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
  XtSetArg(args[n], XmNhighlightThickness, 5);  n++;
  XtSetArg(args[n], XmNhighlightColor, CommonGetColor("red"));  n++;
  XtSetArg(args[n], XmNforeground, CommonGetColor("red"));  n++;
  XtSetValues(ArrowButton2, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNhighlightThickness, 10);  n++;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_LEFT);  n++;
  XtSetValues(ArrowButton2, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNshadowThickness, 4);  n++;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_RIGHT);  n++;
  XtSetArg(args[n], XmNtopShadowColor, CommonGetColor("pink"));  n++;
  XtSetValues(ArrowButton2, args, n);

  CommonPause();

  n = 0;
  XtSetArg(args[n], XmNarrowDirection, XmARROW_DOWN);  n++;
  XtSetArg(args[n], XmNhighlightOnEnter, TRUE);  n++;
  XtSetArg(args[n], XmNbottomShadowColor, CommonGetColor("green"));  n++;
  XtSetValues(ArrowButton2, args, n);

  CommonPause();

  XtDestroyWidget (ArrowButton2);

  n = 0;
  XtSetArg (args[n], XmNorientation, XmVERTICAL); n++;
  parent1 = XmCreateRowColumn (Shell1, "parent1", args, n);
  
  n = 0;
  ArrowButton1 = XmCreateArrowButton (parent1, "ArrowButton1", args, n);
  XtAddCallback (ArrowButton1, XmNactivateCallback, CommonGenericCB, NULL);

  n = 0;
  parent2 = XmCreateBulletinBoard (parent1, "parent2", args, n);
 
  n = 0;
  XtSetArg (args[n], XmNwidth, 200); n++;
  ArrowButton2 = XmCreateArrowButton (parent2, "ArrowButton2", args, n);
  XtAddCallback (ArrowButton2, XmNactivateCallback, CommonGenericCB, NULL);

  XtManageChild (ArrowButton1);
  XtManageChild (ArrowButton2);
  XtManageChild (parent2);
  XtManageChild (parent1);

  CommonPause();

  XtSetSensitive (ArrowButton1, False);
  XtSetSensitive (parent2, False);

  CommonPause();

  XtAppMainLoop(app_context);
  XtDestroyWidget(ArrowButton2);
}















char * concat_args(n, words)
int n;
char *words[];
{
	char *buffer;
	int i, len = 0;

	if (n <= 1)
		return("");

	for (i = 1; i < n; i++)
		len += strlen(words[i]);

	len += (n - 1);

	buffer = (char *) malloc(len + 1);
	if (buffer == NULL) 
		{
		fprintf(stderr, "Out of Memory in concat_args()\n");
		exit(1);
		}
	buffer[0] = '\0';

	for (i = 1; i < n; i++)
		{
		if (i > 1)
			strcat(buffer," ");
		strcat(buffer, words[i]);
		}
	return(buffer);
}

void quit(w, client_data, event)
Widget 	w;
caddr_t	client_data;
XEvent	*event;
{
exit(0);
}
	
void myQuit()
{
	printf("Completed\n");
	exit(0);
}









