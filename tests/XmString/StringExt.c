/* $XConsortium: StringExt.c /main/4 1995/07/15 21:12:39 drk $ */
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
#include <stdio.h>
#include <Xm/XmP.h>
#include <Xm/DrawingA.h>
#include <testlib.h>

/*
 *  Defines
 */
#define NUM_STRINGS 3

/*
 *  Global variables
 */
GC gc;
XmFontList fontlist;
XFontStruct   *font;

main(argc, argv)
int   argc;
char  *argv[];
{
        Widget bboard, testingArea;
	Arg args[10];
	int n;
	XGCValues  gcv;
	XmFontContext font_context;
	XmStringCharSet charset;
	
	void PostString();

	CommonTestInit(argc, argv);

	n = 0;
	bboard = XmCreateBulletinBoard(Shell1, "bboard", args, n);
	XtManageChild (bboard);

	n = 0;
	XtSetArg(args[n], XmNwidth, 300); n++;
	XtSetArg(args[n], XmNheight, 300); n++;
	XtSetArg(args[n], XmNbackground, 0); n++;
	testingArea = XmCreateDrawingArea(bboard, "DrawingArea", args, n);
	XtManageChild(testingArea);

	XtAddEventHandler(testingArea, ButtonPressMask, FALSE,
		PostString, NULL);

	fontlist = CommonGetFontList( default_font );
	XmFontListInitFontContext(&font_context, fontlist);
	XmFontListGetNextFont(font_context, &charset, &font);
	XtFree(charset);
	XmFontListFreeFontContext(font_context);

	XtRealizeWidget (Shell1);

	n = 0;
	XtSetArg(args[n], XmNforeground, &gcv.foreground); n++;
	XtSetArg(args[n], XmNbackground, &gcv.background); n++;
	XtGetValues(testingArea, args, n);

	gcv.font = font->fid;

	gc = XCreateGC(XtDisplay(testingArea), XtWindow(testingArea),
		(GCFont | GCForeground | GCBackground), &gcv);

        CommonPause();
        CommonPause();
	XtAppMainLoop (app_context);
}

