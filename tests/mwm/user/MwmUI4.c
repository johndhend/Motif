/* $XConsortium: MwmUI4.c /main/5 1995/07/15 21:14:17 drk $ */
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

#define NUM_WINDOWS 12

void
main (int argc, char **argv)
{
  Widget TestShell1, TestShell2, TestShell3;
  Widget TopLevelShell[10];
  Widget PB1, PB2, PB3;
  Widget TopLevelPB[10];
  Widget MesDialog1;
  Widget Text1;
  int n,i;
  Arg args[10];
  char buf[32];

  CommonTestInit(argc,argv);


  n=0;
  XtSetArg (args[n], XmNheight, 200); n++;
  XtSetArg (args[n], XmNwidth, 200); n++;
  TestShell1 = XtCreatePopupShell ("TestWindow1",
				 topLevelShellWidgetClass,
				 Shell1, args, n);

  n=0;
  PB1 = XmCreatePushButton (TestShell1, "PB1", args, n);
  XtManageChild (PB1);

  XtPopup (TestShell1,XtGrabNone);

  CommonPause();


  n=0;
  XtSetArg (args[n], XmNheight, 200); n++;
  XtSetArg (args[n], XmNwidth, 200); n++;
  TestShell2 = XtCreatePopupShell ("TestWindow2", 
				 topLevelShellWidgetClass,
				 Shell1, args, n);

  n=0;
  PB2 = XmCreatePushButton (TestShell2, "PB2", args, n);
  XtManageChild (PB2);

  XtPopup (TestShell2,XtGrabNone);


  n=0;
  XtSetArg (args[n], XmNheight, 200); n++;
  XtSetArg (args[n], XmNwidth, 200); n++;
  TestShell3 = XtCreatePopupShell ("TestWindow3", 
				 topLevelShellWidgetClass,
				 Shell1, args, n);

  n=0;
  PB3 = XmCreatePushButton (TestShell3, "PB3", args, n);
  XtManageChild (PB3);

  XtPopup (TestShell3,XtGrabNone);



  CommonPause();

  
  n=0;
  MesDialog1= XmCreateMessageDialog (TestShell1,"MesDialog1",
                                     args, n);
  XtManageChild (MesDialog1);
  
  CommonPause();
  CommonPause();

  

  


  CommonPause();
  CommonPause();
  CommonPause();
  CommonPause();
  CommonPause();

  XtAppMainLoop (app_context);

}

