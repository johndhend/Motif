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
static char rcsid[] = "$XConsortium: OptionMenu2.c /main/10 1995/07/13 18:49:15 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define MAX_BUTTONS 35

#include <testlib.h>
#include "bitmaps/circles1.bmp"

#define XBMu_BITS        circles1_bits
#define XBMu_WIDTH       circles1_width
#define XBMu_HEIGHT      circles1_height
#include "bitmaps/gnu.bmp"

#define XBMgnu_BITS        gnu_bits
#define XBMgnu_WIDTH       gnu_width
#define XBMgnu_HEIGHT      gnu_height

Pixmap pixmap, gnu_pixmap;
Widget PullDown1, Label1, Separator1, ShortBtn1, MediumBtn2, Separator2;
Widget HackBtn3, JedBtn4, Separator3, OptionMenu1;
Widget PushBtn1, PushBtn2, PushBtn3, CascadeBtn1;
Widget submenu1, myButton, bboard, bboard2;
Widget push_btns1[MAX_BUTTONS];

char *btn_labels1[MAX_BUTTONS] = {
	"PushButton11",
	"PushButton12",
	"PushButton13",
	"PushButton14",
	"PushButton15",
	"PushButton16",
	"PushButton17",
	"PushButton18",
	"PushButton19",
	"**********PushButton110**********",
	"PushButton111",
	"PushButton112",
	"PushButton113",
	"PushButton114",
	"PushButton115",
	"PushButton116",
	"PushButton117",
	"PushButton118",
	"PushButton119",
	"**********PushButton120**********",
	"PushButton121",
	"PushButton122",
	"PushButton123",
	"PushButton124",
	"PushButton125",
	"PushButton126",
	"PushButton127",
	"PushButton128",
	"PushButton129",
	"**********PushButton130**********",
	"PushButton131",
	"PushButton132",
	"PushButton133",
	"PushButton134",
	"PushButton135",
	};

