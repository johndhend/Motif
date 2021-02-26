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
static char rcsid[] = "$XConsortium: GetPixImage.c /main/7 1995/07/14 11:50:23 drk $"
#endif
#endif
/***********************************************************************
  	@(#)GetPixImage.c	1.4.1.1	Date:1/22/91
  	Author: TAT
	History:
            05/24/90 SJS add to sccs
	Calls:

	Summary:
            Returns the specified pixmap as an image.  This routine goes beyond
        X's XGetImage() by figuring out the pixmaps dimensions for you as well.

        INPUTS
            pixmap - X id of pixmap you wish returned as an X image

        OUTPUTS
            none
 
        RETURNS
            A pointer to a dynamically allocated image (use XFree to free it).
************************************************************************/
static int error_occurred;

#include <AutoMessages.h>
#include "vislib.h"

static int myhandler(display,myerr)
Display *display;
XErrorEvent *myerr;
{
    if ((myerr->error_code == BadMatch)&&(myerr->request_code == X_GetImage))
        error_occurred = TRUE;
}


XImage *mvsGetPixmapImage(pixmap)
Pixmap pixmap;
{
    int i;
    int x,y,width,height;
    static int first_time = 1;

    XImage *image;

    if (first_time) {
        first_time = 0;
        mvsNumAvailPixmaps = 0;
    }

    for (i=0; i<mvsNumAvailPixmaps; i++) {
        if (pixmap == mvsAvailPixmap[i])
            return mvsAvailImage[i];
    }

    XSetErrorHandler(myhandler);

    x=0;
    error_occurred = FALSE;
    while (error_occurred == FALSE) {
        image = XGetImage(visDisplay,pixmap,x++,0,1,1,AllPlanes,ZPixmap);
        if (image != 0)
            XDestroyImage(image);
    }
    width = x-1;

    y=0;

    error_occurred = FALSE;
    while (error_occurred == FALSE) {
        image = XGetImage(visDisplay,pixmap,0,y++,1,1,AllPlanes,ZPixmap);
        if (image != 0)
            XDestroyImage(image);
    }
    height = y-1;

    XSetErrorHandler(NULL);

    if (mvsNumAvailPixmaps > MAX_PIXMAPS)
        AutoMessage(_AutoMessages[VISMSG40]);
    else {
        mvsAvailPixmap[mvsNumAvailPixmaps] = pixmap;

        mvsAvailImage[mvsNumAvailPixmaps] = XGetImage(visDisplay,pixmap,0,0,
                                                      width,
                                                      height,AllPlanes,ZPixmap);
        mvsNumAvailPixmaps++;
    }

} /* End mvsGetPixmapImage() */
