/* $XConsortium: MwmUI3.c /main/5 1995/07/15 21:14:12 drk $ */
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

void 
PushButtonCallback (Widget, XtPointer, XtPointer);

void 
main (int argc, char **argv)
{

	Widget TestShell1, TestShell2, TestShell3, TestShell4;
        Widget PB1, PB2, PB3, PB4;
        Widget MesDialog1;
        Arg args[10];
        int n;

    
        CommonTestInit (argc, argv);

	/* cautionary message to user */

	CommonPause();


        /* Create 4 top level shells */
   
        n=0;
        XtSetArg (args[n], XmNheight, 100);n++;
        XtSetArg (args[n], XmNwidth, 160);n++;
        TestShell1=XtAppCreateShell ("TestWindow1", "TestWindow1",
				topLevelShellWidgetClass,display, args,n);


        n=0;
        PB1 = XmCreatePushButton (TestShell1, "PB1", args, n);
        XtManageChild (PB1);

        XtRealizeWidget (TestShell1);


        
	n=0;
        XtSetArg (args[n], XmNheight, 100);n++;
        XtSetArg (args[n], XmNwidth, 160);n++;
        TestShell2=XtAppCreateShell ("TestWindow2", "TestWindow2",
				topLevelShellWidgetClass,display, args,n);




        
        n=0;
        PB2 = XmCreatePushButton (TestShell2, "PB2", args, n);
        XtManageChild(PB2);
        XtAddCallback (PB2, XmNactivateCallback, PushButtonCallback, NULL);
         
        XtRealizeWidget (TestShell2);


	n=0;
        XtSetArg (args[n], XmNheight, 100);n++;
        XtSetArg (args[n], XmNwidth, 160);n++;
        TestShell3=XtAppCreateShell ("TestWindow3", "TestWindow3",
				topLevelShellWidgetClass,display, args,n);




        
        n=0;
        PB3 = XmCreatePushButton (TestShell3, "PB3", args, n);
        XtManageChild(PB3);

        XtRealizeWidget (TestShell3);


        n=0;
        XtSetArg (args[n], XmNheight, 100);n++;
        XtSetArg (args[n], XmNwidth, 160);n++;
        TestShell4=XtAppCreateShell ("TestWindow4", "TestWindow4",
				topLevelShellWidgetClass,display, args,n);



	n=0;
        PB4 = XmCreatePushButton (TestShell4, "PB4", args, n);
        XtManageChild(PB4);

         
        XtRealizeWidget (TestShell4);

        CommonPause();

        /* have a dialog box pop up */

        n=0;
        MesDialog1=XmCreateMessageDialog (TestShell3, "MesDialog1", args, n);
        XtManageChild (MesDialog1);

    
        CommonPause();
        CommonPause();
        CommonPause();
        CommonPause(); 
        CommonPause();      
        CommonPause();      
        CommonPause();      

       	XtAppMainLoop(app_context);

}

void 
PushButtonCallback (Widget w, XtPointer client_data, XtPointer call_data)
{
    fprintf (stdout, "The button press event has been passed to the client\n");
}
