/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3g_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:51:39 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 14:59:22 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next_token;
	t_token	*new_tokens;
	t_token	*last_new_token;

	current = *head;
	while (current != NULL)
	{
		next_token = current->next;
		if ((current->type == 6 && current->previous == NULL)
			|| (current->type == 6
				&& current->previous && current->previous->type != D_SMALLER))
		{
			new_tokens = mini_tokenizer(current->string);
			last_new_token = new_tokens;
			while (last_new_token != NULL && last_new_token->next != NULL)
				last_new_token = last_new_token->next;
			replace_node(head, current, new_tokens);
			if (last_new_token != NULL)
				next_token = last_new_token->next;
			else
				next_token = NULL;
		}
		current = next_token;
	}
}

void	replace_node(t_token **head,
		t_token *node_to_replace, t_token *new_nodes)
{
	t_token	*last_new_node;

	if (new_nodes == NULL)
		return ;
	last_new_node = find_last_node(new_nodes);
	insert_new_nodes(head, node_to_replace, new_nodes, last_new_node);
	free_node(node_to_replace);
}

t_token	*find_last_node(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL && current->next != NULL)
		current = current->next;
	return (current);
}

void	insert_new_nodes(t_token **head, t_token *node_to_replace,
		t_token *new_nodes, t_token *last_new_node)
{
	if (*head == node_to_replace)
	{
		last_new_node->next = node_to_replace->next;
		if (node_to_replace->next != NULL)
			node_to_replace->next->previous = last_new_node;
		*head = new_nodes;
		new_nodes->previous = NULL;
	}
	else
	{
		if (node_to_replace->previous != NULL)
		{
			node_to_replace->previous->next = new_nodes;
			new_nodes->previous = node_to_replace->previous;
		}
		last_new_node->next = node_to_replace->next;
		if (node_to_replace->next != NULL)
			node_to_replace->next->previous = last_new_node;
	}
}

void	free_node(t_token *node)
{
	free(node->string);
	free(node);
}

// void replace_node(t_token **head,
// t_token *node_to_replace, t_token *new_nodes) 
// {
//     t_token *last_new_node;

//     if (new_nodes == NULL)
//         return;
//     last_new_node = new_nodes;
//     while (last_new_node->next != NULL)
//         last_new_node = last_new_node->next;
//     // Handling the case where the head is the node to be replaced
//     if (*head == node_to_replace) 
//     {
//         last_new_node->next = node_to_replace->next;
//         if (node_to_replace->next != NULL)
//             node_to_replace->next->previous = last_new_node;
//         *head = new_nodes;
//         new_nodes->previous = NULL;
//     } 
//     else 
//     {
//         if (node_to_replace->previous != NULL) 
//         {
//             node_to_replace->previous->next = new_nodes;
//             new_nodes->previous = node_to_replace->previous;
//         }
//         last_new_node->next = node_to_replace->next;
//         if (node_to_replace->next != NULL)
//             node_to_replace->next->previous = last_new_node;
//     }
//     free(node_to_replace->string);
//     free(node_to_replace);
// }
