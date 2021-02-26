/* $XConsortium: ComboBox5.c /main/4 1996/05/08 23:33:22 drk $ */
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

#include <testlib.h>

#define PROBE()	do { \
		    (void)printf( "%s{%d}\n", __FILE__, __LINE__ ); } \
		while (0)


#define NUM_COMBO_BOX_TYPES 3

#define NUM_STRINGS 5
static char *list_strings[NUM_STRINGS] =
	{ "0123456789012345678901234567890123456789",
          "ABCDEFGHIABCDEFGHIABCDEFGHIABCDEFGHIABCDEFGHI",
          "abcdefghiabcdefghiabcdefghiabcdefghiabcdefghi",
          "shortstring",
          "SayHello" };

Widget Manager;
Widget ComboBox;                /* This is the ComboBox under test. */
Widget TextField;

  /*
   *  Get the default value of the XmNcolumns resource from the TextField.
   */
  void
PrintNumColumns( void )
{
  Arg   args[10];
  int   n;
  short num_columns;

  n = 0;
  XtSetArg( args[n], XmNcolumns, &num_columns ); n++;
  XtGetValues( TextField, args, n );
  (void)printf("XmNcolumns = %d\n", (int)num_columns );
  return;
}

  int
main (int argc, char **argv)
{
  Arg 		args[10];
  int 		n,i, instance;
  XmString      list_item[NUM_STRINGS];
  unsigned char combo_box_type;
  char		buffer[25];

  CommonTestInit (argc, argv);

  (void)printf( "Begin Test\n" );

  if (UserData == NULL)
  {
    (void)printf ("Usage: ComboBox5 -u <comboBoxType>\n");
    exit(0);
  }

 /*
  *  Determine which type of ComboBox is being created.
  */
  if ( strcmp( UserData, "COMBO_BOX" ) == 0 ) 
  {
    instance = 1;
    combo_box_type = XmCOMBO_BOX;
  }
  else if ( strcmp( UserData, "DROP_DOWN_COMBO_BOX" ) == 0 ) 
  {
    instance = 2;
    combo_box_type = XmDROP_DOWN_COMBO_BOX;
  }
  else if ( strcmp( UserData, "DROP_DOWN_LIST" ) == 0 ) 
  {
    instance = 3;
    combo_box_type = XmDROP_DOWN_LIST;
  }
  else {
    (void)printf( "Incorrect ComboBox Type %s\n", UserData );
    exit(0);
  }


  /* Create the parent. */
  n=0;
  Manager = XmCreateForm( Shell1, "Shell1", args, n );
  XtManageChild (Manager);

  /* Create a list item for the ComboBox List child */
  for ( n=0; n<NUM_STRINGS; n++ )
    list_item[n] = XmStringCreateLtoR( list_strings[n], XmFONTLIST_DEFAULT_TAG);

  /*
   *  Create a ComboBox of the requested comboBoxType.
   */
  (void)sprintf( buffer, "ComboBox%d", instance );
  (void)printf( "Creating %s of type %s\n", buffer, UserData );

  n = 0;
  XtSetArg( args[n], XmNtopAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNcomboBoxType, combo_box_type ); n++;
  XtSetArg( args[n], XmNitems, &list_item ); n++;
  XtSetArg( args[n], XmNitemCount, 3 ); n++;
  XtSetArg( args[n], XmNvisibleItemCount, (NUM_STRINGS-1) ); n++;
  ComboBox = XmCreateComboBox( Manager, buffer, args, n );
  XtManageChild( ComboBox );

  for ( n=0; n<NUM_STRINGS; n++ )
      XmStringFree( list_item[n] );

  XtRealizeWidget( Shell1 );

  /*
   *  Retrieve the XmTextField child widget from the ComboBox
   */
  TextField = XtNameToWidget( ComboBox, "*Text" );

#if defined(DEFECT)
  /* The following code should be equivalent to the XtNameToWidget code,
   * but it causes a NULL widget pointer to be returned.
   */
  n = 0;
  XtSetArg( args[n], XmNtextField, &TextField ); n++;
  XtGetValues( ComboBox, args, n );
#endif /* defined(DEFECT) */


  (void)printf( "CommonPause 1\n" );
  PrintNumColumns();
  CommonPause();

  (void)printf( "CommonPause 2\n" );
  n = 0;
  XtSetArg( args[n], XmNcolumns, 10 ); n++;
  XtSetValues( TextField, args, n );
  PrintNumColumns();
  CommonPause();

  (void)printf( "CommonPause 3\n" );
  n = 0;
  XtSetArg( args[n], XmNcolumns, 30 ); n++;
  XtSetValues( TextField, args, n );
  PrintNumColumns();
  CommonPause();

  XtAppMainLoop( app_context );

  XtDestroyWidget( ComboBox );
  XtDestroyWidget( Manager );

  (void)printf( "End Test\n" );

  return 0;
} 
