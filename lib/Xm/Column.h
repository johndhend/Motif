
#include <localdef.h>

#ifndef __column_h__
#define __column_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <Xm/Xm.h>
#include <Xm/Ext.h>

extern WidgetClass xmColumnWidgetClass;

typedef struct _XmColumnClassRec * XmColumnWidgetClass;
typedef struct _XmColumnRec      * XmColumnWidget;

#ifndef XmIsColumn
#define XmIsColumn(w) (XtIsSubclass(w, xmColumnWidgetClass))
#endif

#if NeedFunctionPrototypes
extern Widget XmCreateColumn(Widget, String, ArgList, Cardinal);
extern Widget XmColumnGetChildLabel(Widget);
#else
extern Widget XmCreateColumn();
extern Widget XmColumnGetChildLabel();
#endif

#ifdef __cplusplus
}
#endif

#endif /* __column_h__ */
