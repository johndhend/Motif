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
/*   $XConsortium: motifshell.h /main/5 1995/07/14 10:08:02 drk $ */

/****************************************************************************
 ****************************************************************************
 **
 **   File:     widgetView.h
 **
 **   Project:     Motif - widget examination program
 **
 **   Description: Program which shows resources of widgets
 **
 ****************************************************************************
 ****************************************************************************/

/***************************************************
*                                                  *
*  Revision history:                               *
*                                                  *
*  05/26/89      strong        Initial Version     *
*  06/01/89      strong        1.0                 *
*  06/26/89      pjlevine      complete rewrite    *
*                                                  *
****************************************************/


/*  Standard C headers  */
#include <stdio.h>
#include <sys/signal.h>

/*  X headers  */
#include <X11/IntrinsicP.h>
/*#include <X11/Shell.h>
#include <X11/AtomMgr.h>
#include <X11/Protocols.h>
*/
/*  Xm headers  */
#include <Xm/Xm.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/Command.h>
#include <Xm/CutPaste.h>
#include <Xm/DialogS.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawnB.h>
#include <Xm/FileSB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/List.h>
#include <Xm/MainW.h>
#include <Xm/MenuShell.h>
#include <Xm/MessageB.h>
#include <Xm/PanedW.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>


#define WIDTH        850
#define HEIGHT       750
#define MAX_ARGS     100
/* below are three different types of pushbuttons (and reset) */
#define ACCEL        0x01
#define DEFAULT      0x02
#define INACTIVE     0x04
#define BITSOFF      0x00

/*  Global Variables  */

Display *display;
int     screen;
Font          mfont;
XFontStruct   *mfinfo;

/* flag to select what type of pushbutton you want--
   a default one, one with an accelerator, or an inactive one */
unsigned int  bit_flag;
Widget	  Help_BB;
Widget	  dismiss;
Widget    Dialog;
Widget    Shell;
Widget    MainWindow;
Widget    MenuBar;
Widget    PullDown0;
Widget    PullDown1;
Widget    PullDown2;
Widget    PullDown3;
Widget    PullDown4;
Widget    PullDown5;
Widget    PullDown6;
Widget    PopUp;
Widget    popup_label;
Widget    MenuBtn0;
Widget    MenuBtn1;
Widget    MenuBtn2;
Widget    MenuBtn3;
Widget    MenuBtn4;
Widget    MenuBtn5;
Widget    MenuBtn6;

/* contents of menu 1 */
Widget    Label0A;
Widget    Label1A;
Widget    Label1B;
Widget    Label1C;
Widget    Label1D;
Widget    Label1E;
Widget    Label1F;
Widget    Separator1A;
Widget    RadioBox1;
Widget    RadioBtn1A;
Widget    RadioBtn1B;
Widget    Separator1B;
Widget    ToggleBtn1A;
Widget    ToggleBtn1B;

/* contents of menu 2 */
Widget    Label2A;
Widget    Label2B;
Widget    Label2C;
Widget    Label2D;
Widget    Label2E;
Widget    Label2F;
Widget    Label2G;
Widget    Label2H;

Widget    PullDown2A;
Widget    Cascade2;
Widget    Label2AA;
Widget    Label2AB;
Widget    Separator2A;
Widget    RadioBox2;
Widget    RadioBtn2A;
Widget    RadioBtn2B;
Widget    Separator2B;
Widget    ToggleBtn2A;
Widget    ToggleBtn2B;

/* contents of menu 3 */
Widget    Label3A;
Widget    Label3B;
Widget    Label3C;
Widget    Label3D;
Widget    Label3E;
Widget    Label3F;
Widget    Separator3A;
Widget    RadioBox3;
Widget    RadioBtn3A;
Widget    RadioBtn3B;
Widget    Separator3B;
Widget    ToggleBtn3A;
Widget    ToggleBtn3B;

/* contents of menu 4 */
Widget    Label4A;
Widget    Label4B;
Widget    Label4C;
Widget    Label4D;
Widget    Label4E;

/* contents of menu 5 */
Widget    Label5A;

/* contents of menu 6 */
Widget    Label6A;

/* contents of popup menu */
Widget    LabelP1;
Widget    LabelP2;
Widget    LabelP3;
Widget    LabelP4;
Widget    PullDownP;
Widget    CascadeP;
Widget    LabelP5A;
Widget    LabelP5B;

Widget    HorizScrollBar;
Widget    VertScrollBar;
Widget    WorkRegion;
Widget    TextWin;
Widget    ScrollWin;
Widget    ScrollBar;
Widget    FormWin;
Widget    LabelW;
Widget    TBoardW;
Widget    TextMenuBar;
Widget    PullDownText1;
Widget    PullDownText2;
Widget    PullDownText3;
Widget    MenuBtnText1;
Widget    MenuBtnText2;
Widget    MenuBtnText3;
Widget    HierW;
Widget    HierW2;
Widget    LabelBoardW;
Widget    SWin;
Widget    ScrollBarText;
Widget    DialogSh;
Widget    FileDialog;
Widget    FileSelection;
Widget    ScrollBarList;
Widget    ResourceList;
Widget    ResourceDialog;
Widget    WidgetDList;
Widget    WidgetDialog;
Widget    FileOK;
Widget    TextDialog;
Widget    TextShell;
Widget    FontDialog;
Widget    FontShell;
Widget    FontBulletin;
Widget    FontTestDialog;
Widget    FontTestShell;


