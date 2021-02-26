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
/*   $XConsortium: tk.h /main/6 1995/07/14 09:45:34 drk $ */
/************************************************************
 *     tk.h -- toolkit-specific dialogue layer
 ************************************************************/

#ifndef _tk_h
#define _tk_h

#include <Xm/Xm.h>
#include "tkdef.h"


extern void TkInit();
extern void TkBeep();
extern void TkExit();
extern void TkUpdateStatus(char *str);

extern Boolean TkTextChanged();
extern void TkTextActUnchangedSince();
extern Boolean TkTextChangedSince();

extern void TkTextClear();
extern void TkTextStore(char *txt);
extern int TkTextFormat();
extern size_t TkTextRetrieve(char **txt, int format);

extern void TkAskFileToOpen();
extern void TkAskFileToSave();
extern void TkAskFileToCopy();
extern void TkAskFileToMove();
extern void TkDoneAskingFile();
extern void TkArrangeToOpen();

extern void TkAskSave();
extern void TkDoneAskingSave();

extern void TkWarn(enum warn_reasons reason);
extern void TkWarnAndAskFileToSave(enum warn_reasons reason);
extern void TkQuestionRemove();

extern XmRenderTable TkUpdateRenditions(Widget w, XmRenderTable rt);

extern void TkRegisterCallbacks();


#endif /* _tk_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
