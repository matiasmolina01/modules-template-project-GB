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

int rh_handle_include(char *filename, args_state_t* args_state){
    printf("Handling include for file: %s\n", filename);
    
    if(rh_filename_check(filename) != 0){
        return -1;
    }
    
    // Remove quotes from filename
    size_t len = strlen(filename);
    char *clean_name = (char*)malloc(len - 1); // -2 for quotes, +1 for \0
    if(!clean_name){
        return -1;
    }
    strncpy(clean_name, filename + 1, len - 2);
    clean_name[len - 2] = '\0';
    
    // Find directory portion of input_path
    char *original_path = args_state->input_path;
    char *last_slash = strrchr(original_path, '/');
    if(!last_slash){
        last_slash = strrchr(original_path, '\\');
    }
    
    char *full_path;
    if(last_slash != NULL){
        size_t dir_length = (size_t)(last_slash - original_path) + 1;
        full_path = (char*)malloc(dir_length + strlen(clean_name) + 1);
        if(!full_path){
            free(clean_name);
            return -1;
        }
        strncpy(full_path, original_path, dir_length);
        full_path[dir_length] = '\0';
        strcat(full_path, clean_name);
    }else{
        full_path = strdup(clean_name);
    }
    free(clean_name);
    
    printf("Full include path: %s\n", full_path);
    
    // Create new args_state
    args_state_t new_args = *args_state;
    strcpy(new_args.input_path, full_path);
    free(full_path);
    
    int result = cl_classifier(&new_args);
    printf("Finished classifier\n");
    
    return result;
}

int rh_filename_check(const char *filename){
	//Check if the filename is correct, in ""
	if(filename[0] == '\"' && filename[strlen(filename)-1] == '\"') return 0;
	return -1;
}

void rh_handle_ifdef_directive(char *macro, MacroTable *table, RHStack *stack, int is_negated, RHProcessMacro *process_macro){
	//check if any previous directive is marked as inactive
	int prev_directive = rh_stack_is_active(stack);
	
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
	if(rh_stack_pop(stack) == 0){
		//pop successful continue processing
		return 1;
	}
	//pop fails = underflow / no matching ifdef/ifndef
	printf("Error: Unmatched endif directive found.\n");
	exit(EXIT_FAILURE);
	return 0;
}

