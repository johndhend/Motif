! 
! @OPENGROUP_COPYRIGHT@
! COPYRIGHT NOTICE
! Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
! Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
! ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
! the full copyright text.
! 
! This software is subject to an open license. It may only be
! used on, with or for operating systems which are themselves open
! source systems. You must contact The Open Group for a license
! allowing distribution and sublicensing of this software on, with,
! or for operating systems which are not Open Source programs.
! 
! See http://www.opengroup.org/openmotif/license for full
! details of the license agreement. Any use, reproduction, or
! distribution of the program constitutes recipient's acceptance of
! this agreement.
! 
! EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
! PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
! KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
! WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
! OR FITNESS FOR A PARTICULAR PURPOSE
! 
! EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
! NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
! INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
! DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
! AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
! LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
! ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
! EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
! POSSIBILITY OF SUCH DAMAGES.
! 
! 
! HISTORY
! 
!   $XConsortium: menuBar.msg /main/7 1995/07/13 20:48:19 drk $
!OSF/Motif: @(#)menuBar.msg	3.2  92/01/31
!
!  
!  	THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED
!  AND COPIED ONLY IN ACCORDANCE WITH THE TERMS OF SUCH LICENSE AND
!  WITH THE INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR
!  ANY OTHER COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE
!  AVAILABLE TO ANY OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF THE
!  SOFTWARE IS HEREBY TRANSFERRED.
!  
!  	THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT
!  NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY OPEN SOFTWARE
!  
!  
!  
!  
!  
!  
!  
!  
!  
! DEC is a registered trademark of Digital Equipment Corporation
! DIGITAL is a registered trademark of Digital Equipment Corporation
!
 value
        message : "This is a menuBar with the following\ncharacteristics:\n\n   - background is green\n" &
	"   - borderWidth is 50\n   - borderColor is mediumBlue\n" &
	"   - width is 200\n   - height is 100\n" &
	"   - shadowThickness is 5\n   - bottomshadowColor is navy\n" &
	"   - entryAlignment is\n     XmALIGNMENT_CENTER\n" &
	"   - packing is XmPACK_COLUMN\n   - marginWidth, marginHeight are 10\n" &
	"   - valueChangedcallback is ON\n     for toggleButtons\n" &
	"   - armCallback is ON for\n     pushbuttons\n" &
!	"   - background of TearOffButtons in\n" &
!	"     both Pulldowns should be wheat\n" &
	"   - tearOffModel is XmTEAR_OFF_ENABLED\n" &
	"     for both Pulldown Menus\n" &
	"   - tearOffMenuActivateCallback and\n" &
	"     tearOffMenuDeactivateCallback are\n" &
	"     ON for both Pulldown Menus\n\n" &
	"Automatically created widget resources:\n\n" &
	"   - background of PulldownMenu 1's tearOff\n" &
	"     control is wheat\n" &
	"   - background of PulldownMenu 2's tearOff\n" &
	"     control is red\n" &
	"   - tearOff control has 2 pixel shadow\n" &
	"   - tearOff control has separatorType of\n" &
	"     XmDOUBLE_DASHED_LINE\n\n" &
	"All other resources are set by default.\n";
