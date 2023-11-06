#include <minishell.h>

void *ft_malloc(t_size size);
void *ft_realloc(void *ptr, size_t nmemb, size_t size);
void **ft_realloc_pointer_array(void **ptr, size_t nmemb, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}


void *ft_malloc(t_size size)
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

/*
what would we like to do here?
add another pointer to a pointer array char **array_of_pointers;
that means that we need to reallocate the array
what that means is we need the size to be bigger than the original one
we can subsequently copy the old pointers to their designated spots
afterwards we can copy the new one in the final spot
*/
void **ft_realloc_pointer_array(void **ptr, size_t nmemb, size_t size)
{
	//we already have a pointer to pointers
	//we must now create a new pointer to pointers i.e. a pointer bag
	char *pointer_bag;

	pointer_bag = ft_malloc(sizeof(char *) * nmemb);
	//let's clean now the pointer_bag from all garbage
	ft_bzero()
	//now we need to copy our existing pointer bag pointers into our new pointer_bag
	memmove_array(old_pointer_bag, new_pointer_bag, how_many_pointers);
}