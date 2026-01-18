#ifndef MODULE_CLASSIFIER_H
#define MODULE_CLASSIFIER_H

#include "../main.h"
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

typedef struct MacroTable MacroTable;
typedef struct TextNormalizerState TextNormalizerState;

typedef struct GlobalState{
	TextNormalizerState* tn_state;
	MacroTable* macro_table;
} GlobalState;

Directive cl_directive_type(char* word);
char* cl_normalize_word(char* word);
int cl_define_handler();
int cl_include_handler();
int cl_ifdef_handler();
GlobalState* cl_init_datastructures();
int cl_classifier(char* file_path);

#endif
 