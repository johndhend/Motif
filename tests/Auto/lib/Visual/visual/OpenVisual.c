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
static char rcsid[] = "$XConsortium: OpenVisual.c /main/7 1995/07/14 11:51:02 drk $"
#endif
#endif
/***********************************************************************
  	@(#)OpenVisual.c	1.7.1.1	Date:1/22/91
        Author: TAT
        History:
           03/30/90 SJS Add to sccs tree
           05/24/90 TAT updated for multiple widgets
        Calls:

        Summary:
               (Used to be) mvsInitializ.c      1.1     Date:3/30/90
            Initializes the visual_info, color_table, and pixmap_table
        and  opens the visual checking image file (if needed).

        INPUTS
            none
  
        OUTPUTS 
            none

        RETURNS
            nothing

************************************************************************/


#include <AutoMessages.h>
#include "mvslib.h"


extern Boolean AutoAltVisualFile;
extern char    AutoAltVisualFileName[50];

void mvsOpenVisual() 
{
    static GC gcw,gcb;
    int i,j,x,y;
    XGCValues values;
    Pixel white,black,pixel;
    Window root;
    char data_file_name[255];
    char file_name[255];
    char *visual_path = NULL;
    unsigned long ltemp;
    XVisualInfo *vis_info;
    XVisualInfo vis_info_in;
    int n;
    char *getenv();
    char msg_string[125];

    if (mvsDisplay == (Display *) NULL)
        AutoMessage(_AutoMessages[VISMSG14]);


    /* Initialize MVS Visual Info Record */
    
    vis_info_in.visualid = XDefaultVisual(mvsDisplay,
                                          XDefaultScreen(mvsDisplay))->visualid;
    
    vis_info = XGetVisualInfo(mvsDisplay,VisualIDMask,&vis_info_in,&n);

    if (vis_info == NULL)
      AutoMessage(_AutoMessages[VISMSG14]);        

    mvsVisualInfo.visual = vis_info->visual;
    mvsVisualInfo.class = vis_info->class;
    mvsVisualInfo.depth = vis_info->depth;
    mvsVisualInfo.red_mask = vis_info->red_mask;
    mvsVisualInfo.green_mask = vis_info->green_mask;
    mvsVisualInfo.blue_mask = vis_info->blue_mask;
    mvsVisualInfo.colormap_size = vis_info->colormap_size;
    mvsVisualInfo.bits_per_rgb = vis_info->bits_per_rgb;
  
    mvsVisualInfo.colormap_id = XDefaultColormap(mvsDisplay,XDefaultScreen(mvsDisplay));


    /* Initialize MVS Color Table  */

    if (vis_info->depth == 1)
        mvsNumTableColors = 2;

    else if ((vis_info->class == StaticGray)||(vis_info->class == GrayScale))
        mvsNumTableColors = NUM_GRAYSCALE_COLORS;


    /* intialize mvsColorAllocInfo array */

    for (i=0; i<MAX_COLORS; i++)
        mvsColorAllocInfo[i].alloc_cnt = 0;

    /* Alloc colors black and white */

    if (!mvsAllocNamedColor("Black",&black) || !mvsAllocColor(black)) {
        AutoMessage(_AutoMessages[VISMSG42]);
    }
    else /* never deallocate black color */
        mvsColorAllocInfo[mvsAllocNumFromPixel(black)].alloc_cnt = 1000;

    if (!mvsAllocNamedColor("White",&white) || !mvsAllocColor(white)) {
        AutoMessage(_AutoMessages[VISMSG43]);
    }
    else /* never deallocate white color */
        mvsColorAllocInfo[mvsAllocNumFromPixel(white)].alloc_cnt = 1000;


    /* If generate mode, allocate all colors (just to look nice) */

    if (mvsGetVisualMode() == VISUAL_MODE_GENERATE_PIXMAPS) {
        for (i=0; i<mvsNumTableColors; i++) {
            if ( !mvsAllocNamedColor(mvsColorTable[i].name2,&pixel) ||
                 !mvsAllocColor(pixel) ) {

	        sprintf (msg_string,_AutoMessages[VISMSG44], mvsColorTable[i].name1);
                AutoMessage(msg_string);
                    
	    }
        }
    }


    /* Initialize MVS Pixmap Table */

    root = DefaultRootWindow(mvsDisplay);
        
    gcw = XCreateGC(mvsDisplay,root,0,&values);
    XSetForeground(mvsDisplay,gcw,white);
    gcb = XCreateGC(mvsDisplay,root,0,&values);
    XSetForeground(mvsDisplay,gcb,black);

    for (i=0; i<mvsNumTablePixmaps; i++) {
        mvsPixmapTable[i].pixmap = 
            XCreatePixmap(mvsDisplay,root,
                          mvsPixmapTable[i].width,
                          mvsPixmapTable[i].height,
                          DefaultDepth(mvsDisplay,xisScreen));
        j=0;
        for (y=0; y<mvsPixmapTable[i].height; y++) {
            for (x=0; x<mvsPixmapTable[i].width; x++,j++) {
                if (mvsPixmapTable[i].content[j])
                    XDrawPoint(mvsDisplay,mvsPixmapTable[i].pixmap,gcb,x,y);
                else
                    XDrawPoint(mvsDisplay,mvsPixmapTable[i].pixmap,gcw,x,y);
	    }
        }
    }
    XFreeGC(mvsDisplay,gcw);
    XFreeGC(mvsDisplay,gcb);


    /* 
       Open Image File (if needed)  - look at environment variable
       AUTOVPATH to dtermine where to read and write visual files  
       AUTOMATION ADDED.
    */

    if (AutoAltVisualFile)
	strcpy(file_name, AutoAltVisualFileName);
    else
	strcpy(file_name, mvsTestName);

    visual_path = getenv("AUTOVPATH");
    if (visual_path != NULL) {
	strcpy(data_file_name, visual_path);
	if (visual_path[strlen(visual_path) - 1] != '/')
		strcat(data_file_name, "/");
    	strcat(data_file_name, file_name);
	if (!AutoAltVisualFile)
    		strcat(data_file_name,".vis");
    }
    else {
    	strcpy(data_file_name, file_name);
	if (!AutoAltVisualFile)
    		strcat(data_file_name,".vis");
    }

    switch (mvsGetVisualMode()) {

        case VISUAL_MODE_DONT_CHECK:
            /* do nothing */
            break;

        case VISUAL_MODE_BATCH_COMPARE:
        case VISUAL_MODE_INTERACTIVE_COMPARE:
            mvsImageFd = fopen(data_file_name,"r");
            if (mvsImageFd == NULL) {
                AutoMessage(_AutoMessages[WARNMSG97]);
                AutoMessage(_AutoMessages[WARNMSG124]);
                mvsSetVisualMode(VISUAL_MODE_DONT_CHECK);
            }
            else {
                ltemp = fread_long(mvsImageFd);
                if ((ltemp != mvsImageFileStartCode)||
                    (fseek(mvsImageFd,mvsBeginningOfRecIds=fread_long(mvsImageFd),0)!=0)) {
                    sprintf(msg_string,_AutoMessages[WARNMSG12],data_file_name);
		    AutoMessage(msg_string);
                    AutoMessage(_AutoMessages[WARNMSG124]);
                    fclose(mvsImageFd);
                    mvsSetVisualMode(VISUAL_MODE_DONT_CHECK);
                }
                else {
                    mvsNumRecIds = fread_short(mvsImageFd);
                    for (i=0; i<mvsNumRecIds; i++) {
                        if(fread_short(mvsImageFd) != mvsRecIdRecordStartCode) {
                     sprintf(msg_string,_AutoMessages[WARNMSG12],data_file_name);
		    AutoMessage(msg_string);
                    AutoMessage(_AutoMessages[WARNMSG124]);
                            fclose(mvsImageFd);
                            mvsSetVisualMode(VISUAL_MODE_DONT_CHECK);
                            break;
                        }
                        mvsRecIdLength[i] = fread_short(mvsImageFd);
                        mvsFilePos[i] = (long)fread_long(mvsImageFd);
                        fread(mvsRecIdTable[i],sizeof(char),mvsRecIdLength[i],mvsImageFd);
                    }
                    VIS_trace("Read in %d image record ids\n",mvsNumRecIds);
                }
            }
            break;

        case VISUAL_MODE_GENERATE_PIXMAPS:
	    mvsImageFd = fopen(data_file_name,"w");
            if (mvsImageFd == NULL) {
                AutoError (_AutoMessages[WARNMSG98]);
                exit(-1);
            }
            fwrite_long(mvsImageFd,mvsImageFileStartCode);
            mvsBeginningOfImageFile = ftell(mvsImageFd);
            fwrite_long(mvsImageFd,mvsBeginningOfImageFile); /*reserve 4 bytes*/
            break;

        default:
	    sprintf (msg_string, _AutoMessages[VISMSG17], mvsGetVisualMode());
            AutoMessage(msg_string);
                      
            break;
    }

    XFree(vis_info);

} /* End mvsOpenVisual() */












