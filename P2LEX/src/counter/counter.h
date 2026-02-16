#ifndef MODULE_COUNTER_H
#define MODULE_COUNTER_H


#include "../main.h"


/* === Activación del módulo === */
#ifdef COUNTCONFIG

#define COUNTFILE "debug_count.dbgcnt"

#define COUNTOUT 1   /* o 0 */
#define DBGCOUNT 0   /* o 1 */


/* Contadores globales */
extern long COUNT_COMP;
extern long COUNT_IO;
extern long COUNT_GEN;

/* Contador parcial por función */
typedef struct {
    long comp;
    long io;
    long gen;
} count_local_t;


/* Inicializa contadores globales */
void c_count_init(const char *filename, FILE *main_output);


/* Muestra resumen final */
void c_count_print_summary(void);


/* Función de logging */
void c_count_log(int line,
               const char *func,
               const char *type,
               int inc,
               count_local_t *local);


static inline void c_count_local_init(count_local_t *l) {
    l->comp = 0;
    l->io   = 0;
    l->gen  = 0;
}

#define COUNTCOMP(n, local)            \
    do {                               \
        COUNT_COMP += (n);             \
        (local).comp += (n);           \
        c_count_log(__LINE__, __func__, "COMP", (n), &(local)); \
    } while (0)

#define COUNTIO(n, local)              \
    do {                               \
        COUNT_IO += (n);               \
        (local).io += (n);             \
        c_count_log(__LINE__, __func__, "IO", (n), &(local));   \
    } while (0)

#define COUNTGEN(n, local)             \
    do {                               \
        COUNT_GEN += (n);              \
        (local).gen += (n);            \
        c_count_log(__LINE__, __func__, "GEN", (n), &(local));  \
    } while (0)

#else

/* === RELEASE: coste cero === */
#define COUNTCOMP(n, local)
#define COUNTIO(n, local)
#define COUNTGEN(n, local)

#define count_init(filename, main_output)
#define count_print_summary()
#define count_local_init(local)

#endif /* COUNTCONFIG */

#endif /* MODULE_COUNTER_H */
