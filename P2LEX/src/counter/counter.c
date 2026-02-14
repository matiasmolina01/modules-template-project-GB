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
//Puntero global a un fichero
FILE *count_fp = NULL;
/* Inicialización del sistema de conteo */
void count_init(const char *filename, count_local_t *local) {
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
    if (COUNTOUT == 1 && main_fp != NULL) {
        /* Usar archivo de salida principal */
        count_fp = main_fp;
    } else if (DBGCOUNT == 0) {
        /* Crear archivo independiente de conteo */
       count_fp = fopen(COUNTFILE, "w");
        if (count_fp == NULL) {
            perror("Error al crear archivo de conteo");
        }
    } else {
        /* Por defecto: no se envía a ningún archivo */
        count_fp = NULL;
    }
}
/*Se printea en archivo */
void count_log(int line, const char *func,
               const char *type, int inc,
               count_local_t *local)
{
    fprintf(count_fp,
        "LINE %d | FUNC %s | %s += %d | "
        "PARTIAL [C:%ld I:%ld G:%ld] | "
        "TOTAL [C:%ld I:%ld G:%ld]\n",
        line, func, type, inc,
        local->comp, local->io, local->gen,
        COUNT_COMP, COUNT_IO, COUNT_GEN);
}
#endif
