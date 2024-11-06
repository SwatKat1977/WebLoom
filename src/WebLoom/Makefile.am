# src/WebLoom/Makefile.am

# Compiler and linker flags
AM_CPPFLAGS = -g -std=c++17 -Wall -Wextra -fPIC \
              -I. \
              -I$(WEBLOOM_SPD) \
              -I$(WEBLOOM_LIBMAGIC_INC)

# Install header files
nobase_include_HEADERS = Context.h \
                  Header.h \
                  HttpContentType.h \
                  Request.h \
                  RequestMethod.h \
                  Response.h \
                  RouteHandler.h \
                  SocketDefinitions.h \
                  WebLoomSettings.h \
                  core/FileServer.h \
                  core/HttpServer.h \
                  core/HttpStatus.h \
                  core/IServer.h \
                  core/Logger.h \
                  core/LoggerSettings.h \
                  core/Platform.h \
                  core/ServerBase.h \
                  core/ThreadPool.h

# Install headers into $(prefix)/WebLoom
includedir = $(prefix)/include/WebLoom

# Specify that headers in `core` should be installed in a `core` subdirectory
coredir = $(includedir)/core

# Specify sources and output shared library
lib_LTLIBRARIES = libWebLoom.la
libWebLoom_la_SOURCES = Context.cpp \
                        Header.cpp \
                        HttpContentType.cpp \
                        Request.cpp \
                        Response.cpp \
                        RouteHandler.cpp \
                        core/FileServer.cpp \
                        core/HttpServer.cpp \
                        core/HttpStatus.cpp \
                        core/Logger.cpp \
                        core/Platform.cpp \
                        core/ServerBase.cpp

# Set the libtool versioning
libWebLoom_la_LDFLAGS = -version-info $(LT_VERSION)

# Specify libraries
libWebLoom_la_LIBADD = $(LDADD)

CLEANFILES = $(lib_LTLIBRARIES)

