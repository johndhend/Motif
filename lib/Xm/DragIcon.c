
#include <localdef.h>

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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: DragIcon.c /main/17 1996/10/14 10:44:37 pascale $"
#endif
#endif
/* (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */



#include <Xm/Xm.h>		/* To make cpp on Sun happy. CR 5943 */
#include <Xm/DisplayP.h>
#include <Xm/DragIconP.h>
#include "TextDIconI.h"
#include "DragCI.h"
#include "DragICCI.h"
#include "DragIconI.h"
#include "ImageCachI.h"
#include "MessagesI.h"
#include "RegionI.h"
#include "ScreenI.h"
#include "XmI.h"

#define MESSAGE1	_XmMMsgDragIcon_0000
#define MESSAGE2	_XmMMsgDragIcon_0001

#define PIXMAP_MAX_WIDTH	128
#define PIXMAP_MAX_HEIGHT	128

#define TheDisplay(dd) (XtDisplayOfObject(XtParent(dd)))

typedef struct {
  unsigned int		width, height;
  int			hot_x, hot_y;
  int			offset_x, offset_y;
  char			*dataName;
  XmConst unsigned char	*data;
  char			*maskDataName;
  XmConst unsigned char	*maskData;
} XmCursorDataRec, *XmCursorData;


/********    Static Function Declarations    ********/

static void DragIconInitialize( 
                        Widget req,
                        Widget new_w,
                        ArgList args,
                        Cardinal *numArgs) ;
static Boolean SetValues( 
                        Widget current,
                        Widget req,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args) ;
static void Destroy( 
                        Widget w) ;

static void ScreenObjectDestroy(
                        Widget w,
                        XtPointer client_data,
                        XtPointer call_data) ;
/********    End Static Function Declarations    ********/

#define valid_width 16
#define valid_height 16
#define valid_x_hot 1
#define valid_y_hot 1
#define valid_x_offset 7
#define valid_y_offset 7

static XmConst unsigned char valid_bits[] = {
   0x00, 0x00, 0xfe, 0x01, 0xfe, 0x00, 0x7e, 0x00, 0x3e, 0x00, 0x1e, 0x00,
   0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static XmConst unsigned char valid_m_bits[] = {
   0xff, 0x07, 0xff, 0x03, 0xff, 0x01, 0xff, 0x00, 0x7f, 0x00, 0x3f, 0x00,
   0x1f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static XmConst XmCursorDataRec validCursorDataRec =
{
   valid_width, valid_height,
   valid_x_hot, valid_y_hot,
   valid_x_offset, valid_y_offset,
   "valid",
   valid_bits,
   "valid_m",
   valid_m_bits,
};
   

#define invalid_width 16
#define invalid_height 16
#define invalid_x_hot 1
#define invalid_y_hot 1
#define invalid_x_offset 7
#define invalid_y_offset 7


static XmConst unsigned char invalid_bits[] = {
   0x00, 0x00, 0xe0, 0x03, 0xf8, 0x0f, 0x1c, 0x1c, 0x0c, 0x1e, 0x06, 0x37,
   0x86, 0x33, 0xc6, 0x31, 0xe6, 0x30, 0x76, 0x30, 0x3c, 0x18, 0x1c, 0x1c,
   0xf8, 0x0f, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00};

static XmConst unsigned char invalid_m_bits[] = {
   0xe0, 0x03, 0xf8, 0x0f, 0xfc, 0x1f, 0xfe, 0x3f, 0x1e, 0x3f, 0x8f, 0x7f,
   0xcf, 0x7f, 0xef, 0x7b, 0xff, 0x79, 0xff, 0x78, 0x7e, 0x3c, 0xfe, 0x3f,
   0xfc, 0x1f, 0xf8, 0x0f, 0xe0, 0x03, 0x00, 0x00};

static XmConst XmCursorDataRec invalidCursorDataRec =
{
   invalid_width, invalid_height,
   invalid_x_hot, invalid_y_hot,
   invalid_x_offset, invalid_y_offset,
   "invalid",
   invalid_bits,
   "invalid_m",
   invalid_m_bits,
};


#define none_width 16
#define none_height 16
#define none_x_hot 1
#define none_y_hot 1 
#define none_x_offset 7
#define none_y_offset 7

static XmConst unsigned char none_bits[] = {
   0x00, 0x00, 0xe0, 0x03, 0xf8, 0x0f, 0x1c, 0x1c, 0x0c, 0x1e, 0x06, 0x37,
   0x86, 0x33, 0xc6, 0x31, 0xe6, 0x30, 0x76, 0x30, 0x3c, 0x18, 0x1c, 0x1c,
   0xf8, 0x0f, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00};

static XmConst unsigned char none_m_bits[] = {
   0xe0, 0x03, 0xf8, 0x0f, 0xfc, 0x1f, 0xfe, 0x3f, 0x1e, 0x3f, 0x8f, 0x7f,
   0xcf, 0x7f, 0xef, 0x7b, 0xff, 0x79, 0xff, 0x78, 0x7e, 0x3c, 0xfe, 0x3f,
   0xfc, 0x1f, 0xf8, 0x0f, 0xe0, 0x03, 0x00, 0x00};

static XmConst XmCursorDataRec noneCursorDataRec =
{
   none_width, none_height,
   none_x_hot, none_y_hot,
   none_x_offset, none_y_offset,
   "none",
   none_bits,
   "none_m",
   none_m_bits,
};

#define move_width 16
#define move_height 16
#define move_x_hot 1
#define move_y_hot 1
#define move_x_offset 14
#define move_y_offset 14

static XmConst unsigned char move_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


static XmConst unsigned char move_m_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static XmConst XmCursorDataRec moveCursorDataRec =
{
   move_width, move_height,
   move_x_hot, move_y_hot,
   move_x_offset, move_y_offset,
   "move",
   move_bits,
   "move_m",
   move_m_bits,
};

#define copy_width 16
#define copy_height 16
#define copy_x_hot 1
#define copy_y_hot 1
#define copy_x_offset 14 
#define copy_y_offset 14

static XmConst unsigned char copy_bits[] = {
   0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x1f, 0x02, 0x11,
   0x02, 0x11, 0x02, 0x11, 0x02, 0x11, 0x02, 0x11, 0xfe, 0x11, 0x20, 0x10,
   0x20, 0x10, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00};


static XmConst unsigned char copy_m_bits[] = {
   0xff, 0x03, 0xff, 0x03, 0xff, 0x03, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f,
   0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f,
   0xf0, 0x3f, 0xf0, 0x3f, 0xf0, 0x3f, 0x00, 0x00};

static XmConst XmCursorDataRec copyCursorDataRec =
{
   copy_width, copy_height,
   copy_x_hot, copy_y_hot,
   copy_x_offset, copy_y_offset,
   "copy",
   copy_bits,
   "copy_m",
   copy_m_bits,
};

#define link_width 16
#define link_height 16
#define link_x_hot 1
#define link_y_hot 1
#define link_x_offset 14
#define link_y_offset 14


static XmConst unsigned char link_bits[] = {
   0x00, 0x00, 0xfe, 0x03, 0x02, 0x02, 0x02, 0x02, 0x32, 0x02, 0x32, 0x3e,
   0x42, 0x20, 0x82, 0x20, 0x02, 0x21, 0x3e, 0x26, 0x20, 0x26, 0x20, 0x20,
   0x20, 0x20, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00};


static XmConst unsigned char link_m_bits[] = {
   0xff, 0x07, 0xff, 0x07, 0xff, 0x07, 0xff, 0x07, 0xff, 0x7f, 0xff, 0x7f,
   0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xf0, 0x7f,
   0xf0, 0x7f, 0xf0, 0x7f, 0xf0, 0x7f, 0x00, 0x00};

static XmConst XmCursorDataRec linkCursorDataRec =
{
   link_width, link_height,
   link_x_hot, link_y_hot,
   link_x_offset, link_y_offset,
   "link",
   link_bits,
   "link_m",
   link_m_bits,
};

#define Altsource16_width 16
#define Altsource16_height 16
#define Altsource16_x_hot  2
#define Altsource16_y_hot  2

static XmConst unsigned char Altsource16_bits[] = {
   0xfc, 0x03, 0x04, 0x06, 0x04, 0x0a, 0x04, 0x12, 0x04, 0x3e, 0x04, 0x20,
   0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20,
   0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0xfc, 0x3f};

static XmConst unsigned char Altsource16_m_bits[] = {
   0xfc, 0x03, 0xfc, 0x07, 0xfc, 0x0f, 0xfc, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f,
   0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f,
   0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f};

static XmConst XmCursorDataRec Altsource16CursorDataRec =
{
   Altsource16_width, Altsource16_height,
   Altsource16_x_hot, Altsource16_y_hot,
   0, 0,
   "Altsource16",
   Altsource16_bits,
   "Altsource16_m",
   Altsource16_m_bits,
};


#define Altsource_width 32
#define Altsource_height 32
#define Altsource_x_hot 3
#define Altsource_y_hot 3 

static XmConst unsigned char Altsource_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x7f, 0x00, 0x10, 0x00, 0xc0, 0x00,
   0x10, 0x00, 0x40, 0x01, 0x10, 0x00, 0x40, 0x02, 0x10, 0x00, 0x40, 0x04,
   0x10, 0x00, 0xc0, 0x0f, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08,
   0x10, 0x00, 0x00, 0x08, 0xf0, 0xff, 0xff, 0x0f};

static XmConst unsigned char Altsource_m_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x7f, 0x00, 0xf0, 0xff, 0xff, 0x00,
   0xf0, 0xff, 0xff, 0x01, 0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x07,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x0f};

