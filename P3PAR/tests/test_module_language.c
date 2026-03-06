/* * tests/test_module_language.c
 * * This module is responsible for testing the Language parsing and data structures. 
 * It reads a formatted language.txt file and converts it into the internal 
 * SRA, Rules, and Symbols structures needed for parsing.
 * * This module prints the internal memory structures to a log file or stdout, 
 * allowing the developer to visually confirm that the file parsing mapped 
 * the text correctly into the SRA states, actions, and grammar rules.
 * * The output is directed to a specified file or stdout.
 *
 * The constants and configurations of the tests are defined in the header file test_module_language.h.
 * * Team: [GB]
 * * Update 1: Added get_language and print functionalities for memory verification
 * Author: [Franco Olano Melo]
*/
#include "test_module_language.h"
#include <assert.h>

FILE *ofile = NULL; // file handler to send the module's output (to a file or stdout)

/* Helper function to print the loaded language to the specified output file */
void print_language(Language *lang, FILE *out) {
    if (!lang) {
        fprintf(out, "Language struct is NULL. Parsing failed.\n");
        return;
    }

    fprintf(out, "=== LANGUAGE LOADED SUCCESSFULLY ===\n");
    
    // Find and print the actual name of the start symbol
    char *start_name = "UNKNOWN";
    for (int i = 0; i < lang->num_symbols; i++) {
        if (lang->symbols[i]->id == lang->start_symbol) {
            start_name = lang->symbols[i]->name;
            break;
        }
    }
    fprintf(out, "Start Symbol: %s (ID: %d)\n", start_name, lang->start_symbol);
    
    fprintf(out, "\n--- Symbols (Total: %d, Non-Terminals: %d) ---\n", lang->num_symbols, lang->num_nonterminals);
    for (int i = 0; i < lang->num_symbols; i++) {
        Symbol *s = lang->symbols[i];
        fprintf(out, "  ID: %2d | Name: %-5s | Type: %s\n", 
                s->id, s->name, s->is_terminal ? "TERMINAL" : "NON-TERMINAL");
    }
    
    fprintf(out, "\n--- Grammar Rules (Total: %d) ---\n", lang->num_rules);
    for (int i = 0; i < lang->num_rules; i++) {
        Rule *r = lang->rules[i];
        
        // Find LHS symbol name
        char *lhs_name = "???";
        for (int k = 0; k < lang->num_symbols; k++) {
            if (lang->symbols[k]->id == r->lhs) {
                lhs_name = lang->symbols[k]->name;
                break;
            }
        }

        fprintf(out, "  Rule %2d: %s -> [ ", r->id, lhs_name);
        
        // Find and print RHS symbol names
        for (int j = 0; j < r->rhs_length; j++) {
            char *rhs_name = "???";
            for (int k = 0; k < lang->num_symbols; k++) {
                if (lang->symbols[k]->id == r->rhs[j]) {
                    rhs_name = lang->symbols[k]->name;
                    break;
                }
            }
            fprintf(out, "%s ", rhs_name);
        }
        fprintf(out, "]\n");
    }
    
    fprintf(out, "\n--- SRA Action Table (Total States: %d) ---\n", lang->num_states);
    fprintf(out, "  State | ");
    for (int j = 0; j < lang->num_symbols; j++) {
        fprintf(out, "%-5s ", lang->symbols[j]->name);
    }
    fprintf(out, "\n  ------------------------------------------------------------------------\n");

    for (int i = 0; i < lang->num_states; i++) {
        fprintf(out, "  %5d | ", i);
        for (int j = 0; j < lang->num_symbols; j++) {
            Action act = lang->action_table[i][j];
            if (act.type == ACT_SHIFT) {
                fprintf(out, "S%-4d ", act.state);
            } else if (act.type == ACT_REDUCE) {
                fprintf(out, "R%-4d ", act.rule->id);
            } else if (act.type == ACT_ACCEPT) {
                fprintf(out, "ACC   ");
            } else {
                fprintf(out, "ERR   ");
            }
        }
        fprintf(out, "\n");
    }
    fprintf(out, "====================================\n\n");
}

void test_get_language(const char *test_file_path) {
    fprintf(ofile, "Testing get_language with file: %s\n", test_file_path);
    Language *lang = get_language(test_file_path);
    
    assert(lang != NULL); // Ensure the language was actually allocated and parsed
    
    print_language(lang, ofile);

    // If you implement a free_language(Language *lang) function later, call it here:
    // free_language(lang);
}

int main(int argc, char *argv[]) {
    // Assuming the test framework handles "stdout" vs a real file in set_output_test_file
    ofile = stdout; // Default output to stdout
    // ofile = set_output_test_file(MODLANGTESTLOGFILENAME); // Uncomment if using framework's file handler

    printf("Starting tests for Module Language...\n");
    if (ofile != stdout) fprintf(ofile, "Starting tests for Module Language...\n");
    
    // Provide a default path if no arguments are passed, otherwise use argv[1]
    const char *target_file = (argc >= 2) ? argv[1] : "./tests/test_files/language.txt";
    
    test_get_language(target_file);      
    
    printf("Finished tests for Module Language...\n\n");
    if (ofile != stdout) {
        fprintf(ofile, "Finished tests for Module Language...\n\n");
        fclose(ofile); 
    }
    
    return 0;
}