/* $XConsortium: TestMemory.c /main/5 1995/07/15 21:00:45 drk $ */
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
 * TestMemory.c
 *
 * Module with dummy stubs to enable linking without purify
 */

#include "testlib.h"

void purify_allallocated()

/*************************************************************************
*                                                                        *
*       Name:           purify_allallocated()                            *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}


void purify_allleaks()

/*************************************************************************
*                                                                        *
*       Name:           purify_allleaks()                                *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}


void purify_newallocated()

/*************************************************************************
*                                                                        *
*       Name:           purify_newallocated()                            *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}


void purify_newleaks()

/*************************************************************************
*                                                                        *
*       Name:           purify_newleaks()                                *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}


void purify_clear_newallocated()

/*************************************************************************
*                                                                        *
*       Name:           purify_clear_newallocated()                      *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}


void purify_clear_newleaks()

/*************************************************************************
*                                                                        *
*       Name:           purify_clear_newleaks()                          *
*								 	                                     *
*	Purpose:	This routine is a stub which enables the test            *
*                       programs to be linked without the purify         *
*                       library.                                         *
*									                                     *
*	Return:		Nothing						                             *
*									                                     *
*************************************************************************/
{
  /*  do nothing, just return */
  return;
}
