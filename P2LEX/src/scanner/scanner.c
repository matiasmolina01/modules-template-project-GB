/*
 * -----------------------------------------------------------------------------
 * scanner.c 
 *
 * Usage:
 * Called from the main file to create a token list.
 * Uses the Automata module and Token Handler module as helpers.
 *
 * Status:
 * Final.
 *
 * Author: Franco Olano
 * -----------------------------------------------------------------------------
 */

#include "./scanner.h"
#include <stdio.h> // Added purely for the debug printfs

/*
    Initializes the automata respones as default state (A_CONTINUE)
    Parameters:
            int responses[]: empty array
            int num: number of elements to be initialized in the array 
*/
void s_init_responses(int responses[], int num){
    printf("[DEBUG SCANNER] s_init_responses: Initializing %d automata responses to A_CONTINUE.\n", num);
    for(int i = 0; i < num; i++){
        responses[i] = A_CONTINUE;
        printf("[DEBUG SCANNER] s_init_responses: responses[%d] set to A_CONTINUE.\n", i);
    }
}

/*
    Calls the a_process function for each automata which had a A_CONTINUE response
    Parameters:
            automata_list: array of automata pointer which are going to be updated
            automata_responses: array to be filled with the automata responses
            current_char: char to be processed by the automata
            lookahead: char to be analyzed by the automata to see if it could be processed later
*/
void s_run_automatas(Automata** automata_list, int*automata_responses, char current_char, char lookahead_char, int has_lookahead){

    printf("[DEBUG SCANNER] s_run_automatas: Running automatas for current_char='%c' (ASCII: %d), lookahead='%c' (has_lookahead: %d).\n", current_char, current_char, lookahead_char, has_lookahead);
    Lookahead *lookahead = malloc(sizeof(Lookahead));
    lookahead->has = has_lookahead;
    lookahead->character = lookahead_char;
    
    for(int i = 0; i < NUM_AUTOMATAS; i++){
        printf("[DEBUG SCANNER] s_run_automatas: Checking automata index %d...\n", i);
        if(automata_responses[i] == A_CONTINUE) {
            printf("[DEBUG SCANNER] s_run_automatas: Automata %d state is A_CONTINUE. Calling a_process...\n", i);
			automata_responses[i] = a_process(automata_list[i], current_char, lookahead);
            printf("[DEBUG SCANNER] s_run_automatas: Automata %d returned response code %d.\n", i, automata_responses[i]);
        } else {
            printf("[DEBUG SCANNER] s_run_automatas: Automata %d skipped (not A_CONTINUE).\n", i);
        }
    }
    free(lookahead);
}

/*
    Creates a new token and sets it to the current_token variable
    Parameter:
        global_context: GlobalContext with input information (line, col) and current token
*/
void s_set_new_current_token(GlobalContext* global_context){
    printf("[DEBUG SCANNER] s_set_new_current_token: Creating new token at Line: %d, Col: %d.\n", global_context->input->line_number, global_context->input->column);
    global_context->current_token = t_token_create(global_context->input->line_number, global_context->input->column);
}

/*
    Function to process the token for a given category.
    Updates the token category and adds it to the final token list.
    Parameters:
        global_context: global context with token and token list
        category: one of the valid token categories 
*/
void s_process_token(GlobalContext* global_context, TokenCategory category){
    printf("[DEBUG SCANNER] s_process_token: Processing token with category code %d.\n", category);
    t_token_update_category(global_context->current_token, category);
    tl_token_list_add(global_context->token_list, *global_context->current_token);
    printf("[DEBUG SCANNER] s_process_token: Token added to token_list.\n");
}

/*
    Function to accept a Token given that an automata accepted it
    Parameters:
            global_context: global context with automata and token list
            automata_idx: index of the automata (on the automata list) accepting the Token
*/
void s_accept_token(GlobalContext* global_context, int automata_idx){
    printf("[DEBUG SCANNER] s_accept_token: Accepting token from automata index %d.\n", automata_idx);
    Automata * accepted_automata = global_context->automatas_list[automata_idx];

	int st = accepted_automata->current_state;

    TokenCategory category = accepted_automata->accept[st].category;
    printf("[DEBUG SCANNER] s_accept_token: Automata category resolved to %d.\n", category);

    s_process_token(global_context, category);
    s_set_new_current_token(global_context);
}


/*
    Function to reject a Token given that all automatas rejected it
    Parameters:
            global_context: global context with automata and token list
*/
void s_reject_token(GlobalContext* global_context){
    printf("[DEBUG SCANNER] s_reject_token: Rejecting token. Assigning CAT_NONRECOGNIZED.\n");
    s_process_token(global_context, (TokenCategory) CAT_NONRECOGNIZED);
    s_set_new_current_token(global_context);
}


