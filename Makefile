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
BINLIBDIR = ./bin/lib
HEADERDIR = ./source/header
LIBDIR = ./source/lib
LIBHEADERDIR = ./source/lib/header
LIBOBJDIR = ./bin/lib/obj
OBJDIR = ./bin/obj
SOURCEDIR = ./source

# Compiler flags
FLAGS = -I$(HEADERDIR)
LIBFLAGS = -I$(LIBHEADERDIR)

# Set of object files for having the possibility to handle them together
OBJECTS = $(OBJDIR)/main.o
LIBOBJECTS = $(LIBOBJDIR)/linkedlist.o $(LIBOBJDIR)/singleset.o
LIBS = $(BINLIBDIR)/liblinkedlist.a $(BINLIBDIR)/libsingleset.a

# The main executable. Should be the first "target" to be the default one
Watering: $(OBJECTS) $(LIBS)
	$(CC) -o $(BINDIR)/watering.exe $(OBJECTS) -L$(BINLIBDIR) -llinkedlist -lsingleset $(FLAGS) $(LIBFLAGS)

# Targets and their recipes --------------------------------------------

$(OBJDIR)/main.o: $(SOURCEDIR)/main.c $(HEADERDIR)/main.h
	$(CC) -c -o $(OBJDIR)/main.o $(SOURCEDIR)/main.c $(FLAGS)

$(BINLIBDIR)/liblinkedlist.a: $(LIBOBJDIR)/linkedlist.o
	ar -cvq $(BINLIBDIR)/liblinkedlist.a  $(LIBOBJDIR)/linkedlist.o

$(LIBOBJDIR)/linkedlist.o: $(LIBDIR)/linkedlist.c $(LIBHEADERDIR)/linkedlist.h
	$(CC) -c -o $(LIBOBJDIR)/linkedlist.o $(LIBDIR)/linkedlist.c $(LIBFLAGS)

$(BINLIBDIR)/libsingleset.a: $(LIBOBJDIR)/singleset.o
	ar -cvq $(BINLIBDIR)/libsingleset.a  $(LIBOBJDIR)/singleset.o

$(LIBOBJDIR)/singleset.o: $(LIBDIR)/singleset.c $(LIBHEADERDIR)/singleset.h
	$(CC) -c -o $(LIBOBJDIR)/singleset.o $(LIBDIR)/singleset.c $(LIBFLAGS)

# Recipes without file target ------------------------------------------

# Delete all binaries to force a full (re)compile of all source files next time
clean:
	rm $(BINDIR)/watering.exe $(OBJECTS) $(LIBS) $(LIBOBJECTS)