#ifndef MODULE_RECURSIVITY_HANDLER_H
#define MODULE_RECURSIVITY_HANDLER_H

#include "../main.h"

typedef struct{
	int process; //0 = skip, 1 = process
} rh_process_macro;

int recursivity_handler(int n);

int rh_handle_include(const char *filename);

int rh_filename_check(const char *filename);

void rh_handle_ifdef(char *macro, MacroTable *table, rh_process_macro *result);

void rh_handle_ifndef(char *macro, MacroTable *table, rh_process_macro *result);


#endif
 