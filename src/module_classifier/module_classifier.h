#ifndef MODULE_CLASSIFIER_H
#define MODULE_CLASSIFIER_H

#include "../main.h"

#define INCLUDE_STR "#include" 
#define DEFINE_STR "#define" 
#define IFDEF_STR "#ifdef" 
#define ENDIF_STR "#endif" 
#define MAX_SIZE 100

typedef struct MacroTable MacroTable;
typedef struct TextNormalizerState TextNormalizerState;
typedef struct ReplaceFlags ReplaceFlags;
typedef struct args_state_t args_state_t;
typedef struct RHStack RHStack;
typedef struct RHProcessMacro RHProcessMacro;

typedef enum {
	INCLUDE,
	DEFINE,
	IFDEF,
	ENDIF,
	NO_DIRECTIVE
} Directive;

typedef struct GlobalState{
	TextNormalizerState* tn_state;
	MacroTable* macro_table;
	ReplaceFlags* replace_flags;
	args_state_t* args_state;
	rh_stack* rh_stack;
	rh_process_macro* rh_process_macro;
} GlobalState;

Directive cl_directive_type(char* word);
// interaction with Symbol Table
int cl_define_handler(); 
// interaction with Recursivity Handler
int cl_include_handler(); 
int cl_ifdef_handler();
// initialization of the GlobalState datastructure
GlobalState* cl_init_datastructures();
void cl_free_datastructures(GlobalState* global_state);
// main loop
int cl_classifier(args_state_t* args_state);

#endif
 