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
static char rcsid[] = "$XConsortium: app.c /main/6 1995/07/14 09:43:21 drk $"
#endif
#endif

/************************************************************
 *     app.c -- toolkit-independent code
 *
 *  Contains code to read, write, copy, move & remove files
 *     
 ************************************************************/

#include <limits.h>
#include <stdio.h>

#include <Xm/Xm.h>				  /* for _NO_PROTO */
#include "basic.h"
#include "file.h"

  /* curfile is the file currently open
     newfile is a newly named file */

static FILE *curfile;
static FILE *newfile;

static char curname[256];
static char newname[256];

  /* open_to_read and open_to_write indicate whether
       curfile is open for reading or writing
     open_to_transfer indicates whether newfile
       is open for writing */

static int open_to_read = false;
static int open_to_write = false;
static int open_to_transfer = false;

/*===========================================================
      Public transfer operations, guarded by state flags
============================================================*/

/************************************************************
 * Read File
 ************************************************************/

char *AppReadFile()
{
    if (! open_to_read) return NULL;
    return FileGetText( curfile );
}

/************************************************************
 * Save File
 ************************************************************/

void
  AppSaveFile(char *textchars, size_t numchars)
{
    if (! open_to_write ) return;
    FileSaveText( curfile, textchars, numchars );
}

/************************************************************
 * Transfer File
 ************************************************************/

void 
AppTransferFile(char *textchars, size_t numchars)
{
    if (! open_to_transfer ) return;
    FileSaveText( newfile, textchars, numchars );
}

/************************************************************
 * New file
 ************************************************************/

void AppNewFile()
{
    if ( open_to_read || open_to_write )
    {
        fclose( curfile );
	open_to_read = false;
	open_to_write = false;
    };
}

/************************************************************
 * Remove File
 ************************************************************/

AppRemoveFile()
{
    if ( ! (open_to_read || open_to_write) ) return false;
    AppNewFile();
    return ( FileRemove(curname) == 0 );
}

/************************************************************
 * Get Buffer Name of Current File
 ************************************************************/

char *AppBufferName()
{
    if ( open_to_read || open_to_write )
        return FileTrailingPart( curname );
    else
        return NULL;
}

/*===========================================================
           Initiate and Complete various operations
============================================================*/

/************************************************************
 * Open file for reading
 ************************************************************/


AppOpenReadFile(char *filnam)
{
    if ( (newfile = fopen(filnam,"r")) != NULL )
    {
        AppNewFile();
        strcpy( curname, filnam );
        curfile = newfile;
        open_to_read = true;
        return ( true );
    }
    else
        return ( false );
}

/************************************************************
 * Reopen current file for saving
 ************************************************************/

AppOpenSaveFile()
{
    if ( open_to_write ) return true;
    if (! open_to_read ) return false;
    if ((open_to_write = ((newfile = fopen(curname,"w+")) != NULL)))
    {
        fclose( curfile );
	curfile = newfile;
        return( true );
    }
    else
        return ( false );
}

/************************************************************
 * Open new file for transfer
 ************************************************************/


AppOpenTransferFile(char *filnam)
{
    strcpy( newname, filnam );
    return ( open_to_transfer =
             ( (newfile = fopen(newname,"w+")) != NULL ) );
}

/************************************************************
 * Complete Save As operation
 ************************************************************/

void AppCompleteSaveAsFile()
{
    AppNewFile();
    open_to_transfer = false;
    open_to_write = true;
    curfile = newfile;
    strcpy( curname, newname );
}

/************************************************************
 * Complete Move operation
 ************************************************************/

AppCompleteMoveFile()
{
    int retval;
    if ( ! open_to_transfer ) return false;
    retval = AppRemoveFile();
    open_to_transfer = false;
    open_to_write = true;
    curfile = newfile;
    strcpy( curname, newname );
    return retval;
}

/************************************************************
 * Complete Copy operation
 ************************************************************/

void AppCompleteCopyFile()
{
    open_to_transfer = false;
    fclose( newfile );
}
