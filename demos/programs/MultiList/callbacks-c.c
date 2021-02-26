
#include <localdef.h>

/*
 * Generated by the ICS builderXcessory (BX).
 *
 *
 * Builder Xcessory 3.0A.
 *
 */
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/MessageB.h>
#include <Xm/ToggleB.h>
#include <Xm/Text.h>
#include <Xm/MultiList.h>
#include "extlist.h"
#include <stdio.h>
#include <stdlib.h>

extern PlayerData players[];
extern Pixmap porsche_pix;
extern Pixmap stopsign_pix; 
extern Pixmap crab_pix;
extern Pixmap clown_pix;
static int  NothingSort(short , XmMultiListRowInfo *, XmMultiListRowInfo *);
static int  ExtListAlphaSort(short , XmMultiListRowInfo *, XmMultiListRowInfo *);
static int  ExtListIntSort(short , XmMultiListRowInfo *, XmMultiListRowInfo *);
static int  ExtListDoubleSort(short , XmMultiListRowInfo *, XmMultiListRowInfo *);


/**************************************************************
 *		CALLBACKS
 **************************************************************/
/* ARGSUSED */
Widget 
CreateExtListCB( Widget parent )
{
	XmString tcs;
	Widget retWid;
    Arg args[MAX_ARGS];
    Cardinal argcnt;
    XmMultiListRowInfo *row_info;
    int i, j;
    XmString *col_title_str;
    static String col_titles[] = {
	"At Bat",
	"Name",
	"AVG",
	"AB",
	"R",
	"H",
	"HR",
	"RBI",
	NULL,
    };
    XmMultiListSortFunction **sort_funcs = (XmMultiListSortFunction **) 
                 XtMalloc(sizeof(XmMultiListSortFunction *) * NUM_COLUMNS);


    /*
     * Create the Xm18RowInfo "rows"
     *
     * Create PLAYER_LIMIT Xm18RowInfo structs
     * Initially however, there are no rows
     */

    row_info = (XmMultiListRowInfo *) XtMalloc(sizeof(XmMultiListRowInfo) * LINEUP_LIMIT);

    /*
     * Each Xm18RowInfo contains an array of strings, which represent 
     * the column data.
     *
     * In this example, the following columns are:
     * 0 - Name
     * 1 - "AVG"
     * 2 - "AB"
     * 3 - "R"
     * 4 - "H"
     * 5 - "HR"
     * 6 - "RBI"
     */
    for (i = 0; i < LINEUP_LIMIT; i++) {
	row_info[i].values = (XmString *) 
	    XtMalloc(NUM_COLUMNS * sizeof(XmString));
	for (j = 0; j < NUM_COLUMNS; j++)
	    row_info[i].values[j] = NULL;
    }

    /* Column titles must also be XmStrings */
    col_title_str = (XmString *)XtMalloc( NUM_COLUMNS*sizeof(XmString));

    for (j = 0; j < NUM_COLUMNS; j++) {
      col_title_str[j] = XmStringCreateSimple(col_titles[j]);
      switch (j){
      case 0:
	sort_funcs[j] = (XmMultiListSortFunction *)NothingSort;
	break;
      case 1:
	sort_funcs[j] = (XmMultiListSortFunction *)ExtListAlphaSort;
	break;
      case 2:
      sort_funcs[j] = (XmMultiListSortFunction *)ExtListDoubleSort;
	break;
      default : sort_funcs[j] = (XmMultiListSortFunction *)ExtListIntSort;
      }
    }
    /* These arguments set up the list with no elements. The 
     *  row info will be added each time AddPlayer is done. Look
     *  at that code to see how the row information is initialized
     */  

    argcnt = 0;
    XtSetArg(args[argcnt], XmNfirstColumnPixmaps, True); argcnt++;
    XtSetArg(args[argcnt], XmNentryData, row_info); argcnt++;
    XtSetArg(args[argcnt], XmNnumRows, 0); argcnt++;
    XtSetArg(args[argcnt], XmNnumColumns, NUM_COLUMNS); argcnt++;
    XtSetArg(args[argcnt], XmNcolumnTitles, col_title_str); argcnt++;
    XtSetArg(args[argcnt], XmNtitle, tcs=XmStringCreateSimple("Lineup")); argcnt++;
    XtSetArg(args[argcnt], XmNsortFunctions, sort_funcs);        argcnt++;
    XtSetArg(args[argcnt], XmNselectionPolicy, XmSINGLE_SELECT);   argcnt++;
    XtSetArg(args[argcnt], XmNshowSash, False);   argcnt++;
	retWid = XtCreateManagedWidget("multiListWidget", 
				  xmMultiListWidgetClass, 
				  parent, args, argcnt);    

      XmStringFree(tcs);
    for (j = 0; j < NUM_COLUMNS; j++) 
      XmStringFree(col_title_str[j]);
    XtFree((char*)col_title_str);

    return( retWid);
    
}


