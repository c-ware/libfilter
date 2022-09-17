/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 * 
 * A "redistribution" can be constituted as any version of the source code
 * that is intended to comprise some other derivative work of this code. A
 * fork created for the purpose of contributing to any version of the source
 * does not constitute a truly "derivative work" and does not require listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * @docgen_start
 * @type: project
 * @name: libfilter
 * @brief: filter arbitrary objects with a string
 *
 * @embed: LIBFILTER_FILTER_INIT
 * @show_brief: 0
 *
 * @embed: LIBFILTER_FILTER_SET_OUTPUT
 * @show_brief: 0
 *
 * @embed: LIBFILTER_FILTER_SET_RULE
 * @show_brief: 0
 *
 * @embed: LIBFILTER_FILTER_SET_INPUT
 * @show_brief: 0
 *
 * @embed: LIBFILTER_FILTER_MATCH
 * @show_brief: 0
 *
 * @embed: LIBFILTER_FILTER_DECLARE
 * @show_brief: 0
 *
 * @description
 * @A macro-based and thus type safe way to handle the filtering of arbitrary
 * @arrays of objects based off of an input string. A possible use would be for
 * @an interactive filter program, which might accept data from the stdin.
 * @
 * @The way that objects are filtered is completely customizable, using a filter
 * @rule system to implement custom ways to determine whether an object should
 * @pass through the filter. For documentation on the individual operations
 * @as seen in the SYNOPSIS, see the manuals described in the below table.
 * @
 * @\T
 * @\S ;
 * @\H Manual;Description
 * @\E LIBFILTER_FILTER_INIT(cware);initialize a filter
 * @\E LIBFILTER_FILTER_MATCH(cware);match the input against a string
 * @\E LIBFILTER_FILTER_DECLARE(cware);declare a new filter
 * @\E LIBFILTER_FILTER_SET_RULE(cware);set the filter rule
 * @\E LIBFILTER_FILTER_SET_INPUT(cware);set the input array
 * @\E LIBFILTER_FILTER_SET_OUTPUT(cware);set the output array
 * @\T
 * @description
 *
 * @examples
 * @For examples of how to use libfilter, please see the below manual page(s).
 * @\T
 * @\S ;
 * @\H Manual;Description
 * @\E libfilter-example-strings;an example on filtering strings
 * @\T
 * @examples
 *
 * @reference: cware(cware)
 *
 * @docgen_end
*/

#ifndef CWARE_LIBFILTER_H
#define CWARE_LIBFILTER_H

#include "deps/liberror/liberror.h"

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_DECLARE
 * @brief: declare a new filter structure
 *
 * @include: libfilter/libfilter.h
 *
 * @description
 * @This macro will generate a new basic filter object with a given
 * @name, and the type of object to filter. It is recommended to use
 * @this macro, as opposed to declaring it yourself, as the structure
 * @of the filter may change.
 * @description
 *
 * @mparam: name
 * @brief: the name of the structure
 *
 * @mparam: type
 * @brief: the type of object to filter
 *
 * @reference: libfilter(cware)
 * @docgen_end
*/
#define LIBFILTER_FILTER_DECLARE(name, type)                 \
    struct name {                                            \
        int length;                                          \
        type *input;                                         \
        type *output;                                        \
                                                             \
        int (*filter_rule)(type object, const char *string); \
    }

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_INIT
 * @brief: initialize a new filter
 *
 * @include: libfilter/libfilter.h
 *
 * @description
 * @This macro function will initialize the required fields of a filter
 * @with their default values. Note, that this macro does \Bnot\B make the filter
 * @usable. Rather, it essentially just zeros out the required fields.
 * @description
 *
 * @mparam: filter
 * @brief: a pointer to the filter to initialize
 *
 * @return_value
 * @This macro function will 'return' (first line will evaluate to) the
 * @dereferenced pointer, to allow syntax like initializing on the same
 * @line as the declaration.
 * @return_value
 *
 * @reference: libfilter(cware)
 *
 * @docgen_end
*/
#define LIBFILTER_FILTER_INIT(filter) \
    *filter;                          \
                                      \
    (filter)->input = NULL;           \
    (filter)->output = NULL;          \
    (filter)->filter_rule = NULL;     \
    (filter)->length = 0;

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_SET_RULE
 * @brief: assign the rule to use when filtering
 *
 * @include: libfilter/libfilter.h
 *
 * @description
 * @This macro function will set the rule to use when filtering the contents of
 * @the input array. The rule must have a function signature matching the following,
 * @where \IT\I represents an arbitrary type that the user decides:
 * @
 * @\Bint filter(\B\IT object\I\B, const char *string);\B
 * @
 * @The return value of the filter function should be 1 if the object passes
 * @the filter, and 0 if it does not.
 * @description
 *
 * @mparam: filter
 * @brief: a pointer to the filter to set the rule of
 *
 * @mparam: rule
 * @brief: the filter rule to use
 *
 * @error: filter is NULL
 * @error: rule is NULL
 *
 * @reference: libfilter(cware)
 *
 * @docgen_end
