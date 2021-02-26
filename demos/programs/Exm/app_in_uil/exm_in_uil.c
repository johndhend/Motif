/* $XConsortium: exm_in_uil.c /main/5 1995/07/15 20:44:21 drk $ */
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

/*******************************************************************************
 *
 * exm_in_uil.c - main routine and C callbacks for exm_in_uil program.
 *
 ******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Mrm/MrmPublic.h>
#include <Exm/ExmMrm.h>

static void ManageCb(Widget, String, XtPointer);
static void ExitCb(Widget, XtPointer, XtPointer);

static MrmHierarchy mrmId;
static MrmCode mrmClass;
static char *mrmFiles[]={"exm_in_uil.uid"};
static MRMRegisterArg mrmNames[] = {
        {"ManageCb", (caddr_t)ManageCb },
        {"ExitCb", (caddr_t)ExitCb }
};

static Display *display;
static Widget shell;

int 
main(int argc,
     char **argv)
{
Widget appMain;
XtAppContext appContext;

    MrmInitialize();
    ExmMrmInitialize();	/* register Exm widgets with Mrm */
    XtToolkitInitialize();
    appContext = XtCreateApplicationContext();
    display = XtOpenDisplay(appContext, NULL, "exmdemo", "ExmDemo", NULL, 0,
                            &argc, argv);
    if (display == NULL) {
	fprintf(stderr, "Can't open display\n");
	exit(1);
    }
    shell = XtAppCreateShell("demo", NULL, applicationShellWidgetClass,
						display, NULL, 0);
    if (MrmOpenHierarchy (1, mrmFiles, NULL, &mrmId) != MrmSUCCESS) 
      exit(1);
    MrmRegisterNames(mrmNames, XtNumber(mrmNames));
    MrmFetchWidget (mrmId, "appMain", shell, &appMain, &mrmClass);
    XtManageChild(appMain);
    XtRealizeWidget(shell);
    XtAppMainLoop(appContext);
    exit(0);
}



/*
 * ManageCb - Manage widget passed as client_data.
 */
static void 
ManageCb(Widget w,
	 String id,
	 XtPointer cb)
{
    XtManageChild (XtNameToWidget(shell, id));
}


/*
 * ExitCb - Exit application.
 */
static void 
ExitCb(Widget w,
       XtPointer cd,
       XtPointer cb)
{
    exit(0);
}
