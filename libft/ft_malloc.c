#include <libft.h>

void *ft_malloc(size_t size)
{
    void *new_pointer;

    new_pointer = malloc(size);
    if (!new_pointer)
    {
        printf("malloc failure\n");
        exit(EXIT_FAILURE);
    }
    return (new_pointer);
}