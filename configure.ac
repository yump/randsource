#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([randsource],
		[1.0],
		[https://github.com/yump/randsource/issues])
AC_CONFIG_SRCDIR([src/randsource.c])
AC_CONFIG_HEADERS([config.h])

# Dirs
AC_CONFIG_AUX_DIR([build-aux])

# Checks for programs.
AC_PROG_CC_STDC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([clock_gettime])

# Automake
AM_INIT_AUTOMAKE([foreign dist-xz subdir-objects -Wall -Werror])
AM_PROG_CC_C_O

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
