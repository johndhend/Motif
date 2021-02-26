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
static char rcsid[] = "$XConsortium: ResPartOffM1.c /main/6 1995/07/13 18:37:26 drk $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *  Create a foo widget in a form.  Foo uses XmResolvePartOffsets.
 */

#include <signal.h>
#include <X11/StringDefs.h>
#include <Xm/ScrollBarP.h>

#include <testlib.h>

/*  Foo class structure  */

typedef struct _FooClassPart
{
   int foo;	/*  No new fields needed  */
} FooClassPart;


/*  Full class record declaration for CheckBox class  */

typedef struct _FooClassRec
{
   CoreClassPart        core_class;
   XmPrimitiveClassPart primitive_class;
   XmScrollBarClassPart scrollbar_class;
   FooClassPart         foo_class;
} FooClassRec;

extern FooClassRec fooClassRec;


/*  The Foo resources  */

#define XmNbar		"bar"
#define XmCBar		"Bar"


/*  The Foo instance record  */

typedef struct _FooPart
{
   int bar;
} FooPart;


/*  Full instance record declaration  */

typedef struct _FooRec
{
   CorePart	   core;
   XmPrimitivePart primitive;
   XmScrollBarPart scrollBar;
   FooPart         foo;
} FooRec;


extern WidgetClass fooWidgetClass;

typedef struct _FooClassRec * FooWidgetClass;
typedef struct _FooRec      * FooWidget;



/*  Resource list for Foo  */

#define FooIndex (XmScrollBarIndex + 1)

static XmPartResource resources[] = 
{
   {
      XmNbar, XmCBar, XmRInt, sizeof (int),
      XmPartOffset(Foo, bar), XmRImmediate, (caddr_t) 0
   },
};

/*  Class functions routine definitions  */

static void    ClassInitialize();

static XmOffsetPtr offset;	/* ptr to the offset record  */

/*  The Foo class record definition  */

FooClassRec fooClassRec =
{
   {
      (WidgetClass) &xmScrollBarClassRec, /* superclass	         */
      "Foo",                            /* class_name	         */
      sizeof(FooPart),                  /* widget_size	         */
      ClassInitialize,	                /* class_initialize      */
      NULL,                             /* class_part_initialize */
      FALSE,                            /* class_inited          */
      NULL,                             /* initialize	         */
      NULL,                             /* initialize_hook       */
      XtInheritRealize,                 /* realize	         */	
      NULL,                             /* actions               */	
      0,                                /* num_actions	         */	
      (XtResource *) resources,         /* resources	         */	
      XtNumber (resources),             /* num_resources         */	
      NULLQUARK,                        /* xrm_class	         */	
      TRUE,                             /* compress_motion       */	
      TRUE,                             /* compress_exposure     */	
      TRUE,                             /* compress_enterleave   */
      FALSE,                            /* visible_interest      */	
      NULL,                             /* destroy               */	
      XtInheritResize,                  /* resize                */	
      XtInheritExpose,                  /* expose                */	
      NULL,                             /* set_values    	 */	
      NULL,                             /* set_values_hook       */
      XtInheritSetValuesAlmost,         /* set_values_almost     */
      NULL,				/* get_values_hook       */
      XtInheritAcceptFocus,             /* accept_focus	         */	
      XtVersionDontCheck,               /* version               */
      NULL,                             /* callback private      */
      XtInheritTranslations,            /* tm_table              */
      NULL,                             /* query_geometry        */
      NULL,                             /* display_accelerator   */
      NULL,                             /* extension             */
   },

   {
      XmInheritWidgetProc,		/* border_highlight   */
      XmInheritWidgetProc,		/* border_unhighlight */
      XtInheritTranslations,	        /* translations       */
      NULL,	    		     	/* arm_and_activate   */
      NULL,            			/* get resources      */
      0,                		/* num get_resources  */
      NULL,				/* extension          */
   },

   {
      NULL,				/* extension          */
   },

   {
      0,				/* extension	      */
   }
};



WidgetClass fooWidgetClass = (WidgetClass) &fooClassRec;


/************************************************************************
 *
 *  ClassInitialize
 *     Initialize the getvalue resources.
 *
 ************************************************************************/

static void ClassInitialize ()

{
   XmResolvePartOffsets (fooWidgetClass, &offset);
}


/*  Forward declarations  */

extern void FormCallback();


/*  main  */

void main (argc, argv)
int argc;
char **argv;

{
   Widget form;
   Widget scrollbar;
   Arg args[10];
   int n;



   /*  initialize toolkit  */
    CommonTestInit(argc, argv);
    

   /*  The form creation.  */

   n = 0;
   XtSetArg (args[n], XmNhorizontalSpacing, 4);		n++;
   XtSetArg (args[n], XmNverticalSpacing, 4);		n++;
   XtSetArg (args[n], XmNwidth, 50);			n++;
   XtSetArg (args[n], XmNheight, 500);			n++;
   form = XmCreateForm (Shell1, "form", args, n);
   XtManageChild (form);
   XtAddCallback (form, XmNhelpCallback, FormCallback, NULL);

   XtRealizeWidget (Shell1);

   /*  Arguments to the frame.  */

   n = 0;
   XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);		n++;
   XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
   XtSetArg (args[n], XmNwidth, 50);				n++;
   XtSetArg (args[n], XmNheight, 500);				n++;
   scrollbar = XtCreateManagedWidget("foo", fooWidgetClass, form, args, n);

   CommonPause();

   XtAppMainLoop(app_context);
}



void myQuit()
{
     printf("Begin exiting ... please standby ... \n");
     fflush(stdout);
     exit(0);
}



void FormCallback (fw, closure, call_data)
XmFormWidget fw;
caddr_t closure;
caddr_t call_data;

{
   int reason;

   XmAnyCallbackStruct * call_value = (XmAnyCallbackStruct *) call_data;

   reason = call_value -> reason;

   switch (reason)
   {
      case XmCR_HELP:
         printf ("Reason = XmCR_HELP\n");
      break;

      default:
         printf ("Hit the default, incorrect reason sent!!\n");
      break;
   }
}












