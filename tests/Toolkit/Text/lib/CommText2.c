/* $XConsortium: CommText2.c /main/5 1995/07/15 21:11:03 drk $ */
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

Arg args[MAX_ARGS];
int n;

static char starting_string[] = "Text provides a single and multiline text editor for customizing both user and programmatic interfaces.\n\nText provides separate callback lists to verify the movement of the insert cursor, modification of the text, and changes in input focus.";


int main_text2 (argc, argv)
     int argc;
     char **argv;
{
   Widget         Text1;
   XmString       tcs;
   XtTranslations new_table;
   static char new_translations[] =
	"Ctrl<Key>g:               beep() \n\
	 Ctrl<Key>i:               insert-string(newstring) \n\
	 Ctrl<Key>bracketright:    forward-paragraph() \n\
	 Ctrl<Key>bracketleft:     backward-paragraph() \n\
	 Meta<Key>d:               scroll-one-line-down() \n\
	 Meta<Key>u:               scroll-one-line-up() \n\
	 Ctrl<Key>f:               next-page() \n\
	 Ctrl<Key>b:               previous-page() \n\
	 Ctrl<Key>u:         	   unkill() \n\
	 <Key>BackSpace:	   kill-previous-character() \n\
	 Ctrl<Key>s:		   kill-selection() \n\
	 Ctrl<Key>k:	   	   kill-next-word() \n\
	 Meta<Key>k:	   	   kill-previous-word() \n\
	 Ctrl<Key>r:   	   	   delete-previous-word() \n\
	 Meta<Key>r:	           delete-next-word() \n\
	 Ctrl<Key>c:		   cut-primary()";

/* cut-primary() added for Pir 4244 */

   /*  initialize toolkit  */
   CommonTestInit(argc, argv);
    
   /* Begin Test for Pir2718 */

   n = 0;
   XtSetArg(args[n], XmNdefaultFontList, CommonGetFontList("variable"));  n++;

   /* End Test for Pir2718 */

   XtSetArg(args[n], XmNwidth, 390); n++;
   XtSetArg(args[n], XmNheight, 115); n++;
   XtSetValues(Shell1, args, n);
   
   new_table = XtParseTranslationTable (new_translations);

   n = 0;
   XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
   XtSetArg(args[n], XmNwordWrap, True); n++;
   XtSetArg(args[n], XmNresizeWidth, False);  n++;
   XtSetArg(args[n], XmNresizeHeight, False);  n++;
   XtSetArg(args[n], XmNcolumns, 40);  n++;
   XtSetArg(args[n], XmNcursorPosition, 35);  n++;
   XtSetArg(args[n], XmNrows, 3);  n++;
   XtSetArg(args[n], XmNvalue, starting_string);  n++;
   Text1 = XmCreateText(Shell1, "Text1", args, n);
   XtManageChild(Text1);

   XtOverrideTranslations(Text1, new_table);
   XtRealizeWidget(Shell1);

   CommonPause ();              /* try translations */

#ifdef	PIR_CLOSED
   /* test case for PIR 3520 */
   CommonPause ();
   /* end of test case for PIR 3520 */
#endif	/* PIR_CLOSED */

   CommonPause ();              /* test for 8029 */

   CommonPause ();              /* exit */

   XtAppMainLoop(app_context);
}
