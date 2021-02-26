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
static char rcsid[] = "$XConsortium: LabelGad1.c /main/7 1995/07/13 19:09:32 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */



/****************************************
*   Automatic test program generation   *
*              Version 1.2              *
*       Wed Apr  5 12:26:41 1989        *
****************************************/

#include <testlib.h>
#include "gnu.bmp"
Pixmap gnumap;
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/StringDefs.h>
#include <Xm/XmP.h>

/*  Global Variables  */
Widget    Frame1;
Widget    LabelGadget1;

void  main(argc, argv)
int argc;
char **argv;
{
  Boolean trace = False;
  register int n;
  Arg args[MAX_ARGS];
  XmString tcs;
  int newx,newy,newH,newW;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  400);  n++;
  XtSetArg(args[n], XmNheight, 300);  n++;
  XtSetArg(args[n], XtNgeometry, "+0+0");  n++;
  XtSetValues(Shell1, args, n);
  
  XtRealizeWidget(Shell1);

  n = 0;
  Frame1 = XmCreateFrame(Shell1, "Frame1", args, n);
  XtManageChild(Frame1);

  n = 0;
  LabelGadget1 = XmCreateLabelGadget(Frame1, "LabelGadget1", args, n);
  XtManageChild(LabelGadget1);

  n = 0;
  XtSetArg(args[n], XmNmarginHeight, 20); n++;
  XtSetArg(args[n], XmNmarginWidth, 20); n++;
  XtSetValues(LabelGadget1, args, n);

  CommonPause();

  /* Change frame resource */
  n = 0;
  XtSetArg(args[n],XmNshadowType, XmSHADOW_ETCHED_OUT); n++;
  XtSetArg(args[n],XmNmarginWidth, 2); n++;
  XtSetArg(args[n],XmNmarginHeight, 2); n++;
  XtSetValues(Frame1, args, n);

  /* change so that button displays a pixmap on arm */
  gnumap = 
    XCreatePixmapFromBitmapData(display,
				DefaultRootWindow(display),
				gnu_bits, gnu_width, gnu_height,
				WhitePixel(display,DefaultScreen(display)),
				BlackPixel(display,DefaultScreen(display)),
				DefaultDepth(display,DefaultScreen(display)));

  n = 0;
  XtSetArg(args[n], XmNlabelType, XmPIXMAP);  n++;
  XtSetArg(args[n], XmNlabelPixmap, gnumap);  n++;
  XtSetValues(LabelGadget1, args, n);

  /* Go out and Fetch the current x,y coordinates */
  n = 0;
  XtSetArg(args[n],XmNx,&newx); n++;
  XtSetArg(args[n],XmNy,&newy); n++;
  XtSetArg(args[n],XmNmarginWidth,&newW); n++;
  XtSetArg(args[n],XmNmarginHeight,&newH); n++;
  XtGetValues(LabelGadget1,args,n);

  CommonPause();

  XtDestroyWidget(LabelGadget1);
  XtDestroyWidget(Frame1);

  CommonPause();

  XtAppMainLoop(app_context);
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









