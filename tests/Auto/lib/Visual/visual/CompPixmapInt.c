/* 
 * @OPENGROUP_COPYRIGHT@
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
static char rcsid[] = "$TOG: CompPixmapInt.c /main/9 1999/02/05 18:11:56 jff $"
#endif
#endif
/***********************************************************************
	Summary:
            Compares the pixmap and dumps all errors to stdout.

        INPUTS:
            widget - the widget whose image needs comparing

        OUTPUTS:
            none

        RETURNS:
            nothing
************************************************************************/

#include "vislib.h"
#include "xislib.h"
#include "mvslib.h"

#include <Xm/BulletinB.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Xm/Frame.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>

#include <X11/IntrinsicP.h>

#include <AutoMessages.h>

static XImage *image_comb = NULL;
static XImage *image_screen = NULL;
static XImage *image_orig = NULL;
static XImage *image = NULL;			

#define DIFFER  0
#define ORIG	1
#define SCREEN	2

#define FAIL	0
#define PASS	1

static  Widget  DrawA, BBoard, RowColumn, Inter_Label, Inter_Frame;
static  Widget  Diffs, Pass, Fail, Overlay_orig, Overlay_screen;
static  Widget  Size_Label;
static  unsigned short width, height;
Boolean different_size = False;

static  void DumpWindow();
static  void ExposeCB();
static  void CreateInterActiveWindow();
static  Pixel GetColor();
static  XmFontList GetFont();
static	void FailCB();
static	void PassCB();
static	void OScreenCB();
static	void DisplayOrigCB();
static	void DiffsCB();

extern  Boolean AutoFullOutput;
extern  Boolean AutoTrace;
extern  Boolean AutoWindowDumps;
extern	Widget	Shell1;
extern 	char   AutoFailColor[25];

extern	void    AutoError();
extern  void 	AutoSystem();
extern  void	AutoTraceMsg();

extern  void    mvsGetWidgetColors();

static  Boolean	AutoMoveOn = False;
static  int	Which_Expose = DIFFER; 
short   found_error = False;
short   no_widget_info = False;

