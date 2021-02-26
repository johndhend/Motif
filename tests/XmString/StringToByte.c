/* $XConsortium: StringToByte.c /main/5 1995/07/15 21:13:08 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */
#include <stdio.h>

#include <testlib.h>

void
main( int argc, char **argv )
{
	XmString	string1, string2;
	unsigned char	*byte_stream;
	unsigned int	length1, length2, length3;
        Boolean         same;

     CommonTestInit( argc, argv );

    /*
     *  Create an XmString.
     *  Convert the XmString to a byte stream and back again.
     *  Verify that the converted XmString is the same as the
     *  original.
     */
     string1 = XmStringCreateLtoR("Original", XmFONTLIST_DEFAULT_TAG ); 

     length1 = XmCvtXmStringToByteStream( string1, &byte_stream );

     string2 = XmCvtByteStreamToXmString( byte_stream ); 

     same = XmStringCompare( string1, string2 );

     printf("XmCvtXmStringToByteStream with non-Null byte stream parameter: ");
     if ( same )
        printf("passed.");
     else
        printf("failed.");

     printf("\n\n");


    /*
     *  Verify that the correct length is returned when the byte
     *  stream ( second ) parameter is passed in as Null.
     *  The function should return the length in this instance.
     */
     length2 = XmCvtXmStringToByteStream( string1, (unsigned char **)0 );

     printf("XmCvtXmStringToByteStream with Null byte stream parameter: ");
     if ( length1 == length2 )
        printf("passed.");
     else
        printf("failed.");

     printf("\n\n");

     length3 = XmStringByteStreamLength( byte_stream );  

     printf("XmStringByteStreamLength: ");
     if ( length1 == length3 )
        printf("passed.");
     else
        printf("failed.");

     printf("\n\n");

     CommonPause();

     XmStringFree( string1 );
     XmStringFree( string2 );
     XtFree( byte_stream );
     XtAppMainLoop( app_context );
}
