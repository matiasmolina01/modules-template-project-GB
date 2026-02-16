/*
 * -----------------------------------------------------------------------------
 * automata.c 
 *
 * Usage:
 *     Called from the controller module or test modules to check what category the word is.
 *
 * Status:
 *     Initial development — logic to handle automata is not yet implemented.
 *
 * Author: Matias Molina
 * -----------------------------------------------------------------------------
 */

#include "./automata.h"

/*
    Function to create an automata with the parameters.

    Returns:
        Automata* --> pointer to the created automata.
        NULL --> failure (invalid parameters or memory allocation failure).
*/
Automata* a_create_automata(int numsymbols, int numstates, int numcols, AlphabetSymbol *alphabet, int trans[MAXLEN][MAXCOLS], int initial_state, int current_state, int *accepting_states, TokenCategory category){
    // validations for the parameters...
    if(numstates <= 0 || numstates > MAXLEN){
        //printf("Invalid number of states: %d. Must be between 1 and %d.\n", numstates, MAXLEN);// ------- ERROR @alex
        e_error_report(306);
		return NULL;
    }
    if(numcols <= 0 || numcols > MAXCOLS){
        //printf("Invalid number of columns: %d. Must be between 1 and %d.\n", numcols, MAXCOLS);// ------- ERROR @alex
        e_error_report(306);
        return NULL;
    }

    if(numsymbols <= 0 || numsymbols > MAXLEN){
        //printf("Invalid number of symbols: %d. Must be between 1 and %d.\n", numsymbols, MAXLEN);
		e_error_report(306);
        return NULL;
    } 

    if(alphabet == NULL){
        //printf("Alphabet is NULL.\n"); // ------- ERROR @alex
        e_error_report(308);
		return NULL;
    }
    if(accepting_states == NULL){
        //printf("Accepting states info is NULL.\n");// ------- ERROR @alex
        e_error_report(309);
        return NULL;
    }

    if(initial_state < 0 || initial_state >= numstates){
        //printf("Invalid initial state: %d. Must be between 0 and %d.\n", initial_state, numstates - 1);// ------- ERROR @alex
        e_error_report(306);
		return NULL;
    }

    // AUTOMATA CREATION
    Automata *a = (Automata*)malloc(sizeof(Automata)); // allocate memory for the automata
    if(a == NULL){
        //printf("Memory allocation failed for automata.\n");// ------- ERROR @alex
		e_error_report(307);
		return NULL;
    }
    memset(a, 0, sizeof(*a)); // initialize all fields to 0

    a->numstates = numstates;
    a->numcols = numcols;
    a->numsymbols = numsymbols;
    a->initial_state = initial_state;
    a->current_state = current_state;

    // copy the alphabet
    for(int i = 0; i < numsymbols; i++){
        a->alphabet[i] = alphabet[i];
        if(a->alphabet[i].col < 0 || a->alphabet[i].col >= numcols){ // alphabet not valid
            free(a);
            //printf("Invalid column in alphabet symbol: %d. Must be between 0 and %d.\n", a->alphabet[i].col, numcols - 1);// ------- ERROR @alex
            e_error_report(310);
			return NULL;
        }
    }
    // copy the transition table
    for(int r = 0; r < numstates; r++){
        for(int c = 0; c < numcols; c++){
            a->transitions[r][c] = trans[r][c]; // copy the transition table from the input array
        }
    }
    
    // copy the accepting states info
    for(int i = 0; i < numstates; i++){
        if(accepting_states[i] == 1){
            a->accept[i].flag = 1;
            a->accept[i].category = category; 
        }
    }

    return a; // return the created automata
}


/*
    Function used by next_state to map the character and get the column to use in the matrix for the input c:
    That is to say, found the column of a compressed table of the transition table of the automata that corresponds to the alphabet symbol c.

    Returns:
        col --> return the column of the transition table of the automata.
        A_FAIL (-1) --> failure or not found in alphabet

*/
int a_mapping_alphabet(Automata *automata, char c){
    if(automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return A_FAIL; // if the automata is null, return failure
    }
    int limit; // to indicate the limit of the alphabet to check...
    
    if(automata->numsymbols > 0){ // ... if numsymbols is greater than 0, we use it as limit
        limit = automata->numsymbols;
    } else{ // ... otherwise we use numcols.
        limit = automata->numcols; 
    }

    for(int i = 0; i < limit; i++){
        if(automata->alphabet[i].name == c){ // if we find the character in the alphabet, return the column
            int col = automata->alphabet[i].col;
            if(col < 0 || col >= automata->numcols){ // if the column is invalid, return failure
                //printf("Invalid column in alphabet symbol: %d. Must be between 0 and %d.\n", col, automata->numcols - 1);// ------- ERROR @alex
                e_error_report(310);
				return A_FAIL;
            }
            return col; // return the column of the transition table of the automata
        }
    }
    return A_FAIL; // not found in the alphabet
}

