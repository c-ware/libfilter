/*
 * @docgen_start
 * @type: project
 * @name: libfilter-example-strings
 * @brief: an example of how to filter strings
 *
 * @description
 * @This manual describes an example of how to filter an array of strings
 * @by reading a character from stdin, filtering, and repeating the filtering
 * @until there is only one item. Characters can be deleted by pressing backspace
 * @and then enter.
 * @description
 *
 * @examples
 * @#include "../src/libfilter.h"
 * @
 * @#define STRING_BUFFER_SIZE  32
 * @
 * @// Declare a new filter
 * @LIBFILTER_FILTER_DECLARE(StringFilter, char *);
 * @
 * @// Filter strings based off whether or not "filter" is
 * @// present in the string
 * @int filter_string(char *string, const char *filter) {
 * @    if(strstr(string, filter) == NULL)
 * @        return 0;
 * @
 * @    return 1;
 * @}
 * @
 * @int main(void) {
 * @    char *input[4];
 * @    char *output[4];
 * @    char string[STRING_BUFFER_SIZE + 1];
 * @    int output_index = 0;
 * @    int string_length = 0;
 * @    int output_length = 4;
 * @    struct StringFilter new_filter = LIBFILTER_FILTER_INIT(&new_filter); 
 * @
 * @    memset(input, 0, sizeof(input));
 * @    memset(output, 0, sizeof(output));
 * @    memset(string, 0, sizeof(string));
 * @
 * @    // We want to filter these strings
 * @    input[0] = "foo";
 * @    input[1] = "bar";
 * @    input[2] = "baz";
 * @    input[3] = "tuna";
 * @
 * @    // Clone these into the output for initial printing
 * @    output[0] = "foo";
 * @    output[1] = "bar";
 * @    output[2] = "baz";
 * @    output[3] = "tuna";
 * @
 * @    // Setup the filter
 * @    LIBFILTER_FILTER_SET_INPUT(&new_filter, input, 4);
 * @    LIBFILTER_FILTER_SET_OUTPUT(&new_filter, output);
 * @    LIBFILTER_FILTER_SET_RULE(&new_filter, filter_string);
 * @
 * @    // Begin filtering until the output length is 1
 * @    while(output_length != 1) {
 * @        char next_character = 0;
 * @
 * @        // Display the valid options so far
 * @        for(output_index = 0; output_index < output_length; output_index++) {
 * @            printf("%i: %s\n", output_index + 1, output[output_index]); 
 * @        }
 * @
 * @        // Print a prompt with the current filter string as the typed one
 * @        printf(">>> %s", string); 
 * @
 * @        next_character = fgetc(stdin);
 * @        printf("\\\\n");
 * @
 * @        // Typed string must be able to fit in the buffer
 * @        if(string_length == STRING_BUFFER_SIZE)
 * @            continue;
 * @
 * @        // Backspace-- but make sure it does not index out of the bounds
 * @        // of the array backwards!
 * @        if(next_character == 0x08) {
 * @            if(string_length == 0)
 * @               continue;
 * @
 * @            string_length--; 
 * @            string[string_length] = '\\\\0';
 * @        } else if(next_character != '\\\\n') {
 * @            string[string_length] = next_character;    
 * @            string_length++;
 * @
 * @            string[string_length] = '\\\\0';
 * @        }
 * @
 * @        // Filter the strings
 * @        LIBFILTER_FILTER_MATCH(&new_filter, string, output_length);
 * @
 * @        // Clear the screen
 * @        printf("%s", "\\\\033[2J");
 * @    }
 * @
 * @    printf("You chose: '%s'\n", output[0]);
 * @
 * @    return EXIT_SUCCESS;
 * @}
 * @examples
 *
 * @docgen_end
*/

#include "../src/libfilter.h"

#define STRING_BUFFER_SIZE  32

/* Declare a new filter */
LIBFILTER_FILTER_DECLARE(StringFilter, char *);

/* Filter strings based off whether or not "filter" is
 * present in the string */
int filter_string(char *string, const char *filter) {
    if(strstr(string, filter) == NULL)
        return 0;

    return 1;
}

int main(void) {
    char *input[4];
    char *output[4];
    char string[STRING_BUFFER_SIZE + 1];
    int output_index = 0;
    int string_length = 0;
    int output_length = 4;
    struct StringFilter new_filter = LIBFILTER_FILTER_INIT(&new_filter); 

    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));
    memset(string, 0, sizeof(string));

    /* We want to filter these strings */
    input[0] = "foo";
    input[1] = "bar";
    input[2] = "baz";
    input[3] = "tuna";

    /* Clone these into the output for initial printing */
    output[0] = "foo";
    output[1] = "bar";
    output[2] = "baz";
    output[3] = "tuna";

    /* Setup the filter */
    LIBFILTER_FILTER_SET_INPUT(&new_filter, input, 4);
    LIBFILTER_FILTER_SET_OUTPUT(&new_filter, output);
    LIBFILTER_FILTER_SET_RULE(&new_filter, filter_string);

    /* Begin filtering until the output length is 1 */
    while(output_length != 1) {
        char next_character = 0;

        /* Display the valid options so far */ 
        for(output_index = 0; output_index < output_length; output_index++) {
            printf("%i: %s\n", output_index + 1, output[output_index]); 
        }

        /* Print a prompt with the current filter string as the typed one */
        printf(">>> %s", string); 

        next_character = fgetc(stdin);
        printf("\n");

        /* Typed string must be able to fit in the buffer */
        if(string_length == STRING_BUFFER_SIZE)
            continue;

        /* Backspace-- but make sure it does not index out of the bounds
         * of the array backwards! */
        if(next_character == 0x08) {
            if(string_length == 0)
               continue;

            string_length--; 
            string[string_length] = '\0';
        } else if(next_character != '\n') {
            string[string_length] = next_character;    
            string_length++;

            string[string_length] = '\0';
        }

        /* Filter the strings */
        LIBFILTER_FILTER_MATCH(&new_filter, string, output_length);

        /* Clear the screen */
        printf("%s", "\033[2J");
    }

    printf("You chose: '%s'\n", output[0]);

    return EXIT_SUCCESS;
}
