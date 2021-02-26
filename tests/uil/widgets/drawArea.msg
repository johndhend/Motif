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
!   $XConsortium: drawArea.msg /main/7 1995/07/13 20:44:25 drk $
!OSF/Motif: @(#)drawArea.msg	3.2  92/01/31
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
        message : "This is a Drawing Area widget with the\nfollowing characteristics:\n\n   - width is" &
	" 95\n   - height is 95\n   - backgroundPixmap is of a\n     painter's palette\n" &
	"   - exposeCallback is ON\n   - inputCallback is ON\n" &
	"   - marginWidth is 20\n   - mar" &
	"ginHeight is 20\n\nAll other resources are set be default.\n";

value black  : color('black',foreground);
value white  : color('white',background);
value green  : color('green',background);
value blue   : color('blue',background);
value yellow : color('yellow',background);
value orange : color('orange',background);
value violet : color('violet',background);
value red    : color('red',background);

value mre_colors : color_table(black = ' ',
	white='x',
	red='r',
	green='g',
	blue='b',
	yellow='y',
	orange='o',
	violet='v');

value

        palette: icon(color_table=mre_colors,
'                                ',
'                                ',
'           xxxxxxxxxx           ',
'         xx          xx         ',
'       xx              x        ',
'      x     rrrr        x       ',
'    xx      rrr        x        ',
'   x   b    r       xxx         ',
'   x  bbb         xx            ',
'  x   bbb        xx             ',
' x     b         x              ',
' x           xxx  x     xxxxxx  ',
'x  ggg      x   x  xxxxx      x ',
'x  gggg    x    x              x',
'x   g      x    x              x',
'x          xx  x       oooo    x',
'x           xxx        ooo     x',
'x  yyyy                 o      x',
'x  yyy                         x',
'x   y                          x',
' x                 xxxx       x ',
' x     ooo          xx        x ',
'  x    ooo    v      xx      x  ',
'   x         vvv            x   ',
'    x        vvv           x    ',
'     x       v            x     ',
'      x                  x      ',
'       xx              xx       ',
'         xx          xx         ',
'           xxxxxxxxxx           ',
'                                ',
'                                ');
