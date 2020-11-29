SUBDIRS = data

# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = appearance

bin_PROGRAMS = gde2-appearance-properties

gde2_appearance_properties_SOURCES = \
	appearance.h \
	appearance-desktop.c \
	appearance-desktop.h \
	appearance-font.c \
	appearance-font.h \
	appearance-main.c \
	appearance-themes.c \
	appearance-themes.h \
	appearance-style.c \
	appearance-style.h \
	appearance-ui.c \
	appearance-ui.h \
	appearance-support.c \
	appearance-support.h \
	gde2-wp-info.c \
	gde2-wp-info.h \
	gde2-wp-item.c \
	gde2-wp-item.h \
	gde2-wp-xml.c \
	gde2-wp-xml.h \
	theme-installer.c \
	theme-installer.h \
	theme-save.c \
	theme-save.h \
	theme-util.c \
	theme-util.h

AM_CFLAGS = -DGDE2_DESKTOP_USE_UNSTABLE_API

gde2_appearance_properties_LDADD = \
	$(top_builddir)/libwindow-settings/libgde2-window-settings.la \
	$(top_builddir)/capplets/common/libcommon.la \
	$(GDE2CC_CAPPLETS_LIBS) \
	$(FONT_CAPPLET_LIBS) \
	$(MARCO_LIBS)
gde2_appearance_properties_LDFLAGS = -export-dynamic

gtkbuilderdir = $(pkgdatadir)/ui
pixmapdir = $(pkgdatadir)/pixmaps
wallpaperdir = $(datadir)/gde2-background-properties

AM_CPPFLAGS = \
	$(MARCO_CFLAGS) \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	$(FONT_CAPPLET_CFLAGS) \
	-DGDE2LOCALEDIR="\"$(datadir)/locale\"" \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	-DGDE2CC_GTKBUILDER_DIR="\"$(gtkbuilderdir)\"" \
	-DGDE2CC_PIXMAP_DIR="\"$(pixmapdir)\"" \
	-DWALLPAPER_DATADIR="\"$(wallpaperdir)\""

CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES)

-include $(top_srcdir)/git.mk
