/*
 * -----------------------------------------------------------------------------
 * counter.c 
 *
 * Usage:
 *     Called from all the other modules or test modules to compute (or not) the number of operations.
 *
 * Status:
 *     Initial development — logic to handle counter is not yet implemented.
 *
 * Author: Marc Lounds
 * -----------------------------------------------------------------------------
 */

#include "./counter.h"

#ifdef COUNTCONFIG

#include <stdio.h>
#include <stdlib.h>

//global counters
long COUNT_COMP = 0;
long COUNT_IO   = 0;
long COUNT_GEN  = 0;


//Puntero global a un fichero
static FILE *count_fp = NULL;

// Create the extension for the debug file
static void c_build_dbg_filename(const char *input, char *out, size_t size) {
    snprintf(out, size, "%sdbgcnt", input);
}


/* Inicialización del sistema de conteo */
void c_count_init(const char *filename, FILE *main_output) {
    
    /* Inicializar contadores globales */
    COUNT_COMP = 0;
    COUNT_IO   = 0;
    COUNT_GEN  = 0;

    /* Inicializar contadores locales si se pasa puntero */
    // if (local != NULL) {
    //     local->comp = 0;
    //     local->io   = 0;
    //     local->gen  = 0;
    // }
    //NO HACE FALTA INICIALIZARLO AQUÍ POR QUE SE INICIALIZA CADA VEZ QUE LLAMAS UNA FUNCIÓN

    /* Determinar a dónde enviar los mensajes de conteo */
    if (COUNTOUT == 1 && main_output != NULL) {
        /* Usar archivo de salida principal */
        count_fp = main_output;
        return;

    } 
    if (DBGCOUNT == 0) {
        /* Crear archivo independiente de conteo */
        char dbgname[256];
        // build the name of the debug file based on the input filename
        c_build_dbg_filename(filename, dbgname, sizeof(dbgname));
        count_fp = fopen(dbgname, "w");
        
        if (!count_fp) {
            e_error_report(ERR_C_COUNT_FILE_CREATE_FAILURE);
            count_fp = NULL; // fallback a stdout
        }
    } else {
        /* Por defecto: no se envía a ningún archivo */
        count_fp = NULL;
    }
}

/*Se printea en archivo */
void c_count_log(int line, const char *func,
               const char *type, int inc,
               count_local_t *local)
{
    if (!count_fp) return;

    int written = fprintf(
        count_fp,
        "LINE %d | FUNC %s | %s += %d | "
        "PARTIAL [C:%ld I:%ld G:%ld] | "
        "TOTAL [C:%ld I:%ld G:%ld]\n",
        line, func, type, inc,
        local ? local->comp : 0,
        local ? local->io   : 0,
        local ? local->gen  : 0,
        COUNT_COMP, COUNT_IO, COUNT_GEN
    );

    // TODO: comment this lines of code if we don't want to count the IO of writing to the file
    (void)written; // avoid counting the logger's own IO here (instrument actual I/O sites instead)
}

void c_count_print_summary(void) {
    if (!count_fp) return;

    fprintf(count_fp,
        "\n=== COUNT SUMMARY ===\n"
        "TOTAL COMP: %ld\n"
        "TOTAL IO  : %ld\n"
        "TOTAL GEN : %ld\n",
        COUNT_COMP, COUNT_IO, COUNT_GEN);
}

#endif

/*

HOW TO USE:

call c_count_init at the beginning of the program, passing the input filename and the main output FILE* if you want to log there.
then the program runs as normal. In the middle all the modules can use the COUNTCOMP, COUNTIO, and COUNTGEN macros to increment the respective counters, passing the local count struct if they want to track local counts as well.
finally call c_count_print_summary at the end of the program to print the summary of counts.
*/