/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*- */

/* finestra-window-manager.c
 * Copyright (C) 2002 Seth Nickell
 * Copyright (C) 2002 Red Hat, Inc.
 *
 * Written by: Seth Nickell <snickell@stanford.edu>,
 *             Havoc Pennington <hp@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <config.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gio/gio.h>

#include "finestra-window-manager.h"

#define FINESTRA_SCHEMA "org.gde2.Finestra.general"
#define FINESTRA_THEME_KEY "theme"
#define FINESTRA_FONT_KEY  "titlebar-font"
#define FINESTRA_FOCUS_KEY "focus-mode"
#define FINESTRA_USE_SYSTEM_FONT_KEY "titlebar-uses-system-font"
#define FINESTRA_AUTORAISE_KEY "auto-raise"
#define FINESTRA_AUTORAISE_DELAY_KEY "auto-raise-delay"
#define FINESTRA_MOUSE_MODIFIER_KEY "mouse-button-modifier"
#define FINESTRA_DOUBLE_CLICK_TITLEBAR_KEY "action-double-click-titlebar"
#define FINESTRA_COMPOSITING_MANAGER_KEY "compositing-manager"
#define FINESTRA_COMPOSITING_FAST_ALT_TAB_KEY "compositing-fast-alt-tab"


/* keep following enums in sync with finestra */
enum
{
        ACTION_TITLEBAR_TOGGLE_SHADE,
        ACTION_TITLEBAR_TOGGLE_MAXIMIZE,
        ACTION_TITLEBAR_TOGGLE_MAXIMIZE_HORIZONTALLY,
        ACTION_TITLEBAR_TOGGLE_MAXIMIZE_VERTICALLY,
        ACTION_TITLEBAR_MINIMIZE,
        ACTION_TITLEBAR_NONE,
        ACTION_TITLEBAR_LOWER,
        ACTION_TITLEBAR_MENU
};
enum
{
        FOCUS_MODE_CLICK,
        FOCUS_MODE_SLOPPY,
        FOCUS_MODE_MOUSE
};

static Gde2WindowManagerClass *parent_class;

struct _FinestraWindowManagerPrivate {
        GSettings *settings;
        char *font;
        char *theme;
        char *mouse_modifier;
};

static void
value_changed (GSettings *settings,
               gchar     *key,
               void      *data)
{
        FinestraWindowManager *meta_wm;

        meta_wm = FINESTRA_WINDOW_MANAGER (data);

        gde2_window_manager_settings_changed (GDE2_WINDOW_MANAGER (meta_wm));
}

/* this function is called when the shared lib is loaded */
GObject *
window_manager_new (int expected_interface_version)
{
        GObject *wm;

        if (expected_interface_version != GDE2_WINDOW_MANAGER_INTERFACE_VERSION) {
                g_warning ("Finestra window manager module wasn't compiled with the current version of gde2-control-center");
                return NULL;
        }
  
        wm = g_object_new (finestra_window_manager_get_type (), NULL);

        return wm;
}

static GList *
add_themes_from_dir (GList *current_list, const char *path)
{
        DIR *theme_dir;
        struct dirent *entry;
        char *theme_file_path;
        GList *node;
        gboolean found = FALSE;

        if (!(g_file_test (path, G_FILE_TEST_EXISTS) && g_file_test (path, G_FILE_TEST_IS_DIR))) {
                return current_list;
        }

        theme_dir = opendir (path);
        /* If this is NULL, then we couldn't open ~/.themes.  The test above
         * only checks existence, not wether we can really read it.*/
        if (theme_dir == NULL)
                return current_list;
        
        for (entry = readdir (theme_dir); entry != NULL; entry = readdir (theme_dir)) {
                theme_file_path = g_build_filename (path, entry->d_name, "metacity-1/metacity-theme-2.xml", NULL);

                if (g_file_test (theme_file_path, G_FILE_TEST_EXISTS)) {

                        for (node = current_list; (node != NULL) && (!found); node = node->next) {
                                found = (strcmp (node->data, entry->d_name) == 0);
                        }

                        if (!found) {
                                current_list = g_list_prepend (current_list, g_strdup (entry->d_name));
                        }
                }
                else {
                        g_free (theme_file_path);
                        theme_file_path = g_build_filename (path, entry->d_name, "metacity-1/metacity-theme-1.xml", NULL);

                        if (g_file_test (theme_file_path, G_FILE_TEST_EXISTS)) {

                                for (node = current_list; (node != NULL) && (!found); node = node->next) {
                                        found = (strcmp (node->data, entry->d_name) == 0);
                                }

                                if (!found) {
                                        current_list = g_list_prepend (current_list, g_strdup (entry->d_name));
                                }
                        }
                }

                found = FALSE;
                /*g_free (entry);*/
                g_free (theme_file_path);
        }
   
        closedir (theme_dir);

        return current_list;
}