*/
#define LIBFILTER_FILTER_SET_RULE(filter, rule) \
    LIBERROR_IS_NULL(filter);                   \
    LIBERROR_IS_NULL(rule);                     \
                                                \
    (filter)->filter_rule = rule

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_SET_INPUT
 * @brief: set the input array to filter
 *
 * @include: libfilter/libfilter.h
 *
 * @description
 * @Set the array to use as input to filter, along with the  length
 * @of the array.
 * @description
 *
 * @mparam: filter
 * @brief: pointer to the filter to use
 * 
 * @mparam: array
 * @brief: the array to use as a filter
 *
 * @mparam: array_length
 * @brief: the length of the input array
 *
 * @error: filter is NULL
 * @error: array is NULL
 * @error: array_length is negative
 *
 * @reference: libfilter(cware)
 *
 * @docgen_end
*/
#define LIBFILTER_FILTER_SET_INPUT(filter, array, array_length) \
    LIBERROR_IS_NULL(filter);                                   \
    LIBERROR_IS_NULL(array);                                    \
    LIBERROR_IS_NEGATIVE(array_length);                         \
                                                                \
    (filter)->input = (array);                                  \
    (filter)->length = (array_length)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_SET_OUTPUT
 * @brief: set the output array for the filter
 *
 * @include: libfilter/libfilter.h
 *
 * @description
 * @Set the array to use to store the filtered items. Assumes the length
 * @of the input array, and such, should be called \Bafter\B the input
 * @array is provided.
 * @description
 *
 * @mparam: filter
 * @brief: pointer to the filter to use
 * 
 * @mparam: array
 * @brief: the array to use as output
 *
 * @reference: libfilter(cware)
 *
 * @error: filter is NULL
 * @error: array is NULL
 * @error: filter->input is NULL
 * @error: filter->length is negative
 *
 * @docgen_end
*/
#define LIBFILTER_FILTER_SET_OUTPUT(filter, array) \
    LIBERROR_IS_NULL(filter);                      \
    LIBERROR_IS_NULL(array);                       \
                                                   \
    (filter)->output = (array);

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBFILTER_FILTER_MATCH
 * @brief: filter the input array against a string
 *
 * @description
 * @For each input array element, if it passes the filter, add it to
 * @the output array. The length of the final output array is known
 * @using the \Ioutput_length\I parameter, which should be a variable
 * @that can hold a number.
 * @description
 *
 * @error: filter is NULL
 * @error: string is NULL
 * @error: filter->input is NULL
 * @error: filter->output is NULL
 * @error: filter->filter_rule is NULL
 * @error: filter->length is negative
 *
 * @mparam: filter
 * @brief: pointer to the filter to use
 *
 * @mparam: string
 * @brief: the string to filter the contents by
 *
 * @mparam: output_length
 * @brief: the variable to hold the length of the final filter
 *
 * @return_value
 * @This macro will not evaluate to any final value, although it
 * @will write the final length of the output array to the variable
 * @held in \Ioutput_length\I.
 * @return_value
 *
 * @reference: libfilter(cware)
 * @reference: LIBFILTER_FILTER_SET_INPUT(cware)
 * @reference: LIBFILTER_FILTER_SET_OUTPUT(cware)
 * @reference: LIBFILTER_FILTER_SET_RULE(cware)
 *
 * @docgen_end
*/
#define LIBFILTER_FILTER_MATCH(filter, string, output_length)                                \
do {                                                                                         \
    int __LIBFILTER_INDEX = 0;                                                               \
    int __LIBFILTER_CURSOR = 0;                                                              \
                                                                                             \
    (output_length) = 0;                                                                     \
                                                                                             \
    for(__LIBFILTER_INDEX = 0 ; __LIBFILTER_INDEX < (filter)->length; __LIBFILTER_INDEX++) { \
        if((filter)->filter_rule((filter)->input[__LIBFILTER_INDEX], (string)) == 0)         \
            continue;                                                                        \
                                                                                             \
        (filter)->output[__LIBFILTER_CURSOR] = (filter)->input[__LIBFILTER_INDEX];           \
        __LIBFILTER_CURSOR++;                                                                \
        (output_length)++;                                                                   \
    }                                                                                        \
} while(0)

#endif
