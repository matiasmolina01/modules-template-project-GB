/*
 * -----------------------------------------------------------------------------
 * sra.c
 *
 * Usage:
 *     Parser must call sra_action for each input symbol
 *
 * Status:
 *     Finished.
 *
 * 
 * Author: [Alex Ruiz Lopez]
 * -----------------------------------------------------------------------------
 */


#include "./sra.h"

void sra_shift(SRA* sra, int state, Symbol input_symbol){
	//push stackitem int state, int symbolid
	stack_push(sra->stack, input_symbol.id, state);
}

void sra_reduce(SRA* sra, Rule* rule){
	//pop length of rhs
	for(int i=0; i<rule->rhs_length; ++i){
		stack_pop(sra->stack);
	}
	//check top of the stack
	int top_state = stack_top_state(sra->stack);
	
	//create an empty symbol for the action check
	Symbol lhs_symbol = {
		.id = rule->lhs,
		.name = NULL,
		.is_terminal = 0
	};

	Action goto_action = check_table(sra, top_state, lhs_symbol);

	//action will be always a shift
	sra_shift(sra, goto_action.state, lhs_symbol);
}

void sra_accept(SRA* sra){
	printf("Input accepted.\n");
	return;
}

int sra_action(SRA* sra, Symbol input_symbol){
	Action action = check_table(sra, stack_top_state(sra->stack), input_symbol);
	//just to tell the parser which action was performed, for the input to advance
	int performed_action = -1;
	switch(action.type){
		case ACT_SHIFT:
			sra_shift(sra, action.state, input_symbol);
			performed_action = ACT_SHIFT;
			break;
		case ACT_REDUCE:
			sra_reduce(sra, action.rule);
			performed_action = ACT_REDUCE;
			break;
		case ACT_ACCEPT:
			sra_accept(sra);
			performed_action = ACT_ACCEPT;
			break;
		case ACT_ERROR:
			performed_action = ACT_ERROR;
			break;
	}
	return performed_action;
}

Action check_table(SRA* sra, int state, Symbol input_symbol){
	Action action = sra->automata->action_table[state][input_symbol.id];
	return action;
}