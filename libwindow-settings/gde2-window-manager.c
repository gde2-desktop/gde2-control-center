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

#include "gde2-window-manager.h"

#include <gmodule.h>

static GObjectClass *parent_class;

struct _Gde2WindowManagerPrivate {
        char *window_manager_name;
        Gde2DesktopItem *ditem;
};

GObject *
gde2_window_manager_new (Gde2DesktopItem *it)
{
        const char *settings_lib;
        char *module_name;
        Gde2WindowManagerNewFunc wm_new_func = NULL;
        GObject *wm;
        GModule *module;
        gboolean success;

        settings_lib = gde2_desktop_item_get_string (it, "X-GDE2-WMSettingsModule");

        module_name = g_module_build_path (GDE2_WINDOW_MANAGER_MODULE_PATH,
                                           settings_lib);

        module = g_module_open (module_name, G_MODULE_BIND_LAZY);
        if (module == NULL) {
                g_warning ("Couldn't load window manager settings module `%s' (%s)", module_name, g_module_error ());
		g_free (module_name);
                return NULL;
        }

        success = g_module_symbol (module, "window_manager_new",
                                   (gpointer *) &wm_new_func);  
  
        if ((!success) || wm_new_func == NULL) {
                g_warning ("Couldn't load window manager settings module `%s`, couldn't find symbol \'window_manager_new\'", module_name);
		g_free (module_name);
                return NULL;
        }

	g_free (module_name);

        wm = (* wm_new_func) (GDE2_WINDOW_MANAGER_INTERFACE_VERSION);

        if (wm == NULL)
                return NULL;
        
        (GDE2_WINDOW_MANAGER (wm))->p->window_manager_name = g_strdup (gde2_desktop_item_get_string (it, GDE2_DESKTOP_ITEM_NAME));
        (GDE2_WINDOW_MANAGER (wm))->p->ditem = gde2_desktop_item_ref (it);
  
        return wm;
}

const char * 
gde2_window_manager_get_name (Gde2WindowManager *wm)
{
        return wm->p->window_manager_name;
}

Gde2DesktopItem *
gde2_window_manager_get_ditem (Gde2WindowManager *wm)
{
        return gde2_desktop_item_ref (wm->p->ditem);
}

GList *
gde2_window_manager_get_theme_list (Gde2WindowManager *wm)
{
        Gde2WindowManagerClass *klass = GDE2_WINDOW_MANAGER_GET_CLASS (wm);
        if (klass->get_theme_list)
                return klass->get_theme_list (wm);
        else
                return NULL;
}

char *
gde2_window_manager_get_user_theme_folder (Gde2WindowManager *wm)
{
        Gde2WindowManagerClass *klass = GDE2_WINDOW_MANAGER_GET_CLASS (wm);
        if (klass->get_user_theme_folder)
                return klass->get_user_theme_folder (wm);
        else
                return NULL;
}

void
gde2_window_manager_get_double_click_actions (Gde2WindowManager              *wm,
                                               const Gde2WMDoubleClickAction **actions,
                                               int                             *n_actions)
{
        Gde2WindowManagerClass *klass = GDE2_WINDOW_MANAGER_GET_CLASS (wm);

        *actions = NULL;
        *n_actions = 0;
        
        if (klass->get_double_click_actions)
                klass->get_double_click_actions (wm, actions, n_actions);
}

void
gde2_window_manager_change_settings  (Gde2WindowManager    *wm,
                                       const Gde2WMSettings *settings)
{
        Gde2WindowManagerClass *klass = GDE2_WINDOW_MANAGER_GET_CLASS (wm);
        
        (* klass->change_settings) (wm, settings);
}

void
gde2_window_manager_get_settings (Gde2WindowManager *wm,
                                   Gde2WMSettings    *settings)
{
        Gde2WindowManagerClass *klass = GDE2_WINDOW_MANAGER_GET_CLASS (wm);
        int mask;

        mask = (* klass->get_settings_mask) (wm);
        settings->flags &= mask; /* avoid back compat issues by not returning
                                  * fields to the caller that the WM module
                                  * doesn't know about
                                  */
        
        (* klass->get_settings) (wm, settings);
}

