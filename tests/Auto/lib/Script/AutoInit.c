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
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: AutoInit.c /main/10 1995/07/14 11:27:45 drk $"
#endif
#endif
#include <mvslib.h>
#include <testlib.h>
#include "AutoToken.h"
#include "Automation.h"

#define	MULTI_CLICK_INTERVAL	750

void 			InitTestAutomation();
AutoCommandStructPtr    AutoCommandRoot;


void
InitTestAutomation(
        int argc,
        char **argv )
{

    /* Get proper testName for creation of recorded data files */

    strcpy(mvsTestName,argv[0]);

    /* Determine if you are recording screens or playing them back */

    if (AutoRecord)
    	mvsSetVisualMode(VISUAL_MODE_GENERATE_PIXMAPS);
    else if (AutoManual)
    	mvsSetVisualMode(VISUAL_MODE_INTERACTIVE_COMPARE);
    else if (AutoNoCheck)
	mvsSetVisualMode(VISUAL_MODE_DONT_CHECK);
    else
	mvsSetVisualMode(VISUAL_MODE_BATCH_COMPARE);

    /* Clear the color Cache */

    visClearColorCache();

    /* Set Focus Mode for Input Synthesis */

    xisSetFocusMode(KEYBOARD_FOCUS_NATURAL);

    /* Set MultiClick Interval Time */

    xisSetMultiClickTime(MULTI_CLICK_INTERVAL);

    /* Do not do Grabs/UnGrabs on Button Preses/Releases */

    xisPointerGrabMode = POINTER_GRAB_NATURAL;

    /* Setup the Root node of the Comand Structures */

    AutoCommandRoot = (AutoCommandStructPtr) 
				malloc(sizeof(AutoCommandStruct));
    
    AutoCommandRoot->CommandName = -1;
    AutoCommandRoot->Mask[0] = 0;
    AutoCommandRoot->NumMask = 0;
    AutoCommandRoot->ButtonNumber = 0;
    AutoCommandRoot->Key = 0;
    AutoCommandRoot->KeyOrButtonCount = 0;
    AutoCommandRoot->WidgetName = NULL;
    AutoCommandRoot->WidgetComponent = -1;
    AutoCommandRoot->SystemCommand = NULL;
    AutoCommandRoot->XCoord = 0;
    AutoCommandRoot->YCoord = 0;
    AutoCommandRoot->Location = -1;
    AutoCommandRoot->Gravity = 0;

    AutoCommandRoot->next = NULL;

}
