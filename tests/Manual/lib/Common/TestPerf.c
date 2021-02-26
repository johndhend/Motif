/* $XConsortium: TestPerf.c /main/6 1996/10/07 15:13:04 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */

#include <stdio.h>
#include <sys/time.h>

/*  Xt headers  */

#include <X11/Intrinsic.h>
#include <X11/Shell.h>

/*  Xm headers  */

#include <Xm/Xm.h>

#define STARTUP_TIME_MESSAGE "_STARTUP_TIME_MESSAGE"

Boolean startup_time = False;	   /* Measure startup time ?? */
Boolean startup_exit = False;	   /* Measure startup time and exit ?? */

void CommonGetTime();
void CommonPrintTime();

void    CommonCheckEvent(XEvent *event, Widget shell);

struct timeval value_time[10];
static int     num_value_time = 0;
static Atom    time_atom = (Atom) 0;

/*************************************************************************
*									 *
*   This module contains routines for testing Startup Time performance.  *
*                                                                        *
*       CommonCheckEvent  : is for checking event. The first time the    *
*                           application receives an Expose event, this   *
*                           will send a Client message, and measure the  *
*                           time.                                        *
*                           When receiving this Client message back      *
*                           the current time is get again, and           *
*                           information on time cumulation is printed.   *
*       CommonGetTime     : is getting the current time, and store it in *
*                           the "value_time" array.                      *
*       CommonPrintTime   : is printing the time difference between each *
*                           time value of the array.                     *
*                                                                        *
*   An application willing to test its startup time, should do the       *
*   following:                                                           *
*                                                                        *
*     - Call CommonGetTime at the beginning                              *
*                                                                        *
*     - Modify its main loop to call CommonCheckEvent, passing the event *
*       and the shell as parameter.                                      *
*                                                                        *
*   A boolean startup_time can be used to conditionalize these calls.    *
*   A boolean startup_exit can be used to exit after printing the        *
*   startup time.                                                        *
*                                                                        * 
*************************************************************************/


void CommonCheckEvent(XEvent *event, Widget shell)
{
    
    if (event->type == Expose) {
	XClientMessageEvent xmessage;
	static Boolean first = True;

	if (!first)
	    return;

	first = False;

	time_atom = XInternAtom(XtDisplay(shell), STARTUP_TIME_MESSAGE, False);

	CommonGetTime();

	xmessage.type = ClientMessage;
	xmessage.serial = 0;
	xmessage.send_event = TRUE;
	xmessage.display = XtDisplay(shell);
	xmessage.window = XtWindow(shell);
	xmessage.message_type = time_atom;
	xmessage.format = 8;
	xmessage.data.b[0] = 'z';

	XSendEvent(XtDisplay(shell), XtWindow(shell),  
		   FALSE, NoEventMask, (XEvent *) &xmessage);    
    }
    else
    
	if (time_atom != (Atom) 0) {
	    XClientMessageEvent *xmessage;

	    xmessage = (XClientMessageEvent *) event;

	    if ((xmessage->type == ClientMessage) && 
		(xmessage->message_type == time_atom)) {
                CommonGetTime();
                CommonPrintTime();
		if (startup_exit)
		    exit(0);
	    }
	}
}

void CommonGetTime()
{
    struct timezone zone_time;

    gettimeofday(&value_time[num_value_time], &zone_time);
    num_value_time++;
}

void CommonPrintTime()
{
     struct timeval first, previous, current, lapsed, cumul;
     int i;
     
     first = value_time[0];

     current = value_time[num_value_time-1];

     if (first.tv_usec > current.tv_usec) {
	 current.tv_usec += 1000000;
	 current.tv_sec--;
     }

     cumul.tv_usec = current.tv_usec - first.tv_usec;
     cumul.tv_sec = current.tv_sec - first.tv_sec;

     printf("\nStartup time : %ld.%06d sec\n",
	    (long)cumul.tv_sec, cumul.tv_usec%1000000);
     fflush(stdout);

/*     for (i = 1; i < num_value_time; i++) {

	 previous = value_time[i-1];
	 current = value_time[i];

	 if (previous.tv_usec > current.tv_usec) {
	     current.tv_usec += 1000000;
	     current.tv_sec--;
	 }

	 lapsed.tv_usec = current.tv_usec - previous.tv_usec;
	 lapsed.tv_sec = current.tv_sec - previous.tv_sec;

	 if (first.tv_usec > current.tv_usec) {
	     current.tv_usec += 1000000;
	     current.tv_sec--;
	 }

	 cumul.tv_usec = current.tv_usec - first.tv_usec;
	 cumul.tv_sec = current.tv_sec - first.tv_sec;

	 printf("\nEllapsed time = %d.%06d sec\t Cumul = %d.%06d sec\n",
                lapsed.tv_sec, lapsed.tv_usec%1000000,
		cumul.tv_sec, cumul.tv_usec%1000000);
     }
*/
}

