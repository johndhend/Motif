/* $XConsortium: Color.c /main/4 1995/07/15 21:07:57 drk $ */
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



/* test app context destroy */

#include <testlib.h>


static void gobyebye();

int quitflag = 0;


/* test case for CR 2761. */

void main(argc, argv)
int argc;
char **argv;
{
	Widget fm;
	Widget pb;
	Arg args[32];
	int n, x, y;


	CommonTestInit (argc,argv);


	/* form */

	n=0;
	XtSetArg(args[n],XmNwidth,100); n++;
	XtSetArg(args[n],XmNheight,100); n++;
	fm = XmCreateForm(Shell1,"fm",args,n);

	/* add push button */

	n = 0;
	XtSetArg(args[n],XmNx,20); n++;
	XtSetArg(args[n],XmNy,20); n++;
	XtSetArg(args[n],XmNwidth,60); n++;
	XtSetArg(args[n],XmNheight,60); n++;
	pb = XmCreatePushButton(fm,"bye",args,n);
	XtAddCallback(pb, XmNactivateCallback, gobyebye, NULL);

	/* manage, realize, loop */

	XtManageChild(pb);
	XtManageChild(fm);

	XtRealizeWidget(Shell1);






	CommonPause();





}

static void
gobyebye(w, client, closure)
    Widget w;
    caddr_t client, closure;
{
	XtDestroyApplicationContext(app_context);
	printf ("exiting\n");
	exit(0);

}

