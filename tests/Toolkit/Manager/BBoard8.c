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
static char rcsid[] = "$XConsortium: BBoard8.c /main/4 1995/07/13 18:27:35 drk $"
#endif
#endif
    
#include <testlib.h>

Widget option;
    
static int caseNumber = 0;

static void DoCase(w)
Widget w;
{
    switch(caseNumber)  {
      case 0:
	printf("Add one\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Add one", NULL, 0));
	break;
      case 1:
	printf("Add Two\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Add Two", NULL, 0));
	break;
      case 2:
	printf("Unmanage Option Label\n");
	XtUnmanageChild(XmOptionLabelGadget(option));
	break;
      case 3:
	printf("Add Three\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Add Three", NULL, 0));
	break;
      case 4:
	printf("Add four\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Add four", NULL, 0));
	break;
      case 5:
	printf("Adding five\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Adding five", NULL, 0));
	break;
      case 6:
	printf("Add six\n");
	XtManageChild(XmCreatePushButtonGadget(w, "Add six", NULL, 0));
	break;
      defaults:
	exit(0);
    }	
    caseNumber++;
}


main(argc, argv)
int argc;
char *argv[];
{
    Widget BulletinBoard1, Pulldown1, pb[3];
    Arg args[MAX_ARGS];
    int n, i;
    char str[8];

    CommonTestInit(argc, argv);
        
    n=0;
    XtSetArg(args[n],XmNallowShellResize, True);	n++;
    XtSetArg(args[n],XmNwidth, 400); 			n++;
    XtSetArg(args[n],XmNheight, 300); 			n++;
    XtSetValues(Shell1, args, n);
    
    n=0;
    BulletinBoard1 = XmCreateBulletinBoard(Shell1, "BulletinBoard1", args, n);
    
    n=0;
    Pulldown1 = XmCreatePulldownMenu(BulletinBoard1, "Pulldown1", args, n);
    for (i = 0; i < 3; i++)  {
	n = 0;
	sprintf(str, "PUSH%d", i+1);
	pb[i] = XmCreatePushButtonGadget(Pulldown1, str, args, n);
    }	
    XtManageChildren(pb, 3);
    
    n=0;
    XtSetArg(args[n], XmNsubMenuId, Pulldown1);		n++;
    option = XmCreateOptionMenu(BulletinBoard1, "option", args, n);
    
    XtManageChild(BulletinBoard1);
    XtManageChild(option);

    XtRealizeWidget(Shell1);

    for(i=0; i<7; i++)  {
	DoCase(Pulldown1);
	CommonPause();
    }

    CommonPause();

    XtAppMainLoop(app_context);
}
