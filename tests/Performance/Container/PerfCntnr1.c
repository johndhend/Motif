/* $XConsortium: PerfCntnr1.c /main/5 1995/07/15 21:01:00 drk $ */
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


#include <testlib.h>
#include <math.h>

#define NUM_OBJ 700

void
main(int argc, char **argv)
{
    
    Widget		ScrolledW, Frame, Container, *IconGad;
    int			i,j;
    Cardinal		n, N, num_obj;
    Arg			args[MAX_ARGS];
    Cardinal            test_num;
    XmString            icon_name;

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
    }
    else {
       n = 0;
       Container= XmCreateContainer(Shell1, "Container", args, n);
    }
      
    XtManageChild(Container);
    
    /* take the cube root of num_obj and compute the real num_obj */
    N = (Cardinal) cbrt ((double)num_obj) ;
    num_obj = N*N*N ; 
    IconGad = (Widget*) XtMalloc(num_obj*sizeof(Widget));


    for (i = 0; i < num_obj; i++) {
	char IconName[20] ;

	n = 0 ;
	if (i >= N && i < N*N) {
	    j = i/N - 1 ;
	    XtSetArg(args[n], XmNentryParent, IconGad[j]); n++;
	    sprintf(IconName,"%s%d", XtName(IconGad[j]),(i%N)+1);
	} else if (i > N) {
	    j = i/N ;
	    XtSetArg(args[n], XmNentryParent, IconGad[j]); n++;
	    sprintf(IconName,"%s%d", XtName(IconGad[j]),(i%N)+1);
	} else {
	    sprintf(IconName, "IconGad%d", i+1);
	}

	icon_name = XmStringCreate(IconName, XmSTRING_DEFAULT_CHARSET); 
	XtSetArg(args[n], XmNlabelString, icon_name); n++;
	IconGad[i] = XmCreateIconGadget(Container, IconName, args, n);
    }
    XtManageChildren(IconGad,num_obj);

    
    XtRealizeWidget(Shell1);
    
    CommonPause();

    XtAppMainLoop(app_context);
    
}


