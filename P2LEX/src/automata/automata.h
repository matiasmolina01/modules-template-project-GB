#ifndef MODULE_AUTOMATA_H
#define MODULE_AUTOMATA_H

#include "../main.h"
#define MAXLEN 128
#define MAXCOLS 128

/*
    struct to indicate the symbols of the alphabet of the automata.
*/
typedef struct{
    char name; // symbol of the alphabet
    int col; // columna in the table
} AlphabetSymbol;

/*
    struct to indicate if each state is accepting, and if it is, the category of the token that it accepts.
*/
typedef struct{
    int flag; // to indicate if the state is accepting or not
    char category[MAXLEN]; // to indicate the category of the token if the state is accepting
} AcceptingState;

/*
    struct to indicate the current state of the automata.
*/
typedef struct {
    int numsymbols; // actual number of symbols of the alphabet of the automata
    int numstates; // actual number of states of the automata
    int numcols; // number of columns in the compressed table
    AlphabetSymbol alphabet[MAXLEN]; // the alphabet of the automata
    int transitions[MAXLEN][MAXCOLS]; // the transition table of the automata
    int initial_state; // to indicate the initial state of the automata    
    int current_state; // to indicate the current state of the automata
    AcceptingState accept[MAXLEN]; // if the each state is accepting state, and this information.
} Automata;

/*
    struct to indicate the lookahead of the automata.
*/
typedef struct{
    int has; // to indicate if the lookahead has a character or not
    char character; // the character to lookahead
} Lookahead;

// No magic numbers... (requirements)
#define A_CONTINUE 0 // can keep going (consumed current character)
#define A_ACCEPT 1 // cannot continue with lookahead, but is accepting state (accept token)
#define A_FAIL -1 // cannot continue with lookahead, and is not accepting state (fail token)

// functions:
int a_is_accepting_state(Automata *automata, int state); // if is accepting state or not. (handling to scanner)
int a_advance_automata(Automata *automata, char character);
int a_mapping_alphabet(Automata *automata, char character); // to map the character of the scanner to the column of the transition table of the automata.
int a_next_state(Automata *automata, char character); // to compute the nex state of the transition between current state and the character.
int a_process(Automata *automata, char character, Lookahead *lookahead); // to process the character and the lookahead, and return if can continue, accept or fail.
void a_reset_automata(Automata *automata); // to reset the automata to the initial state.

#endif