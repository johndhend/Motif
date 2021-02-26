/* $XConsortium: lex.c /main/5 1995/07/15 21:01:33 drk $ */
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
#include <string.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include "y.tab.h"
#include "toolchest.h"

extern YYSTYPE yylval;

void
getstring()
{
    Boolean inquote = FALSE;
    static Boolean firstLineChar = TRUE;
    static Boolean firstTokChar;
    static char newline[] = "\n";
    extern char * SaveChar();
    char c;

    /* skip white space and comments */
    while ((c = NextChar()) == ' ' || c == '\t' || c == '\n' || c == '#' ||
	   (c == '!' && firstLineChar))
    {
	if (c == '\n')
	{
	    firstLineChar = TRUE;
	    yylval.string = newline;
	    return;
	}
	else if (c == '#' || firstLineChar && c == '!')
	{
	    while ((c = NextChar()) != '\n' && c != EOF)
		;
	    firstLineChar = TRUE;
	    yylval.string = newline;
	    return;
	}
	else
	    firstLineChar = FALSE;
    }
    PrevChar();
    firstTokChar = TRUE;
    yylval.string = SaveChar();
    while ((c = NextChar()) != '\0' && c != '\n' && (inquote || (c != ' ' && c != '\t')))
    {
	if (c == '!' && firstTokChar)
	{
	    yylval.string = "!";
	    return;
	}
	firstTokChar = FALSE;
	if (c == '"')
	{
	    inquote = !inquote;
	}
	else if (c == '\\')
	{
	    c = NextChar();
	}
    }
    NullChar();
}

int
yylex()
{
    getstring();

    if (yylval.string[0] == '\n')
    {
	return ('\n');
    }
    if (yylval.string[0] == '\0')
    {
	return (0);
    }
    if (yylval.string[0] == '!')
    {
	return (F_EXEC);
    }
    else if ((yylval.string[0] == 'f' || yylval.string[0] == 'F') &&
	     yylval.string[1] == '.')
    {
	if (strcasecmp(yylval.string+2, "exec") == 0)
	{
	    return (F_EXEC);
	}
	else if (strcasecmp(yylval.string+2, "checkexec") == 0)
	{
	    return (F_CHECKEXEC);
	}
	else if (strcasecmp(yylval.string+2, "checkexpr") == 0)
	{
	    return (F_CHECKEXPR);
	}
	else if (strcasecmp(yylval.string+2, "separator") == 0)
	{
	    return (F_SEPARATOR);
	}
	else if (strcasecmp(yylval.string+2, "menu") == 0)
	{
	    return (F_MENU);
	}
	else if (strcasecmp(yylval.string+2, "label") == 0)
	{
	    return (F_LABEL);
	}
	else if (strcasecmp(yylval.string+2, "title") == 0)
	{
	    return (F_TITLE);
	}
	else
	{
	    FileError ("unknown f function %s\n", yylval.string+2);
	    return (STRING);
	}
    }
    else if (strcasecmp(yylval.string, "menu") == 0)
    {
	return (MENU);
    }
    else if (strcasecmp(yylval.string, "sinclude") == 0)
    {
	return (SINCLUDE);
    }
    else if (strcasecmp(yylval.string, "include") == 0)
    {
	return (INCLUDE);
    }
    else if (strcasecmp(yylval.string, "remove") == 0)
    {
	return (REMOVE);
    }
    else if (strcasecmp(yylval.string, "from") == 0)
    {
	return (FROM);
    }
    else if ((yylval.string[0] == '{' || yylval.string[0] == '}') &&
	     yylval.string[1] == '\0')
    {
	return (yylval.string[0]);
    }
    else
    {
	return (STRING);
    }
}

/* internal routine to remove quotes from string */
static char *
realUnquoteString(char *string)
{
    register char *p, *q;
    char *ret;
    Boolean quoted=FALSE;

    ret = (char *)tcMalloc(strlen(string)+1);

    p = string;
    q = ret;
    do
    {
	if (*p == '\\')
	    /* skip it */;
	else if (*p == '"')
	    quoted = !quoted;
	else
	    *q++ = *p;
    }
    while (*p++ != '\0');
    return (ret);
}

/* if the string has no quotes, just return the string itself.
 * if it is a simple string with beginning and ending quotes, Null out
 * the beginning and ending quotes and return it.
 * if it is complexly quoted, tcMalloc a new string and return it.
 */
char *
UnquoteString(char *string)
{
    /* check for embedded backslash */
    if (strchr(string, '\\'))
	return (realUnquoteString(string));
    /* check for simply quoted string */
    if (string[0] == '"' && string[strlen(string)-1] == '"')
    {
	/* remove the quotes */
	string++;
	string[strlen(string)-1] = '\0';
	if (strchr(string, '"'))
	{
	    /* it has an embeeded quote.  undo damage and dequote the string */
	    string[strlen(string)-1] = '"';
	    string--;
	    return (realUnquoteString(string));
	}
	/* no embedded quotes; return the string with quotes removed */
	return (string);
    }
    if (strchr(string, '"'))
	return (realUnquoteString(string));
    /* unquoted string, return it */
    return (string);
}

	       
	
