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

        // Case 1: until the end of comment */
        if (state->in_block_comment) {
            if (i + 1 < len && input_line[i] == '*' && input_line[i + 1] == '/') {
                state->in_block_comment = 0;
                i += 2;
            } else {
                i++;
            }
            continue;
        }

        // Case 2: until the end of the line inside comment //
        if (state->in_line_comment) {
            if (input_line[i] == '\n') {
                state->in_line_comment = 0;
                i++;
            } else {
                i++;
            }
            continue;
        }

        // Case 1: starting comment //
        if (i + 1 < len && state->in_block_comment == 0 && input_line[i] == '/' && input_line[i + 1] == '/') {
            state->in_line_comment = 1;
            i += 2;
            continue;
        }

        // Case 3: starting comment /*
        if (i + 1 < len && state->in_line_comment == 0 && input_line[i] == '/' && input_line[i + 1] == '*') {
            state->in_block_comment = 1;
            i += 2;
            continue;
        }

        // Normal character
        output[j++] = input_line[i++];
    }

    output[j] = '\0';
    return output;
}
