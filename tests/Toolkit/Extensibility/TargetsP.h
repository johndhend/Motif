/* $XConsortium: TargetsP.h /main/4 1995/07/15 21:04:08 drk $ */
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

/*******************************************************************************
 *
 * TargetsP.h: The widget private header file for the ExmTargets
 *                 uniform transfer model demonstration widget.
 *
 ******************************************************************************/

/* Ensure that the file be included only once. */
#ifndef _ExmTargetsP_h
#define _ExmTargetsP_h

/* Allow for C++ compilation. */
#ifdef __cplusplus
extern "C" {
#endif


/* Include appropriate files. */
#include "Targets.h" /* public header file for the ExmTargets widget */

/* #include <Exm/StringP.h> renamed ? */
/* private header file for the ExmString widget */
#include <Exm/StringTransP.h>

/* Data structure to hold data transfer snapshots */
typedef struct _ExmTargetsSnapshotStruct
{
  Atom                                      distinguisher;
  XmString                                  value;
  struct _ExmTargetsSnapshotStruct   *prev;
  struct _ExmTargetsSnapshotStruct   *next;
} ExmTargetsSnapshotStruct;

/* No new inheritable methods. */

/* Define the widget class part. */
typedef struct _ExmTargetsClassPart
{
	XtPointer		extension;
} ExmTargetsClassPart;


/* Define the full class record. */
typedef struct _ExmTargetsClassRec
{
	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	ExmSimpleClassPart	simple_class;
	ExmStringClassPart	string_class;
	ExmTargetsClassPart	targets_class;
} ExmTargetsClassRec;


/* Make the full class record externally accessible. */
externalref ExmTargetsClassRec exmTargetsClassRec;

/* Define the widget instance part. */
typedef struct _ExmTargetsPart
{
  /* Fields and resources for ExmTargets */
        int                                    snap_counter;
        ExmTargetsSnapshotStruct        *snapshots;
	XtCallbackList		               destination_callback;

  /* private state variables for selections */
	int			select_start_x;
	int			select_start_y;
	int                     select_end_x;
	int                     select_end_y;
	int			selected_item_count;
	Boolean			have_clip;
	Boolean			have_primary;
	Boolean			have_secondary;
} ExmTargetsPart;

/* Define the full instance record. */
typedef struct _ExmTargetsRec
{
	CorePart		core;
	XmPrimitivePart		primitive;
	ExmSimplePart		simple;
	ExmStringPart		string;
	ExmTargetsPart	targets;
} ExmTargetsRec;

/* Allow for C++ compilation. */
#ifdef __cplusplus
} /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

/* Ensure that the file be included only once. */
#endif /* _ExmTargetsP_h */
