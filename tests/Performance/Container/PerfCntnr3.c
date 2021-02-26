/* $XConsortium: PerfCntnr3.c /main/6 1996/10/07 15:10:13 drk $ */
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

#include <testlib.h>

#define NUM_OBJ 1000

void IncrBottomCB(Widget, XtPointer, XtPointer);
void DecrTopCB(Widget, XtPointer, XtPointer);
void IncrRightCB(Widget, XtPointer, XtPointer);
void DecrLeftCB(Widget, XtPointer, XtPointer);

static void     PrintLapseTime();

struct timeval  incr_to_bottom_time[2];
struct timeval  decr_to_top_time[2];
struct timeval  incr_to_right_time[2];
struct timeval  decr_to_left_time[2];


void Quit(Widget w, XtPointer client_data, XtPointer call_data)
{

    printf("Time elapsed to scroll to the bottom:\n");
    PrintLapseTime(&incr_to_bottom_time[0], &incr_to_bottom_time[1]);
    printf("Time elapsed to scroll to the top:\n");
    PrintLapseTime(&decr_to_top_time[0], &decr_to_top_time[1]);
    printf("Time elapsed to scroll to the right:\n");
    PrintLapseTime(&incr_to_right_time[0], &incr_to_right_time[1]);
    printf("Time elapsed to scroll to the left:\n");
    PrintLapseTime(&decr_to_left_time[0], &decr_to_left_time[1]);

    printf("Begin exiting ... please standby ... \n");
    exit(0);

}


void
main(int argc, char **argv)
{
    
    Widget		ScrolledW, Frame, Container, *IconGad;
    int			i;
    Cardinal		n, num_obj;
    Arg			args[MAX_ARGS];
    Cardinal            test_num;
    char                IconName[20] ;
	Widget	VertScrollB, HorizScrollB;
	int	VertMax, HorizMax, VertMin, HorizMin, VertIncr, HorizIncr;

    CommonTestInit(argc, argv);

    test_num = 0;
    num_obj = NUM_OBJ;
    
    if (UserData != NULL) {
	
	if (strcmp(UserData, "noscroll") == 0)
	    test_num = 1;
	else {
	    n = atoi(UserData);
	    if (n < num_obj)
	      num_obj = n;
	}

	free(UserData);
	
    }

    n = 0;
    XtSetArg(args[n], XmNheight, 320); n++;
    XtSetArg(args[n], XmNwidth, 340); n++;
    XtSetValues(Shell1, args, n);

    /* We want a scrolledwindow because the container window
       can potentially be huge. If we don't want a scrolled 
       window run it with -u noscroll */

    if (test_num != 1) {

       n = 0;
       XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
       ScrolledW = XmCreateScrolledWindow(Shell1, "ScrolledW", args, n);
       XtManageChild(ScrolledW);
    
       /* but we don't want interaction with the scrolling header */
       n = 0;
       Frame= XmCreateFrame(ScrolledW, "Frame", args, n);
       XtManageChild(Frame);
    
       n = 0;
       Container= XmCreateContainer(Frame, "Container", args, n);
	VertScrollB = XtNameToWidget(ScrolledW, "VertScrollBar");
	HorizScrollB = XtNameToWidget(ScrolledW, "HorScrollBar");

	XtAddCallback(VertScrollB, XmNincrementCallback, IncrBottomCB, (XtPointer)&VertMax);
	XtAddCallback(VertScrollB, XmNdecrementCallback, DecrTopCB, (XtPointer)&VertMin);
	XtAddCallback(HorizScrollB, XmNincrementCallback, IncrRightCB, (XtPointer)&HorizMax);
	XtAddCallback(HorizScrollB, XmNdecrementCallback, DecrLeftCB, (XtPointer)&HorizMin);
    }
    else {
       n = 0;
       Container= XmCreateContainer(Shell1, "Container", args, n);
    }
      
    XtManageChild(Container);
	XtAddCallback(Container, XmNselectionCallback, Quit, NULL);
    
    IconGad = (Widget*) XtMalloc(num_obj*sizeof(Widget));

    for (i = 0; i < num_obj; i++) {
	
	sprintf(IconName,"IconGad%d", i);
	IconGad[i] = XmCreateIconGadget(Container, IconName, args, 0);
    }

    XtManageChildren(IconGad, num_obj);

    XtRealizeWidget(Shell1);

    incr_to_bottom_time[0].tv_sec = 0;
    decr_to_top_time[0].tv_sec = 0;
    incr_to_bottom_time[0].tv_sec = 0;
    incr_to_bottom_time[0].tv_sec = 0;

    CommonPause();

    XtAppMainLoop(app_context);
    
}


void IncrBottomCB(Widget w, XtPointer client_data, XtPointer call_data)
{

    struct  timezone    tz;
	XmScrollBarCallbackStruct *cb = (XmScrollBarCallbackStruct *)call_data;
	/* printf("cb->value = %d\n", cb->value); */
	if (cb->value == 1539) {
        gettimeofday(&incr_to_bottom_time[1],&tz);
    } else {
        if (incr_to_bottom_time[0].tv_sec == 0)
            gettimeofday(&incr_to_bottom_time[0],&tz);
    }

}

void DecrTopCB(Widget w, XtPointer client_data, XtPointer call_data)
{

	struct  timezone    tz;
	XmScrollBarCallbackStruct *cb = (XmScrollBarCallbackStruct *)call_data;
	/* printf("cb->value = %d\n", cb->value); */
	if (cb->value == 0) {
        gettimeofday(&decr_to_top_time[1],&tz);
    } else {
        if (decr_to_top_time[0].tv_sec == 0)
            gettimeofday(&decr_to_top_time[0],&tz);
	}

}

void IncrRightCB(Widget w, XtPointer client_data, XtPointer call_data)
{

	struct  timezone    tz;
	XmScrollBarCallbackStruct *cb = (XmScrollBarCallbackStruct *)call_data;
	/* printf("cb->value = %d\n", cb->value); */
	if (cb->value == 1999) {
        gettimeofday(&incr_to_right_time[1],&tz);
    } else {
        if (incr_to_right_time[0].tv_sec == 0)
            gettimeofday(&incr_to_right_time[0],&tz);
	}

}

void DecrLeftCB(Widget w, XtPointer client_data, XtPointer call_data)
{

	struct  timezone    tz;
	XmScrollBarCallbackStruct *cb = (XmScrollBarCallbackStruct *)call_data;
	/* printf("cb->value = %d\n", cb->value); */
	if (cb->value == 0) {
        gettimeofday(&decr_to_left_time[1],&tz);
    } else {
        if (decr_to_left_time[0].tv_sec == 0)
            gettimeofday(&decr_to_left_time[0],&tz);
	}

}

static void PrintLapseTime(first,second)
struct timeval *first, *second;
{
     struct timeval lapsed;

     if (first->tv_usec > second->tv_usec) {
        second->tv_usec += 1000000;
        second->tv_sec--;
     }

     lapsed.tv_usec = second->tv_usec - first->tv_usec;
     lapsed.tv_sec = second->tv_sec - first->tv_sec;

     printf("lapsed time = %ld.%06d sec\n\n",
            (long)lapsed.tv_sec, lapsed.tv_usec%1000000);
     fflush(stdout);

}
