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
static char *rcsidinterfaceH = "$XConsortium: interface.h /main/6 1995/07/14 09:47:14 drk $";
#endif
#endif

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* widget creation functions */

extern Widget create_mainWindow_widget(char * name,
				       Widget parent,
				       Widget ** warr_ret);

#define WI_MAINWINDOW 0
#define WI_MENUBAR 1
#define WI_FILEMENUBUTTON 2
#define WI_FILEMENU 3
#define WI_QUIT 4
#define WI_EDITMENUBUTTON 5
#define WI_EDITMENU 6
#define WI_CUT 7
#define WI_COPY 8
#define WI_SEPEM 9
#define WI_PASTECOPY 10
#define WI_PASTEMOVE 11
#define WI_FORM 12
#define WI_OPTIONMENU 13
#define WI_SELECTIONMENU 14
#define WI_PRIMARY 15
#define WI_SECONDARY 16
#define WI_CLIPBOARD 17
#define WI_NAMED 18
#define WI_STATE 19
#define WI_SHOWPRIMARY 20
#define WI_SHOWMOTIFDEST 21
#define WI_SHOWNAMED 22
#define WI_FRAME 23
#define WI_DRAWINGAREA 24
#define WI_FRAME1 25
#define WI_WORKAREA 26
#define WI_FIELD2 27
#define WI_L2 28
#define WI_TF2 29
#define WI_FORMATOM 30
#define WI_FORMATMENU 31
#define WI_C_STRING 32
#define WI_LOCALETEXT 33
#define WI_COMPOUNDTEXT 34
#define WI_COMPOUNDSTRING 35
#define WI_DECINT 36
#define WI_HEXINT 37
#define WI_FIELD1 38
#define WI_L1 39
#define WI_TF1 40
#define WI_BUTTONS 41
#define WI_TYPEMENU 42
#define WI_TYPEPULLDOWN 43
#define WI_B_ATOM 44
#define WI_B_DRAWABLE 45
#define WI_B_WINDOW 46
#define WI_B_COLORMAP 47
#define WI_B_INTEGER 48
#define WI_B_PIXEL 49
#define WI_B_COMPOUND_TEXT 50
#define WI_B_STRING 51
#define WI_B_SPAN 52
#define WI_B_LOCALE_TEXT 53
#define WI_B__MOTIF_COMPOUND_STRING 54
#define WI_UNKNOWN_BUTTON 55
#define WI_SETBUTTON 56
#define WI_REMOVEBUTTON 57
#define WI_TARGETLIST 58
#define WI_B_LOCALE 59

#define WI_FRAMELABEL 0

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

