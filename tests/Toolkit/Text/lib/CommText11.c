/* $TOG: CommText11.c /main/7 1997/10/02 16:02:30 csn $ */
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

/*
 *  Global variables.
 */
Widget drawingAreaW, editorW;

char text_string[] = "\
As I was going to St. Ives\n\
I met a man with seven wives\n\
Each wife had seven sacks,\n\
Each sack had seven cats,\n\
Each cat had seven kits\n\
Kits, cats, sacks, and wives,\n\
How many were going to St. Ives?\n\
\n\
I don't know but...\n\
Jack Sprat could eat no fat\n\
His wife could eat no lean\n\
And so between them both\n\
They licked the platter clean";


void enlarge_it(Widget w, XtPointer client_data, XtPointer call_data)
{
	Dimension	get_width;
	int n;
	Arg args[MAX_ARGS];

	n=0;
	XtSetArg(args[n], XmNwidth, &get_width);  n++; 
	XtGetValues(w, args, n);

	n=0;
	if (get_width == 100)
	{
		XtSetArg(args[n], XmNwidth, 120);  n++; 
		XtSetArg(args[n], XmNheight, 120);  n++; 
	}
	else
	{
		XtSetArg(args[n], XmNwidth, 100);  n++;
		XtSetArg(args[n], XmNheight, 100);  n++;
	}
	XtSetValues(w, args, n);
}

void
QuitCB(widget, string, cb)
Widget widget;
char *string;
caddr_t *cb;
{
  exit(1);
}

void
wxEditorCallback(editorW, editor, editorCB)
     Widget editorW;
     caddr_t *editor;
     XmTextVerifyCallbackStruct *editorCB;
{
  XtRemoveCallback(editorW,XmNvalueChangedCallback,
                   wxEditorCallback,NULL);
}

void
keyPressCB(w,wxWidget,xevent,sendAgain)
     Widget w;
     XtPointer wxWidget;
     XEvent *xevent;
     Boolean *sendAgain;
{
  XtRemoveEventHandler(editorW,
                       KeyPressMask,
                       False,
                       keyPressCB,
                       NULL);
}

void
AddCB(widget, string, cb)
Widget widget;
char *string;
caddr_t *cb;
{
  printf("Add insert handler\n");

  XtInsertEventHandler(editorW,
                       KeyPressMask,
                       False,
                       keyPressCB,
                       NULL,
                       XtListHead);
}

Widget
createEditor(parent, x, y)
     Widget parent;
     Position x, y;
{
  Arg args[20];
  int n, i;
  Widget tmpw;

  n = 0;
  XtSetArg(args[n],XmNx, x); n++;
  XtSetArg(args[n],XmNy, y); n++;
  tmpw = XmCreateScrolledWindow(parent,"WINDOW", args, n);

  n = 0;
  XtSetArg(args[n],XmNwidth, 200); n++;
  XtSetArg(args[n],XmNheight, 200); n++;
  XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
  XtSetArg(args[n],XmNwordWrap, False); n++;
  XtSetArg(args[n],XmNscrollHorizontal, False); n++;
  XtSetArg(args[n],XmNscrollVertical, False); n++;
  XtSetArg(args[n],XmNverifyBell, False); n++;
  XtSetArg(args[n],XmNborderWidth, 0); n++;
  editorW = XmCreateText(tmpw,"EDITOR",args,n);

  XtVaSetValues(editorW,XmNwidth,200,XmNheight,200,NULL);
  XtManageChild(editorW);
  XtManageChild(tmpw);

  return editorW;
}

static char render_tag[] = "render1";

