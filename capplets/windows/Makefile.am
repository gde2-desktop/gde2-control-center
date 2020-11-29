# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = window

bin_PROGRAMS = gde2-window-properties

gde2_window_properties_LDADD = $(GDE2CC_CAPPLETS_LIBS)

gde2_window_properties_SOURCES = \
	gde2-metacity-support.h \
	gde2-metacity-support.c \
	gde2-window-properties.c

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-window-properties.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

AM_CPPFLAGS   = $(GDE2CC_CAPPLETS_CFLAGS)					\
	     -DUIDIR=\""$(uidir)"\"  	\
	     -DGDE2LOCALEDIR="\"$(datadir)/locale\""			\
	     -DPIXMAPDIR=\""$(pixmapdir)"\"

CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(Desktop_in_files) $(desktop_DATA)

-include $(top_srcdir)/git.mk
