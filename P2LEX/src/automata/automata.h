#ifndef MODULE_AUTOMATA_H
#define MODULE_AUTOMATA_H

#include "../main.h"
#define MAXLEN 128
#define MAXCOLS 128

typedef enum TokenCategory TokenCategory; // to avoid circular dependency with token_handler.h

/*
    struct to indicate the symbols of the alphabet of the automata.
*/
typedef struct AlphabetSymbol AlphabetSymbol;
/*
    struct to indicate if each state is accepting, and if it is, the category of the token that it accepts.
*/
typedef struct AcceptingState{
    int flag; // to indicate if the state is accepting or not
    TokenCategory category; // to indicate the category of the token if the state is accepting
} AcceptingState;

/*
    struct to indicate the current state of the automata.
*/
typedef struct Automata{
    int numsymbols; // actual number of symbols of the alphabet of the automata
    int numstates; // actual number of states of the automata
    int numcols; // number of columns in the compressed table
    AlphabetSymbol *alphabet; // the alphabet of the automata
    int transitions[MAXLEN][MAXCOLS]; // the transition table of the automata
    int initial_state; // to indicate the initial state of the automata    
    int current_state; // to indicate the current state of the automata
    AcceptingState accept[MAXLEN]; // if the each state is accepting state, and this information.
} Automata;

/*
    struct to indicate the lookahead of the automata.
*/
typedef struct Lookahead{
    int has; // to indicate if the lookahead has a character or not
    char character; // the character to lookahead
} Lookahead;

// No magic numbers... (requirements)
#define A_CONTINUE 0 // can keep going (consumed current character)
#define A_ACCEPT 1 // cannot continue with lookahead, but is accepting state (accept token)
#define A_FAIL -1 // used in case of failure and to indicate that the character is not accepted.
#define A_CAN_NOT_CONTINUE 0 // used to indicate that the character is accepted but cannot continue with lookahead
#define A_CAN_CONTINUE 1 // used to indicate that the character is accepted and can continue with lookahead
#define A_ADV_SUCCESS 1 // used to indicate that the automata advanced successfully to the next state
#define A_ADV_FAIL 0 // used to indicate that the automata did not advance to the next
#define A_NOT_ACCEPTED 0 // used to indicate that the character is not accepted by the automata
#define A_ACCEPTED 1 // used to indicate that the character is accepted by the automata


// functions:
Automata* a_create_automata(int numsymbols, int numstates, int numcols, AlphabetSymbol *alphabet, int trans[MAXLEN][MAXCOLS], int initial_state, int current_state, int *accepting_state, TokenCategory category); // to create an automata with the parameters.
int a_accepting_state(Automata *automata, int state); // if is accepting state or not. (handling to scanner)
int a_advance_automata(Automata *automata, char character);
int a_mapping_alphabet(Automata *automata, char character); // to map the character of the scanner to the column of the transition table of the automata.
int a_next_state(Automata *automata, char character); // to compute the nex state of the transition between current state and the character.
int a_process(Automata *automata, char character, Lookahead *lookahead); // to process the character and the lookahead, and return if can continue, accept or fail.
void a_reset_automata(Automata *automata); // to reset the automata to the initial state.
void a_destroy_automata(Automata *automata); // to free the memory of the automata 

#endif