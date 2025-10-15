#include "str_to_upper.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 64

size_t my_strlen(const char *s)
{
    const char *c = s;
    for (; *c; c++)
        ;
    return c - s;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

char *str_to_upper(const char *s)
{
    if (s == NULL)
        return NULL;

    size_t len = my_strlen(s);
    int fd[2];
    if (pipe(fd) == -1)
        return NULL;

    pid_t pid = fork();

    if (pid == -1)
        return NULL;
    else if (pid == 0)
    {
        close(fd[0]);
        char buffer[BUFSIZE] = { 0 };

        for (size_t i = 0; i < len; i++)
            buffer[i] = to_upper(s[i]);
        buffer[len] = 0;

        if (write(fd[1], buffer, len + 1) == -1)
            return NULL;

        exit(0);
    }
    else
    {
        char *res = malloc(len + 1);

        if (res == NULL)
            return NULL;

        if (read(fd[0], res, len + 1) == -1)
        {
            free(res);
            return NULL;
        }

        close(fd[0]);
        return res;
    }

    return NULL;
}
