CC = gcc
OPTIONS = -Wall -ansi -pedantic

EXECUTABLE = rahan

SOURCE = $(wildcard *.c)
OBJECTS = $(SOURCE:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPTIONS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c %.h
	$(CC) $(OPTIONS) -MMD -c $<

-include *.d