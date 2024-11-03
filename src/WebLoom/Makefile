INCLUDES = -I. \
	    -I$(WEBLOOM_SPD) \
	    -I$(WEBLOOM_LIBMAGIC_INC)
LIBRARIES = -L$(WEBLOOM_LIBMAGIC_LIB) -lmagic

CPPFLAGS = -g -Wall $(INCLUDES) -std=c++17 -Wall -Wextra -fPIC

OBJS = Context.o          \
       Header.o           \
       HttpContentType.o  \
       Request.o          \
       Response.o         \
       RouteHandler.o     \
       core/FileServer.o  \
       core/HttpServer.o  \
       core/HttpStatus.o  \
       core/Logger.o      \
       core/Platform.o    \
       core/ServerBase.o

LIB_DIR = ../bin/
WEBLOOM_LIB = $(LIB_DIR)libWebLoom.so

$(WEBLOOM_LIB): $(OBJS)
	mkdir -p $(LIB_DIR)
	g++ -shared -o $@ $(OBJS) $(LIBRARIES)

all: $(WEBLOOM_LIB)

clean:
	$(RM) $(WEBLOOM_LIB) $(OBJS)
