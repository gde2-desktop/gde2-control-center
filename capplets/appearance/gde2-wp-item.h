/*
 *  Authors: Rodney Dawes <dobey@ximian.com>
 *
 *  Copyright 2003-2006 Novell, Inc. (www.novell.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of version 2 of the GNU General Public License
 *  as published by the Free Software Foundation
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Street #330, Boston, MA 02110-1301, USA.
 *
 */

#include <glib.h>
#include <gio/gio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <libgde2-desktop/gde2-desktop-thumbnail.h>
#include <libgde2-desktop/gde2-bg.h>

#include "gde2-wp-info.h"

#ifndef _GDE2_WP_ITEM_H_
#define _GDE2_WP_ITEM_H_

typedef struct _Gde2WPItem Gde2WPItem;

struct _Gde2WPItem {
  Gde2BG *bg;

  gchar * name;
  gchar * filename;
  gchar * description;
  Gde2BGPlacement options;
  Gde2BGColorType shade_type;

  /* Where the Item is in the List */
  GtkTreeRowReference * rowref;

  /* Real colors */
#if GTK_CHECK_VERSION (3, 0, 0)
  GdkRGBA * pcolor;
  GdkRGBA * scolor;
#else
  GdkColor * pcolor;
  GdkColor * scolor;
#endif

  Gde2WPInfo * fileinfo;

  /* Did the user remove us? */
  gboolean deleted;

  /* Wallpaper author, if present */
  gchar *artist;

  /* Width and Height of the original image */
  gint width;
  gint height;
};

Gde2WPItem * gde2_wp_item_new (const gchar *filename,
				 GHashTable *wallpapers,
				 Gde2DesktopThumbnailFactory *thumbnails);

void gde2_wp_item_free (Gde2WPItem *item);
GdkPixbuf * gde2_wp_item_get_thumbnail (Gde2WPItem *item,
					 Gde2DesktopThumbnailFactory *thumbs,
                                         gint width,
                                         gint height);
GdkPixbuf * gde2_wp_item_get_frame_thumbnail (Gde2WPItem *item,
                                               Gde2DesktopThumbnailFactory *thumbs,
                                               gint width,
                                               gint height,
                                               gint frame);
void gde2_wp_item_update (Gde2WPItem *item);
void gde2_wp_item_update_description (Gde2WPItem *item);
void gde2_wp_item_ensure_gde2_bg (Gde2WPItem *item);

const gchar *wp_item_option_to_string (Gde2BGPlacement type);
const gchar *wp_item_shading_to_string (Gde2BGColorType type);
Gde2BGPlacement wp_item_string_to_option (const gchar *option);
Gde2BGColorType wp_item_string_to_shading (const gchar *shade_type);

#endif
