/* $XConsortium: Label7.c /main/4 1995/07/15 21:08:12 drk $ */
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


main(argc, argv)
int argc;
char **argv;
{
    XtAppContext apc;
    char *font = "timi12";
    Widget  Label1, Label2, BBoard1;
    int     n;
    Arg     args[10];
    XmString string;


    CommonTestInit( argc, argv );

    n = 0;
    XtSetArg( args[n], XmNwidth, 350 ); n++;
    XtSetArg( args[n], XmNheight, 80 ); n++;
    BBoard1 = XmCreateForm( Shell1, "BBoard1", args, n );
    XtManageChild(BBoard1);

    string = XmStringCreate("(H - XmStringCreate", XmFONTLIST_DEFAULT_TAG);

    n = 0;
    XtSetArg( args[n], XmNfontList, CommonGetFontList(font)); n++;
    XtSetArg( args[n], XmNlabelString, string ); n++;
    XtSetArg( args[n], XmNx, 10); n++;
    XtSetArg( args[n], XmNy, 0); n++;
    XtSetArg( args[n], XmNalignment, XmALIGNMENT_CENTER); n++;
    Label1 = XmCreateLabel(BBoard1, "Label1", args, n ); 

    XmStringFree( string );

    XtManageChild( Label1 );


    XtSetLanguageProc(NULL, NULL, NULL);
    string = XmStringCreateLocalized("(H - XmStringCreateLocalized");

    n = 0;
    XtSetArg( args[n], XmNfontList, CommonGetFontList(font)); n++;
    XtSetArg( args[n], XmNlabelString, string ); n++;
    XtSetArg( args[n], XmNx, 10); n++;
    XtSetArg( args[n], XmNy, 40); n++;
    XtSetArg( args[n], XmNalignment, XmALIGNMENT_CENTER); n++;
    Label2 = XmCreateLabel(BBoard1, "Label2", args, n ); 

    XmStringFree( string );

    XtManageChild(Label2);

    XtRealizeWidget(Shell1);

   /* Test CR 5216 */
    CommonPause();

    XtAppMainLoop(app_context);
}

