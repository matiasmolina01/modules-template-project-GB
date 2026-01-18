#ifndef MODULE_CLASSIFIER_H
#define MODULE_CLASSIFIER_H

#include "../main.h"
#include "../module_io_handler/module_io_handler.h"
#include "../module_text_normalizer/module_text_normalizer.h"
#include <string.h>

typedef enum {
	INCLUDE,
	DEFINE,
	IFDEF,
	NO_DIRECTIVE
} Directive;

#define INCLUDE_STR "#include" 
#define DEFINE_STR "#define" 
#define IFDEF_STR "#ifdef" 
#define MAX_SIZE 100

Directive cl_directive_type(char* word);
char* cl_get_next_word();
char* cl_process_line(char* line);
int cl_define_handler(char* line);
int cl_include_handler(char* line);
int cl_ifdef_handler(char* line);
int cl_write_to_output(char* line);
int cl_classifier(char* file_path);

#endif
 