void mvsComparePixmapInt(widget_info)
MvsWidgetInfoRecord  *widget_info;
{
    int x,y,begin_x, begin_y, n;
    Arg args[1];
    Pixmap back_pix = 0L;
    Widget widget;
    /* The length of the widget_name used to be 15 but in some
       tests I ran, the widget name had an entire directory path
       prepended to it and was much more than 15. 256 seems like
       a safe number. -- rgcote 7/29/93 */
    char widget_name[256];
    char *name = NULL;
    int widget_class_code;
    unsigned int checksum,checksum2;
    unsigned char *bp;  /* byte pointer */
    unsigned short border_width;
    short curpixel;
    Pixel matchpixel;
    MvsWidgetClassInfo *wcinfo2;
    MvsWidgetInfoRecord *winfo, *winfo2;
    MvsArgVal *mvs_resources2;
    short color_ref;
    short done;
    MvsWidgetInfoRecord *winfo_stack[100];
    XisObjectRecord *tmp_object;
    MvsWidgetInfoRecord *tmp_info = NULL;
    MvsWidgetInfoRecord *gad_info = NULL;
    Widget tmp_widget = NULL;
    short stack_top = 0;
    int temp_x, temp_y, temp_width, temp_height, temp_bw, revert;
    static unsigned int newhashid = 0;
    Window focus_window;
    Boolean possible_gad_color = False;
    Boolean first_fail_time = True;
    struct _MvsUniqueColorAllocInfoRecord2 
			*widget_unique_color_info;
    struct _MvsUniqueColorAllocInfoRecord2 
			*gad_unique_color_info;
    char msg_string[125];
    Boolean foreign_obj = False;
    int save_x, save_y;

    found_error = False;
    no_widget_info = False;
    different_size = False;

    image_screen = image_orig = image = image_comb = NULL;

    xisProcessObjects();
    xisUpdateObjectAttributes();

    XGetInputFocus(mvsDisplay, &focus_window, &revert);

    /* Do depth first traversal to register any newly seen pixmaps */
    /* and to load latest x,y,width,height information             */
    /* Be sure also the widget has the latest color values         */

    widget = widget_info->widget;
    strcpy(widget_name, XtName(widget));

    winfo = widget_info;
 
    done = 0;
    while (!done) {

        temp_x = winfo->x;
        temp_y = winfo->y;
        temp_height = winfo->height;
        temp_width = winfo->width;
        temp_bw = winfo->border_width;
        mvsGetWidgetGeometry(winfo->widget, &temp_x,&temp_y,&temp_width,
                             &temp_height, &temp_bw   );
        winfo->x = temp_x;
        winfo->y = temp_y;
        winfo->height = temp_height;
        winfo->width = temp_width;
        winfo->border_width = temp_bw;
        
        mvsGetWidgetColors(winfo);

        if (winfo->first_child != NULL) {
            winfo_stack[stack_top++] = winfo;
            winfo = (MvsWidgetInfoRecord *)winfo->first_child;
        }
        else 
            if (winfo->next_sibling != NULL)
                winfo = (MvsWidgetInfoRecord *)winfo->next_sibling;
            else {
                winfo = NULL;
                while (stack_top > 0 && winfo == NULL)
                    winfo = (MvsWidgetInfoRecord *)
                                  winfo_stack[--stack_top]->next_sibling;

                if (stack_top == 0)
                    done = 1;
            } 
    } /* End while(!done) */

    if (newhashid == mvsNumRecIds || 
    			fseek(mvsImageFd,mvsFilePos[newhashid++],0) != 0)
        AutoMessage (_AutoMessages[WARNMSG11]);

    else {
        VIS_trace("#### Found image in recid #%d\n",newhashid);

        if (fread_long(mvsImageFd) != mvsImageRecordStartCode) {
            sprintf (msg_string, _AutoMessages[WARNMSG12], "");
	    AutoMessage(msg_string);
            AutoMessage(_AutoMessages[WARNMSG13]);
        }
        else {
            checksum = fread_long(mvsImageFd);

            width = fread_short(mvsImageFd);
            height = fread_short(mvsImageFd);

            if ((width != widget_info->width + 2*widget_info->border_width)||
                (height != widget_info->height + 2*widget_info->border_width)) {
             
	      sprintf (msg_string, _AutoMessages[VISMSG6], width,height,
                    widget_info->width + 2*widget_info->border_width,
                    widget_info->height + 2*widget_info->border_width,
		    widget_name);
                AutoMessage(msg_string);
                    

		different_size = True;

                mvsDecompressRead(mvsImageFd,mvsImageBuffer,width*height);

		bp = (&mvsImageBuffer[0]);

		CreateInterActiveWindow(widget, (int) width, (int) height,
					(int) (widget_info->width + 
					2*widget_info->border_width),
					(int) (widget_info->height +
					2*widget_info->border_width));
		
		for (y=0; y<height; y++) {
                        for (x=0; x<width; x++) {
                            XPutPixel(image_orig, x, y, *bp);
			bp++;
			}
		}

		found_error = True; /* because of geometry difference */
		Which_Expose = ORIG;

            }
            else {
                mvsDecompressRead(mvsImageFd,mvsImageBuffer,width*height);

                /* check checksum */

                checksum2 = 0;
                bp = &mvsImageBuffer[0];
                for (y=0; y<height; y++) {
                    for (x=0; x<width; x++) {
                        checksum2 += (x+1)*(y+1)*(*bp);
                        bp++;
                    }
                }

                if (checksum != checksum2) {
		    sprintf (msg_string, _AutoMessages[WARNMSG121], 
			     widget_name);
		    AutoMessage(msg_string);
		    AutoMessage(_AutoMessages[WARNMSG123]);
                    
			
                }
                else {

		    /*
   		    get border width and subtract from the the current
		    x and y. In GenPixmap() this done through Translate
    		    Coordinates. A better fix maybe to put this in 
		    mvsGetSubObjects() so that x and y returned include
		    the border_width. 
 		    */

		    border_width = widget_info->border_width;
		  
                    x = widget_info->x - border_width;
                    y = widget_info->y - border_width;

                    image = XGetImage(visDisplay,DefaultRootWindow(visDisplay),
                                      x,y,width,height,AllPlanes, ZPixmap);

		    begin_x = x;
		    begin_y = y;

                    if (image == 0) {
		        sprintf (msg_string, _AutoMessages[VISMSG7], 
				 widget_name);
			AutoError (msg_string);
                        exit(1);
                    }

                    /* Compare images pixel by pixel */

                    bp = (&mvsImageBuffer[0]);

		    CreateInterActiveWindow(widget, (int) width, (int) height,
					    (widget_info->width + 
					    2*widget_info->border_width),
					    (widget_info->height +
					    2*widget_info->border_width));

                    for (y=0; y<height; y++) {
                        for (x=0; x<width; x++) {

		            /* Create two images, 1 representing the orinal
			       recorded image, 1 representing the image
			       on the screen */

			    XPutPixel(image_screen, x, y, XGetPixel(image,x,y));
			    XPutPixel(image_orig, x, y, *bp);

                            /* Get normalized (canonical) color */

			    foreign_obj = False;

		    	    tmp_object = xisFindObjectAtLocation(begin_x + x,
								 begin_y + y);

			    if (tmp_object == NULL) {
				if (AutoFullOutput) {
				   foreign_obj = True;
				   sprintf (msg_string, _AutoMessages[VISMSG8],
					    widget_name, x,y);
                                   AutoMessage(msg_string);

				   break;
				}
				else {
				       sprintf(msg_string, 
					   _AutoMessages[VISMSG34],
					  widget_name); 
			    	   AutoMessage(msg_string);
				   break;
				}
			    }

			    if (foreign_obj)
				break;

		    	    tmp_widget = tmp_object->id.widget;

			    if (tmp_widget != NULL) 
			       widget_class_code  = mvsGetClassCode(tmp_widget);
			    else {
			       /* If the widget is NULL, we may be looking at
				  a pixel on the root window. If so, then
				  we really don't care whether the pixel matches
				  so dump the pixel as PASS and just continue
				  the loop. */
			       if (tmp_object->id.window ==
				   DefaultRootWindow(visDisplay))
			       {
				   DumpPixel(PASS, x, y);
				   bp++;
				   continue;
			       }
			       else
			       {
				   /* Otherwise we found a real error. Log an
				      error message and quit the loop */
				   sprintf(msg_string, _AutoMessages[VISMSG46],
					   x, y);
				   AutoMessage(msg_string);
				   break;
			       }
			    }

			    if (XmIsGadget(tmp_widget) && 
				(widget_class_code 
					== mvsXmPushButtonGadgetClass ||
				 widget_class_code
					== mvsXmToggleButtonGadgetClass)) {
				gad_info = mvsWidgetToWidgetInfo(tmp_widget);
				gad_unique_color_info =
					gad_info->widgetUniqueColorInfo;
				possible_gad_color = True;
			    }

			    /* If the object is a gadget then find parent
			       of the gadget and use it */
				
			    while (XmIsGadget(tmp_widget) &&
				   widget_class_code != mvsXmIconGadgetClass)
				tmp_widget = XtParent(tmp_widget);

		    	    tmp_info = mvsWidgetToWidgetInfo(tmp_widget);

			    curpixel = *bp;
			    if (curpixel >= MAX_UNIQUE_COLORS) {
				sprintf(msg_string, _AutoMessages[VISMSG9], 
					curpixel,x,y);
			        found_error = True;
			    }
				
			    if (tmp_info == NULL)
			    {
				if (no_widget_info == False)
				{
				    /* We only want to log this message once
				       into the output file. Doing it on every
				       pixel of the offending widget will degrade
				       performance too much. */
				    no_widget_info = True;
				    sprintf(msg_string, _AutoMessages[VISMSG47], 
					    XtName(tmp_widget));
				    AutoMessage(msg_string);
				    found_error = True; /* because we couldn't find
							   enough info to fix the
							   pixel */
				}
				/* We can't normalize matchpixel, but at least
				   give it a value. */
				matchpixel = curpixel;
			    }
			    else
			    {
			     if (curpixel < MAX_UNIQUE_COLORS) {
				widget_unique_color_info = 
				  tmp_info->widgetUniqueColorInfo;
				
				/* Convert to expected color "match_pixel" */
				winfo2 = 
				  widget_unique_color_info[curpixel].widget_info;

				if (winfo2 == NULL)
				{
				    found_error = True; /* because we couldn't find
							   enough info to fix the
							   pixel */
				    /* We can't normalize matchpixel, but at least
				       give it a value. */
				    matchpixel = curpixel;
				}
				else {
				    wcinfo2 = winfo2->widget_class_info;
				    color_ref =
				      widget_unique_color_info[curpixel].color_ref;
				    mvs_resources2 = winfo2->mvs_resources;
				    matchpixel = (Pixel)
				      mvs_resources2[wcinfo2->res_color_ref[color_ref]];
				}
			      }
			    }
			      
	       /* If you dont receive a match it may be that the widget
		  does not have the highlight from the parent. If this
		  is the case then use the background color of the parent 
		  to satisfy the highlight color */


                if (XGetPixel(image,x,y) != matchpixel && 
		    curpixel < MAX_UNIQUE_COLORS &&
		    focus_window != XtWindowOfObject(tmp_widget)) {
			tmp_widget = XtParent(tmp_widget);
			tmp_info = mvsWidgetToWidgetInfo(tmp_widget);
			if (tmp_info != NULL) {
                            widget_unique_color_info =
                                tmp_info->widgetUniqueColorInfo;
			    color_ref = 
				widget_unique_color_info[curpixel].color_ref;
                            winfo2 = 
				widget_unique_color_info[curpixel].widget_info;
			}
			else
			    found_error = True; /* because we couldn't find
						   enough info to fix the
						   pixel */

			/* 
			   If the current pixel cannot be found on the parent
			   then we know that there is a failure within the
			   widget itself. 
			*/

			if (tmp_info != NULL && winfo2 != NULL) {
                        	wcinfo2 = winfo2->widget_class_info;
                        	mvs_resources2 = winfo2->mvs_resources;
				name = wcinfo2->resource_info[wcinfo2->res_color_ref[color_ref]].name;

				n = 0;
                                XtSetArg(args[n], XmNbackgroundPixmap,
                                         &back_pix); n++;
                                XtGetValues(tmp_widget, args, n);

			/* Only get matchpixel if the pixel you are looking at
			   is the background color of the parent to see if it
                           matches the highlightColor of the "Picture" widget.
			   No way to find highlightColor of the widget */

				if (strcmp("background", name) == 0)
			  		matchpixel = (Pixel)
					  mvs_resources2[wcinfo2->res_color_ref[color_ref]];
				else {
                                   if (back_pix != 0L) {
                                        if (strcmp("foreground", name) == 0 ||
					    strcmp("bottomShadowColor", name) == 0 ||
					    strcmp("topShadowColor", name) == 0)
                                                matchpixel = (Pixel)
                                                 mvs_resources2[wcinfo2->res_color_ref[color_ref]];
                                   }
                                }
			}
		}

                if (XGetPixel(image,x,y) != matchpixel && 
		    curpixel < MAX_UNIQUE_COLORS &&
		    possible_gad_color) {
			color_ref = 
				gad_unique_color_info[curpixel].color_ref;
                        winfo2 = 
				gad_unique_color_info[curpixel].widget_info;

			/* 
			   If the current pixel cannot be found on the parent
			   then we know that there is a failure within the
			   widget itself. 
			*/

			if (winfo2 == NULL)
				found_error = True; /* because we couldn't find
						       enough info to fix the
						       pixel */
	
			else {
			    int k, num_colors;
			    Pixel image_pixel;

			    wcinfo2 = winfo2->widget_class_info;
			    mvs_resources2 = winfo2->mvs_resources;
			    num_colors = wcinfo2->num_res_colors;
		       
			    image_pixel = XGetPixel(image, x, y);

			    for (k = 0; k < num_colors; k++) {
			     if (wcinfo2->res_color_ref[k] >= 0) {

			       name = wcinfo2->resource_info[wcinfo2->res_color_ref[k]].name;

			/* Only get matchpixel if the pixel you are looking at
			   is the armcolor (in case of PushButtonGadget)
			   and selectColor (in case of ToggleButtonGadget) */

			       if ((strcmp("selectColor", name) == 0 ||
				    strcmp("unselectColor", name) == 0) &&
				   widget_class_code == 
				        mvsXmToggleButtonGadgetClass)
				    if (image_pixel == (Pixel)
				                       mvs_resources2[wcinfo2->res_color_ref[k]])
					matchpixel = (Pixel)
					    mvs_resources2[wcinfo2->res_color_ref[k]];
				if (strcmp("armColor", name ) == 0 &&
				    widget_class_code ==
				    mvsXmPushButtonGadgetClass)
				    matchpixel = (Pixel)
					mvs_resources2[wcinfo2->res_color_ref[k]];
			     }
			    }
			}
		}

                            /* Compare expected "match_pixel" with 
			       actual pixel */

                            if (XGetPixel(image,x,y) != matchpixel) {
                                found_error = True; /* because of pixel
						       mismatch */
				DumpPixel(FAIL, x, y);
				if (AutoFullOutput) {
				       if (first_fail_time && AutoWindowDumps){
						DumpWindow(widget);
						first_fail_time = False;
					}
					sprintf(msg_string, 
						_AutoMessages[VISMSG10],
						widget_name, x,y,matchpixel,
						XGetPixel(image,x,y)); 
					AutoMessage(msg_string);
				}
                            }
			    else
				DumpPixel(PASS, x, y);
                            bp++;
                        }
                    }
                }
            }
            if (found_error) {
		sprintf(msg_string, 
			_AutoMessages[VISMSG35],
			widget_name); 
                AutoMessage(msg_string);
	    }
            if (image != NULL)
                XDestroyImage(image);
        }
    }

    if (found_error) {

    /* Save exisiting (X,Y) which represents the original ending point
       of the test */

	    XtManageChild(BBoard);

	    save_x = xisSavePointerX;
	    save_y = xisSavePointerY;
	    xisSavePointer();

	/* 
	   Put an image out to the Drawing Area which represents the changes
	   between the image on the screen and the image saved in the .vis file
	*/

	    XFlush(mvsDisplay);
	    xisSynchronize();
 	    if (!different_size)
	    	XPutImage(mvsDisplay, XtWindow(DrawA), 
			  DefaultGC(mvsDisplay, DefaultScreen(mvsDisplay)),
			  image_comb, 0, 0, 0, 0, width, height);
	    else
	    	XPutImage(mvsDisplay, XtWindow(DrawA), 
			  DefaultGC(mvsDisplay, DefaultScreen(mvsDisplay)),
			  image_orig, 0, 0, 0, 0, width, height);
	    xisSynchronize();
	    XFlush(mvsDisplay);

	    XSetInputFocus(mvsDisplay, XtWindow(BBoard), RevertToNone,
			   CurrentTime);

	    XmProcessTraversal(RowColumn, XmTRAVERSE_CURRENT);

	/* 
	   Input callback from the Drawing area will force AutoMoveOn to
	   True and you will continue with Automation
	*/

	    while (AutoMoveOn == False)
		    xisSynchronize();

	/* Unmanage Dialog which contains the differences */

	    XtUnmanageChild(BBoard);

    	/* Set AutoMoveOn back to False for next set of comparisons */

    	AutoMoveOn = False;

    	xisProcessObjects();
    	xisUpdateObjectAttributes();

    	/* 
          Restore the original (X,Y) location of the pointer before you 
          clicked on the Drawing Area for continuation. 
        */

    	xisRestorePointer();

    	xisSavePointerX = save_x;
    	xisSavePointerY = save_y;
    }

    /* 
   	Destroy this image which contained the differences and 
   	original and screen images
    */

    if (image_comb != NULL) {
	if (image_comb->data) {
		XtFree(image_comb->data);
		image_comb->data = 0;
	}
    	XDestroyImage(image_comb);
    	image_comb = NULL;
    }

    if (image_screen != NULL) {
	if (image_screen->data) {
		XtFree(image_screen->data);
		image_screen->data = 0;
	}
	XDestroyImage(image_screen);
	image_screen = NULL;
    }

    if (image_orig != NULL) {
	if (image_orig->data) {
		XtFree(image_orig->data);
		image_orig->data = 0;
	}
	XDestroyImage(image_orig);
	image_orig = NULL;
    }


} /* End mvsComparePixmapBatch() */


