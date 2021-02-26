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
/*   $XConsortium: ClassTables.h /main/4 1995/07/13 18:00:10 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <testlib.h>

#define NUM_LEGAL_CHILDREN 22
#define NUM_LEGAL_PARENTS 5

typedef struct {
  char * string;
  WidgetClass class;
} StringClassPair;

static StringClassPair parent_table[] = {
  { "xmBulletinBoardWidgetClass", (WidgetClass) NULL },
  { "xmDrawingAreaWidgetClass", (WidgetClass) NULL },
  { "xmFrameWidgetClass", (WidgetClass) NULL  },
  { "xmMainWindowWidgetClass", (WidgetClass) NULL },
  { "xmFormWidgetClass", (WidgetClass) NULL }
};

static StringClassPair child_table[] = {
  { "xmScaleWidgetClass",  (WidgetClass) NULL },
  { "xmScrollBarWidgetClass",  (WidgetClass) NULL },
  { "xmMessageBoxWidgetClass",  (WidgetClass) NULL },
  { "xmSelectionBoxWidgetClass",  (WidgetClass) NULL },
  { "xmCommandWidgetClass",  (WidgetClass) NULL },
  { "xmFileSelectionBoxWidgetClass",  (WidgetClass) NULL },
  { "xmArrowButtonWidgetClass",  (WidgetClass) NULL },
  { "xmListWidgetClass",  (WidgetClass) NULL },
  { "xmSeparatorWidgetClass",  (WidgetClass) NULL },
  { "xmTextWidgetClass",  (WidgetClass) NULL },
  { "xmTextFieldWidgetClass",  (WidgetClass) NULL },
  { "xmLabelWidgetClass",  (WidgetClass) NULL },
  { "xmDrawnButtonWidgetClass",  (WidgetClass) NULL },
  { "xmPushButtonWidgetClass",  (WidgetClass) NULL },
  { "xmToggleButtonWidgetClass",  (WidgetClass) NULL },
  { "xmArrowButtonGadgetClass",  (WidgetClass) NULL },
  { "xmSeparatorGadgetClass",  (WidgetClass) NULL },
  { "xmLabelGadgetClass",  (WidgetClass) NULL },
  { "xmPushButtonGadgetClass",  (WidgetClass) NULL },
  { "xmToggleButtonGadgetClass", (WidgetClass) NULL },
  { "xmBulletinBoardWidgetClass", (WidgetClass) NULL },
  { "xmFormWidgetClass", (WidgetClass) NULL }
};



WidgetClass parent_classes[5];



