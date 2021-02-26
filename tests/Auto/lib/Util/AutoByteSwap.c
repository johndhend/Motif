/* $XConsortium: AutoByteSwap.c /main/5 1995/07/15 20:59:44 drk $ */
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
/*
 *	file: AutoByteOrder.c
 *
 *	Contains routines to initialize and swap byteOrder if needed
 *
 */
#include <testlib.h>
#include <AutoMwm.h>


/*
 *	Swap the byte order 
 */

#define	swap4bytes(l) {\
		unsigned int t = (unsigned int) l;\
		char n;\
		char *tp = (char *) &t;\
		tp += sizeof(unsigned int) - 4;\
		n = tp[0]; tp[0] = tp[3]; tp[3] = n;\
		n = tp[1]; tp[1] = tp[2]; tp[2] = n;\
		l = t;\
}

#define	swap2bytes(s) {\
		unsigned short t = (unsigned short) s;\
		char n;\
		char *tp = (char *) &t;\
		tp += sizeof(unsigned short) - 2;\
		n = tp[0]; tp[0] = tp[1]; tp[1] = n;\
		s = t;\
}

unsigned char	AutoByteOrderChar = (char) 0;


void
AutoSwapBytes(PropMwmFrameIconInfo *window_prop)
{

	int	i;
		

	if (window_prop->byte_order == AutoByteOrderChar)
		return;

	swap4bytes(window_prop->windowX);
	swap4bytes(window_prop->windowY);
	swap4bytes(window_prop->upperBorderWidth);
	swap4bytes(window_prop->lowerBorderWidth);
	swap4bytes(window_prop->frameWin);
	swap4bytes(window_prop->titleWin);
	swap4bytes(window_prop->menuWin);
	swap2bytes(window_prop->titleRect.x);
	swap2bytes(window_prop->titleRect.y);
	swap2bytes(window_prop->titleRect.width);
	swap2bytes(window_prop->titleRect.height);

	for (i = 0; i < MAX_TITLE_REGIONS; i++) {

		swap4bytes(window_prop->titleGadgets[i].id);
		swap2bytes(window_prop->titleGadgets[i].rect.x);
		swap2bytes(window_prop->titleGadgets[i].rect.y);
		swap2bytes(window_prop->titleGadgets[i].rect.width);
		swap2bytes(window_prop->titleGadgets[i].rect.height);

	}
	swap4bytes(window_prop->titleGadgetCount);

	for (i = 0; i < MAX_RESIZE_HANDLES; i++) {

		swap4bytes(window_prop->resizeGadgets[i].id);
		swap2bytes(window_prop->resizeGadgets[i].rect.x);
		swap2bytes(window_prop->resizeGadgets[i].rect.y);
		swap2bytes(window_prop->resizeGadgets[i].rect.width);
		swap2bytes(window_prop->resizeGadgets[i].rect.height);

	}

	for (i = 0; i < MAX_MENU_ITEMS; i++)
		swap4bytes(window_prop->windowMenu[i].sensitive);
	swap4bytes(window_prop->menuItemCount);
	swap4bytes(window_prop->sensitiveItemCount);

	swap4bytes(window_prop->iconInfo.clientState);
	swap4bytes(window_prop->iconInfo.useIconBox);
	swap4bytes(window_prop->iconInfo.X);
	swap4bytes(window_prop->iconInfo.Y);
	swap4bytes(window_prop->iconInfo.Width);
	swap4bytes(window_prop->iconInfo.Height);
	swap4bytes(window_prop->iconInfo.iconFrameWin);

	swap4bytes(window_prop->iconBoxInfo.iconboxX);
	swap4bytes(window_prop->iconBoxInfo.iconboxY);
	swap4bytes(window_prop->iconBoxInfo.iconboxWidth);
	swap4bytes(window_prop->iconBoxInfo.iconboxHeight);
	swap4bytes(window_prop->iconBoxInfo.pointerX);
	swap4bytes(window_prop->iconBoxInfo.pointerY);
	swap4bytes(window_prop->iconBoxInfo.top_arrowX);
	swap4bytes(window_prop->iconBoxInfo.top_arrowY);
	swap4bytes(window_prop->iconBoxInfo.bottom_arrowX);
	swap4bytes(window_prop->iconBoxInfo.bottom_arrowY);
	swap4bytes(window_prop->iconBoxInfo.left_arrowX);
	swap4bytes(window_prop->iconBoxInfo.left_arrowY);
	swap4bytes(window_prop->iconBoxInfo.right_arrowX);
	swap4bytes(window_prop->iconBoxInfo.right_arrowY);
	swap4bytes(window_prop->iconBoxInfo.vert_inc_needed);
	swap4bytes(window_prop->iconBoxInfo.horiz_inc_needed);
	swap4bytes(window_prop->iconBoxInfo.iconFrameWin);
	swap4bytes(window_prop->iconBoxInfo.iconShellWin);
	swap4bytes(window_prop->iconBoxInfo.iconScrollWin);
	swap4bytes(window_prop->iconBoxInfo.hScrollWin);
	swap4bytes(window_prop->iconBoxInfo.vScrollWin);

}


void
AutoInitByteOrderChar(void )
{

	unsigned int	endian;


	/* bootstrap the byteorder if needed */

	if (AutoByteOrderChar == 0) {

		endian = 1;

		if (*((char *)&endian))
			AutoByteOrderChar = 'l';
		else
			AutoByteOrderChar = 'B';

	}

}
