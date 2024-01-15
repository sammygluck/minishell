/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3b_first_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:49:32 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 12:49:35 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*initial_clean(char *string)
{
	t_quote	q_struct;
	char	*new_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	init_quote(&q_struct);
	new_string = ft_malloc(ft_strlen(string) + 1);
	while (string[i])
	{
		is_in_quote(string[i], &q_struct);
		if (string[i] == '$' && is_quote(string[i + 1])
			&& !is_in_any_quote(string, i))
			i++;
		new_string[j++] = string[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}
