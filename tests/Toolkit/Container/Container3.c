/* $XConsortium: Container3.c /main/5 1995/07/15 21:03:35 drk $ */
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

#include "collapsedState.bmp"
#include "expandedState.bmp"


#define	NAME_LEN	20
#define	NUM_OBJ		9
#define	NUM_COL		4

#define	WIDTH	1
#define	HEIGHT	2
#define	BOTH	3
#define	NEITHER	4


Widget	Container3;
Widget	IconGad1,IconGad2,IconGad3,IconGad4;
Widget	IconGad31,IconGad32,IconGad321,IconGad3211,IconGad33;

char	*ColumnHeadingText[NUM_COL] = { 
    "Icon",
    "Full Title",
    "Favorite Flavor",
    "Age"
    };

char	*FullTitleText[NUM_OBJ] = { 
    "The First Object",
    "2nd Object, but still important",
    "Show",
    "Honorable Mention",
    "Fifth of Beethoven",
    "Snowflake",
    "The Little Dwarfs",
    "100 (in Octal)",
    "Cat Lives"
    };

char	*FlavorText[NUM_OBJ] = { 
    "Chocolate",
    "Raspberry",
    "Blueberry",
    "Maple",
    "Vanilla",
    "Zucchini",
    "Licorice",
    "Potatoe",
    "Lemon"
    };

char	*AgeText[NUM_OBJ] = { 
    "42",
    "10",
    "4",
    "76",
    "2",
    "None of your business","102","23","16"
    };


XmStringTable	*EntryDetails;
XmStringTable	ColumnHeadings;


