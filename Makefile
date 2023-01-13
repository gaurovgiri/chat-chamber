CC = gcc
CFLAGS = -I inc


SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))
OBJECTS += obj/main.o
BINDIR = bin

EXECUTABLE = $(BINDIR)/client

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) -lncurses

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
