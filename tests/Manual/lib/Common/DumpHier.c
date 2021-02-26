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
static char rcsid[] = "$XConsortium: DumpHier.c /main/9 1995/07/14 11:58:44 drk $"
#endif
#endif

#include "testlib.h"
#include <X11/IntrinsicP.h>

void DumpHierarchy(Widget w, FILE *file, int space);

/*************************************************************************
*									 *
*	Name:		CommonDumpHierarchy()				 *
*									 *
*	Function:	This function will take a widget, and a FILE   	 *
*			pointer to indicate where to write the output.	 *
*			The function will print out all widgets names    *
*			underneath that widget.			 	 *
*									 *
*	Returns:	Nothing						 *
*									 *
*									 *
*************************************************************************/

void CommonDumpHierarchy(Widget w, FILE *file)

{
	DumpHierarchy(w, file, 0);
}


void DumpHierarchy(Widget w, FILE *file, int space)

{
	int		i, j;
	CompositeWidget	cw;

	for (j = 0 ; j < space ; j++)
		fprintf(file, " ");

	if (XtIsComposite(w))
	{
		cw = (CompositeWidget)w;
		fprintf(file, "%s(parent)\n",XtName((Widget)cw));
		for(i = 0; i < cw->composite.num_children; i++)
		{
			DumpHierarchy(cw->composite.children[i], file, 
				      (space + 2));
		}
	}
	else
	{
		fprintf(file, "%s(leaf)\n",XtName(w));
	}

}
