/*
 * -----------------------------------------------------------------------------
 * language.h
 *
 * Usage:
 *     Data structures and function definitios of the laguange module.
 *      In charge of loading the language information into the program
 *
 * Status:
 *     Initial development — logic to handle language is not yet implemented.
 *
 * 
 * Author: [Franco Olano Melo]
 * -----------------------------------------------------------------------------
 */

#ifndef MODULE_LANGUAGE_H
#define MODULE_LANGUAGE_H

#include "../main.h"

/* Defines the different types of actions the SRA can perform. */
typedef enum {
    ACT_SHIFT,
    ACT_REDUCE,
    ACT_ACCEPT,
    ACT_ERROR
} ActionType;

/* Represents a grammar rule with an ID, left-hand side symbol, and right-hand side symbols. */
typedef struct Rule {
    int id;
    int lhs;
    int *rhs;
    int rhs_length;
} Rule;

/* Represents an action in the SRA parsing table. */
typedef struct Action {
    ActionType type;
    int state;
    Rule *rule;
} Action;

/* Represents a terminal or non-terminal symbol in the grammar. */
typedef struct Symbol {
    int id;
    char *name;
    int is_terminal;
} Symbol;

/* Holds all the language definitions including symbols, rules, and the action table. */
typedef struct Language {
    Symbol **symbols;
    Rule **rules;
    Action **action_table;
    int num_symbols;
    int num_states;
    int num_nonterminals;
    int start_symbol;
    int num_rules;
} Language;


#define MAX_LINE_LEN 1024
#define READ_MODE "r"

#define MAX_NAME_LEN 100
#define MAX_RHS_LEN 50
#define DEFAULT_CAPACITY 20

/* Section Headers */
#define SEC_SYMBOLS "[SYMBOLS]\n"
#define SEC_START   "[START]\n"
#define SEC_RULES   "[RULES]\n"
#define SEC_ACTIONS "[ACTIONS]\n"

/* String Literals */
#define STR_TERMINAL "TERMINAL"

/* Action Characters */
#define CHAR_SHIFT  'S'
#define CHAR_REDUCE 'R'
#define CHAR_ACCEPT 'A'
#define CHAR_ERROR  'E'

/* Formatting Directives */
#define FMT_SYMBOL   "%d. %s %s"
#define FMT_RULE_HDR "%d. %d :%n"
#define FMT_RHS_ITEM " %d%n"
#define FMT_ACTION   " %c-%d-%d%n"

/* Creates and returns a Language struct by parsing the provided formatted text file path. */
Language* get_language(const char* language_file_path);

#endif