/* $XConsortium: alloc.c /main/5 1995/07/15 21:01:19 drk $ */
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


/*
 *This file contains a front end to malloc.  The function tcMalloc behaves
 *like malloc, but keeps a record.  Calling tcFreeAll will free all memory
 *allocated by tcMalloc
 */
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#define MALLOC_CHUNK 50

static void **entriesMalloced;
static int numEntriesMalloced=0;
static int numEntriesAvail=0;


void *
tcMalloc(size_t size)
{
    if (numEntriesMalloced == numEntriesAvail)
    {
	if (numEntriesAvail == 0)
	{
	    numEntriesAvail = MALLOC_CHUNK;
	    entriesMalloced = (void **) XtMalloc(MALLOC_CHUNK * sizeof(void *));
	}
	else
	{
	    numEntriesAvail += MALLOC_CHUNK;
	    entriesMalloced = (void **) XtRealloc((char *) entriesMalloced,
						  numEntriesAvail * sizeof(void *));
	}
    }
    entriesMalloced[numEntriesMalloced] = (void *)XtMalloc(size);
    return (entriesMalloced[numEntriesMalloced++]);
} 

void
tcFreeAll()
{
    while (numEntriesMalloced > 0)
	XtFree(entriesMalloced[--numEntriesMalloced]);
}
