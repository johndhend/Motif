%{
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
#if defined(__STDC__)
#include <string.h>
#endif

#ifndef XmConst
#if defined(__STDC__) || !defined( NO_CONST )
#define XmConst const
#else
#define XmConst
#endif /* __STDC__ */
#endif /* XmConst */

#ifdef YY_BUFFER_SIZE
#define BUF_SIZE YY_BUFFER_SIZE
#else
#define BUF_SIZE 8192
#endif

char            yystringval[BUF_SIZE];      /* any string value */
char            yynameval[BUF_SIZE];         /* any identifier (name) */
int             yytknval1;              /* terminal token value 1 */
int             yytknval2;              /* terminal token value 2 */

%}

%p 3000
%%

[ \t\f]		{}

[\n]		{ wml_line_count += 1; }

"Alias"			{ return ALIAS; }
"Argument"		{ return ARGUMENT; }
"CharacterSet"		{ return CHARACTERSET; }
"CharacterSize"		{ return CHARACTERSIZE; }
"Child"			{ return CHILD; }
"Children"		{ return CHILDREN; }
"Class"			{ return CLASS; }
"Constraint"		{ return CONSTRAINT; }
"ControlList"		{ return CONTROLLIST; }
"Controls"		{ return CONTROLS; }
"ControlsMapToResource"	{ return CTRLMAPSRESOURCE; }
"ConvenienceFunction"	{ return CONVFUNC; }
"DataType"		{ return DATATYPE; }
"Default"		{ return DEFAULT; }
"DialogClass"		{ return DIALOGCLASS; }
"Direction"		{ return DIRECTION; }
"DocName"		{ return DOCNAME; }
"EnumLiteral"		{ return ENUMLITERAL; }
"EnumerationSet"	{ return ENUMERATIONSET; }
"EnumerationValue"	{ return ENUMERATIONVALUE; }
"Exclude"		{ return EXCLUDE; }
"False"			{ return ATTRFALSE; }
"FontListElementTag"	{ return XMSTRINGCHARSETNAME; }
"Gadget"		{ return GADGET; }
"InternalLiteral"	{ return INTERNALLITERAL; }
"LeftToRight"		{ return LEFTTORIGHT; }
"MetaClass"		{ return METACLASS; }
"MixedOneAndTwoByte"	{ return MIXED1_2BYTE; }
"OneByte"		{ return ONEBYTE; }
"ParentClass"		{ return PARENTCLASS; }
"ParseDirection"	{ return PARSEDIRECTION; }
"Reason"		{ return REASON; }
"Related"		{ return RELATED; }
"Resource"		{ return RESOURCE; }
"ResourceLiteral"	{ return RESOURCELITERAL; }
"Resources"		{ return RESOURCES; }
"RightToLeft"		{ return RIGHTTOLEFT; }
"SubResource"		{ return SUBRESOURCE; }
"SuperClass"		{ return SUPERCLASS; }
"True"			{ return ATTRTRUE; }
"TwoByte"		{ return TWOBYTE; }
"Type"			{ return TYPE; }
"Widget"		{ return WIDGET; }
"WidgetClass"		{ return WIDGETCLASS; }
"XmStringCharsetName"	{ return XMSTRINGCHARSETNAME; }

":"			{ return COLON; }
";"			{ return SEMICOLON; }
"="			{ return EQUALS; }
"{"			{ return LBRACE; }
"}"			{ return RBRACE; }

"!"[^\n]*	{}

"#"[^\n]*	{}

[a-zA-Z_][a-zA-Z0-9$_]* {	/* string without quotes	*/
	strcpy (yystringval, (XmConst char *) yytext);
	return STRING;
	}

\"[^"\n]*\\	{	/* escaped character in the string 	*/
		yymore();
		}

\"[^"\n]*\"	{	/* String in quotes	*/
		strncpy(yystringval, (XmConst char *) yytext+1, yyleng - 2);
		yystringval[yyleng-2] = '\0' ;
		return STRING;
		}
\"[^"\n]*	{
		printf ("\nUnterminated string near %s, line %d",
			yytext, wml_line_count);
		return ERRORTOKEN;
		}

.	{
	printf ("\nEncountered illegal character '%c', line %d",
		yytext[0], wml_line_count);
	return ERRORTOKEN;
	}
