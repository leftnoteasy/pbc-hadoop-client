#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hdclient], [0.1], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([hadoop_rpc.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

LT_INIT

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lhdclient':
AC_CHECK_LIB([hdclient]) 
# FIXME: Replace `main' with a function in `-lpbc':
AC_CHECK_LIB([pbc])

# Checks for header files.
AC_CHECK_HEADERS([netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero gethostbyname socket strdup])

AC_CONFIG_FILES([Makefile test/Makefile])
AC_CONFIG_SUBDIRS([ext/pbc])
AC_OUTPUT
