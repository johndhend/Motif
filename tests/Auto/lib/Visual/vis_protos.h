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
/*   $XConsortium: vis_protos.h /main/7 1995/07/14 11:51:36 drk $ */
/***********************************************************************
  	@(#)vis_protos.h	1.3.1.1	Date:1/22/91
  	Author: SJS
	History:
            09/14/90 Create
	Calls:

	Summary:
************************************************************************/
/**************************************************************************
*                               vislib/visual                             *
**************************************************************************/

extern void mvsGetXisStateHash PARAMS((char hash[], short *num_bytes));

extern void mvsPushHashBits PARAMS((char hash[], int *byte_num, int *bit_num,
                                    long bits, int num_bits));

extern Status mvsAllocColor PARAMS((Pixel pixel));

extern Status mvsAllocNamedColor PARAMS((char name[], Pixel *pixel));

extern void mvsFreeColor PARAMS((Pixel pixel));

extern Pixel mvsAllocUniqueColor PARAMS((MvsWidgetInfoRecord *widget_info,
					 int	color_ref));

extern void mvsFreeUniqueColor PARAMS((MvsWidgetInfoRecord *winfo,
				       Pixel pixel));

extern void mvsCheckNamedColors PARAMS((void));

extern int mvsColorAllocNumFromPixel PARAMS((Pixel pixel));

extern void fwrite_short PARAMS((FILE *fd, unsigned int value));

extern unsigned short fread_short PARAMS((FILE *fd));

extern void fwrite_long PARAMS((FILE *fd, unsigned long value));

extern int mvsStringCompare PARAMS((String str1, String str2));

extern Status mvsAllocColorStruct PARAMS((XColor color));

extern unsigned long fread_long PARAMS((FILE *fd));

extern int findstr PARAMS((char in_string[], char search_string[]));

extern void mvsCalcVisualHash PARAMS((MvsWidgetInfoRecord *widget_info,
                                      unsigned char hash[], short *num_bytes));

extern void mvsCheckVisual PARAMS((MvsWidgetInfoRecord *widget_info));

extern void mvsCloseVisual PARAMS((void));

extern void mvsComparePixmapInteractive PARAMS((MvsWidgetInfoRecord *wid_info));

extern void mvsComparePixmapBatch PARAMS((MvsWidgetInfoRecord *widget_info));

extern int mvsCompareIDs PARAMS((unsigned char str1[], short len1,
                                 unsigned char str2[], short len2));

extern void mvsCompressWrite PARAMS((FILE *fp, unsigned char buffer[],
                                     int size));

extern void mvsDecompressRead PARAMS((FILE *fp, unsigned char buffer[],
                                      int size));

extern XImage *mvsGetPixmapImage PARAMS((Pixmap pixmap));

extern void mvsInitFonts PARAMS((void));

extern int mvsGetVisMode PARAMS((void));

extern void mvsOpenVisual PARAMS((void));

extern void mvsSetVisualMode PARAMS((int mode));

extern XmStringCharSet mvsGetCharSet PARAMS((char *requested_char_set));

extern void mvsGeneratePixmap PARAMS((MvsWidgetInfoRecord *widget_info));

extern short mvsGetCh PARAMS((FILE *fp, unsigned char inbuf[],
                              unsigned char *ch));

extern int visLookUpColorCache PARAMS((XColor *color));

extern void visAddToColorCache PARAMS((XColor *color));

extern void visClearColorCache PARAMS((void));


/**************************************************************************
*                               vislib/enums                              *
**************************************************************************/

extern MvsArgVal EnumPixel PARAMS((int n));
extern MvsArgVal EnumPixmap PARAMS((int n));


/**************************************************************************
*                               vislib/other                              *
**************************************************************************/

visGLOBAL void (*visTraceMsg)() visINIT(NULL); /* Trace message func */

visGLOBAL void (*visWarningMsg)() visINIT(NULL); /* Warning message func */

visGLOBAL void (*visErrorMsg)() visINIT(NULL); /* Error message func */

