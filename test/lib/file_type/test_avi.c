/*
 * This file is part of the StegX project.
 * Copyright (C) 2018  StegX Team
 * 
 * StegX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"

/*
 * Teste la vérification du format AVI.
 * */
void test_file_avi_v1(void **state)
{
    (void)state;
    FILE *f = fopen("../../../env/test/flv/test13.flv", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_avi(f), UNKNOWN);
    fclose(f);
}

void test_file_avi_v2(void **state)
{
    (void)state;
    FILE *f = fopen("../../../env/test/avi/test14.avi", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_avi(f), AVI_UNCOMPRESSED);
    fclose(f);

}

int main(void)
{
    /* Structure CMocka contenant la liste des tests. */
    const struct CMUnitTest avi_tests[] = {
        cmocka_unit_test(test_file_avi_v1),
        cmocka_unit_test(test_file_avi_v2)
    };

    /* Exécute les tests. */
    return cmocka_run_group_tests(avi_tests, NULL, NULL);
}
