
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
/*   $XConsortium: ShellEP.h /main/9 1995/07/13 18:00:25 drk $ */
/*
*  (c) Copyright 1989, 1990  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
*  (c) Copyright 1988 MICROSOFT CORPORATION */
#ifndef _XmShellEP_h
#define _XmShellEP_h

#include <Xm/DesktopP.h>

#ifdef __cplusplus
extern "C" {
#endif


#define XmInheritEventHandler		((XtEventHandler)_XtInherit)

#define _XmRAW_MAP 0
#define _XmPOPUP_MAP 1
#define _XmMANAGE_MAP 2


#ifndef XmIsShellExt
#define XmIsShellExt(w)	XtIsSubclass(w, xmShellExtObjectClass)
#endif /* XmIsShellExt */

typedef struct _XmShellExtRec *XmShellExtObject;
typedef struct _XmShellExtClassRec *XmShellExtObjectClass;
externalref WidgetClass xmShellExtObjectClass;


typedef struct _XmShellExtClassPart{
    XtEventHandler	structureNotifyHandler;
    XtPointer		extension;
}XmShellExtClassPart, *XmShellExtClassPartPtr;

typedef struct _XmShellExtClassRec{
    ObjectClassPart		object_class;
    XmExtClassPart		ext_class;
    XmDesktopClassPart 		desktop_class;
    XmShellExtClassPart 	shell_class;
}XmShellExtClassRec;

typedef struct {
    unsigned long	lastConfigureRequest;
    Boolean		useAsyncGeometry;
} XmShellExtPart, *XmShellExtPartPtr;

externalref XmShellExtClassRec 	xmShellExtClassRec;

typedef struct _XmShellExtRec{
    ObjectPart			object;
    XmExtPart			ext;
    XmDesktopPart		desktop;
    XmShellExtPart		shell;
}XmShellExtRec;


/********    Private Function Declarations    ********/


/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* _XmShellEP_h */
/* DON'T ADD STUFF AFTER THIS #endif */
