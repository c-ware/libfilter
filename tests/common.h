#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../src/libfilter.h"

struct CustomObject {
    int id;
    char *name;
};

LIBFILTER_FILTER_DECLARE(StringFilter, char *);
LIBFILTER_FILTER_DECLARE(CustomObjectFilter, struct CustomObject);

#endif
