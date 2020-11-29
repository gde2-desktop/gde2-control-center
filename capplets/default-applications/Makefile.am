# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = gde2-default-applications-properties

bin_PROGRAMS = gde2-default-applications-properties

gde2_default_applications_properties_LDADD = $(GDE2CC_CAPPLETS_LIBS)
gde2_default_applications_properties_SOURCES = \
	gde2-da-capplet.c gde2-da-capplet.h

@INTLTOOL_DESKTOP_RULE@

uidir = $(pkgdatadir)/ui
dist_ui_DATA = gde2-default-applications-properties.ui

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-default-applications-properties.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gde2-default-applications.pc

AM_CPPFLAGS = \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	$(DEFAULT_APPLICATIONS_CAPPLET_CFLAGS) \
	-DAPPLICATIONSDIR=\""$(datadir)/applications"\"\
	-DGDE2LOCALEDIR=\""$(datadir)/locale"\"\
	-DGDE2CC_UI_DIR=\""$(uidir)"\"

CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(Desktop_in_files) $(desktop_DATA) $(autostart_DATA)
EXTRA_DIST = gde2-default-applications.pc.in gde2-default-applications-properties.desktop.in.in

-include $(top_srcdir)/git.mk
