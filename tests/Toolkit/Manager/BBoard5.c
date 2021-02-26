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
static char rcsid[] = "$XConsortium: BBoard5.c /main/8 1995/07/13 18:26:24 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

/**************************************************************************
 *
 *  Create an arrow using inches and setting the width and height. 
 *  Reset the size, change the unit type, set the size again.
 *
 **************************************************************************/


#include <signal.h>
#include <X11/StringDefs.h>
#include <testlib.h>
#include <string.h>

/* global variables */
Position POSMOVE = 1;

/*  Forward declarations  */
void IncrementPosition();
void DecrementPosition();
void ParseUserData();


/* main loop */

void main (argc, argv)
int argc;
char **argv;
  {
   Widget board;
   Widget arrow[4];
   Arg args[20];
   int n, i;
   char buf[8];
   Position xpos = 0;
   Dimension mHeight, mWidth;

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);
   
   ParseUserData (UserData, &mHeight, &mWidth);

   n = 0;
   XtSetArg (args[n], XmNmarginHeight, mHeight); n++;
   XtSetArg (args[n], XmNmarginWidth, mWidth); n++;
   board = XmCreateBulletinBoard (Shell1, "board", args, n);

   for (i = 0; i <= 3; i++) {
     n = 0;
     sprintf (buf, "Arrow%d", i);
     XtSetArg (args[n], XmNwidth, 25); n++;
     XtSetArg (args[n], XmNheight, 25); n++;
     XtSetArg (args[n], XmNx, xpos); n++;
     XtSetArg (args[n], XmNy, 100); n++;
     arrow[i] = XmCreateArrowButton (board, buf, args, n);
     xpos += 50;
   }

   n = 0;
   XtSetArg (args[n], XmNarrowDirection, XmARROW_LEFT); n++;
   XtSetValues (arrow[0], args, n);
   XtAddCallback (arrow[0], XmNactivateCallback, 
		  DecrementPosition, (XtPointer) XmHORIZONTAL);
   
   n = 0;
   XtSetArg (args[n], XmNarrowDirection, XmARROW_UP); n++;
   XtSetValues (arrow[1], args, n);
   XtAddCallback(arrow[1], XmNactivateCallback, 
		 DecrementPosition, (XtPointer) XmVERTICAL);

   n = 0;
   XtSetArg (args[n], XmNarrowDirection, XmARROW_RIGHT); n++;
   XtSetValues (arrow[2], args, n);
   XtAddCallback (arrow[2], XmNactivateCallback, 
		  IncrementPosition, (XtPointer) XmHORIZONTAL);

   n = 0;
   XtSetArg (args[n], XmNarrowDirection, XmARROW_DOWN); n++;
   XtSetValues (arrow[3], args, n);
   XtAddCallback(arrow[3], XmNactivateCallback, 
		 IncrementPosition, (XtPointer) XmVERTICAL);

   XtManageChildren (arrow, 4);
   XtManageChild (board);
   XtRealizeWidget (Shell1);

   CommonPause(); /* move buttons around */

   /* double margin height and width */
   if ((mWidth == 0)) mWidth = 5;
   if ((mHeight == 0)) mHeight = 5;
   mWidth = mWidth * 2;
   mHeight = mHeight * 2;

   n = 0;
   XtSetArg (args[n], XmNmarginWidth, mWidth); n++;
   XtSetArg (args[n], XmNmarginHeight, mHeight); n++;
   XtSetValues (board, args, n);

   CommonPause();

   XtAppMainLoop (app_context);

 }

void IncrementPosition (w, client_data, call_data)
Widget w;
int client_data;
XtPointer call_data;

{
  Arg args[1];
  Position current_pos;

  if (client_data == XmVERTICAL) {
    XtSetArg (args[0], XmNy, &current_pos);
    XtGetValues (w, args, 1);
#ifdef DEBUG
    printf ("Moving %s from XmNy %d to %d\n", XtName(w), current_pos,
	    current_pos + POSMOVE);
#endif
    XtSetArg (args[0], XmNy, current_pos + POSMOVE);
    XtSetValues (w, args, 1);
  }
  else if (client_data == XmHORIZONTAL) {
    XtSetArg (args[0], XmNx, &current_pos);
    XtGetValues (w, args, 1);
#ifdef DEBUG
    printf ("Moving %s from XmNx %d to %d\n", XtName(w), current_pos,
	    current_pos + POSMOVE);
#endif
    XtSetArg (args[0], XmNx, current_pos + POSMOVE);
    XtSetValues (w, args, 1);
  }
  else printf ("Error in callback: wrong client_data %d\n", client_data);
}

void DecrementPosition (w, client_data, call_data)
Widget w;
int client_data;
XtPointer call_data;

{
  Arg args[1];
  Position current_pos;

  if (client_data == XmVERTICAL) {
    XtSetArg (args[0], XmNy, &current_pos);
    XtGetValues (w, args, 1);
#ifdef DEBUG
    printf ("Moving %s from XmNy %d to %d\n", XtName(w), current_pos,
	    current_pos - POSMOVE);
#endif
    XtSetArg (args[0], XmNy, (current_pos - POSMOVE));
    XtSetValues (w, args, 1);

    
  }
  else if (client_data == XmHORIZONTAL) {
    XtSetArg (args[0], XmNx, &current_pos);
    XtGetValues (w, args, 1);
#ifdef DEBUG
    printf ("Moving %s from XmNx %d to %d\n", XtName(w), current_pos,
	    current_pos - POSMOVE);
#endif
    XtSetArg (args[0], XmNx, (current_pos - POSMOVE));
    XtSetValues (w, args, 1);
  }
  else printf ("Error in callback: wrong client_data %d\n", client_data);
}

void ParseUserData (string, mheight, mwidth)
char * string;
Dimension *mheight, *mwidth;

{

  char *token;
  char buf[8];
  
  /* initialize it */
  buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = '\0';

  if (string == NULL) { /* default settings */
    *mheight = 0;
    *mwidth = 0;
    POSMOVE = 1;
#ifdef DEBUG
      printf ("Move incr: %d, margin h: %d, margin w: %d\n",
	      (int) POSMOVE, (int) *mheight, (int) *mwidth);
      fflush (stdout);
#endif
    return;
  }
  else {
    if ((token = strchr (string, ',')) == NULL) {
      /* only margin width, height are set by user*/
      *mheight = (Dimension) atoi (string);
      *mwidth = (Dimension) atoi (string);
#ifdef DEBUG
      printf ("Move incr: %d, margin h: %d, margin w: %d\n",
	      (int) POSMOVE, (int) *mheight, (int) *mwidth);
      fflush (stdout);
#endif
      return;
    }
    else {
      /* both move increment and margin height, width are set by user */
      strncpy (buf, string, token - string);
      *mheight = *mwidth = (Dimension) atoi (buf);
      POSMOVE = (Position) atoi (++token);
#ifdef DEBUG
      printf ("Move incr: %d, margin h: %d, margin w: %d\n",
	      (int) POSMOVE, (int) *mheight, (int) *mwidth);
      fflush (stdout);
#endif
      return;
    }
  }
}
      
      
    
