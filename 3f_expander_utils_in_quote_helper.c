/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3f_expander_utils_in_quote_helper.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:02:49 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 16:02:52 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote(t_quote *q_struct)
{
	q_struct->in_quote = 0;
	q_struct->quote_type = '\0';
}

int	is_in_quote(char current_chr, t_quote *q_struct)
{
	if (is_quote(current_chr) && q_struct->in_quote == 0)
	{
		q_struct->in_quote = 1;
		q_struct->quote_type = current_chr;
	}
	else if (is_quote(current_chr) && q_struct->in_quote == 1
		&& q_struct->quote_type == current_chr)
		q_struct->in_quote = 0;
	return (q_struct->in_quote);
}

int	is_in_any_quote(const char *str, int index)
{
	t_quote	q_struct;
	int		i;

	init_quote(&q_struct);
	i = 0;
	while (i <= index)
	{
		if (str[i] == '\0')
			break ;
		is_in_quote(str[i], &q_struct);
		i++;
	}
	return (q_struct.in_quote);
}

int	is_in_single_quote(const char *str, int index)
{
	t_quote	q_struct;
	int		i;

	init_quote(&q_struct);
	i = 0;
	while (i <= index)
	{
		if (str[i] == '\0')
			break ;
		if (str[i] == '\'' && q_struct.in_quote == 0)
		{
			q_struct.in_quote = 1;
			q_struct.quote_type = '\'';
		}
		else if (str[i] == '\'' && q_struct.in_quote
			== 1 && q_struct.quote_type == '\'')
			q_struct.in_quote = 0;
		i++;
	}
	return (q_struct.in_quote && q_struct.quote_type == '\'');
}

int	is_in_double_quote(const char *str, int index)
{
	t_quote	q_struct;
	int		i;

	init_quote(&q_struct);
	i = 0;
	while (i <= index)
	{
		if (str[i] == '\0')
			break ;
		if (str[i] == '"' && q_struct.in_quote == 0)
		{
			q_struct.in_quote = 1;
			q_struct.quote_type = '"';
		}
		else if (str[i] == '"' && q_struct.in_quote == 1
			&& q_struct.quote_type == '"')
			q_struct.in_quote = 0;
		i++;
	}
	return (q_struct.in_quote && q_struct.quote_type == '"');
}