static void DumpWindow(widget)
Widget widget;
{
    char trace_msg[100];
    char file_string[25];
    char window_string[25];
    char *send_string[6];
    static int num_failure = 0;
    Boolean sensitive;

    sprintf(file_string, "%s_fail%d", mvsTestName, num_failure++);
    sprintf(window_string, "%ld", XtWindow(widget));

    send_string[0] = "xwd";
    send_string[1] = "-id";
    send_string[2] = window_string;
    send_string[3] = "-out";
    send_string[4] = file_string;
    send_string[5] = (char *) 0;

    if (AutoTrace) {
        sprintf(trace_msg, "DumpWindow: xwd -id %s -out %s for widget %s",
    	      window_string, file_string, XtName(widget));
        AutoTraceMsg(trace_msg);
    }
        
    AutoSystem("xwd", send_string);

}


static void CreateInterActiveWindow(widget, width, height, actual_width,
				    actual_height)
Widget widget;
int width, height;
int actual_width, actual_height;
{  
    Arg args[50];
    int n;
    static Boolean first_time = True;		/* only create Interactive
						   window once */
    char tmp_str[100];
    XmString tcs;

    /*
       This routine will create a Interactive debug window, which will
       allow the user to accept or reject the visual difference shown.
       The user will also be allowed to display the original image or
       the differences layered on top of the current image on the screen.
       If the images are different sizes, only the recorded image will
       be able to be shown.
    */


    /* 
       Create a XImage which contain the differences between the
       image on the screen and the image contained in the .vis file.
       If the original image and the screen image are different
       sizes, only allocate size for the original image. 
    */

    if (different_size == False) {
    	image_comb = XCreateImage(mvsDisplay, 
    	         	          DefaultVisual(mvsDisplay, 
						DefaultScreen(mvsDisplay)),
    	         		  DefaultDepth(mvsDisplay, 
						DefaultScreen(mvsDisplay)),
    	         		  ZPixmap, 0, NULL, width, height,
    	         		  BitmapPad(mvsDisplay), 0);

    	image_screen = XCreateImage(mvsDisplay, 
    	         		    DefaultVisual(mvsDisplay,
						  DefaultScreen(mvsDisplay)),
    	         		    DefaultDepth(mvsDisplay, 
						 DefaultScreen(mvsDisplay)),
    	         		    ZPixmap, 0, NULL, width, height,
    	      	 		    BitmapPad(mvsDisplay), 0);
    }

    image_orig = XCreateImage(mvsDisplay, 
    	         DefaultVisual(mvsDisplay, DefaultScreen(mvsDisplay)),
    	         DefaultDepth(mvsDisplay, DefaultScreen(mvsDisplay)),
    	         ZPixmap, 0, NULL, width, height,
    	      	 BitmapPad(mvsDisplay), 0);

    /*
       Allocate space for the three images, if original image and 
       the screen image are different size, only allocate space for
       the original image.
    */


    if (image_comb && image_screen)  {
      image_comb->data = XtMalloc(image_comb->bytes_per_line * height);
      image_screen->data = XtMalloc(image_screen->bytes_per_line * height);
      if (!image_comb->data || !image_screen->data)
        {
          AutoError(_AutoMessages[WARNMSG14]);
          
        }
    }

    if (image_orig) {
      image_orig->data = XtMalloc(image_orig->bytes_per_line * height);
      if (!image_orig->data)
        {
          AutoError(_AutoMessages[WARNMSG14]);
          
         }
    }
    else {
       AutoError(_AutoMessages[WARNMSG15]);
      
    }

    if  (first_time) {     		/* Create interactive window once */

        tcs = XmStringCreateSimple("Interactive Debug");

        n = 0;
        XtSetArg(args[n], XmNdefaultPosition, False);			n++;
        XtSetArg(args[n], XmNx, 500);					n++;
        XtSetArg(args[n], XmNy, 0);					n++;
        XtSetArg(args[n], XmNmarginWidth, 0);				n++;
        XtSetArg(args[n], XmNmarginHeight, 0);				n++;
        XtSetArg(args[n], XmNdialogTitle, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8"));		n++;
	XtSetArg(args[n], XmNshadowThickness, 0);			n++;
        BBoard = XmCreateBulletinBoardDialog(Shell1, "DEBUG", args, n);
        XtRealizeWidget(BBoard);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple(" Visual Differences Window");

        n = 0;
        XtSetArg(args[n], XmNx, 0);					n++;
        XtSetArg(args[n], XmNy, 0);					n++;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNheight, 40);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15bold"));		n++;
        XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);		n++;
        Inter_Label = XmCreateLabel(BBoard, "InteractiveLabel", args, n);
        XtRealizeWidget(Inter_Label);
        XtManageChild(Inter_Label);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple(" ");

        n = 0;
        XtSetArg(args[n], XmNx, 250);					n++;
        XtSetArg(args[n], XmNy, 11);					n++;
        XtSetArg(args[n], XmNheight, 40);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING);		n++;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        Size_Label = XmCreateLabel(BBoard, "SizeLabel", args, n);
        XtRealizeWidget(Size_Label);
        XtManageChild(Size_Label);

        XmStringFree(tcs);

        n = 0;
        XtSetArg(args[n], XmNy, 40);					n++;
        XtSetArg(args[n], XmNx, 0);					n++;
        XtSetArg(args[n], XmNheight, 40);				n++;
        XtSetArg(args[n], XmNorientation, XmHORIZONTAL);		n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8"));		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNentryAlignment, XmALIGNMENT_CENTER); 	n++;
        RowColumn = XmCreateRowColumn
    			(BBoard, "InteractiveRowColumn", args, n);
        XtRealizeWidget(RowColumn);
        XtManageChild(RowColumn);

        tcs = XmStringCreateSimple("Accept");

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15"));		n++;
        Pass = XmCreatePushButton(RowColumn, "InteractivePass", args, n);
        XtRealizeWidget(Pass);
        XtManageChild(Pass);

        XtAddCallback(Pass, XmNactivateCallback, PassCB, NULL);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple("Reject");

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15"));		n++;
        Fail = XmCreatePushButton(RowColumn, "InteractiveFail", args, n);
        XtRealizeWidget(Fail);
        XtManageChild(Fail);

        XtAddCallback(Fail, XmNactivateCallback, FailCB, NULL);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple("Recorded Image");

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15"));		n++;
        Overlay_orig = XmCreatePushButton
    			(RowColumn, "InteractiveDisplayOrig", args, n);
        XtRealizeWidget(Overlay_orig);
        XtManageChild(Overlay_orig);

        XtAddCallback(Overlay_orig, XmNactivateCallback, DisplayOrigCB, NULL);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple("Overlay Playback");

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15"));		n++;
        Overlay_screen = XmCreatePushButton
    			(RowColumn, "InteractiveOverlayS", args, n);
        XtRealizeWidget(Overlay_screen);
        XtManageChild(Overlay_screen);

        XtAddCallback(Overlay_screen, XmNactivateCallback, OScreenCB, NULL);

        XmStringFree(tcs);

        tcs = XmStringCreateSimple("Show Diffs");

        n = 0;
        XtSetArg(args[n], XmNlabelString, tcs);				n++;
        XtSetArg(args[n], XmNbackground, GetColor("#d0d0d8")); 		n++;
        XtSetArg(args[n], XmNtopShadowColor, GetColor("white"));	n++;
        XtSetArg(args[n], XmNfontList, GetFont("9x15"));		n++;
        Diffs = XmCreatePushButton
    			(RowColumn, "InteractiveDiffs", args, n);
        XtRealizeWidget(Diffs);
        XtManageChild(Diffs);

        XtAddCallback(Diffs, XmNactivateCallback, DiffsCB, NULL);

        XmStringFree(tcs);

        n = 0;
        XtSetArg(args[n], XmNy, 80);					n++;
        XtSetArg(args[n], XmNx, 0);					n++;
        XtSetArg(args[n], XmNshadowType, 
    				XmSHADOW_ETCHED_OUT);			n++;
        XtSetArg(args[n], XmNshadowThickness, 4);			n++;
        Inter_Frame = XmCreateFrame(BBoard, "InteractiveFrame", args, n);
        XtRealizeWidget(Inter_Frame);
        XtManageChild(Inter_Frame);

        n = 0;
        XtSetArg(args[n], XmNwidth, width);				n++;
        XtSetArg(args[n], XmNheight, height);				n++;
        XtSetArg(args[n], XmNmarginWidth, 0);				n++;
        XtSetArg(args[n], XmNmarginHeight, 0);				n++;
        DrawA = XmCreateDrawingArea(Inter_Frame, "InteractiveDrawA", args, n);
        XtRealizeWidget(DrawA);
        XtManageChild(DrawA);
    
        XtAddCallback(DrawA, XmNexposeCallback, ExposeCB, NULL);

        first_time = False; 			/* once and only once */

    }

    /* 
       If this not the first time then just set size of the drawing 
    */

    else  {  
    	n = 0;
	XtSetArg(args[n], XmNwidth, width);				n++;
	XtSetArg(args[n], XmNheight, height);				n++;
	XtSetValues(DrawA, args, n);
    }
    /* 
       If original image and screen image are different, make the Diffs
       button and the OverlayScreen option insensitive becuase images
       have not been created and are useless. Also print out the recorded
       size and the actual size to use as comparisons.
    */

    if (different_size) {  
  	XtSetSensitive(Overlay_screen, False);
    	XtSetSensitive(Diffs, False);

	sprintf(tmp_str, "(Record Size = %d x %d, Actual Size = %d x %d)",
		width, height, actual_width, actual_height);

	tcs = XmStringCreateSimple(tmp_str);

	n = 0;
	XtSetArg(args[n], XmNlabelString, tcs);				n++;
	XtSetValues(Size_Label, args, n);
 	
	XmStringFree(tcs);
    }
    else {
	XtSetSensitive(Overlay_screen, True);
	XtSetSensitive(Diffs, True);

	tcs = XmStringCreateSimple(" ");

	n = 0;
	XtSetArg(args[n], XmNlabelString, tcs);				n++;
	XtSetValues(Size_Label, args, n);	

	XmStringFree(tcs);
    }
}