/* ARGSUSED */
void
RemCB(Widget w, XtPointer client, XtPointer call )
{
    Arg args[5];
    Cardinal argcnt;
    DemoInfo demo_info = (DemoInfo)client;
    XmMultiListRowInfo *items = NULL, *new_items = NULL;
    short items_count = 0, new_items_count = 0;
    int i, j, k;
    
    argcnt = 0;
    XtSetArg(args[argcnt], XmNentryData, &items); argcnt++;
    XtSetArg(args[argcnt], XmNnumRows, &items_count); argcnt++;
    XtGetValues(demo_info->extlist, args, argcnt);

	{
	XmString tcs = XmStringCreateSimple("No Selected Player");
        XtVaSetValues( demo_info->rem_pb, XmNlabelString,tcs, NULL);
	XmStringFree(tcs);
	}

    if (items_count == 0)
	return;
    
    /* Count how many were NOT selected */
    for (i = 0; i < items_count; i++)
	if (!items[i].selected)
	    new_items_count++;

    /* Allocate this amount of memory */
    new_items = (XmMultiListRowInfo *) XtMalloc(sizeof(XmMultiListRowInfo) * LINEUP_LIMIT);

    for (i = 0; i < LINEUP_LIMIT; i++) {
	new_items[i].values = (XmString *) 
	    XtMalloc(NUM_COLUMNS * sizeof(XmString));
	for (j = 0; j < NUM_COLUMNS; j++)
	    new_items[i].values[j] = NULL;
    }

    for (i = 0, j = 0; i < items_count; i++) {
	if (!items[i].selected) {

	    new_items[j].pixmap = items[i].pixmap;

	    new_items[j].selected = False;

	    new_items[j].data = items[i].data;

	    for (k = 0; k < NUM_COLUMNS; k++)
		new_items[j].values[k] = items[i].values[k];
	    j++;
	}
    }

    argcnt = 0;
    XtSetArg(args[argcnt], XmNentryData, new_items); argcnt++;
    XtSetArg(args[argcnt], XmNnumRows, new_items_count); argcnt++;
    XtSetValues(demo_info->extlist, args, argcnt);

    for (i = 0; i < items_count; i++) {
	XtFree((XtPointer) items[i].values);
    }
    XtFree((XtPointer) items);
}

/* ARGSUSED */
void
ToggleFindArea(Widget w, XtPointer client, XtPointer call )
{
  DemoInfo demo_info = (DemoInfo)client;
  Arg args[5];
  Cardinal argcnt = 0;
  Boolean is_set;

  XtSetArg( args[0], XmNset, &is_set );
  XtGetValues( w, args, 1 );

  XtSetArg( args[0], XmNshowFind, is_set );
  XtSetValues( demo_info->extlist, args, 1 );

}


/* ARGSUSED */
void
FirstRowCol(Widget w, XtPointer client, XtPointer call )
{
  DemoInfo demo_info = (DemoInfo)client;
  Arg args[5];
  Cardinal argcnt = 0;

  XtSetArg(args[argcnt], XmNfirstRow, 2); argcnt++;
  XtSetArg(args[argcnt], XmNfirstColumn, 1); argcnt++;
  XtSetValues( demo_info->extlist, args, argcnt );
}


/* ARGSUSED */
void
UnselCB(Widget w, XtPointer client, XtPointer call )
{
  DemoInfo demo_info = (DemoInfo)client;
 
  XmMultiListUnselectAllItems( demo_info->extlist );
  
}