void PostString(w, popup, event)
Widget  w;
char * popup;
XEvent *event;
{
	XmString	         string[NUM_STRINGS];
	static Dimension         x = 50, y = 50;
	Dimension                width1, width2, width3;
	Dimension                height1, height2, height3;
	Dimension		 baseline;
	XRectangle               ClipRect;
	XCharStruct              char_return;
	int                      dir, asc[NUM_STRINGS-1], dsc, i;
	char                     *char_string[NUM_STRINGS];
        char                     buffer[126];

        /* Initialize string array. */
        for ( i = 0; i < NUM_STRINGS; i++ )
            string[i] = (XmString)0;

	/* Use X and Z to show the problems */
	char_string[0] = "X is an Example of Z";
	char_string[1] = "Z is an Example of X";
        char_string[2] = 
          "X is an Example of Z\nZ is an Example of X\nX is an Example of Z";

	string[0] = XmStringCreateLocalized(char_string[0]);
	string[1] = XmStringCreateLtoR(char_string[1], XmFONTLIST_DEFAULT_TAG);
	string[2] = XmStringCreateLtoR(char_string[2], XmFONTLIST_DEFAULT_TAG);

       
       /*
        *  Get the width and height of the one line strings using the functions:
        *      XmStringExtent
	*      XmStringWidth, XmStringHeight
        *      XTextExtents
        */  
        fprintf(stdout, "\n\n");
        fprintf(stdout, "The following functions were called to\n");
        fprintf(stdout, "get the expected and actual dimensions\n");
        fprintf(stdout, "of the Display String.\n\n");

        for ( i = 0; i < NUM_STRINGS; i++ )
        {
          fprintf(stdout, "Display String:\n\"%s\"", char_string[i] );
          fprintf(stdout, "\n\n");

          if ( i < NUM_STRINGS - 1 )
          { 
           XmStringExtent(fontlist, string[i], &width1, &height1);
	   width2 = XmStringWidth( fontlist, string[i] );
	   height2 = XmStringHeight( fontlist, string[i] );

	   XTextExtents(font, char_string[i], strlen(char_string[i]), 
                        &dir, &asc[i], &dsc, &char_return);
           width3 = char_return.rbearing - char_return.lbearing + 1;
	   height3 = asc[i]+dsc;
                 
	   fprintf(stdout, "Function          Width     Height     \n");
	   fprintf(stdout, "--------          -----     ------     \n");
           fprintf(stdout, "XmStringExtent()   %d        %d     \n", 
                           width1, height1 );   
           fprintf(stdout, "XmStringWidth()    %d        -      \n", 
                           width2 );   
           fprintf(stdout, "XmStringHeight()    -         %d     \n", 
                           height2 );   
           fprintf(stdout, "XmTextExtent()     %d        %d     \n", 
                           width3, height3 );   

           fprintf(stdout, "\n");

          /*
           *  Compare the values obtained for width and height from
           *  the XmString functions with the XTextExtent function
           *  to determine whether the XmString functions are
           *  returning the correct values. 
           */
           fprintf(stdout, "XmStringExtent() ");
           if (( width1 != width3 ) && ( height1 != height3 ))
              fprintf(stdout, "failed.\n");
           else
              fprintf(stdout, "passed.\n");

           fprintf(stdout, "XmStringWidth() ");
           if ( width2 != width3 )
              fprintf(stdout, "failed.\n");
           else
              fprintf(stdout, "passed.\n");

           fprintf(stdout, "XmStringHeight() ");
           if ( height2 != height3 )
              fprintf(stdout, "failed.\n");
           else
              fprintf(stdout, "passed.\n");

         /*  
          *  Display the string.
          */
	   ClipRect.x = x + char_return.lbearing - 1;
	   ClipRect.y = y;
	   ClipRect.width = width1;
	   ClipRect.height = height1;
	   XmStringDrawImage (XtDisplay (w), XtWindow (w),
                             fontlist,
                             string[i],
                             gc,
                             x, y, width1,
                             XmALIGNMENT_BEGINNING,
                             XmSTRING_DIRECTION_L_TO_R,
                             NULL);
	   y += (height1 + 3);

          /*
           *  Display the bounding box returned from XmStringExtent()
           *  around the string.
           */
	   XDrawRectangles(XtDisplay (w), XtWindow (w),
	         		gc,
		           	&ClipRect,
			        1);

           fprintf(stdout, "\n\n");
          }

         /*  Get the baseline values for the string. */
          baseline  = XmStringBaseline( fontlist, string[i] ); 

	  fprintf(stdout, "Function            Baseline     \n");
	  fprintf(stdout, "--------            --------     \n\n");

          fprintf(stdout, "XmStringBaseline()     %d        \n",
                           baseline );
          fprintf(stdout, "XTextExtent()          %d        \n",
                           asc[i] );

          fprintf(stdout, "\n");

         /*
          *  Since XmStringBaseline returns the baseline for the first
          *  line of text, we need the ascent of the first line of 
          *  the multiline string. Since the first line of text in
          *  the multiline string is the same of the text in the first
          *  string, set the ascent for the third line to the ascent 
          *  of the first line.
          */
          asc[2] = asc[1];

         /*
          *  Compare the baseline value returned from XmString function
          *  to the ascent value returned from XTextExtent().
          */
          fprintf(stdout, "XmStringBaseline() ");
          if ( baseline != asc[i] )
             fprintf(stdout, "failed.\n");
          else
             fprintf(stdout, "passed.\n");
          
          fprintf(stdout, "\n\n");
      }

      /* Deallocate string array members. */
       for ( i = 0; i < NUM_STRINGS; i++ )
            XmStringFree( string[i] );
}
