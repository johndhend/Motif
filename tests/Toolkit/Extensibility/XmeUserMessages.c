/* $XConsortium: XmeUserMessages.c /main/4 1995/07/15 21:05:31 drk $ */
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


#ifdef REV_INFO
#ifndef lint
static char rcsid[] = ""
#endif
#endif

#include <testlib.h>
#include <Xm/XmosP.h>
#include <Xm/XmP.h>

Widget Btn1;

void  main (argc, argv)
int argc;
char **argv;
{
  Boolean            trace = False, test_passed;
  register int       n;
  Arg                args[MAX_ARGS];
  String             dirname;

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg(args[n], XmNwidth,  200);  n++;
  XtSetArg(args[n], XmNheight, 200);  n++;
  XtSetValues(Shell1, args, n);

  XtRealizeWidget(Shell1);

  /* The following test checks XmeGetHomeDirName by printing the
     returned value and manually checking it at runtime */
  dirname = XmeGetHomeDirName();
  printf("home directory name: %s\n",dirname);
  CommonPause();

  /* The following test checks XmeWarning by printing a warning 
     message and verifying it at runtime */
  n = 0;
  Btn1 = XmCreateArrowButton(Shell1,"button1", args, n);
  XmeWarning(Btn1,"Sample message text.");
  CommonPause();

  /* The following tests check the results of XmeNamesAreEqual */
  printf("Begin testing XmeNamesAreEqual\n");
  test_passed = True;
  /* test if Xm prefix is ignored */
  if (!XmeNamesAreEqual("Xm1000TH_INCHES","1000th_inches")) {
    printf("ERROR - comparing \"Xm1000TH_INCHES\" and \"1000th_inches\"\n");
    test_passed = False;
  }
  /* test if case is ignored */
  if (!XmeNamesAreEqual("MixedCase","mixedcase")) {
    printf("ERROR - comparing \"MixedCase\" and \"mixedcase\"\n");
    test_passed = False;
  }
  /* test if uppercase fails for test_str */
  if (XmeNamesAreEqual("Capitalized","Capitalized")) {
    printf("ERROR - comparing \"Capitalized\" and \"Capitalized\"\n");
    test_passed = False;
  }
  if (test_passed)
    printf("\tAll tests passed\n");
  CommonPause();

  CommonPause();	/* quit */
  XtAppMainLoop(app_context);
  XtDestroyWidget(Btn1);
}
