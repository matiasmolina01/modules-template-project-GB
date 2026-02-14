/*
 * -----------------------------------------------------------------------------
 * scanner.c 
 *
 * Usage:
 *     Called from the main file or test modules to orcherstrate the whole program.
 *
 * Status:
 *     Initial development — logic to handle scanner is not yet implemented.
 *
 * Author: [Franco Olano]
 * -----------------------------------------------------------------------------
 */

#include "./scanner.h"

void s_init_responses(int responses[], int num){
    for(int i = 0; i < num; i++){
        responses[i] = A_CONTINUE;
    }
}

void s_run_automatas(Automata** automata_list, int*automata_responses, char current_char, char lookahead){
    
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        if(automata_list[i] == A_CONTINUE)
        automata_responses[i] = a_process(automata_list[i], current_char, lookahead);
    }
}

void s_accept_token(GlobalContext* global_context, int automata_idx){
    Automata * accepted_automata = global_context->automatas_list[automata_idx];

    t_token_update_category(global_context->current_token,(TokenCategory) accepted_automata->accept->category);

    tl_token_list_add(global_context->token_list, *global_context->current_token);
}

        
void s_reject_token(GlobalContext* global_context){
    t_token_update_category(global_context->current_token, (TokenCategory) CAT_NONRECOGNIZED);
    tl_token_list_add(global_context->token_list, *global_context->current_token);
}


void s_check_responses(GlobalContext* global_context, int* automata_responses){

    int token_status = CURRENT_TOKEN_FAIL;

    for(int i = 0; i < NUM_AUTOMATAS; i++){

        switch(automata_responses[i]){

            case A_ACCEPT:
            token_status = CURRENT_TOKEN_ACCEPTED;
            s_accept_token(global_context, i);
            global_context->current_token = tl_token_create();
            break;

            case A_CONTINUE:
            token_status = CURRENT_TOKEN_CONTINUE;
            break;
        } 
    }

    if(token_status == CURRENT_TOKEN_FAIL){
        s_reject_token(global_context);
        global_context->current_token = tl_token_create();
    }
}


/*
    Implements scanner main functionality

    Parameters:
        GlobalContext*: previously created global context
*/
void s_scanner(GlobalContext* global_context) {

    int automata_reponses[NUM_AUTOMATAS];
    
    s_init_responses(automata_reponses, NUM_AUTOMATAS);

    global_context->current_token = tl_token_create();
    char current_char, lookahead;
    // TODO handler cases where first chars do not exist

    current_char = i_read_char(global_context->input);
    lookahead = i_read_char(global_context->input);

    t_token_append_char(global_context->current_token, current_char);

    while(global_context->input->is_eof == 0){

        s_run_automatas(global_context->automatas_list, automata_reponses, current_char, lookahead);

        s_check_responses(global_context, automata_reponses);

        t_token_append_char(global_context->current_token, lookahead);

        current_char = lookahead;
        lookahead = i_read_char(global_context->input);
    
    }

    o_output_handler(global_context->token_list, "output_file");
    // TODO change file name
}