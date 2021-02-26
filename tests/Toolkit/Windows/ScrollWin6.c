/* $XConsortium: ScrollWin6.c /main/4 1995/07/15 21:11:58 drk $ */
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

static char* textData = "...a place where children did not even know what a bush, a forest, or a pond was;\n\
 where the air was so bad with carbon dioxide and sulphur that pollution killed at least one member in every family;\n\
 a place where men and beasts baked in a furnace for the eight months of summer until\n\
 the monsoon transformed their alleyways and shacks into swamps of mud and excrement;\n\
 a place where leprosy, tuberculosis, dysentery and all the malnutrition diseases ...\n\
 reduced the average life expectancy to one of the lowest in the world; a place where\n\
 eighty-five hundred cows and buffalo, tied up to dung heaps, provided milk infected with germs.\n\
 Above all, however, the City of Joy was a place where the most extreme economic poverty ran rife.\n\
 Nine out of ten of its inhabitants did not have a single rupee per day with which\n\
 to buy half a pound of rice.  Furthermore, like all ... slums, the\n\
 City of Joy was generally ignored by other citizens of Calcutta,\n\
 except in case of crime or strike.  Considered a dangerous\n\
 neighborhood with a terrible reputation, the haunt of untouchables,\n\
 pariahs, social rejects, it was a world apart, living apart from the\n\
 world.\n\
\n\
 The City of Joy, Dominique Lapierre,\n\
 Warner Books, Inc., New York, NY, 1985.";

void  main(argc, argv)
    int     argc;
    char  **argv;
{
    register int  n;
    Arg           args[MAX_ARGS];
    Widget        scroll1, label1, hscrollbar, vscrollbar, frame1;
    XmString      s;

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    XtSetValues(Shell1, args, n);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    scroll1 = XmCreateScrolledWindow(Shell1, "scrollwin1", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmNO_SCROLL); n++;
    frame1 = XmCreateFrame(scroll1, "frame1", args, n);

    n = 0;
    s = XmStringCreateLtoR(textData, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, s); n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
    label1 = XmCreateLabel(frame1, "label1", args, n);
    XmStringFree(s);

    XtManageChild(label1);
    XtManageChild(frame1);
    XtManageChild(scroll1);
    XtRealizeWidget(Shell1);

    CommonPause();

    XtDestroyWidget(label1);
    XtDestroyWidget(frame1);
    XtDestroyWidget(scroll1);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    scroll1 = XmCreateScrolledWindow(Shell1, "scrollwin1", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmSCROLL_VERT); n++;
    frame1 = XmCreateFrame(scroll1, "frame1", args, n);

    n = 0;
    s = XmStringCreateLtoR(textData, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, s); n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
    label1 = XmCreateLabel(frame1, "label1", args, n);
    XmStringFree(s);

    XtManageChild(label1);
    XtManageChild(frame1);
    XtManageChild(scroll1);

    CommonPause();

    XtDestroyWidget(label1);
    XtDestroyWidget(frame1);
    XtDestroyWidget(scroll1);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    scroll1 = XmCreateScrolledWindow(Shell1, "scrollwin1", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmSCROLL_HOR); n++;
    frame1 = XmCreateFrame(scroll1, "frame1", args, n);

    n = 0;
    s = XmStringCreateLtoR(textData, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, s); n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
    label1 = XmCreateLabel(frame1, "label1", args, n);
    XmStringFree(s);

    XtManageChild(label1);
    XtManageChild(frame1);
    XtManageChild(scroll1);

    CommonPause();

    XtDestroyWidget(label1);
    XtDestroyWidget(frame1);
    XtDestroyWidget(scroll1);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    scroll1 = XmCreateScrolledWindow(Shell1, "scrollwin1", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmWORK_AREA); n++;
    frame1 = XmCreateFrame(scroll1, "frame1", args, n);

    n = 0;
    s = XmStringCreateLtoR(textData, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, s); n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
    label1 = XmCreateLabel(frame1, "label1", args, n);
    XmStringFree(s);

    XtManageChild(label1);
    XtManageChild(frame1);
    XtManageChild(scroll1);

    CommonPause();

    XtDestroyWidget(label1);
    XtDestroyWidget(frame1);
    XtDestroyWidget(scroll1);

    n = 0;
    XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED); n++;
    XtSetArg(args[n], XmNwidth, 100); n++;
    XtSetArg(args[n], XmNheight, 100); n++;
    scroll1 = XmCreateScrolledWindow(Shell1, "scrollwin1", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmHOR_SCROLLBAR); n++;
    XtSetArg(args[n], XmNshadowThickness, 10); n++;
    XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
    hscrollbar = XmCreateScrollBar(scroll1, "hscrollbar", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmVERT_SCROLLBAR); n++;
    XtSetArg(args[n], XmNshadowThickness, 10); n++;
    XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
    vscrollbar = XmCreateScrollBar(scroll1, "vscrollbar", args, n);

    n = 0;
    XtSetArg(args[n], XmNscrolledWindowChildType, XmWORK_AREA); n++;
    frame1 = XmCreateFrame(scroll1, "frame1", args, n);

    n = 0;
    s = XmStringCreateLtoR(textData, XmSTRING_DEFAULT_CHARSET);
    XtSetArg(args[n], XmNlabelString, s); n++;
    XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
    label1 = XmCreateLabel(frame1, "label1", args, n);
    XmStringFree(s);

    XtManageChild(label1);
    XtManageChild(frame1);
    XtManageChild(hscrollbar);
    XtManageChild(vscrollbar);
    XtManageChild(scroll1);

    CommonPause();

    XtAppMainLoop(app_context);
}
