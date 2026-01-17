/*
 * -----------------------------------------------------------------------------
 * module_text_normalizer.c 
 *
 * Usage:
 *     Called from the main application or test modules to normalize text.
 *
 * Status:
 *     Initial development — logic to handle text normalizing is not yet implemented.
 *
 * Author: [Anna Vasileva]
 * -----------------------------------------------------------------------------
 */

#include "./module_text_normalizer.h"


char* text_normalizer(const char* input_line, TextNormalizerState* state) {
    int len = strlen(input_line);
    char* output = malloc(len + 1);

    if (!output) return NULL;

    int i = 0;
    int j = 0;

    while (i < len) {

        // Case 1: whole line is a comment //
        if (input_line[i] == '/' && input_line[i + 1] == '/') {
            break;  // ignore rest of line
        }

        // Case 2: starting comment /*
        if (input_line[i] == '/' && input_line[i + 1] == '*') {
            state->in_block_comment = 1;
            i += 2;
            continue;
        }

        // Case 3: until the end of comment */
        if (state->in_block_comment) {
            if (input_line[i] == '*' && input_line[i + 1] == '/') {
                state->in_block_comment = 0;
                i += 2;
            } else {
                i++;
            }
            continue;
        }

        // Normal character
        output[j++] = input_line[i++];
    }

    output[j] = '\0';
    return output;
}