static Widget CreateLabel(char *label, Widget parent)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  n = 0;
  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
  XtSetArg(args[n], XmNlabelString, tcs);  n++;
  widget = XmCreateLabel(parent, label, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

static Widget CreatePushButton(char *label, char mnemonic, Widget parent)
{
    Widget widget;
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
    widget = XmCreatePushButton(parent, label, args, n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}

static Widget CreatePushButtonGadget(char *label, char mnemonic, Widget parent)
{
    Widget widget;
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs;

    n = 0;
    tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);  n++;
    XtSetArg(args[n], XmNmnemonic, mnemonic);  n++;
    widget = XmCreatePushButtonGadget(parent, label, args, n);
    XtManageChild(widget);
    XmStringFree(tcs);

    return(widget);
}

static Widget CreateSeparator(Widget parent, char *name)
{
    Widget widget;
    widget = XmCreateSeparator(parent, name, NULL, 0);
    XtManageChild(widget);
    return(widget);
}

static Widget CreatePullDown(Widget parent, char *name)
{
    Widget widget;
    widget = XmCreatePulldownMenu (parent, name, NULL, 0);
    return(widget);
}

int main(int argc, char **argv)
{
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs;
    XFontStruct *newfont;
    XmFontList newfontlist;
    Widget Frame;
    int num_buttons, i;

    CommonTestInit(argc, argv);

    if (UserData) 
	num_buttons = atoi(UserData);
    else
	num_buttons = MAX_BUTTONS;

    if ((newfont = XLoadQueryFont(display, "8x13bold")) == NULL)
      {
	fprintf(stderr, "Exiting, font 8X13 Bold not available\n");
	fflush(stderr);
	exit(1);
      }

    newfontlist = XmFontListCreate(newfont, XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNwidth,  200);  n++;
    XtSetArg(args[n], XmNheight, 40);   n++;
    XtSetArg(args[n], XtNgeometry, "+0+50");  n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);

    n = 0;
    bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);
    XtManageChild(bboard);

    /*
    **  PullDown1
    */

    PullDown1 = CreatePullDown(bboard, "PullDown1");

    /*
    **  Menu1
    */

    Label1        = CreateLabel("Menu1", PullDown1);

    Separator1    = CreateSeparator(PullDown1, "Separator1");

    ShortBtn1     = CreatePushButtonGadget("Short", 'T', PullDown1);

    MediumBtn2    = CreatePushButtonGadget("MediumLength", 'P', PullDown1);

    Separator2    = CreateSeparator(PullDown1, "Separator2");

    HackBtn3      = CreatePushButton
                    ("ExperienceHackerungnen", 'u', PullDown1);

    JedBtn4       = CreatePushButton
                    ("TennesseeJed", 'o', PullDown1);

    Separator3    = CreateSeparator(PullDown1, "Separator3");

    /*
    **  OptionMenu1
    */

    n = 0;
    tcs = XmStringLtoRCreate("Option: ", XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, tcs);         n++;
    XtSetArg(args[n], XmNmnemonic,    'o');         n++;
    XtSetArg(args[n], XmNsubMenuId,   PullDown1);   n++;
    XtSetArg(args[n], XmNmenuHistory, HackBtn3);    n++; 
    XtSetArg(args[n], XmNwhichButton, 3);	    n++;
    OptionMenu1 = XmCreateOptionMenu(bboard, "optionMenu", args, n);
    XtManageChild(OptionMenu1);
    XmStringFree(tcs);
    
    CommonPause();   /* now change some buttons to pixmaps */
   
    XtUnmanageChild(MediumBtn2);
    XtUnmanageChild(ShortBtn1);
 
    pixmap =XCreatePixmapFromBitmapData(display,
			     DefaultRootWindow(display),
			     XBMu_BITS, XBMu_WIDTH,XBMu_HEIGHT,
			     WhitePixel(display,DefaultScreen(display)),
                             BlackPixel(display,DefaultScreen(display)),
                             DefaultDepth(display,DefaultScreen(display)));

    gnu_pixmap =XCreatePixmapFromBitmapData(display,
            DefaultRootWindow(display),
            XBMgnu_BITS, XBMgnu_WIDTH,XBMgnu_HEIGHT,
            WhitePixel(display,DefaultScreen(display)),
            BlackPixel(display,DefaultScreen(display)),
            DefaultDepth(display,DefaultScreen(display)));

    n = 0;
    XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
    XtSetArg(args[n], XmNlabelPixmap, gnu_pixmap); n++;
    XtSetValues(MediumBtn2, args, n);

    n = 0;
    XtSetArg(args[n], XmNlabelType, XmPIXMAP); n++;
    XtSetArg(args[n], XmNlabelPixmap, pixmap); n++;
    XtSetValues(ShortBtn1, args, n);

    XtManageChild(MediumBtn2);
    XtManageChild(ShortBtn1);

    CommonPause();

    /* test case for CR 5474. The labelPixmap should still be displayed
       even when the OptionMenu is set insensitive. */

    n=0;
    XtSetArg (args[n], XmNsensitive, False); n++;
    XtSetValues (OptionMenu1,args,n);

    CommonPause();

    /* end test for CR 5474. */

    /*
     *  Now change the shadow thickness
     */

    myButton = XmOptionButtonGadget(OptionMenu1);
    n = 0;
    XtSetArg (args[n], XmNshadowThickness, 4); n++;
    XtSetValues (myButton, args, n);

    CommonPause();

    /*
     *  Put up a VERY big OptionMenu
     */

    XtDestroyWidget(PullDown1);
    XtDestroyWidget(OptionMenu1);

    /*
     *  PullDown1
     */

    PullDown1 = CreatePullDown(bboard, "PullDown1");

    /*
     *  Menu1
     */

    Label1        = CreateLabel("Menu1", PullDown1);

    Separator1    = CreateSeparator(PullDown1,"Separator1");

    for (i = 0; i < num_buttons; i++)
	push_btns1[i] = CreatePushButton(btn_labels1[i], 'n', PullDown1);

    Separator3  = CreateSeparator(PullDown1, "Separator3");

    /* just for fun, put another manager in between */
    
    n = 0;
    bboard2 = XmCreateBulletinBoard (bboard, "bboard2", args, n);
    XtManageChild(bboard2);

    /*
     *  OptionMenu1
     */

    tcs = XmStringLtoRCreate("Option: ", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg(args[n], XmNlabelString, tcs);         	n++;
    XtSetArg(args[n], XmNmnemonic,    'O');         	n++;
    XtSetArg(args[n], XmNsubMenuId,   PullDown1);   	n++;
    XtSetArg(args[n], XmNmenuHistory, push_btns1[1]);  	n++; 
    XtSetArg(args[n], XmNwhichButton, 3);	    	n++;
    OptionMenu1 = XmCreateOptionMenu(bboard2, "optionMenu", args, n);
    XtManageChild(OptionMenu1);
    XmStringFree(tcs);
    
    PushBtn1      = CreatePushButton("PushButton1", 't', PullDown1);

    PushBtn3      = CreatePushButton("*********PushButton3**********", '*',
				     PullDown1);

    CommonPause();

    XtAppMainLoop(app_context);
}
