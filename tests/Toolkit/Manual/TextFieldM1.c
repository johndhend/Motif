/* $XConsortium: TextFieldM1.c /main/4 1995/07/15 21:06:32 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
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
 * 
 */
/*
 * HISTORY
 */
#include <testlib.h>

#define MANAGER_WIDTH  300
#define MANAGER_HEIGHT 300
#define MARGIN         10
#define TEXT_WIDTH     (MANAGER_WIDTH/2 - 2*MARGIN)
#define TEXT_HEIGHT    (MANAGER_HEIGHT/2 - 2*MARGIN)

static char string1[] = "\
abcdefghijklmnopqrstuvwxyz\n\
0123456789\n\
abcdefghijklmnopqrstuvwxyz\n\
0123456789\n\
Jan. Feb. Mar. Apr. May Jun. Jul. Aug. Sep. Oct. Nov. Dec."; 

void main (argc, argv) 
int argc; 
char **argv;
{
	int     n = 0;
	Arg     args[MAX_ARGS];
	Widget  BBoard1, Text1;

	CommonTestInit( argc, argv );

 	n = 0;	
	XtSetArg( args[n], XmNwidth, MANAGER_WIDTH ); n++;
	XtSetArg( args[n], XmNheight, MANAGER_HEIGHT ); n++;
	BBoard1 = XmCreateBulletinBoard( Shell1, "BBoard1", args, n );
	XtManageChild( BBoard1 );

      /*
       *  Create an XmTextField widget and destroy it prior to
       *  ever realizing it.
       */
	n = 0;
	XtSetArg( args[n], XmNx, MARGIN ); n++;
	XtSetArg( args[n], XmNy, MARGIN ); n++;
	XtSetArg( args[n], XmNwidth, MANAGER_WIDTH - 2 * MARGIN ); n++;
	XtSetArg( args[n], XmNheight, MANAGER_HEIGHT - 2 * MARGIN ); n++;
	XtSetArg( args[n], XmNvalue, string1 ); n++;
	XtSetArg( args[n], XmNeditable, False ); n++;
	Text1 = XmCreateTextField( BBoard1, "Text1", args, n );
	XtManageChild( Text1 );
	
	XtDestroyWidget( Text1 );

     	XtRealizeWidget(Shell1);

	CommonPause();
	CommonPause();
	XtAppMainLoop( app_context );
}
        
	
