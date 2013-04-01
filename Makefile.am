SUBDIRS = ext/pbc . test

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = \
	libhdclient.la 

hdclientincludedir = $(includedir)/src

hdclientinclude_HEADERS = \
	hadoop_rpc.h

libhdclient_la_SOURCES = \
	src/client_rm_protocol_impl.c \
	src/hadoop_rpc.c \
	src/hadoop_rpc_utils.c \
	src/net_utils.c \
	src/pbc_utils.c \
	src/str_utils.c
