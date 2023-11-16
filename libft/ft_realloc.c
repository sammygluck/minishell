#include <libft.h>

void *ft_realloc(void *ptr, size_t nmemb, size_t size)
{
    void *new_pointer;

    new_pointer = ft_malloc(nmemb * size);
    ft_bzero(new_pointer, nmemb * size);
    if (!ptr)
        return (new_pointer);
    if (!size)
        return (ptr);
    ft_memmove(new_pointer, ptr, nmemb * size);
    free(ptr);
    return (new_pointer);
}