void main_text11 (argc, argv)
     int argc;
     char **argv;
{
	Widget bboard;
	Widget pushbutton;
	Widget pushbutton2;
	Widget text1;
	Arg args[MAX_ARGS];
	XmString string;
	int n;

	XtAccelerators new_accel;
	static char new_accelerators[] =
	"#override Meta<Key>Q:               ArmAndActivate()";
	static char new_accelerators2[] =
	"Meta<Key>Q:               next-page()";

	static XtCallbackRec activateCBs[] =
	{
		{ enlarge_it, NULL },
		{ NULL, NULL },
	};

	CommonTestInit(argc, argv);

	n=0;
	XtSetArg(args[n], XmNmarginWidth, 20);  n++; 
	XtSetArg(args[n], XmNmarginHeight, 20);  n++; 
	bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	string = XmStringLtoRCreate("Push Button 1", XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNactivateCallback, activateCBs);  n++; 
	XtSetArg(args[n], XmNlabelType, XmSTRING);  n++; 
	XtSetArg(args[n], XmNlabelString, string);  n++; 

	pushbutton = XmCreatePushButton(bboard, "pushbutton", args, n); 

	XmStringFree(string);

	new_accel = XtParseAcceleratorTable(new_accelerators);

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	XtSetArg(args[n], XmNy, 140);  n++; 
	string = XmStringLtoRCreate("Push Button 2", XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNactivateCallback, activateCBs);  n++; 
	XtSetArg(args[n], XmNlabelType, XmSTRING);  n++; 
	XtSetArg(args[n], XmNlabelString, string);  n++; 
	XtSetArg(args[n], XmNaccelerators, new_accel);  n++; 

	pushbutton2 = XmCreatePushButton(bboard, "pushbutton2", args, n); 

	XmStringFree(string);

	XtManageChild (bboard);
	XtManageChild (pushbutton);
	XtManageChild (pushbutton2);

	XtRealizeWidget (Shell1);

	XtInstallAccelerators(pushbutton, pushbutton2);


	CommonPause();  

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	XtSetArg(args[n], XmNy, 300);  n++; 
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNvalue, text_string);  n++;
	text1 = XmCreateText(bboard, "text1", args, n);
	XtManageChild (text1);

	/* test case for PIR 2162, PIR 4275 */
	XtInstallAccelerators(text1, pushbutton2);
	/* end of test case for PIR 2162, PIR 4275 */

	CommonPause();  

	XtDestroyWidget(pushbutton);
	XtDestroyWidget(pushbutton2);
	XtDestroyWidget(text1);

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	string = XmStringLtoRCreate("Push Button 1", XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNactivateCallback, activateCBs);  n++; 
	XtSetArg(args[n], XmNlabelType, XmSTRING);  n++; 
	XtSetArg(args[n], XmNlabelString, string);  n++; 

	pushbutton = XmCreatePushButton(bboard, "pushbutton", args, n); 

	XmStringFree(string);

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	XtSetArg(args[n], XmNy, 140);  n++; 
	string = XmStringLtoRCreate("Push Button 2", XmSTRING_DEFAULT_CHARSET);
	XtSetArg(args[n], XmNactivateCallback, activateCBs);  n++; 
	XtSetArg(args[n], XmNlabelType, XmSTRING);  n++; 
	XtSetArg(args[n], XmNlabelString, string);  n++; 

	pushbutton2 = XmCreatePushButton(bboard, "pushbutton2", args, n); 

	XmStringFree(string);

	new_accel = XtParseAcceleratorTable(new_accelerators2);

	n=0;
	XtSetArg(args[n], XmNwidth, 100);  n++; 
	XtSetArg(args[n], XmNheight, 100);  n++; 
	XtSetArg(args[n], XmNy, 300);  n++; 
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg(args[n], XmNvalue, text_string);  n++;
	XtSetArg(args[n], XmNaccelerators, new_accel);  n++; 
	text1 = XmCreateText(bboard, "text1", args, n);

	XtManageChild (pushbutton);
	XtManageChild (pushbutton2);
	XtManageChild (text1);

	XtInstallAccelerators(pushbutton, text1);

	CommonPause();  

        XtDestroyWidget( pushbutton );
        XtDestroyWidget( pushbutton2 );
        XtDestroyWidget( text1 );

       /* Begin testing CR 6142 */
        n = 0;
        XtSetArg( args[n], XmNresizePolicy, XmRESIZE_NONE ); n++;
        XtSetArg( args[n], XmNwidth, 400 ); n++;
        XtSetArg( args[n], XmNheight, 400 ); n++;
        XtSetArg( args[n], XmNmarginHeight, 0 ); n++;
        XtSetArg( args[n], XmNmarginWidth,0 ); n++;
        XtSetArg( args[n], XmNshadowThickness, 0 ); n++;
        XtSetArg( args[n], XmNborderWidth,0 ); n++;
        drawingAreaW = XmCreateDrawingArea( bboard, "window", args, n );
        XtManageChild( drawingAreaW );

        editorW = createEditor(drawingAreaW, 0, 80);

        string = XmStringCreateLtoR( "Add Callback",
                   XmFONTLIST_DEFAULT_TAG );

        n = 0;
        XtSetArg( args[n], XmNx, 100 ); n++;
        XtSetArg( args[n], XmNy, 0 ); n++;
        XtSetArg( args[n], XmNlabelString, string ); n++;
        pushbutton =
          XmCreatePushButton( drawingAreaW, "pushbutton", args, n );
        XtManageChild( pushbutton );

        XtAddCallback(pushbutton, XmNactivateCallback, AddCB, NULL);

        XmStringFree( string );

        CommonPause();


       /*  Reset text in the editor text widget and set font. */
        n = 0;
	XtSetArg( args[n], XmNvalue, "" ); n++;
	XtSetArg( args[n], XmNfontList, CommonGetFontList("12x24")); n++;
        XtSetValues( editorW, args, n );

        CommonPause();
      /*  End testing CR 6142 */

        CommonPause();
	XtAppMainLoop(app_context);
}
