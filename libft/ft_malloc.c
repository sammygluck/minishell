/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:31:26 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 13:31:28 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_malloc(size_t size)
{
	void	*new_pointer;

	new_pointer = malloc(size);
	if (!new_pointer)
	{
		ft_putstr_fd("malloc failure\n", 2);
		exit(EXIT_FAILURE);
	}
	return (new_pointer);
}
