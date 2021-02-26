
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
static char rcsid[] = "$XConsortium: ExtObject.c /main/13 1995/10/25 20:03:50 cde-sun $"
#endif
#endif
/* (c) Copyright 1989, 1990  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/* (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/* (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/* (c) Copyright 1988 MICROSOFT CORPORATION */



#include <string.h>
#include "BaseClassI.h"
#include "ExtObjectI.h"
#include "SyntheticI.h"
#include "XmI.h"


/********    Static Function Declarations    ********/

static void ClassInitialize(void);
static void ClassPartInitPrehook(WidgetClass c);
static void ClassPartInitPosthook(WidgetClass c);
static void ClassPartInitialize(WidgetClass c);
static void InitializePrehook(Widget req, Widget new_w,
			      ArgList args, Cardinal *num_args);
static void Initialize(Widget req, Widget new_w, 
		       ArgList args, Cardinal *num_args);
static Boolean SetValuesPrehook(Widget req, Widget curr, Widget new_w,
				ArgList args, Cardinal *num_args);
static void GetValuesPrehook(Widget new_w, ArgList args, Cardinal *num_args);
static Boolean SetValues(Widget old, Widget ref, Widget new_w,
			 ArgList args, Cardinal *num_args);
static void GetValuesHook(Widget new_w, ArgList args, Cardinal *num_args);
static void Destroy(Widget wid);
static void UseParent(Widget w, int offset, XrmValue *value);

/********    End Static Function Declarations    ********/

/***************************************************************************
 *
 * ExtObject Resources
 *
 ***************************************************************************/


#define Offset(field)	XtOffsetOf(struct _XmExtRec, ext.field)

static XtResource extResources[] =
{
  {
    XmNlogicalParent, XmCLogicalParent, XmRWidget, 
    sizeof (Widget), Offset (logicalParent),
    XmRCallProc, (XtPointer)UseParent
  },
  {
    XmNextensionType, XmCExtensionType, XmRExtensionType, 
    sizeof (unsigned char), Offset (extensionType),
    XmRImmediate, (XtPointer)XmDEFAULT_EXTENSION
  }
};
#undef Offset

#define XmNUM_ELEMENTS	4
#define XmNUM_BYTES	255

typedef struct _XmExtCache {
  char    data[XmNUM_BYTES];
  Boolean inuse;
} XmExtCache;

typedef union {
  XmExtCache	cache;
  double	force_alignment;
} Aligned_XmExtCache;

static Aligned_XmExtCache extarray[XmNUM_ELEMENTS];


static XmBaseClassExtRec myBaseClassExtRec = {
  NULL,				/* Next extension         */
  NULLQUARK,			/* record type XmQmotif   */
  XmBaseClassExtVersion,	/* version                */
  sizeof(XmBaseClassExtRec),	/* size                   */
  InitializePrehook,		/* initialize prehook     */
  SetValuesPrehook,		/* set_values prehook     */
  NULL,				/* initialize posthook    */
  NULL,				/* set_values posthook    */
  NULL,				/* secondary class        */
  NULL,				/* creation proc          */
  NULL,				/* getSecRes data         */
  { 0 },			/* fast subclass          */
  GetValuesPrehook,		/* get_values prehook     */
  NULL,				/* get_values posthook    */
  ClassPartInitPrehook,		/* class_part_prehook     */
  ClassPartInitPosthook,	/* class_part_posthook    */
  NULL,				/* compiled_ext_resources */   
  NULL,				/* ext_resources       	  */   
  0,				/* resource_count     	  */   
  FALSE				/* use_sub_resources	  */
};

