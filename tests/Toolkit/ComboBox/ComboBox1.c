/* $XConsortium: ComboBox1.c /main/6 1996/07/26 10:56:31 jakku $ */
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





/* This test takes all its resources from the resource file ComboBox.defaults
   in the ./tests/Toolkit/ComboBox directory. The test should be passed
   a flag (a number from 1-3), which will determine the XtName of the
   ComboBox widget created. This name then determines what resources
   are set for the ComboBox. The resource file contains 3 set of resources
   for this test */


#include <testlib.h>
#include <Xm/ComboBox.h>


#define match(a,b) strcmp(a,b)==0

void
main (int argc, char **argv)
{
	Widget Parent;
	Widget CB;
	int i,a;
	char buf[3];

	CommonTestInit(argc,argv);

	/* User specifies an integer from 1-3  which determines the Xt name of
	   the Notebook widget. */

	if (UserData == NULL)
	  {
	    fprintf (stderr, "Usage : ComboBox1 -u <1-3>\n");
	    exit(1);
	  }

	if (match (UserData,"1")) 
	  a=1;
	else if (match (UserData,"2")) 
	  a=2;
	else if (match (UserData,"3")) 
	  a=3;
	else if (match (UserData, "4"))
	  a=4;

	Parent = XmCreateForm(Shell1, "Parent", NULL, 0);
	XtManageChild (Parent);

	/* determine Xt Name of ComboBox and create ComboBox */

	sprintf (buf, "CB%d", a);
	CB  = XmCreateComboBox (Parent, buf, NULL, 0);
	XtManageChild (CB);

	XtRealizeWidget (Shell1);

	CommonPause();

	XtAppMainLoop (app_context);
      }







