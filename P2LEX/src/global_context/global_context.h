#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include "../main.h"
/*********	 temporal ****** */
// #include "../alphabet/alphabet.h"
#define NUM_AUTOMATAS 6

///


typedef struct Automata Automata;
typedef struct Token Token;
typedef struct TokenList TokenList;
typedef struct Input Input;
typedef struct Arguments Arguments;

typedef struct GlobalContext{
	Automata* automatas_list[NUM_AUTOMATAS];
	Token* current_token;
	TokenList* token_list;
	Input* input;
	Arguments* arguments;
}GlobalContext;

void gc_init_automatas(Automata** automata_list);

GlobalContext* gc_init(Arguments* arguments);
void gc_destroy(GlobalContext* global_context);

#endif