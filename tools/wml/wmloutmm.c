
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
static char rcsid[] = "$XConsortium: wmloutmm.c /main/9 1995/08/29 11:10:59 drk $"
#endif
#endif



/*
*  (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */

/*
 * This module contains routines responsible for writing the .mm files
 * produced by WML. All files are written into the current directory.
 *
 * Input:
 *	The resolved objects
 *
 * Output:
 *	wml-uil.mm
 *
 */


#include "wml.h"

#if defined(__STDC__)
#include <string.h>
#endif
#include <stdio.h>


/*
 * Routines used only in this module
 */
void wmlOutputWmlUilMm ();
void wmlOutputWmlUilMmClass ();

/*
 * globals
 */
int			tabno = 1;	/* table number */

/*
 * lists re-used repeatedly to order lists for printing
 */
DynamicHandleListDef	mm_arg;
DynamicHandleListDefPtr	mm_arg_ptr = &mm_arg;
DynamicHandleListDef	mm_rsn;
DynamicHandleListDefPtr	mm_rsn_ptr = &mm_rsn;
DynamicHandleListDef	mm_ctl;
DynamicHandleListDefPtr	mm_ctl_ptr = &mm_ctl;



/*
 * Output control routine, which simply outputs each .mm file in turn.
 */

void wmlOutputMmFiles ()

{

wmlOutputWmlUilMm ();

}



/*
 * Routine to write out wml-uil.mm
 *
 * This .mm file contains the tables which are to be included as an
 * appendix to the Uil manual. The tables give the arguments with their
 * default values, reasons, constraints, and controls for each class
 * in the class vectors.
 */

void wmlOutputWmlUilMm ()

{

FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlClassDefPtr		clsobj;		/* class object */



/*
 * Open the output file. Write the canned header stuff
 */
outfil = fopen ("wml-uil.mm", "w");
if ( outfil == NULL )
    {
    printf ("\nCouldn't open wml-uil.mm");
    return;
    }

/*
 * Initialize order lists for the tables.
 */
wmlInitHList (mm_arg_ptr, 200, TRUE);
wmlInitHList (mm_rsn_ptr, 200, TRUE);
wmlInitHList (mm_ctl_ptr, 200, TRUE);

/*
 * Write out a table for each class, for both widget and gadget variants
 */
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    wmlOutputWmlUilMmClass (outfil, clsobj, clsobj->syndef->name);
    }

/*
 * close the output file
 */
printf ("\nCreated wml-uil.mm");
fclose (outfil);

}



/*
 * Routine to write a table for a class entry
 */

void wmlOutputWmlUilMmClass (outfil, clsobj, name)
    FILE			*outfil;
    WmlClassDefPtr		clsobj;
    char			*name;

{

char		*canned1 =
".bp\n\
.ps 12\n";

char		*canned2 =
".ps 10\n\
.vs 12\n\
.LP\n\
.TS H\n\
tab(@);\n\
lB lB\n\
l l.\n\
_\n\
.sp 6p\n\
Controls@Reasons\n\
.sp 6p\n\
_\n\
.sp 6p\n\
.TH\n";

char		*canned3 =
".TE\n\
.TS H\n\
tab(@);\n\
lB lB lB\n\
l l l.\n\
_\n\
.sp 6p\n\
UIL Argument Name@Argument Type@Default Value\n\
.sp 6p\n\
_\n\
.sp 6p\n\
.TH\n";

char		*canned4 =
".TE\n";

WmlClassResDefPtr	argref;		/* current argument reference */
WmlClassResDefPtr	rsnref;		/* current reason reference */
WmlClassCtrlDefPtr	ctlref;		/* current controls reference */
int			argndx;		/* to access ordered vector */
int			rsnndx;		/* to access ordered vector */
int			ctlndx;		/* to access ordered vector */


/*
 * Write out header information
 */
fprintf (outfil, canned1);
fprintf (outfil, "%s\n", name);
fprintf (outfil, canned2);

/*
 * Alphabetize the controls, reason, and argument lists
 */
wmlClearHList (mm_arg_ptr);
wmlClearHList (mm_rsn_ptr);
wmlClearHList (mm_ctl_ptr);

argref = clsobj->arguments;
while ( argref!= NULL )
    {
    while ( argref != NULL && argref->exclude == WmlAttributeTrue )
	argref = argref->next;
    if ( argref != NULL )
	{
	wmlInsertInHList (mm_arg_ptr,
			  argref->act_resource->syndef->name,
			  (ObjectPtr)argref);
	argref = argref->next;
	}
    }

rsnref = clsobj->reasons;
while ( rsnref!=NULL )
    {
    while ( rsnref != NULL && rsnref->exclude == WmlAttributeTrue )
	rsnref = rsnref->next;
    if ( rsnref != NULL )
	{
	wmlInsertInHList (mm_rsn_ptr,
			  rsnref->act_resource->syndef->name,
			  (ObjectPtr)rsnref);
	
	rsnref = rsnref->next;
	}
    }

ctlref = clsobj->controls;
while ( ctlref != NULL )
    {
    wmlInsertInHList (mm_ctl_ptr,
		      ctlref->ctrl->syndef->name,
		      (ObjectPtr)ctlref);
    ctlref = ctlref->next;
    }

/*
 * Write out the controls and reason table.
 */
rsnndx = 0;
ctlndx = 0;
if ( mm_ctl_ptr->cnt == 0 )
    fprintf (outfil, "No children are supported");
while ( rsnndx<mm_rsn_ptr->cnt || ctlndx<mm_ctl_ptr->cnt )
    {
    if ( ctlndx < mm_ctl_ptr->cnt )
	{
	ctlref = (WmlClassCtrlDefPtr) mm_ctl_ptr->hvec[ctlndx].objptr;
	fprintf (outfil, "%s@",
		 ctlref->ctrl->syndef->name);
	ctlndx += 1;
	}
    else
	fprintf (outfil, "@");
    
    if ( rsnndx < mm_rsn_ptr->cnt )
	{
	rsnref = (WmlClassResDefPtr) mm_rsn_ptr->hvec[rsnndx].objptr;
	fprintf (outfil, "%s\n",
		 rsnref->act_resource->syndef->name);
	rsnndx += 1;
	}
    else
	fprintf (outfil, "\n");
    }
fprintf (outfil, canned3);

/*
 * Write out the argument table
 */
argndx = 0;
while ( argndx < mm_arg_ptr->cnt )
    {
    argref = (WmlClassResDefPtr) mm_arg_ptr->hvec[argndx].objptr;
    fprintf (outfil, "%s@%s@",
	     argref->act_resource->syndef->name,
	     argref->act_resource->dtype_def->syndef->name);
    if ( argref->dflt != NULL )
	{
	if ( strchr(argref->dflt,' ') != 0 )
	    fprintf (outfil, "T{\n%s\nT}\n",
		     argref->dflt);
	else
	    fprintf (outfil, "%s\n",
		     argref->dflt);
	}
    else
	{
	if (argref->act_resource->syndef->dflt != NULL) {
	    if ( strchr(argref->act_resource->syndef->dflt,' ') != 0 )
		fprintf (outfil, "T{\n%s\nT}\n",
			 argref->act_resource->syndef->dflt);
	    else
		fprintf (outfil, "%s\n",
			 argref->act_resource->syndef->dflt);
	}
	else
	    fprintf (outfil, "  \n");
    }    
    argndx += 1;
    }
fprintf (outfil, canned4);

}



