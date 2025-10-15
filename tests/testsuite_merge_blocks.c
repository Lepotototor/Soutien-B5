#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdio.h>

#include "../src/merge_blocks.h"

TestSuite(merge_blocks);

Test(merge_blocks, basic_test)
{
    char str1[] = "Who is the end ? ";
    char str2[] = "\tI'm here";
    char result[] = "Who is the end ? \tI'm here";
    char *got = merge_blocks(str1, strlen(str1), str2, strlen(str2) + 1);

    cr_expect(eq(str, result, got));
    free(got);
}

Test(merge_blocks, int_test)
{
    int tab1[] = { 41, 42, 43, 44, 45 };
    int tab2[] = { 8, 9, 45 };
    int result1[] = { 41, 42, 43, 44, 45, 8, 9, 45 };
    int result2[] = { 8, 9, 45, 41, 42, 43, 44, 45 };
    int *got = merge_blocks(tab1, 5 * sizeof(int), tab2, 3 * sizeof(int));

    cr_expect_arr_eq(result1, got, 8);
    free(got);

    got = merge_blocks(tab2, 3 * sizeof(int), tab1, 5 * sizeof(int));
    cr_expect_arr_eq(result2, got, 8 * sizeof(int));
    free(got);
}

Test(merge_blocks, empty_test)
{
    char str1[] = "";
    char str2[] = "";
    char result[] = "";
    char *got = merge_blocks(str1, strlen(str1), str2, strlen(str2) + 1);

    cr_expect(eq(str, result, got));
    free(got);
}

Test(merge_blocks, null_test)
{
    char str[] = "I'm alone";
    char *null = NULL;
    char *got = merge_blocks(null, 0, null, 0);

    cr_expect(eq(ptr, null, got));

    got = merge_blocks(str, strlen(str) + 1, null, 0);
    cr_expect(eq(ptr, str, got));

    got = merge_blocks(null, 0, str, strlen(str) + 1);
    cr_expect(eq(ptr, str, got));
}
