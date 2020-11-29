
AM_CPPFLAGS = $(FONT_VIEWER_CFLAGS) $(GDE2CC_CAPPLETS_CFLAGS) -DDIRECTORY_DIR=\"$(directorydir)\" \
  -DGDE2LOCALEDIR=\"$(datadir)/locale\"

bin_PROGRAMS = gde2-thumbnail-font gde2-font-viewer

gde2_thumbnail_font_LDADD = $(GDE2CC_CAPPLETS_LIBS) $(FONT_VIEWER_LIBS)
gde2_thumbnail_font_SOURCES = ftstream-vfs.c ftstream-vfs.h font-thumbnailer.c totem-resources.c totem-resources.h

gde2_font_viewer_LDADD = $(GDE2CC_CAPPLETS_LIBS) $(FONT_VIEWER_LIBS)
gde2_font_viewer_SOURCES = ftstream-vfs.c ftstream-vfs.h font-view.c

thumbnailerdir = $(datadir)/thumbnailers
thumbnailer_DATA = gde2-font-viewer.thumbnailer

desktopdir = $(datadir)/applications
desktop_in_files = gde2-font-viewer.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

install-data-local: install-desktop-database

install-desktop-database: install-desktopDATA
	update-desktop-database $(DESTDIR)$(desktopdir)

uninstall-local:
	rm -f $(DESTDIR)$(desktopdir)/mimeinfo.cache

@INTLTOOL_DESKTOP_RULE@
@INTLTOOL_DIRECTORY_RULE@
@INTLTOOL_SCHEMAS_RULE@

CLEANFILES = $(desktop_in_files) $(desktop_DATA) \
  $(schemas_DATA) $(directory_DATA)

EXTRA_DIST = \
  $(thumbnailer_DATA) \
  gde2-font-viewer.desktop.in.in

-include $(top_srcdir)/git.mk
