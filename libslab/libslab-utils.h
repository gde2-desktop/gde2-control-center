#ifndef __LIBSLAB_UTILS_H__
#define __LIBSLAB_UTILS_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <libgde2-desktop/gde2-desktop-item.h>
#define GDE2_DESKTOP_USE_UNSTABLE_API 1
#include <libgde2-desktop/gde2-desktop-thumbnail.h>

#ifdef __cplusplus
extern "C" {
#endif

gboolean          libslab_gtk_image_set_by_id (GtkImage *image, const gchar *id);
Gde2DesktopItem *libslab_gde2_desktop_item_new_from_unknown_id (const gchar *id);
gboolean          libslab_gde2_desktop_item_launch_default (Gde2DesktopItem *item);
gchar            *libslab_gde2_desktop_item_get_docpath (Gde2DesktopItem *item);
gboolean          libslab_gde2_desktop_item_open_help (Gde2DesktopItem *item);
guint32           libslab_get_current_time_millis (void);
gint              libslab_strcmp (const gchar *a, const gchar *b);
gint              libslab_strlen (const gchar *a);
void              libslab_handle_g_error (GError **error, const gchar *msg_format, ...);
gboolean          libslab_desktop_item_is_a_terminal (const gchar *uri);
gboolean          libslab_desktop_item_is_logout (const gchar *uri);
gboolean          libslab_desktop_item_is_lockscreen (const gchar *uri);
gchar            *libslab_string_replace_once (const gchar *string, const gchar *key, const gchar *value);
void              libslab_spawn_command (const gchar *cmd);

GdkScreen *libslab_get_current_screen (void);

void libslab_thumbnail_factory_preinit (void);
Gde2DesktopThumbnailFactory *libslab_thumbnail_factory_get (void);

void libslab_checkpoint_init (const char *checkpoint_config_file_basename, const char *checkpoint_file_basename);
void libslab_checkpoint (const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
