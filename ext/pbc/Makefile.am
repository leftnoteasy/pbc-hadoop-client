SUBDIRS = . test

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = \
	libpbc.la 

pbcincludedir = $(includedir)/src

nobase_pbcinclude_HEADERS = \
	pbc.h

libpbc_la_SOURCES = \
	src/alloc.c \
	src/array.c \
	src/bootstrap.c \
	src/context.c \
	src/decode.c \
	src/map.c \
	src/pattern.c \
	src/proto.c \
	src/register.c \
	src/rmessage.c \
	src/stringpool.c \
	src/varint.c \
	src/wmessage.c 