static XmConst XmCursorDataRec AltsourceCursorDataRec =
{
   Altsource_width, Altsource_height,
   Altsource_x_hot, Altsource_y_hot,
   0, 0,
   "Altsource",
   Altsource_bits,
   "Altsource_m",
   Altsource_m_bits,
};

/*
 *  The 16x16 default icon data.
 */

#define state16_width 16
#define state16_height 16
#define state16_x_hot 1
#define state16_y_hot 1
#define state16_x_offset -8
#define state16_y_offset -2
static XmConst unsigned char state16_bits[] =
{
   0x00, 0x00, 0x3e, 0x00, 0x1e, 0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst unsigned char state16M_bits[] =
{
   0x7f, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x1f, 0x00, 0x0f, 0x00,
   0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst XmCursorDataRec state16CursorDataRec =
{
    state16_width, state16_height,
    state16_x_hot, state16_y_hot,
    state16_x_offset, state16_y_offset,
    "state16",
    state16_bits,
    "state16M",
    state16M_bits,
};

#define move16_width 16
#define move16_height 16
#define move16_x_hot 1
#define move16_y_hot 1
#define move16_x_offset -8
#define move16_y_offset -2
static XmConst unsigned char move16_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x07, 0x40, 0x0c,
   0x40, 0x1c, 0x40, 0x3c, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20,
   0x40, 0x20, 0x40, 0x20, 0xc0, 0x3f, 0x00, 0x00
};
static XmConst unsigned char move16M_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0xe0, 0x1f, 0xe0, 0x3f,
   0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f,
   0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f, 0xe0, 0x7f
};
static XmConst XmCursorDataRec move16CursorDataRec =
{
    move16_width, move16_height,
    move16_x_hot, move16_y_hot,
    move16_x_offset, move16_y_offset,
    "move16",
    move16_bits,
    "move16M",
    move16M_bits,
};

