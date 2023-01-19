CC = gcc
CFLAGS = -I inc
LIBS = -lncurses -lm -lsqlite3 -L/usr/lib -lssl -lcrypto

CERTS = certs
SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))
OBJECTS += obj/main.o
BINDIR = bin

EXECUTABLE = $(BINDIR)/server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

# openssl req -x509 -newkey rsa:4096 -keyout $(CERTS)/certi.pem -out $(CERTS)/certi.pem -days 365 -nodes

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) test
