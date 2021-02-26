/* $XConsortium: Scrollbar12.c /main/5 1995/07/15 21:09:25 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
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

#include <testlib.h>

#define SCROLLBAR_WIDTH  50
#define CLIENT_WIDTH     SCROLLBAR_WIDTH * 8
#define CLIENT_HEIGHT    CLIENT_WIDTH
#define SEPARATOR_WIDTH  5
#define MARGINS          20

void main ( int argc, char **argv )
{
  register int n;
  Arg      args[MAX_ARGS];
  Widget   BulletinBoard1, Scrollbar1, Separator1, Separator2;
  Position sb_xcoord, sb_ycoord;

  CommonTestInit(argc, argv);

  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  BulletinBoard1 = XmCreateBulletinBoard(Shell1, "BulletinBoard1", args, n);
  XtManageChild(BulletinBoard1);

 /*
  *  XmNsnapBackMultiple is the default.
  *  Scrollbar should continue sliding regardless of where on the screen
  *  the pointer is being moved.
  */
  sb_xcoord = 3.5 * SCROLLBAR_WIDTH;
  sb_ycoord = 0;

  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord ); n++;
  XtSetArg(args[n], XmNy,  sb_ycoord );  n++;
  XtSetArg(args[n], XmNwidth,  SCROLLBAR_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT - 2 * MARGINS);  n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
  Scrollbar1 = XmCreateScrollBar(BulletinBoard1, "Scrollbar1", args, n);
  XtManageChild(Scrollbar1);

  XtRealizeWidget( Shell1 );

  CommonPause();

 /*
  *  XmNsnapBackMultiple = 0.
  *  Scrollbar slider should "snap back" as soon as pointer moves
  *  outside the bounds of the scrollbar.
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple, 0);  n++;
  XtSetValues( Scrollbar1, args, n );

  CommonPause();

 /*
  *  XmNsnapBackMultiple = 1.
  *  Scrollbar slider should "snap back" as soon as pointer moves
  *  beyond the distance of one SCROLLBAR_WIDTH from the scrollbar boundary.
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple, 1 );  n++;
  XtSetValues( Scrollbar1, args, n );

 /*
  *  Place vertical separators at a distance of one SCROLLBAR_WIDTH
  *  from the bounds of the Scrollbar.
  */
  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord - SCROLLBAR_WIDTH ); n++;
  XtSetArg(args[n], XmNy,  0 );  n++;
  XtSetArg(args[n], XmNwidth, SEPARATOR_WIDTH );  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT - 2 * MARGINS );  n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
  XtSetArg(args[n], XmNseparatorType, XmSHADOW_ETCHED_OUT);  n++;
  Separator1 = XmCreateSeparator( BulletinBoard1, "Separator1", args, n ); 
  XtManageChild( Separator1 );
  
  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord + 2 * SCROLLBAR_WIDTH ); n++;
  XtSetArg(args[n], XmNy,  0 );  n++;
  XtSetArg(args[n], XmNwidth, SEPARATOR_WIDTH );  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT - 2 * MARGINS );  n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);  n++;
  XtSetArg(args[n], XmNseparatorType, XmSHADOW_ETCHED_OUT);  n++;
  Separator2 = XmCreateSeparator( BulletinBoard1, "Separator2", args, n ); 
  XtManageChild( Separator2 );

 /*
  *  Reset the dimensions of the bulletin board widget.
  */
  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  XtSetValues( BulletinBoard1, args, n );
  
  CommonPause();

 /*
  *  XmNsnapBackMultiple =  2.
  *  Scrollbar slider should "snap back" as soon as pointer moves
  *  beyond the distance of 2 x SCROLLBAR_WIDTH from the scrollbar boundary.
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple, 2 );  n++;
  XtSetValues( Scrollbar1, args, n );


 /*
  *  Update the position of the separators to reflect the new
  *  "snap back" boundary.
  */
  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord - 2 * SCROLLBAR_WIDTH );  n++;
  XtSetValues( Separator1, args, n );
  
  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord + 3 * SCROLLBAR_WIDTH );  n++;
  XtSetValues( Separator2, args, n );

 /*
  *  Reset the dimensions of the bulletin board widget.
  */
  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  XtSetValues( BulletinBoard1, args, n );

  CommonPause();

 /*
  *  Change the orientation of the scrollbar to be horizontal.
  *  Place the scrollbar in the horizontal center of its parent.
  *  Set XmNsnapBackMultiple to 1000.
  */
  sb_xcoord = 0;
  sb_ycoord = 3.5 * SCROLLBAR_WIDTH;

  n = 0;
  XtSetArg(args[n], XmNx,  sb_xcoord);  n++;
  XtSetArg(args[n], XmNy,  sb_ycoord);  n++;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH - 2 * MARGINS);  n++;
  XtSetArg(args[n], XmNheight, SCROLLBAR_WIDTH);  n++;
  XtSetArg(args[n], XmNorientation,  XmHORIZONTAL);  n++;
  XtSetArg(args[n], XmNsnapBackMultiple,  1000);  n++;
  XtSetValues( Scrollbar1, args, n );

 /*
  *  Unmanage the separators.
  */ 
  XtUnmanageChild( Separator1 );
  XtUnmanageChild( Separator2 );

 /*
  *  Reset the dimensions of the bulletin board widget.
  */
  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  XtSetValues( BulletinBoard1, args, n );

  CommonPause();

 /*
  *  XmNsnapBackMultiple = 0 
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple,  0);  n++;
  XtSetValues( Scrollbar1, args, n );
  
  CommonPause();

 /*
  *  XmNsnapBackMultiple = 1 
  *  Place separators above and below the scrollbar at the distance
  *  of one scrollbar width.
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple,  1);  n++;
  XtSetValues( Scrollbar1, args, n );
  
  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord );  n++;
  XtSetArg(args[n], XmNy, sb_ycoord - SCROLLBAR_WIDTH );  n++;
  XtSetArg(args[n], XmNwidth, CLIENT_WIDTH - 2 * MARGINS );  n++;
  XtSetArg(args[n], XmNheight, SEPARATOR_WIDTH );  n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL );  n++;
  XtSetValues( Separator1, args, n );
  XtManageChild( Separator1 );

  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord );  n++;
  XtSetArg(args[n], XmNy, sb_ycoord +  2 * SCROLLBAR_WIDTH );  n++;
  XtSetArg(args[n], XmNwidth, CLIENT_WIDTH - 2 * MARGINS );  n++;
  XtSetArg(args[n], XmNheight, SEPARATOR_WIDTH );  n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL );  n++;
  XtSetValues( Separator2, args, n );
  XtManageChild( Separator2 );

 /*
  *  Reset the dimensions of the bulletin board widget.
  */
  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  XtSetValues( BulletinBoard1, args, n );

  CommonPause();

 /*
  *  XmNsnapBackMultiple = 2
  *  Place separators above and below the scrollbar at the distance
  *  of one scrollbar width.
  */
  n = 0;
  XtSetArg(args[n], XmNsnapBackMultiple,  2);  n++;
  XtSetValues( Scrollbar1, args, n );

  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord );  n++;
  XtSetArg(args[n], XmNy, sb_ycoord - 2 * SCROLLBAR_WIDTH );  n++;
  XtSetValues( Separator1, args, n );

  n = 0;
  XtSetArg(args[n], XmNx, sb_xcoord );  n++;
  XtSetArg(args[n], XmNy, sb_ycoord + 3 * SCROLLBAR_WIDTH );  n++;
  XtSetValues( Separator2, args, n );

 /*
  *  Reset the dimensions of the bulletin board widget.
  */
  n = 0;
  XtSetArg(args[n], XmNwidth,  CLIENT_WIDTH);  n++;
  XtSetArg(args[n], XmNheight, CLIENT_HEIGHT);  n++;
  XtSetValues( BulletinBoard1, args, n );

  CommonPause();
  CommonPause();

  XtAppMainLoop( app_context );
}