static GList *  
finestra_get_theme_list (Gde2WindowManager *wm)
{
        GList *themes = NULL;
        char *home_dir_themes;

        home_dir_themes = g_build_filename (g_get_home_dir (), ".themes", NULL);

        themes = add_themes_from_dir (themes, FINESTRA_THEME_DIR);
        themes = add_themes_from_dir (themes, "/usr/share/themes");
        themes = add_themes_from_dir (themes, home_dir_themes);

        g_free (home_dir_themes);

        return themes;
}

static char *
finestra_get_user_theme_folder (Gde2WindowManager *wm)
{
        return g_build_filename (g_get_home_dir (), ".themes", NULL);
}

static void
finestra_change_settings (Gde2WindowManager    *wm,
                          const Gde2WMSettings *settings)
{
        FinestraWindowManager *meta_wm;

        meta_wm = FINESTRA_WINDOW_MANAGER (wm);

        if (settings->flags & GDE2_WM_SETTING_COMPOSITING_MANAGER)
                g_settings_set_boolean (meta_wm->p->settings,
                                        FINESTRA_COMPOSITING_MANAGER_KEY,
                                        settings->compositing_manager);

        if (settings->flags & GDE2_WM_SETTING_COMPOSITING_ALTTAB)
                g_settings_set_boolean (meta_wm->p->settings,
                                        FINESTRA_COMPOSITING_FAST_ALT_TAB_KEY,
                                        settings->compositing_fast_alt_tab);

        if (settings->flags & GDE2_WM_SETTING_MOUSE_FOCUS)
                g_settings_set_enum (meta_wm->p->settings,
                                     FINESTRA_FOCUS_KEY,
                                     settings->focus_follows_mouse ?
                                     FOCUS_MODE_SLOPPY : FOCUS_MODE_CLICK);

        if (settings->flags & GDE2_WM_SETTING_AUTORAISE)
                g_settings_set_boolean (meta_wm->p->settings,
                                        FINESTRA_AUTORAISE_KEY,
                                        settings->autoraise);
        
        if (settings->flags & GDE2_WM_SETTING_AUTORAISE_DELAY)
                g_settings_set_int (meta_wm->p->settings,
                                    FINESTRA_AUTORAISE_DELAY_KEY,
                                    settings->autoraise_delay);

        if (settings->flags & GDE2_WM_SETTING_FONT) {
                g_settings_set_string (meta_wm->p->settings,
                                       FINESTRA_FONT_KEY,
                                       settings->font);
        }
        
        if (settings->flags & GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER) {
                char *value;

                value = g_strdup_printf ("<%s>", settings->mouse_move_modifier);
                g_settings_set_string (meta_wm->p->settings,
                                       FINESTRA_MOUSE_MODIFIER_KEY,
                                       value);
                g_free (value);
        }

        if (settings->flags & GDE2_WM_SETTING_THEME) {
                g_settings_set_string (meta_wm->p->settings,
                                       FINESTRA_THEME_KEY,
                                       settings->theme);
        }

        if (settings->flags & GDE2_WM_SETTING_DOUBLE_CLICK_ACTION) {
                g_settings_set_enum (meta_wm->p->settings,
                                     FINESTRA_DOUBLE_CLICK_TITLEBAR_KEY,
                                     settings->double_click_action);
        }
}

