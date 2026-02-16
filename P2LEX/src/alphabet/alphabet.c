/*
 * -----------------------------------------------------------------------------
 * alphabet.c 
 *
 * Usage:
 *     Called from the automata module or test modules to check what type of character is it.
 *
 * Status:
 *     Initial development — logic to handle alphabet is not yet implemented.
 *
 * Author: []
 * -----------------------------------------------------------------------------
 */

#include "./alphabet.h"


int al_simbolo_index(char c) {

    switch(c) {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'h': return 6;
        case 'i': return 7;
        case 'l': return 8;
        case 'n': return 9;
        case 'o': return 10;
        case 'r': return 11;
        case 's': return 12;
        case 't': return 13;
        case 'u': return 14;
        case 'v': return 15;
        case 'w': return 16;
        default:  return -1;
    }
}


void al_init_keyword_automata(Automata *keyword) {

    // Inicialización básica
    keyword->numstates   = 23;
    keyword->numsymbols  = 17;
    keyword->numcols     = 17;
    keyword->initial_state = 0;
    keyword->current_state = 0;

    // Inicializar tabla de transiciones a -1
    for (int i = 0; i < keyword->numstates; i++) {
        for (int j = 0; j < keyword->numcols; j++) {
            keyword->transitions[i][j] = -1;
        }
    }

    // -------- Transiciones --------

    // Desde q0
    keyword->transitions[0][2] = 18; //c
    keyword->transitions[0][4] = 3; //e
    keyword->transitions[0][7] = 1; //i
    keyword->transitions[0][11] = 12; //r
    keyword->transitions[0][15] = 22; //v
    keyword->transitions[0][16] = 7; //w

    // Desde q1
    keyword->transitions[1][5] = 2; //f
    keyword->transitions[1][8] = 22; //n

    // Desde q3
    keyword->transitions[3][simbolo_index('i')] = 4;

    // Desde q4
    keyword->transitions[4][simbolo_index('r')] = 5;

    // Desde q5
    keyword->transitions[5][simbolo_index('e')] = 6;

    // Desde q7
    keyword->transitions[7][simbolo_index('h')] = 8;

    // Desde q8
    keyword->transitions[8][simbolo_index('i')] = 9;

    // Desde q9
    keyword->transitions[9][simbolo_index('l')] = 10;

    // Desde q10
    keyword->transitions[10][simbolo_index('d')] = 11;

    // Desde q12
    keyword->transitions[12][simbolo_index('d')] = 13;
}


void al_init_operators_automata(Automata *operators){

    operators->num_states = 2;
    operators->numsymbols = 4;

    operators->numcols = 4;

    operators->initial_state = 0;
    operators->current_state = 0;

    // Inicializar tabla de transiciones a -1
    for (int i = 0; i < operators->numstates; i++) {
        for (int j = 0; j < operators->numcols; j++) {
            operators->transitions[i][j] = -1;
        }
    }

    // -------- Transiciones --------

    // Desde q0
    operators->transitions[0][simbolo_index('=')] = 1;
    operators->transitions[0][simbolo_index('>')] = 1;
    operators->transitions[0][simbolo_index('+')] = 1;
    operators->transitions[0][simbolo_index('*')] = 1;
}