#ifndef MODULE_RECURSIVITY_HANDLER_H
#define MODULE_RECURSIVITY_HANDLER_H

#include "../main.h"

#define RH_STACK_CAPACITY 100

typedef struct RHProcessMacro{
	int process; //0 = skip, 1 = process
} RHProcessMacro;

//stack node for ifdef/ifndef directives
typedef struct RHNode{
	char *directive;  // "ifdef", "ifndef", "endif"
	char *macro;      // Associated macro name (NULL for endif)
	int is_active;    // 1 if block should be processed, 0 if skipped
} RHNode;

// stack to handle nested ifdef/ifndef
typedef struct RHStack{
	int top;
	int capacity;
	RHNode *items;
} RHStack;

// Stack operations
RHStack* rh_stack_create(int capacity);

void rh_stack_free(RHStack *stack);

int rh_stack_push(RHStack *stack, const char *directive, const char *macro, int is_active);

int rh_stack_pop(RHStack *stack);

int rh_stack_is_empty(RHStack *stack);

int rh_stack_is_active(RHStack *stack);

//Recursivity handler functions
int recursivity_handler(int n);

int rh_handle_include(const char *filename, args_state_t* args_state);

int rh_filename_check(const char *filename);

void rh_handle_ifdef_directive(char *macro, MacroTable *table, RHStack *stack, int is_negated, RHProcessMacro *process_macro);

int rh_handle_endif(RHStack *stack);

#endif
 