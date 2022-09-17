# M4ke








CC=cc
CFLAGS=-DLIBERROR_FREE_SAFETY -DLIBERROR_ENABLED -g
TESTS=tests/filter_set_rule tests/filter_set_input tests/filter_init tests/filter_set_output tests/filter_match 
EXAMPLES=examples/strings 

all: $(TESTS) $(EXAMPLES)

clean:
	rm -f $(TESTS)

.SUFFIXES:


	


tests/filter_init: tests/filter_init.c src/libfilter.h
	$(CC) tests/filter_init.c $(OBJS) -o tests/filter_init $(CFLAGS)
tests/filter_set_rule: tests/filter_set_rule.c src/libfilter.h
	$(CC) tests/filter_set_rule.c $(OBJS) -o tests/filter_set_rule $(CFLAGS)
tests/filter_set_input: tests/filter_set_input.c src/libfilter.h
	$(CC) tests/filter_set_input.c $(OBJS) -o tests/filter_set_input $(CFLAGS)
tests/filter_set_output: tests/filter_set_output.c src/libfilter.h
	$(CC) tests/filter_set_output.c $(OBJS) -o tests/filter_set_output $(CFLAGS)
tests/filter_match: tests/filter_match.c src/libfilter.h
	$(CC) tests/filter_match.c $(OBJS) -o tests/filter_match $(CFLAGS)

examples/strings: examples/strings.c src/libfilter.h
	$(CC) examples/strings.c $(OBJS) -o examples/strings $(CFLAGS)
