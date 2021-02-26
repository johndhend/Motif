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
/*   $XConsortium: testlib.h /main/11 1995/07/14 12:00:02 drk $ */


/*  Standard C headers  */

#include <stdio.h>
#include <ctype.h>
#include <sys/signal.h>

/*  Xt headers  */

#include <X11/Intrinsic.h>
#include <X11/Shell.h>

/*  Xm headers  */

#include <Xm/Xm.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>
#include <Xm/AtomMgr.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/ComboBox.h>
#include <Xm/Command.h>
#include <Xm/Container.h>
#include <Xm/CutPaste.h>
#include <Xm/DialogS.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawnB.h>
#include <Xm/FileSB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/IconG.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/List.h>
#include <Xm/MainW.h>
#include <Xm/MenuShell.h>
#include <Xm/MessageB.h>
#include <Xm/MwmUtil.h>
#include <Xm/Notebook.h>
#include <Xm/PanedW.h>
#include <Xm/Protocols.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Scale.h>
#include <Xm/Screen.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/SpinB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

/* definitions used in all test modules */

#define MAX_ARGS  	100
#define MAX_FILE        256
#define MAX_FONT_LEN    64

/*  Global Variables  */

extern XtAppContext  	app_context;
extern Display  	*display;
extern Window	  	rootWindow;
extern Screen		* screen;
extern Widget   	Shell1;
extern Widget		InstructionBox;

/* Private Functions */


extern void		CommonUsage(char *test_name);
extern void		CommonGenericCB(Widget w, XtPointer client_data,
			        	XtPointer call_data);
extern void		CommonGetOptions(int *argc, char **argv);
extern void		CommonPause();
extern void		CommonTestInit(int argc, char **argv);
extern void		CommonTestI18NInit(int argc, char **argv, 
					   XtLanguageProc proc, 
					   XtPointer client_data);
extern void 		CommonDumpHierarchy(Widget w, FILE *file);
extern char		*CommonCsToRs(XmString cs);
extern Pixel		CommonGetColor(char *colorstr);
extern XmFontList	CommonGetFontList(char *fontstr);
extern void             CommonExtraResources(Arg args[], Cardinal n);

/* stubs for when NOT linking with malloc library */

extern void             MallocInit(); 
extern void             MallocExit();


/* global variables - command line options */

extern FILE 		*output_file;
extern Boolean 		instructions;
extern char		*UserData;
extern char		*TestName;
extern char             *instruct_file_name;
extern char             *instruct_file_name_orig;
extern int		pause_len;
extern char		test_font[MAX_FONT_LEN];
extern char		default_font[MAX_FONT_LEN];
