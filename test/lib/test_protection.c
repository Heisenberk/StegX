/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "insert.h"
#include "protection.h"
#include "common.h"

/* test de l'algorithme qui melange pour l'insertion et met dans l'ordre 
 * pour l'extraction */
void test_protection(void **state)
{
    (void)state;
    uint8_t tab[10];
    char passwd[6] = "stegx";
    int i;
    for (i = 0; i < 10; i++) {
        tab[i] = i;
    }

    int test = protect_data(tab, 10, passwd, STEGX_MODE_INSERT);
    assert_int_equal(test, 0);

    test = protect_data(tab, 10, passwd, STEGX_MODE_EXTRACT);
    assert_int_equal(test, 0);

    for (i = 0; i < 10; i++) {
        assert_int_equal(tab[i], i);
    }
}

int main(void)
{

    /* Structure CMocka contenant la liste des tests. */
    const struct CMUnitTest check_protection_tests[] = {
        cmocka_unit_test(test_protection)
    };

    /* Exécute les tests. */
    return cmocka_run_group_tests(check_protection_tests, NULL, NULL);
}
