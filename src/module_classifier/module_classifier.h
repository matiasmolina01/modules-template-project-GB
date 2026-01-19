#ifndef MODULE_CLASSIFIER_H
#define MODULE_CLASSIFIER_H

#include "../main.h"

#define INCLUDE_STR "#include" 
#define DEFINE_STR "#define" 
#define IFDEF_STR "#ifdef" 
#define MAX_SIZE 100

typedef struct MacroTable MacroTable;
typedef struct TextNormalizerState TextNormalizerState;
typedef struct ReplaceFlags ReplaceFlags;

typedef enum {
	INCLUDE,
	DEFINE,
	IFDEF,
	NO_DIRECTIVE
} Directive;

typedef struct GlobalState{
	TextNormalizerState* tn_state;
	MacroTable* macro_table;
	ReplaceFlags* replace_flags;
} GlobalState;

Directive cl_directive_type(char* word);
// interaction with Symbol Table
int cl_define_handler(); 
// interaction with Recursivity Handler
int cl_include_handler(); 
int cl_ifdef_handler();
// initialization of the GlobalState datastructure
GlobalState* cl_init_datastructures();
// main loop
int cl_classifier(char* input_file_path, char* output_file_path);

#endif
 