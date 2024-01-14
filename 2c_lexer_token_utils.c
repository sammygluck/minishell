/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2c_lexer_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:12:33 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 12:16:01 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *string, int type)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	token->string = ft_strdup(string);
	token->type = type;
	token->next = NULL;
	token->previous = NULL;
	return (token);
}

void	add_token_to_list(t_token **token_list, t_token *token)
{
	t_token	*head;

	if (!token_list || !token)
	{
		ft_putendl_fd("minishell: error: failed to create lexer_token", 2);
		exit(EXIT_FAILURE);
	}
	if (!*token_list)
	{
		*token_list = token;
		return ;
	}
	head = *token_list;
	while (head->next)
		head = head->next;
	head->next = token;
	head->next->previous = head;
}
