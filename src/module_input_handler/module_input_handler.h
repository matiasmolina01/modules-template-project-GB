#ifndef MODULE_INPUT_HANDLER_H
#define MODULE_INPUT_HANDLER_H

#include "../main.h"

bool ih_open(const char *path);
bool ih_close(int fd);
int ih_read_line(int fd, char *buffer, size_t max);
int ih_write_line(int fd, char *buffer);
int ih_read_line(int fd, char *buffer, size_t max);


#endif
 