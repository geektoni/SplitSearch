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
	@echo ''
	@echo '[*] Test 1: found number'
	./build/splitsearch -i assets/numeric_small -v 22

	@echo ''
	@echo '[*] Test 2: not found number'
	./build/splitsearch -i assets/numeric_small -v 1000

	@echo ''
	@echo '[*] Test 3: found string'
	@echo '================================='
	#./build/splitsearch -i assets/string_largest -v zucchini

	@echo ''
	@echo '[*] Test 4: print output_file'
	@echo '================================='
	./build/splitsearch -i assets/numeric_repetition_small -v 10 -o out_puttest_4

	@echo ''
	@echo '[*] Test 5: print max_value of values found'
	@echo '================================='
	./build/splitsearch -i assets/numeric_repetition_small -v 10 -r 5

	@echo ''
	@echo '[*] Test 6: print max_value of values found in output_file'
	@echo '================================='
	./build/splitsearch -i assets/numeric_large -v 24 -r 3 -o out_puttest_6

	@echo ''
	@echo '[*] Test 7: error: must have default markers to work.'
	@echo '================================='
	./build/splitsearch -v value

clean:
	rm -Rf build/*.o $(OUTFILE)
