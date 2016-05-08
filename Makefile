CC		= gcc
CFLAGS		= 
SRCDIR		= src
BUILDDIR	= build
OUTFILE		= build/splitsearch

OBJS		= $(shell /bin/ls src/ | grep '$[\.c$]'| sed -e 's/\.c/.o/g' | sed -e 's/^/${BUILDDIR}\//')

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

test: compile
	@echo '================================='
	@echo 'Test 1: found number'
	@echo '================================='
	./build/splitsearch -i assets/numeric_small -v 22

	@echo '================================='
	@echo 'Test 2: not found number'
	@echo '================================='
	./build/splitsearch -i assets/numeric_small -v 1000
	
	@echo '================================='
	@echo 'Test 3: found string'
	@echo '================================='
	#./build/splitsearch -i assets/numeric_small -v 22

clean:
	rm -Rf build/*.o $(OUTFILE)
