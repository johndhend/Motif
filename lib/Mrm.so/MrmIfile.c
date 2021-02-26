
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: MrmIfile.c /main/13 1996/11/13 13:56:30 drk $"
#endif
#endif

/* (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */



/*
 *++
 *  FACILITY:
 *
 *      UIL Resource Manager (URM)
 *
 *  ABSTRACT:
 *
 *	This module contains the low-level file utilities
 *
 *--
 */


/*
 *
 *  INCLUDE FILES
 *
 */

#include <Mrm/MrmAppl.h>
#include <Mrm/Mrm.h>
#include <Mrm/IDB.h>

#include <stdio.h>		/* Standard IO definitions		*/
#include <errno.h>
#include <fcntl.h>

#ifndef X_NOT_STDC_ENV
#include <unistd.h>
#endif


/*
 *
 *  DEFINE and MACRO DEFINITIONS
 *
 */

#define	PMODE	0666	/* Default protection mode before umask		*/
#define FAILURE	-1	/* creat/stat returns this			*/

/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine will take the file name specified and
 *	open or create it depending on the access parameter.
 *	An attempt is made to save any existing file of the
 *	same name.
 *
 *
 *  FORMAL PARAMETERS:
 *
 * 	name		the system-dependent file spec of the IDB file
 *			to be opened.
 *	accss		access type desired, read or write access.
 *	os_ext		an operating specific structure to take advantage
 *			of file system features (if any).
 *	file_id		IDB file id used in all calls to low level routines.
 *	returned_fname	The resultant file name.
 *
 *  IMPLICIT INPUTS:
 *
 *      NONE
 *
 *  IMPLICIT OUTPUTS:
 *
 *      NONE
 *
 *  FUNCTION VALUE:
 *
 *	Returns an integer:
 *
 *	MrmSUCCESS	- When access is read and open works
 *	MrmCREATE_NEW	- When access is write and open works
 *	MrmNOT_FOUND	- When access is read and the file isn't present
 *	MrmFAILURE	- When the open fails for any other reason
 *
 *  SIDE EFFECTS:
 *
 *      Opens or creates the named file and assigns a channel to it.
 *
 *--
 */

