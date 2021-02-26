/* $TOG: DNDClientData.c /main/6 1997/11/20 12:42:05 csn $ */
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
#include <Xm/DragDrop.h>
#include "../Toolkit/bitmaps/gnu.bmp"


#define NUM_DROPSITES 5


/*
 * Local functions
 */


static void
HandleDrop (Widget, XtPointer, XtPointer);

static void
DropTransfer (Widget w, XtPointer closure, Atom *seltype, Atom *type, XtPointer value, unsigned long *length, int format);

/*
 * These are the drop sites being  tested
 */

Widget DropSite[5];

Atom COMPOUND_TEXT;

/*
 * Client data structure
 */

typedef struct {  int id;
		  XtPointer data;
	       } ClientData, *ClientDataPointer;


/*
 * dropSiteData related variables
 */

Pixmap MyPixmap;
XmString MyCompString;
char *MyChar;
int MyInt;
Pixel MyPixel;
ClientData TestData1, TestData2, TestData3, TestData4, TestData5, *cdata;



Widget RowCol1;
Widget FormD1, PushB1;

Widget xmDisplay;
Atom importList[1];



void
main (int argc, char **argv)
{
  	

  Arg args[10];
  	int i,n;

	CommonTestInit (argc, argv);

	n=0;
	FormD1 = XmCreateFormDialog (Shell1, "FormD1", args, n);
	XtManageChild (FormD1);

	n=0;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	PushB1 = XmCreatePushButton (FormD1, "Drag Source", args, n);
	XtManageChild (PushB1);


	
		
	n=0;
	XtSetArg (args[n], XmNpacking, XmPACK_COLUMN); n++;
	XtSetArg (args[n], XmNnumColumns, 1); n++;
	RowCol1 = XmCreateRowColumn (Shell1, "Row", args, n);
	XtManageChild (RowCol1);


	n=0;
	DropSite[0] = XmCreateToggleButton(RowCol1, "ToggleBtn1", args, n);
	XtManageChild (DropSite[0]);

	n=0;
	DropSite[1] = XmCreateLabel(RowCol1, "Label1", args, n);
	XtManageChild (DropSite[1]);

	n=0;
	DropSite[2] = XmCreateList(RowCol1, "List1", args, n);
	XtManageChild (DropSite[2]);

	n=0;
	XtSetArg (args[n], XmNshowValue, True); n++;
	XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
	DropSite[3] = XmCreateScale(RowCol1, "Scale1", args, n);
	XtManageChild (DropSite[3]);

	n=0;
	DropSite[4] = XmCreatePushButton(RowCol1, "PushBtn1", args, n);
	XtManageChild (DropSite[4]);

   
	
	/*
	 * Create the drop site
	 */

	COMPOUND_TEXT = XmInternAtom (display, "COMPOUND_TEXT",
				      False);
        importList[0] = COMPOUND_TEXT;
	
        /*
         * Create dropsites
         */

	for (i=0; i < NUM_DROPSITES; i++)
	  {
	    n=0;
	    XtSetArg (args[n], XmNimportTargets, importList); n++;
	    XtSetArg (args[n], XmNnumImportTargets,1); n++;
	    XtSetArg (args[n], XmNdropProc, HandleDrop); n++;
	    XtSetArg (args[n], XmNdropSiteOperations, XmDROP_COPY); n++;
	    XmDropSiteRegister (DropSite[i], args, n);
	    
	  }


   	/*
    	 * Initialize client data structure
    	 */
	
	/*
	 * First
	 */

	MyPixel = CommonGetColor ("Red");
	TestData1.id = 1;
	TestData1.data = (XtPointer)&MyPixel;

	n=0;
	XtSetArg (args[n], XmNclientData, (XtPointer)&TestData1);  n++;
	XmDropSiteUpdate (DropSite[0],args,n);



	/*
	 * Second
	 */

	

	MyPixmap =  XCreatePixmapFromBitmapData(display,
                                DefaultRootWindow(display),
                                gnu_bits, gnu_width, gnu_height,
                                WhitePixel(display,DefaultScreen(display)),
                                BlackPixel(display,DefaultScreen(display)),
                                DefaultDepth(display,DefaultScreen(display)));


	TestData2.id = 2;
	TestData2.data = (XtPointer)&MyPixmap;



	n=0;
	XtSetArg (args[n], XmNclientData, (XtPointer)&TestData2);  n++; 
	XmDropSiteUpdate (DropSite[1],args,n);

	

	/*
	 * Third
	 */


	MyCompString = XmStringCreate ("ListItem", 
					XmSTRING_DEFAULT_CHARSET);

	TestData3.id = 3;
	TestData3.data = (XtPointer)&MyCompString;

	n=0;
	XtSetArg (args[n], XmNclientData, (XtPointer)&TestData3);  n++;
	XmDropSiteUpdate (DropSite[2],args,n);

	

	/*
	 * Fourth
	 */

	MyInt = 2;
	TestData4.id = 4;
	TestData4.data = (XtPointer)&MyInt;
	
	n=0;
	XtSetArg (args[n], XmNclientData, (XtPointer)&TestData4);  n++;
	XmDropSiteUpdate (DropSite[3],args,n);

	/*
	 * Fifth
         */

	MyChar = "Another Label";
	TestData5.id = 5;
	TestData5.data = (XtPointer)&MyChar;
	
	n=0;
	XtSetArg (args[n], XmNclientData, (XtPointer)&TestData5);  n++;
	XmDropSiteUpdate (DropSite[4],args,n); 



	XtRealizeWidget (Shell1);



	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();
	CommonPause();

	XtAppMainLoop(app_context);
  
      }






