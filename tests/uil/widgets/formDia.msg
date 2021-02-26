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
!   $XConsortium: formDia.msg /main/7 1995/07/13 20:45:20 drk $
!OSF/Motif: @(#)formDia.msg	3.2  92/01/31
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
        message : "This is a FormDialog with the following\ncharcteristics:\n\n" &
"   - width is 250\n   - height is 250\n   - background is b" &
"lue\n   - dialogTitle is The Form Dialog\n" &
"   - The form has six PushButtons.\n   - Callbacks are ON for all.\n" &
"   - PushButton1 is attached to form on\n     the BOTTOM, LEFT, and RIGHT.\n" &
"   - PushButton2 is attached to form on\n     the RIGHT and LEFT, and attached\n     to PB1 on the bottom.\n" &
"     rightOffset and leftOffset is 100\n" &
"   - PushButton3 is attached to form on\n     the RIGHT, attached to PB2 on the\n     BOTTOM, attached to PB5 on the TOP.\n" &
"   - PushButton4 is attached to form on\n     the LEFT, attached to PB2 on the\n     BOTTOM, attached to PB5 on the TOP.\n" &
"   - PushButton5 is attached to form on\n     the RIGHT and LEFT, and attached to\n     PB6 on the TOP.\n" &
"     rightOffset and leftOffset is 100\n" &
"   - PushButton6 is attached to form on\n     the TOP, RIGHT, and LEFT.\n" &
	"\n\nAll other resources are set by default.\n";