#define copy16_width 16
#define copy16_height 16
#define copy16_x_hot 1
#define copy16_y_hot 1
#define copy16_x_offset -8
#define copy16_y_offset -2
static XmConst unsigned char copy16_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x80, 0x18, 0x80, 0x38, 0xb0, 0x78,
   0x90, 0x40, 0x90, 0x40, 0x90, 0x40, 0x90, 0x40, 0x90, 0x40, 0x90, 0x7f,
   0x10, 0x00, 0x10, 0x08, 0xf0, 0x0f, 0x00, 0x00
};
static XmConst unsigned char copy16M_bits[] =
{
   0x00, 0x00, 0xc0, 0x1f, 0xc0, 0x3f, 0xc0, 0x7f, 0xf8, 0xff, 0xf8, 0xff,
   0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff,
   0xf8, 0xff, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f
};
static XmConst XmCursorDataRec copy16CursorDataRec =
{
    copy16_width, copy16_height,
    copy16_x_hot, copy16_y_hot,
    copy16_x_offset, copy16_y_offset,
    "copy16",
    copy16_bits,
    "copy16M",
    copy16M_bits,
};

#define link16_width 16
#define link16_height 16
#define link16_x_hot 1
#define link16_y_hot 1
#define link16_x_offset -8
#define link16_y_offset -2
static XmConst unsigned char link16_bits[] =
{
   0x00, 0x00, 0x80, 0x0f, 0x80, 0x18, 0x80, 0x38, 0x80, 0x78, 0xb8, 0x40,
   0x88, 0x4e, 0x88, 0x4c, 0x08, 0x4a, 0x08, 0x41, 0xa8, 0x7c, 0x68, 0x00,
   0xe8, 0x04, 0x08, 0x04, 0xf8, 0x07, 0x00, 0x00
};
static XmConst unsigned char link16M_bits[] =
{
   0xc0, 0x1f, 0xc0, 0x3f, 0xc0, 0x7f, 0xc0, 0xff, 0xfc, 0xff, 0xfc, 0xff,
   0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff,
   0xfc, 0x0f, 0xfc, 0x0f, 0xfc, 0x0f, 0xfc, 0x0f
};
static XmConst XmCursorDataRec link16CursorDataRec =
{
    link16_width, link16_height,
    link16_x_hot, link16_y_hot,
    link16_x_offset, link16_y_offset,
    "link16",
    link16_bits,
    "link16M",
    link16M_bits,
};

#define source16_width 16
#define source16_height 16
#define source16_x_hot 0
#define source16_y_hot 0
static XmConst unsigned char source16_bits[] = 
{
   0x00, 0x00, 0xaa, 0xca, 0x54, 0x85, 0xaa, 0xca, 0x54, 0xe0, 0x2a, 0xe3,
   0x94, 0x81, 0xea, 0xf8, 0x54, 0xd4, 0xaa, 0xac, 0x94, 0xd9, 0xca, 0xac,
   0x64, 0xd6, 0x32, 0xab, 0xa4, 0xd6, 0xfe, 0xff
};
static XmConst XmCursorDataRec source16CursorDataRec =
{
    source16_width, source16_height,
    source16_x_hot, source16_y_hot,
    0, 0,
    "source16",
    /* a file icon */
    source16_bits,
    NULL,
    NULL,
};

/*
 *  The 32x32 default icon data.
 */

#define state32_width 32
#define state32_height 32
#define state32_x_hot 1
#define state32_y_hot 1
#define state32_x_offset -16
#define state32_y_offset -4
static XmConst unsigned char state32_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
   0x1e, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00,
   0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst unsigned char state32M_bits[] =
{
   0x0f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00,
   0x7f, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
   0xff, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst XmCursorDataRec state32CursorDataRec =
{
    state32_width, state32_height,
    state32_x_hot, state32_y_hot,
    state32_x_offset, state32_y_offset,
    "state32",
    state32_bits,
    "state32M",
    state32M_bits,
};

#define move32_width 32
#define move32_height 32
#define move32_x_hot 1
#define move32_y_hot 1
#define move32_x_offset -16
#define move32_y_offset -4
static XmConst unsigned char move32_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00,
   0x20, 0xe0, 0x00, 0x00, 0x20, 0xe0, 0x01, 0x00, 0x20, 0xe0, 0x03, 0x00,
   0x20, 0xe0, 0x07, 0x00, 0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00,
   0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00,
   0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00,
   0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00,
   0xe0, 0xff, 0x0f, 0x00, 0xc0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst unsigned char move32M_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf0, 0x7f, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00,
   0xf0, 0xff, 0x03, 0x00, 0xf0, 0xff, 0x07, 0x00, 0xf0, 0xff, 0x0f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xe0, 0xff, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst XmCursorDataRec move32CursorDataRec =
{
    move32_width, move32_height,
    move32_x_hot, move32_y_hot,
    move32_x_offset, move32_y_offset,
    "move32",
    move32_bits,
    "move32M",
    move32M_bits,
};

#define copy32_width 32
#define copy32_height 32
#define copy32_x_hot 1
#define copy32_y_hot 1
#define copy32_x_offset -16
#define copy32_y_offset -4
static XmConst unsigned char copy32_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00,
   0x20, 0xe0, 0x00, 0x00, 0x20, 0xe0, 0x01, 0x00, 0x20, 0xe0, 0x03, 0x00,
   0x20, 0xe0, 0x07, 0x00, 0x20, 0x00, 0x0c, 0x00, 0x20, 0x00, 0x0c, 0x00,
   0x20, 0x00, 0x2c, 0x00, 0x20, 0x00, 0x6c, 0x00, 0x20, 0x00, 0xec, 0x00,
   0x20, 0x00, 0x8c, 0x01, 0x20, 0x00, 0x8c, 0x01, 0x20, 0x00, 0x8c, 0x01,
   0x20, 0x00, 0x8c, 0x01, 0x20, 0x00, 0x8c, 0x01, 0x20, 0x00, 0x8c, 0x01,
   0xe0, 0xff, 0x8f, 0x01, 0xc0, 0xff, 0x8f, 0x01, 0x00, 0x00, 0x80, 0x01,
   0x00, 0x04, 0x80, 0x01, 0x00, 0x04, 0x80, 0x01, 0x00, 0xfc, 0xff, 0x01,
   0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00
};
static XmConst unsigned char copy32M_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf0, 0x7f, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00,
   0xf0, 0xff, 0x03, 0x00, 0xf0, 0xff, 0x07, 0x00, 0xf0, 0xff, 0x0f, 0x00,
   0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf0, 0xff, 0x7f, 0x00,
   0xf0, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0x01, 0xf0, 0xff, 0xff, 0x03,
   0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03,
   0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03,
   0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x03,
   0x00, 0xfe, 0xff, 0x03, 0x00, 0xfe, 0xff, 0x03, 0x00, 0xfe, 0xff, 0x03,
   0x00, 0xfe, 0xff, 0x03, 0x00, 0xfc, 0xff, 0x03
};
static XmConst XmCursorDataRec copy32CursorDataRec =
{
    copy32_width, copy32_height,
    copy32_x_hot, copy32_y_hot,
    copy32_x_offset, copy32_y_offset,
    "copy32",
    copy32_bits,
    "copy32M",
    copy32M_bits,
};

