#ifndef GDE2_WINDOW_MANAGER_LIST_H
#define GDE2_WINDOW_MANAGER_LIST_H

#include <gtk/gtk.h>

#include "gde2-window-manager.h"

void gde2_wm_manager_init (void);

/* gets the currently active window manager */
Gde2WindowManager *gde2_wm_manager_get_current (GdkScreen *screen);

gboolean gde2_wm_manager_spawn_config_tool_for_current (GdkScreen  *screen,
                                                         GError    **error);

#endif