/* ARGSUSED */
void
QuitCB(w, client, call)
Widget w;
XtPointer client;
XtPointer call;
{
    exit(0);
}

/* ARGSUSED */
void
UpdateRemLabelStr(Widget w,XtPointer client, XtPointer call )
{
  DemoInfo demo_info = (DemoInfo)client;
  Arg args[5];
  Cardinal argcnt;
  XmMultiListRowInfo *row_info = (XmMultiListRowInfo *)call;
    
  if (row_info && row_info->values)
  {
      XtSetArg( args[0],  XmNlabelString, row_info->values[1] );
      XtSetValues( demo_info->rem_pb, args, 1 );
  }
	else
	{
	XmString tcs = XmStringCreateSimple("No Selected Player");
        XtVaSetValues( demo_info->rem_pb, XmNlabelString,tcs, NULL);
	XmStringFree(tcs);
	}
}



/* ARGSUSED */
void
ChoosePlayerCB(Widget w,XtPointer client, XtPointer call )
{
    DemoInfo demo_info = (DemoInfo)client;
    Arg args[5];
    Cardinal argcnt;
    XmMultiListRowInfo *row_info;
    short num_rows;
    int i=0, playernum;
    char buf[BUFSIZ];
    Boolean found=False;
    
    while ((i < NUM_PLAYERS) && (!found)){
      if (w == demo_info->player[i]) found = True;
      else i++;
    }
    playernum = i;


    argcnt = 0;
    XtSetArg(args[argcnt], XmNentryData, &row_info); argcnt++;
    XtSetArg(args[argcnt], XmNnumRows, &num_rows); argcnt++;
    XtGetValues(demo_info->extlist, args, argcnt);
    
    if (num_rows == LINEUP_LIMIT) {
	XmString xmstring;
	static Widget info = NULL;
	
	if (info == NULL) {
	    Arg args[5];
	    Cardinal argcnt;
	    Widget temp;

	    xmstring = 
		XmStringCreateSimple("Cannot have more than nine players.");
	    
	    argcnt = 0;
	    XtSetArg(args[argcnt], XmNtitle, "Error"); argcnt++;
	    XtSetArg(args[argcnt], XmNmessageString, xmstring); argcnt++;
	    info = XmCreateErrorDialog(w, "error", args, argcnt);
	    
	    temp = XmMessageBoxGetChild(info, XmDIALOG_CANCEL_BUTTON);
	    XtUnmanageChild(temp);
	    temp = XmMessageBoxGetChild(info, XmDIALOG_HELP_BUTTON);
	    XtUnmanageChild(temp);
	    XmStringFree(xmstring);
	}
	XtManageChild(info);
	return;
    }
    
    for (i = 0; i < num_rows; i++) {
	XmString xmstring;
	static Widget info = NULL;

	if ((int) row_info[i].data == playernum) {
	    
	    if (info == NULL) {
		Arg args[5];
		Cardinal argcnt;
		Widget temp;
		
		argcnt = 0;
		XtSetArg(args[argcnt], XmNtitle, "Error"); argcnt++;
		info = XmCreateErrorDialog(w, "error", args, argcnt);
		
		temp = XmMessageBoxGetChild(info, XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild(temp);
		temp = XmMessageBoxGetChild(info, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild(temp);
	    }

	    sprintf(buf, "%s already in line up.", players[playernum].name);
	    xmstring = XmStringCreateSimple(buf);

	    argcnt = 0;
	    XtSetArg(args[argcnt], XmNmessageString, xmstring); argcnt++;
	    XtSetValues(info, args, argcnt);
	
	    XtManageChild(info);
	    XmStringFree(xmstring);
	    return;
	}
    }

    row_info[num_rows].data = (XtPointer) playernum;

    switch (players[playernum].picture) {
    case PPORSCHE:
      row_info[num_rows].pixmap = porsche_pix;
      break;
    case PCRAB:
    row_info[num_rows].pixmap = crab_pix;
      break;
    case PCLOWN:
    row_info[num_rows].pixmap = clown_pix;
      break;
    case PSTOP:
    row_info[num_rows].pixmap = stopsign_pix;
      break;
    }

    row_info[num_rows].selected = False;

    row_info[num_rows].values[1] = 
      XmStringCreateSimple(players[playernum].name);


    XtFree((XtPointer) row_info[num_rows].values[2]);
    sprintf(buf, ".%d", players[playernum].average);
    row_info[num_rows].values[2] = XmStringCreateSimple(buf);

    XtFree((XtPointer) row_info[num_rows].values[3]);
    sprintf(buf, "%d", players[playernum].at_bats);
    row_info[num_rows].values[3] = XmStringCreateSimple(buf);

    XtFree((XtPointer) row_info[num_rows].values[4]);
    sprintf(buf, "%d", players[playernum].runs);
    row_info[num_rows].values[4] = XmStringCreateSimple(buf);
    
    XtFree((XtPointer) row_info[num_rows].values[5]);
    sprintf(buf, "%d", players[playernum].hits);
    row_info[num_rows].values[5] = XmStringCreateSimple(buf);

    XtFree((XtPointer) row_info[num_rows].values[6]);    
    sprintf(buf, "%d", players[playernum].home_runs);
    row_info[num_rows].values[6] = XmStringCreateSimple(buf);

    XtFree((XtPointer) row_info[num_rows].values[7]);    
    sprintf(buf, "%d", players[playernum].rbi);
    row_info[num_rows].values[7] = XmStringCreateSimple(buf);

    num_rows++; 

    argcnt = 0;
    XtSetArg(args[argcnt], XmNentryData, row_info); argcnt++;
    XtSetArg(args[argcnt], XmNnumColumns, NUM_COLUMNS); argcnt++;
    XtSetArg(args[argcnt], XmNnumRows, num_rows); argcnt++;
    XtSetValues(demo_info->extlist, args, argcnt);
}

/* ARGSUSED */
void
CreateLabel(w, client, call)
Widget w;
XtPointer client;
XtPointer call;
{
    Arg args[5];
    Cardinal argcnt;
    XmString xmstring;

    xmstring = XmStringCreateLtoR(
"This is a demo of the Open Motif Internationalized Extended List widget.\n\
\n\
The Internationalized Extended List provides multi-column list \n\
capabilities, which are not available in Motif. It uses XmStrings \n\
exclusively, and is able to display color pixmaps in the leftmost \n\
column. Search capability is built into the widget and is accessed \n\
through the Find Area below the list.\n\
\n\
Selections may be done in single select mode or extended select mode.\n\
There are convenience routines for selecting and unselecting rows \n\
programmatically as well. To see some of the features of this widget, \n\
add some data to the list, by selecting one of the players from the \n\
Add Player option menu.\n\
\n\
The Extended List can sort rows based on the currently selected column \n\
using sort routines provided by the developer. Select different\n\
column titles to see what order that sort routine produces. \n\
\n\
Search the list by typing a string into the text field next \n\
to the Find button. Then select the Find button or hit \n\
the Enter key to initiate the search. If the string is found, the \n\
row that contains it will be made viewable and selected. If not \n\
found,the Extended list will issue a beep.\n\
\n\
The Find area may be unmanaged by setting the \"showFind\" resource \n\
to False.See how the widget looks without the Find area taking up space.\n\
\n\
There is a convenience routine for unselecting rows programmatically \n\
Select the Unselect Current pushbutton to see it work.\n\
\n\
To see how the firstRow and firstCol resources work, select the \n\
Row 2, Col 1 button. The extended list will make that the upper left \n\
row and column. Remember, the list cannot be scrolled past its end.  \n\
Therefore, if making a particular row and col the upper leftmost would \n\
cause the list to scroll past its boundaries, it will scroll to the \n\
end ",
				  XmSTRING_DEFAULT_CHARSET);

    argcnt = 0;
    XtSetArg(args[argcnt], XmNalignment, XmALIGNMENT_BEGINNING); argcnt++;
    XtSetArg(args[argcnt], XmNlabelString, xmstring); argcnt++;
    XtSetValues(w, args, argcnt);
    XmStringFree(xmstring);
}




/************************************************************
 *
 *  Sort routines.
 *
 ************************************************************/
static int 
NothingSort( short column, XmMultiListRowInfo *row1, XmMultiListRowInfo *row2 )
{
  return(0);
}


static String
StringFromXmString(XmString xms)
{
    String str;
	if (XmStringGetLtoR(xms,XmFONTLIST_DEFAULT_TAG, &str))
		return str;
	else return NULL;
}


/*      Function Name: ExtListAlphaSort
 *      Description:   A sorting employee to sort things is alphabetic order.
 *          This function only compares the first segment in the XmStrings.
 *          If multi-segment XmStrings were expected, you could loop thru
 *             both strings, extracting all segments and then do the compare
 *      Arguments:     column - column to sort on.
 *                     row1, row2 - two rows to check.
 *      Returns:       -1, 0, or 1 depending upon whether 1 is less than,
 *                                 equal to, or greater than 2.
 */
static int
ExtListAlphaSort( short column, XmMultiListRowInfo *row1, XmMultiListRowInfo *row2 )
{
  String str1 = StringFromXmString(row1->values[column]);
  String str2 = StringFromXmString(row2->values[column]);

  int ret_val;
	
  if (str1 == NULL)
    ret_val = -1; /* str1 is empty. it must be less than str2 */
  else if (str2 == NULL)
    ret_val = 1; /* str2 is empty. str1 must be greater */
  else
    ret_val = strcmp(str1, str2);
  
  /* clean up */
  if (str1 != NULL) XtFree((XtPointer) str1);
  if (str2 != NULL) XtFree((XtPointer) str2);
  
  return (ret_val);
}

/*      Function Name: ExtListIntSort
 *      Description:   A sorting function to sort things in numerical order.
 *      Arguments:     column - column to sort on.
 *                     row1, row2 - two rows to check.
 *      Returns:       -1, 0, or 1 depending upon whether 1 is less than,
 *                                 equal to, or greater than 2.
 */
static int
ExtListIntSort( short column,  XmMultiListRowInfo *row1, XmMultiListRowInfo *row2 )
{
  String str1 = StringFromXmString(row1->values[column]);
  String str2 = StringFromXmString(row2->values[column]);
  int ret_val;
  
  if (str1 == NULL)
    ret_val = -1; /* str1 is empty. it must be less than str2 */
  else if (str2 == NULL)
    ret_val = 1; /* str2 is empty. str1 must be greater */
  else
    {
      int i1, i2;
      
      i1 = atoi(str1);
      i2 = atoi(str2);
      
      if (i1 == i2)
	ret_val = 0;
      else if (i1 < i2)
	ret_val = -1;
      else
	ret_val = 1;
    };
  
  /* clean up */
  if (str1 != NULL) XtFree((XtPointer) str1);
  if (str2 != NULL) XtFree((XtPointer) str2);
  
  return(ret_val);
}

/*      Function Name: ExtListIntSort
 *      Description:   A sorting function to sort things in numerical order.
 *      Arguments:     column - column to sort on.
 *                     row1, row2 - two rows to check.
 *      Returns:       -1, 0, or 1 depending upon whether 1 is less than,
 *                                 equal to, or greater than 2.
 */
static int
ExtListDoubleSort( short column, XmMultiListRowInfo *row1, XmMultiListRowInfo *row2 )
{
  String str1 = StringFromXmString(row1->values[column]);
  String str2 = StringFromXmString(row2->values[column]);
  int ret_val;
  
  if (str1 == NULL)
    ret_val = -1; /* str1 is empty. it must be less than str2 */
  else if (str2 == NULL)
    ret_val = 1; /* str2 is empty. str1 must be greater */
  else
    {
      float i1, i2;
      
      sscanf( str1, "%f", (float *)&i1 );
      sscanf( str2, "%f", (float *)&i2 );
      
      if (i1 == i2)
	ret_val = 0;
      else if (i1 < i2)
	ret_val = -1;
      else
	ret_val = 1;
    };
  
  /* clean up */
  if (str1 != NULL) XtFree((XtPointer) str1);
  if (str2 != NULL) XtFree((XtPointer) str2);
  
  return(ret_val);
}