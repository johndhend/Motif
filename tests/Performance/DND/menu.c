/* $XConsortium: menu.c /main/5 1995/07/15 21:01:38 drk $ */
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


#include <stdio.h>
#include <string.h>
#include <Xm/Xm.h>
#include <Xm/LabelG.h>
#include <Xm/RowColumn.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushBG.h>
#include <Xm/CascadeB.h>
#include "toolchest.h"


static struct menu *menus;

/* allocate a new menu entry */
struct menuEntry *
NewMenuEntry(char *label, enum menuEntryType type)
{
    register struct menuEntry *ret;
    ret = (struct menuEntry *)tcMalloc(sizeof (struct menuEntry));
    ret->label = label;
    ret->type = type;
    ret->sensitive = TRUE;
    ret->removed = FALSE;
    ret->empty = FALSE;
#ifdef TCEDIT
    ret->menuName = "";
    ret->execString = "";
    ret->exprString = "";
#endif
    return (ret);
}

/* look up a menu by name and return it.  If it is not found and mallocIt is
 * true, allocate a new one.
 */
struct menu *
FindMenu(char *name, Boolean mallocIt)
{
    struct menu *menu = menus;

    /* look for the menu */
    while (menu)
    {
	if (strcmp(menu->name, name) == 0)
	    return (menu);
	menu = menu->next;
    };
    /* malloc a new one if appropriate */
    if (mallocIt)
    {
	menu = tcMalloc(sizeof(struct menu));
	menu->next = menus;
	menus = menu;
	menu->name = name;
	menu->firstMenuEntry = NULL;
	menu->lastMenuEntry = NULL;
	menu->referenced = FALSE;
#ifdef TCMENU
	menu->activeEntry = NULL;
	menu->menuWidget = NULL;
#endif
    }
    else
	return (NULL);
}

/* remove itemName from menu menu.  Return TRUE if it was found */
static Boolean
removeItemFromMenu (char *itemName, struct menu *menu)
{
    struct menuEntry *entry = menu->firstMenuEntry;
    struct menuEntry *prev, *next;

    while (entry)
    {
	if (strcmp (itemName, entry->label) == 0 && !entry->removed)
	{
	    entry->removed = TRUE;
	    return (TRUE);
	}
	entry = entry->next;
    }
    return (FALSE);
}

/* remove item name from menu named menuName.  If menuName is NULL, remove
 * it from any menu
 */
void
RemoveMenuEntry(char *name, char *menuName)
{
    register struct menu *menu;

    if (menuName == NULL)
    {
	Boolean found = FALSE;

	for (menu = menus; menu; menu = menu->next)
	{
	    if (removeItemFromMenu(name, menu))
	    {
		if (found)
		    FileError ("Item %s removed from more than one menu", name);
		else found = TRUE;
	    }
	}
	if (!found)
	    FileError ("Can't find %s for removal\n", name);
    }
    else
    {
	menu = FindMenu(menuName, FALSE);
	if (menu == NULL)
	    FileError("Cannot find menu %s for removal\n", menuName);
	else if (!removeItemFromMenu(name, menu))
	    FileError("Item %s not found in menu %s\n", name, menuName);
    }
}

#ifndef TCEDIT
/* recursively build a menu, based on info previously read.  name is the
 * name of the menu, parent is the parent pane, and isMenuBar is true of
 * the menu is a menu bar.
 */
