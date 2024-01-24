/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_expander_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:12:29 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 15:24:57 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_expanded_token_to_list(t_token **token_list, t_token *new, t_token *node_to_replace);
void	var_expansion_split(t_token **token_head, t_token *node_to_replace, t_env_var *env_head);

void	expander(t_token **token_head, t_env_var *env_head)
{
	t_token	*head;

	if (!token_head || !*token_head)
		return ;
	head = *token_head;
	while (head)
	{
		if (head->type == 6 && head->string && ft_strchr(head->string, '$'))
			var_expansion_split(token_head, head, env_head);
		if (head->type == 6 && head->previous
			&& head->previous->type != D_SMALLER)
			head->string = process_token_string(head->string, env_head); //head->previous
		head = head->next;
	}
}

// check if enclosed in double quotes
// if double quotes >> leave node as is
// no double quotes >> split
// if to replace != replace with && to replace not in double quotes
// split replace_with in 2D array

void	var_expansion_split(t_token **token_head, t_token *node_to_replace, t_env_var *env_head)
{
	t_token	*old_next;
	t_token	*new;
	t_token	*head;
	char	**words;
	char	*expanded_node_string;
	int		i;
	//int		len;
	
	// i = 0;
	// len = env_var_name_length(node_to_replace->string);
	// printf("the length of the valid var: %i\n", len);
	// while (node_to_replace->string[i] && node_to_replace->string[i] != '$')
	// 	i++;
	// if (node_to_replace->string[i])
	// 	printf("the char to check: %c\n", node_to_replace->string[i]);
	// if (node_to_replace->string[i - 1])
	// 	printf("the char ervoor to check: %c\n", node_to_replace->string[i - 1]);
	// if (node_to_replace->string[len + 2])
	// 	printf("the char erna to check: %c\n", node_to_replace->string[len + 2]);
	// if (node_to_replace->string[i] != '\0' && node_to_replace->string[i - 1] == '\"' \
	// 		&& node_to_replace->string[len + 2] == '\"')
	// 	return ;
	printf("ok\n");
	old_next = node_to_replace->next;
	expanded_node_string = expanded(node_to_replace->string, env_head);
	words = NULL;
	if (expanded_node_string)
	{
 		words = ft_split(expanded_node_string, ' ');
		if (!words)
			return ;
	}
	i = 0;
	head = *token_head;
	while (words[i])
	{
		new = create_token(words[i], 6);
		if (i == 0)
		{
			while (head->next && head != node_to_replace)
				head = head->next;
			if (head->previous)
				head = head->previous; // go to the node before the node to replace
			head->next = new;
			new->previous = head;
		}
		else
			add_token_to_list(token_head, new);
		i++;
	}
	free_array(words);
	//free(node_to_replace);
	if (old_next)
		old_next->previous = new; // -a

	// ------------------- add link the previous next node -------------- //
	head = *token_head;
	while (head->next)
		head = head->next;
	head->next = old_next;
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
	//create new token
	//squeeze token in list
	new_string = third_clean(str);
	free(str);
	return (new_string);
}
/*
// printf("the expanded node string: %s\n", expanded_node_string);
//rintf("the new address of next in head: %p\n", head->next);
// printf("the address of the new token created: %p\n", new);
// printf("the string of the new token created: %s\n", new->string);
// printf("the new address previous in new: %p\n", new->previous);
// printf("the new token created: %p\n", new);
// printf("the new token string: %s\n", new->string);
// printf("the address of the old next created:%p\n", old_next);
 */