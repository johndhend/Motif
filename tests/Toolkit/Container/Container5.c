/* $XConsortium: Container5.c /main/5 1995/07/15 21:03:46 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */

#include <testlib.h>

#define NUM_OBJ    20
#define	NAME_LEN   20


void
main(int argc, char **argv)
{
    Widget              Container5, *IconGad;   
    int			i, num_obj;
    Cardinal		n;
    Arg			args[MAX_ARGS];
    char		test_char;
    int                 test_num;
    char		ContainerName[NAME_LEN + 1];

    ContainerName[0] = '\0';
    test_char = '\0';
    test_num = 0;

    CommonTestInit(argc, argv);

    num_obj = 10;

    if (UserData != NULL) {
	
	if (strcmp(UserData, "a") == 0) {
	    num_obj = 4;
	    test_num = 1;
	}

	if (strcmp(UserData, "b") == 0) {
	    num_obj = 5;
	    test_num = 2;
	}
	
	if (strcmp(UserData, "c") == 0) {
	    num_obj = 9;
	    test_num = 3;
	}
	
	if (strcmp(UserData, "d") == 0) {
	    num_obj = 20;
	    test_num = 4;
	}
	
	if (strcmp(UserData, "e") == 0) {
	    num_obj = 4;
	    test_num = 5;
	}
	
	test_char = *UserData;
	
	free(UserData);
	
    }
    sprintf(ContainerName, "Container5%c", test_char);

    n = 0;

    Container5 = XmCreateContainer(Shell1, ContainerName, args, n);
    XtManageChild(Container5);

    XtRealizeWidget(Shell1);

    CommonPause();

    /* Add a bunch of Icon Gadgets */

    IconGad = (Widget*) XtMalloc(NUM_OBJ*sizeof(Widget));

    for (i = 0; i < num_obj; i++) {
	char        IconName[20] ;
	XmString   icon_name;

	n = 0 ;
	sprintf(IconName, "IconGad%d", i);
	icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL); 
	XtSetArg(args[n], XmNlabelString, icon_name); n++;
	IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
        XtManageChild(IconGad[i]);
	XmStringFree(icon_name);
    }


    CommonPause();

    if (test_num == 0 || test_num == 1) {
    
	/* Set the Spatial Style to None */

	n = 0;
	XtSetArg(args[n], XmNspatialStyle, XmNONE); n++;
	XtSetValues(Container5, args, n);

	CommonPause();

	/* Unmanage all the children - Change the ResizeModel - and Remanage */

	XtUnmanageChildren(IconGad, num_obj);
    
	n = 0;
	XtSetArg(args[n], XmNspatialStyle, XmGRID); n++;
	XtSetArg(args[n], XmNspatialResizeModel, XmGROW_BALANCED); n++;
	XtSetValues(Container5, args, n);

	XtManageChildren(IconGad, num_obj);

	CommonPause();
    }

    if (test_num == 2) {
	int new_obj;

	/* Test the different ResizeModel - Start by adding children with
	   grow_balanced, then add with grow_major and then grow_minor. */

	new_obj = 4;
	for (i = num_obj; i < (num_obj+new_obj); i++) {
	    char        IconName[20] ;
	    XmString   icon_name;

	    n = 0 ;
	    sprintf(IconName, "IconGad%d", i);
	    icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL);
	    XtSetArg(args[n], XmNlabelString, icon_name); n++;
	    IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
	    XmStringFree(icon_name);
	}

	XtManageChildren(&IconGad[num_obj], new_obj);
	num_obj = num_obj + new_obj;
	
	CommonPause();

	new_obj = 5;
	n = 0;
	XtSetArg(args[n], XmNspatialResizeModel, XmGROW_MAJOR); n++;
	XtSetValues(Container5, args, n);

	for (i = num_obj; i < (num_obj+new_obj); i++) {
	    char        IconName[20] ;
	    XmString   icon_name;

	    n = 0 ;
	    sprintf(IconName, "IconGad%d", i);
	    icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL);
	    XtSetArg(args[n], XmNlabelString, icon_name); n++;
	    IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
	    XmStringFree(icon_name);
	}

	XtManageChildren(&IconGad[num_obj], new_obj);
	num_obj = num_obj + new_obj;
	
	CommonPause();

	n = 0;
	XtSetArg(args[n], XmNspatialResizeModel, XmGROW_MINOR); n++;
	XtSetValues(Container5, args, n);

	for (i = num_obj; i < (num_obj+new_obj); i++) {
	    char        IconName[20] ;
	    XmString   icon_name;

	    n = 0 ;
	    sprintf(IconName, "IconGad%d", i);
	    icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL);
	    XtSetArg(args[n], XmNlabelString, icon_name); n++;
	    IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
	    XmStringFree(icon_name);
	}

	XtManageChildren(&IconGad[num_obj], new_obj);
	num_obj = num_obj + new_obj;
	
    }

    if (test_num == 3) {
	char        IconName[20];
	XmString   icon_name;

	/* Change the spatialStyle to GRID */

	n = 0;
	XtSetArg(args[n], XmNspatialStyle, XmGRID); n++;
	XtSetValues(Container5, args, n);

	CommonPause();

	/* Test the spatialIncludeModel 
	   Add some children and check where they go */

	i = num_obj;
	n = 0 ;
	sprintf(IconName, "IconGad%d", i);
	icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL);
	XtSetArg(args[n], XmNlabelString, icon_name); n++;
	IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
	XmStringFree(icon_name);
	XtManageChild(IconGad[i]);

	CommonPause();

	/* set the spatialIncludeModel to FIRST_FIT */

	n = 0;
	XtSetArg(args[n], XmNspatialIncludeModel, XmFIRST_FIT); n++;
	XtSetValues(Container5, args, n);

	i = num_obj + 1;
	n = 0 ;
	sprintf(IconName, "IconGad%d", i);
	icon_name = XmStringGenerate(IconName, NULL, XmCHARSET_TEXT, NULL);
	XtSetArg(args[n], XmNlabelString, icon_name); n++;
	IconGad[i] = XmCreateIconGadget(Container5, IconName, args, n);
	XmStringFree(icon_name);
	XtManageChild(IconGad[i]);
	
    }

    CommonPause();

    XtAppMainLoop(app_context);

}

