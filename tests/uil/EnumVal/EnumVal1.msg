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
!   $XConsortium: EnumVal1.msg /main/7 1995/07/13 20:26:43 drk $
!OSF/Motif: @(#)EnumVal1.msg	3.2  92/01/31
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
  message :
	"Enumerated Values Test 1:\n\n" &
	"The following is a Bulletin Board set up to test correct\n" &
	"usage of enumeration values. (Note: this explanation text\n" &
	"itself tests the following:\n" &
	"  - XmNeditMode = XmMULTI_LINE_EDIT\n" &
	"Bulletin Board characteristics:\n" &
	"  - XmNborderWidth = 1\n" &
	"  - XmNbackground =  sky_blue\n" &
	"  - XmNmarginWidth =  20\n" &
	"  - XmNmarginHeight =  20\n" &
	"  - XmNdefaultPosition =  false\n" &
	"  - XmNnoResize =  true\n" &
	"  - XmNResizePolicy = XmRESIZE_GROW\n" &
	"  - XmNshadowType = XmSHADOW_ETCHED_OUT\n" &
	"  - XmNshadowThickness = 10\n" &
	"ScrolledList characteristics:\n" &
	"  - XmNwidth = 200\n" &
	"  - XmNheight = 80\n" &
	"  - XmNshadowThickness = 4\n" &
	"  - XmNitems = string_table...\n" &
	"  - XmNvisibleItemCount = 7 (*)\n" &
	"  - XmNselectionPolicy = XmMULTIPLE_SELECT\n" &
	"  - XmNlistSizePolicy = XmCONSTANT\n" &
	"  - XmNscrollBarDisplayPolicy = XmAS_NEEDED\n" &
	"  - XmNscrollBarPlacement = XmTOP_LEFT\n" &
	"(*) visibleItemCount has lower priority than height";
