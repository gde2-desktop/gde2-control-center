# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = keyboard

bin_PROGRAMS = gde2-keyboard-properties

gde2_keyboard_properties_SOURCES = \
	gde2-keyboard-properties.c \
	gde2-keyboard-properties-a11y.c \
	gde2-keyboard-properties-a11y.h \
	gde2-keyboard-properties-xkb.c \
	gde2-keyboard-properties-xkbmc.c \
	gde2-keyboard-properties-xkblt.c \
	gde2-keyboard-properties-xkbltadd.c \
	gde2-keyboard-properties-xkbot.c \
	gde2-keyboard-properties-xkbpv.c \
	gde2-keyboard-properties-xkb.h

gde2_keyboard_properties_LDADD = $(GDE2CC_CAPPLETS_LIBS) $(LIBGDE2KBDUI_LIBS)

@INTLTOOL_DESKTOP_RULE@

uidir   = $(pkgdatadir)/ui
dist_ui_DATA = gde2-keyboard-properties-a11y-notifications.ui \
               gde2-keyboard-properties-dialog.ui \
               gde2-keyboard-properties-layout-chooser.ui \
               gde2-keyboard-properties-model-chooser.ui \
               gde2-keyboard-properties-options-dialog.ui

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-keyboard.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

AM_CPPFLAGS = \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	$(LIBGDE2KBDUI_CFLAGS) \
	-DGDE2LOCALEDIR="\"$(datadir)/locale\"" \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	-DGDE2CC_UI_DIR="\"$(uidir)\""
CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(Desktop_in_files) $(desktop_DATA)
EXTRA_DIST = $(ui_DATA)

-include $(top_srcdir)/git.mk
