/*
 * -----------------------------------------------------------------------------
 * language.c 
 *
 * Usage:
 *     Called from the automata module or test modules to check what type of character is it.
 *
 * Status:
 *     Initial development — logic to handle language is not yet implemented.
 *
 * 
 * Author: []
 * -----------------------------------------------------------------------------
 */



#include "./language.h"

int keyword_accepting_states[NUM_STATES_KEYWORD_AUTOMATA] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
};

int special_accepting_states[NUM_STATES_SPECIAL_CHAR_AUTOMATA] = {
    0, 1, 0
};

int operators_accepting_states[NUM_STATES_OPERATOR_AUTOMATA] = {
    0, 1, 0
};

int numbers_accepting_state[NUM_STATES_NUMBERS_AUTOMATA] = {
    0, 1, 0
};

int identifiers_accepting_state[NUM_STATES_IDENTIFIERS_AUTOMATA] = {
    0, 1, 0
};

int literals_accepting_state[NUM_STATES_LITERALS_AUTOMATA] = {
    0, 0, 1, 0
};

AlphabetSymbol keyword_alphabet[NUM_SYMBOLS_KEYWORD_AUTOMATA] = {
    {'i', 0}, {'f', 1}, {'n', 2}, {'t', 3}, {'e', 4}, {'l', 5}, {'s', 6}, {'w', 7}, 
    {'h', 8}, {'r', 9}, {'u', 10}, {'c', 11}, {'a', 12}, {'v', 13}, {'o', 14}, {'d', 15}
};

AlphabetSymbol special_char_alphabet[NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA] = {
    {'(', 0}, 
    {')', 1}, 
    {'[', 2}, 
    {']', 3}, 
    {';', 4}, 
    {'{', 5}, 
    {'}', 6}, 
    {',', 7}
};

AlphabetSymbol numbers_alphabet[NUM_SYMBOLS_NUMBERS_AUTOMATA] = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}
};

