/* $XConsortium: PNotebook1.c /main/5 1995/07/15 21:01:57 drk $ */
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

#include <stdio.h>
#include <sys/time.h>

#include <testlib.h>
#include "PNotebook1.h"

#define NUM_PAGES 500
#define NUM_MAJOR_TAB 50
#define NUM_MINOR_TAB 20

static void     PrintLapseTime();

struct timeval	flip_fwd_time[2];
struct timeval	flip_bwd_time[2];
struct timeval	tab_to_page_time[2];

Boolean	expect_new_page = False;

static void PrintLapseTime(first,second)
struct timeval *first, *second;
{
     struct timeval lapsed;

     if (first->tv_usec > second->tv_usec) {
        second->tv_usec += 1000000;
        second->tv_sec--;
     }

     lapsed.tv_usec = second->tv_usec - first->tv_usec;
     lapsed.tv_sec = second->tv_sec - first->tv_sec;

     printf("lapsed time = %d.%06d sec\n\n",
            lapsed.tv_sec, lapsed.tv_usec%1000000);
     fflush(stdout);

}

void Quit(Widget w, XtPointer client_data, XtPointer call_data)
{
	printf("Time elapsed to scroll forward through all pages:\n");
	PrintLapseTime(&flip_fwd_time[0],&flip_fwd_time[1]);
	printf("Time elapsed to scroll back through all pages:\n");
	PrintLapseTime(&flip_bwd_time[0],&flip_bwd_time[1]);
	printf("Time elapsed to tab to a page:\n");
	PrintLapseTime(&tab_to_page_time[0],&tab_to_page_time[1]);

	printf("Begin exiting ... please standby ... \n");
	exit(0);
}

void TimeToPageCB(Widget w, XtPointer client_data, XtPointer call_data)
{
        struct  timezone        tz;

	gettimeofday(&tab_to_page_time[0],&tz);
	expect_new_page = True;
}

void PageChangedCB(Widget w, XtPointer client_data, XtPointer call_data)
{
        struct  timezone        tz;
	XmNotebookCallbackStruct *cb = (XmNotebookCallbackStruct *)call_data;

	if ((cb->reason == XmCR_MAJOR_TAB) && expect_new_page)
	  {
	  gettimeofday(&tab_to_page_time[1],&tz);
	  expect_new_page = False;
	  }
	if (cb->reason == XmCR_PAGE_SCROLLER_INCREMENT)
	  {
	  if (flip_fwd_time[0].tv_sec == 0)
		{
		gettimeofday(&flip_fwd_time[0],&tz);
		return;
		}
	  if ((cb->page_number == NUM_PAGES)
	     && (flip_fwd_time[1].tv_sec == 0))
		{
		gettimeofday(&flip_fwd_time[1],&tz);
		return;
		}
	  return;
	  }
	if (cb->reason == XmCR_PAGE_SCROLLER_DECREMENT)
          {     
          if (flip_bwd_time[0].tv_sec == 0)
                {
                gettimeofday(&flip_bwd_time[0],&tz);
                return;
                }
          if ((cb->page_number == 1)
             && (flip_bwd_time[1].tv_sec == 0))
                {       
                gettimeofday(&flip_bwd_time[1],&tz);
                return;
                }
          return;
          }
}

/* This test creates 500 page children of a Notebook widget. The page children
   are of the type specified by the user on the command line. It also creates
   10 major tabs, and 20 minor tabs */

void
main (int argc, char **argv)
{

  Widget Parent;
  Widget Notebook1;
  Widget Page[NUM_PAGES];
  Widget MajorTab[NUM_MAJOR_TAB];
  Widget MinorTab[NUM_MINOR_TAB];
  Widget PageScroller;
  int page_no;  
  char name[16];

  int num_widgets = XtNumber (WidgetStruct);  /* Number of widgets. */
  int w;
  
  Arg args[10];
  int n,i;

  CommonTestInit(argc,argv);

  


  n=0;
  Parent = XmCreateFrame (Shell1, "Parent", args,n);
  XtManageChild(Parent);


  n=0;
  Notebook1 = XmCreateNotebook (Parent, "Notebook1", args, n);
  XtManageChild (Notebook1);

  if (UserData == NULL)
      {
	  for (i=0; i < NUM_PAGES; i++)
	      {
		  sprintf (name, "Page%d", i+1);
		  n=0;
		  XtSetArg (args[n], XmNnotebookChildType, XmPAGE); n++;
		  XtSetArg (args[n], XmNpageNumber, i+1); n++;
		  Page[i] = XmCreateFrame (Notebook1, name, args, n);
	      }

	
      }

  else
      {
        w=0;
	while (strcmp (UserData, WidgetStruct[w].name) != 0 && 
	       (w < num_widgets))
	    w++;

	if (w == num_widgets) 
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
		Page[i] = (*WidgetStruct[w].CreateFunction)
		    (Notebook1,name,args,n);
	    }
    }
  XtManageChildren(Page,NUM_PAGES);




  /* Create major tabs with page numbers in the following sequence: 10,20,30...
     These will be updated later to show a performance problem with changing 
     the page numbers of tabs. */

  for (i=0; i < NUM_MAJOR_TAB; i++)
    {
      if (i == 0)
	sprintf (name, "Press to Quit");
      else if (i == 1)
	sprintf (name, "Press to Time");
      else
	sprintf (name, "MajorTab%d", i+1);
      page_no = (i+1)*10;
      n=0;
      XtSetArg (args[n], XmNpageNumber, page_no); n++;
      XtSetArg (args[n], XmNnotebookChildType, XmMAJOR_TAB); n++;
      MajorTab[i] = XmCreatePushButton(Notebook1,name,args,n);
      XtManageChild (MajorTab[i]);
      if (i == 0)
	XtAddCallback(MajorTab[i],XmNactivateCallback,Quit,NULL);
      else if (i == 1)
	XtAddCallback(MajorTab[i],XmNarmCallback,TimeToPageCB,NULL);
    }

  for (i=0; i < NUM_MINOR_TAB; i++)
    {
      sprintf (name, "MinorTab%d", i+1);
      page_no = (i+1)*5;
      n=0;
      XtSetArg (args[n], XmNnotebookChildType, XmMINOR_TAB); n++;
      XtSetArg (args[n], XmNpageNumber, page_no); n++;
      MinorTab[i] = XmCreatePushButton(Notebook1,name,args,n);
      XtManageChild (MinorTab[i]);
    }



  XtRealizeWidget (Shell1);

  flip_fwd_time[0].tv_sec = 0;
  flip_fwd_time[1].tv_sec = 0;
  flip_bwd_time[0].tv_sec = 0;
  flip_bwd_time[1].tv_sec = 0;
  XtAddCallback(Notebook1,XmNpageChangedCallback,PageChangedCB,NULL);

  CommonPause();

  /* update the major tabs, so they are associated with pages in this sequence:
     20,40,60...*/

  for (i=0; i < NUM_MAJOR_TAB; i++)
    {
      page_no = (i+1)*20;
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
  