void
main(int argc, char **argv)
{
    
    XmStringTable	ColumnDetails;
    int    		i,j;
    Cardinal		n;
    Arg			args[MAX_ARGS];
    int			test_num;
    char		test_char;
    char		ContainerName[NAME_LEN + 1];
    Pixmap		CollapsedStatePixmap, ExpandedStatePixmap;
    
    ContainerName[0] = '\0';
    test_num = 0;
    test_char = '\0';
    
    CommonTestInit(argc, argv);

    if (UserData != NULL) {
	
	if (strcmp(UserData, "a") == 0) 
	    test_num = 1;
	else if (strcmp(UserData, "b") == 0) 
	    test_num = 2;
	else if (strcmp(UserData, "c") == 0) 
	    test_num = 3;
	else if (strcmp(UserData, "d") == 0) 
	    test_num = 4;
	
	test_char = *UserData;
	
	free(UserData);
	
    }
    sprintf(ContainerName, "Container3%c", test_char);
    
    CollapsedStatePixmap = XCreatePixmapFromBitmapData(display, rootWindow,
						       collapsedState_bits,
						       collapsedState_width, 
						       collapsedState_height,
						       CommonGetColor("black"),
						       CommonGetColor("white"),
						       XDefaultDepth(display, 
								     XDefaultScreen(display)));
    
    ExpandedStatePixmap = XCreatePixmapFromBitmapData(display, rootWindow,
						      expandedState_bits,
						      expandedState_width, 
						      expandedState_height,
						      CommonGetColor("white"),
						      CommonGetColor("black"),
						      XDefaultDepth(display, 
								    XDefaultScreen(display)));
    
    
    ColumnHeadings = (XmStringTable) XtMalloc(NUM_COL * sizeof(XmString));

    for (i = 0; i < NUM_COL; i++)
	 ColumnHeadings[i] = XmStringGenerate(ColumnHeadingText[i],
					      NULL,
					      XmCHARSET_TEXT,
					      NULL);

    
    n = 0;
    XtSetArg(args[n], XmNentryViewType, XmLARGE_ICON); n++;
    XtSetArg(args[n], XmNlayoutType, XmOUTLINE); n++;
    XtSetArg(args[n], XmNautomaticSelection, XmNO_AUTO_SELECT); n++;
    XtSetArg(args[n], XmNdetailColumnHeading, ColumnHeadings); n++;
    XtSetArg(args[n], XmNdetailColumnHeadingCount, NUM_COL); n++;
    XtSetArg(args[n], XmNdetailOrderCount, NUM_COL-1); n++;
    XtSetArg(args[n], XmNcollapsedStatePixmap, CollapsedStatePixmap); n++;
    XtSetArg(args[n], XmNexpandedStatePixmap, ExpandedStatePixmap); n++;
    Container3 = XmCreateContainer(Shell1, ContainerName, args, n);
    XtManageChild(Container3);
    
    EntryDetails = (XmStringTable *) XtMalloc(NUM_OBJ * sizeof(XmStringTable));
    
    for (i = 0; i < NUM_OBJ; i++) {

	ColumnDetails = (XmStringTable)XtMalloc((NUM_COL-1) * sizeof(XmString));
	ColumnDetails[0] = XmStringGenerate(FullTitleText[i],
					    NULL,
					    XmCHARSET_TEXT,
					    NULL);
	ColumnDetails[1] = XmStringGenerate(FlavorText[i],
					    NULL,
					    XmCHARSET_TEXT,
					    NULL);
	ColumnDetails[2] = XmStringGenerate(AgeText[i],
					    NULL,
					    XmCHARSET_TEXT,
					    NULL);
	EntryDetails[i] = ColumnDetails;
    }
    
    n = 0;
    XtSetArg(args[n], XmNx, 100); n++;
    XtSetArg(args[n], XmNy, 100); n++;
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNdetail, EntryDetails[0]); n++;
    IconGad1 = XmCreateIconGadget(Container3, "IconGad1", args, n);
    XtManageChild(IconGad1);
    
    n = 0;
    XtSetArg(args[n], XmNx, 200); n++;
    XtSetArg(args[n], XmNy, 200); n++;
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNdetail, EntryDetails[1]); n++;
    IconGad2 = XmCreateIconGadget(Container3, "IconGad2", args, n);
    XtManageChild(IconGad2);
    
    n = 0;
    XtSetArg(args[n], XmNx, 300); n++;
    XtSetArg(args[n], XmNy, 100); n++;
    XtSetArg(args[n], XmNentryViewType, XmLARGE_ICON); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNdetail, EntryDetails[2]); n++;
    IconGad3 = XmCreateIconGadget(Container3, "IconGad3", args, n);
    XtManageChild(IconGad3);
    
    n = 0;
    XtSetArg(args[n], XmNx, 50); n++;
    XtSetArg(args[n], XmNy, 400); n++;
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNdetail, EntryDetails[3]); n++;
    IconGad4 = XmCreateIconGadget(Container3, "IconGad4", args, n);
    XtManageChild(IconGad4);
    
    n = 0;
    XtSetArg(args[n], XmNentryParent, IconGad3); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetail, EntryDetails[4]); n++;
    IconGad31 = XmCreateIconGadget(Container3, "IconGad31", args, n);
    XtManageChild(IconGad31);
    
    n = 0;
    XtSetArg(args[n], XmNentryParent, IconGad3); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetail, EntryDetails[5]); n++;
    IconGad32 = XmCreateIconGadget(Container3, "IconGad32", args, n);
    XtManageChild(IconGad32);
    
    n = 0;
    XtSetArg(args[n], XmNentryParent, IconGad32); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNentryViewType, XmLARGE_ICON); n++;
    XtSetArg(args[n], XmNdetail, EntryDetails[6]); n++;
    IconGad321 = XmCreateIconGadget(Container3, "IconGad321", args, n);
    XtManageChild(IconGad321);
    
    n = 0;
    XtSetArg(args[n], XmNentryParent, IconGad321); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNentryViewType, XmLARGE_ICON); n++;
    XtSetArg(args[n], XmNdetail, EntryDetails[7]); n++;
    IconGad3211 = XmCreateIconGadget(Container3, "IconGad3211", args, n);
    XtManageChild(IconGad3211);
    
    n = 0;
    XtSetArg(args[n], XmNentryParent, IconGad3); n++;
    XtSetArg(args[n], XmNdetailCount, NUM_COL-1); n++; 
    XtSetArg(args[n], XmNentryViewType, XmSMALL_ICON); n++;
    XtSetArg(args[n], XmNdetail, EntryDetails[8]); n++;
    IconGad33 = XmCreateIconGadget(Container3, "IconGad33", args, n);
    XtManageChild(IconGad33);
    
    for (i = 0; i < NUM_OBJ; i++) {
	
	ColumnDetails = EntryDetails[i];
	for (j = 0; j < NUM_COL-1; j++)
	    XmStringFree(ColumnDetails[j]);
	XtFree((XtPointer)ColumnDetails);
	
    }
    XtFree((XtPointer)EntryDetails);
    
    XtRealizeWidget(Shell1);
    
    CommonPause();

    if ((test_num == 1) || (test_num == 2)) {

       CommonPause();
       CommonPause();
       CommonPause();
       CommonPause();
       CommonPause();
    
       for (i = 0; i < NUM_COL; i++)
	 XmStringFree(ColumnHeadings[i]);
       XtFree((XtPointer)ColumnHeadings);
    }

    if (test_num == 3) {

       CommonPause();
    
       for (i = 0; i < NUM_COL; i++)
	 XmStringFree(ColumnHeadings[i]);
       XtFree((XtPointer)ColumnHeadings);
    }

    
    XtAppMainLoop(app_context);
    
}



