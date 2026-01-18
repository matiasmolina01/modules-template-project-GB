#ifndef MODULE_IO_HANDLER_H
#define MODULE_IO_HANDLER_H

#include "../main.h"

#define IH_MAX_LINE_LENGTH 1024


bool ioh_open(const char *path);
bool ioh_close();
int ioh_read_line(char *buffer, size_t max);
int ioh_read_word(char *buffer, size_t max);
int ioh_line_number();
bool ioh_is_eof();


#endif
 