static void
HandleDrop (Widget w, XtPointer client_data, XtPointer call_data)	
{
	XmDropProcCallback DropProc;
        Widget dc;
        XmDropTransferEntryRec transferEntries[2];
        XmDropTransferEntry transferList;
        Atom *importTargets;
        Arg args[MAX_ARGS];
        int n;
        Arg cargs[MAX_ARGS];
        int cn;
        ClientData *cdata;        

	int which_widget;
	XmString tcs, ListItems[1];

	DropProc = (XmDropProcCallback)call_data;
        dc = DropProc->dragContext;
        
	n=0;
	if ((DropProc->dropAction != XmDROP) || 
	    (DropProc->operation != XmDROP_COPY))
	  {
	      XtSetArg(args[n], XmNtransferStatus, XmTRANSFER_FAILURE); n++;
	  } 

	cn=0;
	XtSetArg (cargs[n], XmNclientData, &cdata);  cn++;
	XmDropSiteRetrieve (w, cargs, cn);

	which_widget = cdata->id;
	
	cn = 0;
	switch (which_widget)
	  {
	   case 1:
	     XtSetArg(cargs[cn], XmNbackground, *((Pixel *)cdata->data)); cn++;
	     break;

	   case 2:
	     XtSetArg(cargs[cn], XmNlabelType, XmPIXMAP); cn++;
  	     XtSetArg(cargs[cn], XmNlabelPixmap,*((Pixmap *)cdata->data));cn++; 
	     break;

	   case 3:
	     ListItems[0] = *((XmString *)cdata->data);
	     XmListAddItem (w, ListItems[0], 1);
	     break;

	   case 4:
	     XtSetArg(cargs[cn], XmNvalue,*((int *)cdata->data)); cn++; 
	     break;

	   case 5:
	     tcs = XmStringCreate (*((char **)cdata->data),
                   XmFONTLIST_DEFAULT_TAG); cn++;
	     XtSetArg(cargs[cn], XmNlabelString, tcs); cn++;
	     break;
	
	   default:
	     break;
	     }

	if (cn > 0)
	  XtSetValues (w,cargs,cn);

	XmDropTransferStart(dc,args,n); 
      }















