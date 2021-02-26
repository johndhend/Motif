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
!   $XConsortium: mesBox.msg /main/7 1995/07/13 20:48:53 drk $
!OSF/Motif: @(#)mesBox.msg	3.3  92/01/31
!******************************************************************************
 value
        message : "This is a Message Box with the \nfollowing characteristics:\n\n   - borderWidth is " &
	"4\n   - background color is forest green\n   - foreground color is white\n   - shadowThickness is 5\n" &
	"   - width and height are 400\n" &
	"   - messageAlignment is XmALIGNMENT_END\n   - okCallback is ON" &
	"\n   - helpCallback is ON\n   - cancelCallback is ON\n   - noResize is " &
	"true\n   - autoUnmanage is false\n" &
	"   - messageString is The Message Box\n\n" &
	"Automatically Created Widget Resources:\n\n" &
	"   - the OK button is unmanaged\n" &
	"   - the message label is overidden with\n" &
	"     Overrride(The MessageBox)\n" &
	"   - the symbol label's labelPixmap\n" &
	"     is the pallete icon, also has\n" &
	"     margin width and height of 75\n\n" &
	"All other resources are set by default.\n";


  value
	  wheat	 : color('wheat');
	  navy	 : color('navy');
	  black  : color('black',foreground);
	  white  : color('white',background);
	  green  : color('green',background);
	  blue   : color('blue',background);
	  yellow : color('yellow',background);
	  orange : color('orange',background);
	  violet : color('violet',background);
	  red    : color('red',background);
	
  value 
	colors_8 : color_table(black = ' ',
       			       white='x',
        		       red='r',
        		       green='g',
        		       blue='b',
        		       yellow='y',
       			       orange='o',
       			       violet='v');

   value

        palette: icon(color_table=colors_8,
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
