#ifndef MODULE_CLASSIFIER_H
#define MODULE_CLASSIFIER_H

#include "../main.h"
#include "../module_io_handler/module_io_handler.h"
#include <string.h>

int is_directive(char* line);
char* read_input_line(char* file_path);
char* delete_commets(char* line);
int define_macro(char* line);
int include_file(char* line);
int process_ifdef_block(char* ifdef_block);
int is_directive(char* line);
int classifier(int n);

#endif
 