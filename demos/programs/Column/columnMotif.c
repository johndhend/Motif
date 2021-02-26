
#include <localdef.h>

/* simple test program */

#include <stdlib.h>

#include <Xm/Xm.h>
#include <Xm/XmAll.h>
#include <Xm/Column.h>
#include <Xm/DataF.h>
#include <Xm/TabStack.h>


#define phone_width 16
#define phone_height 16
static unsigned char phone_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x04, 0x10, 0x04, 0x10, 0x04, 0x10,
   0x2c, 0x1a, 0x20, 0x02, 0xb0, 0x06, 0x18, 0x0c, 0xa8, 0x0a, 0x0c, 0x18,
   0xa4, 0x12, 0x04, 0x10, 0xfc, 0x1f, 0x00, 0x00};

static int done = 0;

static void quitCB(Widget w, XtPointer client, XtPointer call) 
{
	done = 1;
}

static void pCB(Widget w, XtPointer client, XtPointer call) 
{
	printf ("Widget '%s' got data not matching XmNpicture\n", XtName(w));
}

static void vCB(Widget w, XtPointer client, XtPointer call) 
{
	XmDataFieldCallbackStruct *cbs = (XmDataFieldCallbackStruct*)call;
	printf ("Widget '%s' got data %s\n", XtName(w),cbs->text);
}

static void addCallbacks(Widget df)
{
	XtAddCallback(df, XmNpictureErrorCallback, pCB, NULL);
	XtAddCallback(df, XmNvalidateCallback, vCB, NULL);
}

static void createQuit(Widget quit_parent)
{
	Widget button = XmCreatePushButton(quit_parent, "quit", NULL, 0);
	XtManageChild(button);
	XtAddCallback(button, XmNactivateCallback, quitCB, (XtPointer)NULL);
}

static void createScreen(Widget parent)
{
	Widget top = XmCreatePanedWindow(parent, "pane", NULL,0);

	Widget tab = XmCreateTabStack(top,"tab",NULL,0);

	XtManageChild(XmCreateScrolledText(tab,"explanation",NULL,0));
	
	{
	Widget columnMotif = XmCreateColumn(tab,"columnMotif",NULL,0);
	Widget w;
	Pixel bg;

	XtManageChild(XmCreateTextField(columnMotif, "name", NULL, 0));
	XtManageChild(XmCreateTextField(columnMotif, "address1", NULL, 0));
	XtManageChild(XmCreateTextField(columnMotif, "address2", NULL, 0));
	XtManageChild(XmCreateTextField(columnMotif, "city", NULL, 0));
	XtManageChild(w=XmCreateDataField(columnMotif, "state", NULL, 0));
	addCallbacks(w);
	XtManageChild(w=XmCreateDataField(columnMotif, "zip", NULL, 0));
	addCallbacks(w);
	XtManageChild(w = XmCreateDataField(columnMotif, "phone", NULL, 0));
	addCallbacks(w);

	XtVaGetValues(columnMotif,XmNbackground,&bg,NULL);
	XtVaSetValues(w,XmNentryLabelPixmap,
		XCreatePixmapFromBitmapData(XtDisplay(w),
			DefaultRootWindow(XtDisplay(w)),
			(char*)phone_bits,
			phone_width, phone_height,
			BlackPixelOfScreen(XtScreen(w)),
			bg,
			DefaultDepthOfScreen(XtScreen(w))),
			NULL);

	XtManageChild(columnMotif);
	}

	createQuit(top);

	XtManageChild(tab);
	XtManageChild(top);
}

#define CLASS "Column"

int main (argc,argv)
int  argc;
char *argv[];
{
	XtAppContext app_context;
	Widget app_shell;
	Display *display;

	XtToolkitInitialize ();
	app_context = XtCreateApplicationContext();
	display = XtOpenDisplay (app_context, NULL, argv[0], CLASS,
			NULL, 0, &argc, argv);
	if (!display)
	{
		XtWarning ("can't open display, exiting...");
		exit (0);
	}

	app_shell = XtAppCreateShell (NULL, CLASS,
			applicationShellWidgetClass, display, NULL, 0);
	XtVaSetValues(app_shell,XmNallowShellResize, True, NULL);

	/* create application */
	createScreen(app_shell);
	
	XtRealizeWidget(app_shell);

	/*	Process events, unwrapping correctly.  */
	while (!done)
	{
		XEvent event;
		XtAppNextEvent(app_context, &event);
        	XtDispatchEvent(&event);
	}

	XtDestroyWidget(app_shell);
	XtDestroyApplicationContext(app_context);
	exit(0);
}

