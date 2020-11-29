REAL_LIBSLAB_CFLAGS = -I$(top_srcdir)/libslab
REAL_LIBSLAB_LIBS = $(top_builddir)/libslab/libgde2-slab.la

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	$(REAL_LIBSLAB_CFLAGS)		\
	$(GDE2CC_SHELL_CFLAGS)  	\
	-DGDE2LOCALEDIR="\"$(datadir)/locale\""

bin_PROGRAMS = gde2-control-center 

gde2_control_center_SOURCES =		\
	control-center.c

gde2_control_center_LDADD =						\
	$(GDE2CC_SHELL_LIBS)						\
	$(REAL_LIBSLAB_LIBS)

sysdir = $(datadir)/applications
sys_in_files = gde2cc.desktop.in
sys_DATA = $(sys_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

directorydir = $(datadir)/desktop-directories
directory_in_files = gde2cc.directory.in
directory_DATA = $(directory_in_files:.directory.in=.directory)
@INTLTOOL_DIRECTORY_RULE@

menudir = $(sysconfdir)/xdg/menus
menu_DATA = gde2cc.menu

EXTRA_DIST = gde2cc.desktop.in.in gde2cc.directory.in gde2cc.menu

DISTCLEANFILES = gde2cc.desktop gde2cc.desktop.in gde2cc.directory

-include $(top_srcdir)/git.mk