static void
finestra_get_settings (Gde2WindowManager *wm,
                       Gde2WMSettings    *settings)
{
        int to_get;
        FinestraWindowManager *meta_wm;

        meta_wm = FINESTRA_WINDOW_MANAGER (wm);
        
        to_get = settings->flags;
        settings->flags = 0;
        
        if (to_get & GDE2_WM_SETTING_COMPOSITING_MANAGER) {
                settings->compositing_manager = g_settings_get_boolean (meta_wm->p->settings,
                                                                        FINESTRA_COMPOSITING_MANAGER_KEY);
                settings->flags |= GDE2_WM_SETTING_COMPOSITING_MANAGER;
        }
        
        if (to_get & GDE2_WM_SETTING_COMPOSITING_ALTTAB) {
                settings->compositing_fast_alt_tab = g_settings_get_boolean (meta_wm->p->settings,
                                                                             FINESTRA_COMPOSITING_FAST_ALT_TAB_KEY);
                settings->flags |= GDE2_WM_SETTING_COMPOSITING_ALTTAB;
        }
        
        if (to_get & GDE2_WM_SETTING_MOUSE_FOCUS) {
                gint finestra_focus_value;

                finestra_focus_value = g_settings_get_enum (meta_wm->p->settings,
                                                         FINESTRA_FOCUS_KEY);
                settings->focus_follows_mouse = FALSE;
                if (finestra_focus_value == FOCUS_MODE_SLOPPY || finestra_focus_value == FOCUS_MODE_MOUSE)
                        settings->focus_follows_mouse = TRUE;

                settings->flags |= GDE2_WM_SETTING_MOUSE_FOCUS;
        }
        
        if (to_get & GDE2_WM_SETTING_AUTORAISE) {
                settings->autoraise = g_settings_get_boolean (meta_wm->p->settings,
                                                              FINESTRA_AUTORAISE_KEY);
                settings->flags |= GDE2_WM_SETTING_AUTORAISE;
        }
        
        if (to_get & GDE2_WM_SETTING_AUTORAISE_DELAY) {
                settings->autoraise_delay =
                        g_settings_get_int (meta_wm->p->settings,
                                            FINESTRA_AUTORAISE_DELAY_KEY);
                settings->flags |= GDE2_WM_SETTING_AUTORAISE_DELAY;
        }

        if (to_get & GDE2_WM_SETTING_FONT) {
                char *str;

                str = g_settings_get_string (meta_wm->p->settings,
                                             FINESTRA_FONT_KEY);

                if (str == NULL)
                        str = g_strdup ("Sans Bold 12");

                if (meta_wm->p->font &&
                    strcmp (meta_wm->p->font, str) == 0) {
                        g_free (str);
                } else {
                        g_free (meta_wm->p->font);
                        meta_wm->p->font = str;
                }
                
                settings->font = meta_wm->p->font;

                settings->flags |= GDE2_WM_SETTING_FONT;
        }
        
        if (to_get & GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER) {
                char *str;
                const char *new;

                str = g_settings_get_string (meta_wm->p->settings,
                                             FINESTRA_MOUSE_MODIFIER_KEY);

                if (str == NULL)
                        str = g_strdup ("<Super>");

                if (strcmp (str, "<Super>") == 0)
                        new = "Super";
                else if (strcmp (str, "<Alt>") == 0)
                        new = "Alt";
                else if (strcmp (str, "<Meta>") == 0)
                        new = "Meta";
                else if (strcmp (str, "<Hyper>") == 0)
                        new = "Hyper";
                else if (strcmp (str, "<Control>") == 0)
                        new = "Control";
                else
                        new = NULL;

                if (new && meta_wm->p->mouse_modifier &&
                    strcmp (new, meta_wm->p->mouse_modifier) == 0) {
                        /* unchanged */;
                } else {
                        g_free (meta_wm->p->mouse_modifier);
                        meta_wm->p->mouse_modifier = g_strdup (new);
                }

                g_free (str);

                settings->mouse_move_modifier = meta_wm->p->mouse_modifier;
                
                settings->flags |= GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER;
        }

        if (to_get & GDE2_WM_SETTING_THEME) {
                char *str;

                str = g_settings_get_string (meta_wm->p->settings,
                                             FINESTRA_THEME_KEY);

                if (str == NULL)
                        str = g_strdup ("Spidey");

                g_free (meta_wm->p->theme);
                meta_wm->p->theme = str;
                settings->theme = meta_wm->p->theme;

                settings->flags |= GDE2_WM_SETTING_THEME;
        }

        if (to_get & GDE2_WM_SETTING_DOUBLE_CLICK_ACTION) {
                settings->double_click_action =
                        g_settings_get_enum (meta_wm->p->settings,
                                             FINESTRA_DOUBLE_CLICK_TITLEBAR_KEY);
                
                settings->flags |= GDE2_WM_SETTING_DOUBLE_CLICK_ACTION;
        }
}

