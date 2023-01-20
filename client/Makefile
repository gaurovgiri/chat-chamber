CC = gcc
CFLAGS = -I inc
LIBS = -lncurses -L/usr/lib -lssl -lcrypto


SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))
OBJECTS += obj/main.o
BINDIR = bin

EXECUTABLE = $(BINDIR)/client

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)


.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) test
