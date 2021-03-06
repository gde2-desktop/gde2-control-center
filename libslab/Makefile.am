pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gde2-slab.pc

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	$(LIBSLAB_CFLAGS)			\
	$(WARN_CFLAGS)

HEADER_FILES=					\
	$(BUILT_SOURCES)			\
	app-resizer.h				\
	app-shell.h				\
	application-tile.h			\
	bookmark-agent.h			\
	directory-tile.h			\
	document-tile.h				\
	double-click-detector.h			\
	gde2-utils.h				\
	libslab-utils.h				\
	nameplate-tile.h			\
	search-bar.h				\
	search-context-picker.h			\
	search-entry.h				\
	shell-window.h				\
	slab-gde2-util.h			\
	slab-section.h				\
	slab.h					\
	system-tile.h				\
	tile.h

lib_LTLIBRARIES = libgde2-slab.la

libgde2_slab_la_SOURCES =			\
	$(MARSHAL_GENERATED)			\
	app-resizer.c				\
	app-shell.c				\
	application-tile.c			\
	bookmark-agent.c			\
	directory-tile.c			\
	document-tile.c				\
	double-click-detector.c			\
	gde2-utils.c				\
	libslab-utils.c				\
	nameplate-tile.c			\
	search-bar.c				\
	search-context-picker.c			\
	search-entry-watermark.h		\
	search-entry.c				\
	shell-window.c				\
	slab-gde2-util.c			\
	slab-section.c				\
	system-tile.c				\
	themed-icon.c				\
	themed-icon.h				\
	tile-action.c				\
	tile.c

libgde2_slab_includedir = $(includedir)/libgde2-slab
libgde2_slab_include_HEADERS = $(HEADER_FILES)
libgde2_slab_la_LIBADD = $(LIBSLAB_LIBS)

search-entry-watermark.h: search-entry-watermark.svg
	echo '#define SEARCH_ENTRY_WATERMARK_SVG "\' > $@; \
	sed -e 's/"/\\"/g' -e 's/$$/\\/' -e 's/#000000/#%s/g' $< >> $@; \
	echo '"' >> $@


MARSHAL_GENERATED = nld-marshal.c nld-marshal.h

nld-marshal.h: nld-marshal.list
	( @GLIB_GENMARSHAL@ --prefix=nld_marshal $(srcdir)/nld-marshal.list --header > nld-marshal.tmp \
	&& mv nld-marshal.tmp nld-marshal.h ) \
	|| ( rm -f nld-marshal.tmp && exit 1 )

nld-marshal.c: nld-marshal.h
	( (echo '#include "nld-marshal.h"'; @GLIB_GENMARSHAL@ --prefix=nld_marshal $(srcdir)/nld-marshal.list --body) > nld-marshal.tmp \
	&& mv nld-marshal.tmp nld-marshal.c ) \
	|| ( rm -f nld-marshal.tmp && exit 1 )


BUILT_SOURCES =				\
	search-entry-watermark.h	\
	$(MARSHAL_GENERATED)

CLEANFILES =				\
	search-entry-watermark.h	\
	$(MARSHAL_GENERATED)

EXTRA_DIST=				\
	search-entry-watermark.svg	\
	nld-marshal.list

-include $(top_srcdir)/git.mk