externaldef(xmextclassrec)
XmExtClassRec xmExtClassRec = {
  {	
    (WidgetClass) &objectClassRec,/* superclass 	 */   
    "dynamic",			  /* class_name 	 */   
    sizeof(XmExtRec),	 	  /* size 		 */   
    ClassInitialize, 		  /* Class Initializer 	 */   
    ClassPartInitialize,	  /* class_part_init 	 */ 
    FALSE,			  /* Class init'ed ? 	 */   
    Initialize,			  /* initialize          */   
    NULL,			  /* initialize_notify   */ 
    NULL,			  /* realize             */   
    NULL,			  /* actions             */   
    0,				  /* num_actions         */   
    extResources,		  /* resources           */   
    XtNumber(extResources),	  /* resource_count      */   
    NULLQUARK, 			  /* xrm_class           */   
    FALSE,			  /* compress_motion     */   
    FALSE,			  /* compress_exposure   */   
    FALSE,			  /* compress_enterleave */   
    FALSE,			  /* visible_interest    */   
    Destroy,			  /* destroy             */   
    NULL,			  /* resize              */   
    NULL,			  /* expose              */   
    SetValues,	 		  /* set_values          */   
    NULL,			  /* set_values_hook     */ 
    NULL,			  /* set_values_almost   */ 
    GetValuesHook,		  /* get_values_hook     */ 
    NULL,			  /* accept_focus        */   
    XtVersion, 			  /* intrinsics version  */   
    NULL,			  /* callback offsets    */   
    NULL,			  /* tm_table            */   
    NULL,			  /* query_geometry      */ 
    NULL,			  /* display_accelerator */ 
    (XtPointer)&myBaseClassExtRec /* extension           */ 
  },	
  {
    NULL,			  /* synthetic resources */
    0				  /* num syn resources	 */
  }
};

externaldef(xmextobjectclass) 
WidgetClass xmExtObjectClass = (WidgetClass) (&xmExtClassRec);

/*ARGSUSED*/
static void 
UseParent(Widget w,
	  int offset,		/* unused */
	  XrmValue *value)
{
  value->addr = (XPointer) &(w->core.parent);
}

/************************************************************************
 *
 *  ClassInitialize
 *
 ************************************************************************/

static void 
ClassInitialize(void)
{
  myBaseClassExtRec.record_type = XmQmotif;
}

/************************************************************************
 *
 *  ClassPartInitPrehook
 *
 ************************************************************************/

static void 
ClassPartInitPrehook(WidgetClass c)
{
  XmExtObjectClass wc = (XmExtObjectClass) c;
  
  if ((WidgetClass)wc != xmExtObjectClass)
    {
      XmExtObjectClass sc = (XmExtObjectClass) c->core_class.superclass;
      XmBaseClassExt *scePtr = _XmGetBaseClassExtPtr(sc, XmQmotif);

      /*
       * If our superclass uses subresources, then we need to
       * temporarily fill it's core resource fields so that objectClass
       * classPartInit will be able to find them for merging.  We
       * assume that we only need to set things up for the
       * superclass and not any deeper ancestors.
       */
      if ((*scePtr)->use_sub_resources)
	{
	  sc->object_class.resources = (*scePtr)->compiled_ext_resources;
	  sc->object_class.num_resources = (*scePtr)->num_ext_resources;
	}
    }
}

/************************************************************************
 *
 *  ClassPartInitPosthook
 *
 ************************************************************************/

static void 
ClassPartInitPosthook(WidgetClass c)
{
  XmExtObjectClass wc = (XmExtObjectClass) c;
  XmBaseClassExt  *wcePtr = _XmGetBaseClassExtPtr(wc, XmQmotif);
  
  if ((*wcePtr) && (*wcePtr)->use_sub_resources)
    {
      /*
       * Put our compiled resources back and zero out oject class so
       * it's invisible to object class create processing.
       */
      (*wcePtr)->compiled_ext_resources = wc->object_class.resources;
      (*wcePtr)->num_ext_resources = wc->object_class.num_resources;
    }
}

/************************************************************************
 *
 *  ClassPartInitialize
 *    Set up the inheritance mechanism for the routines exported by
 *    vendorShells class part.
 *
 ************************************************************************/

static void 
ClassPartInitialize(WidgetClass c)
{
  XmExtObjectClass wc = (XmExtObjectClass) c;
  
  if (wc == (XmExtObjectClass)xmExtObjectClass)
    return;

  _XmBuildExtResources(c);
}

