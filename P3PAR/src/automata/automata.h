#ifndef MODULE_AUTOMATA_H
#define MODULE_AUTOMATA_H

#include "../main.h"
#define MAXLEN 128
#define MAXCOLS 128

/*
    struct to indicate the symbols of the alphabet of the automata.
*/
typedef struct AlphabetSymbol AlphabetSymbol;


/*
    -------------------- temporals struct - until there are declared --------------------
*/
typedef struct Rule Rule;
typedef enum ActionType{
    ACT_SHIFT = 0,
    ACT_REDUCE = 1,
    ACT_ACCEPT = 2,
    ACT_ERROR = 3
} ActionType;

typedef struct Action{
    ActionType type;
    int state; 
    Rule *rule;
} Action;

/*
   -------------------------------------------------------------
*/

/*
    struct to indicate the current state of the automata.
*/
typedef struct Automata{
    int numsymbols; // actual number of symbols of the alphabet of the automata
    int numstates; // actual number of states of the automata
    AlphabetSymbol *alphabet; // the alphabet of the automata
    Action** action_table; // the action table of the automata
    int initial_state; // to indicate the initial state of the automata    
    int current_state; // to indicate the current state of the automata
} Automata;


// No magic numbers... (requirements)
#define A_EMPTY_ERROR -1 // used to indicate that automata dynamic memory is empty (== NULL)
#define A_FAIL -2 // used to indicate that automata action is a fail

// functions:

Automata* a_create_automata(int numsymbols, int numstates, Action** action_table ,AlphabetSymbol *alphabet, int initial_state); // to create an automata with the parameters.
Action a_get_action(Automata *automata, int state, int symbol_id); // to get the action of the automata given a state (row) and a symbol id (column).
int a_reset_automata(Automata *automata); // to reset the automata to the initial state.
int a_destroy_automata(Automata *automata); // to free the memory of the automata 


#endif