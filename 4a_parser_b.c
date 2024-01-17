/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4a_parser_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:20:54 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:38:59 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(t_token *token)
{
	if (token->type == GREATER)
		return (GREATER);
	else if (token->type == D_GREATER)
		return (D_GREATER);
	else if (token->type == SMALLER)
		return (SMALLER);
	else if (token->type == D_SMALLER)
		return (D_SMALLER);
	else
		return (0);
}

void	parse_redirection(t_token **current, t_cmd *command)
{
	t_redir	*new_redir;

	new_redir = create_redirection_node(current);
	append_redirection(command, new_redir);
}

t_redir	*create_redirection_node(t_token **current)
{
	t_redir	*new_redir;

	if (!(*current)->next)
	{
		ft_putendl_fd("Syntax error: missing filename for redirection\n", 2);
		exit(EXIT_FAILURE);
	}
	new_redir = ft_malloc(sizeof(t_redir));
	new_redir->type = (*current)->type;
	new_redir->file = ft_strdup((*current)->next->string);
	new_redir->next = NULL;
	*current = (*current)->next->next;
	return (new_redir);
}

void	append_redirection(t_cmd *command, t_redir *new_redir)
{
	t_redir	*last_redir;

	if (!command->redir)
		command->redir = new_redir;
	else
	{
		last_redir = command->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
}
