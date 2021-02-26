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
static char rcsid[] = "$XConsortium: OptionMenu1.c /main/9 1995/07/13 18:48:46 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#define MY_CHAR_SET	"my_char_set"

Widget PullDown1;
Widget Label1;
Widget Separator1;
Widget PushBtn1;
Widget Separator2;
Widget PushBtn2;
Widget Separator3;
Widget OptionMenu1;
Widget OptionMenu3;
Widget bboard, bboard2;
Widget PushBtn3, PushBtn4, PushBtn5, PushBtn6;
XFontStruct *newfont;
XmFontList newfontlist;

static void ButtonPressed(Widget w, caddr_t call_data, caddr_t client_data)
{
  printf ("Button pressed\n");
}

static Widget CreateLabel(char *label, Widget parent, char *name)
{
  Widget widget;
  register int  n;
  Arg args[MAX_ARGS];
  XmString tcs;

  tcs = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);

  n = 0;
  XtSetArg(args[n], XmNfontList, newfontlist);  	n++;  
  XtSetArg(args[n], XmNlabelString, tcs);  		n++;
  widget = XmCreateLabel(parent, name, args, n);
  XtManageChild(widget);
  XmStringFree(tcs);

  return(widget);
}

static Widget CreatePushButton(char *label, char mnemonic, char *accel,
			       char *accelText, Widget parent, char *name)
{
    Widget widget;
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs, tcs2;

    tcs  = XmStringLtoRCreate(label, XmSTRING_DEFAULT_CHARSET);
    tcs2 = XmStringLtoRCreate(accelText, XmSTRING_DEFAULT_CHARSET); 

    n = 0;
    XtSetArg(args[n], XmNbackground, CommonGetColor("red")); 	n++; 
    XtSetArg(args[n], XmNfontList, newfontlist);  		n++;  
    XtSetArg(args[n], XmNaccelerator, accel); 			n++;
    XtSetArg(args[n], XmNacceleratorText, tcs2);		n++;
    XtSetArg(args[n], XmNlabelString, tcs);  			n++;
    XtSetArg(args[n], XmNmnemonic, mnemonic);  			n++;
    widget = XmCreatePushButton(parent, name, args, n);
    XtManageChild(widget);
    XmStringFree(tcs);
    XmStringFree(tcs2);

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
  Arg args[1];

  XtSetArg (args[0], XmNtearOffModel, XmTEAR_OFF_ENABLED);
  widget = XmCreatePulldownMenu (parent, name, args, 1);
  return(widget);
}

