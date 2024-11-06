INCLUDES = -I. \
	   -I/usr/local/include/WebLoom

CPPFLAGS = -g -Wall $(INCLUDES) -std=c++17 -Wall -Wextra
LIBS = -lWebLoom -lpthread

OBJS = TestWebserver.o

BIN_DIR = ../bin/
BINARY = $(BIN_DIR)dev_test

$(BINARY): $(OBJS)
	g++ -o $(BINARY) $(INCLUDES) $(OBJS) $(LIBS)

all: $(BINARY)

clean:
	$(RM) $(BINARY) $(OBJS)
