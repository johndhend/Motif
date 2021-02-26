/* $XConsortium: Notebook2.c /main/5 1995/07/15 21:07:21 drk $ */
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



Widget Parent;
Widget Notebook;
Widget Frame1,Form1,PW1,RC1,BB1,NB1;
Widget MajorTab[3];
Widget MinorTab[2];
Widget StatusArea[5];
Widget FrameKid1;
Widget FormKid[4];
Widget RCKid[4];
Widget BBKid[4];
Widget PWKid[4];
Widget NBKid1;

void
main (int argc, char **argv)

{
  Arg args[10];
  int n,i;
  char buf[16];

Widget Parent;
Widget Notebook;
Widget Frame1,Form1,PW1,RC1,BB1,PB1;
Widget MajorTab[3];
Widget MinorTab[3];
Widget StatusArea[6];
Widget FrameKid1;
Widget FormKid[4];
Widget RCKid[4];
Widget BBKid[4];
Widget PWKid[4];




  CommonTestInit (argc, argv);



  
  /* 
   * Create the parent. 
   */

  n=0;
  Parent = XmCreateFrame (Shell1, "Parent", args, n);
  XtManageChild (Parent);

  n=0;
  Notebook = XmCreateNotebook (Parent, "Notebook", args, n);
  XtManageChild (Notebook);

    
  for (i=0; i< 3; i++)
    {
      n=0;
      sprintf (buf, "MajorTab%d", i+1);
      MajorTab[i] = XmCreatePushButton (Notebook,buf,args,n);
      XtManageChild(MajorTab[i]);
    }
            


  for (i=0; i< 3; i++)
    {
       sprintf (buf, "MinorTab%d", i+1);
       MinorTab[i] = XmCreatePushButton (Notebook,buf,args,n);
       XtManageChild(MinorTab[i]);
    }
        

  for (i=0; i< 7; i++)
     {
       n=0;
       sprintf (buf,"StatusArea%d", i+1);
       StatusArea[i] = XmCreateText (Notebook, buf, args,n);
       XtManageChild(StatusArea[i]);
     }


  /*
   * Create Pages of Notebook
   */

  n=0;
  Frame1 = XmCreateFrame (Notebook, "Frame1", args, n);
  XtManageChild (Frame1);

  n=0;
  Form1 = XmCreateForm (Notebook, "Form1", args, n);
  XtManageChild (Form1);

  n=0;
  RC1 = XmCreateRowColumn (Notebook, "RC1", args, n);
  XtManageChild (RC1);


  n=0;
  PW1 = XmCreatePanedWindow (Notebook, "PW1", args, n);
  XtManageChild (PW1);

  n=0;
  BB1 = XmCreateBulletinBoard (Notebook, "BB1", args, n);
  XtManageChild (BB1);

  n=0;
  PB1 = XmCreatePushButton (Notebook, "PB1", args, n);
  XtManageChild (PB1);

  n=0;
  NB1 = XmCreateNotebook (Notebook, "NB1", args, n);
  XtManageChild (NB1);

  /*
   *   Create kids of pages
   */

   n=0;
   FrameKid1 = XmCreatePushButton (Frame1,"FrameKid1",args,n);
   XtManageChild (FrameKid1);


  for (i=0; i < 4; i++)
    {
      n=0;
      sprintf (buf, "FormKid%d", i+1);
      FormKid[i] = XmCreatePushButton (Form1,buf,args,n);
      XtManageChild (FormKid[i]);
    }

  for (i=0; i < 4; i++)
    {
      n=0;
      sprintf (buf, "RCKid%d", i+1);
      RCKid[i] = XmCreatePushButton (RC1,buf,args,n);
      XtManageChild (RCKid[i]);
    }


  for (i=0; i < 4; i++)
    {
      n=0;
      sprintf (buf, "PWKid%d", i+1);
      PWKid[i] = XmCreatePushButton (PW1,buf,args,n);
      XtManageChild (PWKid[i]);
    }

  for (i=0; i < 4; i++)
    {
      n=0;
      sprintf (buf, "BBKid%d", i+1);
      BBKid[i] = XmCreatePushButton (BB1,buf,args,n);
      XtManageChild (BBKid[i]);
    }

  n=0;
  NBKid1 = XmCreateMessageBox (NB1, "NBKid1", args, n);
  XtManageChild (NBKid1);


  XtRealizeWidget (Shell1);

  CommonPause();
  CommonPause();
  CommonPause();
  CommonPause();
  XtDestroyWidget (Notebook);
  CommonPause();

  /* 
   * destroy the widget 
   */



  CommonPause();

  XtAppMainLoop (app_context);
    
}

  