int main(int argc, char **argv)
{
    register int  n;
    Arg args[MAX_ARGS];
    XmString tcs;
    char *char_set;

    CommonTestInit(argc, argv);
    
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

    Label1        = CreateLabel("Menu1", PullDown1, "Label1");
    Separator1    = CreateSeparator(PullDown1, "Separator1");
    PushBtn1      = CreatePushButton("PushButton1",'B', "Ctrl<Key>B",
				     "Ctrl-B", PullDown1, "PushBtn1");
    PushBtn2      = CreatePushButton("PushButton2", 'P', "Ctrl<Key>P",
		    		     "Ctrl-P",PullDown1, "PushBtn2");
    Separator2    = CreateSeparator(PullDown1, "Separator2");
    PushBtn3      = CreatePushButton("PushButton3", 'u', "Ctrl<Key>U",
		    		     "Ctrl-U", PullDown1, "PushBtn3");
    PushBtn4      = CreatePushButton("PushButton4",'o', "Ctrl<Key>O",
				     "Ctrl-O", PullDown1, "PushBtn4");
    PushBtn5      = CreatePushButton("PushButton5",'5', "Ctrl<Key>5",
				     "Ctrl-5", PullDown1, "PushBtn5");
    Separator3    = CreateSeparator(PullDown1, "Separator3");


    /* just for fun, put another manager in between */
    
    n = 0;
    bboard2 = XmCreateBulletinBoard(bboard, "bboard2", args, n);
    XtManageChild(bboard2);

    /*
    **  OptionMenu1
    */

    /* Test code for PIR 2695 */

    tcs = XmStringLtoRCreate("Option: ", MY_CHAR_SET);
    char_set = XtMalloc(sizeof(MY_CHAR_SET) + 1);
    strcpy(char_set, MY_CHAR_SET);

    /* End Test Code for PIR 2695 */

    n = 0;
    XtSetArg(args[n], XmNlabelString, tcs);         n++;
    XtSetArg(args[n], XmNsubMenuId,   PullDown1);   n++;
    XtSetArg(args[n], XmNmenuHistory, PushBtn2);    n++; 
    XtSetArg(args[n], XmNwhichButton, 3);	    n++;
    XtSetArg(args[n], XmNmnemonicCharSet, char_set); n++;
    XtSetArg(args[n], XmNfontList, newfontlist);     n++;  
    OptionMenu1 = XmCreateOptionMenu(bboard, "optionMenu", args, n);
    XtManageChild(OptionMenu1);

    XmStringFree(tcs);

    /* Test code for PIR 2695 */

    XtFree(char_set);

    n = 0;
    XtSetArg(args[n], XmNfontList, newfontlist); n++;
    XtSetValues(XmOptionLabelGadget(OptionMenu1), args, n);

    n = 0;
    XtSetArg(args[n], XmNmnemonicCharSet, &char_set);	n++;
    XtGetValues(OptionMenu1, args, n);

    printf("XmNmnemonicCharSet is %s\n", char_set);
    fflush(stdout);

    /* End Test Code for PIR 2695 */
    
    /*
     * Test Code for PIR 2911 and 2915
     *
     *  PIR 2911 - if an OptionMenu is created with mnemonicCharSet and
     *      not mnemonic, then mnemonicCharSet data is not copied
     *      to the labelGadget
     *
     *  PIR 2915 - if an OptionMenu is created with mnemonicCharSet and
     *      then mnemonic is set via SetValues(), then the underlining
     *      is not performed (charSets do not match).
     */

    n = 0;
    XtSetArg(args[n], XmNmnemonic, 'O'); n++;
    XtSetValues(OptionMenu1, args, n);

    /* End Test Code for PIR 2911 */
    /* End Test Code for PIR 2915 */

    CommonPause();
    CommonPause();
    CommonPause();
    CommonPause();

    XtDestroyWidget(PushBtn1);

    PushBtn1 = CreatePushButton("PushButton1", 'P', "Ctrl<Key>P",
				"Ctrl-P",PullDown1, "PushBtn1");

    PushBtn6 = CreatePushButton("*********PushButton6**********", 
				's', "Ctrl<Key>S", "Ctrl-S",
				PullDown1, "PushBtn6");

    CommonPause();

    n = 0;
    XtSetArg(args[n], XmNadjustLast, False); n++;
    XtSetArg(args[n], XmNpacking, XmPACK_COLUMN); n++;
    XtSetArg(args[n], XmNnumColumns, 2); n++;
    XtSetValues (PullDown1, args, n);

    CommonPause();

#ifndef MOTIF1_1

    /*  Test code for new 1.2 vertical option menus. */

    n = 0;
    XtSetArg(args[n], XmNnumColumns, 1); n++;
    XtSetValues(PullDown1, args, n);

    n = 0;
    XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
    XtSetValues(OptionMenu1, args, n);
    
    CommonPause();

#endif

 /* Test for CR 5598 */
     n = 0;
     tcs = XmStringCreateSimple("PushButton6");
     XtSetArg(args[0], XmNlabelString, tcs); n++;
     XtSetValues(PushBtn6, args, n);
     XmStringFree(tcs);

     CommonPause();
 /* End Test for CR 5598 */

    n = 0;
    XtSetArg(args[n], XmNsubMenuId, NULL);	n++;
    XtSetValues(OptionMenu1, args, n);

    CommonPause();

    XtAppMainLoop(app_context);
    
}