Cardinal 
Idb__FU_OpenFile (char 			*name,
		  MrmCode 		access,
		  MrmOsOpenParamPtr 	os_ext,
		  IDBLowLevelFilePtr 	*file_id,
		  char 			*returned_fname)
{

  /*
   * Local variables
   */
  int		file_desc;		/* 'unix' file descriptor */
  int		length;			/* the length of the above string */
  IDBLowLevelFile *a_file;		/* pointer to the file_id */

  /* Fill in the result name with the name specified so far */
  length = strlen (name);
  strcpy (returned_fname, name);
  returned_fname[length] = 0;

  /* Check if this file is to be opened for read or write access */
  if (access == URMWriteAccess)
    {
      file_desc = open (name, O_RDWR, PMODE);
      if (file_desc != FAILURE)		/* filename already exists. */
	{
	  if (os_ext == 0)
	    return MrmFAILURE;
	  else if (!os_ext->nam_flg.clobber_flg)
	    return MrmEXISTS;		/* no clobber. return Exists */
	  else if (os_ext->version != MrmOsOpenParamVersion)
	    return MrmFAILURE;
	  (void) close (file_desc);	/* we care not what close returns*/
	}

      file_desc = creat (name,PMODE);
      if (file_desc == FAILURE)		/* verify that worked */
	return MrmFAILURE;

      close (file_desc);		/* we care not what close returns */
      file_desc = open (name, O_RDWR, PMODE);

      if (file_desc == FAILURE)		/* verify that worked */
	return MrmFAILURE;
    }


  /* Else this file is to opened for read access */
  else if (access == URMReadAccess)
    {
      file_desc = open (name, O_RDONLY, PMODE);

      /* verify that worked */
      if (file_desc == FAILURE)
	{
	  if ( errno == EACCES )
	    return MrmFAILURE;
	  else
	    return MrmNOT_FOUND;
	}
    }

  /* Not URMReadAccess or URMWriteAccess, so return invalid access type	    */
  else
    return MrmFAILURE;


  /*
   * now all we have to do is set up the IDBFile and return the
   * proper success code.
   */

  *file_id = (IDBLowLevelFilePtr)
    XtMalloc(sizeof (IDBLowLevelFile));
  if (*file_id==0)
    return MrmFAILURE;

  a_file = (IDBLowLevelFile *) *file_id;

  a_file->name = XtMalloc (length+1);
  if (a_file->name==0)
    {
      XtFree ((char*)*file_id);
      return (MrmFAILURE);
    }

  a_file->file_desc = file_desc;
  strcpy (a_file->name, name);
  a_file->name[length] = 0;

  if (access == URMWriteAccess)
    return (MrmCREATE_NEW);
  else
    return (MrmSUCCESS);

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine will close the file and free any allocated storage
 *
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		IDB file id
 *	delete		delete the file if == true
 *
 *  IMPLICIT INPUTS:
 *
 *      the file name and channel from the IDBFile record
 *
 *  IMPLICIT OUTPUTS:
 *
 *      NONE
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	- When the file is closed [and deleted] successfully
 *	MrmFAILURE	- When the close fails
 *
 *  SIDE EFFECTS:
 *
 *      Closes the file, deassigns the channel and possible deletes the file.
 *
 *--
 */

Cardinal 
Idb__FU_CloseFile (IDBLowLevelFile	*file_id ,
		   int			delete)
{
  /*
   * Local variables
   */

  int	status;				/* ret status for sys services	*/

  status = close (file_id->file_desc);
  if (status != 0)
    return MrmFAILURE;

  if (delete) {
    status = unlink (file_id->name);
  }

  XtFree (file_id->name);
  XtFree ((char*)file_id);
  return MrmSUCCESS;

}

/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This function reads in the desired record into the given
 *	buffer.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		the IDB file identifier
 *	block_num	the record number to retrieve
 *	buffer		pointer to the buffer to fill in
 *
 *  IMPLICIT INPUTS:
 *
 *      NONE
 *
 *  IMPLICIT OUTPUTS:
 *
 *      NONE
 *
 *  FUNCTION VALUE:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmNOT_FOUND	entry not found
 *	MrmFAILURE	operation failed, no further reason
 *
 *  SIDE EFFECTS:
 *
 *      The buffer is filled in.  Should the $READ fail the buffer's
 *	content is not predictable.
 *
 *--
 */

Cardinal 
Idb__FU_GetBlock (IDBLowLevelFile	*file_id,
		  IDBRecordNumber	block_num,
		  char			*buffer)
{
  /*
   * Local variables
   */
  int	number_read;		/* the number of bytes actually read	*/
  int	fdesc ;			/* file descriptor from lowlevel desc */


  fdesc = file_id->file_desc ;
  lseek (fdesc, (block_num-1)*IDBRecordSize, 0);
  number_read = read (file_id->file_desc, buffer, IDBRecordSize);

  if (number_read != IDBRecordSize) 
    return MrmFAILURE;
  else
    return MrmSUCCESS;
}


/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This function writes the data in the givin buffer into
 *	the desired record in the file.
 *
 *  FORMAL PARAMETERS:
 *
 *	file_id		the IDB file identifier
 *	block_num	the record number to write
 *	buffer		pointer to the buffer to read from
 *
 *  IMPLICIT INPUTS:
 *
 *      NONE
 *
 *  IMPLICIT OUTPUTS:
 *
 *      NONE
 *
 *  FUNCTION VALUE:
 *
 *	Returns an integer by value:
 *
 *	MrmSUCCESS	operation succeeded
 *	MrmFAILURE	operation failed, no further reason
 *
 *  SIDE EFFECTS:
 *
 *	the file is modified.
 *
 *--
 */

Cardinal 
Idb__FU_PutBlock (IDBLowLevelFile	*file_id,
		  IDBRecordNumber	block_num,
		  char			*buffer)
{
  /*
   * Local variables
   */
  int	number_written;		/* the # of bytes acctually written	*/
  int	fdesc ;			/* file descriptor from lowlevel desc */


  fdesc = file_id->file_desc ;
  lseek (fdesc, (block_num-1)*IDBRecordSize, 0);
  number_written = write (file_id->file_desc, buffer, IDBRecordSize);

  if (number_written != IDBRecordSize)
    return MrmFAILURE;
  else
    return MrmSUCCESS;
}

