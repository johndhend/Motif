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

#ifndef X_NOT_STDC_ENV
#include <stdlib.h>			/* For malloc prototype. */
#endif
#include <string.h>			/* For prototypes. */

#include "AutoToken.h"

#define		MAX_KEY_SIZE 512
int  pos, i, count;
char *yyscaleval;
extern char     *yystringval;           /* contains all string data */
extern char     *yyinputstring;         /* contains input string data */
extern int      yydigitval;             /* count info for Key and Button */
int	find_token;	/* Return value from AutoFindToken */

%}

DigitOrLetterOrUnder		[\-\~\/A-Za-z][\-\~\/a-zA-Z0-9$_]*
KeyWord				[A-Z][a-zA-Z0-9$]+
StringData			[ \-\~\/\\,\'\.\?\<\>\*\&\!\@\#\$\%\^\(\)A-Za-z0-9$_][ \-\~\/\\,\'\.\?\<\>\*\&\!\@\#\$\%\^\(\)a-zA-Z0-9$_]*
Digit				[0-9]


%%

[ \t\f\n]			{}
^#.*$				{}

\-?\.?{Digit}*			{ 
				/* Remove decimal point from value. Reasoning
				   is that Scale does not use floating point
				   values, rather the integer representation
				   of the float. */
				yyscaleval = (char *) malloc(sizeof(char) *
						            (yyleng + 1));
				if ((pos = strcspn((char *)yytext, ".")) != yyleng) {
				   count = 0;
				   for (i = 0 ; i < yyleng; i++)
					if (i != pos)
						yyscaleval[count++] = yytext[i];
				}
				else
					strcpy(yyscaleval, (char *)yytext);
				yydigitval = (int) atoi(yyscaleval);
				if (yyscaleval)
					free(yyscaleval);
				return(DIGIT); 
				}

\"{StringData}\"		{
				yyinputstring = (char *) malloc(sizeof(char) *
						               (yyleng + 1));
				strcpy(yyinputstring, (char *) yytext);
				return(ISTRING);
				}

\<{KeyWord}\>			|
{KeyWord}			{
				find_token = AutoFindToken((char*) yytext);
				if ( find_token == -1 ) {
					yystringval = (char *) malloc(
					sizeof(char) * (yyleng + 1));
					strcpy(yystringval, (char *) yytext);
					return(STRING);
				} else {
					return(find_token);
				}
				}

{DigitOrLetterOrUnder}		{
				yystringval = (char *) malloc(sizeof(char) * 
						             (yyleng + 1));
				strcpy(yystringval, (char *) yytext);
				return(STRING);
				}
%%