static int
finestra_get_settings_mask (Gde2WindowManager *wm)
{
        return GDE2_WM_SETTING_MASK;
}

static void
finestra_get_double_click_actions (Gde2WindowManager              *wm,
                                   const Gde2WMDoubleClickAction **actions_p,
                                   int                             *n_actions_p)
{
        static Gde2WMDoubleClickAction actions[] = {
                { ACTION_TITLEBAR_TOGGLE_SHADE, N_("Roll up") },
                { ACTION_TITLEBAR_TOGGLE_MAXIMIZE, N_("Maximize") },
                { ACTION_TITLEBAR_TOGGLE_MAXIMIZE_HORIZONTALLY, N_("Maximize Horizontally") },
                { ACTION_TITLEBAR_TOGGLE_MAXIMIZE_VERTICALLY, N_("Maximize Vertically") },
                { ACTION_TITLEBAR_MINIMIZE, N_("Minimize") },
                { ACTION_TITLEBAR_NONE, N_("None") }
        };
        
        static gboolean initialized = FALSE;

        if (!initialized) {
                int i;
                
                initialized = TRUE;
                i = 0;
                for (i = 0; i < G_N_ELEMENTS (actions); i++) {
                        actions[i].human_readable_name = _(actions[i].human_readable_name);
                }
        }

        *actions_p = actions;
        *n_actions_p = (int) G_N_ELEMENTS (actions);        
}

static void
finestra_window_manager_init (FinestraWindowManager *finestra_window_manager,
                              FinestraWindowManagerClass *class)
{
        finestra_window_manager->p = g_new0 (FinestraWindowManagerPrivate, 1);
        finestra_window_manager->p->settings = g_settings_new (FINESTRA_SCHEMA);
        finestra_window_manager->p->font = NULL;
        finestra_window_manager->p->theme = NULL;
        finestra_window_manager->p->mouse_modifier = NULL;

        g_signal_connect (finestra_window_manager->p->settings,
                          "changed",
                          G_CALLBACK (value_changed), finestra_window_manager);
}

static void
finestra_window_manager_finalize (GObject *object) 
{
        FinestraWindowManager *finestra_window_manager;

        g_return_if_fail (object != NULL);
        g_return_if_fail (IS_FINESTRA_WINDOW_MANAGER (object));

        finestra_window_manager = FINESTRA_WINDOW_MANAGER (object);

        g_object_unref (finestra_window_manager->p->settings);
        g_free (finestra_window_manager->p);

        G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
finestra_window_manager_class_init (FinestraWindowManagerClass *class) 
{
        GObjectClass *object_class;
        Gde2WindowManagerClass *wm_class;

        object_class = G_OBJECT_CLASS (class);
        wm_class = GDE2_WINDOW_MANAGER_CLASS (class);

        object_class->finalize = finestra_window_manager_finalize;

        wm_class->change_settings          = finestra_change_settings;
        wm_class->get_settings             = finestra_get_settings;
        wm_class->get_settings_mask        = finestra_get_settings_mask;
        wm_class->get_user_theme_folder    = finestra_get_user_theme_folder;
        wm_class->get_theme_list           = finestra_get_theme_list;
        wm_class->get_double_click_actions = finestra_get_double_click_actions;
        
        parent_class = g_type_class_peek_parent (class);
}

GType
finestra_window_manager_get_type (void)
{
        static GType finestra_window_manager_type = 0;

        if (!finestra_window_manager_type) {
                static GTypeInfo finestra_window_manager_info = {
                        sizeof (FinestraWindowManagerClass),
                        NULL, /* GBaseInitFunc */
                        NULL, /* GBaseFinalizeFunc */
                        (GClassInitFunc) finestra_window_manager_class_init,
                        NULL, /* GClassFinalizeFunc */
                        NULL, /* user-supplied data */
                        sizeof (FinestraWindowManager),
                        0, /* n_preallocs */
                        (GInstanceInitFunc) finestra_window_manager_init,
                        NULL
                };

                finestra_window_manager_type = 
                        g_type_register_static (gde2_window_manager_get_type (), 
                                                "FinestraWindowManager",
                                                &finestra_window_manager_info, 0);
        }

        return finestra_window_manager_type;
}


