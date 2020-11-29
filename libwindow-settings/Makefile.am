WM_MODULE_DIR=$(libdir)/window-manager-settings

AM_CPPFLAGS = 								\
	-DGDE2LOCALEDIR="\"$(datadir)/locale\""			\
	-DGDE2_ICONDIR=\""$(datadir)/pixmaps"\"			\
	-DG_LOG_DOMAIN=\"capplet-common\"				\
	-DGDE2_WM_PROPERTY_PATH=\"$(datadir)/gde2/wm-properties\"	\
	-DGDE2_WINDOW_MANAGER_MODULE_PATH=\""$(WM_MODULE_DIR)"\"	\
	-I$(top_srcdir)/						\
	@CAPPLET_CFLAGS@						\
	-DMARCO_THEME_DIR=\""$(datadir)/themes"\"

lib_LTLIBRARIES = libgde2-window-settings.la

libgde2_window_settings_la_LDFLAGS = 	\
	-export_dynamic			\
	-no-undefined			\
        -version-info 1:0:0

libgde2_window_settings_la_LIBADD = $(GDE2CC_LIBS)

libgde2_window_settings_la_SOURCES = \
	gde2-window-manager.c	\
	gde2-window-manager.h	\
	gde2-wm-manager.c	\
	gde2-wm-manager.h

libgde2_window_settingsincludedir = $(includedir)/gde2-window-settings-2.0

libgde2_window_settingsinclude_HEADERS =	\
	gde2-window-manager.h			\
	gde2-wm-manager.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gde2-window-settings-2.0.pc

EXTRA_DIST = 					\
	gde2-window-settings-2.0.pc.in

wms_flags = -export_dynamic -avoid-version -module
wmsdir = $(WM_MODULE_DIR)

wms_LTLIBRARIES =			\
	libmarco.la

libmarco_la_SOURCES = 		\
	marco-window-manager.c	\
	marco-window-manager.h

libmarco_la_LDFLAGS = $(wms_flags)
libmarco_la_LIBADD = 		\
	$(GDE2CC_LIBS)			\
	libgde2-window-settings.la

-include $(top_srcdir)/git.mk
