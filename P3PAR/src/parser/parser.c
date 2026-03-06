/*
 * -----------------------------------------------------------------------------
 * parser.c 
 *
 * Usage:
 *     Called from the global context module to parse TokenList using the SRA.
 *
 * Status:
 *     In progress.
 *
 * Author: Anna Vasileva
 * -----------------------------------------------------------------------------
 */

#include "./parser.h"

Parser* parser_create(SRA* sra, TokenList* tokens){
    if(!sra || !tokens) return NULL;

    Parser* p = malloc(sizeof(Parser));
    if(!p) return NULL;

    p->SRA = sra;
    p->token = tokens;

    return p;
}

void parser_destroy(Parser* parser){
    if(!parser) return;
    free(parser);
}

Symbol* parser_token_to_symbol(Token token, Language *language)
{
    
    for(int i = 0; i < language->num_symbols; i++){
        if(strcmp(token.lexeme, language->symbols[i]->name) == 0)
            return language->symbols[i];
    }

    return NULL;
}

char* get_name_operation(int action){
    switch(action){
        case ACT_REDUCE:
            return ACT_REDUCE_NAME;
            break;
        case ACT_SHIFT:
            return ACT_SHIFT_NAME;
            break;
        case ACT_ACCEPT:
            return ACT_ACCEPT_NAME;
            break;
        break;
        case ACT_ERROR:
            return ACT_ERROR_NAME;
            break;
        break;
    }
}

int parser_run(Parser* parser, Language* language, FILE *output_file){
    if(!parser || !parser->SRA || !parser->token) return PARSE_ERROR;

    int current_input_token = 0;

    TokenNode* node = parser->token->head;
    while(node != NULL){
        printf("TOP: %d\n", parser->SRA->stack->top);
        Token* tok = &node->token;
        
        Symbol* sym = parser_token_to_symbol(*tok, language);
        int prev_state = parser->SRA->automata->current_state;
        Stack prev_stack = *(parser->SRA->stack);
        int action = sra_action(parser->SRA, *sym);
        
        o_output_handler(output_file, current_input_token, &prev_stack, get_name_operation(action),
            prev_state, language, parser->token);

        if(action == ACT_SHIFT){
            node = node->next;
            current_input_token++;
        }
        
        else if(action == ACT_REDUCE){
            continue;
        }
        
        else if(action == ACT_ACCEPT || action == ACT_ERROR){
            return action;
        }


    }

    return 0;
}