/*ARGSUSED*/
static void 
InitializePrehook(Widget req,	/* unused */
		  Widget new_w,
		  ArgList args,
		  Cardinal *num_args)
{
  XmExtObjectClass ec = (XmExtObjectClass) XtClass(new_w);
  XmBaseClassExt  *wcePtr = _XmGetBaseClassExtPtr(ec, XmQmotif);
  
  if ((*wcePtr)->use_sub_resources)
    {
      /*
       * Get a uncompiled resource list to use with XtGetSubresources.
       * We can't do this in ClassPartInitPosthook because Xt doesn't
       * set class_inited at the right place and thereby mishandles
       * the XtGetResourceList call.
       */
      _XmProcessLock();
      if ((*wcePtr)->ext_resources == NULL)
	{
	  ec->object_class.resources = (*wcePtr)->compiled_ext_resources;
	  ec->object_class.num_resources = (*wcePtr)->num_ext_resources;
	  
	  XtGetResourceList((WidgetClass) ec,
			    &((*wcePtr)->ext_resources),
			    &((*wcePtr)->num_ext_resources));
	}

      XtGetSubresources(XtParent(new_w),
			(XtPointer)new_w,
			NULL, NULL,
			(*wcePtr)->ext_resources,
			(*wcePtr)->num_ext_resources,
			args, *num_args);
      _XmProcessUnlock();
    }
}

static void 
Initialize(Widget req,
	   Widget new_w,
	   ArgList args,
	   Cardinal *num_args)
{
  XmExtObject      ne = (XmExtObject) new_w;
  XmExtObjectClass ec = (XmExtObjectClass) XtClass(new_w);
  Widget           resParent = ne->ext.logicalParent;
  XmWidgetExtData  extData;
  XmBaseClassExt  *wcePtr = _XmGetBaseClassExtPtr(ec, XmQmotif);
  
  if (!(*wcePtr)->use_sub_resources)
    {
      if (resParent)
	{
	  extData = (XmWidgetExtData) XtCalloc(1, sizeof(XmWidgetExtDataRec));
	  _XmPushWidgetExtData(resParent, extData, ne->ext.extensionType);
	  
	  extData->widget = new_w;
	  _XmProcessLock();
	  extData->reqWidget = (Widget)
	    _XmExtObjAlloc(XtClass(new_w)->core_class.widget_size);
	  memcpy((char *)extData->reqWidget, (char *)req,
		 XtClass(new_w)->core_class.widget_size);
	  _XmProcessUnlock();
	  
	  /*  Convert the fields from unit values to pixel values  */
	  _XmExtImportArgs(new_w, args, num_args);
	}
    }
}

/*ARGSUSED*/
static Boolean 
SetValuesPrehook(Widget req,	/* unused */
		 Widget curr,	/* unused */
		 Widget new_w,
		 ArgList args,
		 Cardinal *num_args)
{
  XmExtObjectClass ec = (XmExtObjectClass) XtClass(new_w);
  XmBaseClassExt *wcePtr = _XmGetBaseClassExtPtr(ec, XmQmotif);
  
  if ((*wcePtr)->use_sub_resources)
    {
      _XmProcessLock();
      XtSetSubvalues((XtPointer)new_w,
		     (*wcePtr)->ext_resources,
		     (*wcePtr)->num_ext_resources,
		     args, *num_args);
      _XmProcessUnlock();
    }

  return False;
}

static void 
GetValuesPrehook(Widget new_w,
		 ArgList args,
		 Cardinal *num_args)
{
  XmExtObjectClass ec = (XmExtObjectClass) XtClass(new_w);
  XmBaseClassExt *wcePtr = _XmGetBaseClassExtPtr(ec, XmQmotif);
  
  if ((*wcePtr)->use_sub_resources)
    {
      _XmProcessLock();
      XtGetSubvalues((XtPointer)new_w,
		     (*wcePtr)->ext_resources,
		     (*wcePtr)->num_ext_resources,
		     args, *num_args);
      _XmProcessUnlock();
    }
}

