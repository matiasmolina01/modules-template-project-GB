#ifndef MAIN_H
#define MAIN_H
 
#include <stdio.h>
#include <stdbool.h>
#include "./utils_files.h"
#include "./module_args/module_args.h"
#include "./module_classifier/module_classifier.h"
#include "./module_text_normalizer/module_text_normalizer.h"
#include "./module_symbol_resolver/module_symbol_resolver.h"
#include "./module_symbol_table/module_symbol_table.h"
#include "./module_input_handler/module_input_handler.h"
#include "./module_output_handler/module_output_handler.h"
#include "./module_recursivity_handler/module_recursivity_handler.h"

// Output file of project run: either a stdout or a filename with log extension (comment one out)
#define PROJOUTFILENAME "./proj_modules_template.log"
//#define PROJOUTFILENAME "stdout"

extern FILE* ofile; // The output handler for the project run (same variable name as in modules)

#endif // MAIN_H
