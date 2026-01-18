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

int recursivity_handler(int n) {
    printf("Recursivity Handler module, still to be implemented\n");
}

// Handle include directive
//starts a classifier with the new file path
int rh_handle_include(const char *filename){
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
		int result = cl_classifier(path, path);
		free(path);
		return result;
	}
}

int rh_filename_check(const char *filename){
	//Check if the filename is correct, in ""
	if(filename[0] == '\"' && filename[strlen(filename)-1] == '\"') return 1;
	return 0;
}

void rh_handle_ifdef(char *macro, MacroTable *table, rh_process_macro *result){
	//Check if the macro exists in the defined macros list
	if(st_exists(table, macro) == 1){
		result->process = 1; //process the following lines
	}else{
		result->process = 0; //skip the following lines
	}
}

void rh_handle_ifndef(char *macro, MacroTable *table, rh_process_macro *result){
	//Check if the macro exists in the defined macros list
	if(st_exists(table, macro) == 0){
		result->process = 1; //process the following lines
	}else{
		result->process = 0; //skip the following lines
	}
}
