#ifndef __THEME_THUMBNAIL_H__
#define __THEME_THUMBNAIL_H__


#include <gtk/gtk.h>
#include "gde2-theme-info.h"

typedef void (* ThemeThumbnailFunc)          (GdkPixbuf          *pixbuf,
                                              gchar              *theme_name,
                                              gpointer            data);

GdkPixbuf *generate_meta_theme_thumbnail     (Gde2ThemeMetaInfo *theme_info);
GdkPixbuf *generate_gtk_theme_thumbnail      (Gde2ThemeInfo     *theme_info);
GdkPixbuf *generate_finestra_theme_thumbnail (Gde2ThemeInfo     *theme_info);
GdkPixbuf *generate_icon_theme_thumbnail     (Gde2ThemeIconInfo *theme_info);

void generate_meta_theme_thumbnail_async     (Gde2ThemeMetaInfo *theme_info,
                                              ThemeThumbnailFunc  func,
                                              gpointer            data,
                                              GDestroyNotify      destroy);
void generate_gtk_theme_thumbnail_async      (Gde2ThemeInfo     *theme_info,
                                              ThemeThumbnailFunc  func,
                                              gpointer            data,
                                              GDestroyNotify      destroy);
void generate_finestra_theme_thumbnail_async (Gde2ThemeInfo     *theme_info,
                                              ThemeThumbnailFunc  func,
                                              gpointer            data,
                                              GDestroyNotify      destroy);
void generate_icon_theme_thumbnail_async     (Gde2ThemeIconInfo *theme_info,
                                              ThemeThumbnailFunc  func,
                                              gpointer            data,
                                              GDestroyNotify      destroy);

void theme_thumbnail_factory_init            (int                 argc,
                                              char               *argv[]);

#endif /* __THEME_THUMBNAIL_H__ */
