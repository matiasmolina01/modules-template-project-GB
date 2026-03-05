#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include "../main.h"

typedef struct Language Language;

/* * Holds the overarching data structures required throughout the parsing process.
 * Currently contains the loaded Language definitions.
 */
typedef struct GlobalContext {
    Language* language;
    SRA* sra;
    TokenList* tokenlist;
} GlobalContext;

/* Allocates memory for a new GlobalContext and initializes its pointers to NULL. 
 * Returns a pointer to the newly created GlobalContext. */
GlobalContext* create_global_context(void);

/* Initializes the GlobalContext by creating it and loading the language from the provided file path.
 * Returns a pointer to the fully populated GlobalContext. */
GlobalContext* init_global_context(const char* language_file_path);

/* Frees the memory associated with the GlobalContext and its internal structures.
 * Returns nothing. */
void destroy_global_context(GlobalContext* context);

#endif /* GLOBAL_CONTEXT_H */