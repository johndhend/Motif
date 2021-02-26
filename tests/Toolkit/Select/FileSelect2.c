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
static char rcsid[] = "$TOG: FileSelect2.c /main/10 1999/05/28 15:45:55 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#include <testlib.h>
#include <unistd.h>

Widget   	CancelW;
Widget     	FileSelectionBox1;
Widget		Text1;

void  GoneCB();

#define MYNSTRINGS_DIR 8
#define TARGET_DIR "/tmp/FS/fourteencharac/fourteencharac/fourteencharac/"

char *mystrings_dir[] = {
   "Hello", "this", "is", "a", "new", "dir", "search", "proc"
};

#define MYNSTRINGS_FILE 8

char *mystrings_file[] = {
   "Hello", "this", "is", "a", "new", "file", "search", "proc"
};

/* New file Search Proc */

XtArgVal NewDirSearchProc()
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    XmString      mymask, myspec, mylist[MYNSTRINGS_DIR];

    /*  Fill in the list, Items, Count */

    for (n = 0; n < MYNSTRINGS_DIR; n++)
    	mylist[n] = XmStringCreateSimple ((char *) mystrings_dir[n]);

    tcs = XmStringCreateSimple ((char *)"A very very long label");

    n = 0;
    XtSetArg (args[n], XmNdirListItems, mylist); 		n++;
    XtSetArg (args[n], XmNdirListItemCount, MYNSTRINGS_DIR); 	n++;
    XtSetArg (args[n], XmNdirListLabelString, tcs ); n++;
    XtSetArg (args[n], XmNdirectoryValid, TRUE); 		n++;
    XtSetArg (args[n], XmNlistUpdated, FALSE); 			n++;
    XtSetValues (FileSelectionBox1, args, n);

    XmStringFree( tcs );
    for (n = 0; n < MYNSTRINGS_DIR; n++)
		XmStringFree(mylist[n]);
}


XtArgVal NewFileSearchProc()
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs;
    XmString      mymask, myspec, mylist[MYNSTRINGS_FILE];

    /*  Fill in the list, Items, Count */

    for (n = 0; n < MYNSTRINGS_FILE; n++)
    	mylist[n] = XmStringCreateSimple ((char *) mystrings_file[n]);

    tcs = XmStringCreateSimple("A Very Long Label for test purposes");

    n = 0;
    XtSetArg (args[n], XmNfileListItems, mylist); 		n++;
    XtSetArg (args[n], XmNfileListItemCount, MYNSTRINGS_FILE); 	n++;
    XtSetArg (args[n], XmNfileListLabelString, tcs ); n++;
    XtSetArg (args[n], XmNlistUpdated, TRUE); 			n++;
    XtSetValues (FileSelectionBox1, args, n);

    XmStringFree(tcs);

    for (n = 0; n < MYNSTRINGS_FILE; n++)
		XmStringFree(mylist[n]);
}


void check_out()
{
    Arg           args[MAX_ARGS];
    XmString      mymask, myspec;
    int           n, *mydircount, *myfilecount;
    XtArgVal      search_proc;


    /* Print out interesting values */

    XmFileSelectionDoSearch (FileSelectionBox1, NULL);

    n = 0;
    XtSetArg (args[n], XmNdirectory, &mymask); 			n++;
    XtSetArg (args[n], XmNpattern, &myspec); 			n++;
    XtSetArg (args[n], XmNdirListItemCount, &mydircount); 	n++;
    XtSetArg (args[n], XmNfileListItemCount, &myfilecount); 	n++;
    XtSetArg (args[n], XmNfileSearchProc, &search_proc); 	n++;
    XtGetValues (FileSelectionBox1, args, n);

#ifdef DEBUG

    printf ("Dir: %s, Pat: %s, dirCount: %i, fileCount: %i,\n", 
             CommonCsToRs(mymask), CommonCsToRs(myspec), 
	     mydircount, myfilecount);

    printf ("Is fileSearchProc NULL? ");

    if (!search_proc) 
	printf (" Yes.\n");
    else 
	printf (" No, address is %d\n", search_proc);

#endif

	if (mymask != NULL)
		XmStringFree(mymask);
	if (myspec != NULL)
		XmStringFree(myspec);

}


void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    XmString      tcs, tcs2;
    Widget	  Frame;

