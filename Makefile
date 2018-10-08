TARGET = wavrev wavinfo wavvol wavecho wavwide
CC = gcc
CFLAGS  = -g -Wall
OBJECTS = wavprocessing.o wavaccess.o parse.o
HEADERS = $(wildcard *.h)
LIBS = -lm

default: $(TARGET)
all: default

.PHONY: default all clean

wavinfo: wavinfo.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavrev: wavrev.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavvol: wavvol.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavecho: wavecho.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavwide: wavwide.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavcat: wavcat.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@

wavmix: wavmix.o $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< $(LIBS) -o $@


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o core
	rm -f $(TARGET)
