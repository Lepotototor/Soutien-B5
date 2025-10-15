#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdio.h>

#include "../src/array_even.h"

TestSuite(array_even);

Test(array_even, basic_test1, .timeout = 5)
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int expected[] = { 2, 4, 6, 8, 10 };
    int *res = NULL;
    size_t size = array_even(arr, 10, &res);

    cr_expect_eq(5, size, "Expected size %i, got %zu", 5, size);
    cr_expect_arr_eq(expected, res, 5, "Returned array is not good");

    free(res);
}

Test(array_even, basic_test2, .timeout = 5)
{
    int arr[] = { 6, 42, 69, 13, 12, 4, 0 };
    int expected[] = { 6, 42, 12, 4, 0 };
    int *res = NULL;
    size_t size = array_even(arr, 7, &res);

    cr_expect_eq(5, size, "Expected size %i, got %zu", 5, size);
    cr_expect_arr_eq(expected, res, 5, "Returned array is not good");

    free(res);
}

Test(array_even, basic_test3, .timeout = 5)
{
    int arr[] = { 7, 9, 13, 4, 6, 1, 10, 43, 69 };
    int expected[] = { 4, 6, 10 };
    int *res = NULL;
    size_t size = array_even(arr, 9, &res);

    cr_expect_eq(3, size, "Expected size %i, got %zu", 3, size);
    cr_expect_arr_eq(expected, res, 3, "Returned array is not good");

    free(res);
}

Test(array_even, only_even, .timeout = 5)
{
    int arr[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 42, 420 };
    size_t s = sizeof(arr) / sizeof(int);
    int *res = NULL;
    size_t size = array_even(arr, s, &res);

    cr_expect_eq(s, size, "Expected size %zu, got %zu", s, size);
    cr_expect_arr_eq(arr, res, s, "Returned array is not good");

    free(res);
}

Test(array_even, no_even, .timeout = 5)
{
    int arr[] = { 1, 3, 5, 7, 9, 11, 13, 21, 43, 57, 99 };
    size_t s = sizeof(arr) / sizeof(int);
    int *res = NULL;
    size_t size = array_even(arr, s, &res);

    cr_expect_eq(0, size, "Expected size %i, got %zu", 0, size);
    cr_expect_eq(NULL, res, "Returned array is not good, it should be NULL");

    free(res);
}

Test(array_even, empty_test, .timeout = 5)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int *res = NULL;
    size_t size = array_even(arr, 0, &res);

    cr_expect_eq(0, size, "Expected size 0, got %zu", size);
    cr_expect_eq(NULL, res, "Expected NULL got an array");
}

Test(array_even, null_test, .timeout = 5)
{
    int *null = NULL;
    int *res = NULL;
    size_t size = array_even(null, 0, &res);

    cr_expect_eq(0, size, "Expected size 0, got %zu", size);
    cr_expect_eq(NULL, res, "Expected NULL got an array");
}
