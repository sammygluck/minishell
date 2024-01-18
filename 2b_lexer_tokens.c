/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_lexer_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:08:43 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/18 09:16:49 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(char *string, int *i, int type, t_token **head)
{
	t_token	*token;
	char	*string_to_add;

	if (type > STRING && type <= SMALLER)
		string_to_add = token_string(type, i);
	if (type > 5)
		string_to_add = word_string(string, i);
	if (!string_to_add)
	{
		ft_putstr_fd("Error: creating string_to_add in lexer failed\n", 2);
		*i = ft_strlen(string) + 1;
		return (1);
	}
	token = create_token(string_to_add, type);
	add_token_to_list(head, token);
	free(string_to_add);
	return (0);
}

char	*token_string(int type, int *i)
{
	if (type == 1 || type == 2)
		*i += 2;
	else
		*i += 1;
	if (type == 1)
		return (ft_strdup(">>"));
	else if (type == 2)
		return (ft_strdup("<<"));
	else if (type == 3)
		return (ft_strdup("|"));
	else if (type == 4)
		return (ft_strdup(">"));
	else if (type == 5)
		return (ft_strdup("<"));
	else
		return (NULL);
}

char	*word_string(char *string, int *i)
{
	t_quote	q_struct;
	char	*result;
	int		j;
	int		chars_to_copy;

	if (!string || !i)
		return (NULL);
	init_quote(&q_struct);
	j = find_word_end(string, *i, &q_struct);
	if (check_quote_error(&q_struct))
		return (NULL);
	chars_to_copy = j - *i;
	result = ft_strndup(&string[*i], chars_to_copy);
	*i = j;
	return (result);
}

int	find_word_end(char *string, int start_index, t_quote *q_struct)
{
	int	j;

	j = start_index;
	while (string[j])
	{
		is_in_quote(string[j], q_struct);
		if (!q_struct->in_quote && (is_token(string, j) || is_space(string[j])))
			break ;
		j++;
	}
	return (j);
}

int	check_quote_error(t_quote *q)
{
	if (q->in_quote)
	{
		printf("Syntax error: missing closing quote for '%c'\n", q->quote_type);
		return (1);
	}
	return (0);
}
