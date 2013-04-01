ACLOCAL_AMFLAGS = -I m4

noinst_bin_PROGRAMS=\
	error_msg_response \
	hadoop_rpc_request \
	new_application_test \
	pbc_register_all \
	yarn_type

noinst_bindir=./

AM_CFLAGS="-I../src"
LDADD = ../ext/pbc/libpbc.la ../libhdclient.la

error_msg_response_SOURCES = error_msg_response.c

hadoop_rpc_request_SOURCES = hadoop_rpc_request.c

new_application_test_SOURCES = new_application_test.c

pbc_register_all_SOURCES = pbc_register_all.c

yarn_type_SOURCES = yarn_type.c
