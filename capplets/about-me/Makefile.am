SUBDIRS = icons

# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = about-me

ui_files = gde2-about-me-dialog.ui gde2-about-me-password.ui gde2-about-me-fingerprint.ui
Desktop_in_files = gde2-about-me.desktop.in

gde2_about_me_SOURCES =	 	\
	eel-alert-dialog.c		\
	eel-alert-dialog.h		\
	eel-gtk-macros.h		\
	gde2-about-me-password.c	\
	gde2-about-me-password.h	\
	e-image-chooser.c		\
	e-image-chooser.h		\
	gde2-about-me-fingerprint.c	\
	gde2-about-me-fingerprint.h	\
	$(MARSHALFILES)			\
	fingerprint-strings.h		\
	gde2-about-me.c

MARSHALFILES = marshal.c marshal.h
BUILT_SOURCES = $(MARSHALFILES)

marshal.h: fprintd-marshal.list
	@GLIB_GENMARSHAL@ --prefix=fprintd_marshal $< --header > $@
marshal.c: fprintd-marshal.list
	@GLIB_GENMARSHAL@ --prefix=fprintd_marshal $< --body --header > $@

bin_PROGRAMS = gde2-about-me

gde2_about_me_LDADD = $(GDE2CC_CAPPLETS_LIBS)
gde2_about_me_LDFLAGS = -export-dynamic

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

uidir   = $(pkgdatadir)/ui
ui_DATA = $(ui_files)

AM_CPPFLAGS = \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	$(LIBEBOOK_CFLAGS) \
	-DDATADIR="\"$(datadir)\"" \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	-DGDE2CC_UI_DIR="\"$(uidir)\"" \
	-DGDE2CC_PIXMAP_DIR="\"$(pkgdatadir)/pixmaps\"" \
	-DGDE2LOCALEDIR="\"$(datadir)/locale\""

CLEANFILES = $(GDE2CC_CAPPLETS_CLEANFILES) $(desktop_DATA) $(MARSHALFILES)
EXTRA_DIST = $(ui_files) fprintd-marshal.list

-include $(top_srcdir)/git.mk
