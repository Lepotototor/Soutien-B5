#include "merge_blocks.h"

#include <malloc.h>
#include <string.h>

void *merge_blocks(void *b1, size_t s1, void *b2, size_t s2)
{
    void *block = malloc(s1 + s2);
    if (block == NULL)
        return NULL;

    memcpy(block, b1, s1);
    memcpy(block + s1, b2, s2);

    return block;
}
