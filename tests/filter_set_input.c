/*
 * Test the assignment of an input array.
*/

#include "common.h"

int main(void) {
    char **input = malloc(sizeof(char *) * 4);
    struct StringFilter my_filter = LIBFILTER_FILTER_INIT(&my_filter);

    LIBERROR_MALLOC_FAILURE(input);

    LIBFILTER_FILTER_SET_INPUT(&my_filter, input, 4);

    assert(my_filter.output == NULL);
    assert(my_filter.filter_rule == NULL);
    assert(my_filter.input == input);
    assert(my_filter.length == 4);

    free(input);

    return 0;
}
