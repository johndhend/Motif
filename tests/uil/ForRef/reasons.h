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
/*   $XConsortium: reasons.h /main/7 1995/07/13 20:30:25 drk $ */

/* This array contains all the available reasons for Callbacks */

static char *REASONS[50] = 
	{
		"XmCR_NONE",
		"XmCR_HELP",
		"XmCR_VALUE_CHANGED",
		"XmCR_INCREMENT",
		"XmCR_DECREMENT",
		"XmCR_PAGE_INCREMENT",
		"XmCR_PAGE_DECREMENT",
		"XmCR_TO_TOP",
		"XmCR_TO_BOTTOM",
		"XmCR_DRAG",
		"XmCR_ACTIVATE",
		"XmCR_ARM",
		"XmCR_DISARM",
		"NO_REASON",
		"NO_REASON",
		"NO_REASON",
		"XmCR_MAP",
		"XmCR_UNMAP",
		"XmCR_FOCUS",
		"XmCR_LOSING_FOCUS",
		"XmCR_MODIFYING_TEXT_VALUE",
		"XmCR_MOVING_INSERT_CURSOR",
		"XmCR_EXECUTE",
		"XmCR_SINGLE_SELECT",
		"XmCR_MULTIPLE_SELECT",
		"XmCR_EXTENDED_SELECT",
		"XmCR_BROWSE_SELECT",
		"XmCR_DEFAULT_ACTION",
		"XmCR_CLIPBOARD_DATA_REQUEST",
		"XmCR_CLIPBOARD_DATA_DELETE",
		"XmCR_CASCADING",
		"XmCR_OK",
		"XmCR_CANCEL",
		"NO_REASON",
		"XmCR_APPLY",
		"XmCR_NO_MATCH",
		"XmCR_COMMAND_ENTERED",
		"XmCR_COMMAND_CHANGED",
		"XmCR_EXPOSE",
		"XmCR_RESIZE",
		"XmCR_INPUT",
	};
