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
/*   $XConsortium: CompoundS.h /main/4 1995/07/13 20:33:36 drk $ */

#include <stdio.h>

#include <Mrm/MrmAppl.h>

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
 * Convenience routine
 */

void		error_proc();

/*
 * Local declarations
 */

MrmHierarchy	s_MrmHierarchy;
MrmType		class;
MrmCode		type;

Widget		toplevel,
		UIL_widgets[3],
		X_widgets[3];

Display		*dsp;

XmString	X_compound_string1[2],
		X_compound_string2[2],
		X_compound_string3[9],
		UIL_compound_string1[3],
		UIL_compound_string2[3],
                UIL_compound_string3[9];

String		X_string = "string1";

String          X_direction_strings[9] =
{
    "CBA",
    "FED",
    "IHG",
    "JKL",
    "MNO",
    "PQR",
    "STU",
    "VWX",
    "YZA",
};

Boolean         X_rtol_direction[9] =
{
    0,1,1,1,0,1,0,0,1,
};

String          X_direction_charset[9] =
{
    "ISO8859-8",
    "ISO8859-8",
    "ISO8859-8",
    "ISO8859-8",
    "ISO8859-8",
    "ISO8859-8",
    "ISO8859-1",
    "ISO8859-1",
    "ISO8859-1",
};

XmStringCharSet	X_charset = "ISO8859-1";

String		UIL_compound_string_names[3] =
{
    "compound_string1",
    "compound_string2",
    "compound_string3",
};

String		UIL_widget_names[3] =
{
    "widget1",
    "widget2",
    "widget3",
};

String          UIL_direction_names[9] =
{
    "direction1",
    "direction2",
    "direction3",
    "direction4",
    "direction5",
    "direction6",
    "direction7",
    "direction8",
    "direction9",
};



String		X_method[2] = 
{
    "XmStringCreate(string, charset)    ",
    "XmStringCreateLtoR(string, charset)",
};

String		UIL_method[3] =
{
    "compound_string(\"string\")                          ",
    "compound_string(#char_set\"string\")                 ",
    "compound_string(\"string\", character_set = char_set)",
};

char	err_msg[80],
    	error_message[12000];

int	errors;

