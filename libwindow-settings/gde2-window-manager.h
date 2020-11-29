/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*- */

/* gde2-window-manager.h
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

#ifndef GDE2_WINDOW_MANAGER_H
#define GDE2_WINDOW_MANAGER_H

#include <glib-object.h>

#include <libgde2-desktop/gde2-desktop-item.h>

/* Increment if backward-incompatible changes are made, so we get a clean
 * error. In principle the libtool versioning handles this, but
 * in combination with dlopen I don't quite trust that.
 */
#define GDE2_WINDOW_MANAGER_INTERFACE_VERSION 1

typedef GObject * (* Gde2WindowManagerNewFunc) (int expected_interface_version);

typedef enum
{
        GDE2_WM_SETTING_FONT                = 1 << 0,
        GDE2_WM_SETTING_MOUSE_FOCUS         = 1 << 1,
        GDE2_WM_SETTING_AUTORAISE           = 1 << 2,
        GDE2_WM_SETTING_AUTORAISE_DELAY     = 1 << 3,
        GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER = 1 << 4,
        GDE2_WM_SETTING_THEME               = 1 << 5,
        GDE2_WM_SETTING_DOUBLE_CLICK_ACTION = 1 << 6,
        GDE2_WM_SETTING_COMPOSITING_MANAGER = 1 << 7,
        GDE2_WM_SETTING_COMPOSITING_ALTTAB  = 1 << 8,
        GDE2_WM_SETTING_MASK                =
        GDE2_WM_SETTING_FONT                |
        GDE2_WM_SETTING_MOUSE_FOCUS         |
        GDE2_WM_SETTING_AUTORAISE           |
        GDE2_WM_SETTING_AUTORAISE_DELAY     |
        GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER |
        GDE2_WM_SETTING_THEME               |
        GDE2_WM_SETTING_DOUBLE_CLICK_ACTION |
        GDE2_WM_SETTING_COMPOSITING_MANAGER |
        GDE2_WM_SETTING_COMPOSITING_ALTTAB
} Gde2WMSettingsFlags;

typedef struct
{
        int number;
        const char *human_readable_name;
} Gde2WMDoubleClickAction;

typedef struct
{
        Gde2WMSettingsFlags flags; /* this allows us to expand the struct
                                     * while remaining binary compatible
                                     */
        const char *font;
        int autoraise_delay;
        /* One of the strings "Alt", "Control", "Super", "Hyper", "Meta" */
        const char *mouse_move_modifier;
        const char *theme;
        int double_click_action;

        guint focus_follows_mouse : 1;
        guint autoraise : 1;

        gboolean compositing_manager;
        gboolean compositing_fast_alt_tab;

} Gde2WMSettings;

#ifdef __cplusplus
extern "C" {
#endif

#define GDE2_WINDOW_MANAGER(obj)          G_TYPE_CHECK_INSTANCE_CAST (obj, gde2_window_manager_get_type (), Gde2WindowManager)
#define GDE2_WINDOW_MANAGER_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST (klass, gde2_window_manager_get_type (), Gde2WindowManagerClass)
#define IS_GDE2_WINDOW_MANAGER(obj)       G_TYPE_CHECK_INSTANCE_TYPE (obj, gde2_window_manager_get_type ())
#define GDE2_WINDOW_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), gde2_window_manager_get_type, Gde2WindowManagerClass))

typedef struct _Gde2WindowManager Gde2WindowManager;
typedef struct _Gde2WindowManagerClass Gde2WindowManagerClass;

typedef struct _Gde2WindowManagerPrivate Gde2WindowManagerPrivate;

struct _Gde2WindowManager
{
        GObject parent;

        Gde2WindowManagerPrivate *p;
};

struct _Gde2WindowManagerClass
{
        GObjectClass klass;

        void         (* settings_changed)       (Gde2WindowManager    *wm);

        void         (* change_settings)        (Gde2WindowManager    *wm,
                                                 const Gde2WMSettings *settings);
        void         (* get_settings)           (Gde2WindowManager    *wm,
                                                 Gde2WMSettings       *settings);

        GList *      (* get_theme_list)         (Gde2WindowManager *wm);
        char *       (* get_user_theme_folder)  (Gde2WindowManager *wm);

        int          (* get_settings_mask)      (Gde2WindowManager *wm);

        void         (* get_double_click_actions) (Gde2WindowManager              *wm,
                                                   const Gde2WMDoubleClickAction **actions,
                                                   int                             *n_actions);

        void         (* padding_func_1)         (Gde2WindowManager *wm);
        void         (* padding_func_2)         (Gde2WindowManager *wm);
        void         (* padding_func_3)         (Gde2WindowManager *wm);
        void         (* padding_func_4)         (Gde2WindowManager *wm);
        void         (* padding_func_5)         (Gde2WindowManager *wm);
        void         (* padding_func_6)         (Gde2WindowManager *wm);
        void         (* padding_func_7)         (Gde2WindowManager *wm);
        void         (* padding_func_8)         (Gde2WindowManager *wm);
        void         (* padding_func_9)         (Gde2WindowManager *wm);
        void         (* padding_func_10)        (Gde2WindowManager *wm);
};

GObject *         gde2_window_manager_new                     (Gde2DesktopItem   *item);
GType             gde2_window_manager_get_type                (void);
const char *      gde2_window_manager_get_name                (Gde2WindowManager *wm);
Gde2DesktopItem *gde2_window_manager_get_ditem               (Gde2WindowManager *wm);

/* GList of char *'s */
GList *           gde2_window_manager_get_theme_list          (Gde2WindowManager *wm);
char *            gde2_window_manager_get_user_theme_folder   (Gde2WindowManager *wm);

/* only uses fields with their flags set */
void              gde2_window_manager_change_settings  (Gde2WindowManager    *wm,
                                                         const Gde2WMSettings *settings);
/* only gets fields with their flags set (and if it fails to get a field,
 * it unsets that flag, so flags should be checked on return)
 */
void              gde2_window_manager_get_settings     (Gde2WindowManager *wm,
                                                         Gde2WMSettings    *settings);

void              gde2_window_manager_settings_changed (Gde2WindowManager *wm);

void gde2_window_manager_get_double_click_actions (Gde2WindowManager              *wm,
                                                    const Gde2WMDoubleClickAction **actions,
                                                    int                             *n_actions);

/* Helper functions for Gde2WMSettings */
Gde2WMSettings *gde2_wm_settings_copy (Gde2WMSettings *settings);
void             gde2_wm_settings_free (Gde2WMSettings *settings);

#ifdef __cplusplus
}
#endif

#endif /* GDE2_WINDOW_MANAGER_H */
