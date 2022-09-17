/*
 * Test the assignment of a filter operation.
*/

#include "common.h"

int custom_rule(char *object, const char *string) {
    if(strstr(object, string) == NULL)
        return 0;

    return 1;
}

int custom_rule_two(char *object, const char *string) {
    if(strstr(object, string) == NULL)
        return 0;

    return 1;
}

int main(void) {
    struct StringFilter my_filter = LIBFILTER_FILTER_INIT(&my_filter);

    LIBFILTER_FILTER_SET_RULE(&my_filter, custom_rule);

    assert(my_filter.input == NULL);
    assert(my_filter.output == NULL);
    assert(my_filter.filter_rule == custom_rule);

    /* How about something else? */
    LIBFILTER_FILTER_SET_RULE(&my_filter, custom_rule_two);

    assert(my_filter.input == NULL);
    assert(my_filter.output == NULL);
    assert(my_filter.filter_rule == custom_rule_two);

    return 0;
}
