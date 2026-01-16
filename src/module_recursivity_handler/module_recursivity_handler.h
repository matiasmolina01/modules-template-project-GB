#ifndef MODULE_RECURSIVITY_HANDLER_H
#define MODULE_RECURSIVITY_HANDLER_H

#include "../main.h"

int recursivity_handler(int n);

void rh_handle_directive(int directive, const char *arg);

void rh_handle_include(const char *filename);

int rh_resolve_include(const char *pre_path, char *resolved_path);

void rh_handle_ifdef(const char *macro, int is_negated);

void rh_skip_until_endif();

void rh_handle_endif();

void rh_enter_context();

void rh_exit_context();

int rh_is_in_recursive_context(const char *filename);

void rh_error(const char *message);

#endif
 