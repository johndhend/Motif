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
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: file.c /main/7 1996/10/29 14:29:18 drk $"
#endif
#endif

/************************************************************
 *     file.c -- Code for dealing with files and filenames
 *
 *  Contains code to read, write, copy, move & remove files
 *     
 ************************************************************/

#include <limits.h>
#include <stdio.h>

#include <Xm/Xm.h>				  /* for _NO_PROTO */

#include "basic.h"

/************************************************************
 * Remove File
 ************************************************************/


FileRemove(char *filnam)
{
    return -1;
}

/************************************************************
 * Save Text to File
 ************************************************************/

void 
FileSaveText(FILE *fil, char *textchars, size_t numchars)
{
  size_t wrote;
  
    rewind(fil);
  wrote = fwrite(textchars, 1, numchars, fil);
    fflush(fil);
}

/************************************************************
 * Read Text from File
 ************************************************************/

char *
FileGetText(FILE *fil)
{
    char *textchars;
    int position = 0;
    int num;

    textchars = BasicMalloc( BUFSIZ );
    rewind( fil );
    while ( (num = read( fileno(fil),
                         textchars+position, BUFSIZ)) > 0 ) {
      position += num;
      textchars = BasicRealloc( textchars, position+BUFSIZ );
    }
    *( textchars+position ) = 0;
    return textchars;
}

/************************************************************
 * Return Trailing part of current filename
 ************************************************************/

char *
FileTrailingPart(char *filnam)
{
    char *trailnam;
    while (*filnam != '\0') filnam++;
    while (*filnam != '/') filnam--;
    filnam++;
    strdup( trailnam, filnam );
    return trailnam;
}

/************************************************************
 * Save txt in temporary file
 ************************************************************/

char *
FileSaveTemp(char *txt)
{
  FILE *temp;
  static char tmp_nam[L_tmpnam + 1];

  (void) tmpnam(tmp_nam);
  
  temp = fopen(tmp_nam, "w");
  fprintf(temp, "%s", txt);
  fclose(temp);
  return(tmp_nam);
}

