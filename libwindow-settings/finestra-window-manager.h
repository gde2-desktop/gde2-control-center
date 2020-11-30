#ifndef FINESTRA_WINDOW_MANAGER_H
#define FINESTRA_WINDOW_MANAGER_H

#include <glib-object.h>
#include "gde2-window-manager.h"

#define FINESTRA_WINDOW_MANAGER(obj)          G_TYPE_CHECK_INSTANCE_CAST (obj, finestra_window_manager_get_type (), FinestraWindowManager)
#define FINESTRA_WINDOW_MANAGER_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST (klass, finestra_window_manager_get_type (), FinestraWindowManagerClass)
#define IS_FINESTRA_WINDOW_MANAGER(obj)       G_TYPE_CHECK_INSTANCE_TYPE (obj, finestra_window_manager_get_type ())

typedef struct _FinestraWindowManager FinestraWindowManager;
typedef struct _FinestraWindowManagerClass FinestraWindowManagerClass;

typedef struct _FinestraWindowManagerPrivate FinestraWindowManagerPrivate;

struct _FinestraWindowManager
{
	Gde2WindowManager parent;
	FinestraWindowManagerPrivate *p;
};

struct _FinestraWindowManagerClass
{
	Gde2WindowManagerClass klass;
};

GType      finestra_window_manager_get_type             (void);

#endif
