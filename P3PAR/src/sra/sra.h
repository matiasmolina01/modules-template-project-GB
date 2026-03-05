/*
 * -----------------------------------------------------------------------------
 * sra.h
 *
 * Usage:
 *     si
 *
 * Status:
 *     Finished.
 *
 * 
 * Author: [Alex Ruiz Lopez]
 * -----------------------------------------------------------------------------
 */

#ifndef MODULE_SRA_H
#define MODULE_SRA_H

#include "../main.h"

typedef struct Stack Stack;
typedef struct Symbol Symbol;
typedef struct Automata Automata;
typedef struct Rule Rule;

typedef struct SRA{
	Automata* automata;
	Stack* stack;
}SRA;

void sra_shift(SRA* sra, int state, Symbol input_symbol);

void sra_accept(SRA* sra);

void sra_reduce(SRA* sra, Rule* rule);

int sra_action(SRA* sra, Symbol input_symbol);

Action check_table(SRA* sra, int state, Symbol input_symbol);


#endif