DumpPixel(status, x, y)
int status;
int x,y;

{
    /* 
       This routine will put a black pixel out to the image on the 
       Drawing Area if the comparison failed. It will put out a 
       white pixel if it passed. 
    */

    Pixel pixel;

    if (status == FAIL)
    	pixel = GetColor(AutoFailColor);
    else
	pixel = GetColor("white");

    XPutPixel(image_comb, x, y, pixel);

}


static void ExposeCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{

    /* 
       This routine will choose the proper image to redisplay in the
       drawing area when an expose event is recognized by the drawing
       area.
    */

    switch (Which_Expose) {
    	case DIFFER:
       			XPutImage(mvsDisplay, XtWindow(DrawA), 
              			  DefaultGC(mvsDisplay, 
    			          	    DefaultScreen(mvsDisplay)),
    	  			  image_comb, 0, 0, 0, 0,
    				  width, height);
    			break;
    	case ORIG:
        		XPutImage(mvsDisplay, XtWindow(DrawA),
          			  DefaultGC(mvsDisplay, 
    				            DefaultScreen(mvsDisplay)),
          		          image_orig, 0, 0, 0, 0,
    				  width, height);
    			break;
    	case SCREEN:
        		XPutImage(mvsDisplay, XtWindow(DrawA),
          			  DefaultGC(mvsDisplay, 
    				            DefaultScreen(mvsDisplay)),
          		          image_screen, 0, 0, 0, 0,
    				  width, height);
    			break;
    	default:	break;
    }
}


