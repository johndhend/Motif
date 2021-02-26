/* $XConsortium: DNDScale1.c /main/5 1995/07/15 21:00:15 drk $ */
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
#include <Xm/DragDrop.h>

#define NUM_TARGETS  2

int        n;
Arg        args[MAX_ARGS];
Widget     BBoard1, Scale1, Text1;
Atom       targets[NUM_TARGETS], STRING, COMPOUND_TEXT;

/*
 *  Callbacks.
 */
static void DropTransferCallback(w, closure, seltype, type, value,
                                                                 length, format)
Widget                  w;
XtPointer               closure ;
Atom                    *seltype ;
Atom                    *type ;
XtPointer               value ;
unsigned long   *length ;
int                     *format ;
{

        XTextProperty   tmp_prop;
        int                     num_vals;
        int                             ok;
       char                    *total_tmp_value = NULL;
        char                    **tmp_value;
        int                     malloc_size = 0;
        char                    *actual_value;
        int                             actual_length = 0;
        Cardinal                i;



        if (*length)
                if (*type == COMPOUND_TEXT ||
                    *type == STRING ) {

                tmp_prop.value = (unsigned char *) value;
                        tmp_prop.encoding = *type;
                        tmp_prop.format = 8;
                        tmp_prop.nitems = *length;
                        num_vals = 0;

                        ok = 0;

                        ok = XmbTextPropertyToTextList(display, &tmp_prop, 
                                 &tmp_value, &num_vals);

                        if (num_vals && (ok == Success || ok > 0)) {

                                for (i = 0; i < num_vals; i++)
                                        malloc_size += strlen(*tmp_value + i);
                                total_tmp_value = 
                                  XtMalloc ((unsigned) malloc_size + 1);
                                total_tmp_value[0] = '\0';
                                for (i = 0; i < num_vals ; i++)
                                        strcat(total_tmp_value, *tmp_value + i);
                                actual_value = total_tmp_value;
                                actual_length = strlen(total_tmp_value);

                        }
                        else {
                                if (value) {
                                        XtFree((char *)value);
                                        value = NULL;
                                }
                                actual_length = -1;
                        }

                }
        /* You no longer need it, so free it */
        if (total_tmp_value != NULL)
                XtFree(total_tmp_value);

}


void
ListExports( Widget w, XtPointer client_data, XtPointer call_data )
{
   Widget  dragContext;
   Atom    *exportTargets;
   int     numExportTargets, i;
   XmDropTransferEntryRec  transferEntries[2];
   XmDropTransferEntry             transferList;


   dragContext = ((XmDragProcCallbackStruct *)call_data)->dragContext;

   n = 0;
   XtSetArg( args[n], XmNexportTargets, &exportTargets ); n++;
   XtSetArg( args[n], XmNnumExportTargets, &numExportTargets ); n++;
   XtGetValues( dragContext, args, n );

   for ( i = 0; i < numExportTargets; i++ )
   {
     if ( exportTargets[i] == STRING ) 
     {
        printf("STRING is a Supported Target for Scale.\n");
        transferEntries[0].target = STRING;
     }
     if ( exportTargets[i] == COMPOUND_TEXT ) 
     {
        printf("COMPOUND_TEXT is a Supported Target for Scale.\n");
        transferEntries[0].target = COMPOUND_TEXT;
     }
   }

   transferEntries[0].client_data = NULL;

   transferList = transferEntries;

   n = 0;
   XtSetArg(args[n], XmNdropTransfers, transferList); n++;
   XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
   XtSetArg(args[n], XmNtransferProc, DropTransferCallback); n++;
   XmDropTransferStart( dragContext, args, n );
}

void main( argc, argv )
int	argc;
char	**argv;
{
    CommonTestInit(argc, argv);

   /** Begin testing CR 4846 **/
    n = 0;
    XtSetArg(args[n], XmNwidth, 200 );  n++;
    XtSetArg(args[n], XmNheight, 200);  n++;
    BBoard1 = XmCreateBulletinBoard( Shell1, "BBoard1", args, n );
    XtManageChild(BBoard1);

    n = 0;
    XtSetArg(args[n], XmNx, 0);  n++;
    XtSetArg(args[n], XmNy, 0);  n++;
    XtSetArg(args[n], XmNwidth, 180);  n++;
    XtSetArg(args[n], XmNheight, 75 );  n++;
    XtSetArg(args[n], XmNfontList, CommonGetFontList("helvo18")); n++;
    XtSetArg(args[n], XmNdecimalPoints, 0);  n++;
    XtSetArg(args[n], XmNminimum, 0); n++;
    XtSetArg(args[n], XmNmaximum, 100); n++;
    XtSetArg(args[n], XmNshowValue, TRUE);  n++;
    XtSetArg(args[n], XmNorientation, XmHORIZONTAL);  n++;
    Scale1 = XmCreateScale( BBoard1, "Scale1", args, n );
    XtManageChild( Scale1 );

    /*  Add a text widget. */
    n = 0;
    XtSetArg(args[n], XmNx, 0);  n++;
    XtSetArg(args[n], XmNy, 100);  n++;
    XtSetArg(args[n], XmNwidth, 180);  n++;
    XtSetArg(args[n], XmNheight, 100);  n++;
    XtSetArg(args[n], XmNrows, 2);  n++;
    XtSetArg( args[n], XmNeditable, True ); n++;
    Text1 = XmCreateText( BBoard1, "Text1", args, n );
    XtManageChild(Text1);

    XtRealizeWidget(Shell1);

   /*  Test whether STRING target is supported by Scale widget. */
    STRING = XmInternAtom(display, "STRING", False);

    n = 0;
    XtSetArg(args[n], XmNdropProc, ListExports);  n++;
    XtSetArg(args[n], XmNimportTargets, &STRING);  n++;
    XtSetArg(args[n], XmNnumImportTargets, 1);  n++;
    XmDropSiteUpdate( Text1, args, n );
   
    CommonPause();
    
   /*  Test whether COMPOUND_TEXT target is supported by Scale widget. */
    COMPOUND_TEXT = XmInternAtom(display, "COMPOUND_TEXT", False);

    n = 0;
    XtSetArg(args[n], XmNimportTargets, &COMPOUND_TEXT);  n++;
    XtSetArg(args[n], XmNnumImportTargets, 1);  n++;
    XmDropSiteUpdate( Text1, args, n );

    CommonPause();

   /** End testing CR 4846 **/

    XtAppMainLoop(app_context);
}