static void
buildMenu(struct menu *menu, Widget parent, Boolean isMenuBar)
{
    register struct menuEntry *entry;
    Arg wargs[10];
    int n;
    Widget w;
    XmString xmstr;
    enum menuEntryType lastType = ME_NONE;
    Boolean thisEntryRemoved = FALSE;
    Boolean lastEntryRemoved;

    if (menu->referenced)
    {
	fprintf (stderr,
		 "WARNING:  menu %s referenced more than once, extra reference ignored\n",
		 menu->name);
	return;
    }
    menu->referenced = TRUE;
    for (entry = menu->firstMenuEntry; entry; entry = entry->next)
    {
	lastEntryRemoved = thisEntryRemoved;
	if (entry->removed)
	{
	    thisEntryRemoved = TRUE;
	}
	else
	{
	    thisEntryRemoved = FALSE;
	    xmstr = XmStringCreateSimple(entry->label);
	    switch (entry->type)
	    {
	    case ME_EXEC:
	    case ME_CHECKEXEC:
	    case ME_CHECKEXPR:
		if (entry->type == ME_CHECKEXEC)
		    entry->sensitive = CheckExec(entry->execString);
		else if (entry->type == ME_CHECKEXPR)
		    entry->sensitive = CheckExpr(entry->exprString);
		else
		    entry->sensitive = TRUE;
		n = 0;
		XtSetArg (wargs[n], XmNlabelString, xmstr);n++;
		XtSetArg (wargs[n], XmNalignment, XmALIGNMENT_CENTER); n++; 
		XtSetArg (wargs[n], XmNsensitive, entry->sensitive); n++; 
		/* In the menu bar we must create a cascade button instead of
		 * a push button.  (Note that since menu pixmaps are only in
		 * the widget, we create a widget rather than a gadget
		 * for the cascade button
		 */
		w = XtCreateManagedWidget(entry->label,
					  isMenuBar?
				              xmCascadeButtonWidgetClass: 
					      xmPushButtonGadgetClass,
					  parent, wargs, n);
		XtAddCallback(w, XmNactivateCallback, ExecCallback,
			      (caddr_t)entry);
		break;
		
	    case ME_SEPARATOR:
		/* if we removed the last entry and the last non
		 * removed entry was a separator, a title, or the start,
		 * remove this entry.  However, don't set thisEntryRemoved
		 * so that if another separator immediatly follows, it is
		 * drawn.
		 */
		if (!(lastEntryRemoved &&
		    (lastType == ME_SEPARATOR ||
		     lastType == ME_TITLE ||
		     lastType == ME_NONE)))
		{
		    n = 0;
		    w = XmCreateSeparatorGadget (parent, entry->label,
						 wargs, n);
		    XtManageChild(w);
		}
		break;
		
	    case ME_TITLE:
		n = 0;
		XtSetArg (wargs[n], XmNlabelString, xmstr);n++;
		XtSetArg (wargs[n], XmNalignment, XmALIGNMENT_CENTER); n++; 
		w = XmCreateLabelGadget(parent, entry->label,
					NULL, 0); n++;
		XtManageChild(w);
		n = 0;
		XtSetArg (wargs[n], XmNseparatorType, XmDOUBLE_LINE); n++;
		w = XmCreateSeparatorGadget (parent, "separator",
					     wargs, n);
		XtManageChild(w);
		
	    case ME_LABEL:
		n = 0;
		XtSetArg (wargs[n], XmNlabelString, xmstr);n++;
		XtSetArg (wargs[n], XmNalignment, XmALIGNMENT_CENTER); n++; 
		w = XmCreateLabelGadget(parent, entry->label,
					NULL, 0);
		XtManageChild(w);
		break;
		
	    case ME_MENU:
		{
		    struct menu *submenu;
		    Widget pane;
		    
		    submenu = FindMenu(entry->menuName, FALSE);
		    if (submenu)
		    {
			n = 0;
			if (menuVisualStatus != SG_VISUAL_DEFAULT)
			{
			    XtSetArg (wargs[n], XmNdepth,
				      menuVisualDepth); n++;
			    XtSetArg (wargs[n], XmNcolormap, 
				      menuVisualColormap); n++;
			    XtSetArg (wargs[n], XmNvisual, menuVisual); n++;
			}
			pane = XmCreatePulldownMenu(parent, entry->menuName,
						    wargs, n);
			wm_windows[0] = XtWindow(pane);
			
			n = 0;
			XtSetArg(wargs[n], XmNsubMenuId, pane);n++;
			XtSetArg(wargs[n], XmNlabelString, xmstr);n++;
			if (isMenuBar && showDecal)
			{
			    XtSetArg(wargs[n], XmNmenuBarPixmap,
				     decalPixmap); n++;
			}
			w = XmCreateCascadeButton(parent, submenu->name,
						  wargs, n);
			XtManageChild(w);
			
			buildMenu (submenu, pane, FALSE);
		    }
		    else
		    {
			/* menu wasn't found.  Mark it so */
			entry->empty = TRUE;
			thisEntryRemoved = TRUE;
		    }
		}
		break;
		
	    default:
		XtError ("Unknown menu item type");
	    }
	    XmStringFree(xmstr);
	    if (!thisEntryRemoved)
		lastType = entry->type;
	}
    }
}
	    
/* build the top level menu.  The flag isMenuBar indicates whether it
 * is in a menu bar
 */
void
BuildTopMenu(Widget parent, Boolean isMenuBar)
{
    struct menu *topMenu;

    if ((topMenu = FindMenu(TOP_MENU_NAME, FALSE)) == NULL)
    {
	char buf[100];
	sprintf(buf, 
		"Menu specification: menu '%s' referenced but not found\n",
		TOP_MENU_NAME);
	XtError(buf);
    }
    buildMenu(topMenu, parent, isMenuBar);
}
#endif
