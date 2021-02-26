/* $XConsortium: ComboBox4.c /main/5 1995/07/15 21:03:14 drk $ */
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




#define NITEMS 40
#define VITEMS 20


void  
main (int argc, char **argv)
{

    Widget             Parent;
    Widget             ComboBox;

    int                n,i;
    Arg                args[MAX_ARGS];
    XmString           TempLabelString, ItemList[NITEMS];






static char *CharItems[] = {
    "Item1",
    "btest1",
    "btest1b", 
    "btest2", 
    "btest3",
    "decor00", 
    "decor01", 
    "decor02", 
    "decor03", 
    "decor04", 
    "decor05",
    "decor06", 
    "decor07", 
    "decor08", 
    "decor09",
    "func00", 
    "func01", 
    "func02", 
    "func03", 
    "func04",
    "func05", 
    "func06", 
    "func07", 
    "func08", 
    "func09",
    "func10", 
    "func11", 
    "func12", 
    "func13", 
    "func14",
    "iplac00", 
    "iplac01", 
    "iplac02", 
    "iplac05", 
    "menu00", 
    "menu04", 
    "mtest1", 
    "parse00",
    "prop00", 
    "rstest1"
    };

    CommonTestInit(argc, argv);
    
    /* Create a ComboBox */

    if (UserData == NULL)
      {
	printf ("Usage: ComboBox4 -u <comboBoxType>\n");
	exit(0);
      }

    n=0;
    Parent = XmCreateFrame (Shell1, "Parent",args,n);
    XtManageChild (Parent);

    /* Set the comboBoxType of ComboBox based on the flag passed by the user. */

    n=0;
    if (strcmp (UserData, "COMBO_BOX") == 0)
	{
	    XtSetArg(args[n], XmNcomboBoxType, XmCOMBO_BOX); n++;
	}
    else
    if (strcmp (UserData, "DROP_DOWN_COMBO_BOX") == 0)
	{
	    XtSetArg(args[n], XmNcomboBoxType, XmDROP_DOWN_COMBO_BOX); n++;
	}

    if (strcmp (UserData, "DROP_DOWN_LIST") == 0)
	{
	    XtSetArg(args[n], XmNcomboBoxType, XmDROP_DOWN_LIST); n++;
	}

    ComboBox = XmCreateComboBox (Parent, "ComboBox", args, n);
    XtManageChild (ComboBox);

    XtRealizeWidget (Shell1);

    
 

    /* Create the list */   
    for (i=0; i<NITEMS; i++)
	{
	    TempLabelString = XmStringCreate(CharItems[i], 
				    XmSTRING_DEFAULT_CHARSET);
	    ItemList[i] = TempLabelString;

	}


    /* Set values on the List Component of the ComboBox. */
    n = 0;
    XtSetArg(args[n], XmNlistSpacing, 5);  			n++;
    XtSetArg(args[n], XmNlistMarginWidth, 2);  			n++;
    XtSetArg(args[n], XmNlistMarginHeight, 2);  		n++;
    XtSetArg(args[n], XmNitems, ItemList); 			n++;
    XtSetArg(args[n], XmNitemCount, NITEMS); 			n++;
    XtSetArg(args[n], XmNvisibleItemCount, VITEMS); 		n++;
    if (XtNameToWidget (ComboBox,"*List") != NULL)
    XtSetValues (XtNameToWidget(ComboBox,"*List"),args,n);

    CommonPause();


    n = 0;
    XtSetArg(args[n], XmNautoShowCursorPosition, True); n++;
    XtSetArg(args[n], XmNcursorPosition, 5); n++;
    XtSetArg(args[n], XmNeditMode, XmSINGLE_LINE_EDIT); n++;
    XtSetArg(args[n], XmNmarginHeight, 20); n++;
    XtSetArg(args[n], XmNmarginWidth, 20); n++;
    XtSetArg (args[n], XmNresizeWidth, True); n++;
    XtSetValues (XtNameToWidget(ComboBox,"Text"),args,n);


    CommonPause();
    
/* Add an Item */

    TempLabelString = XmStringCreate ("ExtraItem", XmSTRING_DEFAULT_CHARSET);
    XmListAddItem (XtNameToWidget(ComboBox,"*List"), TempLabelString, NITEMS+1);
    XmStringFree (TempLabelString);
 
    CommonPause();

    /* Test for XmComboBoxUpdate */

    TempLabelString = XmStringCreate ("Item1", XmSTRING_DEFAULT_CHARSET);
    XmListSelectItem (XtNameToWidget(ComboBox,"*List"), TempLabelString,False);
    XmComboBoxUpdate (ComboBox);
    XmStringFree (TempLabelString);

    

    CommonPause();
    CommonPause();

    XtAppMainLoop(app_context);
}




