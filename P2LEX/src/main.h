#ifndef MAIN_H
#define MAIN_H
 
#include <stdio.h>
#include <stdbool.h>
#include "./utils_files.h"
#include "./language/language.h"
#include "./automata/automata.h"
#include "./scanner/scanner.h"
#include "./counter/counter.h"
#include "./error_handler/error_handler.h"
#include "./input_handler/input_handler.h"
#include "./module_args/module_args.h"
#include "./output_handler/output_handler.h"
#include "./token_handler/token_handler.h"
#include "./global_context/global_context.h"

// Output file of project run: either a stdout or a filename with log extension (comment one out)
#define PROJOUTFILENAME "./proj_modules_template.log"
//#define PROJOUTFILENAME "stdout"

extern FILE* ofile; // The output handler for the project run (same variable name as in modules)

#endif // MAIN_H
