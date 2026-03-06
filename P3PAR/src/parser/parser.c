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
        if(strcmp(token.lexeme, language->symbols[i]) == 0)
            return language->symbols[i];
    }

    return NULL;
}

int parser_run(Parser* parser, Language* language){
    if(!parser || !parser->SRA || !parser->token) return -1;

    TokenNode* node = parser->token->head;
    
    while(node){
        
        Token* tok = &node->token;
        
        Symbol* sym = parser_token_to_symbol(*tok, language);
        
        int action = sra_action(parser->SRA, *sym);
        
        if(action == ACT_SHIFT){
            node = node->next;
        }
        
        else if(action == ACT_REDUCE){
            continue;
        }
        
        else if(action == ACT_ACCEPT){
            return 1;
        }

        else if(action == ACT_ERROR){
            printf("Parser error");
            return -1;
        }
    }

    return 0;
}