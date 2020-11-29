EXTRA_DIST =

AM_CPPFLAGS = \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\""				\
	-DGDE2LOCALEDIR="\"$(datadir)/locale\""			\
	-DGTK_ENGINE_DIR="\"$(GTK_ENGINE_DIR)\"" 			\
	-DG_LOG_DOMAIN=\"capplet-common\"				\
	-DINSTALL_PREFIX=\"$(prefix)\"					\
	-I$(top_srcdir)							\
	-I$(top_srcdir)/libwindow-settings				\
	-DPIXMAP_DIR=\""$(datadir)/gde2-control-center/pixmaps"\"	\
	$(CAPPLET_CFLAGS)						\
	$(DBUS_CFLAGS)							\
	$(GDE2_DESKTOP_CFLAGS)						\
	$(MARCO_CFLAGS)						\
	$(GSD_DBUS_CFLAGS)						\
	$(GIO_CFLAGS)						\
	$(DCONF_CFLAGS)


noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = \
	activate-settings-daemon.c	\
	activate-settings-daemon.h	\
	capplet-stock-icons.c		\
	capplet-stock-icons.h		\
	capplet-util.c			\
	capplet-util.h			\
	dconf-util.c				\
	dconf-util.h				\
	file-transfer-dialog.c		\
	file-transfer-dialog.h		\
	gde2-theme-apply.c		\
	gde2-theme-apply.h 		\
	gde2-theme-info.c		\
	gde2-theme-info.h		\
	gtkrc-utils.c			\
	gtkrc-utils.h			\
	theme-thumbnail.c		\
	theme-thumbnail.h		\
	wm-common.c			\
	wm-common.h

libcommon_la_LIBADD =							\
	$(top_builddir)/libwindow-settings/libgde2-window-settings.la  \
	$(MARCO_LIBS)						\
	$(DBUS_LIBS)							\
	$(GDE2_DESKTOP_LIBS)						\
	$(GIO_LIBS)									\
	$(DCONF_LIBS)

gde2_theme_test_SOURCES = \
	gde2-theme-test.c

gde2_theme_test_LDADD = 						\
	libcommon.la							\
	$(GDE2CC_CAPPLETS_LIBS)						\
	$(GDE2CC_LIBS)

noinst_PROGRAMS = \
	gde2-theme-test

-include $(top_srcdir)/git.mk
