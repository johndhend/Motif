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
/*   $TOG: CallUil.h /main/5 1999/11/23 16:51:12 jff $ */
#include <stdio.h>
#include <signal.h>
#include <Mrm/MrmAppl.h>    
#include <Xm/Xm.h>
#include <uil/UilDef.h>

#define MAX_FILES       10
#define MAX_INFO        32000
#define MAX_CALLBACK    32
#define MAX_LEN         255

/* routines called from Uil file via callbacks */

static void exit_test();
static void Change_Font();
static void Change_Position();
static void Place_Hunt();
static void Hunt_String();
static void Place_FsBox();
static void Get_File();
static void Continue();
void dummy_handler();

/* internally called routines */

static void FlushEvents();
static void Pause();
static void Get_Text();
static char * cs_to_rs();
static void Create_Uid_File();

/* Callback routines for Callable UIL */

Uil_status_type 	MessageCB();
Uil_status_type		StatusCB();

char value_string[MAX_INFO];

char mess_string[MAX_INFO] = "This Test will test the Callable UIL compiler.\nIt will compile three UIL files:\n\n   1) The first will have an error (missing ; on end module)\n   2) The second will have a warning (fontList not supported)\n \
  3) The third will compile correctly\n\nThe following options will be set when calling the Callable Uil compiler:\n\n   1) Listing files will be created\n   2) UID file will be created\n   3) error and warning messages will be reported\n   4) machine code will be produced in listing file\n   5) status_update_delay is set at 300\n   6) Three include directories will be searched\n\nWhen xlist.uil file has sucessfully compiled, It will be used\nin a list utility created in UIL\n\nContinue for UIL compilation error test\n";

static MrmHierarchy	s_MrmHierarchy;
static char		*vec[MAX_FILES];   	
static char		rootname_err[MAX_LEN] = "xlistError";
static char		rootname_warn[MAX_LEN] = "xlistWarn";
static char		rootname_corr[MAX_LEN] = "xlist";
static char 		uid_file[MAX_LEN];

Widget toplevel = NULL;                    
Widget  widgetmain = NULL;
int cur_pos = 0;
Boolean wait;