#define link32_width 32
#define link32_height 32
#define link32_x_hot 1
#define link32_y_hot 1
#define link32_x_offset -16
#define link32_y_offset -4
static XmConst unsigned char link32_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00, 0x00, 0x20, 0x30, 0x00, 0x00,
   0x20, 0x70, 0x00, 0x00, 0x20, 0xf0, 0x00, 0x00, 0x20, 0xf0, 0x01, 0x00,
   0x20, 0x00, 0x7b, 0x00, 0x20, 0x00, 0xc3, 0x00, 0x20, 0x04, 0xc3, 0x01,
   0x20, 0x06, 0xc3, 0x03, 0x20, 0x0f, 0xc2, 0x07, 0x20, 0x36, 0x00, 0x0c,
   0x20, 0xc4, 0x00, 0x0c, 0x20, 0x00, 0x23, 0x0c, 0x20, 0x00, 0x6c, 0x0c,
   0x20, 0x00, 0xf0, 0x0c, 0xe0, 0xff, 0x61, 0x0c, 0xc0, 0xff, 0x23, 0x0c,
   0x00, 0x00, 0x00, 0x0c, 0x00, 0x80, 0x00, 0x0c, 0x00, 0x80, 0x00, 0x0c,
   0x00, 0x80, 0xff, 0x0f, 0x00, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst unsigned char link32M_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf0, 0x3f, 0x00, 0x00, 0xf0, 0x7f, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00,
   0xf0, 0xff, 0x01, 0x00, 0xf0, 0xff, 0x03, 0x00, 0xf0, 0xff, 0xff, 0x00,
   0xf0, 0xff, 0xff, 0x01, 0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x07,
   0xf0, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x1f,
   0xf0, 0xff, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x1f,
   0xf0, 0xff, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x1f,
   0xe0, 0xff, 0xff, 0x1f, 0x00, 0xc0, 0xff, 0x1f, 0x00, 0xc0, 0xff, 0x1f,
   0x00, 0xc0, 0xff, 0x1f, 0x00, 0xc0, 0xff, 0x1f, 0x00, 0x80, 0xff, 0x1f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static XmConst XmCursorDataRec link32CursorDataRec =
{
    link32_width, link32_height,
    link32_x_hot, link32_y_hot,
    link32_x_offset, link32_y_offset,
    "link32",
    link32_bits,
    "link32M",
    link32M_bits,
};

#define source32_width 32
#define source32_height 32
#define source32_x_hot 0
#define source32_y_hot 0
static XmConst unsigned char source32_bits[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x54, 0x55, 0x55, 0xd5,
   0xa8, 0xaa, 0xaa, 0xea, 0x54, 0x55, 0x55, 0xd1, 0xa8, 0xaa, 0xaa, 0xe0,
   0x54, 0x55, 0x55, 0xd0, 0xa8, 0xaa, 0xaa, 0xf0, 0x54, 0x55, 0x55, 0xd9,
   0xa8, 0xaa, 0x00, 0xee, 0x54, 0x55, 0x00, 0xd6, 0xa8, 0x2a, 0x3f, 0xea,
   0x54, 0x95, 0x05, 0xd7, 0xa8, 0xea, 0x82, 0xee, 0x54, 0x45, 0xc1, 0xd5,
   0xa8, 0xaa, 0xf4, 0x81, 0x54, 0xd5, 0x78, 0xff, 0xa8, 0xaa, 0xa0, 0xea,
   0x54, 0x95, 0x41, 0xd5, 0xa8, 0x4a, 0x87, 0xea, 0x54, 0x85, 0x0d, 0xd5,
   0xa8, 0xc2, 0x9a, 0xea, 0x54, 0x61, 0x05, 0xd5, 0xa8, 0xb0, 0xc2, 0xea,
   0x54, 0x58, 0x61, 0xd5, 0x28, 0xac, 0xb0, 0xea, 0x14, 0x56, 0x58, 0xd5,
   0x08, 0xab, 0xa8, 0xea, 0x14, 0x55, 0x51, 0xd5, 0x28, 0xaa, 0xaa, 0xea,
   0xfc, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff,
};

static XmConst XmCursorDataRec source32CursorDataRec =
{
    source32_width, source32_height,
    source32_x_hot, source32_y_hot,
    0, 0,
    "source32",
    /* a file icon */
    source32_bits,
    NULL,
    NULL,
};

typedef struct _XmQuarkToCursorEntryRec{
  XrmQuark		  *xrmName;
  XmConst XmCursorDataRec *cursor;
} XmQuarkToCursorEntryRec, *XmQuarkToCursorEntry;

