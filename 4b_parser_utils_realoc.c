#include <minishell.h>

void **ft_realloc_pointer_array(void **ptr, size_t nmemb, size_t size);

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
	void **pointer_bag;

	pointer_bag = ft_malloc(size * (nmemb + 1));
	ft_bzero(pointer_bag, size * (nmemb + 1));
	memmove_array(ptr, pointer_bag, nmemb);
	free(ptr);
	return(pointer_bag);
}

void memmove_array(void **ptr, void **new_ptr, size_t size)
{
	//the idea here is to replace the old array with the new array.
	//in the end we just want to free the old pointer_bag and not the pointers it holds

	int	i;

	if (!ptr && !new_ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}

}