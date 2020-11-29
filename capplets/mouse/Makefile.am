# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = mouse

bin_PROGRAMS = gde2-mouse-properties

gde2_mouse_properties_LDADD = $(GDE2CC_CAPPLETS_LIBS)
gde2_mouse_properties_SOURCES =	\
	gde2-mouse-properties.c

@INTLTOOL_DESKTOP_RULE@

pixmapdir  = $(pkgdatadir)/pixmaps
pixmap_DATA = \
	double-click-on.png		\
	double-click-off.png		\
	double-click-maybe.png

uidir   = $(pkgdatadir)/ui
ui_DATA = gde2-mouse-properties.ui

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-settings-mouse.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

AM_CPPFLAGS = \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	-DGDE2LOCALEDIR="\"$(datadir)/locale\"" \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	-DGDE2CC_UI_DIR="\"$(uidir)\""
CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(Desktop_in_files) $(desktop_DATA)
EXTRA_DIST = $(ui_DATA) $(pixmap_DATA)

-include $(top_srcdir)/git.mk
