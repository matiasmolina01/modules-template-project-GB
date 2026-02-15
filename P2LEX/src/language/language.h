#ifndef MODULE_LANGUAGE_H
#define MODULE_LANGUAGE_H

#include "../main.h"

#define NUM_AUTOMATAS 6

#define OPERATOR_AUTOMATA 0
#define SPECIAL_CHAR_AUTOMATA 1
#define NUMBERS_AUTOMATA 2
#define KEYWORDS_AUTOMATA 3
#define LITERALS_AUTOMATA 4
#define IDENTIFIERS_AUTOMATA 5

#define DEAD_TRANSITION -1
#define START_STATE 0

#define NUM_STATES_OPERATOR_AUTOMATA 2
#define NUM_SYMBOLS_OPERATOR_AUTOMATA 4
// #define NUM_COLS_OPERATOR_AUTOMATA 4 ???? TODO
// TODO define rest of automatas
// ....


typedef struct Automata Automata;

Automata** l_init_automatas();

#endif