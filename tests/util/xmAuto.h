/* $XConsortium: xmAuto.h /main/4 1995/07/15 21:14:40 drk $ */
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

#define MANUAL		0
#define RECORD  	1
#define COMPARE 	2
#define IGNORE  	3
#define FULL		4
#define DUMP		5
#define TRACE		6
#define DELAY		7
#define SCRIPT  	8
#define VISUAL		9
#define INSTRUCT 	10
#define OUTPUT		11
#define COLOR		12
#define EXTRA		13
#define WRITE		14
#define READ 		15

#define MAXLINE		1024

static void CreateLayout();
static void QuitCB();
static void CreateDialogs();
static void ResetFSB();
static void AddTestCB();
static void GetTestNameCB();
static void BuildTestString();
static void SimpleCB();
static void ClearCB();
static void ClearArgs();
static void PromptCB();
static void ReadInCB();
static void WriteOutCB();
static void BrowseCB();
static void SaveToListCB();
static void ChangeFileCB();
static void ChangeFileCB();
static void FileSelectCB();

Widget Label1, List1, ScaleDelay;
Widget ToggleManual, ToggleIgnore;
Widget ToggleRecord, ToggleCompare;
Widget ToggleFull, ToggleTrace, ToggleWinDump;
Widget PromptDialog, FileSelectBox;

static char CurrentTestString[256];
static char LabelString[1024];
static char arguments[256];

static int list_pos = 0;

static Boolean manual = False;
static Boolean record = False;
static Boolean compare = True;
static Boolean ignore = False;

static Boolean full = False;
static Boolean dumps = False;
static Boolean trace = False;

static int delay = 0;
