#ifndef MODULE_INPUT_HANDLER_H
#define MODULE_INPUT_HANDLER_H

#include "../main.h"

#define IH_MAX_LINE_LENGTH 1024


bool ih_open(const char *path);
bool ih_close();
int ih_read_line(char *buffer, size_t max);
int ih_read_word(char *buffer, size_t max);
int ih_line_number();
bool ih_is_eof();


#endif
 