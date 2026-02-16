/*
 * -----------------------------------------------------------------------------
 * token_handler.c 
 *
 * Usage:
 *     Called from the scanner module or test modules to handle tokens.
 *
 * Status:
 *     Initial development — logic to handle tokens is not yet implemented.
 *
 * Author: Martí Ponsa
 * -----------------------------------------------------------------------------
 */

#include "./token_handler.h"

// Initial capacity for token lexemes; can be adjusted as needed.
#define INITIAL_LEXEME_CAPACITY 16

// Helper function, just visible in this file, nobody shoudl know how the token category is represented internally
static const char *token_category_to_string(TokenCategory cat) {
    switch (cat) {
        case CAT_NUMBER:        return "NUMBER";
        case CAT_IDENTIFIER:    return "IDENTIFIER";
        case CAT_KEYWORD:       return "KEYWORD";
        case CAT_LITERAL:       return "LITERAL";
        case CAT_OPERATOR:      return "OPERATOR";
        case CAT_SPECIALCHAR:   return "SPECIALCHAR";
        case CAT_NONRECOGNIZED: return "NONRECOGNIZED";
        default:                return "UNKNOWN";
    }
}


// Function to create a new token with specified line and column. This only stores the 
// position information; the lexeme and category will be set later, adding one character at a time.
Token t_token_create(int line, int column) {
    Token t;

    // Allocate memory for the lexeme and initialize it.
    t.lexeme = (char *)malloc(INITIAL_LEXEME_CAPACITY);
    if (!t.lexeme) {
		e_error_report(401);
        //e_error_report(); // This error happens when memory allocation for the token's lexeme fails. We should report this error appropriately.
        exit(EXIT_FAILURE);
    }

    t.length = 0;
    t.capacity = INITIAL_LEXEME_CAPACITY;
    t.lexeme[0] = '\0';

    t.category = CAT_NONRECOGNIZED;
    t.line = line;
    t.column = column;

    return t;
}

// Function to append a character to a token's lexeme, resizing the lexeme buffer if necessary.
// This allows building the lexeme incrementally as characters are read from the input. 
void t_token_append_char(Token *t, char c) {
    if (!t) return;

    // Check if we need to resize the lexeme buffer to accommodate the new character and null terminator.
    if (t->length + 1 >= t->capacity) {
        size_t new_capacity = t->capacity * 2;

        char *new_lexeme = (char *)realloc(t->lexeme, new_capacity);
        if (!new_lexeme) {
			e_error_report(401);
            //e_error_report(); // This error happens when memory allocation for expanding the token's lexeme fails. We should report this error appropriately.
            exit(EXIT_FAILURE);
        }

        t->lexeme = new_lexeme;
        t->capacity = new_capacity;
    }

    t->lexeme[t->length++] = c;
    t->lexeme[t->length] = '\0';
}

// Function to update the category of a token. This allows us to set the token's category after we have built its lexeme and determined its type.
void t_token_update_category(Token *t, TokenCategory cat) {
    if (!t) return;
    t->category = cat;
}

// Function to destroy a token and free its resources. This should be called when a token is no longer needed to avoid memory leaks.
void t_token_destroy(Token *t) {
    if (!t) return;

    free(t->lexeme);
    t->lexeme = NULL;
    t->length = 0;
    t->capacity = 0;
}

// Function to initialize a token list. This sets up the list to be empty and ready to store tokens.
TokenList *tl_token_list_init(void) {
    TokenList *list = (TokenList *)malloc(sizeof(TokenList));
    if (!list) {
		e_error_report(400);
        //e_error_report(); // This error happens when memory allocation for a new token list fails. We should report this error appropriately.
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

// Function to add a token to the end of a token list. This creates a new node for the token and updates the list's head, tail, and size accordingly.
void tl_token_list_add(TokenList *list, Token t) {
    if (!list) return;

    TokenNode *node = (TokenNode *)malloc(sizeof(TokenNode));
    if (!node) {
		e_error_report(408);
        //e_error_report();  // This error happens when memory allocation for a new token node fails. We should report this error appropriately.
        exit(EXIT_FAILURE);
    }

    node->token = t;
    node->next = NULL;

    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

// Function to update a token's category and add it to a token list. This is a convenience function that combines updating the token's category and adding it to the list in one step.
void tl_token_update_and_append(TokenList *list, Token *t, TokenCategory cat) {
    if (!list || !t) return;

    t_token_update_category(t, cat);
    tl_token_list_add(list, *t);
}

// Function to get the size of a token list. This returns the number of tokens currently stored in the list.
int tl_token_list_size(const TokenList *list) {
    if (!list) return 0;
    return list->size;
}

// Function to destroy a token list and free all associated resources. This should be called when the list is no longer needed to avoid memory leaks. It iterates through all nodes in the list, destroys each token, and frees the nodes.
void tl_token_list_destroy(TokenList *list) {
    if (!list) return;

    TokenNode *current = list->head;

    while (current) {
        TokenNode *next = current->next;

        /* destroy internal token memory */
        t_token_destroy(&current->token);

        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Functions used by output module:

// Function to print a token in a format suitable for release output.
void t_token_print_release(FILE *out, const Token *t) {
    if (!out || !t) return;

    fprintf(out, "<%s, %s>",
            t->lexeme ? t->lexeme : "",
            token_category_to_string(t->category));
}

// Function to print a token in a detailed format suitable for debugging. 
void t_token_print_debug(FILE *out, const Token *t) {
    if (!out || !t) return;

    fprintf(out,
        "<lexeme=\"%s\", category=%s, line=%d, column=%d, length=%zu, capacity=%zu>",
        t->lexeme ? t->lexeme : "",
        token_category_to_string(t->category),
        t->line,
        t->column,
        t->length,
        t->capacity
    );
}

// Function to print all tokens in a token list in a format suitable for release output. 
void tl_token_list_print_release(FILE *out, const TokenList *list) {
    if (!out || !list || !list->head) return;

    TokenNode *current = list->head;
    int current_line = current->token.line;

    while (current) {
        //New line when line number changes 
        if (current->token.line != current_line) {
            fprintf(out, "\n");
            current_line = current->token.line;
        }

        t_token_print_release(out, &current->token);

        if (current->next && current->next->token.line == current_line)
            fprintf(out, " ");

        current = current->next;
    }

    fprintf(out, "\n");
}

// Function to print all tokens in a token list in a detailed format suitable for debugging. 
void tl_token_list_print_debug(FILE *out, const TokenList *list) {
    if (!out) return;

    if(!list) {
        fprintf(out, "[TOKEN LIST is NULL]\n");
        return;
    }

    fprintf(out, "[TOKEN LIST size=%d]\n", list->size);

    if(list->size == 0) {
        fprintf(out, "  (empty)\n\n");
        return;
    }

    TokenNode *current = list->head;
    int index = 0;

    while (current) {
        fprintf(out, "  %d: ", index);
        t_token_print_debug(out, &current->token);
        fprintf(out, "\n");

        current = current->next;
        index++;
    }

    fprintf(out, "\n");
}

// Old placeholder 
void t_token_handler(void) {
    fprintf(stdout, "Token_handler module is under development.\n");
}