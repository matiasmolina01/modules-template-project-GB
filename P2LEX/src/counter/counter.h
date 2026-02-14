

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
void count_init(void);


/* Muestra resumen final */
void count_print_summary(void);


/* Función de logging */
void count_log(int line,
               const char *func,
               const char *type,
               int inc,
               count_local_t *local);

/* === Macros de conteo === */

#define COUNTCOMP(n, func) \
    do { \
        COUNT_COMP += (n); \ //Actualiza variable global
        (func).comp += (n); \ //Actualiza variable local
        count_log(__LINE__, __func__, "COMP", (n), &(func)); \
    } while(0)

#define COUNTIO(n, func) \
    do { \
        COUNT_IO += (n); \
        (func).io += (n); \
        count_log(__LINE__, __func__, "IO", (n), &(func)); \
    } while(0)

#define COUNTGEN(n, func) \
    do { \
        COUNT_GEN += (n); \
        (func).gen += (n); \
        count_log(__LINE__, __func__, "GEN", (n), &(func)); \
    } while(0)

#else

/* === RELEASE: coste cero === */
#define COUNTCOMP(n, func)
#define COUNTIO(n, func)
#define COUNTGEN(n, func)


#define count_init()
#define count_local_init(local)
#define count_print_summary()



#endif /* COUNTCONFIG */

#endif /* MODULE_COUNTER_H */
