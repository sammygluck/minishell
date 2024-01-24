/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_mini_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:43 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 14:42:59 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*mini_tokenizer(char *string)
{
	t_token	*token_head;
	int		i;
	int		ret_value;

	i = 0;
	token_head = NULL;
	while (string[i])
	{
		if (is_space(string[i]))
			i++;
		else
			ret_value = mini_add_token(string, &i, 6, &token_head);
	}
	if (ret_value)
	{
		free_token_list(&token_head);
		return (NULL);
	}
	return (token_head);
}

int	mini_add_token(char *string, int *i, int type, t_token **head)
{
	t_token	*token;
	char	*string_to_add;
	char	*cleaned;

	string_to_add = mini_word_string(string, i);
	if (!string_to_add)
	{
		ft_putstr_fd("Error: creating string_to_add in mini_lexer failed\n", 2);
		*i = ft_strlen(string) + 1;
		return (1);
	}
	cleaned = third_clean(string_to_add);
	token = create_token(cleaned, type);
	add_token_to_list(head, token);
	free(string_to_add);
	free(cleaned);
	return (0);
}

char	*mini_word_string(char *string, int *i)
{
	t_quote	q_struct;
	char	*result;
	int		j;
	int		chars_to_copy;

	if (!string || !i)
		return (NULL);
	init_quote(&q_struct);
	j = mini_find_word_end(string, *i, &q_struct);
	if (check_quote_error(&q_struct))
		return (NULL);
	chars_to_copy = j - *i;
	result = ft_strndup(&string[*i], chars_to_copy);
	*i = j;
	return (result);
}

int	mini_find_word_end(char *string, int start_index, t_quote *q_struct)
{
	int	j;

	j = start_index;
	while (string[j])
	{
		is_in_quote(string[j], q_struct);
		if (!q_struct->in_quote && is_space(string[j]))
			break ;
		j++;
	}
	return (j);
}
