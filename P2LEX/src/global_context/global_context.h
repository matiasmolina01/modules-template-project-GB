#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include "../main.h"

typedef struct Automata Automata;
typedef struct Token Token;
typedef struct TokenList TokenList;

typedef struct GlobalContext{
	Automata* automatas_list[NUM_AUTOMATAS];
	Token* current_token;
	TokenList* token_list;
	// InputStruct...
}GlobalContext;

GlobalContext* i_init();

#endif