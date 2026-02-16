#ifndef MODULE_SCANNER_H
#define MODULE_SCANNER_H

#include "../main.h"

#define CURRENT_TOKEN_CONTINUE 0
#define CURRENT_TOKEN_FAIL -1
#define CURRENT_TOKEN_ACCEPTED 1

#define HAS_LOOKAHEAD 1
#define NO_LOOKAHEAD 0

#define IS_SEPARATOR 1
#define NO_SEPARATOR 0

typedef struct GlobalContext GlobalContext;
typedef struct Automata Automata;
typedef struct Lookahead Lookahead;
typedef enum TokenCategory TokenCategory;

int s_is_separator(char* lexeme, char separators[], int separator_num);
void s_reset_initial_state(GlobalContext* global_context);
void s_run_automatas(Automata** automata_list, int* automata_responses, char current_char, char lookahead_char, int has_lookahead);
void s_process_token(GlobalContext* global_context, TokenCategory category);
void s_accept_token(GlobalContext* global_context, int automata_idx);
void s_reject_token(GlobalContext* global_context);
void s_check_responses(GlobalContext* global_context);
void s_get_lookahead(GlobalContext* global_context, char*lookahead, int* has_lookahead);
void s_scanner(GlobalContext* global_context);

#endif