/************************************************************************
 *
 *  SetValues
 *
 ************************************************************************/

/*ARGSUSED*/
static Boolean 
SetValues(Widget old,
	  Widget ref,
	  Widget new_w,
	  ArgList args,
	  Cardinal *num_args)
{
  XmExtObject	  ne = (XmExtObject) new_w;
  Widget	  resParent = ne->ext.logicalParent;
  XmWidgetExtData ext = _XmGetWidgetExtData(resParent, ne->ext.extensionType);
  Cardinal	  extSize;
  
  if (resParent)
    {
      _XmProcessLock();
      extSize = XtClass(new_w)->core_class.widget_size;
      
      ext->widget = new_w;
      
      ext->oldWidget = (Widget) _XmExtObjAlloc(extSize);
      memcpy((char *)ext->oldWidget, (char *)old, extSize); 
      
      ext->reqWidget = (Widget) _XmExtObjAlloc(extSize);
      memcpy((char *)ext->reqWidget, (char *)ref, extSize); 
      _XmProcessUnlock();

      /* Convert the necessary fields from unit values to pixel values. */
      _XmExtImportArgs(new_w, args, num_args);
    }

  return FALSE;
}

/************************************************************************
 *
 *  GetValuesHook
 *
 ************************************************************************/

static void 
GetValuesHook(Widget new_w,
	      ArgList args,
	      Cardinal *num_args)
{
  XmExtObject     ne = (XmExtObject) new_w;
  Widget          resParent = ne->ext.logicalParent;
  XmWidgetExtData ext;
  
  if (resParent)
    {
      ext = _XmGetWidgetExtData(resParent, ne->ext.extensionType);
      
      ext->widget = new_w;
      
      _XmExtGetValuesHook(new_w, args, num_args);
    }
}

/************************************************************************
 *
 *  Destroy
 *
 ************************************************************************/

static void 
Destroy(Widget wid)
{
  XmExtObject extObj = (XmExtObject) wid;
  Widget      resParent = extObj->ext.logicalParent;
  
  if (resParent)
    {
      XmWidgetExtData extData;
      
      _XmPopWidgetExtData(resParent, &extData, extObj->ext.extensionType);
      
      XtFree((char *) extData);
    }
}

char * 
_XmExtObjAlloc(int size)
{
  register int i;
  
  if (size <= XmNUM_BYTES)
    {
      for (i = 0; i < XmNUM_ELEMENTS; i++)
	if (! extarray[i].cache.inuse)
	  {
	    extarray[i].cache.inuse = TRUE;
	    return extarray[i].cache.data;
	  }
    }
  
  return XtMalloc(size);
}

void 
_XmExtObjFree(XtPointer element)
{
  register int i;
  
  for (i = 0; i < XmNUM_ELEMENTS; i++)
    if (extarray[i].cache.data == (char*)element)
      {
	extarray[i].cache.inuse = FALSE;
	return;
      }
  
  XtFree((char *) element);
}

/**********************************************************************
 *
 *  _XmBuildExtResources
 *	Build up the ext's synthetic 
 *	resource processing list by combining the super classes with 
 *	this class.
 *
 **********************************************************************/

void 
_XmBuildExtResources(WidgetClass c)
{
  XmExtObjectClass wc = (XmExtObjectClass) c;
  XmExtObjectClass sc;

  _XmProcessLock();
  _XmInitializeSyntheticResources(wc->ext_class.syn_resources,
				  wc->ext_class.num_syn_resources);
  
  if (wc != (XmExtObjectClass) xmExtObjectClass)
    {
      sc = (XmExtObjectClass) wc->object_class.superclass;
      
      _XmBuildResources (&(wc->ext_class.syn_resources),
			 &(wc->ext_class.num_syn_resources),
			 sc->ext_class.syn_resources,
			 sc->ext_class.num_syn_resources);
    }
  _XmProcessUnlock();
}
