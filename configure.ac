# Read package version from version.txt
m4_define([webloom_version], m4_esyscmd([cat version.txt | tr -d '\n']))

AC_INIT([WebLoom], [webloom_version], [WebLoom@invalid.invalid])

AC_CONFIG_MACRO_DIRS([m4])

# Enable Automake
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Initialize Libtool
LT_INIT

# Check for C++ compiler
AC_PROG_CXX

# Read libtool versioning from lib_version.txt and
# set libtool versioning
LT_VERSION=$(cat lib_version.txt | tr -d '\n')
AC_MSG_NOTICE([--- Libtool version: $LT_VERSION])
AC_SUBST(LT_VERSION)

# Check for libmagic
PKG_CHECK_MODULES([LIBMAGIC], [libmagic], [have_libmagic=yes], [have_libmagic=no])
AS_IF([test "x$have_libmagic" = "xyes"],
      [AC_SUBST(LIBMAGIC_CFLAGS, $LIBMAGIC_CFLAGS)]
      [AC_SUBST(LIBMAGIC_LIBS, $LIBMAGIC_LIBS)]
)

# Set include and library paths (use proper variable names)
AC_SUBST(AM_CPPFLAGS, "-I. -I\$(WEBLOOM_SPD) -I\$(WEBLOOM_LIBMAGIC_INC)")
AC_SUBST(LDADD, "-L\$(WEBLOOM_LIBMAGIC_LIB) -lmagic")

# Checks for header files
AC_CHECK_HEADERS([stdio.h stdlib.h])


# Output Makefile in root and subdirectories
AC_CONFIG_FILES([Makefile src/Makefile src/WebLoom/Makefile])

# Generate the configuration script
AC_OUTPUT
