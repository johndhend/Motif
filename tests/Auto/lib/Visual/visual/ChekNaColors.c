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
static char rcsid[] = "$XConsortium: ChekNaColors.c /main/7 1995/07/14 11:47:05 drk $"
#endif
#endif
/***********************************************************************
  	@(#)ChekNaColors.c	1.5.1.1	Date:1/22/91
  	Author: TAT
	History:
	   03/30/90 SJS Add to sccs tree
	   09/11/90 SJS fix arg passing
	Calls:

	Summary:
            Check to make sure all the colors named in mvsColorTalbe are indeed
        installed on the user's server.

        Note: This is no longer a necessary requirement since 
              mvsAllocNamedColor now translates the color name 
              to the appropriate RGB value for the user and calls
              XAllocColor instead of XAllocNamedColor like it used to.

        INPUTS
            none

        OUTPUTS
            none
 
        RETURNS
            nothing
************************************************************************/

#include <AutoMessages.h>
#include "vislib.h"

void mvsCheckNamedColors PARAMS((void))
{
    Display *display2;
    Colormap cmap;
    int i;
    XColor nearest,exact;
    char *name;
    unsigned long pixels[1];
    char msg_string[125];

    display2 = XOpenDisplay(DisplayString(visDisplay));
    cmap = XDefaultColormap(visDisplay,DefaultScreen(visDisplay));

    for (i=0; i<mvsNumTableColors; i++) {
        if (!XAllocNamedColor(display2,cmap,name=mvsColorTable[i].name1,
                              &nearest,&exact)) {
	    sprintf (msg_string, _AutoMessages[VISMSG25], name);
            AutoMessage (msg_string);}
        else {
            if (exact.red != (mvsColorTable[i].red<<8)) {
	      sprintf(msg_string, _AutoMessages[VISMSG26],name,exact.red,mvsColorTable[i].red<<8); 
              AutoMessage(msg_string);}
                    
            if (exact.green != (mvsColorTable[i].green<<8)) {
	      sprintf (msg_string, _AutoMessages[VISMSG27],name,exact.green,mvsColorTable[i].green<<8); 
               AutoMessage(msg_string);}
                    
            if (exact.blue != (mvsColorTable[i].blue<<8)) {
	      sprintf(msg_string, _AutoMessages[VISMSG28],name,exact.blue,mvsColorTable[i].blue<<8); 
              AutoMessage(msg_string); }
                    
        }
        pixels[0] = nearest.pixel;
        XFreeColors(display2,cmap,pixels,1,0);

        if (!XAllocNamedColor(display2,cmap,name=mvsColorTable[i].name2,
                              &nearest,&exact)) {
	   sprintf(msg_string, _AutoMessages[VISMSG25], name);
	   AutoMessage(msg_string);}
        else {
            if (exact.red != (mvsColorTable[i].red<<8)){
	        sprintf(msg_string,_AutoMessages[VISMSG26],name,exact.red,mvsColorTable[i].red<<8); 
                AutoMessage(msg_string);}
                    
            if (exact.green != (mvsColorTable[i].green<<8)) {
	        sprintf (msg_string, _AutoMessages[VISMSG27], name,exact.green,mvsColorTable[i].green<<8);
                AutoMessage(msg_string);}
                    
            if (exact.blue != (mvsColorTable[i].blue<<8)) {
	      sprintf (msg_string, _AutoMessages[WARNMSG28], name,exact.blue,mvsColorTable[i].blue<<8); }
                
                    
        }
        pixels[0] = nearest.pixel;
        XFreeColors(display2,cmap,pixels,1,0);
    }

} /* End mvsCheckNamedColors() */