/*
    Checks the automata responses after processing a character.
    Needs to accept a token if there is an automata which accepted the lexeme
    or reject if every automata failed to process the character (had no valid transitions or in dead state).
    Continue processing the same token token otherwise.
    Parameters:
        global_context: Global Context of the program
        automata_responses: array of automata responses.

*/
void s_check_responses(GlobalContext* global_context, int* automata_responses){
    printf("[DEBUG SCANNER] s_check_responses: Evaluating automata responses...\n");
    int token_status = CURRENT_TOKEN_FAIL;

    for(int i = 0; i < NUM_AUTOMATAS; i++){
        printf("[DEBUG SCANNER] s_check_responses: Automata %d response is %d.\n", i, automata_responses[i]);
        switch(automata_responses[i]){

            case A_CONTINUE:
            printf("[DEBUG SCANNER] s_check_responses: Automata %d triggered A_CONTINUE.\n", i);
            token_status = CURRENT_TOKEN_CONTINUE;
            break;

            case A_ACCEPT:
            printf("[DEBUG SCANNER] s_check_responses: Automata %d triggered A_ACCEPT.\n", i);
            token_status = CURRENT_TOKEN_ACCEPTED;
            s_accept_token(global_context, i);
            break;
        } 
    }

    if(token_status == CURRENT_TOKEN_FAIL){
        printf("[DEBUG SCANNER] s_check_responses: Status is CURRENT_TOKEN_FAIL. Rejecting token.\n");
        s_reject_token(global_context);
    } else {
        printf("[DEBUG SCANNER] s_check_responses: Token status resolved to %d.\n", token_status);
    }
}


/*
    Obtains the lookahead from the input and checks wether there is a next character
    Parameters:
            GlobalContext: global context with input datastructure
            lookahead: lookahead's pointer
            has_lookahead: has lookahead property variable's pointer
*/
void s_get_lookahead(GlobalContext* global_context, char*lookahead, int* has_lookahead){
    printf("[DEBUG SCANNER] s_get_lookahead: Reading next char from input...\n");
    *lookahead = i_read_char(global_context->input);
    printf("[DEBUG SCANNER] s_get_lookahead: Read char '%c' (ASCII: %d).\n", *lookahead, *lookahead);
    
    if (*lookahead == NULL){
        printf("[DEBUG SCANNER] s_get_lookahead: Lookahead is NULL. Setting NO_LOOKAHEAD.\n");
        *has_lookahead = NO_LOOKAHEAD;
    } else {
        printf("[DEBUG SCANNER] s_get_lookahead: Lookahead is valid.\n");
    }
}


/*
    Implements scanner main functionality

    Parameters:
        GlobalContext*: previously created global context
*/
void s_scanner(GlobalContext* global_context) {
    printf("[DEBUG SCANNER] s_scanner: === SCANNER STARTED ===\n");

    // INITIAL CONFIGURATION

        // Initial configuration of automata responses
        printf("[DEBUG SCANNER] s_scanner: Starting initial configuration...\n");
        int automata_reponses[NUM_AUTOMATAS];
        s_init_responses(automata_reponses, NUM_AUTOMATAS);

        // Initial configuration of current char and lookahead
        char current_char, lookahead;
        int has_lookahead = HAS_LOOKAHEAD;
        
        printf("[DEBUG SCANNER] s_scanner: Reading initial current_char...\n");
        current_char = i_read_char(global_context->input);
        printf("[DEBUG SCANNER] s_scanner: Initial current_char is '%c' (ASCII: %d).\n", current_char, current_char);
        
        //s_get_lookahead(global_context, &lookahead, &has_lookahead);

        // Create first token
        s_set_new_current_token(global_context);
        printf("[DEBUG SCANNER] s_scanner: Appending current_char to token...\n");
        t_token_append_char(global_context->current_token, current_char);

    // END OF INITIAL CONFIGURATION


    // MAIN LOOP: until file is completely processed
    printf("[DEBUG SCANNER] s_scanner: Entering main loop...\n");
    while(global_context->input->is_eof == NO_EOF){
		printf("[DEBUG SCANNER] s_scanner: --- Loop Iteration Start ---\n");
        s_get_lookahead(global_context, &lookahead, &has_lookahead);

        s_run_automatas(global_context->automatas_list, automata_reponses, current_char, lookahead, has_lookahead);

        s_check_responses(global_context, automata_reponses);

        printf("[DEBUG SCANNER] s_scanner: Appending lookahead '%c' to token...\n", lookahead);
        t_token_append_char(global_context->current_token, lookahead);

        printf("[DEBUG SCANNER] s_scanner: Shifting lookahead to current_char...\n");
        current_char = lookahead;
        
        printf("[DEBUG SCANNER] s_scanner: --- Loop Iteration End ---\n");
    }

    printf("[DEBUG SCANNER] s_scanner: === SCANNER FINISHED (EOF REACHED) ===\n");
}