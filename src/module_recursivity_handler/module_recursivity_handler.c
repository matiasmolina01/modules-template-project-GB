/*
 * -----------------------------------------------------------------------------
 * module_recursivity_handler.c 
 *
 * Usage:
 *     Called from the main application or test modules to handle recursivity in modules.
 *
 * Status:
 *     Initial development — logic to handle recursivity is not yet implemented.
 *
 * Author: [Alex Ruiz]
 * -----------------------------------------------------------------------------
 */

#include "./module_recursivity_handler.h"
#include <string.h>

int recursivity_handler(int n) {
    printf("Recursivity Handler module, still to be implemented\n");
	return 0;
}

//Create a new stack with x capacity
RHStack* rh_stack_create(int capacity){
	RHStack *stack = (RHStack*)malloc(sizeof(RHStack));
	if(stack == NULL) return NULL;
	
	stack->items = (RHNode*)malloc(sizeof(RHNode) * capacity);
	if(stack->items == NULL){
		free(stack);
		return NULL;
	}
	
	stack->top = -1;
	stack->capacity = capacity;
	return stack;
}

//Free stack
void rh_stack_free(RHStack *stack){
	if(stack == NULL) return;
	
	for(int i = 0; i <= stack->top; i++){
		if(stack->items[i].directive) free(stack->items[i].directive);
		if(stack->items[i].macro) free(stack->items[i].macro);
	}
	
	free(stack->items);
	free(stack);
}

//Push direcvite
int rh_stack_push(RHStack *stack, const char *directive, const char *macro, int is_active){
	if(stack == NULL || stack->top >= stack->capacity - 1){
		return -1; //overflow
	}
	
	stack->top++;
	
	//copy directive
	stack->items[stack->top].directive = (char*)malloc(strlen(directive) + 1);	//+1 for \0
	if(stack->items[stack->top].directive == NULL){
		stack->top--;
		return -1;
	}
	strcpy(stack->items[stack->top].directive, directive);
	
	//copy macro
	if(macro != NULL){
		stack->items[stack->top].macro = (char*)malloc(strlen(macro) + 1); 		//+1 for \0
		
		//if malloc fails we dont push the element (directive + macro)
		if(stack->items[stack->top].macro == NULL){
			free(stack->items[stack->top].directive);
			stack->top--;
			return -1;
		}

		strcpy(stack->items[stack->top].macro, macro);
	}else{	//null if endif
		stack->items[stack->top].macro = NULL;
	}

	//set active flag
	stack->items[stack->top].is_active = is_active;
	return 0;
}

//Pop directive
int rh_stack_pop(RHStack *stack){
	if(stack == NULL || stack->top < 0){
		return -1; //underflow
	}
	
	//free strings
	if(stack->items[stack->top].directive != NULL) free(stack->items[stack->top].directive);
	if(stack->items[stack->top].macro != NULL) free(stack->items[stack->top].macro);
	
	//decrease top, below element now is top
	stack->top--;
	return 0;
}

//empty stack check
int rh_stack_is_empty(RHStack *stack){
	return (stack == NULL || stack->top < 0);
}

//Check if we need to process
int rh_stack_is_active(RHStack *stack){
	if(stack == NULL || stack->top < 0){
		return 1; //empty stack
	}
	
	//check for any inactive block
	for(int i = 0; i <= stack->top; i++){
		if(stack->items[i].is_active == 0){
			return 0; 
		}
	}
	
	return 1;
}

// Handle include directive
//starts a classifier with the new file path
int rh_handle_include(const char *filename, const char* output_file){
    //Check if the filename is correct
	if(rh_filename_check(filename) == 0){	//file is not a valid format
		return 0;
	}
	else if(rh_filename_check(filename) == 1){	//file is in ""
		//remove "" from "path.c" ---> path.c
		int path_len = strlen(filename) - 2;
		char *path = malloc(path_len + 1);
		if(path == NULL) return 0;
		strncpy(path, filename+1, path_len);
		path[path_len] = '\0';
		
		//Initialize a new classifier starting from the provided path
		int result = cl_classifier(path, output_file);
		free(path);
		return result;
	}

	return 0; //should not reach here, but keep compiler happy
}

int rh_filename_check(const char *filename){
	//Check if the filename is correct, in ""
	if(filename[0] == '\"' && filename[strlen(filename)-1] == '\"') return 1;
	return 0;
}

void rh_handle_ifdef_directive(char *macro, MacroTable *table, RHStack *stack, int is_negated, RHProcessMacro *process_macro){
	//check if any previous directive is marked as inactive
	int prev_directive = rh_stackis_active(stack);
	
	//check if the macro exists
	int macro_exists = st_exists(table, macro);
	
	//calculate activity based on negation
	char *directive_name;
	int activity = 0;
	if(is_negated){
		// ifndef: active if macro does NOT exist
		if(prev_directive == 1 && macro_exists == 0){
			activity = 1;
		}
		directive_name = "ifndef";
	}else{
		// ifdef: active if macro exists
		if(prev_directive == 1 && macro_exists == 1){
			activity = 1;
		}
		directive_name = "ifdef";
	}
	
	//push onto the stack
	rh_stack_push(stack, directive_name, macro, activity);
	
	//set process_macro based on activity
	process_macro->process = activity;

	return;
}

int rh_handle_endif(RHStack *stack){
	//pop the top directive
	if(rh_stackpop(stack) == 0){
		//pop successful continue processing
		return 1;
	}
	//pop fails = underflow / no matching ifdef/ifndef
	printf("Error: Unmatched endif directive found.\n");
	exit(EXIT_FAILURE);
	return 0;
}

