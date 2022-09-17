/*
 * Test the initialization of a filter.
*/

#include "common.h"

int main(void) {
    struct StringFilter my_filter = LIBFILTER_FILTER_INIT(&my_filter);

    assert(my_filter.input == NULL);
    assert(my_filter.output == NULL);
    assert(my_filter.filter_rule == NULL);

    return 0;
}
