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
!   $XConsortium: radioBox.msg /main/8 1995/07/13 20:51:31 drk $
!OSF/Motif: @(#)radioBox.msg	3.2  92/01/31
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
        message : "This is a radioBox with the following\ncharacteristics:\n\n" &
"   - The radioBox has five children,\n     4 toggleButtonGadgets and 1 ToggleButton\n   - ValueChangedCallbacks are ON\n" &
"     for all toggleButtons\n   - height and width are 200\n   - borderWidth is 4\n   - background is cadetblue\n" &
"   - marginHeight, marginWidth are 10\n   - numColumns are 2\n   - packing is XmPACK_COLUMN\n" &
"   - spacing is 10\n   - entryAlignment is\n     XmALIGNMENT_CENTER\n   - entryCallback is ON\n\n" &
"   NOTE: The Toggle buttons valueChanged\n   callbacks will not come out. They\n   are vectored to entryCallback.\n\n" &
"All other resources are set by default.\n";