/* Ensure target directory for FSB is set up properly */

    if ( access(TARGET_DIR,F_OK | R_OK) ) {
	printf("Target directory %s is not set up\n",TARGET_DIR);
	exit(1);
    }

    CommonTestInit(argc, argv);

    n = 0;
    Frame = XmCreateFrame(Shell1, "Frame1", args, n);
    XtManageChild(Frame);

    tcs = XmStringCreateSimple(TARGET_DIR);

    tcs2 = XmStringCreateSimple("*");

    n = 0;
    XtSetArg(args[n], XmNdirMask, tcs);  			n++;
    XtSetArg(args[n], XmNdirectory, tcs);  			n++;
    XtSetArg(args[n], XmNpattern, tcs2); 			n++;
    XtSetArg(args[n], XmNwidth, 400);				n++;
    XtSetArg(args[n], XmNresizePolicy, XmRESIZE_NONE);          n++;
    FileSelectionBox1 = XmCreateFileSelectionBox(Frame, "FileSelectionBox1", 
						 args, n);
    XtManageChild(FileSelectionBox1);

    XmStringFree(tcs);
    XmStringFree(tcs2);

    XtRealizeWidget(Shell1);

    /* Print out the DirMask and  DirSpec */

    check_out();

    /* add a callback to the Cancel button to destroy the world */

    CancelW = XmFileSelectionBoxGetChild(FileSelectionBox1,
            				 XmDIALOG_CANCEL_BUTTON);
    XtAddCallback(CancelW,XmNactivateCallback, GoneCB, NULL);

    /* Ok, we will start playing with the doc ideas */

    CommonPause ();

    printf ("Adding an additional Work Area - Text widget\n");

    XtSetArg(args[n], XmNrows, 4);  				n++;
    XtSetArg(args[n], XmNscrollVertical, True);  		n++;
    XtSetArg(args[n], XmNscrollHorizontal, True);  		n++;
    XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);  	n++;
    XtSetArg(args[n], XmNvalue, "Some Text.");  		n++;
    Text1 = XmCreateText(FileSelectionBox1, "Text1", args, n);

    XtManageChild(XmFileSelectionBoxGetChild(FileSelectionBox1,
                                             XmDIALOG_WORK_AREA));

    CommonPause ();

    printf ("Unmanage Files label and list\n");

    XtUnmanageChild(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                                       	XmDIALOG_LIST)));
    XtUnmanageChild(XmFileSelectionBoxGetChild(FileSelectionBox1,
                                       	XmDIALOG_LIST_LABEL));

    CommonPause ();

    printf ("Manage Files and Unmanage Directories label and list\n");

    XtManageChild(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                                     	XmDIALOG_LIST)));
    XtManageChild(XmFileSelectionBoxGetChild(FileSelectionBox1,
                                   	XmDIALOG_LIST_LABEL));
    XtUnmanageChild( XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                                      	XmDIALOG_DIR_LIST)));
    XtUnmanageChild(XmFileSelectionBoxGetChild(FileSelectionBox1,
                                      	XmDIALOG_DIR_LIST_LABEL));

    CommonPause ();

    printf ("Manage Directories label and list - unmap Files list\n");

    XtManageChild(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                    			XmDIALOG_DIR_LIST)));
    XtManageChild(XmFileSelectionBoxGetChild(FileSelectionBox1,
                    			XmDIALOG_DIR_LIST_LABEL));
    XtUnmapWidget(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                    			XmDIALOG_LIST)));

    CommonPause ();

    printf ("Remap the Files list\n");

    XtMapWidget(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                    			XmDIALOG_LIST)));
    XtMapWidget(XtParent (XmFileSelectionBoxGetChild(FileSelectionBox1,
                    			XmDIALOG_LIST_LABEL)));


    /*  Modify the Directory list and Sundries... */

    CommonPause();

    printf("Set new DirSearchProc\n");

    n = 0;
    XtSetArg (args[n], XmNdirSearchProc, NewDirSearchProc); 	n++;
    XtSetValues(FileSelectionBox1, args, n);

    XmFileSelectionDoSearch (FileSelectionBox1, NULL);

    /* check out interesting values */

    check_out();

    /*  Modify the File list and sundries.... */

    CommonPause();

    printf("Set new FileSearchProc\n");

    n = 0;
    XtSetArg (args[n], XmNfileSearchProc, NewFileSearchProc); 	n++;
    XtSetValues (FileSelectionBox1, args, n);

    XmFileSelectionDoSearch (FileSelectionBox1, NULL);

    /* check out interesting values */

    check_out();

    /*  Set the dir and file search proc back to the originals */

    CommonPause();

    /* Begin Test for Pir2985 */

    printf("Set FileSearchProc and DirSearchProc back to default\n");

    tcs = XmStringLtoRCreate(TARGET_DIR,XmSTRING_DEFAULT_CHARSET);

    n = 0;
    XtSetArg (args[n], XmNdirSearchProc, NULL); 		n++;
    XtSetArg (args[n], XmNfileSearchProc, NULL); 		n++;
    XtSetValues (FileSelectionBox1, args, n);

    XmFileSelectionDoSearch (FileSelectionBox1, tcs);


    XmStringFree(tcs);

    /* check_out interesting values */

    check_out();

    /* End Test for Pir2985 */
    
    printf("That's All Folks\n");

    CommonPause();

    XtAppMainLoop(app_context);
}


void GoneCB(w, client_data, call_data )
    Widget  w;
    XtPointer client_data;
    XtPointer call_data;
{
    /* callback for when user clicks the cancel button */
    
    Widget dad;

    dad = XtParent(w);      /* get parent of cancel button */
    XtDestroyWidget(w);      /* destroy widget */
    XtDestroyWidget(dad);   /* and parent */
}
