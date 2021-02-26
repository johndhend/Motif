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
/*   $XConsortium: WMShellGeom.h /main/8 1995/07/13 19:21:38 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/*
 *	file: WMShellGeometry.h
 */

#define	NUM_SCALES		14
#define	MAX_NAME_LEN	100

/* The order should be maintained always */
#define	BASEHEIGHT	0
#define	BASEWIDTH	BASEHEIGHT+1
#define	HEIGHTINC	BASEWIDTH+1
#define	WIDTHINC	HEIGHTINC+1
#define	ICONX		WIDTHINC+1
#define	ICONY		ICONX+1
#define	MAXASPECTX	ICONY+1
#define	MAXASPECTY	MAXASPECTX+1
#define	MINASPECTX	MAXASPECTY+1
#define	MINASPECTY	MINASPECTX+1
#define	MAXHEIGHT	MINASPECTY+1
#define	MAXWIDTH	MAXHEIGHT+1
#define	MINHEIGHT	MAXWIDTH+1
#define	MINWIDTH	MINHEIGHT+1


struct	scale_info {

	Widget	widget;
	char	titleString[MAX_NAME_LEN + 1];
	int		minValue;
	int		maxValue;

};

struct scale_info	Scales[NUM_SCALES] = {

	{ NULL, "baseHeight", 0, -1 },
	{ NULL, "baseWidth",  0, -1 },
	{ NULL, "heightInc",  1, -1 },
	{ NULL, "widthInc",   1, -1 },
	{ NULL, "iconX",      0, -1 },
	{ NULL, "iconY",      0, -1 },
	{ NULL, "maxAspectX", 1, -1 },
	{ NULL, "maxAspectY", 1, -1 },
	{ NULL, "minAspectX", 1, -1 },
	{ NULL, "minAspectY", 1, -1 },
	{ NULL, "maxHeight",  0, -1 },
	{ NULL, "maxWidth",   0, -1 },
	{ NULL, "minHeight",  0, -1 },
	{ NULL, "minWidth",   0, -1 }

};

Arg	scale_values[NUM_SCALES] = {

	{ XmNbaseHeight, -1 },
	{ XmNbaseWidth,  -1 },
	{ XmNheightInc,  -1 },
	{ XmNwidthInc,   -1 },
	{ XmNiconX,      -1 },
	{ XmNiconY,      -1 },
	{ XmNmaxAspectX, -1 },
	{ XmNmaxAspectY, -1 },
	{ XmNminAspectX, -1 },
	{ XmNminAspectY, -1 },
	{ XmNmaxHeight,  -1 },
	{ XmNmaxWidth,   -1 },
	{ XmNminHeight,  -1 },
	{ XmNminWidth,   -1 }

};

int			screenHeight, screenWidth;
Widget	  	Form;
Widget		WMShell_Resources;
Widget		Frame1;
Widget	  	RowCol1;
Widget		WhichShell_Pulldown;
Widget		WhichShell_Option;
Widget		Application_Shell, Top_Shell, Dialog_Shell, All_Shells;
Widget		applicationShell, topLevelShell, dialogShell;
Widget		application_btn, topLevel_btn;

XmFontList 	font_list;
char	fontName[MAX_NAME_LEN + 1];
Bool	no_adjust = False;

/*  Private Functions  */


static void  	Application_ShellCB(Widget w, XtPointer client_data, 
									XtPointer call_data);
static void  	Top_ShellCB(Widget w, XtPointer client_data, 
						   XtPointer call_data);
static void  	Dialog_ShellCB(Widget w, XtPointer client_data, 
							   XtPointer call_data);
static void  	All_ShellsCB(Widget w, XtPointer client_data, 
							 XtPointer call_data);
	
static void 	CreateWMShellResources(Widget w);

static void 	GetWMShellResources();
static void 	SetWMShellResources(Widget widget);

static Widget  	CreatePushButton(Widget parent, char *label);

