
#include <localdef.h>

/* $TOG: Trait.c /main/9 1997/07/07 11:36:10 cshi $ */
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
/* #define DEBUG */



#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/IntrinsicP.h>
#include <Xm/XmP.h>
#include <Xm/VendorSP.h>
#include <Xm/TraitP.h>
#include "HashI.h"
#include "TraitI.h"
#include "XmI.h"

/*
 * Internal data structures
 */

static XmHashTable TraitTable;

typedef struct _XmTraitEntry {
  XtPointer obj;
  XrmQuark  name;
} XmTraitEntryRec, *XmTraitEntry;

/*
 * Static functions
 */

static Boolean TraitCompare(XmHashKey, XmHashKey);
static XmHashValue TraitHash(XmHashKey);

/*
 * List all quarks here
 */

externaldef(traits) XrmQuark XmQTmotifTrait = NULLQUARK;
externaldef(traits) XrmQuark XmQTmenuSystem = NULLQUARK;
externaldef(traits) XrmQuark XmQTtransfer = NULLQUARK;
externaldef(traits) XrmQuark XmQTaccessTextual = NULLQUARK;
externaldef(traits) XrmQuark XmQTmenuSavvy = NULLQUARK;
externaldef(traits) XrmQuark XmQTnavigator = NULLQUARK;
externaldef(traits) XrmQuark XmQTscrollFrame = NULLQUARK;
externaldef(traits) XrmQuark XmQTactivatable = NULLQUARK;
externaldef(traits) XrmQuark XmQTdialogShellSavvy = NULLQUARK;
externaldef(traits) XrmQuark XmQTjoinSide = NULLQUARK;
externaldef(traits) XrmQuark XmQTcareParentVisual = NULLQUARK;
externaldef(traits) XrmQuark XmQTspecifyRenderTable = NULLQUARK;
externaldef(traits) XrmQuark XmQTtakesDefault = NULLQUARK;
externaldef(traits) XrmQuark XmQTcontainerItem = NULLQUARK;
externaldef(traits) XrmQuark XmQTcontainer = NULLQUARK;
externaldef(traits) XrmQuark XmQTspecifyLayoutDirection = NULLQUARK;
externaldef(traits) XrmQuark XmQTaccessColors = NULLQUARK;
externaldef(traits) XrmQuark XmQTspecifyUnitType = NULLQUARK;
externaldef(traits) XrmQuark XmQTtraversalControl = NULLQUARK;
externaldef(traits) XrmQuark XmQTspecifyUnhighlight = NULLQUARK;
externaldef(traits) XrmQuark XmQTpointIn = NULLQUARK;
externaldef(traits) XrmQuark _XmQTclipWindow = NULLQUARK;

/* 
 * Initialize traits system
 * 
 * This routine sets up all quarks used by the traits in 
 * Motif
 */

void _XmInitializeTraits()
{
  /* avoid initializing more than once */
  if(TraitTable != NULL) return;

  /* Create Hash Table */
  TraitTable = _XmAllocHashTable(200, TraitCompare, TraitHash);

  XmQTmotifTrait = XrmPermStringToQuark("XmQTmotifTrait");

  /* Menu system manipulation and status */
  XmQTmenuSystem = XrmPermStringToQuark("XmTmenuSystem");
  XmQTmenuSavvy = XrmPermStringToQuark("XmTmenuSavvy");

  /* Transfer Trait */
  XmQTtransfer = XrmPermStringToQuark("XmTtransfer");

  /* String get/set */
  XmQTaccessTextual = XrmPermStringToQuark("XmTaccessTextual");
  
  /* Navigator/Scrolling trait */
  XmQTnavigator = XrmPermStringToQuark("XmTnavigator");
  XmQTscrollFrame = XrmPermStringToQuark("XmTscrollFrame");
  _XmQTclipWindow= XrmPermStringToQuark("_XmTclipWindow");

  /* Activatable trait */
  XmQTactivatable = XrmPermStringToQuark("XmTactivatable");

  /* JoinSide trait */
  XmQTjoinSide = XrmPermStringToQuark("XmTjoinSide");

  /* DialogShellSavvy trait */
  XmQTdialogShellSavvy = XrmPermStringToQuark("XmTdialogShellSavvy");

  /* Care about Parent Visual trait */
  XmQTcareParentVisual = XrmPermStringToQuark("XmTcareParentVisual");

  /* SpecifyRenderTable trait */
  XmQTspecifyRenderTable = XrmPermStringToQuark("XmTspecifyRenderTable");

  /* TakesDefault trait */
  XmQTtakesDefault = XrmPermStringToQuark("XmTtakesDefault");

  /* Container/Item trait */
  XmQTcontainerItem = XrmPermStringToQuark("XmTcontainerItem");
  XmQTcontainer = XrmPermStringToQuark("XmTcontainer");

  /* LayoutDirection trait */
  XmQTspecifyLayoutDirection = 
    XrmPermStringToQuark("XmTspecifyLayoutDirection");

  /* get colors */
  XmQTaccessColors = XrmPermStringToQuark("XmTaccessColors");

  /* Unit type */
  XmQTspecifyUnitType = XrmPermStringToQuark("XmTspecifyUnitType");

  /* Traversal control. */
  XmQTtraversalControl = XrmPermStringToQuark("XmTtraversalControl");

  /* Specify UnHighlight GC trait */
  XmQTspecifyUnhighlight = XrmPermStringToQuark("XmTspecifyUnhighlight");

  /* PointIn trait */
  XmQTpointIn = XrmPermStringToQuark("XmTpointIn");
}

XtPointer
XmeTraitGet(XtPointer obj, XrmQuark name) 
{
  XtPointer trait;
  XmTraitEntryRec entry;

  entry.obj = obj;
  entry.name = name;

  _XmProcessLock();
  trait = _XmGetHashEntry(TraitTable, &entry);
  _XmProcessUnlock();

  return(trait);
}

Boolean
XmeTraitSet(XtPointer object, XrmQuark name, XtPointer data)
{
  XmTraitEntry entry;

  /* Create key,  this will be freed if the record is removed */
  entry = (XmTraitEntry) XtMalloc(sizeof(XmTraitEntryRec));
  entry -> obj = object;
  entry -> name = name;

  _XmProcessLock();
  if (data != NULL) {
    _XmAddHashEntry(TraitTable, entry, data);
  }
  else { /* if data == NULL then remove the context */
    XtPointer key;
    key = _XmRemoveHashEntry(TraitTable, entry);
    XtFree((char*) entry);
    XtFree((char*) key);
  }
  _XmProcessUnlock();

  return True;
}

static Boolean
TraitCompare(XmHashKey key1, XmHashKey key2)
{
  XmTraitEntry entry1, entry2;

  entry1 = (XmTraitEntry) key1;
  entry2 = (XmTraitEntry) key2;

  return(entry1 -> obj == entry2 -> obj &&
	 entry1 -> name == entry2 -> name);
}

static XmHashValue 
TraitHash(XmHashKey key)
{
  XmTraitEntry entry = (XmTraitEntry) key;

  return(((long) entry -> obj) + ((long) entry -> name));
}
