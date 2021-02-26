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
static char rcsid[] = "$XConsortium: ErrorDia1.c /main/8 1995/07/13 18:56:51 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <signal.h>

#include <X11/StringDefs.h>


#include <testlib.h>

static Widget message1, message2;

void
DestroyCall(w, client, call)
    Widget w;
    XtPointer client, call;
{
    printf("Destroyed MessageBox\n");
}

void
MapFunction (w,d1,d2)
    Widget w;
    XtPointer d1;
    XtPointer d2;
{
    static int test = 0;

    switch (test) {
	case 0: XtManageChild (message1);
		test++;
		break;
	case 1: XtManageChild (message2);
		test = 0;
		break;
    }
}

void
UnmapFunction (w,d1,d2)
    Widget w;
    XtPointer d1;
    XtPointer d2;
{
    XtUnmanageChild (w);
    printf ("Enter Message 1 \n");
}

void
UnmapFunction2 (w,d1,d2)
    Widget w;
    XtPointer d1;
    XtPointer d2;
{
    XtUnmanageChild (w);
    printf ("Cancel Message 2 \n");
}

void
UnmapFunction3 (w,d1,d2)
    Widget w;
    XtPointer d1;
    XtPointer d2;
{
    XtUnmanageChild (w);
    printf ("Enter Message 2 \n");
}

void main (argc, argv)
int argc;
char **argv;

{
    Widget w2;


    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
 
    w2 = XmCreatePushButton (Shell1, "mapbutton", NULL, 0);
    XtManageChild (w2);

    message1 = XmCreateErrorDialog(w2, "message1", NULL, 0);

    XtAddCallback (w2, XmNactivateCallback, MapFunction, NULL);

    XtAddCallback (message1, XmNdestroyCallback, DestroyCall, NULL);
    XtAddCallback (message1, XmNokCallback, UnmapFunction, NULL);

    message2 = XmCreateErrorDialog(w2, "message2", NULL, 0);

    XtAddCallback (message2, XmNokCallback, UnmapFunction3, NULL);
    XtAddCallback (message2, XmNcancelCallback, UnmapFunction2, NULL);

    XtRealizeWidget(Shell1);

    CommonPause();

    XtDestroyWidget(message1);

    CommonPause();

    /* begin test for PIR 3698 */

    message1 = XmCreateErrorDialog(w2, NULL, NULL, 0);
    XtManageChild (message1);

    CommonPause();

    /* end test for PIR 3698 */

    XtAppMainLoop(app_context);
}
