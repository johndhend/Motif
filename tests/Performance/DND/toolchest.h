/* $XConsortium: toolchest.h /main/5 1995/07/15 21:01:53 drk $ */
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


#include "ChRedef.h"
/* #include "sgi_visual.h" */
#include <X11/Intrinsic.h>

/* Chests menu description file pathnames: */

#define HOME_CHESTRC "/.chestrc"
#define SYS_CHESTRC  "/usr/lib/X11/system.chestrc"
#define CHEST_SUFFIX ".chest"
#define CHEST_SUFFIX_LENGTH 6

/* name of the top level menu */
#define TOP_MENU_NAME "ToolChest"

/* menu entry types */
enum menuEntryType {ME_NONE, ME_EXEC, ME_CHECKEXEC, ME_CHECKEXPR, ME_SEPARATOR,
		  ME_LABEL, ME_TITLE, ME_MENU};

struct menuEntry
{
    char *label;
    enum menuEntryType type;
    char *menuName;	/* these two fields could be unionized if this gets */
    char *execString;	/* more complicated				    */
    char *exprString;
    Boolean sensitive:1;
    Boolean removed:1;	/* explicitly removed */
    Boolean empty:1;	/* empty menu */
    struct menuEntry*next, *prev;
#ifdef TCMENU
    struct menu *containingMenu;
    Widget entryWidget;
#endif /*TCMENU */
};

struct menu
{
    char *name;
    struct menuEntry *firstMenuEntry;
    struct menuEntry *lastMenuEntry;
    Boolean referenced:1;
    struct menu *next;
#ifdef TCMENU
    struct menuEntry *activeEntry;
    Widget menuWidget;
#endif    
};
    

extern int lineno;
extern char *progName;

/* Visual information */
extern Boolean menuVisualStatus;	/* overall visual status */
extern char * menuVisualType;		/* visual type*/
extern int menuVisualDepth;		/* depth of visual */
extern Colormap menuVisualColormap;	/* the associated colormap */
extern Visual *menuVisual;		/* the visual itself */
extern Window wm_windows[2];	/* windows for XSetWMColormapWindows */


/* Decal information */
extern Boolean showDecal;		/* True if the decal should be shown */
extern Pixel decalForeground;		/* foreground color of Decal */

/* functions */
extern void tcFreeAll();


extern void * tcMalloc(size_t);
extern void FileError();
extern void AppendFile(char *name);
extern void IncludeFile(char *name, Boolean warnIfMissing);
extern char NextChar();
extern void PrevChar();
extern char *SaveChar();
extern void NullChar();
extern char *UnquoteString(char *string);

/* menu functions */
extern struct menuEntry *NewMenuEntry(char *label, enum menuEntryType type);
extern struct menu *FindMenu(char *name, Boolean mallocIt);
extern void RemoveMenuEntry(char *name, char *menuName);
extern void BuildTopMenu(Widget parent, Boolean isMenuBar);

/* execution functions */
extern void ExecCallback (Widget widget, struct menuEntry *client_data,
			  caddr_t call_data);
extern Boolean CheckExec(char *command);
extern Boolean CheckExpr(char *expr);



/* FROM globals.c */
int lineno;	/* current line number */
char *progName;

/* Visual information */
Boolean menuVisualStatus;	/* overall visual status */
char * menuVisualType;		/* visual type*/
int menuVisualDepth;		/* depth of visual */
Colormap menuVisualColormap;	/* the associated colormap */
Visual *menuVisual;		/* the visual itself */
Window wm_windows[2];	/* windows for XSetWMColormapWindows */

/* Decal information */
Boolean showDecal;		/* True if the decal should be shown */
Pixel decalForeground;		/* foreground color of Decal */
