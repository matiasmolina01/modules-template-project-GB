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

#define NUM_STATES_OPERATOR_AUTOMATA 3
#define NUM_SYMBOLS_OPERATOR_AUTOMATA 4


#define NUM_STATES_KEYWORD_AUTOMATA 23
#define NUM_SYMBOLS_KEYWORD_AUTOMATA 16

#define NUM_STATES_NUMBERS_AUTOMATA 3
#define NUM_SYMBOLS_NUMBERS_AUTOMATA 10

#define NUM_STATES_SPECIAL_CHAR_AUTOMATA 3
#define NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA 8

#define NUM_STATES_IDENTIFIERS_AUTOMATA 3
#define NUM_SYMBOLS_IDENTIFIERS_AUTOMATA 62


#define NUM_STATES_LITERALS_AUTOMATA 4
#define NUM_SYMBOLS_LITERALS_AUTOMATA 63

#define SEPARATORS {' ', '\t', '\n'}
#define SEPARATOR_NUM 3


typedef struct AlphabetSymbol{
    char name; // symbol of the alphabet
    int col; // columna in the table
} AlphabetSymbol;


extern int keyword_transitions[NUM_STATES_KEYWORD_AUTOMATA][NUM_SYMBOLS_KEYWORD_AUTOMATA];
extern int identifiers_transitions[NUM_STATES_IDENTIFIERS_AUTOMATA][NUM_SYMBOLS_IDENTIFIERS_AUTOMATA];
extern int numbers_transitions[NUM_STATES_NUMBERS_AUTOMATA][NUM_SYMBOLS_NUMBERS_AUTOMATA];
extern int special_char_transitions[NUM_STATES_SPECIAL_CHAR_AUTOMATA][NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA];
extern int operators_transitions[NUM_STATES_OPERATOR_AUTOMATA][NUM_SYMBOLS_OPERATOR_AUTOMATA];
extern int literals_transitions[NUM_STATES_LITERALS_AUTOMATA][NUM_SYMBOLS_LITERALS_AUTOMATA];

extern int keyword_accepting_states[NUM_STATES_KEYWORD_AUTOMATA];
extern int special_accepting_states[NUM_STATES_SPECIAL_CHAR_AUTOMATA];
extern int operators_accepting_states[NUM_STATES_OPERATOR_AUTOMATA];
extern int numbers_accepting_state[NUM_STATES_NUMBERS_AUTOMATA];
extern int identifiers_accepting_state[NUM_STATES_IDENTIFIERS_AUTOMATA];
extern int literals_accepting_state[NUM_STATES_LITERALS_AUTOMATA];


extern AlphabetSymbol keyword_alphabet[NUM_SYMBOLS_KEYWORD_AUTOMATA];

extern AlphabetSymbol special_char_alphabet[NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA];
extern  AlphabetSymbol numbers_alphabet[NUM_SYMBOLS_NUMBERS_AUTOMATA];

extern  AlphabetSymbol literals_alphabet[NUM_SYMBOLS_LITERALS_AUTOMATA];


extern  AlphabetSymbol identifiers_alphabet[NUM_SYMBOLS_IDENTIFIERS_AUTOMATA];

extern  AlphabetSymbol operators_alphabet[NUM_SYMBOLS_OPERATOR_AUTOMATA];

typedef struct Automata Automata;

#endif