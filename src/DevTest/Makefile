INCLUDES = -I. \
	   -I../WebLoom

CPPFLAGS = -g -Wall $(INCLUDES) -std=c++17 -Wall -Wextra
LIBS = -L../bin -lWebLoom -lpthread

OBJS = TestWebserver.o

LIB_DIR = ../bin/
BINARY = $(LIB_DIR)dev_test

$(BINARY): $(OBJS)
	g++ -o $(BINARY) $(INCLUDES) $(OBJS) $(LIBS)

all: $(BINARY)

clean:
	$(RM) $(BINARY) $(OBJS)