AlphabetSymbol literals_alphabet[NUM_SYMBOLS_LITERALS_AUTOMATA] = {
    // a-z -> columnas 0-25
    {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
    {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
    {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
    {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
    {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25},

    // A-Z -> columnas 26-51
    {'A', 26}, {'B', 27}, {'C', 28}, {'D', 29}, {'E', 30},
    {'F', 31}, {'G', 32}, {'H', 33}, {'I', 34}, {'J', 35},
    {'K', 36}, {'L', 37}, {'M', 38}, {'N', 39}, {'O', 40},
    {'P', 41}, {'Q', 42}, {'R', 43}, {'S', 44}, {'T', 45},
    {'U', 46}, {'V', 47}, {'W', 48}, {'X', 49}, {'Y', 50}, {'Z', 51},

    // 0-9 -> columnas 52-61
    {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56},
    {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61},

    // " -> columna 62 (La llave para abrir/cerrar el literal)
    {'"', 62}
};

AlphabetSymbol identifiers_alphabet[NUM_SYMBOLS_IDENTIFIERS_AUTOMATA] = {
    // a-z -> columnas 0-25
    {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
    {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
    {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
    {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
    {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25},

    // A-Z -> columnas 26-51
    {'A', 26}, {'B', 27}, {'C', 28}, {'D', 29}, {'E', 30},
    {'F', 31}, {'G', 32}, {'H', 33}, {'I', 34}, {'J', 35},
    {'K', 36}, {'L', 37}, {'M', 38}, {'N', 39}, {'O', 40},
    {'P', 41}, {'Q', 42}, {'R', 43}, {'S', 44}, {'T', 45},
    {'U', 46}, {'V', 47}, {'W', 48}, {'X', 49}, {'Y', 50}, {'Z', 51},

    // 0-9 -> columnas 52-61 (Solo se aceptan a partir del Estado 1)
    {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56},
    {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}
};

AlphabetSymbol operators_alphabet[NUM_SYMBOLS_OPERATOR_AUTOMATA] = {
    {'=', 0}, 
    {'+', 1}, 
    {'>', 2}, 
    {'*', 3}
};

int keyword_transitions[NUM_STATES_KEYWORD_AUTOMATA][NUM_SYMBOLS_KEYWORD_AUTOMATA] = {
    {1, 22, 22, 22, 3, 22, 22, 6, 22, 10, 22, 15, 22, 18, 22, 22}, // State 0
    {22, 21, 2, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 1
    {22, 22, 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 2
    {22, 22, 22, 22, 22, 4, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 3
    {22, 22, 22, 22, 22, 22, 5, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 4
    {22, 22, 22, 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 5
    {22, 22, 22, 22, 22, 22, 22, 22, 7, 22, 22, 22, 22, 22, 22, 22}, // State 6
    {8, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 7
    {22, 22, 22, 22, 22, 9, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 8
    {22, 22, 22, 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 9
    {22, 22, 22, 22, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 10
    {22, 22, 22, 12, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 11
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 22, 22, 22, 22, 22}, // State 12
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 14, 22, 22, 22, 22, 22, 22}, // State 13
    {22, 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 14
    {22, 22, 22, 22, 22, 22, 22, 22, 16, 22, 22, 22, 22, 22, 22, 22}, // State 15
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 17, 22, 22, 22}, // State 16
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 22, 22, 22, 22, 22, 22}, // State 17
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 19, 22}, // State 18
    {20, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 19
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21}, // State 20
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, // State 21 (Accepting State)
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}  // State 22 (Dead State)
};

#ifdef COUNTCONFIG
/* Counts static language resources: alphabet sizes and transition table sizes. */
void l_count_language_stats(void) {
    count_local_t __cnt_local_lc__;
    c_count_local_init(&__cnt_local_lc__);

    /* Count alphabet symbol definitions */
    COUNTGEN(NUM_SYMBOLS_KEYWORD_AUTOMATA, __cnt_local_lc__);
    COUNTGEN(NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, __cnt_local_lc__);
    COUNTGEN(NUM_SYMBOLS_NUMBERS_AUTOMATA, __cnt_local_lc__);
    COUNTGEN(NUM_SYMBOLS_LITERALS_AUTOMATA, __cnt_local_lc__);
    COUNTGEN(NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, __cnt_local_lc__);
    COUNTGEN(NUM_SYMBOLS_OPERATOR_AUTOMATA, __cnt_local_lc__);

    /* Count transition table entries (as comparisons) */
    COUNTCOMP(NUM_STATES_KEYWORD_AUTOMATA * NUM_SYMBOLS_KEYWORD_AUTOMATA, __cnt_local_lc__);
    COUNTCOMP(NUM_STATES_IDENTIFIERS_AUTOMATA * NUM_SYMBOLS_IDENTIFIERS_AUTOMATA, __cnt_local_lc__);
    COUNTCOMP(NUM_STATES_NUMBERS_AUTOMATA * NUM_SYMBOLS_NUMBERS_AUTOMATA, __cnt_local_lc__);
    COUNTCOMP(NUM_STATES_SPECIAL_CHAR_AUTOMATA * NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA, __cnt_local_lc__);
    COUNTCOMP(NUM_STATES_OPERATOR_AUTOMATA * NUM_SYMBOLS_OPERATOR_AUTOMATA, __cnt_local_lc__);
    COUNTCOMP(NUM_STATES_LITERALS_AUTOMATA * NUM_SYMBOLS_LITERALS_AUTOMATA, __cnt_local_lc__);
}
#endif
	
int identifiers_transitions[NUM_STATES_IDENTIFIERS_AUTOMATA][NUM_SYMBOLS_IDENTIFIERS_AUTOMATA] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

int numbers_transitions[NUM_STATES_NUMBERS_AUTOMATA][NUM_SYMBOLS_NUMBERS_AUTOMATA] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

int special_char_transitions[NUM_STATES_SPECIAL_CHAR_AUTOMATA][NUM_SYMBOLS_SPECIAL_CHAR_AUTOMATA] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2}
};

int operators_transitions[NUM_STATES_OPERATOR_AUTOMATA][NUM_SYMBOLS_OPERATOR_AUTOMATA] = {
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {2, 2, 2, 2}
};

int literals_transitions[NUM_STATES_LITERALS_AUTOMATA][NUM_SYMBOLS_LITERALS_AUTOMATA] = {
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
};


