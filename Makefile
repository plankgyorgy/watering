# In case having same environment variable AND using not GNU make
SHELL = /bin/sh

# Clear suffix list
.SUFFIXES:

# Use only files having these extensions
.SUFFIXES: .c .o .h

# Phony targets (that are rather labels)
.PHONY: clean Watering

# C compiler
CC = gcc

# Paths
BINDIR = ./bin
HEADERDIR = ./header
LIBDIR = ./source/lib
LIBHEADERDIR = ./source/lib/header
OBJDIR = ./bin/obj
SOURCEDIR = ./source

# Compiler flags
FLAGS = -I$(HEADERDIR)
LIBFLAGS = -I$(LIBHEADERDIR)

# Set of object files for having the possibility to handle them together
OBJECTS = $(OBJDIR)/main.o

# The main executable. Should be the first "target" to be the default one
Watering: $(OBJECTS)
	$(CC) -o $(BINDIR)/Watering $(OBJECTS) $(FLAGS)

# Targets and their recipes --------------------------------------------

$(OBJDIR)/main.o: $(SOURCEDIR)/main.c $(HEADERDIR)/main.h
	$(CC) -c -o $(OBJDIR)/main.o $(SOURCEDIR)/main.c $(FLAGS)

# Recipes without file target ------------------------------------------

# Delete all binaries to force a full (re)compile of all source files next time
clean:
	rm $(BINDIR)/Watering $(OBJECTS)