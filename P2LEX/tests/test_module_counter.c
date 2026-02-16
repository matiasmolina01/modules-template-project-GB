/*
 * -----------------------------------------------------------------------------
 * test_module_counter.c
 *
 * Unit tests for module_counter.
 *
 * Team: GB
 *     
 * Update 1:
 * 
 * - module_counter functionality test
 * 
 * Author: Martí Ponsa
 * Date: 16-02-2026
 * 
 * -----------------------------------------------------------------------------
 */


#define COUNTCONFIG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tests/test_module_counter.h"

static void report(const char *name, int ok) {
    printf("%-48s : %s\n", name, ok ? "PASS" : "FAIL");
}
static void test_counter_init_with_output(void) {
    const char *infile = "test_counter_input.tmp";
    const char *outname = "test_counter_output.tmp";
    FILE *out = fopen(outname, "w+");
    if (!out) {
        printf("Could not open temp output file for counter tests\n");
        return;
    }

    /* initialize counts to zero via c_count_init */
    c_count_init(infile, out);

        count_local_t local;
        c_count_local_init(&local);

        printf("DEBUG before increments: COUNT_COMP=%ld COUNT_IO=%ld COUNT_GEN=%ld\n", COUNT_COMP, COUNT_IO, COUNT_GEN);
        printf("DEBUG local before: C=%ld I=%ld G=%ld\n", local.comp, local.io, local.gen);

        COUNTCOMP(5, local);
        printf("DEBUG after COUNTCOMP: COUNT_COMP=%ld COUNT_IO=%ld COUNT_GEN=%ld local C=%ld I=%ld G=%ld\n",
            COUNT_COMP, COUNT_IO, COUNT_GEN, local.comp, local.io, local.gen);

        COUNTIO(3, local);
        printf("DEBUG after COUNTIO:    COUNT_COMP=%ld COUNT_IO=%ld COUNT_GEN=%ld local C=%ld I=%ld G=%ld\n",
            COUNT_COMP, COUNT_IO, COUNT_GEN, local.comp, local.io, local.gen);

        COUNTGEN(2, local);
        printf("DEBUG after COUNTGEN:   COUNT_COMP=%ld COUNT_IO=%ld COUNT_GEN=%ld local C=%ld I=%ld G=%ld\n",
            COUNT_COMP, COUNT_IO, COUNT_GEN, local.comp, local.io, local.gen);

        /* print summary */
        c_count_print_summary();

    fflush(out);
    rewind(out);

    /* read contents */
    char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf)-1, out);
    buf[n] = '\0';

    /* print captured output so summary is visible in test run */
    printf("\n-- Captured counter output (test) --\n%s\n-- End captured output --\n", buf);

    report("c_count_log wrote LINE entries", strstr(buf, "LINE") != NULL);
    report("c_count_print_summary wrote SUMMARY", strstr(buf, "COUNT SUMMARY") != NULL || strstr(buf, "COUNT SUMMARY") != NULL);

    /* globals should reflect increments */
    report("COUNT_COMP updated", COUNT_COMP >= 5);
    report("COUNT_IO updated", COUNT_IO >= 3);
    report("COUNT_GEN updated", COUNT_GEN >= 2);

    fclose(out);
    remove(outname);
}


static void test_counter_init_creates_dbgfile(void) {
    const char *infile = "test_counter_dbgfile";
    char dbgname[256];
    snprintf(dbgname, sizeof(dbgname), "%sdbgcnt", infile);
    /* remove if exists from previous runs */
    remove(dbgname);

    c_count_init(infile, NULL);

    /* file should exist now (or count_fp NULL if fopen failed) */
    FILE *f = fopen(dbgname, "r");
    report("c_count_init created dbg file", f != NULL);
    if (f) {
        /* read and print dbg file contents to make summary visible */
        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        rewind(f);
        if (len > 0) {
            char *dbgbuf = (char*)malloc((size_t)len + 1);
            if (dbgbuf) {
                fread(dbgbuf, 1, (size_t)len, f);
                dbgbuf[len] = '\0';
                printf("\n-- Captured dbg file (%s) --\n%s\n-- End dbg file --\n", dbgname, dbgbuf);
                free(dbgbuf);
            }
        }
        fclose(f);
        remove(dbgname);
    }
}


void test_counter_run_all(void) {
    printf("\nRunning counter module tests...\n");
    test_counter_init_with_output();
    test_counter_init_creates_dbgfile();
    printf("Finished counter module tests.\n\n");
}


int main(void) {
    printf("\nStarting tests for Module counter...\n");

    test_counter_run_all();

    printf("Finished tests for Module counter...\n\n");
    return 0;
}