/* Used to be XmConst, but this was not linking on Solaris */
static XmQuarkToCursorEntryRec AltquarkToCursorTable[] = {
    { &_XmValidCursorIconQuark,  &state32CursorDataRec},
    { &_XmInvalidCursorIconQuark,&state32CursorDataRec},
    { &_XmNoneCursorIconQuark,   &state32CursorDataRec},
    { &_XmMoveCursorIconQuark,   &move32CursorDataRec},
    { &_XmCopyCursorIconQuark,   &copy32CursorDataRec},
    { &_XmLinkCursorIconQuark,   &link32CursorDataRec},
    { &_XmDefaultDragIconQuark,  &AltsourceCursorDataRec},
};

/* Used to be XmConst, but this was not linking on Solaris */
static XmQuarkToCursorEntryRec AltquarkTo16CursorTable[] = {
    { &_XmValidCursorIconQuark,  &validCursorDataRec},
    { &_XmInvalidCursorIconQuark,&invalidCursorDataRec},
    { &_XmNoneCursorIconQuark,   &noneCursorDataRec},
    { &_XmMoveCursorIconQuark,   &moveCursorDataRec},
    { &_XmCopyCursorIconQuark,   &copyCursorDataRec},
    { &_XmLinkCursorIconQuark,   &linkCursorDataRec},
    { &_XmDefaultDragIconQuark,  &Altsource16CursorDataRec},
};

/* Used to be XmConst, but this was not linking on Solaris */
static XmQuarkToCursorEntryRec	quarkToCursorTable[] = {
    {&_XmValidCursorIconQuark, 	&state32CursorDataRec},
    {&_XmInvalidCursorIconQuark,&state32CursorDataRec},
    {&_XmNoneCursorIconQuark, 	&state32CursorDataRec},
    {&_XmMoveCursorIconQuark,	&move32CursorDataRec},
    {&_XmCopyCursorIconQuark,	&copy32CursorDataRec},
    {&_XmLinkCursorIconQuark,	&link32CursorDataRec},
    {&_XmDefaultDragIconQuark, 	&source32CursorDataRec},
};

/* Used to be XmConst, but this was not linking on Solaris */
static XmQuarkToCursorEntryRec	quarkTo16CursorTable[] = {
    {&_XmValidCursorIconQuark, 	&state16CursorDataRec},
    {&_XmInvalidCursorIconQuark,&state16CursorDataRec},
    {&_XmNoneCursorIconQuark, 	&state16CursorDataRec},
    {&_XmMoveCursorIconQuark,	&move16CursorDataRec},
    {&_XmCopyCursorIconQuark,	&copy16CursorDataRec},
    {&_XmLinkCursorIconQuark,	&link16CursorDataRec},
    {&_XmDefaultDragIconQuark, 	&source16CursorDataRec},
};

#undef Offset
#define Offset(x) (XtOffsetOf( struct _XmDragIconRec, drag.x))

static XContext _XmTextualDragIconContext = (XContext) NULL;

static XtResource resources[]=
{
    {
	XmNdepth, XmCDepth, XmRInt,
        sizeof(int), Offset(depth), 
        XmRImmediate, (XtPointer)1,
    },
    {
	XmNwidth, XmCWidth, XmRHorizontalDimension,
	sizeof(Dimension), Offset(width),
	XmRImmediate, (XtPointer) 0,
    },
    {
	XmNheight, XmCHeight, XmRVerticalDimension,
	sizeof(Dimension), Offset(height),
	XmRImmediate, (XtPointer) 0,
    },
    {
	XmNhotX, XmCHot, XmRPosition,
        sizeof(Position), Offset(hot_x), 
        XmRImmediate, (XtPointer)0,
    },
    {
	XmNhotY, XmCHot, XmRPosition,
        sizeof(Position), Offset(hot_y),
        XmRImmediate, (XtPointer)0,
    },
    {
	XmNmask, XmCPixmap, XmRBitmap,
        sizeof(Pixmap), Offset(mask),
        XmRImmediate, (XtPointer)XmUNSPECIFIED_PIXMAP,
    },
    {
	XmNpixmap, XmCPixmap, XmRDynamicPixmap,
        sizeof(Pixmap), Offset(pixmap),
        XmRImmediate, (XtPointer)XmUNSPECIFIED_PIXMAP,
    },
    {
	XmNoffsetX, XmCOffset, XmRPosition,
        sizeof(Position), Offset(offset_x), 
        XmRImmediate, (XtPointer)0,
    },
    {
	XmNoffsetY, XmCOffset, XmRPosition,
        sizeof(Position), Offset(offset_y),
        XmRImmediate, (XtPointer)0,
    },
    {
	XmNattachment, XmCAttachment, XmRIconAttachment,
		sizeof(unsigned char), Offset(attachment),
		XmRImmediate, (XtPointer) XmATTACH_NORTH_WEST
    },
};

externaldef(xmdragiconclassrec)
XmDragIconClassRec xmDragIconClassRec = {
    {	
	(WidgetClass) &objectClassRec,	/* superclass		*/   
	"XmDragIcon",			/* class_name 		*/   
	sizeof(XmDragIconRec),		/* size 		*/   
	NULL,	                        /* Class Initializer 	*/   
	NULL,				/* class_part_init 	*/ 
	FALSE, 				/* Class init'ed ? 	*/   
	DragIconInitialize,		/* initialize         	*/   
	NULL, 				/* initialize_notify    */ 
	NULL,	 			/* realize            	*/   
	NULL,	 			/* actions            	*/   
	0,				/* num_actions        	*/   
	(XtResourceList)resources,	/* resources          	*/   
	XtNumber(resources),		/* resource_count     	*/   
	NULLQUARK, 			/* xrm_class          	*/   
	FALSE, 				/* compress_motion    	*/   
	XtExposeNoCompress, 		/* compress_exposure  	*/   
	FALSE, 				/* compress_enterleave	*/   
	FALSE, 				/* visible_interest   	*/   
	Destroy,			/* destroy            	*/   
	NULL,		 		/* resize             	*/   
	NULL,				/* expose             	*/   
	SetValues, 			/* set_values		*/
	NULL, 				/* set_values_hook      */ 
	XtInheritSetValuesAlmost,	/* set_values_almost    */ 
	NULL,				/* get_values_hook      */ 
	NULL, 				/* accept_focus       	*/   
	XtVersion, 			/* intrinsics version 	*/   
	NULL, 				/* callback offsets   	*/   
	NULL,				/* tm_table           	*/   
	NULL, 				/* query_geometry       */ 
	NULL,				/* display_accelerator  */ 
	NULL, 				/* extension            */ 
    },	
    {					/* dragIcon		*/
	NULL,				/* extension		*/
    },
};

