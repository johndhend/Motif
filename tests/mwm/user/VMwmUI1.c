/* $XConsortium: VMwmUI1.c /main/5 1995/07/15 21:14:25 drk $ */
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
#include <testlib.h>



void 
main (int argc, char **argv)
{

	Widget TestShell1, TestShell2; 
        Widget PB1, PB2;
        Arg args[10];
        int n;
    
        CommonTestInit (argc, argv);
	XtRealizeWidget (Shell1);
	

   
        n=0;
        XtSetArg (args[n], XtNheight, 200);n++;
        XtSetArg (args[n], XtNwidth, 200);n++;
        TestShell1=XtCreatePopupShell("TestWindow1", 
				      topLevelShellWidgetClass,
				      Shell1,args,n);


        n=0;
        PB1 = XmCreatePushButton (TestShell1, "PB1", args, n);
        XtManageChild (PB1);

	XtPopup (TestShell1, XtGrabNone);





 
        n=0;
        XtSetArg (args[n], XtNheight, 200);n++;
        XtSetArg (args[n], XtNwidth, 200);n++;
        TestShell2=XtCreatePopupShell ("TestWindow2", 
				       topLevelShellWidgetClass,
				       Shell1,args,n);




        
        n=0;
        PB2 = XmCreatePushButton (TestShell2, "PB2", args, n);
        XtManageChild(PB2);
        XtPopup(TestShell2, XtGrabNone);

    
	CommonPause();
	CommonPause();
	CommonPause();
        CommonPause();
        CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
        CommonPause();
        CommonPause();
	CommonPause();
        CommonPause();
        CommonPause();
	

        
        
       	XtAppMainLoop(app_context);

}

