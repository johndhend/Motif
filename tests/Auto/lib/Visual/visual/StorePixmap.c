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
static char rcsid[] = "$XConsortium: StorePixmap.c /main/5 1995/07/14 11:51:22 drk $"
#endif
#endif
/***********************************************************************
  	Author: REC
	History:
	    Created 04/15/93 by REC
	Calls:

	Summary:
            Stores the current pixmap in a temporary buffer (file) to
	    be compared against another pixmap later in the compare
	    run.

        INPUTS:
            widget - the widget whose image needs comparing
	    identifier - tag associated with the image

        OUTPUTS:
            none

        RETURNS:
            nothing

************************************************************************/

#include <AutoMessages.h>
#include "vislib.h"
#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#endif

struct mvsTempImageRec *mvsTempImageRecHead, *mvsTempImageRecTail;

void mvsStorePixmap(widget_info, identifier)
MvsWidgetInfoRecord *widget_info;
char *identifier;
{
    int i,x,y, n;
    Widget widget;
    XImage *image;
    static GC compare_gc, normalized_gc;
    XGCValues values;
    Window tmp_window;
    static int first_time = 1;
    unsigned char *bp;  		/* byte pointer */
    unsigned int width,height;
    Window root,child;
    unsigned int depth;
    unsigned int border_width;
    struct mvsTempImageRec *current_rec;
    unsigned char *tmpbuf;

    /* NOT COMPLETELY IMPLEMENTED YET, SO RETURN AND DO NOTHING */
    /* if is added only to suppres compiler warning		*/
    if (first_time != 1) return;
      
    tmpbuf = (unsigned char *)XtMalloc(MAX_IMAGE_DIMENSION*MAX_IMAGE_DIMENSION);

    widget = widget_info->widget;

    if (first_time) {
        first_time = 0;
	mvsTempImageRecHead = (struct mvsTempImageRec *) 
	    malloc(sizeof(struct mvsTempImageRec));
	current_rec = mvsTempImageRecHead;
	mvsTempImageRecTail = mvsTempImageRecHead;
    }
    else  {
	current_rec = (struct mvsTempImageRec *)
	    malloc(sizeof(struct mvsTempImageRec));
	mvsTempImageRecTail->next = current_rec;
	mvsTempImageRecTail = current_rec;
    }


    /* Get the visual state */
    tmp_window = XtWindowOfObject(widget);


    /* Get the image (assumed with normalized colors) */
    XGetGeometry(visDisplay, tmp_window, &root,&x,&y,&width,&height,
		 &border_width,&depth);

    width += 2*border_width;
    height += 2*border_width;

    XTranslateCoordinates(visDisplay, tmp_window,root,
			  -border_width,
			  -border_width,
			  &x,&y,&child);

    /* Must normalize the colors of the pixmap to be those used
       during a record session.  I believe this can done by getting
       the "hard-wired" color settings, setting a GC and creating
       and new pixmap.  This new pixmap is what should get stored
       into the temp visual records.  Not implemented yet.
     */

    image = XGetImage( visDisplay,XDefaultRootWindow(visDisplay),
		      x,y,width,height,AllPlanes, ZPixmap   );


    if (image == 0) {
	AutoError(_AutoMessages[VISMSG12]);
    }

    /* copy to temp image buffer in current temp image structure */
    n = 0;
    bp = &tmpbuf[0];
    for (y=0; y<height; y++) {
	for (x=0; x<width; x++) {
	    *bp = XGetPixel(image,x,y);
	    
	    /* Automation - dont look at color. Would require a 
	       lookup of widget ID and then conversion to correct pixel 
	     */
	    bp++;
	    n++;
	}
    }

    strcpy ((char *)current_rec->mvsTempImageBuffer, (char *)tmpbuf);

    if (image != NULL) 
	XDestroyImage(image);
    
    /* store the name, width and height of the image */
    strcpy (current_rec->mvsTempImageName, identifier);
    current_rec->mvsTempImageWidth = width;
    current_rec->mvsTempImageHeight = height;
    current_rec->next = NULL;

    XtFree((char *)tmpbuf);

    return;

} /* End mvsStorePixmap() */
