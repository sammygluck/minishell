/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_third_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:04:22 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 13:04:25 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote(char c, t_quote *q_struct)
{
	if (is_quote(c))
	{
		if (q_struct->in_quote == 0)
		{
			q_struct->quote_type = c;
			q_struct->in_quote = 1;
			return (1);
		}
		else if (q_struct->in_quote == 1 && c == q_struct->quote_type)
		{
			q_struct->in_quote = 0;
			q_struct->quote_type = '\0';
			return (1);
		}
	}
	return (0);
}

char	*third_clean(char *string)
{
	t_quote	q_struct;
	char	*output;
	int		i;
	int		j;

	init_quote(&q_struct);
	output = ft_malloc(ft_strlen(string) + 1);
	i = 0;
	j = 0;
	while (string[i])
	{
		if (!handle_quote(string[i], &q_struct))
			output[j++] = string[i];
		i++;
	}
	output[j] = '\0';
	return (output);
}
