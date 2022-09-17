/*
 * Test the assignment of an output array.
*/

#include "common.h"

int main(void) {
    char **output = malloc(sizeof(char *) * 4);
    struct StringFilter my_filter = LIBFILTER_FILTER_INIT(&my_filter);

    LIBFILTER_FILTER_SET_OUTPUT(&my_filter, output);
    
    assert(my_filter.length == 0);
    assert(my_filter.input == NULL);
    assert(my_filter.output == output);

    free(output);

    return 0;
}