externaldef(dragIconobjectclass) WidgetClass 
      xmDragIconObjectClass = (WidgetClass) &xmDragIconClassRec;


/************************************************************************
 *
 *  DragIconInitialize
 *
 ************************************************************************/

/*ARGSUSED*/
static void 
DragIconInitialize(
        Widget req,		/* unused */
        Widget new_w,
        ArgList args,		/* unused */
        Cardinal *numArgs )	/* unused */
{
    XmDragIconObject	dragIcon = (XmDragIconObject)new_w;
    Screen		*screen = XtScreenOfObject(XtParent(dragIcon));
    Display *		display = XtDisplay(new_w);
    XmDisplay		xmdpy = (XmDisplay) XmGetXmDisplay(display);
    Boolean		use_alt = xmdpy -> display.enable_drag_icon;

    dragIcon->drag.isDirty = False;
    if (dragIcon->drag.pixmap == XmUNSPECIFIED_PIXMAP) {

	XmCursorData	cursorData = NULL;
	Cardinal	i = 0;
	XImage 		*image = NULL;
	Dimension	maxW, maxH;

	/*
	 *  If this is one of the default cursors (recognized by name)
	 *  then we use the built in images to generate the pixmap, its
	 *  mask (as appropriate), and its dimensions and hot spot.
	 */ 

	XmeQueryBestCursorSize (XtParent(dragIcon), &maxW, &maxH);

	if (maxW < 32 || maxH < 32) {
	    /*
	     *  Use small icons.
	     */
	  if (! use_alt) {
	    for (i = 0; i < XtNumber(quarkTo16CursorTable); i++) {
	      if ((*(quarkTo16CursorTable[i].xrmName)) ==
		  dragIcon->object.xrm_name) {
		cursorData = (XmCursorData) quarkTo16CursorTable[i].cursor;
		break;
	      }
	    }
	  } else {
	    for (i = 0; i < XtNumber(quarkTo16CursorTable); i++) {
	      if ((*(AltquarkTo16CursorTable[i].xrmName)) ==
		  dragIcon->object.xrm_name) {
		cursorData = (XmCursorData) AltquarkTo16CursorTable[i].cursor;
		break;
	      }
	    }
	  }
	}
	else {
	    /*
	     *  Use large icons.
	     */
	  if (! use_alt) {
	    for (i = 0; i < XtNumber(quarkToCursorTable); i++) {
	      if ((*(quarkToCursorTable[i].xrmName)) ==
		  dragIcon->object.xrm_name) {
		cursorData = (XmCursorData) quarkToCursorTable[i].cursor;
		break;
	      }
	    }
	  } else {
	    for (i = 0; i < XtNumber(quarkToCursorTable); i++) {
	      if ((*(AltquarkToCursorTable[i].xrmName)) ==
		  dragIcon->object.xrm_name) {
		cursorData = (XmCursorData) AltquarkToCursorTable[i].cursor;
		break;
	      }
	    }
	  }
	}

	if (cursorData) {
	    dragIcon->drag.depth = 1;
	    dragIcon->drag.width = cursorData->width;
	    dragIcon->drag.height = cursorData->height;
	    dragIcon->drag.hot_x = cursorData->hot_x;
	    dragIcon->drag.hot_y = cursorData->hot_y;
	    dragIcon->drag.offset_x = cursorData->offset_x;
	    dragIcon->drag.offset_y = cursorData->offset_y;

	    _XmCreateImage(image, display, (char *)cursorData->data,
			dragIcon->drag.width, dragIcon->drag.height, 
			LSBFirst);
    
	    _XmInstallImage(image, cursorData->dataName, 	
		            (int)dragIcon->drag.hot_x, 
		            (int)dragIcon->drag.hot_y);
	    dragIcon->drag.pixmap =
		XmGetPixmapByDepth (screen, cursorData->dataName, 1, 0, 1);
    
	    if (cursorData->maskData) {
		_XmCreateImage(image, display, (char *)cursorData->maskData,
			    dragIcon->drag.width, dragIcon->drag.height, 
			    LSBFirst);
	
		_XmInstallImage (image, cursorData->maskDataName, 0, 0);
	
		dragIcon->drag.mask =
		    XmGetPixmapByDepth(screen, cursorData->maskDataName, 
				       1, 0, 1);
	    }
	}
	dragIcon->drag.region = NULL;
    }
    else if (dragIcon->drag.pixmap != XmUNSPECIFIED_PIXMAP) {
      int		depth;
      unsigned int	width, height;
      int		hot_x, hot_y;
      String		name;
      Pixel		foreground, background;
      if ((dragIcon->drag.width == 0) || (dragIcon->drag.height == 0)) {
	    if (XmeGetPixmapData(screen,
				 dragIcon->drag.pixmap,
				 &name,
				 &depth, 
				 &foreground, &background,
				 &hot_x, &hot_y,
				 &width, &height)) {
		dragIcon->drag.depth = depth;
		dragIcon->drag.hot_x = hot_x;
		dragIcon->drag.hot_y = hot_y;
		dragIcon->drag.width = (Dimension)width;
		dragIcon->drag.height = (Dimension)height;
	    }
	    else {
		dragIcon->drag.width = 
		  dragIcon->drag.height = 0;
		dragIcon->drag.pixmap = XmUNSPECIFIED_PIXMAP;
		XmeWarning ((Widget) new_w, MESSAGE1);
	    }
	}
        if (dragIcon->drag.mask != XmUNSPECIFIED_PIXMAP) {
           XImage * image;

           if (dragIcon->drag.width > 0 && dragIcon->drag.height > 0) {
                image = XGetImage(display, (Drawable) dragIcon->drag.mask,
				  0, 0, dragIcon->drag.width,
				  dragIcon->drag.height, 1L, XYPixmap);

	        dragIcon->drag.region = (Region) _XmRegionFromImage(image);
		if (image)
		    XDestroyImage(image);
            } else
	        dragIcon->drag.region = NULL;
	   
        } else
	   dragIcon->drag.region = NULL;
    }

    dragIcon->drag.restore_region = NULL;
    dragIcon->drag.x_offset = 0;
    dragIcon->drag.y_offset = 0;

    if (dragIcon->drag.pixmap == XmUNSPECIFIED_PIXMAP) {
	XmeWarning ((Widget) new_w, MESSAGE2);
    }
}

