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
/*   $XConsortium: String.h /main/7 1995/07/13 19:53:28 drk $ */

#define	MAX_STRINGS	22
#define	MAX_TEXTS	8

XmString	string[MAX_STRINGS] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

char		*text[MAX_TEXTS] =
{
    "This is\nString1.",
    "String3 here",
    "String5\n",
    "String5",
    "Any old\ntext.",
    "This is the text",
	"This is to test PIR3933",
    "This tests\n\n\nPIR7403",
};

XmStringCharSet	charset[5] =
{
#ifndef MOTIF1_1
    (XmStringCharSet) XmFONTLIST_DEFAULT_TAG,
#else
    (XmStringCharSet) XmSTRING_DEFAULT_CHARSET,
#endif
    NULL,
    "ISOLatin1",
    "MyCharset",
    (XmStringCharSet) XmFALLBACK_CHARSET
};

char		*charsetname[5] =
{
#ifndef MOTIF1_1
	"XmFONTLIST_DEFAULT_TAG",
#else
    "XmSTRING_DEFAULT_CHARSET",
#endif
    "NULL",
    "ISOLatin1",
    "MyCharset",
    "XmFALLBACK_CHARSET"
};

char		error_string[120];

int		string_num,
		text_num,
		charset_num,
		test_num,
		errors;
