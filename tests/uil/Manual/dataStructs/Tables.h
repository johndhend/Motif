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
/*   $XConsortium: Tables.h /main/4 1995/07/13 20:34:45 drk $ */

#include <Mrm/MrmAppl.h>

#include <Xm/PushB.h>

#define NUM_TESTS	6

/* TEMP FIX from XmString.c */

typedef struct _XmFontListRec
{
    XFontStruct      *font;
    XmStringCharSet  charset;
}
    XmFontListRec;

/*
 * Name of uid file
 */

String		filename_vec[] =
{
    "dataS.uid"
};

MrmCount	filename_num =
(sizeof(filename_vec) / sizeof(filename_vec[0]));

/*
 * Callback routines
 */

void		integer_table_proc(),
		compound_string_table_proc(),
		asciz_string_table_proc(),
		font_table_proc(),
		identifier_proc();

/*
 * Convenience routine
 */

void		error_proc();
void		compare_fonts();

/*
 * Names to register with MrmRegisterNames
 */

static MrmRegisterArg reglist[] = 
{
    "integer_table_proc",		(caddr_t) integer_table_proc,
    "compound_string_table_proc",	(caddr_t) compound_string_table_proc,
    "asciz_string_table_proc",		(caddr_t) asciz_string_table_proc,
    "font_table_proc",			(caddr_t) font_table_proc,
    "identifier_proc",			(caddr_t) identifier_proc,
    "ident1",				(caddr_t) 50,
    "ident2",				(caddr_t) 2001
};

static int reglist_num =
(sizeof(reglist) / sizeof(reglist[0]));

/*
 * Local declarations
 */

MrmHierarchy	s_MrmHierarchy;
MrmType		class;

Display		*dsp;
Colormap	cmap;

Widget		toplevel = NULL,
		UIL_widgets[NUM_TESTS] =
		{
		    NULL, NULL, NULL, NULL, NULL, NULL
		};

String		UIL_widget_names[NUM_TESTS] = 
		{
		    "widget5",
		    "widget5a",
		    "widget6",
		    "widget7",
		    "widget8",
		    "widget9"
		};

String		test_result_headers[NUM_TESTS] =
		{
		    "Integer Table",
		    "Integer Table 2 (OSF CR 5691)",
		    "Compound String Table",
		    "Asciz String Table",
		    "Font Table",
		    "Identifier"
		};

int		X_integer_table[5] = 
		{
		    628,
		    0,
		    -90009,
		    4883,
		    -29
		};

String		X_compound_string_table[3] =
		{
		    "stRIng1",
		    "string number 2",
		    "Third string"
		};

String		X_asciz_string_table[4] = 
		{
		    "a_string",
		    "ThiS_stRing2",
		    "3_stringG",
		    "String_4_U"
		};

String		X_font_names[3] = 
		{
		    "fixed",
		    "6x10",
		    "8x13bold"
		};

int		expected_ident[2] =
{
    50,
    2001
};

String		ident_type[2] =
{
    "Identifier as widget resource value",
    "Identifier as callback tag value   "
};

int		ident_int = 0;

int		errors[NUM_TESTS] =
		{
		    0, 0, 0, 0, 0, 0
		};

int		ndx;
