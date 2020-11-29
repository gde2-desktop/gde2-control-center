#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gde2-settings-client.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include "activate-settings-daemon.h"

static void popup_error_message (void)
{
  GtkWidget *dialog;

  dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING,
				   GTK_BUTTONS_OK, _("Unable to start the settings manager 'gde2-settings-daemon'.\n"
				   "Without the GDE2 settings manager running, some preferences may not take effect. This could "
				   "indicate a problem with DBus, or a non-GDE2 (e.g. KDE) settings manager may already "
				   "be active and conflicting with the GDE2 settings manager."));

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

/* Returns FALSE if activation failed, else TRUE */
gboolean 
activate_settings_daemon (void)
{
  DBusGConnection *connection = NULL;
  DBusGProxy *proxy = NULL;
  GError *error = NULL;

  connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if (connection == NULL)
    {
      popup_error_message ();
      g_error_free (error);
      return FALSE;
    }
    
  proxy = dbus_g_proxy_new_for_name (connection,
                                     "org.gde2.SettingsDaemon",
                                     "/org/gde2/SettingsDaemon",
                                     "org.gde2.SettingsDaemon");

  if (proxy == NULL)
    {
      popup_error_message ();
      return FALSE;
    }

  if (!org_gde2_SettingsDaemon_awake(proxy, &error))
    {
      popup_error_message ();
      g_error_free (error);
      return FALSE;
    }

  return TRUE;
}
