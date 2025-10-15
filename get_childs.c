#include "get_childs.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 64
#define NUMSIZE 10

int *get_childs(size_t n)
{
    int *tab = calloc(n, sizeof(int));
    if (tab == NULL)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            free(tab);
            return NULL;
        }
        else if (pid == 0)
        {
            printf("I'm child number %zu, my pid is %i\n", i, getpid());
            exit(0);
        }
        else
            tab[i] = pid;
    }

    for (size_t i = 0; i < n; i++)
        wait(NULL);

    return tab;
}
