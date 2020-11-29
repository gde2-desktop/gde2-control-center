#ifndef MARCO_WINDOW_MANAGER_H
#define MARCO_WINDOW_MANAGER_H

#include <glib-object.h>
#include "gde2-window-manager.h"

#define MARCO_WINDOW_MANAGER(obj)          G_TYPE_CHECK_INSTANCE_CAST (obj, marco_window_manager_get_type (), MarcoWindowManager)
#define MARCO_WINDOW_MANAGER_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST (klass, marco_window_manager_get_type (), MarcoWindowManagerClass)
#define IS_MARCO_WINDOW_MANAGER(obj)       G_TYPE_CHECK_INSTANCE_TYPE (obj, marco_window_manager_get_type ())

typedef struct _MarcoWindowManager MarcoWindowManager;
typedef struct _MarcoWindowManagerClass MarcoWindowManagerClass;

typedef struct _MarcoWindowManagerPrivate MarcoWindowManagerPrivate;

struct _MarcoWindowManager
{
	Gde2WindowManager parent;
	MarcoWindowManagerPrivate *p;
};

struct _MarcoWindowManagerClass
{
	Gde2WindowManagerClass klass;
};

GType      marco_window_manager_get_type             (void);

#endif