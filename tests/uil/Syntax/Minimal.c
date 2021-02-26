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
static char rcsid[] = "$XConsortium: Minimal.c /main/7 1995/07/13 20:40:19 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
#include <stdio.h>


#include <Mrm/MrmAppl.h>                   /* Motif Toolkit */
#include <Xm/Label.h>
#include <Xm/LabelP.h>
#include <Xm/BulletinB.h>
#include <Xm/BulletinBP.h>
#include <Xm/PushB.h>
#include <Xm/PushBP.h>

static MrmHierarchy	s_MrmHierarchy;		/* MRM database hierarch id */
static char		*vec[]={"Minimal.uid"};
						/* MRM database file list   */
static MrmCode		class ;

static void helloworld_button_activate();

static MrmCount		regnum = 1 ;
static MrmRegisterArg	regvec[] = {
	{"helloworld_button_activate",(caddr_t)helloworld_button_activate}
	};

/*
 *  Main program
 */
int main(argc, argv)
int argc;
char **argv;
{
     /*
     *  Declare the variables to contain the two widget ids
     */
    Widget toplevel, hellominimalmain;
    Arg arglist[1] ;

    /*
     *  Initialize the MRM. We only register the required classes.
     */

    MrmRegisterClass
	(0, NULL, "XmCreateBulletinBoard", XmCreateBulletinBoard,
	 (WidgetClass) &xmBulletinBoardClassRec);
    MrmRegisterClass
	(0, NULL, "XmCreatePushButton", XmCreatePushButton,
	 (WidgetClass) &xmPushButtonClassRec);
    MrmRegisterClass
	(0, NULL, "XmCreateLabel", XmCreateLabel,
	 (WidgetClass) &xmLabelClassRec);


    /*
     *  Initialize the toolkit.  This call returns the id of the "toplevel"
     *  widget.  The applications "main" widget must be the only child
     *  of this widget.
     */

    toplevel = XtInitialize(
	"Minimal Files",		/* application name */
	"helloworldclass",              /* application class */
	NULL, 0,                        /* options */
	&argc, argv);                   /* command line parameters */

    XtSetArg (arglist[0], XtNallowShellResize, TRUE) ;
    XtSetValues (toplevel, arglist, 1) ;

    /*
     *  Define the Mrm.hierarchy (only 1 file)
     */

    if (MrmOpenHierarchy (1,			    /* number of files	    */
			vec, 			    /* files     	    */
			NULL,			    /* os_ext_list (null)   */
			&s_MrmHierarchy)	    /* ptr to returned id   */
			!= MrmSUCCESS) {
	printf ("can't open hierarchy\n");
     }

    /*
     * 	Register our callback routines so that the resource manager can 
     * 	resolve them at widget-creation time.
     */

    if (MrmRegisterNames (regvec, regnum)
			!= MrmSUCCESS)
			    printf("can't register names\n");

    /*
     *  Call MRM to fetch and create the pushbutton and its container
     */

    if (MrmFetchWidget (s_MrmHierarchy,
			"hellominimal_main",
			toplevel,
			&hellominimalmain,
			&class)
			!= MrmSUCCESS)
			    printf("can't fetch interface\n");

    /*
     *  Make the toplevel widget "manage" the main window (or whatever the
     *  the uil defines as the topmost widget).  This will
     *  cause it to be "realized" when the toplevel widget is "realized"
     */

    XtManageChild(hellominimalmain);
    
    /*
     *  Realize the toplevel widget.  This will cause the entire "managed"
     *  widget hierarchy to be displayed
     */

    XtRealizeWidget(toplevel);

    /*
     *  Loop and process events
     */

    XtMainLoop();

    /* UNREACHABLE */
    return (0);
}

static void helloworld_button_activate( widget, tag, callback_data )
	Widget	widget;
	char    *tag;
	XmAnyCallbackStruct *callback_data;
{
    Arg arglist[2];

    static int call_count = 0;

    printf("In hello_world_button_activate\n");

    call_count += 1 ;
    switch ( call_count )
        {
        case 1:
            XtSetArg( arglist[0], XmNlabelString,
                XmStringLtoRCreate("Goodbye\nMinimal!",""));
            XtSetValues( widget, arglist, 1 );
            break ;
        case 2:
            exit(1);
            break ;
        }
}
