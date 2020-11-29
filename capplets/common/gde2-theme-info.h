/* gde2-theme-info.h - GDE2 Theme information

   Copyright (C) 2002 Jonathan Blandford <jrb@gnome.org>
   All rights reserved.

   This file is part of the Gde2 Library.

   The Gde2 Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gde2 Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gde2 Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#ifndef GDE2_THEME_INFO_H
#define GDE2_THEME_INFO_H

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdk.h>

typedef enum {
	GDE2_THEME_TYPE_METATHEME,
	GDE2_THEME_TYPE_ICON,
	GDE2_THEME_TYPE_CURSOR,
	GDE2_THEME_TYPE_REGULAR
} Gde2ThemeType;

typedef enum {
	GDE2_THEME_CHANGE_CREATED,
	GDE2_THEME_CHANGE_DELETED,
	GDE2_THEME_CHANGE_CHANGED
} Gde2ThemeChangeType;

typedef enum {
	GDE2_THEME_MARCO = 1 << 0,
	GDE2_THEME_GTK_2 = 1 << 1,
	GDE2_THEME_GTK_2_KEYBINDING = 1 << 2
} Gde2ThemeElement;

typedef struct _Gde2ThemeCommonInfo Gde2ThemeCommonInfo;
typedef struct _Gde2ThemeCommonInfo Gde2ThemeIconInfo;
struct _Gde2ThemeCommonInfo
{
	Gde2ThemeType type;
	gchar* path;
	gchar* name;
	gchar* readable_name;
	gint priority;
	gboolean hidden;
};

typedef struct _Gde2ThemeInfo Gde2ThemeInfo;
struct _Gde2ThemeInfo
{
	Gde2ThemeType type;
	gchar* path;
	gchar* name;
	gchar* readable_name;
	gint priority;
	gboolean hidden;

	guint has_gtk : 1;
	guint has_keybinding : 1;
	guint has_marco : 1;
};

typedef struct _Gde2ThemeCursorInfo Gde2ThemeCursorInfo;
struct _Gde2ThemeCursorInfo {
	Gde2ThemeType type;
	gchar* path;
	gchar* name;
	gchar* readable_name;
	gint priority;
	gboolean hidden;

	GArray* sizes;
	GdkPixbuf* thumbnail;
};

typedef struct _Gde2ThemeMetaInfo Gde2ThemeMetaInfo;
struct _Gde2ThemeMetaInfo {
	Gde2ThemeType type;
	gchar* path;
	gchar* name;
	gchar* readable_name;
	gint priority;
	gboolean hidden;

	gchar* comment;
	gchar* icon_file;

	gchar* gtk_theme_name;
	gchar* gtk_color_scheme;
	gchar* marco_theme_name;
	gchar* icon_theme_name;
	gchar* notification_theme_name;
	gchar* sound_theme_name;
	gchar* cursor_theme_name;
	guint cursor_size;

	gchar* application_font;
	gchar* documents_font;
	gchar* desktop_font;
	gchar* windowtitle_font;
	gchar* monospace_font;
	gchar* background_image;
};

enum {
	COLOR_FG,
	COLOR_BG,
	COLOR_TEXT,
	COLOR_BASE,
	COLOR_SELECTED_FG,
	COLOR_SELECTED_BG,
	COLOR_TOOLTIP_FG,
	COLOR_TOOLTIP_BG,
	NUM_SYMBOLIC_COLORS
};

typedef void (*ThemeChangedCallback) (Gde2ThemeCommonInfo* theme, Gde2ThemeChangeType change_type, Gde2ThemeElement element_type, gpointer user_data);

#define GDE2_THEME_ERROR gde2_theme_info_error_quark()

enum {
	GDE2_THEME_ERROR_GTK_THEME_NOT_AVAILABLE = 1,
	GDE2_THEME_ERROR_WM_THEME_NOT_AVAILABLE,
	GDE2_THEME_ERROR_ICON_THEME_NOT_AVAILABLE,
	GDE2_THEME_ERROR_GTK_ENGINE_NOT_AVAILABLE,
	GDE2_THEME_ERROR_UNKNOWN
};


/* GTK/Marco/keybinding Themes */
Gde2ThemeInfo     *gde2_theme_info_new                   (void);
void                gde2_theme_info_free                  (Gde2ThemeInfo     *theme_info);
Gde2ThemeInfo     *gde2_theme_info_find                  (const gchar        *theme_name);
GList              *gde2_theme_info_find_by_type          (guint               elements);
GQuark              gde2_theme_info_error_quark           (void);
gchar              *gtk_theme_info_missing_engine          (const gchar *gtk_theme,
                                                            gboolean nameOnly);

/* Icon Themes */
Gde2ThemeIconInfo *gde2_theme_icon_info_new              (void);
void                gde2_theme_icon_info_free             (Gde2ThemeIconInfo *icon_theme_info);
Gde2ThemeIconInfo *gde2_theme_icon_info_find             (const gchar        *icon_theme_name);
GList              *gde2_theme_icon_info_find_all         (void);
gint                gde2_theme_icon_info_compare          (Gde2ThemeIconInfo *a,
							    Gde2ThemeIconInfo *b);

/* Cursor Themes */
Gde2ThemeCursorInfo *gde2_theme_cursor_info_new	   (void);
void                  gde2_theme_cursor_info_free	   (Gde2ThemeCursorInfo *info);
Gde2ThemeCursorInfo *gde2_theme_cursor_info_find	   (const gchar          *name);
GList                *gde2_theme_cursor_info_find_all	   (void);
gint                  gde2_theme_cursor_info_compare      (Gde2ThemeCursorInfo *a,
							    Gde2ThemeCursorInfo *b);

/* Meta themes*/
Gde2ThemeMetaInfo *gde2_theme_meta_info_new              (void);
void                gde2_theme_meta_info_free             (Gde2ThemeMetaInfo *meta_theme_info);
Gde2ThemeMetaInfo *gde2_theme_meta_info_find             (const gchar        *meta_theme_name);
GList              *gde2_theme_meta_info_find_all         (void);
gint                gde2_theme_meta_info_compare          (Gde2ThemeMetaInfo *a,
							    Gde2ThemeMetaInfo *b);
gboolean            gde2_theme_meta_info_validate         (const Gde2ThemeMetaInfo *info,
                                                            GError            **error);
Gde2ThemeMetaInfo *gde2_theme_read_meta_theme            (GFile              *meta_theme_uri);

/* Other */
void                gde2_theme_init                       (void);
void                gde2_theme_info_register_theme_change (ThemeChangedCallback func,
							    gpointer             data);

#if GTK_CHECK_VERSION (3, 0, 0)
gboolean            gde2_theme_color_scheme_parse         (const gchar         *scheme,
							    GdkRGBA             *colors);
#else
gboolean            gde2_theme_color_scheme_parse         (const gchar         *scheme,
							    GdkColor            *colors);
#endif
gboolean            gde2_theme_color_scheme_equal         (const gchar         *s1,
							    const gchar         *s2);

#endif /* GDE2_THEME_INFO_H */
