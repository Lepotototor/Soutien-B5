#include "resize_tab.h"

#include <malloc.h>

struct tab *resize_tab(struct tab *tab, size_t new_size)
{
    if (new_size >= tab->size)
        return tab;
    else if (new_size == 0)
    {
        if (tab->data)
            free(tab->data);
        free(tab);
        return NULL;
    }

    int *new_tab = realloc(tab->data, new_size);
    if (new_tab == NULL)
        return tab;

    tab->data = new_tab;
    tab->size = new_size;

    return tab;
}

struct tab *sub_tab(struct tab *tab, size_t new_size)
{
    if (new_size >= tab->size)
        new_size = tab->size;
    else if (new_size == 0)
        return NULL;

    struct tab *res = malloc(sizeof(struct tab));
    if (res == NULL)
        return NULL;

    int *new_tab = malloc(new_size);
    if (new_tab == NULL)
    {
        free(res);
        return NULL;
    }

    res->data = new_tab;
    res->size = new_size;

    return tab;
}
