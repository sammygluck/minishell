/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:33:00 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 13:33:21 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t nmemb, size_t size)
{
	void	*new_pointer;

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
