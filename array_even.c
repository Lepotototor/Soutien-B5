#include "array_even.h"

#include <malloc.h>

size_t array_even(const int *a, size_t len, int **result)
{
    int *tab = NULL;
    size_t size = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (a[i] % 2 == 0)
        {
            size++;
            int *new_tab = realloc(tab, size * sizeof(int));
            if (new_tab == NULL)
            {
                free(*result);
                *result = NULL;
                return 0;
            }
            tab = new_tab;
            tab[size - 1] = a[i];
        }
    }

    *result = tab;

    return size;
}
