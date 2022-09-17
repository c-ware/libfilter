/*
 * Test the actual matching functionality and make sure it
 * works properly.
*/

#include "common.h"

int custom_rule(char *object, const char *string) {
    if(strstr(object, string) == NULL)
        return 0;

    return 1;
}

int main(void) {
    int final_length = 0;
    char **input = malloc(sizeof(char *) * 4);
    char **output = malloc(sizeof(char *) * 4);
    struct StringFilter my_filter = LIBFILTER_FILTER_INIT(&my_filter);

    /* Configure the filter */
    LIBFILTER_FILTER_SET_RULE(&my_filter, custom_rule);
    LIBFILTER_FILTER_SET_INPUT(&my_filter, input, 4);
    LIBFILTER_FILTER_SET_OUTPUT(&my_filter, output);

    input[0] = "foo";
    input[1] = "bar";
    input[2] = "baz";
    input[3] = "tuna";

    /* Perform the filtering */
    LIBFILTER_FILTER_MATCH(&my_filter, "foo", final_length);

    /* Is the output correct? */
    assert(final_length == 1);
    assert(strcmp(output[0], "foo") == 0);
    assert(strcmp(my_filter.output[0], "foo") == 0);

    /* Verify that the macro does not modify the input */
    assert(strcmp(input[0], "foo") == 0);
    assert(strcmp(input[1], "bar") == 0);
    assert(strcmp(input[2], "baz") == 0);
    assert(strcmp(input[3], "tuna") == 0);

    /* How about a more basic input? */
    LIBFILTER_FILTER_MATCH(&my_filter, "a", final_length);

    assert(final_length == 3);
    assert(strcmp(output[0], "bar") == 0);
    assert(strcmp(output[1], "baz") == 0);
    assert(strcmp(output[2], "tuna") == 0);
    assert(strcmp(my_filter.output[0], "bar") == 0);
    assert(strcmp(my_filter.output[1], "baz") == 0);
    assert(strcmp(my_filter.output[2], "tuna") == 0);

    /* Verify that the macro does not modify the input */
    assert(strcmp(input[0], "foo") == 0);
    assert(strcmp(input[1], "bar") == 0);
    assert(strcmp(input[2], "baz") == 0);
    assert(strcmp(input[3], "tuna") == 0);

    free(input);
    free(output);

    return 0;
}
