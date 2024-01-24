/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_expander_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:12:29 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 15:00:26 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token **token_head, t_env_var *env_head)
{
	t_token	*head;

	if (!token_head || !*token_head)
		return ;
	head = *token_head;
	while (head)
	{
		if ((head->type == 6 && head->previous == NULL)
			|| (head->type == 6 && head->previous
				&& head->previous->type != D_SMALLER))
			head->string = process_token_string(head->string, env_head);
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
	return (str);
}

/*
A. SQUEEZE NODE IN BETWEEN
1. deal with old one
	create a var to hold on to it while we process the rest
	once processed, free all resources
2. deal with new one
	set previous, node to point to new node
	set new node to point to previous node
	set last node of new list to point to next node before squeeze
	set next node before squeeze to point to last node

B. NEW NODE CREATION
1. iterate over string
	a. create new token based on space if it's not in a quote
	b. the token is a string token type
	c. 
*/
