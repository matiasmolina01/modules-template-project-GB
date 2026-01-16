#ifndef MODULE_OUTPUT_HANDLER_H
#define MODULE_OUTPUT_HANDLER_H

#include "../main.h"

int oh_open(const char *path);
int oh_close(int fd);
int oh_write_line(int fd, char *buffer);

#endif
 