include(m4ke.m4)

CC=cc
CFLAGS=-DLIBERROR_FREE_SAFETY -DLIBERROR_ENABLED -g
TESTS=CONVERT_FILES(tests, .c,)
EXAMPLES=CONVERT_FILES(examples, .c,)

all: $(TESTS) $(EXAMPLES)

clean:
	rm -f $(TESTS)

.SUFFIXES:

dnl Declare all implicit rules
NEW_IMPLICIT_RULE(.c, , `	$(CC) $1 $(OBJS) -o $2 $(CFLAGS)')

dnl Test targets
NEW_RULE(tests/filter_init, .c,, src/libfilter.h)
NEW_RULE(tests/filter_set_rule, .c,, src/libfilter.h)
NEW_RULE(tests/filter_set_input, .c,, src/libfilter.h)
NEW_RULE(tests/filter_set_output, .c,, src/libfilter.h)
NEW_RULE(tests/filter_match, .c,, src/libfilter.h)

dnl Example targets
NEW_RULE(examples/strings, .c,, src/libfilter.h)
