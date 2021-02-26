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
static char rcsid[] = "$XConsortium: Navigation10.c /main/6 1995/07/13 19:40:36 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */

#include <signal.h>
#include <X11/StringDefs.h>

#include <testlib.h>

/*  Forward declarations  */

Widget Form, Form1, Form2, Form3, Form4, Form5, Form6, Form7, Form8, Form9;
Widget PushButton1, PushButton2, PushButton3;
static void RunTest();
static void CreateForm();
static void DestroyForm();
static void PushButtonCallback();
static void CreateMatrix();
extern char *optarg;
static char *color_name[] = {
  "Red",       "Green",       "Blue", 
  "Orange",    "Yellow",      "Pink",
  "Magenta",   "Brown",       "Violet",
};

enum { unmap, unmanage, destroy, nochange } remove_mode;
extern char *UserData;          /* from the TestInit routines */

/*  main  */

void main (argc, argv)
     int argc;
     char **argv;
{
  int screen;
  Arg args[25];
  int n;
  char c;

  /*  initialize toolkit  */

  CommonTestInit(argc, argv);
    
  n = 0;
  XtSetArg (args[n], XmNwidth, 1);               n++;
  XtSetArg (args[n], XmNheight, 1);              n++;
  XtSetValues(Shell1, args, n);
    

  if (UserData != NULL) {
      if (strcmp (UserData, "unmap") == 0) 
	remove_mode = unmap;
      else if (strcmp (UserData, "unmanage") == 0)
	remove_mode = unmanage;
      else if (strcmp (UserData, "nochange") == 0)
	remove_mode = nochange;
      else 
	remove_mode = destroy;
    }
  else {
    printf ("Test error: no mode specified\n", UserData);
    exit (1);
  }

  RunTest(Shell1);

  XtAppMainLoop(app_context);      
}


static void RunTest(Shell1)
Widget Shell1;
{
  Arg      args[MAX_ARGS];
  unsigned int n;
 
				/* Part 1 of Test */
    CreateForm(Shell1);
    
    /*  Create the first Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form1 = XmCreateBulletinBoard(Form, "Form1", args, n);
    
    /*  Create the second Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form1);		                n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form2 = XmCreateBulletinBoard(Form, "Form2", args, n);
    
    /*  Create the third Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form2); 	                        n++;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);               n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form3 = XmCreateBulletinBoard(Form, "Form3", args, n);
    
    /*  Create the fourth Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form1);	                        n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form4 = XmCreateBulletinBoard(Form, "Form4", args, n);
    
    /*  Create the fifth Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form4);		                n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form2);        	                n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form5 = XmCreateBulletinBoard(Form, "Form5", args, n);
    
    /*  Create the sixth Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form5); 	                        n++;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);               n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form3);    	                n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form6 = XmCreateBulletinBoard(Form, "Form6", args, n);
    
    /*  Create the seventh Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form4);    	                n++;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form7 = XmCreateBulletinBoard(Form, "Form7", args, n);
    
    /*  Create the eigth Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form7);		                n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form5);        	                n++;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form8 = XmCreateBulletinBoard(Form, "Form8", args, n);
    
    /*  Create the ninth Form.  */
    n = 0;
    XtSetArg (args[n], XmNallowOverlap, False);                         n++;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNrightWidget, Form8); 	                        n++;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);               n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET);	        n++;
    XtSetArg (args[n], XmNtopWidget, Form6);         	                n++;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	        n++;
    XtSetArg (args[n], XmNresizePolicy, XmRESIZE_GROW);                 n++;
    Form9 = XmCreateBulletinBoard(Form, "Form9", args, n);

    /* Create Form Matrices. */
    CreateMatrix(Form1, color_name[0]);
    CreateMatrix(Form2, color_name[1]);
    CreateMatrix(Form3, color_name[2]);
    CreateMatrix(Form4, color_name[3]);
    CreateMatrix(Form5, color_name[4]);
    CreateMatrix(Form6, color_name[5]);
    CreateMatrix(Form7, color_name[6]);
    CreateMatrix(Form8, color_name[7]);
    CreateMatrix(Form9, color_name[8]);

    /* Manage children. */
    XtManageChild(Form1);
    XtManageChild(Form2);
    XtManageChild(Form3);
    XtManageChild(Form4);
    XtManageChild(Form5);
    XtManageChild(Form6);
    XtManageChild(Form7);
    XtManageChild(Form8);
    XtManageChild(Form9);
    XtManageChild(Form);

    XtRealizeWidget (Shell1);

    
    CommonPause();

    DestroyForm();

}

static void CreateForm(Shell1)
Widget Shell1;
{
  unsigned int n;
  Arg args[MAX_ARGS];
  
  /*  The form creation. */
  n = 0;
  XtSetArg (args[n], XmNallowOverlap, False);                          n++;  
  Form = XmCreateForm ((Widget) Shell1, "Form", args, n);
}

static void DestroyForm()
{
  XtDestroyWidget(Form);
}

				/* Support Routines */

static void PushButtonCallback (pb, client_data, call_data)
     Widget pb;
     XtPointer client_data;
     XtPointer call_data;
{

  switch (remove_mode) {
  case unmap:
    XtSetMappedWhenManaged (pb, False);
    XtUnmapWidget(pb);
    break;
  case unmanage:
    XtUnmanageChild(pb);
    break;
  case destroy:
    XtDestroyWidget(pb);
    break;
  case nochange:
    /* do nothing */
    break;
  }

}


static void CreateMatrix(form, color)
     Widget form;
     char *color;
{
  int n, m, i;
  Arg args[MAX_ARGS];
  Widget PushButton[9];
  extern void PushButtonCallback();
  char buf[32];

 
  for (i = 0; i <= 8; i++) {

          /* Create all nine children, lined in up columns of three and
	     with Color%d,number names. Each child gets the standard
	     activate callback by default */

	  sprintf (buf, "%s%d", color, i);

	  n = 0;
	  XtSetArg (args[n], XmNbackground, CommonGetColor(color));     n++;

          if ((i%3) == 0) {   /* left column */
		XtSetArg (args[n], XmNx, 1); n++; 
          }

	  if ((i%3) == 1)  {   /* middle column */
		XtSetArg (args[n], XmNx, 75); n++;
          }
 
	  if ((i%3) == 2)   {	/* right column */
		XtSetArg (args[n], XmNx, 150); n++; 
	  }

	  /* now the y coordinates */
	  /* we won't bother to calculate the y position since the
	     heights of buttons won't vary as much as the widths
	     which have to accomodate different color-name labels.
	     These are just a "best guess" at what looks okay. */

	  if (i <= 2)	{ XtSetArg (args[n], XmNy, 1); n++; }
	  if ((i >= 3) && (i <= 5))  { XtSetArg (args[n], XmNy, 35); n++; }
	  if ((i >= 6) && (i <= 8))  { XtSetArg (args[n], XmNy, 60); n++;  }

	  PushButton[i] = XmCreatePushButton(form, buf, args, n);
       
	  XtAddCallback(PushButton[i], XmNactivateCallback, 
			PushButtonCallback, (XtPointer) NULL);
  }

  /* Manage children. */
  XtManageChildren(PushButton, 9);

}