static void PassCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{
    printf("Failure on Visual Comparison - Accepted\n");

    AutoMoveOn = True;
}


static void FailCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{
    printf("Failure on Visual Comparison - Not accepted\n");

    AutoMoveOn = True;
}


static void OScreenCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{
    int x, y;
    Pixel fail;

    Which_Expose = SCREEN;

    fail = GetColor(AutoFailColor);

    for (x = 0; x < width; x++) {
	for (y = 0; y < height; y++) {

		if (XGetPixel(image_comb, x, y) == fail)
			XPutPixel(image_screen, x, y, fail);
		else
			XPutPixel(image_screen, x, y, 
 				  XGetPixel(image_screen, x, y));

	}
    }
    XPutImage(mvsDisplay, XtWindow(DrawA),
	      DefaultGC(mvsDisplay, DefaultScreen(mvsDisplay)),
	      image_screen, 0, 0, 0, 0, width, height);

}


static void DisplayOrigCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{

    Which_Expose = ORIG;

    XPutImage(mvsDisplay, XtWindow(DrawA),
	      DefaultGC(mvsDisplay, DefaultScreen(mvsDisplay)),
	      image_orig, 0, 0, 0, 0, width, height);

}


static void DiffsCB(widget, cld, cd)
Widget widget;
XtPointer cld, cd;
{

    Which_Expose = DIFFER;

    XPutImage(mvsDisplay, XtWindow(DrawA),
	      DefaultGC(mvsDisplay, DefaultScreen(mvsDisplay)),
	      image_comb, 0, 0, 0, 0, width, height);

}


static Pixel GetColor(colorstr)
char *colorstr;
{
   XrmValue from, to;

   from.size = strlen(colorstr) +1;
   if (from.size < sizeof(String)) from.size = sizeof(String);
   from.addr = colorstr;
   to.addr = NULL;
   XtConvert(Shell1, XmRString, &from, XmRPixel, &to);
    if (to.addr != NULL)
      return ((Pixel) *((Pixel *) to.addr));
    else
      return ((Pixel) NULL);

}


static XmFontList GetFont(fontstr)
char *fontstr;
{

    XFontStruct   *newfont;
    XmFontList    fontlist;


    if (!(newfont = XLoadQueryFont (mvsDisplay, fontstr)))
     newfont = XLoadQueryFont (mvsDisplay, "fixed");
    fontlist = XmFontListCreate (newfont, XmSTRING_DEFAULT_CHARSET);

    return(fontlist);

}

