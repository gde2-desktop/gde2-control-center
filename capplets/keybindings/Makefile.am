# This is used in GDE2CC_CAPPLETS_CFLAGS
cappletname = keybinding

bin_PROGRAMS = gde2-keybinding-properties

gde2_keybinding_properties_LDADD = $(GDE2CC_CAPPLETS_LIBS)
gde2_keybinding_properties_SOURCES = \
	gde2-keybinding-properties.c \
	eggcellrendererkeys.c \
	eggcellrendererkeys.h \
	eggaccelerators.c \
	eggaccelerators.h

@INTLTOOL_DESKTOP_RULE@

uidir = $(pkgdatadir)/ui
ui_DATA = gde2-keybinding-properties.ui

desktopdir = $(datadir)/applications
Desktop_in_files = gde2-keybinding.desktop.in
desktop_DATA = $(Desktop_in_files:.desktop.in=.desktop)

@INTLTOOL_XML_NOMERGE_RULE@

xmldir = $(pkgdatadir)/keybindings
xml_in_files = 00-multimedia-key.xml.in 01-desktop-key.xml.in
xml_DATA = $(xml_in_files:.xml.in=.xml)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gde2-keybindings.pc

AM_CPPFLAGS = \
	$(GDE2CC_CAPPLETS_CFLAGS) \
	-DGDE2LOCALEDIR="\"$(datadir)/locale\"" \
	-DGDE2CC_DATA_DIR="\"$(pkgdatadir)\"" \
	-DGDE2CC_UI_DIR="\"$(uidir)\"" \
	-DGDE2CC_KEYBINDINGS_DIR="\"$(pkgdatadir)/keybindings\""
CLEANFILES = \
	$(GDE2CC_CAPPLETS_CLEANFILES) \
	$(Desktop_in_files) \
	$(desktop_DATA) \
	$(xml_DATA)
EXTRA_DIST = $(ui_DATA) $(xml_in_files) gde2-keybindings.pc.in


-include $(top_srcdir)/git.mk
