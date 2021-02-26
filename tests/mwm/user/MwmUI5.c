/* $XConsortium: MwmUI5.c /main/4 1995/07/15 21:14:21 drk $ */
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

typedef struct _test_dialog_rec *test_dialog;
typedef struct _test_dialog_rec {
    Widget          form_dialog;
    Widget          test_button;
    Widget          ok_button;
    test_dialog     the_test_dialog;
} test_dialog_rec;

Widget              toplevel;
test_dialog         the_test_dialog;
static int          dialog_id = 0;

static test_dialog  test_dialog_create ();
static void         test_dialog_manage ();
static void         test_dialog_unmanage ();


unsigned int main (argc, argv)
    int argc;
    char         *argv[];
{
    Widget       TestShell1;
    XmString     label_string;
    Arg          args[10];
    int          n;

    CommonTestInit (argc,argv);


    n = 0;
    XtSetArg (args[n], XmNallowShellResize, True); n++;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    the_test_dialog = test_dialog_create (Shell1);

    n=0;
    XtSetArg (args[n], XmNwidth, 100); n++;
    XtSetArg (args[n], XmNheight, 100); n++;
    TestShell1 = XtAppCreateShell ("TestWindow1", "TestWindow1",
                                   topLevelShellWidgetClass,
                                   display, args, n);

    XtRealizeWidget (TestShell1);
    CommonPause();
    CommonPause();
    XtAppMainLoop (app_context);
}


static void activate_proc (widget, the_dialog)
    Widget      widget;
    test_dialog the_dialog;
{
    if (widget == the_dialog->test_button)
    {
        if (the_dialog->the_test_dialog == NULL)
        {
            the_dialog->the_test_dialog = test_dialog_create
(the_dialog->form_dialog);
        }
        test_dialog_manage (the_dialog->the_test_dialog);
    }
    else if (widget == the_dialog->ok_button)
    {
        test_dialog_unmanage (the_dialog);
    }
}


static test_dialog test_dialog_create (parent)
  Widget parent;
{
    Arg         args[20];
    int         n;
    test_dialog the_dialog;
    the_dialog = (test_dialog) XtMalloc(sizeof(test_dialog_rec));
    the_dialog->the_test_dialog = NULL;
    dialog_id++;
    {
        char     id_string[20];
        XmString dialog_title;
        sprintf(id_string, "Form%d", dialog_id);
        dialog_title = XmStringCreate(id_string, XmSTRING_DEFAULT_CHARSET);
        n = 0;
        XtSetArg (args[n], XmNautoUnmanage, False); n++;
        XtSetArg (args[n], XmNdialogTitle, dialog_title); n++;
        the_dialog->form_dialog = (Widget) XmCreateFormDialog (
            parent,
            id_string,
            args, n);
        XtManageChild (the_dialog->form_dialog);
    }
    n = 0;
    the_dialog->test_button = XmCreatePushButtonGadget (
        the_dialog->form_dialog,
        "Make Child",
        args, n);
    XtManageChild (the_dialog->test_button);
    XtAddCallback (the_dialog->test_button, XmNactivateCallback, activate_proc,
the_dialog);
    n = 0;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
    XtSetArg(args[n], XmNtopWidget, the_dialog->test_button); n++;
    the_dialog->ok_button = XmCreatePushButtonGadget (
        the_dialog->form_dialog,
        "Destroy Me",
        args, n);
    XtManageChild (the_dialog->ok_button);
    XtAddCallback (the_dialog->ok_button, XmNactivateCallback, activate_proc,
the_dialog);
    return (the_dialog);
}
static void test_dialog_manage (the_dialog)
    test_dialog the_dialog;
{
    XtManageChild(the_dialog->form_dialog);
}
static void test_dialog_unmanage (the_dialog)
    test_dialog the_dialog;
{
    /*
    **  Now unmanage this form.
    */
    XtUnmanageChild(the_dialog->form_dialog);
}


