#ifndef MODULE_RECURSIVITY_HANDLER_H
#define MODULE_RECURSIVITY_HANDLER_H

#include "../main.h"

typedef struct{
	int process; //0 = skip, 1 = process
} rh_process_macro;

//stack node for ifdef/ifndef directives
typedef struct{
	char *directive;  // "ifdef", "ifndef", "endif"
	char *macro;      // Associated macro name (NULL for endif)
	int is_active;    // 1 if block should be processed, 0 if skipped
} rh_node;

// stack to handle nested ifdef/ifndef
typedef struct{
	int top;
	int capacity;
	rh_node *items;
} rh_stack;

// Stack operations
rh_stack* rh_stack_create(int capacity);

void rh_stack_free(rh_stack *stack);

int rh_stack_push(rh_stack *stack, const char *directive, const char *macro, int is_active);

int rh_stack_pop(rh_stack *stack);

int rh_stack_is_empty(rh_stack *stack);

int rh_stack_is_active(rh_stack *stack);

//Recursivity handler functions
int recursivity_handler(int n);

int rh_handle_include(const char *filename, const char *output_file);

int rh_filename_check(const char *filename);

void rh_handle_ifdef_directive(char *macro, MacroTable *table, rh_stack *stack, int is_negated, rh_process_macro *process_macro);

int rh_handle_endif(rh_stack *stack);

#endif
 