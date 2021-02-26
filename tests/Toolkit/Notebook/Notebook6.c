/* $XConsortium: Notebook6.c /main/5 1995/07/15 21:07:48 drk $ */
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
#include "Notebook6.h"

#define NUM_PAGES 100
#define NUM_MAJOR_TAB 20
#define NUM_MINOR_TAB 10


/* This test creates 100 page children of a Notebook widget. The page children
   are of the type specified by the user on the command line. It also creates
   20 major tabs, and 10 minor tabs */

void
main (int argc, char **argv)
{

  Widget Parent;
  Widget Notebook1;
  Widget Page[NUM_PAGES];
  Widget MajorTab[NUM_MAJOR_TAB];
  Widget MinorTab[NUM_MINOR_TAB];
  int page_no;  
  char name[16];

  int num_widgets = XtNumber (WidgetStruct);  /* Number of widgets. */
  int w;
  
  Arg args[10];
  int n,i;

  CommonTestInit(argc,argv);

  
  if (UserData == NULL)
    {
      printf ("Usage: PNotebook1 -u\nXmForm\nXmLabel\nXmLabelGadget\nXmList\nXmMainWindow\nXmMessageBox\nXmPanedWindow\nXmPushButton\nXmPushButtonGadget\nXmRowColumn\nXmScale\nXmScrollbar\nXmScrolledText\nXmSelectionBox\nXmSeparator\nXmSeparatorGadget\nXmText\nXmTextField\nXmToggleButton\nXmToggleButtonGadget\nXmScrolledWindow\n");

      exit(0);
    }

  CommonPause();

  n=0;
  Parent = XmCreateFrame (Shell1, "Parent", args,n);
  XtManageChild(Parent);


  n=0;
  Notebook1 = XmCreateNotebook (Parent, "Notebook1", args, n);
  XtManageChild (Notebook1);



  /* Apply the creation function of the widget specifed by the user. */

  w=0;
  while (strcmp (UserData, WidgetStruct[w].name) != 0 && (w < num_widgets))
    w++;

  if (w==num_widgets) 
    {
      printf ("Not a valid widget!\n");
      exit(0);
    }
  

  for (i=0; i < NUM_PAGES; i++)
    {
      sprintf (name, "Page%d", i+1);
      n=0;
      XtSetArg (args[n], XmNnotebookChildType, XmPAGE); n++;
      XtSetArg (args[n], XmNpageNumber, i+1); n++;
      Page[i] = (*WidgetStruct[w].CreateFunction)(Notebook1,name,args,n);
    }

  XtManageChildren(Page,NUM_PAGES);



  /* Create major tabs with page numbers in the following sequence: 5,10,15...
     These will be updated later to show a performance problem with changing 
     the page numbers of tabs. */

  for (i=0; i < NUM_MAJOR_TAB; i++)
    {
      sprintf (name, "MajorTab%d", i+1);
      page_no = (i+1)*5;
      n=0;
      XtSetArg (args[n], XmNpageNumber, page_no); n++;
      XtSetArg (args[n], XmNnotebookChildType, XmMAJOR_TAB); n++;
      MajorTab[i] = XmCreatePushButton(Notebook1,name,args,n);
      XtManageChild (MajorTab[i]);
    }


  
  for (i=0; i < NUM_MINOR_TAB; i++)
    {
      sprintf (name, "MinorTab%d", i+1);
      page_no = i+1;
      n=0;
      XtSetArg (args[n], XmNnotebookChildType, XmMINOR_TAB); n++;
      XtSetArg (args[n], XmNpageNumber, page_no); n++;
      MinorTab[i] = XmCreatePushButton(Notebook1,name,args,n);
      XtManageChild (MinorTab[i]);
    }



  XtRealizeWidget (Shell1);

  CommonPause();

  /* update the major tabs, so they are associated with pages in this sequence:
     10,20,30...*/

  for (i=0; i < NUM_MAJOR_TAB; i++)
    {
      page_no = (i+1)*10;
      n=0;
      XtSetArg (args[n], XmNpageNumber, page_no); n++;
      XtSetValues (MajorTab[i], args, n);
    }

  CommonPause();

  /* Update the shadow thickness. */

  for (i=0; i < NUM_MAJOR_TAB; i++)
    {
      n=0;
      XtSetArg (args[n], XmNshadowThickness, 3); n++;
      XtSetValues (MajorTab[i], args, n);
    }

  CommonPause();
  CommonPause();
  
  XtAppMainLoop(app_context);

}
  
