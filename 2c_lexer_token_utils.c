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

t_token	*create_token(char *string, int type);
void	add_token_to_list(t_token **token_list, t_token *token);

/*
returns a pointer to a new token node;
arguments: a string and a type of token;
malloc errors are handled in ft_malloc;
*/
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

/*
adds a given pointer to a token to the end of the list of tokens;
as of now, returns nothing;
*/
void	add_token_to_list(t_token **token_list, t_token *token)
{
	t_token	*head;

	if (!token_list || !token)
		return ; //shouldn't I exit?
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