/************************************************************************
 *
 *  XmCreateDragIcon
 *
 ************************************************************************/

Widget 
XmCreateDragIcon(
        Widget parent,
        String name,
        ArgList argList,
        Cardinal argCount )
{
    return (XtCreateWidget (name, xmDragIconObjectClass, parent,
		            argList, argCount));
}

/************************************************************************
 *
 *  _XmDestroyDefaultDragIcon ()
 *
 *  A default XmDragIcon's pixmap and mask (if present) were installed in
 *  the Xm pixmap cache from built-in images when the XmDragIcon was
 *  initialized.
 ************************************************************************/

void 
_XmDestroyDefaultDragIcon(
	XmDragIconObject icon)
{
    Screen	*screen = XtScreenOfObject(XtParent(icon));

    if (icon->drag.pixmap != XmUNSPECIFIED_PIXMAP) {
	XmDestroyPixmap (screen, icon->drag.pixmap);
	icon->drag.pixmap = XmUNSPECIFIED_PIXMAP;
    }
    if (icon->drag.mask != XmUNSPECIFIED_PIXMAP) {
	XmDestroyPixmap (screen, icon->drag.mask);
	icon->drag.mask = XmUNSPECIFIED_PIXMAP;
    }
    XtDestroyWidget ((Widget) icon);
}

/************************************************************************
 *
 *  _XmDragIconIsDirty ()
 *
 *  Test the isDirty member of XmDragIconObject.
 ************************************************************************/

Boolean 
_XmDragIconIsDirty(
	XmDragIconObject icon)
{
    return (icon->drag.isDirty);
}

/************************************************************************
 *
 *  _XmDragIconClean ()
 *
 *  Clear the isDirty member of XmDragIconObjects.
 ************************************************************************/

void
_XmDragIconClean(
	XmDragIconObject icon1,
	XmDragIconObject icon2,
	XmDragIconObject icon3)
{
    if (icon1)
	icon1->drag.isDirty = False;
    if (icon2)
	icon2->drag.isDirty = False;
    if (icon3)
	icon3->drag.isDirty = False;
}

/************************************************************************
 *
 *  SetValues
 *
 ************************************************************************/

/*ARGSUSED*/
static Boolean
SetValues(
    Widget	current,
    Widget	req,		/* unused */
    Widget	new_w,
    ArgList	args,		/* unused */
    Cardinal	*num_args)	/* unused */
{
    XmDragIconObject	newIcon = (XmDragIconObject) new_w;
    XmDragIconObject	oldIcon = (XmDragIconObject) current;

    /*
     *  Mark the icon as dirty if any of its resources have changed.
     */

    if ((newIcon->drag.depth != oldIcon->drag.depth) ||
	(newIcon->drag.pixmap != oldIcon->drag.pixmap) ||
	(newIcon->drag.mask != oldIcon->drag.mask) ||
	(newIcon->drag.width != oldIcon->drag.width) ||
	(newIcon->drag.height != oldIcon->drag.height) ||
	(newIcon->drag.attachment != oldIcon->drag.attachment) ||
	(newIcon->drag.offset_x != oldIcon->drag.offset_x) ||
        (newIcon->drag.offset_y != oldIcon->drag.offset_y) ||
	(newIcon->drag.hot_x != oldIcon->drag.hot_x) ||
        (newIcon->drag.hot_y != oldIcon->drag.hot_y)) {

	newIcon->drag.isDirty = True;
    }

    if (newIcon->drag.mask != oldIcon->drag.mask) {
       if (newIcon->drag.mask != XmUNSPECIFIED_PIXMAP) {
	   XImage * image;

	   if (newIcon->drag.width > 0 && newIcon->drag.height > 0) {
		image = XGetImage(XtDisplay(new_w),
				  (Drawable) newIcon->drag.mask,
				  0, 0, newIcon->drag.width,
				  newIcon->drag.height, 1L, XYPixmap);

		newIcon->drag.region = (Region) _XmRegionFromImage(image);
		if (image)
		    XDestroyImage(image);
	    }
	    else
		newIcon->drag.region = NULL;
       }
       else
	    newIcon->drag.region = NULL;

       if (oldIcon->drag.region) {
	  XDestroyRegion(oldIcon->drag.region);
	  oldIcon->drag.region = NULL;
       }
    }

    return False;
}

/************************************************************************
 *
 *  Destroy
 *
 *  Remove any cached cursors referencing this icon.
 ************************************************************************/

static void 
Destroy(
        Widget w )
{
     XmDragIconObject	dragIcon = (XmDragIconObject) w;

     if (dragIcon->drag.region != NULL) {
        XDestroyRegion(dragIcon->drag.region);
        dragIcon->drag.region = NULL;
     }

     if (dragIcon->drag.restore_region != NULL) {
        XDestroyRegion(dragIcon->drag.restore_region);
        dragIcon->drag.restore_region = NULL;
     }

    _XmScreenRemoveFromCursorCache (dragIcon);
}



