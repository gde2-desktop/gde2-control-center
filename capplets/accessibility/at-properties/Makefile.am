bin_PROGRAMS = gde2-at-properties

gde2_at_properties_LDADD = $(AT_CAPPLET_LIBS) $(GDE2CC_CAPPLETS_LIBS) $(top_builddir)/capplets/common/libcommon.la
gde2_at_properties_SOURCES = \
	main.c
gde2_at_properties_LDFLAGS = -export-dynamic

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-at-properties.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

pixmapdir  = $(pkgdatadir)/pixmaps
pixmap_DATA =					\
	at-startup.png				\
	at-support.png

uidir = $(pkgdatadir)/ui
ui_DATA = at-enable-dialog.ui

AM_CPPFLAGS   = $(AT_CAPPLET_CFLAGS)     \
             $(GDE2CC_CAPPLETS_CFLAGS) \
	     -DUIDIR=\""$(uidir)"\" \
	     -DPIXMAPDIR=\""$(pixmapdir)"\" \
	     -DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	     -DGDE2LOCALEDIR="\"$(datadir)/locale\""
CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(Desktop_in_files) $(desktop_DATA)
EXTRA_DIST = $(ui_DATA) $(pixmap_DATA)

-include $(top_srcdir)/git.mk
