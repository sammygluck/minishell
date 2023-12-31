/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_expander_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:12:29 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 08:12:33 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token **token_head, t_env_var *env_head);

/*
    outline:
    for each lexer string, unless heredoc -> replace old one with expanded one
    make sure to free all necesarry parts

*/

void	expander(t_token **token_head, t_env_var *env_head)
{
	t_token	*head;

	if (!token_head || !*token_head)
		return ;
	head = *token_head;
	while (head)
	{
		if (head->type == 6)
			head->string = process_token_string(head->string, env_head);
		//if it's a heredoc part.....
		head = head->next;
	}
}

char	*process_token_string(char *str, t_env_var *env_head)
{
	char	*new_string;

	new_string = initial_clean(str);
	free(str);
	str = new_string;
	new_string = expanded(str, env_head);
	if (new_string)
		str = new_string;
	new_string = third_clean(str);
	free(str);
	return (new_string);
}