static void
gde2_window_manager_init (Gde2WindowManager *gde2_window_manager, Gde2WindowManagerClass *class)
{
	gde2_window_manager->p = g_new0 (Gde2WindowManagerPrivate, 1);
}

static void
gde2_window_manager_finalize (GObject *object) 
{
	Gde2WindowManager *gde2_window_manager;

	g_return_if_fail (object != NULL);
	g_return_if_fail (IS_GDE2_WINDOW_MANAGER (object));

	gde2_window_manager = GDE2_WINDOW_MANAGER (object);

	g_free (gde2_window_manager->p);

	parent_class->finalize (object);
}

enum {
  SETTINGS_CHANGED,
  LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = { 0 };

static void
gde2_window_manager_class_init (Gde2WindowManagerClass *class) 
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS (class);

	object_class->finalize = gde2_window_manager_finalize;
        
	parent_class = g_type_class_peek_parent (class);

        
        signals[SETTINGS_CHANGED] =
                g_signal_new ("settings_changed",
                              G_OBJECT_CLASS_TYPE (class),
                              G_SIGNAL_RUN_FIRST | G_SIGNAL_NO_RECURSE,
                              G_STRUCT_OFFSET (Gde2WindowManagerClass, settings_changed),
                              NULL, NULL,
                              g_cclosure_marshal_VOID__VOID,
                              G_TYPE_NONE, 0);
}


GType
gde2_window_manager_get_type (void)
{
	static GType gde2_window_manager_type = 0;

	if (!gde2_window_manager_type) {
		static GTypeInfo gde2_window_manager_info = {
			sizeof (Gde2WindowManagerClass),
			NULL, /* GBaseInitFunc */
			NULL, /* GBaseFinalizeFunc */
			(GClassInitFunc) gde2_window_manager_class_init,
			NULL, /* GClassFinalizeFunc */
			NULL, /* user-supplied data */
			sizeof (Gde2WindowManager),
			0, /* n_preallocs */
			(GInstanceInitFunc) gde2_window_manager_init,
			NULL
		};

		gde2_window_manager_type = 
			g_type_register_static (G_TYPE_OBJECT, 
						"Gde2WindowManager",
						&gde2_window_manager_info, 0);                
	}

	return gde2_window_manager_type;
}


void
gde2_window_manager_settings_changed (Gde2WindowManager *wm)
{
        g_signal_emit (wm, signals[SETTINGS_CHANGED], 0);
}

/* Helper functions for Gde2WMSettings */
Gde2WMSettings *
gde2_wm_settings_copy (Gde2WMSettings *settings)
{
        Gde2WMSettings *retval;

        g_return_val_if_fail (settings != NULL, NULL);

        retval = g_new (Gde2WMSettings, 1);
        *retval = *settings;

        if (retval->flags & GDE2_WM_SETTING_FONT)
                retval->font = g_strdup (retval->font);
        if (retval->flags & GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER)
                retval->mouse_move_modifier = g_strdup (retval->mouse_move_modifier);
        if (retval->flags & GDE2_WM_SETTING_THEME)
                retval->theme = g_strdup (retval->theme);

        return retval;
}

void
gde2_wm_settings_free (Gde2WMSettings *settings)
{
        g_return_if_fail (settings != NULL);

        if (settings->flags & GDE2_WM_SETTING_FONT)
                g_free ((void *) settings->font);
        if (settings->flags & GDE2_WM_SETTING_MOUSE_MOVE_MODIFIER)
                g_free ((void *) settings->mouse_move_modifier);
        if (settings->flags & GDE2_WM_SETTING_THEME)
                g_free ((void *)settings->theme);

        g_free (settings);
}

