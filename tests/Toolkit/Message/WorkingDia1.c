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
static char rcsid[] = "$XConsortium: WorkingDia1.c /main/9 1995/07/13 19:03:51 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*  include files  */
#include <testlib.h>
#include <Xm/XmP.h>

static Pixmap CreatePixmap ();
static Pixmap hourPix = (Pixmap)0;
static char hourBits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07,
   0x40, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00,
   0x00, 0x0e, 0x70, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xf8, 0x1f, 0x00,
   0x00, 0xf0, 0x0f, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0xe0, 0x0f, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0xf0, 0x0f, 0x00, 0x00, 0xe8, 0x1f, 0x00, 0x00, 0xe4, 0x2f, 0x00,
   0x00, 0xf2, 0x5f, 0x00, 0x00, 0xf9, 0x9f, 0x00, 0x80, 0xfd, 0x3f, 0x01,
   0xc0, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Widget mbox;                        /*  MessageBox widget   */

static int destroy = False;
static  XmString str1 = NULL;
static  XmString str2 = NULL;
static  XmString str3 = NULL;
static  XmString str4 = NULL;
static  XmString str5 = NULL;
static  XmString str6 = NULL;


/* callbacks */
static void OkCB();
static XtCallbackRec ok_cb[] = {
    { OkCB, NULL},
    { NULL, NULL}
};
static void CancelCB();
static XtCallbackRec cancel_cb[] = {
    { CancelCB, NULL},
    { NULL, NULL}
};
static void HelpCB();
static XtCallbackRec help_cb[] = {
    { HelpCB, NULL},
    { NULL, NULL}
};


/*#### OkCB ####*/
static void OkCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    child = XmMessageBoxGetChild (w, XmDIALOG_HELP_BUTTON);
    if (child) XtDestroyWidget (child);

    n=0;
    XtSetArg (args[n], XmNhelpLabelString, str1); n++;
    XtSetValues (w, args, n);
}


/*#### CancelCB ####*/
static void CancelCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    child = XmMessageBoxGetChild (w, XmDIALOG_SYMBOL_LABEL);
    if (child) XtDestroyWidget (child);

    n=0;
    XtSetArg (args[n], XmNsymbolPixmap, hourPix); n++;
    XtSetValues (w, args, n);
}


/*#### HelpCB ####*/
static void HelpCB (w, client_data, call_data) 
Widget      w;                           /*  widget id           */
XtPointer     client_data;                 /*  data from application   */
XtPointer     call_data;                   /*  data from widget class  */
{
    Arg          args[10];
    register int n;
    Widget   child=NULL;

    child = XmMessageBoxGetChild (w, XmDIALOG_MESSAGE_LABEL);
    if (child) XtDestroyWidget (child);

    n=0;
    XtSetArg (args[n], XmNmessageString, str1); n++;
    XtSetValues (w, args, n);
}


/*#### main ####*/
void main (argc,argv)
int argc;
char **argv;
{
    Arg             args[MAX_ARGS];
    register int    n;            
    Widget	    Frame;


    /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    
    n = 0;
    XtSetArg (args[n], XmNwidth, 10);                     n++;
    XtSetArg (args[n], XmNheight, 10);                    n++;
    XtSetValues(Shell1, args, n);

    n = 0;
    Frame = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame);
    

    /* create a pixmap */
    hourPix = CreatePixmap (XtScreen(Shell1), hourBits, 32, 32,
                            BlackPixelOfScreen(XtScreen(Shell1)),
                            WhitePixelOfScreen(XtScreen(Shell1)));

    /* create compound string */
    str1 = XmStringCreate ("HelpBtn", XmSTRING_DEFAULT_CHARSET);
    str2 = XmStringCreate ("Symbol", XmSTRING_DEFAULT_CHARSET);
    str3 = XmStringCreate ("Message", XmSTRING_DEFAULT_CHARSET);
    str4 = XmStringCreate ("destroy & set resource", XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNokCallback, ok_cb);                         n++;
    XtSetArg (args[n], XmNcancelCallback, cancel_cb);                 n++;
    XtSetArg (args[n], XmNhelpCallback, help_cb);                     n++;
    XtSetArg (args[n], XmNmessageString, str4);                       n++;
    XtSetArg (args[n], XmNokLabelString, str1);                       n++;
    XtSetArg (args[n], XmNcancelLabelString, str2);                   n++;
    XtSetArg (args[n], XmNhelpLabelString, str3);                     n++;
    XtSetArg (args[n], XmNautoUnmanage, False);                       n++;

    mbox = XmCreateWorkingDialog(Frame, "mbox", args, n);

    XtRealizeWidget (Shell1);
    XtManageChild (mbox);

    CommonPause();

    /*  process events  */
    XtAppMainLoop(app_context);
}


/***********************************************************************
 *
 *  CreatePixmap - This routine will return a pixmap from the output
 *         of the bitmap editor.  The output pixmap will be 
 *         the depth of the screen.  This is so that label can
 *         write it using its current foreground and background.
 *
 ***********************************************************************/

static Pixmap CreatePixmap (screen, bitmap_bits, bitmap_height, bitmap_width,
                foreground_pixel, background_pixel)
Screen *screen;
unsigned short *bitmap_bits;
int     bitmap_height, bitmap_width;
Pixel   foreground_pixel, background_pixel;
{
    register Display *display = DisplayOfScreen (screen);
    XImage image;
    Pixmap pixmap;
    GC gc;
    XGCValues gcValues;

    image.height       = bitmap_height;     /* dimensions */
    image.width        = bitmap_width;

    image.format       = XYBitmap;       /* assumed input is bit-map */
    image.depth        = 1;          /* hence, depth of 1    */

    image.data         = (char*) bitmap_bits;   /* where the bits are */

    image.xoffset      = 0;         /* leading pixels to skip ?  */
    image.byte_order       = LSBFirst;      /* magic numbers, describing */
    image.bitmap_pad       = 8;         /* data format of bit map    */
    image.bitmap_bit_order = LSBFirst;
    image.bitmap_unit      = 8;
    image.bytes_per_line   = (bitmap_width + 7) / 8;

    image.obdata       = NULL;

    /* get a chunk of off-screen, display on root screen */
    /* 1 bit deep, this is still just bit data, not color pixel data */
    pixmap = XCreatePixmap (display, RootWindowOfScreen (screen),
                image.width, image.height, 
                (unsigned) DefaultDepthOfScreen(screen));
    if (!pixmap)
    return (pixmap);

    /* When putting a XYPixmap type image, the foreground and */
    /* and background of the gc should not be used, but I'll  */
    /* leave this in here anyway.                 */

    gcValues.foreground = foreground_pixel;
    gcValues.background = background_pixel;

    /* build a gc to use when drawing into the pixmap */
    gc = XCreateGC (display, pixmap, GCForeground | GCBackground, &gcValues);

    if (! gc)
    return ((Pixmap) NULL);

    /* put bits into the pixmap */
    XPutImage (display, pixmap, gc, &image, 0, 0, 
           0, 0, image.width, image.height);

    XFreeGC (display, gc);

    return (pixmap);
}
