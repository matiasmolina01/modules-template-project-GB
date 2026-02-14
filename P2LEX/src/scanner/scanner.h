#ifndef MODULE_SCANNER_H
#define MODULE_SCANNER_H

#include "../main.h"

#define CURRENT_TOKEN_CONTINUE 0
#define CURRENT_TOKEN_FAIL -1
#define CURRENT_TOKEN_ACCEPTED 1

typedef struct GlobalContext GlobalContext;
typedef struct Automata Automata;

void s_init_responses(int responses[], int num);
void s_run_automatas(Automata** automata_list, int*automata_responses, char current_char, char lookahead);
void s_check_responses(GlobalContext* global_context, int* automata_responses);
void s_scanner(GlobalContext* global_context);

#endif