/*
    Function to compute the next state of the transition between current state and the character. 

    Returns:
        new_state --> the new state after the transition
        0 --> if the character is not accepted
        A_FAIL (-1) --> invalid state or failure.

*/
int a_next_state(Automata *automata, char c){
    if(automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return A_FAIL; // if the automata is null, return failure
    } 
    
    int cr = automata->current_state; // current state
    if(cr < 0 || cr >= automata->numstates){
        //printf("Invalid current state: %d. Must be between 0 and %d.\n", cr, automata->numstates - 1);// ------- ERROR @alex
        e_error_report(312);
		return A_FAIL; // if the current state is invalid, return failure
    }

    int col = a_mapping_alphabet(automata, c); // get the column of the transition table of the automata for the character
    if(col < 0) return 0; // if the character is not in the alphabet, return 0 (not accepted) --> a_mapping_alphabet returns A_FAIL (-1 < 0)

    // if the character is in the alphabet...
    int new_state = automata->transitions[cr][col]; // ...get the new state from the transition table of the automata

    // error handling for the new state...
    if(new_state < 0) return 0; //(not accepted)
    if(new_state >= automata->numstates){
        //printf("Invalid new state: %d. Must be between 0 and %d.\n", new_state, automata->numstates - 1);// ------- ERROR @alex
        e_error_report(313);
		return A_FAIL; // return A_FAIL 
    }

    return new_state; // return the new state after the transition
}


/*
    Function to check if the state is an accepting state or not.

    Returns:
        1 --> if the state is an accepting state.
        0 --> if the state is not an accepting state.
        A_FAIL (-1) --> failure (invalid state or automata is null).
*/
int a_accepting_state(Automata *automata, int state){
    if(automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return 0; // if the automata is null, return failure
    }
    if(state < 0 || state >= automata->numstates) return 0; // if the state is invalid,  (not accepting)
    if(automata->accept[state].flag == 1){
        return 1;
    }
    return 0;
}

/*
    Function to advance the automata with a given character from scanner. The function checks if the character 
    is accepted by the automata, and if it is, it advances to the next state. If the character is not accepted, 
    it does not advance to the next state.
    (MAIN FUNCTION TO ADVANCE THE AUTOMATA WITH A CHARACTER)

    Returns:
        1 --> if the character is accepted and the automata has advanced to the next state and the new state is inside current state.
        0 --> if the character is not accepted and the automata has not advanced to the next state.
        A_FAIL (-1) --> failure
*/
int a_advance_automata(Automata *automata, char c){
    if(automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return A_FAIL; // if the automata is null, return failure
    }
    int new_state = a_next_state(automata, c); // get the new state from the transition table of the automata for the character
    if(new_state > 0){ // we consider that the initial state is always 0, so the new state cannot be 0.
        automata->current_state = new_state; // advance to the new state
        return 1; // character accepted and automata advanced to the next state (success)
    }
    return new_state; // 0 or A_FAIL (-1)

}

/*
    Function to processes the lookahead character of the automata.

    Returns:
        1 --> if there are valid transitions with the lookahead character (can continue)
        0 --> if is not accepting
        A_FAIL (-1) --> failure
*/
int a_lookahead_process(Automata *automata, Lookahead *lookahead){
    if (automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return A_FAIL; // if the automata is null, return failure
    }
    if (lookahead == NULL){
        //printf("Lookahead is NULL.\n"); // ------- ERROR @alex
        e_error_report(314);
		return 0; // if the lookahead is null, return failure
    }
    if (lookahead->has == 0){
        return 0; // and lookahead has no character -> is not accepting
    }

    int new_state = a_next_state(automata, lookahead->character); // get the next state from the transition table of the automata for the lookahead character
    if(new_state > 0) return 1; // if have new_state, there are valid transitions with the lookahead character (can continue)

    return 0; // if not have next state with lookahead character, return 0 (is not accepting)
}

/*
    Function to processes one transition step of the automaton. Consumes current_char, checks if it can continue 
    with lookahead_char, and determines whether to continue, accept, or fail.

    Returns:
        0 (A_CONTINUE) --> current character consumed and can continue with lookahead
        1 (A_ACCEPT) --> current character consumed but cannot continue with lookahead.
        -1 (A_FAIL) --> cannot consume the current character or stopped in a non-accepting state.
*/
int a_process(Automata *automata, char c, Lookahead *lookahead){
    if(automata == NULL || lookahead == NULL){
        //printf("Automata or Lookahead is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		e_error_report(314);
		return A_FAIL; // if the automata or lookahead is null, return failure
    }
    int adv = a_advance_automata(automata, c); // try to advance the automata with the current character
    if(adv == 0 || adv == A_FAIL){ // if the character is not accepted or there is a failure, return fail
        return A_FAIL; // if the character is not accepted, return fail
    }

    int can_continue = a_lookahead_process(automata, lookahead); 
    if(can_continue == 1){ // if the character is not accepted, return fail
        return A_CONTINUE; // can continue with lookahead
    }

    if(a_accepting_state(automata, automata->current_state) == 1){ // if the new state is accepting, return accept
        return A_ACCEPT;
    }
    return A_FAIL;
}

/*
    Function to reset the automata to the initial state. (current state = intial state)
*/
void a_reset_automata(Automata *automata){
    if(automata == NULL){
        //printf("Automata is NULL.\n"); // ------- ERROR @alex
        e_error_report(311);
		return;
    } 
    automata->current_state = automata->initial_state;
}

/*
    Function to free the memory of the automata.
*/
void a_destroy_automata(Automata *automata){
    if(automata == NULL) return;
    free(automata);
}