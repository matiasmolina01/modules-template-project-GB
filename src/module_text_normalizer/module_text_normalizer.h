#ifndef MODULE_TEXT_NORMALIZER_H
#define MODULE_TEXT_NORMALIZER_H

#include "../main.h"

typedef struct {
    int in_block_comment;  // 0 = outside, 1 = inside /* */
    int in_line_comment;  // 0 = code line, 1 = after //
} TextNormalizerState;

char* text_normalizer(
    const char* input_line,
    TextNormalizerState* state
);

#endif