CC		= gcc
CFLAGS		= 
SRCDIR		= ./src
BUILDDIR	= ./build
OUTFILE		= ./build/splitsearch
OBJS		= $(BUILDDIR)/main.o $(BUILDDIR)/argparsing.o $(BUILDDIR)/splitsearch.o

.PHONY: clean help

help:
	@echo '================================='
	@echo ' Splitsearch make usage:'
	@echo '================================='
	@echo ' * clean: clear all .o files'
	@echo ' * compile: compile all project'
	@echo ' * build: clean and compile all project'
	@echo ' * test: execute the project on a test input file'

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

compile: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUTFILE)

build: clean compile

test:

clean:
	rm -Rf build/*.o