/* ARGSUSED */
static void
ScreenObjectDestroy(
        Widget w,
        XtPointer client_data,
        XtPointer call_data )
{
   Widget drag_icon = (Widget) client_data;

   XtDestroyWidget(drag_icon);  /* destroy drag_icon */
   _XmProcessLock();
   XDeleteContext(XtDisplay(w), RootWindowOfScreen(XtScreen(w)),  
		  _XmTextualDragIconContext);
   _XmProcessUnlock();
}


Widget
XmeGetTextualDragIcon(
        Widget w )
{
    Widget drag_icon;
    Arg args[10];
    int n = 0;
    Pixmap icon, icon_mask;
    Screen *screen = XtScreen(w);
    XImage *image = NULL;
    Window      root;
    Widget screen_object;
    XmDisplay dpy;
    Boolean use_alt;
    XContext loc_context;
    _XmWidgetToAppContext(w);

   _XmAppLock(app);
   root = RootWindowOfScreen(XtScreen(w));
   dpy = (XmDisplay) XmGetXmDisplay(XtDisplay(w));
   use_alt = dpy -> display.enable_drag_icon;

   _XmProcessLock();
   if (_XmTextualDragIconContext == (XContext) NULL)
      _XmTextualDragIconContext = XUniqueContext();
   loc_context = _XmTextualDragIconContext;
   _XmProcessUnlock();

   if (XFindContext(XtDisplay(w), root,
                    loc_context, (char **) &drag_icon)) {
       Dimension height, width;
       int x_hot, y_hot;
       XmConst unsigned char *icon_bits;
       XmConst unsigned char *icon_mask_bits;

       XmeQueryBestCursorSize(w, &width, &height);

       if (width < 64 && height < 64) {
	 if (use_alt) {
	   icon_bits = XmTEXTUAL_DRAG_ICON_BITS_Alt_16;
	   icon_mask_bits = XmTEXTUAL_DRAG_ICON_MASK_BITS_Alt_16;
	   height = XmTEXTUAL_DRAG_ICON_HEIGHT_Alt_16;
	   width = XmTEXTUAL_DRAG_ICON_WIDTH_Alt_16;
	   x_hot = XmTEXTUAL_DRAG_ICON_X_HOT_Alt_16;
	   y_hot = XmTEXTUAL_DRAG_ICON_Y_HOT_Alt_16;
	 } else {
	   icon_bits = XmTEXTUAL_DRAG_ICON_BITS_16;
	   icon_mask_bits = XmTEXTUAL_DRAG_ICON_MASK_BITS_16;
	   height = XmTEXTUAL_DRAG_ICON_HEIGHT_16;
	   width = XmTEXTUAL_DRAG_ICON_WIDTH_16;
	   x_hot = XmTEXTUAL_DRAG_ICON_X_HOT_16;
	   y_hot = XmTEXTUAL_DRAG_ICON_Y_HOT_16;
	 }
       } else {
	 if (use_alt) {
	   icon_bits = XmTEXTUAL_DRAG_ICON_BITS_Alt_32;
	   icon_mask_bits = XmTEXTUAL_DRAG_ICON_MASK_BITS_Alt_32;
	   height = XmTEXTUAL_DRAG_ICON_HEIGHT_Alt_32;
	   width = XmTEXTUAL_DRAG_ICON_WIDTH_Alt_32;
	   x_hot = XmTEXTUAL_DRAG_ICON_X_HOT_Alt_32;
	   y_hot = XmTEXTUAL_DRAG_ICON_Y_HOT_Alt_32;
	 } else {
	   icon_bits = XmTEXTUAL_DRAG_ICON_BITS_32;
	   icon_mask_bits = XmTEXTUAL_DRAG_ICON_MASK_BITS_32;
	   height = XmTEXTUAL_DRAG_ICON_HEIGHT_32;
	   width = XmTEXTUAL_DRAG_ICON_WIDTH_32;
	   x_hot = XmTEXTUAL_DRAG_ICON_X_HOT_32;
	   y_hot = XmTEXTUAL_DRAG_ICON_Y_HOT_32;
	 }
       }

       _XmCreateImage(image, XtDisplay(w), (char *)icon_bits, 
		width, height, LSBFirst);
       _XmInstallImage(image, "XmTextualDragIcon", x_hot, y_hot);
       icon = XmGetPixmapByDepth(screen, "XmTextualDragIcon", 1, 0, 1);

       _XmCreateImage(image, XtDisplay(w), (char *)icon_mask_bits, 
		   width, height, LSBFirst);
       _XmInstallImage(image, "XmTextualDragIconMask", x_hot, y_hot);
       icon_mask = XmGetPixmapByDepth(screen, "XmTextualDragIconMask", 
				      1, 0, 1);
       screen_object = XmGetXmScreen(XtScreen(w));

       XtSetArg(args[n], XmNhotX, x_hot);  n++;
       XtSetArg(args[n], XmNhotY, y_hot);  n++;
       XtSetArg(args[n], XmNheight, height);  n++;
       XtSetArg(args[n], XmNwidth, width);  n++;
       XtSetArg(args[n], XmNmaxHeight, height);  n++;
       XtSetArg(args[n], XmNmaxWidth, width);  n++;
       XtSetArg(args[n], XmNmask, icon_mask);  n++;
       XtSetArg(args[n], XmNpixmap, icon);  n++;
       drag_icon = XtCreateWidget("drag_icon", xmDragIconObjectClass,
                                  screen_object, args, n);

       XSaveContext(XtDisplay(w), root,
                    loc_context, (char *) drag_icon);

       XtAddCallback(screen_object, XmNdestroyCallback, ScreenObjectDestroy,
                       (XtPointer) drag_icon);
   }

   _XmAppUnlock(app);
   return drag_icon;
}

