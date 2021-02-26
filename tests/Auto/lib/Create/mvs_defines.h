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
/*   $XConsortium: mvs_defines.h /main/8 1995/07/14 11:25:59 drk $ */
/***********************************************************************
  	@(#)mvs_defines.h	1.11.1.1	Date:1/22/91
  	Author: SJS
	History:
            09/14/90 Create, separate
	Calls:

	Summary:
************************************************************************/


#define  MAX_RESOURCE_NAME_LENGTH 128
#define  MAX_TEST_NAME 256

#define  MAX_STRING_LENGTH 1024
#define  MAX_STRING_VAL 64
#define  MAX_RESOURCES 150
#define  MAX_COMM_RES  40
#define  MAX_INTRES	40
#define  MAX_CALLBACKS 300
#define  MAX_CALLBACK_REF 10

#ifdef MAX_WIDGETS
#define  MAX_NUM_WIDGET_INFOS MAX_WIDGETS
#else
#define  MAX_NUM_WIDGET_INFOS 200
#endif


#define  MAXCLASS        57
#define  MAX_COLORS 256
#define  MAX_COLOR_REF 10

/* Automation Added */
/* NOTE: MAX_UNIQUE_COLORS is the maximum number of unique
 * normalized colors automation can hold per widget. 
 */

#define  MAX_UNIQUE_COLORS 10



/** Define PARAMS to handle function prototypes ****/

#ifndef PARAMS
#define PARAMS(x) x
#endif

#define VIS_error (*visErrorMsg)
#define VIS_warning (*visWarningMsg)
#define VIS_trace (*visTraceMsg)

/***** Define Max MACRO for usage within enumeration functions *****/

#define Max_n(y) \
    if (n>(y))   \
        msg_error("passed bad value '%d' to enum function when max=%d\n",n,y);\
    if (n==(-1)) return ((y)+1)

/*************************************************************************/
/*      These are Interanal resources associated with each Widget Class  */
/* Internal resources are used when describing widget behavior.          */
/*************************************************************************/

#define XvNaddMode		"addMode"
#define XvNbuttonPressRegion	"buttonPressRegion"
#define XvNwidgetArmed		"widgetArmed"
#define XvNchildList		"childList"
#define XvNcurrIndex		"currIndex"
#define XvNcurrWidget		"currWidget"
#define XvNfocusRegion		"focusRegion"
#define XvNmenuLevel		"menuLevel"
#define XvNpendDelete		"pendDelete"
#define XvNpositionChanged	"positionChanged"
#define XvNprimaryGained	"primaryGained"
#define XvNselectionStarted	"selectionStarted"
#define XvNtoggleInRowColSelected	"toggleInRowColSelected"
#define XvNtotalChild		"totalChild"
#define XvN2ndSelectionStarted	"2ndSelectionStarted"
#define XvNwhichToggle		"whichToggle"

/* Defines for cascade related behaviors in menus */
#define DRAG_MODE               0
#define KEY_MODE                1
#define PTR_ACTIVATE_MODE       2
#define KEY_ACTIVATE_MODE       3
#define MAX_MODE                4

/* Failure return from mvsGetResourceNum() function */
#define NON_EXISTENT   (-1)


/* Defines used to determine what parts of validation to run */

#define CREATE_SECT     (1<<1)
#define SET_SECT        (1<<2)
#define BEHAVIOR_SECT   (1<<3)

/************ Level of message detail *****************/    

#define FAILURE   (1<<1)
#define ERROR     (1<<2)
#define WARNING   (1<<3)
#define INFO      (1<<4)
#define TRACE     (1<<5)

