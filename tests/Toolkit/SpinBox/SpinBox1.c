/* $XConsortium: SpinBox1.c /main/5 1995/07/15 21:09:44 drk $ */
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


#include "testlib.h"



#define match(a,b) strcmp(a,b)==0
#define NUM_ITEM 5

void
main(int argc, char **argv)
{

  Arg args[10];
  int n,a,i;
  char buf[16];

  Widget TextF1,TextF2;
  Widget Parent;
  Widget SpinBox;

		     
  

  CommonTestInit(argc,argv);

   if (UserData == NULL)
     a=1;
	
    else
      {
    if (match (UserData,"1")) 
	  a=1;
	else if (match (UserData,"2")) 
	  a=2;
	else if (match (UserData,"3")) 
	  a=3;
	else if (match (UserData,"4")) 
	  a=4;
  }

	Parent = XmCreateFrame(Shell1, "Parent", NULL, 0);
	XtManageChild (Parent);


        sprintf (buf, "SpinBox%d", a);
	SpinBox  = XmCreateSpinBox(Parent, buf, NULL,0);
        XtManageChild (SpinBox);

        
        TextF1 = XmCreateTextField (SpinBox, "TextF1", NULL, 0);
        XtManageChild (TextF1);

        TextF2 = XmCreateTextField (SpinBox, "TextF2", NULL, 0);
        XtManageChild (TextF2);


        XtRealizeWidget (Shell1);

        CommonPause();
        CommonPause();
	XtAppMainLoop (app_context);
}
